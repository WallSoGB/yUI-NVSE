#include <main.h>
#include <Safewrite.hpp>
#include <Gameplay.hpp>
#include <SimpleINILibrary.h>

namespace Fix::DroppedItems
{
	inline int enable = 1;

	BSSimpleList<TESObjectREFR*>* iterDroppedItem;

	TESObjectREFR* __fastcall GetHead(ExtraDataList* extradatalist)
	{
		const auto xDropped = reinterpret_cast<ExtraDroppedItemList*>(extradatalist->GetExtra(BSExtraData::kExtraData_DroppedItemList));
		if (!xDropped) return nullptr;
		iterDroppedItem = xDropped->kDroppedItemList.Head();
		if (!iterDroppedItem) return nullptr;
		return iterDroppedItem->m_item;
	}

	TESObjectREFR* __fastcall GetNext()
	{
		return (iterDroppedItem = iterDroppedItem->m_pkNext) ? iterDroppedItem->m_item : nullptr;
	}

	template <UInt32 retn> __declspec(naked) void HookGetNext()
	{
		static const UInt32 retnAddr = retn;
		static const UInt32 ProcessWeapon = 0x419970;
		static const auto GetNextWeapon = reinterpret_cast<UInt32>(GetNext);
		__asm
		{
			mov eax, [ecx] // dereference
			mov ecx, [eax] // this
			call ProcessWeapon
			call GetNextWeapon
			jmp retnAddr
		}
	}

	void Patch(const bool enable)
	{
		if (enable)
		{
			WriteRelCall(0x75C793, GetHead);
			WriteRelJump(0x75C9AB, HookGetNext<0x75C798>);
		}
		else
		{
			UndoSafeWrite(0x75C793);
			UndoSafeWrite(0x75C9AB);
		}
	}

	extern void Init(CSimpleIni& ini)
	{
		if (g_nvseInterface->isEditor) return;
		enable = ini.GetOrCreate("General", "bFixDroppedItems", 1, "; fix the issue where Container Menu would display only a single dropped item at a time");
		Patch(enable);
	}
}
