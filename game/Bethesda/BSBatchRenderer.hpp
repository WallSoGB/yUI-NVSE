#pragma once

#include "NiTMap.hpp"
#include "BSRenderPass.hpp"
#include "BSSimpleList.hpp"
#include "NiObject.hpp"
#include "PersistentPassList.hpp"
#include "NiTPointerList.hpp"
//#include <PerfCounter.hpp> <-- don't have this

class BSShader;
class NiTexture;

class BSBatchRenderer : public NiObject {
public:
	virtual void RegisterPassGeometryGroup(BSRenderPass* apRenderPass, UInt32 auiPassEnum);
	virtual void Unk_24(RenderPassTypes minPass, RenderPassTypes maxPass, bool bBlendAlpha);

	struct GeometryGroup {
		GeometryGroup(RenderPassTypes aeMaxPass);
		~GeometryGroup();

		char ucFlags;
		UInt16 usCount;
		RenderPassTypes eMaxPass;
		BSBatchRenderer* pBatchRenderer;
		PersistentPassList PassList;
		UInt32 unk1C;
		float fDepth;

		void RegisterPass(BSRenderPass* apRenderPass, bool abUnk);
		void Render(bool bBlendAlpha);
		void RemoveAll();
	};

	struct AccumStruct4 {
		PersistentPassList structs[5];
		DWORD dword64;
	};

	enum GroupTypes {
		UNK_0 = 0,
		UNK_1 = 1,
		BLENDED_DECAL_1 = 2,
		BLENDED_DECAL_2 = 3,
		UNK_4 = 4,
		UNK_5 = 5,
		REFRACT_1 = 6,
		UNK_7 = 7,
		REFRACT_2 = 8,
		UNK_9 = 9,
		UNK_10 = 10,
		DEPTH_WORLD = 11,
		DEPTH_PLAYER = 12,
	};

	AccumStruct4*									accumStructures4;
	NiTMap<UInt32, UInt32>							passMap;
	DWORD											uiMaxPass;
	RenderPassTypes									passStart;
	RenderPassTypes									passEnd;
	DWORD*											textureBlendStagesList;
	tList<UInt16>									lCurrentPass;
	UInt32											uiSomeCounter;
	bool											bAutoClearPasses;
	BSBatchRenderer::GeometryGroup*					pGeometryGroupsA[13];
	BSBatchRenderer::GeometryGroup*					pAlphaGroups[2];
	NiTPointerList<BSBatchRenderer::GeometryGroup*> pGroupingAlphasGroup[2];
	BSBatchRenderer::GeometryGroup*					pGeometryGroupsB[2]; // 0 is for facegen stuff? FaceGenAccessory and FaceGenHairHat go there

	static RenderPassTypes uiRenderPassToIgnore;
	static bool bShowOnlySelectedPass;
//	static PerfCounter renderPassImmediatelyCounter; <-- don't have that

	static BSBatchRenderer* Create(UInt32 auiMaxPass, UInt32 aeBatchRendererCreationType);

	static void BeginPass(UInt32 auiPass, BSShader* apShader);
	static void __cdecl RenderPassImmediately(BSRenderPass* apRenderPass, UInt32 auiCurrentPass, bool abTestAlpha, bool abBlendAlpha, bool a4);
	static void RenderPassImmediately_Skinned(BSRenderPass* apRenderPass, bool abTestAlpha, bool abBlendAlpha, bool a4);
	static void RenderPassImmediately_Custom(BSRenderPass* apRenderPass, bool abTestAlpha, bool abBlendAlpha, bool a4);
	static void EndPass();

	void Unk_B9B3D0(BSRenderPass* apPass, UInt32 auiGroup);
	void RegisterGeometryGroupPass(BSRenderPass* apPass, UInt32 aGroup, bool abUnk);
	void SortAlphaPasses(NiCamera* apCamera, bool abSortByClosestPoint);
	static SInt32 __cdecl SortingFunction(BSRenderPass** apPassPtrOne, BSRenderPass** apPassPtrTwo);

	static void __fastcall RegisterPassGeometryGroup_Hook(BSBatchRenderer* apThis, void*, BSRenderPass* apRenderPass, UInt32 auiPassEnum);

	static bool HasPassStarted();
	static void SetHasPassStarted(bool abHasStarted);

	static BSShader* GetLastShader();
	static void SetLastShader(BSShader* apShader);
	static RenderPassTypes GetLastPass();
	static void SetLastPass(UInt32 auiPass);
	static UInt32 GetCurrentPassType();
	static void SetCurrentPassType(UInt32 auiPass);
	static BSRenderPass* GetCurrentPass();
	static void SetCurrentPass(BSRenderPass* apPass);

	static NiTexture* GetStageTexture(UInt32 auiStage);
	static void SetStageTexture(UInt32 auiStage, NiTexture* apTexture);

	void Unk_B99BC0(UInt32 unused);
	void StartGroupingAlphas(NiBound* apBound, bool abZPrePass, NiCamera* apCamera, bool abGetSortByClosestPoint);
};
ASSERT_SIZE(BSBatchRenderer, 0x98);