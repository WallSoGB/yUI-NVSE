#pragma once

#include "hkVector4.hpp"

class hkDiagonal {
public:
	hkVector4	pt0;
	hkVector4	pt1;
};

ASSERT_SIZE(hkDiagonal, 0x20)