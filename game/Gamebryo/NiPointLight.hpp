#pragma once

#include "NiLight.hpp"

NiSmartPointer(NiPointLight);

class NiPointLight : public NiLight {
public:
	NiPointLight();
	virtual ~NiPointLight();

	float m_fAtten0;
	float m_fAtten1;
	float m_fAtten2;

	CREATE_OBJECT(NiPointLight, 0xA7D6E0)
};

ASSERT_SIZE(NiPointLight, 0xFC)