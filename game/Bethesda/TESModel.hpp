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
	virtual void	SetModel(char* apcPath);	// 06
	virtual bool	Unk_07();

	virtual				~TESModel();
	virtual const char*	GetModel();
	virtual void		SetModel(const char* apcPath);
	virtual bool		Unk_7();

	enum {
		kFacegenFlag_Head = 0x01,
		kFacegenFlag_Torso = 0x02,
		kFacegenFlag_RightHand = 0x04,
		kFacegenFlag_LeftHand = 0x08,
	};

	BSStringT	kModel;
	void*		pTexturesA;
	void*		pMaterialsA;
	UInt8		ucFacegenFlags;
	UInt8		pad15[3];

	void SetPath(const char* newPath) { kModel.Set(newPath); }
};
static_assert(sizeof(TESModel) == 0x18);