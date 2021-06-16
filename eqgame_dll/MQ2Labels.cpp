// MQ2Labels.cpp : Defines the entry point for the DLL application.
//

// MQ2 Custom Labels


#include "MQ2Main.h"
#include <sstream>
#include <map>

typedef enum eStatEntry
{
	eStatClassless = 1,
	eStatCurHP,
	eStatCurMana,
	eStatCurEndur,
	eStatMaxHP,
	eStatMaxMana,
	eStatMaxEndur,
	eStatATK,
	eStatAC,
	eStatSTR,
	eStatSTA,
	eStatDEX,
	eStatAGI,
	eStatINT,
	eStatWIS,
	eStatCHA,
	eStatMR,
	eStatFR,
	eStatCR,
	eStatPR,
	eStatDR,
	eStatWalkspeed,
	eStatRunspeed,
	eStatWeight,
	eStatMaxWeight,
	eStatMeleePower,
	eStatSpellPower,
	eStatHealingPower,
	eStatMeleeHaste,
	eStatSpellHaste,
	eStatHealingHaste,
	eStatMeleeCrit,
	eStatSpellCrit,
	eStatHealingCrit,
	eStatTotalPower,
	eStatSynergyLevel,
	eStatMitigation,
	eStatAAPoints,
	eStatSynergyLevel1,
	eStatSynergyLevel2,
	eStatSynergyLevel3,
	eStatSynergyLevel4,
	eStatSynergyLevel5,
	eStatSynergyLevel6,
	eStatSynergyLevel7,
	eStatSynergyLevel8,
	eStatSynergyLevel9,
	eStatSynergyLevel10,
	eStatSynergyLevel11,
	eStatSynergyLevel12,
	eStatMax
};

typedef enum EQLabelTypes {
	Name = 1,
	Level = 2,
	Class = 3,
	Deity = 4,
	Strength = 5,
	Stamina = 6,
	Dexterity = 7,
	Agility = 8,
	Wisdom = 9,
	Intelligence = 10,
	Charisma = 11,
	SavevsPoison = 12,
	SavevsDisease = 13,
	SavevsFire = 14,
	SavevsCold = 15,
	SavevsMagic = 16,
	CurrentHitPoints = 17,
	MaximumHitPoints = 18,
	HitPointPercentage = 19,
	ManaPercentage = 20,
	StaminaEndurancePercentage = 21,
	CurrentMitigation = 22,
	CurrentOffense = 23,
	Weight = 24,
	MaximumWeight = 25,
	ExperiencePercentage = 26,
	AlternateExperiencePercentage = 27,
	TargetName = 28,
	TargetHitPointPercentage = 29,
	GroupMember1Name = 30,
	GroupMember2Name = 31,
	GroupMember3Name = 32,
	GroupMember4Name = 33,
	GroupMember5Name = 34,
	GroupMember1HealthPercentage = 35,
	GroupMember2HealthPercentage = 36,
	GroupMember3HealthPercentage = 37,
	GroupMember4HealthPercentage = 38,
	GroupMember5HealthPercentage = 39,
	GroupPet1HealthPercentage = 40,
	GroupPet2HealthPercentage = 41,
	GroupPet3HealthPercentage = 42,
	GroupPet4HealthPercentage = 43,
	GroupPet5HealthPercentage = 44,
	Buff0 = 45,
	Buff1 = 46,
	Buff2 = 47,
	Buff3 = 48,
	Buff4 = 49,
	Buff5 = 50,
	Buff6 = 51,
	Buff7 = 52,
	Buff8 = 53,
	Buff9 = 54,
	Buff10 = 55,
	Buff11 = 56,
	Buff12 = 57,
	Buff13 = 58,
	Buff14 = 59,
	Spell1 = 60,
	Spell2 = 61,
	Spell3 = 62,
	Spell4 = 63,
	Spell5 = 64,
	Spell6 = 65,
	Spell7 = 66,
	Spell8 = 67,
	PlayersPetName = 68,
	PlayersPetHPPercent = 69,
	PlayersCurrentHP = 70,
	CurrentAlternateAdvancementPointsAvailabletoSpend = 71,
	CurrentExperiencePercentageAssignedtoAlternateAdvancement = 72,
	CharacterLastName = 73,
	CharacterTitle = 74,
	CurrentMP3SongName = 75,
	CurrentMP3SongDurationMinutesValue = 76,
	CurrentMP3SongDurationSecondsValue = 77,
	CurrentMP3SongPositionMinutesValue = 78,
	CurrentMP3SongPositionSecondsValue = 79,
	Song1 = 80,
	Song2 = 81,
	Song3 = 82,
	Song4 = 83,
	Song5 = 84,
	Song6 = 85,
	PetBuff1 = 86,
	PetBuff2 = 87,
	PetBuff3 = 88,
	PetBuff4 = 89,
	PetBuff5 = 90,
	PetBuff6 = 91,
	PetBuff7 = 92,
	PetBuff8 = 93,
	PetBuff9 = 94,
	PetBuff10 = 95,
	PetBuff11 = 96,
	PetBuff12 = 97,
	PetBuff13 = 98,
	PetBuff14 = 99,
	PetBuff15 = 100,
	PetBuff16 = 101,
	PetBuff17 = 102,
	PetBuff18 = 103,
	PetBuff19 = 104,
	PetBuff20 = 105,
	PetBuff21 = 106,
	PetBuff22 = 107,
	PetBuff23 = 108,
	PetBuff24 = 109,
	PetBuff25 = 110,
	PetBuff26 = 111,
	PetBuff27 = 112,
	PetBuff28 = 113,
	PetBuff29 = 114,
	PetBuff30 = 115,
	PersonalTributeTimer = 116,
	CurrentAmountofTributePoints = 117,
	TotalCareerTribute = 118,
	TributeCostPer10Mins = 119,
	TargetofTargetPercentage = 120,
	GuildTributeTimer = 121,
	GuildTributePool = 122,
	GuildTributePayment = 123,
	ManaNumber = 124,
	ManaNumberMax = 125,
	EnduranceNumber = 126,
	EnduranceNumberMax = 127,
	ManaMaxMana = 128,
	EnduranceMaxEndurance = 129,
	None130 = 130,
	None131 = 131,
	TaskSystemDurationTimer = 132,
	Spell9 = 133,
	CastingSpellName = 134,
	TargetofTargetName = 135,
	CorruptionResist = 136,
	PlayerCombatTimerLabel = 137,
	Spell10 = 138,
	GroupMember1ManaPercentage = 139,
	GroupMember2ManaPercentage = 140,
	GroupMember3ManaPercentage = 141,
	GroupMember4ManaPercentage = 142,
	GroupMember5ManaPercentage = 143,
	GroupMember1EndurancePercentage = 144,
	GroupMember2EndurancePercentage = 145,
	GroupMember3EndurancePercentage = 146,
	GroupMember4EndurancePercentage = 147,
	GroupMember5EndurancePercentage = 148,
	Spell11 = 149,
	Spell12 = 150,
	HPPercentageExtendedTargetWindow0 = 151,
	HPPercentageExtendedTargetWindow1 = 152,
	HPPercentageExtendedTargetWindow2 = 153,
	HPPercentageExtendedTargetWindow3 = 154,
	HPPercentageExtendedTargetWindow4 = 155,
	HPPercentageExtendedTargetWindow5 = 156,
	HPPercentageExtendedTargetWindow6 = 157,
	HPPercentageExtendedTargetWindow7 = 158,
	HPPercentageExtendedTargetWindow8 = 159,
	HPPercentageExtendedTargetWindow9 = 160,
	HPPercentageExtendedTargetWindow10 = 161,
	HPPercentageExtendedTargetWindow11 = 162,
	HPPercentageExtendedTargetWindow12 = 163,
	HPPercentageExtendedTargetWindow13 = 164,
	HPPercentageExtendedTargetWindow14 = 165,
	HPPercentageExtendedTargetWindow15 = 166,
	HPPercentageExtendedTargetWindow16 = 167,
	HPPercentageExtendedTargetWindow17 = 168,
	HPPercentageExtendedTargetWindow18 = 169,
	HPPercentageExtendedTargetWindow19 = 170,
	ManaPercentageExtendedTargetWindow0 = 171,
	ManaPercentageExtendedTargetWindow1 = 172,
	ManaPercentageExtendedTargetWindow2 = 173,
	ManaPercentageExtendedTargetWindow3 = 174,
	ManaPercentageExtendedTargetWindow4 = 175,
	ManaPercentageExtendedTargetWindow5 = 176,
	ManaPercentageExtendedTargetWindow6 = 177,
	ManaPercentageExtendedTargetWindow7 = 178,
	ManaPercentageExtendedTargetWindow8 = 179,
	ManaPercentageExtendedTargetWindow9 = 180,
	ManaPercentageExtendedTargetWindow10 = 181,
	ManaPercentageExtendedTargetWindow11 = 182,
	ManaPercentageExtendedTargetWindow12 = 183,
	ManaPercentageExtendedTargetWindow13 = 184,
	ManaPercentageExtendedTargetWindow14 = 185,
	ManaPercentageExtendedTargetWindow15 = 186,
	ManaPercentageExtendedTargetWindow16 = 187,
	ManaPercentageExtendedTargetWindow17 = 188,
	ManaPercentageExtendedTargetWindow18 = 189,
	ManaPercentageExtendedTargetWindow19 = 190,
	EndurancePercentageExtendedTargetWindow0 = 191,
	EndurancePercentageExtendedTargetWindow1 = 192,
	EndurancePercentageExtendedTargetWindow2 = 193,
	EndurancePercentageExtendedTargetWindow3 = 194,
	EndurancePercentageExtendedTargetWindow4 = 195,
	EndurancePercentageExtendedTargetWindow5 = 196,
	EndurancePercentageExtendedTargetWindow6 = 197,
	EndurancePercentageExtendedTargetWindow7 = 198,
	EndurancePercentageExtendedTargetWindow8 = 199,
	EndurancePercentageExtendedTargetWindow9 = 200,
	EndurancePercentageExtendedTargetWindow10 = 201,
	EndurancePercentageExtendedTargetWindow11 = 202,
	EndurancePercentageExtendedTargetWindow12 = 203,
	EndurancePercentageExtendedTargetWindow13 = 204,
	EndurancePercentageExtendedTargetWindow14 = 205,
	EndurancePercentageExtendedTargetWindow15 = 206,
	EndurancePercentageExtendedTargetWindow16 = 207,
	EndurancePercentageExtendedTargetWindow17 = 208,
	EndurancePercentageExtendedTargetWindow18 = 209,
	EndurancePercentageExtendedTargetWindow19 = 210,
	Haste = 211,
	HitPointRegeneration = 212,
	ManaRegeneration = 213,
	EnduranceRegeneration = 214,
	SpellShield = 215,
	CombatEffects = 216,
	Shielding = 217,
	DamageShielding = 218,
	DamageOverTimeShielding = 219,
	DamageShieldMitigation = 220,
	Avoidance = 221,
	Accuracy = 222,
	StunResist = 223,
	StrikeThrough = 224,
	HealAmount = 225,
	SpellDamage = 226,
	Clairvoyance = 227,
	SkillDamageBash = 228,
	SkillDamageBackstab = 229,
	SkillDamageDragonpunch = 230,
	SkillDamageEaglestrike = 231,
	SkillDamageFlyingkick = 232,
	SkillDamageKick = 233,
	SkillDamageRoundkick = 234,
	SkillDamageTigerclaw = 235,
	SkillDamageFrenzy = 236,
	WeightMaxWeight = 237,
	BaseStrength = 238,
	BaseStamina = 239,
	BaseDexterity = 240,
	BaseAgility = 241,
	BaseWisdom = 242,
	BaseIntelligence = 243,
	BaseCharisma = 244,
	BaseSavevsPoison = 245,
	BaseSavevsDisease = 246,
	BaseSavevsFire = 247,
	BaseSavevsCold = 248,
	BaseSavevsMagic = 249,
	BaseSavevsCorruption = 250,
	HeroicStrength = 251,
	HeroicStamina = 252,
	HeroicDexterity = 253,
	HeroicAgility = 254,
	HeroicWisdom = 255,
	HeroicIntelligence = 256,
	HeroicCharisma = 257,
	HeroicSavevsPoison = 258,
	HeroicSavevsDisease = 259,
	HeroicSavevsFire = 260,
	HeroicSavevsCold = 261,
	HeroicSavevsMagic = 262,
	HeroicSavevsCorruption = 263,
	CapStrength = 264,
	CapStamina = 265,
	CapDexterity = 266,
	CapAgility = 267,
	CapWisdom = 268,
	CapIntelligence = 269,
	CapCharisma = 270,
	CapSavevsPoison = 271,
	CapSavevsDisease = 272,
	CapSavevsFire = 273,
	CapSavevsCold = 274,
	CapSavevsMagic = 275,
	CapSavevsCorruption = 276,
	CapSpellShield = 277,
	CapCombatEffects = 278,
	CapShielding = 279,
	CapDamageShielding = 280,
	CapDamageOverTimeShielding = 281,
	CapDamageShieldMitigation = 282,
	CapAvoidance = 283,
	CapAccuracy = 284,
	CapStunResist = 285,
	CapStrikeThrough = 286,
	CapSkillDamageBash = 287,
	CapSkillDamageBackstab = 288,
	CapSkillDamageDragonpunch = 289,
	CapSkillDamageEaglestrike = 290,
	CapSkillDamageFlyingkick = 291,
	CapSkillDamageKick = 292,
	CapSkillDamageRoundkick = 293,
	CapSkillDamageTigerclaw = 294,
	CapSkillDamageFrenzy = 295,
	LoyaltyTokenCount = 296,
	TributeTrophyTimer = 297,
	TributeTrophyCost = 298,
	GuildTributeTrophyTimer = 299,
	GuildTributeTrophyCost = 300,
	TargetofPetHP = 301,
	AggroTargetName = 302,
	AggroMostHatedName = 303,
	AggroMostHatedNameNoLock = 304,
	AggroMyHatePercent = 305,
	AggroMyHatePercentNoLock = 306,
	AggroMostHatedHatePercent = 307,
	AggroMostHatedHatePercentNoLock = 308,
	AggroGroup1HatePercent = 309,
	AggroGroup2HatePercent = 310,
	AggroGroup3HatePercent = 311,
	AggroGroup4HatePercent = 312,
	AggroGroup5HatePercent = 313,
	AggroExtendedTarget1HatePercent = 314,
	AggroExtendedTarget2HatePercent = 315,
	AggroExtendedTarget3HatePercent = 316,
	AggroExtendedTarget4HatePercent = 317,
	AggroExtendedTarget5HatePercent = 318,
	AggroExtendedTarget6HatePercent = 319,
	AggroExtendedTarget7HatePercent = 320,
	AggroExtendedTarget8HatePercent = 321,
	AggroExtendedTarget9HatePercent = 322,
	AggroExtendedTarget10HatePercent = 323,
	AggroExtendedTarget11HatePercent = 324,
	AggroExtendedTarget12HatePercent = 325,
	AggroExtendedTarget13HatePercent = 326,
	AggroExtendedTarget14HatePercent = 327,
	AggroExtendedTarget15HatePercent = 328,
	AggroExtendedTarget16HatePercent = 329,
	AggroExtendedTarget17HatePercent = 330,
	AggroExtendedTarget18HatePercent = 331,
	AggroExtendedTarget19HatePercent = 332,
	AggroExtendedTarget20HatePercent = 333,
	NA334 = 334,
	MercenaryAAExperiencePercentLabel = 335,
	MercenaryAAExperiencePointsLabel = 336,
	MercenaryAAExperiencePointsSpentLabel = 337,
	MercenaryHP = 338,
	MercenaryMaxHP = 339,
	MercenaryMana = 340,
	MercenaryMaxMana = 341,
	MercenaryEndurance = 342,
	MercenaryMaxEndurance = 343,
	MercenaryArmorClass = 344,
	MercenaryAttack = 345,
	MercenaryHastePercent = 346,
	MercenaryStrength = 347,
	MercenaryStamina = 348,
	MercenaryIntelligence = 349,
	MercenaryWisdom = 350,
	MercenaryAgility = 351,
	MercenaryDexterity = 352,
	MercenaryCharisma = 353,
	MercenaryCombatHPRegeneration = 354,
	MercenaryCombatManaRegeneration = 355,
	MercenaryCombatEnduranceRegeneration = 356,
	MercenaryHealAmount = 357,
	MercenarySpellDamage = 358,
	NA359 = 359,
	PowerSourcePercentageRemaining = 360,
	NA361 = 361,
	Velocity = 401,
	AccuracyAgain = 402,
	Evasion = 403,
	NA404 = 404,
	Spell13 = 414,
	Spell14 = 415,
	NA416 = 416,
	ExtraBuff0 = 500,
	ExtraBuff1 = 501,
	ExtraBuff2 = 502,
	ExtraBuff3 = 503,
	ExtraBuff4 = 504,
	ExtraBuff5 = 505,
	ExtraBuff6 = 506,
	ExtraBuff7 = 507,
	ExtraBuff8 = 508,
	ExtraBuff9 = 509,
	ExtraBuff10 = 510,
	ExtraBuff11 = 511,
	ExtraBuff12 = 512,
	ExtraBuff13 = 513,
	ExtraBuff14 = 514,
	ExtraBuff15 = 515,
	ExtraBuff16 = 516,
	ExtraBuff17 = 517,
	ExtraBuff18 = 518,
	ExtraBuff19 = 519,
	ExtraBuff20 = 520,
	ExtraBuff21 = 521,
	ExtraBuff22 = 522,
	ExtraBuff23 = 523,
	ExtraBuff24 = 524,
	ExtraBuff25 = 525,
	ExtraBuff26 = 526,
	ExtraBuff27 = 527,
	ExtraBuff28 = 528,
	ExtraBuff29 = 529,
	ExtraBuff30 = 530,
	ExtraBuff31 = 531,
	ExtraBuff32 = 532,
	ExtraBuff33 = 533,
	ExtraBuff34 = 534,
ExtraBuff35 = 535,
ExtraBuff36 = 536,
ExtraBuff37 = 537,
ExtraBuff38 = 538,
ExtraBuff39 = 539,
ExtraBuff40 = 540,
ExtraBuff41 = 541,
NA549 = 549,
BlockedBuff0 = 550,
BlockedBuff1 = 551,
BlockedBuff2 = 552,
BlockedBuff3 = 553,
BlockedBuff4 = 554,
BlockedBuff5 = 555,
BlockedBuff6 = 556,
BlockedBuff7 = 557,
BlockedBuff8 = 558,
BlockedBuff9 = 559,
BlockedBuff10 = 560,
BlockedBuff11 = 561,
BlockedBuff12 = 562,
BlockedBuff13 = 563,
BlockedBuff14 = 564,
BlockedBuff15 = 565,
BlockedBuff16 = 566,
BlockedBuff17 = 567,
BlockedBuff18 = 568,
BlockedBuff19 = 569,
BlockedBuff20 = 570,
BlockedBuff21 = 571,
BlockedBuff22 = 572,
BlockedBuff23 = 573,
BlockedBuff24 = 574,
BlockedBuff25 = 575,
BlockedBuff26 = 576,
BlockedBuff27 = 577,
BlockedBuff28 = 578,
BlockedBuff29 = 579,
NA580 = 580,
SongBuff0 = 600,
SongBuff1 = 601,
SongBuff2 = 602,
SongBuff3 = 603,
SongBuff4 = 604,
SongBuff5 = 605,
SongBuff6 = 606,
SongBuff7 = 607,
SongBuff8 = 608,
SongBuff9 = 609,
SongBuff10 = 610,
SongBuff11 = 611,
SongBuff12 = 612,
SongBuff13 = 613,
SongBuff14 = 614,
SongBuff15 = 615,
SongBuff16 = 616,
SongBuff17 = 617,
SongBuff18 = 618,
SongBuff19 = 619,
SongBuff20 = 620,
SongBuff21 = 621,
SongBuff22 = 622,
SongBuff23 = 623,
SongBuff24 = 624,
SongBuff25 = 625,
SongBuff26 = 626,
SongBuff27 = 627,
SongBuff28 = 628,
SongBuff29 = 629,
NA630 = 630,
PetBlockedBuff0 = 650,
PetBlockedBuff1 = 651,
PetBlockedBuff2 = 652,
PetBlockedBuff3 = 653,
PetBlockedBuff4 = 654,
PetBlockedBuff5 = 655,
PetBlockedBuff6 = 656,
PetBlockedBuff7 = 657,
PetBlockedBuff8 = 658,
PetBlockedBuff9 = 659,
PetBlockedBuff10 = 660,
PetBlockedBuff11 = 661,
PetBlockedBuff12 = 662,
PetBlockedBuff13 = 663,
PetBlockedBuff14 = 664,
PetBlockedBuff15 = 665,
PetBlockedBuff16 = 666,
PetBlockedBuff17 = 667,
PetBlockedBuff18 = 668,
PetBlockedBuff19 = 669,
PetBlockedBuff20 = 670,
PetBlockedBuff21 = 671,
PetBlockedBuff22 = 672,
PetBlockedBuff23 = 673,
PetBlockedBuff24 = 674,
PetBlockedBuff25 = 675,
PetBlockedBuff26 = 676,
PetBlockedBuff27 = 677,
PetBlockedBuff28 = 678,
PetBlockedBuff29 = 679,
MeleePower = 1002,
SpellPower = 1003,
HealingPower = 1004,
TotalPower = 1005,
SynergyLevel = 1006,
SpellHaste = 1009,
MeleeHaste = 1010,
HealingHaste = 1011,
SpellCrit = 1012,
MeleeCrit = 1013,
HealingCrit = 1014,
Walkspeed = 1015,
Runspeed = 1016,
Classless = 1017,
Mitigation = 1018,
AAPoints = 1019,
SynergyLevel1 = 1020,
SynergyLevel2 = 1021,
SynergyLevel3 = 1022,
SynergyLevel4 = 1023,
SynergyLevel5 = 1024,
SynergyLevel6 = 1025,
SynergyLevel7 = 1026,
SynergyLevel8 = 1027,
SynergyLevel9 = 1028,
SynergyLevel10 = 1029,
SynergyLevel11 = 1030,
SynergyLevel12 = 1031,
EQLabelTypesMax,
};

typedef string(*pEqTypesFunc)(EQLabelTypes LabelID);

std::map<EQLabelTypes, pEqTypesFunc> eqTypesMap = std::map<EQLabelTypes, pEqTypesFunc>();

std::map<EQLabelTypes, eStatEntry> statLabelMappings = std::map<EQLabelTypes, eStatEntry>();

std::map<eStatEntry, int64_t> statEntries;

std::string GetSpeedFloatRepresentationOfStat(eStatEntry statType)
{
	auto statItr = statEntries.find(statType);

	if (statItr != statEntries.end())
	{
		std::stringstream strStream(stringstream::in || stringstream::out);
		strStream.precision(3);
		strStream << (float)((statItr)->second / 100000.f);
		return strStream.str();
	}

	return string(" ");
}

std::string GetStringWeightFloatRepresentationOfStat(eStatEntry statType)
{
	auto statItr = statEntries.find(statType);

	if (statEntries.find(statType) != statEntries.end())
	{
		double num_val = (statItr)->second / 10.0;

		std::stringstream strStream(stringstream::in | stringstream::out);
		strStream << num_val;
		return strStream.str();
	}

	return string(" ");
}

std::string GetStringRepresentationOfStat(eStatEntry statType)
{
	auto statItr = statEntries.find(statType);

	if (statEntries.find(statType) != statEntries.end())
	{
		std::stringstream strStream(stringstream::in | stringstream::out);
		strStream << (statItr)->second;
		return strStream.str();
	}

	return string(" ");
}

std::string GetStringRepresentationOfClass()
{
	auto statItr = statEntries.find(eStatClassless);

	if (statEntries.find(eStatClassless) != statEntries.end())
	{
		if (statItr->second == 17)
			return string("Classless");

		if (statItr->second >= 1 && statItr->second <= 16)
			return string((char*)GetClassDesc(pLocalPlayer->Data.pSpawn->Class));
	}

	if (pLocalPlayer && pLocalPlayer->Data.pSpawn)
	{
		return string((char*)GetClassDesc(pLocalPlayer->Data.pSpawn->Class));
	}
	return "None";
}

std::string EQLabelFunction(EQLabelTypes LabelID)
{
	if (LabelID >= EQLabelTypesMax)
		return string(" ");

	auto iter = statLabelMappings.find(EQLabelTypes(LabelID));
	if (iter == statLabelMappings.end())
		return string(" ");

	return GetStringRepresentationOfStat(iter->second);
}

std::string EQSynergyLabelFunction(EQLabelTypes LabelID)
{
	if (LabelID >= EQLabelTypesMax)
		return string(" ");

	auto iter = statLabelMappings.find(EQLabelTypes(LabelID));
	if (iter == statLabelMappings.end())
		return string(" ");

	auto statItr = statEntries.find(eStatClassless);
	if (statItr == statEntries.end())
	{
		return string(" ");
	}

	if (statItr->second != 17)
	{
		return string(" ");
	}


	return GetStringRepresentationOfStat(iter->second);
}

std::string EQClasslessFunction(EQLabelTypes LabelID)
{
	if (LabelID >= EQLabelTypesMax)
		return string(" ");

	auto iter = statLabelMappings.find(EQLabelTypes(LabelID));
	if (iter == statLabelMappings.end())
		return string(" ");

	return GetStringRepresentationOfClass();
}

std::string EQDualManaLabelFunction(EQLabelTypes LabelID)
{
	if (LabelID >= EQLabelTypesMax)
		return string(" ");

	return GetStringRepresentationOfStat(eStatCurMana) + " / " + GetStringRepresentationOfStat(eStatMaxMana);
}

std::string EQSpeedLabelFunction(EQLabelTypes LabelID)
{
	if (LabelID >= EQLabelTypesMax)
		return string(" ");

	auto iter = statLabelMappings.find(EQLabelTypes(LabelID));
	if (iter == statLabelMappings.end())
		return string(" ");

	return GetSpeedFloatRepresentationOfStat(iter->second);
}

std::string EQDualHPLabelFunction(EQLabelTypes LabelID)
{
	if (LabelID >= EQLabelTypesMax)
		return string(" ");

	return GetStringRepresentationOfStat(eStatCurHP) + " / " + GetStringRepresentationOfStat(eStatMaxHP);
}

std::string EQHPPercentageLabelFunction(EQLabelTypes LabelID)
{
	if (LabelID >= EQLabelTypesMax)
		return "100";

	auto statItrCur = statEntries.find(eStatCurHP);

	auto statItrMax = statEntries.find(eStatMaxHP);

	if (statItrCur == statEntries.end() || statItrMax == statEntries.end())
	{
		return "100";
	}

	auto statCur = statItrCur->second;
	auto statMax = statItrMax->second;

	auto outVal = (int)((double)statCur / (double)statMax * 100.0);
	std::stringstream strStream(stringstream::in | stringstream::out);
	strStream << outVal;
	return strStream.str();
}

std::string EQManaPercentageLabelFunction(EQLabelTypes LabelID)
{
	if (LabelID >= EQLabelTypesMax)
		return "100";

	auto statItrCur = statEntries.find(eStatCurMana);

	auto statItrMax = statEntries.find(eStatMaxMana);

	if (statItrCur == statEntries.end() || statItrMax == statEntries.end())
	{
		return "100";
	}

	auto statCur = statItrCur->second;
	auto statMax = statItrMax->second;

	auto outVal = (int)((double)statCur / (double)statMax * 100.0);
	std::stringstream strStream(stringstream::in | stringstream::out);
	strStream << outVal;
	return strStream.str();
}

std::string EQEndurPercentageLabelFunction(EQLabelTypes LabelID)
{
	if (LabelID >= EQLabelTypesMax)
		return "100";

	auto statItrCur = statEntries.find(eStatCurEndur);

	auto statItrMax = statEntries.find(eStatMaxEndur);

	if (statItrCur == statEntries.end() || statItrMax == statEntries.end())
	{
		return "100";
	}

	auto statCur = statItrCur->second;
	auto statMax = statItrMax->second;

	auto outVal = (int)((double)statCur / (double)statMax * 100.0);
	std::stringstream strStream(stringstream::in | stringstream::out);
	strStream << outVal;
	return strStream.str();
}


std::string EQGaugeLabelFunction(eStatEntry curStat, eStatEntry maxStat, int* outVal)
{

	auto statItrCur = statEntries.find(curStat);

	auto statItrMax = statEntries.find(maxStat);

	if (statItrCur == statEntries.end() || statItrMax == statEntries.end())
	{
		return " ";
	}

	auto statCur = statItrCur->second;
	auto statMax = statItrMax->second;

	*outVal = (int)((double)statCur / (double)statMax * 1000.0);

	std::stringstream strStream(stringstream::in | stringstream::out);
	strStream << *outVal;
	return strStream.str();
}

std::string EQDualEndurLabelFunction(EQLabelTypes LabelID)
{
	if (LabelID >= EQLabelTypesMax)
		return string(" ");

	return GetStringRepresentationOfStat(eStatCurEndur) + " / " + GetStringRepresentationOfStat(eStatMaxEndur);
}

std::string EQCurWeightLabelFunction(EQLabelTypes LabelID)
{
	if (LabelID >= EQLabelTypesMax)
		return string(" ");

	return GetStringWeightFloatRepresentationOfStat(eStatWeight);
}

std::string EQMaxWeightLabelFunction(EQLabelTypes LabelID)
{
	if (LabelID >= EQLabelTypesMax)
		return string(" ");

	return GetStringWeightFloatRepresentationOfStat(eStatMaxWeight);
}

std::string EQWeightLabelFunction(EQLabelTypes LabelID)
{
	if (LabelID >= EQLabelTypesMax)
		return string(" ");

	return GetStringWeightFloatRepresentationOfStat(eStatWeight) + " / " + GetStringWeightFloatRepresentationOfStat(eStatMaxWeight);
}

typedef struct EdgeStatEntry_Struct {
	uint32_t statKey;
	uint64_t statValue;
};

typedef struct EdgeStat_Struct
{
	uint32_t count;
	EdgeStatEntry_Struct entries[0];
};

PLUGIN_API BOOL OnLabelReceivePPPacket()
{
	statEntries.clear();
	return true;
}

PLUGIN_API BOOL OnRecvEdgeStatLabelPacket(DWORD Type, PVOID Packet, DWORD Size) 
{
	if ((Size <= 4) || !Packet)
	{
		return true;
	}

	EdgeStat_Struct* incValues = (EdgeStat_Struct*)Packet;
	if (incValues->count * sizeof(EdgeStatEntry_Struct) != (Size - 4))
		return true;

	for (auto i = 0; i < incValues->count; i++)
	{
		if (incValues->entries[i].statKey == 0 || incValues->entries[i].statKey >= eStatMax)
			continue;
		eStatEntry Val = (eStatEntry)incValues->entries[i].statKey;
		statEntries[Val] = incValues->entries[i].statValue;
	}

	return true;
}

// CSidlManager::CreateLabel 0x5F2470

// the tool tip is already copied out of the 
// in class CControlTemplate.  use this struct
// to mock up the class, so we don't have to
// worry about class instatiation and crap

struct _CControl {
    /*0x000*/    DWORD Fluff[0x24]; // if this changes update ISXEQLabels.cpp too
    /*0x090*/    CXSTR * EQType;
};

struct _PhysicsInfo {
	/*0x0000*/    float Unknown;
	/*0x0004*/    float Unknown2;
	/*0x0008*/    float Unknown3;
	/*0x00012*/   float Velocity;
	/*0x00016*/   float Velocity2;
};

// optimize off because the tramp looks blank to the compiler
// and it doesn't respect the fact the it will be a real routine
#pragma optimize ("g", off)

class CSidlManagerHook {
public:
    class CXWnd * CreateLabel_Trampoline(class CXWnd *, struct _CControl *);
    class CXWnd * CreateLabel_Detour(class CXWnd *CWin, struct _CControl *CControl)
    {
        CLABELWND *p;
        class CXWnd *tmp = CreateLabel_Trampoline(CWin, CControl);
        p = (CLABELWND *)tmp;
        if (CControl->EQType) {
            *((DWORD *)&p->SidlPiece) = atoi(CControl->EQType->Text);
        } else {
            *((DWORD *)&p->SidlPiece) = 0;
        }

        return tmp;
    }
};

DETOUR_TRAMPOLINE_EMPTY(class CXWnd * CSidlManagerHook::CreateLabel_Trampoline(class CXWnd *, struct _CControl *));

int __cdecl GetGaugeValueFromEQ_Trampoline(int, class CXStr *, bool *, unsigned long *);
int __cdecl GetGaugeValueFromEQ_Detour(int EQType, class CXStr *out, bool *arg3, unsigned long *colorout)
{
	int ret = GetGaugeValueFromEQ_Trampoline(EQType, out, arg3, colorout);
	if (out && out->Ptr) {
		if (out && out->Ptr) {
			bool Found = FALSE;
			std::string eqtypesString = "";
			if (1 == EQType) {
 				std::string pTargetRatio = EQGaugeLabelFunction(eStatCurHP, eStatMaxHP, &ret);
			}
			else if (2 == EQType) {
				std::string pTargetName = EQGaugeLabelFunction(eStatCurMana, eStatMaxMana, &ret);
			}
			else if (3 == EQType) {
				std::string pTargetName = EQGaugeLabelFunction(eStatCurEndur, eStatMaxEndur, &ret);
			}
			else if (6 == EQType && pTarget != nullptr && pTarget == pLocalPlayer) {
				std::string pTargetName = EQGaugeLabelFunction(eStatCurHP, eStatMaxHP, &ret);
				SetCXStr(&out->Ptr, pTarget->Data.DisplayedName);
			}

		}
	}
	return ret;
}

int __cdecl GetLabelFromEQ_Trampoline(int, class CXStr *, bool *, unsigned long *);
int __cdecl GetLabelFromEQ_Detour(int EQType, class CXStr *out, bool *arg3, unsigned long *colorout)
{
	int ret = GetLabelFromEQ_Trampoline(EQType, out, arg3, colorout);
	if (out && out->Ptr) {
		bool Found = FALSE;
		std::string eqtypesString = "";

		if (EQType == 29)
		{
			if (pTarget && pLocalPlayer && pTarget == pLocalPlayer)
			{
				eqtypesString = EQHPPercentageLabelFunction((EQLabelTypes)EQType);
				SetCXStr(&out->Ptr, (PCHAR)eqtypesString.c_str());
			}
			return ret;
		}
		for (auto eqtype : eqTypesMap) {
			if (eqtype.first == EQType) {

				auto func = eqtype.second;
				if (func)
				{
					eqtypesString = (*func)(eqtype.first);
					Found = TRUE;
					break;
				}
			}
		}
		if (Found)
		{
			SetCXStr(&out->Ptr, (PCHAR)eqtypesString.c_str());
		}
	}
	return ret;
}


// CLabelHook::Draw_Detour

class CLabelHook {
public:
    VOID Draw_Trampoline(VOID);
    VOID Draw_Detour(VOID)
    {
        PCLABELWND pThisLabel;
        __asm {mov [pThisLabel], ecx};
        //          (PCLABELWND)this;
        Draw_Trampoline();
        CHAR Buffer[MAX_STRING] = {0};
        BOOL Found=FALSE;
        DWORD index;

		std::string eqtypesString = "";

		if ((DWORD)pThisLabel->SidlPiece>=0) {
            for (auto eqtype : eqTypesMap) {
                if (eqtype.first==pThisLabel->SidlPiece) {

					auto func = eqtype.second;
					if (func)
					{
						eqtypesString = (*func)(eqtype.first);
						Found = TRUE;
						break;
					}
                }
            }
        }
        if (Found) SetCXStr(&(pThisLabel->Wnd.WindowText),(PCHAR)eqtypesString.c_str());
    }
}; 

class EQCharacter1Hook {
public:
	int32_t MaxHP_Trampoline(int, int);
	int32_t MaxHP_Detour(int a1, int a2)
	{
		if (statEntries.find(eStatMaxHP) != statEntries.end())
		{
			//For display purposes we really, really should not care what the value is. Only that it's the 'right' value for unconscious purposes.
			return statEntries[eStatMaxHP] >= (INT_MAX - 1) ? INT_MAX - 1 : (int32_t) statEntries[eStatMaxHP];
		}
		return 100;
	}

	int32_t MaxMana_Trampoline(int);
	int32_t MaxMana_Detour(int a1)
	{
		if (statEntries.find(eStatMaxMana) != statEntries.end())
		{
			//For display purposes we really, really should not care what the value is. Only that it's the 'right' value for unconscious purposes.
			return statEntries[eStatMaxMana] >= (INT_MAX - 1) ? INT_MAX - 1 : (int32_t)statEntries[eStatMaxMana];
		}
		return 100;
	}

	int32_t MaxEndurance_Trampoline(int);
	int32_t MaxEndurance_Detour(int a1)
	{
		if (statEntries.find(eStatMaxEndur) != statEntries.end())
		{
			//For display purposes we really, really should not care what the value is. Only that it's the 'right' value for unconscious purposes.
			return statEntries[eStatMaxEndur] >= (INT_MAX - 1) ? INT_MAX - 1 : (int32_t)statEntries[eStatMaxEndur];
		}
		return 100;
	}


	int32_t CurHP_Trampoline(int, unsigned char);
	int32_t CurHP_Detour(int a1, unsigned char a2)
	{
		if (statEntries.find(eStatCurHP) != statEntries.end())
		{
			//For display purposes we really, really should not care what the value is. Only that it's the 'right' value for unconscious purposes.
			return statEntries[eStatCurHP] >= (INT_MAX - 1) ? INT_MAX - 1 : (int32_t)statEntries[eStatCurHP];
		}
		return 100;
	}

	int32_t CurMana_Trampoline(int);
	int32_t CurMana_Detour(int a1)
	{
		if (statEntries.find(eStatCurMana) != statEntries.end())
		{
			//For display purposes we really, really should not care what the value is. Only that it's the 'right' value for unconscious purposes.
			return statEntries[eStatCurMana] >= (INT_MAX - 1) ? INT_MAX - 1 : (int32_t)statEntries[eStatCurMana];
		}
		return 100;
	}

	int32_t CurEndurance_Trampoline(int);
	int32_t CurEndurance_Detour(int a1)
	{
		if (statEntries.find(eStatCurEndur) != statEntries.end())
		{
			//For display purposes we really, really should not care what the value is. Only that it's the 'right' value for unconscious purposes.
			return statEntries[eStatCurEndur] >= (INT_MAX - 1) ? INT_MAX - 1 : (int32_t)statEntries[eStatCurEndur];
		}
		return 100;
	}


	int GetUsableClass_Trampoline(int a1, DWORD a2);
	int GetUsableClass_Detour(int a1, DWORD a2)
	{
		auto statItr = statEntries.find(eStatClassless);
		if (statItr != statEntries.end())
		{
			if (statItr->second == 17)
				return -1;
		}

		return GetUsableClass_Trampoline(a1, a2);
	}

	int IsSpellcaster_Trampoline();
	int IsSpellcaster_Detour()
	{
		return 1;
	}

	int IsSpellcaster2_Trampoline(int, int, int, int);
	int IsSpellcaster2_Detour(int a1, int a2, int a3, int a4)
	{
		return 1;
	}

	int IsSpellcaster3_Trampoline();
	int IsSpellcaster3_Detour()
	{
		return 1;
	}

	VOID ClampVelocity_Trampoline(int);
	VOID ClampVelocity_Detour(int a1)
	{
		ClampVelocity_Trampoline(a1);

		//if (pLocalPlayer && pLocalPlayer->Data.pSpawn)
		//{
		//	if (statEntries.find(eStatWalkspeed) != statEntries.end() && statEntries.find(eStatRunspeed) != statEntries.end())

		//		if (pLocalPlayer->Data.pSpawn->WalkSpeed)
		//		{
		//			pLocalPlayer->Data.pSpawn->WalkSpeed = (DWORD)((float)(statEntries[eStatWalkspeed] / 100000));
		//			pLocalPlayer->Data.RunSpeed = (DWORD)((float)(statEntries[eStatRunspeed] / 100000));
		//			pLocalPlayer->Data.SpeedRun = (DWORD)((float)(statEntries[eStatRunspeed] / 100000));
		//		}
		//}
	}

	int GetSpellLevelNeeded_Trampoline(int spellid);
	int GetSpellLevelNeeded_Detour(int spellid)
	{
		auto statItr = statEntries.find(eStatClassless);
		if (statItr != statEntries.end())
		{
			if (statItr->second == 17)
				return 1;
		}

		return GetSpellLevelNeeded_Trampoline(spellid);
	}

	int CanStartMem_Trampoline(int spellid);
	int CanStartMem_Detour(int spellid)
	{
		return 1;
	}

	double CalculateWeight_Trampoline();
	double CalculateWeight_Detour()
	{
		double value = 1.0;

		if (pLocalPlayer->Data.pSpawn->SpeedRun)
		{

			if (statEntries.find(eStatRunspeed) != statEntries.end() && *EQADDR_RUNWALKSTATE == 1)
			{
				int64_t val = (int64_t)statEntries[eStatRunspeed];

				if (val == 0)
					return 0.0f;

				return ((double)val / 100000.0);
			}

			if (statEntries.find(eStatWalkspeed) != statEntries.end())
			{
				float val = (int32_t)statEntries[eStatWalkspeed];

				if (val == 0)
					return 0;
				return ((double)val / 100000.0);
			}
		}
		return value;
	}

};

DETOUR_TRAMPOLINE_EMPTY(VOID CLabelHook::Draw_Trampoline(VOID));
DETOUR_TRAMPOLINE_EMPTY(int32_t EQCharacter1Hook::CurHP_Trampoline(int, unsigned char));
DETOUR_TRAMPOLINE_EMPTY(int32_t EQCharacter1Hook::CurMana_Trampoline(int));
DETOUR_TRAMPOLINE_EMPTY(int32_t EQCharacter1Hook::CurEndurance_Trampoline(int));
DETOUR_TRAMPOLINE_EMPTY(int32_t EQCharacter1Hook::MaxHP_Trampoline(int, int));
DETOUR_TRAMPOLINE_EMPTY(int32_t EQCharacter1Hook::MaxMana_Trampoline(int));
DETOUR_TRAMPOLINE_EMPTY(int32_t EQCharacter1Hook::MaxEndurance_Trampoline(int));
DETOUR_TRAMPOLINE_EMPTY(void EQCharacter1Hook::ClampVelocity_Trampoline(int));
DETOUR_TRAMPOLINE_EMPTY(int EQCharacter1Hook::GetSpellLevelNeeded_Trampoline(int));
DETOUR_TRAMPOLINE_EMPTY(int EQCharacter1Hook::CanStartMem_Trampoline(int));
DETOUR_TRAMPOLINE_EMPTY(double EQCharacter1Hook::CalculateWeight_Trampoline());
DETOUR_TRAMPOLINE_EMPTY(int __cdecl GetGaugeValueFromEQ_Trampoline(int, class CXStr *, bool *, unsigned long *));
DETOUR_TRAMPOLINE_EMPTY(int __cdecl GetLabelFromEQ_Trampoline(int, class CXStr *, bool *, unsigned long *));
DETOUR_TRAMPOLINE_EMPTY(int EQCharacter1Hook::GetUsableClass_Trampoline(int, DWORD));
DETOUR_TRAMPOLINE_EMPTY(int EQCharacter1Hook::IsSpellcaster_Trampoline());
DETOUR_TRAMPOLINE_EMPTY(int EQCharacter1Hook::IsSpellcaster2_Trampoline(int, int, int, int));
DETOUR_TRAMPOLINE_EMPTY(int EQCharacter1Hook::IsSpellcaster3_Trampoline());
BOOL StealNextGauge=FALSE;
DWORD NextGauge=0;

// Called once, when the plugin is to initialize
PLUGIN_API VOID InitializeMQ2Labels(VOID)
{
 //   DebugSpewAlways("Initializing MQ2Labels");
	eqTypesMap[EQLabelTypes::CurrentHitPoints] = EQLabelFunction;
	eqTypesMap[EQLabelTypes::ManaNumber] = EQLabelFunction;
	eqTypesMap[EQLabelTypes::EnduranceNumber] = EQLabelFunction;
	eqTypesMap[EQLabelTypes::MaximumHitPoints] = EQLabelFunction;
	eqTypesMap[EQLabelTypes::ManaNumberMax] = EQLabelFunction;
	eqTypesMap[EQLabelTypes::EnduranceNumberMax] = EQLabelFunction;
	eqTypesMap[EQLabelTypes::PlayersCurrentHP] = EQDualHPLabelFunction;
	eqTypesMap[EQLabelTypes::ManaMaxMana] = EQDualManaLabelFunction;
	eqTypesMap[EQLabelTypes::EnduranceMaxEndurance] = EQDualEndurLabelFunction;
	eqTypesMap[EQLabelTypes::Strength] = EQLabelFunction;
	eqTypesMap[EQLabelTypes::Stamina] = EQLabelFunction;
	eqTypesMap[EQLabelTypes::Dexterity] = EQLabelFunction;
	eqTypesMap[EQLabelTypes::Agility] = EQLabelFunction;
	eqTypesMap[EQLabelTypes::Wisdom] = EQLabelFunction;
	eqTypesMap[EQLabelTypes::Intelligence] = EQLabelFunction;
	eqTypesMap[EQLabelTypes::Charisma] = EQLabelFunction;
	eqTypesMap[EQLabelTypes::SpellHaste] = EQLabelFunction;
	eqTypesMap[EQLabelTypes::HitPointPercentage] = EQHPPercentageLabelFunction;
	eqTypesMap[EQLabelTypes::ManaPercentage] = EQManaPercentageLabelFunction;
	eqTypesMap[EQLabelTypes::StaminaEndurancePercentage] = EQEndurPercentageLabelFunction;
	eqTypesMap[EQLabelTypes::MeleeHaste] = EQLabelFunction;
	eqTypesMap[EQLabelTypes::HealingHaste] = EQLabelFunction;
	eqTypesMap[EQLabelTypes::SpellCrit] = EQLabelFunction;
	eqTypesMap[EQLabelTypes::MeleeCrit] = EQLabelFunction;
	eqTypesMap[EQLabelTypes::HealingCrit] = EQLabelFunction;
	eqTypesMap[EQLabelTypes::SpellPower] = EQLabelFunction;
	eqTypesMap[EQLabelTypes::MeleePower] = EQLabelFunction;
	eqTypesMap[EQLabelTypes::HealingPower] = EQLabelFunction;
	eqTypesMap[EQLabelTypes::TotalPower] = EQLabelFunction;
	eqTypesMap[EQLabelTypes::SavevsMagic] = EQLabelFunction;
	eqTypesMap[EQLabelTypes::SavevsCold] = EQLabelFunction;
	eqTypesMap[EQLabelTypes::SavevsFire] = EQLabelFunction;
	eqTypesMap[EQLabelTypes::SavevsPoison] = EQLabelFunction;
	eqTypesMap[EQLabelTypes::SavevsDisease] = EQLabelFunction;
	eqTypesMap[EQLabelTypes::Walkspeed] = EQSpeedLabelFunction;
	eqTypesMap[EQLabelTypes::Runspeed] = EQSpeedLabelFunction;
	eqTypesMap[EQLabelTypes::CurrentOffense] = EQLabelFunction;
	eqTypesMap[EQLabelTypes::CurrentMitigation] = EQLabelFunction;
	eqTypesMap[EQLabelTypes::Classless] = EQLabelFunction;
	eqTypesMap[EQLabelTypes::Class] = EQClasslessFunction;
	eqTypesMap[EQLabelTypes::Weight] = EQCurWeightLabelFunction;
	eqTypesMap[EQLabelTypes::MaximumWeight] = EQMaxWeightLabelFunction;
	eqTypesMap[EQLabelTypes::WeightMaxWeight] = EQWeightLabelFunction;
	eqTypesMap[EQLabelTypes::Mitigation] = EQSpeedLabelFunction;
	eqTypesMap[EQLabelTypes::AAPoints] = EQLabelFunction;
	eqTypesMap[EQLabelTypes::SynergyLevel] = EQSynergyLabelFunction;
	eqTypesMap[EQLabelTypes::SynergyLevel1] = EQSynergyLabelFunction;
	eqTypesMap[EQLabelTypes::SynergyLevel2] = EQSynergyLabelFunction;
	eqTypesMap[EQLabelTypes::SynergyLevel3] = EQSynergyLabelFunction;
	eqTypesMap[EQLabelTypes::SynergyLevel4] = EQSynergyLabelFunction;
	eqTypesMap[EQLabelTypes::SynergyLevel5] = EQSynergyLabelFunction;
	eqTypesMap[EQLabelTypes::SynergyLevel6] = EQSynergyLabelFunction;
	eqTypesMap[EQLabelTypes::SynergyLevel7] = EQSynergyLabelFunction;
	eqTypesMap[EQLabelTypes::SynergyLevel8] = EQSynergyLabelFunction;
	eqTypesMap[EQLabelTypes::SynergyLevel9] = EQSynergyLabelFunction;
	eqTypesMap[EQLabelTypes::SynergyLevel10] = EQSynergyLabelFunction;
	eqTypesMap[EQLabelTypes::SynergyLevel11] = EQSynergyLabelFunction;
	eqTypesMap[EQLabelTypes::SynergyLevel12] = EQSynergyLabelFunction;

	statLabelMappings[EQLabelTypes::CurrentHitPoints] = eStatEntry::eStatCurHP;
	statLabelMappings[EQLabelTypes::ManaNumber] = eStatEntry::eStatCurMana;
	statLabelMappings[EQLabelTypes::EnduranceNumber] = eStatEntry::eStatCurEndur;
	statLabelMappings[EQLabelTypes::MaximumHitPoints] = eStatEntry::eStatMaxHP;
	statLabelMappings[EQLabelTypes::ManaNumberMax] = eStatEntry::eStatMaxMana;
	statLabelMappings[EQLabelTypes::EnduranceNumberMax] = eStatEntry::eStatMaxEndur;
	statLabelMappings[EQLabelTypes::Strength] = eStatEntry::eStatSTR;
	statLabelMappings[EQLabelTypes::Stamina] = eStatEntry::eStatSTA;
	statLabelMappings[EQLabelTypes::Dexterity] = eStatEntry::eStatDEX;
	statLabelMappings[EQLabelTypes::Agility] = eStatEntry::eStatAGI;
	statLabelMappings[EQLabelTypes::Wisdom] = eStatEntry::eStatWIS;
	statLabelMappings[EQLabelTypes::Intelligence] = eStatEntry::eStatINT;
	statLabelMappings[EQLabelTypes::Charisma] = eStatEntry::eStatCHA;
	statLabelMappings[EQLabelTypes::SpellHaste] = eStatEntry::eStatSpellHaste;
	statLabelMappings[EQLabelTypes::MeleeHaste] = eStatEntry::eStatMeleeHaste;
	statLabelMappings[EQLabelTypes::HealingHaste] = eStatEntry::eStatHealingHaste;
	statLabelMappings[EQLabelTypes::SpellCrit] = eStatEntry::eStatSpellCrit;
	statLabelMappings[EQLabelTypes::MeleeCrit] = eStatEntry::eStatMeleeCrit;
	statLabelMappings[EQLabelTypes::HealingCrit] = eStatEntry::eStatHealingCrit;
	statLabelMappings[EQLabelTypes::SpellPower] = eStatEntry::eStatSpellPower;
	statLabelMappings[EQLabelTypes::MeleePower] = eStatEntry::eStatMeleePower;
	statLabelMappings[EQLabelTypes::HealingPower] = eStatEntry::eStatHealingPower;
	statLabelMappings[EQLabelTypes::TotalPower] = eStatEntry::eStatTotalPower;
	statLabelMappings[EQLabelTypes::SynergyLevel] = eStatEntry::eStatSynergyLevel;
	statLabelMappings[EQLabelTypes::SavevsMagic] = eStatEntry::eStatMR;
	statLabelMappings[EQLabelTypes::SavevsCold] = eStatEntry::eStatCR;
	statLabelMappings[EQLabelTypes::SavevsFire] = eStatEntry::eStatFR;
	statLabelMappings[EQLabelTypes::SavevsPoison] = eStatEntry::eStatPR;
	statLabelMappings[EQLabelTypes::SavevsDisease] = eStatEntry::eStatDR;
	statLabelMappings[EQLabelTypes::CurrentOffense] = eStatEntry::eStatATK;
	statLabelMappings[EQLabelTypes::CurrentMitigation] = eStatEntry::eStatAC;
	statLabelMappings[EQLabelTypes::Mitigation] = eStatEntry::eStatMitigation;
	statLabelMappings[EQLabelTypes::Classless] = eStatEntry::eStatClassless;
	statLabelMappings[EQLabelTypes::Class] = eStatEntry::eStatClassless;
	statLabelMappings[EQLabelTypes::Weight] = eStatEntry::eStatWeight;
	statLabelMappings[EQLabelTypes::MaximumWeight] = eStatEntry::eStatMaxWeight;
	statLabelMappings[EQLabelTypes::AAPoints] = eStatEntry::eStatAAPoints;
	statLabelMappings[EQLabelTypes::SynergyLevel1] = eStatEntry::eStatSynergyLevel1;
	statLabelMappings[EQLabelTypes::SynergyLevel2] = eStatEntry::eStatSynergyLevel2;
	statLabelMappings[EQLabelTypes::SynergyLevel3] = eStatEntry::eStatSynergyLevel3;
	statLabelMappings[EQLabelTypes::SynergyLevel4] = eStatEntry::eStatSynergyLevel4;
	statLabelMappings[EQLabelTypes::SynergyLevel5] = eStatEntry::eStatSynergyLevel5;
	statLabelMappings[EQLabelTypes::SynergyLevel6] = eStatEntry::eStatSynergyLevel6;
	statLabelMappings[EQLabelTypes::SynergyLevel7] = eStatEntry::eStatSynergyLevel7;
	statLabelMappings[EQLabelTypes::SynergyLevel8] = eStatEntry::eStatSynergyLevel8;
	statLabelMappings[EQLabelTypes::SynergyLevel9] = eStatEntry::eStatSynergyLevel9;
	statLabelMappings[EQLabelTypes::SynergyLevel10] = eStatEntry::eStatSynergyLevel10;
	statLabelMappings[EQLabelTypes::SynergyLevel11] = eStatEntry::eStatSynergyLevel11;
	statLabelMappings[EQLabelTypes::SynergyLevel12] = eStatEntry::eStatSynergyLevel12;


    // Add commands, macro parameters, hooks, etc.
    //EasyClassDetour(CLabel__Draw,CLabelHook,Draw_Detour,VOID,(VOID),Draw_Trampoline);
    EzDetour(CLabel__Draw,&CLabelHook::Draw_Detour,&CLabelHook::Draw_Trampoline);
	EzDetour(EQ_Character__Max_HP, &EQCharacter1Hook::MaxHP_Detour, &EQCharacter1Hook::MaxHP_Trampoline);
	EzDetour(EQ_Character__Cur_HP, &EQCharacter1Hook::CurHP_Detour, &EQCharacter1Hook::CurHP_Trampoline);
	EzDetour(EQ_Character__Cur_Mana, &EQCharacter1Hook::CurMana_Detour, &EQCharacter1Hook::CurMana_Trampoline);
	EzDetour(EQ_Character__Max_Mana, &EQCharacter1Hook::MaxMana_Detour, &EQCharacter1Hook::MaxMana_Trampoline);
	EzDetour(EQ_Character__Cur_Endurance, &EQCharacter1Hook::CurEndurance_Detour, &EQCharacter1Hook::CurEndurance_Trampoline);
	EzDetour(EQ_Character__Max_Endurance, &EQCharacter1Hook::MaxEndurance_Detour, &EQCharacter1Hook::MaxEndurance_Trampoline);
	//EzDetour(PlayerPhysics__ClampVelocity, &EQCharacter1Hook::ClampVelocity_Detour, &EQCharacter1Hook::ClampVelocity_Trampoline);
	EzDetour(EQ_Character__GetUsableClasses, &EQCharacter1Hook::GetUsableClass_Detour, &EQCharacter1Hook::GetUsableClass_Trampoline);
	EzDetour(EQ_Character__IsSpellcaster, &EQCharacter1Hook::IsSpellcaster_Detour, &EQCharacter1Hook::IsSpellcaster_Trampoline);
	EzDetour(EQ_Character__IsSpellcaster_2, &EQCharacter1Hook::IsSpellcaster2_Detour, &EQCharacter1Hook::IsSpellcaster2_Trampoline);
	EzDetour(EQ_Character__IsSpellcaster_3, &EQCharacter1Hook::IsSpellcaster3_Detour, &EQCharacter1Hook::IsSpellcaster3_Trampoline);
	EzDetour(EQ_Character__CalculateWeight, &EQCharacter1Hook::CalculateWeight_Detour, &EQCharacter1Hook::CalculateWeight_Trampoline);
	EzDetour(EQ_Spell__GetSpellLevelNeeded, &EQCharacter1Hook::GetSpellLevelNeeded_Detour, &EQCharacter1Hook::GetSpellLevelNeeded_Trampoline);
	EzDetour(CSpellBookWnd__CanStartMemming, &EQCharacter1Hook::CanStartMem_Detour, &EQCharacter1Hook::CanStartMem_Trampoline);
    EzDetour(CSidlManager__CreateLabel,&CSidlManagerHook::CreateLabel_Detour,&CSidlManagerHook::CreateLabel_Trampoline);
	EzDetour(CLabel__Draw, &CLabelHook::Draw_Detour, &CLabelHook::Draw_Trampoline);
    EzDetour(__GetGaugeValueFromEQ,GetGaugeValueFromEQ_Detour, GetGaugeValueFromEQ_Trampoline);
	EzDetour(__GetLabelFromEQ, GetLabelFromEQ_Detour, GetLabelFromEQ_Trampoline);
}

// Called once, when the plugin is to shutdown
PLUGIN_API VOID ShutdownLabelsPlugin(VOID)
{
   // DebugSpewAlways("Shutting down MQ2Labels");
	eqTypesMap.clear();
	statLabelMappings.clear();
    // Remove commands, macro parameters, hooks, etc.
    RemoveDetour(CSidlManager__CreateLabel);
    RemoveDetour(CLabel__Draw);
    //RemoveDetour(CGaugeWnd__Draw);
    //RemoveDetour(__GetGaugeValueFromEQ);
}

