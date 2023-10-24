#pragma once

struct BSHash {
	UInt8 cLast;
	UInt8 cLast2;
	UInt8 cLength;
	UInt8 cFirst;
	UInt32 iCRC;

	static void MakeDirAndFile(const char* apString, BSHash& arDirHash, BSHash& arFileHash);
};

ASSERT_SIZE(BSHash, 0x8);