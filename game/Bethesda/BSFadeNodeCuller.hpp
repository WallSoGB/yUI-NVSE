#pragma once

#include "NiCullingProcess.hpp"

NiRTTIAddress(BSFadeNodeCuller, 0x1201F7C)

class BSFadeNodeCuller : public NiCullingProcess {
public:
	BSFadeNodeCuller() {};
	~BSFadeNodeCuller() {};

	const NiRTTI* GetRTTI() override { return BSFadeNodeCuller__ms_RTTI; };
	void Process(NiAVObject* apObject) override;
	void ProcessAlt(const NiCamera* apCamera, NiAVObject* apScene, NiVisibleArray* apVisibleSet) override;
	void AppendVirtual(NiGeometry* apGeom) override {};
};