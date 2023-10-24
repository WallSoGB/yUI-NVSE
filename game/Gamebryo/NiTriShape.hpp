#pragma once

#include "NiTriBasedGeom.hpp"

NiSmartPointer(NiTriShape);

class NiTriShape : public NiTriBasedGeom {
public:
	NiTriShape();
	virtual ~NiTriShape();

	CREATE_OBJECT(NiTriShape, 0xA744D0);

	NiTriShapeData* GetModelData();

	UInt32 GetTriListLength();
	UInt16* GetTriList();

	static void __fastcall RenderImmediateEx(NiTriShape* apThis, void*, NiDX9Renderer* apRenderer);
	static void __fastcall RenderImmediateAltEx(NiTriShape* apThis, void*, NiDX9Renderer* apRenderer);
};

ASSERT_SIZE(NiTriShape, 0xC4);