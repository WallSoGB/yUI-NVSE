#pragma once

#include "NiNode.hpp"

NiSmartPointer(Model);

class Model {
public:
	Model();
	~Model();

	const char* path;
	UInt32		RefCounter1;
	UInt32		RefCounter2;
	NiNode*		spNode;
};

ASSERT_SIZE(Model, 0x10)