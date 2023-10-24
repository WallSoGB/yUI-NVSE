#pragma once

#include "NiObject.hpp"

NiSmartPointer(NiAdditionalGeometryData);

class BSPackedAdditionalGeometryData;

class NiAdditionalGeometryData : public NiObject {
public:
	enum Types : UInt32 {
		AGD_NITYPE_INVALID = 0x0,
		AGD_NITYPE_FLOAT1 = 0x1,
		AGD_NITYPE_FLOAT2 = 0x2,
		AGD_NITYPE_FLOAT3 = 0x3,
		AGD_NITYPE_FLOAT4 = 0x4,
		AGD_NITYPE_LONG1 = 0x5,
		AGD_NITYPE_LONG2 = 0x6,
		AGD_NITYPE_LONG3 = 0x7,
		AGD_NITYPE_LONG4 = 0x8,
		AGD_NITYPE_ULONG1 = 0x9,
		AGD_NITYPE_ULONG2 = 0xA,
		AGD_NITYPE_ULONG3 = 0xB,
		AGD_NITYPE_ULONG4 = 0xC,
		AGD_NITYPE_SHORT1 = 0xD,
		AGD_NITYPE_SHORT2 = 0xE,
		AGD_NITYPE_SHORT3 = 0xF,
		AGD_NITYPE_SHORT4 = 0x10,
		AGD_NITYPE_USHORT1 = 0x11,
		AGD_NITYPE_USHORT2 = 0x12,
		AGD_NITYPE_USHORT3 = 0x13,
		AGD_NITYPE_USHORT4 = 0x14,
		AGD_NITYPE_BYTE1 = 0x15,
		AGD_NITYPE_BYTE2 = 0x16,
		AGD_NITYPE_BYTE3 = 0x17,
		AGD_NITYPE_BYTE4 = 0x18,
		AGD_NITYPE_UBYTE1 = 0x19,
		AGD_NITYPE_UBYTE2 = 0x1A,
		AGD_NITYPE_UBYTE3 = 0x1B,
		AGD_NITYPE_UBYTE4 = 0x1C,
		AGD_NITYPE_BLEND1 = 0x1D,
		AGD_NITYPE_BLEND2 = 0x1E,
		AGD_NITYPE_BLEND3 = 0x1F,
		AGD_NITYPE_BLEND4 = 0x20,
		AGD_NITYPE_COUNT = 0x21,
		AGD_NITYPE_CUSTOM = 0x22,
	};


	class NiAGDDataStream {
	public:
		UInt8  m_ucflags;
		UInt32 m_uiType;
		UInt32 m_uiUnitSize;
		UInt32 m_uiTotalSize;
		UInt32 m_uiStride;
		UInt32 m_uiBlockIndex;
		UInt32 m_uiBlockOffset;
	};

	class NiAGDDataBlock : public NiMemObject {
	public:
		NiAGDDataBlock();
		virtual ~NiAGDDataBlock();
		virtual void* Allocate(void*);
		virtual void Unk2(UInt8* apucDataBlock, UInt32 auiBlockSize); // Does effectively nothing
		virtual void Unk3(UInt8* apucDataBlock, UInt32 auiBlockSize); // Does effectively nothing
		virtual void Deallocate(void*);

		UInt32 m_uiDataBlockSize;
		UInt8* m_pucDataBlock;
		bool bIsCopied;
		bool bIsSmall; // Set below 64 verts + copied
	};

	NiAdditionalGeometryData();
	virtual ~NiAdditionalGeometryData();

	virtual bool IsBSPackedAdditionalGeometryData();
	virtual NiAGDDataBlock* CreateDataBlock();

	UInt32								m_uiRevID;
	UInt16								m_usVertexCount;
	UInt32								m_uiDataStreamCount;
	NiAGDDataStream*					m_pkDataStreamEntries;
	UInt32								unk18; // Set to 1 by Precipitation
	NiTPrimitiveArray<NiAGDDataBlock*>	m_aDataBlocks;

	CREATE_OBJECT(NiAdditionalGeometryData, 0xA73E20);
	static NiAdditionalGeometryData* Create(UInt16 ausVertCount, UInt32 auiObjectCount);

	bool SetDataBlock(UInt32 uiIndex, UInt8* pucData, UInt32 uiTotalSize, bool bCopyData);
	void SetDataBlockCount(UInt32 auiCount);
	bool SetDataStream(UInt32 uiStreamIndex, UInt32 uiBlockIndex, UInt32 uiBlockOffset, Types uiType, UInt16 usCount, UInt32 uiUnitSize, UInt32 uiStride);
};

ASSERT_SIZE(NiAdditionalGeometryData, 0x2C)