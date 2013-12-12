/*
 * Copyright (C) 2008-2013 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
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

#ifndef __BATTLEGROUNDBG_H
#define __BATTLEGROUNDBG_H

#include "Battleground.h"

enum BG_BG_WorldStates
{
    BG_BG_OP_OCCUPIED_BASES_HORDE       = 1778,
    BG_BG_OP_OCCUPIED_BASES_ALLY        = 1779,
    BG_BG_OP_RESOURCES_ALLY             = 1776,
    BG_BG_OP_RESOURCES_HORDE            = 1777,
    BG_BG_OP_RESOURCES_MAX              = 1780,
    BG_BG_OP_RESOURCES_WARNING          = 1955
/*
    BG_BG_OP_LIGHTHOUSE_ICON            = 1842,             //LIGHTHOUSE map icon (NONE)
    BG_BG_OP_LIGHTHOUSE_STATE_ALLIANCE  = 1767,             //LIGHTHOUSE map state (ALLIANCE)
    BG_BG_OP_LIGHTHOUSE_STATE_HORDE     = 1768,             //LIGHTHOUSE map state (HORDE)
    BG_BG_OP_LIGHTHOUSE_STATE_CON_ALI   = 1769,             //LIGHTHOUSE map state (CON ALLIANCE)
    BG_BG_OP_LIGHTHOUSE_STATE_CON_HOR   = 1770,             //LIGHTHOUSE map state (CON HORDE)

    BG_BG_OP_WATERWORKS_ICON            = 1845,             //WATERWORKS map icon (NONE)
    BG_BG_OP_WATERWORKS_STATE_ALLIANCE  = 1772,             //WATERWORKS state (ALLIANCE)
    BG_BG_OP_WATERWORKS_STATE_HORDE     = 1773,             //WATERWORKS state (HORDE)
    BG_BG_OP_WATERWORKS_STATE_CON_ALI   = 1774,             //WATERWORKS state (CON ALLIANCE)
    BG_BG_OP_WATERWORKS_STATE_CON_HOR   = 1775,             //WATERWORKS state (CON HORDE)

    BG_BG_OP_MINES_ICON                 = 1846,             //MINES map icon (NONE)
    BG_BG_OP_MINES_STATE_ALLIANCE       = 1782,             //MINES map state (ALLIANCE)
    BG_BG_OP_MINES_STATE_HORDE          = 1783,             //MINES map state (HORDE)
    BG_BG_OP_MINES_STATE_CON_ALI        = 1784,             //MINES map state (CON ALLIANCE)
    BG_BG_OP_MINES_STATE_CON_HOR        = 1785,             //MINES map state (CON HORDE)
*/
};

const uint32 BG_BG_OP_NODESTATES[5] =    {1767, 1782, 1772};

const uint32 BG_BG_OP_NODEICONS[5]  =    {1842, 1846, 1845};

/* Note: code uses that these IDs follow each other */
enum BG_BG_NodeObjectId
{
    BG_BG_OBJECTID_NODE_BANNER_0    = 208779,       // Light House
    BG_BG_OBJECTID_NODE_BANNER_1    = 208781,       // Waterworks
    BG_BG_OBJECTID_NODE_BANNER_2    = 208780,       // Mines
};

enum BG_BG_ObjectType
{
    // for all 5 node points 8*5=40 objects
    BG_BG_OBJECT_BANNER_NEUTRAL          = 0,
    BG_BG_OBJECT_BANNER_CONT_A           = 1,
    BG_BG_OBJECT_BANNER_CONT_H           = 2,
    BG_BG_OBJECT_BANNER_ALLY             = 3,
    BG_BG_OBJECT_BANNER_HORDE            = 4,
    BG_BG_OBJECT_AURA_ALLY               = 5,
    BG_BG_OBJECT_AURA_HORDE              = 6,
    BG_BG_OBJECT_AURA_CONTESTED          = 7,
    //gates
    BG_BG_OBJECT_GATE_A                  = 40,
    BG_BG_OBJECT_GATE_H                  = 41,
    //buffs
    BG_BG_OBJECT_SPEEDBUFF_LIGHTHOUSE    = 42,
    BG_BG_OBJECT_REGENBUFF_LIGHTHOUSE    = 43,
    BG_BG_OBJECT_BERSERKBUFF_LIGHTHOUSE  = 44,
    BG_BG_OBJECT_SPEEDBUFF_WATERWORKS    = 45,
    BG_BG_OBJECT_REGENBUFF_WATERWORKS    = 46,
    BG_BG_OBJECT_BERSERKBUFF_WATERWORKS  = 47,
    BG_BG_OBJECT_SPEEDBUFF_MINES         = 48,
    BG_BG_OBJECT_REGENBUFF_MINES         = 49,
    BG_BG_OBJECT_BERSERKBUFF_MINES       = 50,

    BG_BG_OBJECT_MAX                     = 51
};

/* Object id templates from DB */
enum BG_BG_ObjectTypes
{
    BG_BG_OBJECTID_BANNER_A             = 180058,
    BG_BG_OBJECTID_BANNER_CONT_A        = 180059,
    BG_BG_OBJECTID_BANNER_H             = 180060,
    BG_BG_OBJECTID_BANNER_CONT_H        = 180061,

    BG_BG_OBJECTID_AURA_A               = 180100,
    BG_BG_OBJECTID_AURA_H               = 180101,
    BG_BG_OBJECTID_AURA_C               = 180102,

    BG_BG_OBJECTID_GATE_A_1             = 207177,
    BG_BG_OBJECTID_GATE_A_2             = 180322,
    BG_BG_OBJECTID_GATE_H_1             = 207178,
    BG_BG_OBJECTID_GATE_H_2             = 180322
};

enum BG_BG_Timers
{
    BG_BG_FLAG_CAPTURING_TIME           = 60000
};

enum BG_BG_Score
{
    BG_BG_WARNING_NEAR_VICTORY_SCORE    = 1800,
    BG_BG_MAX_TEAM_SCORE                = 2000
};

/* do NOT change the order, else wrong behaviour */
enum BG_BG_BattlegroundNodes
{
    BG_BG_NODE_LIGHTHOUSE       = 0,
    BG_BG_NODE_WATERWORKS       = 1,
    BG_BG_NODE_MINES            = 2,

    BG_BG_DYNAMIC_NODES_COUNT   = 3,                        // dynamic nodes that can be captured

    BG_BG_SPIRIT_ALIANCE        = 4,
    BG_BG_SPIRIT_HORDE          = 5,

    BG_BG_ALL_NODES_COUNT       = 5                         // all nodes (dynamic and static)
};

enum BG_BG_NodeStatus
{
    BG_BG_NODE_TYPE_NEUTRAL             = 0,
    BG_BG_NODE_TYPE_CONTESTED           = 1,
    BG_BG_NODE_STATUS_ALLY_CONTESTED    = 1,
    BG_BG_NODE_STATUS_HORDE_CONTESTED   = 2,
    BG_BG_NODE_TYPE_OCCUPIED            = 3,
    BG_BG_NODE_STATUS_ALLY_OCCUPIED     = 3,
    BG_BG_NODE_STATUS_HORDE_OCCUPIED    = 4
};

enum BG_BG_Sounds
{
    BG_BG_SOUND_NODE_CLAIMED            = 8192,
    BG_BG_SOUND_NODE_CAPTURED_ALLIANCE  = 8173,
    BG_BG_SOUND_NODE_CAPTURED_HORDE     = 8213,
    BG_BG_SOUND_NODE_ASSAULTED_ALLIANCE = 8212,
    BG_BG_SOUND_NODE_ASSAULTED_HORDE    = 8174,
    BG_BG_SOUND_NEAR_VICTORY            = 8456
};

enum BG_BG_Objectives
{
    BG_OBJECTIVE_ASSAULT_BASE           = 122,
    BG_OBJECTIVE_DEFEND_BASE            = 123
};

#define BG_BG_NotBGBGWeekendHonorTicks      260
#define BG_BG_BGBGWeekendHonorTicks         160
#define BG_BG_NotBGBGWeekendReputationTicks 160
#define BG_BG_BGBGWeekendReputationTicks    120

#define BG_EVENT_START_BATTLE               9158 // Achievement: Let's Get This Done

// x, y, z, o
const float BG_BG_NodePositions[BG_BG_DYNAMIC_NODES_COUNT][4] =
{
    {1057.790f, 1278.285f, 3.1500f, 1.945662f},                   // Light House
    {1251.010f, 958.2685f, 5.6000f, 5.892280f},                   // Waterworks
    {980.0446f, 948.7411f, 12.650f, 5.904071f}                    // Mines
};

// x, y, z, o, rot0, rot1, rot2, rot3
const float BG_BG_DoorPositions[4][8] =
{
    { 918.160f, 1336.75f, 27.6299f, 2.87927f, 0.0f, 0.0f, 0.983231f, 0.182367f },
    { 918.160f, 1336.75f, 26.6299f, 2.87927f, 0.0f, 0.0f, 0.983231f, 0.182367f },
    { 1396.15f, 977.014f, 7.43169f, 6.27043f, 0.0f, 0.0f, 0.006378f, -0.99998f },
    { 1396.15f, 977.014f, 0.33169f, 6.27043f, 0.0f, 0.0f, 0.006378f, -0.99998f }
};

struct NodeInfo
{
    uint8 bannerType;
    uint32 timer;
    uint32 team;
};

// Tick intervals and given points: case 0, 1, 2, 3 captured nodes
const uint32 BG_BG_TickIntervals[4] = {0, 9000, 3000, 1000};
const uint32 BG_BG_TickPoints[4] = {0, 10, 10, 30};

// WorldSafeLocs ids for 3 nodes, and for ally, and horde starting location
const uint32 BG_BG_GraveyardIds[BG_BG_ALL_NODES_COUNT] = {1735, 1736, 1738, 1739, 1740};

// x, y, z, o
const float BG_BG_BuffPositions[BG_BG_DYNAMIC_NODES_COUNT][4] =
{
    //NEEDS CORRECT CO ORDS
    { 1063.57f, 1313.42f, 4.91f, 4.14f }, // Lighthouse
    { 961.830f, 977.03f, 14.15f, 4.55f }, // Waterworks
    { 1193.09f, 1017.46f, 7.98f, 0.24f }  // Mine
};

// x, y, z, o
const float BG_BG_SpiritGuidePos[BG_BG_ALL_NODES_COUNT][4] =
{
    //NEEDS CORRECT CO ORDS
    {1200.03f, 1171.09f, -56.47f, 5.15f},                   // stables
    {1017.43f, 960.61f, -42.95f, 4.88f},                    // blacksmith
    {833.00f, 793.00f, -57.25f, 5.27f},                     // farm
    {1354.05f, 1275.48f, -11.30f, 4.77f},                   // alliance starting base
    {714.61f, 646.15f, -10.87f, 4.34f}                      // horde starting base
};

struct BG_BG_BannerTimer
{
    uint32      timer;
    uint8       type;
    uint8       teamIndex;
};

struct BattlegroundBGScore : public BattlegroundScore
{
    BattlegroundBGScore(): BasesAssaulted(0), BasesDefended(0) { }
    ~BattlegroundBGScore() { }
    uint32 BasesAssaulted;
    uint32 BasesDefended;
};

class BattlegroundBG : public Battleground
{
    public:
        BattlegroundBG();
        ~BattlegroundBG();

        void AddPlayer(Player* player);
        void StartingEventCloseDoors();
        void StartingEventOpenDoors();
        void RemovePlayer(Player* player, uint64 guid, uint32 team);
        void HandleAreaTrigger(Player* Source, uint32 Trigger);
        bool SetupBattleground();
        void Reset();
        void EndBattleground(uint32 winner);
        WorldSafeLocsEntry const* GetClosestGraveYard(Player* player);

        /* Scorekeeping */
        void UpdatePlayerScore(Player* Source, uint32 type, uint32 value, bool doAddHonor = true);

        void FillInitialWorldStates(WorldPacket& data);

        /* Nodes occupying */
        void EventPlayerClickedOnFlag(Player* source, GameObject* target_obj);

        /* achievement req. */
        bool IsJuggerNotEligible(uint8 team) const;
        bool IsDontGetCockyKidEligible(uint32 team) const { return dontGetCockyKid[GetTeamIndexByTeamId(team)]; }
        bool IsFullCoverageEligible(uint32 team) const;

        uint32 GetPrematureWinner();
    private:
        void PostUpdateImpl(uint32 diff);
        /* Gameobject spawning/despawning */
        void _CreateBanner(uint8 node, uint8 type, uint8 teamIndex, bool delay);
        void _DelBanner(uint8 node, uint8 type, uint8 teamIndex);
        void _SendNodeUpdate(uint8 node);

        /* Creature spawning/despawning */
        /// @todo working, scripted peons spawning
        void _NodeOccupied(uint8 node, Team team);
        void _NodeDeOccupied(uint8 node);

        int32 _GetNodeNameId(uint8 node);

        /* Nodes info:
            0: neutral
            1: ally contested
            2: horde contested
            3: ally occupied
            4: horde occupied     */
        uint8               m_Nodes[BG_BG_DYNAMIC_NODES_COUNT];
        uint8               m_prevNodes[BG_BG_DYNAMIC_NODES_COUNT];
        BG_BG_BannerTimer   m_BannerTimers[BG_BG_DYNAMIC_NODES_COUNT];
        uint32              m_NodeTimers[BG_BG_DYNAMIC_NODES_COUNT];
        uint32              m_lastTick[BG_TEAMS_COUNT];
        uint32              m_HonorScoreTics[BG_TEAMS_COUNT];
        uint32              m_ReputationScoreTics[BG_TEAMS_COUNT];
        bool                m_IsInformedNearVictory;
        uint32              m_HonorTics;
        uint32              m_ReputationTics;
        // need for achievements
        NodeInfo m_nodeInfo[BG_BG_DYNAMIC_NODES_COUNT];
        bool dontGetCockyKid[BG_TEAMS_COUNT];
};
#endif