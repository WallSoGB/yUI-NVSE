#pragma once

#include "NiInterpController.hpp"
#include "NiInterpolator.hpp"

NiSmartPointer(NiSingleInterpController);

class NiSingleInterpController : public NiInterpController {
public:
	NiSingleInterpController();
	virtual ~NiSingleInterpController();

	NiInterpolatorPtr m_spInterpolator;

	CREATE_OBJECT(NiSingleInterpController, 0xC5C9D0);
};