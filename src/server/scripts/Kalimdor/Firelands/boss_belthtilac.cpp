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
    SAY_SOFT_ENRAGE                                 = -1999972, //TODO Add Sound
    SAY_ON_DOGS_FALL                             = -1999973, //TODO Add Sound
    SAY_ON_DEAD                                     = -1999974, //TODO Add Sound
};

enum Spells
{
    // Bethilac
    // Phase 1
    SPELL_EMBER_FLARE = 98934, // And Phase 2
    SPELL_METEOR_BURN = 99076,
    SPELL_CONSUME = 99304, // And Cinderweb Drone and Phase 2
    SPELL_SMOLDERING_DEVASTATION = 99052,

    // Phase 2
    SPELL_FRENZY = 23537,
    SPELL_THE_WIDOWS_KISS = 99506,

    // Ciderweb Spinner
    SPELL_BURNING_ACID = 98471, // And Cinderweb Drone
    SPELL_FIERY_WEB_SPIN_H = 97202,

    // Cinderweb Drone
    SPELL_BOILING_SPLATTER = 0, // ID ?
    SPELL_FIXATE_H = 49026,

    //Cinderweb Spiderling
    SPELL_SEEPING_VENOM = 97079,

    // Engorged Broodling
    SPELL_VOLATILE_BURST_H = 99990,
};

enum Events
{
    EVENT_SUMMON_CINDERWEB_SPINNER = 1,
    EVENT_SPINNER_BURNING_ACID = 2,
};

Position const CinderwebSummonPos[7] =
{
    {55.614f, 385.11f, 0, 0},
    {61.906f, 352.12f, 0, 0},
    {49.118f, 352.12f, 0, 0},
    {36.080f, 357.46f, 0, 0},
    {28.873f, 372.63f, 0, 0},
    {32.848f, 382.93f, 0, 0},
    {39.499f, 393.54f, 0, 0}
};

// Grounds
const float groundLow = 74.042f;
const float groundUp = 111.767f;

// Event Timers
const int timerSummonCinderwebSpinner = 11000;
const int timerSpinnerBurningAcid = 7000;

/**** Beth'ilac ****/
