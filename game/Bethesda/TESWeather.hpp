#pragma once

#include "TESForm.hpp"
#include "TESImageSpaceModifiableCountForm.hpp"
#include "TESTexture1024.hpp"
#include "TESModel.hpp"

class TESWeather : public TESForm {
public:
	TESWeather();
	~TESWeather();

	struct WeatherSound
	{
		UInt32 soundID;
		UInt32 type;
	};

	enum WeatherData {
		WD_WIND_SPEED = 0x0,
		WD_CLOUD_SPEEDY = 0x1,
		WD_CLOUD_SPEEDX = 0x2,
		WD_TRANS_DELTA = 0x3,
		WD_SUN_GLARE = 0x4,
		WD_SUN_DAMAGE = 0x5,
		WD_BEGIN_PRECIP = 0x6,
		WD_END_PRECIP = 0x7,
		WD_BEGIN_THUNDER = 0x8,
		WD_END_THUNDER = 0x9,
		WD_THUNDER_FREQ = 0xA,
		WD_FLAGS = 0xB,
		WD_LIGHTNING_R = 0xC,
		WD_LIGHTNING_G = 0xD,
		WD_LIGHTNING_B = 0xE,
		WD_BEGIN_EFFECT = 0xF,
		WD_END_EFFECT = 0x10,
		WD_WIND_DIR = 0x11,
		WD_WIND_DIR_RANGE = 0x12,
		WD_WIND_TURBULENCE = 0x13,
		WD_COUNT = 0x15,
	};


	TESImageSpaceModifiableCountForm pImageSpaceMods;
	TESTexture1024 cloudTexture[4];
	UInt8 cloudSpeed[4];
	UInt32 uiCloudColorData[4][6];
	TESModel model;
	UInt8 ucWeatherData[15];
	float fFogData[6];
	UInt32 uiColorData[10][6];
	BSSimpleList<WeatherSound*> soundList;
	float fHDRInfo[14];
	UInt32 unk238;
	UInt32 unk23C;
	UInt32 unk240;
	UInt32 unk244;
	UInt32 unk248;
	UInt32 unk24C;
	UInt32 unk250;
	UInt32 unk254;
	UInt32 unk258;
	UInt32 unk25C;
	UInt32 unk260;
	UInt32 unk264;
	UInt32 unk268;
	UInt32 unk26C;
	UInt32 unk270;
	UInt32 unk274;
	UInt32 unk278;
	UInt32 unk27C;
	UInt32 unk280;
	UInt32 unk284;
	UInt32 unk288;
	UInt32 unk28C;
	UInt32 unk290;
	UInt32 unk294;
	UInt32 unk298;
	UInt32 unk29C;
	UInt32 unk2A0;
	UInt32 unk2A4;
	UInt32 unk2A8;
	UInt32 unk2AC;
	UInt32 unk2B0;
	UInt32 unk2B4;
	UInt32 unk2B8;
	UInt32 unk2BC;
	UInt32 unk2C0;
	UInt32 unk2C4;
	UInt32 unk2C8;
	UInt32 unk2CC;
	UInt32 unk2D0;
	UInt32 unk2D4;
	UInt32 unk2D8;
	UInt32 unk2DC;
	UInt32 unk2E0;
	UInt32 unk2E4;
	UInt32 unk2E8;
	UInt32 unk2EC;
	UInt32 unk2F0;
	UInt32 unk2F4;
	UInt32 unk2F8;
	UInt32 unk2FC;
	UInt32 unk300;
	UInt32 unk304;
	UInt32 unk308;
	UInt32 unk30C;
	UInt32 unk310;
	UInt32 unk314;
	UInt32 unk318;
	UInt32 unk31C;
	UInt32 unk320;
	UInt32 unk324;
	UInt32 unk328;
	UInt32 unk32C;
	UInt32 unk330;
	UInt32 unk334;
	UInt32 unk338;
	UInt32 unk33C;
	UInt32 unk340;
	UInt32 unk344;
	UInt32 unk348;
	UInt32 unk34C;
	UInt32 unk350;
	UInt32 unk354;
	UInt32 unk358;
	UInt32 unk35C;
	UInt32 unk360;
	UInt32 unk364;
	UInt32 numCloudLayers;

	bool IsRainy();
	double GetWeatherData(WeatherData aeData, float afMax, float afMin);
};

ASSERT_SIZE(TESWeather, 0x36C);

/*
// 2F4
class TESWeather : public TESForm
{
public:
TESWeather();
~TESWeather();

struct ColorData {
RGBA colors[6];
};

UInt32					unk018;						// 018
TESImageSpaceModifier	*imageSpaceMods[6];			// 01C
TESTexture				layerTextures[4];			// 034
UInt8					cloudSpeed[4];				// 064
UInt32					unk068[24];					// 068
TESModel				model;						// 0C8
UInt8					windSpeed;					// 0E0
UInt8					cloudSpeedLower;			// 0E1
UInt8					cloudSpeedUpper;			// 0E2
UInt8					transDelta;					// 0E3
UInt8					sunGlare;					// 0E4
UInt8					sunDamage;					// 0E5
UInt8					precipitationBeginFadeIn;	// 0E6
UInt8					precipitationEndFadeOut;	// 0E7
UInt8					lightningBeginFadeIn;		// 0E8
UInt8					lightningEndFadeOut;		// 0E9
UInt8					lightningFrequency;			// 0EA
UInt8					weatherClassification;		// 0EB
UInt32					lightningColor;				// 0EC
float					fogDistance[6];				// 0F0
ColorData				colors[10];				// 108
UInt32					unk1F8[63];					// 1F8
};
static_assert(sizeof(TESWeather) == 0x2F4);

*/