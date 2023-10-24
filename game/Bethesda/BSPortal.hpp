#pragma once

#include "BSOcclusionPlane.hpp"
#include "BSPortalSharedNode.hpp"

class BSMultiBoundRoom;

class BSPortal : public BSOcclusionPlane {
public:
	BSMultiBoundRoom* pMultiBoundRoom[2];
	NiPointer<BSPortalSharedNode> spSharedGeometry;
};

ASSERT_SIZE(BSPortal, 0x108)