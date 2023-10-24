#pragma once
#include "BSTimer.hpp"

struct TimeGlobal : BSTimer
{
	float unk20;  // 020
	float unk24;  // 024
	float unk28;  // 028

	static TimeGlobal* GetSingleton() { return reinterpret_cast<TimeGlobal*>(0x11F6394); };
	__forceinline void				Set(const Float32 value, const char isImmediateChange) { ThisCall<void>(0xAA4DB0, this, value, isImmediateChange); }
	static __forceinline Float32	Get() { return *reinterpret_cast<Float32*>(0x11AC3A0); }
	static __forceinline Float32	GetTarget() { return *reinterpret_cast<Float32*>(0x11AC3A4); }
};

struct ToBeNamed
{
	char		m_path[0x104];	// 0000
	BSFile* m_file;			// 0104
	UInt32		m_unk0108;		// 0108
	UInt32		m_offset;		// 010C
};