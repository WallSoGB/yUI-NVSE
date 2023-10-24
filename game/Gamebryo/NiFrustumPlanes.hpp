#pragma once

#include "NiPlane.hpp"
#include "NiTransform.hpp"
#include "NiFrustum.hpp"

class NiCamera;

class NiFrustumPlanes {
public:
	NiFrustumPlanes() {
		m_uiActivePlanes = 63;
	}
	~NiFrustumPlanes() {};

	enum ActivePlanes {
		NEAR_PLANE = 0,
		FAR_PLANE = 1,
		LEFT_PLANE = 2,
		RIGHT_PLANE = 3,
		TOP_PLANE = 4,
		BOTTOM_PLANE = 5,
		MAX_PLANES = 6
	};

	NiPlane	m_akCullingPlanes[MAX_PLANES];
	UInt32	m_uiActivePlanes;

	void Set(NiFrustum* kFrust, NiTransform* kXform);

	void Set(NiCamera* apCamera);


	const NiPlane& GetPlane(UInt32 ePlane) const;
	bool IsPlaneActive(UInt32 ePlane) const;
	bool IsAnyPlaneActive() const;
	void EnablePlane(UInt32 ePlane);
	void DisablePlane(UInt32 ePlane);
	void SetActivePlaneState(UInt32 uiState);
};

ASSERT_SIZE(NiFrustumPlanes, 0x64);