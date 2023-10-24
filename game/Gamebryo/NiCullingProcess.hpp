#pragma once

#include "NiRTTI.hpp"
#include "NiAVObject.hpp"
#include "NiGeometry.hpp"
#include "NiCamera.hpp"
#include "NiVisibleArray.hpp"
#include "NiFrustumPlanes.hpp"

class NiCullingProcess : public NiMemObject {
public:
	NiCullingProcess() {};

	virtual NiRTTI*						GetRTTI();
	virtual NiNode*						IsNiNode();
	virtual BSFadeNode*					IsFadeNode();
	virtual BSMultiBoundNode*			IsMultiBoundNode();
	virtual NiGeometry*					IsGeometry();
	virtual NiTriBasedGeom*				IsTriBasedGeometry();
	virtual NiTriStrips*				IsTriStrips();
	virtual NiTriShape*					IsTriShape();
	virtual BSSegmentedTriShape*		IsSegmentedTriShape();
	virtual BSResizableTriShape*		IsResizableTriShape();
	virtual NiParticles*				IsParticlesGeom();
	virtual NiLines*					IsLinesGeom();
	virtual bhkCollisionObject*			IsBhkNiCollisionObject();
	virtual bhkBlendCollisionObject*	IsBhkBlendCollisionObject();
	virtual bhkRigidBody*				IsBhkRigidBody();
	virtual bhkLimitedHingeConstraint*	IsBhkLimitedHingeConstraint();
	virtual								~NiCullingProcess();
	virtual void						Process(NiAVObject* pkObject);
	virtual void						ProcessAlt(const NiCamera* pkCamera, NiAVObject* pkScene, NiVisibleArray* pkVisibleSet);
	virtual void						AppendVirtual(NiGeometry*);

	bool				m_bUseVirtualAppend;
	NiVisibleArray*		m_pkVisibleSet;
	NiCamera*			m_pkCamera;
	NiFrustum			m_kFrustum;
	NiFrustumPlanes		m_kPlanes;

	static NiCullingProcess* Create(NiCullingProcess* apThis, NiVisibleArray* pkVisibleSet = 0);

	void SetCamera(const NiCamera* apCamera);
	void SetFrustum(const NiFrustum* kFrustum);

	void DoCulling(NiAVObject* pkObject);
};

ASSERT_SIZE(NiCullingProcess, 0x90);