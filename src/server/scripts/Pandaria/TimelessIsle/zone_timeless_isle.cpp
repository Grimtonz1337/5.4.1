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
#include "ScriptedGossip.h"
#include "GossipDef.h"
#include "timeless_isle.h"

#define NIUZAO 					"Though blood floods the ground, the mountain is unmoved. - Niuzao"
#define YULON 					"The truth shines brightest in clouded times. - Yu'lon"
#define CHI_JI 					"Hope's fire grows when the flames come together. - Chi-Ji"
#define XUEN 					"Strength and power are as different as sun and moon. - Xuen"
#define CORRUPTED				"The shrine was corrupted by Ordos!"

class player_on_enter_ti : public PlayerScript
{
	public:
		player_on_enter_ti() : PlayerScript("player_on_enter_ti") {	}

		void OnUpdateZone(Player* player, uint32 Zone, uint32 newArea)
		{
			if (Zone == 6757)
			{
				if (player->HasAura(145389))
					return;

				else if (!player->HasAura(145389))
					player->CastSpell(player, 145389, true);
			}

			else
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

            bool OnGossipHello(Player* player, GameObject* go) OVERRIDE
        	{
            	player->CLOSE_GOSSIP_MENU();
            	go->RemoveFlag(GAMEOBJECT_FIELD_FLAGS, GO_FLAG_INTERACT_COND);
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
                            go->RemoveFlag(GAMEOBJECT_FIELD_FLAGS, GO_FLAG_INTERACT_COND);
                            used = false; // this will stop/prevent it from updating it
                            break;
                        default:
                        	break;
                    }
                }
            }

        private:
        	uint8 Choice;
        	bool used;
        };

        GameObjectAI* GetAI(GameObject* go) const OVERRIDE
        {
            return new go_time_lost_shrine_tiAI(go);
        }
};

class go_gleaming_crane_statue_ti : public GameObjectScript
{
    public:
        go_gleaming_crane_statue_ti() : GameObjectScript("go_gleaming_crane_statue_ti") { }

        struct go_gleaming_crane_statue_tiAI : public GameObjectAI
        {
            go_gleaming_crane_statue_tiAI(GameObject* go) : GameObjectAI(go) {	}

            uint64 playerGUID;
            uint32 WingsTimer;

            bool OnGossipHello(Player* player, GameObject* go) OVERRIDE
        	{
            	player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Touch the statue.", GOSSIP_SENDER_MAIN, 1);

            	player->SEND_GOSSIP_MENU(player->GetGossipTextId(go), go->GetGUID());

            	return true;
        	}

        	bool OnGossipSelect(Player* player, GameObject* go, uint32 /*sender*/, uint32 action) OVERRIDE
        	{
        		player->PlayerTalkClass->ClearMenus();
        		player->CLOSE_GOSSIP_MENU();

        		switch (action)
        		{
        			case 1:
        				player->CastSpell(player, 144387, true); // knockback in the air
        				playerGUID = player->GetGUID();
        				used = true;
        				WingsTimer = 6000;
        				break;
        			default:
        				break;
        		}

        		return true;
        	}

        	void UpdateAI(uint32 diff) OVERRIDE
            {
                if (used == false)
                	return;

                if (WingsTimer <= diff)
                {
                	if (Player* player = ObjectAccessor::GetPlayer(*go, playerGUID))
                	{
                		player->CastSpell(player, 144385, true);
                		used = false;
                	}
                }

                else WingsTimer -= diff;
            }

        private:
        	bool used;
       	};

       	GameObjectAI* GetAI(GameObject* go) const OVERRIDE
        {
            return new go_gleaming_crane_statue_tiAI(go);
        }
};

class spell_timeless_isle_crane_wings : public SpellScriptLoader
{
    public:
        spell_timeless_isle_crane_wings() : SpellScriptLoader("spell_timeless_isle_crane_wings") { }

        class spell_timeless_isle_crane_wings_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_timeless_isle_crane_wings_AuraScript);

            void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                 if (Unit* caster = GetCaster())
                 	caster->CastSpell(caster, 144391, true);
            }

            void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Unit* caster = GetCaster())
                	caster->CastSpell(caster, 148162, true);
            }

            void Register() OVERRIDE
            {
            	OnEffectApply += AuraEffectApplyFn(spell_timeless_isle_crane_wings_AuraScript::OnApply, EFFECT_0, SPELL_AURA_FEATHER_FALL, AURA_EFFECT_HANDLE_REAL);
                OnEffectRemove += AuraEffectRemoveFn(spell_timeless_isle_crane_wings_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const OVERRIDE
        {
            return new spell_timeless_isle_crane_wings_AuraScript();
        }
};

void AddSC_zone_timeless_isle()
{
	new player_on_enter_ti();
    new go_time_lost_shrine_ti();
    new go_gleaming_crane_statue_ti();
    new spell_timeless_isle_crane_wings();
}
