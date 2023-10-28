#pragma once
#include "TESBoundAnimObject.hpp"
#include "TESSoundFile.hpp"

// 0x6C
class TESSound :
	public TESBoundAnimObject,
	public TESSoundFile
{
public:
	TESSound();
	~TESSound();

	struct  TESSoundData
	{
		enum EnumFlags : UInt32
		{
			kFlag_RandomFrequencyShift = 1,
			kFlag_PlayAtRandom = 2,
			kFlag_EnvironmentIgnored = 4,
			kFlag_RandomLocation = 8,
			kFlag_Loop = 16,
			kFlag_MenuSound = 32,
			kFlag_2D = 64,
			kFlag_360LFE = 128,
			kFlag_DialogueSound = 256,
			kFlag_EnvelopeFast = 512,
			kFlag_EnvelopeSlow = 1024,
			kFlag_2DRadius = 2048,
			kFlag_MuteWhenSubmerged = 4096,
			kFlag_StartAtRandomPosition = 8192,
		};

		UInt8		minAttenuationDist;
		UInt8		maxAttenuationDist;
		UInt8		frequencyAdj;
		UInt8		byte03;
		EnumFlags	eFlags;
		UInt16		staticAttenuation;
		UInt8		endsAt;
		UInt8		startsAt;
		UInt16		attenuationCurve[5];
		UInt16		reverbAttenuation;
		UInt32		priority;
		UInt32		loopPointBegin;
		UInt32		loopPointEnd;
	};

	BSStringT		kEditorID;
	TESSoundData	kData;
	UInt8			ucRngChance;
	UInt8			gap69[3];

};
static_assert(sizeof(TESSound) == 0x6C);