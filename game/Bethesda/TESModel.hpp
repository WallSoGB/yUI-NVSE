#pragma once
#include "BaseFormComponent.hpp"
#include "BSString.hpp"

// 0x18
class TESModel : public BaseFormComponent
{
public:
	TESModel();

	virtual			~TESModel();
	virtual char*	GetModel();
	virtual void	SetModel(const char* apcPath);	// 06
	virtual bool	Unk_07();

	enum {
		kFacegenFlag_Head		= 1 << 0,
		kFacegenFlag_Torso		= 1 << 1,
		kFacegenFlag_RightHand	= 1 << 2,
		kFacegenFlag_LeftHand	= 1 << 3,
	};

	BSStringT<char>	kModel;
	void*			pTexturesA;
	void*			pMaterialsA;
	UInt8			ucFacegenFlags;
	UInt8			pad15[3];

	void SetPath(const char* newPath) { kModel.Set(newPath); }
};
static_assert(sizeof(TESModel) == 0x18);