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

enum Yells
{
    SAY_AGGRO                                    = -1999971,
    SAY_ON_DEAD                                     = -1999974 //TODO Add Sound
};

enum Spells
{
    SPELL_CAT_FORM                                 = 98374,
    SPELL_SCORPION_FORM                             = 98379,

    SPELL_ADRENALINE                             = 97238,
    SPELL_BERSERK                                 = 26662,
    SPELL_BURNING_ORBS                             = 98451,
    SPELL_FIERY_CYCLONE                             = 98443,
    SPELL_FLAME_SCYTE                             = 98474, // 10N
    SPELL_FURY                                     = 97235,
    SPELL_LEAPING_FLAMES                         = 98476,
    SPELL_LEAPING_FLAMES_SUMMON                     = 101222,
    SPELL_SEARING_SEEDS                             = 98450,
};

enum Events
{
    EVENT_LEAPING_FLAMES = 1,
    EVENT_BERSERK         = 2,
    EVENT_SWITCH_TO_NEXT_FORM = 3,
};

enum MajordomoPhase
{
    PHASE_DRUID,
    PHASE_CAT,
    PHASE_SCORPION
};

enum Misc
{
    DISPLAYID_DRUID                                  = 37953, 
    DISPLAYID_CAT                                  = 38747, // The two animals Display ids are needed
    DISPLAYID_SCORPION                              = 36617,  // because they are not handled through the spells
};

/**** Majordomo Staghelm ****/