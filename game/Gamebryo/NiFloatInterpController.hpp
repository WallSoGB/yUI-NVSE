#pragma once

#include "NiSingleInterpController.hpp"

NiSmartPointer(NiFloatInterpController);

class NiFloatInterpController : public NiSingleInterpController {
public:
	NiFloatInterpController();
	virtual ~NiFloatInterpController();
};

ASSERT_SIZE(NiFloatInterpController, 0x38);