#pragma once

#include "NiSkinInstance.hpp"

class DismemberPartition;

NiSmartPointer(BSDismemberSkinInstance);

class BSDismemberSkinInstance : public NiSkinInstance {
public:
	BSDismemberSkinInstance();
	~BSDismemberSkinInstance();

	UInt32 partitionNumber;
	DismemberPartition* partitions;
	bool  IsRenderable;  //In Load this is made in OR with every partition->Enabled flag

	CREATE_OBJECT(BSDismemberSkinInstance, 0xA6C8A0)
};

ASSERT_SIZE(BSDismemberSkinInstance, 0x40);