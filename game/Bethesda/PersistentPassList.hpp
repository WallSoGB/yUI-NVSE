#pragma once

#include "DList.hpp"
#include "BSRenderPass.hpp"

class PersistentPassList {
public:
	virtual void Destroy(bool bDoFree);

	DListNode<BSRenderPass>* m_pPass[3];
	UInt32 m_uiCount;

	void Render(bool bBlendAlpha);
	void AlphaSort(SInt32(__cdecl* Sort)(BSRenderPass** apPassPtrOne, BSRenderPass** apPassPtrTwo));
	void Unk_B99890(BSRenderPass** appRenderPass);
	void Unk_B99840(BSRenderPass** appRenderPass);
};
