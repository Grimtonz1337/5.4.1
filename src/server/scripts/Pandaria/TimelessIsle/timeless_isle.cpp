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

        	if (me->isDead())
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

        	if (me->isDead())
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

        	if (me->isDead())
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

        	if (me->isDead())
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

        	if (me->isDead())
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

        	if (me->isDead())
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

        	if (me->isDead())
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
        	{
        		if (me->IsWithinMeleeRange(me->GetVictim()))
        			DoCastVictim(SPELL_POUNCE_STUN, true);

        		else if (!me->IsWithinMeleeRange(me->GetVictim()))
        			return;
        	}

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

class npc_spirit_of_jadefire : public CreatureScript
{
public:
    npc_spirit_of_jadefire() : CreatureScript("npc_spirit_of_jadefire") { }

    struct npc_spirit_of_jadefireAI : public ScriptedAI
    {
        npc_spirit_of_jadefireAI(Creature* creature) : ScriptedAI(creature) {	}

        uint32 JadefireBoltTimer;
        uint32 JadeflameStrikeTimer;

        void Reset() OVERRIDE
        {
        	JadefireBoltTimer = 3500;
        	JadeflameStrikeTimer = 8000;

        	InCombat = false;

        	me->SetReactState(REACT_AGGRESSIVE);
        }

        void EnterCombat(Unit* /*target*/)
        {
        	InCombat = true;
        }

        void UpdateAI(uint32 diff) OVERRIDE
        {
        	if (!UpdateVictim())
        		return;

        	if (!InCombat)
        		return;

        	if (me->isDead())
        		return;

        	if (JadefireBoltTimer <= diff)
        	{
        		DoCastVictim(SPELL_JADEFIRE_BOLT, false);

        		JadefireBoltTimer = urand(5000, 6000);
        	}

        	else
        		JadefireBoltTimer -= diff;

        	if (JadeflameStrikeTimer <= diff)
        	{
        		DoCastAOE(SPELL_JADEFLAME_STRIKE, false);

        		JadeflameStrikeTimer = urand(10000, 15000);
        	}

        	else
        		JadeflameStrikeTimer -= diff;

        	DoMeleeAttackIfReady();
        }

    private:
    	bool InCombat;
    };

    CreatureAI* GetAI(Creature* creature) const OVERRIDE
    {
        return new npc_spirit_of_jadefireAI(creature);
    }
};

class npc_monstrous_spineclaw : public CreatureScript
{
public:
    npc_monstrous_spineclaw() : CreatureScript("npc_monstrous_spineclaw") { }

    struct npc_monstrous_spineclawAI : public ScriptedAI
    {
        npc_monstrous_spineclawAI(Creature* creature) : ScriptedAI(creature) {	}

        uint32 ClawFlurryTimer;

        void Reset() OVERRIDE
        {
        	ClawFlurryTimer = urand(6000, 8000);

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

        	if (me->isDead())
        		return;

        	if (ClawFlurryTimer <= diff)
        	{
        		DoCastAOE(SPELL_CLAW_FLURRY, false);

        		ClawFlurryTimer = urand(7000, 8000);
        	}

        	else
        		ClawFlurryTimer -= diff;

        	DoMeleeAttackIfReady();
        }

    private:
    	bool InCombat;
    };

    CreatureAI* GetAI(Creature* creature) const OVERRIDE
    {
        return new npc_monstrous_spineclawAI(creature);
    }
};

class npc_great_turtle_furyshell : public CreatureScript
{
public:
    npc_great_turtle_furyshell() : CreatureScript("npc_great_turtle_furyshell") { }

    struct npc_great_turtle_furyshellAI : public ScriptedAI
    {
        npc_great_turtle_furyshellAI(Creature* creature) : ScriptedAI(creature) {	}

        uint32 GeyserTimer;
        uint32 ShellSpinTimer;
        uint32 SnappingBiteTimer;

        void Reset() OVERRIDE
        {
        	GeyserTimer = urand(4000, 6000);
        	ShellSpinTimer = urand(5000, 7000);
        	SnappingBiteTimer = 12000;

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

        	if (me->isDead())
        		return;

        	if (GeyserTimer <= diff)
        	{
        		DoCastVictim(SPELL_GEYSER, false);

        		GeyserTimer = urand(10000, 14000);
        	}

        	else
        		GeyserTimer -= diff;

        	if (ShellSpinTimer <= diff)
        	{
        		DoCastAOE(SPELL_SHELL_SPIN, false);

        		ShellSpinTimer = urand(11000, 15000);
        	}

        	else
        		ShellSpinTimer -= diff;

        	if (SnappingBiteTimer <= diff)
        	{
        		DoCastVictim(SPELL_SNAPPING_BITE, false);

        		SnappingBiteTimer = urand(10000, 18000);
        	}

        	else
        		SnappingBiteTimer -= diff;

        	DoMeleeAttackIfReady();
        }

    private:
    	bool InCombat;
    };

    CreatureAI* GetAI(Creature* creature) const OVERRIDE
    {
        return new npc_great_turtle_furyshellAI(creature);
    }
};

class npc_ironfur_steelhorn : public CreatureScript
{
public:
    npc_ironfur_steelhorn() : CreatureScript("npc_ironfur_steelhorn") { }

    struct npc_ironfur_steelhornAI : public ScriptedAI
    {
        npc_ironfur_steelhornAI(Creature* creature) : ScriptedAI(creature) {	}

        uint32 HeadbuttTimer;
        uint32 IronFurTimer;
        uint32 OxChargeTimer;
        uint32 OxChargeStunTimer;

        void Reset() OVERRIDE
        {
        	HeadbuttTimer = 6000;
        	IronFurTimer = urand(8000, 10000);
        	OxChargeTimer = urand(7500, 12500);

        	InCombat = false;
        	Charged = false;

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

        	if (me->isDead())
        		return;

        	if (HeadbuttTimer <= diff)
        	{
        		DoCastAOE(SPELL_HEADBUTT);

        		HeadbuttTimer = urand(8000, 12000);
        	}

        	else
        		HeadbuttTimer -= diff;

        	if (IronFurTimer <= diff)
        	{
        		DoCast(me, SPELL_IRON_FUR);

        		IronFurTimer = urand(17000, 22000);
        	}

        	else
        		IronFurTimer -= diff;

        	if (OxChargeTimer <= diff)
        	{
        		DoCastVictim(SPELL_OX_CHARGE, false);

        		OxChargeTimer = urand(12000, 16500);
        		OxChargeStunTimer = 3000;
        	}

        	else
        		OxChargeTimer -= diff;

        	if (OxChargeStunTimer <= diff)
        	{
        		if (!Charged)
        			Charged = true;

        		if (me->IsWithinMeleeRange(me->GetVictim()))
        			DoCastVictim(SPELL_OX_CHARGE_STUN);

        		else if (!me->IsWithinMeleeRange(me->GetVictim()))
        			return;
        	}

        	else
        		OxChargeStunTimer -= diff;

        	DoMeleeAttackIfReady();
        }

    private:
    	bool InCombat;
    	bool Charged;
    };

    CreatureAI* GetAI(Creature* creature) const OVERRIDE
    {
        return new npc_ironfur_steelhornAI(creature);
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
	new npc_spirit_of_jadefire();
	new npc_monstrous_spineclaw();
	new npc_great_turtle_furyshell();
	new npc_ironfur_steelhorn();
}
