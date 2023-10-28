#pragma once

#include "NiTListBase.hpp"
#include "BSRenderPass.hpp"
#include "NiTPointerAllocator.hpp"
#include "NiTPointerListBase.hpp"

class PersistentPassListAllocator : public NiTPointerAllocator<size_t> {
public:
	NiTListItem<BSRenderPass*>* m_pkCurrentItem;
};

class PersistentPassList : public NiTPointerListBase<PersistentPassListAllocator, BSRenderPass*> {
public:
	PersistentPassList();
	virtual ~PersistentPassList();

	void RemoveAll();

	void Render(bool bBlendAlpha);
	void AlphaSort(SInt32(__cdecl* Sort)(BSRenderPass** apPassPtrOne, BSRenderPass** apPassPtrTwo));
	void AddHead(BSRenderPass*& appRenderPass);
	void AddTail(BSRenderPass*& appRenderPass);
};

ASSERT_SIZE(PersistentPassList, 0x14);
