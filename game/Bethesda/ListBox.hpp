#pragma once
#include "BSSimpleList.hpp"
#include "InventoryChanges.hpp"

template <typename Item> struct ListBoxItem
{
	Tile*	pkTile			= nullptr;
	Item* object		= nullptr;
	UInt8 byte08		= 0;
	UInt8 pad09[3];

	ListBoxItem(Item* object, Tile*	pkTile = nullptr) : tile(tile), object(object), pad09{} {}
};

// 0C
template <class Item> 
class ListBoxBase : public BSSimpleList<Item>
{
public:

	virtual bool	SetSelectedTile(Tile*	pkTile) { return false; };
	virtual Tile*	GetSelectedTile() { return nullptr; };
	virtual Tile*	HandleKeyboardInput(KeyboardMenuInputCode code) { return nullptr; };
	virtual bool	IsMenuEqual(Menu* that) { return false; };
	virtual void	ScrollToHighlight() {};
	virtual Tile*	GetTileByIndex(int index, char isNotTileListIndex) { return nullptr; };

	ListBoxBase() { ThisCall(0x7240C0, this); };
};	// 00C
static_assert(sizeof(ListBoxBase<void*>) == 0xC);

// 30
template <typename Item> 
class ListBox : public ListBoxBase<ListBoxItem<Item>*>
{
public:

	ListBox() { ThisCall(0x723750, this); }
	virtual	~ListBox() { ThisCall(0x723820, this); };
	virtual void	FreeAllTiles() {};
	virtual void	Sort(SInt32(__cdecl*)(ListBoxItem<Item>*, ListBoxItem<Item>*)) {};

	enum
	{
		kFlag_RecalculateHeightsOnInsert = 1,
		kFlag_FreeContChangeOnListItemDestruction = 2, // assumes the object is a InventoryChanges - do not set this if the object isn't one...
	};

	Tile*			parentTile;			// 0C
	Tile*			selected;			// 10
	Tile*			scrollBar;			// 14
	const char*		templateName;		// 18
	UInt16			itemCount;			// 1C
	UInt16			pad1E;				// 1E
	Float32			unk20;				// 20
	Float32			storedListIndex;	// 24
	Float32			storedScrollbarPos;	// 28
	UInt16			flags;				// 2C
	UInt16			pad2E;				// 2E

	Tile* GetNthTile(SInt32 index)
	{
		if (index < 0) return this->GetLastItem()->tile;
		for (const auto iter : this)
		{
			if (!index) return iter->tile;
			index--;
		}
		return nullptr;
	}

	void Clear()
	{
		for (const auto iter : this)
		{
			if (iter->tile) iter->tile->Destroy(true);
			GameHeapFree(iter);
		}
		this->RemoveAll();
		selected = nullptr;
		itemCount = 0;
	}

	typedef bool(__cdecl* FilterFunction)(Item* form);
	void Filter(FilterFunction callback) { ThisCall(0x729FE0, this, callback); }

	// identical to Filter, but hooked by InventorySortButton for filtering contchanges
	void FilterAlt(FilterFunction callback) { ThisCall(0x730BB0, this, callback); }

	// Identical to Filter, but passing a value instead of a pointer
	void FilterVal(bool(__cdecl* callback)(Item)) { ThisCall(0x730BB0, this, callback); }

	typedef void(__cdecl* ForEachFunc)(Tile*, Item*);
	void ForEach(ForEachFunc func, int maxIndex1 = -1, int maxIndex2 = 0x7FFFFFFF) { ThisCall(0x7314C0, this, func, maxIndex1, maxIndex2); }

	Tile* GetTileFromItem(Item* item)
	{
		for (const auto iter : this->list) if (iter->object == item) return iter->tile;
		return nullptr;
	}

	Item* GetItemForTile(Tile*	pkTile)
	{
		for (const auto iter : this->list) if (iter->tile == tile) return iter->object;
		return nullptr;
	}

	Item* GetSelected() { return GetItemForTile(selected); }

	bool SetSelected(Tile*	pkTile)
	{
		if (!parentTile) return false;

		if (tile)
		{
			if (!GetItemForTile(tile)) return false;
			if (!(Float32)tile->Get("_enabled")) return false;
		}

		selected = tile;

		ThisCall(0x71A740, this);

		return true;
	}

	void SaveScrollPosition() { ThisCall(0x7312E0, this); }
	int GetNumVisibleItems() { return ThisCall<int>(0x71AE60, this); }
	void RestorePosition(bool playSound = false) { ThisCall(0x731360, this, playSound); }

	typedef SInt32(*SortingFunction)(const ListBoxItem<Item>*, const ListBoxItem<Item>*);

	Tile* Insert(Item* item, const char* text, SortingFunction sortingFunction = nullptr, const char* _templateName = nullptr)
	{
		if (!this->parentTile) return nullptr;
		auto _template = _templateName ? _templateName : this->templateName;
		if (!_template) return nullptr;

		const auto newTile = this->parentTile->AddTileFromTemplate(_template);
		if (!(Float32)newTile->Get(kTileValue_id)) newTile->Set(kTileValue_id, -1);
		if (text) newTile->Set(kTileValue_string, text);

		auto listItem = static_cast<ListBoxItem<Item>*>(GameHeapAlloc(sizeof(ListBoxItem<Item*>)));
		listItem->tile = newTile;
		listItem->object = item;
		listItem->byte08 = 0;
		if (sortingFunction)
		{
			ThisCall(0x7A7EB0, &this->list, listItem, sortingFunction); // InsertSorted
			if (this->flags & kFlag_RecalculateHeightsOnInsert)
			{
				ThisCall(0x71A670, this);
			}
		}
		else
		{
			this->list.Append(listItem);
			if (this->flags & kFlag_RecalculateHeightsOnInsert)
			{
				ThisCall(0x7269D0, this, newTile);
				ThisCall(0x71AD30, this);
			}
			newTile->Set(kTileValue_listindex, this->itemCount++);
		}

		if (this->itemCount == 1)
		{
			const auto numVisibleItemsTrait = Tile::TraitNameToID("_number_of_visible_items");
			if ((Float32)this->parentTile->Get(numVisibleItemsTrait) > 0)
			{
				auto valPtr = ThisCall<Tile::Value*>(0xA00E90, this->parentTile, kTileValue_height);
				ThisCall(0xA09200, valPtr);
				ThisCall(0xA09130, valPtr, 2000, newTile, kTileValue_height);

				Float32 numVisible = this->parentTile->Get(numVisibleItemsTrait);
				ThisCall(0xA09080, valPtr, kTileValue_Mul, numVisible);
				ThisCall(0xA09410, valPtr, 0);
			}
		}

		return newTile;
	}

	ListBoxItem<Item>* InsertAlt(Item* item, const char* text, const char* _templateName = nullptr)
	{
		if (!this->parentTile) return nullptr;
		auto _template = _templateName ? _templateName : this->templateName;
		if (!_template) return nullptr;

		const auto newTile = this->parentTile->AddTileFromTemplate(_template);
		if (!(Float32)newTile->Get(kTileValue_id)) newTile->Set(kTileValue_id, -1);
		if (text) newTile->Set(kTileValue_string, text);

		auto listItem = static_cast<ListBoxItem<Item>*>(GameHeapAlloc(sizeof(ListBoxItem<Item*>)));
		listItem->tile = newTile;
		listItem->object = item;
		listItem->byte08 = 0;

		return listItem;
	}

	void HandleScrollbar()
	{
		if (!parentTile) return;

		const Float32 valueNum = parentTile->Get(kTileValue_height);

		UInt32 items = 1;

		if (unk20 > 0.0 && valueNum > 0.0)
		{
			if (valueNum < unk20)
				items = max(std::ceil(GetNumVisibleItems() * (unk20 - valueNum) / unk20) + 1, 2);

			if (items > 1)
				parentTile->Set("_scroll_delta", std::ceil((unk20 - valueNum) / (items - 1)));
		}

		const Float32 doublestacked = parentTile->Get("_doublestacked");

		if (!scrollBar) return;

		scrollBar->Set("_number_of_items", std::floor(doublestacked ? (items * 0.667) : items));
	}

	void SortAlt(ListBoxItem<Item>* listItem, SortingFunction sortingFunction = nullptr)
	{
		if (sortingFunction)
		{
			ThisCall(0x7A7EB0, &this->list, listItem, sortingFunction); // InsertSorted
			if (this->flags & kFlag_RecalculateHeightsOnInsert) ThisCall(0x71A670, this);
		}
		else
		{
			this->list.Append(listItem);
			if (this->flags & kFlag_RecalculateHeightsOnInsert)
			{
				ThisCall(0x7269D0, this, listItem->tile);
				HandleScrollbar();
			}
			listItem->tile->Set(kTileValue_listindex, this->itemCount++);
		}

		if (this->itemCount == 1)
		{
			const auto numVisibleItemsTrait = Tile::TraitNameToID("_number_of_visible_items");
			if (this->parentTile->Get(numVisibleItemsTrait) > 0)
			{
				auto valPtr = ThisCall<Tile::Value*>(0xA00E90, this->parentTile, kTileValue_height);
				ThisCall(0xA09200, valPtr);
				ThisCall(0xA09130, valPtr, 2000, listItem->tile, kTileValue_height);

				Float32 numVisible = this->parentTile->Get(numVisibleItemsTrait);
				ThisCall(0xA09080, valPtr, kTileValue_Mul, numVisible);
				ThisCall(0xA09410, valPtr, 0);
			}
		}
	}

	Tile* InsertVal(Item item, const char* text, signed int (*sortingFunction)(ListBoxItem<Item>* a1, ListBoxItem<Item>* a2) = nullptr, const char* _templateName = nullptr)
	{
		return ThisCall<Tile*>(0x754690, this, item, text, sortingFunction, _templateName);
	}

	void HighlightLastItem()
	{
		const auto tile = this->GetNthTile(this->itemCount - 1);
		this->SetSelectedTile(tile);
		this->ScrollToHighlight();
	}

	void ScrollToTop()
	{
		this->storedScrollbarPos = 0;
		this->storedListIndex = 0;
		this->RestorePosition();
	}

	void SetParentEnabled(bool isEnabled) const { parentTile->Set("_enabled", isEnabled); }
	bool IsEnabled() const { return parentTile && parentTile->Get("_enabled"); }
	// initialises the fields and appends the menu list to the global listbox array

};
static_assert(sizeof(ListBox<void*>) == 0x30);

class MenuItemEntryList : public ListBox<InventoryEntryData>
{
public:
	void RestoreScrollPositionProxy(Float32 listIndex, Float32 scrollbarPos) { ThisCall(0x7832E0, this, listIndex, scrollbarPos); }
};
