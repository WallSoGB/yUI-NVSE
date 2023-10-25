#pragma once
#include "NiAVObject.hpp"
#include "NiTArray.hpp"

NiSmartPointer(NiNode);
NiRTTIAddress(NiNode, 0x11F4428);

class NiNode : public NiAVObject {
public:
	NiNode();
	virtual ~NiNode();

	virtual void			AttachChild(NiAVObject* pkChild, bool bFirstAvail);
	virtual void			InsertChildAt(UInt32 i, NiAVObject* pkChild);
	virtual void			DetachChild(NiAVObject* pkChild, NiAVObjectPtr* aspAVObject);
	virtual void			DetachChildAlt(NiAVObject* pkChild);
	virtual void			DetachChildAt(UInt32 i, NiAVObjectPtr* aspAVObject);
	virtual NiAVObject*		DetachChildAtAlt(UInt32 i);
	virtual void			SetAt(UInt32 i, NiAVObject* pkChild, NiAVObjectPtr* aspAVObject);
	virtual void			SetAtAlt(UInt32 i, NiAVObject* pkChild);
	virtual void			UpdateUpwardPass();

	NiTObjectArray<NiAVObjectPtr> m_kChildren;

	CREATE_OBJECT(NiNode, 0xA5F030);

	UInt32 GetArrayCount();
	UInt32 GetChildCount();
	NiAVObject* GetAt(UInt32 i);

	NiNode* FindNodeByName(const NiFixedString& akName);

	static void __fastcall OnVisibleEx(NiNode* apThis, void*, NiCullingProcess* apCuller);
};

ASSERT_SIZE(NiNode, 0xAC);