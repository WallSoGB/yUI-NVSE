#pragma once

#include "BSNiNode.hpp"

NiSmartPointer(BSValueNode);

class BSValueNode : public BSNiNode {
public:
	BSValueNode();
	~BSValueNode();

	UInt8 m_ucflags;
	SInt32 iValue;
	NiObjectPtr spReservedObject;

	CREATE_OBJECT(BSValueNode, 0xC43A30);
};

ASSERT_SIZE(BSValueNode, 0xB8)