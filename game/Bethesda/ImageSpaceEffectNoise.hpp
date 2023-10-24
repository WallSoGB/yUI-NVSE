#pragma once

#include "ImageSpaceEffect.hpp"

class ImageSpaceEffectNoise : public ImageSpaceEffect {
public:
	ImageSpaceTexture pNoiseMap;
	ImageSpaceTexture pTexBuffer;
	ImageSpaceTexture pPermutedTex2D;
	ImageSpaceTexture pPermutedGradientTex;
	char p[512];
	float fTexRatio0[4];
	float fTexRatio1[4];
	bool bIsLoaded;

	static ImageSpaceEffectNoise*	GetInstance();
	bool							IsLoaded();
	UInt32							InitializeUtilityBuffers(SInt32 aiSeed);
	void							ShufflePermuationTable();

	static void						SetNoiseScale(float afScale);
	static float					GetNoiseScale();
	static void						SetTexScale(float afX, float afY, float afZ);
	static NiColorA 				GetTexScale();
	static void						SetTexScrolls(NiColorA afScroll0, NiColorA afScroll1, NiColorA afScroll2);
	static void						GetTexScrolls(NiColorA* apfScroll0, NiColorA* apfScroll1, NiColorA* apfScroll2);
	static void						SetNoiseAmplitude(float afX, float afY, float afZ);
	static NiColorA 				GetNoiseAmplitude();
};

ASSERT_SIZE(ImageSpaceEffectNoise, 0x2BC);