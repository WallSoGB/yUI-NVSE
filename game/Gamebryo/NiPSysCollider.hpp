#pragma once

#include "NiObject.hpp"
#include "NiPoint3.hpp"

class NiPSysSpawnModifier;
class NiPSysColliderManager;

NiSmartPointer(NiPSysCollider);

class NiPSysCollider : public NiObject {
public:
	NiPSysCollider();
	virtual ~NiPSysCollider();

	float					m_fBounce;
	bool					m_bSpawnOnCollide;
	bool					m_bDieOnCollide;
	NiPSysSpawnModifier*	m_pkSpawnModifier;
	NiPoint3				m_kCollisionPoint;
	float					m_fCollisionTime;
	NiPSysColliderManager*	m_pkManager;
	NiPSysColliderPtr		m_spNext;

	CREATE_OBJECT(NiPSysCollider, 0xC2D5B0)
};

ASSERT_SIZE(NiPSysCollider, 0x2C);