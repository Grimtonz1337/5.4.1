#include "ObjectMgr.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "Spell.h"
#include "Vehicle.h"
#include "Cell.h"
#include "CellImpl.h"
#include "GridNotifiers.h"
#include "GridNotifiersImpl.h"
#include "siege_of_orgrimmar.h"

enum Spells
{
	// Garrosh Hellscream

    // Intro
    SPELL_ATTACK_THRALL                 = 147831,

	// Phase 1
	SPELL_DESECRATE						= 144748,
	SPELL_HELLSCREAMS_WARSONG			= 144821,
	// Garrosh spawns Warbringers and Farseers also

	// Transition Phase
	SPELL_YSHAARJS_PROTECTION			= 144945,
	SPELL_REALM_OF_YSHAARJ				= 144954,
	SPELL_ANNIHILATE					= 144969,

	// Phase 2
	SPELL_WHIRLING_CORRUPTION			= 144985,
	SPELL_TOUCH_OF_YSHAARJ				= 145071,
	SPELL_GRIPPING_DESPAIR				= 145183,
	SPELL_EXPLOSIVE_DESPAIR				= 145213,

	// Phase 3
	SPELL_EMPOWERED_WHIRLING_CORRUPTION	= 145037,
	SPELL_EMPOWERED_TOUCH_OF_YSHAARJ	= 145175,
	SPELL_EMPOWERED_DESECRATE			= 145831,
	SPELL_EMPOWERED_GRIPPING_DESPAIR	= 145195,

	// Activates
	SPELL_ACTIVATE_WHIRL_CORRUPTION		= 145833,
	SPELL_ACTIVATE_TOUCH_OF_YSHAARJ		= 145832,
	SPELL_ACTIVATE_DESECRATE			= 145829,
	SPELL_ACTIVATE_GRIPPING_DESPAIR		= 145831,

	// Hidden Spells workarounds
	SPELL_THROW_AXE_AT_HEART			= 145235,
	SPELL_DRAG_EVERYONE					= 144866,
	SPELL_ABSORB_ENERGY					= 144946,
	SPELL_PHASE_2_TRIGGER				= 144958,
	SPELL_PHASE_3_TRIGGER				= 145647,
    SPELL_SUMMON_FADING_BREATH          = 147296,

    // Thrall
    SPELL_ASTRAL_RECALL                 = 147811,
    SPELL_CALL_OF_THE_ELEMENTS          = 147815,
    SPELL_ATTACK_GARROSH                = 147892,
    SPELL_EXHAUSTED                     = 147861,
    SPELL_LIGHTNING                     = 147804,

    // Kor'kron Warbringer
    SPELL_HAMSTRING                     = 144582,

    // Farseer Wolf Rider
    SPELL_ANCESTRAL_FURY                = 144585,
    SPELL_ANCESTRAL_CHAIN_HEAL          = 144583,
    SPELL_CHAIN_LIGHTNING               = 144584,
    SPELL_FURY                          = 144588,
};

enum Events
{
	// Intro
	EVENT_THRALL_SAY_1					= 1,
	EVENT_GARROSH_SAY_1					= 2,
	EVENT_GARROSH_SAY_2					= 3,
	EVENT_GARROSH_SAY_3					= 4,
	EVENT_GARROSH_EMOTE_1				= 5,
	EVENT_THRALL_SAY_2					= 6,
	EVENT_THRALL_CALL_SPIRITS			= 7,
	EVENT_GARROSH_SAY_4					= 8,
	EVENT_PRISON_THRALL					= 9,
	EVENT_THRALL_SAY_3					= 10,
	EVENT_THRALL_EMOTE_1				= 11,
	EVENT_GARROSH_SAY_5					= 12,
	EVENT_GARROSH_MOVE					= 13,
	EVENT_START_ATTACKING				= 14,
	EVENT_THRALL_EMOTE_2				= 15,
	EVENT_THRALL_ASTRAL_RECALL			= 16,
	EVENT_START_ENCOUNTER				= 17,

	// Events that trigger all the time
	EVENT_ENERGY_GAIN					= 18,

	// Phase 1
	EVENT_HELLSCREAM_WARSONG			= 19,
    EVENT_HELLSCREAMS_WARSONG           = 20,
	EVENT_DESECRATE						= 21,
	EVENT_SPAWN_WARBRINGERS				= 22,
	EVENT_SPAWN_FARSEERS				= 23,
	EVENT_SPAWN_SIEGE_ENGINEERS			= 24,

	// Phase 2
	EVENT_WHIRLING_CORRUPTION			= 25,
	EVENT_TOUCH_OF_YSHAARJ				= 26,
	EVENT_GRIPPING_DESPAIR				= 27,

	// Phase Transition
	EVENT_REALM_OF_YSHAARJ				= 28,
	EVENT_EVERYTHING_DEAD				= 29,
	EVENT_ANNIHILATE					= 30,
	EVENT_ABSORB_POWER					= 31,

	// Phase Workarounds
	EVENT_REALM_OF_YSHAARJ_1			= 32,
	EVENT_REALM_OF_YHSAARJ_2 			= 33,
	EVENT_REALM_OF_YSHAARJ_3			= 34,
	EVENT_REALM_OF_YSHAARJ_4			= 35,

	EVENT_PHASE_2_TRANSFORM_1			= 36,
	EVENT_PHASE_2_TRANSFORM_2			= 37,
	EVENT_PHASE_2_TRANSFORM_3			= 38,
	EVENT_PHASE_2_TRANSFORM_4			= 39,

    EVENT_PHASE_3_TRANSFORM_1           = 40,
	EVENT_PHASE_3_TRANSFORM_2			= 41,
	EVENT_PHASE_3_TRANSFORM_3			= 42,
	EVENT_PHASE_3_TRANSFORM_4			= 43,
	EVENT_PHASE_3_TRANSFORM_5			= 44,

    // Kor'kron Warbringer
    EVENT_HAMSTRING                     = 45,

    // Farseer Wolf Rider
    EVENT_ANCESTRAL_CHAIN_HEAL          = 46,
    EVENT_CHAIN_LIGHTNING               = 47,
};

enum Text
{
    // Garrosh Hellscream

    // Intro
	SAY_PRE_COMBAT_1					= 0, // "Ha! Do you remember nothing of Honor? Of glory on the battlefield? You who would parlay with the humans, who allowed warlocks to practice their dark magics right under our feet. You are weak."
	SAY_PRE_COMBAT_2					= 1, // "We are the Orcish Horde, the True Horde. We die, bloody and thrashing on the field of battle, like true orcs SHOULD."
	SAY_PRE_COMBAT_3					= 2, // "You are an Orc no longer, and speak for none but yourself. You betrayed our people to forge your fragile alliances, and I will take great pleasure in tearing them apart."
	SAY_PRE_COMBAT_4					= 3, // "Fool. My Dark Shaman have twisted and tortured the elements for miles around. They cannot hear you now. Once again you prove too weak and powerless to do anything."
	SAY_PRE_COMBAT_5					= 4, // "So, you wish to face off against a real Orc Warchief. So be it."

    // Combat
	SAY_AGGRO							= 5, // "I, Garrosh, son of Grom, will show you what it means to be called Hellscream!" "My people should have taken this world long ago, during the First War! But they fell to corruption in their weakness. They asked the pitiful races of Azeroth to join the Horde. I will succeed where they have failed, and no power in this world can stop me!"
	SAY_IRON_STAR						= 6, // "Witness the power of the true Horde's arsenal." "We will cleanse this world in steel and fire."
	SAY_WARBRINGERS						= 7, // "Warbringers, bloody your blades. Lok'tar Ogar!"
	SAY_FARSEERS						= 8, // "Farseers, mend our wounds!"
	SAY_WARSONG							= 9, // "For the True Horde!" "Die with honor!" "Blood and thunder!"
	SAY_PHASE_2							= 10, // "Anger, hatred, fear!! They are weapons of war - the tools of a Warchief!"
	SAY_PHASE_2_CONTINUED				= 11, // "Yes...yes. I can see it now...I can see the future of this world...A world ruled by the Horde...MY Horde."
	SAY_REALM_OF_YSHAARJ				= 12, // "The old one calls to you." "The Heart will be your end!" "See the visions of fear, despair and doubt as I have." "You will be trapped for eternity!"
	SAY_WHIRLING_CORRUPTION				= 13, // "The power flows through me!"
	SAY_EMPOWERED_WHIRLING_CORRUPTION	= 14, // "The power to crush your world, and everything on it!" "All will fall, in the name of Hellscream!"
	SAY_PHASE_3							= 15, // "The True Horde WILL come to pass. I have SEEN it. IT HAS SHOWN ME. I HAVE SEEN MOUNTAINS OF SKULLS AND RIVERS OF BLOOD. AND I WILL... HAVE... MY... WORLD!"
	SAY_PHASE_4							= 16, // "You think you have WON? You are BLIND. I WILL FORCE YOUR EYES OPEN!" "BEHOLD, MY GLORIOUS DESTINY!"
	SAY_UNSTABLE_IRON_STAR				= 17, // "THERE IS NO PLACE FOR YOU IN MY WORLD." "I WILL DESTROY EVERYTHING YOU HAVE EVER LOVED."
	SAY_KILL							= 18, // "Pitiful." "Weak."
	SAY_WIPE							= 19, // "Now you know your place in my new world."
	SAY_DEATH_NORMAL					= 20, // "No, it cannot end like this. What I…what I have seen?"
	SAY_DEATH_HEROIC					= 21, // "No... NO... This world... is my destiny... My, destiny."

    // Thrall

    SAY_THRALL_1                        = 0, // "It is not too late, Garrosh. Lay down the mantle of Warchief. We can end this here, now, with no more bloodshed."
    SAY_THRALL_2                        = 1, // "Then you have forced my hand. I will correct the mistake I made long ago. Spirits of the wind, the earth, the water, hear my call! Come to my aid!"
    SAY_THRALL_3                        = 2, // "Never powerless, Garrosh. And never alone."
};

enum Phases
{
	PHASE_NORMAL						= 1,
	PHASE_1								= 2,
	PHASE_TRANSITION 					= 3,
	PHASE_2								= 4,
	PHASE_3 							= 5,
	PHASE_4 							= 6, // Heroic only
};

enum Points
{
    // Garrosh Hellscream
	POINT_CENTER_1						= 1,
	POINT_CENTER_2						= 2,
};

enum Actions
{
	ACTION_START_INTRO					= 0,
	ACTION_HELLSCREAMS_WARSONG			= 1,
	ACTION_PHASE_2_TRANSFORM			= 2,
	ACTION_REALM_OF_YSHAARJ				= 3,
	ACTION_PHASE_3_TRANSFORM			= 4,
};

Position const Center					= {0.00000f, 0.00000f, 0.00000f, 0.00000f};
Position const ThrallFaceGarrosh        = {0.00000f, 0.00000f, 0.00000f, 0.00000f};
Position const GarroshFaceThrall        = {0.00000f, 0.00000f, 0.00000f, 0.00000f};
Position const NearCenter_1             = {0.00000f, 0.00000f, 0.00000f, 0.00000f};
Position const NearCenter_2             = {0.00000f, 0.00000f, 0.00000f, 0.00000f};

Position const KorkronSpawnPosition[6]	=
{
	{0.00000f, 0.00000f, 0.00000f, 0.00000f},
	{0.00000f, 0.00000f, 0.00000f, 0.00000f},
	{0.00000f, 0.00000f, 0.00000f, 0.00000f},
	{0.00000f, 0.00000f, 0.00000f, 0.00000f},
	{0.00000f, 0.00000f, 0.00000f, 0.00000f},
	{0.00000f, 0.00000f, 0.00000f, 0.00000f},
};

Position const SiegeEngineer[2]			=
{
	{0.00000f, 0.00000f, 0.00000f, 0.00000f},
	{0.00000f, 0.00000f, 0.00000f, 0.00000f},
};

#define ALL_PHASES                      (events.IsInPhase(PHASE_1) ? PHASE_2 : PHASE_3)
#define PHASE_2_3 	                    (events.IsInPhase(PHASE_2) ? PHASE_2 : PHASE_3)
#define HEALTH_PHASE_1                  RAID_MODE<uint64>(161370688, 451401792, 239875344, 236386256, 154915744, 236386256)

class StartCombat : public BasicEvent
{
    public:
        StartCombat(Creature* owner)
            : _owner(owner)
        {
        }

        bool Execute(uint64 /*time*/, uint32 /*diff*/)
        {
            _owner->SetReactState(REACT_AGGRESSIVE);
            if (Unit* target = _owner->AI()->SelectTarget(SELECT_TARGET_RANDOM, 0, 0.0f, true)
                _owner->AI()->AttackStart(target);
            return true;
        }

    private:
        Creature* _owner;
};

class PowerIronStar : public BasicEvent
{
    public:
        PowerIronStar(Creature* IronStar, Creature* owner)
            : Star(IronStar), _owner(owner)
        {
        }

        bool Execute(uint64 /*time*/, uint32 /*diff*/)
        {
            if (_owner->isDead())
            {
                Star->RemoveAllAuras();
                return true;
            }

            else
            {
                _owner->InterruptNonMeleeSpells(true);
                _owner->RemoveAllAuras();
                _owner->DespawnOrUnsummon(2000);
                if (Creature* Bunny = Star->SummonCreature(NPC_IRON_STAR_BUNNY, CenterPosition, TEMPSUMMON_MANUAL_DESPAWN))
                Star->GetMotionMaster()->MovePoint(POINT_EXPLODE, );
            }

            return true;
        }

    private:
        Creature* _summoner;
        Creature* _owner;
};

class boss_garrosh_hellscream : public CreatureScript
{
    public:
        boss_garrosh_hellscream() : CreatureScript("boss_garrosh_hellscream") { }

        struct boss_garrosh_hellscreamAI : public BossAI
        {
            boss_garrosh_hellscreamAI(Creature* creature) : BossAI(creature, DATA_GARROSH_HELLSCREAM) { }

            void Reset() OVERRIDE
            {
                _Reset();
                SetEquipmentSlots(true);
                events.SetPhase(PHASE_NORMAL);
                me->SetReactState(REACT_PASSIVE);
                me->SetPower(POWER_ENERGY, 0);
                me->SetMaxHealth(HEALTH_PHASE_1);
                me->SetHealth(HEALTH_PHASE_1);
                me->SetSheath(SHEATH_STATE_MELEE);
            }

            void JustDied(Unit* /*killer*/) OVERRIDE
            {
                if (!IsHeroic())
                	Talk(SAY_DEATH_NORMAL);

                else if (IsHeroic())
                	Talk(SAY_DEATH_HEROIC);
            }

            void EnterCombat(Unit* /*target*/) OVERRIDE
            {
                me->setActive(true);
                me->SetWalk(false);

                if (!events.IsInPhase(PHASE_TRANSITION)) // we don't want these spells in Transition phase...
                {
                	Talk(SAY_AGGRO);

                    events.SetPhase(PHASE_1);
                    events.ScheduleEvent(EVENT_HELLSCREAM_WARSONG, urand(21500, 24000), 0, PHASE_1);
                    events.ScheduleEvent(EVENT_DESECRATE, urand(10000, 12000), 0, ALL_PHASES);
                    events.ScheduleEvent(EVENT_SPAWN_WARBRINGERS, urand(43000, 45500), 0, PHASE_1);
                    events.ScheduleEvent(EVENT_SPAWN_FARSEERS, 30000, 0, PHASE_1);
                    events.ScheduleEvent(EVENT_SPAWN_SIEGE_ENGINEERS, 20000, 0, PHASE_1);
                    events.ScheduleEvent(EVENT_ENERGY_GAIN, 500, 0);

                    me->SummonCreature(NPC_KORKRON_WARBRINGER, KorkronSpawnPosition[0], TEMPSUMMON_MANUAL_DESPAWN);
                	me->SummonCreature(NPC_KORKRON_WARBRINGER, KorkronSpawnPosition[1], TEMPSUMMON_MANUAL_DESPAWN);
                	me->SummonCreature(NPC_KORKRON_WARBRINGER, KorkronSpawnPosition[2], TEMPSUMMON_MANUAL_DESPAWN);
                	me->SummonCreature(NPC_KORKRON_WARBRINGER, KorkronSpawnPosition[3], TEMPSUMMON_MANUAL_DESPAWN);
                	me->SummonCreature(NPC_KORKRON_WARBRINGER, KorkronSpawnPosition[4], TEMPSUMMON_MANUAL_DESPAWN);
                	me->SummonCreature(NPC_KORKRON_WARBRINGER, KorkronSpawnPosition[5], TEMPSUMMON_MANUAL_DESPAWN);
               	}
            }

            void JustReachedHome() OVERRIDE
            {
                _JustReachedHome();
                instance->SetBossState(DATA_GARROSH_HELLSCREAM, NOT_STARTED);
            }

            void EnterEvadeMode() OVERRIDE
            {
                instance->SetBossState(DATA_GARROSH_HELLSCREAM, FAIL);
                me->Respawn(true);
                me->SetReactState(REACT_PASSIVE);
                summons.DespawnAll();
                BossAI::EnterEvadeMode();
            }

            void KilledUnit(Unit* victim) OVERRIDE
            {
                if (victim->GetTypeId() == TYPEID_PLAYER && !me->IsInEvadeMode()) // I am not sure if he yells something when he kills you in Transition...
                    Talk(SAY_KILL);

                if (!me->GetVictim() && !me->IsInEvadeMode())
                {
                	BossAI::EnterEvadeMode();
                	Talk(SAY_WIPE);
                }
            }

            void DoAction(int32 action) OVERRIDE
            {
                switch (action)
                {
                    case ACTION_START_INTRO:
                        if (!me->FindNearestCreature(NPC_THRALL, 100.0f))
                            me->SummonCreature(NPC_THRALL, Center, TEMPSUMMON_MANUAL_DESPAWN);

                        events.ScheduleEvent(EVENT_THRALL_SAY_1, 1, 1, PHASE_NORMAL);
                        events.ScheduleEvent(EVENT_GARROSH_SAY_1, 12000, 1, PHASE_NORMAL);
                        events.ScheduleEvent(EVENT_GARROSH_SAY_2, 34000, 1, PHASE_NORMAL);
                        events.ScheduleEvent(EVENT_GARROSH_SAY_3, 47000, 1, PHASE_NORMAL);
                        events.ScheduleEvent(EVENT_GARROSH_EMOTE_1, 53000, 1, PHASE_NORMAL);
                        events.ScheduleEvent(EVENT_THRALL_SAY_2, 65000, 1, PHASE_NORMAL);
                        events.ScheduleEvent(EVENT_THRALL_CALL_SPIRITS, 73000, 1, PHASE_NORMAL);
                        events.ScheduleEvent(EVENT_GARROSH_SAY_4, 80000, 1, PHASE_NORMAL);
                        events.ScheduleEvent(EVENT_PRISON_THRALL, 85000, 1, PHASE_NORMAL);
                        events.ScheduleEvent(EVENT_THRALL_SAY_3, 101000, 1, PHASE_NORMAL);
                        events.ScheduleEvent(EVENT_THRALL_EMOTE_2, 107000, 1, PHASE_NORMAL);
                        events.ScheduleEvent(EVENT_GARROSH_SAY_5, 108000, 1, PHASE_NORMAL);
                        events.ScheduleEvent(EVENT_GARROSH_MOVE, 110000, 1, PHASE_NORMAL);
                        events.ScheduleEvent(EVENT_START_ATTACKING, 118000, 1, PHASE_NORMAL);
                        events.ScheduleEvent(EVENT_THRALL_EMOTE_1, 122000, 1, PHASE_NORMAL);
                        events.ScheduleEvent(EVENT_THRALL_ASTRAL_RECALL, 137000, 1, PHASE_NORMAL);
                        events.ScheduleEvent(EVENT_START_ENCOUNTER, 140000, 1, PHASE_NORMAL);
                        break;
                    case ACTION_HELLSCREAMS_WARSONG:
                        DoCastAOE(SPELL_HELLSCREAMS_WARSONG, false);
                        events.ScheduleEvent(EVENT_HELLSCREAMS_WARSONG, 1500, 1, PHASE_1);
                        break;
                    case ACTION_PHASE_2_TRANSFORM:
                        events.ScheduleEvent(EVENT_REALM_OF_YSHAARJ, 25000, 0, PHASE_2);
                        events.ScheduleEvent(EVENT_PHASE_2_TRANSFORM_1, 500, 1, PHASE_2);
                        events.ScheduleEvent(EVENT_PHASE_2_TRANSFORM_2, 4500, 1, PHASE_2);
                        events.ScheduleEvent(EVENT_PHASE_2_TRANSFORM_3, 6000, 1, PHASE_2);
                        events.ScheduleEvent(EVENT_PHASE_2_TRANSFORM_4, 12000, 1, PHASE_2);
                        break;
                    case ACTION_REALM_OF_YSHAARJ:
                    	if (Creature* Heart = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_HEART_OF_YSHAARJ_SANCTUM)))
                    		Heart->AI()->DoCastAOE(SPELL_DRAG_EVERYONE);

                    	me->SetHealth(me->GetHealthPct() + 10.0f);

                    	events.RescheduleEvent(EVENT_DESECRATE, urand(72000, 73000), 0, ALL_PHASES);
                    	events.RescheduleEvent(EVENT_TOUCH_OF_YSHAARJ, urand(77000, 78500), 0, PHASE_2_3);
                    	events.RescheduleEvent(EVENT_WHIRLING_CORRUPTION, urand(92000, 94000), 0, PHASE_2_3);
                    	events.RescheduleEvent(EVENT_GRIPPING_DESPAIR, urand(77000, 79000), 0, PHASE_2_3);
                    	events.ScheduleEvent(EVENT_EVERYTHING_DEAD, 5000, 0, PHASE_TRANSITION);
                    	events.ScheduleEvent(EVENT_ABSORB_POWER, 6000, 0, PHASE_TRANSITION); // every 2 seconds, he gains 1 power
                    	events.ScheduleEvent(EVENT_REALM_OF_YSHAARJ_1, 2000, 0, PHASE_TRANSITION);
                    	events.ScheduleEvent(EVENT_REALM_OF_YHSAARJ_2, 4000, 0, PHASE_TRANSITION);
                    	events.ScheduleEvent(EVENT_REALM_OF_YSHAARJ_4, 62000, 0, PHASE_TRANSITION);
                    	break;
                    case ACTION_PHASE_3_TRANSFORM:
                        events.ScheduleEvent(EVENT_PHASE_3_TRANSFORM_1, 100, 0, PHASE_3);
                    	events.ScheduleEvent(EVENT_PHASE_3_TRANSFORM_2, 4000, 0, PHASE_3);
                    	events.ScheduleEvent(EVENT_PHASE_3_TRANSFORM_3, 7000, 0, PHASE_3);
                    	events.ScheduleEvent(EVENT_PHASE_3_TRANSFORM_4, 10000, 0, PHASE_3);
                    	events.ScheduleEvent(EVENT_PHASE_3_TRANSFORM_5, 12000, 0, PHASE_3);
                    	break;
                    default:
                        break;
                }
            }

            void DamageTaken(Unit* /*attacker*/, uint32& /*damage*/) OVERRIDE
            {
                if (events.IsInPhase(PHASE_1) && !HealthAbovePct(10))
                {
                    events.SetPhase(PHASE_2);
                    me->SetReactState(REACT_PASSIVE);
                    me->AttackStop();
                    me->GetMotionMaster()->MovePoint(POINT_CENTER_1, Center);
                    return;
                }

                if (events.IsInPhase(PHASE_2) && !HealthAbovePct(10))
                {
                    events.SetPhase(PHASE_3);
                    events.RescheduleEvent(EVENT_DESECRATE, urand(21000, 22000), 0, PHASE_3);
                    events.RescheduleEvent(EVENT_TOUCH_OF_YSHAARJ, urand(30000, 31500), 0, PHASE_3);
                    events.RescheduleEvent(EVENT_WHIRLING_CORRUPTION, 45000, 0, PHASE_3);
                    events.RescheduleEvent(EVENT_GRIPPING_DESPAIR, urand(10000, 11000), 0, PHASE_3);
                    me->SetReactState(REACT_PASSIVE);
                    me->AttackStop();
                    me->GetMotionMaster()->MovePoint(POINT_CENTER_2, Center);
                    return;
                }

                if (IsHeroic())
                {
                    if (events.IsInPhase(PHASE_3) && !HealthAbovePct(10))
                    {
                        events.SetPhase(PHASE_4);
                        // TODO
                        return;
                    }
                }
            }

            void SpellHitTarget(Unit* /*target*/, SpellInfo const* spell) OVERRIDE
            {
                if (spell->Id == SPELL_YSHAARJS_PROTECTION)
                    me->SetReactState(REACT_PASSIVE);
            }

            void MovementInform(uint32 type, uint32 pointId) OVERRIDE
            {
                if (type != POINT_MOTION_TYPE)
                    return;

                switch (pointId)
                {
                    case POINT_CENTER_1:
                        me->AI()->DoAction(ACTION_PHASE_2_TRANSFORM);
                        break;
                    case POINT_CENTER_2:
                        me->AI()->DoAction(ACTION_PHASE_3_TRANSFORM);
                        break;
                    default:
                        break;
                }
            }

            void UpdateAI(uint32 diff) OVERRIDE
            {
                if (!UpdateVictim())
                    return;

                events.Update(diff);

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_THRALL_SAY_1:
                            if (Creature* Thrall = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_THRALL)))
                            {
                                Thrall->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_ONESHOT_TALK);
                                Thrall->AI()->Talk(SAY_THRALL_1);
                            }

                            break;
                        case EVENT_GARROSH_SAY_1:
                            if (Creature* Thrall = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_THRALL)))
                                Thrall->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_ONESHOT_NONE);

                            me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_ONESHOT_TALK);
                            Talk(SAY_PRE_COMBAT_1);
                            break;
                        case EVENT_GARROSH_SAY_2:
                            Talk(SAY_PRE_COMBAT_2);
                            break;
                        case EVENT_GARROSH_SAY_3:
                            me->HandleEmoteCommand(EMOTE_ONESHOT_ROAR);
                            Talk(SAY_PRE_COMBAT_3);
                            break;
                        case EVENT_GARROSH_EMOTE_1:
                            me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_ONESHOT_TALK);
                            break;
                        case EVENT_THRALL_SAY_2:
                            if (Creature* Thrall = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_THRALL)))
                            {
                                Thrall->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_ONESHOT_TALK);
                                Thrall->AI()->Talk(SAY_THRALL_2);
                            }

                            me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_ONESHOT_NONE);
                            break;
                        case EVENT_THRALL_CALL_SPIRITS:
                            if (Creature* Thrall = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_THRALL)))
                            {
                                Thrall->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_ONESHOT_NONE);
                                Thrall->CastSpell(Thrall, SPELL_CALL_OF_THE_ELEMENTS, false);
                            }

                            break;
                        case EVENT_GARROSH_SAY_4:
                            me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_ONESHOT_TALK);
                            Talk(SAY_PRE_COMBAT_4);
                            break;
                        case EVENT_PRISON_THRALL:
                            // TODO he needs to be prisoned with a purple-ish spell
                            break;
                        case EVENT_THRALL_SAY_3:
                            me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_ONESHOT_NONE);

                            if (Creature* Thrall = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_THRALL)))
                            {
                                Thrall->CastSpell(Thrall, SPELL_LIGHTNING, false);
                                Thrall->AI()->Talk(SAY_THRALL_3);
                            }

                            break;
                        case EVENT_THRALL_EMOTE_1:
                            if (Creature* Thrall = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_THRALL)))
                                Thrall->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_READY2H);

                            break;
                        case EVENT_GARROSH_SAY_5:
                            me->HandleEmoteCommand(EMOTE_ONESHOT_TALK);
                            Talk(SAY_PRE_COMBAT_5);
                            break;
                        case EVENT_GARROSH_MOVE:
                            if (Creature* Thrall = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_THRALL)))
                            {
                                Thrall->SetWalk(false);
                                Thrall->GetMotionMaster()->MovePoint(0, ThrallFaceGarrosh);
                            }

                            me->SetWalk(true);
                            me->GetMotionMaster()->MovePoint(0, GarroshFaceThrall);
                            me->HandleEmoteCommand(EMOTE_ONESHOT_NONE);
                            break;
                        case EVENT_START_ATTACKING:
                            if (Creature* Thrall = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_THRALL)))
                            {
                                Thrall->CastSpell(me, SPELL_ATTACK_GARROSH, false);
                                me->CastSpell(Thrall, SPELL_ATTACK_THRALL, false);
                            }

                            break;
                        case EVENT_THRALL_EMOTE_2:
                            if (Creature* Thrall = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_THRALL)))
                            {
                                Thrall->AddAura(SPELL_EXHAUSTED, Thrall);
                                // TODO he needs to get knocked back by a spell that garrosh uses...
                            }

                            me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_ONESHOT_NONE);
                            break;
                        case EVENT_THRALL_ASTRAL_RECALL:
                            if (Creature* Thrall = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_THRALL)))
                                Thrall->CastSpell(Thrall, SPELL_ASTRAL_RECALL, false);

                            break;
                        case EVENT_START_ENCOUNTER:
                            me->SetReactState(REACT_AGGRESSIVE);
                            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
                            break;
                        case EVENT_ENERGY_GAIN:
                        	if (me->IsInCombat() && !me->isDead())
                        	{
                        		if (me->GetPower(POWER_ENERGY) <= 24)
                        		{
                        			me->RemoveAurasDueToSpell(SPELL_ACTIVATE_WHIRL_CORRUPTION);
                        			me->RemoveAurasDueToSpell(SPELL_ACTIVATE_DESECRATE);
                        			me->RemoveAurasDueToSpell(SPELL_ACTIVATE_GRIPPING_DESPAIR);
                        			me->RemoveAurasDueToSpell(SPELL_ACTIVATE_TOUCH_OF_YSHAARJ);
                        		}

                        		if (me->GetPower(POWER_ENERGY) >= 25)
                        		{
                        			if (me->HasAura(SPELL_ACTIVATE_WHIRL_CORRUPTION))
                        				return;

                        			else if (!me->HasAura(SPELL_ACTIVATE_WHIRL_CORRUPTION))
                        				me->AddAura(SPELL_ACTIVATE_WHIRL_CORRUPTION, me);
                        		}

                        		if (me->GetPower(POWER_ENERGY) >= 50)
                        		{
                        			if (me->HasAura(SPELL_ACTIVATE_TOUCH_OF_YSHAARJ))
                        				return;

                        			else if (!me->HasAura(SPELL_ACTIVATE_TOUCH_OF_YSHAARJ))
                        				me->AddAura(SPELL_ACTIVATE_TOUCH_OF_YSHAARJ, me);
                        		}

                        		if (me->GetPower(POWER_ENERGY) >= 75)
                        		{
                        			if (me->HasAura(SPELL_ACTIVATE_DESECRATE))
                        				return;

                        			if (!me->HasAura(SPELL_ACTIVATE_DESECRATE))
                        				me->AddAura(SPELL_ACTIVATE_DESECRATE, me);
                        		}

                        		if (me->GetPower(POWER_ENERGY) == 100)
                        		{
                        			if (me->HasAura(SPELL_ACTIVATE_GRIPPING_DESPAIR))
                        				return;

                        			else if (!me->HasAura(SPELL_ACTIVATE_GRIPPING_DESPAIR))
                        				me->AddAura(SPELL_ACTIVATE_GRIPPING_DESPAIR, me);
                        		}
                        	}

                        	else if (!me->IsInCombat() && me->isDead())
                        		return;

                        	events.ScheduleEvent(EVENT_ENERGY_GAIN, 500, 0);
                        	break;
                        case EVENT_HELLSCREAM_WARSONG:
                            me->AI()->DoAction(ACTION_HELLSCREAMS_WARSONG);
                            events.ScheduleEvent(EVENT_HELLSCREAM_WARSONG, urand(40000, 42000), 0, PHASE_1);
                            break;
                        case EVENT_HELLSCREAMS_WARSONG:
                            Talk(SAY_WARSONG);
                            break;
                        case EVENT_DESECRATE:
                            if (!me->HasAura(SPELL_ACTIVATE_DESECRATE))
                            {
                                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.0f, true))
                                    DoCast(target, SPELL_DESECRATE);
                            }

                            else if (me->HasAura(SPELL_ACTIVATE_DESECRATE))
                            {
                                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.0f, true))
                                    DoCast(target, SPELL_EMPOWERED_DESECRATE);
                            }

                            events.ScheduleEvent(EVENT_DESECRATE, urand(39500, 41500), 0, ALL_PHASES);
                            break;
                        case EVENT_SPAWN_WARBRINGERS:
                            Talk(SAY_WARBRINGERS);
                            Choice = urand(1, 2);

                            if (Choice == 1)
                            {
                                me->SummonCreature(NPC_KORKRON_WARBRINGER, KorkronSpawnPosition[0], TEMPSUMMON_MANUAL_DESPAWN);
                                me->SummonCreature(NPC_KORKRON_WARBRINGER, KorkronSpawnPosition[1], TEMPSUMMON_MANUAL_DESPAWN);
                                me->SummonCreature(NPC_KORKRON_WARBRINGER, KorkronSpawnPosition[2], TEMPSUMMON_MANUAL_DESPAWN);
                            }

                            if (Choice == 2)
                            {
                                me->SummonCreature(NPC_KORKRON_WARBRINGER, KorkronSpawnPosition[3], TEMPSUMMON_MANUAL_DESPAWN);
                                me->SummonCreature(NPC_KORKRON_WARBRINGER, KorkronSpawnPosition[4], TEMPSUMMON_MANUAL_DESPAWN);
                                me->SummonCreature(NPC_KORKRON_WARBRINGER, KorkronSpawnPosition[5], TEMPSUMMON_MANUAL_DESPAWN);
                            }

                            events.ScheduleEvent(EVENT_SPAWN_WARBRINGERS, urand(38000, 42000), 0, PHASE_1);
                            break;
                        case EVENT_SPAWN_FARSEERS:
                            Talk(SAY_FARSEERS);
                            Choice = urand(1, 2);

                            if (Choice == 1)
                            {
                                me->SummonCreature(NPC_KORKRON_FARSEER, KorkronSpawnPosition[1], TEMPSUMMON_MANUAL_DESPAWN);
                            }

                            if (Choice == 2)
                            {
                                me->SummonCreature(NPC_KORKRON_FARSEER, KorkronSpawnPosition[4], TEMPSUMMON_MANUAL_DESPAWN);
                            }

                            events.ScheduleEvent(EVENT_SPAWN_FARSEERS, urand(48050, 50050), 0, PHASE_1);
                            break;
                        case EVENT_SPAWN_SIEGE_ENGINEERS:
                            me->SummonCreature(NPC_SIEGE_ENGINEER, SiegeEngineer[0], TEMPSUMMON_MANUAL_DESPAWN);
                            me->SummonCreature(NPC_SIEGE_ENGINEER, SiegeEngineer[1], TEMPSUMMON_MANUAL_DESPAWN);
                            events.ScheduleEvent(EVENT_SPAWN_SIEGE_ENGINEERS, 40000, 0, PHASE_1);
                            break;
                        case EVENT_WHIRLING_CORRUPTION:
                        	if (!me->HasAura(SPELL_ACTIVATE_WHIRL_CORRUPTION))
                        	{
                        		DoCastAOE(SPELL_WHIRLING_CORRUPTION, false);
                        		Talk(SAY_WHIRLING_CORRUPTION);
                        	}

                        	else if (me->HasAura(SPELL_ACTIVATE_WHIRL_CORRUPTION))
                        	{
                        		DoCastAOE(SPELL_EMPOWERED_WHIRLING_CORRUPTION, false);
                        		Talk(SAY_EMPOWERED_WHIRLING_CORRUPTION);
                        	}

                        	events.ScheduleEvent(EVENT_WHIRLING_CORRUPTION, urand(45000, 50000), 0, PHASE_2_3);
                        	break;
                        case EVENT_TOUCH_OF_YSHAARJ:
                        	if (!me->HasAura(SPELL_ACTIVATE_TOUCH_OF_YSHAARJ))
                        	{
                        		if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1, 0.0f, true, -SPELL_TOUCH_OF_YSHAARJ))
                        			DoCast(target, SPELL_TOUCH_OF_YSHAARJ);
                        	}

                        	else if (me->HasAura(SPELL_ACTIVATE_TOUCH_OF_YSHAARJ))
                        	{
                        		if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1, 0.0f, true, -SPELL_EMPOWERED_TOUCH_OF_YSHAARJ))
                        			DoCast(target, SPELL_EMPOWERED_TOUCH_OF_YSHAARJ);
                        	}

                        	events.ScheduleEvent(EVENT_TOUCH_OF_YSHAARJ, 45000, 0, PHASE_2_3);
                        	break;
                        case EVENT_GRIPPING_DESPAIR:
                        	if (!me->HasAura(SPELL_ACTIVATE_GRIPPING_DESPAIR))
                        	{
                        		if (me->IsWithinMeleeRange(me->GetVictim()))
                        			DoCastVictim(SPELL_GRIPPING_DESPAIR);
                        	}

                        	else if (me->HasAura(SPELL_ACTIVATE_GRIPPING_DESPAIR))
                        	{
                        		if (me->IsWithinMeleeRange(me->GetVictim()))
                        			DoCastVictim(SPELL_EMPOWERED_GRIPPING_DESPAIR);
                        	}

                        	events.ScheduleEvent(EVENT_GRIPPING_DESPAIR, urand(15000, 17000), 0, PHASE_2_3);
                        	break;
                        case EVENT_REALM_OF_YSHAARJ:
                        	events.SetPhase(PHASE_TRANSITION);
                        	me->AI()->DoAction(ACTION_REALM_OF_YSHAARJ);
                        	break;
                        case EVENT_EVERYTHING_DEAD:
                        	if (!me->FindNearestCreature(NPC_EMBODIED_FEAR, 200.0f))
                        	{
                        		me->RemoveAurasDueToSpell(SPELL_YSHAARJS_PROTECTION);
                        		me->RemoveAurasDueToSpell(SPELL_ABSORB_ENERGY);
                        		events.ScheduleEvent(EVENT_REALM_OF_YSHAARJ_3, 2500, 0, PHASE_TRANSITION);
                        	}

                        	else if (me->FindNearestCreature(NPC_EMBODIED_FEAR, 200.0f))
                        		events.ScheduleEvent(EVENT_EVERYTHING_DEAD, 500, 0, PHASE_TRANSITION);

                        	if (!me->FindNearestCreature(NPC_EMBODIED_DOUBT, 200.0f))
                        	{
                        		me->RemoveAurasDueToSpell(SPELL_YSHAARJS_PROTECTION);
                        		me->RemoveAurasDueToSpell(SPELL_ABSORB_ENERGY);
                        		events.ScheduleEvent(EVENT_REALM_OF_YSHAARJ_3, 2500, 0, PHASE_TRANSITION);
                        	}

                        	else if (me->FindNearestCreature(NPC_EMBODIED_FEAR, 200.0f))
                        		events.ScheduleEvent(EVENT_EVERYTHING_DEAD, 500, 0, PHASE_TRANSITION);

                        	if (!me->FindNearestCreature(NPC_EMBODIED_DESPAIR, 200.0f))
                        	{
                        		me->RemoveAurasDueToSpell(SPELL_YSHAARJS_PROTECTION);
                        		me->RemoveAurasDueToSpell(SPELL_ABSORB_ENERGY);
                        		events.ScheduleEvent(EVENT_REALM_OF_YSHAARJ_3, 2500, 0, PHASE_TRANSITION);
                        	}

                        	else if (me->FindNearestCreature(NPC_EMBODIED_DESPAIR, 200.0f))
                        		events.ScheduleEvent(EVENT_EVERYTHING_DEAD, 500, 0, PHASE_TRANSITION);

                        	break;
						case EVENT_ANNIHILATE:
							if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.0f, true))
							{
								me->SetFacingToObject(target);
								me->SetReactState(REACT_PASSIVE);
								DoCast(target, SPELL_ANNIHILATE);
							}

							events.ScheduleEvent(EVENT_ANNIHILATE, 3000, 0, PHASE_TRANSITION);
							break;
						case EVENT_ABSORB_POWER:
							if (me->HasAura(SPELL_ABSORB_ENERGY))
								me->ModifyPower(POWER_ENERGY, 1);

							events.ScheduleEvent(EVENT_ABSORB_POWER, 2000, 0, PHASE_TRANSITION);
							break;
						case EVENT_REALM_OF_YSHAARJ_1:
                        	// TODO make players teleport to a realm of yshaarj

                        	break;
                        case EVENT_REALM_OF_YHSAARJ_2:
                        	DoCast(me, SPELL_YSHAARJS_PROTECTION);
                        	DoCast(me, SPELL_ABSORB_ENERGY);
                        	Talk(SAY_REALM_OF_YSHAARJ);
                            DoZoneInCombat(me, 200.0f);
                        	instance->DoCastSpellOnPlayers(SPELL_REALM_OF_YSHAARJ);

                        	break;
                        case EVENT_REALM_OF_YSHAARJ_3:
                        	me->SetReactState(REACT_PASSIVE);
                        	me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_READY2H);

                        	events.ScheduleEvent(EVENT_ANNIHILATE, 1, 0, PHASE_TRANSITION);
							break;
						case EVENT_REALM_OF_YSHAARJ_4:
							me->SetReactState(REACT_AGGRESSIVE);
                            me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_ONESHOT_NONE);
							// DoCastAOE(SPELL_JUMP_TO_GROUND); TODO make everyone teleport to the main area, at the heart of yshaarj in the inner sanctum
							break;
						case EVENT_PHASE_2_TRANSFORM_1:
                            Talk(SAY_PHASE_2);
                            break;
                        case EVENT_PHASE_2_TRANSFORM_2:
                        	if (Creature* Heart = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_HEART_OF_YSHAARJ_SANCTUM)))
                            	DoCast(Heart, SPELL_THROW_AXE_AT_HEART);
                            break;
                        case EVENT_PHASE_2_TRANSFORM_3:
                        	DoCast(me, SPELL_PHASE_2_TRIGGER);
                            // me->HandleEmoteCommand(TODO);
                            me->SetDisableGravity(true);
                            me->GetMotionMaster()->MovePoint(0, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ()+4, me->GetOrientation());
                            break;
                        case EVENT_PHASE_2_TRANSFORM_4:
                        	me->SetFullHealth();
                        	me->RemoveAurasDueToSpell(SPELL_PHASE_2_TRIGGER);
                            me->SetDisableGravity(false);
                            me->GetMotionMaster()->MoveFall();
                            me->SetReactState(REACT_AGGRESSIVE);
                            Talk(SAY_PHASE_2_CONTINUED);
                            break;
                        case EVENT_PHASE_3_TRANSFORM_1:
                            Talk(SAY_PHASE_3);
                            break;
                        case EVENT_PHASE_3_TRANSFORM_2:
							// me->HandleEmoteCommand(TODO);
							break;
						case EVENT_PHASE_3_TRANSFORM_3:
							DoCast(me, SPELL_PHASE_3_TRIGGER);
							break;
						case EVENT_PHASE_3_TRANSFORM_4:
							// me->SetDisplayId(TODO);
							me->SetHealth(me->GetHealthPct() + 20.0f); // I think this is right...
							me->ModifyPowerPct(POWER_ENERGY, 100.0f, true);

							break;
						case EVENT_PHASE_3_TRANSFORM_5:
							me->SetReactState(REACT_AGGRESSIVE);
							break;
                        default:
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }

        private:
            InstanceScript* instance;

            uint8 Choice;

            void SendPacketToPlayers(WorldPacket const* data) const
            {
                Map::PlayerList const& players = me->GetMap()->GetPlayers();
                if (!players.isEmpty())
                {
                    for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr)
                    {
                        if (Player* player = itr->GetSource())
                        {
                            player->GetSession()->SendPacket(data);
                        }
                    }
                }
            }
        };

        CreatureAI* GetAI(Creature* creature) const OVERRIDE
        {
            return new boss_garrosh_hellscreamAI(creature);
        }
};

class npc_korkron_warbringer : public CreatureScript
{
    public:
        npc_korkron_warbringer() :  CreatureScript("npc_korkron_warbringer") { }

        struct npc_korkron_warbringerAI : public ScriptedAI
        {
            npc_korkron_warbringerAI(Creature* creature) : ScriptedAI(creature) { }

            void Reset() OVERRIDE
            {
                _events.Reset();
                me->SetReactState(REACT_PASSIVE);
                me->SetSheath(SHEATH_STATE_MELEE);
            }

            void EnterCombat(Unit* target) OVERRIDE
            {
                me->SetWalk(false);
                me->SetReactState(REACT_AGGRESSIVE);

                _events.ScheduleEvent(EVENT_HAMSTRING, urand(8000, 14000)); // TODO adjust timers
            }

            void IsSummonedBy(Unit* summoner) OVERRIDE
            {
                if (summoner->GetEntry() == NPC_GARROSH_HELLSCREAM)
                {
                    if (Creature* Point = me->FindNearestCreature(NPC_POINT_BUNNY, 500.0f))
                    {
                        me->SetWalk(false);
                        me->GetMotionMaster()->MovePoint(0, Point->GetPositionX(), Point->GetPositionY(), Point->GetPositionZ(), Point->GetOrientation());
                        me->m_Events.AddEvent(new StartCombat(me), me->m_Events.CalculateTime(5000));
                    }
                }
            }

            void UpdateAI(uint32 diff) OVERRIDE
            {
                if (!UpdateVictim())
                    return;

                _events.Update(diff);

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                while (uint32 eventId = _events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_HAMSTRING:
                            if (me->IsWithinMeleeRange(me->GetVictim()))
                                DoCastVictim(SPELL_HAMSTRING);

                            _events.ScheduleEvent(EVENT_HAMSTRING, urand(8000, 11000));
                            break;
                        default:
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }

            private:
                EventMap* _events;
        };

        CreatureAI* GetAI(Creature* creature) const OVERRIDE
        {
            return new npc_korkron_warbringerAI(creature);
        }
};

class npc_farseer_wolf_rider : public CreatureScript
{
    public:
        npc_farseer_wolf_rider() :  CreatureScript("npc_farseer_wolf_rider") { }

        struct npc_farseer_wolf_riderAI : public ScriptedAI
        {
            npc_farseer_wolf_riderAI(Creature* creature) : ScriptedAI(creature) { }

            void Reset() OVERRIDE
            {
                _events.Reset();
                me->SetReactState(REACT_PASSIVE);
                me->SetSheath(SHEATH_STATE_MELEE); // not sure if he has a weapon...
            }

            void EnterCombat(Unit* /*target*/) OVERRIDE
            {
                me->SetWalk(false);
                me->SetReactState(REACT_AGGRESSIVE);

                _events.ScheduleEvent(EVENT_ANCESTRAL_CHAIN_HEAL, urand(6000, 9000)); // TODO adjust timers
                _events.ScheduleEvent(EVENT_CHAIN_LIGHTNING, urand(8000, 13000)); // TODO adjust timers
            }

            void IsSummonedBy(Unit* summoner) OVERRIDE
            {
                if (summoner->GetEntry() == NPC_GARROSH_HELLSCREAM)
                {
                    if (Creature* Point = me->FindNearestCreature(NPC_POINT_BUNNY, 500.0f))
                    {
                        me->SetWalk(false);
                        me->GetMotionMaster()->MovePoint(0, Point->GetPositionX(), Point->GetPositionY(), Point->GetPositionZ(), Point->GetOrientation());
                        me->AddAura(SPELL_ANCESTRAL_FURY, me);
                        me->m_Events.AddEvent(new StartCombat(me), me->m_Events.CalculateTime(5000));
                    }
                }
            }

            void SpellInterrupted(uint32 spellId, uint32 /*unTimeMs*/) // TODO, check if Ancrestral Fury works correctly. If it does, remove this chunk of code
            {
                switch (spellId->Id)
                {
                    case SPELL_ANCESTRAL_CHAIN_HEAL:
                        me->AddAura(SPELL_FURY, me);
                        break;
                    case SPELL_CHAIN_LIGHTNING:
                        me->AddAura(SPELL_FURY, me);
                        break;
                    default:
                        break;
                }
            }

            void UpdateAI(uint32 diff) OVERRIDE
            {
                if (!UpdateVictim())
                    return;

                _events.Update(diff);

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                while (uint32 eventId = _events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_ANCESTRAL_CHAIN_HEAL:
                            if (Creature* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.0f, false))
                            {
                                if (target->isDead())
                                    return;

                                else if (!target->isDead())
                                {
                                    if (target->GetTypeId() == TYPEID_PLAYER)
                                        return;

                                    else
                                        DoCast(target, SPELL_ANCESTRAL_CHAIN_HEAL);
                                }
                            }

                            _events.ScheduleEvent(EVENT_ANCESTRAL_CHAIN_HEAL, urand(8000, 14000)); // TODO adjust timers
                            break;
                        case EVENT_CHAIN_LIGHTNING:
                            DoCastAOE(SPELL_CHAIN_LIGHTNING, false);

                            _events.ScheduleEvent(EVENT_CHAIN_LIGHTNING, urand(10000, 14000)); // TODO adjust timers
                            break;
                        default:
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }

            private:
                EventMap* _events;
        };

        CreatureAI* GetAI(Creature* creature) const OVERRIDE
        {
            return new npc_farseer_wolf_riderAI(creature);
        }
};

class at_inner_sanctum : public AreaTriggerScript
{
public:
    at_inner_sanctum() : AreaTriggerScript("at_inner_sanctum") { }

    bool OnTrigger(Player* player, const AreaTriggerEntry* /*at*/) OVERRIDE
    {
        InstanceScript* _instance = player->GetInstanceScript();

        if (player->IsGameMaster())
            return true;

        if (_instance->GetData(DATA_GARROSH_HELLSCREAM) == NOT_STARTED)
        {
            _instance->SetData(DATA_GARROSH_HELLSCREAM, IN_PROGRESS);
        }

        return true;
    }

    private:
        InstanceScript* _instance;
};

class npc_siege_engineer : public CreatureScript
{
    public:
        npc_siege_engineer() :  CreatureScript("npc_siege_engineer") { }

        struct npc_siege_engineerAI : public ScriptedAI
        {
            npc_siege_engineerAI(Creature* creature) : ScriptedAI(creature) { }

            void Reset() OVERRIDE
            {
                _events.Reset();
                me->SetReactState(REACT_PASSIVE);
            }

            void EnterCombat(Unit* /*target*/) OVERRIDE
            {
                me->SetWalk(false);
                me->SetReactState(REACT_PASSIVE);
                // this is a quick workaround. he doesn't anything... at all.
            }

            void IsSummonedBy(Unit* summoner) OVERRIDE
            {
                if (summoner->GetEntry() == NPC_GARROSH_HELLSCREAM)
                {
                    if (Creature* Point = me->FindNearestCreature(NPC_SIEGE_ENGINEER_POINT_BUNNY, 100.0f))
                    {
                        me->SetWalk(false);
                        me->GetMotionMaster()->MovePoint(POINT_SIEGE_ENGINEER, Point->GetPositionX(), Point->GetPositionY(), Point->GetPositionZ(), Point->GetOrientation());
                    }
                }
            }

            void UpdateAI(uint32 diff) OVERRIDE
            {
                if (!UpdateVictim())
                    return;

                _events.Update(diff);

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                while (uint32 eventId = _events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_ACTIVATE_IRON_STAR:
                            if (Creature* Star = me->FindNearestCreature(NPC_IRON_STAR, 50.0f))
                            {
                                me->SetFacingToObject(Star);
                                me->CastSpell(Star, SPELL_POWER_IRON_STAR, false);
                            }
                    }
                }
            }

void AddSC_boss_garrosh_hellscream()
{
    new boss_garrosh_hellscream();
    new npc_korkron_warbringer();
    new npc_farseer_wolf_rider();
    new npc_siege_engineer();
    new at_inner_sanctum();
}
