#pragma once
#include "TESBoundAnimObject.hpp"
#include "TESModelTextureSwap.hpp"
#include "TESScriptableForm.hpp"
#include "BGSDestructibleObjectForm.hpp"
#include "BGSOpenCloseForm.hpp"

class TESSound;

// 0x90
class TESObjectDOOR :
	public TESBoundAnimObject,			// 00
	public TESFullName, 				// 30
	public TESModelTextureSwap,			// 3C
	public TESScriptableForm,			// 5C
	public BGSDestructibleObjectForm,	// 68
	public BGSOpenCloseForm				// 70 
{
public:
	TESObjectDOOR();
	~TESObjectDOOR();

	UInt32 unk74;
	TESSound* openSound;
	TESSound* closeSound;
	TESSound* randomLoopingSound;
	UInt8 flags84;
	UInt8 byte85;
	UInt8 byte86;
	UInt8 byte87;
	BSSimpleList<int> list88;
};
static_assert(sizeof(TESObjectDOOR) == 0x90);