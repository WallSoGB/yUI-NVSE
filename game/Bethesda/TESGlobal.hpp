#pragma once
#include "TESForm.hpp"

// 28
class TESGlobal : public TESForm {
public:
	TESGlobal();
	~TESGlobal();

	enum
	{
		kType_Short = 's',
		kType_Long = 'l',
		kType_Float = 'f'
	};

	BSStringT	name;		// 18
	UInt8	type;		// 20
	UInt8	pad21[3];	// 21
	float	data;		// 24
};
static_assert(sizeof(TESGlobal) == 0x28);