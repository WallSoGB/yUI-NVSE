#pragma once

#include "NiNode.hpp"
#include "NiPointLight.hpp"
#include "Actor.hpp"

struct MuzzleFlash {
	bool bEnabled;
	bool bMPSEnabled;
	bool bUpdateLight;
	bool gap03;
	float fEnableTimer;
	float fDurationTimer;
	NiNode* node;
	NiPointLight* light;
	BGSProjectile* projectile;
	TESObjectWEAP* sourceWeap;
	Actor* sourceActor;
};