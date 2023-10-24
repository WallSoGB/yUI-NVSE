#pragma once
#include "QueuedFileEntry.hpp"
#include "NiSourceTexture.hpp"

class QueuedTexture : public QueuedFileEntry {
public:
	QueuedTexture();
	~QueuedTexture();

	NiSourceTexturePtr spTexture;	// 030
	UInt8 flags;				// 034
};
static_assert(sizeof(QueuedTexture) == 0x38);