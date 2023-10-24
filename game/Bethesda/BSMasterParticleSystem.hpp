#pragma once

#include "NiNode.hpp"
#include "DList.hpp"

NiSmartPointer(BSMasterParticleSystem);

class BSMasterParticleSystem : public NiNode {
public:
	BSMasterParticleSystem();
	~BSMasterParticleSystem();

	DList<UInt32> lEmitterObjList;
	UInt16 wordB8;
	UInt16 usActiveEmitterObjCount;
	UInt16 wordBC;
	UInt32 dwordC0;
	UInt32 dwordC4;
	UInt32 dwordC8;
	NiTPrimitiveArray<NiParticles*> ChildParticles;
	float fMasterPSysTime;

	CREATE_OBJECT(BSMasterParticleSystem, 0xC5E5A0)
};

ASSERT_SIZE(BSMasterParticleSystem, 0xE0)