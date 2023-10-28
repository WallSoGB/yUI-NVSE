#pragma once

#include "hkVector4.hpp"

class hkaRaycastInterface {
public:
	hkaRaycastInterface();
	~hkaRaycastInterface();

	virtual hkaRaycastInterface*	Destroy(bool doFree);
	virtual bool*					castRay(bool*, hkVector4*, hkVector4*, UInt32, float, hkVector4*);
	virtual bool*					castRay(bool*, hkVector4*, hkVector4*, UInt32, hkVector4*);
};

ASSERT_SIZE(hkaRaycastInterface, 0x4);