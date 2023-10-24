#pragma once

#include "IOTask.hpp"
#include "BSSimpleArray.hpp"
#include "NiSmartPointer.hpp"

class QueuedReference;
class QueuedChildren;
class QueuedParents;
class NiObject;

NiSmartPointer(QueuedFile);

// 0x28
class QueuedFile : public IOTask {
public:
	QueuedFile();
	~QueuedFile();

	virtual void DoRequestHandles();
	virtual void DoOnChildrenFinished(UInt32 arg0);
	virtual void DoOnTaskFinished();

	// size?
	struct FileEntry {
		UInt32	unk00;
		UInt32	unk04;
		UInt32	uiSize;
		UInt32	uiOffset;
	};

	UInt32 eContext;
	QueuedReference* spParent;
	QueuedChildren* pChildren;
	QueuedParents* pParents;
};
static_assert(sizeof(QueuedFile) == 0x28);

// 0x14
class QueuedChildren : public BSSimpleArray<NiPointer<QueuedFile>> {
	UInt32	counter;
};
static_assert(sizeof(QueuedChildren) == 0x14);