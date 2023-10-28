#pragma once

#include "NiCullingProcess.hpp"
#include "BSShaderAccumulator.hpp"

class BSCullingProcess : public NiCullingProcess {
public:
	BSCullingProcess(NiVisibleArray* apVisibleSet = nullptr);
	~BSCullingProcess() {};

	void Process(NiAVObject* apObject) override;
	void ProcessAlt(const NiCamera* apCamera, NiAVObject* apScene, NiVisibleArray* apVisibleSet) override;
	void AppendVirtual(NiGeometry* apGeom) override;

	enum BSCPCullingType {
		BSCP_CULL_NORMAL = 0x0, // Normal culling
		BSCP_CULL_ALLPASS = 0x1, // Everything is visible, but frustum culling still applies
		BSCP_CULL_ALLFAIL = 0x2, // Everything is culled
		BSCP_CULL_IGNOREMULTIBOUNDS = 0x3, // Doesn't cull using multibounds, frustum still applies
		BSCP_CULL_FORCEMULTIBOUNDSNOUPDATE = 0x4, // Culls, but doesn't save the result
	};

	BSCPCullingType					eCullMode; // Current mode
	BSCPCullingType					eTypeStack[10]; // Stored modes
	UInt32							uiStackIndex; // Current index of the mode stack
	BSCompoundFrustum*				pCompoundFrustum; // Frustum
	NiPointer<BSShaderAccumulator>	spAccumulator; // Current accumulator

	void SetCullMode(BSCPCullingType aeType);
	void PushCullMode(BSCPCullingType aeType);
	void PopCullMode();

	void SetAccumulator(BSShaderAccumulator* pkAccumulator);

	bool AddShared(NiAVObject* apObject);
	void ClearSharedMap();

	static void __fastcall ProcessEx(BSCullingProcess* apThis, void*, NiAVObject* apScene);
	static void __fastcall ProcessAltEx(BSCullingProcess* apThis, void*, const NiCamera* apCamera, NiAVObject* apScene, NiVisibleArray* apVisibleSet);
};
ASSERT_SIZE(BSCullingProcess, 0xC8)