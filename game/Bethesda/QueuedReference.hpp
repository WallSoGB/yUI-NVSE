#pragma once

#include "QueuedFile.hpp"
#include "NiRefObject.hpp"

class TESObjectREFR;
class NiRefObject;
class NiNode;
class AttachDistant3DTask;

NiSmartPointer(QueuedReference);

// 0x40
class QueuedReference : public QueuedFile {
public:
	QueuedReference();
	~QueuedReference();

	virtual void QueueModels();
	virtual void UseDistant3D();
	virtual void AttachDistant3D(NiNode* apNode);
	virtual bool BackgroundClone();
	virtual void DoAttach();
	virtual void FinishAttach();

	TESObjectREFR*					pRefr;
	NiRefObjectPtr					spUnk02C;
	NiRefObjectPtr					spUnk030;
	NiRefObjectPtr					spCloned3D;
	NiPointer<AttachDistant3DTask>	spAttachDistant3DTask;
	UInt32							uiWaitCount;
};
static_assert(sizeof(QueuedReference) == 0x40);