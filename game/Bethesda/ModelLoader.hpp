#pragma once
#include "KFModel.hpp"
#include "LockFreeMap.hpp"
#include "LockFreeQueue.hpp"
#include "NiSmartPointer.hpp"
#include "QueuedAnimIdle.hpp"
#include "QueuedHelmet.hpp"
#include "QueuedReference.hpp"
#include "QueuedReplacementKFList.hpp"
#include "QueuedTexture.hpp"
#include "BackgroundCloneThread.hpp"
#include "AttachDistant3DTask.hpp"
#include "IOManager.hpp"

class Animation;
class AnimIdle;
struct BSFileEntry;
class KFModel;
class LoadedFile;
class Model;
class TESObjectREFR;

class ModelLoader {
public:
	ModelLoader();
	~ModelLoader();

	LockFreeCaseInsensitiveStringMap<Model*>*						pModelMap;
	LockFreeCaseInsensitiveStringMap<KFModel*>*						pKFModelMap;
	LockFreeMap<TESObjectREFR*, NiPointer<QueuedReference> >*		pQueuedReferenceMap1;
	LockFreeMap<TESObjectREFR*, NiPointer<QueuedReference> >*		pQueuedReferenceMap2;
	LockFreeMap<AnimIdle*, NiPointer<QueuedAnimIdle>>*				pQueuedAnimIdleMap;
	LockFreeMap<Animation*, NiPointer<QueuedReplacementKFList>>*	pQueuedReplacementKFListMap;
	LockFreeMap<TESObjectREFR*, NiPointer<QueuedHelmet>>*			pQueuedHelmetMap;
	LockFreeQueue<NiPointer<AttachDistant3DTask>>*					pAttachDistant3DTaskQueue;
	LockFreeMap<BSFileEntry*, NiPointer<QueuedTexture>>*			pQueuedTextureMap;
	LockFreeCaseInsensitiveStringMap<LoadedFile*>*					pLoadedFileMap;
	BackgroundCloneThread*											pBackgroundCloneThread;
	bool															bHasDelayedFree;

	static ModelLoader* GetSingleton();

	UInt32 GetReferenceCount();
	UInt32 GetTotalTaskCount();

	void QueueReference(TESObjectREFR* apRefr, IO_TASK_PRIORITY aePriority, bool abAllowQueueReferenceQueuing);

	NiNode* LoadFile(const char* apPath, UInt32 aeLODFadeMult, bool a4, int a5, char a6, bool abNoRefCountIncrease);

	static void __fastcall DisplayDebugLoadingText(ModelLoader* apThis);
	static bool __fastcall UpdateAttachDistant3DQueue(ModelLoader* apThis);
};
static_assert(sizeof(ModelLoader) == 0x30);