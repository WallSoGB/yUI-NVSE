#pragma once

#include "NiObject.hpp"

class ImageSpaceModifierInstance : public NiObject {
public:
	virtual bool						IsExpired();
	virtual void						Apply();
	virtual ImageSpaceModifierInstance*	IsForm();
	virtual void						PrintInfo(const char* apBuffer);

	bool					bIsHidden;
	float					fStrength;
	NiObjectPtr				spTarget;
	float					fAge;
	UInt32					uiFlags;
};

ASSERT_SIZE(ImageSpaceModifierInstance, 0x1C);