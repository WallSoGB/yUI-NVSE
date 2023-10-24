#pragma once

#include "NiTriShape.hpp"
#include "SkyObject.hpp"
#include "NiBillboardNode.hpp"
#include "BSShaderAccumulator.hpp"
#include "NiDirectionalLight.hpp"
#include "SkyShaderProperty.hpp"

class NiPick;

class Sun : public SkyObject {
public:
	NiBillboardNodePtr		spSunBaseNode;
	NiBillboardNodePtr		spSunGlareNode;
	NiTriShapePtr			spSunBase;
	NiTriShapePtr			spSunQuery;
	NiPick*					pSunPick; // Unused
	NiDirectionalLightPtr	spLight;
	float					fGlareScale;
	bool					bDoOcclusionTests;
	BSShaderAccumulatorPtr	spSunAccumulator;

	void StartSunOcclusion() {
		bDoOcclusionTests = true;
		if (spSunAccumulator.m_pObject)
			spSunAccumulator.m_pObject->ResetSunOcclusion();
	}

	void CalculateSunGlare(UInt32 aiTestNumber, BSShaderAccumulator* apAccumulator, NiCamera* apCamera) {
		DWORD uiContext;
		MemoryManager::EnterContext(uiContext, MC_SKY);
		NiTriShape* pSunBase = spSunBase;
		if (pSunBase && bDoOcclusionTests && apAccumulator) {
			spSunAccumulator = apAccumulator;
			pSunBase->m_kWorld.m_fScale /= 25.0f;
			apAccumulator->DoSunOcclusionQuery(pSunBase, aiTestNumber, apCamera);
			pSunBase->m_kWorld.m_fScale *= 25.0f;
		}
		MemoryManager::LeaveContext(uiContext);
	}

	float GetAlphaColor() {
		NiTriShape* pSunQuery = spSunQuery;
		return pSunQuery->GetShadeProperty<SkyShaderProperty>()->kVertexColor.a;
	}
};

ASSERT_SIZE(Sun, 0x2C);