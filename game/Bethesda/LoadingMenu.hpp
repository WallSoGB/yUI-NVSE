#pragma once
#include "Menu.hpp"

class LoadingMenu : public Menu
{
public:
	LoadingMenu();
	~LoadingMenu();

	struct TileDatas
	{
		UInt32 x;
		UInt32 y;
		UInt32 height;
		UInt32 width;
		UInt32 font;
		UInt8 justify;
	};

	union
	{
		Tile*	pkTile028[38];
		struct
		{
			Tile3D*			loading_nif;
			TileText*		loading_plateno_text2;
			TileText*		loading_info_text;
			TileText*		loading_currobj_text;
			TileText*		loading_stat1_label;
			TileText*		loading_stat1_val;
			TileText*		loading_stat2_label;
			TileText*		loading_stat2_val;
			TileText*		loading_stat3_label;
			TileText*		loading_stat3_val;
			TileImage*		loading_levelprog_meter;
			Tile3D*			loading_pinwheel;
			TileImage*		loading_world_image;
			TileText*		loading_plateno_text1;
			TileText*		loading_currobj_label;
			TileText*		loading_levelprog_label;
			TileRect*		loading_levelprog_rect;
			TileText*		loading_stat_label_rect;
			TileRect*		loading_stat_val_rect;
			TileText*		loading_stat4_label;
			TileText*		loading_stat4_val;
			TileText*		loading_stat5_label;
			TileText*		loading_stat5_val;
			TileText*		loading_stat6_label;
			TileText*		loading_stat6_val;
			TileText*		loading_stat7_label;
			TileText*		loading_stat7_val;
			TileRect*		loading_currobj_rect;
			TileText*		loading_levelprog_curlevel;
			TileText*		loading_levelprog_nextlevel;
			TileText*		loading_levelprog_char_marker;
			TileRect*		loading_stat_rect;
			TileImage*		loading_tile_slide_01;
			TileImage*		loading_tile_slide_02;
			TileText*		hidden_tip_text_01;
			TileText*		tip_text_02;
			TileImage*		tip_matte_01;
			TileImage*		tip_matte_02;
		};
	};
	UInt32					minX;
	UInt32					minY;
	UInt32					maxX;
	UInt32					maxY;
	DList<Tile>				statTiles;
	DList<Tile>				currObjTiles;
	DList<Tile>				levelProgTiles;
	DList<Tile>				hiddenTipTiles;
	DList<Tile>				tipTiles;
	UInt32					miscStatArray[43];
	String					str1B8;
	NiColorA				backgroundColor;
	BSSimpleList<TESLoadScreen>	loadScrList;
	void*					ptr1D8;
	TESLoadScreen*			loadScr1DC;
	UInt32					nextUpdateTime;
	UInt32					time1E4;
	TESWorldSpace*			worldspace;
	UInt32					unk1E8;
	UInt32					unk1EC;
	Sound					sound1F0;
	Sound					sound1FC;
	void*					srcTexture[4];
	UInt32					unk21C;
	UInt16					wrd220;
	UInt16					flags;
	TileDatas				tileDatas[38];
	UInt32					unk5B4;
	UInt32					unk5B8;
	UInt32					unk5BC;

	static LoadingMenu* GetSingleton() { return *reinterpret_cast<LoadingMenu**>(0x11DA0C0); };
};
static_assert(sizeof(LoadingMenu) == 0x5C0);