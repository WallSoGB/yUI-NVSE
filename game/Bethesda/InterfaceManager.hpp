#pragma once

#include "TESObjectREFR.hpp"
#include "NiTArray.hpp"
#include "Tile.hpp"
#include "BSGraphics.hpp"
#include "Menu.hpp"
#include "FOPipboyManager.hpp"
#include "BSRenderedTexture.hpp"

class TileMenu;
class TileImage;
class SceneGraph;

enum SpecialInputCode : UInt32
{
	kInputCode_Backspace = 0x80000000,
	kInputCode_ArrowLeft = 0x80000001,
	kInputCode_ArrowRight = 0x80000002,
	kInputCode_ArrowUp = 0x80000003,
	kInputCode_ArrowDown = 0x80000004,
	kInputCode_Home = 0x80000005,
	kInputCode_End = 0x80000006,
	kInputCode_Delete = 0x80000007,
	kInputCode_Enter = 0x80000008,
	kInputCode_PageUp = 0x80000009,
	kInputCode_PageDown = 0x8000000A
};

class bhkSimpleShapePhantom;

struct PlayerCameraSphere
{
	bhkSimpleShapePhantom* unk000;
	bhkSimpleShapePhantom* unk004;
};

// 0x580
class InterfaceManager
{
public:
	InterfaceManager();
	~InterfaceManager();

	// 0x178
	struct Struct0178
	{
		UInt32		unk00;
		UInt32		NiTPrimitiveArray[9];
		UInt8		byte28;
		UInt8		byte29;
		UInt8		byte2A;
		UInt8		byte2B;
		UInt32		startTime;
		Float32		durationX;
		Float32		durationY;
		Float32		intensityX;
		Float32		intensityY;
		Float32		frequencyX;
		Float32		frequencyY;
		Float32		unk48;
		Float32		unk4C;
		UInt32		imageSpaceEffectParam;
		UInt8		isFlycamEnabled;
		UInt8		byte55;
		UInt8		byte56;
		UInt8		byte57;
		Float32		fBlurRadiusHUD;
		Float32		fScanlineFrequencyHUD;
		Float32		fBlurIntensityHUD;
	};

	struct RefAndNiNode
	{
		TESObjectREFR*	pRef;
		NiNode*			pNode;
	};

	struct VATSHighlightData {
		enum QueryType
		{
			LIMB_QUERY_NONE = 0x0,
			LIMB_QUERY_FULL = 0x1,
			LIMB_QUERY_PARTIAL = 0x2,
		};

		UInt32			mode;
		RefAndNiNode	target;
		UInt32			numHighlightedRefs;
		UInt32			flashingRefIndex;
		RefAndNiNode	highlightedRefs[32];
		UInt32			unk114;
		bool			bIsOcclusionEnabled;
		bool			unused119[16];
		bool			byte12B;
		BSGraphics::OcclusionQuery* pPartialLimbQuery[16];
		BSGraphics::OcclusionQuery* pEntireLimbQuery[16];
		bool			bHasExecutedQuery[16];
		UInt32			totalArea[16];
		UInt32			visibleArea[16];
		UInt32			selectedLimbID;
		UInt32			numHighlightedBodyParts;
		UInt32			highLightedBodyParts[16];
		bool			byte284;
		Float32			time288;
		Float32			distortVertical;
		UInt32			distortDuration;
		Float32			vatsDistortTime;
		bool			byte298;
		Float32			time29C;
		Float32			burstDuration;
		Float32			burstIntensity2;
		Float32			burstIntensity;
		Float32			pulseIntensity;
		Float32			pulseRadius;
		bool			byte2B4;
		bool			byte2B5;
		Float32			unk2B8;
		Float32			unk2BC;
		Float32			fVATSTargetPulseRate;
		NiRefObject*	unk2C4;
		UInt32			visibleAreaScale_alwaysOne;
		BSShaderAccumulator* spAccumulator;

		static BSRenderedTexture* GetCurrentHighlightedNodeTexture() {
			return (*(BSRenderedTexturePtr*)0x11DEB38);
		}

		static void SetCurrentHighlightedNodeTexture(BSRenderedTexture* apTexture) {
			(*(BSRenderedTexturePtr*)0x11DEB38) = apTexture;
		}

		void HandleOcclusionQueries(BSRenderedTexture* apCurrentNodeTexture, QueryType aeQueryType, bool a4, int a5, NiRenderer::ClearFlags uiClearMode, bool abEndFrame);

		NiNode* GetTargetNode() {
			return target.pNode;
		}

		void AddRef(TESObjectREFR* ref);
		void AddRefAndSetFlashing(TESObjectREFR* ref);
		void ResetRefs();
	};

	struct Tutorials
	{
		SInt32 tutorialFlags[41];
		UInt32 currentShownHelpID;
		UInt32 timeA8;
	};

	struct MenuFade
	{
		Menu*		menu;
		Float32		fadeTimer;
		Float32		fadeDuration;
		MenuFade*	prev;
		MenuFade*	next;
	};

	enum PipboyTabs
	{
		kStats = 1,
		kItems,
		kData
	};

	enum KeyModifier
	{
		kAltHeld = 0x1,
		kControlHeld = 0x2,
		kShiftHeld = 0x4,
	};

	enum Mode
	{
		kGameMode = 1,
		kMenuMode
	};

	enum Helps
	{
		kHelpPipBoyItems = 0x5,
		kHelpPipBoyRepair = 0x6,
		kSPECIAL = 0xC,
		kHelpChargenTagSkills = 0xE,
		kHelpChargenRace = 0xF,
		kHelpLeveling = 0x10,
		kHelpDialogue = 0x11,
		kHelpHacking = 0x13,
		kHelpLockpickingPC = 0x14,
		kHelpVATSPC = 0x15,
		kHelpContainer = 0x16,
		kHelpBarter = 0x17,
		kHelpTerminal = 0x18,
		kHelpPipBoyStats = 0x19,
		kHelpMapMenu = 0x1A,
		kHelpVATSXbox = 0x1B,
		kHelpLockpickingXBox = 0x1C,
		kHelpItemMod = 0x1D,
		kHelpCaravanBetting = 0x1E,
		kHelpCaravanDeckBuilding = 0x1F,
		kHelpCaravanStartingCaravans = 0x20,
		kHelpCaravanContractWar = 0x21,
		kHelpWeapons = 0x22,
		kHelpApparel = 0x23,
		kHelpAmmo = 0x24,
		kHelpAmmoBox = 0x25,
		kHelpCrafting = 0x26,
		kHelpReputation = 0x27,
		kHelpHardcoreNeeds = 0x28,
	};

	UInt32							flags;				// 000
	SceneGraph*						sceneGraph004;		// 004
	SceneGraph*						sceneGraph008;		// 008
	UInt32							currentMode;		// 00C	1 = GameMode; 2 = MenuMode
	// checked for 1 at 0x70BA97
	// set to 2 at 0x70BA8D
	// set to 3 at 0x714E96, 0x714E20 - checked at 0x70B94E
	// set to 4 at 0x714D5D, 0x715177 (CloseAllMenus)
	// set to 5 at 0x70B972 - checked at 0x70BA84, 0x70CA14, 0x70CC7A
	UInt8							byte010;
	UInt8							byte011;
	UInt8							statsMenuTab;
	UInt8							inventoryMenuTab;
	UInt8							byte14;
	UInt8							mapMenuTab;
	UInt8							gap16[2];
	UInt32							pickLength;			// 018
	UInt32							unk01C;				// 01C
	UInt8							byte020;			// 020
	UInt8							byte021;			// 021
	UInt8							byte022;			// 022
	UInt8							byte023;			// 023
	UInt32							unk024;				// 024
	TileImage*						cursor;				// 028
	Float32							flt02C;				// 02C
	Float32							flt030;				// 030
	Float32							flt034;				// 034
	Float32							cursorX;			// 038
	Float32							flt03C;				// 03C
	Float32							cursorY;			// 040
	Float32							mouseWheel;			// 044	-120.0 = down; 120.0 = up
	Float32							timeLeftClickHeld;	// 048 time in menus only
	Tile*							draggedTile;		// 04C
	SInt32							dragStartX;			// 050
	Float32							dragOldX;			// 054
	Float32							dragOldY;			// 058
	SInt32							dragStartY;			// 05C
	Float32							dragNewX;			// 060
	Float32							dragNewY;			// 064
	UInt32							unk068[2];			// 068
	BSSimpleList<TESObjectREFR*>	selectableRefs;		// 070
	UInt32							selectedRefIndex;	// 078
	bool							debugText;			// 07C
	UInt8							isMouseVisible;		// 07D
	UInt8							byte07E;			// 07E
	UInt8							byte07F;			// 07F
	NiNode*							mainRootNode;		// 080
	NiNode*							cursorRootNode;		// 084
	UInt32							unk088;				// 088
	BSShaderAccumulator*			shaderAccum08C;		// 08C
	BSShaderAccumulator*			shaderAccum090;		// 090
	ShadowSceneNode*				shadowScene094;		// 094
	ShadowSceneNode*				shadowScene098;		// 098
	Tile*							menuRoot;			// 09C
	Tile*							globalsTile;		// 0A0	globals.xml
	NiNode*							unk0A4;				// 0A4 saw Tile? seen NiNode
	UInt32							unk0A8;				// 0A8
	NiObject*						unk0AC;				// 0AC seen NiAlphaProperty
	UInt8							byte0B0;
	UInt8							byte0B1;
	UInt16							wrd0B2;
	UInt32							unk0B4;
	Tile*							safeZone;
	Tile*							activeTileAlt;		// 0BC
	UInt32							unk0C0;				// 0C0
	UInt32							unk0C4;				// 0C4
	UInt8							shouldHideAllPipboyMenus;			// 0C8
	UInt8							byte0C9;			// 0C9
	UInt8							byte0CA;			// 0CA
	UInt8							byte0CB;			// 0CB
	Tile*							activeTile;			// 0CC
	Menu*							activeMenu;			// 0D0
	Tile*							tile0D4;			// 0D4
	Menu*							menu0D8;			// 0D8
	UInt8							unk0DC;
	UInt8							IsFullHelp;
	UInt16							unk0DE;
	UInt32							unk0E0;
	SInt8							msgBoxButton;		// 0E4 -1 if no button pressed
	UInt8							byte0E5;			// 0E5
	UInt8							byte0E6;			// 0E6
	UInt8							byte0E7;			// 0E7
	UInt32							unk0E8;				// 0E8
	UInt8							isEmergencyTextureRelease; // 0EC
	UInt8							hasMouseMoved;		// 0ED
	UInt8							byte0EE;			// 0EE
	UInt8							byte0EF;			// 0EF
	TESObjectREFR*					debugSelection;		// 0F0	compared to activated object during Activate
	UInt32							unk0F4;				// 0F4
	UInt32							unk0F8;				// 0F8
	TESObjectREFR*					crosshairRef;		// 0FC
	TESObjectREFR*					telekinesisTarget;
	NiPoint3						pt104;
	UInt8							byte110;			// 
	UInt8							pad111[3];			// 111
	UInt32							menuStack[10];		// 114
	PlayerCameraSphere*				ptr13C;				// 13C ?
	UInt32							unk140;				// 140
	UInt32							unk144;				// 144
	UInt8							byte148;			// 148
	UInt8							isShift;			// 149
	UInt8							byte14A;			// 14A
	UInt8							byte14B;			// 14B
	KeyModifier						keyModifiers;		// 14C
	UInt32							currentKey;			// 150
	UInt32							keyRepeatStartTime;	// 154
	UInt32							lastKeyRepeatTime;	// 158
	SpecialInputCode				currentControllerKey; // 15C
	UInt32							nextControllerRepeatTime; // 160
	MenuFade*						menuFades;			// 164
	UInt8							isRenderedMenuSet;	// 168
	UInt8							gap169[3];			// 169
	FORenderedMenu*					renderedMenu;		// 16C
	UInt8							isMovedMouseInRenderedMenu; // 170
	UInt8							byte171;			// 171
	UInt8							byte172;			// 172
	UInt8							byte173;			// 173
	FOPipboyManager*				pipboyManager;		// 174
	Struct0178						unk178;				// 178
	VATSHighlightData				vatsHighlightData;	// 1DC
	Float32							menuScaledCursorPosX; // 4AC
	Float32							menuScaledCursorPosY; // 4B0
	UInt8							isRenderedMenuOrPipboyManager; // 4B4
	UInt8							byte4B5;			// 4B5
	UInt8							byte4B6;			// 4B6
	UInt8							byte4B7;			// 4B7
	UInt32							queuedPipboyTabToSwitchTo; // 4B8
	UInt32							pipBoyMode;			// 4BC
	void							(*onPipboyOpenCallback)();	// 4C0
	BSSimpleList<UInt32>			list4C4;			// 4C4
	UInt8							isDestroyAllMenus;	// 4CC
	UInt8							preventLevelUpTillContainerOpened;	// 4CD
	UInt8							pad4CE;				// 4CE
	UInt8							pad4CF;				// 4CF
	Float32							fScale4D0;			// 4D0
	Tutorials						help;				// 4D4


	void ClosePipboy();

	static __forceinline InterfaceManager* GetSingleton() { return *(InterfaceManager**)(0x11D8A80); };;
	static __forceinline VATSHighlightData* GetVATSHighlightData() {
		if (!GetSingleton() || !GetSingleton()->flags) return nullptr;
		return &GetSingleton()->vatsHighlightData;
	};

	static __forceinline bool IsDialogMenuOpen() { return *(bool*)0x11D9514; };

	static __forceinline bool GetPipboyModeIs2() {
		return GetSingleton()->pipBoyMode == 2;
	};

	static __forceinline bool GetPipboyModeIs3() {
		return GetSingleton()->pipBoyMode == 3;
	};

	static __forceinline bool IsPipboyMode2or3() {
		if (!GetSingleton() || !GetSingleton()->flags) return false;
		return GetPipboyModeIs2() || GetPipboyModeIs3();
	};

	static __forceinline bool IsRenderedMenuOrPipboyOpen() {
		if (IsPipboyMode2or3()) {
			if(!GetPipboyManager()->bIsInitialized)
				return false;
		}
		return ThisStdCall(0x7079F0, GetSingleton());
	}

	static bool GetIsDebugText() {
		InterfaceManager* interfaceManager = GetSingleton();
		if (!interfaceManager || !&interfaceManager) { return false; }
		return interfaceManager->debugText;
	}

	static bool IsPipBoyOpen() {
		return StdCall<bool>(0x7178A0);
	}

	static FORenderedMenu* GetRenderedMenuOrPipboyManager() {
		InterfaceManager* interfaceManager = GetSingleton();
		if (IsPipBoyOpen()) {
			return interfaceManager->pipboyManager;
		}
		else {
			return interfaceManager->renderedMenu;
		}
	}

	static FOPipboyManager* GetPipboyManager() {
		InterfaceManager* interfaceManager = GetSingleton();
		if (!interfaceManager || !&interfaceManager) { return nullptr; }
		return interfaceManager->pipboyManager;
	}

	static bool	 IsMenuVisible(UInt32 menuType);
	static Menu* GetMenuByType(UInt32 menuType);
	static Menu* TempMenuByType(UInt32 menuType);
	static TileMenu* GetMenuByPath(const char* componentPath, const char** slashPos);
	static Tile::Value* GetMenuComponentValue(const char* componentPath);
	static Tile* GetMenuComponentTile(const char* componentPath);
	static Tile::Value* GetMenuComponentValueAlt(const char* componentPath);

	UInt32						GetTopVisibleMenuID();
	Tile*						GetActiveTile();

	char GetMessageBoxResult()
	{
		auto button = this->msgBoxButton;
		this->msgBoxButton = -1;
		return button;
	};
};
static_assert(sizeof(InterfaceManager) == 0x580);
static_assert(sizeof(InterfaceManager::Struct0178) == 0x64);