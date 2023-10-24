#pragma once
#include "Menu.hpp"

// 0FC
class ComputersMenu : public Menu
{
public:
	ComputersMenu();
	~ComputersMenu();

	enum Buttons
	{
		kComputersServer = 0x0,
		kComputersFileFirectoryListbox = 0x1,
		kComputersDisplayZone = 0x2,
		kComputersHeader1 = 0x3,
		kComputersHeader2 = 0x4,
		kComputersResultText = 0x5,
		kComputersCursor = 0x6,
		kComputersWelcome = 0x7,
		kComputersResultPrompt = 0x8,
		kComputersIntroWelcome = 0x9,
		kComputersIntroLogon = 0xA,
		kComputersIntroEnterPW = 0xB,
		kComputersIntroPWDisplay = 0xC,
		kComputersBackground = 0xD,
		kComputersDisplayZoneText = 0xE,
		kComputersSeparator = 0xF,
	};


	Tile*	pkTile_computers_server;
	Tile*	pkTile_computers_file_directory;
	Tile*	pkTile_computers_display_zone;
	Tile*	pkTile_computers_header1;
	Tile*	pkTile_computers_header2;
	Tile*	pkTile_computers_result_text;
	Tile*	pkTile_computers_cursor;
	Tile*	pkTile_computers_welcome;
	Tile*	pkTile_computers_result_prompt;
	Tile*	pkTile_computers_intro_welcome;
	Tile*	pkTile_computers_intro_logon;
	Tile*	pkTile_computers_intro_enterpw;
	Tile*	pkTile_computers_intro_pwdisplay;
	Tile*	pkTile_computers_background;
	Tile*	pkTile_computers_display_zone_text;
	Tile*	pkTile_computers_separator;
	ListBox<MenuEntry> terminalMenuItemsListBox;
	TList<void> subMenuBGSTerminals;
	UInt32 time0A0;
	Tile::Value* isComputersCursorVisible;
	BGSTerminal* targetRefBaseForm;
	TESObjectREFR* targetRef;
	UInt32 stage;
	String noteTextStr;
	const char* remainingNoteText; // pointer into the current note text, moves as you change page 
	UInt8 byte0C0;
	UInt8 isRenderingSubmenu;
	UInt8 gap0C2[2];
	Sound UIHackingFanHumLP;
	Sound UIHackingCharScroll;
	Sound UIHackingCharEnter;
	DList<HackingText>* hackingTexts;
	UInt32 playNoteAudioCallback;
	UInt32 showNoteTextCallback;
	UInt32 showNoteImageCallback;
	UInt32 unk0F8;

	void ShowOrAdvanceNote(BGSNote* note) { ThisCall(0x7590C0, this, note); }
	bool IsInNote() { return remainingNoteText; };

	static ComputersMenu* GetSingleton() { return *reinterpret_cast<ComputersMenu**>(0x11D9334); };
};
static_assert(sizeof(ComputersMenu) == 0xFC);
