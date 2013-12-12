/*
 * Copyright (C) 2008-2013 TrinityCore <http://www.trinitycore.org/>
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

#ifndef __BATTLEGROUNDTK_H
#define __BATTLEGROUNDTK_H

#include "Language.h"
#include "Battleground.h"

// MAP OF Temple of Kotmogu
/* ########################################################################## */
/* #                                                                        # */
/* #                               Z1                                       # */
/* #                                                                        # */
/* #                                                                        # */
/* #--------*******************************************************---------# */
/* #        *                    |-----------|                    *         # */
/* #        *                    |-----------|                    *         # */
/* #        *                      Z2                             *         # */
/* #        *       __                                __          *         # */
/* #        *      |__|                              |__|         *         # */
/* #        *                                                     *         # */
/* #        *                   ***************                   *         # */
/* #        *                   *  Z3         *                   *         # */
/* #   H    *                   *      -      *                   *     A   # */
/* #        *                   *   [  O  ]   *                   *         # */
/* #        *                   *      -      *                   *         # */
/* #        *                   *             *                   *         # */
/* #        *                   ***************                   *         # */
/* #        *       __                                __          *         # */
/* #        *      |__|                              |__|         *         # */
/* #        *                      Z2                             *         # */
/* #        *                    |-----------|                    *         # */
/* #        *                    |-----------|                    *         # */
/* #--------*******************************************************---------# */
/* #                                                                        # */
/* #                               Z1                                       # */
/* #                                                                        # */
/* #                                                                        # */
/* ########################################################################## */

#define BG_TK_MAX_TEAM_SCORE      1600
#define BG_TK_ORB_POINTS_MAX      1600
#define BG_TK_ORB_RESPAWN_TIME    (23*IN_MILLISECONDS)
#define BG_TK_ORB_DROP_TIME       (10*IN_MILLISECONDS)
#define BG_TK_TIME_LIMIT          (25*MINUTE*IN_MILLISECONDS)
#define BG_TK_EVENT_START_BATTLE  8563

#define BG_TK_NotEYWeekendHonorTicks    260
#define BG_TK_EYWeekendHonorTicks       160

#define TK_EVENT_START_BATTLE           13180 // Achievement: Flurry

enum BG_TK_OBJECT
{
    //orbs
    BG_TK_OBJECT_ORB1                    = 210656,         //GREEN ORB
    BG_TK_OBJECT_ORB2                    = 210656,         //ORANGE ORB
    BG_TK_OBJECT_ORB3                    = 210656,         //PURPLE ORB
    BG_TK_OBJECT_ORB4                    = 210656,         //YELLOW ORB
    BG_TK_OBJECT_PILLAR                  = 210656,         //ORB PILLAR
    //gates
    BG_TK_OBJECT_GATE_A                  = 40,
    BG_TK_OBJECT_GATE_H                  = 41,
    //buffs
    BG_TK_OBJECT_SPEEDBUFF_ORB1          = 42,         //GREEN ORB CORNER
    BG_TK_OBJECT_REGENBUFF_ORB1          = 43,         //GREEN ORB CORNER
    BG_TK_OBJECT_BERSERKBUFF_ORB1        = 44,         //GREEN ORB CORNER
    BG_TK_OBJECT_SPEEDBUFF_ORB2          = 45,         //ORANGE ORB CORNER
    BG_TK_OBJECT_REGENBUFF_ORB2          = 46,         //ORANGE ORB CORNER
    BG_TK_OBJECT_BERSERKBUFF_ORB2        = 47,         //ORANGE ORB CORNER
    BG_TK_OBJECT_SPEEDBUFF_ORB3          = 48,         //PURPLE ORB CORNER
    BG_TK_OBJECT_REGENBUFF_ORB3          = 49,         //PURPLE ORB CORNER
    BG_TK_OBJECT_BERSERKBUFF_ORB3        = 50,         //PURPLE ORB CORNER
    BG_TK_OBJECT_SPEEDBUFF_ORB4          = 51,         //YELLOW ORB CORNER
    BG_TK_OBJECT_REGENBUFF_ORB4          = 52,         //YELLOW ORB CORNER
    BG_TK_OBJECT_BERSERKBUFF_ORB4        = 53,         //YELLOW ORB CORNER
};    
    enum BG_TK_Sound
{
    BG_TK_SOUND_ORB_PLACED        = 8232,
    BG_TK_SOUND_A_ORB_PICKED_UP   = 8174,
    BG_TK_SOUND_H_ORB_PICKED_UP   = 8174,
    BG_TK_SOUND_ORB_RESPAWNED     = 8232
};

enum BG_TK_SpellId
{
    //ORB AURA
    BG_TK_SPELL_ORB1              = 121220,         //GREEN ORB
    BG_TK_SPELL_ORB2              = 121221,         //ORANGE ORB
    BG_TK_SPELL_ORB3              = 121219,         //PURPLE ORB
    BG_TK_SPELL_ORB4              = 121217,         //YELLOW ORB
    //ZONE BUFFS
    BG_TK_SPELL_ZONE1             = 121175,         //ZONE1 dmg taken by 30%. dmg done by 10%. heal received by 5%. 
    BG_TK_SPELL_ZONE2             = 112055,         //ZONE2 dmg taken by 50%. dmg done by 30%. heal received by 10%.
    BG_TK_SPELL_ZONE3             = 127959,         //ZONE3 dmg taken by 100%. dmg done by 30%. heal received by 30%.
    //ORB DROPPED
    BG_TK_SPELL_ORB_DROPPED       = 112839
};

enum BG_TK_WorldStates
{
    BG_TK_ICON_A                  = 6308,
    BG_TK_ICON_H                  = 6307,
    BG_TK_ORB_POINTS_A            = 6303,
    BG_TK_ORB_POINTS_H            = 6304,
    BG_TK_ORB_STATE               = 6309,
    BG_TK_TIME_ENABLED            = 4247,
    BG_TK_TIME_REMAINING          = 4248
};

enum BG_TK_OrbState
{
    BG_TK_ORB_STATE_ON_BASE       = 0,
    BG_TK_ORB_STATE_WAIT_RESPAWN  = 1,
    BG_TK_ORB_STATE_ON_PLAYER     = 2,
    BG_TK_ORB_STATE_ON_GROUND     = 3
};

enum BG_TK_Graveyards
{
    TK_GRAVEYARD_RECTANGLEA1      = 3552,
    TK_GRAVEYARD_RECTANGLEA2      = 4058,
    TK_GRAVEYARD_RECTANGLEH1      = 3553,
    TK_GRAVEYARD_RECTANGLEH2      = 4057,
};

enum BG_TK_Events
{
    TK_EVENT_ORB                  = 0,
    // spiritguides will spawn (same moment, like TP_EVENT_DOOR_OPEN)
    TK_EVENT_SPIRITGUIDES_SPAWN   = 2
};

//tick point according to which zone
const uint32 BG_TK_TickPoints[3] = {2, 4, 6};
const uint32 BG_TK_TickIntervals[2] = {0, 5};

class BattlegroundTKScore : public BattlegroundScore
{
    public:
        BattlegroundTKScore() : OrbHandles(0), VictoryPoints(0) {};
        virtual ~BattlegroundTKScore() {};

        uint32 OrbHandles;
        uint32 VictoryPoints;
};

class BattlegroundTK : public Battleground
{
    public:
        BattlegroundTK();
        ~BattlegroundTK();
};
#endif
