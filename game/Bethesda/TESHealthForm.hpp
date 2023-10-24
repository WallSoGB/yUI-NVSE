#pragma once
#include "BaseFormComponent.hpp"
// Complete

// 0x8
class TESHealthForm : public BaseFormComponent {
public:
	TESHealthForm();
	~TESHealthForm() override;
	virtual UInt32	GetHealth();	// 0004

	UInt32	health;		// 004
};
static_assert(sizeof(TESHealthForm) == 0x8);