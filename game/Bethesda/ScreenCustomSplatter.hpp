#pragma once

#include "NiNode.hpp"
#include "NiCamera.hpp"

class ScreenCustomSplatter {
public:

	static __forceinline NiNode* GetRootNode() { return *(NiNode**)0x11C7810; };
	
	static __forceinline NiCamera* GetCamera() { return *(NiCamera**)0x11C781C; };

	static __forceinline bool HasNodes() {
		if (!GetRootNode()) return false;
		return GetRootNode()->m_kChildren.m_usESize != 0;
	}
};