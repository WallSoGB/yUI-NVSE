#pragma once
#include <NiNodes.h>
#include <Types.h>
#include <BSExtraData.h>

enum AnimAction : SInt16
{
	kAnimAction_None = -0x1,
	kAnimAction_Equip_Weapon = 0x0,
	kAnimAction_Unequip_Weapon = 0x1,
	kAnimAction_Attack = 0x2,
	kAnimAction_Attack_Eject = 0x3,
	kAnimAction_Attack_Follow_Through = 0x4,
	kAnimAction_Attack_Throw = 0x5,
	kAnimAction_Attack_Throw_Attach = 0x6,
	kAnimAction_Block = 0x7,
	kAnimAction_Recoil = 0x8,
	kAnimAction_Reload = 0x9,
	kAnimAction_Stagger = 0xA,
	kAnimAction_Dodge = 0xB,
	kAnimAction_Wait_For_Lower_Body_Anim = 0xC,
	kAnimAction_Wait_For_Special_Idle = 0xD,
	kAnimAction_Force_Script_Anim = 0xE,
	kAnimAction_ReloadLoopStart = 0xF,
	kAnimAction_ReloadLoopEnd = 0x10,
	kAnimAction_ReloadLoop = 0x11,
};


// Straight from OBSE. Needs to be debugged ! ! ! 
// This is used all over the game code to manage actors and occassionally other objects.
class ActorProcessLists
{
public:
	ActorProcessLists();
	~ActorProcessLists();

	struct ActorList {
		TList<Actor>			head;
		TList<Actor>::Node*		tail;
	};

	ActorList				middleHighActors;		// 00
	ActorList				lowActors0C;			// 0C significantly smaller list than lowActors18. 
													//	  Plausible: actors currently scheduled for low processing
	ActorList				lowActors18;			// 18
	float					unk24;					// 24
	UInt32					unk28;					// 28
	void*					unk2C;					// 2C
	UInt32					unk30;					// 30
	void*					unk34;					// 34
	UInt32					unk38[0x0A];			// 38
	// almost confirmed to be at index 60
	TList<BSTempEffect>		tempEffects;			// 60
	// needs recalc of offsets
	UInt32					unk4C[4];				// 4C
	TList<Actor>			highActors;				// 5C
	Actor*					actor64;				// 64
	TList<Actor>::Node*		unkNodes[3];			// 68 ##TODO: which lists do these belong to
	UInt32					unk74;					// 74 Possibly not a member. Definitely no more members following this.
};

extern ActorProcessLists * g_actorProcessLists;

class AmmoInfo : public InventoryChanges
{
public:
	UInt32			unk0C;	// 0C
	UInt32			unk10;	// 10
	UInt32			unk14;	// 14
	UInt32			unk18;	// 18
	UInt32			unk1C;	// 1C
	UInt32			unk20;	// 20
	UInt32			unk24;	// 24
	UInt32			unk28;	// 28
	UInt32			unk2C;	// 2C
	UInt32			unk30;	// 30
	UInt32			unk34;	// 34
	UInt32			unk38;	// 38
	UInt32			unk3C;	// 3C
	UInt32			unk40;	// 40
	TESObjectWEAP*	ammoWeapon;	// 44
};

struct PackageInfo
{
	TESPackage*			package;		// 00
	union								// 04
	{
		TESPackageData* packageData;
		void*			actorPkgData;
	};
	TESObjectREFR*		targetRef;		// 08
	UInt32				unk0C;			// 0C	Initialized to 0FFFFFFFFh, set to 0 on start
	float				unk10;			// 10	Initialized to -1.0	. Set to GameHour on start so some time
	UInt32				flags;			// 14	Flags, bit0 would be not created and initialized
};


class AnimSequenceBase
{
public:
	virtual void Destroy(bool doFree);
	virtual void AddAnimGroupSequence(BSAnimGroupSequence* sequence, int unused);
	virtual bool RemoveAnimGroupSequence(BSAnimGroupSequence* sequence, int unused);
	virtual bool IsSingle();
	virtual BSAnimGroupSequence* GetSequenceByIndex(int index);
	virtual BSAnimGroupSequence* GetSequenceByAnimGroup(TESAnimGroup* group);
	virtual signed int GetIndexOfSequenceName(const char* name);
};

class AnimSequenceSingle : public AnimSequenceBase
{
public:
	BSAnimGroupSequence* anim;
};

// 08
class AnimSequenceMultiple : public AnimSequenceBase
{
public:
	DList<BSAnimGroupSequence>* anims; // 04
};



enum Coords
{
	kCoords_X = 0,	// 00
	kCoords_Y,		// 01
	kCoords_Z,		// 02
	kCoords_Max		// 03
};

struct NavMeshVertex
{
	float coords[kCoords_Max];	// 000
};	// 00C

enum Vertices
{
	kVertices_0 = 0,	// 00
	kVertices_1,		// 01
	kVertices_2,		// 02
	kVertices_Max		// 03
};

enum Sides
{
	kSides_0_1 = 0,	// 00
	kSides_1_2,		// 01
	kSides_2_0,		// 02
	kSides_Max		// 03
};

struct NavMeshTriangle
{
	SInt16	verticesIndex[kVertices_Max];	// 000
	SInt16	sides[kSides_Max];				// 006
	UInt32	flags;							// 00C
};	// Alloc'd by 0x10

struct NavMeshInfo;

struct EdgeExtraInfo
{
	struct Connection
	{
		NavMeshInfo* navMeshInfo;
		SInt16			triangle;
	};

	UInt32	unk000;			// 00
	Connection connectTo;	// 04
};	// Alloc'd by 0x0C

struct NavMeshTriangleDoorPortal
{
	TESObjectREFR* door;	// 00
	UInt16			unk004;	// 04
	UInt16			pad006;	// 06
};	// Alloc'd to 0x08

struct NavMeshCloseDoorInfo
{
	UInt32	unk000;	// 00
	UInt32	unk004;	// 04
};	// Alloc'd to 0x08

struct NavMeshPOVData;
class ObstacleData;
struct ObstacleUndoData;

struct NavMeshStaticAvoidNode
{
	UInt32	unk000;	// 00
	UInt32	unk004;	// 04
	UInt32	unk008;	// 08
	UInt32	unk00C;	// 0C
	UInt32	unk010;	// 10
	UInt32	unk014;	// 14
	UInt32	unk018;	// 18
	UInt32	unk01C;	// 1C
	UInt32	unk020;	// 20
	UInt32	unk024;	// 24
};	// Alloc'd to 0x28

class ScrapHeapQueue
{
public:
	struct QueuedCmdCall
	{
		UInt32			opcode;		// 00
		void* cmdAddr;	// 04
		UInt32			thisObj;	// 08	refID
		UInt32			numArgs;	// 0C
		FunctionArg		args[4];	// 10

		QueuedCmdCall(void* _cmdAddr, UInt32 _thisObj, UInt8 _numArgs) : opcode(0x2B), cmdAddr(_cmdAddr),
			thisObj(_thisObj), numArgs(_numArgs), args{}
		{
		}
	};

	static ScrapHeapQueue* GetSingleton() { return *reinterpret_cast<ScrapHeapQueue**>(0x11DF1A8); }
	__forceinline void			AddQueuedCmdCall(QueuedCmdCall qCall) { ThisCall(0x87D160, this, &qCall); }
};

inline const UInt32* g_TlsIndexPtr = reinterpret_cast<UInt32*>(0x0126FD98);

struct TLSData
{
	// thread local storage

	UInt32			pad000[(0x260 - 0x000) >> 2];	// 000
	NiNode* lastNiNode;						// 260	248 in FOSE
	TESObjectREFR* lastNiNodeREFR;					// 264	24C in FOSE
	UInt8			consoleMode;					// 268
	UInt8			pad269[3];						// 269
	// 25C is used as do not head track the player , 
	// 2B8 is used to init QueudFile::unk0018, 
	// 28C might count the recursive calls to Activate, limited to 5.
};


static TLSData* GetTLSData()
{
	UInt32 TlsIndex = *g_TlsIndexPtr;
	TLSData* data = nullptr;

	__asm {
		mov		ecx, [TlsIndex]
		mov		edx, fs: [2Ch]	// linear address of thread local storage array
		mov		eax, [edx + ecx * 4]
		mov[data], eax
	}

	return data;
}

#pragma once
#include <Containers.h>
#include <Utilities.h>
#include <Sound.h>
#include <InventoryChanges.h>

/*    Class							     vtbl	  Type  Size
 *   ----------------------------		------		--  --
 *	ExtraAction                        ????????		0E	14
 *	ExtraActivateLoopSound             ????????		87	18
 *	ExtraActivateRef                   ????????		53	18
 *	ExtraActivateRefChildren           ????????		54	18
 *	ExtraAmmo                          ????????		6E	14
 *	ExtraAnim                          ????????		10	10
 *	ExtraAshPileRef                    ????????		89	10
 *	ExtraCannotWear                    ????????		3E	0C	// no data
 *	ExtraCell3D                        ????????		2	10
 *	ExtraCellAcousticSpace             ????????		81	10
 *	ExtraCellCanopyShadowMask          ????????		0A	1C
 *	ExtraCellClimate                   ????????		8	10
 *	ExtraCellImageSpace                ????????		59	10
 *	ExtraCellMusicType                 ????????		7	10
 *	ExtraCellWaterType                 ????????		3	10
 *	ExtraCharge                        ????????		28	10
 *	ExtraCollisionData                 ????????		72	10
 *	ExtraCombatStyle                   ????????		69	10
 *	ExtraContainerChanges              ????????		15	10
 *	ExtraCount                         ????????		24	10
 *	ExtraCreatureAwakeSound            ????????		7D	18
 *	ExtraCreatureMovementSound         ????????		8A	18
 *	ExtraDecalRefs                     ????????		57	14
 *	ExtraDetachTime                    ????????		0B	10
 *	ExtraDismemberedLimbs              ????????		5F	30
 *	ExtraDistantData                   ????????		13	18
 *	ExtraDroppedItemList               ????????		3A	14
 *	ExtraEditorRefMovedData            ????????		4C	30
 *	ExtraEmittanceSource               ????????		67	10
 *	ExtraEnableStateChildren           ????????		38	14
 *	ExtraEnableStateParent             ????????		37	14
 *	ExtraEncounterZone                 ????????		74	10
 *	ExtraFactionChanges                ????????		5E	10
 *	ExtraFollower                      ????????		1D	10
 *	ExtraFollowerSwimBreadcrumbs       ????????		8B	28
 *	ExtraFriendHits                    ????????		45	1C
 *	ExtraGhost                         ????????		1F	0C	// no data
 *	ExtraGlobal                        ????????		22	10
 *	ExtraGuardedRefData                ????????		7C	1C
 *	ExtraHasNoRumors                   ????????		4E	10
 *	ExtraHavok                         ????????		1	14
 *	ExtraHeadingTarget                 ????????		46	10
 *	ExtraHealth                        ????????		25	10
 *	ExtraHealthPerc                    ????????		7A	10
 *	ExtraHotkey                        ????????		4A	10
 *	ExtraIgnoredBySandbox              ????????		80	0C	// no data
 *	ExtraInfoGeneralTopic              ????????		4D	10
 *	ExtraItemDropper                   ????????		39	10
 *	ExtraLastFinishedSequence          ????????		41	10
 *	ExtraLevCreaModifier               ????????		1E	10
 *	ExtraLeveledCreature               ????????		2E	14
 *	ExtraLeveledItem                   ????????		2F	14
 *	ExtraLight                         ????????		29	10
 *	ExtraLinkedRef                     ????????		51	10
 *	ExtraLinkedRefChildren             ????????		52	14
 *	ExtraLitWaterRefs                  ????????		85	14
 *	ExtraLock                          ????????		2A	10
 *	ExtraMapMarker                     ????????		2C	10
 *	ExtraMerchantContainer             ????????		3C	10
 *	ExtraModelSwap                     ????????		5B	14
 *	ExtraMultiBound                    ????????		61	10
 *	ExtraMultiBoundData                ????????		62	10
 *	ExtraMultiBoundRef                 ????????		63	10
 *	ExtraNavMeshPortal                 ????????		5A	14
 *	ExtraNorthRotation                 ????????		43	10
 *	ExtraObjectHealth                  ????????		56	10
 *	ExtraOcclusionPlane                ????????		71	10
 *	ExtraOcclusionPlaneRefData         ????????		76	10
 *	ExtraOpenCloseActivateRef          ????????		6C	10
 *	ExtraOriginalReference             ????????		20	10
 *	ExtraOwnership                     ????????		21	10
 *	ExtraPackage                       ????????		19	1C
 *	ExtraPackageData                   ????????		70	10
 *	ExtraPackageStartLocation          ????????		18	1C
 *	ExtraPatrolRefData                 ????????		6F	10
 *	ExtraPatrolRefInUseData            ????????		88	10
 *	ExtraPersistentCell                ????????		0C	10
 *	ExtraPlayerCrimeList               ????????		35	10
 *	ExtraPoison                        ????????		3F	10
 *	ExtraPortal                        ????????		78	10
 *	ExtraPortalRefData                 ????????		77	10
 *	ExtraPrimitive                     ????????		6B	10
 *	ExtraProcessMiddleLow              ????????		9	10
 *	ExtraRadiation                     ????????		5D	10
 *	ExtraRadioData                     ????????		68	1C
 *	ExtraRadius                        ????????		5C	10
 *	ExtraRagdollData                   ????????		14	10
 *	ExtraRandomTeleportMarker          ????????		3B	10
 *	ExtraRank                          ????????		23	10
 *	ExtraReferencePointer              ????????		1C	10
 *	ExtraReflectedRefs                 ????????		65	14
 *	ExtraReflectorRefs                 ????????		66	14
 *	ExtraRefractionProperty            ????????		48	10
 *	ExtraRegionList                    ????????		4	10
 *	ExtraReservedMarkers               ????????		82	10
 *	ExtraRoom                          ????????		79	10
 *	ExtraRoomRefData                   ????????		7B	10
 *	ExtraRunOncePacks                  ????????		1B	10
 *	ExtraSavedAnimation                ????????		42	10
 *	ExtraSavedHavokData                ????????		3D	10
 *	ExtraSayToTopicInfo                ????????		75	18
 *	ExtraSayTopicInfoOnceADay          ????????		73	10
 *	ExtraScale                         ????????		30	10
 *	ExtraScript                        ????????		0D	14
 *	ExtraSeed                          ????????		31	10
 *	ExtraSeenData                      ????????		5	24	: ExtraIntSeenData is also 5 but 2C
 *	ExtraSound                         ????????		4F	18
 *	ExtraStartingPosition              ????????		0F	24
 *	ExtraStartingWorldOrCell           ????????		49	10
 *	ExtraTalkingActor                  ????????		55	10
 *	ExtraTeleport                      ????????		2B	10
 *	ExtraTerminalState                 ????????		50	10
 *	ExtraTimeLeft                      ????????		27	10
 *	ExtraTrespassPackage               ????????		1A	10
 *	ExtraUsedMarkers                   ????????		12	10
 *	ExtraUses                          ????????		26	10
 *	ExtraWaterLightRefs                ????????		84	14
 *	ExtraWaterZoneMap                  ????????		7E	20
 *	ExtraWeaponAttackSound             ????????		86	18
 *	ExtraWeaponIdleSound               ????????		83	18
 *	ExtraWeaponModFlags                ????????		8D	10
 *	ExtraWorn                          ????????		16	0C	// no data
 *	ExtraWornLeft                      ????????		17	0C	// no data
 *	ExtraXTarget                       ????????		44	10
 */

 /* BaseExtraList methods:
	 AddExtra		0x0040A180
	 GetByType		0x0040A320, pass typeID
	 ItemsInList		0x0040A130
	 RemoveExtra		0x0040A250

   ExtraDataList methods:
	 DuplicateExtraListForContainer	0x0041B090
 */

#define				GetByTypeCast(xDataList, Type) DYNAMIC_CAST(xDataList.GetByType(kExtraData_ ## Type), BSExtraData, Extra ## Type)
extern const char*	GetExtraDataName(UInt8 ExtraDataType);
SInt32				GetCountForExtraDataList(ExtraDataList* list);


FactionListData* GetExtraFactionList(BaseExtraList& xDataList);
SInt8									GetExtraFactionRank(BaseExtraList& xDataList, TESFaction* faction);
void									SetExtraFactionRank(BaseExtraList& xDataList, TESFaction* faction, SInt8 rank);

#pragma once

#include <unordered_map>
#include <vector>

// for IsInventoryObjectType list, see GameForms.h

enum ParamType
{
	kParamType_String =					0x00,
	kParamType_Integer =				0x01,
	kParamType_Float =					0x02,
	kParamType_ObjectID =				0x03,	// GetItemCount				TESForm *, must pass IsInventoryObjectType and TESForm::Unk_3A
	kParamType_ObjectRef =				0x04,	// Activate					TESObjectREFR *, REFR-PFLA
	kParamType_ActorValue =				0x05,	// ModActorValue			UInt32 *, immediate UInt16
	kParamType_Actor =					0x06,	// ToggleAI					TESObjectREFR *, must pass IsActor (ACHR-ACRE)
	kParamType_SpellItem =				0x07,	// AddSpell					TESForm *, must be either SpellItem or book
	kParamType_Axis =					0x08,	// Rotate					char *, immediate char, X Y Z
	kParamType_Cell =					0x09,	// GetInCell				TESObjectCELL *, must be cell
	kParamType_AnimationGroup =			0x0A,	// PlayGroup				UInt32 *, immediate UInt16
	kParamType_MagicItem =				0x0B,	// Cast						MagicItem *
	kParamType_Sound =					0x0C,	// Sound					TESForm *, kFormType_Sound
	kParamType_Topic =					0x0D,	// Say						TESForm *, kFormType_Dialog
	kParamType_Quest =					0x0E,	// ShowQuestVars			TESForm *, kFormType_Quest
	kParamType_Race =					0x0F,	// GetIsRace				TESForm *, kFormType_Race
	kParamType_Class =					0x10,	// GetIsClass				TESForm *, kFormType_Class
	kParamType_Faction =				0x11,	// Faction					TESForm *, kFormType_Faction
	kParamType_Sex =					0x12,	// GetIsSex					UInt32 *, immediate UInt16
	kParamType_Global =					0x13,	// GetGlobalValue			TESForm *, kFormType_Global
	kParamType_Furniture =				0x14,	// IsCurrentFurnitureObj	TESForm *, kFormType_Furniture or kFormType_ListForm
	kParamType_TESObject =				0x15,	// PlaceAtMe				TESObject *, must pass TESForm::Unk_3A
	kParamType_VariableName =			0x16,	// GetQuestVariable			only works in conditionals
	kParamType_QuestStage =				0x17,	// SetStage					handled like integer
	kParamType_MapMarker =				0x18,	// ShowMap					TESObjectREFR *, see ObjectRef
	kParamType_ActorBase =				0x19,	// SetEssential				TESActorBase * (NPC / creature)
	kParamType_Container =				0x1A,	// RemoveMe					TESObjectREFR *, see ObjectRef
	kParamType_WorldSpace =				0x1B,	// CenterOnWorld			TESWorldSpace *, kFormType_WorldSpace
	kParamType_CrimeType =				0x1C,	// GetCrimeKnown			UInt32 *, immediate UInt16
	kParamType_AIPackage =				0x1D,	// GetIsCurrentPackage		TESPackage *, kFormType_Package
	kParamType_CombatStyle =			0x1E,	// SetCombatStyle			TESCombatStyle *, kFormType_CombatStyle
	kParamType_MagicEffect =			0x1F,	// HasMagicEffect			EffectSetting *
	kParamType_FormType =				0x20,	// GetIsUsedItemType		UInt8 *, immediate UInt16
	kParamType_WeatherID =				0x21,	// GetIsCurrentWeather		TESForm *, kFormType_Weather
	kParamType_NPC =					0x22,	// unused					TESNPC *, kFormType_NPC
	kParamType_Owner =					0x23,	// IsOwner					TESForm *, kFormType_NPC or kFormType_Faction
	kParamType_EffectShader =			0x24,	// PlayMagicShaderVisuals	TESForm *, kFormType_EffectShader
	kParamType_FormList	=				0x25,	// IsInList					kFormType_ListForm
	kParamType_MenuIcon =				0x26,	// unused					kFormType_MenuIcon
	kParamType_Perk =					0x27,	// Add Perk					kFormType_Perk
	kParamType_Note =					0x28,	// Add Note					kFormType_Note
	kParamType_MiscellaneousStat =		0x29,	// ModPCMiscStat			UInt32 *, immediate UInt16
	kParamType_ImageSpaceModifier =		0x2A,	//							kFormType_ImageSpaceModifier
	kParamType_ImageSpace =				0x2B,	//							kFormType_ImageSpace
	kParamType_Double =					0x2C,	// 
	kParamType_ScriptVariable =			0x2D,	// 
	kParamType_Unhandled2E =			0x2E,	// 
	kParamType_EncounterZone =			0x2F,	//							kFormType_EncounterZone
	kParamType_Unhandled30 =			0x30,	// 
	kParamType_Message =				0x31,	//							kFormType_Message
	kParamType_InvObjOrFormList =		0x32,	// AddItem					IsInventoryObjectType or kFormType_ListForm
	kParamType_Alignment =				0x33,	// GetIsAlignment			UInt32 *, immediate UInt16
	kParamType_EquipType =				0x34,	// GetIsUsedEquipType		UInt32 *, immediate UInt16
	kParamType_NonFormList =			0x35,	// GetIsUsedItem			TESForm::Unk_3A and not kFormType_ListForm
	kParamType_SoundFile =				0x36,	// PlayMusic				kFormType_SoundFile
	kParamType_CriticalStage =			0x37,	// SetCriticalStage			UInt32 *, immediate UInt16

	// added for dlc (1.1)
	kParamType_LeveledOrBaseChar =		0x38,	// AddNPCToLeveledList		NPC / LeveledCharacter
	kParamType_LeveledOrBaseCreature =	0x39,	// AddCreatureToLeveledList	Creature / LeveledCreature
	kParamType_LeveledChar =			0x3A,	// AddNPCToLeveledList		kFormType_LeveledCharacter
	kParamType_LeveledCreature =		0x3B,	// AddCreatureToLeveledList	kFormType_LeveledCreature
	kParamType_LeveledItem =			0x3C,	// AddItemToLeveledList		kFormType_LeveledItem
	kParamType_AnyForm =				0x3D,	// AddFormToFormList		any form

	// new vegas
	kParamType_Reputation =				0x3E,	//							kFormType_Reputation
	kParamType_Casino =					0x3F,	//							kFormType_Casino
	kParamType_CasinoChip =				0x40,	//							kFormType_CasinoChip
	kParamType_Challenge =				0x41,	//							kFormType_Challenge
	kParamType_CaravanMoney =			0x42,	//							kFormType_CaravanMoney
	kParamType_CaravanCard =			0x43,	//							kFormType_CaravanCard
	kParamType_CaravanDeck =			0x44,	//							kFormType_CaravanDeck
	kParamType_Region =					0x45,	//							kFormType_Region

	// custom NVSE types
	kParamType_StringVar =			0x01,
	kParamType_Array =				0x100,	// only usable with compiler override; StandardCompile() will report unrecognized param type
};

enum CommandReturnType : UInt8
{
	kRetnType_Default,
	kRetnType_Form,
	kRetnType_String,
	kRetnType_Array,
	kRetnType_ArrayIndex,
	kRetnType_Ambiguous,

	kRetnType_Max
};

struct ParamInfo
{
	const char	* typeStr;
	UInt32		typeID;		// ParamType
	UInt32		isOptional;	// do other bits do things?
};

#define COMMAND_ARGS		ParamInfo * paramInfo, void * scriptData, TESObjectREFR * thisObj, TESObjectREFR * containingObj, Script * scriptObj, ScriptEventList * eventList, double * result, UInt32 * opcodeOffsetPtr
#define PASS_COMMAND_ARGS	paramInfo, scriptData, thisObj, containingObj, scriptObj, eventList, result, opcodeOffsetPtr
#define EXTRACT_ARGS		paramInfo, scriptData, opcodeOffsetPtr, thisObj, containingObj, scriptObj, eventList
#define COMMAND_ARGS_EVAL	TESObjectREFR * thisObj, void * arg1, void * arg2, double * result
#define PASS_CMD_ARGS_EVAL	thisObj, arg1, arg2, result
#define COMMAND_ARGS_EX		ParamInfo *paramInfo, void *scriptData, UInt32 *opcodeOffsetPtr, Script *scriptObj, ScriptEventList *eventList
#define EXTRACT_ARGS_EX		paramInfo, scriptData, opcodeOffsetPtr, scriptObj, eventList
#define PASS_FMTSTR_ARGS	paramInfo, scriptData, opcodeOffsetPtr, scriptObj, eventList

//Macro to make CommandInfo definitions a bit less tedious

#define DEFINE_CMD_FULL(name, altName, description, refRequired, numParams, paramInfo, parser) \
	extern bool Cmd_ ## name ## _Execute(COMMAND_ARGS); \
	static CommandInfo (kCommandInfo_ ## name) = { \
	#name, \
	#altName, \
	0, \
	#description, \
	refRequired, \
	numParams, \
	paramInfo, \
	HANDLER(Cmd_ ## name ## _Execute), \
	parser, \
	NULL, \
	0 \
	};

#define DEFINE_CMD_ALT(name, altName, description, refRequired, numParams, paramInfo) \
	DEFINE_CMD_FULL(name, altName, description, refRequired, numParams, paramInfo, Cmd_Default_Parse)	

#define DEFINE_CMD_ALT_EXP(name, altName, description, refRequired, paramInfo) \
	DEFINE_CMD_FULL(name, altName, description, refRequired, (sizeof(paramInfo) / sizeof(ParamInfo)), paramInfo, Cmd_Expression_Parse)	

#define DEFINE_COMMAND(name, description, refRequired, numParams, paramInfo) \
	DEFINE_CMD_FULL(name, , description, refRequired, numParams, paramInfo, Cmd_Default_Parse)	

#define DEFINE_CMD(name, description, refRequired, paramInfo) \
	DEFINE_COMMAND(name, description, refRequired, (sizeof(paramInfo) / sizeof(ParamInfo)), paramInfo)

#define DEFINE_COMMAND_EXP(name, description, refRequired, paramInfo) \
	DEFINE_CMD_ALT_EXP(name, , description, refRequired, paramInfo)	

#define DEFINE_COMMAND_PLUGIN(name, description, refRequired, numParams, paramInfo) \
	DEFINE_CMD_FULL(name, , description, refRequired, numParams, paramInfo, NULL)

#define DEFINE_COMMAND_ALT_PLUGIN(name, altName, description, refRequired, numParams, paramInfo) \
	DEFINE_CMD_FULL(name, altName, description, refRequired, numParams, paramInfo, NULL)

// for commands which can be used as conditionals
#define DEFINE_CMD_ALT_COND_ANY(name, altName, description, refRequired, paramInfo, parser) \
	extern bool Cmd_ ## name ## _Execute(COMMAND_ARGS); \
	extern bool Cmd_ ## name ## _Eval(COMMAND_ARGS_EVAL); \
	static CommandInfo (kCommandInfo_ ## name) = { \
	#name,	\
	#altName,		\
	0,		\
	#description,	\
	refRequired,	\
	(sizeof(paramInfo) / sizeof(ParamInfo)),	\
	paramInfo,	\
	HANDLER(Cmd_ ## name ## _Execute),	\
	parser,	\
	HANDLER_EVAL(Cmd_ ## name ## _Eval),	\
	1	\
	};

#define DEFINE_CMD_ALT_COND(name, altName, description, refRequired, paramInfo) \
	DEFINE_CMD_ALT_COND_ANY(name, altName, description, refRequired, paramInfo, Cmd_Default_Parse)

#define DEFINE_CMD_ALT_COND_PLUGIN(name, altName, description, refRequired, paramInfo) \
	DEFINE_CMD_ALT_COND_ANY(name, altName, description, refRequired, paramInfo, NULL)

#define DEFINE_CMD_COND(name, description, refRequired, paramInfo) \
	DEFINE_CMD_ALT_COND(name, , description, refRequired, paramInfo)

typedef bool (* Cmd_Execute)(COMMAND_ARGS);
typedef bool (* Cmd_Parse)(UInt32 numParams, ParamInfo * paramInfo, ScriptLineBuffer * lineBuf, ScriptBuffer * scriptBuf);
typedef bool (* Cmd_Eval)(COMMAND_ARGS_EVAL);

#define HANDLER(x)	x
#define HANDLER_EVAL(x)	x

struct CommandInfo
{
	const char*	longName;		// 00
	const char*	shortName;		// 04
	UInt32		opcode;			// 08
	const char*	helpText;		// 0C
	UInt16		needsParent;	// 10
	UInt16		numParams;		// 12
	ParamInfo*	params;			// 14

	// handlers
	Cmd_Execute	execute;		// 18
	Cmd_Parse	parse;			// 1C
	Cmd_Eval	eval;			// 20

	UInt32		flags;			// 24		might be more than one field (reference to 25 as a byte)

	void	DumpFunctionDef() const;
	void	DumpDocs() const;
};

enum NVSEOpcodes
{
	kNVSEOpcodeStart = 0x1400,
	kNVSEOpcodeTest = 0x2000
};

struct CommandMetadata
{
	CommandMetadata() :parentPlugin(kNVSEOpcodeStart), returnType(kRetnType_Default) { }

	UInt32				parentPlugin;
	CommandReturnType	returnType;
};

class CommandTable
{
public:
	CommandTable();
	~CommandTable();

	static void	Init();

	void	Read(CommandInfo * start, CommandInfo * end);
	void	Add(CommandInfo * info, CommandReturnType retnType = kRetnType_Default, UInt32 parentPluginOpcodeBase = 0);
	void	PadTo(UInt32 id, CommandInfo * info = NULL);
	bool	Replace(UInt32 opcodeToReplace, CommandInfo* replaceWith);

	CommandInfo *	GetStart()	{ return &m_commands[0]; }
	CommandInfo *	GetEnd()	{ return GetStart() + m_commands.size(); }
	CommandInfo *	GetByName(const char * name);
	CommandInfo *	GetByOpcode(UInt32 opcode);

	void	SetBaseID(UInt32 id)	{ m_baseID = id; m_curID = id; }
	UInt32	GetMaxID()			{ return m_baseID + m_commands.size(); }
	void	SetCurID(UInt32 id)		{ m_curID = id; }
	UInt32	GetCurID()			{ return m_curID; }

	void	Dump();
	void	DumpAlternateCommandNames();
	void	DumpCommandDocumentation(UInt32 startWithID = kNVSEOpcodeStart);

	CommandReturnType	GetReturnType(const CommandInfo * cmd);
	void				SetReturnType(UInt32 opcode, CommandReturnType retnType);

	UInt32				GetRequiredNVSEVersion(const CommandInfo * cmd);
	PluginInfo *		GetParentPlugin(const CommandInfo * cmd);

private:
	// add commands for each release (will help keep track of commands)
	void AddCommandsV1();
	void AddCommandsV3s();
	void AddCommandsV4();
	void AddCommandsV5();
	void AddDebugCommands();

	typedef std::vector <CommandInfo>				CommandList;
	typedef std::unordered_map<UInt32, CommandMetadata>	CmdMetadataList;

	CommandList		m_commands;
	CmdMetadataList	m_metadata;

	UInt32		m_baseID;
	UInt32		m_curID;

	std::vector<UInt32>	m_opcodesByRelease;	// maps an NVSE major version # to opcode of first command added to that release, beginning with v0008

	void	RecordReleaseVersion();
	void	RemoveDisabledPlugins();
};

extern CommandTable	g_consoleCommands;
extern CommandTable	g_scriptCommands;

#pragma once
#include <Containers.h>
#include <Utilities.h>

bool IsConsoleMode();
bool GetConsoleEcho();
void SetConsoleEcho(bool doEcho);

class ConsoleManager
{
public:
	ConsoleManager();
	~ConsoleManager();

	struct TextNode
	{
		TextNode* next;
		TextNode* prev;
		String				text;
	};

	struct TextList
	{
		TextNode* first;
		TextNode* last;
		UInt32				count;

		TextList* Append(TextNode*);
	};

	struct RecordedCommand
	{
		char				buf[100];
	};

	void* scriptContext;
	TextList				printedLines;
	TextList				inputHistory;
	unsigned int			historyIndex;
	unsigned int			unk020;
	unsigned int			printedCount;
	unsigned int			unk028;
	unsigned int			lineHeight;
	int						textXPos;
	int						textYPos;
	UInt8					isConsoleOpen;
	UInt8					unk39;
	UInt8					isBatchRecording;
	UInt8					unk3B;
	unsigned int			numRecordedCommands;
	RecordedCommand			recordedCommands[20];
	char					scofPath[260];

	__forceinline static ConsoleManager*	GetSingleton(bool canCreateNew = true) { return CdeclCall<ConsoleManager*>(0x0071B160, canCreateNew); }
	void									AppendToSentHistory(const char*);
	__forceinline void						Print(const char* fmt, va_list args) { ThisCall(0x0071D0A0, this, fmt, args); }

	static char*							GetConsoleOutputFilename();
	static bool								HasConsoleOutputFilename();
};

inline ConsoleManager* operator<<(ConsoleManager* console, const std::string& str)
{
	UInt32 numLines = str.length() / 500;
	for (UInt32 i = 0; i < numLines; i++)
		console->Print(str.substr(i * 500, 500).c_str(), nullptr);

	console->Print(str.substr(numLines * 500, str.length() - numLines * 500).c_str(), nullptr);

	return console;
};

#pragma once
#include <Utilities.h>


enum {
	eListCount = -3,
	eListEnd = -2,
	eListInvalid = -1,
};


template <class Node, class Info>
class Visitor
{
	const Node* m_pHead;

	template <class Op>
	UInt32 FreeNodes(Node* node, Op& compareOp) const
	{
		static UInt32 nodeCount = 0;
		static UInt32 numFreed = 0;
		static Node* lastNode = nullptr;
		static bool bRemovedNext = false;

		if (node->Next())
		{
			nodeCount++;
			FreeNodes(node->Next(), compareOp);
			nodeCount--;
		}

		if (compareOp.Accept(node->Info()))
		{
			if (nodeCount) node->Delete();
			else node->DeleteHead(lastNode);
			numFreed++;
			bRemovedNext = true;
		}
		else
		{
			if (bRemovedNext) node->SetNext(lastNode);
			bRemovedNext = false;
			lastNode = node;
		}

		const UInt32 returnCount = numFreed;

		if (!nodeCount)	//reset vars after recursing back to head
		{
			numFreed = 0;
			lastNode = NULL;
			bRemovedNext = false;
		}

		return returnCount;
	}

	class AcceptAll {
	public:
		bool Accept(Info* info) {
			return true;
		}
	};

	class AcceptEqual {
		const Info* m_toMatch;
	public:
		AcceptEqual(const Info* info) : m_toMatch(info) { }
		bool Accept(const Info* info) { return info == m_toMatch; }
	};

	class AcceptStriCmp {
		const char* m_toMatch;
	public:
		AcceptStriCmp(const char* info) : m_toMatch(info) { }
		bool Accept(const char* info) { return m_toMatch && info ? !_stricmp(info, m_toMatch) ? true : false : false; }
	};
public:
	Visitor(const Node* pHead) : m_pHead(pHead) { }

	UInt32 Count() const {
		UInt32 count = 0;
		const Node* pCur = m_pHead;
		while (pCur && pCur->Info() != NULL) {
			++count;
			pCur = pCur->Next();
		}
		return count;
	}

	Info* GetNthInfo(UInt32 n) const {
		UInt32 count = 0;
		const Node* pCur = m_pHead;
		while (pCur && count < n && pCur->Info() != NULL) {
			++count;
			pCur = pCur->Next();
		}
		return (count == n && pCur) ? pCur->Info() : NULL;
	}

	template <class Op>
	void Visit(Op&& op) const {
		const Node* pCur = m_pHead;
		bool bContinue = true;
		while (pCur && pCur->Info() && bContinue) {
			bContinue = op.Accept(pCur->Info());
			if (bContinue) pCur = pCur->Next();
		}
	}

	template <class Op>
	const Node* Find(Op&& op, const Node* prev = NULL) const
	{
		const Node* pCur;
		if (!prev) pCur = m_pHead;
		else pCur = prev->next;
		bool bFound = false;
		while (pCur && !bFound)
		{
			if (pCur->Info())
			{
				bFound = op.Accept(pCur->Info());
				if (!bFound) pCur = pCur->Next();
			}
			else pCur = pCur->Next();
		}
		return pCur;
	}

	Node* FindInfo(const Info* toMatch) { return Find(AcceptEqual(toMatch)); }

	template <class Op>
	UInt32 CountIf(Op&& op) const
	{
		UInt32 count = 0;
		const Node* pCur = m_pHead;
		while (pCur)
		{
			if (pCur->Info() && op.Accept(pCur->Info())) count++;
			pCur = pCur->Next();
		}
		return count;
	}

	const Node* GetLastNode() const
	{
		const Node* pCur = m_pHead;
		while (pCur && pCur->Next()) pCur = pCur->Next();
		return pCur;
	}

	void RemoveAll() const { FreeNodes(const_cast<Node*>(m_pHead), AcceptAll()); }

	template <class Op>
	UInt32 RemoveIf(Op&& op) { return FreeNodes(const_cast<Node*>(m_pHead), op); }

	bool Remove(const Info* toRemove) { return RemoveIf(AcceptEqual(toRemove)) ? true : false; }

	bool RemoveString(const char* toRemove) { return RemoveIf(AcceptStriCmp(toRemove)) ? true : false; }

	void Append(Node* newNode)
	{
		Node* lastNode = const_cast<Node*>(GetLastNode());
		if (lastNode == m_pHead && !m_pHead->Info()) lastNode->DeleteHead(newNode);
		else lastNode->SetNext(newNode);
	}

	template <class Op>
	UInt32 GetIndexOf(Op&& op)
	{
		UInt32 idx = 0;
		const Node* pCur = m_pHead;
		while (pCur && pCur->Info() && !op.Accept(pCur->Info()))
		{
			idx++;
			pCur = pCur->Next();
		}

		if (pCur && pCur->Info()) return idx;
		return -1;
	}
};

struct CoordXY
{
	Float32	x;
	Float32	y;

	CoordXY() : x(0), y(0) {}

	CoordXY(float _x, float _y) : x(_x), y(_y) {}

	inline CoordXY& operator =(const CoordXY& rhs)
	{
		*(Float64*)this = *(Float64*)&rhs;
		return *this;
	}
};

#pragma once
#include <NiObjects.h>
#include <Utilities.h>

struct ChunkAndFormType {
	UInt32		chunkType;	// ie 
	UInt32		formType;	// ie 0x2A
	const char*	formName;	// ie 'NPC_'
};

static const UInt32 _ModInfo_GetNextChunk = 0x004726B0; // args: none retn: UInt32 subrecordType (third call in TESObjectARMO_LoadForm)
static const UInt32 _ModInfo_GetChunkData = 0x00472890;	// args: void* buf, UInt32 bufSize retn: bool readSucceeded (fifth call in TESObjectARMO_LoadForm)
static const UInt32 _ModInfo_Read32		  =	0x004727F0;	// args: void* buf retn: void (find 'LPER', then next call, still in TESObjectARMO_LoadForm)
static const UInt32 _ModInfo_HasMoreSubrecords = 0x004726F0;	// Last call before "looping" to GetNextChunk in TESObjectARMO_LoadForm.
static const UInt32 _ModInfo_InitializeForm = 0x00472F60;	// args: TESForm* retn: void (second call in TESObjectARMO_LoadForm)

// addresses of static ModInfo members holding type info about currently loading form
static UInt32* s_ModInfo_CurrentChunkTypeCode = (UInt32*)0x011C54F4;
static UInt32* s_ModInfo_CurrentFormTypeEnum = (UInt32*)0x011C54F0;
// in last call (SetStaticFieldsAndGetFormTypeEnum) of first call (ModInfo__GetFormInfoTypeID) from _ModInfo_InitializeForm
		//		s_ModInfo_CurrentChunkTypeCode is first cmp
		//		s_ModInfo_CurrentChunkTypeEnum is next mov
static const ChunkAndFormType* s_ModInfo_ChunkAndFormTypes = (const ChunkAndFormType*)0x01187008;	// Array used in the loop in SetStaticFieldsAndGetFormTypeEnum, starts under dd offset aNone

static UInt8** g_CreatedObjectData = (UInt8**)0x011C54CC;	// pointer to FormInfo + form data, filled out by TESForm::SaveForm()
static UInt32* g_CreatedObjectSize = (UInt32*)0x011C54D0;
		// in first call (Form_startSaveForm) in TESObjectARMO__SaveForm:
		//		g_CreatedObjectSize is set to 18h
		//		g_CreatedObjectData is set to the eax result of the next call

// 10
class BoundObjectListHead
{
public:
	BoundObjectListHead();
	~BoundObjectListHead();

	UInt32			boundObjectCount;	// 0
	TESBoundObject*	first;				// 4
	TESBoundObject*	last;				// 8
	UInt32			unkC;				// C
};

struct FormRecordData
{
	UInt8		typeID;		// corresponds to kFormType_XXX
	UInt32		typeCode;	// i.e. 'GMST', 'FACT'
	UInt32		unk08;		// only seen zero
};

struct ChunkHeader
{
	UInt32	type : 4;	// i.e. 'XGRD', 'DATA'
	UInt16	size : 2;
};

struct ModInfo		// referred to by game as TESFile
{
	ModInfo();
	~ModInfo();

	// 18 info about currently loading form
	struct FormInfo  // Record Header in FNVEdit
	{
		UInt32		recordType;			// 00 i.e. 'FACT', 'GMST'						Signature
		UInt32		dataSize;			// 04 looks like size of entire record			Data Size
		UInt32		formFlags;			// 08 copied to TESForm->flags					Record Flags
		UInt32		formID;				// 0C											FormID
		UInt32		unk10;				// 10											Version Control Info 1
		UInt16		formVersion;		// 14 always initialized to 0F on SaveForm.		Form Version
		UInt16		unk16;				// 16                                           Version Control Info 2
	};

	// 18 info about current group of form
	struct GroupInfo  // Record Header in FNVEdit
	{
		UInt32		recordType;			// 00 'GRUP'									Signature
		UInt32		groupSize;			// 04 Size of entire record						Size
		UInt32		groupLabel;			// 08 copied to TESForm->flags					Label
		UInt32		groupType;			// 0C forms, dialog, cell...					Type
		UInt32		unk10;				// 10											Stamp
		UInt16		unk14;				// 14											Part of Unknown
		UInt16		unk16;				// 16                                           Part of Unknown
	};

	struct FileHeader	// File header in FNVEdit Signature 'HEDR'
	{
		Float32	version;		//	00
		UInt32	recordCount;	//	04
		UInt32	nextObectID;	//	08
	};

	struct	MasterSize	// Data member of the master list in WIN32_FIND_DATA format
	{
		UInt32	low;
		UInt32	high;
	};

	TList<ModInfo>						unkList;			// 000 treated as ModInfo during InitializeForm, looks to be a linked list of modInfo. Also during Save in GECK.
	UInt32 /*NiTPointerMap<TESFile*>*/	* pointerMap;		// 008
	UInt32								unk00C;				// 00C
	BSFile*								unkFile;			// 010
	UInt32								unk014;				// 014 
	void								* unk018;			// 018 seen all zeroes. size unknown, seen not valid pointer in FalloutNV.esm
	void								* unk01C;			// 01C as above
	char								name[0x104];		// 020
	char								filepath[0x104];	// 124
	UInt32								unk228;				// 228
	UInt32								unk22C;				// Masters are init'd to dword_1186740 (0x2800) same val as BSFile+10? Buffer size ?
	UInt32								unk230;				// 230
	UInt32								unk234;				// 234
	UInt32								unk238;				// 238
	UInt32								unk23C;				// 23C
	FormInfo							formInfo;			// 240
	ChunkHeader							subRecordHeader;	// 258
	UInt32								unk260;				// 260 could be file size, as it is compared with fileOffset during load module. But filesize would be an Int64 !
	UInt32								fileOffset;			// 264
	UInt32								dataOffset;			// 268 index into dataBuf
	UInt32								subrecordBytesRead;	// 26C generates error on Read if != expected length
	FormInfo							writeInfo;			// 270 "used" to add record to the plugin.
	UInt32								writeOffset;		// 288
	UInt32								subrecordBytesToWrite;	// 28C
	TList<UInt32>						TList290;			// 290 looks to be a list of form or a list of formInfo. referenced from TESForm::WriteForm
	UInt8								unk298;				// 298
	UInt8								bIsBigEndian;		// 299
	UInt8								unk29A;				// 29A
	UInt8								pad29B;
	WIN32_FIND_DATA						fileData;			// 29C
	FileHeader							header;				// 3DC
	UInt8								flags;				// 3E8	Bit 0 is ESM . Runtime: Bit 2 is Valid, Bit 3 is Unselected Editor: 2 is selected, 3 is active, 4 may be invalid, 6 is endian, 14 controls VCI.
	UInt8								pad3E9[3];
	TList<char*>						refModNames;		// 3EC
	TList<MasterSize*>					refModData;			// 3F4 most likely full of 0
	UInt32								numRefMods;			// 3FC related to modindex; see 4472D0
																// formIDs in mod are as saved in GECK, must fix up at runtime
	ModInfo								** refModInfo;		// 400 used to look up modInfo based on fixed mod index, double-check
	UInt32								unk404;				// 404
	UInt32								unk408;				// 408
	UInt8								modIndex;			// 40C init to 0xFF
	UInt8								pad40D[3];
	String								author;				// 410
	String								description;		// 418
	void								* dataBuf;			// 420 
	UInt32								dataBufSize;		// 424 looks like size of entire record
	UInt8								unk428;				// 428 decide if forms needs to be reloaded on LoadFiles
	UInt8								pad429[3];

	// In Editor: 430 = ONAM array and 434 ONAM array count. Allocated at 0438
	
	bool IsLoaded() const { return true; }

	/*** used by TESForm::LoadForm() among others ***/
	MEMBER_FN_PREFIX(ModInfo);
	DEFINE_MEMBER_FN(GetNextChunk, UInt32, _ModInfo_GetNextChunk);	// returns chunk type
	DEFINE_MEMBER_FN(GetChunkData, bool, _ModInfo_GetChunkData, UInt8* buf, UInt32 bufSize); // max size, not num to read
	DEFINE_MEMBER_FN(Read32, void, _ModInfo_Read32, void* out);
	DEFINE_MEMBER_FN(HasMoreSubrecords, bool, _ModInfo_HasMoreSubrecords);
};

static_assert(sizeof(WIN32_FIND_DATA) == 0x140);
static_assert(sizeof(ModInfo) == 0x42C);

struct ModList
{
	TList<ModInfo>		modInfoList;		// 00
	UInt32				loadedModCount;		// 08
	ModInfo*			loadedMods[0xFF];	// 0C
};
static_assert(sizeof(ModList) == 0x408);

// A0
struct WaterSurfaceManager
{
	// B0 c'tor @ 0x4ED5F0
	struct WaterGroup
	{
		TESWaterForm* waterForm;		// 00
		NiPoint4				vector04;		// 04
		NiPoint4				vector14;		// 14
		DList<TESObjectREFR>	waterPlanes;	// 24
		DList<void>				list30;			// 30
		DList<void>				list3C;			// 3C
		DList<void>				list48;			// 48
		NiAVObject* object54;		// 54
		NiAVObject* object58;		// 58
		UInt8					byte5C;			// 5C
		UInt8					byte5D;			// 5D
		UInt8					byte5E;			// 5E
		UInt8					byte5F;			// 5F
		UInt8					byte60;			// 60
		UInt8					pad61[3];		// 61
		DList<void>				list64;			// 64
		DList<void>				list70;			// 70
		DList<void>				list7C;			// 7C
		DList<void>				list88;			// 88
		NiObject* object94;		// 94
		NiObject* object98;		// 98
		UInt32					unk9C;			// 9C
		UInt32					unkA0;			// A0
		NiObject* objectA4;		// A4
		NiObject* objectA8;		// A8
		UInt32					unkAC;			// AC
	};

	struct Struct8C
	{
		UInt32		unk00;
		UInt32		unk04;
		UInt32		unk08;
	};

	UInt32								unk00;			// 00
	UInt32								unk04;			// 04
	NiObject* object08;		// 08
	NiObject* object0C;		// 0C
	NiObject* object10;		// 10
	NiObject* object14;		// 14
	NiObject* object18;		// 18
	NiObject* object1C;		// 1C	Seen NiSourceTexture
	NiObject* object20;		// 20
	UInt32								unk24;			// 24
	UInt32								unk28;			// 28
	UInt32								unk2C;			// 2C
	UInt32								unk30;			// 30
	UInt32								unk34;			// 34
	UInt32								unk38;			// 38
	DList<WaterGroup>					waterGroups;	// 3C
	WaterGroup* waterLOD;		// 48	(Assumed)
	NiTPointerMap<TESObjectREFR>		map4C;			// 4C
	NiTPointerMap<TESObjectREFR>		map5C;			// 5C
	NiTPointerMap<TESWaterForm>			map6C;			// 6C
	NiTMapBase<TESObjectREFR*, void*>	map7C;			// 7C
	Struct8C							unk8C;			// 8C
	float								flt98;			// 98
	UInt32								unk9C;			// 9C
};
static_assert(sizeof(WaterSurfaceManager) == 0xA0);


#pragma once
#include <NiTypes.h>
#include <Containers.h>

// can be passed to QueueUIMessage to determine Vaultboy icon displayed
enum eEmotion {
	happy = 0,
	sad = 1,
	neutral = 2,
	pain = 3
};

class ButtonIcon;

typedef void (*_ShowMessageBox_Callback)();
extern const _ShowMessageBox_Callback ShowMessageBox_Callback;

typedef bool (*_ShowMessageBox)(const char* message, UInt32 unk1, UInt32 unk2, _ShowMessageBox_Callback callback, UInt32 unk4, UInt32 unk5, float unk6, float unk7, ...);
extern const _ShowMessageBox ShowMessageBox;

// set to scriptObj->refID after calling ShowMessageBox()
// GetButtonPressed checks this before returning a value, if it doesn't match it returns -1
typedef UInt32* _ShowMessageBox_pScriptRefID;
extern const _ShowMessageBox_pScriptRefID ShowMessageBox_pScriptRefID;
typedef UInt8* _ShowMessageBox_button;
extern const _ShowMessageBox_button ShowMessageBox_button;

typedef bool (*_QueueUIMessage)(const char* msg, UInt32 emotion, const char* ddsPath, const char* soundName, float msgTime, bool maybeNextToDisplay);
extern const _QueueUIMessage QueueUIMessage;

const UInt32 kMaxMessageLength = 0x4000;

class bhkSimpleShapePhantom;

struct PlayerCameraSphere
{
	bhkSimpleShapePhantom* unk000;
	bhkSimpleShapePhantom* unk004;
};

struct SystemColorManager
{
	enum SystemColorNodes
	{
		kNone = 0,
		kHUDMain,
		kHUDAlt,
		kTerminal,
		kPipBoy,
		kStartMenu
	};

	// 0C
	class SystemColor
	{
	public:
		SystemColor();
		~SystemColor();

		virtual void	Destructor(bool doFree);
		virtual UInt32	GetColor();
		virtual void	SetColor(UInt32 newColor);
		virtual bool	IsHard();
		virtual bool	IsSoft();

		String		traitName;

		void SetColorRGB(UInt32 r, UInt32 g, UInt32 b);
	};

	// 10
	class HardSystemColor : public SystemColor
	{
	public:
		HardSystemColor();
		~HardSystemColor();

		UInt32		color;		// 0C
	};

	// 10
	class SoftSystemColor : public SystemColor
	{
	public:
		SoftSystemColor();
		~SoftSystemColor();

		Setting* setting;	// 0C
	};

	DList<SystemColor>	sysColors;
	UInt32				unk0C;

	static SystemColorManager* GetSingleton() { return *reinterpret_cast<SystemColorManager**>(0x11D8A88); };
	int GetColor(SystemColorNodes node) { return ThisCall<int>(0x7190A0, this, node); };
	void SetColor(SystemColorNodes node, UInt32 color) { ThisCall(0x719120, this, node, color); };
};

union Color
{
	UInt32 rgba;
	struct
	{
		UInt8 a, b, g, r;
	};
};

union RGB
{
	UInt32 rgb;
	struct
	{
		UInt8 b, g, r;
	};
};

const UInt32 FontArraySize = 8;

struct FontInfo {
	FontInfo();
	~FontInfo();

	struct Data03C {
		UInt32	unk000;	// 000
		UInt16	wrd004;	// 004	Init'd to 0
		UInt16	wrd006;	// 006	Init'd to 0x0FFFF
	};	// 0008


	// 3928
	struct FontData
	{
		struct TexFileName
		{
			UInt32			unk00;
			char			fileName[0x20];
		};

		struct CharDimensions
		{
			float			flt00;		// 0
			float			flt04;		// 4
			float			flt08;		// 8
			float			flt0C;		// C
			float			flt10;		// 10
			float			flt14;		// 14
			float			flt18;		// 18
			float			flt1C;		// 1C
			float			flt20;		// 20
			float			width;		// 24
			float			height;		// 28
			float			flt2C;		// 2C
			float			widthMod;	// 30
			float			flt34;		// 34
		//	totalWidth = width + widthMod
		};
		static_assert(sizeof(CharDimensions) == 0x38);

		float			lineHeight;				// 0000
		UInt32			numTextures;			// 0004
		TexFileName		textures[8];			// 0008
		CharDimensions	charDimensions[256];	// 0128
	};
	static_assert(sizeof(FontData) == 0x3928);

	struct TextReplaced {
		String	str000;	// 000	Init'd to ""
		UInt32	unk008;	// 008	Init'd to arg1
		UInt32	unk00C;	// 00C	Init'd to arg2
		UInt32	unk010;	// 010	Init'd to arg3
		UInt32	unk014;	// 014	Init'd to arg4
		UInt32	unk018;	// 018	Init'd to 0
		UInt8	byt01C;	// 01C	Init'd to arg5
		UInt8	fill[3];
	};	// 020

	UInt8						isLoaded;		// 000	Init'd to 0, loaded successfully in OBSE (word bool ?)
	UInt8						pad01[3];		// 001
	char*						filePath;		// 004	Init'd to arg2, passed to OpenBSFile
	UInt32						id;				// 008	1 based, up to 8 apparently
	NiObject*					unk00C[8];		// 00C	in OBSE: NiTexturingProperty			* textureProperty
	float						unk02C;			// 02C	Those two values seem to be computed by looping through the characters in the font (max height/weight ?)
	float						unk030;			// 030
	UInt32						unk034;			// 038	in OBSE: NiD3DShaderConstantMapEntry	* unk34;
	FontData*					fontData;		// 038	Init'd to 0, might be the font content, at Unk004 we have the count of font texture
	Data03C						dat03C;			// 03C
	BSSimpleArray<ButtonIcon>	unk044;			// 044

	static FontInfo* Load(const char* path, UInt32 ID);
	bool GetName(char* out);	// filename stripped of path and extension
};	// 054
static_assert(sizeof(FontInfo) == 0x54);

class FontManager
{
public:
	FontManager();
	~FontManager();

	// 3C


	FontInfo*			fontInfos[8];		// 00
	UInt8				byte20;				// 20
	UInt8				pad21[3];			// 21
	FontInfo*			extraFonts[80];		// 24

	NiPoint3* GetStringDimensions(NiPoint3* outDims, const char* srcString, UInt32 fontID, Float32 wrapwidth = 0x7F7FFFFF, UInt32 startIdx = 0) { return ThisCall<NiPoint3*>(0xA1B020, this, outDims, srcString, fontID, wrapwidth, startIdx); };
	NiPoint3* GetStringDimensions(const char* srcString, UInt32 fontID, Float32 wrapwidth = 0x7F7FFFFF, UInt32 startIdx = 0)
	{
		NiPoint3 out;
		return GetStringDimensions(&out, srcString, fontID, wrapwidth, startIdx);
	}

	std::string StringShorten(const std::string& str, const UInt32 font, const Float32 max) const;

	static FontManager* GetSingleton() { return *reinterpret_cast<FontManager**>(0x11F33F8); };
};


static_assert(sizeof(FontInfo) == 0x54);

struct __declspec(align(4)) FontTextReplaced
{
	String str;
	UInt32 wrapWidth;
	UInt32 wrapLimit;
	UInt32 initdToZero;
	UInt32 wrapLines;
	UInt32 length;
	UInt8 newLineCharacter;
	UInt8 gap1D[3];
	TList<void> lineWidths;

	FontTextReplaced() : gap1D{}
	{
		str.m_bufLen = 0;
		str.m_data = nullptr;
		str.m_dataLen = 0;
		wrapWidth = 0;
		wrapLimit = 0;
		initdToZero = 0;
		wrapLines = 0;
		length = 0;
		newLineCharacter = 0;
	}
	;

	~FontTextReplaced()
	{
		str.Set(NULL);
		lineWidths.RemoveAll();
	}

	void GetVariableEscapedText(const char* input);
};

static_assert(sizeof(FontTextReplaced) == 0x28);
static void(__thiscall* Font__CheckForVariablesInText)(FontInfo*, const char* input, FontTextReplaced* a3) = (void(__thiscall*)(FontInfo*, const char*, FontTextReplaced*))0xA12FB0;



struct FontHeightData
{
	float		heightBase;
	float		heightwGap;
};
//s_fontHeightDatas[90];

#pragma once
#include <NiTypes.h>

/*** class hierarchy
 *
 *	yet again taken from rtti information
 *	ni doesn't seem to use multiple inheritance
 *
 *	thanks to the NifTools team for their work on the on-disk format
 *	thanks to netimmerse for NiObject::DumpAttributes
 *
 *	all offsets here are assuming patch 1.2 as they changed dramatically
 *	0xE8 bytes were removed from NiObjectNET, and basically everything derives from that
 *
 *	NiObject derives from NiRefObject
 *
 *	BSFaceGenMorphData - derived from NiRefObject
 *		BSFaceGenMorphDataHead
 *		BSFaceGenMorphDataHair
 *
 *	BSTempEffect - derived from NiObject
 *		BSTempEffectDecal
 *		BSTempEffectGeometryDecal
 *		BSTempEffectParticle
 *		MagicHitEffect
 *			MagicModelHitEffect
 *			MagicShaderHitEffect
 *
 *	NiDX92DBufferData - derived from NiRefObject and something else
 *		NiDX9DepthStencilBufferData
 *			NiDX9SwapChainDepthStencilBufferData
 *			NiDX9ImplicitDepthStencilBufferData
 *			NiDX9AdditionalDepthStencilBufferData
 *		NiDX9TextureBufferData
 *		NiDX9OnscreenBufferData
 *			NiDX9SwapChainBufferData
 *			NiDX9ImplicitBufferData
 *
 *	NiObject
 *		NiObjectNET
 *			NiProperty
 *				NiTexturingProperty
 *				NiVertexColorProperty
 *				NiWireframeProperty
 *				NiZBufferProperty
 *				NiMaterialProperty
 *				NiAlphaProperty
 *				NiStencilProperty
 *				NiRendererSpecificProperty
 *				NiShadeProperty
 *					BSShaderProperty
 *						SkyShaderProperty
 *						ParticleShaderProperty
 *						BSShaderLightingProperty
 *							DistantLODShaderProperty
 *							TallGrassShaderProperty
 *							BSShaderPPLightingProperty
 *								SpeedTreeShaderPPLightingProperty
 *									SpeedTreeBranchShaderProperty
 *								Lighting30ShaderProperty
 *								HairShaderProperty
 *							SpeedTreeShaderLightingProperty
 *								SpeedTreeLeafShaderProperty
 *								SpeedTreeFrondShaderProperty
 *							GeometryDecalShaderProperty
 *						PrecipitationShaderProperty
 *						BoltShaderProperty
 *						WaterShaderProperty
 *				NiSpecularProperty
 *				NiFogProperty
 *					BSFogProperty
 *				NiDitherProperty
 *			NiTexture
 *				NiDX9Direct3DTexture
 *				NiSourceTexture
 *					NiSourceCubeMap
 *				NiRenderedTexture
 *					NiRenderedCubeMap
 *			NiAVObject
 *				NiDynamicEffect
 *					NiLight
 *						NiDirectionalLight
 *						NiPointLight
 *							NiSpotLight
 *						NiAmbientLight
 *					NiTextureEffect
 *				NiNode
 *					SceneGraph
 *					BSTempNodeManager
 *					BSTempNode
 *					BSCellNode
 *					BSClearZNode
 *					BSFadeNode
 *					BSScissorNode
 *					BSTimingNode
 *					BSFaceGenNiNode
 *					NiBillboardNode
 *					NiSwitchNode
 *						NiLODNode
 *							NiBSLODNode
 *					NiSortAdjustNode
 *					NiBSPNode
 *					ShadowSceneNode
 *				NiCamera
 *					BSCubeMapCamera - RTTI data incorrect
 *					NiScreenSpaceCamera
 *				NiGeometry
 *					NiLines
 *					NiTriBasedGeom
 *						NiTriShape
 *							BSScissorTriShape
 *							NiScreenElements
 *							NiScreenGeometry
 *							TallGrassTriShape
 *						NiTriStrips
 *							TallGrassTriStrips
 *					NiParticles
 *						NiParticleSystem
 *							NiMeshParticleSystem
 *						NiParticleMeshes
 *			NiSequenceStreamHelper
 *		NiRenderer
 *			NiDX9Renderer
 *		NiPixelData
 *		NiCollisionObject
 *			NiCollisionData
 *			bhkNiCollisionObject
 *				bhkCollisionObject
 *					bhkBlendCollisionObject
 *						WeaponObject
 *						bhkBlendCollisionObjectAddRotation
 *				bhkPCollisionObject
 *					bhkSPCollisionObject
 *		NiControllerSequence
 *			BSAnimGroupSequence
 *		NiTimeController
 *			BSDoorHavokController
 *			BSPlayerDistanceCheckController
 *			NiD3DController
 *			NiControllerManager
 *			NiInterpController
 *				NiSingleInterpController
 *					NiTransformController
 *					NiPSysModifierCtlr
 *						NiPSysEmitterCtlr
 *						NiPSysModifierBoolCtlr
 *							NiPSysModifierActiveCtlr
 *						NiPSysModifierFloatCtlr
 *							NiPSysInitialRotSpeedVarCtlr
 *							NiPSysInitialRotSpeedCtlr
 *							NiPSysInitialRotAngleVarCtlr
 *							NiPSysInitialRotAngleCtlr
 *							NiPSysGravityStrengthCtlr
 *							NiPSysFieldMaxDistanceCtlr
 *							NiPSysFieldMagnitudeCtlr
 *							NiPSysFieldAttenuationCtlr
 *							NiPSysEmitterSpeedCtlr
 *							NiPSysEmitterPlanarAngleVarCtlr
 *							NiPSysEmitterPlanarAngleCtlr
 *							NiPSysEmitterLifeSpanCtlr
 *							NiPSysEmitterInitialRadiusCtlr
 *							NiPSysEmitterDeclinationVarCtlr
 *							NiPSysEmitterDeclinationCtlr
 *							NiPSysAirFieldSpreadCtlr
 *							NiPSysAirFieldInheritVelocityCtlr
 *							NiPSysAirFieldAirFrictionCtlr
 *					NiFloatInterpController
 *						NiFlipController
 *						NiAlphaController
 *						NiTextureTransformController
 *						NiLightDimmerController
 *					NiBoolInterpController
 *						NiVisController
 *					NiPoint3InterpController
 *						NiMaterialColorController
 *						NiLightColorController
 *					NiExtraDataController
 *						NiFloatsExtraDataPoint3Controller
 *						NiFloatsExtraDataController
 *						NiFloatExtraDataController
 *						NiColorExtraDataController
 *				NiMultiTargetTransformController
 *				NiGeomMorpherController
 *			bhkBlendController
 *			bhkForceController
 *			NiBSBoneLODController
 *			NiUVController
 *			NiPathController
 *			NiLookAtController
 *			NiKeyframeManager
 *			NiBoneLODController
 *			NiPSysUpdateCtlr
 *			NiPSysResetOnLoopCtlr
 *			NiFloatController
 *				NiRollController
 *		bhkRefObject
 *			bhkSerializable
 *				bhkWorld - NiRTTI has incorrect parent
 *					bhkWorldM
 *				bhkAction
 *					bhkUnaryAction
 *						bhkMouseSpringAction
 *						bhkMotorAction
 *					bhkBinaryAction
 *						bhkSpringAction
 *						bhkAngularDashpotAction
 *						bhkDashpotAction
 *				bhkWorldObject
 *					bhkPhantom
 *						bhkShapePhantom
 *							bhkSimpleShapePhantom
 *							bhkCachingShapePhantom
 *						bhkAabbPhantom
 *							bhkAvoidBox
 *					bhkEntity
 *						bhkRigidBody
 *							bhkRigidBodyT
 *				bhkConstraint
 *					bhkLimitedHingeConstraint
 *					bhkMalleableConstraint
 *					bhkBreakableConstraint
 *					bhkWheelConstraint
 *					bhkStiffSpringConstraint
 *					bhkRagdollConstraint
 *					bhkPrismaticConstraint
 *					bhkHingeConstraint
 *					bhkBallAndSocketConstraint
 *					bhkGenericConstraint
 *						bhkFixedConstraint
 *					bhkPointToPathConstraint
 *					bhkPoweredHingeConstraint
 *				bhkShape
 *					bhkTransformShape
 *					bhkSphereRepShape
 *						bhkConvexShape
 *							bhkSphereShape
 *							bhkCapsuleShape
 *							bhkBoxShape
 *							bhkTriangleShape
 *							bhkCylinderShape
 *							bhkConvexVerticesShape
 *								bhkCharControllerShape
 *							bhkConvexTransformShape
 *							bhkConvexSweepShape
 *						bhkMultiSphereShape
 *					bhkBvTreeShape
 *						bhkTriSampledHeightFieldBvTreeShape
 *						bhkMoppBvTreeShape
 *					bhkShapeCollection
 *						bhkListShape
 *						bhkPackedNiTriStripsShape
 *						bhkNiTriStripsShape
 *					bhkHeightFieldShape
 *						bhkPlaneShape
 *				bhkCharacterProxy
 *					bhkCharacterListenerArrow - no NiRTTI
 *					bhkCharacterListenerSpell - no NiRTTI
 *					bhkCharacterController - no NiRTTI
 *		NiExtraData
 *			TESObjectExtraData
 *			BSFaceGenAnimationData
 *			BSFaceGenModelExtraData
 *			BSFaceGenBaseMorphExtraData
 *			DebugTextExtraData
 *			NiStringExtraData
 *			NiFloatExtraData
 *				FadeNodeMaxAlphaExtraData
 *			BSFurnitureMarker
 *			NiBinaryExtraData
 *			BSBound
 *			NiSCMExtraData
 *			NiTextKeyExtraData
 *			NiVertWeightsExtraData
 *			bhkExtraData
 *			PArrayPoint
 *			NiIntegerExtraData
 *				BSXFlags
 *			NiFloatsExtraData
 *			NiColorExtraData
 *			NiVectorExtraData
 *			NiSwitchStringExtraData
 *			NiStringsExtraData
 *			NiIntegersExtraData
 *			NiBooleanExtraData
 *		NiAdditionalGeometryData
 *			BSPackedAdditionalGeometryData
 *		NiGeometryData
 *			NiLinesData
 *			NiTriBasedGeomData
 *				NiTriStripsData
 *					NiTriStripsDynamicData
 *				NiTriShapeData
 *					NiScreenElementsData
 *					NiTriShapeDynamicData
 *					NiScreenGeometryData
 *			NiParticlesData
 *				NiPSysData
 *					NiMeshPSysData
 *				NiParticleMeshesData
 *		NiTask
 *			BSTECreateTask
 *			NiParallelUpdateTaskManager::SignalTask
 *			NiGeomMorpherUpdateTask
 *			NiPSysUpdateTask
 *		NiSkinInstance
 *		NiSkinPartition
 *		NiSkinData
 *		NiRenderTargetGroup
 *		Ni2DBuffer
 *			NiDepthStencilBuffer
 *		NiUVData
 *		NiStringPalette
 *		NiSequence
 *		NiRotData
 *		NiPosData
 *		NiMorphData
 *		NiTransformData
 *		NiFloatData
 *		NiColorData
 *		NiBSplineData
 *		NiBSplineBasisData
 *		NiBoolData
 *		NiTaskManager
 *			NiParallelUpdateTaskManager
 *		hkPackedNiTriStripsData
 *		NiInterpolator
 *			NiBlendInterpolator
 *				NiBlendTransformInterpolator
 *				NiBlendAccumTransformInterpolator
 *				NiBlendFloatInterpolator
 *				NiBlendQuaternionInterpolator
 *				NiBlendPoint3Interpolator
 *				NiBlendColorInterpolator
 *				NiBlendBoolInterpolator
 *			NiLookAtInterpolator
 *			NiKeyBasedInterpolator
 *				NiFloatInterpolator
 *				NiTransformInterpolator
 *				NiQuaternionInterpolator
 *				NiPoint3Interpolator
 *				NiPathInterpolator
 *				NiColorInterpolator
 *				NiBoolInterpolator
 *					NiBoolTimelineInterpolator
 *			NiBSplineInterpolator
 *				NiBSplineTransformInterpolator
 *					NiBSplineCompTransformInterpolator
 *				NiBSplinePoint3Interpolator
 *					NiBSplineCompPoint3Interpolator
 *				NiBSplineFloatInterpolator
 *					NiBSplineCompFloatInterpolator
 *				NiBSplineColorInterpolator
 *					NiBSplineCompColorInterpolator
 *		NiAVObjectPalette
 *			NiDefaultAVObjectPalette
 *		BSReference
 *		BSNodeReferences
 *		NiPalette
 *		NiLODData
 *			NiRangeLODData
 *			NiScreenLODData
 *		NiPSysModifier
 *			BSWindModifier
 *			NiPSysMeshUpdateModifier
 *			NiPSysRotationModifier
 *			NiPSysEmitter
 *				NiPSysMeshEmitter
 *				NiPSysVolumeEmitter
 *					NiPSysCylinderEmitter
 *					NiPSysSphereEmitter
 *					NiPSysBoxEmitter
 *					BSPSysArrayEmitter
 *			NiPSysGravityModifier
 *			NiPSysSpawnModifier
 *			BSParentVelocityModifier
 *			NiPSysPositionModifier
 *			NiPSysGrowFadeModifier
 *			NiPSysDragModifier
 *			NiPSysColorModifier
 *			NiPSysColliderManager
 *			NiPSysBoundUpdateModifier
 *			NiPSysBombModifier
 *			NiPSysAgeDeathModifier
 *			NiPSysFieldModifier
 *				NiPSysVortexFieldModifier
 *				NiPSysTurbulenceFieldModifier
 *				NiPSysRadialFieldModifier
 *				NiPSysGravityFieldModifier
 *				NiPSysDragFieldModifier
 *				NiPSysAirFieldModifier
 *		NiPSysEmitterCtlrData
 *		NiAccumulator
 *			NiBackToFrontAccumulator
 *				NiAlphaAccumulator
 *					BSShaderAccumulator
 *		NiScreenPolygon
 *		NiScreenTexture
 *		NiPSysCollider
 *			NiPSysSphericalCollider
 *			NiPSysPlanarCollider
 *
 *	NiShader
 *		NiD3DShaderInterface
 *			NiD3DShader
 *				NiD3DDefaultShader
 *					SkyShader
 *					ShadowLightShader
 *						ParallaxShader
 *						SkinShader
 *						HairShader
 *						SpeedTreeBranchShader
 *					WaterShaderHeightMap
 *					WaterShader
 *					WaterShaderDisplacement
 *					ParticleShader
 *					TallGrassShader
 *					PrecipitationShader
 *					SpeedTreeLeafShader
 *					BoltShader
 *					Lighting30Shader
 *					GeometryDecalShader
 *					SpeedTreeFrondShader
 *					DistantLODShader
 *
 *	NiD3DShaderConstantMap
 *		NiD3DSCM_Vertex
 *		NiD3DSCM_Pixel
 *
 ****/

class NiStream;
class NiTextKeyExtraData;

class NiMemObject
{
};

// 008
class NiRefObject : public NiMemObject
{
public:
	NiRefObject();
	~NiRefObject();

	virtual void		Destructor(bool freeThis);	// 00
	virtual void		Free();					// 01

//	void		** _vtbl;		// 000
	UInt32		m_uiRefCount;	// 004 - name known
};

// 008
class NiObject : public NiRefObject
{
public:
	NiObject();
	~NiObject();

	virtual NiRTTI*		GetType();		// 02
	virtual NiNode*		GetAsNiNode();	// 03 
	virtual UInt32		Unk_04();		// 04
	virtual UInt32		Unk_05();		// 05
	virtual UInt32		Unk_06();		// 06
	virtual UInt32		Unk_07();		// 07
	virtual UInt32		Unk_08();		// 08
	virtual UInt32		Unk_09();		// 09
	virtual UInt32		Unk_0A();		// 0A
	virtual UInt32		Unk_0B();		// 0B
	virtual UInt32		Unk_0C();		// 0C
	virtual UInt32		Unk_0D();		// 0D
	virtual UInt32		Unk_0E();		// 0E
	virtual UInt32		Unk_0F();		// 0F
	virtual UInt32		Unk_10();		// 10
	virtual UInt32		Unk_11();		// 11
	virtual NiObject*	Copy();			// 12 (returns this, GetAsNiObject ?). Big doubt with everything below, except last which is 022
	virtual void		Load(NiStream * stream);
	virtual void		PostLoad(NiStream * stream);
	virtual void		FindNodes(NiStream * stream);	// give NiStream all of the NiNodes we own
	virtual void		Save(NiStream * stream);
	virtual bool		Compare(NiObject * obj);
	virtual void		DumpAttributes(NiTArray <char *> * dst);
	virtual void		DumpChildAttributes(NiTArray <char *> * dst);
	virtual void		Unk_1A();
	virtual void		Unk_1B(UInt32 arg);
	virtual void		Unk_1C();
	virtual void		GetType2();					// calls GetType
	virtual void		Unk_1E(UInt32 arg);
	virtual void		Unk_1F();
	virtual void		Unk_20();
	virtual void		Unk_21();
	virtual void		Unk_22();
};

class RefNiObject
{
	NiObject*	object;	// 00
};

// 018 (used to be 100, delta E8) confirmed, confirmed no virtual funcs
class NiObjectNET : public NiObject
{
public:
	NiObjectNET();
	~NiObjectNET();
	
	const char*			m_pcName;						// 008 - name known
	NiTimeController*	m_controller;					// 00C - size ok

	NiExtraData**		m_extraDataList;				// 010 - size ok
	UInt16				m_extraDataListLen;				// 014 - size ok
	UInt16				m_extraDataListCapacity;		// 016 - size ok
	// 018

	const char* GetName() const { return m_pcName ? m_pcName : "NULL"; }
	void SetName(const char* newName);
	NiExtraData* __fastcall GetExtraData(UInt32 vtbl) const;
	NiExtraData* GetExtraData2(const char* name);
	bool AddExtraData(NiExtraData* xData);

	void DumpExtraData();

};
static_assert(sizeof(NiObjectNET) == 0x18);

// 030
class NiTexture : public NiObjectNET
{
public:
	NiTexture();
	~NiTexture();

	virtual UInt32	GetWidth() = 0;
	virtual UInt32	GetHeight() = 0;

	// 8
	struct Str028
	{
		UInt32	unk0;
		UInt32	unk4;
	};

	class RendererData
	{
	public:
		virtual void	Destroy(bool arg);
		virtual UInt32	GetWidth();
		virtual UInt32	GetHeight();
		virtual void	Unk_03();
	};

	enum
	{
		kPixelLayout_Palette8BPP = 0,
		kPixelLayout_Raw16BPP,
		kPixelLayout_Raw32BPP,
		kPixelLayout_Compressed,
		kPixelLayout_Bumpmap,
		kPixelLayout_Palette4BPP,
		kPixelLayout_Default,
	};

	enum
	{
		kMipMap_Disabled = 0,
		kMipMap_Enabled,
		kMipMap_Default,
	};

	enum
	{
		kAlpha_None = 0,
		kAlpha_Binary,	// 1bpp
		kAlpha_Smooth,	// 8bpp
		kAlpha_Default,
	};

	UInt32			pixelLayout;	// 018
	UInt32			alphaFormat;	// 01C
	UInt32			mipmapFormat;	// 020
	RendererData	* rendererData;	// 024
	NiTexture		* nextTex;		// 028 - linked list updated in ctor/dtor
	NiTexture		* prevTex;		// 02C
};

// NiDX9Direct3DTexture - not referenced

// 048
class NiSourceTexture : public NiTexture
{
public:
	NiSourceTexture();
	~NiSourceTexture();

	virtual void	Unk_15();
	virtual void	FreePixelData();
	virtual bool	Unk_17();

	UInt8		unk030;				// 030 - is static?
	UInt8		unk031[3];			// 031
	void		* unk034;			// 034
	const char	* fileName;			// 038
	NiObject	* pixelData;		// 03C - NiPixelData
	UInt8		loadDirectToRender;	// 040
	UInt8		persistRenderData;	// 041
	UInt8		pad042[2];			// 042
	void		* unk044;			// 044
};

// 04C
class NiSourceCubeMap : public NiSourceTexture
{
public:
	NiSourceCubeMap();
	~NiSourceCubeMap();

	UInt32	unk048;	// 048
};

// 040
class NiRenderedTexture : public NiTexture
{
public:
	NiRenderedTexture();
	~NiRenderedTexture();

	struct Str030
	{
		UInt32	pad00;
		UInt32	pad04;
		UInt32	width;
		UInt32	height;
	};

	virtual Str030 *	Unk_15();

	Str030	* unk030;	// 030
	UInt32	pad034;		// 034
	UInt32	pad038;		// 038
	UInt32	pad03C;		// 03C
};

// 05C
class NiRenderedCubeMap : public NiRenderedTexture
{
public:
	NiRenderedCubeMap();
	~NiRenderedCubeMap();

	UInt32		unk040;		// 040
	NiObject	* faces[6];	// 044
};

// 018
class NiSequenceStreamHelper : public NiObjectNET
{
public:
	NiSequenceStreamHelper();
	~NiSequenceStreamHelper();
};

//	name			d3dfmt   00 01 04       08       0C       10       14       18       1C 1D 20       24       28 29 2C       30       34 35 38       3C       40 41
//	R8G8B8			00000014 01 18 00000000 00000000 00000014 00000000 00000002 00000000 08 01 00000001 00000000 08 01 00000000 00000000 08 01 00000013 00000005 00 01
//	A8R8G8B8		00000015 01 20 00000001 00000000 00000015 00000000 00000002 00000000 08 01 00000001 00000000 08 01 00000000 00000000 08 01 00000003 00000000 08 01
//	X8R8G8B8		00000016 01 20 00000000 00000000 00000016 00000000 00000002 00000000 08 01 00000001 00000000 08 01 00000000 00000000 08 01 0000000E 00000005 08 01
//	R5G6B5			00000017 01 10 00000000 00000000 00000017 00000000 00000002 00000000 05 01 00000001 00000000 06 01 00000000 00000000 05 01 00000013 00000005 00 01
//	X1R5G5B5		00000018 01 10 00000000 00000000 00000018 00000000 00000002 00000000 05 01 00000001 00000000 05 01 00000000 00000000 05 01 0000000E 00000005 01 01
//	A1R5G5B5		00000019 01 10 00000001 00000000 00000019 00000000 00000002 00000000 05 01 00000001 00000000 05 01 00000000 00000000 05 01 00000003 00000000 01 01
//	A4R4G4B4		0000001A 01 10 00000001 00000000 0000001A 00000000 00000002 00000000 04 01 00000001 00000000 04 01 00000000 00000000 04 01 00000003 00000000 04 01
//	R3G3B2			0000001B 01 0A 00000000 00000000 0000001B 00000000 00000002 00000000 02 01 00000001 00000000 03 01 00000000 00000000 03 01 0000000E 00000005 02 01
//	A8				0000001C 01 08 0000000B 00000000 0000001C 00000000 00000003 00000000 08 01 00000013 00000005 00 01 00000013 00000005 00 01 00000013 00000005 00 01
//	A8R3G3B2		0000001D 01 10 00000001 00000000 0000001D 00000000 00000002 00000000 02 01 00000001 00000000 03 01 00000000 00000000 03 01 00000003 00000000 08 01
//	X4R4G4B4		0000001E 01 10 00000000 00000000 0000001E 00000000 00000002 00000000 04 01 00000001 00000000 04 01 00000000 00000000 04 01 0000000E 00000000 04 01
//	A2B10G10R10		0000001F 01 20 00000001 00000000 0000001F 00000000 00000000 00000000 0A 01 00000001 00000000 0A 01 00000002 00000000 0A 01 00000003 00000000 02 01
//	A8B8G8R8		00000020 01 20 00000001 00000000 00000020 00000000 00000000 00000000 08 01 00000001 00000000 08 01 00000002 00000000 08 01 00000003 00000000 08 01
//	X8B8G8R8		00000021 01 20 00000000 00000000 00000021 00000000 00000000 00000000 08 01 00000001 00000000 08 01 00000002 00000000 08 01 0000000E 00000005 08 01
//	G16R16			00000022 01 20 0000000C 00000000 00000022 00000000 00000001 00000000 10 01 00000000 00000000 10 01 00000013 00000005 00 01 00000013 00000005 00 01
//	A2R10G10B10		00000023 01 20 00000001 00000000 00000023 00000000 00000002 00000000 0A 01 00000001 00000000 0A 01 00000000 00000000 0A 01 00000003 00000000 02 01
//	A16B16G16R16	00000024 01 40 00000001 00000000 00000024 00000000 00000000 00000001 10 01 00000001 00000001 10 01 00000002 00000001 10 01 00000003 00000001 10 01
//	A8P8			00000028 01 10 0000000C 00000000 00000028 00000000 00000010 00000003 08 01 00000003 00000000 08 01 00000013 00000005 00 01 00000013 00000005 00 01
//	P8				00000029 01 08 00000002 00000000 00000029 00000000 00000010 00000003 08 01 00000013 00000005 00 01 00000013 00000005 00 01 00000013 00000005 00 01
//	L8				00000032 01 08 0000000B 00000000 00000032 00000000 00000009 00000000 08 01 00000013 00000005 00 01 00000013 00000005 00 01 00000013 00000005 00 01
//	A8L8			00000033 01 10 0000000C 00000000 00000033 00000000 00000009 00000000 08 01 00000003 00000000 08 01 00000013 00000005 00 01 00000013 00000005 00 01
//	A4L4			00000034 01 08 0000000C 00000000 00000034 00000000 00000009 00000000 04 01 00000003 00000000 04 01 00000013 00000005 00 01 00000013 00000005 00 01
//	V8U8			0000003C 01 10 00000008 00000000 0000003C 00000000 00000005 00000000 08 01 00000006 00000000 08 01 00000013 00000005 00 01 00000013 00000005 00 01
//	L6V5U5			0000003D 01 10 00000009 00000000 0000003D 00000000 00000005 00000000 05 01 00000006 00000000 05 01 00000009 00000000 06 00 00000013 00000005 00 00
//	X8L8V8U8		0000003E 01 20 00000009 00000000 0000003E 00000000 00000005 00000000 08 01 00000006 00000000 08 01 00000009 00000000 08 00 0000000E 00000005 08 00
//	Q8W8V8U8		0000003F 01 20 00000008 00000000 0000003F 00000000 00000005 00000000 08 01 00000006 00000000 08 01 00000007 00000000 08 01 00000008 00000000 08 01
//	V16U16			00000040 01 20 00000008 00000000 00000040 00000000 00000005 00000000 10 01 00000006 00000000 10 01 00000013 00000005 00 01 00000013 00000005 00 01
//	A2W10V10U10		00000043 01 20 00000008 00000000 00000043 00000000 00000005 00000000 0A 01 00000006 00000000 0B 01 00000007 00000000 0B 01 00000013 00000005 00 01
//	D16_LOCKABLE	00000046 01 10 0000000F 00000000 00000046 00000000 00000011 00000000 10 01 00000013 00000005 00 01 00000013 00000005 00 01 00000013 00000005 00 01
//	D32				00000047 01 20 0000000F 00000000 00000047 00000000 00000011 00000000 20 01 00000013 00000005 00 01 00000013 00000005 00 01 00000013 00000005 00 01
//	D15S1			00000049 01 10 0000000F 00000000 00000049 00000000 00000012 00000000 01 01 00000011 00000000 0F 01 00000013 00000005 00 01 00000013 00000005 00 01
//	D24S8			0000004B 01 20 0000000F 00000000 0000004B 00000000 00000012 00000000 08 01 00000011 00000000 18 01 00000013 00000005 00 01 00000013 00000005 00 01
//	D24X8			0000004D 01 20 0000000F 00000000 0000004D 00000000 0000000E 00000000 08 01 00000011 00000000 18 01 00000013 00000005 00 01 00000013 00000005 00 01
//	D24X4S4			0000004F 01 20 0000000F 00000000 0000004F 00000000 00000012 00000000 04 01 0000000E 00000000 04 01 00000011 00000000 18 01 00000013 00000005 00 01
//	D16				00000050 01 10 0000000F 00000000 00000050 00000000 00000011 00000000 10 01 00000013 00000005 00 01 00000013 00000005 00 01 00000013 00000005 00 01
//	L16				00000051 01 10 0000000B 00000000 00000051 00000000 00000009 00000000 10 01 00000013 00000005 00 01 00000013 00000005 00 01 00000013 00000005 00 01
//	D32F_LOCKABLE	00000052 01 20 0000000B 00000000 00000052 00000000 0000000E 00000005 20 01 00000013 00000005 00 01 00000013 00000005 00 01 00000013 00000005 00 01
//	D24FS8			00000053 01 20 0000000B 00000000 00000053 00000000 0000000E 00000005 20 01 00000013 00000005 00 01 00000013 00000005 00 01 00000013 00000005 00 01
//	Q16W16V16U16	0000006E 01 40 0000000B 00000000 0000006E 00000000 0000000E 00000005 40 01 00000013 00000005 00 01 00000013 00000005 00 01 00000013 00000005 00 01
//	R16F			0000006F 01 10 0000000B 00000000 0000006F 00000000 00000000 00000001 10 01 00000013 00000005 00 01 00000013 00000005 00 01 00000013 00000005 00 01
//	G16R16F			00000070 01 20 0000000C 00000000 00000070 00000000 00000000 00000001 10 01 00000001 00000001 10 01 00000013 00000005 00 01 00000013 00000005 00 01
//	A16B16G16R16F	00000071 01 40 00000001 00000000 00000071 00000000 00000000 00000001 10 01 00000001 00000001 10 01 00000002 00000001 10 01 00000003 00000001 10 01
//	R32F			00000072 01 20 0000000B 00000000 00000072 00000000 00000000 00000002 20 01 00000013 00000005 00 01 00000013 00000005 00 01 00000013 00000005 00 01
//	G32R32F			00000073 01 40 0000000C 00000000 00000073 00000000 00000000 00000002 20 01 00000001 00000002 20 01 00000013 00000005 00 01 00000013 00000005 00 01
//	A32B32G32R32F	00000074 01 80 00000001 00000000 00000074 00000000 00000000 00000002 20 01 00000001 00000002 20 01 00000002 00000002 20 01 00000003 00000002 20 01
//	CxV8U8			00000075 01 10 0000000B 00000000 00000075 00000000 0000000E 00000005 10 01 00000013 00000005 00 01 00000013 00000005 00 01 00000013 00000005 00 01
//	DXT1			xxxxxxxx 01 00 00000004 00000000 xxxxxxxx 00000000 00000004 00000004 00 01 00000013 00000005 00 01 00000013 00000005 00 01 00000013 00000005 00 01
//	DXT3			xxxxxxxx 01 00 00000005 00000000 xxxxxxxx 00000000 00000004 00000004 00 01 00000013 00000005 00 01 00000013 00000005 00 01 00000013 00000005 00 01
//	DXT5			xxxxxxxx 01 00 00000006 00000000 xxxxxxxx 00000000 00000004 00000004 00 01 00000013 00000005 00 01 00000013 00000005 00 01 00000013 00000005 00 01

//	invalid			xxxxxxxx 01 00 0000000B 00000000 xxxxxxxx 00000000 0000000E 00000005 00 01 00000013 00000005 00 01 00000013 00000005 00 01 00000013 00000005 00 01
//	D32_LOCKABLE	00000054 01 00 0000000B 00000000 00000054 00000000 0000000E 00000005 00 01 00000013 00000005 00 01 00000013 00000005 00 01 00000013 00000005 00 01
//	S8_LOCKABLE		00000055 01 00 0000000B 00000000 00000055 00000000 0000000E 00000005 00 01 00000013 00000005 00 01 00000013 00000005 00 01 00000013 00000005 00 01
//	VERTEXDATA		00000064 01 00 0000000B 00000000 00000064 00000000 0000000E 00000005 00 01 00000013 00000005 00 01 00000013 00000005 00 01 00000013 00000005 00 01
//	INDEX16			00000065 01 00 0000000B 00000000 00000065 00000000 0000000E 00000005 00 01 00000013 00000005 00 01 00000013 00000005 00 01 00000013 00000005 00 01
//	INDEX32			00000066 01 00 0000000B 00000000 00000066 00000000 0000000E 00000005 00 01 00000013 00000005 00 01 00000013 00000005 00 01 00000013 00000005 00 01

// 44
struct TextureFormat
{
	enum
	{
		kFormat_RGB = 0,		// 0
		kFormat_RGBA,			// 1
		kFormat_A,				// 2
		kFormat_Unk3,			// 3
		kFormat_DXT1,			// 4
		kFormat_DXT3,			// 5
		kFormat_DXT5,			// 6
		kFormat_Unk7,			// 7
		kFormat_Bump,			// 8
		kFormat_BumpLuminance,	// 9
		kFormat_UnkA,			// A
		kFormat_Other,			// B - A8 L8 L16 D32F_LOCKABLE D24FS8 Q16W16V16U16 R16F R32F CxV8U8
		kFormat_Other2,			// C - G16R16 A8P8 A8L8 A4L4 G16R16F G32R32F
		kFormat_UnkD,			// D
		kFormat_UnkE,			// E
		kFormat_Depth,			// F
	};

	enum
	{
		kType_Blue,			// 00
		kType_Green,		// 01
		kType_Red,			// 02
		kType_Alpha,		// 03
		kType_Unk04,		// 04
		kType_BumpU,		// 05
		kType_BumpV,		// 06
		kType_Unk07,		// 07
		kType_Unk08,		// 08
		kType_Luminance,	// 09
		kType_Unk0A,		// 0A
		kType_Unk0B,		// 0B
		kType_Unk0C,		// 0C
		kType_Unk0D,		// 0D
		kType_Unused,		// 0E
		kType_Unk0F,		// 0F
		kType_PalIdx,		// 10
		kType_Depth,		// 11
		kType_Stencil,		// 12
		kType_None,			// 13
	};

	enum
	{
		kType2_Default,		// 00
		kType2_16Bit,		// 01
		kType2_32Bit,		// 02
		kType2_Palettized,	// 03
		kType2_Compressed,	// 04
		kType2_None,		// 05
	};

	UInt8	unk00;		// 00 - always 01? (checked all D3DFMT)
	UInt8	bpp;		// 01 - zero for dxt
	UInt8	pad02[2];	// 02
	UInt32	format;		// 04 - default kFormat_A (really)
	UInt32	unk08;		// 08 - always 00000000? (checked all D3DFMT)
	UInt32	d3dfmt;		// 0C
	UInt32	unk10;		// 10 - always 00000000? (checked all D3DFMT)

	struct Channel
	{
		UInt32	type;		// 0
		UInt32	type2;		// 4
		UInt8	bits;		// 8
		UInt8	unk9;		// 9 - only seen non-01 when unused (L6V5U5 X8L8V8U8)
		UInt8	padA[2];	// A
	};

	Channel	channels[4];	// 14

	void InitFromD3DFMT(UInt32 fmt);
};

// 070
class NiPixelData : public NiObject
{
public:
	NiPixelData();
	~NiPixelData();

	// face size = unk05C[mipmapLevels]
	// total size = face size * numFaces

	TextureFormat	format;		// 008
	NiRefObject		* unk04C;	// 04C
	UInt32	unk050;			// 050
	UInt32	* width;		// 054 - array for mipmaps?
	UInt32	* height;		// 058
	UInt32	* unk05C;		// 05C - sizes?
	UInt32	mipmapLevels;	// 060
	UInt32	unk064;			// 064
	UInt32	unk068;			// 068
	UInt32	numFaces;		// 06C
};

class ControlledBlock;

// 0C
class NiInterpolator : public NiObject
{
public:
	NiInterpolator();
	~NiInterpolator();

	virtual void	Unk_23();
	virtual void	Unk_24();
	virtual void	Unk_25();
	virtual void	Unk_26();
	virtual void	Unk_27();
	virtual void	Unk_28();
	virtual void	Unk_29();
	virtual void	Unk_2A();
	virtual void	Unk_2B();
	virtual void	Unk_2C();
	virtual void	Unk_2D();
	virtual void	Unk_2E();
	virtual void	Unk_2F();
	virtual void	Unk_30();
	virtual void	Unk_31();
	virtual void	Unk_32();
	virtual void	Unk_33();
	virtual void	Unk_34();
	virtual void	Unk_35();
	virtual void	Unk_36();

	float m_lastTime;

};

struct UpdateParams
{
	float		timePassed;
	bool		updateControllers;
	UInt8		byte05;
	UInt8		byte06;
	UInt8		byte07;
	UInt8		byte08;
	UInt8		pad09[3];

	UpdateParams() { ZeroMemory(this, sizeof(UpdateParams)); }
};

// 34
class NiTimeController : public NiObject
{
public:
	/*8C*/virtual void		Unk_23();
	/*90*/virtual void		Unk_24();
	/*94*/virtual void		Update(UpdateParams& updParams);
	/*98*/virtual void		SetTarget(NiNode* pTarget);
	/*9C*/virtual void		Unk_27();
	/*A0*/virtual void		Unk_28();
	/*A4*/virtual void		Unk_29();
	/*A8*/virtual void		Unk_2A();
	/*AC*/virtual void		Unk_2B();
	/*B0*/virtual void		Unk_2C();

	UInt16				flags;				// 08
	UInt16				unk0A;				// 0A
	float				frequency;			// 0C
	float				phaseTime;			// 10
	float				lowKeyTime;			// 14
	float				highKeyTime;		// 18
	float				startTime;			// 1C
	float				lastTime;			// 20
	float				weightedLastTime;	// 24
	float				scaledTime;			// 28
	NiNode* target;			// 2C
	NiTimeController* nextCtrl;			// 30
};

class NiDefaultAVObjectPalette;

// 7C
class NiControllerManager : public NiTimeController
{
public:
	/*B4*/virtual void		Unk_2D();

	NiTArray<NiControllerSequence*>				sequences;		// 34
	void* ptr44;			// 44
	UInt32										unk48;			// 48
	UInt32										unk4C;			// 4C
	NiTStringPointerMap<NiControllerSequence*>	seqStrMap;		// 50	Case-sensitive!
	NiTArray<void*>* arr64;			// 64
	UInt32										unk68;			// 68
	UInt32										unk6C;			// 6C
	UInt32										unk70;			// 70
	UInt32										unk74;			// 74
	NiDefaultAVObjectPalette* defObjPlt;		// 78

	NiControllerSequence* FindSequence(const char* seqName);
};
static_assert(sizeof(NiControllerManager) == 0x7C);

class NiInterpController : public NiTimeController
{
};

class NiBlendInterpolator : public NiInterpolator
{
public:
	struct InterpArrayItem
	{
		NiPointer<NiTransformInterpolator> m_spInterpolator;
		float m_fWeight;
		float m_fNormalizedWeight;
		char m_cPriority;
		float m_fEaseSpinner;
		float m_fUpdateTime;
	};
	unsigned char m_uFlags;
	unsigned char m_ucArraySize;
	unsigned char m_ucInterpCount;
	unsigned char m_ucSingleIdx;
	unsigned char m_cHighPriority;
	unsigned char m_cNextHighPriority;
	InterpArrayItem* m_pkInterpArray;
	NiInterpolator* m_pkSingleInterpolator;
	float m_fWeightThreshold;
	float m_fSingleTime;
	float m_fHighSumOfWeights;
	float m_fNextHighSumOfWeights;
	float m_fHighEaseSpinner;
};

class NiBlendTransformInterpolator : public NiBlendInterpolator
{
};

/* 44137 */
class NiMultiTargetTransformController : NiInterpController
{
public:
	NiBlendTransformInterpolator* m_pkBlendInterps;
	NiAVObject** m_ppkTargets;
	unsigned __int16 m_usNumInterps;
};

struct NiFixedString
{
private:
	char* data;
public:
	const char* CStr() const
	{
		return data ? data : "";
	}
};


// 068
class NiControllerSequence : public NiObject
{
public:
	NiControllerSequence();
	~NiControllerSequence();
	virtual bool		Unk_23(float arg1, UInt8 arg2);

	enum
	{
		kState_Inactive = 0,
		kState_Animating,
		kState_EaseIn,
		kState_EaseOut,
		kState_TransSource,
		kState_TransDest,
		kState_MorphSource
	};

	enum
	{
		kCycle_Loop = 0,
		kCycle_Reverse,
		kCycle_Clamp,
	};

	// 10
	struct Unk014
	{
		NiRefObject	* unk00;	// 00
		NiRefObject	* unk04;	// 04
		UInt32		unk08;		// 08
		UInt8		unk0C;		// 0C
		UInt8		unk0D;		// 0D
		UInt8		pad0E[2];	// 0E
	};

	// 10
	struct Unk018
	{
		NiRefObject	* unk00;	// 00
		UInt16		unk04;		// 04
		UInt16		unk06;		// 06
		UInt16		unk08;		// 08
		UInt16		unk0A;		// 0A
		UInt16		unk0C;		// 0C
		UInt8		pad0E[2];	// 0E
	};

	struct ControlledBlock
	{
		NiTransformInterpolator* interpolator;
		NiMultiTargetTransformController* multiTargetCtrl;
		NiBlendInterpolator* blendInterpolator;
		UInt8 blendIdx;
		UInt8 priority;
		UInt8 gap0E[2];
	};

	struct IDTag
	{
		NiFixedString m_kAVObjectName;
		NiFixedString m_kPropertyType;
		NiFixedString m_kCtlrType;
		NiFixedString m_kCtlrID;
		NiFixedString m_kInterpolatorID;
	};

	enum FlagsKNVSE
	{
		kFlag_DestframeStartTime = 1
	};

	enum AnimState
	{
		kAnimState_Inactive = 0x0,
		kAnimState_Animating = 0x1,
		kAnimState_EaseIn = 0x2,
		kAnimState_EaseOut = 0x3,
		kAnimState_TransSource = 0x4,
		kAnimState_TransDest = 0x5,
		kAnimState_MorphSource = 0x6,
	};

	enum CycleType
	{
		LOOP = 0x0,
		REVERSE = 0x1,
		CLAMP = 0x2,
		MAX_CYCLE_TYPES = 0x3,
	};

	const char* sequenceName; // 8
	UInt32 numControlledBlocks; // C
	UInt32 arrayGrowBy; // 10
	NiControllerSequence::ControlledBlock* controlledBlocks; // 14
	NiControllerSequence::IDTag* IDTagArray; // 18
	float seqWeight; // 1C
	NiTextKeyExtraData* textKeyData; // 20
	CycleType cycleType;
	float frequency;
	float beginKeyTime;
	float endKeyTime;
	float lastTime;
	float weightedLastTime;
	float lastScaledTime;
	NiControllerManager* owner;
	AnimState state;
	float offset;
	float startTime;
	float endTime;
	float destFrame;
	NiControllerSequence* partnerSequence;
	const char* accumRootName;
	UInt32 node60_maybeAccumRoot;
	UInt32 kNVSEFlags; // deprecated string palette
	SInt16 curAnimNIdx;
	UInt16 wrd6A;
	UInt32 spNotesA;
	UInt16 numNotes;
	UInt8 hasHashHashAtStartOfNodeName;
	UInt8 byte73;

	bool Play();
	void SetStartOffset(float offset)
	{
		destFrame = offset;
		kNVSEFlags |= kFlag_DestframeStartTime;
	}
};
static_assert(sizeof(NiControllerSequence) == 0x74);

// 06C
class BSAnimGroupSequence : public NiControllerSequence
{
public:
	BSAnimGroupSequence();
	~BSAnimGroupSequence();

	TESAnimGroup		* animGroup;	//068

	BSAnimGroupSequence* Get3rdPersonCounterpart() const;
};
static_assert(sizeof(BSAnimGroupSequence) == 0x78);

const auto s = sizeof(BSAnimGroupSequence);

class NiBinaryStream
{
public:
	NiBinaryStream();
	~NiBinaryStream();

	virtual void	Destructor(bool freeMemory);		// 00
	virtual void	Unk_01();							// 04
	virtual void	SeekCur(SInt32 delta);				// 08
	virtual void	GetBufferSize();					// 0C
	virtual void	InitReadWriteProcs(bool useAlt);	// 10

//	void	** m_vtbl;		// 000
	UInt32	m_offset;		// 004
	void*	m_readProc;		// 008 - function pointer
	void*	m_writeProc;	// 00C - function pointer
};
static_assert(sizeof(NiBinaryStream) == 0x10);

class NiFile: public NiBinaryStream
{
public:
	NiFile();
	~NiFile();

	virtual void	Seek();			// 14
	virtual UInt32	GetFilename();	// 18
	virtual void	Unk_07();		// 1C

	UInt32	m_bufSize;	// 010
	UInt32	m_unk014;	// 014 - Total read in buffer
	UInt32	m_unk018;	// 018 - Consumed from buffer
	UInt32	m_unk01C;	// 01C
	void*	m_buffer;	// 020
	FILE*	m_File;		// 024
};
static_assert(sizeof(NiFile) == 0x28);

// 158
class BSFile : NiFile
{
public:
	BSFile();
	~BSFile();

	virtual void	Reset();	// 20
	virtual void	Unk_09();	// 24
	virtual void	Unk_0A();	// 28
	virtual void	Unk_0B();	// 2C
	virtual void	Unk_0C();	// 30
	virtual void	Read();		// 34
	virtual void	Write();	// 38

	UInt32		m_modeReadWriteAppend;	// 028
	UInt8		m_good;					// 02C
	UInt8		pad02D[3];				// 02D
	UInt8		m_unk030;				// 030
	UInt8		pad031[3];				// 031
	UInt32		m_unk034;				// 034
	UInt32		m_unk038;				// 038 - init'd to FFFFFFFF
	UInt32		m_unk03C;				// 038
	UInt32		m_unk040;				// 038
	char		m_path[0x104];			// 044
	UInt32		m_unk148;				// 148
	UInt32		m_unk14C;				// 14C
	UInt32		m_fileSize;				// 150
	UInt32		m_unk154;				// 154
};
static_assert(sizeof(BSFile) == 0x158);

struct ArchiveFile : BSFile
{
	UInt32 unk158;
	UInt32 unk15C;
};
static_assert(sizeof(ArchiveFile) == 0x160);

struct CompressedArchiveFile : ArchiveFile
{
	void* ptr160;
	void* ptr164;
	UInt32 streamLength;
	UInt32 unk16C;
	UInt32 streamOffset;
	UInt32 unk174;
};

/**** misc non-NiObjects ****/

// 30
class NiPropertyState : public NiRefObject
{
public:
	NiPropertyState();
	~NiPropertyState();

	UInt32	unk008[(0x30 - 0x08) >> 2];	// 008
};

// 20
class NiDynamicEffectState : public NiRefObject
{
public:
	NiDynamicEffectState();
	~NiDynamicEffectState();

	UInt8	unk008;		// 008
	UInt8	pad009[3];	// 009
	UInt32	unk00C;		// 00C
	UInt32	unk010;		// 010
	UInt32	unk014;		// 014
	UInt32	unk018;		// 018
	UInt32	unk01C;		// 01C
};

// name is a guess
class NiCulledGeoList
{
public:
	NiCulledGeoList();
	~NiCulledGeoList();

	NiGeometry	** m_geo;		// 00
	UInt32		m_numItems;		// 04
	UInt32		m_bufLen;		// 08
	UInt32		m_bufGrowSize;	// 0C
};

// 90
class NiCullingProcess
{
public:
	NiCullingProcess();
	~NiCullingProcess();

	virtual void	Destructor(bool freeMemory);
	virtual void	Unk_01(void * arg);
	virtual void	Cull(NiCamera * camera, NiAVObject * scene, NiCulledGeoList * culledGeo);
	virtual void	AddGeo(NiGeometry * arg);

//	void			** m_vtbl;		// 00
	UInt8			m_useAddGeoFn;	// 04 - call AddGeo when true, else just add to the list
	UInt8			pad05[3];		// 05
	NiCulledGeoList	* m_culledGeo;	// 08
};

class NiTextKey : public NiMemObject
{
public:
	float m_fTime;
	NiFixedString m_kText;
};


class NiExtraData : public NiObject
{
public:
	NiFixedString m_kName;
};

// 24
class BSBound : public NiExtraData
{
public:
	NiPoint3		centre;			// 0C
	NiPoint3		dimensions;		// 18
};

class NiTextKeyExtraData : public NiExtraData
{
public:
	unsigned int m_uiNumKeys;
	NiTextKey* m_pKeys;
};


struct NiQuatTransform
{
	NiPoint3 m_kTranslate;
	NiPoint4 m_kRotate;
	float m_fScale;
};

/* 1224 */
enum KeyType
{
	NOINTERP = 0x0,
	LINKEY = 0x1,
	BEZKEY = 0x2,
	TCBKEY = 0x3,
	EULERKEY = 0x4,
	STEPKEY = 0x5,
	NUMKEYTYPES = 0x6,
};

struct NiAnimationKey
{
	float m_fTime;
};

struct NiRotKey : NiAnimationKey
{
	NiPoint4 m_quat;
};

struct NiPosKey : NiAnimationKey
{
	NiPoint3 m_Pos;
};

struct NiFloatKey : NiAnimationKey
{
	float m_fValue;
};

class NiTransformData : public NiObject
{
public:
	unsigned __int16 m_usNumRotKeys;
	unsigned __int16 m_usNumPosKeys;
	unsigned __int16 m_usNumScaleKeys;
	KeyType m_eRotType;
	KeyType m_ePosType;
	KeyType m_eScaleType;
	unsigned __int8 m_ucRotSize;
	unsigned __int8 m_ucPosSize;
	unsigned __int8 m_ucScaleSize;
	NiRotKey* m_pkRotKeys;
	NiPosKey* m_pkPosKeys;
	NiFloatKey* m_pkScaleKeys;
};

struct NiKeyBasedInterpolator : NiInterpolator
{
};

class NiTransformInterpolator : public NiKeyBasedInterpolator
{
public:
	NiQuatTransform m_kTransformValue;
	NiPointer<NiTransformData> m_spData;
	unsigned __int16 m_usLastTransIdx;
	unsigned __int16 m_usLastRotIdx;
	unsigned __int16 m_usLastScaleIdx;
	bool bPose;
};

class NiProperty : public NiObjectNET
{
public:
	NiProperty();
	~NiProperty();

	virtual UInt32	GetPropertyType();
	virtual void	UpdateController(float arg);

	enum Type
	{
		kPropertyType_Alpha = 0,
		kPropertyType_Culling = 1,
		kPropertyType_Material = 2,
		kPropertyType_Shade = 3,
		kPropertyType_TileShader = kPropertyType_Shade,
		kPropertyType_Stencil = 4,
		kPropertyType_Texturing = 5,
		kPropertyType_Dither = 8,
		kPropertyType_Specular = 9,
		kPropertyType_VertexColor = 10,
		kPropertyType_ZBuffer = 11,
		kPropertyType_Fog = 13,
	};
};
class NiTexturingProperty : public NiProperty
{
public:
	NiTexturingProperty();
	~NiTexturingProperty();

	UInt32				unk18[6];	// 18
};


#pragma once
#include <Containers.h>
#include <NiTypes.h>
#include <NiNodes.h>

// UNMODIFIED OBSE FILE. I need NiNode class definition.

/***										type
 *	NiAVObject
 *		NiDynamicEffect
 *			NiLight
 *				NiDirectionalLight			01
 *				NiPointLight				02
 *					NiSpotLight				03
 *				NiAmbientLight				00
 *			NiTextureEffect					04
 *		NiNode
 *			SceneGraph
 *			BSTempNodeManager
 *			BSTempNode
 *			BSCellNode
 *			BSClearZNode
 *			BSFadeNode
 *			BSScissorNode
 *			BSTimingNode
 *			BSFaceGenNiNode
 *			NiBillboardNode
 *			NiSwitchNode
 *				NiLODNode
 *					NiBSLODNode
 *			NiSortAdjustNode
 *			NiBSPNode
 *			ShadowSceneNode
 *		NiCamera
 *			BSCubeMapCamera					RTTI data incorrect
 *			NiScreenSpaceCamera
 *		NiGeometry
 *			NiLines
 *			NiTriBasedGeom
 *				NiTriShape
 *					BSScissorTriShape
 *					NiScreenElements
 *					NiScreenGeometry
 *					TallGrassTriShape
 *				NiTriStrips
 *					TallGrassTriStrips
 *			NiParticles
 *				NiParticleSystem
 *					NiMeshParticleSystem
 *				NiParticleMeshes
 */

class NiCamera;
class NiLODData;
class ShadowSceneLight;	// 220, derives from NiRefObject
class BSImageSpaceShader;
class NiScreenPolygon;
class NiScreenTexture;
class NiPSysModifier;
class NiRenderer;
class NiGeometryData;

// 9C
class NiAVObject : public NiObjectNET
{
public:
	/*08C*/virtual void		Unk_23(UInt32 arg1);
	/*090*/virtual void		Unk_24(NiMatrix33* arg1, NiPoint3* arg2, bool arg3);
	/*094*/virtual void		Unk_25(UInt32 arg1);
	/*098*/virtual void		Unk_26(UInt32 arg1);
	/*09C*/virtual NiAVObject* GetObjectByName(void* objName);
	/*0A0*/virtual void		Unk_28(UInt32 arg1, UInt32 arg2, UInt32 arg3);
	/*0A4*/virtual void		Unk_29(void* updParams, UInt32 arg2);
	/*0A8*/virtual void		Unk_2A(UInt32 arg1, UInt32 arg2);
	/*0AC*/virtual void		Unk_2B(UInt32 arg1, UInt32 arg2);
	/*0B0*/virtual void		Unk_2C(UInt32 arg1);
	/*0B4*/virtual void		Unk_2D(UInt32 arg1);
	/*0B8*/virtual void		UpdateTransform(void* updInfo);
	/*0BC*/virtual void		Unk_2F();
	/*0C0*/virtual void		UpdateBounds(void* updInfo);
	/*0C4*/virtual void		Unk_31(UInt32 arg1, UInt32 arg2);
	/*0C8*/virtual void		Unk_32(UInt32 arg1);
	/*0CC*/virtual void		Unk_33(UInt32 arg1);
	/*0D0*/virtual void		Unk_34();
	/*0D4*/virtual void		Unk_35(UInt32 arg1);
	/*0D8*/virtual void		Unk_36(UInt32 arg1);

	enum NiFlags
	{
		kNiFlag_Hidden = 0x00000001,
		kNiFlag_SelectiveUpdate = 0x00000002,
		kNiFlag_SelUpdTransforms = 0x00000004,
		kNiFlag_SelUpdController = 0x00000008,
		kNiFlag_SelUpdRigid = 0x00000010,
		kNiFlag_DisplayObject = 0x00000020,
		kNiFlag_DisableSorting = 0x00000040,
		kNiFlag_SelUpdTransformsOverride = 0x00000080,
		kNiFlag_UnkBit8 = 0x00000100,
		kNiFlag_SaveExternalGeomData = 0x00000200,
		kNiFlag_NoDecals = 0x00000400,
		kNiFlag_AlwaysDraw = 0x00000800,
		kNiFlag_MeshLOD = 0x00001000,
		kNiFlag_FixedBound = 0x00002000,
		kNiFlag_TopFadeNode = 0x00004000,
		kNiFlag_IgnoreFade = 0x00008000,
		kNiFlag_NoAnimSyncX = 0x00010000,
		kNiFlag_NoAnimSyncY = 0x00020000,
		kNiFlag_NoAnimSyncZ = 0x00040000,
		kNiFlag_NoAnimSyncS = 0x00080000,
		kNiFlag_NoDismember = 0x00100000,
		kNiFlag_NoDismemberValidity = 0x00200000,
		kNiFlag_RenderUse = 0x00400000,
		kNiFlag_MaterialsApplied = 0x00800000,
		kNiFlag_HighDetail = 0x01000000,
		kNiFlag_ForceUpdate = 0x02000000,
		kNiFlag_PreProcessedNode = 0x04000000,
		kNiFlag_UnkBit27 = 0x08000000,
		kNiFlag_UnkBit28 = 0x10000000,
		kNiFlag_IsPointLight = 0x20000000,	//	JIP only
		kNiFlag_DoneInitLights = 0x40000000,	//	JIP only
		kNiFlag_IsInserted = 0x80000000	//	JIP only
	};

	NiNode*					m_parent;				// 18
	void*					m_collisionObject;		// 1C
	NiSphere*				m_kWorldBound;			// 20
	DList<NiProperty>		m_propertyList;			// 24
	UInt32					m_flags;				// 30
	NiTransform				m_localTransform;		// 34
	NiTransform				m_worldTransform;		// 68

	void Update();
	UInt32 GetIndex();
	bool __fastcall ReplaceObject(NiAVObject* object);
	NiProperty* __fastcall GetProperty(UInt32 propID);

	void DumpProperties();
	void DumpParents();
};
static_assert(sizeof(NiAVObject) == 0x9C);

// DC+
class NiDynamicEffect : public NiAVObject
{
public:
	NiDynamicEffect();
	~NiDynamicEffect();

	virtual UInt32	GetEffectType();

	UInt8	enable;		// 0AC
	UInt8	pad0AD[3];	// 0AD
	UInt32	unk0B0;		// 0B0 - init'd to monotonically increasing number (uid?)
	UInt32	unk0B4;		// 0B4
	UInt32	unk0B8;		// 0B8 - init'd to 1

	NiTPointerList <NiNode *>	affectedNodes;		// 0BC
	NiTPointerList <NiNode *>	unaffectedNodes;	// 0CC
};

// 108
class NiLight : public NiDynamicEffect
{
public:
	NiLight();
	~NiLight();

	float	m_fDimmer;	// 0DC
	NiColor	m_kAmb;		// 0E0
	NiColor	m_kDiff;	// 0EC
	NiColor	m_kSpec;	// 0F8
	UInt32	unk104;		// 104
};

// 114
class NiDirectionalLight : public NiLight
{
public:
	NiDirectionalLight();
	~NiDirectionalLight();

	// UpdateTransform ticks unk0B8 and copies m_direction

	enum { kType = 1 };

	NiPoint3	m_direction;	// 108
};

// 114
class NiPointLight : public NiLight
{
public:
	NiPointLight();
	~NiPointLight();

	// UpdateTransform ticks unk0B8

	enum { kType = 2 };

	float	m_fAtten0;	// 108
	float	m_fAtten1;	// 10C
	float	m_fAtten2;	// 110
};

// 128
class NiSpotLight : public NiPointLight
{
public:
	NiSpotLight();
	~NiSpotLight();

	// UpdateTransform ticks unk0B8 and copies m_kWorldDir

	enum { kType = 3 };

	NiPoint3	m_kWorldDir;		// 114
	float		m_fSpotAngle;		// 120
	float		m_fSpotExponent;	// 124
};

// 108
class NiAmbientLight : public NiLight
{
public:
	NiAmbientLight();
	~NiAmbientLight();

	enum { kType = 0 };
};

// 174
class NiTextureEffect : public NiDynamicEffect
{
public:
	NiTextureEffect();
	~NiTextureEffect();

	enum { kType = 4 };

	enum
	{
		kTextureMode_ProjectedLight = 0,
		kTextureMode_ProjectedShadow,
		kTextureMode_EnvironmentMap,
		kTextureMode_FogMap,
	};

	enum
	{
		kCoordMode_WorldParallel = 0,
		kCoordMode_WorldPerspective,
		kCoordMode_SphereMap,
		kCoordMode_SpecularCubeMap,
		kCoordMode_DiffuseCubeMap,
	};

	NiMatrix33	m_kModelProjMat;	// 0DC
	NiPoint3	m_kModelProjTrans;	// 100
	NiMatrix33	m_kWorldProjMat;	// 10C
	NiPoint3	m_kWorldProjTrans;	// 130
	NiObject	* m_texture;		// 13C
	UInt32		m_eFilter;			// 140 - see NiTexturingProperty::kFilterMode_* without the shift
	UInt32		m_eClamp;			// 144 - see NiTexturingProperty::kClampMode_* without the shift
	UInt32		m_eTextureMode;		// 148
	UInt32		m_eCoordMode;		// 14C
	UInt8		m_bPlaneEnable;		// 150
	UInt8		pad151[3];			// 151
	NiPlane		m_kModelPlane;		// 154
	NiPlane		m_kWorldPlane;		// 164
};


// AC
class NiNode : public NiAVObject
{
public:
	/*0DC*/virtual void		AddObject(NiAVObject* object, bool arg2);
	/*0E0*/virtual void		AddObjectAt(UInt32 index, NiAVObject* object);
	/*0E4*/virtual void		RemoveObject2(NiAVObject* toRemove, NiAVObject** arg2);
	/*0E8*/virtual void		RemoveObject(NiAVObject* toRemove);	//	Calls RemoveObject2 with arg2 as ptr to NULL
	/*0EC*/virtual void		RemoveNthObject2(UInt32 index, NiAVObject** arg2);
	/*0F0*/virtual void		RemoveNthObject(UInt32 index);			//	Calls RemoveNthObject2 with arg2 as ptr to NULL
	/*0F4*/virtual void		Unk_3D(UInt32 arg1, UInt32 arg2, UInt32 arg3);
	/*0F8*/virtual void		Unk_3E(UInt32 arg1, UInt32 arg2);
	/*0FC*/virtual void		Unk_3F();

	NiTArray<NiAVObject*>	m_children;		// 9C

	static NiNode* __stdcall Create(const char* nameStr);		//	str of NiString
	NiNode* CreateCopy();
	NiAVObject* __fastcall GetBlockByName(const char* nameStr);	//	str of NiString
	NiAVObject* __fastcall GetBlock(const char* blockName);
	NiNode* __fastcall GetNode(const char* nodeName) const;
	bool IsMovable();
	void RemoveCollision();
	void BulkSetMaterialPropertyTraitValue(UInt32 traitID, float value);
	bool HasPhantom();
	void GetBodyMass(float* totalMass);
	void ApplyForce(NiPoint4* forceVector);
	void Dump();
};
static_assert(sizeof(NiNode) == 0xAC);

// F0
class SceneGraph : public NiNode
{
public:
	SceneGraph();
	~SceneGraph();

	NiCamera			* camera;			// 0DC
	UInt32				unk0E0;				// 0E0
	NiCullingProcess	* cullingProcess;	// 0E4
	UInt32				unk0E8;				// 0E8
	float				cameraFOV;			// 0EC
};
//static_assert(sizeof(SceneGraph) == 0x0F0);

// E0
class BSTempNodeManager : public NiNode
{
public:
	BSTempNodeManager();
	~BSTempNodeManager();

	// overrides Unk_18 and related to scan children for BSTempNodes
	// removes them? tests against unk0DC

	float	unk0DC;	// 0DC
};

// E0
class BSTempNode : public NiNode
{
public:
	BSTempNode();
	~BSTempNode();

	float	unk0DC;	// 0DC
};

// BSCellNode - in RTTI but unref'd

// E8
class BSClearZNode : public NiNode
{
public:
	BSClearZNode();
	~BSClearZNode();

	// in Draw, scan for BSShaderAccumulator on the renderer, set 21E0 to 0 before calling parent Draw, reset to 1 afterwards

	UInt8	unk0DC;	// 0DC
	UInt8	unk0DD;	// 0DD
	float	unk0E0;	// 0E0 - init'd to 283840
	float	unk0E4;	// 0E4 - init'd to 100
};

// F0
class BSFadeNode : public NiNode
{
public:
	BSFadeNode();
	~BSFadeNode();

	// overload Draw to do LOD-based fade

	UInt8	unk0DC;			// 0DC
	UInt8	unk0DD[3];		// 0DD
	float	fNearDistSqr;	// 0E0
	float	fFarDistSqr;	// 0E4
	float	fCurrentAlpha;	// 0E8
	UInt8	cMultType;		// 0EC
	UInt8	unk0ED[3];		// 0ED
};

// EC
class BSScissorNode : public NiNode
{
public:
	BSScissorNode();
	~BSScissorNode();

	// mess about with renderer in Draw (presumably to set scissor mode)

	UInt32	unk0DC;	// 0DC
	UInt32	unk0E0;	// 0E0
	UInt32	unk0E4;	// 0E4
	UInt32	unk0E8;	// 0E8
};

// BSTimingNode - unref'd

// 118
class BSFaceGenNiNode : public NiNode
{
public:
	BSFaceGenNiNode();
	~BSFaceGenNiNode();

	virtual NiObject *	GetAnimationData();
	virtual void		SetAnimationData(NiObject * obj);
	virtual float *		GetRotation(float * dst);
	virtual void		SetRotation(float * src);	// ticks bRotatedLastUpdate
	virtual bool		GetAnimationUpdate();
	virtual void		SetAnimationUpdate(bool arg);
	virtual bool		GetApplyRotationToParent();
	virtual void		SetApplyRotationToParent(bool arg);
	virtual bool		GetFixedNormals();
	virtual void		SetFixedNormals(bool arg);
	virtual void		Unk_31(void * arg);	// scans children, "could not find bone for the head node"

	// spAnimationData->Unk15(idx) returns emotion weighting (max 0x0C)
	// spAnimationData->Unk17(idx) returns movement weighting (max 0x10)
	// spAnimationData->Unk1A(idx) returns phoneme weighting (max 0x0F)

	NiObject	* spAnimationData;		// 0DC
	float		m_rotation[9];			// 0E0 - init'd to identity mtx
	UInt8		bForceBaseMorph;		// 104
	UInt8		bFixedNormals;			// 105
	UInt8		bAnimationUpdate;		// 106
	UInt8		bRotatedLastUpdate;		// 107
	UInt8		bApplyRotationToParent;	// 108
	UInt8		pad109[3];				// 109
	float		fLastTime;				// 10C - init'd to -1
	UInt8		bUsingLoResHead;		// 110
	UInt8		bIAmPlayerCharacter;	// 111
	UInt8		bIAmInDialouge;			// 112
	UInt8		pad113;					// 113
	Actor		* pActor;				// 114
};

// E4
class NiBillboardNode : public NiNode
{
public:
	NiBillboardNode();
	~NiBillboardNode();

	enum
	{
		kMode_AlwaysFaceCamera =	0,
		kMode_RotateAboutUp,
		kMode_RigidFaceCamera,
		kMode_AlwaysFaceCenter,
		kMode_RigidFaceCenter,
		kMode_BSRotateAboutUp,
		kMode_Mask =				7,

		kFlag_Unk3 =				1 << 3,
	};

	// update functions set kFlag_Unk3

	UInt16	flags;				// 0DC
	UInt8	pad0DE[2];			// 0DE
	float	m_lastUpdateTime;	// 0E0
};

// FC
class NiSwitchNode : public NiNode
{
public:
	NiSwitchNode();
	~NiSwitchNode();

	// only updates/displays/etc child with index m_iIndex
	// keeps track of the last time each child was updated to save work

	enum
	{
		kUpdateOnlyActive =	1 << 0,
	};

	UInt16				flags;			// 0DC
	UInt8				pad0DE[2];		// 0DE
	UInt32				m_iIndex;		// 0E0 - active child idx
	float				lastUpdateTime;	// 0E4
	UInt32				curUpdateIdx;	// 0E8
	NiTArray <UInt32>	childUpdateIdx;	// 0EC - last update idx for each child
};

// 104
class NiLODNode : public NiSwitchNode
{
public:
	NiLODNode();
	~NiLODNode();

	NiLODData	* lodData;	// 0FC
	UInt8		unk100;		// 100
	UInt8		pad101[3];	// 101
};

// NiBSLODNode - unref'd

// E0
class NiSortAdjustNode : public NiNode
{
public:
	NiSortAdjustNode();
	~NiSortAdjustNode();

	UInt32	unk0DC;	// 0DC
};

// FC
class NiBSPNode : public NiNode
{
public:
	NiBSPNode();
	~NiBSPNode();

	NiPlane	m_kModelPlane;	// 0DC
	NiPlane	m_kWorldPlane;	// 0EC
};

// 130
class ShadowSceneNode : public NiNode
{
public:
	ShadowSceneNode();
	~ShadowSceneNode();

	NiObject			* unk0DC;	// 0DC
	UInt16				unk0E0;		// 0E0
	UInt8				pad0E2[2];	// 0E2
	NiTPointerList <ShadowSceneLight *>	lights;		// 0E4
	NiTPointerList <ShadowSceneLight *>	lights2;	// 0F4
	UInt32				pad104;		// 104
	UInt32				unk108;		// 108
	UInt32				unk10C;		// 10C
	ShadowSceneLight	* unk110;	// 110
	ShadowSceneLight	* unk114;	// 114
	UInt32				unk118;		// 118
	UInt8				unk11C;		// 11C
	UInt8				pad11D[3];	// 11D
	NiObject			* unk120;	// 120
	UInt32				unk124;		// 124
	UInt32				unk128;		// 128
	UInt8				unk12C;		// 12C
	UInt8				pad12D[3];	// 12D
};

// 124
class NiCamera : public NiAVObject
{
public:
	NiCamera();
	~NiCamera();

	UInt32		unk0AC[(0xEC - 0xAC) >> 2];	// 0AC
	NiFrustum	m_kViewFrustum;				// 0EC
	float		m_fMinNearPlaneDist;		// 108
	float		m_fMaxFarNearRatio;			// 10C
	NiViewport	m_kPort;					// 110
	float		unk120;						// 120
};

// 150
class BSCubeMapCamera : public NiCamera
{
public:
	BSCubeMapCamera();
	~BSCubeMapCamera();

	// 1C
	class Str14C
	{
	public:
		Str14C();
		~Str14C();

		NiTPointerList <BSImageSpaceShader *>	shaders;	// 00
		NiObject	* unk010;	// 10
		NiObject	* unk014;	// 14
		UInt32		unk018;		// 18
	};

	UInt32		unk124;			// 124
	NiObject	* unk128[6];	// 128
	NiObject	* unk140;		// 140
	UInt32		pad144;			// 144
	NiObject	* unk148;		// 148
	Str14C		* unk14C;		// 14C
};

// 144
class NiScreenSpaceCamera : public NiCamera
{
public:
	NiScreenSpaceCamera();
	~NiScreenSpaceCamera();

	NiTArray <NiScreenPolygon *>	polygons;	// 124
	NiTArray <NiScreenTexture *>	textures;	// 134
};

// C0
class NiGeometry : public NiAVObject
{
public:
	NiGeometry();
	~NiGeometry();

	virtual void	Render(NiRenderer * arg);
	virtual void	Unk_22(NiRenderer * arg);
	virtual void	SetGeomData(NiObject * obj);
	virtual void	Unk_24();		// geomData->Unk_15()
	virtual void	Unk_25(NiRenderer * arg);

	NiPropertyState			* unk0AC;	// 0AC
	NiDynamicEffectState	* unk0B0;	// 0B0
	NiGeometryData			* geomData;	// 0B4
	NiObject				* skinData;	// 0B8
	NiObject				* shader;	// 0BC
};

// C0
class NiLines : public NiGeometry
{
public:
	NiLines();
	~NiLines();
};

// C0
class NiTriBasedGeom : public NiGeometry
{
public:
	NiTriBasedGeom();
	~NiTriBasedGeom();

	// use this API for SUPER MAX SPEED
	virtual void	GetTri(UInt32 idx, NiPoint3 ** a, NiPoint3 ** b, NiPoint3 ** c) = 0;
};

// C0
class NiTriShape : public NiTriBasedGeom
{
public:
	NiTriShape();
	~NiTriShape();
};

// D0
class BSScissorTriShape : public NiTriShape
{
public:
	BSScissorTriShape();
	~BSScissorTriShape();

	UInt32	unk0C0;	// 0C0
	UInt32	unk0C4;	// 0C4
	UInt32	unk0C8;	// 0C8
	UInt32	unk0CC;	// 0CC
};

// C0
class NiScreenElements : public NiTriShape
{
public:
	NiScreenElements();
	~NiScreenElements();
};

// C0
class NiScreenGeometry : public NiTriShape
{
public:
	NiScreenGeometry();
	~NiScreenGeometry();
};

// D4
class TallGrassTriShape : public NiTriShape
{
public:
	TallGrassTriShape();
	~TallGrassTriShape();

	UInt16		instanceCount;	// 0C0
	UInt8		pad0C2[2];		// 0C2
	NiSphere	pLocalBound;	// 0C4
};

// C0
class NiTriStrips : public NiTriBasedGeom
{
public:
	NiTriStrips();
	~NiTriStrips();
};

// D4
class TallGrassTriStrips : public NiTriStrips
{
public:
	TallGrassTriStrips();
	~TallGrassTriStrips();

	virtual void		SetLocalBound(float x, float y, float z, float radius);
	virtual void		SetInstanceCount(UInt16 count);
	virtual NiSphere *	GetLocalBound();

	UInt16		instanceCount;	// 0C0
	UInt8		pad0C2[2];		// 0C2
	NiSphere	pLocalBound;	// 0C4
};

// C0
class NiParticles : public NiGeometry
{
public:
	NiParticles();
	~NiParticles();
};

// F0
class NiParticleSystem : public NiParticles
{
public:
	NiParticleSystem();
	~NiParticleSystem();

	virtual void	Unk_26(float arg);
	virtual void	Update(float time);

	UInt8	inWorldSpace;		// 0C0
	UInt8	pad0C1[3];			// 0C1
	NiTPointerList <NiPSysModifier *>	modifiers;		// 0C4
	NiTPointerMap <NiPSysModifier *>	modifierMap;	// 0D4 - wrong, should be NiTStringPointerMap <NiPSysModifier *>
	UInt8	unk0E4;				// 0E4
	UInt8	pad0E5[3];			// 0E5
	float	systemUpdateTime;	// 0E8
	UInt8	unk0EC;				// 0EC
	UInt8	pad0ED[3];			// 0ED
};

// F8
class NiMeshParticleSystem : public NiParticleSystem
{
public:
	NiMeshParticleSystem();
	~NiMeshParticleSystem();

	float	transformUpdateTime;	// 0F0
	UInt8	unk0F4;					// 0F4
	UInt8	unk0F5[3];				// 0F5
};

// C8
class NiParticleMeshes : public NiParticles
{
public:
	NiParticleMeshes();
	~NiParticleMeshes();

	float	transformUpdateTime;	// 0C0
	UInt8	unk0C4;					// 0C4
	UInt32	unk0C5[3];				// 0C5
};

#pragma once

#define DECL_FLOAT_OP(op) \
	NiPoint3 operator op(const float n) const \
	{ \
		return NiPoint3(x op n, y op n, z op n); \
	} \
	NiPoint3 operator op##=(const float n) \
	{ \
		return *this = NiPoint3(x op n, y op n, z op n); \
	} \

#define DECL_VEC_OP(op) \
	NiPoint3 operator op(const NiPoint3 v) const \
	{ \
		return NiPoint3(x op v.x, y op v.y, z op v.z); \
	} \
	NiPoint3 operator op##=(const NiPoint3 v) \
	{ \
		return *this = NiPoint3(x op v.x, y op v.y, z op v.z); \
	}


// 8
struct NiRTTI {
	const char* name;
	NiRTTI* parent;
};
static_assert(sizeof(NiRTTI) == 0x008);

class NiPoint2
{
public:
	float x;
	float y;

	void Scale(float mult)
	{
		x *= mult;
		y *= mult;
	}
};

// C
class NiPoint3
{
public:
	Float32 x;
	Float32 y;
	Float32 z;

	void operator*(Float32 scale) {
		x *= scale;
		y *= scale;
		z *= scale;
	};

	void Init(NiPoint3* point)
	{
		x = point->x;
		y = point->y;
		z = point->z;
	};

	NiPoint3() : x(0.f), y(0.f), z(0.f)
	{
	};

	NiPoint3(const float x, const float y, const float z) : x(x), y(y), z(z)
	{
	};


	DECL_FLOAT_OP(*);
	DECL_FLOAT_OP(/ );

	DECL_VEC_OP(+);
	DECL_VEC_OP(-);
	DECL_VEC_OP(*);
	DECL_VEC_OP(/ );

	float length() const
	{
		return sqrtf(x * x + y * y + z * z);
	}

	float length_sqr() const
	{
		return x * x + y * y + z * z;
	}

	NiPoint3 normal() const
	{
		const auto len = length();
		return len == 0.F ? NiPoint3() : NiPoint3(x / len, y / len, z / len);
	}

	static float dot(const NiPoint3& v1, const NiPoint3& v2)
	{
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}

	static NiPoint3 cross(const NiPoint3& v1, const NiPoint3& v2)
	{
		return NiPoint3(
			v1.y * v2.z - v1.z * v2.y,
			v1.z * v2.x - v1.x * v2.z,
			v1.x * v2.y - v1.y * v2.x);
	}

	NiPoint3* operator+=(NiPoint3* toAdd)
	{
		this->x += toAdd->x;
		this->y += toAdd->y;
		this->z += toAdd->z;
		return this;
	}

	NiPoint3* operator-=(NiPoint3* point)
	{
		this->x -= point->x;
		this->y -= point->y;
		this->z -= point->z;
		return this;
	}

	float CalculateDistSquared(NiPoint3* to)
	{
		float deltaX = (x - to->x);
		float deltaY = (y - to->y);
		float deltaZ = (z - to->z);

		return deltaX * deltaX + deltaY * deltaY + deltaZ * deltaZ;
	}

	bool operator==(NiPoint3* compare)
	{
		return x == compare->x && y == compare->y && z == compare->z;
	}

	bool FltEquals(NiPoint3* compare)
	{
		if (abs(x - compare->x) > FLT_EPSILON) return false;
		if (abs(y - compare->y) > FLT_EPSILON) return false;
		return (abs(z - compare->z) <= FLT_EPSILON);
	}
};
static_assert(sizeof(NiPoint3) == 0x00C);

// 10 - always aligned?
class NiPoint4 {
public:
	Float32 x;
	Float32 y;
	Float32 z;
	Float32 w;
};
static_assert(sizeof(NiPoint4) == 0x010);

// 24
class NiMatrix33 {
public:
	union
	{
		Float32 dataAlt[9]{};
		Float32 data[3][3];
		struct
		{
			NiPoint3 x;
			NiPoint3 y;
			NiPoint3 z;
		};
	};
	NiMatrix33()
	= default;
};
static_assert(sizeof(NiMatrix33) == 0x024);

// 34
class NiTransform {
public:
	NiMatrix33	rot;		// 00
	NiPoint3	pos;		// 24
	float		scale;		// 30
};
static_assert(sizeof(NiTransform) == 0x034);

// 10
struct NiSphere
{
	float	x, y, z, radius;
};

// 1C
struct NiFrustum
{
	float	l;			// 00
	float	r;			// 04
	float	t;			// 08
	float	b;			// 0C
	float	n;			// 10
	float	f;			// 14
	UInt8	o;			// 18
	UInt8	pad19[3];	// 19
};

// 10
struct NiViewport
{
	float	l;
	float	r;
	float	t;
	float	b;
};

// C
struct NiColor
{
	float	r;
	float	g;
	float	b;
};

// 10
struct NiColorAlpha
{
	float	r;
	float	g;
	float	b;
	float	a;
};

// 10
struct NiPlane
{
	NiPoint3	nrm;
	float		offset;
};

// 10
// NiTArrays are slightly weird: they can be sparse
// this implies that they can only be used with types that can be NULL?
// not sure on the above, but some code only works if this is true
// this can obviously lead to fragmentation, but the accessors don't seem to care
// weird stuff
template <typename T_Data> struct NiTArray
{
	virtual void* Destroy(UInt32 doFree);

	T_Data*     data;			// 04
	UInt16		capacity;		// 08 - init'd to size of preallocation
	UInt16		firstFreeEntry;	// 0A - index of the first free entry in the block of free entries at the end of the array (or numObjs if full)
	UInt16		numObjs;		// 0C - init'd to 0
	UInt16		growSize;		// 0E - init'd to size of preallocation

	T_Data operator[](UInt32 idx)
	{
		if (idx < firstFreeEntry)
			return data[idx];
		return NULL;
	}

	T_Data Get(UInt32 idx) { return data[idx]; }

	UInt16 Length() { return firstFreeEntry; }
	void AddAtIndex(UInt32 index, T_Data* item);	// no bounds checking
	void SetCapacity(UInt16 newCapacity);	// grow and copy data if needed

	class Iterator
	{
		friend NiTArray;

		T_Data* pData;
		UInt32		count;

	public:
		explicit operator bool() const { return count != 0; }
		void operator++()
		{
			pData++;
			count--;
		}

		T_Data& operator*() const { return *pData; }
		T_Data& operator->() const { return *pData; }
		T_Data& Get() const { return *pData; }

		Iterator& operator=(const Iterator& rhs)
		{
			pData = rhs.pData;
			return *this;
		}
		bool operator!=(const Iterator& rhs) { return count > 0; }

		Iterator(NiTArray* source) : pData(source->data), count(source->firstFreeEntry) {}
		Iterator() : pData(nullptr), count(0) {}
	};

	Iterator begin() { return Iterator(this); }
	Iterator end() { return Iterator(); }
};

template <typename T> void NiTArray<T>::AddAtIndex(UInt32 index, T* item)
{
	ThisStdCall(0x00869640, this, index, item);
}

template <typename T> void NiTArray<T>::SetCapacity(UInt16 newCapacity)
{
	ThisStdCall(0x008696E0, this, newCapacity);
}

// 18
// an NiTArray that can go above 0xFFFF, probably with all the same weirdness
// this implies that they make fragmentable arrays with 0x10000 elements, wtf
template <typename T> class NiTLargeArray
{
public:
	NiTLargeArray();
	~NiTLargeArray();

	void	** _vtbl;		// 00
	T		* data;			// 04
	UInt32	capacity;		// 08 - init'd to size of preallocation
	UInt32	firstFreeEntry;	// 0C - index of the first free entry in the block of free entries at the end of the array (or numObjs if full)
	UInt32	numObjs;		// 10 - init'd to 0
	UInt32	growSize;		// 14 - init'd to size of preallocation

	T operator[](UInt32 idx) {
		if (idx < firstFreeEntry)
			return data[idx];
		return NULL;
	}

	T Get(UInt32 idx) { return (*this)[idx]; }

	UInt32 Length() { return firstFreeEntry; }
};

// 8
template <typename T> struct NiTSet
{
	T*		data;		// 00
	UInt16	capacity;	// 04
	UInt16	length;		// 06
};

// 10
template <typename T_Data> class NiTPointerMap
{
public:
	NiTPointerMap();
	virtual ~NiTPointerMap();

	struct Entry
	{
		Entry*	next;
		UInt32	key;
		T_Data*	data;
	};

	virtual void	Destroy(bool doFree);
	virtual UInt32	CalculateBucket(UInt32 key);
	virtual bool	CompareKey(UInt32 lhs, UInt32 rhs);
	virtual void	FillEntry(Entry* entry, UInt32 key, T_Data data);
	virtual void	FreeKey(Entry* entry);
	virtual Entry*	AllocNewEntry();
	virtual void	FreeEntry(Entry* entry);

	T_Data *		Lookup(UInt32 key);
	bool			Insert(Entry* nuEntry);

//	void**			_vtbl;			// 0
	UInt32			m_numBuckets;	// 4
	Entry**			m_buckets;		// 8
	UInt32			m_numItems;		// C

	// note: traverses in non-numerical order
	class Iterator
	{
		friend NiTPointerMap;

		NiTPointerMap* m_table;
		Entry* m_entry;
		Entry** m_bucket;
		
		void FindNonEmpty();

	public:

		Iterator() : m_table(nullptr), m_entry(nullptr), m_bucket(nullptr) {}
		Iterator(NiTPointerMap* table, Entry* entry = nullptr)
			: m_table(table), m_entry(entry), m_bucket(table->m_buckets) { FindNonEmpty(); }

		~Iterator() { }

		T_Data*		Get();
		UInt32		GetKey();
		bool		Next();
		bool		Done();

		//		T_Key Key() const { return m_entry->key; }

		explicit operator bool() const { return m_entry != nullptr; }
		void operator++()
		{
			m_entry = m_entry->next;
			if (!m_entry)
			{
				m_bucket++;
				FindNonEmpty();
			}
		}

		T_Data* operator->() const { return m_entry->data; }
		T_Data*& operator*() const { return m_entry->data; }
		Iterator& operator=(const Iterator& rhs)
		{
			m_entry = rhs.m_entry;
			return *this;
		}
		bool operator!=(const Iterator& rhs) { return m_entry != rhs.m_entry; }
	};

	Iterator begin() { return Iterator(this); }
	Iterator end() { return Iterator(); }

};

template <typename T_Data> T_Data* NiTPointerMap <T_Data>::Lookup(UInt32 key)
{
	for (Entry * traverse = m_buckets[key % m_numBuckets]; traverse; traverse = traverse->next)
		if (traverse->key == key)
			return traverse->data;
	return nullptr;
}

template <typename T_Data> bool NiTPointerMap<T_Data>::Insert(Entry* nuEntry)
{
	// game code does not appear to care about ordering of entries in buckets
	UInt32 bucket = nuEntry->key % m_numBuckets;
	Entry* prev = nullptr;
	for (Entry* cur = m_buckets[bucket]; cur; cur = cur->next) {
		if (cur->key == nuEntry->key) return false;
		if (!cur->next) {
			prev = cur;
			break;
		}
	}

	if (prev) prev->next = nuEntry;
	else m_buckets[bucket] = nuEntry;

	m_numBuckets++;
	return true;
}

template <typename T_Data> void NiTPointerMap<T_Data>::Iterator::FindNonEmpty()
{
	for (Entry** end = &m_table->m_buckets[m_table->m_numBuckets]; m_bucket != end; ++m_bucket)
		if ((m_entry = *m_bucket)) return;
}

template <typename T_Data> T_Data * NiTPointerMap <T_Data>::Iterator::Get()
{
	return m_entry ? m_entry->data : nullptr;
}

template <typename T_Data> UInt32 NiTPointerMap <T_Data>::Iterator::GetKey()
{
	return m_entry ? m_entry->key : 0;
}

template <typename T_Data> bool NiTPointerMap <T_Data>::Iterator::Next()
{
	if (m_entry) m_entry = m_entry->next;

	while (!m_entry && (m_bucket < (m_table->m_numBuckets - 1)))
	{
		++m_bucket;
		m_entry = m_table->m_buckets[m_bucket];
	}

	return m_entry != nullptr;
}

template <typename T_Data> bool NiTPointerMap <T_Data>::Iterator::Done()
{
	return m_entry == nullptr;
}

/*
template <typename T_Data> void NiTPointerMap <T_Data>::Iterator::FindValid()
{
	// validate bucket
	if(m_bucket >= m_table->m_numBuckets) return;

	// get bucket
	m_entry = m_table->m_buckets[m_bucket];

	// find non-empty bucket
	while(!m_entry && (m_bucket < (m_table->m_numBuckets - 1)))
	{
		m_bucket++;

		m_entry = m_table->m_buckets[m_bucket];
	}
}
*/

// 10
// todo: NiTPointerMap should derive from this
// cleaning that up now could cause problems, so it will wait
template <typename T_Key, typename T_Data> class NiTMapBase
{
public:
	NiTMapBase();
	~NiTMapBase();

	struct Entry
	{
		Entry*	next;	// 000
		T_Key	key;	// 004
		T_Data	data;	// 008
	};

	virtual NiTMapBase<T_Key, T_Data>*	Destructor(bool doFree);						// 000
	virtual UInt32						Hash(T_Key key);								// 001
	virtual void						Equal(T_Key key1, T_Key key2);					// 002
	virtual void						FillEntry(Entry entry, T_Key key, T_Data data);	// 003
	virtual	void						Unk_004(void * arg0);							// 004
	virtual	void						Unk_005();										// 005
	virtual	void						Unk_006();										// 006

	//void**	_vtbl;	// 0
	UInt32		numBuckets;	// 4
	Entry**		buckets;	// 8
	UInt32		numItems;	// C

	__forceinline bool LookUp(T_Key key, T_Data *dataOut)
	{
		return ThisCall<bool>(0x00853130, this, key, dataOut);
	}

	class Iterator
	{
		friend NiTPointerMap;

		NiTMapBase* m_table;
		Entry* m_entry;
		Entry** m_bucket;

		void FindNonEmpty();

	public:

		Iterator() : m_table(nullptr), m_entry(nullptr), m_bucket(nullptr) {}
		Iterator(NiTMapBase* table, Entry* entry = nullptr)
			: m_table(table), m_entry(entry), m_bucket(table->buckets) {
			FindNonEmpty();
		}

		~Iterator() { }

		T_Data* Get();
		UInt32		GetKey();
		bool		Next();
		bool		Done();

		//		T_Key Key() const { return m_entry->key; }

		explicit operator bool() const { return m_entry != nullptr; }
		void operator++()
		{
			m_entry = m_entry->next;
			if (!m_entry)
			{
				m_bucket++;
				FindNonEmpty();
			}
		}

		Entry* operator->() { return m_entry; }
		Entry*& operator*() { return m_entry; }
		Iterator& operator=(const Iterator& rhs)
		{
			m_entry = rhs.m_entry;
			return *this;
		}
		bool operator!=(const Iterator& rhs) { return m_entry != rhs.m_entry; }
	};

	Iterator begin() { return Iterator(this); }
	Iterator end() { return Iterator(); }
};

template <typename T_Key, typename T_Data>
void NiTMapBase<T_Key, T_Data>::Iterator::FindNonEmpty()
{
	for (Entry** end = &m_table->buckets[m_table->numBuckets]; m_bucket != end; ++m_bucket)
		if ((m_entry = *m_bucket)) return;
}

template <typename T_Key, typename T_Data> class NiTMap : public NiTMapBase<T_Key, T_Data>
{
public:
	NiTMap();
	~NiTMap();
};

// 14
template <typename T_Data> class NiTStringPointerMap : public NiTPointerMap <T_Data>
{
public:
	NiTStringPointerMap();
	~NiTStringPointerMap();

	UInt32	unk010;
};

// not sure how much of this is in NiTListBase and how much is in NiTPointerListBase
// 10
template <typename T> class NiTListBase
{
public:
	NiTListBase();
	~NiTListBase();

	struct Node
	{
		Node*	next;
		Node*	prev;
		T*		data;
	};

	virtual void	Destructor();
	virtual Node*	AllocateNode();
	virtual void	FreeNode(Node * node);

//	void**		_vtbl;		// 000
	Node*		first;		// 004
	Node*		last;		// 008
	UInt32		numItems;	// 00C


	class Iterator
	{
		Node* m_curr;

	public:
		Iterator	operator++()
		{
			m_curr = m_curr->next;
			return *this;
		}
		T* operator->() const { return m_curr->data; }
		T*& operator*() const { return m_curr->data; }
		Iterator& operator=(const Iterator& rhs)
		{
			m_curr = rhs.m_curr;
			return *this;
		}
		bool		operator!=(const Iterator& rhs) { return m_curr && m_curr->data; }

		Iterator() : m_curr(nullptr) {}
		Iterator(Node* node) : m_curr(node) {}
		Iterator(const T* _list) : m_curr(const_cast<Node*>(&_list->first)) {}
	};

	Iterator begin() const { return Iterator(this); }
	Iterator end() const { return Iterator(); }

	UInt32 count() const
	{
		if (!first->data) return 0;
		UInt32 count = 0;
		for (const auto iter : *this) count++;
		return count;
	}

	bool contains(T* item) const
	{
		for (const auto iter : *this) if (iter == item) return true;
		return false;
	}
};

// 10
template <typename T> class NiTPointerListBase : public NiTListBase <T>
{
public:
	NiTPointerListBase();
	~NiTPointerListBase();
};

// 10
template <typename T> class NiTPointerList : public NiTPointerListBase <T>
{
public:
	NiTPointerList();
	~NiTPointerList();
};

// 4
template <typename T> class NiPointer
{
public:
	NiPointer(T *init) : data(init)		{	}

	T*		data;

	const T&	operator *() const { return *data; }
	T&			operator *() { return *data; }

	operator const T*() const { return data; }
	operator T*() { return data; }
};

// 14
template <typename T> class BSTPersistentList
{
public:
	BSTPersistentList();
	~BSTPersistentList();

	virtual void	Destroy(bool destroy);

//	void	** _vtbl;	// 00
	UInt32	unk04;		// 04
	UInt32	unk08;		// 08
	UInt32	unk0C;		// 0C
	UInt32	unk10;		// 10
};

#pragma once

#define DIRECTINPUT_VERSION 0x0800
#define DIRECTSOUND_VERSION 0x0800
#include <dinput.h>
//#include <dsound.h>
#include <utilities.h>

// 1C00 (1.0) / 1C04 (1.1)
struct OSInputGlobals
{
	enum
	{
		kFlag_HasJoysticks		= 1 << 0,
		kFlag_HasMouse			= 1 << 1,
		kFlag_HasKeyboard		= 1 << 2,
		kFlag_BackgroundMouse	= 1 << 3,
	};


	enum ControlType
	{
		kControlType_Keyboard,
		kControlType_Mouse,
		kControlType_Joystick
	};


	enum KeyState
	{
		isHeld = 0x0,
		isPressed = 0x1,
		isDepressed = 0x2,
		isChanged = 0x3,
	};

	enum ControllerState
	{
		kControllerState_NotHeld = -1,
		kControllerState_IsHeld = 0,
		kControllerState_IsDepressed = 1,
		kControllerState_IsPressed = 2,
	};

	enum ControlCode
	{
		Forward = 0x0,
		Backward = 0x1,
		Left = 0x2,
		Right = 0x3,
		Attack = 0x4,
		Activate = 0x5,
		Aim = 0x6,
		ReadyItem = 0x7,
		Crouch = 0x8,
		Run = 0x9,
		AlwaysRun = 0xA,
		AutoMove = 0xB,
		Jump = 0xC,
		TogglePOV = 0xD,
		MenuMode = 0xE,
		Rest = 0xF,
		VATS_ = 0x10,
		Hotkey1 = 0x11,
		AmmoSwap = 0x12,
		Hotkey3 = 0x13,
		Hotkey4 = 0x14,
		Hotkey5 = 0x15,
		Hotkey6 = 0x16,
		Hotkey7 = 0x17,
		Hotkey8 = 0x18,
		QuickSave = 0x19,
		QuickLoad = 0x1A,
		Grab = 0x1B,
		Escape_ = 0x1C,
		Console = 0x1D,
		Screenshot = 0x1E,
		kControlCode_NONE = 255,
	};

	enum Scancodes
	{
		_Escape = 0x1,
		One = 0x2,
		Two = 0x3,
		Three = 0x4,
		Four = 0x5,
		Five = 0x6,
		Six = 0x7,
		Seven = 0x8,
		Eight = 0x9,
		Nine = 0xA,
		Zero = 0xB,
		Minus = 0xC,
		Equals = 0xD,
		Backspace = 0xE,
		Tab = 0xF,
		Q = 0x10,
		W = 0x11,
		E = 0x12,
		R = 0x13,
		T = 0x14,
		Y = 0x15,
		U = 0x16,
		I = 0x17,
		O = 0x18,
		P = 0x19,
		LeftBracket = 0x1A,
		RightBracket = 0x1B,
		Enter = 0x1C,
		LeftControl = 0x1D,
		A = 0x1E,
		S = 0x1F,
		D = 0x20,
		F = 0x21,
		G = 0x22,
		H = 0x23,
		J = 0x24,
		K = 0x25,
		L = 0x26,
		SemiColon = 0x27,
		Apostrophe = 0x28,
		Tilde = 0x29,
		LeftShift = 0x2A,
		BackSlash = 0x2B,
		Z = 0x2C,
		X = 0x2D,
		C = 0x2E,
		V = 0x2F,
		B = 0x30,
		N = 0x31,
		M = 0x32,
		Comma = 0x33,
		Period = 0x34,
		ForwardSlash = 0x35,
		RightShift = 0x36,
		NumStar = 0x37,
		LeftAlt = 0x38,
		SpaceBar = 0x39,
		CapsLock = 0x3A,
		F1 = 0x3B,
		F2 = 0x3C,
		F3 = 0x3D,
		F4 = 0x3E,
		F5 = 0x3F,
		F6 = 0x40,
		F7 = 0x41,
		F8 = 0x42,
		F9 = 0x43,
		F10 = 0x44,
		NumLock = 0x45,
		ScrollLock = 0x46,
		Num7 = 0x47,
		Num8 = 0x48,
		Num9 = 0x49,
		NumMinus = 0x4A,
		Num4 = 0x4B,
		Num5 = 0x4C,
		Num6 = 0x4D,
		NumPlus = 0x4E,
		Num1 = 0x4F,
		Num2 = 0x50,
		Num3 = 0x51,
		Num0 = 0x52,
		NumPeriod = 0x53,
		F11 = 0x57,
		F12 = 0x58,
		NumEnter = 0x9C,
		RightControl = 0x9D,
		NumSlash = 0xB5,
		PrintScrn = 0xB7,
		RightAlt = 0xB8,
		Home = 0xC7,
		UpArrow = 0xC8,
		PageUp = 0xC9,
		LeftArrow = 0xCB,
		RightArrow = 0xCD,
		End_ = 0xCF,
		DownArrow = 0xD0,
		PageDown = 0xD1,
		Delete_ = 0xD3,
		LeftMouse = 0x100,
		RightMouse = 0x101,
		MiddleMouse = 0x102,
		MouseButton3 = 0x103,
		MouseButton4 = 0x104,
		MouseButton5 = 0x105,
		MouseButton6 = 0x106,
		MouseButton7 = 0x107,
		MouseWheelUp = 0x108,
		MouseWheelDown = 0x109,
	};

	enum
	{
		kMaxControlBinds = 0x1C,
	};

	enum XboxControlCode
	{
		kXboxCtrl_DPAD_UP = 0x1,
		kXboxCtrl_DPAD_DOWN = 0x2,
		kXboxCtrl_DPAD_LEFT = 0x3,
		kXboxCtrl_DPAD_RIGHT = 0x4,
		kXboxCtrl_START = 0x5,
		kXboxCtrl_BACK = 0x6,
		kXboxCtrl_LS_BUTTON = 0x7,
		kXboxCtrl_RS_BUTTON = 0x8,
		kXboxCtrl_BUTTON_A = 0x9,
		kXboxCtrl_BUTTON_B = 0xA,
		kXboxCtrl_BUTTON_X = 0xB,
		kXboxCtrl_BUTTON_Y = 0xC,
		kXboxCtrl_BUTTON_LT = 0xD,
		kXboxCtrl_BUTTON_RT = 0xE,
		kXboxCtrl_LB = 0xF,
		kXboxCtrl_RB = 0x10,
		kXboxCtrl_L3 = 0x11,
		kXboxCtrl_R3 = 0x12,
	};

	enum XboxButtonMask
	{
		kXboxMask_DPAD_UP = 1,
		kXboxMask_DPAD_DOWN = 2,
		kXboxMask_DPAD_LEFT = 4,
		kXboxMask_DPAD_RIGHT = 8,
		kXboxMask_START = 0x10,
		kXboxMask_BACK = 0x20,
		kXboxMask_LS_BUTTON = 0x40,
		kXboxMask_RS_BUTTON = 0x80,
		kXboxMask_LB = 0x100,
		kXboxMask_RB = 0x200,
		kXboxMask_GUIDE = 0x400,
		kXboxMask_BUTTON_A = 0x1000,
		kXboxMask_BUTTON_B = 0x2000,
		kXboxMask_BUTTON_X = 0x4000,
		kXboxMask_BUTTON_Y = 0x8000,
	};

	enum InputGlobalsController
	{
		kThumbLX = 0x7,
		kThumbLY = 0x8,
		kThumbRX = 0x9,
		kThumbRY = 0xA,
	};

	enum MouseButtonNames
	{
		kLeftClick = 0,
		kRightClick
	};

	struct Bind
	{
		UInt8 controller;
		UInt8 mouse;
		UInt8 key;
		UInt8 pad03;
	};
	static_assert(sizeof(Bind) == 0x4);

	UInt8 isControllerDisabled;
	UInt8 byte0001;
	UInt8 byte0002;
	UInt8 byte0003;
	UInt32 flags;
	void* directInput;
	UInt32 unk000C;
	UInt32 unk0010;
	UInt32 unk0014;
	UInt32 unk0018;
	UInt32 unk001C;
	UInt32 unk0020;
	UInt32 unk0024;
	UInt32 unk0028;
	void* unk002C;
	void* unk0030;
	UInt32 unk0034[320];
	UInt32 unk534[1264];
	UInt32 unk18F4;
	UInt8 currKeyStates[256];
	UInt8 lastKeyStates[256];
	UInt32 unk1AF8;
	UInt32 unk1AFC;
	UInt32 unk1B00;
	UInt32 unk1B04;
	UInt32 numMouseButtons;
	UInt32 unk1B0C;
	UInt32 unk1B10;
	UInt32 unk1B14;
	UInt32 unk1B18;
	UInt32 unk1B1C;
	UInt32 unk1B20;
	int xDelta;
	int yDelta;
	int mouseWheelScroll;
	UInt8 currButtonStates[8];
	int lastxDelta;
	int lastyDelta;
	int lastMouseWheelScroll;
	UInt8 lastButtonStates[8];
	UInt32 swapLeftRightMouseButtons;
	UInt8 mouseSensitivity;
	UInt8 byte1B51;
	UInt8 byte1B52;
	UInt8 byte1B53;
	UInt32 doubleClickTime;
	UInt8 buttonStates1B58[8];
	UInt32 unk1B60[8];
	UInt32* controllerVibration;
	UInt32 unk1B84;
	UInt8 isControllerEnabled;
	UInt8 byte1B89;
	UInt8 byte1B8A;
	UInt8 byte1B8B;
	UInt32 unk1B8C;
	UInt8 byte1B90;
	UInt8 byte1B91;
	UInt16 overrideFlags;
	UInt8 keyBinds[28];
	UInt8 mouseBinds[28];
	UInt8 joystickBinds[28];
	UInt8 controllerBinds[28];

	static OSInputGlobals* GetSingleton() { return *reinterpret_cast<OSInputGlobals**>(0x011F35CC); }

	void ResetMouseButtons();
	void ResetPressedControls() { ThisCall(0xA253D0, this); };
	void ResetControlState(UInt8 code);

	bool GetControlState(ControlCode code, KeyState state) { return ThisCall<bool>(0xA24660, this, code, state); };
	void SetControlHeld(ControlCode code) { ThisCall(0xA24280, this, code); };
	bool GetMouseState(MouseButtonNames buttonID, KeyState state) { return ThisCall<bool>(0xA23A50, this, buttonID, state); };
	bool GetKeyState(int key, KeyState state) { return ThisCall<bool>(0xA24180, this, key, state); };
	signed int GetControllerValue(int a1, int key) { return ThisCall<signed int>(0xA23390, this, a1, key); };
	void SetDebounceMenuMode(bool isSet = true)
	{
		if (isSet)
		{
			overrideFlags |= 8;
		}
		else
		{
			overrideFlags &= ~8;
		}
	}
	bool IsDebounceMenuMode()
	{
		return overrideFlags & 8;
	}

	void SetBind(ControlCode code, Bind bind)
	{
		keyBinds[code] = bind.key;
		mouseBinds[code] = bind.mouse;
		controllerBinds[code] = bind.controller;
	}

	void Unbind(ControlCode code)
	{
		Bind unbound;
		unbound.key = 0xFF;
		unbound.mouse = 0xFF;
		unbound.controller = 0xFF;
		unbound.pad03 = 0xFF;
		SetBind(code, unbound);
	}

	enum ERumblePattern
	{
		eRumblePattern_Constant = 0x0,
		eRumblePattern_Square = 0x1,
		eRumblePattern_Triangle = 0x2,
		eRumblePattern_Sawtooth = 0x3,
	};

	static ControllerState GetControllerState(XboxControlCode button, bool includeThumbsticks = 1);
	void ResetRumble();
	void Rumble(float left, float right, int durationMS, int pulseDuration, ERumblePattern pattern, bool a7, bool isForce);

};
static_assert(sizeof(OSInputGlobals) == 0x1C04);
static_assert(offsetof(OSInputGlobals, mouseBinds) == 0x1BB0);

#if 0
#include "Types.h"

class TESGameSound;
class NiAVObject;

// 58
class TESGameSound
{
public:
	TESGameSound();
	~TESGameSound();

	UInt32			unk00[3];	// 00
	UInt32			hashKey;	// 0C
	UInt32			unk10[4];	// 10
	float			x;			// 20
	float			y;			// 24
	float			z;			// 28
	UInt32			unk2C[4];	// 2C
	float			unk3C;		// 3C
	UInt32			unk40[3];	// 40
	const char *	name;		// 4C
	UInt32			unk50;		// 50
	UInt32			unk54;		// 54
};

// 328
class OSSoundGlobals
{
public:
	OSSoundGlobals();
	~OSSoundGlobals();

	enum
	{
		kFlags_HasDSound =		1 << 0,
		kFlags_HasHardware3D =	1 << 2,
	};
	
	typedef NiTPointerMap <TESGameSound>	TESGameSoundMap;
	typedef NiTPointerMap <NiAVObject>		NiAVObjectMap;

	UInt32					unk000;						// 000
	UInt32					unk004;						// 004
	IDirectSound8			* dsoundInterface;			// 008
	IDirectSoundBuffer8		* primaryBufferInterface;	// 00C
	DSCAPS					soundCaps;					// 010
	UInt32					unk070;						// 070
	UInt32					unk074;						// 074
	IDirectSound3DListener	* listenerInterface;		// 078
	UInt32					unk07C[(0x0A4-0x07C) >> 2];	// 07C
	UInt8					unk0A4;						// 0A4
	UInt8					unk0A5;						// 0A5
	UInt8					unk0A6;						// 0A6
	UInt8					pad0A7;						// 0A7
	UInt32					unk0A8;						// 0A8
	UInt32					flags;						// 0AC - flags?
	UInt32					unk0B0;						// 0B0
	float					unk0B4;						// 0B4
	float					masterVolume;				// 0B8
	float					footVolume;					// 0BC
	float					voiceVolume;				// 0C0
	float					effectsVolume;				// 0C4
	UInt32					unk0C8;						// 0C8 - time
	UInt32					unk0CC;						// 0CC - time
	UInt32					unk0D0;						// 0D0 - time
	UInt32					unk0D4[(0x0DC-0x0D4) >> 2];	// 0D4
	UInt32					unk0DC;						// 0DC
	UInt32					unk0E0[(0x2F0-0x0E0) >> 2];	// 0E0
	float					musicVolume;				// 2F0
	UInt32					unk2F4;						// 2F4
	float					musicVolume2;				// 2F8
	UInt32					unk2FC;						// 2FC
	TESGameSoundMap			* gameSoundMap;				// 300
	NiAVObjectMap			* niObjectMap;				// 304
	NiTPointerList <void>	* soundMessageMap;			// 308 - AudioManager::SoundMessage *
	UInt32					unk30C[(0x320-0x30C) >> 2];	// 30C
	void					* soundMessageList;			// 320
	UInt32					unk324;						// 324
};

static_assert(sizeof(OSSoundGlobals) == 0x328);
#endif

class OSSoundGlobals {
};

// A4
class OSGlobals
{
public:
	OSGlobals();
	~OSGlobals();

	UInt8			oneMore;			// 00
	UInt8			quitGame;			// 01	// The seven are initialized to 0, this one is set by QQQ
	UInt8			exitToMainMenu;		// 02
	UInt8			unk03;				// 03
	UInt8			unk04;				// 04
	UInt8			unk05;				// 05
	UInt8			unk06;				// 06	// This looks promising as TFC bool byte
	UInt8			unk07;				// 07
	HWND			window;				// 08
	HINSTANCE		procInstance;		// 0C
	UInt32			mainThreadID;		// 10
	HANDLE			mainThreadHandle;	// 14
	UInt32*			unk18;				// 18 ScrapHeapManager::Buffer*
	UInt32			unk1C;				// 1C
	OSInputGlobals	* input;			// 20
	OSSoundGlobals	* sound;			// 24
	UInt32			unk28;				// 28 relates to unk18
	//...
	UInt32*			unk50;				// 50, same object as unk18
	//..
	UInt32			unk60;				// 60 relates to unk50

	OSGlobals* GetSingleton() { return *reinterpret_cast<OSGlobals**>(0x011DEA0C); }
};

//static_assert(sizeof(OSGlobals) == 0x0A4);	// found in oldWinMain 0x0086AF4B

extern OSGlobals ** g_osGlobals;

// credits to Luthien and Stooie
struct XINPUT_GAMEPAD_EX
{
	UInt32		eventCount;		// 00
	UInt16		wButtons;		// 04
	UInt8		bLeftTrigger;	// 06
	UInt8		bRightTrigger;	// 07
	SInt16		sThumbLX;		// 08
	SInt16		sThumbLY;		// 0A
	SInt16		sThumbRX;		// 0C
	SInt16		sThumbRY;		// 0E

	static XINPUT_GAMEPAD_EX* GetCurrent() { return (XINPUT_GAMEPAD_EX*)0x11F35A8; };
	static XINPUT_GAMEPAD_EX* GetPrevious() { return (XINPUT_GAMEPAD_EX*)0x11F35B8; };

};


#include "Containers.h"
#include "NiTypes.h"
#include "Utilities.h"

// Form type class: use to preload some information for created objects (?) refr and Cells
struct formTypeClassData
{
	typedef UInt8 EncodedID[3];	// Codes the refID on 3 bytes, as used in changed forms and save refID mapping

	struct Data01 // Applies to CELL where changeFlags bit30 (Detached CELL) and bit29 (CHANGE_CELL_EXTERIOR_CHAR) are set
	{
		UInt16	worldspaceIndex;	// 00 Index into visitedWorldspaces		goes into unk000
		UInt8	coordX;				// 02	goes into unk004
		UInt8	coordY;				// 03	goes into unk008, paired with 002
		UInt8	detachTime;			// 04	goes into unk00C
	};

	struct Data02 // Applies to CELL where changeFlags bit30 (Detached CELL) and bit 28 (CHANGE_CELL_EXTERIOR_SHORT) are set and changeFlags bit29 is clear
	{
		UInt16	worldspaceIndex;	// 00 Index into visitedWorldspaces		goes into unk000
		UInt16	coordX;				// 02	goes into unk004
		UInt16	coordY;				// 03	goes into unk008, paired with 002
		UInt32	detachTime;			// 04	goes into unk00C
	};

	// The difference between the two preceding case seems to be how big the data (coordinates?) are

	struct Data03 // Applies to CELL where changeFlags bit30 (Detached CELL) is set and changeFlags bit28 and bit29 are clear
	{
		UInt32	detachTime;	// 00	goes into unk00C. Null goes into unk000, 004 and 008
	};

	struct Data04 // Applies to references where changeFlags bit3 (CHANGE_REFR_CELL_CHANGED) is clear and
					// either bit1 (CHANGE_REFR_MOVE) or bit2 (CHANGE_REFR_HAVOK_MOVE) is set
	{
		EncodedID	cellOrWorldspaceID;	// 000	goes into unk000, Null goes into unk004, 008, 00C, 010 and byt02C
		float		posX;	// 003	goes into unk014
		float		posY;	// 007	goes into unk018, associated with unk003
		float		posZ;	// 00B	goes into unk01C, associated with unk003	(pos?)
		float		rotX;	// 00F	goes into unk020
		float		rotY;	// 013	goes into unk024, associated with unk00F
		float		rotZ;	// 017	goes into unk028, associated with unk00F	(rot?)
	};

	struct Data05 // Applies to created objects (ie 0xFFnnnnnn)
	{
		EncodedID	cellOrWorldspaceID;	// 000	goes into unk000
		float		posX;	// 003	goes into unk014
		float		posY;	// 007	goes into unk018, associated with unk003
		float		posZ;	// 00B	goes into unk01C, associated with unk003	(pos?)
		float		rotX;	// 00F	goes into unk020
		float		rotY;	// 013	goes into unk024, associated with unk024
		float		rotZ;	// 017	goes into unk028, associated with unk028	(rot?)
		UInt8		flags;	// 01B	goes into unk02C	bit0 always set, bit1 = ESP or persistent, bit2 = Byt081 true
		EncodedID	baseFormID;	// 01C	goes into unk004, Null goes into unk008, 00C and 010
	};

	struct Data06 // Applies to references whose changeFlags bit3 (CHANGE_REFR_CELL_CHANGED) is set
	{
		EncodedID	cellOrWorldspace;		// 000	goes into unk000
		float		posX;					// 003	goes into unk014
		float		posY;					// 007	goes into unk018, associated with unk003
		float		posZ;					// 00B	goes into unk01C, associated with unk003	(pos?)
		float		rotX;					// 00F	goes into unk020
		float		rotY;					// 013	goes into unk024, associated with unk00F
		float		rotZ;					// 017	goes into unk028, associated with unk00F	(rot?)
		EncodedID	newCellOrWorldspaceID;	// 01C	goes into unk008
		SInt16		coordX;					// 01E	goes into unk00C
		SInt16		coordY;					// 020	goes into unk010, Null goes into unk004 and byt02C
	};

	struct Data00  // Every other cases (no data)
	{
	};

	union Data
	{
		Data00	data00;
		Data01	data01;
		Data02	data02;
		Data03	data03;
		Data04	data04;
		Data05	data05;
		Data06	data06;
	};

	Data data;	// 00
};

struct PreloadCELLdata	// Unpacked and decoded version of Data01, 02 end 03
{
	UInt32	worldspaceID;	// 000
	SInt32	coordX;			// 004
	SInt32	coordY;			// 008
	UInt32	detachTime;		// 00C
};

struct PreloadREFRdata	// Unpacked and decoded version of Data04, 05 and 06
{
	UInt32	cellOrWorldspaceID;		// 000
	UInt32	baseFormID;				// 004
	UInt32	newCellOrWorldspaceID;	// 008
	SInt32	coordX;					// 00C
	SInt32	coordY;					// 010
	float	posXcoordX;				// 014
	float	posYcoordY;				// 018
	float	posZ;					// 01C
	float	rotX;					// 020
	float	rotY;					// 024
	float	rotZ;					// 028
	UInt8	flg02C;					// 02C
};

union preloadData
{
	PreloadCELLdata	cell;
	PreloadREFRdata	refr;
};

class BGSLoadGameBuffer
{
	BGSLoadGameBuffer();
	~BGSLoadGameBuffer();

	virtual UInt8			GetSaveFormVersion();	// replaced in descendant 
	virtual TESForm* getForm();				// only implemented in descendants
	virtual TESObjectREFR* getREFR();				// only implemented in descendants
	virtual Actor* getActor();				// only implemented in descendants

	char* chunk;			// 004
	UInt32	chunkSize;		// 008
	UInt32	chunkConsumed;	// 00C
};

struct BGSFormChange
{
	UInt32	changeFlags;
	UInt32	unk004;			// Pointer to the changed record or the save record ?
};

struct	BGSSaveLoadChangesMap
{
	NiTPointerMap<BGSFormChange> BGSFormChangeMap;
	// most likely more
};

// 030
class BGSLoadFormBuffer : public BGSLoadGameBuffer
{
	BGSLoadFormBuffer();
	~BGSLoadFormBuffer();

	typedef UInt8 EncodedID[3];
	struct Header	// 00C
	{
		EncodedID	encodeID;			// 00
		UInt32		changeFlags;		// 03
		UInt8		codedTypeAndLength;	// 07
		UInt8		formVersion;		// 08
		UInt8		pad009[3];			// 09
	};

	UInt32			refID;				// 010
	Header			header;				// 014
	UInt32			bufferSize;			// 020
	TESForm* form;				// 024
	UInt32			flg028;				// 028	bit1 form invalid
	BGSFormChange* currentFormChange;	// 02C
};

class BGSSaveFormBuffer : public BGSLoadGameBuffer
{
	BGSSaveFormBuffer();
	~BGSSaveFormBuffer();

};	// in BGSSaveGameBuffer there is a 010, which look like a counter (ChunkCount ?), then the Header


class SaveGameManager
{
public:
	SaveGameManager();
	~SaveGameManager();

	struct SaveGameData
	{
		const char* name;		// 00
		UInt32		unk04;		// 04
		UInt32		saveNumber;	// 08 index?
		const char* pcName;	// 0C
		const char* pcTitle;	// 10
		const char* location;	// 14
		const char* time;		// 18
	};

	TList<SaveGameData>*	saveList;		// 00
	UInt32					numSaves;		// 04
	UInt32					unk08;			// 08
	UInt8					unk0C;			// 0C	flag for either opened or writable or useSeparator (|)
	UInt8					unk0D;
	UInt8					unk0E;
	UInt8					unk0F;
/*
	const char				* unk10;		// 10 name of most recently loaded/saved game?
	UInt32					unk14;			// 14 init to -1
	UInt8					unk18;			// 18
	UInt8					pad19[3];
	UInt8					unk20;			// 20 init to 1
	UInt8					unk21;
	UInt8					pad22[2];
	UInt32					unk24;			// 24
	UInt32					unk28;			// 28
*/
	static SaveGameManager*		GetSingleton() { return *reinterpret_cast<SaveGameManager**>(0x011DE134); }
	__forceinline UInt32		ConstructSavegameFilename(const char* filename, char* outputBuf, bool bTempFile) { return StdCall<UInt32>(0x0084FF90, filename, outputBuf, bTempFile); }
	__forceinline bool			ConstructSavegamePath(char* outputBuf) { return StdCall<bool>(0x0084FF30, outputBuf); }
};

std::string GetSavegamePath();

#pragma once
#include "Utilities.h"
#include "TESForm.h"

struct ScriptEventList;
struct ScriptBuffer;

extern CRITICAL_SECTION	csGameScript;				// trying to avoid what looks like concurrency issues

// 54 / 48


struct ConditionEntry
{
	struct Data
	{
		union Param
		{
			float	number;
			TESForm	* form;
		};

		// ### TODO: this
		UInt32		operatorAndFlags;	// 00
		float		comparisonValue;	// 04
		UInt16		functionIndex;		// 08 is opcode & 0x0FFF
		UInt16		unk0A;
		Param		param1;				// 0C
		Param		param2;				// 10
		UInt32		unk14;
	};

	Data			* data;
	ConditionEntry	* next;
};

// 6C
struct QuestStageItem
{
	UInt32			unk00;			// 00
	ConditionEntry	conditionList;	// 04
	Script			resultScript;	// 0C
	UInt32			unk5C;			// 5C disk offset to log text records? consistent within a single quest
	UInt8			index;			// 60 sequential
	bool			hasLogText;		// 61
	UInt8			unk62[2];		// 62 pad?
	UInt32			logDate;		// 64
	TESQuest		* owningQuest;	// 68;
};

static_assert(sizeof(QuestStageItem) == (0x54 + 0x1C));

// 41C
struct ScriptLineBuffer
{
	static const UInt32	kBufferSize = 0x200;

	UInt32				lineNumber;			// 000 counts blank lines too
	char				paramText[0x200];	// 004 portion of line text following command
	UInt32				paramTextLen;		// 204
	UInt32				lineOffset;			// 208
	UInt8				dataBuf[0x200];		// 20C
	UInt32				dataOffset;			// 40C
	UInt32				cmdOpcode;			// 410 not initialized. Opcode of command being parsed
	UInt32				callingRefIndex;	// 414 not initialized. Zero if cmd not invoked with dot syntax
	UInt32				errorCode;			// 418

	// these write data and update dataOffset
	bool Write(const void* buf, UInt32 bufsize);
	bool WriteFloat(double buf);
	bool WriteString(const char* buf);
	bool Write32(UInt32 buf);
	bool Write16(UInt16 buf);
	bool WriteByte(UInt8 buf);
};

// size 0x58? Nothing initialized beyond 0x50.
struct ScriptBuffer
{	
	template <typename tData> struct Node
	{
		tData		* data;
		Node<tData>	* next;
	};

	enum RuntimeMode
	{
		kEditor = 0,
		kGameConsole = 1,
	};

	ScriptBuffer();
	~ScriptBuffer();

	const char* scriptText;		// 000
	UInt32			textOffset;			// 004 
	RuntimeMode		runtimeMode;		// 008
	String			scriptName;			// 00C
	UInt32			errorCode;			// 014
	bool			partialScript;		// 018
	UInt8			pad019[3];			// 019
	UInt32			curLineNumber;		// 01C
	UInt8			* scriptData;		// 020 pointer to 0x4000-byte array
	UInt32			dataOffset;			// 024
	UInt32			unk028;				// 028
	UInt32			numRefs;			// 02C
	UInt32			unk030;				// 030
	UInt32			varCount;			// 034 script->varCount
	UInt8			scriptType;			// 038 script->type
	UInt8			unk039;				// 039 script->unk35
	UInt8			unk03A[2];
	Script::VarInfoEntry	vars;		// 03C
	Script::RefListEntry	refVars;	// 044 probably ref vars
	Script*			currentScript;				// 04C num lines?
	Node<ScriptLineBuffer>	lines;		// 050
	// nothing else initialized

	// convert a variable or form to a RefVar, add to refList if necessary
	Script::RefVariable* ResolveRef(const char* refName);
	UInt32	GetRefIdx(Script::RefVariable* ref);
	UInt32	GetVariableType(VariableInfo* varInfo, Script::RefVariable* refVar);
};


// represents the currently executing script context
class ScriptRunner
{
public:
	static const UInt32	kStackDepth = 10;

	enum
	{
		kStackFlags_IF = 1 << 0,
		kStackFlags_ELSEIF = 1 << 1,
		/* ELSE and ENDIF modify the above flags*/
	};

	TESObjectREFR*		containingObj;		/*00*/  // set when executing scripts on inventory objects
	TESForm*			callingRefBaseForm;	/*04*/ 
	ScriptEventList*	eventList;			/*08*/ 
	UInt32				unk0C;				/*0C*/ 
	UInt32				unk10;				/*10*/  // pointer? set to NULL before executing an instruction
	Script*				script;				/*14*/ 
	UInt32				unk18;				/*18*/ // set to 6 after a failed expression evaluation
	UInt32				unk1C;				/*1C*/ // set to Expression::errorCode
	UInt32				ifStackDepth;		/*20*/ 
	UInt32				ifStack[kStackDepth];		/*24*/ // stores flags
	UInt32				unk4C[(0xA0 - 0x4C) >> 2];	/*4C*/ 
	UInt8				invalidReferences;	/*A0*/ // set when the dot operator fails to resolve a reference (inside the error message handler)
	UInt8				unkA1;				/*A1*/// set when the executing CommandInfo's 2nd flag bit (+0x25) is set
	UInt16				padA2;				/*A2*/ 
};
static_assert(sizeof(ScriptRunner) == 0xA4);

// unk1 = 0
// unk2 = 0
// callback = may be NULL apparently
// unk4 = 0
// unk5 = 0x17 (why?)
// unk6 = 0
// unk7 = 0
// then buttons
// then NULL

void ShowCompilerError(ScriptLineBuffer* lineBuf, const char* fmt, ...);

// only records individual objects if there's a block that matches it
// ### how can it tell?
struct ScriptEventList
{
	enum
	{
		kEvent_OnAdd					= 1 << 0,
		kEvent_OnEquip					= 1 << 1,		// Called on Item and on Refr
		kEvent_OnActorEquip				= kEvent_OnEquip,	// presumably the game checks the type of the object
		kEvent_OnDrop					= 1 << 2,
		kEvent_OnUnequip				= 1 << 3,
		kEvent_OnActorUnequip			= kEvent_OnUnequip,
		kEvent_OnDeath					= 1 << 4,
		kEvent_OnMurder					= 1 << 5,
		kEvent_OnCombatEnd				= 1 << 6,		// See 0x008A083C
		kEvent_OnHit					= 1 << 7,		// See 0x0089AB12
		kEvent_OnHitWith				= 1 << 8,		// TESObjectWEAP*	0x0089AB2F
		kEvent_OnPackageStart			= 1 << 9,
		kEvent_OnPackageDone			= 1 << 10,
		kEvent_OnPackageChange			= 1 << 11,
		kEvent_OnLoad					= 1 << 12,
		kEvent_OnMagicEffectHit			= 1 << 13,		// EffectSetting* 0x0082326F
		kEvent_OnSell					= 1 << 14,		// 0x0072FE29 and 0x0072FF05, linked to 'Barter Amount Traded' Misc Stat
		kEvent_OnStartCombat			= 1 << 15,

		kEvent_OnOpen					= 1 << 16,		// while opening some container, not all
		kEvent_OnClose					= 1 << 17,		// idem
		kEvent_SayToDone				= 1 << 18,		// in Func0050 0x005791C1 in relation to SayToTopicInfo (OnSayToDone? or OnSayStart/OnSayEnd?)
		kEvent_OnGrab					= 1 << 19,		// 0x0095FACD and 0x009604B0 (same func which is called from PlayerCharacter_func001B and 0021)
		kEvent_OnRelease				= 1 << 20,		// 0x0047ACCA in relation to container
		kEvent_OnDestructionStageChange	= 1 << 21,		// 0x004763E7/0x0047ADEE
		kEvent_OnFire					= 1 << 22,		// 0x008BAFB9 (references to package use item and use weapon are close)

		kEvent_OnTrigger				= 1 << 28,		// 0x005D8D6A	Cmd_EnterTrigger_Execute
		kEvent_OnTriggerEnter			= 1 << 29,		// 0x005D8D50	Cmd_EnterTrigger_Execute
		kEvent_OnTriggerLeave			= 1 << 30,		// 0x0062C946	OnTriggerLeave ?
		kEvent_OnReset					= 1 << 31		// 0x0054E5FB
	};

	struct Event
	{
		TESForm	* object;
		UInt32	eventMask;
	};

	struct VarEntry;

	struct Var
	{
		UInt32		id;
		VarEntry	* nextEntry;
		double		data;

		UInt32 GetFormId();
	};

	struct VarEntry
	{
		Var			* var;
		VarEntry	* next;
	};

	struct Struct010
	{
		UInt8 unk00[8];
	};

	typedef TList<Event> EventList;

	Script			* m_script;		// 00
	UInt32			  m_unk1;			// 04
	EventList		* m_eventList;	// 08
	VarEntry		* m_vars;		// 0C
	Struct010		* unk010;		// 10

	Var *	GetVariable(UInt32 id);
	UInt32	ResetAllVariables();

	void	Destructor();
	TList<Var>* GetVars() const;
	void					EventCreate(UInt32 eventCode, TESObjectREFR* container);

};

ScriptEventList* EventListFromForm(TESForm* form);

typedef bool (* _MarkBaseExtraListScriptEvent)(TESForm* target, BaseExtraList* extraList, UInt32 eventMask);
extern const _MarkBaseExtraListScriptEvent MarkBaseExtraListScriptEvent;

typedef void (_cdecl * _DoCheckScriptRunnerAndRun)(TESObjectREFR* refr, BaseExtraList* extraList);
extern const _DoCheckScriptRunnerAndRun DoCheckScriptRunnerAndRun;

struct ExtractedParam
{
	// float/double types are kept as pointers
	// this avoids problems with storing invalid floats/doubles in to the fp registers which has a side effect
	// of corrupting data

	enum
	{
		kType_Unknown = 0,
		kType_String,		// str
		kType_Imm32,		// imm
		kType_Imm16,		// imm
		kType_Imm8,			// imm
		kType_ImmDouble,	// immDouble
		kType_Form,			// form
	};

	UInt8	type;
	bool	isVar;	// if true, data is stored in var, otherwise it's immediate

	union
	{
		// immediate
		UInt32			imm;
		const double	* immDouble;
		TESForm			* form;
		struct
		{
			const char	* buf;
			UInt32		len;
		} str;

		// variable
		struct 
		{
			ScriptEventList::Var	* var;
			ScriptEventList			* parent;
		} var;
	} data;
};


UInt32 GetDeclaredVariableType(const char* varName, const char* scriptText);	// parses scriptText to determine var type
Script* GetScriptFromForm(TESForm* form);
CommandInfo* GetEventCommandInfo(UInt16 opcode);

// Gets the real script data ptr, as it can be a pointer to a buffer on the stack in case of vanilla expressions in set and if statements
UInt8* GetScriptDataPosition(Script* script, void* scriptDataIn, const UInt32* opcodeOffsetPtrIn);

#pragma once
#include "NiTypes.h"
#include "Containers.h"

// 0014
template<class M, class T> class NiTStringTemplateMap : public M
{
public:
	UInt8	byt0010;	// 0010
	UInt8	fil0011[3];	// 0011
};

template<class T> class NiTStringMap : public NiTStringTemplateMap<NiTMap<char const*, T>, T>
{
};

template<class T> class BSTCaseInsensitiveStringMap : public NiTStringMap<T>
{
};

template<class T> class SettingCollectionMap : public SettingCollection<T>
{
public:
	SettingCollectionMap();
	virtual ~SettingCollectionMap();

	BSTCaseInsensitiveStringMap<T*>	settingMap;
};
static_assert(sizeof(SettingCollectionList<void>) == 0x114);

class GameSettingCollection : public SettingCollectionMap<Setting>
{
public:
	GameSettingCollection();
	virtual ~GameSettingCollection();

	static GameSettingCollection * GetSingleton();
};
static_assert(sizeof(GameSettingCollection) == 0x120);

Setting* GetINISetting(const std::string& settingName);
Setting* GetGameSetting(const std::string& settingName);

#pragma once
#include <Containers.h>
#include <NiTypes.h>
#include <Utilities.h>

// 254
class BSSoundInfo
{
public:
	BSSoundInfo();
	~BSSoundInfo();

	UInt32			unk000[72];		// 000
	const char*		filePath;		// 120
	UInt32			unk124[76];		// 124
};

enum AudioRequestTypes
{
	kRequestType_Stop = 3,
	kRequestType_Stop2 = 4,
	kRequestType_Delay = 5,
	kRequestType_StopSoundFadeOutTime = 9,
	kRequestType_DialogueFadeInOrOut = 0xD,
	kRequestType_RecalculateVolumesForChangesToMasterVolume = 0xE,
	kRequestType_Volume = 0x10,
	kRequestType_FrequencyAdjustment = 0x14,
	kRequestType_FadeAllSFX = 0x18,
	kRequestType_SetState400ForSomeSounds = 0x1A,
	kRequestType_ClearState400ForSomeSounds = 0x1B,
	kRequestType_SetState400ForSomeSounds2 = 0x1C,
	kRequestType_ClearState400ForSomeSounds2 = 0x1D,
	kRequestType_SoundAtPos = 0x1E,
	kRequestType_Attenuation = 0x21,
	kRequestType_ReverbAttenuation = 0x22,
	kRequestType_PlayWithMinMaxDistance = 0x23,
	kRequestType_SetsPlayingSoundClearStateBit200 = 0x26,
	kRequestType_PlayAtNode = 0x27,
	kRequestType_NiNodeSound = 0x29,
	kRequestType_StopAllSoundsWithFlags = 0x2A,
	kRequestType_SetAudioListenerPosition = 0x38,
	kRequestType_HasCompletionCallback = 0x3A,
	kRequestType_HasSomeCallback = 0x3B,
	kRequestType_StartsAtEndsAt = 0x3E,
	kRequestType_MultiThreaded = 0x35,
	kRequestType_ToggleFirstPersonForPlayingSound = 0x40,
	kRequestType_Priority = 0x41,
	kRequestType_Speed = 0x42
};

// 20
struct AudioRequestData
{
	UInt32				type;		// 00
	UInt32				soundKey;	// 04
	FunctionArg			value1;		// 08
	FunctionArg			value2;		// 0C
	NiNode*				niNode;		// 10
	NiPoint3			pos;		// 14
};

// 188
class BSAudioManager
{
public:
	virtual void				Destroy(bool doFree);

	enum AudioFlags
	{
		kAudioFlags_2D = 0x1,
		kAudioFlags_3D = 0x2,
		kAudioFlags_UseMissingVoiceAssetIfMissing = 0x4,
		kAudioFlags8 = 0x8,
		kAudioFlags_Loop = 0x10,
		kAudioFlags20 = 0x20,
		kAudioFlags_RandomFrequencyShift = 0x40,
		kAudioFlags80 = 0x80,
		kAudioFlags100 = 0x100,
		kAudioFlags800 = 0x800,
		kAudioFlagsMaybeUnderwater = 0x2000,
		kAudioFlags4000 = 0x4000,
		kAudioFlags10000 = 0x10000,
		kAudioFlags20000 = 0x20000,
		kAudioFlags40000 = 0x40000,
		kAudioFlags_Radio100000 = 0x100000,
		kAudioFlags200000 = 0x200000,
		kAudioFlags_Radio400000 = 0x400000,
		kAudioFlags_Modulated = 0x80000,
		kAudioFlags1000000 = 0x1000000,
		kAudioFlags_EnvelopeFast = 0x2000000,
		kAudioFlags_EnvelopeSlow = 0x4000000,
		kAudioFlags_2DRadius = 0x8000000,
		kAudioFlags20000000 = 0x20000000,
		kAudioFlags40000000 = 0x40000000,
	};

	enum Volumes
	{
		kMaster = 0,
		kFoot,
		kVoice,
		kEffects,
		kMusic,
		kRadio,
		kVATSCamera,
	};

	// 10
	struct AudioRequest
	{
		UInt32				count;			// 00
		UInt8				byte04;			// 04
		UInt8				pad05[3];		// 05
		AudioRequestData*	requestData;	// 08
		UInt32				tickCount;		// 0C
	};

	struct UnkC
	{
		UInt32 ptr00;
		UInt32 unk04;
		UInt32 count08;
	};

	UInt32 unk004;
	UInt32 unk008;
	UnkC						unk00C;
	UnkC						unk018;
	AudioRequest				request024;			// 024
	AudioRequest				request034;			// 034
	AudioRequest				request044;			// 044
	NiTPointerMap<BSGameSound>	playingSounds;		// 054
	NiTPointerMap<BSSoundInfo>	playingSoundInfos1;	// 064
	NiTPointerMap<BSSoundInfo>	playingSoundInfos2;	// 074
	NiTPointerMap<NiAVObject>	soundPlayingObjects;// 084
	DList<BSGameSound>			cachedSounds;		// 094
	UInt32						unk0A0;				// 0A0
	UInt32						unk0A4;				// 0A4
	float						flt0A8;				// 0A8
	_RTL_CRITICAL_SECTION		criticalSectionAC;
	_RTL_CRITICAL_SECTION		criticalSectionC4;
	_RTL_CRITICAL_SECTION		criticalSectionDC;
	_RTL_CRITICAL_SECTION		criticalSectionF4;
	_RTL_CRITICAL_SECTION		criticalSection10C;
	DList<void>					list124;			// 124
	UInt32						lastTickCount;		// 130
	UInt8						byte134;			// 134
	UInt8						byte135;			// 135
	UInt8						pad136[2];			// 136
	UInt32						threadID;			// 138
	BSAudioManagerThread*		audioMgrThread;		// 13C
	float						volumes[12];		// 140
	//	0	Master
	//	1	Foot
	//	2	Voice
	//	3	Effects
	//	4	Music
	//	5	Radio
	UInt32						unk170;				// 170
	UInt8						byte174;			// 174
	UInt8						byte175;			// 175
	UInt8						pad176[2];			// 176
	UInt32						unk178;				// 178
	UInt32						unk17C;				// 17C
	UInt32						nextMapKey;			// 180
	UInt8						ignoreTimescale;
	UInt8						byte185;
	UInt8						byte186;
	UInt8						byte187;

	void AddRequest(UInt32 type, UInt32 soundID, UInt32 intValue, UInt32 next, UInt32 a6, float posX = 0, float posY = 0, float posZ = 0) { ThisCall(0xADB1A0, this, type, soundID, intValue, next, a6, posX, posY, posZ); };

	static BSAudioManager* GetSingleton() { return reinterpret_cast<BSAudioManager*>(0x11F6EF0); };
};
static_assert(sizeof(BSAudioManager) == 0x188);

class BSAudioListener
{
public:
	virtual void	Destroy(bool doFree);
	virtual void	Unk_01();
	virtual void	SetOriginWorldPos(NiPoint3* pos);
	virtual void	Unk_03();
	virtual void	UpdatePositionAndOrientation();
	virtual void	SetFrontAndTopOrientation(NiPoint3* front, NiPoint3* top);
	virtual void	Unk_06();
	virtual void	Unk_07();
	virtual void	SetVelocity(NiPoint3* pVelocity);
	virtual void	Unk_09();
	virtual void	Unk_0A();
	virtual void	Unk_0B();
	virtual void	SetRolloffFactor(float factor);
};

class IDirectSound3DListener;

// 64
class BSWin32AudioListener : public BSAudioListener
{
public:
	NiPoint3				originWorldPos;		// 04
	UInt32					unk10[6];			// 10
	NiPoint3				velocity;			// 28
	UInt32					sysTime;			// 34
	float					flt38;				// 38
	float					flt3C;				// 3C
	float					flt40;				// 40
	UInt32					unk44;				// 44
	IDirectSound3DListener** ptr48;			// 48
	NiPoint3				topOrientation;		// 4C
	NiPoint3				frontOrientation;	// 58
};
static_assert(sizeof(BSWin32AudioListener) == 0x64);

class IDirectSound8;
class IDirectSoundBuffer;

// A4
class BSWin32Audio
{
public:
	virtual void			Destroy(bool doFree);
	virtual void			CreateAudioListener(HWND _window);
	virtual void			Unk_02();
	virtual void			Unk_03();	// Does nothing
	virtual void			Unk_04();	// Does nothing
	virtual BSGameSound*	CreateGameSound(const char* filePath);
	virtual void			InsertPathPrefix(char* filePath);	// Prefixes path with data\\sound\\ if fx\\ or song\\.
	virtual void			Unk_07();	// Does nothing

	UInt8					byte04;			// 04
	UInt8					byte05;			// 05
	UInt8					byte06;			// 06
	UInt8					pad07;			// 07
	UInt32					unk08;			// 08
	UInt8					byte0C;			// 0C
	UInt8					pad0D[3];		// 0D
	BSWin32AudioListener*	listener;		// 10
	UInt32					unk14[3];		// 14
	bool					(*GetSoundDataFromRefID)(UInt32 refID, char* outFilePath, UInt32* outFlags, TESSound** outSound);	// 20	0x82D150
	bool					(*GetSoundDataFromEDID)(const char* EDIDstr, char* outFilePath, UInt32* outFlags, TESSound** outSound);	// 24	0x82D280
	bool					(*PickSoundFileFromFolder)(char* outFilePath);	// 28	0x5E3630
	UInt32					(*FillGameSoundProps)(UInt32* mapKey, TESSound* soundForm, UInt32* outFlags0C);	// 2C	0x82D400
	void					(*sub_832C40)();	// 30
	void					(*sub_832C80)();	// 34
	IDirectSound8**			ptr38;					// 38
	IDirectSoundBuffer*		ptr3C;					// 3C
	UInt32					unk40[24];				// 40
	HWND					window;					// A0

	static BSWin32Audio* GetSingleton() { return *(BSWin32Audio**)0x11F6D98; }
};
static_assert(sizeof(BSWin32Audio) == 0xA4);

// 30
class BSThread
{
public:
	virtual void Destroy(bool bDoFree);
	virtual bool ThreadProc();

	_RTL_CRITICAL_SECTION criticalsection;
	HANDLE createdThread;
	HANDLE creatorThread;
	UInt32 threadID;
	UInt32 creatorThreadID;
	bool bIsInitialised;
};

// 9C
class FAMThread : public BSThread
{
public:
	UInt32				unk30[27];	// 30
};

enum
{
	kMusicState_Pause = 1 << 2,
	kMusicState_Stop = 1 << 3,
	kMusicState_Play = 1 << 4,
	kMusicState_Loop = 1 << 5,
};

// 288
struct PlayingMusic
{
	enum Type
	{
		kPlayMusicCommand = 6,
		kRadio = 7,
		kMainMenu = 8,
		kNone = 9,
	};

	char						track1Path[MAX_PATH];	// 000
	FAMThread*					famThread;				// 104
	char						track2Path[MAX_PATH];	// 108
	UInt32						unk20C;					// 20C
	float						flt210;					// 210
	float						flt214;					// 214
	float						flt218;					// 218
	float						track1Volume;			// 21C
	UInt8						track1Flags;			// 220
	UInt8						track2Flags;			// 221
	UInt8						pad222[2];				// 222
	UInt32						track1Type;				// 224
	UInt32						unk228[8];				// 228
	float						flt248;					// 248
	float						flt24C;					// 24C
	float						flt250;					// 250
	float						track2Volume;			// 254
	UInt32						track2Type;				// 258
	UInt32						unk25C[8];				// 25C
	UInt32						track1Active;			// 27C
	UInt32						unk280;					// 280
	MediaLocationController*	medLocCtrl;				// 284

	static PlayingMusic* GetSingleton() { return (PlayingMusic*)0x11DD0F0; }
};
static_assert(sizeof(PlayingMusic) == 0x288);

// 0C
struct Sound
{
	UInt32		soundKey{};		// 00
	UInt8		byte04{};		// 04
	UInt8		pad05[3]{};		// 05
	UInt32		unk08{};		// 08

	Sound() : soundKey(0xFFFFFFFF), byte04(0), unk08(0) {}

	Sound(const char* soundPath, UInt32 flags) { ThisCall(0xAD7550, BSWin32Audio::GetSingleton(), this, soundPath, flags); }

	void Play() { ThisCall(0xAD8830, this, 1); }
	void SetNiNode(NiNode* node) { ThisCall(0xAD8F20, this, node); }
	void SetVolume(float volume) { ThisCall(0xAD89E0, this, volume); }
	void PlayDelayed(int delayMS, int unused) { ThisCall(0xAD8870, this, delayMS, unused); }

	void SetPos(float x, float y, float z) { ThisCall(0xAD8B60, this, x, y, z); }
	void SetPos(const NiPoint3* posVec) { ThisCall(0xAD8B60, this, posVec->x, posVec->y, posVec->z); }
	void SetPos(const NiPoint3 posVec) { ThisCall(0xAD8B60, this, posVec.x, posVec.y, posVec.z); }

	Sound& operator= (Sound other)
	{
		soundKey = other.soundKey;
		byte04 = other.byte04;
		unk08 = other.unk08;
		return *this;
	}

	bool IsPlaying() { return ThisCall<bool>(0xAD8930, this); }

	static void PlayEDID(const char* soundEDID, UInt32 flags, TESObjectREFR* refr);
	static void PlayFile(const char* filePath, UInt32 flags, TESObjectREFR* refr);
	static void PlayTESSound(TESSound* gameSound, UInt32 flags, TESObjectREFR* refr);

	static Sound InitByFilename(const char* path)
	{
		Sound sound;
		ThisStdCall(0xAD7480, CdeclCall<void*>(0x453A70), &sound, path, 0, nullptr);
		return sound;
	}

	void Set3D(Actor* actor);
};

void PlayGameSound(const char* soundPath);

// 1C
struct VoiceEntry
{
	struct Response
	{
		String		str;
		char*		fileName;
	};

	TList<void>		list00;
	Response*		response;
	TESTopicInfo*	topicInfo;
	TESTopic*		topic;
	TESQuest*		quest;
	Actor*			actor;
};

namespace Radio
{
	struct RadioEntry
	{
		struct Struct04
		{
			struct Struct00
			{
				TList<VoiceEntry>	voiceEntries;
				Struct00*			next;
			};

			Struct00*	unk00;
			UInt32		unk04;
			UInt32		rng08;
			UInt32		soundTimeRemaining0C;
			UInt8		byte10;
			UInt8		byte11;
			UInt8		gap12[2];
			UInt32		flags;
			TList<void> list18;
		};

		TESObjectREFR*	radioRef;
		Struct04		unk04;

		static RadioEntry* GetSingleton() { return *reinterpret_cast<RadioEntry**>(0x11DD42C); }
	};

	TESObjectREFR* GetCurrentStation();
	typedef RadioEntry::Struct04::Struct00 VoiceEntryList;

	static void (*SetEnabled)(bool toggleON) = (void(__cdecl*)(bool))0x8324E0;
	static void (*SetStation)(TESObjectREFR* station, bool toggleON) = (void(__cdecl*)(TESObjectREFR*, bool))0x832240;
	bool GetEnabled();
	TList<TESObjectREFR>* GetFoundStations();
	void GetNearbyStations(TList<TESObjectREFR>* dst);

	void SetActiveStation(TESObjectREFR* station);
}

#pragma once
#include <NiTypes.h>
#include <NiObjects.h>
#include <Containers.h>
#include <BaseFormComponent.h>


struct VariableInfo
{
	UInt32			idx;		// 00
	UInt32			pad04;		// 04
	Float64			data;		// 08
	UInt8			type;		// 10
	UInt8			pad11[3];	// 11
	UInt32			unk14;		// 14
	String			name;		// 18
};

enum EActionListForm
{
	eActionListForm_AddAt	= 00,
	eActionListForm_DelAt,
	eActionListForm_ChgAt,
	eActionListForm_GetAt,
	eActionListForm_Check,
	eActionListForm_Max,
};

enum EWhichListForm
{
	eWhichListForm_RaceHair					= 00,
	eWhichListForm_RaceEyes,
	eWhichListForm_RaceHeadPart,			// ? //
	eWhichListForm_BaseFaction,
	eWhichListForm_BaseRank,
	eWhichListForm_BasePackage,
	eWhichListForm_BaseSpellListSpell,
	eWhichListForm_BaseSpellListLevSpell,
	eWhichListForm_FactionRankName,
	eWhichListForm_FactionRankFemaleName,
	eWhichListForm_HeadParts,
	eWhichListForm_LevCreatureRef,
	eWhichListForm_LevCharacterRef,
	eWhichListForm_FormList,
	eWhichListForm_Max,
};

#pragma once

class hkaRaycastInterface
{
public:
	hkaRaycastInterface();
	~hkaRaycastInterface();
	virtual hkaRaycastInterface*	Destroy(bool doFree);
	virtual void					Unk_01(void* arg0);
	virtual void					Unk_02();

	// Assumed to be 0x010 bytes due to context where the vftable is used
	UInt32							unk000[(0x010 - 0x004) >> 2];	// 0000
};
static_assert(sizeof(hkaRaycastInterface) == 0x010);

class bhkRagdollController : public hkaRaycastInterface
{
public:
	bhkRagdollController();
	~bhkRagdollController();

	UInt32	unk000[(0x021C - 0x010) >> 2];	// 0010
	UInt8	fill021C[3];					// 021C
	bool	bool021F;						// 021F	when null assume FIK status is false
	bool	fikStatus;						// 0220
	UInt8	fill0221[3];					// 0221
};
static_assert(sizeof(bhkRagdollController) == 0x0224);

class PathingLocation
{
public:
	void* vtbl;
	NiPoint3 location;
	UInt32 currentNavMeshInfo;
	UInt32 navMeshInfo;
	TESObjectCELL* cell;
	TESWorldSpace* worldspace;
	UInt32 unk020;
	UInt16 unk024;
	UInt8 flags026;
	UInt8 gap027;
};


typedef TList<BGSQuestObjective::Target> QuestObjectiveTargets;

struct CasinoStats
{
	UInt32		casinoRefID;
	UInt32		earnings;
	UInt16		unk08;
	UInt8		gap0A[2];
};

template <typename ...Args>
void ApplyPerkModifiers(UInt32 id, Actor* actor, Args ...args)
{
	CdeclCall<void>(0x05E58F0, id, actor, std::forward<Args>(args)...);
}

enum APCostActions
{
	kActionPointsAttackUnarmed = 0x0,
	kActionPointsAttackOneHandMelee = 0x1,
	kActionPointsAttackTwoHandMelee = 0x2,
	kActionPointsAttackPistol = 0x3,
	kActionPointsAttackRifle = 0x4,
	kActionPointsAttackHandle = 0x5,
	kActionPointsAttackLauncher = 0x6,
	kActionPointsAttackGrenade = 0x7,
	kActionPointsAttackMine = 0x8,
	kActionPointsReload = 0x9,
	kActionPointsCrouch = 0xA,
	kActionPointsStand = 0xB,
	kActionPointsSwitchWeapon = 0xC,
	kActionPointsToggleWeaponDrawn = 0xD,
	kActionPointsHeal = 0xE,
	kActionPointsVATSUnarmedAttack1 = 0x11,
	kActionPointsOneHandThrown = 0x13,
	kActionPointsAttackThrown = 0x14,
	kActionPointsVATSUnarmedAttackGround = 0x15,
};

struct __declspec(align(4)) VATSQueuedAction
{
	APCostActions			actionType;
	UInt8					isSuccess;
	UInt8					byte05;
	UInt8					isMysteriousStrangerVisit;
	UInt8					byte07;
	UInt8					remainingShotsToFire_Burst;
	UInt8					count09;
	UInt8					gap0A[2];
	TESObjectREFR*			unkref;
	ActorValueCode			bodyPart;
	ActorHitData*			hitData;
	float					unk18;
	float					unk1C;
	float					apCost;
	UInt8					isMissFortuneVisit;
	UInt8					gap25[3];
};

enum AnimMoveTypes
{
	kAnimMoveType_Walking = 0x0,
	kAnimMoveType_Sneaking = 0x1,
	kAnimMoveType_Swimming = 0x2,
	kAnimMoveType_Flying = 0x3,
};

const char* GetActorValueString(UInt32 actorValue); // should work now
UInt32 GetActorValueForString(const char* strActorVal, bool bForScript = false);

typedef char* (*_GetActorValueName)(UInt32 actorValueCode);
extern const _GetActorValueName GetActorValueName;
UInt32 GetActorValueMax(UInt32 actorValueCode);


#pragma once
#include <NiNodes.h>
#include <OSDepend.h>

#include "Utilities.h"


struct MouseFilter
{
	float targetValue = 0;
	float remainingValue = 0;
	float lastAmount = 0;

	float smooth(float delta, float scale)
	{
		targetValue += delta;
		delta = (targetValue - remainingValue) * scale;
		lastAmount += (delta - lastAmount) * 0.5F;

		if (delta > 0.0F && delta > lastAmount || delta < 0.0F && delta < lastAmount)
		{
			delta = lastAmount;
		}

		remainingValue += delta;
		return delta;
	}

	void reset()
	{
		targetValue = 0;
		remainingValue = 0;
		lastAmount = 0;
	}
};


enum class IsDXKeyState
{
	IsHeld		= 0x0,
	IsPressed	= 0x1,
	IsDepressed	= 0x2,
	IsChanged	= 0x3,
};


enum AnimState
{
	kAnimState_Inactive		= 0x0,
	kAnimState_Animating	= 0x1,
	kAnimState_EaseIn		= 0x2,
	kAnimState_EaseOut		= 0x3,
	kAnimState_TransSource	= 0x4,
	kAnimState_TransDest	= 0x5,
	kAnimState_MorphSource	= 0x6,
};

enum class ControlCode
{
	Forward = 0x0,
	Backward = 0x1,
	Left = 0x2,
	Right = 0x3,
	Attack = 0x4,
	Activate = 0x5,
	Aim = 0x6,
	ReadyItem = 0x7,
	Crouch = 0x8,
	Run = 0x9,
	AlwaysRun = 0xA,
	AutoMove = 0xB,
	Jump = 0xC,
	TogglePOV = 0xD,
	MenuMode = 0xE,
	Rest = 0xF,
	VATS_ = 0x10,
	Hotkey1 = 0x11,
	AmmoSwap = 0x12,
	Hotkey3 = 0x13,
	Hotkey4 = 0x14,
	Hotkey5 = 0x15,
	Hotkey6 = 0x16,
	Hotkey7 = 0x17,
	Hotkey8 = 0x18,
	QuickSave = 0x19,
	QuickLoad = 0x1A,
	Grab = 0x1B,
	Escape = 0x1C,
	Console = 0x1D,
	Screenshot = 0x1E,
};

extern OSInputGlobals** g_inputGlobals;



//TESAnimGroup::AnimGroupInfo* GetGroupInfo(UInt8 groupId);
UInt32 GetSequenceType(UInt8 groupId);

TESForm* __stdcall LookupFormByRefID(UInt32 refID);
void FormatScriptText(std::string& str);

UInt16 GetActorRealAnimGroup(Actor* actor, UInt8 groupID);