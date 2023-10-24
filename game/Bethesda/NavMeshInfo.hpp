#pragma once

#include "NiPoint3.hpp"

class TESObjectCELL;

struct NavMeshInfo {
	UInt32 refID;
	UInt32 cellID;
	UInt32 flags;
	UInt32 coords;
	NiPoint3 NiPoint3;
	TESObjectCELL* parentCell;
	float float20;
	TESObjectCELL* cell2;
	BYTE gap28[12];
	SInt32 int34;
	BYTE gap38[12];
	UInt32 dword44;
	BYTE gap48[12];
	UInt32 dword54;
	UInt32 dword58;
};