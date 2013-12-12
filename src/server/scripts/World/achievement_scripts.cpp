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

#include "ScriptMgr.h"

#include "BattlegroundAB.h"
#include "BattlegroundWS.h"
#include "BattlegroundIC.h"
#include "BattlegroundSA.h"
#include "BattlegroundAV.h"
#include "BattlegroundTP.h"
#include "BattlegroundBG.h"
#include "BattlegroundTK.h"
#include "BattlegroundSM.h"
#include "BattlegroundDG.h"
#include "Vehicle.h"
#include "Player.h"
#include "Creature.h"

class achievement_resilient_victory : public AchievementCriteriaScript
{
    public:
        achievement_resilient_victory() : AchievementCriteriaScript("achievement_resilient_victory") { }

        bool OnCheck(Player* source, Unit* /*target*/) OVERRIDE
        {
            Battleground* bg = source->GetBattleground();
            if (!bg)
                return false;

            if (bg->GetTypeID(true) != BATTLEGROUND_AB)
                return false;

            if (!static_cast<BattlegroundAB*>(bg)->IsTeamScores500Disadvantage(source->GetTeam()))
                return false;

            return true;
        }
};

class achievement_bg_control_all_nodes : public AchievementCriteriaScript
{
    public:
        achievement_bg_control_all_nodes() : AchievementCriteriaScript("achievement_bg_control_all_nodes") { }

        bool OnCheck(Player* source, Unit* /*target*/) OVERRIDE
        {
            Battleground* bg = source->GetBattleground();
            if (!bg)
                return false;

            if (!bg->IsAllNodesControlledByTeam(source->GetTeam()))
                return false;

            return true;
        }
};

class achievement_save_the_day : public AchievementCriteriaScript
{
    public:
        achievement_save_the_day() : AchievementCriteriaScript("achievement_save_the_day") { }

        bool OnCheck(Player* source, Unit* target) OVERRIDE
        {
            if (!target)
                return false;

            if (Player const* player = target->ToPlayer())
            {
                Battleground* bg = source->GetBattleground();
                if (!bg)
                    return false;

                if (bg->GetTypeID(true) != BATTLEGROUND_WS)
                    return false;

                if (static_cast<BattlegroundWS*>(bg)->GetFlagState(player->GetTeam()) == BG_WS_FLAG_STATE_ON_BASE)
                    return true;
            }
            return false;
        }
};

class achievement_bg_ic_resource_glut : public AchievementCriteriaScript
{
    public:
        achievement_bg_ic_resource_glut() : AchievementCriteriaScript("achievement_bg_ic_resource_glut") { }

        bool OnCheck(Player* source, Unit* /*target*/) OVERRIDE
        {
            if (source->HasAura(SPELL_OIL_REFINERY) && source->HasAura(SPELL_QUARRY))
                return true;

            return false;
        }
};

class achievement_bg_ic_glaive_grave : public AchievementCriteriaScript
{
    public:
        achievement_bg_ic_glaive_grave() : AchievementCriteriaScript("achievement_bg_ic_glaive_grave") { }

        bool OnCheck(Player* source, Unit* /*target*/) OVERRIDE
        {
            if (Creature* vehicle = source->GetVehicleCreatureBase())
            {
                if (vehicle->GetEntry() == NPC_GLAIVE_THROWER_H ||  vehicle->GetEntry() == NPC_GLAIVE_THROWER_A)
                    return true;
            }

            return false;
        }
};

class achievement_bg_ic_mowed_down : public AchievementCriteriaScript
{
    public:
        achievement_bg_ic_mowed_down() : AchievementCriteriaScript("achievement_bg_ic_mowed_down") { }

        bool OnCheck(Player* source, Unit* /*target*/) OVERRIDE
        {
            if (Creature* vehicle = source->GetVehicleCreatureBase())
            {
                if (vehicle->GetEntry() == NPC_KEEP_CANNON)
                    return true;
            }

            return false;
        }
};

class achievement_bg_sa_artillery : public AchievementCriteriaScript
{
    public:
        achievement_bg_sa_artillery() : AchievementCriteriaScript("achievement_bg_sa_artillery") { }

        bool OnCheck(Player* source, Unit* /*target*/) OVERRIDE
        {
            if (Creature* vehicle = source->GetVehicleCreatureBase())
            {
                if (vehicle->GetEntry() == NPC_ANTI_PERSONNAL_CANNON)
                    return true;
            }

            return false;
        }
};

class achievement_arena_kills : public AchievementCriteriaScript
{
    public:
        achievement_arena_kills(char const* name, uint8 arenaType) : AchievementCriteriaScript(name),
            _arenaType(arenaType)
        {
        }

        bool OnCheck(Player* source, Unit* /*target*/) OVERRIDE
        {
            // this checks GetBattleground() for NULL already
            if (!source->InArena())
                return false;

            return source->GetBattleground()->GetArenaType() == _arenaType;
        }

    private:
        uint8 const _arenaType;
};

class achievement_sickly_gazelle : public AchievementCriteriaScript
{
public:
    achievement_sickly_gazelle() : AchievementCriteriaScript("achievement_sickly_gazelle") { }

    bool OnCheck(Player* /*source*/, Unit* target) OVERRIDE
    {
        if (!target)
            return false;

        if (Player* victim = target->ToPlayer())
            if (victim->IsMounted())
                return true;

        return false;
    }
};

class achievement_everything_counts : public AchievementCriteriaScript
{
    public:
        achievement_everything_counts() : AchievementCriteriaScript("achievement_everything_counts") { }

        bool OnCheck(Player* source, Unit* /*target*/) OVERRIDE
        {
            Battleground* bg = source->GetBattleground();
            if (!bg)
                return false;

            if (bg->GetTypeID(true) != BATTLEGROUND_AV)
                return false;

            if (static_cast<BattlegroundAV*>(bg)->IsBothMinesControlledByTeam(source->GetTeam()))
                return true;

            return false;
        }
};

class achievement_bg_av_perfection : public AchievementCriteriaScript
{
    public:
        achievement_bg_av_perfection() : AchievementCriteriaScript("achievement_bg_av_perfection") { }

        bool OnCheck(Player* source, Unit* /*target*/) OVERRIDE
        {
            Battleground* bg = source->GetBattleground();
            if (!bg)
                return false;

            if (bg->GetTypeID(true) != BATTLEGROUND_AV)
                return false;

            if (static_cast<BattlegroundAV*>(bg)->IsAllTowersControlledAndCaptainAlive(source->GetTeam()))
                return true;

            return false;
        }
};

class achievement_bg_sa_defense_of_ancients : public AchievementCriteriaScript
{
    public:
        achievement_bg_sa_defense_of_ancients() : AchievementCriteriaScript("achievement_bg_sa_defense_of_ancients")
        {
        }

        bool OnCheck(Player* player, Unit* /*target*/) OVERRIDE
        {
            if (!player)
                return false;

            Battleground* battleground = player->GetBattleground();
            if (!battleground)
                return false;

            if (player->GetTeamId() == static_cast<BattlegroundSA*>(battleground)->Attackers)
                return false;

            if (!static_cast<BattlegroundSA*>(battleground)->gateDestroyed)
                return true;

            return false;
        }
};

enum ArgentTournamentAreas
{
    AREA_ARGENT_TOURNAMENT_FIELDS  = 4658,
    AREA_RING_OF_ASPIRANTS         = 4670,
    AREA_RING_OF_ARGENT_VALIANTS   = 4671,
    AREA_RING_OF_ALLIANCE_VALIANTS = 4672,
    AREA_RING_OF_HORDE_VALIANTS    = 4673,
    AREA_RING_OF_CHAMPIONS         = 4669,
};

class achievement_tilted : public AchievementCriteriaScript
{
    public:
        achievement_tilted() : AchievementCriteriaScript("achievement_tilted") {}

        bool OnCheck(Player* player, Unit* /*target*/) OVERRIDE
        {
            if (!player)
                return false;

            bool checkArea = player->GetAreaId() == AREA_ARGENT_TOURNAMENT_FIELDS ||
                                player->GetAreaId() == AREA_RING_OF_ASPIRANTS ||
                                player->GetAreaId() == AREA_RING_OF_ARGENT_VALIANTS ||
                                player->GetAreaId() == AREA_RING_OF_ALLIANCE_VALIANTS ||
                                player->GetAreaId() == AREA_RING_OF_HORDE_VALIANTS ||
                                player->GetAreaId() == AREA_RING_OF_CHAMPIONS;

            return checkArea && player->duel && player->duel->isMounted;
        }
};

class achievement_not_even_a_scratch : public AchievementCriteriaScript
{
    public:
        achievement_not_even_a_scratch() : AchievementCriteriaScript("achievement_not_even_a_scratch") { }

        bool OnCheck(Player* source, Unit* /*target*/) OVERRIDE
        {
            if (!source)
                return false;

            Battleground* battleground = source->GetBattleground();
            if (!battleground)
                return false;

            if (static_cast<BattlegroundSA*>(battleground)->notEvenAScratch(source->GetTeam()))
                return true;

            return false;
        }
};

enum FlirtWithDisaster
{
    AURA_PERFUME_FOREVER           = 70235,
    AURA_PERFUME_ENCHANTRESS       = 70234,
    AURA_PERFUME_VICTORY           = 70233,
};

class achievement_flirt_with_disaster_perf_check : public AchievementCriteriaScript
{
    public:
        achievement_flirt_with_disaster_perf_check() : AchievementCriteriaScript("achievement_flirt_with_disaster_perf_check") { }

        bool OnCheck(Player* player, Unit* /*target*/) OVERRIDE
        {
            if (!player)
                return false;

            if (player->HasAura(AURA_PERFUME_FOREVER) || player->HasAura(AURA_PERFUME_ENCHANTRESS) || player->HasAura(AURA_PERFUME_VICTORY))
                return true;

            return false;
        }
};

class achievement_bg_bog_jugger_not : public AchievementCriteriaScript
{
   public:
       achievement_bg_bog_jugger_not() : AchievementCriteriaScript("achievement_bg_bg_jugger_not")
       {
       }

       bool OnCheck(Player* player, Unit* /*target*/)
       {
           if (player->GetBattlegroundTypeId() != BATTLEGROUND_BG || !player->GetBattleground())
               return false;

           BattlegroundBG const* const battleground = static_cast<BattlegroundBG*>(player->GetBattleground());
           if (battleground->IsJuggerNotEligible(player->GetTeamId()))
               return true;

           return false;
       }
};

class achievement_bg_bog_dont_get_cocky_kid : public AchievementCriteriaScript
{
   public:
       achievement_bg_bog_dont_get_cocky_kid() : AchievementCriteriaScript("achievement_bg_bg_dont_get_cocky_kid")
       {
       }

       bool OnCheck(Player* player, Unit* /*target*/)
       {
           if (player->GetBattlegroundTypeId() != BATTLEGROUND_BG || !player->GetBattleground())
               return false;

           BattlegroundBG const* const battleground = static_cast<BattlegroundBG*>(player->GetBattleground());
           if (battleground->IsDontGetCockyKidEligible(player->GetTeamId()))
               return true;

           return false;
       }
};

class achievement_bg_bog_full_coverage : public AchievementCriteriaScript
{
   public:
       achievement_bg_bog_full_coverage() : AchievementCriteriaScript("achievement_bg_bg_full_coverage")
       {
       }

       bool OnCheck(Player* player, Unit* /*target*/)
       {
           if (player->GetBattlegroundTypeId() != BATTLEGROUND_BG || !player->GetBattleground())
               return false;

           BattlegroundBG const* const battleground = static_cast<BattlegroundBG*>(player->GetBattleground());
           if (battleground->IsFullCoverageEligible(player->GetTeamId()))
               return true;

           return false;
       }
};

class achievement_bg_tp_twin_peaks_perfection : public AchievementCriteriaScript
{
   public:
       achievement_bg_tp_twin_peaks_perfection() : AchievementCriteriaScript("achievement_bg_tp_twin_peaks_perfection") { }

       bool OnCheck(Player* player, Unit* /*target*/)
       {
           if (player->GetBattlegroundTypeId() != BATTLEGROUND_TP || !player->GetBattleground())
               return false;

           BattlegroundTP const* const battleground = static_cast<BattlegroundTP*>(player->GetBattleground());
           if (battleground->IsTwinPeaksPerfectionEligible(player))
               return true;

           return false;
       }
};

class achievement_bg_tp_double_jeopardy : public AchievementCriteriaScript
{
   public:
       achievement_bg_tp_double_jeopardy() : AchievementCriteriaScript("achievement_bg_tp_double_jeopardy")
       {
       }

       bool OnCheck(Player* player, Unit* /*target*/)
       {
           if (player->GetBattlegroundTypeId() != BATTLEGROUND_TP || !player->GetBattleground())
               return false;

           BattlegroundTP const* const battleground = static_cast<BattlegroundTP*>(player->GetBattleground());
           if (battleground->IsDoubleJeopardyEligible(player))
               return true;

           return false;
       }
};

//BG TK
//Four Square
//Hold all four Orbs of Power at least once in a single Temple of Kotmogu battle.
class achievement_bg_tk_four_square : public AchievementCriteriaScript
{
    public:
        achievement_bg_tk_four_square() : AchievementCriteriaScript("achievement_bg_tk_four_square") 
		{
		}

		bool OnCheck(Player* player, Unit* /*target*/)
        {
           if (player->GetBattlegroundTypeId() != BATTLEGROUND_TK || !player->GetBattleground())
			   return false;
		   
		   BattlegroundTK const* const battleground = static_cast<BattlegroundTK*>(player->GetBattleground());
           //TODO
		   //if (battleground->IsFourSquareEligible(player))
           //    return true;

           return false;
		}
};

//I've Got the Power
//Win Temple of Kotmogu while controlling all 4 Orbs of Power.
class achievement_bg_tk_got_the_power : public AchievementCriteriaScript
{
    public:
        achievement_bg_tk_got_the_power() : AchievementCriteriaScript("achievement_bg_tk_got_the_power") 
		{
		}

		bool OnCheck(Player* player, Unit* /*target*/)
        {
           if (player->GetBattlegroundTypeId() != BATTLEGROUND_TK || !player->GetBattleground())
			   return false;
		   
		   BattlegroundTK const* const battleground = static_cast<BattlegroundTK*>(player->GetBattleground());
           //TODO
		   //if (battleground->IsGotThePowerEligible(player))
           //    return true;

           return false;
		}
};

//Powerball
//Hold an Orb of Power in the center of the Temple of Kotmogu for 90 seconds.
class achievement_bg_tk_powerball : public AchievementCriteriaScript
{
    public:
        achievement_bg_tk_powerball() : AchievementCriteriaScript("achievement_bg_tk_powerball") 
		{
		}

		bool OnCheck(Player* player, Unit* /*target*/)
        {
           if (player->GetBattlegroundTypeId() != BATTLEGROUND_TK || !player->GetBattleground())
			   return false;
		   
		   BattlegroundTK const* const battleground = static_cast<BattlegroundTK*>(player->GetBattleground());
           //TODO
		   //if (battleground->IsPowerballEligible(player))
           //    return true;

           return false;
		}
};

//Temple of Kotmogu All-Star
//Hold four Orbs of Power and kill four enemies who are holding an Orb of Power in a single Temple of Kotmogu match.
class achievement_bg_tk_allstar : public AchievementCriteriaScript
{
    public:
        achievement_bg_tk_allstar() : AchievementCriteriaScript("achievement_bg_tk_allstar") 
		{
		}

		bool OnCheck(Player* player, Unit* /*target*/)
        {
           if (player->GetBattlegroundTypeId() != BATTLEGROUND_TK || !player->GetBattleground())
			   return false;
		   
		   BattlegroundTK const* const battleground = static_cast<BattlegroundTK*>(player->GetBattleground());
           //TODO
		   //if (battleground->IsTkAllstarEligible(player))
           //    return true;

           return false;
		}
};

//BG SM
//End of the Line
//Seize control of a mine cart that is controlled by the opposing team within 20 yards of the depot, and then capture it.
class achievement_bg_sm_end_of_the_line : public AchievementCriteriaScript
{
    public:
        achievement_bg_sm_end_of_the_line() : AchievementCriteriaScript("achievement_bg_sm_end_of_the_line") 
		{
		}

		bool OnCheck(Player* player, Unit* /*target*/)
        {
           if (player->GetBattlegroundTypeId() != BATTLEGROUND_SM || !player->GetBattleground())
			   return false;
		   
		   BattlegroundSM const* const battleground = static_cast<BattlegroundSM*>(player->GetBattleground());
           //TODO
		   //if (battleground->IsEndOfTheLineEligible(player))
           //    return true;

           return false;
		}
};

//Five for Five
//Capture five mine carts in a single Silvershard Mines battle without dying.
class achievement_bg_sm_five_for_five : public AchievementCriteriaScript
{
    public:
        achievement_bg_sm_five_for_five() : AchievementCriteriaScript("achievement_bg_sm_five_for_five") 
		{
		}

		bool OnCheck(Player* player, Unit* /*target*/)
        {
           if (player->GetBattlegroundTypeId() != BATTLEGROUND_SM || !player->GetBattleground())
			   return false;
		   
		   BattlegroundSM const* const battleground = static_cast<BattlegroundSM*>(player->GetBattleground());
           //TODO
		   //if (battleground->IsFiveForFiveEligible(player))
           //    return true;

           return false;
		}
};

//Mine Cart Courier
//Capture a mine cart using each of the 5 sets of tracks in a single Silvershard Mines match.
class achievement_bg_sm_mine_cart_courier : public AchievementCriteriaScript
{
    public:
        achievement_bg_sm_mine_cart_courier() : AchievementCriteriaScript("achievement_bg_sm_mine_cart_courier") 
		{
		}

		bool OnCheck(Player* player, Unit* /*target*/)
        {
           if (player->GetBattlegroundTypeId() != BATTLEGROUND_SM || !player->GetBattleground())
			   return false;
		   
		   BattlegroundSM const* const battleground = static_cast<BattlegroundSM*>(player->GetBattleground());
           //TODO
		   //if (battleground->IsCartCourierEligible(player))
           //    return true;

           return false;
		}
};

//My Diamonds and Your Rust
//Win a Silvershard Mines battle without letting the enemy team capture a mine cart.
class achievement_bg_sm_diamonds_for_rust : public AchievementCriteriaScript
{
   public:
        achievement_bg_sm_diamonds_for_rust() : AchievementCriteriaScript("achievement_bg_sm_diamonds_for_rust") 
		{
		}

		bool OnCheck(Player* player, Unit* /*target*/)
        {
           if (player->GetBattlegroundTypeId() != BATTLEGROUND_SM || !player->GetBattleground())
			   return false;
		   
		   BattlegroundSM const* const battleground = static_cast<BattlegroundSM*>(player->GetBattleground());
           //TODO
		   //if (battleground->IsDiamondForRustEligible(player))
           //    return true;

           return false;
		}
};

//BG DG
//Capping Spree
//Personally capture the enemy mine cart 4 times in a single Deepwind Gorge battleground.
class achievement_bg_dg_capping_spree : public AchievementCriteriaScript
{
    public:
        achievement_bg_dg_capping_spree() : AchievementCriteriaScript("achievement_bg_dg_capping_spree") 
		{
		}

		bool OnCheck(Player* player, Unit* /*target*/)
        {
           if (player->GetBattlegroundTypeId() != BATTLEGROUND_DG || !player->GetBattleground())
			   return false;
		   
		   BattlegroundDG const* const battleground = static_cast<BattlegroundDG*>(player->GetBattleground());
           //TODO
		   //if (battleground->IsCappingSpreeEligible(player))
           //    return true;

           return false;
		}
};

//Deepwind Gorge All-Star
//Assault a mine, Defend a mine, Capture a mine cart and Return a mine cart in a single Deepwind Gorge match.
class achievement_bg_dg_allstar : public AchievementCriteriaScript
{
    public:
        achievement_bg_dg_allstar() : AchievementCriteriaScript("achievement_bg_dg_allstar") 
		{
		}

		bool OnCheck(Player* player, Unit* /*target*/)
        {
           if (player->GetBattlegroundTypeId() != BATTLEGROUND_DG || !player->GetBattleground())
			   return false;
		   
		   BattlegroundDG const* const battleground = static_cast<BattlegroundDG*>(player->GetBattleground());
           //TODO
		   //if (battleground->IsDgAllstarEligible(player))
           //    return true;

           return false;
		}
};

//Deepwind Gorge Perfection
//Win Deepwind Gorge with a score of 1600 to 0.
class achievement_bg_dg_perfection : public AchievementCriteriaScript
{
    public:
        achievement_bg_dg_perfection() : AchievementCriteriaScript("achievement_bg_dg_perfection") 
		{
		}

		bool OnCheck(Player* player, Unit* /*target*/)
        {
           if (player->GetBattlegroundTypeId() != BATTLEGROUND_DG || !player->GetBattleground())
			   return false;
		   
		   BattlegroundDG const* const battleground = static_cast<BattlegroundDG*>(player->GetBattleground());
           //TODO
		   //if (battleground->IsDgPerfectionEligible(player))
           //    return true;

           return false;
		}
};

//Puddle Jumper
//Fall 25 yards without dying in Deepwind Gorge.
class achievement_bg_dg_puddle_jumper : public AchievementCriteriaScript
{
    public:
        achievement_bg_dg_puddle_jumper() : AchievementCriteriaScript("achievement_bg_dg_puddle_jumper") 
		{
		}

		bool OnCheck(Player* player, Unit* /*target*/)
        {
           if (player->GetBattlegroundTypeId() != BATTLEGROUND_DG || !player->GetBattleground())
			   return false;
		   
		   BattlegroundDG const* const battleground = static_cast<BattlegroundDG*>(player->GetBattleground());
           //TODO
		   //if (battleground->IsPuddleJumperEligible(player))
           //    return true;

           return false;
		}
};
void AddSC_achievement_scripts()
{
    new achievement_resilient_victory();
    new achievement_bg_control_all_nodes();
    new achievement_save_the_day();
    new achievement_bg_ic_resource_glut();
    new achievement_bg_ic_glaive_grave();
    new achievement_bg_ic_mowed_down();
    new achievement_bg_sa_artillery();
    new achievement_bg_bog_jugger_not();
    new achievement_bg_bog_dont_get_cocky_kid();
    new achievement_bg_bog_full_coverage();
    new achievement_bg_tp_twin_peaks_perfection();
    new achievement_bg_tp_double_jeopardy();
    new achievement_sickly_gazelle();
    new achievement_everything_counts();
    new achievement_bg_av_perfection();
    new achievement_arena_kills("achievement_arena_2v2_kills", ARENA_TYPE_2v2);
    new achievement_arena_kills("achievement_arena_3v3_kills", ARENA_TYPE_3v3);
    new achievement_arena_kills("achievement_arena_5v5_kills", ARENA_TYPE_5v5);
    new achievement_bg_sa_defense_of_ancients();
    new achievement_tilted();
    new achievement_not_even_a_scratch();
    new achievement_flirt_with_disaster_perf_check();
    //TODO SCRIPT NEW BG
    new achievement_bg_tk_four_square();
    new achievement_bg_tk_got_the_power();
    new achievement_bg_tk_powerball();
    new achievement_bg_tk_allstar();
    new achievement_bg_sm_end_of_the_line();
    new achievement_bg_sm_five_for_five();
    new achievement_bg_sm_mine_cart_courier();
    new achievement_bg_sm_diamonds_for_rust();
    new achievement_bg_dg_capping_spree();
    new achievement_bg_dg_allstar();
    new achievement_bg_dg_perfection();
    new achievement_bg_dg_puddle_jumper();
}
