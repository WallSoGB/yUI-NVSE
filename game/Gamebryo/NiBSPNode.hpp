#pragma once

#include "NiNode.hpp"

NiSmartPointer(NiBSPNode);

class NiBSPNode : public NiNode {
public:
	NiBSPNode();
	virtual ~NiBSPNode();

	NiPlane m_kModelPlane;
	NiPlane m_kWorldPlane;

	CREATE_OBJECT(NiBSPNode, 0xA9AEA0);
};

ASSERT_SIZE(NiBSPNode, 0xCC)