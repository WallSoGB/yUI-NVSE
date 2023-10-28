#pragma once
#include "ExtraContainerChanges.hpp"
#include "TESChildCell.hpp"
#include "ExtraDroppedItemList.hpp"

class ExtraScript;
class NiNode;
class TESContainer;
class TESSound;
struct AnimData;
struct BipedAnim;
class NiGeometry;
class ExtraDroppedItemList;
class ValidBip01Names;
class ExtraLockData;
class hkpRigidBody;

struct LoadedRefData {
	TESObjectREFR* pCurrentWaterType;
	UInt32 iUnderwaterCount;
	float fRelevantWaterHeight;
	float revealDistance;
	UInt32 flags;
	NiNodePtr spNode;
	NiNode* niNode18;
};

class TESObjectREFR : public TESForm
{
public:

	TESObjectREFR();
	~TESObjectREFR() override;
	virtual void				GetStartingPosition(NiPoint3* pos, NiPoint3* rot, TESForm** formOut, TESForm* defaultCell);
	virtual void				Unk_4F();
	virtual void				Unk_50();
	virtual void				Unk_51();
	virtual bool				CastShadows();
	virtual void				Unk_53();
	virtual void				IsCastShadows();
	virtual void				SetCastShadows(char a2);
	virtual void				Unk_56();
	virtual bool				IsObstacle();
	virtual void				MarkBaseFormAsModified();
	virtual void				Unk_59();
	virtual void				Unk_5A();
	virtual void				GetStartingAngle();
	virtual void				GetStartingPos();
	virtual void				SetStartingPos(NiPoint3 pos);
	virtual void				Unk_5E();
	virtual TESObjectREFR*		RemoveItem(TESForm* toRemove, BaseExtraList* extraList, UInt32 count, UInt32 keepOwner, UInt32 drop, TESObjectREFR* destRef, 
		UInt32 unk6, UInt32 unk7, UInt32 unk8, UInt8 unk9);	// 40 unk2 quantity? Returns the reference assigned to the removed item.

	//	virtual void				GetBodyPartData();
	virtual void				RemoveByType(int type, char keepOwner, int count);
	virtual bool				EquipObject(TESForm* item, UInt32 count, ExtraDataList* xData, bool lockEquip);
	virtual void				Unk_62();	// Linked to Unequip (and or equip maybe)
	virtual void				Unk_63();
	virtual void				AddItem(TESForm* item, ExtraDataList* xDataList, UInt32 Quantity);	// Needs confirmation
	virtual void				Unk_65();
	virtual void				GetMagicCaster();
	virtual void				GetMagicTarget();							// Actor: GetMagicEffectList
	virtual bool				GetIsChildSize(bool checkHeight);		// 068 Actor: GetIsChildSize
	virtual UInt32				GetActorUnk0148();					// result can be interchanged with baseForm, so TESForm* ?
	virtual void				SetActorUnk0148(UInt32 arg0);
	virtual void				GetBSFaceGenNiNodeBiped();
	virtual void				GetBSFaceGenNiNodeSkinned();				// REFR: GetBSFaceGenNiNodeSkinned
	virtual void				Unk_6D();				// REFR: calls 006C
	virtual void				Unk_6E();				// MobileActor: calls 006D then NiNode::Func0040
	virtual void				Unk_6F();
	virtual bool				Unload3D();
	virtual void				AnimateNiNode();					// same in FOSE ! identical to Func0052 in OBSE which says (inits animation-related data, and more)
	virtual void				GenerateNiNode(bool arg0);				// same in FOSE !
	virtual void				Set3D(NiNode* niNode, bool unloadArt);	// same in FOSE !
	virtual NiNode *			GetNiNode();						// same in FOSE !
	virtual void				IsBaseFormCastsShadows();
	virtual NiPoint3*			GetMinBounds(NiPoint3* out);
	virtual NiPoint3*			GetMaxBounds(NiPoint3* out);
	virtual void				Unk_78();
	virtual AnimData*			GetAnimData();			// 0079
	virtual ValidBip01Names*	GetValidBip01Names();	// 007A	Character only
	virtual ValidBip01Names*	CallGetValidBip01Names();
	virtual void				SetValidBip01Names(ValidBip01Names validBip01Names);
	virtual NiPoint3*			GetPos();				// GetPos or GetDistance
	virtual void				Unk_7E(UInt32 arg0);
	virtual void				UpdateNiNode(char a2);
	virtual void				Unk_80(UInt32 arg0);
	virtual void				Unk_81(UInt32 arg0);
	virtual void				Unk_82();
	virtual NiNode*				GetProjectileNode();
	virtual void				Unk_84(UInt32 arg0);
	virtual UInt32				GetSitSleepState();				// 0 or GetActor::Unk01AC
	virtual bool				IsCharacter();				// return false for Actor and Creature, true for character and PlayerCharacter
	virtual bool				IsCreature();
	virtual bool				IsExplosion();
	virtual bool				IsProjectile();
	virtual void				SetParentCell();				// SetParentCell (Interior only ?)
	virtual bool				HasNoHealthOrDestroyed(bool essentialUnconcious = false);			// IsDead = HasNoHealth (baseForm health <= 0 or Flags bit23 set)
	virtual bool				GetHasKnockedState();
	virtual bool				Unk_8D();
	virtual void				Unk_8E();
	virtual void				GetExtraDataAnimNoteReceiver();

#ifdef EDITOR
	EditorData	editorData;			// +04
#endif
	TESChildCell*	pkChildCell;
	TESSound*		pkLoopSound;
	TESForm*		pkObjectReference;
	NiPoint3		kRotation;
	NiPoint3		kPosition;
	Float32			fRefScale;
	TESObjectCELL*	pkParentCell;
	ExtraDataList	kExtraList;
	LoadedRefData*	pkLoadedData;

	ExtraScript* GetExtraScript() const;
	ScriptEventList* GetEventList() const;

	bool IsTaken() const { return (eFlags & kFlags_Taken) != 0; }
	bool IsPersistent() const { return (eFlags & kFlags_Persistent) != 0; }
	bool IsTemporary() { return (eFlags & kFlags_Temporary) ? true : false; }
	bool IsDeleted() const { return (eFlags & kFlags_Deleted) ? true : false; }

	bool Update3D();
	bool Update3D_v1c();	// Less worse version as used by some modders
	TESContainer* GetContainer();
	bool IsMapMarker();
//	bool GetInventoryItems(InventoryItemsMap& invItems);
	ExtraDroppedItemList* GetDroppedItems();
	bool GetVisibleWhenDistant();

	double GetHeadingAngle(const TESObjectREFR* to) const;

	static TESObjectREFR* Create(bool abTemp = false);

	const char* GetModelPath();

	__forceinline TESObjectCELL* GetParentCell() const { return pkParentCell; }

	static TESObjectREFR* FindReferenceFor3D(NiAVObject* apObject) {
		return CdeclCall<TESObjectREFR*>(0x56F930, apObject);
	}

	TESForm* GetBaseForm();
	void InitBaseForm(TESForm* apForm);

	bool HandleActivation();


	SInt32					GetItemCount(TESForm* form) { return ThisCall<SInt32>(0x575610, this, form); };
	void					AddItemAlt(TESForm* item, UInt32 count, float condition, bool doEquip);
	bool					GetInventoryItems(UInt8 typeID);
	TESWorldSpace*			GetParentWorld() { return ThisCall<TESWorldSpace*>(0x575D70, this); };
	bool __fastcall			GetInSameCellOrWorld(const TESObjectREFR* target) const;
	Float32 __vectorcall	GetDistance(TESObjectREFR* target);
	Float32 __vectorcall	GetDistance2D(TESObjectREFR* target);
	void					SetPos(NiPoint3& posVector);
	void					SetAngle(NiPoint3& rotVector);
	Float32					GetHeadingAngle(const TESObjectREFR* target);
	bool					MoveToCell(TESForm* worldOrCell, NiPoint3& posVector);
	void					DeleteReference();
	TESObjectREFR*			GetMerchantContainer();
	float					GetWaterImmersionPerc();
	bool					IsMobile();
	bool					IsGrabbable();
	bool					ValidForHooks();
	NiAVObject*				GetNiBlock(const char* blockName);
	NiNode* __fastcall		GetNode(const char* nodeName);
	hkpRigidBody*			GetRigidBody(const char* nodeName);
	bool					RunScriptSource(const char* sourceStr);
	ExtraLockData*			GetLockData() const { return ThisCall<ExtraLockData*>(0x569160, (void*) this); }
	void					SetScale(float scale);
	bool					IsOwnedByActor(Actor* actor, bool includeFactionOwnership) { return ThisCall<bool>(0x5785E0, this, actor, includeFactionOwnership); };
	TESObjectREFR*			ResolveOwnership() { return ThisCall<TESObjectREFR*>(0x567790, this); };
	bool					IsInInterior() { return ThisCall<bool>(0x575D10, this); };
	NiNode*					GetNiNode2();
	NiAVObject*				GetNifBlock(UInt32 pcNode, const char* blockName);
	bool					IsCrimeOrEnemy();
	NiPoint3				GetCenter() const;
	NiPoint3				GetDimensions() const;
	__forceinline Float32	GetScale() { return ThisCall<float>(0x567400, this); }
	TESObjectREFR*			ResolveAshpile();
	bool					IsLocked() const;

	__forceinline bool		Activate(Actor* activator, UInt32 unk1, UInt32 unk2, UInt32 unk3) { return ThisCall<bool>(0x573170, this, activator, unk1, unk2, unk3); }

	Float64					GetInventoryWeight();

	std::vector<InventoryChanges*> GetAllItems(UInt32 checkLinkedRec = 0);

	void					OpenCloseContainer(bool open = false, bool sounds = true);

	const char*				GetBaseFormFullName() { return ThisCall<const char*>(0x55D520, this); }
	const char*				GetJIPName();
	static TESObjectREFR*	FindReferenceFor3D(const NiNode* node) { return CdeclCall<TESObjectREFR*>(0x56F930, node); }
};
static_assert(sizeof(TESObjectREFR) == 0x68);

TESForm* GetPermanentBaseForm(TESObjectREFR* thisObj);	// For LevelledForm, find real baseForm, not temporary one.

// Taken from JIP LN NVSE.
float __vectorcall GetDistance3D(const TESObjectREFR* ref1, const TESObjectREFR* ref2);