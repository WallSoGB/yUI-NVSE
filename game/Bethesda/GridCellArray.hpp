#pragma once

#include "NiPoint3.hpp"
#include "GridCell.hpp"
#include "GridArray.hpp"

class BSRenderedTexture;

class GridCellArray : public GridArray {
public:
	SInt32 iDimension;
	GridCell* pGridCellA;
	NiPoint3 WorldCenter;
	bool bLandAttached;
	BSRenderedTexture* shadowMask;

	GridCell* GetCell(SInt32 aX, SInt32 aY);
};