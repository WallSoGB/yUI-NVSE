#pragma once

#include "NiGeometry.hpp"

class NiTriBasedGeomData;

class NiTriBasedGeom : public NiGeometry {
public:
	NiTriBasedGeom();
	virtual ~NiTriBasedGeom();

	virtual void GetModelTriangle(UInt16 usTriangle, NiPoint3*& pkP0, NiPoint3*& pkP1, NiPoint3*& pkP2);

	NiTriBasedGeomData* GetModelData();
};

ASSERT_SIZE(NiTriBasedGeom, 0xC4);