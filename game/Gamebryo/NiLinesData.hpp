#pragma once

#include "NiGeometryData.hpp"

NiSmartPointer(NiLinesData);

class NiLinesData : public NiGeometryData {
public:
	NiLinesData();
	virtual ~NiLinesData();

	bool* m_pkFlags;

	CREATE_OBJECT(NiLinesData, 0xA8A700)
};

ASSERT_SIZE(NiLinesData, 0x44)