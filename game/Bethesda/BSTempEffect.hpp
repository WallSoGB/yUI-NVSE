#pragma once
#include "NiObject.hpp"

class TESObjectCELL;
class NiNode;

// 0x18
class BSTempEffect : public NiObject 
{
public:
	BSTempEffect();
	virtual ~BSTempEffect();

	virtual void			Initialize();			// 35
	virtual BSTempEffect*	GetSelf();				// 36 | ???? Used by particles
	virtual bool			Update(float afTime);	// 37 | Returns true if effect is finished
	virtual NiNode*			Get3D();				// 38 | Returns geometry
	virtual void			Unk_39();				// 39 | ????
	virtual bool			Unk_40();				// 40 | ???? Used by MagicModelHitEffect and particles
	virtual UInt32			GetSaveSize();			// 41
	virtual void			SaveGame();				// 42
	virtual void			SaveGame2();			// 43 | Saves cell refid, skips bInitialized
	virtual void 			LoadGame();				// 44
	virtual void			LoadGame2();			// 45 | Loads cell refid?
	virtual void			SetTarget();			// 46 | Used by MagicHitEffect
	virtual void			Unk_47();				// 47 | ????
	virtual bool			IsFirstPerson();		// 48 | Used by shell casings

	Float32			fLifetime;
	TESObjectCELL*	pkCell;
	Float32			fAge;
	bool			bInitialized;
};
static_assert(sizeof(BSTempEffect) == 0x18);