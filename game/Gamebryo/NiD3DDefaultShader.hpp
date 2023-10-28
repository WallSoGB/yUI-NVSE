#pragma once
#include "NiD3DShader.hpp"
#include "NiDynamicEffectState.hpp"

// 0x5C
class NiD3DDefaultShader : public NiD3DShader {
public:
	enum PassFogStatus {
		NO_FOG = 0x0,
		BLACK_FOG = 0x1,
		STANDARD_FOG = 0x2,
	};

	void*							Unk3C;
	UInt32							m_uiMaxTextureIndex;
	UInt32							m_uiRemainingStages;
	UInt32							m_uiRemainingTextures;
	UInt32							m_uiOldLightingValue;
	PassFogStatus*					m_peFogPassArray;
	UInt32							m_uiFogPassArraySize;
	const NiDynamicEffectState*		m_pkLastState;
};
static_assert(sizeof(NiD3DDefaultShader) == 0x5C);