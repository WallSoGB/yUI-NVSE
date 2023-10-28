#pragma once

#include "NiTListBase.hpp"
#include "NiTObjectAllocator.hpp"

// Possibly unused
template <class T_Data>
class NiTObjectList : public NiTListBase <NiTObjectAllocator<T_Data>, T_Data> {
public:
	~NiTObjectList() { RemoveAll(); };

	// 0xB71300
	void RemoveAll() {
		NiTListItem<T_Data>* pkCurr = NiTListBase<NiTObjectAllocator<T_Data>, T_Data>::m_pkHead;
		while (pkCurr)
		{
			NiTListItem<T_Data>* pkDel = pkCurr;
			pkCurr = pkCurr->m_pkNext;
			DeleteItem(pkDel);
		}

		NiTListBase<NiTObjectAllocator<T_Data>, T_Data>::m_kAllocator.m_uiCount = 0;
		NiTListBase<NiTObjectAllocator<T_Data>, T_Data>::m_pkHead = 0;
		NiTListBase<NiTObjectAllocator<T_Data>, T_Data>::m_pkTail = 0;
	};

protected:
	// 0x49FA80
	NiTListItem<T_Data>* NewItem() {
		return (NiTListItem<T_Data>*)NiTListBase<NiTObjectAllocator<T_Data>, T_Data>::m_kAllocator.Allocate();
	};
	// 0xE6E8A0
	void DeleteItem(NiTListItem<T_Data>* pkItem) {
		NiTListBase<NiTObjectAllocator<T_Data>, T_Data>::m_kAllocator.Deallocate(pkItem);
	}
};