#pragma once

#include "NiBinaryStream.hpp"

class NiFile : public NiBinaryStream {
public:
	NiFile();
	virtual ~NiFile();

	virtual void	SeekAlt(SInt32 iOffset, SInt32 iWhence);
	virtual char*	GetFilename();
	virtual UInt32	GetFileSize();

	enum OpenMode {
		READ_ONLY = 0x0,
		WRITE_ONLY = 0x1,
		APPEND_ONLY = 0x2,
	};

	UInt32		m_uiBufferAllocSize;
	UInt32		m_uiBufferReadSize;
	UInt32		m_uiPos;
	UInt32		m_kSystemFile;
	char*		m_pBuffer;
	_iobuf*		m_pFile;
	OpenMode	m_eMode;
	bool		m_bGood;

	UInt32 ReadBuffer(void* pvBuffer, UInt32 uiBytes, UInt32* puiComponentSizes, UInt32 uiNumComponents);
};

ASSERT_SIZE(NiFile, 0x30);