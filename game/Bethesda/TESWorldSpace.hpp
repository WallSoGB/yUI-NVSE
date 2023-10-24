#pragma once
#include "TESForm.hpp"
#include "TESTexture.hpp"
#include "TESObjectCELL.hpp"
#include "BSPortalGraph.hpp"
#include "BSSimpleArray.hpp"
#include "BSMap.hpp"

class BGSTerrainManager;
class TESClimate;
class TESImageSpace;
class TESWaterForm;
class BGSMusicType;
class BGSEncounterZone;
class BGSImpactData;
class LODdata;

// 0xEC
class TESWorldSpace : public TESForm, public TESFullName, public TESTexture 
{
public:
	TESWorldSpace();
	~TESWorldSpace();

	struct CoordXY {
		float	X;
		float	Y;
	};

	struct DCoordXY {
		SInt32	X;
		SInt32	Y;
	};

	struct WCoordXY {
		SInt16	X;
		SInt16	Y;
	};

	struct Offset_Data
	{
		UInt32** unk000;	// 000 array of UInt32 stored in OFST record (indexed by relative CellXY).
		CoordXY min;		// 004 NAM0
		CoordXY max;		// 00C NAM9
		UInt32	fileOffset;	// 014 TESWorldSpace file offset in modInfo
	};

	struct MapData
	{
		DCoordXY	usableDimensions;
		WCoordXY	cellNWCoordinates;
		WCoordXY	cellSECoordinates;
	};	// 010

	struct ImpactData {
		typedef BSMap<BGSImpactData*, BGSImpactData*> ImpactImpactMap;
		enum MaterialType
		{
			eMT_Stone = 0,
			eMT_Dirt,
			eMT_Grass,
			eMT_Glass,
			eMT_Metal,
			eMT_Wood,
			eMT_Organic,
			eMT_Cloth,
			eMT_Water,
			eMT_HollowMetal,
			eMT_OrganicBug,
			eMT_OrganicGlow,

			eMT_Max
		};

		ImpactImpactMap	impactImpactMap[eMT_Max];	// 000
		char			footstepMaterials[0x12C];	// 030
	};

	NiTPointerMap<SInt32, TESObjectCELL*>*						pCellMap;			// 030 confirmed
	TESObjectCELL*						pPersistentCell;				// 034 should be the Permanent cell
	UInt32								unk038;				// 038
	BGSTerrainManager*					pTerrainManager;
	TESClimate*							pClimate;
	TESImageSpace*						pImageSpace;
	ImpactData*							pImpactSwap;
	UInt8								cFlags;				// 04C confirmed DATA
	UInt16								sParentUseFlags;		// 04E init'd to FF if has a parent. 5 is use ImageSpace, 4 is use parent climate, 3 is use parent Water, 1 is use parent LOD data, 0 is use parent LAND data
	NiTPointerMap<UInt32, BSSimpleList<TESObjectREFR*>*>					fixedPersistentRefMap;			// 050 confirmed
	BSSimpleList<TESObjectREFR*>		mobilePersistentRefs;				// 060
	NiTMap<UInt32, TESObjectREFR*>*		OverlappedMultiboundMap;
	BSPortalGraphPtr					spPortalGraph;				// 068 confirmed as BSSimpleList
	TESWorldSpace*						pParentWorld;			// 070 confirmed
	TESWaterForm*						pWorldWater;
	TESWaterForm*						pLODWater;
	float								fWaterLODHeight;		// 07C confirmed NAM4
	MapData								mapData;			// 080 confirmed MNAM
	float								fWorldMapScale;		// 090 confirmed ONAM for three floats
	float								fWorldMapCellX;		// 094 confirmed
	float								fWorldMapCellY;		// 098 confirmed
	BGSMusicType*						pMusic;			// 09C confirmed ZNAM
	CoordXY								min;				// 0A0 confirmed NAM0 min of all Offset_Data.min
	CoordXY								max;				// 0A8 confirmed NAM9 max of all Offset_data.max
	NiTMap<TESFile*, TESWorldSpace::Offset_Data*>						offsetMap;			// 0B0 guarded by an isESM
	BSStringT							editorID;				// 0C0
	float								fDefaultLandHeight;	// 0C8 confirmed DNAM for the two
	float								fDefaultWaterHeight;	// 0CC
	BGSEncounterZone*					pEncounterZone;	// 0D0 confirmed
	TESTexture							canopyShadow;		// 0D4 confirmed NNAM
	TESTexture							waterNoiseTexture;	// 0E0 confirmed XNAM

	BGSTerrainManager* GetTerrainManager();
	TESObjectCELL* GetCellAtCoord(SInt32 x, SInt32 y);
	bool GetNoLODWater();
	float GetWaterLODHeight();
	TESWaterForm* GetLODWaterType();
	BSPortalGraph* GetPortalGraph();
};
static_assert(sizeof(TESWorldSpace) == 0xEC);