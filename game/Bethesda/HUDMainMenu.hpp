#pragma once
#include "Menu.hpp"
#include "BSSimpleArray.hpp"
#include "NiPoint3.hpp"
#include "BSSoundHandle.hpp"
#include "BSTimer.hpp"
#include "HotKeyWheel.hpp"

class TileImage;
class TileText;
class TileRect;
class Tile3D;
class TESObjectREFR;
class NiControllerSequence;
class Actor;

// 278
class HUDMainMenu : public Menu // 1004
{
public:
	HUDMainMenu();
	~HUDMainMenu();

	struct QueuedMessage
	{
		char	msgText[0x204];			// 000
		char	iconPate[MAX_PATH];		// 204
		char	soundPath[MAX_PATH];	// 308
		float	displayTime;			// 40C
	};

	struct QueuedQuestText
	{
		char msg[0x104];
		bool byte104;
		bool byte105;
	};

	struct SubtitleData
	{
		char text[MAX_PATH];
		UInt32 startTime;
		float displayTime;
		NiPoint3 pos;
		UInt32 priority;
	};

	enum EnumVisibilityFlags
	{
		kActionPoints			= 1 << 0,
		kHitPoints				= 1 << 1,
		kRadiationMeter			= 1 << 2,
		kEnemyHealth			= 1 << 3,
		kQuestReminder			= 1 << 4,
		kRegionLocation			= 1 << 5,
		kReticleCenter			= 1 << 6,
		kSneakMeter				= 1 << 7,
		kMessages				= 1 << 8,
		kInfo					= 1 << 9,
		kSubtitles				= 1 << 10,
		kHotkeys				= 1 << 11,
		kXpMeter				= 1 << 12,
		kBreathMeter			= 1 << 13,
		kExplosivePositioning	= 1 << 14,
		kCrippledLimbIndicator	= 1 << 15,
		kHardcoreMode			= 1 << 16,
	};


	enum HUDStates
	{
		kRECALCULATE = 0x1,
		kNormal,
		kPipBoy,
		kPause,
		kLoading,
		kDialog,
		kVATSMenu,
		kVATSPlayback,
		kContainer,
		kBeginSit,
		kSleepWait,
		kPlayerDisabledControls,
		kUnusedD,
		kLevelUpMenu,
		kHacking,
		kComputers,
		kMessage,
		kSpecialBook,
		kLoveTester,
		kVanityCam,
		kUnused15,
		kAiming,
		kAimingScope,
		kIntroMovie,
		kGambling,
	};

	enum MeterAlign
	{
		kHUDHealthAlign_Left = 0x0,
		kHUDHealthAlign_Right = 0x1,
		kHUDHealthAlign_Centered = 0x2,
	};

	UInt32							unk028;
	union
	{
		Tile*	pkTiles[0x56];
		struct
		{
			TileImage*		tileHitPointsMeter;		// 02C	HitPoints\meter
			TileText*		tileHitPointsText;		// 030	HitPoints\justify_right_text
			TileRect*		tileHitPointsCompassIcon1;		// 034	HitPoints\compass_window\compass_icon_group
			TileRect*		tileHitPointsCompassIcon2;		// 038	HitPoints\compass_window\compass_icon_group
			TileRect*		tileHitPointsCompassIcon3;		// 03C	HitPoints\compass_window\compass_icon_group
			TileImage*		tileHitPointsCompass;		// 040	HitPoints\compass_window
			TileImage*		tileActionPointsMeter1;		// 044	ActionPoints\meter
			TileText*		tileActionPointsMeterText1;		// 048	ActionPoints\justify_right_text
			TileText*		tileActionPointsMeterText2;		// 04C	ActionPoints\justify_right_text
			TileImage*		tileActionPointsMeter2;		// 050	ActionPoints\meter
			TileImage*		tileActionPointsMeter3;		// 054	ActionPoints\MeterBackground
			TileText*		tileActionPointsMeterText3;		// 058	ActionPoints\justify_right_text
			TileRect*		tile05C;		// 05C	QuestReminder\QuestStages
			TileRect*		tile060;		// 060	QuestReminder\QuestAdded
			TileText*		tile064;		// 064	Region_Location\justify_left_text
			TileText*		tile068;		// 068	Region_Location\justify_left_text
			TileImage*		tile06C;		// 06C	RadiationMeter\radiation_bracket
			TileImage*		tile070;		// 070	RadiationMeter\radiation_pointer
			TileText*		tile074;		// 074	RadiationMeter\radiation_text_value
			TileText*		tile078;		// 078	RadiationMeter\radiation_text
			TileImage*		tile07C;		// 07C	EnemyHealth\enemy_health_bracket
			TileImage*		tile080;		// 080	EnemyHealth\meter
			TileText*		tile084;		// 084	EnemyHealth\justify_center_text
			TileText*		sneakLabel;	// 088	SneakMeter\sneak_nif
			TileImage*		tile08C;		// 08C	Messages\message_icon
			TileText*		tile090;		// 090	Messages\justify_left_text
			TileImage*		tile094;		// 094	Messages\message_bracket
			TileText*		tile098;		// 098	Subtitles\justify_center_text
			TileRect*		tileTakePrompt;		// 09C	Info\justify_center_hotrect
			TileText*		tile0A0;		// 0A0	Info\justify_center_hotrect\PCShortcutLabel
			TileImage*		tile0A4;		// 0A4	Info\justify_center_hotrect\xbox_button
			TileText*		tile0A8;		// 0A8	Info\justify_center_text
			TileText*		tileLockLevelStr;	// 0AC	Info\justify_center_text
			TileText*		tile0B0;		// 0B0	Info\justify_center_text
			TileText*		tilePickupWeightStr;	// 0B4	Info\justify_right_text
			TileText*		tilePickupWG;			// 0B8	Info\justify_left_text
			TileText*		tilePickupValueStr;	// 0BC	Info\justify_right_text
			TileText*		tilePickupVAL;		// 0C0	Info\justify_left_text
			TileImage*		tile0C4;		// 0C4	Info\info_seperator
			TileRect*		tile0C8;		// 0C8	Hokeys\hotkey_selector
			TileText*		tile0CC;		// 0CC	Hokeys\justify_center_text
			TileImage*		tile0D0;		// 0D0	HitPoints\left_bracket
			TileImage*		tile0D4;		// 0D4	ActionPoints\right_bracket
			TileImage*		tile0D8;		// 0D8	XPMeter\XPBracket
			TileText*		tile0DC;		// 0DC	XPMeter\XPAmount
			TileText*		tile0E0;		// 0E0	XPMeter\XPLabel
			TileImage*		tile0E4;		// 0E4	XPMeter\XPPointer
			TileText*		tile0E8;		// 0E8	XPMeter\XPLastLevel
			TileText*		tile0EC;		// 0EC	XPMeter\XPNextLevel
			TileText*		tile0F0;		// 0F0	XPMeter\XPLevelUp
			TileImage*		tile0F4;		// 0F4	ReticleCenter\reticle_center
			TileImage*		tileCrippledLimbFace;			// 0F8	crippled_limb_indicator\Face
			TileImage*		tileCrippledLimbHead;			// 0FC	crippled_limb_indicator\Head
			TileImage*		tileCrippledLimbTorso;			// 100	crippled_limb_indicator\Torso
			TileImage*		tileCrippledLimbLeftArm;		// 104	crippled_limb_indicator\Left_Arm
			TileImage*		tileCrippledLimbRightArm;		// 108	crippled_limb_indicator\Right_Arm
			TileImage*		tileCrippledLimbLeftLeg;		// 10C	crippled_limb_indicator\Left_Leg
			TileImage*		tileCrippledLimbRightLeg;		// 110	crippled_limb_indicator\Right_Leg
			TileRect*		tileActionPoints;				// 114	ActionPoints
			TileRect*		tileHitPoints;					// 118	HitPoints
			TileRect*		tileRadiationMeter;				// 11C	RadiationMeter
			TileRect*		tileEnemyHealth;				// 120	EnemyHealth
			TileRect*		tileQuestReminder;				// 124	QuestReminder
			TileRect*		tileRegionLocation;				// 128	Region_Location
			TileRect*		tileReticleCenter;				// 12C	ReticleCenter
			TileRect*		tileSneakMeter;					// 130	SneakMeter
			TileRect*		tileMessages;					// 134	Messages
			TileRect*		tileInfo;						// 138	Info
			TileRect*		tileSubtitles;					// 13C	Subtitles
			TileRect*		tileHotkeys;					// 140	Hokeys
			TileRect*		tileXPMeter;					// 144	XPMeter
			TileRect*		tileBreathMeter;				// 148	BreathMeter
			TileRect*		tileExplosivePositioningRect;	// 14C	Explosive_positioning_rect
			TileRect*		tileCrippledLimbIndicator;		// 150	crippled_limb_indicator
			TileImage*		tileDDTIcon;					// 154	DDTIcon
			TileImage*		tileDDTIconEnemy;				// 158	DDTIconEnemy
			TileText*		tileAmmoTypeLabel;				// 15C	AmmoTypeLabel
			TileRect*		tileHardcoreMode;				// 160	HardcoreMode
			TileText*		tileHardcoreModeDehydration;	// 164	HardcoreMode\Dehydration
			TileText*		tileHardcoreModeSleep;			// 168	HardcoreMode\Sleep
			TileText*		tileHardcoreModeHunger;			// 16C	HardcoreMode\Hunger
			TileImage*		tileDDTIconAP;					// 170	DDTIcon
			TileImage*		tileDDTIconEnemyAP;				// 174	DDTIconEnemyAP
			TileText*		tileHardcoreModeRads;			// 178	HardcoreMode\Rads
			TileText*		tileHardcoreModeLMBs;			// 17C	HardcoreMode\LMBs
			TileImage*		tileCNDArrows;					// 180	CNDArrows
		};
	};


	UInt32						unk184;				// 184
	Float32						flt188;				// 188
	BSSimpleList<QueuedMessage*>		queuedMessages;		// 18C
	UInt32						uiCurrMsgStartTime;	// 194
	BSSimpleArray<SubtitleData>	subtitlesArr;		// 198
	SubtitleData* pCurrentSubtitle;	// 1A8
	BSSoundHandle						radiationSound;		// 1AC
	TESObjectREFR* pCrosshairRef;		// 1B8
	UInt32						uiVisibilityFlags;	// 1BC
	UInt32						uiVisibilityOverrides;// 1C0
	UInt32						uiStage;				// 1C4
	HotKeyWheel					hotkeyWheel;		// 1C8	Hokeys\hotkey_selector
	UInt8					bIsForceFirstPerson;			// 1FC
	UInt8					byte1FD;				// 1FD
	UInt8					byte1FE;				// 1FE
	UInt8					byte1FF;				// 1FF
	NiControllerSequence*	pNiContSeq;				// 200
	UInt8					bIsLevelUpQueued;		// 204
	UInt8					bAutoDisplayObjectives;	// 205
	UInt8					pad206[2];				// 206
	UInt32					unk208;					// 208
	UInt32					uiQuestTargets;			// 20C
	UInt32					unk210;					// 210
	UInt32					uiCompassWidth;			// 214
	UInt32					uiMaxCompassAngle;		// 218
	Actor*					pHealthTarget;			// 21C
	UInt32					unk220;					// 220
	BSTimer					timer224;				// 224
	Float32					fEnemyHealthBarTime;	// 244
	Float32					fLastQuestUpdateReminderTime; // 248
	UInt32					timeArmorIcon;			// 24C
	UInt32					timeDTIcon;				// 250
	UInt8					bDoClearQuestUpdates;	// 254
	UInt8					byte255;				// 255
	UInt8					byte256;				// 256
	UInt8					byte257;				// 257
	BSSimpleList<QueuedQuestText*>	queuedQuestTextList;	// 258
	UInt8					bIsQuestAddedTextVisible;//260
	UInt8					bIsQuestStagesTextVisible;//261
	UInt8					pad262[2];				// 262
	BSSimpleList<UInt32>			xpMessages;				// 264
	BSSimpleList<UInt32>			list26C;				// 26C
	Float32					fHUDShake;				// 274

	void RemoveQueuedQuestAndLocationUpdates();
	void RemoveCrippledLimbIndicator();

	__forceinline static HUDMainMenu*	GetSingleton() { return *reinterpret_cast<HUDMainMenu**>(0x11D96C0); }
	__forceinline static void			SetQuestUpdateText(char* src, bool a2, bool a3) { CdeclCall(0x77A5B0, src, a2, a3); }
	__forceinline static Float32		GetOpacity() { return *reinterpret_cast<Float32*>(0x11D979C); };
	static bool	 IsUsingScope() { return GetSingleton() && GetSingleton()->bIsForceFirstPerson; };
};
static_assert(sizeof(HUDMainMenu) == 0x278);