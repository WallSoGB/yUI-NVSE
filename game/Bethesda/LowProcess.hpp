#pragma once

#include "BaseProcess.hpp"
#include "BSSimpleList.hpp"

class LowProcess : public BaseProcess {
public:

	struct FloatPair {
		float	flt000;
		float	flt004;
	};

	struct	ActorValueModifier
	{
		UInt8	actorValue;	// 00 Might allow for other values
		UInt8	pad[3];		// 01
		float	damage;		// 04
	};

	struct ActorValueModifiers
	{
		BSSimpleList<ActorValueModifier*>	avModifierList;	// 00
		UInt8						unk008;			// 08
		UInt8						pad009[3];		// 09
		void*** modifiedAV;	// 0C	array of damaged actorValue
	};	// 10

	LowProcess();
	~LowProcess() override;
	virtual void	Unk_1ED();
	virtual void	Unk_1EE();
	virtual void	Unk_1EF();
	virtual void	Unk_1F0();
	virtual void	Unk_1F1();
	virtual void	Unk_1F2();
	virtual void	Unk_1F3();
	virtual void	Unk_1F4();
	virtual void	Unk_1F5();
	virtual void	Unk_1F6();
	virtual void	Unk_1F7();
	virtual void	Unk_1F8();
	virtual void	Unk_1F9();
	virtual void	Unk_1FA();
	virtual void	Unk_1FB();
	virtual void	Unk_1FC();
	virtual void	Unk_1FD();
	virtual void	Unk_1FE();
	virtual void	Unk_1FF();
	virtual void	Unk_200();
	virtual void	Unk_201();
	virtual void	Unk_202();
	virtual void	Unk_203();
	virtual void	Unk_204();
	virtual void	Unk_205();
	virtual void	Unk_206();

	UInt8				byte30;		// 8 = IsAlerted
	UInt8				pad31[3];
	UInt32				unk34;
	FloatPair			unk38;
	TESForm*			unk40;		// Used when picking idle anims.
	UInt32				unk44;		// not initialized!	refr, expected actor, might be CombatTarget
	UInt32				unk48;
	UInt32				unk4C;
	UInt32				unk50;
	UInt32				unk54;		// not initialized!
	UInt32				unk58;
	BSSimpleList<UInt32> unk5C;		// List
	UInt32				unk64;
	UInt32				unk68;
	BSSimpleList<TESForm*>		unk06C;
	BSSimpleList<UInt32>		unk074;
	BSSimpleList<UInt32>		unk07C;
	UInt32				unk084;
	UInt32				unk088;
	UInt32				unk08C;
	UInt32				unk090;
	ActorValueModifiers	damageModifiers;
	UInt32				unkA4;
	float				gameDayDied;
	float				playerDamageDealt; // not initialized!
	float				unkB0;		// not initialized!
};
static_assert(sizeof(LowProcess) == 0xB4);
// LowProcess has 207 virtual func