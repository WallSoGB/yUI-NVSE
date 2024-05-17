#pragma once

enum EnumActorValueCode
{
	kAVCode_None = -1,
	kAVCode_Aggression = 0x0,
	kAVCode_Confidence = 0x1,
	kAVCode_Energy = 0x2,
	kAVCode_Responsibility = 0x3,
	kAVCode_Mood = 0x4,

	kAVCode_Strength = 0x5,
	kAVCode_Perception = 0x6,
	kAVCode_Endurance = 0x7,
	kAVCode_Charisma = 0x8,
	kAVCode_Intelligence = 0x9,
	kAVCode_Agility = 0xA,
	kAVCode_Luck = 0xB,
	kAVCode_SpecialStart = kAVCode_Strength,
	kAVCode_SpecialEnd = kAVCode_Luck,

	kAVCode_ActionPoints = 0xC,
	kAVCode_CarryWeight = 0xD,
	kAVCode_CritChance = 0xE,
	kAVCode_HealRate = 0xF,
	kAVCode_Health = 0x10,
	kAVCode_MeleeDamage = 0x11,
	kAVCode_DamageResistance = 0x12,
	kAVCode_PoisonResist = 0x13,
	kAVCode_RadResist = 0x14,
	kAVCode_SpeedMult = 0x15,
	kAVCode_Fatigue = 0x16,
	kAVCode_Karma = 0x17,
	kAVCode_XP = 0x18,

	kAVCode_PerceptionCondition = 0x19,
	kAVCode_EnduranceCondition = 0x1A,
	kAVCode_LeftAttackCondition = 0x1B,
	kAVCode_RightAttackCondition = 0x1C,
	kAVCode_LeftMobilityCondition = 0x1D,
	kAVCode_RightMobilityCondition = 0x1E,
	kAVCode_BrainCondition = 0x1F,
	kAVCode_BodyPartStart = kAVCode_PerceptionCondition,
	kAVCode_BodyPartEnd = kAVCode_BrainCondition,

	kAVCode_Barter = 0x20,
	kAVCode_BigGuns = 0x21,
	kAVCode_EnergyWeapons = 0x22,
	kAVCode_Explosives = 0x23,
	kAVCode_Lockpick = 0x24,
	kAVCode_Medicine = 0x25,
	kAVCode_MeleeWeapons = 0x26,
	kAVCode_Repair = 0x27,
	kAVCode_Science = 0x28,
	kAVCode_Guns = 0x29,
	kAVCode_Sneak = 0x2A,
	kAVCode_Speech = 0x2B,
	kAVCode_Survival = 0x2C,
	kAVCode_Unarmed = 0x2D,
	kAVCode_SkillsStart = kAVCode_Barter,
	kAVCode_SkillsEnd = kAVCode_Unarmed,

	kAVCode_InventoryWeight = 0x2E,
	kAVCode_Paralysis = 0x2F,
	kAVCode_Invisibility = 0x30,
	kAVCode_Chameleon = 0x31,
	kAVCode_NightEye = 0x32,
	kAVCode_Turbo = 0x33,
	kAVCode_FireResist = 0x34,
	kAVCode_WaterBreathing = 0x35,
	kAVCode_RadiationRads = 0x36,
	kAVCode_BloodyMess = 0x37,
	kAVCode_UnarmedDamage = 0x38,
	kAVCode_Assistance = 0x39,
	kAVCode_ElectricResist = 0x3A,
	kAVCode_FrostResist = 0x3B,
	kAVCode_EnergyResist = 0x3C,
	kAVCode_EmpResist = 0x3D,

	kAVCode_Variable01 = 0x3E,
	kAVCode_Variable02 = 0x3F,
	kAVCode_Variable03 = 0x40,
	kAVCode_Variable04 = 0x41,
	kAVCode_Variable05 = 0x42,
	kAVCode_Variable06 = 0x43,
	kAVCode_Variable07 = 0x44,
	kAVCode_Variable08 = 0x45,
	kAVCode_Variable09 = 0x46,
	kAVCode_Variable10 = 0x47,

	kAVCode_IgnoreCrippledLimbs = 0x48,
	kAVCode_Dehydration = 0x49,
	kAVCode_Hunger = 0x4A,
	kAVCode_SleepDeprivation = 0x4B,
	kAVCode_DamageThreshold = 0x4C,
	kAVCode_Max = 0x4D,
};