#pragma once

#include "NiCullingProcess.hpp"

class BSFadeNodeCuller : public NiCullingProcess {
public:
	BSFadeNodeCuller() { ThisStdCall(0x872EA0, this, 0); };
	~BSFadeNodeCuller();
};