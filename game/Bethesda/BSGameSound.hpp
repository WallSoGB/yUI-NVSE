#pragma once

class BSGameSound 
{
public:
	virtual BSGameSound*	Destroy(bool doFree);
	virtual bool			CheckStateFlagsBit5();
	virtual bool			CheckStateFlagsBit19();
	virtual bool			CheckStateFlagsBit6();
	virtual float			GetVolume();
	virtual void			SetIsLooping(bool doSet);
	virtual void			Unk_06();
	virtual void			Unk_07();
	virtual void			Unk_08();
	virtual void			Unk_09();
	virtual void			Unk_0A();
	virtual void			CopyFrom(BSGameSound* source, bool arg2);
	virtual void			Unk_0C();
	virtual bool			Unk_0D();
	virtual bool			Unk_0E();
	virtual bool			SetVolume(float inVol);
	virtual void			Unk_10();
	virtual bool			Unk_11();
	virtual void			Unk_12();
	virtual void			Unk_13(float arg1, float arg2, float arg3);
	virtual void			Unk_14(float arg1, float arg2, float arg3);
	virtual void			Unk_15(NiPoint3& arg1);
	virtual void			Unk_16();
	virtual void			Unk_17(float arg1, float arg2);
	virtual void			Unk_18(UInt16 arg1, UInt16 arg2, UInt16 arg3, UInt16 arg4, UInt16 arg5);
	virtual bool			SetFrameFrequencyPerc(float freqPerc);
	virtual float			GetFrameFrequencyPerc();
	virtual void			Seek(UInt32 timePoint);

	enum SoundFlags
	{
		kFlag_2D = 1,
		kFlag_3D = 2,
		kFlag_IsVoice = 4,
		kFlag_IsFootsteps = 8,
		kFlag_Loop = 0x10,
		kFlag_NotDialogue = 0x20,
		kFlag_RandomFrequencyShift = 0x40,
		kFlag_UnkBit7 = 0x80,
		kFlag_UnkBit8 = 0x100,
		kFlag_UnkBit9 = 0x200,
		kFlag_UnkBit10 = 0x400,
		kFlag_IsMusic = 0x800,
		kFlag_MuteWhenSubmerged1 = 0x1000,
		kFlag_MaybeUnderwater = 0x2000,
		kFlag_DonotCache = 0x10000,
		kFlag_FirstPerson = 0x40000,
		kFlag_Modulated = 0x80000,
		kFlag_IsRadio = 0x100000,
		kFlag_UnkBit22 = 0x400000,
		kFlag_EnvelopeFast = 0x2000000,
		kFlag_EnvelopeSlow = 0x4000000,
		kFlag_2DRadius = 0x8000000
	};

	enum Flags00C
	{
		kFlag_MuteWhenSubmerged = 1,
		kFlag_StartAtRandomPosition = 2,
	};

	enum StateFlags
	{
		kState_Stopped = 0x10,
		kState_UnkBit5 = 0x20,
		kState_UnkBit6 = 0x40,
		kState_UnkBit9 = 0x200,
		kState_Muted = 0x400,
		kState_UnkBit15 = 0x8000,
		kState_UnkBit16 = 0x10000,
		kState_IsLooping = 0x20000,
		kState_UnkBit19 = 0x80000,
		kState_UnkBit20 = 0x100000,
	};

	UInt32 uiID;
	UInt32 audioFlags;
	UInt32 flags00C;
	UInt32 state;
	UInt32 duration;
	UInt16 staticAttenuation;
	UInt16 systemAttenuation;
	UInt16 distanceAttenuation;
	UInt16 faderAttenuation;
	UInt16 unk020;
	UInt16 unk022;
	float volume;
	float flt028;
	float flt02C;
	UInt32 unk030;
	UInt16 baseSamplingFreq;
	char filePath[254];
	TESSound*		sourceSound;
	float			frequencyMod;
	float maxAttenuationDist;
	float minAttenuationDist;
	UInt32 uiSourceID;
	UInt32 uiAlternateID;
	UInt32 uiChunkSizeInBytes;
	float flt150;
	UInt32 environmentType;
	SInt8			randFrequencyShift;		// 158
	UInt8			byte159;				// 159
	UInt16 samplingFreq;
	UInt32 unk15C;
	UInt32 audioDelayMS;
	UInt32 unk164;
	UInt32 unk168;
	UInt32 time16C;
	UInt32 time170;
	UInt32 unk174;
	UInt32 unk178;
	UInt32 unk17C;
	UInt32 unk180;
	UInt32 unk184;
	UInt32 priority;
	UInt32 unk18C;
	UInt32 unk190;
	UInt32 unk194;
};
static_assert(sizeof(BSGameSound) == 0x198);