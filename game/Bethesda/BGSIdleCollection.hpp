#pragma once
#include "BaseFormComponent.hpp"

// 0x10
class BGSIdleCollection : public BaseFormComponent
{
	UInt8		byte4;
	UInt8		byte5;
	UInt32		dword8;
	Float32		floatC;
};
static_assert(sizeof(BGSIdleCollection) == 0x10);