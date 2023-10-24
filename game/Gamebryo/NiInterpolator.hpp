#pragma once

#include "NiObject.hpp"

NiSmartPointer(NiInterpolator);

class NiInterpolator : public NiObject {
public:
	NiInterpolator();
	virtual ~NiInterpolator();

	float m_fLastTime;
};

ASSERT_SIZE(NiInterpolator, 0xC);