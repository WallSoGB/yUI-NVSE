#pragma once

#include "NiCamera.hpp"

class NiGeometry;

NiSmartPointer(NiAccumulator);

class NiAccumulator : public NiObject {
public:
	NiAccumulator();
	virtual ~NiAccumulator();

	[[deprecated("Don't use this one, use StartAccumulating for inlines")]] 
	// Do Not Use
	virtual void vStartAccumulating(const NiCamera* pkCamera);

	virtual void FinishAccumulating();
	virtual void RegisterObjectArray(void* kArray);
	virtual void RegisterObject(NiGeometry* apGeometry);
	virtual bool AddShared(NiAVObject* apObject);
	virtual void ClearSharedMap();

	NiCamera* m_pkCamera;

	void StartAccumulating(const NiCamera* pkCamera);
};

ASSERT_SIZE(NiAccumulator, 0xC);