#pragma once

#include "NiNode.hpp"

NiRTTIAddress(BSClearZNode, 0x1201F74);

class BSClearZNode : public NiNode {
public:
	bool bChangeFarClip;
	bool bChangeNearClip;
	float fFarClip;
	float fNearClip;

	static BSClearZNode* CreateObject();
};

ASSERT_SIZE(BSClearZNode, 0xB8);