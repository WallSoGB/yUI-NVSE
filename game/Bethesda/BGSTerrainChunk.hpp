#pragma once

#include "NiGeometry.hpp"
#include "BSMultiBoundNode.hpp"
#include "BSShaderPPLightingProperty.hpp"

struct BGSTerrainNode;
class BGSTerrainChunkLoadTask;

struct BGSTerrainChunk {
	BGSTerrainChunk(BGSTerrainNode* apNode, UInt32 auiLODLevel, SInt16 x, SInt16 y);

	BGSTerrainNode* pNode;
	NiGeometryPtr spLandMesh;
	BSMultiBoundNodePtr spWaterNode;
	BSMultiBoundNodePtr spWaterReflectNode;
	BSMultiBoundNodePtr spMultiBoundNode10;
	BSMultiBoundNodePtr spMultiBoundNode14;
	BSMultiBoundNodePtr spMultiBoundNode18;
	TESObjectREFR* pWaterRef;
	TESObjectREFR* pWaterReflectRef;
	NiPointer<BGSTerrainChunkLoadTask> spChunkLoadTask;
	bool byte028;
	bool bIsInitialized;
	bool bInitializedShaderProperty;
	bool gap02B;
	NiPointer<BSShaderPPLightingProperty> spShaderProperty;

	void InitializeShaderProperty();
	void AttachWaterLOD(bool abForce);
};

ASSERT_SIZE(BGSTerrainChunk, 0x30);