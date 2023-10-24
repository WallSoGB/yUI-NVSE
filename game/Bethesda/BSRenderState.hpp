#pragma once

class BSRenderPass;

enum BSCompareFunctions {
	BSCMP_ALWAYS = 0x0,
	BSCMP_LESS = 0x1,
	BSCMP_EQUAL = 0x2,
	BSCMP_LESSEQUAL = 0x3,
	BSCMP_GREATER = 0x4,
	BSCMP_NOTEQUAL = 0x5,
	BSCMP_GREATEREQUAL = 0x6,
	BSCMP_NEVER = 0x7,
};

enum BSStencilBufferOperations {
	BSSTENCILOP_KEEP = 0x0,
	BSSTENCILOP_ZERO = 0x1,
	BSSTENCILOP_REPLACE = 0x2,
	BSSTENCILOP_INCR = 0x3,
	BSSTENCILOP_DECR = 0x4,
	BSSTENCILOP_INVERT = 0x5,
};

enum RenderStateCounters : UInt32 {
	kZBuffer = 0x0,
	kZWrite = 0x1,
	kZFunc = 0x2,
	kDepthBias = 0x3,
	kAlphaTest = 0x4,
	kAlphaFunc = 0x5,
	kAlphaBlend = 0x6,
	kAlphaBlends = 0x7,
	kBlendOp = 0x8,
	kStencilEnable = 0x9,
	kStencilActions = 0xA,
	kStencilFuncs = 0xB,
	kStencilWrite = 0xC,
	kScissorTest = 0xD,
	kClipPlane = 0xF,
	kColorWrite = 0x10,
	kColorWrite123 = 0x11,
	kFillMode = 0x12,
	kCullMode = 0x13,
	kTMSAA = 0x14,
};


class BSRenderState {
public:
	// TMSAA fixes
	static void InitHooks();
	static void SetVendorFormats();
	static void __cdecl CollectState(UInt32 bEnable, bool abMarkStatus);
	static void SetAlphaAntiAliasing(UInt32 bEnable, UInt32 abMarkStatus, BSRenderPass* pCurrentPass = nullptr);
	static void __cdecl SetAlphaAntiAliasing_Hook(UInt32 bEnable, bool abMarkStatus);
	static void SetAlphaBlendEnable(bool a, bool b);
	static void ResetAlphaBlendEnable(bool abMarkStatus);

	static void SetAlphaFuncAndRef(UInt32 a, UInt32 b, UInt32 c);
	static void SetSrcAndDstBlends(UInt32 a, UInt32 b, UInt32 c);

	static void SetFillMode(UInt32 bEnable, bool abMarkStatus);
	static void ResetFillMode(bool abMarkStatus);

	
	static void SetColorWriteEnable(UInt32 a, bool b);
	static void SetColorWriteEnable7(bool abMarkStatus);


	static void SetScissorTestEnable(bool a, bool b);
	static void SetScissorRectangle(SInt32 left, SInt32 top, SInt32 right, SInt32 bottom);
	static void AdjustScissorRectangle(SInt32 left, SInt32 top, SInt32 right, SInt32 bottom, bool b);
	static void ResetScissorRectangle();

	static void EnableZBuffer(bool abMarkStatus);

	static void EnableZWrite(bool abMarkStatus);
	static void SetZWriteEnable(bool a, bool b);
	static void SetZEnable(D3DZBUFFERTYPE a, bool abMarkStatus);

	static void SetStencilEnable(bool a, bool b);
	static void SetStencils(BSCompareFunctions a1, int a2, DWORD stencilMask, int a4);
	static void SetStencilOperations(BSStencilBufferOperations stencilFail, BSStencilBufferOperations stencilZFail, BSStencilBufferOperations stencilPass, int a4);
	static void SetStencilWriteMask(bool a, bool b);
	static void DisableStencil(bool abMarkStatus);

	static void SetClipPlaneEnable(bool a1, bool a2, bool a3, bool a4, bool a5, bool a6, int a7);
	static void ResetClipPlane(bool abMarkStatus);

	static void AddStatus(RenderStateCounters type, bool abMark);
	static void RemoveStatus(RenderStateCounters type, bool abMark);
	static void DecreaseStatus(RenderStateCounters type);
	static void ResetStatus(RenderStateCounters type);
	static UInt32 GetStatus(RenderStateCounters type);

	static RenderStateCounters GetStateCount(UInt32 type);

	enum ForceState : UInt32 {
		DEFAULT = 0,
		ENABLE = 1,
		DISABLE = 2
	};

	struct SavedStatus {
		bool bEnable;
		bool bMarkStatus;
	};

	static UInt32 uiInternalStatus;
	static SavedStatus currentStatus;
};