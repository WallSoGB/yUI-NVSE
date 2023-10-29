#pragma once

class Actor;
class TESForm;
class TESModelTextureSwap;
class TESObjectARMO;
class TESObjectWEAP;
class TESRace;
class NiNode;

// 02B4
struct BipedAnim {	// somehow descend from NiNodeArray

	BipedAnim() { ThisStdCall(0x4AACA0, this); };
	~BipedAnim() { ThisStdCall(0x418E00, this); };

	enum OptionalBoneType {
		kOptionalBone_Bip01Head			= 0,
		kOptionalBone_Weapon			= 1,
		kOptionalBone_Bip01LForeTwist	= 2,
		kOptionalBone_Bip01Spine2		= 3,
		kOptionalBone_Bip01Neck1		= 4,
	};

	// 008
	struct OptionalBone
	{
		bool	exists;
		NiNode* bone;
	};

	// 010
	struct VB01Data
	{
		union
		{
			TESForm* item;
			TESObjectARMO* armor;
			TESObjectWEAP* weapon;
			TESRace* race;
		};
		TESModelTextureSwap* modelTexture;
		NiNode* boneNode;
		UInt32 unk00C;
	};

	NiNode* pRoot;
	OptionalBone bones[5];
	VB01Data slotData[20];
	VB01Data unk016C[20];
	UInt32 unk2AC;
	Actor* actor;
};