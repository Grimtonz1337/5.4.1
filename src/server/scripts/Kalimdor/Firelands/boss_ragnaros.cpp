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

enum Yells //need texts
{
    //Ragnaros
    SAY_AGGRO = -0, //sound id 24517
    SAY_DEATH = -0, //sound id 24519
    SAY_KILL_1 = -0, //sound id 24531
    SAY_KILL_2 = -0, //sound id 24530
    SAY_KILL_3 = -0, //sound id 24529
    SAY_HAMMER_DROP_1 = -0, //sound id 24520
    SAY_HAMMER_DROP_2 = -0, //sound id 24521
    SAY_HAMMER_DROP_3 = -0, //sound id 24522
    SAY_HAMMER_PICKUP_1 = -0, //sound id 24523
    SAY_HAMMER_PICKUP_2 = -0, //sound id 24524
    SAY_HAMMER_PICKUP_3 = -0, //sound id 24525
    SAY_PURGE = -0, //sound id 24532

    //Thrall on Heroic
    SAY_DIALOG_1 = -0,
    SAY_DIALOG_2 = -0,
};

enum Spells
{
    //ragnaros
    SPELL_SULFURAS_SMASH = 98710,
    SPELL_LIVING_METEOR = 99268, //every difficult
    SPELL_WRATH_OF_RAGNAROS = 98263,
    SPELL_MAGMA_SMASH = 98313,
    SPELL_CLEAVING_BLOW = 98951, //on 40% hp
    SPELL_BURNING_WOUND = 99399,
    SPELL_MAGMA_TRAP = 98164, //every difficult
    SPELL_LAVA_WAVE = 100293,
    SPELL_HAND_OF_RAGNAROS = 98237,

    //living meteor
    SPELL_METEOR_CRASH = 99287, //10 player normal
};

enum Events //non heroic
{
    //Basic Event
    EVENT_SULFURAS_SMASH = 0,
    EVENT_HAMMER_DROP = 1,
    EVENT_GO_DOWN = 2,
    EVENT_GO_UP = 3,
    EVENT_HAMMER_PICKUP = 4,

    //Sulfuras Hammer Event
    EVENT_PULL_ADDS = 3,
    EVENT_KILL_PLAYERS = 4,

    //Events while Ragnaros is down
    EVENT_SUMMON_ADDS_1 = 5,
    EVENT_SUMMON_ADDS_2 = 6,

};

enum Phase
{
    PHASE_ONE = 1,
    PHASE_TWO = 2,
    PHASE_THREE = 3,
    PHASE_FOUR = 4,
    PHASE_FIVE = 5,
};

/*
void AddSC_boss_ragnaros_cata()
{
    new boss_ragnaros_cata();
    new npc_living_meteor();
}

*/