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

enum Datas
{
	DATA_CHI_JI							= 0,
	DATA_NIUZAO							= 1,
	DATA_YU_LON							= 2,
	DATA_XUEN							= 3,
	DATA_ORDOS							= 4,
};

enum Bosses
{
	BOSS_CHI_JI							= 71952,
	BOSS_NIUZAO							= 71954,
	BOSS_YU_LON							= 71955,
	BOSS_XUEN							= 71953,
	BOSS_ORDOS							= 72057,
};

enum Rares
{
	RARE_ARCHIEREUS_OF_FLAME			= 73174,
	RARE_ARCHIEREUS_OF_FLAME_CLOAK		= 73666, // the above and this line are the SAME npcs, but with different ids. One is spawned at the very ground, close to the center of the Timeless Isle, the other one is spawned at the top place of the Timeless Isle, that you need the cloak to get there.
	RARE_BUFO							= 72775,
	RARE_CHAMPION_OF_THE_BLACK_FLAME	= 73171,
	RARE_CHELON							= 72045,
	RARE_CINDERFALL						= 73175,
	RARE_CRANEGNASHER					= 72049,
	RARE_DREAD_SHIP_VAZUVIUS			= 73281,
	RARE_EMERALD_GANDER					= 73158,
	RARE_EVERMAW						= 73279,
	RARE_FLINTLORD_GAIRAN				= 73172,
	RARE_GOLGANARR						= 72970,
	RARE_GREAT_TURTLE_FURYSHELL			= 73161,
	RARE_GUCHI_THE_SWARMBRINGER			= 72909,
	RARE_HUOLON							= 73167,
	RARE_IRONFUR_STEELHORN				= 73160,
	RARE_IMPERIAL_PYTHON				= 73163,
	RARE_JAKUR_OF_ORDON					= 73169,
	RARE_KARKANOS						= 72193,
	RARE_LEAFMENDER						= 73277,
	RARE_MONSTROUS_SPINECLAW			= 73166,
	RARE_RATTLESKEW						= 72048,
	RARE_ROCK_MOSS						= 73157,
	RARE_SPELURK						= 71864,
	RARE_SPIRIT_OF_JADEFIRE				= 72769,
	RARE_TSAVOKA						= 72808,
	RARE_URDUR_THE_CAUTERIZER			= 73173,
	RARE_WATCHER_OSU					= 73170,
	RARE_ZESQUA							= 72245,
	RARE_ZHU_GON_THE_SOUR				= 71919,
	RARE_STINKBRAID						= 73704,
};

enum Creatures
{
	NPC_EMPEROR_SHAOHAO_TI				= 73303,
};

enum SharedSpells
{
	// This means, that if 2 or more creatures use the same spell, it can be found here
	SPELL_DEFENSIVE_LEAP				= 147650,
	SPELL_POUNCE_LEAP					= 147649,
	SPELL_POUNCE_STUN					= 147651,

	SPELL_GEYSER						= 147572,
	SPELL_SHELL_SPIN					= 147571,
	SPELL_SNAPPING_BITE					= 147569,

	SPELL_IRON_FUR						= 147368,
	SPELL_OX_CHARGE						= 147386,
	SPELL_OX_CHARGE_CAST				= 147385, // trigger for above spell :P
};

// Scripts information

enum TimeLostShrine
{
	// Events
	EVENT_BACK_TO_USE					= 0,

	// Spells
	SPELL_FORTITUDE_OF_NIUZAO			= 147281,
	SPELL_WISDOM_OF_YULON				= 147282,
	SPELL_CHI_JIS_HOPE					= 147283,
	SPELL_XUENS_STRENGTH				= 147284,
	SPELL_ORDOS_BURNING_SACRIFICE		= 147285,
};

enum EmperorShaohao
{
	SAY_DEFEATED_CHI_JI					= 0,
};

enum Cinderfall
{
	SPELL_MOLTEN_INFERNO_1				= 147881,
	SPELL_MOLTEN_INFERNO_2				= 147878,
	SPELL_MOLTEN_INFERNO_3				= 147880,
	SPELL_MOLTEN_INFERNO_4				= 147879,
};

enum Huolon
{
	SPELL_LIGHTNING_BREATH				= 147826,
	SPELL_STORM_BLOSSOM					= 147828,
};

enum ImperialPython
{
	SPELL_HUGE_FANG						= 147290
};

enum EmeraldGander
{
	SPELL_GUST_OF_WIND					= 147310,
	SPELL_HEALING_SONG					= 147309,
	SPELL_WINDFEATHER					= 147306,
};

enum Golganarr
{
	// Says
	SAY_SPAWN							= 0,

	// Spells
	SPELL_STOMP							= 147543,
	SPELL_STOMP_FRENZY					= 147544,
	SPELL_BOULDER						= 147546,
	SPELL_BOULDER_FRENZY				= 147545,
	SPELL_FRENZY 						= 147510,
	SPELL_EXHAUSTION					= 147513,
};

enum WatcherOsu
{
	SPELL_FALLING_FLAMES				= 147723,
	SPELL_PYROBLAST						= 147720,
};

enum Tsavoka
{
	SPELL_GREATER_SWIPE					= 147653
};

enum SpiritOfJadefire
{
	SPELL_JADEFIRE_BOLT					= 147454,
	SPELL_JADEFLAME_STRIKE				= 147456,
};

enum MonstrousSpineclaw
{
	SPELL_CLAW_FLURRY					= 147560,
};

enum IronFurrSteelhorn
{
	SPELL_HEADBUTT						= 147384
};