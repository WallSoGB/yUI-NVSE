#pragma once
#include "TESBoundObject.hpp"
#include "TESModelTextureSwap.hpp"

class TESSound;

// 0x60
class BGSAddonNode :
	public TESBoundObject,
	public TESModelTextureSwap
{
public:
	BGSAddonNode();
	~BGSAddonNode();

	struct ADDON_DATA
	{
		UInt16	usMasterParticleCap;
		char	cFlags;
	};

	UInt32		iIndex;
	TESSound*	pkSound;
	ADDON_DATA	kData;
	UInt32		uiMasterParticleLock;
};
static_assert(sizeof(BGSAddonNode) == 0x60);