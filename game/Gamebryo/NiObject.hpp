#pragma once

#include "NiRefObject.hpp"
#include "NiRTTI.hpp"
#include "NiTArray.hpp"
#include "NiObjectGroup.hpp"
#include "NiBound.hpp"

class bhkBlendCollisionObject;
class bhkCollisionObject;
class bhkLimitedHingeConstraint;
class bhkRigidBody;
class BSFadeNode;
class BSMultiBoundNode;
class BSResizableTriShape;
class BSSegmentedTriShape;
class NiCloningProcess;
class NiGeometry;
class NiLines;
class NiNode;
class NiParticles;
class NiStream;
class NiTriBasedGeom;
class NiTriShape;
class NiTriStrips;
class NiControllerManager;

NiSmartPointer(NiObject);
NiRTTIAddress(NiObject, 0x11F4418);

// 0x8
class NiObject : public NiRefObject {
public:
	NiObject();
	virtual ~NiObject();

	virtual const NiRTTI*				GetRTTI() const;									// 02 | Returns NiRTTI of the object
	virtual NiNode*						IsNiNode();											// 03 | Returns this if it's a NiNode, otherwise nullptr
	virtual BSFadeNode*					IsFadeNode();										// 04 | Returns this if it's a BSFadeNode, otherwise nullptr
	virtual BSMultiBoundNode*			IsMultiBoundNode();									// 05 | Returns this if it's a BSMultiBoundNode, otherwise nullptr
	virtual NiGeometry*					IsGeometry();										// 06 | Returns this if it's a NiGeometry, otherwise nullptr
	virtual NiTriBasedGeom*				IsTriBasedGeometry();								// 07 | Returns this if it's a NiTriBasedGeom, otherwise nullptr
	virtual NiTriStrips*				IsTriStrips();										// 08 | Returns this if it's a NiTriStrips, otherwise nullptr
	virtual NiTriShape*					IsTriShape();										// 09 | Returns this if it's a NiTriShape, otherwise nullptr
	virtual BSSegmentedTriShape*		IsSegmentedTriShape();								// 10 | Returns this if it's a BSSegmentedTriShape, otherwise nullptr
	virtual BSResizableTriShape*		IsResizableTriShape();								// 11 | Returns this if it's a BSResizableTriShape, otherwise nullptr
	virtual NiParticles*				IsParticlesGeom();									// 12 | Returns this if it's a NiParticles, otherwise nullptr
	virtual NiLines*					IsLinesGeom();										// 13 | Returns this if it's a NiLines, otherwise nullptr
	virtual bhkCollisionObject*			IsBhkNiCollisionObject();							// 14 | Returns this if it's a bhkCollisionObject, otherwise nullptr
	virtual bhkBlendCollisionObject*	IsBhkBlendCollisionObject();						// 15 | Returns this if it's a bhkBlendCollisionObject, otherwise nullptr
	virtual bhkRigidBody*				IsBhkRigidBody();									// 16 | Returns this if it's a bhkRigidBody, otherwise nullptr
	virtual bhkLimitedHingeConstraint*	IsBhkLimitedHingeConstraint();						// 17 | Returns this if it's a bhkLimitedHingeConstraint, otherwise nullptr
	virtual NiObject*					CreateClone(NiCloningProcess* apCloning);			// 18 | Creates a clone of this object
	virtual void						LoadBinary(NiStream* apStream);						// 19 | Loads objects from disk
	virtual void						LinkObject(NiStream* apStream);						// 20 | Called by the streaming system to resolve links to other objects once it can be guaranteed that all objects have been loaded
	virtual void						RegisterStreamables(NiStream* apStream);			// 21 | When an object is inserted into a stream, it calls register streamables to make sure that any contained objects or objects linked in a scene graph are streamed as well
	virtual void						SaveBinary(NiStream* apStream);						// 22 | Saves objects to disk
	virtual bool						IsEqual(NiObject* apObject);						// 23 | Compares this object with another
	virtual void						GetViewerStrings(NiTArray<const char*>* apStrings); // 24 | Gets strings containing information about the object
	virtual void						AddViewerStrings(NiTArray<const char*>* apStrings); // 25 | Adds additional strings containing information about the object
	virtual void						ProcessClone(NiCloningProcess* apCloning);			// 26 | Post process for CreateClone
	virtual void						PostLinkObject(NiStream* apStream);					// 27 | Called by the streaming system to resolve any tasks that require other objects to be correctly linked. It is called by the streaming system after LinkObject has been called on all streamed objects
	virtual bool						StreamCanSkip();									// 28
	virtual const NiRTTI*				GetStreamableRTTI();								// 29
	virtual void						SetBound(NiBound* apNewBound);						// 30 | Replaces the bound of the object
	virtual void						GetBlockAllocationSize();							// 31 | Used by geometry data
	virtual NiObjectGroup				GetGroup();											// 32 | Used by geometry data
	virtual void						SetGroup(NiObjectGroup* apGroup);					// 33 | Used by geometry data
	virtual NiControllerManager*		IsControllerManager();								// 34 | Returns this if it's a NiControllerManager, otherwise nullptr

	NiObject* Clone() { return ThisStdCall<NiObject*>(0xA5D680, this); }

	bool IsKindOf(const NiRTTI* pkRTTI) {
		for (const NiRTTI* i = GetRTTI(); i; i = i->m_pkBaseRTTI) {
			if (i == pkRTTI)
				return true;
		}
		return false;
	}

	bool IsExactKindOf(const NiRTTI* pkRTTI) {
		return GetRTTI() == pkRTTI;
	}

	static bool IsExactKindOf(const NiRTTI* pkRTTI, NiObject* apObject) {
		if (!apObject)
			return false;
		return apObject->IsExactKindOf(pkRTTI);
	}
};

ASSERT_SIZE(NiObject, 0x8);