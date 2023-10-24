#pragma once

#include "NiRefObject.hpp"
#include "NiString.hpp"

class BSFaceGenMorphDataHair;

class BSFaceGenModel : public NiRefObject {
public:
	struct MeshData
	{
		NiString egmPath;
		UInt32 unk008;
		NiRefObject* unk00C;
		NiRefObject* unk010;
		UInt32 unk014;
		UInt32 unk018;
		BSFaceGenMorphDataHair* hairMorph;
		UInt32 unk020;
	};

	BSFaceGenModel::MeshData* meshData;
	UInt32 unk0C;
};