/* Copyright (C) 2010-2013 OpenEmu <http://www.openemulator.com/>
*
* This file is free software; as a special exception the author gives
* unlimited permission to copy and/or distribute it, with or without
* modifications, as long as this notice is preserved.
*
* This program is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
* implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*
*/

#include "ObjectMgr.h"
#include "ScriptMgr.h"
#include "Object.h"
#include "Player.h"
#include "GameObject.h"
#include "GameObjectAI.h"
#include "Unit.h"
#include "UnitAI.h"
#include "ScriptedCreature.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "Spell.h"
#include "timeless_isle.h"

class npc_cinderfall : public CreatureScript
{
public:
    npc_cinderfall() : CreatureScript("npc_cinderfall") { }

    struct npc_cinderfallAI : public ScriptedAI
    {
        npc_cinderfallAI(Creature* creature) : ScriptedAI(creature) {	}

        uint32 MoltenInfernoTimer; // the only spell
        uint8 MoltenInfernoChoice; // 4 spells, choose one

        void Reset() OVERRIDE
        {
        	MoltenInfernoTimer = 2000;
        	InCombat = false;

        	me->SetReactState(REACT_AGGRESSIVE);
        	me->AddUnitState(UNIT_STATE_CANNOT_AUTOATTACK);
        }

        void EnterCombat(Unit* target) OVERRIDE
        {
        	InCombat = true;

        	me->SetFacingToObject(target);
        }

        void UpdateAI(uint32 diff) OVERRIDE
        {
        	if (!UpdateVictim())
        		return;

        	if (!InCombat)
        		return;

        	if (MoltenInfernoTimer <= diff)
        	{
        		MoltenInfernoChoice = urand(1, 4);

        		switch (MoltenInfernoChoice)
        		{
        			case 1:
        				DoCastAOE(SPELL_MOLTEN_INFERNO_1, false);
        				break;

        			case 2:
        				DoCastAOE(SPELL_MOLTEN_INFERNO_2, false);
        				break;

        			case 3:
        				DoCastAOE(SPELL_MOLTEN_INFERNO_3, false);
        				break;

        			case 4:
        				DoCastAOE(SPELL_MOLTEN_INFERNO_4, false);
        				break;
        			default:
        				break;
        		}

        		MoltenInfernoTimer = urand(3000, 5000);
        	}

        	else
        		MoltenInfernoTimer -= diff;
        }

    private:
    	bool InCombat;
    };

    CreatureAI* GetAI(Creature* creature) const OVERRIDE
    {
        return new npc_cinderfallAI(creature);
    }
};

class npc_huolon : public CreatureScript
{
public:
    npc_huolon() : CreatureScript("npc_huolon") { }

    struct npc_huolonAI : public ScriptedAI
    {
        npc_huolonAI(Creature* creature) : ScriptedAI(creature) {	}

        uint32 LightningBreathTimer;
        uint32 StormBlossomTimer;

        void Reset() OVERRIDE
        {
        	LightningBreathTimer = 6000;
        	StormBlossomTimer = 8000;
        	InCombat = false;

        	me->SetReactState(REACT_AGGRESSIVE);
        }

        void EnterCombat(Unit* /*target*/) OVERRIDE
        {
        	InCombat = true;
        }

        void UpdateAI(uint32 diff) OVERRIDE
        {
        	if (!UpdateVictim())
        		return;

        	if (!InCombat)
        		return;

        	if (LightningBreathTimer <= diff)
        	{
        		DoCastAOE(SPELL_LIGHTNING_BREATH, false);

        		LightningBreathTimer = urand(9000, 12000);
        	}

        	else
        		LightningBreathTimer -= diff;

        	if (StormBlossomTimer <= diff)
        	{
        		if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.0f, true))
        		{
        			/* DoCast(target, SPELL_STORM_BLOSSOM); */

        			StormBlossomTimer = 15000;
        		}
        	}

        	else
        		StormBlossomTimer -= diff;

        	DoMeleeAttackIfReady();
        }

    private:
    	bool InCombat;
    };

    CreatureAI* GetAI(Creature* creature) const OVERRIDE
    {
        return new npc_huolonAI(creature);
    }
};

class npc_imperial_python : public CreatureScript
{
public:
    npc_imperial_python() : CreatureScript("npc_imperial_python") { }

    struct npc_imperial_pythonAI : public ScriptedAI
    {
        npc_imperial_pythonAI(Creature* creature) : ScriptedAI(creature) {	}

        uint32 HugeFangTimer;

        void Reset() OVERRIDE
        {
        	HugeFangTimer = 2000;
        	InCombat = false;

        	me->SetReactState(REACT_AGGRESSIVE);
        	me->AddUnitState(UNIT_STATE_CANNOT_AUTOATTACK);
        }

        void EnterCombat(Unit* /*target*/) OVERRIDE
        {
        	InCombat = true;
        }

        void UpdateAI(uint32 diff) OVERRIDE
        {
        	if (!UpdateVictim())
        		return;

        	if (!InCombat)
        		return;

        	if (HugeFangTimer <= diff)
        	{
        		DoCastVictim(SPELL_HUGE_FANG, false);

        		HugeFangTimer = 5000;
        	}

        	else
        		HugeFangTimer -= diff;
        }

    private:
    	bool InCombat;
    };

    CreatureAI* GetAI(Creature* creature) const OVERRIDE
    {
        return new npc_imperial_pythonAI(creature);
    }
};

class npc_emerald_gander : public CreatureScript
{
public:
    npc_emerald_gander() : CreatureScript("npc_emerald_gander") { }

    struct npc_emerald_ganderAI : public ScriptedAI
    {
        npc_emerald_ganderAI(Creature* creature) : ScriptedAI(creature) {	}

        uint32 GustofWindTimer;

        void Reset() OVERRIDE
        {
        	GustofWindTimer = urand(6000, 9000);

        	me->SetReactState(REACT_AGGRESSIVE);
        }

        void EnterCombat(Unit* /*target*/) OVERRIDE
        {
        	InCombat = true;

        	DoCast(me, SPELL_WINDFEATHER);
        }

        void UpdateAI(uint32 diff) OVERRIDE // TODO: find when does Healing Song being cast and script it
        {
        	if (!UpdateVictim())
        		return;

        	if (!InCombat)
        		return;

        	if (GustofWindTimer <= diff)
        	{
        		DoCastAOE(SPELL_GUST_OF_WIND, false);

        		GustofWindTimer = urand(12000, 16000);
        	}

        	else
        		GustofWindTimer -= diff;

        	DoMeleeAttackIfReady();
        }

    private:
    	bool InCombat;
    };

    CreatureAI* GetAI(Creature* creature) const OVERRIDE
    {
        return new npc_emerald_ganderAI(creature);
    }
};

class npc_golganarr : public CreatureScript
{
public:
    npc_golganarr() : CreatureScript("npc_golganarr") { }

    struct npc_golganarrAI : public ScriptedAI
    {
        npc_golganarrAI(Creature* creature) : ScriptedAI(creature) {	}

        uint32 BoulderTimer;
        uint32 StompTimer;
        uint32 FrenzyTimer;

        void Reset() OVERRIDE
        {
        	BoulderTimer = urand(8000, 11000);
        	StompTimer = 14500;
        	FrenzyTimer = 30000;

        	InCombat = false;

        	me->SetReactState(REACT_AGGRESSIVE);
        }

        void EnterCombat(Unit* /*target*/) OVERRIDE
        {
        	InCombat = true;
        }

        void SpellHit(Unit* caster, SpellInfo const* spell) OVERRIDE
        {
            if (spell->Id == SPELL_FRENZY)
            	DoSpellAttackIfReady(SPELL_STOMP_FRENZY);
        }

        void JustRespawned() OVERRIDE
        {
            ScriptedAI::JustRespawned();
            
            me->YellToZone(SAY_SPAWN, LANG_UNIVERSAL, 0);
        }

        void UpdateAI(uint32 diff) OVERRIDE
        {
        	if (!UpdateVictim())
        		return;

        	if (!InCombat)
        		return;

        	if (BoulderTimer <= diff)
        	{
        		if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.0f, true))
        		{
        			if (!me->HasAura(SPELL_FRENZY))
	        			DoCast(target, SPELL_BOULDER);

	        		else
	        			DoCast(target, SPELL_BOULDER_FRENZY);
        		}

	        	BoulderTimer = urand(15000, 25000);
        	}

        	else
        		BoulderTimer -= diff;

        	if (StompTimer <= diff)
        	{
        		DoCastAOE(SPELL_STOMP, false);

        		StompTimer = urand(6000, 11000);
        	}

        	else
        		StompTimer -= diff;

        	if (FrenzyTimer <= diff)
        	{
        		DoCast(me, SPELL_FRENZY);

        		FrenzyTimer = urand(40000, 60000);
        	}

        	else
        		FrenzyTimer -= diff;

        	DoMeleeAttackIfReady();
        }

    private:
    	bool InCombat;
    };

    CreatureAI* GetAI(Creature* creature) const OVERRIDE
    {
        return new npc_golganarrAI(creature);
    }
};

class npc_watcher_osu : public CreatureScript
{
public:
    npc_watcher_osu() : CreatureScript("npc_watcher_osu") { }

    struct npc_watcher_osuAI : public ScriptedAI
    {
        npc_watcher_osuAI(Creature* creature) : ScriptedAI(creature) {	}

        uint32 FallingFlamesTimer;
        uint32 PyroblastTimer;

        void Reset() OVERRIDE
        {
        	FallingFlamesTimer = urand(9000, 15000);
        	PyroblastTimer = 7500;

        	InCombat = false;

        	me->SetReactState(REACT_AGGRESSIVE);
        }

        void EnterCombat(Unit* /*target*/) OVERRIDE
        {
        	InCombat = true;
        }

        void UpdateAI(uint32 diff) OVERRIDE
        {
        	if (!UpdateVictim())
        		return;

        	if (!InCombat)
        		return;

        	if (FallingFlamesTimer <= diff)
        	{
        		DoCastAOE(SPELL_FALLING_FLAMES, false);

        		FallingFlamesTimer = urand(15000, 22000);
        	}

        	else
        		FallingFlamesTimer -= diff;

        	if (PyroblastTimer <= diff)
        	{
        		DoCastVictim(SPELL_PYROBLAST, false);

        		PyroblastTimer = urand(9000, 16000);
        	}

        	else
        		PyroblastTimer -= diff;

        	DoMeleeAttackIfReady();
        }

    private:
    	bool InCombat;
    };

    CreatureAI* GetAI(Creature* creature) const OVERRIDE
    {
        return new npc_watcher_osuAI(creature);
    }
};

class npc_tsavoka : public CreatureScript
{
public:
    npc_tsavoka() : CreatureScript("npc_tsavoka") { }

    struct npc_tsavokaAI : public ScriptedAI
    {
        npc_tsavokaAI(Creature* creature) : ScriptedAI(creature) {	}

        uint32 GreaterSwipeTimer;
        uint32 DefensiveLeapTimer;
        uint32 LeapDone;
        uint32 StunTimer;
        uint8 LeapOrNot;

        bool Leaped;

        void Reset() OVERRIDE
        {
        	GreaterSwipeTimer = urand(6000, 8000);
        	DefensiveLeapTimer = urand(11000, 13500);

        	InCombat = false;
        	Leaped = false;

        	me->SetReactState(REACT_AGGRESSIVE);
        }

        void EnterCombat(Unit* target) OVERRIDE
        {
        	InCombat = true;

        	LeapOrNot = urand(1, 2);

        	if (LeapOrNot == 1)
        		DoCast(target, SPELL_POUNCE_LEAP);

        	else if (LeapOrNot == 2)
        		me->Attack(target, true);
        }

        void SpellHitTarget(Unit* target, SpellInfo const* spell)
        {
        	if (target->GetTypeId() == TYPEID_PLAYER && target->IsAlive() && spell->Id == SPELL_POUNCE_LEAP)
        		StunTimer = 3000;
        }

        void UpdateAI(uint32 diff) OVERRIDE
        {
        	if (!UpdateVictim())
        		return;

        	if (!InCombat)
        		return;

        	if (GreaterSwipeTimer <= diff)
        	{
        		DoCastAOE(SPELL_GREATER_SWIPE, false);

        		GreaterSwipeTimer = urand(9000, 14000);
        	}

        	else
        		GreaterSwipeTimer -= diff;

        	if (DefensiveLeapTimer <= diff)
        	{
        		DoCast(me, SPELL_DEFENSIVE_LEAP);

        		LeapDone = 3000;
        		DefensiveLeapTimer = urand(10000, 16000);
        	}

        	else
        		DefensiveLeapTimer -= diff;

        	if (LeapDone <= diff)
        		DoCastVictim(SPELL_POUNCE_LEAP, false);

        	else
        		LeapDone -= diff;

        	if (StunTimer <= diff)
        		DoCastVictim(SPELL_POUNCE_STUN, true);

        	else
        		StunTimer -= diff;

        	DoMeleeAttackIfReady();
        }

    private:
    	bool InCombat;
    };

    CreatureAI* GetAI(Creature* creature) const OVERRIDE
    {
        return new npc_tsavokaAI(creature);
    }
};

void AddSC_timeless_isle()
{
	new npc_cinderfall();
	new npc_huolon();
	new npc_imperial_python();
	new npc_emerald_gander();
	new npc_golganarr();
	new npc_watcher_osu();
	new npc_tsavoka();
}
