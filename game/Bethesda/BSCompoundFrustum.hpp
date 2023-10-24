#pragma once

#include "NiFrustumPlanes.hpp"
#include "NiBound.hpp"
#include "BSSimpleArray.hpp"

class NiAVObject;

class BSCompoundFrustum {
public:
	BSCompoundFrustum();
	~BSCompoundFrustum() { ThisStdCall(0xC47770, this); };

	struct FunctionOp {
		SInt32 op;
		SInt32 jp;
		SInt32 jf;
	};

	static BSCompoundFrustum* Create(BSCompoundFrustum* apThis);

	bool bPrethreaded;
	BSSimpleArray<NiFrustumPlanes> kPlanes;
	BSSimpleArray<FunctionOp> kFunctionOperators;
	SInt32 iFreePlane;
	SInt32 iFreeOp;
	SInt32 iFirstOp;
	NiFrustumPlanes kViewFrustum;
	NiPoint3 kViewPosition;
	bool bSkipViewFrustum;

	bool CullCheck(NiBound* apBound, NiFrustumPlanes* apPlanes);
	bool CullCheckAlt(NiBound* apBound, NiFrustumPlanes* apPlanes);
	bool Process(NiAVObject* apObject);
	UInt32* GetActivePlaneState();
	void SetActivePlaneState(UInt32* apState);
	void PrethreadOpList();
};