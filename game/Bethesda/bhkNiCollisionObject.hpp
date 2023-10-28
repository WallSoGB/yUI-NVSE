#pragma once

#include "NiCollisionObject.hpp"
#include "NiTransform.hpp"

class bhkWorldObject;

NiSmartPointer(bhkNiCollisionObject);

class bhkNiCollisionObject : public NiCollisionObject {
public:
	virtual NiPoint3* GetLinearVelocityInGameUnits(NiPoint3* outVel);
	virtual void CollisionObjTransformToTargetNode();
	virtual void TargetNodeTransformToCollisionObj();
	virtual void UpdateVelocity();
	virtual void SetMotionType(UInt32 aeType, bhkRigidBody* apBody, bool abUpdateMotion);
	virtual bool IsFixedMotion();
	virtual void SetTargetNodeTransform(NiTransform& akTransform);
	virtual bool Unk_2F();
	virtual void ToggleDebugDisplay(bool abToggle);

	enum Flags {
		kFlag_Active =		  1,
		kFlag_Notify =		  4,
		kFlag_SetLocal =		8,
		kFlag_DebugDisplay =	0x10,
		kFlag_UseVelocity =	 0x20,
		kFlag_Reset =		   0x40,
		kFlag_SyncOnUpdate =	0x80,
		kFlag_AnimTargeted =	0x400,
		kFlag_DismemberLimb =   0x800
	};

	UInt32		  uiFlags;
	bhkWorldObject* pWorldObject;
};