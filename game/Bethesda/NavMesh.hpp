#pragma once

#include "TESForm.hpp"
#include "TESChildCell.hpp"
#include "NiRefObject.hpp"
#include "BSSimpleArray.hpp"
#include "NiPoint3.hpp"
#include "NiTMap.hpp"

struct NavMeshInfo;
struct ObstacleUndoData;
struct NavMeshTriangleDoorPortal;
struct NavMeshClosedDoorInfo;
struct NavMeshStaticAvoidNode;

struct NavMeshTriangle {
	SInt16 verticesIndex[3];
	SInt16 sides[3];
	UInt32 flags;
};

struct EdgeExtraInfo {
	struct Connection
	{
		NavMeshInfo* navMeshInfo;
		SInt16 triangle;
	};

	UInt32 unk000;
	EdgeExtraInfo::Connection connectTo;
};

NiSmartPointer(NavMesh);

class NavMeshVertex;
class NavMeshPOVData;

// 8C
class ObstacleData : public NiRefObject
{
public:
	UInt32						unk08;			// 08
	NiRefObject*				object0C;		// 0C
	UInt32						unk10[25];		// 10
	UInt8						byte74;			// 74
	UInt8						byte75[3];		// 75
	BSSimpleArray<NavMeshInfo>	navMeshInfos;	// 78
	NiRefObject*				object88;		// 88
};

class NavMesh : public TESForm {
public:
	virtual void		Unk_4E(void);

	TESChildCell								childCell;			// 018
	NiRefObject									refObject;			// 01C
	TESObjectCELL*								parentCell;			// 024
	BSSimpleArray<NavMeshVertex>				vertexArr;			// 028
	BSSimpleArray<NavMeshTriangle>				triangleArr;		// 038
	BSSimpleArray<EdgeExtraInfo>				edgeInfoArr;		// 048
	BSSimpleArray<NavMeshTriangleDoorPortal>	doorPortalArr;		// 058
	BSSimpleArray<NavMeshClosedDoorInfo>		closedDorrArr;		// 068
	BSSimpleArray<UInt16>						unk078Arr;			// 078
	NiTMap<UInt16, NavMeshPOVData*>			povDataMap;			// 088
	BSSimpleArray<UInt16>						unk098Arr;			// 098
	UInt32										unk0A8;				// 0A8
	float										unk0AC[8];			// 0AC
	BSSimpleArray<UInt16>*						arrPtr0CC;			// 0CC
	BSSimpleArray<ObstacleUndoData>				obstacleUndoArr;	// 0D0
	NiTMap<UInt16, ObstacleData*>*			obstacleDataMap;	// 0E0
	BSSimpleArray<UInt16>						unk0E4Arr;			// 0E4
	BSSimpleArray<NavMeshStaticAvoidNode>		avoidNodeArr;		// 0F4
	UInt32*										ptr104;				// 104

	void IncRefCount();
	void DecRefCount();
};
static_assert(sizeof(NavMesh) == 0x108);