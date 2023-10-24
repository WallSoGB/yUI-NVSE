#pragma once
#include "BSGameSound.hpp"
#include "NiPoint3.hpp"

// 230
class BSWin32GameSound : public BSGameSound
{
public:
	void* impDirectSound;
	void** SoundBuffer;
	void** SoundBuffer3D_1A0;
	UInt32 unk1A4;
	UInt32 unk1A8;
	UInt32 unk1AC;
	UInt32 unk1B0;
	UInt32*			ptr1B4;					// 1B4	DirectSound func table
	UInt32			unk1B8[5];				// 1B8
	UInt32*			ptr1CC;					// 1CC	DirectSound func table
	void** SoundBuffer3D_1D0;
	UInt32*			ptr1D4;					// 1D4	DirectSound func table
	UInt32 unk1D8;
	UInt32 chunkSizeInBytes_2;
	UInt32 unk1E0;
	UInt32 unk1E4;
	UInt32 unk1E8;
	UInt32 unk1EC;
	UInt32 unk1F0;
	UInt32 unk1F4;
	UInt32 unk1F8;
	UInt32 unk1FC;
	UInt32 unk200;
	UInt32 unk204;
	UInt32* unk208;
	UInt16			word20C;				// 20C
	UInt16			word20E;				// 20E
	UInt16			word210;				// 210
	UInt16			word212;				// 212
	UInt16			word214;				// 214
	UInt16			word216;				// 216
	NiPoint3		originWorldPos;			// 218
	UInt32 unk224;
	void* unk228;
	UInt32 unk22C;
};
static_assert(sizeof(BSWin32GameSound) == 0x230);