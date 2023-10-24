#pragma once

#include "NiNode.hpp"

NiSmartPointer(NiSwitchNode);

class NiSwitchNode : public NiNode {
public:
	NiSwitchNode();
	~NiSwitchNode();

	enum {
		UPDATE_ONLY_ACTIVE_CHILD_MASK = 0x1,
		UPDATECONTROLLERS_MASK = 0x2,
	};

	UInt16						m_usFlags;
	SInt32						m_iIndex;
	float						m_fSavedTime;
	UInt32						m_uiRevID;
	NiTPrimitiveArray<UInt32>	m_kChildRevID;

	CREATE_OBJECT(NiSwitchNode, 0xA94550)
};;

ASSERT_SIZE(NiSwitchNode, 0xCC)