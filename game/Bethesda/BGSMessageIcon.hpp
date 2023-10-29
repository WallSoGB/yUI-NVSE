#pragma once
#include "TESIcon.hpp"

// 0x10
class BGSMessageIcon :
	public BaseFormComponent
{
public:
	BGSMessageIcon();
	~BGSMessageIcon();
	TESIcon kMessageIcon;
};
static_assert(sizeof(BGSMessageIcon) == 0x10);