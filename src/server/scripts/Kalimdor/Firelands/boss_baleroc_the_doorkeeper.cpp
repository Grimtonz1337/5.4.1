/*
 * Copyright (C) 2013 OpenEmulator <http://www.openemulator.com/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "ScriptPCH.h"
#include "firelands.h"
/* Base script for Baleroc the Gatekeeper, a warning that this will be unstable at first
SDComp: 15%
Todo: Implement sound/text, implement shards of glory.
*/

enum SpellIds
{
    SPELL_BERSERK = 26662,
    SPELL_BLAZE_OF_GLORY = 99252,
    SPELL_INCENDIARY_SOUL = 99369,
    SPELL_DECIMATION_BLADE = 99353,
    SPELL_INFERNO_BLADE = 99351,
};

class boss_baleroc : public CreatureScript
{
public:
    boss_baleroc() : CreatureScript("boss_baleroc") { }
  
    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_balerocAI(pCreature);
    }

    struct boss_balerocAI : public ScriptedAI
    {
        boss_balerocAI(Creature *c) : ScriptedAI(c) { }

        uint32 BlazeOfGloryTimer;
        uint32 DecimationBladeTimer;
        uint32 InfernoBladeTimer;
        uint32 IncendiarySoulTimer;
        uint32 BerserkTimer;
   
        void Reset()
        {
            BlazeOfGloryTimer = 100;
            DecimationBladeTimer = 100; // These timers are probably wrong.
            InfernoBladeTimer = 40000;
            IncendiarySoulTimer = 0;
            BerserkTimer = 360000;
        }

       void KilledUnit(Unit * /*victim*/)
       {
           me->MonsterYell("You have been judged.", LANG_UNIVERSAL, NULL);
       }

       void EnterCombat(Unit * /*who*/)
       {
           me->MonsterYell("You are forbidden from my master's domain, mortals.", LANG_UNIVERSAL, NULL); // Sound NYI
       }

       void UpdateAI(uint32 uiDiff)
       {
           if (!UpdateVictim())
               return;

           if (BlazeOfGloryTimer <= uiDiff)
           {
               DoCastVictim(SPELL_BLAZE_OF_GLORY);
               BlazeOfGloryTimer = 10000;
           }
           else
               BlazeOfGloryTimer -= uiDiff;
           
           if (DecimationBladeTimer <= uiDiff)
           {
               DoCastVictim(SPELL_DECIMATION_BLADE);
               DecimationBladeTimer = 15000;
           }
           else
               DecimationBladeTimer -= uiDiff;
           
           if (InfernoBladeTimer <= uiDiff)
           {
               DoCastVictim(SPELL_INFERNO_BLADE);
               InfernoBladeTimer = 60000;
           }
           else
               InfernoBladeTimer -= uiDiff;
           
           if (BerserkTimer <= uiDiff)
               DoCast(me, SPELL_BERSERK);
           else
               BerserkTimer -= uiDiff;
           DoMeleeAttackIfReady();
       }
    };
};

void AddSC_boss_baleroc()
{
    new boss_baleroc();
}