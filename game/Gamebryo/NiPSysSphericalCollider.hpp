#pragma once

#include "NiPSysCollider.hpp"
#include "NiAVObject.hpp"

NiSmartPointer(NiPSysSphericalCollider);

class NiPSysSphericalCollider : public NiPSysCollider {
public:
	NiPSysSphericalCollider();
	virtual ~NiPSysSphericalCollider();

	NiAVObject*		m_pkColliderObj;
	float			m_fRadius;
	float			m_fScaledRadius;
	float			m_fRadiusSq;
	NiPoint3		m_kPosition;
	NiTransform		m_kLastColliderTransform;
	NiTransform		m_kLastPSysTransform;

	CREATE_OBJECT(NiPSysSphericalCollider, 0xC282A0)
};

ASSERT_SIZE(NiPSysSphericalCollider, 0xB0);