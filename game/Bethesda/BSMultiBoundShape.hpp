#pragma once

#include "NiObject.hpp"
#include "NiPoint3.hpp"

NiSmartPointer(BSMultiBoundShape);

class BSMultiBoundShape : public NiObject {
public:
	struct BoundVertices {
		NiPoint3 point[8];
	};


	enum BSMBCullResult
	{
		BS_CULL_UNTESTED = 0x0,
		BS_CULL_VISIBLE = 0x1,
		BS_CULL_CULLED = 0x2,
		BS_CULL_OCCLUDED = 0x3,
	};

	BSMBCullResult kCullResult;
};

ASSERT_SIZE(BSMultiBoundShape, 0xC);