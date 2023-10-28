#pragma once

#include "NiDynamicEffect.hpp"
#include "NiColor.hpp"

NiSmartPointer(NiLight);
NiRTTIAddress(NiLight, 0x11F4A28);

class NiLight : public NiDynamicEffect {
public:
	NiLight();
	virtual ~NiLight();

	float	m_fDimmer;
	NiColor m_kAmb;
	NiColor m_kDiff;
	NiColor m_kSpec;
	void*	m_pvRendererData;
};

ASSERT_SIZE(NiLight, 0xF0);