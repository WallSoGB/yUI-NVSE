#pragma once

class alignas(16) hkQuaternion {
public: 
	float x;
	float y;
	float z;
	float w;
};

ASSERT_SIZE(hkQuaternion, 0x10);