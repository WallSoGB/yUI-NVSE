#pragma once
#include "TESBoundAnimObject.hpp"
#include "TESModelTextureSwap.hpp"
#include "TESIcon.hpp"
#include "BGSMessageIcon.hpp"
#include "TESScriptableForm.hpp"
#include "TESWeightForm.hpp"
#include "TESValueForm.hpp"
#include "BGSDestructibleObjectForm.hpp"

class TESSound;

// 0xC8
class TESObjectLIGH :
	public TESBoundAnimObject,			// 000
	public TESFullName,					// 030
	public TESModelTextureSwap,			// 03C
	public TESIcon,						// 05C
	public BGSMessageIcon,				// 068
	public TESScriptableForm,			// 078
	public TESWeightForm,				// 084
	public TESValueForm,				// 08C
	public BGSDestructibleObjectForm	// 094
{
public:
	TESObjectLIGH();
	~TESObjectLIGH();

	enum
	{
		kFlag_Dynamic = 1,
		kFlag_CanBeCarried = 2,
		kFlag_Negative = 4,
		kFlag_Flicker = 8,
		kFlag_Unused = 16,
		kFlag_OffByDefault = 32,
		kFlag_FlickerSlow = 64,
		kFlag_Pulse = 128,
		kFlag_PulseSlow = 256,
		kFlag_SpotLight = 512,
		kFlag_SpotShadow = 1024,
	};

	SInt32						time;			// 09C
	UInt32						radius;			// 0A0
	UInt8						red;			// 0A4
	UInt8						green;			// 0A5
	UInt8						blue;			// 0A6
	UInt8						padA7;			// 0A7
	UInt32						lightFlags;		// 0A8
	float						falloffExp;		// 0AC
	float						FOV;			// 0B0
	float						fadeValue;		// 0B4
	TESSound* sound;			// 0B8
	UInt32						padBC[3];		// 0BC

	void SetFlag(UInt32 pFlag, bool bMod)
	{
		lightFlags = bMod ? (lightFlags | pFlag) : (lightFlags & ~pFlag);
	}
};
static_assert(sizeof(TESObjectLIGH) == 0x0C8);