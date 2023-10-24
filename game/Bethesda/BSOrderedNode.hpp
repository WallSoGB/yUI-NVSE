#pragma once

#include "BSNiNode.hpp"

NiSmartPointer(BSOrderedNode);

class BSOrderedNode : public BSNiNode {
public:
	BSOrderedNode();
	~BSOrderedNode();

	NiBound StaticBound;
	bool bHasStaticBound;

	CREATE_OBJECT(BSOrderedNode, 0xBC2CB0)
};

ASSERT_SIZE(BSOrderedNode, 0xC0);