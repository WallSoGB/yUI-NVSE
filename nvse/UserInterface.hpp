#pragma once
#include <Tile.hpp>
#include <InventoryMenu.hpp>
#include <HUDMainMenu.hpp>
#include <InterfaceManager.hpp>

class MyTile;

template <typename T_Name> class EasyTiles
{
public:

	static const char*			TraitIDToName(const Tile::EnumValue id);	// slow

	__forceinline Tile*			InjectUIXML(const std::filesystem::path& str) { return exists(str) ? Tile::ReadXML(str.generic_string().c_str()) : nullptr; };
	Tile*						InjectUIXML(const std::filesystem::path& xmlPath, bool ignoreUIO);

	Tile*						GetComponent(const std::string& componentPath);

	Tile*								GetParentByID(const UInt32 id)
	{
		CdeclCall(0xA044F0); // enter tile critical section

		Tile*	pkTile = this;
		while (pkTile = pkTile->pkParent)
		{
			if (static_cast<UInt32>(pkTile->Get(Tile::kValue_id)) == id)
			{
				break;
			}
		}

		CdeclCall(0xA04500); // leave tile critical section
		return pkTile;
	}

	MyTile* GetChildAlt(const std::string& childName) const
	{
		bool any = false;
		UInt32 index = 0;
		auto tileName = childName;

		if (childName[0] == '*') any = true;
		if (const auto separator = childName.find_last_of(':')) {
			index = atoi(childName.substr(separator + 1).c_str());
			tileName = childName.substr(0, separator - 1);
		}

		for (auto tile : *(Tile*)this) if ((any || tileName == std::string_view(tile->kName)) && !index--) return reinterpret_cast<MyTile*>(tile);
		return nullptr;
	}

	Tile*								AddTileFromTemplate(const char* templateName, const char* altName = nullptr);
	TileMenu*							GetTileMenu();

	MyTile& operator[](const std::string& path)
	{
		MyTile* tile = reinterpret_cast<MyTile*>(static_cast<T_Name*>(this));
		return *tile->GetChildAlt(path);
	}
	MyTile& operator[](const char* path)
	{
		MyTile* tile = reinterpret_cast<MyTile*>(static_cast<T_Name*>(this));
		return *tile->GetChildAlt(path);
	}

};

class MyTile : public Tile, public EasyTiles<MyTile> {};

template <typename T_Name>
class EasyMenus
{
public:
	MyTile& operator[](const std::string& path)
	{
		MyTile* tile = reinterpret_cast<MyTile*>(static_cast<T_Name*>(this)->pkRootTile);
		return *tile->GetChildAlt(path);
	}
	MyTile& operator[](const char* path)
	{
		MyTile* tile = reinterpret_cast<MyTile*>(static_cast<T_Name*>(this)->pkRootTile);
		return *tile->GetChildAlt(path);
	}
	static T_Name& Get() { return *(T_Name*)T_Name::GetSingleton(); }

};

class MyMenu :			public Menu,			public EasyMenus<MyMenu> {};
class MyInventoryMenu :	public InventoryMenu,	public EasyMenus<MyInventoryMenu> {};
class MyHUDMainMenu :	public HUDMainMenu,		public EasyMenus<MyHUDMainMenu> {};


/*

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
if (iter->tile) iter->tile->~Tile();
GameHeapFree(iter);
}
RemoveAll();
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

auto listItem = static_cast<ListBoxItem<Item>*>(GameHeapAlloc(sizeof(ListBoxItem<Item>)));
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
void RestoreScrollPositionProxy(Float32 listIndex, Float32 scrollbarPos) { ThisCall(0x7832E0, this, listIndex, scrollbarPos); };

ListBox* SetNthFlag(char flags, char value) {}

*/