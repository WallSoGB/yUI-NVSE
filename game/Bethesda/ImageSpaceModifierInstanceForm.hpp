#pragma once

#include "ImageSpaceModifierInstance.hpp"

class TESImageSpaceModifier;

class ImageSpaceModifierInstanceForm : public ImageSpaceModifierInstance {
public:
	TESImageSpaceModifier* imageSpaceMod;		// 1C
	TESImageSpaceModifier* lastImageSpaceMod;	// 20
	float					lastStrength;		// 24
	NiObject* lastTarget;		// 28
	float					transitionTime;		// 2C
};