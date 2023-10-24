#pragma once
#include "PathingLocation.hpp"

class PathingRequest;
class PathingSolution;
class DetailedActorPathHandler;
class ActorPathingMessageQueue;

// 0x88
class ActorMover
{
public:
	ActorMover();
	
	virtual				~ActorMover();
	virtual void		Unk_01();
	virtual void		ClearMovementFlag();
	virtual void		SetMovementFlags(UInt16 ausMovementFlags);
	virtual void		Unk_04();
	virtual void		Unk_05();
	virtual void		HandleTurnAnimationTimer(Float32 afTimePassed);
	virtual void		Unk_07();
	virtual UInt32		GetMovementFlags();
	virtual void		Unk_09();
	virtual void		Unk_0A();
	virtual void		Unk_0B();
	virtual void		Unk_0C();
	virtual void		Unk_0D();
	virtual void		Unk_0E();

	NiPoint3			pt04;						// 04
	NiPoint3			kOverrideMovement;			// 10
	PathingRequest*		pkPathingRequest;			// 1C
	PathingSolution*	pkPathingSolution;			// 20
	DetailedActorPathHandler* pkPathHandler;		// 24
	Actor*				pkActor;					// 28
	UInt32				uiDoorRefIDForPathing;		// 2C
	ActorPathingMessageQueue* pkPathingMsgQueue;	// 30
	UInt32				uiMovementFlags1;			// 34
	UInt32				unk38;						// 38
	UInt32				uiMovementFlags2;			// 3C
	UInt16				wrd40;						// 40
	UInt16				wrd42;						// 42
	PathingLocation		kPathingLocation;			// 44
	UInt32				unk6C;						// 6C
	UInt8				bPathingFailed;				// 70
	UInt8				byte71;						// 71
	UInt8				byte72;						// 72
	UInt8				byte73;						// 73
	UInt8				bIsWaitingOnPath;			// 74
	UInt8				byte75;						// 75
	UInt8				byte76;						// 76
	UInt8				bIsOverrideMovement;		// 77
	UInt8				byte78;						// 78
	UInt8				gap79[3];					// 79
	UInt32				time7C;						// 7C
	UInt32				time80;						// 80
	UInt32				count84;					// 84
};
static_assert(sizeof(ActorMover) == 0x88);