#pragma once
#include <Tile.hpp>
#include <InventoryMenu.hpp>
#include <HUDMainMenu.hpp>
//	#include <InterfaceManager.hpp>

class MyTile;

template <typename T_Name> class EasyTiles
{
public:

	static const char*			TraitIDToName(const Tile::EnumValue id);	// slow

	__forceinline Tile*			InjectUIXML(const std::filesystem::path& str) { return exists(str) ? ReadXML(str.generic_string().c_str()) : nullptr; };
	Tile*						InjectUIXML(const std::filesystem::path& xmlPath, bool ignoreUIO);

	Tile*						GetComponent(const std::string& componentPath);

	Tile*								GetParentByID(const UInt32 id)
	{
		CdeclCall(0xA044F0); // enter tile critical section

		Tile*	pkTile = this;
		while (tile = tile->parent)
		{
			if (static_cast<UInt32>(tile->Get(kTileValue_id)) == id)
			{
				break;
			}
		}

		CdeclCall(0xA04500); // leave tile critical section
		return tile;
	}

	Tile*					AddTileFromTemplate(const char* templateName, const char* altName = nullptr);
	TileMenu*							GetTileMenu();

	MyTile& operator[](const std::string& path)
	{
		return *static_cast<T_Name*>(this)->pkRootTile->GetChildAlt(path.c_str());
	}
	MyTile& operator[](const char* path)
	{
		return *static_cast<Tile*>(static_cast<T_Name*>(this)->GetChildAlt(path));
	}

};

class MyTile : public Tile, public EasyTiles<MyTile> {};

template <typename T_Name>
class EasyMenus
{
public:
	MyTile& operator[](const std::string& path)
	{
		return *static_cast<Tile*>(static_cast<T_Name*>(this)->pkRootTile->GetChildAlt(path.c_str()));
	}
	MyTile& operator[](const char* path)
	{
		return *static_cast<Tile*>(static_cast<T_Name*>(this)->pkRootTile->GetChildAlt(path));
	}
	static T_Name& Get() { return *(T_Name*)GetSingleton(); }

};

class MyMenu :			public Menu,			public EasyMenus<MyMenu> {};
class MyInventoryMenu :	public InventoryMenu,	public EasyMenus<MyInventoryMenu> {};
class MyHUDMainMenu :	public HUDMainMenu,		public EasyMenus<MyHUDMainMenu> {};