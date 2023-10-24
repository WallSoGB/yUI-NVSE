#pragma once

class BSTreeNode : public BSFadeNode {
public:
	BSTreeModel* TreeModel;		// E4
	UInt32				UnkE0;			// E8
	UInt32				UnkE4;			// EC
	UInt32				UnkE8;			// F0
	float				UnkEC;			// F4
};

ASSERT_SIZE(BSTreeNode, 0xF8);