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
#include "timeless_isle.h"

#define NIUZAO 					"Though blood floods the ground, the mountain is unmoved."
#define YULON 					"The truth shines brightest in clouded times."
#define CHI_JI 					"Hope's fire grows when the flames come together."
#define XUEN 					"Strength and power are as different as sun and moon."
#define CORRUPTED				"The shrine was corrupted by Ordos!"

class player_on_enter_ti : public PlayerScript
{
	public:
		player_on_enter_ti() : PlayerScript("player_on_enter_ti") {	}

		void OnUpdateZone(Player* player, uint32 newZone, uint32 newArea)
		{
			if (newZone == 6757)
			{
				if (player->HasAura(145389))
					return;

				else if (!player->HasAura(145389))
					player->CastSpell(player, 145389, true);
			}

			else if (!newZone == 6757)
				player->RemoveAurasDueToSpell(145389);
		}
};

class go_time_lost_shrine_ti : public GameObjectScript
{
    public:
        go_time_lost_shrine_ti() : GameObjectScript("go_time_lost_shrine_ti") { }

        struct go_time_lost_shrine_tiAI : public GameObjectAI
        {
            go_time_lost_shrine_tiAI(GameObject* go) : GameObjectAI(go) {	}

            EventMap _events;
            bool used;

            bool OnGossipHello(Player* player, GameObject* go) OVERRIDE
        	{
            	player->CLOSE_GOSSIP_MENU();
            	go->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_INTERACT_COND);
            	WorldPacket packet(SMSG_MESSAGECHAT, 200);

            	if (used == false)
            	{
            		used = true;

            		Choice = urand(1, 5);
            	}

            	if (player->HasAura(SPELL_FORTITUDE_OF_NIUZAO))
            		player->RemoveAurasDueToSpell(SPELL_FORTITUDE_OF_NIUZAO);

            	if (player->HasAura(SPELL_WISDOM_OF_YULON))
            		player->RemoveAurasDueToSpell(SPELL_WISDOM_OF_YULON);

            	if (player->HasAura(SPELL_CHI_JIS_HOPE))
            		player->RemoveAurasDueToSpell(SPELL_CHI_JIS_HOPE);

            	if (player->HasAura(SPELL_XUENS_STRENGTH))
            		player->RemoveAurasDueToSpell(SPELL_XUENS_STRENGTH);

            	if (Choice == 1)
            	{
            		go->CastSpell(player, SPELL_FORTITUDE_OF_NIUZAO);
            		go->BuildMonsterChat(&packet, CHAT_MSG_RAID_WARNING, NIUZAO, LANG_UNIVERSAL, 0, player->GetGUID());
            	}

            	if (Choice == 2)
            	{
            		go->CastSpell(player, SPELL_WISDOM_OF_YULON);
            		go->BuildMonsterChat(&packet, CHAT_MSG_RAID_WARNING, YULON, LANG_UNIVERSAL, 0, player->GetGUID());
            	}

            	if (Choice == 3)
            	{
            		go->CastSpell(player, SPELL_CHI_JIS_HOPE);
            		go->BuildMonsterChat(&packet, CHAT_MSG_RAID_WARNING, CHI_JI, LANG_UNIVERSAL, 0, player->GetGUID());
            	}

            	if (Choice == 4)
            	{
            		go->CastSpell(player, SPELL_XUENS_STRENGTH);
            		go->BuildMonsterChat(&packet, CHAT_MSG_RAID_WARNING, XUEN, LANG_UNIVERSAL, 0, player->GetGUID());
            	}

            	if (Choice == 5)
            	{
            		go->CastSpell(player, SPELL_ORDOS_BURNING_SACRIFICE);
            		go->BuildMonsterChat(&packet, CHAT_MSG_RAID_WARNING, CORRUPTED, LANG_UNIVERSAL, 0, player->GetGUID());
            	}

            	_events.ScheduleEvent(EVENT_BACK_TO_USE, 300000);

            	return true;
        	}

            void UpdateAI(uint32 diff) OVERRIDE
            {
                if (_events.Empty())
                    return;

                _events.Update(diff);

                if (used == false)
                	return;

                while (uint32 eventId = _events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_BACK_TO_USE:
                            go->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_INTERACT_COND);
                            break;
                        default:
                        	break;
                    }
                }
            }

        private:
        	uint8 Choice;
        };

        GameObjectAI* GetAI(GameObject* go) const OVERRIDE
        {
            return new go_time_lost_shrine_tiAI(go);
        }
};

void AddSC_zone_timeless_isle()
{
	new player_on_enter_ti();
    new go_time_lost_shrine_ti();
}
