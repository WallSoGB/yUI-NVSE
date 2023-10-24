#pragma once

#include "QueuedFileEntry.hpp"
#include "Model.hpp"
#include "TESModel.hpp"
#include <BSFadeNode.hpp>

NiSmartPointer(QueuedModel);

// 0x48
class QueuedModel : public QueuedFileEntry {
public:
	QueuedModel();
	~QueuedModel();

	virtual void Unk_0C(UInt32 arg0);

	ModelPtr		spModel;
	TESModel*		pTESModel;
	ENUM_LOD_MULT	eLODFadeMult;
	UInt8			ucFlags;	// bit 0 and bit 1 init'd by parms, bit 2 set after textureSwap, bit 3 is model set, bit 4 is file found.
	UInt8			pad03D[3];		// 03D
	float			flt040;
	UInt32			unk044;
};
static_assert(sizeof(QueuedModel) == 0x48);