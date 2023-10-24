#pragma once

#include "NiObject.hpp"
#include "hkReferencedObject.hpp"

class bhkRefObject : public NiObject {
public:
	bhkRefObject();
	virtual ~bhkRefObject();

	virtual void SethkObject(hkReferencedObject* aphkObject);	// 35
	virtual void Link(bool abAttach);							// 36			

	hkReferencedObject* phkObject;
};

ASSERT_SIZE(bhkRefObject, 0xC);