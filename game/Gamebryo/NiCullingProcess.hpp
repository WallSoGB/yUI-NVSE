#pragma once

#include "NiRTTI.hpp"
#include "NiAVObject.hpp"
#include "NiGeometry.hpp"
#include "NiCamera.hpp"
#include "NiVisibleArray.hpp"
#include "NiFrustumPlanes.hpp"

NiRTTIAddress(NiCullingProcess, 0x11F4990);

class NiCullingProcess : public NiMemObject {
public:
	NiCullingProcess(NiVisibleArray* apVisibleSet = nullptr);

	virtual const NiRTTI*				GetRTTI() { return NiCullingProcess__ms_RTTI; }
	virtual NiNode*						IsNiNode() { return nullptr; };
	virtual BSFadeNode*					IsFadeNode() { return nullptr; };
	virtual BSMultiBoundNode*			IsMultiBoundNode() { return nullptr; };
	virtual NiGeometry*					IsGeometry() { return nullptr; };
	virtual NiTriBasedGeom*				IsTriBasedGeometry() { return nullptr; };
	virtual NiTriStrips*				IsTriStrips() { return nullptr; };
	virtual NiTriShape*					IsTriShape() { return nullptr; };
	virtual BSSegmentedTriShape*		IsSegmentedTriShape() { return nullptr; };
	virtual BSResizableTriShape*		IsResizableTriShape() { return nullptr; };
	virtual NiParticles*				IsParticlesGeom() { return nullptr; };
	virtual NiLines*					IsLinesGeom() { return nullptr; };
	virtual bhkCollisionObject*			IsBhkNiCollisionObject() { return nullptr; };
	virtual bhkBlendCollisionObject*	IsBhkBlendCollisionObject() { return nullptr; };
	virtual bhkRigidBody*				IsBhkRigidBody() { return nullptr; };
	virtual bhkLimitedHingeConstraint*	IsBhkLimitedHingeConstraint() { return nullptr; };
	virtual								~NiCullingProcess() {};
	virtual void						Process(NiAVObject* apObject);
	virtual void						ProcessAlt(const NiCamera* apCamera, NiAVObject* apScene, NiVisibleArray* apVisibleSet);
	virtual void						AppendVirtual(NiGeometry* apGeom) {};

	bool				m_bUseVirtualAppend;
	NiVisibleArray*		m_pkVisibleSet;
	NiCamera*			m_pkCamera;
	NiFrustum			m_kFrustum;
	NiFrustumPlanes		m_kPlanes;

	void SetCamera(const NiCamera* apCamera);
	void SetFrustum(const NiFrustum* kFrustum);

	void DoCulling(NiAVObject* pkObject);
};

ASSERT_SIZE(NiCullingProcess, 0x90);