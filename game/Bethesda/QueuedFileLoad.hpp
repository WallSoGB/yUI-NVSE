#pragma once

#include "QueuedFileEntry.hpp"
#include "NiRefObject.hpp"

NiSmartPointer(QueuedFile);

class QueuedFileLoad : public QueuedFileEntry {
public:
	QueuedFileLoad();
	~QueuedFileLoad();

	NiRefObjectPtr spObject;
	UInt32 dword34;
};

ASSERT_SIZE(QueuedFileLoad, 0x38);