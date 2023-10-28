#pragma once

class hkBaseObject {
public:
	virtual void Destroy(bool);
};

ASSERT_SIZE(hkBaseObject, 0x4);