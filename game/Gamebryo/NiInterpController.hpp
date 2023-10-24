#pragma once

#include "NiTimeController.hpp"

NiSmartPointer(NiInterpController);

class NiInterpController : public NiTimeController {
public:
	NiInterpController();
	virtual ~NiInterpController();
};

ASSERT_SIZE(NiInterpController, 0x34)