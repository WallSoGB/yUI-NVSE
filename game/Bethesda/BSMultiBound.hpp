#pragma once
#include "BSMultiBoundAABB.hpp"

NiSmartPointer(BSMultiBound);

// 0x10
class BSMultiBound : public NiObject
{
public:
	BSMultiBound();
	~BSMultiBound();

	UInt32 uiBoundFrameCount;
	BSMultiBoundAABBPtr spShape;

	static bool bIgnoreMultiBounds;

	CREATE_OBJECT(BSMultiBound, 0xC361A0);

	BSMultiBoundAABB* GetShape() const;
	void SetShape(BSMultiBoundAABB* apShape);
};
static_assert(sizeof(BSMultiBound) == 0x10);