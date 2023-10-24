#pragma once
#include "TESObjectREFR.hpp"
#include "BaseProcess.hpp"

// 0x88
class MobileObject : public TESObjectREFR
{
public:
	MobileObject();
	~MobileObject() override;
	virtual void		StartHighProcess(); // 0x90
	virtual void		Unk_91();
	virtual void		Unk_92();
	virtual void		Unk_93();
	virtual void		Move();
	virtual void		Jump();
	virtual void		nullsub_96();
	virtual void		ProcessAI();
	virtual void		Unk_98();
	virtual void		Unk_99();
	virtual void		Unk_9A();
	virtual void		Unk_9B();
	virtual void		Unk_9C();
	virtual void		Unk_9D();
	virtual void		Unk_9E();
	virtual void		Unk_9F();
	virtual void		StartConversation();	// StartConversation(targetActor, subjectLocationData, targetLocationData, headTrack, allowMovement, arg, topicID, arg, arg
	virtual void		DoSpeechLoadLipFiles();
	virtual void		Unk_A2();
	virtual void		Unk_A3();
	virtual void		Unk_A4();
	virtual void		Unk_A5();
	virtual void		Unk_A6();
	virtual void		Unk_A7();
	virtual void		Unk_A8();
	virtual void		Unk_A9();
	virtual void		SetPos();
	virtual void		Unk_AB();
	virtual void		HandleRunDetection();
	virtual void		Unk_AD();
	virtual void		Unk_AE();
	virtual void		GetRotation();
	virtual void		Unk_B0();
	virtual void		SetRotation();
	virtual void		Unk_B2();
	virtual void		Unk_B3();
	virtual void		GetSpeechExpression();
	virtual void		SetExpression();
	virtual void		GetSpeechVolume();
	virtual void		SetEmotionValue();
	virtual void		Unk_B8();
	virtual void		Unk_B9();
	virtual void		IsLifeStateDying();
	virtual void		Unk_BB();
	virtual void		Unk_BC();
	virtual void		Unk_BD();
	virtual void		Update();
	virtual void		Unk_BF();
	virtual void		Unk_C0();

	BaseProcess*	pkBaseProcess;						// 068
	UInt32			unk6C;
	Actor*			conversationActor;					// 070 -
	Float32			nextHeadTrackUpdateTimer;			// 074 - loaded
	Float32			voiceTimer;							// 078 - loaded
	UInt8			unk07C;								// 07C - loaded
	UInt8			unk07D;								// 07D - loaded
	UInt8			unk07E;								// 07E - loaded
	UInt8			unk07F;								// 07F - loaded
	UInt8			unk080;								// 080 -	bool bTalkingThroughActivator;
	UInt8			unk082;								// 082 - cleared when starting combat on player
	UInt8			unk083;								// 083 -	bool bSoundCallBackSet;
	UInt8			unk085;								// 085 - loaded
	UInt8			extraInfoGeneralTopicDataFlags;		// 086 - loaded
	UInt8			unk087;								// 087	Init'd to the inverse of NoLowLevelProcessing

};
static_assert(sizeof(MobileObject) == 0x88);