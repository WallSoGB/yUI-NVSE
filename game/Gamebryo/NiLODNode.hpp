#pragma once

#include "NiSwitchNode.hpp"
#include "NiLODData.hpp"

NiSmartPointer(NiLODNode);

class NiLODNode : public NiSwitchNode {
public:
	NiLODNode();
	virtual ~NiLODNode();

	NiLODDataPtr	m_spLODData;
	bool			m_bLODActive;

	CREATE_OBJECT(NiLODNode, 0xA99710)
};

ASSERT_SIZE(NiLODNode, 0xD4)