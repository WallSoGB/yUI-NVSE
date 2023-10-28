#pragma once
#include "NiObject.hpp"

class hkReferencedObject;

class bhkRefObject : public NiObject {
public:
	bhkRefObject();
	virtual ~bhkRefObject();

	virtual void SethkObject(hkReferencedObject* aphkObject);	// 35
	virtual void Link(bool abAttach);							// 36			

	hkReferencedObject* phkObject;
};
static_assert(sizeof(bhkRefObject) == 0xC);