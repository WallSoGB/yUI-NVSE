#pragma once

#include "MobIterOperator.hpp"
#include "BSMultiBound.hpp"
#include "BSFadeNodeCuller.hpp"
#include "BSMultiBoundSphere.hpp"

static void(__stdcall* HighActorCuller_Destroy)() = (void(__stdcall*)())0xFD9380;

class HighActorCuller : public MobIterOperator {
public:
	HighActorCuller();
	~HighActorCuller();

	BSFadeNodeCuller fadeNodeCuller;
	BSMultiBoundNode* spMBNode;
	BSMultiBound* spMultiBound;
	BSMultiBoundSphere* spMBSphere;

	static bool bCreated;

	static HighActorCuller* GetSingleton();

	static void Create();

	static void Run(NiCamera* apCamera);
};