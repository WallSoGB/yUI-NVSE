#include "CommandTable.h"
#include "Safewrite.hpp"
#include "GameAPI.h"
#include "GameData.h"
#include "Objects.h"
#include "GameEffects.h"
#include "GameExtraData.h"
#include "GameForms.h"
#include "GameProcess.h"
#include "GameRTTI.h"
#include "GameSettings.h"
#include "GameUI.h"
#include <string>
#include "Utilities.hpp"
#include "PluginManager.h"
#include "NiNodes.h"
#include <stdexcept>

#include "Commands_Console.h"
#include "Commands_Game.h"
#include "Commands_Input.h"
#include "Commands_Inventory.h"
#include "Commands_List.h"
#include "Commands_Math.h"
#include "Commands_MiscRef.h"
#include "Commands_Misc.h"
#include "Commands_Packages.h"
#include "Commands_Script.h"
#include "Commands_Scripting.h"
#include "Commands_UI.h"
#include "Commands_InventoryRef.h"
#include "Commands_Factions.h"
#include "Commands_Array.h"
#include "Commands_String.h"
#include "Commands_Algohol.h"
#include "Commands_Animation.h"

CommandTable g_consoleCommands;
CommandTable g_scriptCommands;

#if RUNTIME

// 1.4.0.525 runtime
UInt32 g_offsetConsoleCommandsStart = 0x0118E8E0;
UInt32 g_offsetConsoleCommandsLast = 0x011908C0;
UInt32 g_offsetScriptCommandsStart = 0x01190910;
UInt32 g_offsetScriptCommandsLast = 0x01196D10;
static const Cmd_Parse g_defaultParseCommand = (Cmd_Parse)0x005B1BA0;

#else

// 1.4.0.518 editor
UInt32 g_offsetConsoleCommandsStart = 0x00E9DB88;
UInt32 g_offsetConsoleCommandsLast = 0x00E9FB90;
UInt32 g_offsetScriptCommandsStart = 0x00E9FBB8;
UInt32 g_offsetScriptCommandsLast = 0x00EA5FB8;
static const Cmd_Parse g_defaultParseCommand = (Cmd_Parse)0x005C67E0;

#endif

struct PatchLocation
{
	UInt32	ptr;
	UInt32	offset;
	UInt32	type;
};

#if RUNTIME

static const PatchLocation kPatch_ScriptCommands_Start[] =
{
	{	0x005B1172, 0x00 },
	{	0x005B19B1, 0x00 },
	{	0x005B19CE, 0x04 },
	{	0x005B19F8, 0x08 },
	{	0x005BCC0A, 0x0C },
	{	0x005BCC2D, 0x00 },
	{	0x005BCC50, 0x04 },
	{	0x005BCC70, 0x0C },
	{	0x005BCC86, 0x0C },
	{	0x005BCCA6, 0x04 },
	{	0x005BCCB8, 0x04 },
	{	0x005BCCD4, 0x0C },
	{	0x005BCCE4, 0x04 },
	{	0x005BCCF4, 0x00 },
	{	0x005BCD13, 0x0C },
	{	0x005BCD23, 0x00 },
	{	0x005BCD42, 0x04 },
	{	0x005BCD54, 0x04 },
	{	0x005BCD70, 0x04 },
	{	0x005BCD80, 0x00 },
	{	0x005BCD9F, 0x00 },
	{	0x0068170B, 0x20 },
	{	0x00681722, 0x10 },
	{	0x00681752, 0x20 },
	{	0x00681AEB, 0x20 },
	{	0x00681CDE, 0x00 },
	{	0x006820FF, 0x14 },
	{	0x0068228D, 0x12 },
	{	0x006822FF, 0x14 },
	{	0x00682352, 0x14 },
	{	0x006823B2, 0x14 },
	{	0x0087A909, 0x12 },
	{	0x0087A948, 0x14 },
	{	0 },
};

static const PatchLocation kPatch_ScriptCommands_End[] =
{
	{	0x005AEA59, 0x08 },
	{	0 },
};

// 127B / 027B
// 1280 / 0280
static const PatchLocation kPatch_ScriptCommands_MaxIdx[] =
{
	{	0x00593909 + 1, 0 },
	{	0x005AEA57 + 6, 0 },
	{	0x005B115B + 3, 0 },
	{	0x005B19A0 + 3, (UInt32)(-0x1000) },
	{	0x005BCBDD + 6, (UInt32)(-0x1000) },
	{	0 },
};

void ApplyPatchEditorOpCodeDataList(void) {
}

#else

static const PatchLocation kPatch_ScriptCommands_Start[] =
{
	{	0x004072AF, 0x00 },
	{	0x004073FA, 0x00 },
	{	0x004A2374, 0x24 },
	{	0x004A23E8, 0x24 },
	{	0x004A2B9B, 0x00 },
	{	0x004A3CE2, 0x20 },
	{	0x004A3CF2, 0x10 },
	{	0x004A431A, 0x00 },
	{	0x004A474A, 0x20 },
	{	0x004A485F, 0x00 },
	{	0x004A4ED1, 0x00 },
	{	0x004A5134, 0x00 },
	{	0x004A58B4, 0x12 },
	{	0x004A58F5, 0x12 },
	{	0x004A5901, 0x14 },
	{	0x004A593E, 0x12 },
	{	0x004A5949, 0x14 },
	{	0x004A5A26, 0x12 },
	{	0x004A5A6D, 0x12 },
	{	0x004A5A79, 0x14 },
	{	0x004A5AD6, 0x12 },
	{	0x004A5B1D, 0x12 },
	{	0x004A5B29, 0x14 },
	{	0x004A5B7C, 0x12 },
	{	0x004A5BD9, 0x12 },
	{	0x004A5C28, 0x12 },
	{	0x004A5C34, 0x14 },
	{	0x004A600C, 0x14 },
	{	0x004A6704, 0x12 },
	{	0x004A6749, 0x12 },
	{	0x004A6755, 0x14 },
	{	0x004A684C, 0x12 },
	{	0x004A6A8F, 0x12 },
	{	0x004A6A9F, 0x14 },
	{	0x004A6BDF, 0x12 },
	{	0x004A6D30, 0x14 },
	{	0x004A6D74, 0x14 },
	{	0x004A703B, 0x12 },
	{	0x004A716D, 0x12 },
	{	0x004A71B5, 0x14 },
	{	0x004A7268, 0x14 },
	{	0x004A735A, 0x12 },
	{	0x004A7536, 0x14 },
	{	0x0059C532, 0x20 },
	{	0x0059C53B, 0x24 },
	{	0x0059C6BA, 0x24 },
	{	0x005C53F4, 0x04 },
	{	0x005C548D, 0x08 },
	{	0x005C6636, 0x00 },
	{	0x005C9499, 0x00 },
	{	0 },
};

static const PatchLocation kPatch_ScriptCommands_End[] =
{
	{	0x004A433B, 0x00 },
	{	0x0059C710, 0x24 },
	{	0x005C5372, 0x08 },
	{	0x005C541F, 0x04 },
	{	0 },
};

// 280 / 1280 / 27F
static const PatchLocation kPatch_ScriptCommands_MaxIdx[] =
{
	{	0x004A2B87 + 2,	(UInt32)(-0x1000) },
	{	0x0059C576 + 2,	(UInt32)(-0x1000) },
	{	0x005B1817 + 1,	0 },
	{	0x005C5370 + 6,	0 },

	{	0x004A439D + 2, (UInt32)(-0x1000) - 1 },
	{	0x004A43AD + 1, (UInt32)(-0x1000) - 1 },
	{	0x004A43B9 + 2, (UInt32)(-0x1000) - 1 },

	{	0x005C6625 + 1,	(UInt32)(-0x1000) - 1 },
	{	0x005C948B + 2,	(UInt32)(-0x1000) - 1 },

	{	0 },
};

#define OpCodeDataListAddress	0x004A4390	// The function containing the fith element of array kPatch_ScriptCommands_MaxIdx
#define hookOpCodeDataListAddress		0x004A5562	// call hookOpCodeDataList. This is the second reference to the function.

static void* OpCodeDataListFunc = (void*)OpCodeDataListAddress;

int __fastcall hookOpCodeDataList(UInt32 ECX, UInt32 EDX, UInt32 opCode) {  // Replacement for the vanilla version that truncate opCode by 1000
	_asm {
		mov eax, opCode
		add eax, 0x01000
		push eax
		call OpCodeDataListFunc	//	baseOpCodeDataList	// ecx and edx are still in place
	}
}

void ApplyPatchEditorOpCodeDataList(void) {
	SInt32 RelativeAddress = (UInt32)(&hookOpCodeDataList) - hookOpCodeDataListAddress - 5 /* EIP after instruction that we modify*/;
	SafeWrite32(hookOpCodeDataListAddress+1, (UInt32)RelativeAddress);
}

#endif

static void ApplyPatch(const PatchLocation * patch, UInt32 newData)
{
	for(; patch->ptr; ++patch)
	{
		switch(patch->type)
		{
		case 0:
			SafeWrite32(patch->ptr, newData + patch->offset);
			break;

		case 1:
			SafeWrite16(patch->ptr, newData + patch->offset);
			break;
		}
	}
}

bool Cmd_Default_Parse(UInt32 numParams, ParamInfo * paramInfo, ScriptLineBuffer * lineBuf, ScriptBuffer * scriptBuf)
{
	return g_defaultParseCommand(numParams, paramInfo, lineBuf, scriptBuf);
}

#if RUNTIME

bool Cmd_GetNVSEVersion_Eval(COMMAND_ARGS_EVAL)
{
	*result = NVSE_VERSION_INTEGER;
	if (IsConsoleMode()) {
		Console_Print("NVSE version: %d", NVSE_VERSION_INTEGER);
	}
	return true;
}

bool Cmd_GetNVSEVersion_Execute(COMMAND_ARGS)
{
	return Cmd_GetNVSEVersion_Eval(thisObj, 0, 0, result);
}

bool Cmd_GetNVSERevision_Eval(COMMAND_ARGS_EVAL)
{
	*result = NVSE_VERSION_INTEGER_MINOR;
	if (IsConsoleMode()) {
		Console_Print("NVSE revision: %d", NVSE_VERSION_INTEGER_MINOR);
	}
	return true;
}

bool Cmd_GetNVSERevision_Execute(COMMAND_ARGS)
{
	return Cmd_GetNVSERevision_Eval(thisObj, 0, 0, result);
}

bool Cmd_GetNVSEBeta_Eval(COMMAND_ARGS_EVAL)
{
	*result = NVSE_VERSION_INTEGER_BETA;
	if (IsConsoleMode()) {
		Console_Print("NVSE beta: %d", NVSE_VERSION_INTEGER_BETA);
	}
	return true;
}

bool Cmd_GetNVSEBeta_Execute(COMMAND_ARGS)
{
	return Cmd_GetNVSEBeta_Eval(thisObj, 0, 0, result);
}

bool Cmd_DumpDocs_Execute(COMMAND_ARGS)
{
	if (IsConsoleMode()) {
		Console_Print("Dumping Command Docs");
	}
	g_scriptCommands.DumpCommandDocumentation();
	if (IsConsoleMode()) {
		Console_Print("Done Dumping Command Docs");
	}
	return true;
}

class Dumper {
	UInt32 m_sizeToDump;
public:
	Dumper(UInt32 sizeToDump = 512) : m_sizeToDump(sizeToDump) {}
	bool Accept(void *addr) {
		if (addr) {
			DumpClass(addr, m_sizeToDump);
		}
		return true;
	}
};

#endif

static ParamInfo kTestArgCommand_Params[] =
{
	{	"int", kParamType_Integer, 0 },
};

static ParamInfo kTestDumpCommand_Params[] = 
{
	{	"form", kParamType_ObjectID, 1},
};

DEFINE_CMD_COND(GetNVSEVersion, returns the installed version of NVSE, 0, NULL);
DEFINE_CMD_COND(GetNVSERevision, returns the numbered revision of the installed version of NVSE, 0, NULL);
DEFINE_CMD_COND(GetNVSEBeta, returns the numbered beta of the installed version of NVSE, 0, NULL);
DEFINE_COMMAND(DumpDocs, , 0, 0, NULL);

#define ADD_CMD(command) Add(&kCommandInfo_ ## command )
#define ADD_CMD_RET(command, rtnType) Add(&kCommandInfo_ ## command, rtnType )
#define REPL_CMD(command) Replace(GetByName(command)->opcode, &kCommandInfo_ ## command )

CommandTable::CommandTable() { }
CommandTable::~CommandTable() { }

void CommandTable::Init(void)
{
	static CommandInfo* kCmdInfo_Unused_1;
#if RUNTIME
	kCmdInfo_Unused_1 = (CommandInfo*)0x0118E4F8;
#else
	kCmdInfo_Unused_1 = (CommandInfo*)0x00E9D7A0;
#endif

	// read in the console commands
	g_consoleCommands.SetBaseID(0x0100);
	g_consoleCommands.Read((CommandInfo *)g_offsetConsoleCommandsStart, (CommandInfo *)g_offsetConsoleCommandsLast);

	// read in the script commands
	g_scriptCommands.SetBaseID(0x1000);
	g_scriptCommands.Read((CommandInfo *)g_offsetScriptCommandsStart, (CommandInfo *)g_offsetScriptCommandsLast);

	// blocktype "Unused_1" becomes "Function"
	UInt16 onUnused_1Opcode = kCmdInfo_Unused_1->opcode;
	*kCmdInfo_Unused_1 = kCommandInfo_Function;
	kCmdInfo_Unused_1->opcode = onUnused_1Opcode;

	// pad to opcode 0x1400 to give Bethesda lots of room
	g_scriptCommands.PadTo(kNVSEOpcodeStart);

	// Add NVSE Commands
	g_scriptCommands.AddCommandsV1();
	g_scriptCommands.AddCommandsV3s();
	g_scriptCommands.AddCommandsV4();
	g_scriptCommands.AddCommandsV5();

#if _DEBUG
	g_scriptCommands.AddDebugCommands();
#endif

	// register plugins
	g_pluginManager.Init();

	// patch the code
	ApplyPatch(kPatch_ScriptCommands_Start, (UInt32)g_scriptCommands.GetStart());
	ApplyPatch(kPatch_ScriptCommands_End, (UInt32)g_scriptCommands.GetEnd());
	ApplyPatch(kPatch_ScriptCommands_MaxIdx, g_scriptCommands.GetMaxID());

	ApplyPatchEditorOpCodeDataList();

	_MESSAGE("max id = %08X", g_scriptCommands.GetMaxID());

	_MESSAGE("console commands");
	g_consoleCommands.Dump();
	_MESSAGE("script commands");
	g_scriptCommands.Dump();

	_MESSAGE("patched");
}

void CommandTable::Read(CommandInfo * start, CommandInfo * end)
{
	UInt32	numCommands = end - start;
	m_commands.reserve(m_commands.size() + numCommands);

	for(; start != end; ++start)
		Add(start);
}

void CommandTable::Add(CommandInfo * info, CommandReturnType retnType, UInt32 parentPluginOpcodeBase)
{
	UInt32	backCommandID = m_baseID + m_commands.size();	// opcode of the next command to add

	info->opcode = m_curID;

	if(m_curID == backCommandID)
	{
		// adding at the end?
		m_commands.push_back(*info);
	}
	else if(m_curID < backCommandID)
	{
		// adding to existing data?
		ASSERT(m_curID >= m_baseID);

		m_commands[m_curID - m_baseID] = *info;
	}
	else
	{
		HALT("CommandTable::Add: adding past the end");
	}

	m_curID++;

	CommandMetadata * metadata = &m_metadata[info->opcode];

	metadata->parentPlugin = parentPluginOpcodeBase;
	metadata->returnType = retnType;
}

bool CommandTable::Replace(UInt32 opcodeToReplace, CommandInfo* replaceWith)
{
	for (CommandList::iterator iter = m_commands.begin(); iter != m_commands.end(); ++iter)
	{
		if (iter->opcode == opcodeToReplace)
		{
			*iter = *replaceWith;
			iter->opcode = opcodeToReplace;
			return true;
		}
	}

	return false;
}

static CommandInfo kPaddingCommand =
{
	"", "",
	0,
	"command used for padding",
	0,
	0,
	NULL,

	Cmd_Default_Execute,
	Cmd_Default_Parse,
	NULL,
	NULL
};

void CommandTable::PadTo(UInt32 id, CommandInfo * info)
{
	if(!info) info = &kPaddingCommand;

	while(m_baseID + m_commands.size() < id)
	{
		info->opcode = m_baseID + m_commands.size();
		m_commands.push_back(*info);
	}

	m_curID = id;
}

void CommandTable::Dump(void)
{
	for(CommandList::iterator iter = m_commands.begin(); iter != m_commands.end(); ++iter)
	{
		_DMESSAGE("%08X %04X %s %s", iter->opcode, iter->needsParent, iter->longName, iter->shortName);
	}
}


void CommandTable::DumpAlternateCommandNames(void)
{
	for (CommandList::iterator iter= m_commands.begin(); iter != m_commands.end(); ++iter)
	{
		if (iter->shortName)
			_MESSAGE("%s", iter->shortName);
	}
}

const char* SimpleStringForParamType(UInt32 paramType)
{
	switch(paramType) {
		case kParamType_String: return "string";
		case kParamType_Integer: return "integer";
		case kParamType_Float: return "float";
		case kParamType_ObjectID: return "ref";
		case kParamType_ObjectRef: return "ref";
		case kParamType_ActorValue: return "actorValue";
		case kParamType_Actor: return "ref";
		case kParamType_SpellItem: return "ref";
		case kParamType_Axis: return "axis";
		case kParamType_Cell: return "ref";
		case kParamType_AnimationGroup: return "animGroup";
		case kParamType_MagicItem: return "ref";
		case kParamType_Sound: return "ref";
		case kParamType_Topic: return "ref";
		case kParamType_Quest: return "ref";
		case kParamType_Race: return "ref";
		case kParamType_Class: return "ref";
		case kParamType_Faction: return "ref";
		case kParamType_Sex: return "sex";
		case kParamType_Global: return "global";
		case kParamType_Furniture: return "ref";
		case kParamType_TESObject: return "ref";
		case kParamType_VariableName: return "string";
		case kParamType_QuestStage: return "short";
		case kParamType_MapMarker: return "ref";
		case kParamType_ActorBase: return "ref";
		case kParamType_Container: return "ref";
		case kParamType_WorldSpace: return "ref";
		case kParamType_CrimeType: return "crimeType";
		case kParamType_AIPackage: return "ref";
		case kParamType_CombatStyle: return "ref";
		case kParamType_MagicEffect: return "ref";
		case kParamType_FormType: return "formType";
		case kParamType_WeatherID: return "ref";
		case kParamType_NPC: return "ref";
		case kParamType_Owner: return "ref";
		case kParamType_EffectShader: return "ref";
		case kParamType_FormList:			return "ref";
		case kParamType_MenuIcon:			return "ref";
		case kParamType_Perk:				return "ref";
		case kParamType_Note:				return "ref";
		case kParamType_MiscellaneousStat:	return "ref";
		case kParamType_ImageSpaceModifier:	return "ref";
		case kParamType_ImageSpace:			return "ref";
		case kParamType_EncounterZone:		return "ref";
		case kParamType_Message:			return "ref";
		case kParamType_InvObjOrFormList:	return "ref";
		case kParamType_Alignment:			return "ref";
		case kParamType_EquipType:			return "ref";
		case kParamType_NonFormList:		return "ref";
		case kParamType_SoundFile:			return "ref";
		case kParamType_CriticalStage:		return "ref";
		case kParamType_LeveledOrBaseChar:	return "ref";
		case kParamType_LeveledOrBaseCreature:	return "ref";
		case kParamType_LeveledChar:		return "ref";
		case kParamType_LeveledCreature:	return "ref";
		case kParamType_LeveledItem:		return "ref";
		case kParamType_AnyForm:			return "ref";
		case kParamType_Reputation:			return "ref";
		case kParamType_Casino:				return "ref";
		case kParamType_CasinoChip:			return "ref";
		case kParamType_Challenge:			return "ref";
		case kParamType_CaravanMoney:		return "ref";
		case kParamType_CaravanCard:		return "ref";
		case kParamType_CaravanDeck:		return "ref";
		case kParamType_Region:				return "ref";

		// custom NVSE types
		// kParamType_StringVar is same as Integer
		case kParamType_Array:				return "array_var";

		default: return "<unknown>";
	}
}

const char* StringForParamType(UInt32 paramType)
{
	switch(paramType) {
		case kParamType_String:				return "String";
		case kParamType_Integer:			return "Integer";
		case kParamType_Float:				return "Float";
		case kParamType_ObjectID:			return "ObjectID";
		case kParamType_ObjectRef:			return "ObjectRef";
		case kParamType_ActorValue:			return "ActorValue";
		case kParamType_Actor:				return "Actor";
		case kParamType_SpellItem:			return "SpellItem";
		case kParamType_Axis:				return "Axis";
		case kParamType_Cell:				return "Cell";
		case kParamType_AnimationGroup:		return "AnimationGroup";
		case kParamType_MagicItem:			return "MagicItem";
		case kParamType_Sound:				return "Sound";
		case kParamType_Topic:				return "Topic";
		case kParamType_Quest:				return "Quest";
		case kParamType_Race:				return "Race";
		case kParamType_Class:				return "Class";
		case kParamType_Faction:			return "Faction";
		case kParamType_Sex:				return "Sex";
		case kParamType_Global:				return "Global";
		case kParamType_Furniture:			return "Furniture";
		case kParamType_TESObject:			return "Object";
		case kParamType_VariableName:		return "VariableName";
		case kParamType_QuestStage:			return "QuestStage";
		case kParamType_MapMarker:			return "MapMarker";
		case kParamType_ActorBase:			return "ActorBase";
		case kParamType_Container:			return "Container";
		case kParamType_WorldSpace:			return "WorldSpace";
		case kParamType_CrimeType:			return "CrimeType";
		case kParamType_AIPackage:			return "AIPackage";
		case kParamType_CombatStyle:		return "CombatStyle";
		case kParamType_MagicEffect:		return "MagicEffect";
		case kParamType_FormType:			return "FormType";
		case kParamType_WeatherID:			return "WeatherID";
		case kParamType_NPC:				return "NPC";
		case kParamType_Owner:				return "Owner";
		case kParamType_EffectShader:		return "EffectShader";
		case kParamType_FormList:			return "FormList";
		case kParamType_MenuIcon:			return "MenuIcon";
		case kParamType_Perk:				return "Perk";
		case kParamType_Note:				return "Note";
		case kParamType_MiscellaneousStat:	return "MiscStat";
		case kParamType_ImageSpaceModifier:	return "ImageSpaceModifier";
		case kParamType_ImageSpace:			return "ImageSpace";
		case kParamType_Double:				return "Double";
		case kParamType_Unhandled2D:		return "unk2D";
		case kParamType_Unhandled2E:		return "unk2E";
		case kParamType_EncounterZone:		return "EncounterZone";
		case kParamType_Unhandled30:		return "unk30";
		case kParamType_Message:			return "Message";
		case kParamType_InvObjOrFormList:	return "InvObjectOrFormList";
		case kParamType_Alignment:			return "Alignment";
		case kParamType_EquipType:			return "EquipType";
		case kParamType_NonFormList:		return "NonFormList";
		case kParamType_SoundFile:			return "SoundFile";
		case kParamType_CriticalStage:		return "CriticalStage";
		case kParamType_LeveledOrBaseChar:	return "LeveledOrBaseChar";
		case kParamType_LeveledOrBaseCreature:	return "LeveledOrBaseCreature";
		case kParamType_LeveledChar:		return "LeveledChar";
		case kParamType_LeveledCreature:	return "LeveledCreature";
		case kParamType_LeveledItem:		return "LeveledItem";
		case kParamType_AnyForm:			return "AnyForm";
		case kParamType_Reputation:			return "Reputation";
		case kParamType_Casino:				return "Casino";
		case kParamType_CasinoChip:			return "CasinoChip";
		case kParamType_Challenge:			return "Challenge";
		case kParamType_CaravanMoney:		return "CaravanMoney";
		case kParamType_CaravanCard:		return "CaravanCard";
		case kParamType_CaravanDeck:		return "CaravanDeck";
		case kParamType_Region:				return "Region";

		// custom NVSE types
		// kParamType_StringVar is same as Integer
		case kParamType_Array:				return "ArrayVar";

		default: return "<unknown>";
	}
}

void CommandTable::DumpCommandDocumentation(UInt32 startWithID)
{
	_MESSAGE("NVSE Commands from: %#x", startWithID);

	_MESSAGE("<br><b>Function Quick Reference</b>");
	CommandList::iterator itEnd = m_commands.end();
	for (CommandList::iterator iter = m_commands.begin();iter != itEnd; ++iter) {
		if (iter->opcode >= startWithID) {
			iter->DumpFunctionDef();
		}
	}

	_MESSAGE("<hr><br><b>Functions In Detail</b>");
	for (CommandList::iterator iter = m_commands.begin();iter != itEnd; ++iter) {
		if (iter->opcode >= startWithID) {
			iter->DumpDocs();
		}
	}
}

void CommandInfo::DumpDocs() const
{
	_MESSAGE("<p><a name=\"%s\"></a><b>%s</b> ", longName, longName);
	_MESSAGE("<br><b>Alias:</b> %s<br><b>Parameters:</b>%d", (strlen(shortName) != 0) ? shortName : "none", numParams);
	if (numParams > 0) {
		for(UInt32 i = 0; i < numParams; i++)
		{
			ParamInfo	* param = &params[i];
			const char* paramTypeName = StringForParamType(param->typeID);
			if (param->isOptional != 0) {
				_MESSAGE("<br>&nbsp;&nbsp;&nbsp;<i>%s:%s</i> ", param->typeStr, paramTypeName);
			} else {
				_MESSAGE("<br>&nbsp;&nbsp;&nbsp;%s:%s ", param->typeStr, paramTypeName);
			}
		}
	}
	_MESSAGE("<br><b>Return Type:</b> FixMe<br><b>Opcode:</b> %#4x (%d)<br><b>Condition Function:</b> %s<br><b>Description:</b> %s</p>", opcode, opcode, eval ? "Yes" : "No",helpText);
}

void CommandInfo::DumpFunctionDef() const
{
	_MESSAGE("<br>(FixMe) %s<a href=\"#%s\">%s</a> ", needsParent > 0 ? "reference." : "", longName, longName);
	if (numParams > 0) {
		for(UInt32 i = 0; i < numParams; i++)
		{
			ParamInfo	* param = &params[i];
			const char* paramTypeName = StringForParamType(param->typeID);
			if (param->isOptional != 0) {
				_MESSAGE("<i>%s:%s</i> ", param->typeStr, paramTypeName);
			} else {
				_MESSAGE("%s:%s ", param->typeStr, paramTypeName);
			}
		}
	}
}


CommandInfo * CommandTable::GetByName(const char * name)
{
	for (CommandList::iterator iter = m_commands.begin(); iter != m_commands.end(); ++iter)
		if (!StrCompare(name, iter->longName) || (iter->shortName && !StrCompare(name, iter->shortName)))
			return &(*iter);

	return NULL;
}


CommandInfo* CommandTable::GetByOpcode(UInt32 opcode)
{
	const auto baseOpcode = m_commands.begin()->opcode;
	const auto arrayIndex = opcode - baseOpcode;
	if (arrayIndex >= m_commands.size())
	{
		return nullptr;
	}
	auto* const command = &m_commands[arrayIndex];
	if (command->opcode != opcode)
	{
		//_MESSAGE("ERROR: mismatched command opcodes when executing CommandTable::GetByOpcode (opcode: %X base: %X index: %d index opcode: %X)",
		//	opcode, baseOpcode, arrayIndex, command->opcode);
		return nullptr;
	}
	return command;

}

CommandReturnType CommandTable::GetReturnType(const CommandInfo* cmd)
{
	return m_metadata[cmd->opcode].returnType;
}

void CommandTable::SetReturnType(UInt32 opcode, CommandReturnType retnType)
{
	CommandInfo* cmdInfo = GetByOpcode(opcode);
	if (!cmdInfo)
		_MESSAGE("CommandTable::SetReturnType() - cannot locate command with opcode %04X", opcode);
	else {
		m_metadata[opcode].returnType = retnType;
	}
}

void CommandTable::RecordReleaseVersion(void)
{
	m_opcodesByRelease.push_back(GetCurID());
}

UInt32 CommandTable::GetRequiredNVSEVersion(const CommandInfo* cmd)
{
	UInt32  ver = 0;
	if (cmd) {
		if (cmd->opcode < m_opcodesByRelease[0])	// vanilla cmd
			ver = 0;
		else if (cmd->opcode >= kNVSEOpcodeTest)	// plugin cmd, we have no way of knowing
			ver = -1;
		else {
			for (UInt32 i = 0; i < m_opcodesByRelease.size(); i++) {
				if (cmd->opcode >= m_opcodesByRelease[i]) {
					ver = i;
				}
				else {
					break;
				}
			}
		}
	}

	return ver;
}

void CommandTable::RemoveDisabledPlugins(void)
{
	for (CommandList::iterator iter = m_commands.begin(); iter != m_commands.end(); ++iter)
	{
		// plugin failed to load but still registered some commands?
		// realistically the game is going to go down hard if this happens anyway
		if(g_pluginManager.LookupHandleFromBaseOpcode(m_metadata[iter->opcode].parentPlugin) == kPluginHandle_Invalid)
			Replace(iter->opcode, &kPaddingCommand);
	}
}

static char * kNVSEname = "NVSE";

static PluginInfo g_NVSEPluginInfo =
{
	PluginInfo::kInfoVersion,
	kNVSEname,
	NVSE_VERSION_INTEGER,
};

PluginInfo * CommandTable::GetParentPlugin(const CommandInfo * cmd)
{
	if (!cmd->opcode || cmd->opcode<kNVSEOpcodeStart)
		return NULL;

	if (cmd->opcode < kNVSEOpcodeTest)
		return &g_NVSEPluginInfo;

	PluginInfo *info = g_pluginManager.GetInfoFromBase(m_metadata[cmd->opcode].parentPlugin);
	if (info)
		return info;

	return NULL;
}

void ImportConsoleCommand(const char * name)
{
	CommandInfo	* info = g_consoleCommands.GetByName(name);
	if(info)
	{
		CommandInfo	infoCopy = *info;

		std::string	newName;

		newName = std::string("con_") + name;

		infoCopy.shortName = "";
		infoCopy.longName = _strdup(newName.c_str());

		g_scriptCommands.Add(&infoCopy);

//		_MESSAGE("imported console command %s", name);
	}
	else
	{
		_WARNING("couldn't find console command (%s)", name);

		// pad it
		g_scriptCommands.Add(&kPaddingCommand);
	}
}

bool Cmd_tcmd_Execute(COMMAND_ARGS)
{
	auto* player = LookupFormByID(0x14);
	auto* playerRef = DYNAMIC_CAST(player, TESForm, TESObjectREFR);
	auto* list = GameFuncs::GetAnims(playerRef, 0xC);
	for (auto iter = list->Begin(); !iter.End(); ++iter)
	{
		_MESSAGE("ANIM %s", iter.Get());
	}
	return true;
}

bool Cmd_tcmd2_Execute(COMMAND_ARGS)
{
	return true;
}

bool Cmd_tcmd3_Execute(COMMAND_ARGS)
{
	return true;
}

DEFINE_COMMAND(tcmd, test, 0, 0, NULL);
DEFINE_CMD_ALT(tcmd2, testargcmd ,test, 0, 1, kTestArgCommand_Params);
DEFINE_CMD_ALT(tcmd3, testdump, dump info, 0, 1, kTestDumpCommand_Params);


// internal commands added at the end
void CommandTable::AddDebugCommands()
{
	ADD_CMD_RET(CloneForm, kRetnType_Form);
	ADD_CMD_RET(PlaceAtMeAndKeep, kRetnType_Form);
	ADD_CMD_RET(GetMe, kRetnType_Form);							// Tested, not suitable for publishing

	ADD_CMD(tcmd);
	ADD_CMD(tcmd2);
	ADD_CMD(tcmd3);

	ADD_CMD(DumpDocs);

	ADD_CMD(ForcePlayIdle);
}

void CommandTable::AddCommandsV1()
{
	// record return type of vanilla commands which return forms
	g_scriptCommands.SetReturnType(0x1025, kRetnType_Form);		// PlaceAtMe
	g_scriptCommands.SetReturnType(0x10CD, kRetnType_Form);		// GetActionRef
	g_scriptCommands.SetReturnType(0x10CE, kRetnType_Form);		// GetSelf
	g_scriptCommands.SetReturnType(0x10CF, kRetnType_Form);		// GetContainer
	g_scriptCommands.SetReturnType(0x10E8, kRetnType_Form);		// GetCombatTarget
	g_scriptCommands.SetReturnType(0x10E9, kRetnType_Form);		// GetPackageTarget
	g_scriptCommands.SetReturnType(0x1113, kRetnType_Form);		// GetParentRef
	g_scriptCommands.SetReturnType(0x116B, kRetnType_Form);		// GetLinkedRef
	g_scriptCommands.SetReturnType(0x11BD, kRetnType_Form);		// PlaceAtMeHealthPercent
	g_scriptCommands.SetReturnType(0x11CF, kRetnType_Form);		// GetPlayerGrabbedRef
	g_scriptCommands.SetReturnType(0x124E, kRetnType_Form);		// GetOwnerLastTarget
	g_scriptCommands.SetReturnType(0x1265, kRetnType_Form);		// ObjectUnderTheReticule

	RecordReleaseVersion();

	// beta 1
	ADD_CMD(GetNVSEVersion);
	ADD_CMD(GetNVSERevision);
	ADD_CMD(GetNVSEBeta);
	ADD_CMD_RET(GetBaseObject, kRetnType_Form);
	ADD_CMD(GetWeight);
	ADD_CMD(GetHealth);
	ADD_CMD(GetValue);
	ADD_CMD(SetWeight);
	ADD_CMD(SetHealth);
	ADD_CMD(SetBaseItemValue);
	ADD_CMD(GetType);
	ADD_CMD_RET(GetRepairList, kRetnType_Form);
	ADD_CMD(GetEquipType);
	ADD_CMD_RET(GetWeaponAmmo, kRetnType_Form);
	ADD_CMD(GetWeaponClipRounds);
	ADD_CMD(GetAttackDamage);
	ADD_CMD(GetWeaponType);
	ADD_CMD(GetWeaponMinSpread);
	ADD_CMD(GetWeaponSpread);
	ADD_CMD(GetWeaponProjectile);
	ADD_CMD(GetWeaponSightFOV);
	ADD_CMD(GetWeaponMinRange);
	ADD_CMD(GetWeaponMaxRange);
	ADD_CMD(GetWeaponAmmoUse);
	ADD_CMD(GetWeaponActionPoints);
	ADD_CMD(GetWeaponCritDamage);
	ADD_CMD(GetWeaponCritChance);
	ADD_CMD(GetWeaponCritEffect);
	ADD_CMD(GetWeaponFireRate);
	ADD_CMD(GetWeaponAnimAttackMult);
	ADD_CMD(GetWeaponRumbleLeftMotor);
	ADD_CMD(GetWeaponRumbleRightMotor);
	ADD_CMD(GetWeaponRumbleDuration);
	ADD_CMD(GetWeaponRumbleWavelength);
	ADD_CMD(GetWeaponAnimShotsPerSec);
	ADD_CMD(GetWeaponAnimReloadTime);
	ADD_CMD(GetWeaponAnimJamTime);
	ADD_CMD(GetWeaponSkill);
	ADD_CMD(GetWeaponResistType);
	ADD_CMD(GetWeaponFireDelayMin);
	ADD_CMD(GetWeaponFireDelayMax);
	ADD_CMD(GetWeaponAnimMult);
	ADD_CMD(GetWeaponReach);
	ADD_CMD(GetWeaponIsAutomatic);
	ADD_CMD(GetWeaponHandGrip);
	ADD_CMD(GetWeaponReloadAnim);
	ADD_CMD(GetWeaponBaseVATSChance);
	ADD_CMD(GetWeaponAttackAnimation);
	ADD_CMD(GetWeaponNumProjectiles);
	ADD_CMD(GetWeaponAimArc);
	ADD_CMD(GetWeaponLimbDamageMult);
	ADD_CMD(GetWeaponSightUsage);
	ADD_CMD(GetWeaponHasScope);
	ImportConsoleCommand("SetGameSetting");
	ImportConsoleCommand("SetINISetting");
	ImportConsoleCommand("GetINISetting");
	ImportConsoleCommand("RefreshINI");
	ImportConsoleCommand("Save");
	ImportConsoleCommand("SaveINI");
	ImportConsoleCommand("QuitGame");
	ImportConsoleCommand("LoadGame");
	ImportConsoleCommand("CloseAllMenus");
	ImportConsoleCommand("SetVel");
	ADD_CMD(ListGetCount);
	ADD_CMD_RET(ListGetNthForm, kRetnType_Form);
	ADD_CMD(ListGetFormIndex);
	ADD_CMD(ListAddForm);
	ADD_CMD(ListAddReference);
	ADD_CMD(ListRemoveNthForm);
	ADD_CMD(ListRemoveForm);
	ADD_CMD(ListReplaceNthForm);
	ADD_CMD(ListReplaceForm);
	ADD_CMD(ListClear);
	ADD_CMD_RET(GetEquippedObject, kRetnType_Form);
	ADD_CMD(GetEquippedCurrentHealth);
	ADD_CMD(CompareNames);
	ADD_CMD(SetName);
	ADD_CMD(GetHotkeyItem);
	ADD_CMD(GetNumItems);
	ADD_CMD_RET(GetInventoryObject, kRetnType_Form);
	ADD_CMD(SetEquippedCurrentHealth);
	ADD_CMD(GetCurrentHealth);
	ADD_CMD(SetCurrentHealth);
	ADD_CMD(IsKeyPressed);
	ADD_CMD(TapKey);
	ADD_CMD(HoldKey);
	ADD_CMD(ReleaseKey);
	ADD_CMD(DisableKey);
	ADD_CMD(EnableKey);
	ADD_CMD(GetNumKeysPressed);
	ADD_CMD(GetKeyPress);
	ADD_CMD(GetNumMouseButtonsPressed);
	ADD_CMD(GetMouseButtonPress);
	ADD_CMD(GetControl);
	ADD_CMD(GetAltControl);
	ADD_CMD(MenuTapKey);
	ADD_CMD(MenuHoldKey);
	ADD_CMD(MenuReleaseKey);
	ADD_CMD(DisableControl);
	ADD_CMD(EnableControl);
	ADD_CMD(TapControl);
	ADD_CMD(SetControl);
	ADD_CMD(SetAltControl);
	ADD_CMD(SetIsControl);
	ADD_CMD(IsControl);
	ADD_CMD(IsKeyDisabled);
	ADD_CMD(IsControlDisabled);
	ADD_CMD(IsControlPressed);
	ADD_CMD(IsPersistent);
	ADD_CMD_RET(GetParentCell, kRetnType_Form);
	ADD_CMD_RET(GetParentWorldspace, kRetnType_Form);
	ADD_CMD_RET(GetTeleportCell, kRetnType_Form);
	ADD_CMD_RET(GetLinkedDoor, kRetnType_Form);
	ADD_CMD_RET(GetFirstRef, kRetnType_Form);
	ADD_CMD_RET(GetNextRef, kRetnType_Form);
	ADD_CMD(GetNumRefs);
	ADD_CMD_RET(GetFirstRefInCell, kRetnType_Form);
	ADD_CMD(GetNumRefsInCell);
	ADD_CMD(GetRefCount);
	ADD_CMD(SetRefCount);
	ADD_CMD(GetArmorAR);
	ADD_CMD(IsPowerArmor);
	ADD_CMD(SetIsPowerArmor);
	ADD_CMD(SetRepairList);
	ADD_CMD(IsQuestItem);
	ADD_CMD(SetQuestItem);
	ADD_CMD_RET(GetObjectEffect, kRetnType_Form);
	ADD_CMD(SetWeaponAmmo);
	ADD_CMD(SetWeaponClipRounds);
	ADD_CMD(SetAttackDamage);
	ADD_CMD(SetWeaponType);
	ADD_CMD(SetWeaponMinSpread);
	ADD_CMD(SetWeaponSpread);
	ADD_CMD(SetWeaponProjectile);
	ADD_CMD(SetWeaponSightFOV);
	ADD_CMD(SetWeaponMinRange);
	ADD_CMD(SetWeaponMaxRange);
	ADD_CMD(SetWeaponAmmoUse);
	ADD_CMD(SetWeaponActionPoints);
	ADD_CMD(SetWeaponCritDamage);
	ADD_CMD(SetWeaponCritChance);
	ADD_CMD(SetWeaponCritEffect);
	ADD_CMD(SetWeaponAnimAttackMult);
	ADD_CMD(SetWeaponAnimMult);
	ADD_CMD(SetWeaponReach);
	ADD_CMD(SetWeaponIsAutomatic);
	ADD_CMD(SetWeaponHandGrip);
	ADD_CMD(SetWeaponReloadAnim);
	ADD_CMD(SetWeaponBaseVATSChance);
	ADD_CMD(SetWeaponAttackAnimation);
	ADD_CMD(SetWeaponNumProjectiles);
	ADD_CMD(SetWeaponAimArc);
	ADD_CMD(SetWeaponLimbDamageMult);
	ADD_CMD(SetWeaponSightUsage);
	ADD_CMD(GetNumericGameSetting);
	ADD_CMD(SetNumericGameSetting);
	ADD_CMD(GetNumericIniSetting);
	ADD_CMD(SetNumericIniSetting);
	ADD_CMD(Label);
	ADD_CMD(Goto);
	ADD_CMD(PrintToConsole);
	ADD_CMD(DebugPrint);
	ADD_CMD(SetDebugMode);
	ADD_CMD(GetDebugMode);

	// beta 2
	ADD_CMD(GetUIFloat);
	ADD_CMD(SetUIFloat);
	ADD_CMD(SetUIString);
	ADD_CMD_RET(GetCrosshairRef, kRetnType_Form);
	ADD_CMD(GetGameRestarted);
	ImportConsoleCommand("ToggleMenus");
	ImportConsoleCommand("TFC");	// changed from ToggleFreeCamera
	ImportConsoleCommand("TCL");	// changed from ToggleCollision
	ADD_CMD(GetGameLoaded);
	ADD_CMD(GetWeaponItemMod);
	ADD_CMD(IsModLoaded);
	ADD_CMD(GetModIndex);
	ADD_CMD(GetNumLoadedMods);
	ADD_CMD(GetSourceModIndex);
	ADD_CMD(GetDebugSelection);
	ADD_CMD(GetArmorDT);
	ADD_CMD(SetArmorAR);
	ADD_CMD(SetArmorDT);

	// beta 3
	ADD_CMD(IsScripted);
	ADD_CMD_RET(GetScript, kRetnType_Form);
	ADD_CMD(RemoveScript);
	ADD_CMD(SetScript);
	ADD_CMD(IsFormValid);
	ADD_CMD(IsReference);

	// beta 4 - compat with 1.2.0.285

	// beta 5
	ADD_CMD(GetWeaponRequiredStrength);
	ADD_CMD(GetWeaponRequiredSkill);
	ADD_CMD(SetWeaponRequiredStrength);
	ADD_CMD(SetWeaponRequiredSkill);
	ADD_CMD(SetWeaponResistType);
	ADD_CMD(SetWeaponSkill);
	ADD_CMD(GetAmmoSpeed);
	ADD_CMD(GetAmmoConsumedPercent);
	ADD_CMD(GetAmmoCasing);
	ADD_CMD(GetPlayerCurrentAmmoRounds);
	ADD_CMD(SetPlayerCurrentAmmoRounds);
	ADD_CMD(GetPlayerCurrentAmmo);

	// beta 6 - compat with 1.2.0.314
	ADD_CMD_RET(GetOpenKey, kRetnType_Form);
	ADD_CMD(Exp);
	ADD_CMD(Log10);
	ADD_CMD(Floor);
	ADD_CMD(Ceil);
	ADD_CMD(LeftShift);
	ADD_CMD(RightShift);
	ADD_CMD(LogicalAnd);
	ADD_CMD(LogicalOr);
	ADD_CMD(LogicalXor);
	ADD_CMD(LogicalNot);
	ADD_CMD(Pow);
	ADD_CMD(Fmod);
	ADD_CMD(Rand);

	// beta 7 - compat with 1.2.0.352
	
	// beta 8 - rewrite loader to work around steam bugs
	
	// beta 9 - compat with 1.3.0.452
	ADD_CMD(SortUIListBox);
	ADD_CMD_RET(GetOwner, kRetnType_Form);

	// beta 10 - compat with editor 1.3.0.452

	RecordReleaseVersion();

	// 2 beta 1
	ADD_CMD(GetLocalRefIndex);
	ADD_CMD_RET(BuildRef, kRetnType_Form);
	ADD_CMD(SetNameEx);
	ADD_CMD(MessageEx);
	ADD_CMD(MessageBoxEx);
	ADD_CMD_RET(TempCloneForm, kRetnType_Form);
	ADD_CMD(IsClonedForm);
	ADD_CMD_RET(GetParentCellOwner, kRetnType_Form);
	ADD_CMD(GetOwningFactionRequiredRank);
	ADD_CMD(GetParentCellOwningFactionRequiredRank);
	
	// 2 beta 2
	ADD_CMD(SetUIStringEx);

	// 2 beta 3
	// 2 beta 4

	// 2 beta 5
	ImportConsoleCommand("SetUFOCamSpeedMult");
	ImportConsoleCommand("TDT");
	ADD_CMD(SetWeaponFireRate);
	ADD_CMD(GetWeaponLongBursts);
	ADD_CMD(SetWeaponLongBursts);

	// 2 beta 6 - compat with 1.4.0.525
	ADD_CMD(GetWeaponFlags1);
	ADD_CMD(GetWeaponFlags2);
	ADD_CMD(SetWeaponFlags1);
	ADD_CMD(SetWeaponFlags2);
	ADD_CMD(GetActorBaseFlagsLow);
	ADD_CMD(SetActorBaseFlagsLow);
	ADD_CMD(GetActorBaseFlagsHigh);
	ADD_CMD(SetActorBaseFlagsHigh);
	ADD_CMD(ClearBit);
	ADD_CMD(SetBit);

	// 2 beta 7 - quick fix for InterfaceManager ptr

	// 2 beta 8 - compat with editor 1.4.0.518

	// 2 beta 9 - quick fix for IsControlDisabled

	// 2 beta 10 - compat with nogore runtime 1.4.0.525
	ADD_CMD(GetEquippedWeaponModFlags);
	ADD_CMD(SetEquippedWeaponModFlags);
	ADD_CMD(GetWeaponItemModEffect);
	ADD_CMD(GetWeaponItemModValue1);
	ADD_CMD(GetWeaponItemModValue2);

	// 2 beta 11 - fixed TESObjectWEAP struct (mod value 2 off by one)
	// 2 beta 12 - fixed GetWeaponItemModEffect etc. using 0-based indexing
}

void CommandTable::AddCommandsV3s()
{
	RecordReleaseVersion();

	// 3 alpha 01 sub 1 - submission hlp
	ADD_CMD(HasOwnership);
	ADD_CMD(IsOwned);
	ADD_CMD(SetOwningFactionRequiredRank);
	ADD_CMD_RET(GetDialogueTarget, kRetnType_Form);
	ADD_CMD_RET(GetDialogueSubject, kRetnType_Form);
	ADD_CMD_RET(GetDialogueSpeaker, kRetnType_Form);
	ADD_CMD_RET(SetPackageLocationReference, kRetnType_Form);
	ADD_CMD(GetAgeClass);
	ADD_CMD(RemoveMeIR);
	ADD_CMD(CopyIR);
	ADD_CMD_RET(CreateTempRef, kRetnType_Form);
	ADD_CMD_RET(GetFirstRefForItem, kRetnType_Form);
	ADD_CMD_RET(GetNextRefForItem, kRetnType_Form);
	ADD_CMD(AddItemOwnership);
	ADD_CMD(AddItemHealthPercentOwner);
	ADD_CMD(GetTokenValue);
	ADD_CMD(SetTokenValue);
	ADD_CMD_RET(GetTokenRef, kRetnType_Form);
	ADD_CMD(SetTokenRef);
	ADD_CMD(SetTokenValueAndRef);
	ADD_CMD(GetPaired);
	ADD_CMD(GetRespawn);
	ADD_CMD(SetRespawn);
	ADD_CMD(GetPermanent);
	ADD_CMD(SetPermanent);
	ADD_CMD_RET(GetBaseForm, kRetnType_Form);
	ADD_CMD(IsRefInList);

#ifdef RUNTIME
	// 3 beta 02 sub 5 - submission hlp
	GetByName("GetFactionRank")->eval = &Cmd_GetFactionRank_Eval;
	GetByName("GetFactionRank")->execute = &Cmd_GetFactionRank_Execute;
#endif

	// 3 beta 03 - forgotten ?
	ADD_CMD(SetOpenKey);

	// 3 beta 03 - submission hlp
	ADD_CMD_RET(GetCurrentPackage, kRetnType_Form);
	ADD_CMD(GetPackageLocation);
	ADD_CMD(GetPackageCount);
	ADD_CMD_RET(GetNthPackage, kRetnType_Form);
	ADD_CMD(SetNthPackage);
	ADD_CMD(AddPackageAt);
	ADD_CMD(RemovePackageAt);
	ADD_CMD(RemoveAllPackages);

	// 3 beta 04 - submission hlp
	ADD_CMD(ClearOpenKey);

	// 3 beta 05 - submission hlp
	ADD_CMD(SetPackageTargetReference);
	ADD_CMD(SetPackageTargetCount);
	ADD_CMD(GetPackageTargetCount);
	ADD_CMD(SetPackageLocationRadius);
	ADD_CMD(GetPackageLocationRadius);
}

void CommandTable::AddCommandsV4()
{
	RecordReleaseVersion();

	// 4.1 beta 01 - submission hlp
	ADD_CMD(SetEyes);
	ADD_CMD_RET(GetEyes, kRetnType_Form);
	ADD_CMD(SetHair);
	ADD_CMD_RET(GetHair, kRetnType_Form);
	ADD_CMD(GetHairLength);
	ADD_CMD(SetHairLength);
	ADD_CMD(GetHairColor);
	ADD_CMD(SetHairColor);
	ADD_CMD(GetNPCWeight);
	ADD_CMD(SetNPCWeight);
	ADD_CMD(GetNPCHeight);
	ADD_CMD(SetNPCHeight);
	ADD_CMD(Update3D);

#ifdef RUNTIME
	// 4.1 beta 01 - submission hlp
	GetByName("ModFactionRank")->execute = &Cmd_ModFactionRank_Execute;
#endif

	// 4.1 beta 01 - subset of CommandScripts from OBSE 21 beta 4
	ADD_CMD(GetVariable);
	ADD_CMD(HasVariable);
	ADD_CMD(GetRefVariable);
	ADD_CMD_RET(GetArrayVariable, kRetnType_Array);		// corrected in version 4.5 Beta 7
	ADD_CMD(CompareScripts);
	ADD_CMD(ResetAllVariables);
	ADD_CMD(GetNumExplicitRefs);
	ADD_CMD_RET(GetNthExplicitRef, kRetnType_Form);
	ADD_CMD(RunScript);
	ADD_CMD_RET(GetCurrentScript, kRetnType_Form);
	ADD_CMD_RET(GetCallingScript, kRetnType_Form);

	// 4.1 beta 01 - general merged into scripting
	ADD_CMD(Let);
	ADD_CMD(eval);
	ADD_CMD(While);
	ADD_CMD(Loop);
	ADD_CMD(ForEach);
	ADD_CMD(Continue);
	ADD_CMD(Break);
	ADD_CMD_RET(ToString, kRetnType_String);
	ADD_CMD(Print);
	ADD_CMD(testexpr);
	ADD_CMD_RET(TypeOf, kRetnType_String);
	ADD_CMD(Function);
	ADD_CMD_RET(Call, kRetnType_Ambiguous);
	ADD_CMD(SetFunctionValue);
	ADD_CMD_RET(GetUserTime, kRetnType_Array);	// corrected in version 4.2 Beta 4 alpha 1
	ADD_CMD_RET(GetModLocalData, kRetnType_Ambiguous);	// corrected in version 5.0 Beta 3
	ADD_CMD(SetModLocalData);							// restored in version 5.0 Beta 3
	ADD_CMD(ModLocalDataExists);
	ADD_CMD(RemoveModLocalData);
	ADD_CMD_RET(GetAllModLocalData, kRetnType_Array);	// corrected in version 4.5 Beta 6
	ADD_CMD(Internal_PushExecutionContext);
	ADD_CMD(Internal_PopExecutionContext);

	// 4.1 beta 01 - Arrays (except "NI" stuff)
	ADD_CMD_RET(ar_Construct, kRetnType_Array);
	ADD_CMD(ar_Size);
	ADD_CMD(ar_Dump);
	ADD_CMD(ar_DumpID);
	ADD_CMD(ar_Erase);
	ADD_CMD_RET(ar_Sort, kRetnType_Array);
	ADD_CMD_RET(ar_CustomSort, kRetnType_Array);
	ADD_CMD_RET(ar_SortAlpha, kRetnType_Array);
	ADD_CMD_RET(ar_Find, kRetnType_ArrayIndex);
	ADD_CMD_RET(ar_First, kRetnType_ArrayIndex);
	ADD_CMD_RET(ar_Last, kRetnType_ArrayIndex);
	ADD_CMD_RET(ar_Next, kRetnType_ArrayIndex);
	ADD_CMD_RET(ar_Prev, kRetnType_ArrayIndex);
	ADD_CMD_RET(ar_Keys, kRetnType_Array);
	ADD_CMD(ar_HasKey);
	ADD_CMD_RET(ar_BadStringIndex, kRetnType_String);
	ADD_CMD(ar_BadNumericIndex);
	ADD_CMD_RET(ar_Copy, kRetnType_Array);
	ADD_CMD_RET(ar_DeepCopy, kRetnType_Array);
	ADD_CMD_RET(ar_Null, kRetnType_Array);
	ADD_CMD(ar_Resize);
	ADD_CMD(ar_Insert);
	ADD_CMD(ar_InsertRange);
	ADD_CMD(ar_Append);
	ADD_CMD_RET(ar_List, kRetnType_Array);
	ADD_CMD_RET(ar_Map, kRetnType_Array);
	ADD_CMD_RET(ar_Range, kRetnType_Array);


	// 4.1 beta 01 - StringVar
	ADD_CMD(sv_Destruct);
	ADD_CMD_RET(sv_Construct, kRetnType_String);
	ADD_CMD(sv_Set);
	ADD_CMD(sv_Compare);
	ADD_CMD(sv_Length);
	ADD_CMD(sv_Erase);
	ADD_CMD_RET(sv_SubString, kRetnType_String);
	ADD_CMD(sv_ToNumeric);
	ADD_CMD(sv_Insert);
	ADD_CMD(sv_Count);
	ADD_CMD(sv_Find);
	ADD_CMD(sv_Replace);
	ADD_CMD(sv_GetChar);
	ADD_CMD_RET(sv_Split, kRetnType_Array);
	ADD_CMD_RET(sv_Percentify, kRetnType_String);
	ADD_CMD_RET(sv_ToUpper, kRetnType_String);
	ADD_CMD_RET(sv_ToLower, kRetnType_String);

	ADD_CMD(IsLetter);
	ADD_CMD(IsDigit);
	ADD_CMD(IsPrintable);
	ADD_CMD(IsPunctuation);
	ADD_CMD(IsUpperCase);
	ADD_CMD(CharToAscii);

	ADD_CMD(ToUpper);
	ADD_CMD(ToLower);
	ADD_CMD_RET(AsciiToChar, kRetnType_String);
	ADD_CMD_RET(NumToHex, kRetnType_String);
	ADD_CMD(ToNumber);

	ADD_CMD_RET(GetNthModName, kRetnType_String);
	ADD_CMD_RET(GetName, kRetnType_String);
	ADD_CMD_RET(GetKeyName, kRetnType_String);
	ADD_CMD_RET(GetFormIDString, kRetnType_String);
	ADD_CMD_RET(GetRawFormIDString, kRetnType_String);
	ADD_CMD_RET(GetFalloutDirectory, kRetnType_String);
	ADD_CMD_RET(ActorValueToString, kRetnType_String);
	ADD_CMD_RET(ActorValueToStringC, kRetnType_String);

	// 4 beta 01 - using strings with forms
	ADD_CMD_RET(GetModelPath, kRetnType_String);
	ADD_CMD_RET(GetIconPath, kRetnType_String);
	ADD_CMD_RET(GetBipedModelPath, kRetnType_String);
	ADD_CMD_RET(GetBipedIconPath, kRetnType_String);
	ADD_CMD_RET(GetTexturePath, kRetnType_String);
	ADD_CMD(SetModelPathEX);
	ADD_CMD(SetIconPathEX);
	ADD_CMD(SetBipedIconPathEX);
	ADD_CMD(SetBipedModelPathEX);
	ADD_CMD(SetTexturePath);

	ADD_CMD_RET(GetNthFactionRankName, kRetnType_String);
	ADD_CMD(SetNthFactionRankNameEX);

	ADD_CMD_RET(GetStringGameSetting, kRetnType_String);
	ADD_CMD(SetStringGameSettingEX);

	// 4.2 beta 02
	ADD_CMD_RET(GetRace, kRetnType_Form);
	ADD_CMD_RET(GetRaceName, kRetnType_String);
	ImportConsoleCommand("SCOF");
	ADD_CMD(PickOneOf);

	// 4.2 beta 03 alpha 5
	ADD_CMD(IsPlayerSwimming);
	ADD_CMD(GetTFC);

	// 4.2 beta 03 alpha 6	- Algohol OBSE plugin by emtim (with permission)

	//	Vector3 commands
	ADD_CMD( V3Length );
	ADD_CMD( V3Normalize );
	//ADD_CMD( V3Dotproduct );
	ADD_CMD( V3Crossproduct );

	//	Quaternion commands
	ADD_CMD( QFromEuler );
	ADD_CMD( QFromAxisAngle );
	ADD_CMD( QNormalize );
	ADD_CMD( QMultQuatQuat );
	ADD_CMD( QMultQuatVector3 );
	ADD_CMD( QToEuler );
	ADD_CMD( QInterpolate );

	// 4.2 beta 04 alpha 1
	ADD_CMD(IsPlayable);
	ADD_CMD(SetIsPlayable);
	ADD_CMD(GetEquipmentSlotsMask);
	ADD_CMD(SetEquipmentSlotsMask);
	ImportConsoleCommand("SQV");		// requires ConsoleEcho to be turned on!
	ADD_CMD(GetConsoleEcho);
	ADD_CMD(SetConsoleEcho);

	// 4.2 beta 04 alpha 5
	ADD_CMD_RET(GetScopeModelPath, kRetnType_String);
	ADD_CMD(SetScopeModelPath);

	// 4.3 and 4.4 sk�pped

	// 4.5 beta 01 none added

	// 4.5 beta 02
	ADD_CMD(EndVATScam);	// Provided by Queued

	// 4.5 beta 06
	ADD_CMD(EquipItem2);	// EquipItem2 is broken in the sense that the item is equipped after equipitem returns so which item is equipped is not detected :(
	ADD_CMD(EquipMe);
	ADD_CMD(UnequipMe);
	ADD_CMD(IsEquipped);
	ADD_CMD_RET(GetInvRefsForItem, kRetnType_Array);
	ADD_CMD(SetHotkeyItem);
	ADD_CMD(ClearHotkey);
	ADD_CMD(PrintDebug);
	ADD_CMD(SetVariable);
	ADD_CMD(SetRefVariable);
	ImportConsoleCommand("ShowVars");		// requires ConsoleEcho to be turned on!
	ADD_CMD_RET(GetStringIniSetting, kRetnType_String);
	ADD_CMD(SetStringIniSetting);

	// 4.5 beta 07

	ADD_CMD(GetPerkRank);										// Tested
	ADD_CMD(GetAltPerkRank);									// Tested
	ADD_CMD(GetEquipmentBipedMask);								// Tested
	ADD_CMD(SetEquipmentBipedMask);								// Tested
	ADD_CMD_RET(GetRefs, kRetnType_Array);						// Tested
	ADD_CMD_RET(GetRefsInCell, kRetnType_Array);				// Tested
	ADD_CMD(GetBaseNumFactions);								// Tested
	ADD_CMD_RET(GetBaseNthFaction, kRetnType_Form);				// Tested
	ADD_CMD(GetBaseNthRank);									// Tested
	ADD_CMD(GetNumRanks);										// Tested
	ADD_CMD_RET(GetRaceHairs, kRetnType_Array);					// Tested
	ADD_CMD_RET(GetRaceEyes, kRetnType_Array);					// Tested
	ADD_CMD_RET(GetBaseSpellListSpells, kRetnType_Array);		// Tested
	ADD_CMD_RET(GetBaseSpellListLevSpells, kRetnType_Array);	// Tested but no data
	ADD_CMD_RET(GetBasePackages, kRetnType_Array);				// Tested
	ADD_CMD_RET(GetBaseFactions, kRetnType_Array);				// Tested
	ADD_CMD_RET(GetBaseRanks, kRetnType_Array);					// Tested
	ADD_CMD_RET(GetActiveFactions, kRetnType_Array);			// Tested
	ADD_CMD_RET(GetActiveRanks, kRetnType_Array);				// Tested
	ADD_CMD_RET(GetFactionRankNames, kRetnType_Array);			// Tested
	ADD_CMD_RET(GetFactionRankFemaleNames, kRetnType_Array);	// Tested
	ADD_CMD_RET(GetHeadParts, kRetnType_Array);					// Tested
	ADD_CMD_RET(GetLevCreatureRefs, kRetnType_Array);			// Tested
	ADD_CMD_RET(GetLevCharacterRefs, kRetnType_Array);			// Tested
	ADD_CMD_RET(GetListForms, kRetnType_Array);					// Tested
	ADD_CMD(GenericAddForm);									// Tested									
	ADD_CMD_RET(GenericReplaceForm, kRetnType_Form);			// Tested
	ADD_CMD_RET(GenericDeleteForm, kRetnType_Form);				// Tested
	ADD_CMD(IsPluginInstalled);									// Tested
	ADD_CMD(GetPluginVersion);									// Tested
	ADD_CMD_RET(GenericGetForm, kRetnType_Form);				// Tested
	ImportConsoleCommand("INV");								// Tested
	ADD_CMD_RET(GetNthDefaultForm, kRetnType_Form);				// Tested
	ADD_CMD(SetNthDefaultForm);									// Tested
	ADD_CMD_RET(GetDefaultForms, kRetnType_Array);				// Tested

	// 4.5 beta 08 private. Fix only

	// 4.6 beta 01
	ADD_CMD(GetGridsToLoad);
	ADD_CMD(OutputLocalMapPicturesOverride);
	ADD_CMD(SetOutputLocalMapPicturesGrids);

	// Events
	ADD_CMD(SetEventHandler);
	ADD_CMD(RemoveEventHandler);
	ADD_CMD_RET(GetCurrentEventName, kRetnType_String);
	ADD_CMD(DispatchEvent);

	ADD_CMD(GetInGrid);
	ADD_CMD(GetInGridInCell);									// Name is bad, but in line with others

	// 4.6 beta 02 : Fixes only

	// 4.6 beta 03
	ADD_CMD(AddSpellNS);
	ADD_CMD(GetFlagsLow);
	ADD_CMD(SetFlagsLow);
	ADD_CMD(GetFlagsHigh);
	ADD_CMD(SetFlagsHigh);
	ADD_CMD(HasConsoleOutputFilename);
	ADD_CMD_RET(GetConsoleOutputFilename, kRetnType_String);
	ADD_CMD(PrintF);
	ADD_CMD(PrintDebugF);
	ImportConsoleCommand("TFIK");
	ADD_CMD(IsLoadDoor);
	ADD_CMD(GetDoorTeleportX);
	ADD_CMD(GetDoorTeleportY);
	ADD_CMD(GetDoorTeleportZ);
	ADD_CMD(GetDoorTeleportRot);
	ADD_CMD(SetDoorTeleport);

	// 4.6 beta 04 : Never public
	ADD_CMD(GenericCheckForm);
	ADD_CMD(GetEyesFlags);
	ADD_CMD(SetEyesFlags);
	ADD_CMD(GetHairFlags);
	ADD_CMD(SetHairFlags);

}

void CommandTable::AddCommandsV5()
{
	RecordReleaseVersion();

	// 5.0 beta 01
	ADD_CMD(ar_Packed);
	ADD_CMD(GetActorFIKstatus);
	ADD_CMD(SetActorFIKstatus);
	ADD_CMD(GetBit);

	// 5.0 beta 02
	ADD_CMD(HasEffectShader);

	// 5.0 beta 03
	ADD_CMD_RET(GetCurrentQuestObjectiveTeleportLinks, kRetnType_Array);
	
	// Port of trig functions from OBSE
	ADD_CMD(ATan2);
	ADD_CMD(Sinh);
	ADD_CMD(Cosh);
	ADD_CMD(Tanh);
	ADD_CMD(dSin);
	ADD_CMD(dCos);
	ADD_CMD(dTan);
	ADD_CMD(dASin);
	ADD_CMD(dACos);
	ADD_CMD(dATan);
	ADD_CMD(dATan2);
	ADD_CMD(dSinh);
	ADD_CMD(dCosh);
	ADD_CMD(dTanh);

	// 5.1 beta 01
	ADD_CMD_RET(GetNthAnimation, kRetnType_String);
	ADD_CMD(AddAnimation);
	ADD_CMD(DelAnimation);
	ADD_CMD(DelAnimations);
	ADD_CMD_RET(GetClass, kRetnType_Form);
	ADD_CMD_RET(GetNameOfClass, kRetnType_String);
	ADD_CMD(ShowLevelUpMenu);

	ADD_CMD(SetWeaponAnimationPath);
	ADD_CMD(SetActorAnimationPath);
}

namespace PluginAPI
{
	const CommandInfo* GetCmdTblStart() { return g_scriptCommands.GetStart(); }
	const CommandInfo* GetCmdTblEnd() { return g_scriptCommands.GetEnd(); }
	const CommandInfo* GetCmdByOpcode(UInt32 opcode) { return g_scriptCommands.GetByOpcode(opcode); }
	const CommandInfo* GetCmdByName(const char* name) { return g_scriptCommands.GetByName(name); }
	UInt32 GetCmdRetnType(const CommandInfo* cmd) { return g_scriptCommands.GetReturnType(cmd); }
	UInt32 GetReqVersion(const CommandInfo* cmd) { return g_scriptCommands.GetRequiredNVSEVersion(cmd); }
	const PluginInfo* GetCmdParentPlugin(const CommandInfo* cmd) { return g_scriptCommands.GetParentPlugin(cmd); }
	const PluginInfo* GetPluginInfoByName(const char *pluginName) {	return g_pluginManager.GetInfoByName(pluginName); }
}

#include <ConsoleManager.h>

__declspec(naked) bool IsConsoleMode()
{
	__asm
	{
		mov		al, byte ptr ds : [0x11DEA2E]
		test	al, al
		jz		done
		mov		eax, dword ptr ds : [0x126FD98]
		mov		edx, fs : [0x2C]
		mov		eax, [edx + eax * 4]
		test	eax, eax
		jz		done
		mov		al, [eax + 0x268]
		done :
		retn
	}
}

ConsoleManager::TextList* ConsoleManager::TextList::Append(TextNode* append)
{
	append->prev = 0;
	append->next = this->first;
	if (this->first) this->first->prev = append;
	else this->last = append;
	this->first = append;
	++this->count;
	return this;
}

char* ConsoleManager::GetConsoleOutputFilename()
{
	return GetSingleton()->scofPath;
};

bool ConsoleManager::HasConsoleOutputFilename() {
	return 0 != GetSingleton()->scofPath[0];
}

void ConsoleManager::AppendToSentHistory(const char* str)
{
	// create text node
	auto* textNode = static_cast<TextNode*>(GameHeapAlloc(sizeof(TextNode)));
	textNode->next = 0;
	textNode->prev = 0;

	textNode->text.m_data = NULL;
	textNode->text.Init(0);
	textNode->text.Set(str);

	// append it to the input history
	this->inputHistory.Append(textNode);
}

bool* bEchoConsole = reinterpret_cast<bool*>(0x011F158C);

bool GetConsoleEcho()
{
	return *bEchoConsole != 0;
}

void SetConsoleEcho(const bool doEcho)
{
	*bEchoConsole = doEcho ? true : false;
}

#include <Containers.h>
#include <Utilities.h>

String::String() : m_data(NULL), m_dataLen(0), m_bufLen(0) {}

String::~String()
{
	if (m_data)
	{
		GameHeapFree(m_data);
		m_data = NULL;
	}
	m_bufLen = m_dataLen = 0;
}

bool String::Set(const char* src)
{
	if (!src) {
		GameHeapFree(m_data);
		m_data = 0;
		m_bufLen = 0;
		m_dataLen = 0;
		return true;
	}

	UInt32	srcLen = strlen(src);

	// realloc if needed
	if (srcLen > m_bufLen)
	{
		GameHeapFree(m_data);
		m_data = (char*)GameHeapAlloc(srcLen + 1);
		m_bufLen = m_data ? srcLen : 0;
	}

	if (m_data)
	{
		strcpy_s(m_data, m_bufLen + 1, src);
		m_dataLen = srcLen;
	}
	else
	{
		m_dataLen = 0;
	}

	return m_data != NULL;
}

bool String::Includes(const char* toFind) const
{
	if (!m_data || !toFind)		//passing null ptr to std::string c'tor = CRASH
		return false;
	std::string curr(m_data, m_dataLen);
	std::string str2(toFind);
	std::string::iterator currEnd = curr.end();
	return (std::search(curr.begin(), currEnd, str2.begin(), str2.end(), ci_equal) != currEnd);
}

bool String::Replace(const char* _toReplace, const char* _replaceWith)
{
	if (!m_data || !_toReplace)
		return false;

	std::string curr(m_data, m_dataLen);
	std::string toReplace(_toReplace);

	std::string::iterator currBegin = curr.begin();
	std::string::iterator currEnd = curr.end();
	std::string::iterator replaceIt = std::search(currBegin, currEnd, toReplace.begin(), toReplace.end(), ci_equal);
	if (replaceIt != currEnd) {
		std::string replaceWith(_replaceWith);
		// we found the substring, now we need to do the modification
		std::string::size_type replacePos = distance(currBegin, replaceIt);
		curr.replace(replacePos, toReplace.size(), replaceWith);
		Set(curr.c_str());
		return true;
	}
	return false;
}

bool String::Append(const char* toAppend)
{
	std::string curr("");
	if (m_data)
		curr = std::string(m_data, m_dataLen);

	curr += toAppend;
	Set(curr.c_str());
	return true;
}

double String::Compare(const String& compareTo, bool caseSensitive)
{
	if (!m_data)
		return -2;		//signal value if comparison could not be made

	std::string first(m_data, m_dataLen);
	std::string second(compareTo.m_data, compareTo.m_dataLen);

	if (!caseSensitive)
	{
		std::transform(first.begin(), first.end(), first.begin(), tolower);
		std::transform(second.begin(), second.end(), second.begin(), tolower);
	}

	double comp = 0;
	if (first < second)
		comp = -1;
	else if (first > second)
		comp = 1;

	return comp;
}

const char* String::CStr() const
{
	return m_dataLen && m_data ? m_data : "";
}

void String::Init(UInt32 bufSize)
{
	if (m_data) GameHeapFree(m_data);
	m_bufLen = bufSize;
	m_data = (char*)GameHeapAlloc(m_bufLen + 1);
	*m_data = 0;
	m_dataLen = 0;
}


void String::AppendChar(char toAppend)
{
	if (m_bufLen == m_dataLen)
	{
		m_bufLen++;
		char* newStr = (char*)GameHeapAlloc(m_bufLen + 1);
		if (m_data)
		{
			memcpy(newStr, m_data, m_dataLen);
			GameHeapFree(m_data);
		}
		m_data = newStr;
	}
	m_data[m_dataLen++] = toAppend;
	m_data[m_dataLen] = 0;
}

void String::InsertChar(char toInsert, UInt32 index)
{
	if (index > m_dataLen) return;
	if (m_bufLen == m_dataLen)
	{
		m_bufLen++;
		char* newStr = (char*)GameHeapAlloc(m_bufLen + 1);
		if (m_data)
		{
			memcpy(newStr, m_data, m_dataLen);
			GameHeapFree(m_data);
		}
		m_data = newStr;
	}
	if (index < m_dataLen)
		memcpy(m_data + index + 1, m_data + index, m_dataLen - index);
	m_dataLen++;
	m_data[index] = toInsert;
	m_data[m_dataLen] = 0;
}

void String::EraseAt(UInt32 index)
{
	if (!m_data || (index >= m_dataLen)) return;
	m_dataLen--;
	if (m_dataLen)
	{
		UInt32 length = m_dataLen - index;
		if (!length)
			m_data[m_dataLen] = 0;
		else
			memmove(m_data + index, m_data + index + 1, length + 1);
	}
	else *m_data = 0;
}

void String::EraseAfter(UInt32 index)
{
	while (m_dataLen > index)
	{
		EraseAt(index);
	}
}

int String::EraseWord(UInt32 index)
{
	int charsSinceSpace = GetCharsSinceSpace(m_data, index);
	int newIndex = index - charsSinceSpace;
	while (charsSinceSpace--)
	{
		EraseAt(--index);
	}
	return newIndex;
}

void String::EraseNextWord(UInt32 index)
{
	int charsTillSpace = GetCharsTillSpace(m_data, index) + 1;
	while (charsTillSpace--)
	{
		EraseAt(index);
	}
}

void String::RemoveLastChar()
{
	if (!m_data || !m_dataLen) return;
	m_data[--m_dataLen] = '\0';
}

#include "GameData.h"


class LoadedModFinder
{
	const char * m_stringToFind;

public:
	LoadedModFinder(const char * str) : m_stringToFind(str) { }

	bool Accept(ModInfo* modInfo)
	{
		return !StrCompare(modInfo->name, m_stringToFind);
	}
};

const ModInfo * TESDataHandler::LookupModByName(const char * modName)
{
	return modList.modInfoList.Find(LoadedModFinder(modName));
}

std::vector<ModInfo*> activeMods;

std::vector<ModInfo*> TESDataHandler::GetActiveModList()
{
	if (activeMods.empty())
		for (const auto iter: modList.modInfoList)
			if (iter->IsLoaded()) activeMods.push_back(iter);
	return activeMods;
}

UInt8 TESDataHandler::GetActiveModCount() const
{
	if (activeMods.empty())
		for (const auto iter : modList.modInfoList)
			if (iter->IsLoaded()) activeMods.push_back(iter);
	return activeMods.size();
}

UInt8 TESDataHandler::GetModIndex(const char* modName)
{
	return modList.modInfoList.GetIndexOf(LoadedModFinder(modName));
}

const char* TESDataHandler::GetNthModName(UInt32 modIndex)
{
	if (modIndex == 0xFF) return "Runtime";
	if (const auto iter = GetActiveModList()[modIndex]) return iter->name;
	return "";
}

void TESDataHandler::DisableAssignFormIDs(bool shouldAsssign)
{
	ThisStdCall(0x464D30, this, shouldAsssign);
}


ModInfo::ModInfo() {
	//
};

ModInfo::~ModInfo() {
	//
};

#include "GameTasks.h"
#include "TESObjectREFR.h"

// IOManager** g_ioManager = (IOManager**)0x00B33A10;
ModelLoader** g_modelLoader = (ModelLoader**)0x011C3B3C;
UInt32 kModelLoader_QueueReference = 0x00444850;
UInt32 * kBSTaskCounter = (UInt32*) 0x0011C3B38;

#if 0
bool IOManager::IsInQueue(TESObjectREFR *refr) 
{
	for (LockFreeQueue< NiPointer<IOTask> >::Node *node = taskQueue->head->next; node; node = node->next) 
	{
		QueuedReference *qr = OBLIVION_CAST(node->data, IOTask, QueuedReference);
		if (!qr)
			continue;

		if (qr->refr == refr)
			return true;
	}

	return false;
}

void IOManager::DumpQueuedTasks()
{
#if 0
	_MESSAGE("Dumping queued tasks:");
	for (LockFreeQueue< NiPointer<IOTask> >::Node *node = taskQueue->head->next; node; node = node->next)
	{
		QueuedReference* qr = OBLIVION_CAST(node->data, IOTask, QueuedReference);
		if (!qr)
			continue;
		else if (qr->refr)
		{
			Console_Print("\t%s (%08x)", GetFullName(qr->refr), qr->refr->refID);
			_MESSAGE("\t%s (%08x)", GetFullName(qr->refr), qr->refr->refID);
		}
		else
			_MESSAGE("NULL reference");
	}
#endif

}

IOManager* IOManager::GetSingleton()
{
	return *g_ioManager;
}
#endif

ModelLoader* ModelLoader::GetSingleton()
{
	return *g_modelLoader;
}

void ModelLoader::QueueReference(TESObjectREFR* refr, UInt32 arg1, bool ifInMainThread)
{
	ThisStdCall(kModelLoader_QueueReference, this, refr, arg1, (UInt32)ifInMainThread);	// arg1 is encoded based on the parent cell and arg2 is most likely a boolean
}

UInt32* BSTask::GetCounterSingleton()
{
	return kBSTaskCounter;
}

#include <InterfaceManager.h>
#include <TESObjectREFR.h>
#include <SafeWrite.h>

const _QueueUIMessage QueueUIMessage = reinterpret_cast<_QueueUIMessage>(0x007052F0);	// Called from Cmd_AddSpell_Execute

const _ShowMessageBox ShowMessageBox = reinterpret_cast<_ShowMessageBox>(0x00703E80);
const _ShowMessageBox_Callback ShowMessageBox_Callback = reinterpret_cast<_ShowMessageBox_Callback>(0x005B4A70);
const _ShowMessageBox_pScriptRefID ShowMessageBox_pScriptRefID = reinterpret_cast<_ShowMessageBox_pScriptRefID>(0x011CAC64);
const _ShowMessageBox_button ShowMessageBox_button = reinterpret_cast<_ShowMessageBox_button>(0x0118C684);

int* (__thiscall* Tile_A01000)(Tile*, enum TileValues) = (int* (__thiscall*)(Tile*, enum TileValues))0xA01000;
void(__thiscall* TileValueSetString)(int*, char*, char) = (void(__thiscall*)(int*, char*, char))0xA0A300;
void FontTextReplaced::GetVariableEscapedText(const char* input) { Font__CheckForVariablesInText(FontManager::GetSingleton()->fontInfos[0], input, this); }

FontInfo* FontInfo::Load(const char* path, UInt32 ID)
{
	FontInfo* info = (FontInfo*)GameHeapAlloc(sizeof(FontInfo));
	return (FontInfo*)ThisStdCall(0x00A12020, info, ID, path, 1);
}

bool FontInfo::GetName(char* out)
{
	UInt32 len = strlen(filePath);
	len -= 4;					// '.fnt'
	UInt32 start = len;
	while (filePath[start - 1] != '\\') {
		start--;
	}

	len -= start;

	memcpy(out, filePath + start, len);
	out[len] = 0;

	return true;
}

std::string FontManager::StringShorten(const std::string& str, const UInt32 font, const Float32 max) const
{
	if (str.empty() || font < 1) return "";

	const auto charDimensions = fontInfos[font - 1]->fontData->charDimensions;

	const auto dotDims = charDimensions['.'];
	const auto dotWidth = (dotDims.width + dotDims.widthMod + dotDims.flt2C) * 3.0;
	Float64 accumulator = 0;
	UInt32 length = 0;

	for (const auto iterChar : str)
	{
		if (accumulator + dotWidth < max) length++;
		if (accumulator >= max) return str.substr(0, length) + "...";
		const auto charDims = charDimensions[iterChar];
		// < 100 is a sanity check because cyrillic fonts for whatever reason have this value ruined
		accumulator += charDims.width + charDims.flt2C + charDims.widthMod < 100 ? charDims.widthMod : 0;
	}
	return str;
}

void InterfaceManager::VATSHighlightData::AddRef(TESObjectREFR* ref)
{
	if (ref->GetNiNode())
	{
		ThisCall(0x800D50, this, ref);
		this->mode = 1;
	}
};

void InterfaceManager::VATSHighlightData::AddRefAndSetFlashing(TESObjectREFR* ref)
{
	if (ref->GetNiNode())
	{
		ThisCall(0x800E50, this, ref);
		this->mode = 1;
	}
};

/*
 * Lifted from JIP LN
 */
__declspec(naked) UInt32 InterfaceManager::GetTopVisibleMenuID()
{
	__asm
	{
		cmp		byte ptr[ecx + 0xC], 2
		jb		retn0
		mov		eax, [ecx + 0xD0]
		add		ecx, 0x114
		test	eax, eax
		jz		stackIter
		mov		eax, [eax + 0x20]
		retn
		ALIGN 16
	stackIter:
		add		ecx, 4
		cmp[ecx], 0
		jnz		stackIter
		mov		eax, [ecx - 4]
		cmp		eax, 1
		jnz		done
		mov		ecx, 0x11F3479
		mov		eax, 0x3EA
		cmp[ecx], 0
		jnz		done
		mov		al, 0xFF
		cmp[ecx + 0x15], 0
		jnz		done
		mov		al, 0xEB
		cmp[ecx + 1], 0
		jnz		done
		mov		eax, 0x40B
		cmp[ecx + 0x21], 0
		jnz		done
		mov		al, 0x25
		cmp[ecx + 0x3B], 0
		jnz		done
	retn0 :
		xor eax, eax
	done :
		retn
	}
}

Tile* InterfaceManager::GetActiveTile()
{
	return activeTile ? activeTile : activeTileAlt;
}

#include <InventoryChanges.h>

#include <TESForm.h>
#include <BSExtraData.h>
#include <TESObjectREFR.h>

#include <RTTI.h>

void InventoryChanges::Cleanup()
{
	// Didn't find the hook, let's fake it
	if (!extendData) return;

	for (const auto iter : *extendData)
	{
		if (const auto xCount = reinterpret_cast<ExtraCount*>(iter->GetByType(kExtraData_Count)); xCount &&
			xCount->count <= 1)
			iter->RemoveByType(kExtraData_Count);

		if (!countDelta && !iter->m_data) // There are other extras than count like ExtraWorn :)
			extendData->RemoveItem(iter);
	}
	extendData->RemoveItem(nullptr);
}

InventoryChanges* InventoryChanges::Create(TESForm* pForm, UInt32 count, ExtendDataList* pExtendDataList)
{
	const auto xData = static_cast<InventoryChanges*>(GameHeapAlloc(sizeof(InventoryChanges)));
	if (xData) {
		memset(xData, 0, sizeof(InventoryChanges));
		if (pForm) {
			xData->form = pForm;
			xData->countDelta = count;
			if (pExtendDataList == nullptr)
			{
				pExtendDataList = static_cast<ExtendDataList*>(GameHeapAlloc(sizeof(ExtendDataList)));
				if (pExtendDataList) memset(pExtendDataList, 0, sizeof(ExtendDataList));
			}
			xData->extendData = pExtendDataList;
		}
	}
	return xData;
}

ExtendDataList* InventoryChanges::Add(ExtraDataList* newList)
{
	if (extendData)
		extendData->AddAt(newList, eListEnd);
	else
		extendData = ExtendDataList::Create(newList);
	const auto xCount = (ExtraCount*)newList->GetByType(kExtraData_Count);
	countDelta += xCount ? xCount->count : 1;
	return extendData;
}

bool InventoryChanges::Remove(ExtraDataList* toRemove, bool bFree)
{
	if (extendData && toRemove) {
		const SInt32 index = extendData->GetIndexOfItem(toRemove);
		if (index >= 0) {
			const auto xCount = (ExtraCount*)toRemove->GetByType(kExtraData_Count);
			const SInt16 count = xCount ? xCount->count : 1;

			extendData->RemoveNth(index);
			countDelta -= count;
			if (bFree) {
				toRemove->RemoveAll(true);
				GameHeapFree(toRemove);
			}
			return true;
		}

	}
	return false;
}

bool InventoryChanges::HasExtraLeveledItem()
{
	if (!extendData) return false;
	for (const auto iter : *extendData)	if (iter->HasType(kExtraData_LeveledItem)) return true;
	return false;
}


ExtraDataList* InventoryChanges::GetEquippedExtra()
{
	return GetCustomExtra(kExtraData_Worn);
}

ExtraDataList* InventoryChanges::GetCustomExtra(UInt32 whichVal)
{
	if (!extendData) return nullptr;
	const TListNode<ExtraDataList>* xdlIter = extendData->Head();
	do if (const auto xData = xdlIter->data; xData && xData->HasType(whichVal)) return xData;
	while ((xdlIter = xdlIter->next));
	return nullptr;
}

BSExtraData* InventoryChanges::GetExtraData(UInt32 whichVal)
{
	const auto extra = GetCustomExtra(whichVal);
	return extra ? extra->GetByType(whichVal) : nullptr;
}

UInt32 InventoryChanges::GetWeaponNumProjectiles(Actor* owner)
{
	return ThisCall<UInt8>(0x525B20, this->form, this->HasWeaponMod(0xC), 0, owner);
}

bool InventoryChanges::ShouldDisplay()
{
	return this->form->IsItemPlayable() && *this->form->GetTheName();
}

UInt8 InventoryChanges::GetWeaponMod()
{
	const auto xModFlags = reinterpret_cast<ExtraWeaponModFlags*>(this->GetExtraData(kExtraData_WeaponModFlags));
	return xModFlags ? xModFlags->flags : 0;
}

Float64 InventoryChanges::GetHealthPercentAlt(bool axonisFix, bool checkDestruction)
{
	Float64 healthPer = -1;

	if (const auto healthForm = DYNAMIC_CAST(form->TryGetREFRParent(), TESForm, TESHealthForm))
	{
		const auto xHealth = form->GetIsReference() ? reinterpret_cast<ExtraHealth*>(reinterpret_cast<TESObjectREFR*>(form)->extraDataList.GetByType(kExtraData_Health)) : reinterpret_cast<ExtraHealth*>(this->GetExtraData(kExtraData_Health));

		healthPer = xHealth ? xHealth->health / ((int)healthForm->health + (
			HasWeaponMod(TESObjectWEAP::kWeaponModEffect_IncreaseMaxCondition)
			? reinterpret_cast<TESObjectWEAP*>(form)->GetEffectModValue(TESObjectWEAP::kWeaponModEffect_IncreaseMaxCondition)
			: 0))
			: 1;
	}
	else if (checkDestruction)
	{
		const auto destructible = DYNAMIC_CAST(form->TryGetREFRParent(), TESForm, BGSDestructibleObjectForm);
		if (destructible && destructible->data)
		{
			const auto xObjHealth = form->GetIsReference() ? reinterpret_cast<ExtraObjectHealth*>(reinterpret_cast<TESObjectREFR*>(form)->extraDataList.GetByType(kExtraData_ObjectHealth)) : reinterpret_cast<ExtraObjectHealth*>(this->GetExtraData(kExtraData_ObjectHealth));
			healthPer = xObjHealth ? xObjHealth->health / (int)destructible->data->health : 1;
		}
	}
	return axonisFix ? healthPer >= 0.995 ? 1 : healthPer >= 95 ? 0.95 : healthPer : healthPer;
}

bool InventoryChanges::GetEquipped()
{
	if (reinterpret_cast<ExtraWorn*>(GetExtraData(kExtraData_Worn))) return true;
	if (reinterpret_cast<ExtraWornLeft*>(GetExtraData(kExtraData_WornLeft))) return true;
	return false;
}

ExtraDataList* InventoryChanges::GetExtraData() const { return extendData ? extendData->first.data : nullptr; }

UInt32 InventoryChanges::GetClipSize()
{
	if (form->typeID != kFormType_TESObjectWEAP) return 0;
	return reinterpret_cast<TESObjectWEAP*>(form)->GetClipRounds(HasWeaponMod(0x2));
}

__declspec(naked) InventoryChanges* InventoryChangesList::FindForItem(TESForm* item)
{
	__asm
	{
		mov		edx, [esp + 4]
	listIter:
		mov		eax, [ecx]
		test	eax, eax
		jz		listNext
		cmp[eax + 8], edx
		jz		done
	listNext :
		mov		ecx, [ecx + 4]
		test	ecx, ecx
		jnz		listIter
		xor eax, eax
	done :
		retn	4
	}
}


void InventoryChanges::Equip(Actor* actor, ExtraDataList* extra)
{
	actor->EquipItem(form, countDelta, extra ? extra : extendData->first.data, 0, 0, 1);
}

InventoryChanges::WithExtraData InventoryChanges::HotkeyGet(const UInt8 hotkey)
{
	const auto xChanges = reinterpret_cast<ExtraContainerChanges*>(PlayerCharacter::GetSingleton()
		->extraDataList.GetByType(kExtraData_ContainerChanges));
	for (const auto itemIter : *xChanges->data->objList)
	{
		for (const auto iter : *itemIter->extendData)
		{
			const auto xHotKey = reinterpret_cast<ExtraHotkey*>(iter->GetByType(kExtraData_Hotkey));
			if (xHotKey && xHotKey->index == hotkey)
				return { itemIter, iter };
		}
	}
	return {};
}

InventoryChanges::WithExtraData InventoryChanges::HotkeyClear(const UInt8 hotkey)
{
	const auto xChanges = reinterpret_cast<ExtraContainerChanges*>(PlayerCharacter::GetSingleton()
		->extraDataList.GetByType(kExtraData_ContainerChanges));
	for (const auto itemIter : *xChanges->data->objList)
	{
		for (const auto iter : *itemIter->extendData)
		{
			const auto xHotKey = reinterpret_cast<ExtraHotkey*>(iter->GetByType(kExtraData_Hotkey));
			if (xHotKey && xHotKey->index == hotkey) {
				iter->RemoveByType(kExtraData_Hotkey);
				return { itemIter, iter };
			}
		}
	}
	return {};
}

InventoryChanges::WithExtraData InventoryChanges::HotkeySet(const UInt8 hotkey)
{
	const auto cleared = HotkeyClear(hotkey);
	ExtraHotkey* xHotKey = nullptr;
	for (const auto iter : *extendData)
	{
		xHotKey = reinterpret_cast<ExtraHotkey*>(iter->GetByType(kExtraData_Hotkey));
		if (xHotKey) break;
	}
	if (!xHotKey)
	{
		xHotKey = ExtraHotkey::Create();
		if (xHotKey)
		{
			if (!extendData)
				Add(ExtraDataList::Create());
			if (extendData)
			{
				if (!extendData->count())
					extendData->AddAt(ExtraDataList::Create(), 0);
				if (extendData->count())
					extendData->GetNth(0)->Add(xHotKey);
			}
		}
	}
	if (xHotKey) xHotKey->index = hotkey;
	return cleared;
}

ExtraContainerChangesData* ExtraContainerChangesData::Create(TESObjectREFR* owner)
{
	const auto data = static_cast<ExtraContainerChangesData*>(GameHeapAlloc(sizeof(ExtraContainerChangesData)));
	if (data) {
		data->owner = owner;
		data->objList = nullptr;
		data->unk2 = 0.0;
		data->unk3 = 0.0;
	}
	return data;
}

class AcceptTESFormInInventoryChanges
{
	TESForm* m_toMatch;
public:
	AcceptTESFormInInventoryChanges(TESForm* match) : m_toMatch(match) { }
	bool Accept(const InventoryChanges* match) const { return (match && m_toMatch == match->form); }
};

ExtendDataList* ExtraContainerChangesData::Add(TESForm* form, ExtraDataList* dataList)
{
	if (!objList) objList = InventoryChangesList::Create(0, 0, nullptr);

	// try to locate the form
	InventoryChanges* found = objList->Find(AcceptTESFormInInventoryChanges(form));
	if (!found) {
		// add it to the list with a count delta of 0
		found = InventoryChanges::Create(form, 0);
		objList->AddAt(found, eListEnd);
	}

	return found->Add(dataList);
}

#include <Utilities.h>
#include <Menu.h>
#include <TESObjectREFR.h>
#include <SafeWrite.h>

static UInt8*	g_bUpdatePlayerModel		= (UInt8*)0x011C5CB4;	// this is set to true when player confirms change of race in RaceSexMenu -

void (*ToggleMenus)(bool toggleON) = reinterpret_cast<void(*)(bool)>(0x703810);
bool(__cdecl* GetIsMenuMode)() = reinterpret_cast<bool(*)()>(0x702360);
void(__cdecl* HUDMainMenu_UpdateVisibilityState)(signed int) = reinterpret_cast<void(*)(int)>(0x771700);
void(__cdecl* MenuButton_Downloads)() = reinterpret_cast<void(*)()>(0x7D0550);

void MenuButton_DownloadsClick() { MenuButton_Downloads(); }

InventoryChanges** g_modMenuTarget = reinterpret_cast<InventoryChanges**>(0x11D9F58);

UInt8* menuVisibility = reinterpret_cast<UInt8*>(0x011F308F);
NiTArray<TileMenu*>* tileMenuArray = reinterpret_cast<NiTArray<TileMenu*>*>(0x011F3508);
// IF requires change of skeleton - and back to false when model updated
bool Menu::IsVisible(const UInt32 menuType) { return menuType >= kMenuType_Min && menuType <= kMenuType_Max ? menuVisibility[menuType] : false; }
bool Menu::IsVisible() const { return IsVisible(id); }
TileMenu* Menu::GetTileMenu(const UInt32 menuType) { return menuType >= kMenuType_Min && menuType <= kMenuType_Max ? tileMenuArray->Get(menuType - kMenuType_Min) : nullptr; }
TileMenu* Menu::GetTileMenu() const { return tileMenuArray->Get(id - kMenuType_Min); }

Menu* Menu::GetMenu(const UInt32 menuType)
{
	const auto tileMenu = GetTileMenu(menuType);
	return tileMenu ? tileMenu->menu : nullptr;
}

std::unordered_map<std::string, UInt32> menuNameToID = {
	{"MessageMenu", kMenuType_Message},			{"InventoryMenu", kMenuType_Inventory},				{"StatsMenu", kMenuType_Stats},
	{"HUDMainMenu", kMenuType_HUDMain},			{"LoadingMenu", kMenuType_Loading},					{"ContainerMenu", kMenuType_Container},
	{"DialogMenu", kMenuType_Dialog},			{"SleepWaitMenu", kMenuType_SleepWait},				{"StartMenu", kMenuType_Start},
	{"LockpickMenu", kMenuType_LockPick},		{"QuantityMenu", kMenuType_Quantity},				{"MapMenu", kMenuType_Map},
	{"BookMenu", kMenuType_Book},				{"LevelUpMenu", kMenuType_LevelUp},					{"RepairMenu", kMenuType_Repair},
	{"RaceSexMenu", kMenuType_RaceSex},			{"CharGenMenu", kMenuType_CharGen},					{"TextEditMenu", kMenuType_TextEdit},
	{"BarterMenu", kMenuType_Barter},			{"SurgeryMenu", kMenuType_Surgery},					{"HackingMenu", kMenuType_Hacking},
	{"VATSMenu", kMenuType_VATS},				{"ComputersMenu", kMenuType_Computers},				{"RepairServicesMenu", kMenuType_RepairServices},
	{"TutorialMenu", kMenuType_Tutorial},		{"SpecialBookMenu", kMenuType_SpecialBook},			{"ItemModMenu", kMenuType_ItemMod},
	{"LoveTesterMenu", kMenuType_LoveTester},	{"CompanionWheelMenu", kMenuType_CompanionWheel},	{"TraitSelectMenu", kMenuType_TraitSelect},
	{"RecipeMenu", kMenuType_Recipe},			{"SlotMachineMenu", kMenuType_SlotMachine},			{"BlackjackMenu", kMenuType_Blackjack},
	{"RouletteMenu", kMenuType_Roulette},		{"CaravanMenu", kMenuType_Caravan},					{"TraitMenu", kMenuType_Trait},
};

TileMenu* Menu::GetTileMenu(const std::string& componentPath) 
{
	return GetTileMenu(menuNameToID[componentPath]);
}

Menu* Menu::GetMenu(const std::string& componentPath) 
{
	const auto tileMenu = GetTileMenu(componentPath);
	return tileMenu ? tileMenu->menu : nullptr;
}

Menu* Menu::TempMenuByType(const UInt32 menuType)
{
	return menuType >= kMenuType_Min && menuType <= kMenuType_Max ? CdeclCall<Menu*>(0x00707990, menuType) : nullptr;
}

bool Menu::GetTemplateExists(const std::string& templateName) const
{
	for (const auto node : menuTemplates) if (templateName == node->templateName) return true;
	return false;
}

bool InventoryMenu::IsKeyringOpen() const
{
	return tile->Get(static_cast<TileValueIDs>(*reinterpret_cast<UInt32*>(0x11D9EB8))); // Trait_KeyringOpen
}

bool DialogMenu::IsNPCTalking() const
{
	return tile->Get(static_cast<TileValueIDs>(*reinterpret_cast<UInt32*>(0x11D9500))); // g_dialogMenu_TraitShowingText
}

bool IsInStartMenu()
{
	const auto menu = StartMenu::GetSingleton();
	return menu && menu->flags & StartMenu::kInStartMenu;
}

/*
StartMenu::Option* StartMenu::Option::Create(const char* str, void (*callback)(), UInt32 flags)
{
	StartMenuOption* option = (StartMenuOption*)GameHeapAlloc(sizeof(StartMenuOption));
	*reinterpret_cast<UInt32*>(option) = kVtbl_StartMenuOption;
	option->displayString = str;
	option->callback = callback;
	option->data = flags;

	return option;
}
*/

/*
StartMenuUserOption* StartMenuUserOption::Init(char* str, void (*callback)(StartMenuUserOption*), StartMenuOption::WhichMenus flags, int type, int numOptions, int buttonWidth, char** optionNames)
{
	return 
}

StartMenuUserOption* StartMenuUserOption::Create(char* str, void(__cdecl* callback)(StartMenuUserOption*), StartMenuOption::WhichMenus flags, int type, int numOptions, int buttonWidth, char** optionNames)
{
	StartMenuUserOption* option = (StartMenuUserOption*)GameHeapAlloc(sizeof(StartMenuUserOption));
	return option->Init(str, callback, flags, type, numOptions, buttonWidth, optionNames);
}
*/

/*

static MapMenu* GetSingleton() { return *(MapMenu**)0x11DA368; };
static TList<TESObjectREFR> GetAvailableRadioStations() { return *(TList<TESObjectREFR>*)0x11DD59C; };
static TESObjectREFR* GetCurrentRadioStation() { return *(TESObjectREFR**)0x11DD42C; };

void Zoom(bool direction, float amount) { ThisCall(0x79C5A0, this, direction, amount); };

void Move(float deltaX, float deltaY)
{
	if (!this->tileWorldMap || (this->currentTab != MapMenu::kLocalMap && this->currentTab != MapMenu::kWorldMap))
	{
		return;
	}

	this->tileWorldMap->SetFloat(kTileValue_dragstartx, 1.0F, 1);
	this->tileWorldMap->SetFloat(kTileValue_dragstarty, 1.0F, 1);

	ThisCall(0xA01290, this->tileWorldMap, kTileValue_dragdeltax, deltaX);
	ThisCall(0xA01290, this->tileWorldMap, kTileValue_dragdeltay, deltaY);

	if (this->tile038)
	{
		this->clickStartPos.x = this->tile038->GetFloat(kTileValue_x);
		this->clickStartPos.y = this->tile038->GetFloat(kTileValue_y);
	}
}

void MoveDirection(MenuSpecialKeyboardInputCode direction)
{
	switch (direction)
	{
	case kMenu_UpArrow:
		this->Move(0.0F, 20.0F);
		break;
	case kMenu_DownArrow:
		this->Move(0.0F, -20.0F);
		break;
	case kMenu_LeftArrow:
		this->Move(20.0F, 0.0F);
		break;
	case kMenu_RightArrow:
		this->Move(-20.0F, 0.0F);
		break;
	}
}

void RefreshWorldMap()
{
	ThisCall(0xA04150, this->tile038);
	this->mapMarkerList.RemoveAll();

	// skip code moving the cursor
	WriteRelJump(0x79DF73, 0x79E053);

	// MapMenu::SetupWorldMap
	ThisCall(0x79CDB0, this);

	// restore code moving the cursor
	SafeWriteBuf(0x79DF73, "\x6A\x00\x68\xB1\x0F", 5);
}

void RefreshLocalMap()
{
	ThisCall(0xA04150, this->tile030);

	// skip code moving the cursor
	WriteRelJump(0x79DF73, 0x79E053);

	// MapMenu::SetupLocalMap
	ThisCall(0x79D410, this);

	// restore code moving the cursor
	SafeWriteBuf(0x79DF73, "\x6A\x00\x68\xB1\x0F", 5);
}
};*/

Tile::Value* StringToTilePath(const std::string& componentPath)
{
	const auto firstSlash = componentPath.find_first_of('/');
	const auto lastSlash = componentPath.find_last_of('/');
	const auto tileMenu = Menu::GetTileMenu(componentPath.substr(0, firstSlash));
	const auto tile = tileMenu->GetComponent(componentPath.substr(firstSlash + 2, lastSlash));
	const auto component = Tile::TraitNameToID(componentPath.substr(lastSlash + 2).data());
	return tile->GetValue(component);
}

/*
 * Lifted from Stewie's Tweaks
 * RefreshItemsList calls itemsList->FreeAllTiles() and then allocates the memory for all the tiles again
 * instead skip the calls that free/allocate
 */

bool Menu::RefreshItemsListForm(TESForm* form)
{
	bool refresh = false;
	if (const auto menu = BarterMenu::GetSingleton(); menu->IsVisible())
	{
		menu->Refresh(form);
		refresh = true;
	}
	if (const auto menu = ContainerMenu::GetSingleton(); menu->IsVisible())
	{
		menu->Refresh(form);
		refresh = true;
	}
	if (const auto menu = RepairServicesMenu::GetSingleton(); menu->IsVisible())
	{
		menu->Refresh();
		refresh = true;
	}
	return refresh;
}

void Menu::RefreshItemsListQuick()
{
	SafeWriteBuf(0x78319C, "\xE8\x2F\xCE\xFF\xFF\xEB\x70", 7); // InventoryMenu, call SaveCurrentTabScrollPosition and skip reallocating tiles

	SafeWrite16(0x75C3F5, 0); // ContainerMenu, nop JE by changing dest
	SafeWrite16(0x75C443, 0x60EB); // ContainerMenu

	SafeWrite16(0x72DC9C, 0); // BarterMenu
	SafeWrite32(0x72DCD3, 0x0004B2E9); // BarterMenu, jump over code recalculating the selected items for trading

	RefreshItemsList();

	SafeWriteBuf(0x78319C, "\x6A\x00\x6A\x00\x68\x50\x28", 7); // InventoryMenu

	SafeWrite16(0x75C3F5, 0x0182); // ContainerMenu
	SafeWrite16(0x75C443, 0x4D8B); // ContainerMenu

	SafeWrite16(0x72DC9C, 0x01F6);
	SafeWrite32(0x72DCD3, 0x00D1840F); // jump over code recalculating the selected items for trading
}

#include <NiNodes.h>
#include <Utilities.h>

void TextureFormat::InitFromD3DFMT(UInt32 fmt)
{
	typedef void (* _D3DFMTToTextureFormat)(UInt32 d3dfmt, TextureFormat * dst);
	_D3DFMTToTextureFormat D3DFMTToTextureFormat = (_D3DFMTToTextureFormat)0x00E7C1E0;
	
	D3DFMTToTextureFormat(fmt, this);
}

static const UInt32 kNiObjectNET_SetNameAddr = 0x00A5B690;

NiExtraData* __fastcall NiObjectNET::GetExtraData(UInt32 vtbl) const
{
	for (UInt16 index = 0; index < m_extraDataListLen; index++)
	{
		const auto iter = this->m_extraDataList[index];
		if (*(UInt32*)iter == vtbl)
			return iter;
	}
	return nullptr;
}

NiExtraData* NiObjectNET::GetExtraData2(const char* name)
{
	return ThisCall<NiExtraData*>(0x006FF9C0, this, name);
}

bool NiObjectNET::AddExtraData(NiExtraData* xData)
{
	return ThisCall<bool>(0xA5BA40, this, xData);
}

void NiObjectNET::SetName(const char* newName)
{
	// uses cdecl, not stdcall
	_asm
	{
		push newName
		// mov ecx, this (already)
		call kNiObjectNET_SetNameAddr
		add esp, 4
	}
	// OBSE : ThisStdCall(kNiObjectNET_SetNameAddr, this, newName);
}

#include "NiObjects.h"

void NiAVObject::Dump(UInt32 level, const char * indent)
{
	UInt32 childCount = 0;
	char locIndent[257];
	strcpy_s(locIndent, 257, indent);
	if (strlen(indent) < 254)
		strcat_s(locIndent, 257, "  ");
	NiNode* niNode = GetAsNiNode();
	if (niNode)
		childCount = niNode->m_children.Length();
	_MESSAGE("[%0.4d]%s - name: '%s' [%0.8X] has %d children", level, locIndent, m_pcName, niNode, childCount);
	for (UInt32 i = 0; i < childCount; i++)
	{
		NiAVObject* child = niNode->m_children[i];
		child->Dump(level+1, locIndent);
	}
	if (0 == level)
		_MESSAGE("\n");
}

#include <SaveLoadGame.h>

std::string GetSavegamePath()
{
	char path[0x104] = "\0";
	SaveGameManager::GetSingleton()->ConstructSavegamePath(path);
	return path;
}

#include <Script.h>

#include <TESForm.h>
#include <TESObjectREFR.h>
#include <RTTI.h>
#include <CommandTable.h>

UInt32 GetDeclaredVariableType(const char* varName, const char* scriptText)
{
	Tokenizer scriptLines(scriptText, "\n\r");
	std::string curLine;
	while (scriptLines.NextToken(curLine) != -1)
	{
		Tokenizer tokens(curLine.c_str(), " \t\n\r;");
		std::string curToken;

		if (tokens.NextToken(curToken) != -1)
		{
			UInt32 varType = -1;

			// variable declaration?
			if (!StrCompare(curToken.c_str(), "string_var"))
				varType = Script::eVarType_String;
			else if (!StrCompare(curToken.c_str(), "array_var"))
				varType = Script::eVarType_Array;
			else if (!StrCompare(curToken.c_str(), "float"))
				varType = Script::eVarType_Float;
			else if (!StrCompare(curToken.c_str(), "long") || !StrCompare(curToken.c_str(), "int") || !StrCompare(curToken.c_str(), "short"))
				varType = Script::eVarType_Integer;
			else if (!StrCompare(curToken.c_str(), "ref") || !StrCompare(curToken.c_str(), "reference"))
				varType = Script::eVarType_Ref;

			if (varType != -1 && tokens.NextToken(curToken) != -1 && !StrCompare(curToken.c_str(), varName))
			{
				return varType;
			}
		}
	}

	return Script::eVarType_Invalid;
}

Script* GetScriptFromForm(TESForm* form)
{
	if (const auto refr =  DYNAMIC_CAST(form, TESForm, TESObjectREFR))
		form = refr->baseForm;
	const auto scriptable = DYNAMIC_CAST(form, TESForm, TESScriptableForm);
	return scriptable ? scriptable->script : nullptr;
}

enum class ScriptOperatorCode
{
	kOp_LeftBracket = 0x0,
	kOp_RightBracket = 0x1,
	kOp_LogicalAnd = 0x2,
	kOp_LogicalOr = 0x3,
	kOp_LessThanOrEqual = 0x4,
	kOp_LessThan = 0x5,
	kOp_GreaterThanOrEqual = 0x6,
	kOp_GreaterThan = 0x7,
	kOp_Equals = 0x8,
	kOp_NotEquals = 0x9,
	kOp_Minus = 0xA,
	kOp_Plus = 0xB,
	kOp_Multiply = 0xC,
	kOp_Divide = 0xD,
	kOp_Modulo = 0xE,
	kOp_Tilde = 0xF,
	kOp_MAX = 0x10,
};

struct ScriptOperator
{
	ScriptOperatorCode code;
	UInt8 precedence;
	char operatorString[3];
};
//std::span<ActorValueInfo*> g_actorValues = { reinterpret_cast<ActorValueInfo**>(0x11D61C8), kAVCode_Max };

std::span g_eventBlockCommandInfos = { reinterpret_cast<CommandInfo*>(0x118E2F0), 38 };
std::span g_scriptStatementCommandInfos = { reinterpret_cast<CommandInfo*>(0x118CB50), 16 };
std::span g_gameScriptOperators = { reinterpret_cast<ScriptOperator*>(0x118CAD0), 16 };

CommandInfo* GetEventCommandInfo(UInt16 opcode)
{
	if (opcode > 37) return nullptr;
	return &g_eventBlockCommandInfos[opcode];
}

UInt32 Script::GetVariableType(VariableInfo* varInfo)
{
	if (text) return GetDeclaredVariableType(varInfo->name.m_data, text);
	// if it's a ref var a matching varIdx will appear in RefList
	for (RefListEntry* refEntry = &refList; refEntry; refEntry = refEntry->next)
		if (refEntry->var->varIdx == varInfo->idx) return eVarType_Ref;
	return varInfo->type;
}

bool Script::IsUserDefinedFunction() const
{
	auto* scriptData = static_cast<UInt8*>(data);
	return *(scriptData + 8) == 0x0D;
}

UInt32 Script::GetVarCount() const
{
	// info->varCount include index
	auto count = 0U;
	auto* node = &this->varList;
	while (node)
	{
		if (node->data)
			++count;
		node = node->Next();
	}
	return count;
}

UInt32 Script::GetRefCount() const
{
	auto count = 0U;
	auto* node = &this->refList;
	while (node)
	{
		if (node->var)
			++count;
		node = node->Next();
	}
	return count;
}

TList<VariableInfo>* Script::GetVars()
{
	return reinterpret_cast<TList<VariableInfo>*>(&this->varList);
}

TList<Script::RefVariable>* Script::GetRefList()
{
	return reinterpret_cast<TList<RefVariable>*>(&this->refList);
}

#if RUNTIME

Script* Script::CreateScript()
{
	auto* buf = GameHeapAlloc(sizeof Script);
	return ThisStdCall<Script*>(0x5AA0F0, buf);
}

void Script::DeleteScript() const
{
	ThisStdCall(0x5AA170, this, false);
}

ScriptEventList* Script::CreateEventList()
{
	ScriptEventList* result = nullptr;
//	EnterCriticalSection(&csGameScript);
	try
	{
		result = ThisCall<ScriptEventList*>(0x5ABF60, this);	// 4th sub above Script::Execute (was 1st above in Oblivion) Execute is the second to last call in Run
	} catch(...) {}

//	LeaveCriticalSection(&csGameScript);
	return result;
}

#endif

UInt32 ScriptBuffer::GetRefIdx(Script::RefVariable* ref)
{
	UInt32 idx = 0;
	for (Script::RefListEntry* curEntry = &refVars; curEntry && curEntry->var; curEntry = curEntry->next)
	{
		idx++;
		if (ref == curEntry->var) break;
	}
	return idx;
}

UInt32 ScriptBuffer::GetVariableType(VariableInfo* varInfo, Script::RefVariable* refVar)
{
	const char* scrText = scriptText;
	if (refVar)
	{
		if (refVar->form)
		{
			TESScriptableForm* scriptable = NULL;
			switch (refVar->form->typeID)
			{
			case kFormType_TESObjectREFR:
				{
					TESObjectREFR* refr = DYNAMIC_CAST(refVar->form, TESForm, TESObjectREFR);
					scriptable = DYNAMIC_CAST(refr->baseForm, TESForm, TESScriptableForm);
					break;
				}
			case kFormType_TESQuest:
				scriptable = DYNAMIC_CAST(refVar->form, TESForm, TESScriptableForm);
			}

			if (scriptable && scriptable->script)
			{
				if (scriptable->script->text)
					scrText = scriptable->script->text;
				else
					return scriptable->script->GetVariableType(varInfo);
			}
		}
		else			// this is a ref variable, not a literal form - can't look up script vars
			return Script::eVarType_Invalid;
	}

	return GetDeclaredVariableType(varInfo->name.m_data, scrText);
}

/******************************
 Script
******************************/

class ScriptVarFinder
{
public:
	const char* m_varName;
	ScriptVarFinder(const char* varName) : m_varName(varName)
		{	}
	bool Accept(VariableInfo* varInfo)
	{
		//_MESSAGE("  cur var: %s to match: %s", varInfo->name.m_data, m_varName);
		if (!StrCompare(m_varName, varInfo->name.m_data))
			return true;
		return false;
	}
};

VariableInfo* Script::GetVariableByName(const char* varName)
{
	VarListVisitor visitor(&varList);
	const VarInfoEntry* varEntry = visitor.Find(ScriptVarFinder(varName));
	if (varEntry) return varEntry->data;
	return nullptr;
}

Script::RefVariable	* Script::GetRefFromRefList(UInt32 refIdx)
{
	UInt32	idx = 1;	// yes, really starts at 1
	if (refIdx)	for(RefListEntry * entry = &refList; entry; entry = entry->next)
	{
		if(idx == refIdx) return entry->var;
		idx++;
	}
	return nullptr;
}

VariableInfo* Script::GetVariableInfo(UInt32 idx)
{
	for (Script::VarInfoEntry* entry = &varList; entry; entry = entry->next)
		if (entry->data && entry->data->idx == idx)
			return entry->data;

	return NULL;
}

UInt32 Script::AddVariable(TESForm * form)
{
	UInt32		resultIdx = 1;

	RefVariable	* var = (RefVariable*)GameHeapAlloc(sizeof(RefVariable));

	var->name.Set("");
	var->form = form;
	var->varIdx = 0;

	if(!refList.var)
	{
		// adding the first object
		refList.var = var;
		refList.next = NULL;
	}
	else
	{
		resultIdx++;

		// find the last RefListEntry
		RefListEntry	* entry;
		for(entry = &refList; entry->next; entry = entry->next, resultIdx++) ;

		RefListEntry	* newEntry = (RefListEntry *)GameHeapAlloc(sizeof(RefListEntry));

		newEntry->var = var;
		newEntry->next = NULL;

		entry->next = newEntry;
	}

	info.numRefs = resultIdx + 1;

	return resultIdx;
}

void Script::CleanupVariables()
{
	delete refList.var;

	RefListEntry	* entry = refList.next;
	while(entry)
	{
		RefListEntry	* next = entry->next;

		delete entry->var;
		delete entry;

		entry = next;
	}
}

VariableInfo* Script::VarInfoEntry::GetVariableByName(const char* varName)
{
	for (Script::VarInfoEntry* entry = this; entry; entry = entry->next)
	{
		if (entry->data && !StrCompare(entry->data->name.m_data, varName))
			return entry->data;
	}

	return NULL;
}

UInt32 Script::RefListEntry::GetIndex(Script::RefVariable* refVar)
{
	UInt32 idx = 0;
	for (RefListEntry* cur = this; cur; cur = cur->next)
	{
		idx++;
		if (cur->var == refVar)
			return idx;
	}

	return 0;
}

/***********************************
 ScriptLineBuffer
***********************************/

//const char	* ScriptLineBuffer::kDelims_Whitespace = " \t\n\r";
//const char  * ScriptLineBuffer::kDelims_WhitespaceAndBrackets = " \t\n\r[]";

bool ScriptLineBuffer::Write(const void* buf, UInt32 bufsize)
{
	if (dataOffset + bufsize >= kBufferSize)
		return false;

	memcpy(dataBuf + dataOffset, buf, bufsize);
	dataOffset += bufsize;
	return true;
}

bool ScriptLineBuffer::Write32(UInt32 buf)
{
	return Write(&buf, sizeof(UInt32));
}

bool ScriptLineBuffer::WriteString(const char* buf)
{
	UInt32 len = StrLen(buf);
	if ((len < 0x10000) && Write16(len) && len)
		return Write(buf, len);

	return false;
}

bool ScriptLineBuffer::Write16(UInt16 buf)
{
	return Write(&buf, sizeof(UInt16));
}

bool ScriptLineBuffer::WriteByte(UInt8 buf)
{
	return Write(&buf, sizeof(UInt8));
}

ScriptBuffer::ScriptBuffer()
{
	ThisStdCall(0x5AE490, this);
}

ScriptBuffer::~ScriptBuffer()
{
	ThisStdCall(0x5AE5C0, this);
}

bool ScriptLineBuffer::WriteFloat(double buf)
{
	return Write(&buf, sizeof(double));
}


void ScriptEventList::Destructor()
{
	if (m_eventList)
		m_eventList->RemoveAll();
	while (m_vars) {
		if (m_vars->var) GameHeapFree(m_vars->var);
		VarEntry* next = m_vars->next;
		GameHeapFree(m_vars);
		m_vars = next;
	}
}

TList<ScriptEventList::Var>* ScriptEventList::GetVars() const
{
	return reinterpret_cast<TList<Var>*>(m_vars);
}

void ScriptEventList::EventCreate(UInt32 eventCode, TESObjectREFR* container)
{
	// create Event struct
	const auto pEvent = (ScriptEventList::Event*)GameHeapAlloc(sizeof(ScriptEventList::Event));
	if (pEvent) {
		pEvent->eventMask = eventCode;
		pEvent->object = container;
	}

	if (!m_eventList) {
		m_eventList = new EventList{};
	}
	if (m_eventList && pEvent)
		m_eventList->AddAt(pEvent, 0);
}

UInt32 ScriptEventList::ResetAllVariables()
{
	UInt32 numVars = 0;
	for (VarEntry* entry = m_vars; entry; entry = entry->next)
		if (entry->var)
		{
			entry->var->data = 0.0;
			numVars++;
		}
	return numVars;
}

ScriptEventList::Var* ScriptEventList::GetVariable(UInt32 id)
{
	for (VarEntry* entry = m_vars; entry; entry = entry->next)
		if (entry->var && entry->var->id == id) return entry->var;
	return nullptr;
}

ScriptEventList* EventListFromForm(TESForm* form)
{
	if (const auto refr = DYNAMIC_CAST(form, TESForm, TESObjectREFR))
		return refr->GetEventList();
	if (const auto quest = DYNAMIC_CAST(form, TESForm, TESQuest))
		return quest->scriptEventList;
	return nullptr;
}

UInt32 ScriptEventList::Var::GetFormId()
{
	return *(UInt32*)(&data);
}

void ShowCompilerError(ScriptLineBuffer* lineBuf, const char* fmt, ...)
{

	char errorHeader[0x400];
	UInt32 offset = sprintf_s(errorHeader, 0x400, "Error on line %d\n\n", lineBuf->lineNumber);

	va_list	args;
	va_start(args, fmt);

	char	errorMsg[0x200];
	vsprintf_s(errorMsg, 0x200, fmt, args);

	strcat_s(errorHeader, 0x400, errorMsg);
	Log() << errorHeader;

	va_end(args);
}

UInt8* GetScriptDataPosition(Script* script, void* scriptDataIn, const UInt32* opcodeOffsetPtrIn)
{
	if (scriptDataIn != script->data) // set ... to or if ..., script data is stored on stack and not heap
	{
		auto* scriptData = *(static_cast<UInt8**>(scriptDataIn) + 0x1D5);
		return scriptData + *opcodeOffsetPtrIn + 1;
	}
	return static_cast<UInt8*>(scriptDataIn) + *opcodeOffsetPtrIn;
}


const _MarkBaseExtraListScriptEvent MarkBaseExtraListScriptEvent = reinterpret_cast<_MarkBaseExtraListScriptEvent>(0x005AC750);
const _DoCheckScriptRunnerAndRun DoCheckScriptRunnerAndRun = reinterpret_cast<_DoCheckScriptRunnerAndRun>(0x005AC190);

#include "Setting.h"

UInt32 Setting::GetType() const
{
	if (!name) return kSetting_Other;

	switch(name[0]) 
	{
		case 'b': 
		case 'B': return kSetting_Bool;
		case 'c': 
		case 'C': return kSetting_Char;
		case 'i': 
		case 'I': return kSetting_Integer;
		case 'u': 
		case 'U': return kSetting_Unsigned;
		case 'f': 
		case 'F': return kSetting_Float;
		case 's':
		case 'S': return kSetting_String;
		case 'r': 
		case 'R': return kSetting_r;
		case 'a': 
		case 'A': return kSetting_a;
		default: return kSetting_Other;
	}
}

Float32 Setting::GetAsFloat() const
{
	switch (GetType())
	{
	case kSetting_Bool:
	case kSetting_Integer: return data.i;
	case kSetting_Unsigned: return data.uint;
	case kSetting_Float: return data.f;
	default:
		return false;
	}
}

std::string Setting::GetAsString() const
{
	if (GetType() == kSetting_String) return data.str;
	return "";
}

bool Setting::Set(double newVal)
{
	switch (GetType())
	{
	case kSetting_Bool:
		data.i = newVal ? 1 : 0;
		return true;
	case kSetting_Integer:
		data.i = newVal;
		return true;
	case kSetting_Unsigned:
		data.uint = newVal;
		return true;
	case kSetting_Float:
		data.f = newVal;
		return true;
	default:
		return false;
	}
}

bool Setting::Set(const char* str)
{
	if (GetType() == kSetting_String)
	{
		char * newVal = static_cast<char*>(GameHeapAlloc(strlen(str) + 1));
		if (!strcpy_s(newVal, strlen(str)+1, str)) {
			data.str = newVal;
			return true;
		}
	}
	return false;
}

GameSettingCollection * GameSettingCollection::GetSingleton()
{
	return *(GameSettingCollection**)0x011C8048;
}

INISettingCollection* INISettingCollection::GetSingleton()
{
	return *(INISettingCollection**)0x011F96A0;
}

INIPrefSettingCollection* INIPrefSettingCollection::GetSingleton()
{
	return *(INIPrefSettingCollection**)0x011F35A0;
}

class IniSettingFinder
{
public:
	const char* m_settingName;
	IniSettingFinder(const char* name) : m_settingName(name)
		{	}
	bool Accept(Setting* info)
	{
		return !StrCompare(m_settingName, info->name);
	}
};

Setting* GetINISetting(const std::string& settingName)
{
	Setting* setting = nullptr;
	IniSettingFinder finder(settingName.c_str());

	// check prefs first
	const auto coll = INIPrefSettingCollection::GetSingleton();
	if (coll) setting = coll->settingList.Find(finder);

	if (!setting)
	{
		const auto coll = INISettingCollection::GetSingleton();
		if (coll) setting = coll->settingList.Find(finder);
	}

	return setting;
}

Setting* GetGameSetting(const std::string& settingName)
{
	for (const auto iter : GameSettingCollection::GetSingleton()->settingMap)
		if (std::string(iter->key) == settingName) return iter->data;
	return nullptr;
}

#include <Sound.h>
#include <NiObjects.h>
#include <TESObjectREFR.h>


void Sound::PlayEDID(const char* soundEDID, UInt32 flags, TESObjectREFR* refr)
{
	Sound sound;
	ThisCall(0xAD7550, BSWin32Audio::GetSingleton(), &sound, soundEDID, flags);
	if (sound.soundKey != 0xFFFFFFFF)
	{
		sound.SetPos(refr->PosVector());
		sound.Play();
	}
}

void Sound::PlayFile(const char* filePath, UInt32 flags, TESObjectREFR* refr)
{
	NiNode* refrNode = refr->GetNiNode();
	if (!refrNode) return;
	Sound sound;
	ThisCall(0xAD7480, BSWin32Audio::GetSingleton(), &sound, filePath, flags, nullptr);
	if (sound.soundKey != 0xFFFFFFFF)
	{
		sound.SetPos(refrNode->m_worldTransform.pos);
		sound.SetNiNode(refrNode);
		sound.Play();
	}
}

void Sound::PlayTESSound(TESSound* gameSound, UInt32 flags, TESObjectREFR* refr)
{
	const char* filePath = gameSound->soundFile.path.m_data;
	if (!filePath) return;
	NiNode* refrNode = refr->GetNiNode();
	if (!refrNode) return;
	Sound sound;
	ThisCall(0xAD7480, BSWin32Audio::GetSingleton(), &sound, filePath, flags, gameSound);
	if (sound.soundKey != 0xFFFFFFFF)
	{
		sound.SetPos(refrNode->m_worldTransform.pos);
		sound.SetNiNode(refrNode);
		sound.Play();
	}
}

void PlayGameSound(const char* soundPath)
{
	Sound sound(soundPath, 0x121);
	sound.Play();
}

namespace Radio
{
	TESObjectREFR* GetCurrentStation()
	{
		TESObjectREFR* station = nullptr;
		if (RadioEntry::GetSingleton())
		{
			station = RadioEntry::GetSingleton()->radioRef;
		}

		return station;
	}
	
	void GetNearbyStations(TList<TESObjectREFR>* dst)
	{
		CdeclCall(0x4FF1A0, PlayerCharacter::GetSingleton(), dst, nullptr);
	}

	TList<TESObjectREFR>* GetFoundStations() { return reinterpret_cast<TList<TESObjectREFR>*>(0x11DD59C); };
	bool GetEnabled() { return *reinterpret_cast<UInt8*>(0x11DD434); }
	void SetActiveStation(TESObjectREFR* station)
	{
		if (GetEnabled())
		{
			// stops the current playing dialogue line
			SetEnabled(false);
		}

		SetEnabled(true);

		SetStation(station, true);
	}
}

void Sound::Set3D(Actor* actor)
{
	if (!actor)
		return;
	auto* pos = actor->GetPos();
	auto* node = actor->GetNiNode();
	if (pos && node)
	{
		ThisStdCall(0xAD8B60, this, pos->x, pos->y, pos->z);
		ThisStdCall(0xAD8F20, this, node);
	}
}
#include <TESForm.h>
#include <TESObject.h>
#include <TESObjectREFR.h>

#include "Script.h"
#include "RTTI.h"
#include "GameData.h"
#include "SaveLoadGame.h"


TESForm* CreateFormInstance(const UInt8 type) { return CdeclCall<TESForm*>(0x00465110, type); }

static const ActorValueInfo** ActorValueInfoPointerArray = (const ActorValueInfo**)0x0011D61C8;		// See GetActorValueInfo
static const _GetActorValueInfo GetActorValueInfo = (_GetActorValueInfo)0x00066E920;	// See GetActorValueName
BGSDefaultObjectManager ** g_defaultObjectManager = (BGSDefaultObjectManager**)0x011CA80C;

TESForm* TESForm::TryGetREFRParent() const
{
	auto result = this;
	if (const auto refr = DYNAMIC_CAST(this, TESForm, TESObjectREFR); refr && refr->baseForm)
		result = refr->baseForm;
	return const_cast<TESForm*>(result);
}

TESFullName* TESForm::GetFullName()
{
	if (typeID == kFormType_TESObjectCELL)		// some exterior cells inherit name of parent worldspace
	{
		const auto cell = reinterpret_cast<TESObjectCELL*>(this);
		TESFullName *fullName = &cell->fullName;
		return fullName->name.m_data && fullName->name.m_dataLen || !cell->worldSpace ? fullName : &cell->worldSpace->fullName;
	}
	const TESForm *baseForm = GetIsReference() ? reinterpret_cast<TESObjectREFR*>(this)->baseForm : this;
	return DYNAMIC_CAST(baseForm, TESForm, TESFullName);
}

const char* TESForm::GetTheName()
{
	if (GetIsReference())
	{
		const auto name = reinterpret_cast<TESObjectREFR*>(this)->GetJIPName();
		if (name && name[0]) return name;
	}
	const auto fullName = GetFullName();
	return fullName ? fullName->name.CStr() : "";
}

Script* TESForm::GetScript()
{
	const auto scriptForm = DYNAMIC_CAST(this, TESForm, TESScriptableForm);
	Script* script = nullptr;
	if (scriptForm) // Let's try for a MGEF
		script = scriptForm ? scriptForm->script : nullptr;
	else if (const auto effect = DYNAMIC_CAST(this, TESForm, EffectSetting))
		script = effect->GetScript();
	return script;
}

void TESForm::DoAddForm(TESForm* newForm, bool persist, bool record)
{
	TESDataHandler::GetSingleton()->DoAddForm(newForm);

	if (persist)
	{
		// Only some forms can be safely saved as SaveForm. ie TESPackage at the moment.
		bool canSave = false;
		const auto package = DYNAMIC_CAST(newForm, TESForm, TESPackage);
		if (package)
			canSave = true;
		// ... more ?

		if (canSave)
			TESSaveLoadGame::Get()->AddCreatedForm(newForm);
	}
}

TESForm* TESForm::CloneForm(bool persist) const
{
	TESForm* result = CreateFormInstance(typeID);
	if (result)
	{
		result->CopyFrom(this);
		// it looks like some fields are not copied, case in point: TESObjectCONT does not copy BoundObject information.
		const auto boundObject = DYNAMIC_CAST(result, TESForm, TESBoundObject);
		if (boundObject)
		{
			const auto boundSource = DYNAMIC_CAST(this, TESForm, TESBoundObject);
			if (boundSource)
			{
				for (UInt8 i = 0; i < 6; i++)
					boundObject->bounds[i] = boundSource->bounds[i];
			}
		}
		DoAddForm(result, persist);
	}

	return result;
}

class FindByForm {
	TESForm* m_pForm;
public:
	FindByForm(TESForm* pForm) : m_pForm(pForm) {}
	bool Accept(TESForm* pForm) const {
		return pForm && (pForm->refID == m_pForm->refID) ? true : false;
	}
};

SInt32 BGSListForm::GetIndexOf(TESForm* pForm)
{
	return list.GetIndexOf(FindByForm(pForm));
}

SInt32 BGSListForm::RemoveForm(TESForm* pForm)
{
	const SInt32 index = GetIndexOf(pForm);
	if (index >= 0) RemoveNthForm(index);
	return index;
}

SInt32 BGSListForm::ReplaceForm(TESForm* pForm, TESForm* pReplaceWith)
{
	const SInt32 index = GetIndexOf(pForm);
	if (index >= 0) list.ReplaceNth(index, pReplaceWith);
	return index;
}

bool BGSListForm::Contains(TESForm* form)
{
	if (!form) return false;
	for (const auto iter : list) if (iter->refID == form->refID) return true;
	return false;
}

bool BGSListForm::ContainsRecursive(TESForm* form, UInt32 reclvl)
{
	if (!form) return false;
	if (this == form) return true;
	if (reclvl > 100) return false; [[unlikely]]
	for (const auto iter : list)
		if (iter->typeID == kFormType_BGSListForm)
			if (reinterpret_cast<BGSListForm*>(iter)->ContainsRecursive(form, reclvl++)) return true;
	return false;
}

bool FormContainsRecusive(TESForm* parent, TESForm* child)
{
	if (!parent || !child) return false;
	if (parent->refID == child->refID) return true;
	if (parent->typeID == kFormType_BGSListForm)
		if (reinterpret_cast<BGSListForm*>(parent)->ContainsRecursive(child)) return true;
	return false;
}

bool TESForm::IsItemPlayable()
{
	if (this->typeID == kFormType_TESObjectWEAP && reinterpret_cast<TESObjectWEAP*>(this)->weaponFlags1 & 0x80) return false;
	if (this->typeID == kFormType_TESObjectARMO && reinterpret_cast<TESObjectARMO*>(this)->bipedModel.bipedFlags & 0x40) return false;
	if (this->typeID == kFormType_TESAmmo && reinterpret_cast<TESAmmo*>(this)->flags & 0x2) return false;
	return true;
}

bool TESForm::IsInventoryObjectAlt()
{
	switch (this->typeID)
	{
	case kFormType_TESObjectARMO:
	case kFormType_TESObjectBOOK:
	case kFormType_TESObjectCLOT:
	case kFormType_IngredientItem:
	case kFormType_TESObjectMISC:
	case kFormType_TESObjectWEAP:
	case kFormType_TESAmmo:
	case kFormType_TESKey:
	case kFormType_AlchemyItem:
	case kFormType_BGSNote:
	case kFormType_TESObjectARMA:
	case kFormType_TESObjectIMOD:
	case kFormType_TESCasinoChips:
	case kFormType_TESCaravanCard:
	case kFormType_TESCaravanMoney:
		return true;
	case kFormType_TESObjectLIGH:
		if (const auto light = DYNAMIC_CAST(this, TESForm, TESObjectLIGH))
			if (light->lightFlags & 2)
				return true;
	[[fallthrough]];
	default: return false;
	}
}

extern TESDataHandler* g_TESDataHandler;

TESForm* TESForm::GetByID(const char* mod, UInt32 refID)
{
	if (const auto modInfo = g_TESDataHandler->LookupModByName(mod))
		return GetByID((modInfo->modIndex << 24) + (refID & 0x00FFFFFF));
	return nullptr;
}

TESForm* TESForm::GetByID(const char* mod, const char* refID)
{
	if (const auto modInfo = g_TESDataHandler->LookupModByName(mod))
		return GetByID((modInfo->modIndex << 24) + (HexStringToInt(refID) & 0x00FFFFFF));
	return nullptr;
}

const char* TESPackage::TargetData::StringForTargetCode(UInt8 targetCode)
{
	switch (targetCode)	{
	case kTargetType_Refr:			return "Reference";
	case kTargetType_BaseObject:	return "Object";
	case kTargetType_TypeCode:		return "ObjectType";
	default:						return nullptr;
	}
}

UInt8 TESPackage::TargetData::TargetCodeForString(const char* targetStr)
{
	if (!_stricmp(targetStr, "REFERENCE"))
		return kTargetType_Refr;
	if (!_stricmp(targetStr, "OBJECT"))
		return kTargetType_BaseObject;
	if (!_stricmp(targetStr, "OBJECTTYPE"))
		return kTargetType_TypeCode;
	return 0xFF;
}

TESPackage::TargetData* TESPackage::TargetData::Create()
{
	const auto data = (TargetData*)GameHeapAlloc(sizeof(TargetData));

	// fill out with same defaults as editor uses
	data->count = 0;
	data->target.objectCode = kObjectType_Activators;
	data->targetType = kTargetType_TypeCode;

	return data;
}

TESPackage::TargetData* TESPackage::GetTargetData()
{
	if (!target) target = TargetData::Create();
	return target;
}

void TESPackage::SetTarget(TESObjectREFR* refr)
{
	TargetData* tdata = GetTargetData();
	tdata->targetType = kTargetType_Refr;
	tdata->target.refr = refr;
	tdata->count = 150;	//DefaultDistance
}

void TESPackage::SetCount(UInt32 aCount)
{
	if (target) {
		TargetData* tdata = GetTargetData();
		tdata->count = aCount;
	}
}

void TESPackage::SetTarget(TESForm* baseForm, UInt32 count)
{
	TargetData* tdata = GetTargetData();
	tdata->targetType = kTargetType_BaseObject;
	tdata->count = count;
	tdata->target.form = baseForm;
}

void TESPackage::SetTarget(eObjectType typeCode, UInt32 count)
{
	if (typeCode > 0 && typeCode < kObjectType_Max)
	{
		TargetData* tdata = GetTargetData();
		tdata->targetType = kTargetType_TypeCode;
		tdata->target.objectCode = typeCode;
		tdata->count= count;
	}
}

TESPackage::LocationData* TESPackage::LocationData::Create()
{
	const auto data = (LocationData*)GameHeapAlloc(sizeof(LocationData));

	data->locationType = kPackLocation_CurrentLocation;
	data->object.form = nullptr;
	data->radius = 0;

	return data;
}

TESPackage::LocationData* TESPackage::GetLocationData()
{
	if (!location) location = LocationData::Create();
	return location;
}

bool TESPackage::IsFlagSet(UInt32 flag)
{
	return packageFlags & flag;
}

void TESPackage::SetFlag(UInt32 flag, bool bSet)
{
	bSet ? packageFlags |= flag : packageFlags &= ~flag;

	// handle either-or flags
	switch (flag)
	{
	case kPackageFlag_LockDoorsAtStart:
		if (IsFlagSet(kPackageFlag_UnlockDoorsAtStart) == bSet)
			SetFlag(kPackageFlag_UnlockDoorsAtStart, !bSet);
		break;
	case kPackageFlag_UnlockDoorsAtStart:
		if (IsFlagSet(kPackageFlag_LockDoorsAtStart) == bSet)
			SetFlag(kPackageFlag_LockDoorsAtStart, !bSet);
		break;
	case kPackageFlag_LockDoorsAtEnd:
		if (IsFlagSet(kPackageFlag_UnlockDoorsAtEnd) == bSet)
			SetFlag(kPackageFlag_UnlockDoorsAtEnd, !bSet);
		break;
	case kPackageFlag_UnlockDoorsAtEnd:
		if (IsFlagSet(kPackageFlag_LockDoorsAtEnd) == bSet)
			SetFlag(kPackageFlag_LockDoorsAtEnd, !bSet);
		break;
	case kPackageFlag_LockDoorsAtLocation:
		if (IsFlagSet(kPackageFlag_UnlockDoorsAtLocation) == bSet)
			SetFlag(kPackageFlag_UnlockDoorsAtLocation, !bSet);
		break;
	case kPackageFlag_UnlockDoorsAtLocation:
		if (IsFlagSet(kPackageFlag_LockDoorsAtLocation) == bSet)
			SetFlag(kPackageFlag_LockDoorsAtLocation, !bSet);
		break;
	}
}

static const char* TESPackage_ObjectTypeStrings[TESPackage::kObjectType_Max] =
{
	"NONE", "Activators", "Armors", "Books", "Clothing", "Containers", "Doors", "Ingredients", "Lights", "Miscellaneous", "Flora", "Furniture",
	"Weapons: Any", "Ammo", "NPCs", "Creatures", "Keys", "Alchemy", "Food", "All: Combat Wearable", "All: Wearable", "Weapons: Ranged", "Weapons: Melee",
	"Weapons: NONE", "Actor Effects: Any", "Actor Effects: Range Target", "Actor Effects: Range Touch", "Actor Effects: Range Self"
};

// add 1 to code before indexing
static const char* TESPackage_DayStrings[] = {
	"Any", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Weekdays", "Weekends", "MWF", "TT"
};

// add 1
static const char* TESPackage_MonthString[] = {
	"Any", "January", "February", "March", "April", "May", "June", "July", "August", "September",
	"October", "November", "December", "Spring", "Summer", "Autumn", "Winter"
};

static const char* TESPackage_LocationStrings[] = {
	"Reference", "Cell", "Current", "Editor", "Object", "ObjectType"
};

static const char* TESPackage_TypeStrings[TESPackage::kPackageType_Max] = {
	"Find", "Follow", "Escort", "Eat", "Sleep", "Wander", "Travel", "Accompany", "UseItemAt", "Ambush",
	"FleeNotCombat", "Sandbox", "Patrol", "Guard", "Dialogue", "UseWeapon"
};

static const char* TESPackage_ProcedureStrings[TESPackage::kProcedure_Max] = {
	"TRAVEL", "ACTIVATE", "ACQUIRE", "WAIT", "DIALOGUE", "GREET", "GREET DEAD", "WANDER", "SLEEP", 
	"OBSERVE COMBAT", "EAT", "FOLLOW", "ESCORT", "COMBAT", "ALARM", "PURSUE", "FLEE", "DONE", "YELD", 
	"TRAVEL TARGET", "CREATE FOLLOW", "GET UP", "MOUNT HORSE", "DISMOUNT HORSE", "DO NOTHING", "UNKNOWN 019", "UNKNOWN 01A",
	"ACCOMPANY", "USE ITEM AT", "AIM", "NOTIFY", "SANDMAN", "WAIT AMBUSH", "SURFACE", "WAIT FOR SPELL", "CHOOSE CAST", 
	"FLEE NON COMBAT", "REMOVE WORN ITEMS", "SEARCH", "CLEAR MOUNT POSITION", "SUMMON CREATURE DEFEND", "AVOID AREA", 
	"UNEQUIP ARMOR", "PATROL", "USE WEAPON", "DIALOGUE ACTIVATE", "GUARD", "SANDBOX", "USE IDLE MARKER", "TAKE BACK ITEM", 
	"SITTING", "MOVEMENT BLOCKED", "CANIBAL FEED", 
};

const char* TESPackage::StringForPackageType(const ePackageType pkgType)
{
	return pkgType >= kPackageType_Min && pkgType < kPackageType_Max ? TESPackage_TypeStrings[pkgType] : "";
}

const char* TESPackage::StringForObjectCode(const eObjectType objCode)
{
	return objCode >= kObjectType_Min && objCode < kObjectType_Max ? TESPackage_ObjectTypeStrings[objCode] : "";
}

UInt8 TESPackage::ObjectCodeForString(const char* objString)
{
	for (UInt32 i = 0; i < kObjectType_Max; i++) {
		if (!_stricmp(objString, TESPackage_ObjectTypeStrings[i]))
			return i;
	}

	return kObjectType_Max;
}

static const char** s_procNames = reinterpret_cast<const char**>(0x011A3CC0);

const char* TESPackage::StringForProcedureCode(const eProcedure proc)
{
	return proc >= kProcedure_Min && proc < kProcedure_Max ? TESPackage_ProcedureStrings[proc] : "";
}

const char* TESPackage::StringForProcedureCode(eProcedure proc, bool bRemovePrefix)
{
	static size_t prefixLen = strlen("PROCEDURE_");
	const char* name;
	// special-case "AQUIRE" (sic) to fix typo in game executable
	if (proc == kProcedure_ACQUIRE)
		name = "PROCEDURE_ACQUIRE";
	else
		name = proc >= kProcedure_Min && proc < kProcedure_Max ? s_procNames[proc] : nullptr;

	if (name && bRemovePrefix) name += prefixLen;

	return name;
}

const char* TESPackage::PackageTime::DayForCode(UInt8 dayCode)
{
	return (dayCode + 1 < sizeof TESPackage_DayStrings) ? TESPackage_DayStrings[dayCode] : "";
}

BGSQuestObjective* TESQuest::GetObjective(UInt32 objectiveID) const
{
	auto iter = lVarOrObjectives.Head();
	do
	{
		const auto objective = (BGSQuestObjective*)iter->data;
		if (objective && IS_TYPE(objective, BGSQuestObjective) && (objective->objectiveId == objectiveID))
			return objective;
	} while (iter = iter->next);
	return NULL;
}

const char* TESPackage::PackageTime::MonthForCode(UInt8 monthCode)
{
	return (monthCode + 1 < sizeof TESPackage_MonthString) ? TESPackage_MonthString[monthCode] : "";
}

UInt8 TESPackage::PackageTime::CodeForDay(const char* dayStr)
{
	for (UInt8 i = 0; i < sizeof(TESPackage_DayStrings); i++)
		if (!_stricmp(dayStr, TESPackage_DayStrings[i])) return i-1;
	return kWeekday_Any;
}

UInt8 TESPackage::PackageTime::CodeForMonth(const char* monthStr)
{
	for (UInt8 i = 0; i < sizeof(TESPackage_MonthString); i++)
		if (!_stricmp(monthStr, TESPackage_MonthString[i]))	return i-1;
	return kMonth_Any;
}

const char* TESPackage::LocationData::StringForLocationCode(const ePackageLocation locCode)
{
	return locCode >= kPackLocation_Min && locCode < kPackLocation_Max ? TESPackage_LocationStrings[locCode] : "";
}

const char* TESPackage::LocationData::StringForLocationCodeAndData()
{
#define resultSize 256
	static char result[resultSize];
	if (locationType < kPackLocation_Max) {
		switch (locationType) { 
			case kPackLocation_NearReference:
			case kPackLocation_InCell:
			case kPackLocation_ObjectID:
				if (object.form)
					sprintf_s(result, resultSize, "%s \"%s\" [%08X] with a radius of %u", TESPackage_LocationStrings[locationType], object.form->GetTheName(), 
						object.form->refID, radius);
				else
					sprintf_s(result, resultSize, "%s \"\" [%08X] with a radius of %u", TESPackage_LocationStrings[locationType], 0, radius);
				break;
			case kPackLocation_ObjectType:
				sprintf_s(result, resultSize, "%s \"%s\" [%04X] with a radius of %u", TESPackage_LocationStrings[locationType], StringForObjectCode(object.objectCode),
					object.objectCode, radius);
				break;
			default:
				sprintf_s(result, resultSize, "%s with a radius of %u", TESPackage_LocationStrings[locationType], radius);
				break;
		}
		return result;
	}
	return "";
}

const char* TESPackage::TargetData::StringForTargetCodeAndData()
{
#define resultSize 256
	static char result[resultSize];
	if (targetType < kTargetType_Max) {
		switch (targetType) { 
			case kTargetType_Refr:
				if (target.refr)
					sprintf_s(result, resultSize, "%s \"%s\" [%08X] with a distance of %u", StringForTargetCode(targetType), target.refr->GetTheName(),
						target.refr->refID, count);
				else
					sprintf_s(result, resultSize, "%s [%08X] with a distance of %u", StringForTargetCode(targetType), 0, count);
				break;
			case kTargetType_BaseObject:
				if (target.form)
					sprintf_s(result, resultSize, "%s \"%s\" [%08X] with a count of %u", StringForTargetCode(targetType), target.form->GetTheName(), target.form->refID, count);
				else
					sprintf_s(result, resultSize, "%s [%08X] with a count of %u", StringForTargetCode(targetType), 0, count);
				break;
			case kTargetType_TypeCode:
				sprintf_s(result, resultSize, "%s \"%s\" [%04X] with a radius of %u", StringForTargetCode(targetType), StringForObjectCode(target.objectCode),
						target.objectCode, count);
				break;
			default:
				sprintf_s(result, resultSize, "%s with a radius of %u", StringForTargetCode(targetType), count);
				break;
		}
		return result;
	}
	return "";
}

UInt8 TESPackage::LocationData::LocationCodeForString(const char* locStr)
{
	for (UInt32 i = 0; i < kPackLocation_Max; i++)
		if (!_stricmp(locStr, TESPackage_LocationStrings[i]))
			return i;
	return kPackLocation_Max;
}

const char* TESFaction::GetNthRankName(const UInt32 whichRank, const bool bFemale)
{
	Rank* rank = ranks.GetNth(whichRank);
	return rank ? bFemale ? rank->femaleName.CStr() : rank->name.CStr() : nullptr;
}

void TESFaction::SetNthRankName(const char* newName, const UInt32 whichRank, const bool bFemale)
{
	Rank* rank = ranks.GetNth(whichRank);
	if (rank) (bFemale ? rank->femaleName : rank->name).Set(newName);
}

UInt32 EffectItemList::CountItems() const
{
	return list.count();
}

EffectItem* EffectItemList::ItemAt(const UInt32 whichItem)
{
	return list.GetNth(whichItem);
}

const char* EffectItemList::GetNthEIName(const UInt32 whichEffect) const
{
	const EffectItem* effItem = list.GetNth(whichEffect);
	return effItem->setting ? effItem->setting->GetFullName()->name.CStr() : "<no name>";
}

BGSDefaultObjectManager* BGSDefaultObjectManager::GetSingleton()
{
	return *g_defaultObjectManager;
}

Script* EffectSetting::SetScript(Script* newScript)
{
	Script* oldScript = nullptr;
	if (1 == archtype )
	{
		oldScript = DYNAMIC_CAST(associatedItem, TESForm, Script);
		associatedItem = newScript;
	}
	return oldScript;
};

Script* EffectSetting::	RemoveScript()
{
	return SetScript(nullptr);
};
#include <TESObject.h>

#include "RTTI.h"
#include "TESObjectREFR.h"

static constexpr UInt8 kHandGripTable[] =
{
	TESObjectWEAP::eHandGrip_Default,
	TESObjectWEAP::eHandGrip_1,
	TESObjectWEAP::eHandGrip_2,
	TESObjectWEAP::eHandGrip_3,
	TESObjectWEAP::eHandGrip_4,
	TESObjectWEAP::eHandGrip_5,
	TESObjectWEAP::eHandGrip_6,
};

bool TESObjectWEAP::IsMeleeWeapon() const
{
	return eWeaponType >= 0 && eWeaponType <= 2;
}

float TESObjectWEAP::GetModBonuses(UInt32 effectID)
{
	float result = 0;
	for (UInt32 idx = 0; idx < 3; idx++) if (effectMods[idx] == effectID) result += value1Mod[idx];
	return result;
}

UInt8 TESObjectWEAP::HandGrip() const
{
	for (UInt32 i = 0; i < std::size(kHandGripTable); i++) if (handGrip == kHandGripTable[i]) return i;
	return 0;
}

void TESObjectWEAP::SetHandGrip(UInt8 _handGrip)
{
	if (_handGrip < std::size(kHandGripTable)) handGrip = kHandGripTable[_handGrip];
}

UInt8 TESObjectWEAP::AttackAnimation() const
{
	switch (attackAnim) {
	case eAttackAnim_Default:		return 0;
	case eAttackAnim_Attack3:		return 1;
	case eAttackAnim_Attack4:		return 2;
	case eAttackAnim_Attack5:		return 3;
	case eAttackAnim_Attack6:		return 4;
	case eAttackAnim_Attack7:		return 5;
	case eAttackAnim_Attack8:		return 6;
	case eAttackAnim_AttackLeft:	return 7;
	case eAttackAnim_AttackLoop:	return 8;
	case eAttackAnim_AttackRight:	return 9;
	case eAttackAnim_AttackSpin:	return 10;
	case eAttackAnim_AttackSpin2:	return 11;
	case eAttackAnim_AttackThrow:	return 12;
	case eAttackAnim_AttackThrow2:	return 13;
	case eAttackAnim_AttackThrow3:	return 14;
	case eAttackAnim_AttackThrow4:	return 15;
	case eAttackAnim_AttackThrow5:	return 16;
	case eAttackAnim_PlaceMine:		return 17;
	case eAttackAnim_PlaceMine2:	return 18;
	default:						return -1;
	}
}

void TESObjectWEAP::SetAttackAnimation(UInt8 _attackAnim)
{
	switch (_attackAnim) {
	case 0: {
		attackAnim = eAttackAnim_Default;
		break;
	}
	case 1: {
		attackAnim = eAttackAnim_Attack3;
		break;
	}
	case 2: {
		attackAnim = eAttackAnim_Attack4;
		break;
	}
	case 3: {
		attackAnim = eAttackAnim_Attack5;
		break;
	}
	case 4: {
		attackAnim = eAttackAnim_Attack6;
		break;
	}
	case 5: {
		attackAnim = eAttackAnim_Attack7;
		break;
	}
	case 6: {
		attackAnim = eAttackAnim_Attack8;
		break;
	}

	case 7: {
		attackAnim = eAttackAnim_AttackLeft;
		break;
	}
	case 8: {
		attackAnim = eAttackAnim_AttackLoop;
		break;
	}
	case 9: {
		attackAnim = eAttackAnim_AttackRight;
		break;
	}
	case 10: {
		attackAnim = eAttackAnim_AttackSpin;
		break;
	}
	case 11: {
		attackAnim = eAttackAnim_AttackSpin2;
		break;
	}
	case 12: {
		attackAnim = eAttackAnim_AttackThrow;
		break;
	}
	case 13: {
		attackAnim = eAttackAnim_AttackThrow2;
		break;
	}
	case 14: {
		attackAnim = eAttackAnim_AttackThrow3;
		break;
	}
	case 15: {
		attackAnim = eAttackAnim_AttackThrow4;
		break;
	}
	case 16: {
		attackAnim = eAttackAnim_AttackThrow5;
		break;
	}
	case 17: {
		attackAnim = eAttackAnim_PlaceMine;
		break;
	}
	case 18: {
		attackAnim = eAttackAnim_PlaceMine2;
		break;
	}
	default:
		break;
	}
}

TESObjectIMOD* TESObjectWEAP::GetItemMod(UInt8 which)
{
	TESObjectIMOD* pMod = nullptr;
	switch (which) {
	case 1: pMod = itemMod1; break;
	case 2: pMod = itemMod2; break;
	case 3: pMod = itemMod3; break;
	default: break;
	}
	return pMod;
}

Float32 TESObjectWEAP::GetEffectModValue(kWeaponModEffects value, UInt8 second)
{
	if (value == GetItemModEffect(1)) return second ? GetItemModValue2(1) : GetItemModValue1(1);
	if (value == GetItemModEffect(2)) return second ? GetItemModValue2(2) : GetItemModValue1(2);
	if (value == GetItemModEffect(3)) return second ? GetItemModValue2(3) : GetItemModValue1(3);
	return -1;
}

bool TESObjectWEAP::IsMeleeWeapon()
{
	return eWeaponType == kWeapType_HandToHandMelee || eWeaponType == kWeapType_OneHandMelee || eWeaponType == kWeapType_TwoHandMelee;
}

bool TESObjectWEAP::IsRangedWeapon()
{
	return (this->projectile);
}


float TESObjectWEAP::GetWeaponValue(UInt32 whichVal)
{
	if (!this) return false;
	switch (whichVal) {
	case eWeap_Type:				return eWeaponType;
	case eWeap_MinSpread:			return minSpread;
	case eWeap_Spread:				return spread;
	case eWeap_Proj:				return projectile ? projectile->refID : false;
	case eWeap_SightFOV:			return sightFOV;
	case eWeap_MinRange:			return minRange;
	case eWeap_Range:				return maxRange;
	case eWeap_AmmoUse:				return ammoUse;
	case eWeap_APCost:				return AP;
	case eWeap_CritDam:				return criticalDamage;
	case eWeap_CritChance:			return criticalPercent;
	case eWeap_CritEffect:			return criticalEffect ? criticalEffect->refID : false;
	case eWeap_FireRate:			return fireRate;
	case eWeap_AnimAttackMult:		return animAttackMult;
	case eWeap_RumbleLeft:			return rumbleLeftMotor;
	case eWeap_RumbleRight:			return rumbleRightMotor;
	case eWeap_RumbleDuration:		return rumbleDuration;
	case eWeap_RumbleWaveLength:	return rumbleWavelength;
	case eWeap_AnimShotsPerSec:		return animShotsPerSec;
	case eWeap_AnimReloadTime:		return animReloadTime;
	case eWeap_AnimJamTime:			return animJamTime;
	case eWeap_Skill:				return weaponSkill;
	case eWeap_ResistType:			return resistType;
	case eWeap_FireDelayMin:		return semiAutoFireDelayMin;
	case eWeap_FireDelayMax:		return semiAutoFireDelayMax;
	case eWeap_AnimMult:			return animMult;
	case eWeap_Reach:				return reach;
	case eWeap_IsAutomatic:			return IsAutomatic();
	case eWeap_HandGrip:			return HandGrip();
	case eWeap_ReloadAnim:			return reloadAnim;
	case eWeap_VATSChance:			return baseVATSChance;
	case eWeap_AttackAnim:			return AttackAnimation();
	case eWeap_NumProj:				return numProjectiles;
	case eWeap_AimArc:				return aimArc;
	case eWeap_LimbDamageMult:		return limbDamageMult;
	case eWeap_SightUsage:			return sightUsage;
	case eWeap_ReqStr:				return strRequired;
	case eWeap_ReqSkill:			return skillRequirement;
	case eWeap_LongBursts:			return weaponFlags2 & (eFlag_LongBurst);
	case eWeap_Flags1:				return weaponFlags1;
	case eWeap_Flags2:				return weaponFlags2;
	case eWeap_HasScope:			return HasScope();
	case eWeap_IgnoresDTDR:			return IgnoresDTDR();
	case eWeap_SoundLevel:			return soundLevel;
	case eWeap_ClipSize:
	{
		if (const auto pClipRounds = DYNAMIC_CAST(this, TESForm, BGSClipRoundsForm); pClipRounds) return pClipRounds->clipRounds;
		break;
	}
	default: throw std::out_of_range("unknown weapon value");
	}
	return false;
}

UInt32 TESObjectARMO::GetArmorValue(UInt32 whichVal)
{
	if (!this) return false;
	switch (whichVal) {
	case 1:	return bipedModel.bipedFlags & eBipedFlag_HeavyArmor ? 3 : bipedModel.bipedFlags & eBipedFlag_MediumArmor ? 2 : 1;
	case 2:	return bipedModel.bipedFlags & eBipedFlag_PowerArmor ? 1 : 0;
	case 3:	return bipedModel.bipedFlags & eBipedFlag_HasBackPack ? 1 : 0;
	case 4:	return armorRating;
	case 5:	return static_cast<UInt32>(damageThreshold);
	case 6: return bipedModel.partMask;
	default: throw std::out_of_range("unknown armor value");
	}
	return false;
}

UInt32 AlchemyItem::HasBaseEffectRestoresAV(const SInt32 avCode)
{
	for (const auto effect : magicItem.list.list)
		if (effect->GetSkillCode() == avCode && (effect->setting && !(effect->setting->effectFlags & EffectSetting::kDetrimental)))
			return effect->magnitude;
	return 0;
}

UInt32 AlchemyItem::HasBaseEffectDamagesAV(const SInt32 avCode)
{
	for (const auto effect : magicItem.list.list)
		if (effect->GetSkillCode() == avCode && (effect->setting && effect->setting->effectFlags & EffectSetting::kDetrimental))
			return effect->magnitude;
	return 0;
}

bool AlchemyItem::IsAddictive()
{
	return withdrawalEffect && withdrawalEffect->refID;
}

bool AlchemyItem::IsFood()
{
	return alchFlags & 2;
}

bool AlchemyItem::IsMedicine()
{
	return alchFlags & 4;
}

bool AlchemyItem::IsPoison()
{
	EffectSetting* effSetting = nullptr;
	for (const auto effItem : magicItem.list.list)
	{
		effSetting = effItem->setting;
		if (effSetting && !(effSetting->effectFlags & 4)) return false;
	}

	return effSetting != nullptr;
}

bool AlchemyItem::IsFoodAlt()
{
	return HasBaseEffectRestoresAV(kAVCode_Hunger) && HasBaseEffectRestoresAV(kAVCode_Hunger) > HasBaseEffectRestoresAV(kAVCode_Dehydration) ? true : false;
}

bool AlchemyItem::IsWaterAlt()
{
	return HasBaseEffectRestoresAV(kAVCode_Dehydration) && HasBaseEffectRestoresAV(kAVCode_Hunger) == 0 ? true : false;
}

bool HasBaseEffectChangesAV(TESForm* form, const int avCode)
{
	const auto armor = DYNAMIC_CAST(form, TESForm, TESObjectARMO);
	if (!armor) return false;
	const auto enchantment = armor->enchantable.enchantItem;
	if (!enchantment) return false;
	for (const auto effect : enchantment->magicItem.list.list)
		if (effect->GetSkillCode() == avCode && (effect->setting && effect->setting->effectFlags & EffectSetting::kRecover))
			return true;
	return false;
}

#include <BaseFormComponent.h>
#include <TESObjectREFR.h>
#include <RTTI.h>
#include <InventoryChanges.h>
#include <GameTasks.h>
#include <SafeWrite.h>
#include <NiObjects.h>
#include <unordered_set>

#include "BaseProcess.h"
#include "Setting.h"
#include <numbers>

static constexpr UInt32 s_TESObject_REFR_init						= 0x0055A2F0;	// TESObject_REFR initialization routine (first reference to s_TESObject_REFR_vtbl)
static constexpr UInt32 s_TESObjectREFR__GetContainer				= 0x0055D310;	// First call in REFR::RemoveItem
static constexpr UInt32 s_TESObjectREFR_Set3D						= 0x005702E0;	// void : (const char*)
static constexpr UInt32 s_PlayerCharacter_GenerateNiNode			= 0x0094E1D0; // Func0072
static constexpr UInt32 kPlayerUpdate3Dpatch						= 0x0094EB7A;
static constexpr UInt32 TESObjectREFR_Set3D							= 0x0094EB40;
static constexpr UInt32 ValidBip01Names_Destroy						= 0x00418E00;
static constexpr UInt32 ExtraAnimAnimation_Destroy					= 0x00418D20;
static constexpr UInt32 RefNiRefObject_ReplaceNiRefObject			= 0x0066B0D0;

static constexpr UInt32 kg_Camera1st	= 0x011E07D0;
static constexpr UInt32 kg_Camera3rd	= 0x011E07D4;
static constexpr UInt32 kg_Bip			= 0x011E07D8;
static constexpr UInt8 kPlayerUpdate3DpatchFrom	= 0x0B6;
static constexpr UInt8 kPlayerUpdate3DpatchTo	= 0x0EB;

static NiObject **	g_3rdPersonCameraNode =				(NiObject**)kg_Camera3rd;
static NiObject **	g_1stPersonCameraBipedNode =		(NiObject**)kg_Bip;
static NiObject **	g_1stPersonCameraNode =				(NiObject**)kg_Camera1st;

ScriptEventList* TESObjectREFR::GetEventList() const
{
	if (BSExtraData* xData = extraDataList.GetByType(kExtraData_Script))
		if (const ExtraScript* xScript = DYNAMIC_CAST(xData, BSExtraData, ExtraScript))
			return xScript->eventList;
	return nullptr;
}

TESContainer* TESObjectREFR::GetContainer()
{
	if (IsActor()) return &static_cast<TESActorBase*>(baseForm)->container;
	if (baseForm->typeID == kFormType_TESObjectCONT)
		return &static_cast<TESObjectCONT*>(baseForm)->container;
	return nullptr;
}

bool TESObjectREFR::IsMapMarker() { return baseForm ? baseForm->refID == 0x010 : false; }

bool TESObjectREFR::Update3D_v1c()
{
	UInt8 kPlayerUpdate3DpatchFrom = 0x0B6;
	UInt8 kPlayerUpdate3DpatchTo = 0x0EB;

	if (this == PlayerCharacter::GetSingleton())
	{
		static constexpr UInt32 kPlayerUpdate3Dpatch = 0x0094EB7A;
		// Lets try to allow unloading the player3D never the less...
		SafeWrite8(kPlayerUpdate3Dpatch, kPlayerUpdate3DpatchTo);
	}

	Set3D(nullptr, true);
	ModelLoader::GetSingleton()->QueueReference(this, 1, 0);
	return true;
}

bool TESObjectREFR::Update3D()
{
	if (this == PlayerCharacter::GetSingleton()) {
		// Lets try to allow unloading the player3D never the less...
		SafeWrite8(kPlayerUpdate3Dpatch, kPlayerUpdate3DpatchTo);
	}

	Set3D(nullptr, true);
	ModelLoader::GetSingleton()->QueueReference(this, 1, false);
	return true;
}

TESActorBase* Actor::GetActorBase()
{
	if (modIndex == 0xFF)
		if (const auto xLvlCre = GetExtraType(extraDataList, LeveledCreature)) return xLvlCre->actorBase;
	return static_cast<TESActorBase*>(baseForm);
}

TESObjectREFR* TESObjectREFR::Create(bool bTemp)
{
	const auto refr = static_cast<TESObjectREFR*>(GameHeapAlloc(sizeof(TESObjectREFR)));
	ThisStdCall(s_TESObject_REFR_init, refr);
//	if (bTemp) MarkAsTemporary();
	return refr;
}

Float64 TESObjectREFR::GetInventoryWeight()
{
	if (const auto xChanges = reinterpret_cast<ExtraContainerChanges*>(this->extraDataList.GetByType(kExtraData_ContainerChanges)))
		return xChanges->data->GetInventoryWeight();
	return 0;
}

std::vector<InventoryChanges*> TESObjectREFR::GetAllItems(UInt32 checkLinkedRec)
{
	std::vector<InventoryChanges*> vector;
	
	InventoryChanges* entry = nullptr;
	void* iterator = nullptr;
	ThisCall(0x575510, this, 0, &iterator, &entry);
	if (iterator && entry) for (auto iter = ThisCall<InventoryChanges*>(0x4CA330, entry, iterator); iter; iter = ThisCall<InventoryChanges*>(0x4CA330, entry, iterator))
		if (iter->ShouldDisplay()) vector.push_back(iter);

	// Vanilla method is more than twice as slow but it does a lot of stuff, like removing LvlItem garbage, combining throwables, etc

	/*
	if (const auto entryList = GetContainerChangesList()) for (auto iter : *entryList) 
		if (iter->countDelta > 0) vector.push_back(iter);

	if (const auto container = GetContainer()) for (const auto iter : container->formCountList)
		if (iter->form->typeID != kFormType_TESLevItem && iter->count > 0) vector.push_back(InventoryChanges::Create(iter->form, iter->count));
	*/

	// Process linked ref for vendor containers, recursive, but hopefully no one links container on itself
	// UPD: someone linked container on itself, ffs
	if (!checkLinkedRec || checkLinkedRec > 5) {}
	else if (const auto xLinkedRef = reinterpret_cast<ExtraLinkedRef*>(this->extraDataList.GetByType(kExtraData_LinkedRef)))
		if (const auto linked = xLinkedRef->linkedRef)
		{
			const auto newvector = linked->GetAllItems(checkLinkedRec + 1);
			vector.insert(vector.end(), newvector.begin(), newvector.end());
		}

	if (this->IsActor())
		if (const auto xDropped = reinterpret_cast<ExtraDroppedItemList*>(this->extraDataList.GetByType(kExtraData_DroppedItemList)))
			for (const auto iter : xDropped->itemRefs) vector.push_back(InventoryChanges::Create(iter, 1));

	return vector;
}

void TESObjectREFR::OpenCloseContainer(bool open, bool sounds)
{
	const auto rootNode = this->GetNiNode();
	if (rootNode && (!this->IsActor() || reinterpret_cast<Actor*>(this)->lifeState != kLifeState_Dying))
	{
		const auto ctrlMgr = reinterpret_cast<NiControllerManager*>(rootNode->m_controller);
		if (ctrlMgr && IS_TYPE(ctrlMgr, NiControllerManager))
		{
			if (const auto sequence = open ? ctrlMgr->FindSequence("Open") : ctrlMgr->FindSequence("Close"))
			{
				for (const auto iter : ctrlMgr->sequences)
					if (iter->sequenceName && (*(UInt32*)iter->sequenceName != 'eldI'))
						iter->Unk_23(0, 0);
				if (sequence->Play()) this->MarkAsModified(0x10000000);
			}
		}
	}

	if (!sounds) return;
	if (baseForm->typeID == kFormType_TESObjectCONT) {
		const auto sound = open ? reinterpret_cast<TESObjectCONT*>(baseForm)->openSound : reinterpret_cast<TESObjectCONT*>(baseForm)->closeSound;
		if (sound) Sound::PlayTESSound(sound, BSAudioManager::kAudioFlags_3D | BSAudioManager::kAudioFlags100, this);
	}
	else
	{
		PlayGameSound(open ? "DRSBodyGenericOpen" : "DRSBodyGenericClose");
	}

}

const char* TESObjectREFR::GetJIPName()
{
	if (!(extraDataList.JIPExtraListFlags & BaseExtraList::kJIPExtraListFlag_AltRefName)) return "";
	return GetBaseFormFullName();
}

TESForm* GetPermanentBaseForm(TESObjectREFR* thisObj)	// For LevelledForm, find real baseForm, not temporary one.
{
	if (thisObj)
		if (const auto pXCreatureData = DYNAMIC_CAST(thisObj->extraDataList.GetByType(kExtraData_LeveledCreature), BSExtraData, ExtraLeveledCreature); pXCreatureData && pXCreatureData->baseForm)
			return pXCreatureData->baseForm;
	if (thisObj && thisObj->baseForm)
		return thisObj->baseForm;
	return nullptr;
}

void Actor::EquipItem(TESForm * objType, UInt32 equipCount, ExtraDataList* itemExtraList, UInt32 shouldApplyEnchantment, UInt32 lockEquip, UInt32 noMessage)
{
	ThisStdCall(0x0088C650, this, objType, equipCount, itemExtraList, shouldApplyEnchantment, lockEquip, noMessage);
}

void Actor::UnequipItem(TESForm* objType, UInt32 unequipCount, ExtraDataList* itemExtraList, UInt32 shouldApplyEnchantment, UInt32 lockUnequip, UInt32 noMessage)
{
	ThisStdCall(0x0088C790, this, objType, unequipCount, itemExtraList, shouldApplyEnchantment, lockUnequip, noMessage);
}

std::vector<TESForm*> Actor::GetEquippedItems()
{
	std::vector<TESForm*> itemList;
	if (const auto xChanges = static_cast<ExtraContainerChanges *>(extraDataList.GetByType(kExtraData_ContainerChanges))) {
		InventoryChangesArray outEntryData;
		const UInt32 count = xChanges->data->GetAllEquipped(outEntryData);
		for (UInt32 i = 0; i < count ; i++) itemList.push_back(outEntryData[i]->form);
	}
	return itemList;
}

InventoryChangesArray Actor::GetEquippedEntryDataList()
{
	InventoryChangesArray itemArray;
	ExtendDataArray outExtendData;
	if(const auto xChanges = static_cast<ExtraContainerChanges *>(extraDataList.GetByType(kExtraData_ContainerChanges)))
		xChanges->data->GetAllEquipped(itemArray);
	return itemArray;
}

Float64 Actor::GetCalculatedSpread(UInt32 mode, InventoryChanges* entry)
{
	if (!entry) entry = reinterpret_cast<InventoryChanges*>(this->baseProcess->GetWeaponInfo());

	if (!entry || !entry->form) return 0;

	Float64 totalSpread = 0;

	if (mode == 0)
	{
		const bool hasDecreaseSpreadEffect = ThisStdCall<bool>(0x4BDA70, entry, 3);
		const auto minSpread = ThisStdCall<double>(0x524B80, entry->form, hasDecreaseSpreadEffect);
		const double weapSpread = ThisStdCall<float>(0x524BE0, entry->form, hasDecreaseSpreadEffect);

		totalSpread = (weapSpread * ThisStdCall<double>(0x8B0DD0, this, 1) + minSpread) * 0.01745329238474369;

		const auto eqAmmo = ThisStdCall<TESAmmo*>(0x525980, entry->form, static_cast<MobileObject*>(this));
		totalSpread = CdeclCall<Float64>(0x59A030, 3, (eqAmmo ? &eqAmmo->effectList : nullptr), static_cast<Float32>(totalSpread));

		if (this != PlayerCharacter::GetSingleton())
		{
			const auto spreadPenalty = ThisStdCall<double>(0x8B0DD0, this, 2);

			Setting* fNPCMaxGunWobbleAngle = GetGameSetting("fNPCMaxGunWobbleAngle");

			totalSpread += spreadPenalty * fNPCMaxGunWobbleAngle->data.f * 0.01745329238474369;
		}

		const auto noIdea = ThisStdCall<HighProcess*>(0x8D8520, this)->angle1D0;
		totalSpread = totalSpread + noIdea;

		if (entry->HasWeaponMod(0xC)) totalSpread *= ThisStdCall<float>(0x4BCF60, entry->form, 0xC, 1);
	}
	else if (mode == 1)
	{
		if (!entry->form || reinterpret_cast<TESObjectWEAP*>(entry->form)->IsMeleeWeapon())
			totalSpread = 1.0;
		else
			totalSpread = ThisStdCall<double>(0x8B0DD0, this, 2);

		if (!this->IsDoingAttackAnim())
		{
			const Setting* fNonAttackGunWobbleMult = GetGameSetting("fNonAttackGunWobbleMult");

			totalSpread = totalSpread * fNonAttackGunWobbleMult->data.f;
		}

		totalSpread *= 0.01745329238474369;
	}
	else if (mode == 2)
	{
		totalSpread = ThisStdCall<double>(0x8B0DD0, this, 0);
		const Setting* fGunWobbleMultScope = GetGameSetting("fGunWobbleMultScope");
		totalSpread = totalSpread * fGunWobbleMultScope->data.f;

	}
	return totalSpread;

}

bool Actor::IsCombatTarget(const Actor* source)
{
	if (source->isInCombat)
		for (const auto iter : *source->combatTargets)
			if (iter == this) return true;
	return false;
}

bool Actor::IsHostileCompassTarget() const
{
	if (const auto player = PlayerCharacter::GetSingleton()) for (const auto iter : *player->compassTargets)
		if (iter->isHostile && iter->target == this) return true;
	return false;
}

__declspec(naked) double __fastcall AdjustDmgByDifficulty(ActorHitData *hitData, PlayerCharacter* g_thePlayer = PlayerCharacter::GetSingleton())
{
	__asm
	{
		mov		edx, g_thePlayer
		mov		eax, 0x119B310
		cmp		dword ptr [ecx+4], edx
		jz		isPlayer
		add		eax, 0x14
	isPlayer:
		mov		edx, [edx+0x7B8]
		mov		eax, [eax+edx*4]
		fld		dword ptr [ecx+0x14]
		fmul	dword ptr [eax+4]
		retn
	}
}

Float32 Actor::GetHitDataValue(UInt32 valueType) const
{
	if (!baseProcess || (baseProcess->processLevel > 1)) return 0;
	ActorHitData* hitData = baseProcess->GetLastHitData();
	if (!hitData) return 0;
	switch (valueType)
	{
	case 0:	return AdjustDmgByDifficulty(hitData);
	case 1:	return hitData->limbDmg;
	case 2:	return hitData->flags & 0x80000000 ? 1 : 0;
	case 3:	return hitData->wpnBaseDmg;
	case 4:	return hitData->fatigueDmg;
	case 5:	return hitData->armorDmg;
	}
	return 0;
}

Float32 Actor::GetActorValue(ActorValueCode avcode)
{
	return this->avOwner.GetActorValue(avcode);
}

void Actor::SendStealingAlarm(TESObjectREFR* container, bool checkItems)
{
	if (!checkItems) {
		const auto owner = ThisStdCall<TESForm*>(0x567790, container); // TESObjectREFR::ResolveOwnership
		if (!owner) return;
		ThisStdCall(0x8BFA40, this, container, NULL, NULL, 1, owner); // Actor::HandleStealing,
		return;
	}
	const auto owner = ThisStdCall<TESForm*>(0x567790, container); // TESObjectREFR::ResolveOwnership
	if (!owner) return;
	const auto xChanges = reinterpret_cast<ExtraContainerChanges*>(this->extraDataList.GetByType(kExtraData_ContainerChanges));
	if (!xChanges || !xChanges->data || !xChanges->data->objList) return;

	for (const auto entry : *xChanges->data->objList) {
		if (!entry->extendData || !entry->form) continue;
		for (const auto xData : *entry->extendData) {
			if (xData && xData->HasType(kExtraData_Ownership)) {
				const auto xOwn = reinterpret_cast<ExtraOwnership*>(xData->GetByType(kExtraData_Ownership));
				if (xOwn->owner && xOwn->owner->refID == owner->refID) {
					ThisStdCall(0x8BFA40, this, container, NULL, NULL, 1, owner); // Actor::HandleStealing
					return;
				}
			}
		}
	}
}


bool TESObjectREFR::IsCrimeOrEnemy()
{
	const auto actor = static_cast<Actor*>(this);
	return ThisCall(0x579690, this) && (!this->IsActor() || !actor->isTeammate) || this->IsActor() && (actor->
		IsCombatTarget(PlayerCharacter::GetSingleton()) || actor->IsHostileCompassTarget());
}

bool TESObjectREFR::GetInventoryItems(InventoryItemsMap &invItems)
{
	TESContainer *container = GetContainer();
	if (!container) return false;
	const auto xChanges = static_cast<ExtraContainerChanges*>(extraDataList.GetByType(kExtraData_ContainerChanges));
	const auto entryList = (xChanges && xChanges->data) ? xChanges->data->objList : nullptr;
	if (!entryList) return false;

	TESForm *item;
	SInt32 countDelta;
	InventoryChanges *entry;

	for (const auto contIter : container->formCountList)
	{
		item = contIter->form;
		if (item->typeID == kFormType_TESObjectCONT || invItems.contains(item)) continue;
		SInt32 contCount = container->GetCountForForm(item);
		if ((entry = entryList->FindForItem(item)))
		{
			countDelta = entry->countDelta;
			if (entry->HasExtraLeveledItem())
				contCount = countDelta;
			else contCount += countDelta;
		}
		if (contCount > 0)
			invItems.emplace(item, InventoryItemData(contCount, entry));
	}

	for (const auto entry_data : *entryList)
	{
		item = entry_data->form;
		if (invItems.contains(item)) continue;
		countDelta = entry_data->countDelta;
		if (countDelta > 0)
			invItems.emplace(item, InventoryItemData(countDelta, entry_data));
	}

	return !invItems.empty();
}

__declspec(naked) float __vectorcall Point2Distance(const NiPoint3& pt1, const NiPoint3& pt2)
{
	__asm
	{
		movq	xmm0, qword ptr[ecx]
		movq	xmm1, qword ptr[edx]
		subps	xmm0, xmm1
		mulps	xmm0, xmm0
		haddps	xmm0, xmm0
		sqrtss	xmm0, xmm0
		retn
	}
}

__declspec(naked) float __vectorcall Point3Distance(const NiPoint3& pt1, const NiPoint3& pt2)
{
	__asm
	{
		movups	xmm0, [ecx]
		movups	xmm1, [edx]
		subps	xmm0, xmm1
		mulps	xmm0, xmm0
		xorps	xmm1, xmm1
		haddps	xmm0, xmm1
		haddps	xmm0, xmm1
		sqrtss	xmm0, xmm0
		retn
	}
}

bool __fastcall TESObjectREFR::GetInSameCellOrWorld(const TESObjectREFR *target) const
{
	const TESObjectCELL* parentCell = this->parentCell;
	if (!parentCell)
	{
		const auto extraCell = (ExtraPersistentCell*) extraDataList.GetByType(kExtraData_PersistentCell);

		if (!extraCell) return false;

		parentCell = extraCell->persistentCell;
	}

	const TESObjectCELL* targetParentCell = target->parentCell;
	if (!targetParentCell)
	{
		const auto extraCell = (ExtraPersistentCell*) target->extraDataList.GetByType(kExtraData_PersistentCell);

		if (!extraCell) return false;

		targetParentCell = extraCell->persistentCell;
	}

	if (parentCell == targetParentCell) return true;

	if (!parentCell->worldSpace) return false;

	if (parentCell->worldSpace == targetParentCell->worldSpace) return true;

	return false;
}

float __vectorcall TESObjectREFR::GetDistance(TESObjectREFR* target)
{
	return GetInSameCellOrWorld(target) ? Point3Distance(*GetPos(), *target->GetPos()) : FLT_MAX;
}

float __vectorcall TESObjectREFR::GetDistance2D(TESObjectREFR* target)
{
	return GetInSameCellOrWorld(target) ? Point2Distance(*GetPos(), *target->GetPos()) : FLT_MAX;
}

Float32 TESObjectREFR::GetHeadingAngle(const TESObjectREFR* target)
{
	if (!target) return 0;
	return rot.z - atan2(target->pos.x - pos.x, target->pos.y - pos.y) - 2 * std::numbers::pi;
}

__declspec(naked) NiAVObject* __fastcall NiNode::GetBlockByName(const char *nameStr)	//	str of NiFixedString
{
	__asm
	{
		movzx	eax, word ptr [ecx+0xA6]
		test	eax, eax
		jz		done
		push	esi
		push	edi
		mov		esi, [ecx+0xA0]
		mov		edi, eax
		ALIGN 16
	iterHead:
		dec		edi
		js		iterEnd
		mov		eax, [esi]
		add		esi, 4
		test	eax, eax
		jz		iterHead
		cmp		[eax+8], edx
		jz		found
		mov		ecx, [eax]
		cmp		dword ptr [ecx+0xC], 0x6815C0
		jnz		iterHead
		mov		ecx, eax
		call	NiNode::GetBlockByName
		test	eax, eax
		jz		iterHead
	found:
		pop		edi
		pop		esi
		retn
		ALIGN 16
	iterEnd:
		xor		eax, eax
		pop		edi
		pop		esi
	done:
		retn
	}
}
__declspec(naked) NiAVObject* __fastcall NiNode::GetBlock(const char* blockName)
{
	__asm
	{
		cmp[edx], 0
		jz		retnNULL
		push	ecx
		push	edx
		__asm mov eax, 0xA5B690 __asm call eax
		pop		ecx
		pop		ecx
		test	eax, eax
		jz		done
		lock dec dword ptr[eax - 8]
		jz		retnNULL
		cmp[ecx + 8], eax
		jz		found
		mov		edx, eax
		call	NiNode::GetBlockByName
		retn
	found :
		mov		eax, ecx
		retn
	retnNULL :
		xor eax, eax
	done :
		retn
	}
}

__declspec(naked) NiNode* __fastcall NiNode::GetNode(const char *nodeName) const
{
	__asm
	{
		call	NiNode::GetBlock
		test	eax, eax
		jz		done
		xor		edx, edx
		mov		ecx, [eax]
		cmp		dword ptr [ecx+0xC], 0x6815C0
		cmovnz	eax, edx
	done:
		retn
	}
}

__declspec(naked) NiNode* TESObjectREFR::GetNiNode()
{
	/*
	 *  result = this->renderState;
  if ( !result )
	return result;

  result = (TESObjectREFR::RenderState *)result->niNode14;
  if ( this->refID == 0x14 && !this->isInThirdPerson )
	return (TESObjectREFR::RenderState *)this->node1stPerson;

  return result;
	 *
	 */
	__asm
	{
		mov		eax, [ecx + 0x64] // renderstate
		test	eax, eax
		jz		done
		mov		eax, [eax + 0x14]	// ninode0x14
		cmp		dword ptr[ecx + 0xC], 0x14 // player
		jnz		done
		cmp		byte ptr[ecx + 0x64A], 0 // isinthirdperson
		jnz		done
		mov		eax, [ecx + 0x694] //third person node0
	done:
		retn
	}
}

__declspec(naked) NiNode* __fastcall TESObjectREFR::GetNode(const char* nodeName)
{
	__asm
	{
		call	TESObjectREFR::GetNiNode
		test	eax, eax
		jz		done
		cmp[edx], 0
		jz		done
		mov		ecx, eax
		call	NiNode::GetBlock
		test	eax, eax
		jz		done
		xor edx, edx
		mov		ecx, [eax]
		cmp		dword ptr[ecx + 0xC], 0x6815C0
		cmovnz	eax, edx
	done :
		retn
	}
}

// jazz code
__declspec(naked) NiAVObject* __fastcall GetNifBlock2(TESObjectREFR *thisObj, UInt32 pcNode, const char *blockName)
{
	__asm
	{
		test	dl, dl
		jz		notPlayer
		cmp		dword ptr [ecx+0xC], 0x14 // player
		jnz		notPlayer
		test	dl, 1
		jz		get1stP
		mov		eax, [ecx+0x64]
		test	eax, eax
		jz		done
		mov		eax, [eax+0x14]
		jmp		gotRoot
	get1stP:
		mov		eax, [ecx+0x694]
		jmp		gotRoot
	notPlayer:
		call	TESObjectREFR::GetNiNode
	gotRoot:
		test	eax, eax
		jz		done
		mov		edx, [esp+4]
		cmp		[edx], 0
		jz		done
		mov		ecx, eax
		call	NiNode::GetBlock
	done:
		retn	4
	}
}

NiAVObject* TESObjectREFR::GetNifBlock(UInt32 pcNode, const char* blockName)
{
	return GetNifBlock2(this, pcNode, blockName);
}

QuestObjectiveTargets*	PlayerCharacter::GetCurrentQuestObjectiveTargets() { return ThisStdCall<QuestObjectiveTargets*>(0x00952BA0, this); }
TESObjectREFR*			PlayerCharacter::GetPlacedMarkerOrTeleportLink() { return ThisStdCall<TESObjectREFR*>(0x77A400, this); }

bool Explosion::CanStoreAmmo()
{
	if (!source) return false;
	if (source->typeID != kFormType_Character && source->typeID != kFormType_Creature) return false;
	if (!source->IsActor()) return false;
	if (ammo && (ammo->typeID != kFormType_TESAmmo && ammo->typeID != kFormType_TESObjectWEAP)) return false; // temporary check until I resolve saving issue
	return true;
}

UInt32* g_weaponTypeToAnim = reinterpret_cast<UInt32*>(0x118A838);

UInt16 GetActorRealAnimGroup(Actor* actor, UInt8 groupID)
{
	UInt8 animHandType = 0;
	if (const auto* form = actor->GetWeaponForm())
		animHandType = g_weaponTypeToAnim[form->eWeaponType];
	const auto moveFlags = actor->actorMover->GetMovementFlags();
	UInt8 moveType = 0;
	if ((moveFlags & 0x800) != 0)
		moveType = kAnimMoveType_Swimming;
	else if ((moveFlags & 0x2000) != 0)
		moveType = kAnimMoveType_Flying;
	else if ((moveFlags & 0x400) != 0)
		moveType = kAnimMoveType_Sneaking;
	const auto isPowerArmor = ThisStdCall<bool>(0x8BA3E0, actor) || ThisStdCall<bool>(0x8BA410, actor);
	return (moveType << 12) + (isPowerArmor << 15) + (animHandType << 8) + groupID;
}

TESAmmo* ActorHitData::GetAmmo() const
{
	if (!projectile) return nullptr;
	if (projectile->IsProjectile()) return projectile->ammo;
	if (explosion->IsExplosion() && explosion->CanStoreAmmo()) return explosion->ammo;
	return nullptr;
}

TESObjectWEAP* ActorHitData::GetWeapon() const
{
	if (!projectile) return nullptr;
	if (projectile->IsProjectile()) return projectile->weapon;
	if (explosion->IsExplosion()) return explosion->weapon;
	if (weapon) return weapon;
	return nullptr;
}

Script* ActorHitData::GetAmmoScript() const
{
	const auto ammo = GetAmmo();
	if (!ammo) return nullptr;
	if (ammo->typeID == kFormType_TESAmmo) return ammo->scriptable.script;
	if (ammo->typeID == kFormType_TESObjectWEAP) return reinterpret_cast<TESObjectWEAP*>(ammo)->scritpable.script;
	return nullptr;
}

/*
void Actor::FireWeapon()
{
	animGroupId110 = static_cast<UInt32>(GetAnimData()->GetNextAttackGroupID());
	this->baseProcess->SetQueuedIdleFlag(kIdleFlag_FireWeapon);
	Actor::HandleQueuedAnimFlags(this); //Actor::HandleQueuedIdleFlags
}

void Actor::EjectFromWeapon(TESObjectWEAP* weapon)
{
	if (weapon && Actor::IsDoingAttackAnimation(this) && !weapon->IsMeleeWeapon() && !weapon->IsAutomatic())
	{
		baseProcess->SetQueuedIdleFlag(kIdleFlag_AttackEjectEaseInFollowThrough);
		Actor::HandleQueuedAnimFlags(this);
	}
}
*/
TESObjectWEAP* Actor::GetWeaponForm() const
{
	const auto weaponInfo = this->baseProcess->GetWeaponInfo();
	if (!weaponInfo) return nullptr;
	return weaponInfo->weapon;
}

bool Actor::IsAnimActionReload() const
{
	const auto currentAnimAction = static_cast<AnimAction>(baseProcess->GetCurrentAnimAction());
	const static std::unordered_set s_reloads = { kAnimAction_Reload, kAnimAction_ReloadLoop, kAnimAction_ReloadLoopStart, kAnimAction_ReloadLoopEnd };
	return s_reloads.contains(currentAnimAction);
}

NiPoint3 TESObjectREFR::GetCenter() const
{
	if (this->IsActor())
		if (const auto baseProcess = ((Actor*)this)->baseProcess; baseProcess && baseProcess->processLevel != 1)
			return baseProcess->GetBoundingBox()->centre;
	if (this->renderState && this->renderState->niNode14)
		if (const auto bounds = reinterpret_cast<BSBound*>(this->renderState->niNode14->GetExtraData(kVtbl_BSBound)))
			return bounds->centre;
	if (this->baseForm && this->baseForm->IsBoundObject())
		if (const auto bounds = (reinterpret_cast<TESBoundObject*>(this->baseForm)))
		{
			NiPoint3 ni3 {};
			ni3.x = abs(bounds->right.x + bounds->left.x) / 2;
			ni3.y = abs(bounds->right.y + bounds->left.y) / 2;
			ni3.z = abs(bounds->right.z + bounds->left.z) / 2;

			const auto rot = this->rot;

			const auto sX = sin(rot.x);
			const auto sY = sin(rot.y);
			const auto sZ = sin(rot.z);
			const auto cX = cos(rot.x);
			const auto cY = cos(rot.y);
			const auto cZ = cos(rot.z);

			const Float32 newX = (ni3.x * cZ + ni3.y * sZ) * cY + ni3.z * -sY;
			const Float32 newY = (ni3.x * -sZ + ni3.y * cZ) * cX + ((ni3.x * cZ + ni3.y * sZ) * sY + ni3.z * cY) * sX;
			const Float32 newZ = (ni3.x * -sZ + ni3.y * cZ) * -sX + ((ni3.x * cZ + ni3.y * sZ) * sY + ni3.z * cY) * cX;

			ni3.x = newX;
			ni3.y = newY;
			ni3.z = newZ;

			return ni3;
		}
	const NiPoint3 ni3{};
	return ni3;
}

NiPoint3 TESObjectREFR::GetDimensions() const
{
	if (this->IsActor())
		if (const auto baseProcess = ((Actor*)this)->baseProcess; baseProcess && baseProcess->processLevel != 1)
			return baseProcess->GetBoundingBox()->dimensions;
	if (this->renderState && this->renderState->niNode14)
		if (const auto bounds = reinterpret_cast<BSBound*>(this->renderState->niNode14->GetExtraData(kVtbl_BSBound)))
			return bounds->dimensions;
	if (this->baseForm && this->baseForm->IsBoundObject())
		if (const auto bounds = (reinterpret_cast<TESBoundObject*>(this->baseForm)))
		{
			NiPoint3 ni3 {};
			ni3.x = abs(bounds->right.x - bounds->left.x) / 2;
			ni3.y = abs(bounds->right.y - bounds->left.y) / 2;
			ni3.z = abs(bounds->right.z - bounds->left.z) / 2;

			const auto rot = this->rot;

			const auto sX = sin(rot.x);
			const auto sY = sin(rot.y);
			const auto sZ = sin(rot.z);
			const auto cX = cos(rot.x);
			const auto cY = cos(rot.y);
			const auto cZ = cos(rot.z);

			const Float32 newX = (ni3.x * cZ + ni3.y * sZ) * cY + ni3.z * -sY;
			const Float32 newY = (ni3.x * -sZ + ni3.y * cZ) * cX + ((ni3.x * cZ + ni3.y * sZ) * sY + ni3.z * cY) * sX;
			const Float32 newZ = (ni3.x * -sZ + ni3.y * cZ) * -sX + ((ni3.x * cZ + ni3.y * sZ) * sY + ni3.z * cY) * cX;

			ni3.x = newX;
			ni3.y = newY;
			ni3.z = newZ;

			return ni3;
		}
	const NiPoint3 ni3{};
	return ni3;
}

TESObjectREFR* TESObjectREFR::ResolveAshpile()
{
	if (*(UInt32*)baseForm == kVtbl_TESObjectACTI)
		if (const auto xAshPileRef = reinterpret_cast<ExtraAshPileRef*>(extraDataList.GetByType(kExtraData_AshPileRef)))
			return xAshPileRef->sourceRef;
	return this;
}

bool TESObjectREFR::IsLocked() const
{
	const auto data = GetLockData();
	return data && data->IsLocked();
}


const _GetActorValueName GetActorValueName = reinterpret_cast<_GetActorValueName>(0x00066EAC0);	// See Cmd_GetActorValue_Eval

// g_baseActorValueNames is only filled in after oblivion's global initializers run
const char* GetActorValueString(UInt32 actorValue)
{
	const char* name = 0;
	if (actorValue <= kAVCode_Max)
		name = GetActorValueName(actorValue);
	if (!name)
		name = "unknown";

	return name;
}

UInt32 GetActorValueForScript(const char* avStr)
{
	for (UInt32 i = 0; i <= kAVCode_Max; i++) {
		if (_stricmp(avStr, GetActorValueName(i)) == 0)
			return i;
	}
	return kAVCode_None;
}

UInt32 GetActorValueForString(const char* strActorVal, bool bForScript)
{
	if (bForScript)
		return GetActorValueForScript(strActorVal);

	for (UInt32 n = 0; n <= kAVCode_Max; n++) {
		if (_stricmp(strActorVal, GetActorValueName(n)) == 0)
			return n;
	}
	return kAVCode_None;
}

std::unordered_map<UInt32, UInt32> ActorValueMax = {
	{ kAVCode_Aggression, 3 },
	{ kAVCode_Confidence, 4 },
	{ kAVCode_Energy, 100 },
	{ kAVCode_Responsibility, 100 },
	{ kAVCode_Mood, 8 },

	{ kAVCode_Strength, 10 },
	{ kAVCode_Perception, 10 },
	{ kAVCode_Endurance, 10 },
	{ kAVCode_Charisma, 10 },
	{ kAVCode_Intelligence, 10 },
	{ kAVCode_Agility, 10 },
	{ kAVCode_Luck, 10 },

	{ kAVCode_ActionPoints, 0 },
	{ kAVCode_CarryWeight, 0 },
	{ kAVCode_CritChance, 100 },
	{ kAVCode_HealRate, 0 },
	{ kAVCode_Health, 0 },
	{ kAVCode_MeleeDamage, 0 },
	{ kAVCode_DamageResistance, 100 },
	{ kAVCode_PoisonResist, 100 },
	{ kAVCode_RadResist, 100 },
	{ kAVCode_SpeedMult, 0 },
	{ kAVCode_Fatigue, 0 },
	{ kAVCode_Karma, 1000 },
	{ kAVCode_XP, 0 },

	{ kAVCode_PerceptionCondition, 100 },
	{ kAVCode_EnduranceCondition, 100 },
	{ kAVCode_LeftAttackCondition, 100 },
	{ kAVCode_RightAttackCondition, 100 },
	{ kAVCode_LeftMobilityCondition, 100 },
	{ kAVCode_RightMobilityCondition, 100 },
	{ kAVCode_BrainCondition, 100 },

	{ kAVCode_Barter, 100 },
	{ kAVCode_BigGuns, 100 },
	{ kAVCode_EnergyWeapons, 100 },
	{ kAVCode_Explosives, 100 },
	{ kAVCode_Lockpick, 100 },
	{ kAVCode_Medicine, 100 },
	{ kAVCode_MeleeWeapons, 100 },
	{ kAVCode_Repair, 100 },
	{ kAVCode_Science, 100 },
	{ kAVCode_Guns, 100 },
	{ kAVCode_Sneak, 100 },
	{ kAVCode_Speech, 100 },
	{ kAVCode_Survival, 100 },
	{ kAVCode_Unarmed, 100 },

	{ kAVCode_InventoryWeight, 0 },
	{ kAVCode_Paralysis, 1 },
	{ kAVCode_Invisibility, 1 },
	{ kAVCode_Chameleon, 1 },
	{ kAVCode_NightEye, 1 },
	{ kAVCode_Turbo, 1 },
	{ kAVCode_FireResist, 100 },
	{ kAVCode_WaterBreathing, 1 },
	{ kAVCode_RadiationRads, 1000 },
	{ kAVCode_BloodyMess, 1 },
	{ kAVCode_UnarmedDamage, 100 },
	{ kAVCode_Assistance, 2 },

	{ kAVCode_ElectricResist, 100 },

	{ kAVCode_FrostResist, 100 },
	{ kAVCode_EnergyResist, 100 },
	{ kAVCode_EmpResist, 100 },
	{ kAVCode_Variable01, 1 },
	{ kAVCode_Variable02, 1 },
	{ kAVCode_Variable03, 1 },
	{ kAVCode_Variable04, 1 },
	{ kAVCode_Variable05, 1 },
	{ kAVCode_Variable06, 1 },
	{ kAVCode_Variable07, 1 },
	{ kAVCode_Variable08, 1 },
	{ kAVCode_Variable09, 1 },
	{ kAVCode_Variable10, 1 },

	{ kAVCode_IgnoreCrippledLimbs, 1 },
	{ kAVCode_Dehydration, 1000 },
	{ kAVCode_Hunger, 1000 },
	{ kAVCode_SleepDeprivation, 1000 },
	{ kAVCode_DamageThreshold, 100 },
};

#include <Tile.h>
#include <Menu.h>

#include "SafeWrite.h"

NiTMapBase <const char*, int>* g_traitNameMap = reinterpret_cast<NiTMapBase<const char*, int>*>(0x011F32F4);

Tile::Value* Tile::GetValue(const TileValueIDs id) const
{
	const auto data = values.data;
	auto iterLeft = 0;
	auto iterRight = values.size;
	while (iterLeft != iterRight)
	{
		const auto addr = (iterLeft + iterRight) >> 1;

		Value* result = data[addr];
		if (result->id == id) return result;

		 result->id < id ? iterLeft = addr + 1 : iterRight = addr;
	}

	return nullptr;
}

Tile* Tile::GetNthChild(const UInt32 index)
{
	if (!children.Empty()) if (const auto node = children.GetNthChild(index); node) return node->data;
	return nullptr;
}

Tile* Tile::GetChild(const std::string& childName) const
{
	bool any = false;
	UInt32 index = 0;
	auto tileName = childName;

	if (childName[0] == '*') any = true;
	if (const auto separator = childName.find_last_of(':')) {
		index = atoi(childName.substr(separator + 1).c_str());
		tileName = childName.substr(0, separator - 1);
	}

	for (const auto tile : children) if ((any || tileName == tile->name.CStr()) && !index--) return tile;
	return nullptr;
}

Tile* Tile::GetComponent(const std::string& componentPath)
{
	auto child = this;
	for (const auto word : std::views::split(componentPath, '/'))
	{
		child = child->GetChild(word.data());
		if (!child) return nullptr;
	}
	return child;
}

Tile* Tile::InjectUIXML(const std::filesystem::path& xmlPath, const bool ignoreUIO)
{
	if (ignoreUIO) 	// allow hot-reloading the menu even if UIO is installed
	{
		const UInt32 previousResolveXMLFile = DetourRelCall(0xA01B87, 0xA01E20);
		const auto tile = InjectUIXML(xmlPath);
		WriteRelCall(0xA01B87, previousResolveXMLFile);
		return tile;
	}
	return InjectUIXML(xmlPath);
}

Tile* Tile::AddTileFromTemplate(const char* templateName, const char* altName)
{
	const auto tile = GetParentMenu()->AddTileFromTemplate(this, templateName, 0);
	if (altName) tile->name.Set(altName);
	return tile;
}

std::string Tile::GetFullPath() const
{
	auto tileMenu = this;

	std::string fullPath = std::string(tileMenu->name.CStr());

	while (NOT_TYPE(tileMenu, TileMenu) && (tileMenu = tileMenu->parent)) {
		fullPath = std::string(tileMenu->name.CStr()) + "/" + fullPath;
	} 
	
	return fullPath;
}

// not a one-way mapping, so we just return the first
// also this is slow and sucks
const char* Tile::TraitIDToName(const TileValueIDs id)
{
	for (const auto bucket : *g_traitNameMap)
		if (bucket->data == id)
			return bucket->key;
	return nullptr;
}

TileMenu* Tile::GetTileMenu()
{
	auto tileMenu = this;
	do if IS_TYPE(tileMenu, TileMenu) break;
	while ((tileMenu = tileMenu->parent));
	return reinterpret_cast<TileMenu*>(tileMenu);
}

void Tile::PokeValue(const TileValueIDs id)
{
	const auto value = GetValue(id);
	if (!value) return;
	const auto oldValue = value->num;
	value->SetFloat(static_cast<Float32>(0x3F800000), 0);
	value->SetFloat(oldValue, 0);
}

#include <Types.h>
#include <string>
#include <TESObjectREFR.h>
#include <BaseProcess.h>
#include "GameData.h"
/*** String ***/

// an array of structs describing each of the game's anim groups
static const TESAnimGroup::AnimGroupInfo* s_animGroupInfos = (const TESAnimGroup::AnimGroupInfo*)0x011977D8;

TESAnimGroup::AnimGroupID AnimData::GetNextAttackGroupID() const
{
	switch (ThisStdCall<char>(0x495E40, this, 0))
	{
	case '3': return TESAnimGroup::kAnimGroup_Attack3;
	case '4': return TESAnimGroup::kAnimGroup_Attack4;
	case '5': return TESAnimGroup::kAnimGroup_Attack5;
	case '6': return TESAnimGroup::kAnimGroup_Attack6;
	case '7': return TESAnimGroup::kAnimGroup_Attack7;
	case '8': return TESAnimGroup::kAnimGroup_Attack8;
	case 'l': return TESAnimGroup::kAnimGroup_AttackLeft;
	default:
		if (const auto weaponInfo = this->actor->baseProcess->GetWeaponInfo(); weaponInfo && weaponInfo->weapon)
			if (const auto attackAnim = weaponInfo->weapon->attackAnim; attackAnim != 0xFF) 
				return static_cast<TESAnimGroup::AnimGroupID>(attackAnim);
		return TESAnimGroup::kAnimGroup_AttackRight;
	}
}

const char* TESAnimGroup::StringForAnimGroupCode(UInt32 groupCode)
{
	return (groupCode < kAnimGroup_Max) ? s_animGroupInfos[groupCode].name : NULL;
}

UInt32 TESAnimGroup::AnimGroupForString(const char* groupName)
{
	for (UInt32 i = 0; i < kAnimGroup_Max; i++) {
		if (!_stricmp(s_animGroupInfos[i].name, groupName)) {
			return i;
		}
	}

	return kAnimGroup_Max;
}

OSInputGlobals** g_inputGlobals = reinterpret_cast<OSInputGlobals**>(0x11F35CC);

NiControllerSequence* NiControllerManager::FindSequence(const char* seqName)
{
	for (const auto iter : sequences) if (!StrCompare(iter->sequenceName, seqName)) return iter;
	return nullptr;
}

// jazz code
__declspec(naked) bool NiControllerSequence::Play()
{
//	if (owner) owner->flags |= 0x8;
//	offset = 0x0FF7FFFFF;
	__asm
	{
		push	ecx
		push	0
		push	0
		push	0
		push	0x3F800000
		push	0
		push	0
		mov		eax, 0xA34F20
		call	eax
		pop		ecx
		test	al, al
		jz		done
		mov		dword ptr [ecx+0x48], 0xFF7FFFFF
		mov		edx, [ecx+0x40]
		test	edx, edx
		jz		done
		or		byte ptr [edx+8], 8
	done:
		retn
	}
}

BSAnimGroupSequence* BSAnimGroupSequence::Get3rdPersonCounterpart() const
{
	const auto animData = PlayerCharacter::GetSingleton()->baseProcess->GetAnimData();
	if (const auto base = animData->mapAnimSequenceBase->Lookup(this->animGroup->groupID))
		return base->GetSequenceByIndex(0);
	return nullptr;
}

bool TESAnimGroup::IsAttackIS()
{
	const auto idMinor = static_cast<AnimGroupID>(groupID & 0xFF);
	switch (idMinor)
	{
	case kAnimGroup_AttackLeftIS: break;
	case kAnimGroup_AttackRightIS: break;
	case kAnimGroup_Attack3IS: break;
	case kAnimGroup_Attack4IS: break;
	case kAnimGroup_Attack5IS: break;
	case kAnimGroup_Attack6IS: break;
	case kAnimGroup_Attack7IS: break;
	case kAnimGroup_Attack8IS: break;
	case kAnimGroup_AttackLoopIS: break;
	case kAnimGroup_AttackSpinIS: break;
	case kAnimGroup_AttackSpin2IS: break;
	case kAnimGroup_PlaceMineIS: break;
	case kAnimGroup_PlaceMine2IS: break;
	case kAnimGroup_AttackThrowIS: break;
	case kAnimGroup_AttackThrow2IS: break;
	case kAnimGroup_AttackThrow3IS: break;
	case kAnimGroup_AttackThrow4IS: break;
	case kAnimGroup_AttackThrow5IS: break;
	case kAnimGroup_Attack9IS: break;
	case kAnimGroup_AttackThrow6IS: break;
	case kAnimGroup_AttackThrow7IS: break;
	case kAnimGroup_AttackThrow8IS: break;
	default: return false;
	}
	return true;
}

bool TESAnimGroup::IsAttackNonIS()
{
	const auto idMinor = static_cast<AnimGroupID>(groupID & 0xFF);
	switch (idMinor)
	{
	case kAnimGroup_AttackLeft: break;
	case kAnimGroup_AttackRight: break;
	case kAnimGroup_Attack3: break;
	case kAnimGroup_Attack4: break;
	case kAnimGroup_Attack5: break;
	case kAnimGroup_Attack6: break;
	case kAnimGroup_Attack7: break;
	case kAnimGroup_Attack8: break;
	case kAnimGroup_AttackLoop: break;
	case kAnimGroup_AttackSpin: break;
	case kAnimGroup_AttackSpin2: break;
	case kAnimGroup_AttackPower: break;
	case kAnimGroup_AttackForwardPower: break;
	case kAnimGroup_AttackBackPower: break;
	case kAnimGroup_AttackLeftPower: break;
	case kAnimGroup_AttackRightPower: break;
	case kAnimGroup_AttackCustom1Power: break;
	case kAnimGroup_AttackCustom2Power: break;
	case kAnimGroup_AttackCustom3Power: break;
	case kAnimGroup_AttackCustom4Power: break;
	case kAnimGroup_AttackCustom5Power: break;
	case kAnimGroup_PlaceMine: break;
	case kAnimGroup_PlaceMine2: break;
	case kAnimGroup_AttackThrow: break;
	case kAnimGroup_AttackThrow2: break;
	case kAnimGroup_AttackThrow3: break;
	case kAnimGroup_AttackThrow4: break;
	case kAnimGroup_AttackThrow5: break;
	case kAnimGroup_Attack9: break;
	case kAnimGroup_AttackThrow6: break;
	case kAnimGroup_AttackThrow7: break;
	case kAnimGroup_AttackThrow8: break;

	default: return false;
	}
	return true;
}

/*
TESAnimGroup::AnimGroupInfo* GetGroupInfo(UInt8 groupId)
{
	return &g_animGroupInfos[groupId];
}

UInt32 GetSequenceType(UInt8 groupId)
{
	return GetGroupInfo(groupId)->sequenceType;
}

TESAnimGroup::AnimGroupInfo* TESAnimGroup::GetGroupInfo() const
{
	return GetGroupInfo(groupID);
}
*/

UInt8 TESAnimGroup::GetBaseGroupID() const
{
	return groupID;
}

__declspec(naked) TESForm* __stdcall LookupFormByRefID(UInt32 refID)
{
	__asm
	{
		mov		ecx, ds: [0x11C54C0]
		mov		eax, [esp + 4]
		xor		edx, edx
		div		dword ptr[ecx + 4]
		mov		eax, [ecx + 8]
		mov		eax, [eax + edx * 4]
		test	eax, eax
		jz		done
		mov		edx, [esp + 4]
		ALIGN 16
	iterHead:
		cmp		[eax + 4], edx
		jz		found
		mov		eax, [eax]
		test	eax, eax
		jnz		iterHead
		retn	4
	found:
		mov		eax, [eax + 8]
	done :
		retn	4
	}
}

extern TESDataHandler* g_TESDataHandler;
TESForm* GetRefFromString(char* mod, char* id)
{
	const auto itemID = (g_TESDataHandler->GetModIndex(mod) << 24) | strtoul(id, nullptr, 0);
	return LookupFormByRefID(itemID);
}

void FormatScriptText(std::string& str)
{
	UInt32 pos = 0;

	while (((pos = str.find('%', pos)) != -1) && pos < str.length() - 1)
	{
		char toInsert = 0;
		switch (str[pos + 1])
		{
		case '%':
			pos += 2;
			continue;
		case 'r':
		case 'R':
			toInsert = '\n';
			break;
		case 'q':
		case 'Q':
			toInsert = '"';
			break;
		default:
			pos += 1;
			continue;
		}

		str.insert(pos, 1, toInsert); // insert char at current pos
		str.erase(pos + 1, 2);		  // erase format specifier
		pos += 1;
	}
}

#include <BaseFormComponent.h>


// static
UInt32 TESBipedModelForm::MaskForSlot(UInt32 slot)
{
	return 0x1 << slot;
}

UInt32 TESBipedModelForm::GetSlotsMask() const {
	return partMask;
}

void TESBipedModelForm::SetSlotsMask(UInt32 mask)
{
	partMask = (mask & ePartBitMask_Full);
}

UInt32 TESBipedModelForm::GetBipedMask() const {
	return bipedFlags & 0xFF;
}

void TESBipedModelForm::SetBipedMask(UInt32 mask)
{
	bipedFlags = mask & 0xFF;
}

void  TESBipedModelForm::SetPath(const char* newPath, UInt32 whichPath, bool bFemalePath)
{
	String* toSet = nullptr;

	switch (whichPath)
	{
	case ePath_Biped:
		toSet = &bipedModel[bFemalePath ? 1 : 0].nifPath;
		break;
	case ePath_Ground:
		toSet = &groundModel[bFemalePath ? 1 : 0].nifPath;
		break;
	case ePath_Icon:
		toSet = &icon[bFemalePath ? 1 : 0].ddsPath;
		break;
	default: break;
	}

	if (toSet) toSet->Set(newPath);
}

const char* TESBipedModelForm::GetPath(UInt32 whichPath, bool bFemalePath)
{
	String* pathStr = nullptr;

	switch (whichPath)
	{
	case ePath_Biped:
		pathStr = &bipedModel[bFemalePath ? 1 : 0].nifPath;
		break;
	case ePath_Ground:
		pathStr = &groundModel[bFemalePath ? 1 : 0].nifPath;
		break;
	case ePath_Icon:
		pathStr = &icon[bFemalePath ? 1 : 0].ddsPath;
		break;
	default: break;
	}

	return pathStr ? pathStr->m_data : "";
}

SInt8 TESActorBaseData::GetFactionRank(TESFaction* faction)
{
	for (const auto iter : factionList) if (iter->faction == faction) return iter->rank;
	return -1;
}

SInt32 TESContainer::GetCountForForm(TESForm* form)
{
	SInt32 result = 0;
	for (const auto iter : formCountList)
		if (iter->form == form) result += iter->count;
	return result;
}

#include <BSExtraData.h>

#include <TESForm.h>
#include <TESObjectREFR.h>
#include <Script.h>
#include <RTTI.h>

static const UInt32 s_ExtraDataListVtbl							= 0x010143E8;	//	0x0100e3a8;

bool BaseExtraList::HasType(UInt32 type) const
{
	return (m_presenceBitfield[type >> 3] & 1 << (type & 7)) != 0;
}

void BaseExtraList::MarkType(UInt32 type, bool bCleared)
{
	UInt8 bitMask = 1 << (type & 7);
	UInt8 &flag = m_presenceBitfield[type >> 3];
	if (bCleared) flag &= ~bitMask;
	else flag |= bitMask;
}

ExtraDataList* ExtraDataList::Create(BSExtraData* xBSData)
{
	ExtraDataList* xData = (ExtraDataList*)GameHeapAlloc(sizeof(ExtraDataList));
	memset(xData, 0, sizeof(ExtraDataList));
	((UInt32*)xData)[0] = s_ExtraDataListVtbl;
	if (xBSData) xData->Add(xBSData);
	return xData;
}


ExtendDataList* ExtendDataList::Create(ExtraDataList* pExtraDataList)
{
	auto xData = (ExtendDataList*)GameHeapAlloc(sizeof(ExtendDataList));
	if (xData) {
		memset(xData, 0, sizeof(ExtendDataList));
		if (pExtraDataList)
			if (xData->AddAt(pExtraDataList, eListEnd) == eListInvalid) {
				GameHeapFree(xData);
				xData = NULL;
			}
	}
	return xData;
}

void ExtendDataList::Free(ExtendDataList* xData, bool bFreeList)
{
	if (xData)
	{
		if (bFreeList)
		{
			UInt32 i = 0;
			ExtraDataList* pExtraDataList = xData->GetNth(i);
			while (pExtraDataList)
			{
				for (UInt32 j = 0; j < 0xFF; j++)
					pExtraDataList->RemoveByType(j);
				i++;
				pExtraDataList = xData->GetNth(i);
			}
		}
		GameHeapFree(xData);
	}
}

bool ExtendDataList::Add(ExtendDataList* xData, ExtraDataList* xList) {
	if (xData && xList) {
		xData->AddAt(xList, eListEnd);
		return true;
	}
	return false;
}

bool ExtendDataList::Remove(ExtendDataList* xData, ExtraDataList* xList, bool bFreeList) {
	if (xData && xList) {
		UInt32 i = 0;
		ExtraDataList* pExtraDataList = xData->GetNth(i);
		while (pExtraDataList && pExtraDataList != xList) {
			i++;
			pExtraDataList = xData->GetNth(i);
		}
		if (pExtraDataList == xList) {
			xData->RemoveNth(i);
			if (bFreeList) {
				for (UInt32 j = 0; j < 0xFF; j++)
					pExtraDataList->RemoveByType(j);
				GameHeapFree(xList);
			}
			return true;
		}
	}
	return false;
}

bool BaseExtraList::MarkScriptEvent(UInt32 eventMask, TESForm* eventTarget)
{
	return MarkBaseExtraListScriptEvent(eventTarget, this, eventMask);
}

void InventoryChanges::Free(bool bFreeList) {
	if (this->extendData) {
		ExtendDataList::Free(this->extendData, bFreeList);
	}
	GameHeapFree(this);
}


// Finds an Item (type) in an EntryDataList
class ItemInEntryDataListMatcher
{
	TESForm* m_toMatch;
public:
	ItemInEntryDataListMatcher(TESForm* match) : m_toMatch(match) { }

	bool Accept(InventoryChanges* match) { return (match && m_toMatch == match->form); }
};


class ExtraFactionChangesMatcher
{
	TESFaction* pFaction;
	ExtraFactionChanges* xFactionChanges;
public:
	ExtraFactionChangesMatcher(TESFaction* faction, ExtraFactionChanges* FactionChanges) : pFaction(faction), xFactionChanges(FactionChanges) {}
	bool Accept(const FactionListEntry* data) { return data->faction == pFaction; }
};

// Finds an ExtendDataList in an EntryDataList
class ExtendDataListInEntryDataListMatcher
{
	ExtendDataList* m_toMatch;
public:
	ExtendDataListInEntryDataListMatcher(ExtendDataList* match) : m_toMatch(match) { }

	bool Accept(InventoryChanges* match) { return match && match->extendData ? match->extendData == m_toMatch : false; }
};

// Finds an Item from its base form in an EntryDataList
class BaseInEntryDataLastMatcher
{
	TESForm* m_toMatch;
public:
	BaseInEntryDataLastMatcher(TESForm* match) : m_toMatch(match) { }

	bool Accept(InventoryChanges* match) { return (match && match->form && m_toMatch == match->form->TryGetREFRParent()); }
};

// Finds an item by refID in an EntryDataList
class RefIDInEntryDataListMatcher
{
	UInt32 m_toMatch;
public:
	RefIDInEntryDataListMatcher(UInt32 match) : m_toMatch(match) { }

	bool Accept(InventoryChanges* match) { return (match && match->form && m_toMatch == match->form->refID); }
};

// Finds an item by the refID of its base form in an EntryDataList
class BaseIDInEntryDataListMatcher
{
	UInt32 m_toMatch;
public:
	BaseIDInEntryDataListMatcher(UInt32 match) : m_toMatch(match) { }

	bool Accept(InventoryChanges* match) { return (match && match->form && match->form->TryGetREFRParent() && m_toMatch == match->form->TryGetREFRParent()->refID); }
};


InventoryChangesList* InventoryChangesList::Create(UInt32 refID, UInt32 count, ExtendDataList* pExtendDataList)
{
	const auto xData = (InventoryChangesList*)GameHeapAlloc(sizeof(InventoryChangesList));
	if (xData) {
		memset(xData, 0, sizeof(InventoryChangesList));
		xData->AddAt(InventoryChanges::Create(TESForm::GetByID(refID), count, pExtendDataList), eListEnd);
	}
	return xData;
}

void InventoryChangesList::Free(bool bFreeList) {
	UInt32 i = 0;
	InventoryChanges* pX = this->GetNth(i);
	while (pX) {
		pX->Free(bFreeList);
		i++;
		pX = this->GetNth(i);
	}
	GameHeapFree(this);
}

static const UInt32 s_ExtraContainerChangesVtbl = 0x01015BB8;	//	0x0100fb78;
static const UInt32 s_ExtraWornVtbl = 0x01015BDC;
//static const UInt32 s_ExtraWornLeftVtbl							= 0x01015BE8;
static const UInt32 s_ExtraCannotWearVtbl = 0x01015BF4;

static const UInt32 s_ExtraOwnershipVtbl = 0x010158B4;	//	0x0100f874;
static const UInt32 s_ExtraRankVtbl = 0x010158CC;	//	0x0100f88c;
static const UInt32 s_ExtraActionVtbl = 0x01015BAC;
static const UInt32 s_ExtraFactionChangesVtbl = 0x01015F30;
static const UInt32 s_ExtraScriptVtbl = 0X1015914;

//static const UInt32 s_ExtraScript_init							= 0x0042C760;

static const UInt32 s_ExtraHealthVtbl = 0x010158E4;
static const UInt32 s_ExtraLockVtbl = 0x0101589C;
static const UInt32 s_ExtraCountVtbl = 0x010158D8;
static const UInt32 s_ExtraTeleportVtbl = 0x010158A8;
static const UInt32 s_ExtraWeaponModFlagsVtbl = 0x010159A4;

static const UInt32 s_ExtraHotkeyVtbl = 0x0101592C;

static const UInt32 s_ExtraSemaphore = 0x011C3920;
static const UInt32 s_SemaphoreWait = 0x0040FBF0;
static const UInt32 s_SemaphoreLeave = 0x0040FBA0;

static void** g_ExtraSemaphore = (void**)s_ExtraSemaphore;

void* GetExtraSemaphore()
{
	return *g_ExtraSemaphore;
};

void CallSemaphore(void* Semaphore, UInt32 SemaphoreFunc)
{
	_asm pushad
	_asm mov ecx, Semaphore
	_asm call SemaphoreFunc
	_asm popad
};

void CallSemaphore4(void* Semaphore, UInt32 SemaphoreFunc)
{
	_asm pushad
	_asm push ecx;	does not seem to be used at all
	_asm mov ecx, Semaphore
	_asm call SemaphoreFunc
	_asm popad
};


ExtraContainerChanges* ExtraContainerChanges::Create()
{
	const auto xChanges = (ExtraContainerChanges*)BSExtraData::Create(kExtraData_ContainerChanges, sizeof(ExtraContainerChanges), s_ExtraContainerChangesVtbl);
	xChanges->data = nullptr;
	return xChanges;
}

ExtraContainerChanges* ExtraContainerChanges::Create(TESObjectREFR* thisObj, UInt32 refID, UInt32 count, ExtendDataList* pExtendDataList)
{
	const auto xData = (ExtraContainerChanges*)BSExtraData::Create(kExtraData_ContainerChanges, sizeof(ExtraContainerChanges), s_ExtraContainerChangesVtbl);
	if (xData) {
		xData->data = ExtraContainerChangesData::Create(thisObj);
		if (refID) {
			xData->data->objList = InventoryChangesList::Create(refID, count, pExtendDataList);
		}
	}
	return xData;
}


Float64 ExtraContainerChangesData::GetInventoryWeight()
{
	return ThisCall<Float64>(0x4D0900, this, PlayerCharacter::GetSingleton()->isHardcore);
}

void ExtraContainerChangesFree(ExtraContainerChanges* xData, bool bFreeList) {
	if (xData) {
		if (xData->data) {
			if (xData->data->objList && bFreeList) {
				xData->data->objList->Free(true);
			}
			GameHeapFree(xData->data);
		}
		GameHeapFree(xData);
	}
}

void ExtraContainerChangesData::Cleanup()
{
	if (objList) {
		for (const auto iter : *objList) {
			iter->Cleanup();

			// make sure we don't have any NULL ExtraDataList's in extend data, game will choke when saving
			if (iter->extendData == nullptr) continue;

			for (SInt32 index = 0; index < iter->extendData->count(); ) {
				if (const auto xtendData = iter->extendData->GetNth(index); xtendData && !xtendData->m_data) {
					iter->extendData->RemoveNth(index);
					GameHeapFree(xtendData);
				}
				else index++;
			}
		}
	}
}

ExtraDataList* ExtraContainerChangesData::SetEquipped(TESForm* obj, bool bEquipped, bool bForce)
{
	if (true) {
		if (const auto xData = objList->Find(ItemInEntryDataListMatcher(obj))) {
			ExtraDataList* Possible = nullptr;
			if (xData->extendData && (xData->extendData->count() > 0))
				for (const auto iter : *xData->extendData)
					if (iter->HasType(kExtraData_Worn) || iter->HasType(kExtraData_WornLeft)) {
						if (!bEquipped)
							if (bForce || !iter->HasType(kExtraData_WornLeft)) {
								iter->RemoveByType(kExtraData_Worn);
								iter->RemoveByType(kExtraData_WornLeft);
								Cleanup();
								return iter;
							}

					}
					else if (bEquipped && (bForce || !iter->HasType(kExtraData_CannotWear)))
						Possible = iter;
			if (!xData->extendData)
				xData->extendData = ExtendDataList::Create(nullptr);
			if (Possible) {
				Possible->Add(ExtraWorn::Create());
				return Possible;
			}
		}
	}
	return nullptr;
}

bool ExtraContainerChangesData::Remove(TESForm* obj, ExtraDataList* dataList, bool bFree)
{
	for (UInt32 i = 0; i < objList->count(); i++)
		if (objList->GetNth(i)->form == obj) {
			if (const auto found = objList->GetNth(i); dataList && found->extendData) {
				for (UInt32 j = 0; j < found->extendData->count(); j++)
					if (found->extendData->GetNth(j) == dataList)
						found->extendData->RemoveNth(j);
			}
			else if (!dataList && !found->extendData)
				objList->RemoveNth(i);
		}
	return false;
}

ExtraContainerChanges* ExtraContainerChanges::GetForRef(TESObjectREFR* refr)
{
	auto xChanges = reinterpret_cast<ExtraContainerChanges*>(refr->extraDataList.GetByType(kExtraData_ContainerChanges));
	if (!xChanges) {
		xChanges = Create();
		refr->extraDataList.Add(xChanges);
	}
	return xChanges;
}

UInt32 ExtraContainerChangesData::GetAllEquipped(std::vector<InventoryChanges*>& outEntryData)
{
	if (objList) for (const auto entry : *objList)
	{
		if (entry->extendData) for (const auto extraDataList : *entry->extendData)
		{
			if (extraDataList->HasType(kExtraData_Worn)) outEntryData.push_back(entry);
		}
	}
	return outEntryData.size();
}

// static
BSExtraData* BSExtraData::Create(UInt8 xType, UInt32 size, UInt32 vtbl)
{
	void* memory = GameHeapAlloc(size);
	memset(memory, 0, size);
	static_cast<UInt32*>(memory)[0] = vtbl;
	const auto xData = static_cast<BSExtraData*>(memory);
	xData->type = xType;
	return xData;
}

ExtraHealth* ExtraHealth::Create()
{
	const auto xHealth = (ExtraHealth*)BSExtraData::Create(kExtraData_Health, sizeof(ExtraHealth), s_ExtraHealthVtbl);
	return xHealth;
}

ExtraWorn* ExtraWorn::Create()
{
	const auto xWorn = (ExtraWorn*)BSExtraData::Create(kExtraData_Worn, sizeof(ExtraWorn), s_ExtraWornVtbl);
	return xWorn;
}

//ExtraWornLeft* ExtraWornLeft::Create() 
//{
//	ExtraWornLeft* xWornLeft = (ExtraWornLeft*)BSExtraData::Create(kExtraData_WornLeft, sizeof(ExtraWornLeft), s_ExtraWornLeftVtbl);
//	return xWornLeft;
//}

ExtraCannotWear* ExtraCannotWear::Create()
{
	const auto xCannotWear = (ExtraCannotWear*)BSExtraData::Create(kExtraData_CannotWear, sizeof(ExtraCannotWear), s_ExtraCannotWearVtbl);
	return xCannotWear;
}

ExtraLock* ExtraLock::Create()
{
	const auto xLock = (ExtraLock*)BSExtraData::Create(kExtraData_Lock, sizeof(ExtraLock), s_ExtraLockVtbl);
	const auto lockData = (ExtraLockData*)GameHeapAlloc(sizeof(ExtraLockData));
	memset(lockData, 0, sizeof(ExtraLockData));
	xLock->data = lockData;
	return xLock;
}

ExtraCount* ExtraCount::Create(UInt32 count)
{
	const auto xCount = (ExtraCount*)BSExtraData::Create(kExtraData_Count, sizeof(ExtraCount), s_ExtraCountVtbl);
	xCount->count = count;
	return xCount;
}

ExtraTeleport* ExtraTeleport::Create()
{
	const auto tele = (ExtraTeleport*)BSExtraData::Create(kExtraData_Teleport, sizeof(ExtraTeleport), s_ExtraTeleportVtbl);

	// create data
	const auto data = (ExtraTeleportData*)GameHeapAlloc(sizeof(ExtraTeleportData));
	data->linkedDoor = NULL;
	data->yRot = -0.0;
	data->xRot = 0.0;
	data->x = 0.0;
	data->y = 0.0;
	data->z = 0.0;
	data->zRot = 0.0;

	tele->data = data;
	return tele;
}

ExtraWeaponModFlags* ExtraWeaponModFlags::Create()
{
	const auto xWeaponModFlags = (ExtraWeaponModFlags*)BSExtraData::Create(kExtraData_WeaponModFlags, sizeof(ExtraWeaponModFlags), s_ExtraWeaponModFlagsVtbl);

	xWeaponModFlags->flags = 0;

	return xWeaponModFlags;
}

SInt32 GetCountForExtraDataList(ExtraDataList* list)
{
	if (!list)
		return 1;

	const auto xCount = (ExtraCount*)list->GetByType(kExtraData_Count);
	return xCount ? xCount->count : 1;
}

ExtraOwnership* ExtraOwnership::Create()
{
	const auto xOwner = (ExtraOwnership*)BSExtraData::Create(kExtraData_Ownership, sizeof(ExtraOwnership), s_ExtraOwnershipVtbl);
	return xOwner;
}

ExtraRank* ExtraRank::Create()
{
	const auto xRank = (ExtraRank*)BSExtraData::Create(kExtraData_Rank, sizeof(ExtraRank), s_ExtraRankVtbl);
	return xRank;
}

ExtraAction* ExtraAction::Create()
{
	const auto xAction = (ExtraAction*)BSExtraData::Create(kExtraData_Action, sizeof(ExtraAction), s_ExtraActionVtbl);
	return xAction;
}

const char* GetExtraDataName(UInt8 ExtraDataType) {
	switch (ExtraDataType) {
	case	kExtraData_Havok: return "Havok"; break;
	case	kExtraData_Cell3D: return "Cell3D"; break;
	case	kExtraData_CellWaterType: return "CellWaterType"; break;
	case	kExtraData_RegionList: return "RegionList"; break;
	case	kExtraData_SeenData: return "SeenData"; break;
	case	kExtraData_CellMusicType: return "CellMusicType"; break;
	case	kExtraData_CellClimate: return "CellClimate"; break;
	case	kExtraData_ProcessMiddleLow: return "ProcessMiddleLow"; break;
	case	kExtraData_CellCanopyShadowMask: return "CellCanopyShadowMask"; break;
	case	kExtraData_DetachTime: return "DetachTime"; break;
	case	kExtraData_PersistentCell: return "PersistentCell"; break;
	case	kExtraData_Script: return "Script"; break;
	case	kExtraData_Action: return "Action"; break;
	case	kExtraData_StartingPosition: return "StartingPosition"; break;
	case	kExtraData_Anim: return "Anim"; break;
	case	kExtraData_UsedMarkers: return "UsedMarkers"; break;
	case	kExtraData_DistantData: return "DistantData"; break;
	case	kExtraData_RagdollData: return "RagdollData"; break;
	case	kExtraData_ContainerChanges: return "ContainerChanges"; break;
	case	kExtraData_Worn: return "Worn"; break;
	case	kExtraData_WornLeft: return "WornLeft"; break;
	case	kExtraData_PackageStartLocation: return "PackageStartLocation"; break;
	case	kExtraData_Package: return "Package"; break;
	case	kExtraData_TrespassPackage: return "TrespassPackage"; break;
	case	kExtraData_RunOncePacks: return "RunOncePacks"; break;
	case	kExtraData_ReferencePointer: return "ReferencePointer"; break;
	case	kExtraData_Follower: return "Follower"; break;
	case	kExtraData_LevCreaModifier: return "LevCreaModifier"; break;
	case	kExtraData_Ghost: return "Ghost"; break;
	case	kExtraData_OriginalReference: return "OriginalReference"; break;
	case	kExtraData_Ownership: return "Ownership"; break;
	case	kExtraData_Global: return "Global"; break;
	case	kExtraData_Rank: return "Rank"; break;
	case	kExtraData_Count: return "Count"; break;
	case	kExtraData_Health: return "Health"; break;
	case	kExtraData_Uses: return "Uses"; break;
	case	kExtraData_TimeLeft: return "TimeLeft"; break;
	case	kExtraData_Charge: return "Charge"; break;
	case	kExtraData_Light: return "Light"; break;
	case	kExtraData_Lock: return "Lock"; break;
	case	kExtraData_Teleport: return "Teleport"; break;
	case	kExtraData_MapMarker: return "MapMarker"; break;
	case	kExtraData_LeveledCreature: return "LeveledCreature"; break;
	case	kExtraData_LeveledItem: return "LeveledItem"; break;
	case	kExtraData_Scale: return "Scale"; break;
	case	kExtraData_Seed: return "Seed"; break;
	case	kExtraData_PlayerCrimeList: return "PlayerCrimeList"; break;
	case	kExtraData_EnableStateParent: return "EnableStateParent"; break;
	case	kExtraData_EnableStateChildren: return "EnableStateChildren"; break;
	case	kExtraData_ItemDropper: return "ItemDropper"; break;
	case	kExtraData_DroppedItemList: return "DroppedItemList"; break;
	case	kExtraData_RandomTeleportMarker: return "RandomTeleportMarker"; break;
	case	kExtraData_MerchantContainer: return "MerchantContainer"; break;
	case	kExtraData_SavedHavokData: return "SavedHavokData"; break;
	case	kExtraData_CannotWear: return "CannotWear"; break;
	case	kExtraData_Poison: return "Poison"; break;
	case	kExtraData_LastFinishedSequence: return "LastFinishedSequence"; break;
	case	kExtraData_SavedAnimation: return "SavedAnimation"; break;
	case	kExtraData_NorthRotation: return "NorthRotation"; break;
	case	kExtraData_XTarget: return "XTarget"; break;
	case	kExtraData_FriendHits: return "FriendHits"; break;
	case	kExtraData_HeadingTarget: return "HeadingTarget"; break;
	case	kExtraData_RefractionProperty: return "RefractionProperty"; break;
	case	kExtraData_StartingWorldOrCell: return "StartingWorldOrCell"; break;
	case	kExtraData_Hotkey: return "Hotkey"; break;
	case	kExtraData_EditorRefMovedData: return "EditorRefMovedData"; break;
	case	kExtraData_InfoGeneralTopic: return "InfoGeneralTopic"; break;
	case	kExtraData_HasNoRumors: return "HasNoRumors"; break;
	case	kExtraData_Sound: return "Sound"; break;
	case	kExtraData_TerminalState: return "TerminalState"; break;
	case	kExtraData_LinkedRef: return "LinkedRef"; break;
	case	kExtraData_LinkedRefChildren: return "LinkedRefChildren"; break;
	case	kExtraData_ActivateRef: return "ActivateRef"; break;
	case	kExtraData_ActivateRefChildren: return "ActivateRefChildren"; break;
	case	kExtraData_TalkingActor: return "TalkingActor"; break;
	case	kExtraData_ObjectHealth: return "ObjectHealth"; break;
	case	kExtraData_DecalRefs: return "DecalRefs"; break;
	case	kExtraData_CellImageSpace: return "CellImageSpace"; break;
	case	kExtraData_NavMeshPortal: return "NavMeshPortal"; break;
	case	kExtraData_ModelSwap: return "ModelSwap"; break;
	case	kExtraData_Radius: return "Radius"; break;
	case	kExtraData_Radiation: return "Radiation"; break;
	case	kExtraData_FactionChanges: return "FactionChanges"; break;
	case	kExtraData_DismemberedLimbs: return "DismemberedLimbs"; break;
	case	kExtraData_MultiBound: return "MultiBound"; break;
	case	kExtraData_MultiBoundData: return "MultiBoundData"; break;
	case	kExtraData_MultiBoundRef: return "MultiBoundRef"; break;
	case	kExtraData_ReflectedRefs: return "ReflectedRefs"; break;
	case	kExtraData_ReflectorRefs: return "ReflectorRefs"; break;
	case	kExtraData_EmittanceSource: return "EmittanceSource"; break;
	case	kExtraData_RadioData: return "RadioData"; break;
	case	kExtraData_CombatStyle: return "CombatStyle"; break;
	case	kExtraData_Primitive: return "Primitive"; break;
	case	kExtraData_OpenCloseActivateRef: return "OpenCloseActivateRef"; break;
	case	kExtraData_AnimNoteReciever: return "AnimNoteReciever"; break;
	case	kExtraData_Ammo: return "Ammo"; break;
	case	kExtraData_PatrolRefData: return "PatrolRefData"; break;
	case	kExtraData_PackageData: return "PackageData"; break;
	case	kExtraData_OcclusionPlane: return "OcclusionPlane"; break;
	case	kExtraData_CollisionData: return "CollisionData"; break;
	case	kExtraData_SayTopicInfoOnceADay: return "SayTopicInfoOnceADay"; break;
	case	kExtraData_EncounterZone: return "EncounterZone"; break;
	case	kExtraData_SayToTopicInfo: return "SayToTopicInfo"; break;
	case	kExtraData_OcclusionPlaneRefData: return "OcclusionPlaneRefData"; break;
	case	kExtraData_PortalRefData: return "PortalRefData"; break;
	case	kExtraData_Portal: return "Portal"; break;
	case	kExtraData_Room: return "Room"; break;
	case	kExtraData_HealthPerc: return "HealthPerc"; break;
	case	kExtraData_RoomRefData: return "RoomRefData"; break;
	case	kExtraData_GuardedRefData: return "GuardedRefData"; break;
	case	kExtraData_CreatureAwakeSound: return "CreatureAwakeSound"; break;
	case	kExtraData_WaterZoneMap: return "WaterZoneMap"; break;
	case	kExtraData_IgnoredBySandbox: return "IgnoredBySandbox"; break;
	case	kExtraData_CellAcousticSpace: return "CellAcousticSpace"; break;
	case	kExtraData_ReservedMarkers: return "ReservedMarkers"; break;
	case	kExtraData_WeaponIdleSound: return "WeaponIdleSound"; break;
	case	kExtraData_WaterLightRefs: return "WaterLightRefs"; break;
	case	kExtraData_LitWaterRefs: return "LitWaterRefs"; break;
	case	kExtraData_WeaponAttackSound: return "WeaponAttackSound"; break;
	case	kExtraData_ActivateLoopSound: return "ActivateLoopSound"; break;
	case	kExtraData_PatrolRefInUseData: return "PatrolRefInUseData"; break;
	case	kExtraData_AshPileRef: return "AshPileRef"; break;
	case	kExtraData_CreatureMovementSound: return "CreatureMovementSound"; break;
	case	kExtraData_FollowerSwimBreadcrumbs: return "FollowerSwimBreadcrumbs"; break;
	};
	return "unknown";
}

ExtraScript* ExtraScript::Create(TESScriptableForm* pScript, bool create, TESObjectREFR* container) {
	const auto xScript = reinterpret_cast<ExtraScript*>(BSExtraData::Create(kExtraData_Script, sizeof(ExtraScript), s_ExtraScriptVtbl));
	if (xScript && (pScript && pScript->script)) {
		xScript->script = pScript->script;
		if (create) {
			xScript->eventList = xScript->script->CreateEventList();
			if (container)
				xScript->eventList->EventCreate(ScriptEventList::kEvent_OnAdd, container);
		}
	}
	return xScript;
}

ExtraFactionChanges* ExtraFactionChanges::Create()
{
	const auto xFactionChanges = (ExtraFactionChanges*)BSExtraData::Create(kExtraData_FactionChanges, sizeof(ExtraFactionChanges), s_ExtraFactionChangesVtbl);
	const auto FactionChangesData = (FactionListData*)GameHeapAlloc(sizeof(FactionListData));
	memset(FactionChangesData, 0, sizeof(FactionListData));
	xFactionChanges->data = FactionChangesData;
	return xFactionChanges;
}

FactionListData* GetExtraFactionList(BaseExtraList& xDataList)
{
	const auto xFactionChanges = GetByTypeCast(xDataList, FactionChanges);
	if (xFactionChanges)
		return xFactionChanges->data;
	return NULL;
}

SInt8 GetExtraFactionRank(BaseExtraList& xDataList, TESFaction* faction)
{
	const auto xFactionChanges = GetByTypeCast(xDataList, FactionChanges);
	if (xFactionChanges && xFactionChanges->data) {
		ExtraFactionChangesMatcher matcher(faction, xFactionChanges);
		FactionListEntry* pData = xFactionChanges->data->Find(matcher);
		return (pData) ? pData->rank : -1;
	}
	return -1;
}

void SetExtraFactionRank(BaseExtraList& xDataList, TESFaction* faction, SInt8 rank)
{
	FactionListEntry* pData = NULL;
	auto xFactionChanges = GetByTypeCast(xDataList, FactionChanges);
	if (xFactionChanges && xFactionChanges->data) {
		ExtraFactionChangesMatcher matcher(faction, xFactionChanges);
		pData = xFactionChanges->data->Find(matcher);
		if (pData)
			pData->rank = rank;
	}
	if (!pData) {
		if (!xFactionChanges) {
			xFactionChanges = ExtraFactionChanges::Create();
			xDataList.Add(xFactionChanges);
		}
		pData = (FactionListEntry*)GameHeapAlloc(sizeof(FactionListEntry));
		if (pData) {
			pData->faction = faction;
			pData->rank = rank;
			xFactionChanges->data->AddAt(pData, -2);
		}
	}
}

ExtraHotkey* ExtraHotkey::Create()
{
	const auto xHotkey = (ExtraHotkey*)BSExtraData::Create(kExtraData_Hotkey, sizeof(ExtraHotkey), s_ExtraHotkeyVtbl);
	xHotkey->index = 0;
	return xHotkey;
}

{
	kAddr_LoadModel = 0x447080,
	kAddr_ApplyAmmoEffects = 0x59A030,
	kAddr_MoveToMarker = 0x5CCB20,
	kAddr_ApplyPerkModifiers = 0x5E58F0,
	kAddr_ReturnThis = 0x6815C0,
	kAddr_PurgeTerminalModel = 0x7FFE00,
	kAddr_EquipItem = 0x88C650,
	kAddr_UnequipItem = 0x88C790,
	kAddr_ReturnTrue = 0x8D0360,
	kAddr_InitFontInfo = 0xA12020,
	kAddr_GetItemValue = 0x4BD400,
	kAddr_EvaluateConditions = 0x680C60,
	kAddr_EvaluateCondition = 0x681600,
};


// NOT VANILLA, USED FOR CONVENIENCE
class ValueCaster
{
	Value* ptr;
public:
	ValueCaster(Value* ptr = nullptr) : ptr(ptr) {};
	explicit operator bool() const { return ptr; }
	operator Float32() const { return ptr && ptr->num ? ptr->num : 0.0; }
	explicit operator UInt32() const { return ptr && ptr->num ? ptr->num : 0; }
	operator const char*() const { return ptr && ptr->str ? ptr->str : ""; }
};


enum ObjectVtbl
{

	kVtbl_BGSDehydrationStage = 0x101144C,
	kVtbl_BGSHungerStage = 0x10115B4,
	kVtbl_BGSSleepDeprevationStage = 0x10116FC,
	kVtbl_AlchemyItem = 0x1011964,
	kVtbl_MagicItemObject = 0x1011B4C,
	kVtbl_TESIcon = 0x1011CD4,
	kVtbl_MagicItem = 0x1011D0C,
	kVtbl_TESFullName = 0x1011D54,
	kVtbl_BaseFormComponent = 0x1011D68,
	kVtbl_Setting = 0x1012120,
	kVtbl_GameSettingCollection = 0x101212C,
	kVtbl_EffectItemList = 0x1012508,
	kVtbl_EffectSetting = 0x1012834,
	kVtbl_EnchantmentItem = 0x1012EA4,
	kVtbl_MagicItemForm = 0x1013044,
	kVtbl_IngredientItem = 0x1013284,
	kVtbl_SpellItem = 0x1013F8C,
	kVtbl_ExtraCell3D = 0x1014204,
	kVtbl_BSExtraData = 0x1014210,
	kVtbl_ExtraHavok = 0x101421C,
	kVtbl_ExtraRegionList = 0x1014228,
	kVtbl_ExtraCellMusicType = 0x1014234,
	kVtbl_ExtraCellAcousticSpace = 0x1014240,
	kVtbl_ExtraCellClimate = 0x101424C,
	kVtbl_ExtraCellImageSpace = 0x1014258,
	kVtbl_ExtraCellImpactSwap = 0x1014264,
	kVtbl_ExtraCellWaterType = 0x1014270,
	kVtbl_ExtraProcessMiddleLow = 0x101427C,
	kVtbl_ExtraCellCanopyShadowMask = 0x1014288,
	kVtbl_ExtraSeenData = 0x1014294,
	kVtbl_ExtraNorthRotation = 0x10142A0,
	kVtbl_ExtraDetachTime = 0x10142AC,
	kVtbl_BaseExtraList = 0x1014300,
	kVtbl_ExtraDataList = 0x10143E8,
	kVtbl_ExtraReflectedRefs = 0x1014428,
	kVtbl_ExtraReflectorRefs = 0x1014434,
	kVtbl_ExtraWaterLightRefs = 0x1014440,
	kVtbl_ExtraLitWaterRefs = 0x101444C,
	kVtbl_ExtraSpecialRenderFlags = 0x1014458,
	kVtbl_ExtraNavMeshPortal = 0x1014618,
	kVtbl_ExtraRadioData = 0x1015138,
	kVtbl_ExtraHealthPerc = 0x1015178,
	kVtbl_ExtraObjectHealth = 0x1015184,
	kVtbl_ExtraTerminalState = 0x1015190,
	kVtbl_ExtraEditorID = 0x101519C,
	kVtbl_ExtraOpenCloseActivateRef = 0x10151A8,
	kVtbl_ExtraPrimitive = 0x10151B4,
	kVtbl_ExtraPatrolRefData = 0x10151C0,
	kVtbl_ExtraOcclusionPlaneRefData = 0x10151CC,
	kVtbl_ExtraPortalRefData = 0x10151D8,
	kVtbl_ExtraRoomRefData = 0x10151E4,
	kVtbl_ExtraCollisionData = 0x10151F0,
	kVtbl_ExtraPackageData = 0x10151FC,
	kVtbl_ExtraRadius = 0x1015208,
	kVtbl_ExtraRadiation = 0x1015214,
	kVtbl_ExtraLock = 0x101589C,
	kVtbl_ExtraTeleport = 0x10158A8,
	kVtbl_ExtraOwnership = 0x10158B4,
	kVtbl_ExtraGlobal = 0x10158C0,
	kVtbl_ExtraRank = 0x10158CC,
	kVtbl_ExtraCount = 0x10158D8,
	kVtbl_ExtraHealth = 0x10158E4,
	kVtbl_ExtraUses = 0x10158F0,
	kVtbl_ExtraTimeLeft = 0x10158FC,
	kVtbl_ExtraCharge = 0x1015908,
	kVtbl_ExtraScript = 0x1015914,
	kVtbl_ExtraScale = 0x1015920,
	kVtbl_ExtraHotkey = 0x101592C,
	kVtbl_ExtraReferencePointer = 0x1015938,
	kVtbl_ExtraTresPassPackage = 0x1015944,
	kVtbl_ExtraLeveledItem = 0x1015950,
	kVtbl_ExtraPoison = 0x101595C,
	kVtbl_ExtraHeadingTarget = 0x1015968,
	kVtbl_ExtraHasNoRumors = 0x1015974,
	kVtbl_ExtraModelSwap = 0x1015980,
	kVtbl_ExtraActorCause = 0x101598C,
	kVtbl_ExtraAmmo = 0x1015998,
	kVtbl_ExtraWeaponModFlags = 0x10159A4,
	kVtbl_ExtraSecuritronFace = 0x10159B0,
	kVtbl_ExtraModdingItem = 0x10159BC,
	kVtbl_ExtraCombatStyle = 0x10159C8,
	kVtbl_ExtraAnim = 0x1015B28,
	kVtbl_ExtraDismemberedLimbs = 0x1015B34,
	kVtbl_ExtraStartingPosition = 0x1015B40,
	kVtbl_ExtraStartingWorldOrCell = 0x1015B4C,
	kVtbl_ExtraLight = 0x1015B58,
	kVtbl_ExtraFollower = 0x1015B64,
	kVtbl_ExtraGuardedRefData = 0x1015B70,
	kVtbl_ExtraLeveledCreature = 0x1015B7C,
	kVtbl_ExtraMapMarker = 0x1015B88,
	kVtbl_ExtraAudioMarker = 0x1015B94,
	kVtbl_ExtraAudioBuoyMarker = 0x1015BA0,
	kVtbl_ExtraAction = 0x1015BAC,
	kVtbl_ExtraContainerChanges = 0x1015BB8,
	kVtbl_ExtraOriginalReference = 0x1015BC4,
	kVtbl_ExtraGhost = 0x1015BD0,
	kVtbl_ExtraWorn = 0x1015BDC,
	kVtbl_ExtraWornLeft = 0x1015BE8,
	kVtbl_ExtraCannotWear = 0x1015BF4,
	kVtbl_ExtraInfoGeneralTopic = 0x1015C00,
	kVtbl_ExtraSeed = 0x1015C0C,
	kVtbl_ExtraPackageStartLocation = 0x1015C18,
	kVtbl_ExtraPackage = 0x1015C24,
	kVtbl_ExtraPlayerCrimeList = 0x1015C30,
	kVtbl_ExtraPersistentCell = 0x1015C3C,
	kVtbl_ExtraRagDollData = 0x1015C48,
	kVtbl_ExtraEncounterZone = 0x1015C54,
	kVtbl_ExtraUsedMarkers = 0x1015C60,
	kVtbl_ExtraReservedMarkers = 0x1015C6C,
	kVtbl_ExtraRunOncePacks = 0x1015C78,
	kVtbl_ExtraDistantData = 0x1015C84,
	kVtbl_ExtraEnableStateParent = 0x1015C90,
	kVtbl_ExtraEnableStateChildren = 0x1015C9C,
	kVtbl_ExtraRandomTeleportMarker = 0x1015CA8,
	kVtbl_ExtraLinkedRefChildren = 0x1015CB4,
	kVtbl_ExtraLinkedRef = 0x1015CC0,
	kVtbl_ExtraAshPileRef = 0x1015CCC,
	kVtbl_ExtraActivateRefChildren = 0x1015CD8,
	kVtbl_ExtraActivateRef = 0x1015CE4,
	kVtbl_ExtraDecalRefs = 0x1015CF0,
	kVtbl_ExtraMerchantContainer = 0x1015E04,
	kVtbl_ExtraLevCreaModifier = 0x1015E10,
	kVtbl_ExtraLastFinishedSequence = 0x1015E1C,
	kVtbl_ExtraXTarget = 0x1015E28,
	kVtbl_ExtraEmittanceSource = 0x1015E34,
	kVtbl_ExtraMultiBoundRef = 0x1015E40,
	kVtbl_ExtraMultiBoundData = 0x1015E4C,
	kVtbl_ExtraMultiBound = 0x1015E58,
	kVtbl_ExtraOcclusionPlane = 0x1015E64,
	kVtbl_ExtraPortal = 0x1015E70,
	kVtbl_ExtraRoom = 0x1015E7C,
	kVtbl_ExtraItemDropper = 0x1015E88,
	kVtbl_ExtraDroppedItemList = 0x1015E94,
	kVtbl_ExtraSavedAnimation = 0x1015EA0,
	kVtbl_ExtraSavedHavokData = 0x1015EAC,
	kVtbl_ExtraFriendHits = 0x1015EB8,
	kVtbl_ExtraRefractionProperty = 0x1015EC4,
	kVtbl_ExtraEditorRefMoveData = 0x1015ED0,
	kVtbl_ExtraSound = 0x1015EDC,
	kVtbl_ExtraCreatureAwakeSound = 0x1015EE8,
	kVtbl_ExtraCreatureMovementSound = 0x1015EF4,
	kVtbl_ExtraWeaponIdleSound = 0x1015F00,
	kVtbl_ExtraWeaponAttackSound = 0x1015F0C,
	kVtbl_ExtraActivateLoopSound = 0x1015F18,
	kVtbl_ExtraTalkingActor = 0x1015F24,
	kVtbl_ExtraFactionChanges = 0x1015F30,
	kVtbl_ExtraSayTopicInfoOnceADay = 0x1015F3C,
	kVtbl_ExtraSayToTopicInfo = 0x1015F48,
	kVtbl_ExtraWaterZoneMap = 0x1015F54,
	kVtbl_ExtraIgnoredBySandbox = 0x1015F64,
	kVtbl_ExtraPatrolRefInUseData = 0x1015F70,
	kVtbl_ExtraFollowerSwimBreadcrumbs = 0x1015F7C,
	kVtbl_NiAlphaProperty = 0x10162DC,
	kVtbl_NiProperty = 0x1016374,
	kVtbl_QueuedTexture = 0x1016788,
	kVtbl_QueuedModel = 0x1016890,
	kVtbl_BSStream = 0x1016904,
	kVtbl_QueuedTreeBillboard = 0x101698C,
	kVtbl_QueuedTreeModel = 0x10169D4,
	kVtbl_QueuedMagicItem = 0x1016A18,
	kVtbl_QueuedKF = 0x1016A48,
	kVtbl_QueuedAnimIdle = 0x1016A80,
	kVtbl_QueuedReplacementKF = 0x1016AC0,
	kVtbl_QueuedHead = 0x1016B04,
	kVtbl_QueuedHelmet = 0x1016B4C,
	kVtbl_QueuedReference = 0x1016BA4,
	kVtbl_AttachDistant3DTask = 0x1016BEC,
	kVtbl_IOTask = 0x1016C10,
	kVtbl_QueuedTree = 0x1016C5C,
	kVtbl_QueuedActor = 0x1016CA4,
	kVtbl_QueuedCharacter = 0x1016CEC,
	kVtbl_QueuedCreature = 0x1016D34,
	kVtbl_QueuedPlayer = 0x1016D7C,
	kVtbl_QueuedFileLoad = 0x1016DC4,
	kVtbl_QueuedFaceGenFile = 0x1016E1C,
	kVtbl_BackgroundCloneThread = 0x1016E50,
	kVtbl_QueuedReplacementKFList = 0x1016FC0,
	kVtbl_InterfacedClass = 0x1017458,
	kVtbl_INISettingCollection = 0x101772C,
	kVtbl_TES = 0x10178B4,
	kVtbl_BSTempNodeManager = 0x10178BC,
	kVtbl_BSTempNode = 0x1017D24,
	kVtbl_RendererSettingCollection = 0x1018508,
	kVtbl_BGSAmmoForm = 0x101A3B8,
	kVtbl_BGSBipedModelList = 0x101A4C4,
	kVtbl_BGSClipRoundsForm = 0x101A644,
	kVtbl_BGSDestructibleObjectForm = 0x101A6A0,
	kVtbl_BGSEquipType = 0x101AA14,
	kVtbl_BGSIdleCollection = 0x101AA98,
	kVtbl_BGSMessageIcon = 0x101AB58,
	kVtbl_BGSPickupPutdownSounds = 0x101ABD8,
	kVtbl_BGSRepairItemList = 0x101ADE8,
	kVtbl_BGSTouchSpellForm = 0x101AEF0,
	kVtbl_TESActorBaseData = 0x101B0DC,
	kVtbl_TESAIForm = 0x101BE98,
	kVtbl_TESAnimation = 0x101BF50,
	kVtbl_TESAttackDamageForm = 0x101BF68,
	kVtbl_TESAttributes = 0x101BF84,
	kVtbl_TESBipedModelForm = 0x101BFD8,
	kVtbl_TESModelRDT = 0x101BFEC,
	kVtbl_TESContainer = 0x101C130,
	kVtbl_TESDescription = 0x101C18C,
	kVtbl_TESEnchantableForm = 0x101C1B0,
	kVtbl_TESForm = 0x101C794,
	kVtbl_TESHealthForm = 0x101CB94,
	kVtbl_TESImageSpaceModifiableForm = 0x101CBD8,
	kVtbl_TESLeveledList = 0x101CD04,
	kVtbl_TESModel = 0x101CF44,
	kVtbl_TESModelList = 0x101D0D4,
	kVtbl_TESModelTextureSwap = 0x101D124,
	kVtbl_TESProduceForm = 0x101D2A4,
	kVtbl_TESRaceForm = 0x101D398,
	kVtbl_TESReactionForm = 0x101D46C,
	kVtbl_TESScriptableForm = 0x101D518,
	kVtbl_TESSpellList = 0x101D628,
	kVtbl_TESTexture = 0x101D7C4,
	kVtbl_TESValueForm = 0x101D81C,
	kVtbl_TESWeightForm = 0x101D874,
	kVtbl_AnimSequenceSingle = 0x101D8C8,
	kVtbl_AnimSequenceBase = 0x101D8E8,
	kVtbl_AnimSequenceMultiple = 0x101D908,
	kVtbl_AnimIdle = 0x101DCD8,
	kVtbl_NiRefObject = 0x101DCE4,
	kVtbl_BSAnimGroupSequence = 0x101DE3C,
	kVtbl_NiStencilProperty = 0x101E07C,
	kVtbl_BSCullingProcess = 0x101E2EC,
	kVtbl_hkpAllRayHitCollector = 0x101E588,
	kVtbl_hkpRayHitCollector = 0x101E594,
	kVtbl_BGSPrimitive = 0x101E72C,
	kVtbl_BGSPrimitivePlane = 0x101E75C,
	kVtbl_BSOcclusionPlane = 0x101E794,
	kVtbl_BSPortal = 0x101E82C,
	kVtbl_BGSPrimitiveBox = 0x101E8C4,
	kVtbl_BSMultiBoundAABB = 0x101E8E4,
	kVtbl_BSMultiBoundOBB = 0x101E9A4,
	kVtbl_BGSPrimitiveSphere = 0x101EA64,
	kVtbl_BSMultiBoundSphere = 0x101EA8C,
	kVtbl_BGSSceneInfo = 0x101EC68,
	kVtbl_BSAnimNoteReceiver = 0x101FC74,
	kVtbl_IBSAnimNoteReceiver = 0x101FC80,
	kVtbl_bhkMouseSpringAction = 0x101FFCC,
	kVtbl_bhkUnaryAction = 0x102009C,
	kVtbl_bhkAction = 0x102016C,
	kVtbl_bhkSerializable = 0x102023C,
	kVtbl_GridArray = 0x1020634,
	kVtbl_GridCellArray = 0x1020698,
	kVtbl_INIPrefSettingCollection = 0x1022744,
	kVtbl_BSCustomSplatterExtraData = 0x10228C4,
	kVtbl_BSSplatterExtraData = 0x1022A24,
	kVtbl_ImageSpaceEffectParam = 0x10231CC,
	kVtbl_BGSDecalNode = 0x1023734,
	kVtbl_TESRegion = 0x102397C,
	kVtbl_TESRegionData = 0x1023AC4,
	kVtbl_TESRegionDataGrass = 0x1023B24,
	kVtbl_TESRegionDataImposter = 0x1023BC8,
	kVtbl_TESRegionDataLandscape = 0x1023C8C,
	kVtbl_TESRegionDataManager = 0x1023CE4,
	kVtbl_TESRegionDataMap = 0x1023D28,
	kVtbl_TESRegionDataSound = 0x1023DA4,
	kVtbl_TESRegionDataWeather = 0x1023E18,
	kVtbl_TESRegionGrassObject = 0x1023EC4,
	kVtbl_TESRegionObjectBase = 0x1023EE4,
	kVtbl_TESRegionGrassObjectList = 0x1024094,
	kVtbl_TESRegionList = 0x10240A0,
	kVtbl_BGSAddonNode = 0x1024214,
	kVtbl_BGSAddonNodeSoundHandleExtra = 0x10243D4,
	kVtbl_BGSConstructibleObject = 0x10245A4,
	kVtbl_BGSDebris = 0x1024834,
	kVtbl_BGSPreloadable = 0x1024970,
	kVtbl_BGSExplosion = 0x1024A94,
	kVtbl_BGSMovableStatic = 0x1024CEC,	//	Has an irregular structure; the enumed vtbl is the "effective" one used at runtime; actual vtbl is 0x1024E84
	kVtbl_BGSPlaceableWater = 0x1024F4C,
	kVtbl_BGSProjectile = 0x10251AC,
	kVtbl_BGSStaticCollection = 0x102535C,
	kVtbl_BGSTalkingActivator = 0x1025594,
	kVtbl_PathingLocation = 0x102583C,
	kVtbl_BGSTerminal = 0x1025914,
	kVtbl_TESAmmo = 0x1026064,
	kVtbl_TESCasinoChips = 0x10263DC,
	kVtbl_TESCasino = 0x1026574,
	kVtbl_TESCombatStyle = 0x10266E4,
	kVtbl_TESEffectShader = 0x102685C,
	kVtbl_TESFlora = 0x1026BD0,
	kVtbl_TESFurniture = 0x1026D0C,
	kVtbl_TESGrass = 0x102814C,
	kVtbl_TESKey = 0x1028444,
	kVtbl_TESLevCharacter = 0x102864C,
	kVtbl_TESLevCreature = 0x102886C,
	kVtbl_TESLevItem = 0x1028A64,
	kVtbl_TESLevSpell = 0x1028C5C,
	kVtbl_TESObjectLIGH = 0x1028EE4,
	kVtbl_TESBoundObject = 0x102960C,
	kVtbl_TESBoundAnimObject = 0x102980C,
	kVtbl_TESBoundTreeObject = 0x1029994,
	kVtbl_TESObject = 0x1029B1C,
	kVtbl_TESObjectACTI = 0x1029D5C,
	kVtbl_BGSOpenCloseForm = 0x1029EE0,
	kVtbl_TESObjectANIO = 0x102A0A4,
	kVtbl_TESObjectARMA = 0x102A31C,
	kVtbl_TESObjectARMO = 0x102A62C,
	kVtbl_TESObjectBOOK = 0x102A9C4,
	kVtbl_TESObjectCLOT = 0x102AC0C,
	kVtbl_TESObjectCONT = 0x102AEB4,
	kVtbl_TESObjectDOOR = 0x102B1FC,
	kVtbl_TESObjectIMOD = 0x102B5AC,
	kVtbl_TESObjectMISC = 0x102B844,
	kVtbl_TESObjectSTAT = 0x102BA2C,
	kVtbl_TESObjectTREE = 0x102BC94,
	kVtbl_TESModelTree = 0x102BE70,
	kVtbl_TESIconTree = 0x102BE94,
	kVtbl_TESTexture1024 = 0x102BEB4,
	kVtbl_NiBillboardNode = 0x102BF44,
	kVtbl_BSShaderTextureSet = 0x102C04C,
	kVtbl_BSTextureSet = 0x102C0EC,
	kVtbl_TESObjectWEAP = 0x102C51C,
	kVtbl_BGSEncounterZone = 0x102CBBC,
	kVtbl_BGSLightingTemplate = 0x102CD94,
	kVtbl_LoadedReferenceMap = 0x102CF0C,
	kVtbl_ExteriorCellLoaderTask = 0x102D028,
	kVtbl_ImageSpaceModifierInstanceForm = 0x102D12C,
	kVtbl_ImageSpaceModifierInstance = 0x102D1CC,
	kVtbl_ImageSpaceModifierInstanceDOF = 0x102D2A4,
	kVtbl_ImageSpaceModifierInstanceRB = 0x102D36C,
	kVtbl_ImageSpaceModifierInstanceDRB = 0x102D454,
	kVtbl_ImageSpaceModifierInstanceTemp = 0x102D50C,
	kVtbl_TESClimate = 0x102D5C4,
	kVtbl_TESImageSpace = 0x102D7F4,
	kVtbl_TESImageSpaceModifier = 0x102D97C,
	kVtbl_NiFloatData = 0x102DABC,
	kVtbl_NiColorData = 0x102DB4C,
	kVtbl_TESObjectLAND = 0x102DCD4,
	kVtbl_TESChildCell = 0x102DE10,
	kVtbl_BSPackedAdditionalGeometryData = 0x102E1DC,
	kVtbl_NiAdditionalGeometryData = 0x102E274,
	kVtbl_hkpMoppCode = 0x102E368,
	kVtbl_hkReferencedObject = 0x102E378,
	kVtbl_hkBaseObject = 0x102E388,
	kVtbl_NiBinaryExtraData = 0x102E394,
	kVtbl_TESLandTexture = 0x102E6C4,
	kVtbl_TESObjectCELL = 0x102E9B4,
	kVtbl_CheckWithinMultiBoundTask = 0x102EE48,
	kVtbl_hkpWorldCinfo = 0x102F0EC,
	kVtbl_TESWindListener = 0x102F10C,
	kVtbl_hkpEntityListener = 0x102F13C,
	kVtbl_TESObjectREFR = 0x102F55C,
	kVtbl_bhkRigidBody = 0x10301B4,
	kVtbl_bhkEntity = 0x10302BC,
	kVtbl_bhkWorldObject = 0x1030394,
	kVtbl_bhkCollisionObject = 0x103046C,
	kVtbl_bhkWaterPhantomCallbackShape = 0x1030534,
	kVtbl_hkpPhantomCallbackShape = 0x1030570,
	kVtbl_hkpShape = 0x10305A8,
	kVtbl_bhkSimpleShapePhantom = 0x10305DC,
	kVtbl_bhkShapePhantom = 0x10306B4,
	kVtbl_bhkPhantom = 0x103078C,
	kVtbl_bhkAabbPhantom = 0x1030864,
	kVtbl_bhkBoxShape = 0x103093C,
	kVtbl_bhkConvexShape = 0x1030A24,
	kVtbl_bhkSphereRepShape = 0x1030B0C,
	kVtbl_bhkShape = 0x1030BF4,
	kVtbl_bhkSphereShape = 0x1030CDC,
	kVtbl_bhkAcousticSpacePhantomCallbackShape = 0x1030DC0,
	kVtbl_ExtraAnimNoteReceiver = 0x1030F14,
	kVtbl_TESWaterForm = 0x103140C,
	kVtbl_TESWeather = 0x103168C,
	kVtbl_TESWorldSpace = 0x103195C,
	kVtbl_BGSAcousticSpace = 0x10320FC,
	kVtbl_BGSCameraPath = 0x103245C,
	kVtbl_NiFormArray = 0x10326FC,
	kVtbl_BGSCameraShot = 0x10327F4,
	kVtbl_BGSDefaultObjectManager = 0x1032DC4,
	kVtbl_BGSImpactData = 0x1032F6C,
	kVtbl_BGSImpactDataSet = 0x103323C,
	kVtbl_BGSListForm = 0x10334B4,
	kVtbl_BGSMenuIcon = 0x1033654,
	kVtbl_BGSMessage = 0x10337C4,
	kVtbl_BGSMusicType = 0x103397C,
	kVtbl_TESSoundFile = 0x1033AB8,
	kVtbl_BGSRadiationStage = 0x1033B34,
	kVtbl_BGSTextureSet = 0x1033D1C,
	kVtbl_MediaLocationController = 0x10340C4,
	kVtbl_MediaSet = 0x10342EC,
	kVtbl_TESAmmoEffect = 0x103449C,
	kVtbl_TESCaravanCard = 0x103478C,
	kVtbl_TESCaravanMoney = 0x10349B4,
	kVtbl_TESCaravanDeck = 0x1034B4C,
	kVtbl_hkpClosestRayHitCollector = 0x1034EC4,
	kVtbl_TESGlobal = 0x1036524,
	kVtbl_TESLoadScreen = 0x10366CC,
	kVtbl_TESLoadScreenType = 0x1036854,
	kVtbl_TESRecipeCategory = 0x10369DC,
	kVtbl_TESRecipe = 0x1036B2C,
	kVtbl_Script = 0x1037094,
	kVtbl_MobIterOperator = 0x103CF5C,
	kVtbl_TESSound = 0x1044FFC,
	kVtbl_BGSBodyPart = 0x1045404,
	kVtbl_TESModelPSA = 0x104540C,
	kVtbl_BGSBodyPartData = 0x1045504,
	kVtbl_BGSEntryPointFunctionDataOneValue = 0x10462C0,
	kVtbl_BGSEntryPointFunctionData = 0x10462E0,
	kVtbl_BGSEntryPointFunctionDataTwoValue = 0x1046300,
	kVtbl_BGSEntryPointFunctionDataLeveledList = 0x1046320,
	kVtbl_BGSEntryPointFunctionDataActivateChoice = 0x1046340,
	kVtbl_BGSHeadPart = 0x10464B4,
	kVtbl_BGSIdleMarker = 0x104664C,
	kVtbl_BGSNote = 0x1046874,
	kVtbl_BGSPerkEntry = 0x1046B48,
	kVtbl_BGSQuestPerkEntry = 0x1046B84,
	kVtbl_BGSAbilityPerkEntry = 0x1046C44,
	kVtbl_BGSEntryPointPerkEntry = 0x1046D0C,
	kVtbl_BGSPerk = 0x1046EC4,
	kVtbl_BGSQuestObjective = 0x1047088,
	kVtbl_BGSRagdoll = 0x10470EC,
	kVtbl_BGSVoiceType = 0x104733C,
	kVtbl_Reset3DMobIterator = 0x1047670,
	kVtbl_TESAnimGroup = 0x10484E8,
	kVtbl_TESChallenge = 0x104891C,
	kVtbl_TESClass = 0x1048BB4,
	kVtbl_TESCreature = 0x1048F5C,
	kVtbl_TESActorBase = 0x10492AC,
	kVtbl_ActorValueOwner = 0x1049450,
	kVtbl_TESEyes = 0x104973C,
	kVtbl_TESFaction = 0x10498DC,
	kVtbl_TESHair = 0x1049B9C,
	kVtbl_TESIdleForm = 0x1049D0C,
	kVtbl_TESModelAnim = 0x1049E48,
	kVtbl_TESNPC = 0x104A2F4,
	kVtbl_TESQuest = 0x104AC44,
	kVtbl_TESRace = 0x104B4BC,
	kVtbl_BGSTextureModel = 0x104B5F8,
	kVtbl_TESReputation = 0x104BA24,
	kVtbl_TESSkill = 0x104CC0C,
	kVtbl_TESTopic = 0x104D19C,
	kVtbl_TopicInfoArray = 0x104D338,
	kVtbl_TESTopicInfo = 0x104D5B4,
	kVtbl_BGSAcousticSpaceListener = 0x104D8E8,
	kVtbl_bhkEntityListener = 0x104D91C,
	kVtbl_TargetEntry = 0x104D9C4,
	kVtbl_ZoneEntry = 0x104D9CC,
	kVtbl_TrapTargetEntry = 0x104D9D8,
	kVtbl_BGSZoneTargetListener = 0x104D9E0,
	kVtbl_hkpAllCdPointCollector = 0x104DA28,
	kVtbl_hkpCdPointCollector = 0x104DA3C,
	kVtbl_CellMopp = 0x104DAB4,
	kVtbl_bhkTriSampledHeightFieldBvTreeShape = 0x104DAC4,
	kVtbl_bhkBvTreeShape = 0x104DBAC,
	kVtbl_FOCollisionListener = 0x104DD38,
	kVtbl_bhkContactListener = 0x104DD5C,
	kVtbl_hkpContactListener = 0x104DD7C,
	kVtbl_FOIslandActivationListener = 0x104DE00,
	kVtbl_hkpIslandActivationListener = 0x104DE10,
	kVtbl_HavokStreambufFactory = 0x104DEA4,
	kVtbl_hkFileSystem = 0x104DEC0,
	kVtbl_HavokError = 0x104DEF4,
	kVtbl_hkError = 0x104DF8C,
	kVtbl_hkStreamReader = 0x104DFB4,
	kVtbl_hkStreamWriter = 0x104DFE8,
	kVtbl_HavokFileStreambufReader = 0x104E014,
	kVtbl_HavokFileStreambufWriter = 0x104E054,
	kVtbl_LoadedAreaBound = 0x104E130,
	kVtbl_SpecificItemCollector = 0x104E1DC,
	kVtbl_TESArrowTargetListener = 0x104E228,
	kVtbl_bhkArrowTargetListener = 0x104E254,
	kVtbl_hkpAllCdBodyPairCollector = 0x104E318,
	kVtbl_hkpCdBodyPairCollector = 0x104E328,
	kVtbl_TESTrapListener = 0x104E37C,
	kVtbl_bhkTrapListener = 0x104E3A4,
	kVtbl_hkpPhantomListener = 0x104E3D0,
	kVtbl_TrapEntry = 0x104E3E8,
	kVtbl_WaterTargetEntry = 0x104E438,
	kVtbl_TESWaterListener = 0x104E450,
	kVtbl_WaterZone = 0x104E4B0,
	kVtbl_BlendSettingCollection = 0x104E6AC,
	kVtbl_Atmosphere = 0x104EB68,
	kVtbl_Clouds = 0x104EC08,
	kVtbl_Moon = 0x104ED28,
	kVtbl_Precipitation = 0x104ED98,
	kVtbl_Sky = 0x104EDEC,
	kVtbl_SkyObject = 0x104F0F8,
	kVtbl_SkyTask = 0x104F118,
	kVtbl_Stars = 0x104F1D8,
	kVtbl_Sun = 0x104F298,
	kVtbl_BSFaceGenAnimationData = 0x1064E1C,
	kVtbl_BSFaceGenImage = 0x10653C4,
	kVtbl_BSFaceGenKeyframe = 0x10653FC,
	kVtbl_BSFaceGenKeyframeMultiple = 0x106544C,
	kVtbl_BSFaceGenModelMap = 0x1065678,
	kVtbl_BSFaceGenModel = 0x1065AF4,
	kVtbl_BSFaceGenModelExtraData = 0x1065BF4,
	kVtbl_BSFaceGenMorph = 0x1065CB8,
	kVtbl_BSFaceGenMorphDifferential = 0x1065CC4,
	kVtbl_BSFaceGenMorphStatistical = 0x1065CD0,
	kVtbl_BSFaceGenMorphDataHead = 0x1065EB4,
	kVtbl_BSFaceGenMorphData = 0x1065F04,
	kVtbl_BSFaceGenMorphDataHair = 0x1065F5C,
	kVtbl_BSFaceGenBaseMorphExtraData = 0x1065FAC,
	kVtbl_BSFaceGenNiNode = 0x10660DC,
	kVtbl_BSTreeModel = 0x1066768,
	kVtbl_BSTreeNode = 0x10668E4,
	kVtbl_bhkSPCollisionObject = 0x1066ACC,
	kVtbl_bhkPCollisionObject = 0x1066B94,
	kVtbl_bhkMultiSphereShape = 0x1066C5C,
	kVtbl_bhkTransformShape = 0x1066D44,
	kVtbl_bhkCapsuleShape = 0x1066E2C,
	kVtbl_ActorValueInfo = 0x1067A2C,
	kVtbl_TESPackage = 0x106847C,
	kVtbl_TESAmbushPackageData = 0x1068860,
	kVtbl_TESPackageData = 0x1068884,
	kVtbl_TESDialoguePackageData = 0x10688AC,
	kVtbl_TESEatPackageData = 0x1068938,
	kVtbl_TESEscortPackageData = 0x1068960,
	kVtbl_TESFollowPackageData = 0x1068988,
	kVtbl_TESPatrolPackageData = 0x10689E4,
	kVtbl_TESUseItemPackageData = 0x1068A0C,
	kVtbl_TESUseWeaponPackageData = 0x1068A64,
	kVtbl_UseWeaponActorPackageData = 0x1068A88,
	kVtbl_ActorPackageData = 0x1068AA4,
	kVtbl_NiTask = 0x1069674,
	kVtbl_BSTempEffect = 0x1069754,
	kVtbl_BSTempEffectDebris = 0x106986C,
	kVtbl_BSTempEffectGeometryDecal = 0x10699BC,
	kVtbl_BSDismemberSkinInstance = 0x1069A84,
	kVtbl_NiSkinInstance = 0x1069B14,
	kVtbl_BSTempEffectParticle = 0x1069C5C,
	kVtbl_BSTempEffectSimpleDecal = 0x1069DDC,
	kVtbl_NavMesh = 0x106A0B4,
	kVtbl_NavMeshPOVSearch = 0x106B39C,
	kVtbl_NavMeshSearch = 0x106B63C,
	kVtbl_NavMeshSearchClosePoint = 0x106B6FC,
	kVtbl_NavMeshSearchFlee = 0x106B78C,
	kVtbl_NavMeshSearchHide = 0x106B7DC,
	kVtbl_NavMeshSearchLOS = 0x106B830,
	kVtbl_NavMeshSearchMaxCost = 0x106B87C,
	kVtbl_NavMeshSearchSLPoint = 0x106B96C,
	kVtbl_PathSmootherPOVSearch = 0x106B9CC,
	kVtbl_NavMeshInfoMap = 0x106BB8C,
	kVtbl_NavMeshInfoSearch = 0x106C22C,
	kVtbl_ObstacleUndoData = 0x106C2D4,
	kVtbl_bhkObstacleDeactivationListener = 0x106C3B4,
	kVtbl_hkpEntityActivationListener = 0x106C3C4,
	kVtbl_bhkObstacleRemovalListener = 0x106C3D4,
	kVtbl_ReferenceObstacleArray = 0x106C484,
	kVtbl_ObstacleData = 0x106C490,
	kVtbl_BSTasklet = 0x106C5D8,
	kVtbl_ObstacleTaskData = 0x106C7EC,
	kVtbl_BSWin32TaskletData = 0x106C800,
	kVtbl_BSTaskletData = 0x106C814,
	kVtbl_FindTriangleForLocationFilter = 0x106C934,
	kVtbl_CheckLineOfSightFilterWater = 0x106C93C,
	kVtbl_PathingCoverLocation = 0x106CBC0,
	kVtbl_PathingLOSGridMap = 0x106CEAC,
	kVtbl_PathingLOSMap = 0x106CF5C,
	kVtbl_PathingRequest = 0x106D030,
	kVtbl_PathingAvoidNodeArray = 0x106D1E4,
	kVtbl_PathingRequestClosePoint = 0x106D230,
	kVtbl_PathingRequestCover = 0x106D29C,
	kVtbl_PathingRequestCoveredMove = 0x106D2D4,
	kVtbl_PathingRequestFlee = 0x106D300,
	kVtbl_PathingRequestHide = 0x106D32C,
	kVtbl_PathingRequestLOS = 0x106D38C,
	kVtbl_PathingRequestOptimalLocation = 0x106D3B8,
	kVtbl_PathingRequestSafeStraightLine = 0x106D414,
	kVtbl_PathingSearchRayCast = 0x106D47C,
	kVtbl_PathingSolution = 0x106D4BC,
	kVtbl_PathingTaskData = 0x106D550,
	kVtbl_TeleportDoorSearch = 0x106D8FC,
	kVtbl_BGSDistantObjectBlockLoadTask = 0x106DC3C,
	kVtbl_BGSDistantTreeBlockLoadTask = 0x106DED0,
	kVtbl_BGSTerrainChunkLoadTask = 0x106E1DC,
	kVtbl_CCallbackBase = 0x106E7B4,
	kVtbl_FORenderedTerminal = 0x106EBE4,
	kVtbl_TileMenu = 0x106ED44,
	kVtbl_TileRect = 0x106ED70,
	kVtbl_Tile = 0x106ED9C,
	kVtbl_TileImage = 0x106F01C,
	kVtbl_TutorialMenu = 0x106FF84,
	kVtbl_StatsMenu = 0x106FFD4,
	kVtbl_TextEditMenu = 0x1070034,
	kVtbl_SurgeryMenu = 0x1070084,
	kVtbl_VATSMenu = 0x10700D4,
	kVtbl_SpecialBookMenu = 0x1070124,
	kVtbl_LoveTesterMenu = 0x1070174,
	kVtbl_QuantityMenu = 0x10701C4,
	kVtbl_ListBoxBase = 0x1070418,
	kVtbl_RecipeMenu = 0x107048C,
	kVtbl_BarterMenu = 0x10706EC,
	kVtbl_BlackjackMenu = 0x10708FC,
	kVtbl_BookMenu = 0x1070ECC,
	kVtbl_CaravanMenu = 0x107108C,
	kVtbl_CharGenMenu = 0x1071BB4,
	kVtbl_CompanionWheelMenu = 0x1071D0C,
	kVtbl_ComputersMenu = 0x1072004,
	kVtbl_ContainerMenu = 0x10721AC,
	kVtbl_CreditsMenu = 0x107235C,
	kVtbl_DialogMenu = 0x107257C,
	kVtbl_HackingMenu = 0x10728F4,
	kVtbl_HUDMainMenu = 0x1072DF4,
	kVtbl_InventoryMenu = 0x10739B4,
	kVtbl_ItemModMenu = 0x1073B7C,
	kVtbl_LevelUpMenu = 0x1073CDC,
	kVtbl_LoadingMenu = 0x1073EBC,
	kVtbl_LoadingMenuThread = 0x10740AC,
	kVtbl_LockpickMenu = 0x107439C,
	kVtbl_MapMenu = 0x1074D44,
	kVtbl_MessageMenu = 0x107566C,
	kVtbl_PlayerNameEntryMenu = 0x10757FC,
	kVtbl_RaceSexMenu = 0x1075974,
	kVtbl_FORenderedMenuRaceSex = 0x10759EC,
	kVtbl_RepairMenu = 0x1075C5C,
	kVtbl_RepairServicesMenu = 0x1075DB4,
	kVtbl_RouletteMenu = 0x1075F7C,
	kVtbl_SleepWaitMenu = 0x10763AC,
	kVtbl_SlotMachineMenu = 0x10764DC,
	kVtbl_StartMenu = 0x1076D1C,
	kVtbl_TraitMenu = 0x10779BC,
	kVtbl_TraitSelectMenu = 0x1077ABC,
	kVtbl_FOPipboyManager = 0x10780AC,
	kVtbl_FORenderedMenu = 0x107841C,
	kVtbl_AbsorbEffect = 0x10792AC,
	kVtbl_ActiveEffect = 0x107935C,
	kVtbl_AssociatedItemEffect = 0x107951C,
	kVtbl_bhkCharacterListenerSpell = 0x10795E4,
	kVtbl_bhkTelekinesisListener = 0x1079744,
	kVtbl_BoundItemEffect = 0x107979C,
	kVtbl_CalmEffect = 0x107989C,
	kVtbl_ChameleonEffect = 0x107994C,
	kVtbl_CommandCreatureEffect = 0x10799FC,
	kVtbl_CommandEffect = 0x1079A9C,
	kVtbl_CommandHumanoidEffect = 0x1079B3C,
	kVtbl_ConcussionEffect = 0x1079BDC,
	kVtbl_CureEffect = 0x1079C8C,
	kVtbl_DarknessEffect = 0x1079D2C,
	kVtbl_DemoralizeEffect = 0x1079DDC,
	kVtbl_DetectLifeEffect = 0x1079E7C,
	kVtbl_DisintegrateArmorEffect = 0x1079F2C,
	kVtbl_DisintegrateWeaponEffect = 0x1079FFC,
	kVtbl_DispelEffect = 0x107A0CC,
	kVtbl_FrenzyEffect = 0x107A16C,
	kVtbl_InvisibilityEffect = 0x107A21C,
	kVtbl_LightEffect = 0x107A2CC,
	kVtbl_LimbConditionEffect = 0x107A3FC,
	kVtbl_LockEffect = 0x107A4AC,
	kVtbl_MagicBallProjectile = 0x107A554,
	kVtbl_MagicBoltProjectile = 0x107A8F4,
	kVtbl_MagicCaster = 0x107AC5C,
	kVtbl_MagicFogProjectile = 0x107AD84,
	kVtbl_MagicHitEffect = 0x107B0EC,
	kVtbl_MagicModelHitEffect = 0x107B24C,
	kVtbl_MagicProjectile = 0x107B394,
	kVtbl_MagicShaderHitEffect = 0x107B70C,
	kVtbl_MagicSprayProjectile = 0x107B8C4,
	kVtbl_MagicTarget = 0x107BC28,
	kVtbl_NightEyeEffect = 0x107BD7C,
	kVtbl_NonActorMagicCaster = 0x107BE80,
	kVtbl_NonActorMagicTarget = 0x107BECC,
	kVtbl_OpenEffect = 0x107BF1C,
	kVtbl_ParalysisEffect = 0x107BFBC,
	kVtbl_ReanimateEffect = 0x107C06C,
	kVtbl_ScriptEffect = 0x107C164,
	kVtbl_ShieldEffect = 0x107C1FC,
	kVtbl_SummonCreatureEffect = 0x107C2AC,
	kVtbl_SunDamageEffect = 0x107C3EC,
	kVtbl_TelekinesisEffect = 0x107C48C,
	kVtbl_TurnUndeadEffect = 0x107C53C,
	kVtbl_ValueAndConditionsEffect = 0x107C5DC,
	kVtbl_ValueModifierEffect = 0x107C68C,
	kVtbl_VampirismEffect = 0x107C7BC,
	kVtbl_CBSAStream = 0x107CB4C,
	kVtbl_CAsyncStream = 0x107CB6C,
	kVtbl_CBSAReader = 0x107CDAC,
	kVtbl_RadioConvTask = 0x107CF18,
	kVtbl_BGSReconstructFormsMap = 0x107E930,
	kVtbl_BGSReconstructCellsMap = 0x107E950,
	kVtbl_BGSReconstructCellSubBlocksMap = 0x107E970,
	kVtbl_BGSReconstructCellBlocksMap = 0x107E990,
	kVtbl_BGSReconstructWorldSpacesMap = 0x107E9B0,
	kVtbl_BGSReconstructFormsInFileMap = 0x107E9D0,
	kVtbl_BGSOffsetDataArray = 0x107EA60,
	kVtbl_BGSReconstructFormsInAllFilesMap = 0x107EA74,
	kVtbl_BGSSaveLoadChangesMap = 0x107ED68,
	kVtbl_BGSCellNumericIDArrayMap = 0x107FEF4,
	kVtbl_BGSSaveLoadStatsMap = 0x1080174,
	kVtbl_ChangesMap = 0x10804A8,
	kVtbl_InteriorCellNewReferencesMap = 0x1080514,
	kVtbl_ExteriorCellNewReferencesMap = 0x1080534,
	kVtbl_NumericIDBufferMap = 0x1080554,
	kVtbl_SaveGameFile = 0x1081A5C,
	kVtbl_BGSLoadFormBuffer = 0x1082028,
	kVtbl_BGSLoadGameBuffer = 0x1082048,
	kVtbl_BGSSaveFormBuffer = 0x1082308,
	kVtbl_BGSSaveGameBuffer = 0x1082324,
	kVtbl_BGSMoviePlayer = 0x1082564,
	kVtbl_HighActorCuller = 0x1082CC0,
	kVtbl_BSFadeNodeCuller = 0x1082CCC,
	kVtbl_RegSettingCollection = 0x1082ED8,
	kVtbl_MemoryManagerFile = 0x1083AE8,
	kVtbl_IMemoryManagerFile = 0x1083B00,
	kVtbl_SceneGraph = 0x1083B5C,
	kVtbl_SeenData = 0x1083FC4,
	kVtbl_IntSeenData = 0x1083FE4,
	kVtbl_Actor = 0x1084254,
	kVtbl_CachedValuesOwner = 0x1084734,
	kVtbl_bhkFilteredCdBodyCollector = 0x1084E54,
	kVtbl_AILinearTaskThread = 0x1085688,
	kVtbl_BSLinearTaskThread = 0x10856A0,
	kVtbl_DetectionTaskData = 0x1085728,
	kVtbl_MobileObjectTaskletData = 0x1085748,
	kVtbl_AnimationTaskData = 0x1085768,
	kVtbl_ActorUpdateTaskData = 0x1085788,
	kVtbl_PackageUpdateTaskData = 0x10857A8,
	kVtbl_ActorsScriptTaskData = 0x10857C8,
	kVtbl_MovementTaskData = 0x10857E8,
	kVtbl_AITaskThread = 0x1085818,
	kVtbl_ArrowProjectile = 0x1085954,
	kVtbl_BaseProcess = 0x1085E2C,
	kVtbl_bhkCharacterListenerArrow = 0x1086684,
	kVtbl_BSPlayerDistanceCheckController = 0x10867FC,
	kVtbl_Character = 0x1086A6C,
	kVtbl_Creature = 0x10870AC,
	kVtbl_HighProcess = 0x1087864,
	kVtbl_ActorPathingMessageQueue = 0x1088158,
	kVtbl_LipTask = 0x10885B8,
	kVtbl_LowProcess = 0x10886E4,
	kVtbl_MiddleHighProcess = 0x108904C,
	kVtbl_MiddleLowProcess = 0x1089BCC,
	kVtbl_MobileObject = 0x108A49C,
	kVtbl_PlayerCharacter = 0x108AA3C,
	kVtbl_BeamProjectile = 0x108C3C4,
	kVtbl_CombatAction = 0x108CAB8,
	kVtbl_CombatActionAttackRanged = 0x108CB50,
	kVtbl_CombatActionAttackRangedFromCover = 0x108CB7C,
	kVtbl_CombatActionAttackRangedExplosive = 0x108CB94,
	kVtbl_CombatActionAttackRangedExplosiveFromCover = 0x108CBAC,
	kVtbl_CombatActionAttackMelee = 0x108CBC4,
	kVtbl_CombatActionAttackHandToHand = 0x108CBDC,
	kVtbl_CombatActionAttackGrenade = 0x108CBF4,
	kVtbl_CombatActionAttackGrenadeFlushTarget = 0x108CC0C,
	kVtbl_CombatActionAttackGrenadeFromCover = 0x108CC24,
	kVtbl_CombatActionMove = 0x108CC3C,
	kVtbl_CombatActionMoveAndSwitchToMelee = 0x108CC54,
	kVtbl_CombatActionMoveAndAttackRanged = 0x108CC6C,
	kVtbl_CombatActionMoveAndAttackRangedExplosive = 0x108CC84,
	kVtbl_CombatActionMoveAndAttackGrenade = 0x108CC9C,
	kVtbl_CombatActionDrawWeapon = 0x108CCB4,
	kVtbl_CombatActionSwitchWeapon = 0x108CCCC,
	kVtbl_CombatActionAvoidThreat = 0x108CCE4,
	kVtbl_CombatActionSearch = 0x108CCFC,
	kVtbl_CombatActionInvestigate = 0x108CD14,
	kVtbl_CombatActionDodge = 0x108CD2C,
	kVtbl_CombatActionIgnoreBlockedTarget = 0x108CD44,
	kVtbl_CombatActionFlee = 0x108CD5C,
	kVtbl_CombatActionActivateCombatItem = 0x108CD74,
	kVtbl_CombatActionUseCombatItem = 0x108CD8C,
	kVtbl_CombatActionApproachTarget = 0x108CDA4,
	kVtbl_CombatActionAcquireLineOfSight = 0x108CDBC,
	kVtbl_CombatActionHide = 0x108CDD4,
	kVtbl_CombatController = 0x108CE74,
	kVtbl_CombatPlanner = 0x108CFD8,
	kVtbl_CombatCoverMap = 0x108D0E4,
	kVtbl_CombatGoal = 0x108D440,
	kVtbl_CombatGoalKillTarget = 0x108D47C,
	kVtbl_CombatGoalFindTarget = 0x108D488,
	kVtbl_CombatGoalAvoidThreats = 0x108D494,
	kVtbl_CombatGoalFlee = 0x108D4A0,
	kVtbl_CombatGoalActivateCombatItem = 0x108D4AC,
	kVtbl_CombatGoalUseCombatItem = 0x108D4B8,
	kVtbl_CombatGoalFlank = 0x108D4C4,
	kVtbl_CombatGoalFallBack = 0x108D4D0,
	kVtbl_CombatGoalAmbush = 0x108D4DC,
	kVtbl_CombatGoalReachDestination = 0x108D4E8,
	kVtbl_CombatGoalAdvance = 0x108D4F4,
	kVtbl_CombatGoalGuard = 0x108D500,
	kVtbl_CombatGoalCluster = 0x108D50C,
	kVtbl_CombatGoalHideFromTarget = 0x108D518,
	kVtbl_CombatGoalFlushTarget = 0x108D524,
	kVtbl_CombatGoalStayInCombatArea = 0x108D530,
	kVtbl_CombatGroupStrategyFlank = 0x108D93C,
	kVtbl_CombatGroupStrategy = 0x108D94C,
	kVtbl_CombatGroupStrategyFallBack = 0x108D95C,
	kVtbl_CombatGroupStrategyAmbush = 0x108D96C,
	kVtbl_CombatGroupStrategyAdvance = 0x108D97C,
	kVtbl_CombatTargetMap = 0x108E1E8,
	kVtbl_CombatThreatMap = 0x108E2E8,
	kVtbl_ContinuousBeamProjectile = 0x108EA64,
	kVtbl_Explosion = 0x108EE04,
	kVtbl_bhkLiquidAction = 0x108F1BC,
	kVtbl_hkpFixedBufferCdPointCollector = 0x108F288,
	kVtbl_FlameProjectile = 0x108F2F4,
	kVtbl_GrenadeProjectile = 0x108F674,
	kVtbl_MissileProjectile = 0x108FA44,
	kVtbl_bhkHingeConstraint = 0x108FDDC,
	kVtbl_bhkConstraint = 0x108FEBC,
	kVtbl_hkHingeConstraintCinfo = 0x108FF98,
	kVtbl_hkConstraintCinfo = 0x108FFB4,
	kVtbl_Projectile = 0x10900DC,
	kVtbl_ProjectileListener = 0x1090594,
	kVtbl_CombatProcedureActivateObject = 0x109082C,
	kVtbl_CombatProcedure = 0x1090874,
	kVtbl_CombatProcedureAttackGrenade = 0x10909BC,
	kVtbl_CombatProcedureAttackLow = 0x1090AEC,
	kVtbl_CombatProcedureAttackMelee = 0x1090C04,
	kVtbl_CombatProcedureAttackRanged = 0x1090ED4,
	kVtbl_CombatProcedureBeInCover = 0x10910F4,
	kVtbl_CombatProcedureEngageTarget = 0x1091514,
	kVtbl_CombatProcedureEvade = 0x1091984,
	kVtbl_CombatProcedureHideFromTarget = 0x1091A64,
	kVtbl_CombatProcedureMove = 0x1091BB4,
	kVtbl_CombatProcedureSearch = 0x1091DB4,
	kVtbl_CombatProcedureSwitchWeapon = 0x10920CC,
	kVtbl_CombatProcedureUseCombatItem = 0x109214C,
	kVtbl_ActorMover = 0x109223C,
	kVtbl_ActorPathHandler = 0x109231C,
	kVtbl_DetailedActorPathHandler = 0x10923EC,
	kVtbl_DoorInPathFilter = 0x1092484,
	kVtbl_PlayerMover = 0x109297C,
	kVtbl_VirtualActorPathHandler = 0x10929FC,
	kVtbl_AlarmPackage = 0x1092BDC,
	kVtbl_BackUpPackage = 0x1092D84,
	kVtbl_DialoguePackage = 0x1092F6C,
	kVtbl_EscortActorPackageData = 0x1093188,
	kVtbl_FleePackage = 0x10931E4,
	kVtbl_GuardActorPackageData = 0x10933C8,
	kVtbl_PatrolActorPackageData = 0x1093418,
	kVtbl_SandBoxActorPackageData = 0x10935F8,
	kVtbl_SearchPackage = 0x1093674,
	kVtbl_SpectatorPackage = 0x109381C,
	kVtbl_TrespassPackage = 0x10939EC,
	kVtbl_CEnumPins = 0x1093C50,
	kVtbl_CEnumMediaTypes = 0x1093C74,
	kVtbl_CMediaSample = 0x1093C9C,
	kVtbl_CMemAllocator = 0x1093D28,
	kVtbl_CAsyncOutputPin = 0x1093E24,
	kVtbl_CAsyncReader = 0x1093EAC,
	kVtbl_TileText = 0x1094878,
	kVtbl_Tile3D = 0x10948AC,
	kVtbl_TileExtra = 0x1094CFC,
	kVtbl_DebugText = 0x1094EFC,
	kVtbl_IDebugText = 0x1094F30,
	kVtbl_DebugTextExtraData = 0x1094FB4,
	kVtbl_Menu = 0x1095484,
	kVtbl_RadialTile = 0x1095750,
	kVtbl_NiAVObjectPalette = 0x109607C,
	kVtbl_NiControllerManager = 0x109619C,
	kVtbl_NiDefaultAVObjectPalette = 0x1096284,
	kVtbl_NiInterpController = 0x109632C,
	kVtbl_NiMultiTargetTransformController = 0x1096444,
	kVtbl_NiControllerSequence = 0x1096584,
	kVtbl_BSMultiTargetTreadTransfController = 0x1096694,
	kVtbl_NiBlendAccumTransformInterpolator = 0x1096784,
	kVtbl_NiTransformController = 0x109687C,
	kVtbl_NiBlendInterpolator = 0x109697C,
	kVtbl_NiSingleInterpController = 0x1096BD4,
	kVtbl_NiGeomMorpherController = 0x1096CEC,
	kVtbl_NiColorInterpolator = 0x1096E14,
	kVtbl_NiFloatInterpolator = 0x1096F34,
	kVtbl_NiKeyBasedInterpolator = 0x1097054,
	kVtbl_NiPosData = 0x109717C,
	kVtbl_NiPathInterpolator = 0x109720C,
	kVtbl_NiTransformInterpolator = 0x1097314,
	kVtbl_NiBlendFloatInterpolator = 0x1097414,
	kVtbl_NiBlendTransformInterpolator = 0x109750C,
	kVtbl_NiFloatExtraDataController = 0x10975FC,
	kVtbl_NiMorphData = 0x10976FC,
	kVtbl_BSFrustumFOVController = 0x109780C,
	kVtbl_BSBlendTreadTransfInterpolator = 0x1097904,
	kVtbl_BSTreadTransfInterpolator = 0x10979F4,
	kVtbl_BSRotAccumTransfInterpolator = 0x1097AF4,
	kVtbl_BSAnimNote = 0x1097BF4,
	kVtbl_BSLookIKNote = 0x1097C8C,
	kVtbl_BSGrabIKNote = 0x1097D34,
	kVtbl_BSAnimNotes = 0x1097DD4,
	kVtbl_NiVisController = 0x1097E8C,
	kVtbl_NiUVData = 0x1097F84,
	kVtbl_NiUVController = 0x1098064,
	kVtbl_NiTextureTransformController = 0x1098184,
	kVtbl_NiTextKeyExtraData = 0x109827C,
	kVtbl_NiStringPalette = 0x109832C,
	kVtbl_NiSequenceStreamHelper = 0x10983BC,
	kVtbl_NiSequence = 0x1098454,
	kVtbl_NiRotData = 0x10984EC,
	kVtbl_NiFloatController = 0x109857C,
	kVtbl_NiRollController = 0x1098634,
	kVtbl_NiQuaternionInterpolator = 0x10986F4,
	kVtbl_NiPoint3Interpolator = 0x109881C,
	kVtbl_NiPathController = 0x109893C,
	kVtbl_NiMaterialColorController = 0x1098A14,
	kVtbl_NiLookAtInterpolator = 0x1098B0C,
	kVtbl_NiLookAtController = 0x1098C14,
	kVtbl_NiLightDimmerController = 0x1098CCC,
	kVtbl_NiLightColorController = 0x1098DD4,
	kVtbl_NiKeyframeManager = 0x1098F4C,
	kVtbl_NiTransformData = 0x1099004,
	kVtbl_NiFloatsExtraDataPoint3Controller = 0x109917C,
	kVtbl_NiFloatsExtraDataController = 0x109928C,
	kVtbl_NiFlipController = 0x1099384,
	kVtbl_NiColorExtraDataController = 0x109947C,
	kVtbl_NiBSplineTransformInterpolator = 0x109957C,
	kVtbl_NiBSplinePoint3Interpolator = 0x10996DC,
	kVtbl_NiBSplineFloatInterpolator = 0x10997F4,
	kVtbl_NiBSplineCompTransformInterpolator = 0x109991C,
	kVtbl_NiBSplineCompPoint3Interpolator = 0x1099A24,
	kVtbl_NiBSplineCompFloatInterpolator = 0x1099B2C,
	kVtbl_NiBSplineCompColorInterpolator = 0x1099C34,
	kVtbl_NiBSplineColorInterpolator = 0x1099D3C,
	kVtbl_NiBSplineData = 0x1099E54,
	kVtbl_NiBSplineBasisData = 0x1099F24,
	kVtbl_NiBoolTimelineInterpolator = 0x1099FB4,
	kVtbl_NiBoolInterpolator = 0x109A0B4,
	kVtbl_NiBoolData = 0x109A1D4,
	kVtbl_NiBoneLODController = 0x109A2D4,
	kVtbl_NiBlendQuaternionInterpolator = 0x109A3AC,
	kVtbl_NiBlendPoint3Interpolator = 0x109A49C,
	kVtbl_NiBlendColorInterpolator = 0x109A58C,
	kVtbl_NiBlendBoolInterpolator = 0x109A67C,
	kVtbl_NiAlphaController = 0x109A76C,
	kVtbl_NiGeomMorpherUpdateTask = 0x109A864,
	kVtbl_NiInterpolator = 0x109A924,
	kVtbl_NiExtraDataController = 0x109AA14,
	kVtbl_NiFloatInterpController = 0x109AB44,
	kVtbl_NiBoolInterpController = 0x109AC54,
	kVtbl_NiPoint3InterpController = 0x109AD74,
	kVtbl_NiBSplineInterpolator = 0x109AE8C,
	kVtbl_NiAVObject = 0x109B00C,
	kVtbl_NiObjectNET = 0x109B244,
	kVtbl_NiObject = 0x109B4F4,
	kVtbl_NiNode = 0x109B5AC,
	kVtbl_NiVertexColorProperty = 0x109B72C,
	kVtbl_NiZBufferProperty = 0x109B7FC,
	kVtbl_NiTexture = 0x109B944,
	kVtbl_NiSourceTexture = 0x109B9EC,
	kVtbl_NiSourceCubeMap = 0x109BABC,
	kVtbl_NiRenderer = 0x109BB94,
	kVtbl_NiStream = 0x109BDCC,
	kVtbl_NiGeometryData = 0x109BF9C,
	kVtbl_NiDynamicEffect = 0x109C174,
	kVtbl_NiCullingProcess = 0x109C28C,
	kVtbl_NiTexturingProperty = 0x109C514,
	kVtbl_NiTimeController = 0x109C874,
	kVtbl_NiCamera = 0x109CB9C,
	kVtbl_NiTriStrips = 0x109CD44,
	kVtbl_NiLight = 0x109CE4C,
	kVtbl_NiStringExtraData = 0x109D39C,
	kVtbl_NiTriShape = 0x109D454,
	kVtbl_NiLines = 0x109D55C,
	kVtbl_NiMaterialProperty = 0x109D6C4,
	kVtbl_NiDirectionalLight = 0x109D7B4,
	kVtbl_NiTriStripsData = 0x109D8AC,
	kVtbl_NiImageConverter = 0x109D9A4,
	kVtbl_NiDevImageConverter = 0x109D9C4,
	kVtbl_NiExtraData = 0x109DA1C,
	kVtbl_NiTriShapeData = 0x109DAC4,
	kVtbl_NiPixelData = 0x109DBB4,
	kVtbl_NiPointLight = 0x109DD0C,
	kVtbl_NiGeometryGroupManager = 0x109DF2C,
	kVtbl_NiRenderedTexture = 0x109DF8C,
	kVtbl_NiGeometry = 0x109E04C,
	kVtbl_NiCollisionObject = 0x109E174,
	kVtbl_NiShadeProperty = 0x109E274,
	kVtbl_NiTriShapeDynamicData = 0x109E32C,
	kVtbl_NiSkinPartition = 0x109E47C,
	kVtbl_NiSkinData = 0x109E574,
	kVtbl_BSResizableTriShape = 0x109E704,
	kVtbl_BSSegmentedTriShape = 0x109E834,
	kVtbl_NiScreenElements = 0x109E984,
	kVtbl_NiScreenElementsData = 0x109EA94,
	kVtbl_NiFloatsExtraData = 0x109EC0C,
	kVtbl_NiColorExtraData = 0x109ECCC,
	kVtbl_NiTriBasedGeom = 0x109ED94,
	kVtbl_NiVertWeightsExtraData = 0x109EE9C,
	kVtbl_NiLinesData = 0x109F23C,
	kVtbl_NiTriBasedGeomData = 0x109F2F4,
	kVtbl_NiImageReader = 0x109F3D0,
	kVtbl_NiNIFImageReader = 0x109F3E4,
	kVtbl_NiPalette = 0x109F3FC,
	kVtbl_NiDDSReader = 0x109F48C,
	kVtbl_NiTGAReader = 0x109F4B0,
	kVtbl_NiBMPReader = 0x109F4C4,
	kVtbl_Ni2DBuffer = 0x109F4DC,
	kVtbl_NiShader = 0x109F584,
	kVtbl_NiCullingProperty = 0x109F68C,
	kVtbl_NiMaterial = 0x109F73C,
	kVtbl_NiSingleShaderMaterialLibrary = 0x109F7B4,
	kVtbl_NiMaterialLibrary = 0x109F7F4,
	kVtbl_NiScreenGeometry = 0x109F81C,
	kVtbl_NiScreenPolygon = 0x109F914,
	kVtbl_NiScreenGeometryData = 0x109F9C4,
	kVtbl_NiScreenSpaceCamera = 0x109FAB4,
	kVtbl_NiVectorExtraData = 0x109FB94,
	kVtbl_NiTriStripsDynamicData = 0x109FC54,
	kVtbl_NiTextureEffect = 0x109FD0C,
	kVtbl_NiSwitchStringExtraData = 0x109FF64,
	kVtbl_NiSwitchNode = 0x10A001C,
	kVtbl_NiStringsExtraData = 0x10A0134,
	kVtbl_NiSpotLight = 0x10A01CC,
	kVtbl_NiSpecularProperty = 0x10A02E4,
	kVtbl_NiSortAdjustNode = 0x10A0384,
	kVtbl_NiScreenTexture = 0x10A048C,
	kVtbl_NiScreenLODData = 0x10A051C,
	kVtbl_NiParticlesData = 0x10A05E4,
	kVtbl_NiRangeLODData = 0x10A073C,
	kVtbl_NiPersistentSrcTextureRendererData = 0x10A08AC,
	kVtbl_NiParticleMeshesData = 0x10A09BC,
	kVtbl_NiParticleMeshes = 0x10A0A6C,
	kVtbl_NiLODNode = 0x10A0B64,
	kVtbl_NiIntegersExtraData = 0x10A0C7C,
	kVtbl_NiIntegerExtraData = 0x10A0D24,
	kVtbl_NiFogProperty = 0x10A0E0C,
	kVtbl_NiFloatExtraData = 0x10A0EC4,
	kVtbl_NiDitherProperty = 0x10A0F6C,
	kVtbl_NiBSPNode = 0x10A1024,
	kVtbl_NiBooleanExtraData = 0x10A112C,
	kVtbl_NiParticles = 0x10A11D4,
	kVtbl_NiAmbientLight = 0x10A12CC,
	kVtbl_NiAlphaAccumulator = 0x10A13AC,
	kVtbl_NiShaderConstantMap = 0x10A1478,
	kVtbl_NiDepthStencilBuffer = 0x10A2084,
	kVtbl_NiGlobalConstantEntry = 0x10A2148,
	kVtbl_NiShaderFactory = 0x10A2164,
	kVtbl_NiSingleShaderMaterial = 0x10A21DC,
	kVtbl_NiLODData = 0x10A2254,
	kVtbl_NiAccumulator = 0x10A2304,
	kVtbl_NiBackToFrontAccumulator = 0x10A23AC,
	kVtbl_NiFile = 0x10A2490,
	kVtbl_NiBinaryStream = 0x10A24B8,
	kVtbl_NiAllocator = 0x10A24D0,
	kVtbl_NiStandardAllocator = 0x10A24FC,
	kVtbl_BSNiAllocator = 0x10A2528,
	kVtbl_NiSearchPath = 0x10A2554,
	kVtbl_NiMemStream = 0x10A256C,
	kVtbl_BSCoreMessage = 0x10A2708,
	kVtbl_BSThread = 0x10A27D4,
	kVtbl_ZeroOverheadHeap = 0x10A2884,
	kVtbl_IMemoryHeap = 0x10A28C8,
	kVtbl_MemoryHeap = 0x10A28FC,
	kVtbl_AbstractHeap = 0x10A2BBC,
	kVtbl_FutBinaryFileC = 0x10A2C20,
	kVtbl_BSFaceGenBinaryFile = 0x10A2C38,
	kVtbl_BSAudio = 0x10A323C,
	kVtbl_BSAudioManager = 0x10A3368,
	kVtbl_BSAudioManagerThread = 0x10A33D0,
	kVtbl_AudioLoadTask = 0x10A3718,
	kVtbl_BSGameSound = 0x10A3964,
	kVtbl_BSWin32Audio = 0x10A39D8,
	kVtbl_BSWin32AudioListener = 0x10A3B7C,
	kVtbl_BSAudioListener = 0x10A3BB4,
	kVtbl_BSWin32GameSound = 0x10A3BF4,
	kVtbl_BSSaveDataSystemUtility = 0x10A4288,
	kVtbl_BSSystemUtility = 0x10A42B4,
	kVtbl_BSMsgDialogSystemUtility = 0x10A42CC,
	kVtbl_BSSystemUtilitiesStrings = 0x10A42DC,
	kVtbl_BSCacheDriveSystemUtility = 0x10A42EC,
	kVtbl_BSGameDataSystemUtility = 0x10A42FC,
	kVtbl_BSDiscBootSystemUtility = 0x10A4318,
	kVtbl_BSSysInfoSystemUtility = 0x10A4328,
	kVtbl_Archive = 0x10A45AC,
	kVtbl_ArchiveFile = 0x10A45FC,
	kVtbl_CompressedArchiveFile = 0x10A464C,
	kVtbl_BSFile = 0x10A4764,
	kVtbl_BSTaskletManagerCallback = 0x10A47B8,
	kVtbl_BSFileCache = 0x10A47CC,
	kVtbl_BSSearchPath = 0x10A4810,
	kVtbl_BSWin32FileCache = 0x10A483C,
	kVtbl_BSWin32TaskletManager = 0x10A4880,
	kVtbl_BSTaskletManager = 0x10A48AC,
	kVtbl_BSWin32TaskletGroupData = 0x10A48D8,
	kVtbl_BSTaskletGroupData = 0x10A48E8,
	kVtbl_IdvFileError = 0x10A51E0,
	kVtbl_CTreeEngine = 0x10A5670,
	kVtbl_CIdvCamera = 0x10A5890,
	kVtbl_Uniform = 0x10A58A0,
	kVtbl_Random = 0x10A58C8,
	kVtbl_CBillboardLeaf = 0x10A58FC,
	kVtbl_PosGen = 0x10A59D4,
	kVtbl_Normal = 0x10A5A2C,
	kVtbl_SymGen = 0x10A5A54,
	kVtbl_BSFadeNode = 0x10A8F90,
	kVtbl_DistantLODShaderProperty = 0x10ADAD0,
	kVtbl_ShadowSceneNode = 0x10ADCF8,
	kVtbl_TallGrassShaderProperty = 0x10ADEA8,
	kVtbl_BSShaderPPLightingProperty = 0x10AE0D0,
	kVtbl_WaterShaderProperty = 0x10AE438,
	kVtbl_BSShaderNoLightingProperty = 0x10AE670,
	kVtbl_BSShaderLightingProperty = 0x10AE7B0,
	kVtbl_BSShaderBloodSplatterProperty = 0x10AF8E8,
	kVtbl_BSBatchRenderer = 0x10B7DC8,
	kVtbl_LightingData = 0x10B7EB8,
	kVtbl_ParticleShader = 0x10B80A8,
	kVtbl_ParticleShaderProperty = 0x10B8250,
	kVtbl_SpeedTreeBillboardShaderProperty = 0x10B8330,
	kVtbl_BSShaderProperty = 0x10B8488,
	kVtbl_TallGrassShader = 0x10B8980,
	kVtbl_SkyShaderProperty = 0x10B8CE0,
	kVtbl_PrecipitationShader = 0x10B8E80,
	kVtbl_PrecipitationShaderProperty = 0x10B9008,
	kVtbl_SpeedTreeLeafShader = 0x10B9190,
	kVtbl_SpeedTreeBranchShaderProperty = 0x10B9338,
	kVtbl_SpeedTreeShaderPPLightingProperty = 0x10B9490,
	kVtbl_SpeedTreeShaderLightingProperty = 0x10B95C0,
	kVtbl_SpeedTreeLeafShaderProperty = 0x10B9700,
	kVtbl_GeometryDecalShaderProperty = 0x10B9828,
	kVtbl_Lighting30ShaderProperty = 0x10B9910,
	kVtbl_BSDistantTreeShader = 0x10B9AA8,
	kVtbl_BSDistantTreeShaderProperty = 0x10B9C40,
	kVtbl_TileShaderProperty = 0x10B9D28,
	kVtbl_BSFogProperty = 0x10B9E38,
	kVtbl_Lighting30Shader = 0x10BA0F8,
	kVtbl_BoltShader = 0x10BA3B0,
	kVtbl_BoltShaderProperty = 0x10BA528,
	kVtbl_BSClearZNode = 0x10BA608,
	kVtbl_BSOrderedNode = 0x10BA730,
	kVtbl_BSMaterialEmittanceMultController = 0x10BA858,
	kVtbl_BSRefractionFirePeriodController = 0x10BA948,
	kVtbl_BSRefractionStrengthController = 0x10BAA38,
	kVtbl_VolumetricFogShaderProperty = 0x10BAB28,
	kVtbl_HairShaderProperty = 0x10BABF8,
	kVtbl_BeamShader = 0x10BAD98,
	kVtbl_VolumetricFogShader = 0x10BAF60,
	kVtbl_BSShaderNoLighting = 0x10BB230,
	kVtbl_TileShader = 0x10BB410,
	kVtbl_GeometryDecalShader = 0x10BB588,
	kVtbl_ParallaxShader = 0x10BB7A8,
	kVtbl_SkinShader = 0x10BB980,
	kVtbl_HairShader = 0x10BBB50,
	kVtbl_SpeedTreeBranchShader = 0x10BC070,
	kVtbl_DistantLODShader = 0x10BC260,
	kVtbl_BSCubeMapCamera = 0x10BC470,
	kVtbl_NiParticleSystem = 0x10BD44C,
	kVtbl_NiPSysEmitterCtlr = 0x10BD594,
	kVtbl_NiPSysMeshEmitter = 0x10BD7FC,
	kVtbl_NiPSysCylinderEmitter = 0x10BD8B4,
	kVtbl_NiPSysSphereEmitter = 0x10BD974,
	kVtbl_NiPSysBoxEmitter = 0x10BDA2C,
	kVtbl_NiPSysRotationModifier = 0x10BDAEC,
	kVtbl_NiPSysMeshUpdateModifier = 0x10BDC4C,
	kVtbl_NiMeshParticleSystem = 0x10BDD84,
	kVtbl_NiPSysEmitter = 0x10BDE84,
	kVtbl_NiPSysGravityModifier = 0x10BDFF4,
	kVtbl_NiPSysSpawnModifier = 0x10BE124,
	kVtbl_NiPSysData = 0x10BE254,
	kVtbl_BSStripParticleSystem = 0x10BE35C,
	kVtbl_NiPSysUpdateTask = 0x10BE45C,
	kVtbl_BSStripPSysData = 0x10BE514,
	kVtbl_NiPSysVortexFieldModifier = 0x10BE604,
	kVtbl_NiPSysUpdateCtlr = 0x10BE6B4,
	kVtbl_NiPSysTurbulenceFieldModifier = 0x10BE774,
	kVtbl_NiPSysSphericalCollider = 0x10BE834,
	kVtbl_NiPSysResetOnLoopCtlr = 0x10BE8E4,
	kVtbl_NiPSysRadialFieldModifier = 0x10BE99C,
	kVtbl_NiPSysPositionModifier = 0x10BEA54,
	kVtbl_NiPSysPlanarCollider = 0x10BEB0C,
	kVtbl_NiPSysModifierActiveCtlr = 0x10BEBBC,
	kVtbl_NiPSysInitialRotSpeedVarCtlr = 0x10BECBC,
	kVtbl_NiPSysInitialRotSpeedCtlr = 0x10BEDBC,
	kVtbl_NiPSysInitialRotAngleVarCtlr = 0x10BEEBC,
	kVtbl_NiPSysInitialRotAngleCtlr = 0x10BEFBC,
	kVtbl_NiPSysGrowFadeModifier = 0x10BF0BC,
	kVtbl_NiPSysGravityStrengthCtlr = 0x10BF1AC,
	kVtbl_NiPSysGravityFieldModifier = 0x10BF2AC,
	kVtbl_NiPSysFieldMaxDistanceCtlr = 0x10BF354,
	kVtbl_NiPSysFieldMagnitudeCtlr = 0x10BF454,
	kVtbl_NiPSysFieldAttenuationCtlr = 0x10BF554,
	kVtbl_NiPSysEmitterSpeedCtlr = 0x10BF654,
	kVtbl_NiPSysEmitterPlanarAngleVarCtlr = 0x10BF754,
	kVtbl_NiPSysEmitterPlanarAngleCtlr = 0x10BF854,
	kVtbl_NiPSysEmitterLifeSpanCtlr = 0x10BF954,
	kVtbl_NiPSysEmitterInitialRadiusCtlr = 0x10BFA54,
	kVtbl_NiPSysEmitterDeclinationVarCtlr = 0x10BFB54,
	kVtbl_NiPSysEmitterDeclinationCtlr = 0x10BFC54,
	kVtbl_NiPSysEmitterCtlrData = 0x10BFD54,
	kVtbl_NiPSysDragModifier = 0x10BFE44,
	kVtbl_NiPSysDragFieldModifier = 0x10BFF2C,
	kVtbl_NiPSysColorModifier = 0x10BFFE4,
	kVtbl_NiPSysColliderManager = 0x10C008C,
	kVtbl_NiPSysBoundUpdateModifier = 0x10C0134,
	kVtbl_NiPSysBombModifier = 0x10C01EC,
	kVtbl_NiPSysAgeDeathModifier = 0x10C0304,
	kVtbl_NiPSysAirFieldSpreadCtlr = 0x10C03CC,
	kVtbl_NiPSysAirFieldModifier = 0x10C04CC,
	kVtbl_NiPSysAirFieldInheritVelocityCtlr = 0x10C05E4,
	kVtbl_NiPSysAirFieldAirFrictionCtlr = 0x10C06E4,
	kVtbl_NiMeshPSysData = 0x10C07EC,
	kVtbl_NiPSysModifierCtlr = 0x10C08AC,
	kVtbl_NiPSysModifier = 0x10C09CC,
	kVtbl_NiPSysVolumeEmitter = 0x10C0A8C,
	kVtbl_NiPSysFieldModifier = 0x10C0B5C,
	kVtbl_NiPSysCollider = 0x10C0C4C,
	kVtbl_NiPSysModifierBoolCtlr = 0x10C0D2C,
	kVtbl_NiPSysModifierFloatCtlr = 0x10C0E44,
	kVtbl_BSMultiBound = 0x10C0F7C,
	kVtbl_BSMultiBoundRoom = 0x10C1064,
	kVtbl_BSReference = 0x10C1364,
	kVtbl_BSNodeReferences = 0x10C13F4,
	kVtbl_MessageHandler = 0x10C14A8,
	kVtbl_QueuedChildren = 0x10C14E8,
	kVtbl_QueuedParents = 0x10C1510,
	kVtbl_QueuedFile = 0x10C1524,
	kVtbl_QueuedFileEntry = 0x10C1554,
	kVtbl_IOManager = 0x10C1604,
	kVtbl_BSTaskThread = 0x10C1844,
	kVtbl_BSXFlags = 0x10C1854,
	kVtbl_BSValueNode = 0x10C195C,
	kVtbl_BSParallelTaskThread = 0x10C1AF0,
	kVtbl_BSRangeNode = 0x10C1B2C,
	kVtbl_BSWindModifier = 0x10C1C6C,
	kVtbl_BSMultiBoundNode = 0x10C1D14,
	kVtbl_BSBlastNode = 0x10C1EB4,
	kVtbl_BSDebrisNode = 0x10C1FC4,
	kVtbl_BSDamageStage = 0x10C20D4,
	kVtbl_BSPortalSharedNode = 0x10C21FC,
	kVtbl_BSMultiBoundShape = 0x10C2324,
	kVtbl_BSParticleSystemManager = 0x10C23FC,
	kVtbl_UpdateMasterPsysTaskletData = 0x10C256C,
	kVtbl_BSSceneGraph = 0x10C2714,
	kVtbl_NiBSBoneLODController = 0x10C29CC,
	kVtbl_BSFurnitureMarker = 0x10C2A94,
	kVtbl_BSBound = 0x10C2B64,
	kVtbl_BSPortalGraph = 0x10C2D44,
	kVtbl_BSPSysMultiTargetEmitterCtlr = 0x10C2D54,
	kVtbl_BSScissorTriShape = 0x10C2E7C,
	kVtbl_BSMasterParticleSystem = 0x10C2FB4,
	kVtbl_BSTextureData = 0x10C30F4,
	kVtbl_BSNiNode = 0x10C31A4,
	kVtbl_BSPSysStripUpdateModifier = 0x10C32C4,
	kVtbl_BSPSysSimpleColorModifier = 0x10C3384,
	kVtbl_BSMultiBoundCapsule = 0x10C34AC,
	kVtbl_BSWArray = 0x10C357C,
	kVtbl_PArrayPoint = 0x10C361C,
	kVtbl_BSPSysArrayEmitter = 0x10C36C4,
	kVtbl_BSParentVelocityModifier = 0x10C37FC,
	kVtbl_BSDecalPlacementVectorExtraData = 0x10C38AC,
	kVtbl_BSAttachPoints = 0x10C396C,
	kVtbl_bhkMemoryAllocator = 0x10C3AF8,
	kVtbl_hkMemoryAllocator = 0x10C3B30,
	kVtbl_bhkOnStartupCallback = 0x10C3B68,
	kVtbl_bhkOnExitCallback = 0x10C3B74,
	kVtbl_hkpCollidableCollidableFilter = 0x10C3B80,
	kVtbl_hkpRayCollidableFilter = 0x10C3B8C,
	kVtbl_hkpShapeCollectionFilter = 0x10C3B98,
	kVtbl_hkpRayShapeCollectionFilter = 0x10C3BAC,
	kVtbl_hkpBroadPhaseCastCollector = 0x10C3BB8,
	kVtbl_ahkpWorld = 0x10C3BC4,
	kVtbl_hkpWorldRayCaster = 0x10C3BD4,
	kVtbl_bhkCollisionFilter = 0x10C3C18,
	kVtbl_bhkWorldCinfo = 0x10C3C44,
	kVtbl_bhkWorld = 0x10C40B4,
	kVtbl_bhkNiCollisionObject = 0x10C4314,
	kVtbl_hkpCharacterProxyListener = 0x10C446C,
	kVtbl_bhkCharacterListener = 0x10C4488,
	kVtbl_bhkShapeCollection = 0x10C44E4,
	kVtbl_bhkCharacterProxy = 0x10C45CC,
	kVtbl_bhkCachingShapePhantom = 0x10C4694,
	kVtbl_hkpClosestCdPointCollector = 0x10C476C,
	kVtbl_bhkCollisionBox = 0x10C477C,
	kVtbl_bhkListShape = 0x10C485C,
	kVtbl_bhkCharacterStateClimbing = 0x10C4944,
	kVtbl_bhkCharacterStateFlying = 0x10C496C,
	kVtbl_bhkCharacterController = 0x10C49C4,
	kVtbl_bhkWindListener = 0x10C4B2C,
	kVtbl_hkaRaycastInterface = 0x10C4B60,
	kVtbl_bhkRagdollShareData = 0x10C4B74,
	kVtbl_bhkRagdollController = 0x10C4DDC,
	kVtbl_hkaSkeleton = 0x10C4DEC,
	kVtbl_bhkStiffSpringConstraint = 0x10C52BC,
	kVtbl_hkStiffSpringConstraintCinfo = 0x10C5398,
	kVtbl_bhkBlendCollisionObject = 0x10C53DC,
	kVtbl_hkpMotion = 0x10C59F4,
	kVtbl_bhkRefObject = 0x10C5B54,
	kVtbl_WeaponObject = 0x10C5C1C,
	kVtbl_bhkLimitedHingeConstraint = 0x10C5CE4,
	kVtbl_hkLimitedHingeConstraintCinfo = 0x10C5DC0,
	kVtbl_bhkBinaryAction = 0x10C5EF4,
	kVtbl_bhkBlendCollisionObjectAddRotation = 0x10C6234,
	kVtbl_hkReferencedObjectLock = 0x10C6334,
	kVtbl_hkpNullContactMgr = 0x10C6378,
	kVtbl_hkpBroadPhaseListener = 0x10C63BC,
	kVtbl_hkpDefaultConvexListFilter = 0x10C63CC,
	kVtbl_hkpPhantomBroadPhaseListener = 0x10C63F0,
	kVtbl_hkpBroadPhaseBorderListener = 0x10C6410,
	kVtbl_hkpNullContactMgrFactory = 0x10C6420,
	kVtbl_hkpNullCollisionFilter = 0x10C646C,
	kVtbl_hkpSimpleWorldRayCaster = 0x10C647C,
	kVtbl_hkpWorldLinearCaster = 0x10C6488,
	kVtbl_hkpWorld = 0x10C6714,
	kVtbl_hkDebugDisplay = 0x10C69CC,
	kVtbl_bhkWorldM = 0x10C69F4,
	kVtbl_bhkBlendController = 0x10C6B14,
	kVtbl_hkpKeyframedRigidMotion = 0x10C6BEC,
	kVtbl_hkpMaxSizeMotion = 0x10C6C64,
	kVtbl_hkpFixedRigidMotion = 0x10C6CDC,
	kVtbl_hkpSphereMotion = 0x10C6D54,
	kVtbl_hkpBoxMotion = 0x10C6DC4,
	kVtbl_hkpThinBoxMotion = 0x10C6E34,
	kVtbl_hkpCharacterMotion = 0x10C6EA4,
	kVtbl_hkpWorldObject = 0x10C6F64,
	kVtbl_hkpEntity = 0x10C6F7C,
	kVtbl_hkpShapeContainer = 0x10C6FB0,
	kVtbl_hkpSingleShapeContainer = 0x10C6FD0,
	kVtbl_hkpBvShape = 0x10C6FF8,
	kVtbl_hkpBoxShape = 0x10C70B4,
	kVtbl_hkpConvexTransformShapeBase = 0x10C710C,
	kVtbl_hkpPhantom = 0x10C7214,
	kVtbl_hkpShapePhantom = 0x10C7254,
	kVtbl_hkaRagdollRaycastInterface = 0x10C7304,
	kVtbl_bhkRagdollPenetrationUtil = 0x10C7324,
	kVtbl_hkPackedNiTriStripsData = 0x10C740C,
	kVtbl_hkpTriangleShape = 0x10C749C,
	kVtbl_hkNormalTriangleShape = 0x10C74EC,
	kVtbl_hkPackedNiTriStripsShape = 0x10C755C,
	kVtbl_hkNiTriStripsShape = 0x10C75C4,
	kVtbl_bhkPackedNiTriStripsShape = 0x10C761C,
	kVtbl_bhkNiTriStripsShape = 0x10C771C,
	kVtbl_hkpRigidBody = 0x10C7888,
	kVtbl_hkpCharacterContext = 0x10C8198,
	kVtbl_bhkMalleableConstraint = 0x10C81AC,
	kVtbl_hkMalleableConstraintCinfo = 0x10C8288,
	kVtbl_hkpMalleableConstraintData = 0x10C82A4,
	kVtbl_ahkpMalleableConstraintData = 0x10C82EC,
	kVtbl_ahkpCharacterProxy = 0x10C83E8,
	kVtbl_hkpCharacterProxy = 0x10C84A4,
	kVtbl_hkBSHeightFieldShape = 0x10C853C,
	kVtbl_hkErrStream = 0x10C85A0,
	kVtbl_bhkRigidBodyT = 0x10C879C,
	kVtbl_bhkWaterListener = 0x10C88B8,
	kVtbl_bhkOrientHingedBodyAction = 0x10C8914,
	kVtbl_hkpLimitedHingeConstraintData = 0x10C89E4,
	kVtbl_bhkForceController = 0x10C8A2C,
	kVtbl_bhkBallAndSocketConstraint = 0x10C8B0C,
	kVtbl_bhkRagdollConstraint = 0x10C8BEC,
	kVtbl_hkBallAndSocketConstraintCinfo = 0x10C8CC8,
	kVtbl_hkRagdollConstraintCinfo = 0x10C8CE4,
	kVtbl_bhkRagdollTemplateData = 0x10C8D3C,
	kVtbl_bhkRagdollTemplate = 0x10C8DCC,
	kVtbl_hkpMouseSpringAction = 0x10C8E94,
	kVtbl_hkNativeFileSystem = 0x10C8EB8,
	kVtbl_hkDummySingleton = 0x10C8ED4,
	kVtbl_hkMemorySystem = 0x10C8EFC,
	kVtbl_hkpCharacterStateManager = 0x10C9194,
	kVtbl_hkpHingeConstraintData = 0x10C91EC,
	kVtbl_hkpPhantomOverlapListener = 0x10C925C,
	kVtbl_hkpCollisionFilter = 0x10C92D4,
	kVtbl_hkOstream = 0x10C9314,
	kVtbl_hkMemoryTrackStreamWriter = 0x10C933C,
	kVtbl_hkArrayStreamWriter = 0x10C9368,
	kVtbl_bhkPoseArray = 0x10C93FC,
	kVtbl_bhkExtraData = 0x10C94A4,
	kVtbl_bhkSpringAction = 0x10C955C,
	kVtbl_bhkMotorAction = 0x10C9634,
	kVtbl_bhkDashpotAction = 0x10C970C,
	kVtbl_bhkAngularDashpotAction = 0x10C97E4,
	kVtbl_bhkBreakableConstraint = 0x10C98BC,
	kVtbl_ahkpBreakableConstraintData = 0x10C999C,
	kVtbl_hkBreakableConstraintCinfo = 0x10C99E0,
	kVtbl_bhkWheelConstraint = 0x10C9A14,
	kVtbl_hkWheelConstraintCinfo = 0x10C9AF0,
	kVtbl_bhkRagdollLimitsConstraint = 0x10C9B0C,
	kVtbl_hkRagdollLimitsConstraintCinfo = 0x10C9BE8,
	kVtbl_bhkPrismaticConstraint = 0x10C9C84,
	kVtbl_hkPrismaticConstraintCinfo = 0x10C9D60,
	kVtbl_bhkFixedConstraint = 0x10C9D7C,
	kVtbl_bhkGenericConstraint = 0x10C9E5C,
	kVtbl_hkGenericConstraintCinfo = 0x10C9F38,
	kVtbl_hkFixedConstraintCinfo = 0x10C9F54,
	kVtbl_bhkHingeLimitsConstraint = 0x10C9F74,
	kVtbl_hkHingeLimitsConstraintCinfo = 0x10CA050,
	kVtbl_bhkBallSocketConstraintChain = 0x10CA06C,
	kVtbl_bhkConstraintChain = 0x10CA14C,
	kVtbl_hkBallSocketChainCinfo = 0x10CA22C,
	kVtbl_bhkMoppBvTreeShape = 0x10CA24C,
	kVtbl_hkScaledMoppBvTreeShape = 0x10CA330,
	kVtbl_bhkTriangleShape = 0x10CA3F4,
	kVtbl_bhkPlaneShape = 0x10CA4DC,
	kVtbl_bhkHeightFieldShape = 0x10CA5C4,
	kVtbl_bhkExtendedMeshShapeData = 0x10CA6B4,
	kVtbl_bhkExtendedMeshShape = 0x10CA744,
	kVtbl_bhkCylinderShape = 0x10CA834,
	kVtbl_bhkConvexVerticesShape = 0x10CA924,
	kVtbl_bhkConvexTransformShape = 0x10CAA0C,
	kVtbl_bhkConvexSweepShape = 0x10CAAF4,
	kVtbl_bhkConvexListShape = 0x10CABDC,
	kVtbl_hkThreadMemory = 0x10CACD0,
	kVtbl_hkMemoryBlockServer = 0x10CAD0C,
	kVtbl_hkLeakDetectAllocator = 0x10CAD3C,
	kVtbl_hkFreeListMemorySystem = 0x10CAD74,
	kVtbl_hkVisualDebugger = 0x10CB100,
	kVtbl_hkpWorldDeletionListener = 0x10CB1C4,
	kVtbl_hkpActionListener = 0x10CB1D4,
	kVtbl_hkpConstraintListener = 0x10CB1E4,
	kVtbl_hkProcessContext = 0x10CB220,
	kVtbl_hkpPhysicsContext = 0x10CB2B4,
	kVtbl_bhkCharacterPointCollector = 0x10CB300,
	kVtbl_bhkCharacterStateProjectile = 0x10CB344,
	kVtbl_bhkCharacterStateInAir = 0x10CB36C,
	kVtbl_bhkCharacterStateJumping = 0x10CB398,
	kVtbl_bhkCharacterStateSwimming = 0x10CB3C4,
	kVtbl_bhkCharacterStateOnGround = 0x10CB3F0,
	kVtbl_hkCharControllerShape = 0x10CB45C,
	kVtbl_bhkCharControllerShape = 0x10CB4AC,
	kVtbl_hkpSphereShape = 0x10CB5AC,
	kVtbl_hkaFootPlacementIkSolver = 0x10CB644,
	kVtbl_hkpRagdollConstraintData = 0x10CB71C,
	kVtbl_hkpConstraintMotor = 0x10CB76C,
	kVtbl_hkpLimitedForceConstraintMotor = 0x10CB780,
	kVtbl_hkpPositionConstraintMotor = 0x10CB798,
	kVtbl_hkaRagdollInstance = 0x10CB830,
	kVtbl_hkaSkeletonMapper = 0x10CB864,
	kVtbl_hkpAabbPhantom = 0x10CC004,
	kVtbl_hkpConstraintInstance = 0x10CC040,
	kVtbl_bhkPositionConstraintMotor = 0x10CC064,
	kVtbl_hkpVelocityConstraintMotor = 0x10CC0D8,
	kVtbl_bhkVelocityConstraintMotor = 0x10CC0EC,
	kVtbl_bhkSpringDamperConstraintMotor = 0x10CC164,
	kVtbl_hkPointToPathConstraintCinfo = 0x10CC2E0,
	kVtbl_hkpAction = 0x10CC2FC,
	kVtbl_hkpBinaryAction = 0x10CC320,
	kVtbl_hkpShapeCollection = 0x10CC364,
	kVtbl_hkpListShape = 0x10CC3D8,
	kVtbl_hkpTransformShape = 0x10CC41C,
	kVtbl_hkpNullBroadPhaseListener = 0x10CC4E0,
	kVtbl_hkpSimulation = 0x10CC4F4,
	kVtbl_hkpCollisionDispatcher = 0x10CC7C0,
	kVtbl_hkpReportContactMgr = 0x10CC86C,
	kVtbl_hkpSimpleContactConstraintData = 0x10CC934,
	kVtbl_hkpSimpleConstraintContactMgr = 0x10CC984,
	kVtbl_hkpMultiThreadedSimulation = 0x10CCBC4,
	kVtbl_hkpPhysicsSystem = 0x10CCE28,
	kVtbl_hkStatisticsCollector = 0x10CCE98,
	kVtbl_hkpConstraintOwner = 0x10CCEBC,
	kVtbl_hkpSimulationIsland = 0x10CCF28,
	kVtbl_hkpWorldPostSimulationListener = 0x10CCF7C,
	kVtbl_hkKdTreeCastCollector = 0x10CCF8C,
	kVtbl_hkpKdTreeCollidableRaycaster = 0x10CCFB8,
	kVtbl_hkpKdTreeWorldLinearCaster = 0x10CCFCC,
	kVtbl_hkpAabbTreeWorldManager = 0x10CD078,
	kVtbl_hkpKdTreeWorldManager = 0x10CD278,
	kVtbl_hkpCollisionCallbackUtil = 0x10CD33C,
	kVtbl_hkpDefaultWorldMaintenanceMgr = 0x10CD34C,
	kVtbl_hkpBroadPhaseBorder = 0x10CD3C4,
	kVtbl_hkpContinuousSimulation = 0x10CD45C,
	kVtbl_hkpNullAgent = 0x10CD54C,
	kVtbl_hkpEntityEntityBroadPhaseListener = 0x10CD598,
	kVtbl_hkp3AxisSweep = 0x10CD5CC,
	kVtbl_hkpSimpleShapePhantom = 0x10CE15C,
	kVtbl_hkaDetectRagdollPenetration = 0x10CE1A8,
	kVtbl_hkpCapsuleShape = 0x10CE25C,
	kVtbl_hkDisplayGeometry = 0x10CE2B4,
	kVtbl_hkDisplayCapsule = 0x10CE2CC,
	kVtbl_hkpSampledHeightFieldShape = 0x10CE31C,
	kVtbl_hkpTriSampledHeightFieldCollection = 0x10CE390,
	kVtbl_hkpBvTreeShape = 0x10CE3C8,
	kVtbl_hkpTriSampledHeightFieldBvTreeShape = 0x10CE404,
	kVtbl_hkBufferedStreamWriter = 0x10CE448,
	kVtbl_hkpMultiSphereShape = 0x10CE4BC,
	kVtbl_hkOrientHingedBodyAction = 0x10CE504,
	kVtbl_hkpUnaryAction = 0x10CE528,
	kVtbl_hkDefaultError = 0x10CE5D4,
	kVtbl_hkSocket = 0x10CE658,
	kVtbl_hkBufferedStreamReader = 0x10CE688,
	kVtbl_hkStdioStreamReader = 0x10CE6C0,
	kVtbl_hkStdioStreamWriter = 0x10CE6F4,
	kVtbl_hkLiquidAction = 0x10CE740,
	kVtbl_hkCpuJobThreadPool = 0x10CE774,
	kVtbl_hkpSymmetricAgentFlipCollector = 0x10CE7FC,
	kVtbl_hkpSymmetricAgentFlipCastCollector = 0x10CE80C,
	kVtbl_hkpSymmetricAgentFlipBodyCollector = 0x10CE81C,
	kVtbl_hkpBvTreeStreamAgent = 0x10CE838,
	kVtbl_hkpBvTreeAgent = 0x10CE8F4,
	kVtbl_hkpMoppAgent = 0x10CE930,
	kVtbl_hkHeightFieldRayForwardingCollector = 0x10CEA14,
	kVtbl_hkpHeightFieldAgent = 0x10CEAA8,
	kVtbl_hkpMapPointsToSubShapeContactMgr = 0x10CEB44,
	kVtbl_hkpPredGskfAgent = 0x10CEB94,
	kVtbl_hkpFlagCdBodyPairCollector = 0x10CEBD0,
	kVtbl_hkpSimpleClosestContactCollector = 0x10CEBE0,
	kVtbl_hkpConvexListAgent = 0x10CEBF0,
	kVtbl_hkpListAgent = 0x10CED34,
	kVtbl_hkpMultiRayConvexAgent = 0x10CEDD4,
	kVtbl_hkpMultiSphereTriangleAgent = 0x10CEE4C,
	kVtbl_hkpCapsuleTriangleAgent = 0x10CEEFC,
	kVtbl_hkpCapsuleCapsuleAgent = 0x10CEF94,
	kVtbl_hkpSphereBoxAgent = 0x10CEFDC,
	kVtbl_hkpSphereTriangleAgent = 0x10CF060,
	kVtbl_hkpSphereCapsuleAgent = 0x10CF0E4,
	kVtbl_hkpSphereSphereAgent = 0x10CF16C,
	kVtbl_hkpBoxBoxAgent = 0x10CF1C4,
	kVtbl_hkpPhantomAgent = 0x10CF238,
	kVtbl_hkpTransformAgent = 0x10CF280,
	kVtbl_hkpShapeCollectionAgent = 0x10CF318,
	kVtbl_hkpMultiSphereAgent = 0x10CF354,
	kVtbl_hkpBvAgent = 0x10CF3CC,
	kVtbl_hkMemoryTrackStreamReader = 0x10CF734,
	kVtbl_hkDefaultBuiltinTypeRegistry = 0x10CF78C,
	kVtbl_hkTypeInfoRegistry = 0x10CF7B0,
	kVtbl_hkDynamicClassNameRegistry = 0x10CF7D4,
	kVtbl_hkDefaultClassNameRegistry = 0x10CF804,
	kVtbl_hkVtableClassRegistry = 0x10CF844,
	kVtbl_hkpPhysicsData = 0x10CF9A4,
	kVtbl_hkBinaryTagfileWriter = 0x10CF9C8,
	kVtbl_hkpStorageSampledHeightFieldShape = 0x10CFB34,
	kVtbl_hkpStorageExtendedMeshShape = 0x10CFD44,
	kVtbl_hkpStorageMeshShape = 0x10D055C,
	kVtbl_hkpPhysicsSystemWithContacts = 0x10D07F4,
	kVtbl_hkpCachingShapePhantom = 0x10D087C,
	kVtbl_hkpSpringAction = 0x10D08F4,
	kVtbl_hkpMotorAction = 0x10D0944,
	kVtbl_hkpDashpotAction = 0x10D0994,
	kVtbl_hkpAngularDashpotAction = 0x10D09F4,
	kVtbl_hkpBreakableConstraintData = 0x10D0A1C,
	kVtbl_hkpWheelConstraintData = 0x10D0A64,
	kVtbl_hkpStiffSpringConstraintData = 0x10D0AAC,
	kVtbl_hkpRagdollLimitsData = 0x10D0AF4,
	kVtbl_hkpPrismaticConstraintData = 0x10D0B3C,
	kVtbl_hkpGenericConstraintData = 0x10D0B9C,
	kVtbl_hkpHingeLimitsData = 0x10D0BE4,
	kVtbl_hkpBallSocketChainData = 0x10D0C8C,
	kVtbl_hkpBallAndSocketConstraintData = 0x10D0CD4,
	kVtbl_hkMoppBvTreeShapeBase = 0x10D0D70,
	kVtbl_hkpMoppBvTreeShape = 0x10D0DAC,
	kVtbl_hkpPlaneShape = 0x10D0E18,
	kVtbl_hkpConvexTranslateShape = 0x10D0E5C,
	kVtbl_hkpExtendedMeshShape = 0x10D0ECC,
	kVtbl_hkpCylinderShape = 0x10D0F1C,
	kVtbl_hkDisplayCylinder = 0x10D0F84,
	kVtbl_hkpConvexVerticesShape = 0x10D0FC4,
	kVtbl_hkpConvexTransformShape = 0x10D102C,
	kVtbl_hkpConvexListShape = 0x10D10C4,
	kVtbl_hkSolverAllocator = 0x10D1110,
	kVtbl_hkFreeListAllocator = 0x10D1464,
	kVtbl_hkSystemMemoryBlockServer = 0x10D14C8,
	kVtbl_hkOArchive = 0x10D14F8,
	kVtbl_hkProcess = 0x10D1508,
	kVtbl_hkProcessHandler = 0x10D1528,
	kVtbl_hkCommandRouter = 0x10D1548,
	kVtbl_hkServerProcessHandler = 0x10D1598,
	kVtbl_hkpWeldingViewer = 0x10D1634,
	kVtbl_hkpWorldSnapshotViewer = 0x10D1720,
	kVtbl_hkpWorldMemoryViewer = 0x10D1794,
	kVtbl_hkpVehicleViewer = 0x10D1854,
	kVtbl_hkpSweptTransformDisplayViewer = 0x10D1918,
	kVtbl_hkpSimulationIslandViewer = 0x10D1A28,
	kVtbl_hkpShapeDisplayViewer = 0x10D1B04,
	kVtbl_hkpPhantomDisplayViewer = 0x10D1BDC,
	kVtbl_hkpUserShapePhantomTypeIdentifier = 0x10D1C2C,
	kVtbl_hkpMousePickingViewer = 0x10D1CE4,
	kVtbl_hkpRigidBodyInertiaViewer = 0x10D1D80,
	kVtbl_hkpToiCountViewer = 0x10D1E6C,
	kVtbl_hkpToiContactPointViewer = 0x10D1F0C,
	kVtbl_hkpInactiveContactPointViewer = 0x10D1FB0,
	kVtbl_hkpActiveContactPointViewer = 0x10D203C,
	kVtbl_hkpConvexRadiusViewer = 0x10D20F8,
	kVtbl_hkpConstraintViewer = 0x10D21C4,
	kVtbl_hkpRigidBodyCentreOfMassViewer = 0x10D22A8,
	kVtbl_hkpMidphaseViewer = 0x10D2330,
	kVtbl_hkpBroadphaseViewer = 0x10D23B4,
	kVtbl_hkgpConvexHull = 0x10D36E0,
	kVtbl_hkpPointToPlaneConstraintData = 0x10D37E4,
	kVtbl_hkpSpringDamperConstraintMotor = 0x10D3838,
	kVtbl_hkTraceStream = 0x10D3CC0,
	kVtbl_hkpConstraintCollisionFilter = 0x10D3D18,
	kVtbl_hkpDeferredConstraintOwner = 0x10D3DF8,
	kVtbl_hkpBroadPhase = 0x10D3F7C,
	kVtbl_hkKdTreeBundleCastCollector = 0x10D4050,
	kVtbl_hkKdTreeCollidableRayBundleCaster = 0x10D4060,
	kVtbl_hkpAabbTreeCollidableRaycaster = 0x10D4094,
	kVtbl_hkpCollidableMediator = 0x10D40B4,
	kVtbl_hkpEndOfStepCallbackUtil = 0x10D40E0,
	kVtbl_hkpDefaultToiResourceMgr = 0x10D4310,
	kVtbl_hkLocalFrameGroup = 0x10D460C,
	kVtbl_hkSimpleLocalFrame = 0x10D461C,
	kVtbl_hkStackTracer = 0x10D4DE4,
	kVtbl_hkBsdSocket = 0x10D5030,
	kVtbl_hkpGskBaseAgent = 0x10D51CC,
	kVtbl_hkpGskfAgent = 0x10D5224,
	kVtbl_hkCrc32StreamWriter = 0x10D538C,
	kVtbl_hkStaticClassNameRegistry = 0x10D6014,
	kVtbl_hkVersionPatchManager = 0x10D6138,
	kVtbl_hkSerializeDeprecated = 0x10D6260,
	kVtbl_hkDataRefCounted = 0x10D62F4,
	kVtbl_hkDataClassNative = 0x10D62FC,
	kVtbl_hkDataObjectNative = 0x10D6334,
	kVtbl_hkDataArrayNative = 0x10D642C,
	kVtbl_hkDataWorldNative = 0x10D6518,
	kVtbl_hkBinaryPackfileWriter = 0x10D65BC,
	kVtbl_hkSubStreamWriter = 0x10D65EC,
	kVtbl_hkPackfileWriter = 0x10D6708,
	kVtbl_hkBinaryTagfileReader = 0x10D6CE8,
	kVtbl_ArrayOfTuplesImplementation = 0x10D6E4C,
	kVtbl_hkDataObjectDict = 0x10D6EE4,
	kVtbl_VecArrayImplementation = 0x10D6F4C,
	kVtbl_PointerArrayImplementation = 0x10D6FE4,
	kVtbl_ByteArrayImplementation = 0x10D707C,
	kVtbl_IntArrayImplementation = 0x10D7114,
	kVtbl_RealArrayImplementation = 0x10D71AC,
	kVtbl_CstringArrayImplementation = 0x10D7244,
	kVtbl_hkDataClassDict = 0x10D73C8,
	kVtbl_StructArrayImplementation = 0x10D73FC,
	kVtbl_hkDataWorldDict = 0x10D7510,
	kVtbl_hkIstream = 0x10D7540,
	kVtbl_hkpMeshShape = 0x10D7754,
	kVtbl_hkpSerializedAgentNnEntry = 0x10D77D8,
	kVtbl_hkpConstraintChainInstanceAction = 0x10D79C4,
	kVtbl_hkpConstraintChainInstance = 0x10D79E8,
	kVtbl_hkpMoppCostFunction = 0x10D7BA8,
	kVtbl_hkpMoppShapeMediator = 0x10D7BB8,
	kVtbl_hkpMoppCachedShapeMediator = 0x10D7BE4,
	kVtbl_hkFreeListAllocatorServer = 0x10D7C10,
	kVtbl_hkLargeBlockAllocator = 0x10D7C34,
	kVtbl_hkWindowsSystemClock = 0x10D7C58,
	kVtbl_hkIArchive = 0x10D7C80,
	kVtbl_hkProcessFactory = 0x10D7C90,
	kVtbl_hkDebugDisplayHandler = 0x10D7CFC,
	kVtbl_hkServerDebugDisplayHandler = 0x10D7DA8,
	kVtbl_hkDisplaySerializeOStream = 0x10D7DB8,
	kVtbl_hkDisplaySerializeIStream = 0x10D7DC8,
	kVtbl_hkInspectProcess = 0x10D7E0C,
	kVtbl_hkStatisticsProcess = 0x10D7E48,
	kVtbl_hkDebugDisplayProcess = 0x10D7ED0,
	kVtbl_hkpPhysicsContextWorldListener = 0x10D7F04,
	kVtbl_hkpWorldViewerBase = 0x10D7F44,
	kVtbl_hkStreamStatisticsCollector = 0x10D8040,
	kVtbl_hkpShapeDisplayBuilder = 0x10D8094,
	kVtbl_hkpUserShapeDisplayBuilder = 0x10D80A4,
	kVtbl_hkDisplayAABB = 0x10D80D0,
	kVtbl_hkDisplayConvex = 0x10D80E8,
	kVtbl_hkDisplayBox = 0x10D8100,
	kVtbl_hkpContactPointViewer = 0x10D8184,
	kVtbl_hkpConvexRadiusBuilder = 0x10D8214,
	kVtbl_hkpUserConvexRadiusBuilder = 0x10D8224,
	kVtbl_hkDisplaySemiCircle = 0x10D8274,
	kVtbl_hkDisplayPlane = 0x10D828C,
	kVtbl_hkDisplayCone = 0x10D82A4,
	kVtbl_hkpPointToPathConstraintData = 0x10DA004,
	kVtbl_hkpPulleyConstraintData = 0x10DA04C,
	kVtbl_hkpPairCollisionFilter = 0x10DA0C8,
	kVtbl_hkCpuWorldGetClosestPointsCollector = 0x10DB94C,
	kVtbl_hkCpuWorldLinearCastCollector = 0x10DB9E4,
	kVtbl_hkCpuWorldRayCastCollector = 0x10DBAF8,
	kVtbl_hkpFixedBufferRayHitCollector = 0x10DBB04,
	kVtbl_hkaAnimation = 0x10DDB3C,
	kVtbl_hkaWaveletCompressedAnimation = 0x10DDC5C,
	kVtbl_hkaSplineCompressedAnimation = 0x10DE0EC,
	kVtbl_hkaDeltaCompressedAnimation = 0x10DE90C,
	kVtbl_hkpRejectChassisListener = 0x10DEBF4,
	kVtbl_hkpVehicleWheelCollide = 0x10DEC04,
	kVtbl_hkpVehicleLinearCastWheelCollide = 0x10DEC3C,
	kVtbl_hkpVehicleInstance = 0x10DF34C,
	kVtbl_hkpVehicleDefaultSuspension = 0x10DF89C,
	kVtbl_hkpVehicleDefaultBrake = 0x10DF9F4,
	kVtbl_hkpVehicleData = 0x10DFF44,
	kVtbl_hkpTyremarksWheel = 0x10E00CC,
	kVtbl_hkpTyremarksInfo = 0x10E00DC,
	kVtbl_hkpSerializedDisplayRbTransforms = 0x10E04AC,
	kVtbl_hkpPoweredChainMapper = 0x10E0654,
	kVtbl_hkpRotationalConstraintData = 0x10E11EC,
	kVtbl_hkpSimpleMeshShape = 0x10E2144,
	kVtbl_hkpMultiRayShape = 0x10E222C,
	kVtbl_hkxAttributeHolder = 0x10E310C,
	kVtbl_hkxNode = 0x10E311C,
	kVtbl_hkxMaterial = 0x10E33DC,
	kVtbl_hkxSparselyAnimatedInt = 0x10E350C,
	kVtbl_hkxSparselyAnimatedEnum = 0x10E351C,
	kVtbl_hkxEnum = 0x10E352C,
	kVtbl_hkMonitorStreamColorTable = 0x10E3E5C,
	kVtbl_hkaInterleavedUncompressedAnimation = 0x10E5474,
	kVtbl_hkaFootstepAnalysisInfoContainer = 0x10E56D4,
	kVtbl_hkaDefaultAnimatedReferenceFrame = 0x10E57A4,
	kVtbl_hkaBoneAttachment = 0x10E587C,
	kVtbl_hkaAnimationPreviewColorContainer = 0x10E58C8,
	kVtbl_hkaAnimationContainer = 0x10E59AC,
	kVtbl_hkaAnimationBinding = 0x10E5A58,
	kVtbl_hkpVehicleRayCastWheelCollide = 0x10E5AE4,
	kVtbl_hkpVehicleManager = 0x10E5B4C,
	kVtbl_hkpVehicleRayCastBatchingManager = 0x10E5B68,
	kVtbl_hkpVehicleLinearCastBatchingManager = 0x10E5BFC,
	kVtbl_hkpVehicleDriverInputAnalogStatus = 0x10E5D94,
	kVtbl_hkpVehicleDefaultAnalogDriverInput = 0x10E5DA8,
	kVtbl_hkpVehicleDefaultVelocityDamper = 0x10E5E9C,
	kVtbl_hkpVehicleDefaultTransmission = 0x10E5FF4,
	kVtbl_hkpVehicleDefaultSteering = 0x10E60C4,
	kVtbl_hkpVehicleDefaultEngine = 0x10E62A4,
	kVtbl_hkpVehicleDefaultAerodynamics = 0x10E6394,
	kVtbl_hkpSerializedDisplayMarkerList = 0x10E66FC,
	kVtbl_hkpSerializedDisplayMarker = 0x10E676C,
	kVtbl_hkpReorientAction = 0x10E6834,
	kVtbl_hkpGroupCollisionFilter = 0x10E6DEC,
	kVtbl_hkpDisplayBindingData = 0x10E75EC,
	kVtbl_hkpDisableEntityCollisionFilter = 0x10E7700,
	kVtbl_hkpConstrainedSystemFilter = 0x10E7874,
	kVtbl_hkpConvexPieceStreamData = 0x10E7C24,
	kVtbl_hkpLinearParametricCurve = 0x10E80B4,
	kVtbl_hkpDefaultWorldMemoryWatchDog = 0x10E81A4,
	kVtbl_hkpCallbackConstraintMotor = 0x10E83B4,
	kVtbl_hkpShapeInfo = 0x10E8824,
	kVtbl_hkpMoppModifier = 0x10E8894,
	kVtbl_hkpRemoveTerminalsMoppModifier = 0x10E88B4,
	kVtbl_hkpGroupFilter = 0x10E8A6C,
	kVtbl_hkpFastMeshShape = 0x10E8AB0,
	kVtbl_hkpConvexVerticesConnectivity = 0x10E8D8C,
	kVtbl_hkpConvexPieceMeshShape = 0x10E8E94,
	kVtbl_hkpCompressedSampledHeightFieldShape = 0x10E901C,
	kVtbl_hkpCollisionFilterList = 0x10E90E8,
	kVtbl_hkMemoryMeshShape = 0x10E929C,
	kVtbl_hkxVertexVectorDataChannel = 0x10E9300,
	kVtbl_hkxVertexSelectionChannel = 0x10E9358,
	kVtbl_hkxVertexIntDataChannel = 0x10E93AC,
	kVtbl_hkxVertexFloatDataChannel = 0x10E943C,
	kVtbl_hkxTriangleSelectionChannel = 0x10E9494,
	kVtbl_hkxTextureInplace = 0x10E9544,
	kVtbl_hkxTextureFile = 0x10E95B4,
	kVtbl_hkxSparselyAnimatedString = 0x10E9614,
	kVtbl_hkxSparselyAnimatedBool = 0x10E96C8,
	kVtbl_hkxSkinBinding = 0x10E977C,
	kVtbl_hkxScene = 0x10E99D8,
	kVtbl_hkxNodeSelectionSet = 0x10E9A34,
	kVtbl_hkxMeshSection = 0x10E9B7C,
	kVtbl_hkxMaterialShader = 0x10E9CCC,
	kVtbl_hkxMaterialEffect = 0x10E9DEC,
	kVtbl_hkxLight = 0x10E9E74,
	kVtbl_hkxIndexBuffer = 0x10E9F48,
	kVtbl_hkxEdgeSelectionChannel = 0x10E9FA4,
	kVtbl_hkxCamera = 0x10EA0A4,
	kVtbl_hkxAnimatedVector = 0x10EA10C,
	kVtbl_hkxAnimatedQuaternion = 0x10EA154,
	kVtbl_hkxAnimatedMatrix = 0x10EA188,
	kVtbl_hkxAnimatedFloat = 0x10EA1AC,
	kVtbl_hkPlatformObjectWriter = 0x10EA370,
	kVtbl_hkOffsetOnlyStreamWriter = 0x10EA388,
	kVtbl_hkObjectCopier = 0x10EA3B0,
	kVtbl_hkObjectResource = 0x10EA4DC,
	kVtbl_hkPackfileData = 0x10EA51C,
	kVtbl_hkMemoryStreamReader = 0x10EA540,
	kVtbl_hkpMoppCodeGenerator = 0x10EA5B4,
	kVtbl_hkpMoppDefaultAssembler = 0x10EA5DC,
	kVtbl_hkpMoppDefaultSplitter = 0x10EA610,
	kVtbl_hkDisplaySphere = 0x10EA630,
	kVtbl_IConvexOverlapImpl = 0x10EADEC,
	kVtbl_hkGskShape = 0x10EADFC,
	kVtbl_hkgpMesh = 0x10EB000,
	kVtbl_hkResourceMap = 0x10EB19C,
	kVtbl_hkMemoryResourceHandle = 0x10EB288,
	kVtbl_hkMemoryResourceContainer = 0x10EB2C4,
	kVtbl_hkContainerResourceMap = 0x10EB308,
	kVtbl_hkaMeshBinding = 0x10EB770,
	kVtbl_hkpStiffSpringChainData = 0x10EB98C,
	kVtbl_hkpPoweredChainData = 0x10EB9D4,
	kVtbl_hkpCompressedMeshShape = 0x10EBA5C,
	kVtbl_hkxVertexBuffer = 0x10EBA94,
	kVtbl_hkxEnvironment = 0x10EBAB8,
	kVtbl_hkaFootstepAnalysisInfo = 0x10EBD64,
	kVtbl_hkpGunProjectile = 0x10EBF94,
	kVtbl_hkpProjectileGun = 0x10EBFB0,
	kVtbl_hkpMountedBallGun = 0x10EC004,
	kVtbl_hkpGravityGun = 0x10EC090,
	kVtbl_hkpFirstPersonGun = 0x10EC0E4,
	kVtbl_hkpBallGun = 0x10EC174,
	kVtbl_hkpRemoveTerminalsMoppModifier2 = 0x10EC1A4,
	kVtbl_hkxMesh = 0x10EC1DC,
	kVtbl_hkxMaterialShaderSet = 0x10EC1EC,
	kVtbl_hkAlignSceneToNodeOptions = 0x10EC1FC,
	kVtbl_hkKdTreeCpuBroadphaseBundleCastCollector = 0x10EC614,
	kVtbl_hkpConvexPieceShape = 0x10ECE2C,
	kVtbl_NiDX9SourceTextureData = 0x10ED37C,
	kVtbl_NiDX9Renderer = 0x10EE4BC,
	kVtbl_NiDX9ShaderDeclaration = 0x10EE70C,
	kVtbl_NiD3DShaderDeclaration = 0x10EE7CC,
	kVtbl_NiD3DDefaultShader = 0x10EECAC,
	kVtbl_NiD3DShader = 0x10EEDA4,
	kVtbl_NiDX92DBufferData = 0x10EEED4,
	kVtbl_NiDX9TextureBufferData = 0x10EEFBC,
	kVtbl_NiDX9ImplicitBufferData = 0x10EF06C,
	kVtbl_NiDX9ImplicitDepthStencilBufferData = 0x10EF114,
	kVtbl_NiDX9AdditionalDepthStencilBufferData = 0x10EF184,
	kVtbl_NiD3DPass = 0x10EF364,
	kVtbl_NiD3DShaderInterface = 0x10EF39C,
	kVtbl_NiShaderConstantMapEntry = 0x10EF4D8,
	kVtbl_NiD3DShaderConstantMap = 0x10EF544,
	kVtbl_NiD3DRenderState = 0x10EF60C,
	kVtbl_NiD3DGeometryGroupManager = 0x10EF718,
	kVtbl_NiD3DShaderProgram = 0x10EF73C,
	kVtbl_NiD3DPixelShader = 0x10EF7D4,
	kVtbl_NiD3DVertexShader = 0x10EF87C,
	kVtbl_NiDX9TextureData = 0x10EFB7C,
	kVtbl_NiDX9SourceCubeMapData = 0x10EFC34,
	kVtbl_NiDX9VertexBufferManager = 0x10EFE94,
	kVtbl_NiFragmentShaderInstanceDescriptor = 0x10EFEFC,
	kVtbl_NiDX9FragmentShader = 0x10EFF44,
	kVtbl_NiD3DGPUProgramCache = 0x10F0094,
	kVtbl_NiGeometryBufferData = 0x10F017C,
	kVtbl_NiDX9IndexBufferManager = 0x10F02F0,
	kVtbl_NiDX9RenderedTextureData = 0x10F02FC,
	kVtbl_NiDX9RenderedCubeMapData = 0x10F049C,
	kVtbl_NiDX9DynamicTextureData = 0x10F05EC,
	kVtbl_NiDX9ErrorShader = 0x10F0764,
	kVtbl_NiDX9TextureManager = 0x10F086C,
	kVtbl_NiDX9RenderState = 0x10F088C,
	kVtbl_NiDX9PersistentSrcTextureRendererData = 0x10F099C,
	kVtbl_NiD3DShaderProgramCreator = 0x10F0A68,
	kVtbl_NiD3DShaderProgramCreatorHLSL = 0x10F0A90,
	kVtbl_NiD3DShaderProgramCreatorAsm = 0x10F0AC0,
	kVtbl_NiD3DShaderProgramCreatorObj = 0x10F0AF4,
	kVtbl_NiD3DShaderFactory = 0x10F0CC4,
	kVtbl_NiD3DShaderProgramFactory = 0x10F0F70,
	kVtbl_NiStaticGeometryGroup = 0x10F0FD4,
	kVtbl_NiUnsharedGeometryGroup = 0x10F1008,
	kVtbl_NiDynamicGeometryGroup = 0x10F10C4,
	kVtbl_NiD3DHLSLPixelShader = 0x10F10F4,
	kVtbl_NiD3DHLSLVertexShader = 0x10F119C,
	kVtbl_NiDX9ShaderConstantManager = 0x10F1550,
	kVtbl_NiGeometryGroup = 0x10F1644,
	kVtbl_NiD3DShaderConstantManager = 0x10F16CC,
	kVtbl_NiBoundingVolume = 0x10F16F4,
	kVtbl_NiHalfSpaceBV = 0x10F1728,
	kVtbl_NiUnionBV = 0x10F1778,
	kVtbl_NiCapsuleBV = 0x10F17D0,
	kVtbl_NiBoxBV = 0x10F1814,
	kVtbl_NiSphereBV = 0x10F1854,
	kVtbl_NiCollisionData = 0x10F18BC,
	kVtbl_NiIntersector = 0x10F1A84,
	kVtbl_NiCapsuleSphereIntersector = 0x10F1AA0,
	kVtbl_NiCapsuleCapsuleIntersector = 0x10F1ABC,
	kVtbl_NiCapsuleTriIntersector = 0x10F1AD8,
	kVtbl_NiBoxCapsuleIntersector = 0x10F1AF4,
	kVtbl_NiBoxSphereIntersector = 0x10F1B10,
	kVtbl_NiSphereTriIntersector = 0x10F1B2C,
	kVtbl_NiOBBRoot = 0x10F1B44,
	kVtbl_NiOBBNode = 0x10F1B58,
	kVtbl_NiOBBLeaf = 0x10F1B70,
	kVtbl_MoviePlayer = 0x10F1C44,
	kVtbl_NiRenderedCubeMap = 0x110102C,
	kVtbl_NiRenderTargetGroup = 0x11010EC,
	kVtbl_NiShaderDeclaration = 0x11011EC,
	kVtbl_NiSCMExtraData = 0x110129C,
	kVtbl_NiGPUProgramCache = 0x11013B4,
	kVtbl_NiMaterialResource = 0x1101464,
	kVtbl_StartMenuOption = 0x1076EE0,
	kVtbl_StartMenuUserOption = 0x107704C,

};


// Finds an ExtraDataList in an ExtendDataList
class ExtraDataListInExtendDataListMatcher {
	ExtraDataList* m_toMatch;
public:
	ExtraDataListInExtendDataListMatcher(ExtraDataList* match) : m_toMatch(match) { }

	bool Accept(ExtraDataList* match)
	{
		return (m_toMatch == match);
	}
};

// Finds an ExtraDataList in an ExtendDataList embedded in one of the EntryData from an EntryDataList
class ExtraDataListInEntryDataListMatcher {
	ExtraDataList* m_toMatch;
public:
	ExtraDataListInEntryDataListMatcher(ExtraDataList* match) : m_toMatch(match) { }

	bool Accept(ExtraContainerChanges::EntryData* match)
	{
		if (match && match->extendData)
			return match->extendData->GetIndexOf(ExtraDataListInExtendDataListMatcher(m_toMatch)) >= 0;
		else
			return false;
	}
};

// Finds an ExtendDataList in an EntryDataList
class ExtendDataListInEntryDataListMatcher {
	ExtraContainerChanges::ExtendDataList* m_toMatch;
public:
	ExtendDataListInEntryDataListMatcher(ExtraContainerChanges::ExtendDataList* match) : m_toMatch(match) { }

	bool Accept(ExtraContainerChanges::EntryData* match)
	{
		if (match && match->extendData)
			return (match->extendData == m_toMatch);
		else
			return false;
	}
};

// Finds an EntryData in an EntryDataList
class EntryDataInEntryDataListMatcher {
	ExtraContainerChanges::EntryData* m_toMatch;
public:
	EntryDataInEntryDataListMatcher(ExtraContainerChanges::EntryData* match) : m_toMatch(match) { }

	bool Accept(ExtraContainerChanges::EntryData* match)
	{
		return (m_toMatch == match);
	}
};

// Finds an Item (type) in an EntryDataList
class ItemInEntryDataListMatcher {
	TESForm* m_toMatch;
public:
	ItemInEntryDataListMatcher(TESForm* match) : m_toMatch(match) { }

	bool Accept(ExtraContainerChanges::EntryData* match)
	{
		return (match && m_toMatch == match->type);
	}
};

// Finds an Item from its base form in an EntryDataList
class BaseInEntryDataLastMatcher {
	TESForm* m_toMatch;
public:
	BaseInEntryDataLastMatcher(TESForm* match) : m_toMatch(match) { }

	bool Accept(ExtraContainerChanges::EntryData* match)
	{
		return (match && match->type && m_toMatch == match->type->TryGetREFRParent());
	}
};

// Finds an item by refID in an EntryDataList
class RefIDInEntryDataListMatcher {
	UInt32 m_toMatch;
public:
	RefIDInEntryDataListMatcher(UInt32 match) : m_toMatch(match) { }

	bool Accept(ExtraContainerChanges::EntryData* match)
	{
		return (match && match->type && m_toMatch == match->type->refID);
	}
};

// Finds an item by the refID of its base form in an EntryDataList
class BaseIDInEntryDataListMatcher {
	UInt32 m_toMatch;
public:
	BaseIDInEntryDataListMatcher(UInt32 match) : m_toMatch(match) { }

	bool Accept(ExtraContainerChanges::EntryData* match)
	{
		return (match && match->type && match->type->TryGetREFRParent() && m_toMatch == match->type->TryGetREFRParent()->refID);
	}
};


extern ExtraContainerChanges::ExtendDataList* ExtraContainerChangesExtendDataListCreate(ExtraDataList* pExtraDataList = NULL);
extern void ExtraContainerChangesExtendDataListFree(ExtraContainerChanges::ExtendDataList* xData, bool bFreeList = false);
extern bool ExtraContainerChangesExtendDataListAdd(ExtraContainerChanges::ExtendDataList* xData, ExtraDataList* xList);
extern bool ExtraContainerChangesExtendDataListRemove(ExtraContainerChanges::ExtendDataList* xData, ExtraDataList* xList, bool bFreeList = false);

extern void ExtraContainerChangesEntryDataFree(ExtraContainerChanges::EntryData* xData, bool bFreeList = false);

extern ExtraContainerChanges::EntryDataList* ExtraContainerChangesEntryDataListCreate(UInt32 refID = 0, UInt32 count = 1, ExtraContainerChanges::ExtendDataList* pExtendDataList = NULL);
extern void ExtraContainerChangesEntryDataListFree(ExtraContainerChanges::EntryDataList* xData, bool bFreeList = false);

extern void ExtraContainerChangesFree(ExtraContainerChanges* xData, bool bFreeList = false);

extern char* GetExtraDataValue(BSExtraData* traverse);
extern const char* GetExtraDataName(UInt8 ExtraDataType);

SInt32 GetCountForExtraDataList(ExtraDataList* list);

struct InventoryItemData {
	SInt32								count;
	ExtraContainerChanges::EntryData* entry;

	InventoryItemData(SInt32 _count, ExtraContainerChanges::EntryData* _entry) : count(_count), entry(_entry) {}
};

typedef UnorderedMap<TESForm*, InventoryItemData> InventoryItemsMap;