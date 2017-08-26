/*=================================================================
	File created by Yohann NICOLAS.
	Add support 1.13d by L'Autour.

    @file D2wrapper.cpp
    @brief Main Diablo II extra DLL handler.

    This is the sources of the D2DLL class.

=================================================================*/

#include "globalVariable.h"		// Install_VariableOnRealm()
#include "commands.h"			// Install_Commands()
#include "othersFeatures.h"		// Install_ChangeResolution()
#include "mainScreen.h"			// Install_PrintPlugYVersion() Install_VersionChange()
#include "savePath.h"			// Install_ChangingSavePath()
#include "bigStash.h"			// Install_BigStash()
#include "skillPerLevelUp.h"	// Install_SkillPerLevelUp()
#include "statPerLevelUp.h"		// Install_StatPerLevelUp()
#include "statsPoints.h"		// Install_StatsPoints() Install_StatsLimitShiftClick()
#include "infinityStash.h"		// Install_MultiPageStash()
#include "newInterfaces.h"		// Install_NewInterfaces()
#include "extraOptions.h"		// Install_AlwaysRegenMapInSP()
#include "language.h"			// Install_LanguageManagement()
#include "windowed.h"			// installed with Install_PrintPlugYVersion()
#include "customLibraries.h"
#include "common.h"

using Versions = VersionUtility::Versions;

// Required Files
int version_Game = Versions::UNKNOWN;
int version_D2Client = Versions::UNKNOWN;
int version_D2CMP = Versions::UNKNOWN;
int version_D2Common = Versions::UNKNOWN;
int version_D2Game = Versions::UNKNOWN;
int version_D2gfx = Versions::UNKNOWN;
int version_D2Lang = Versions::UNKNOWN;
int version_D2Launch = Versions::UNKNOWN;
int version_D2Net = Versions::UNKNOWN;
int version_D2Win = Versions::UNKNOWN;
int version_Fog = Versions::UNKNOWN;
int version_Storm = Versions::UNKNOWN;

DWORD offset_Game = NULL;
DWORD offset_D2Client = NULL;
DWORD offset_D2CMP = NULL;
DWORD offset_D2Common = NULL;
DWORD offset_D2Game = NULL;
DWORD offset_D2gfx = NULL;
DWORD offset_D2Lang = NULL;
DWORD offset_D2Launch = NULL;
DWORD offset_D2Net = NULL;
DWORD offset_D2Win = NULL;
DWORD offset_Fog = NULL;
DWORD offset_Storm = NULL;

const char* S_Game = "Game.exe";
const char* S_D2Client = "D2Client.dll";
const char* S_D2CMP = "D2CMP.dll";
const char* S_D2Common = "D2Common.dll";
const char* S_D2Game = "D2Game.dll";
const char* S_D2gfx = "D2gfx.dll";
const char* S_D2Lang = "D2Lang.dll";
const char* S_D2Launch = "D2Launch.dll";
const char* S_D2Net = "D2Net.dll";
const char* S_D2Win = "D2Win.dll";
const char* S_Fog = "Fog.dll";
const char* S_Storm = "Storm.dll";

// Change the protection scheme of a loaded
// DLL called libraryName in memory space at address addr+size to allow us to customize it.
void hookLibrary(const char* libraryName, DWORD addr)
{
	DWORD dw=0;
	BYTE* offsetPESignature = addr + *(BYTE**)((BYTE*)addr + 0x3C);
	DWORD sizeOfCode = *(DWORD*)(offsetPESignature + 0x1C);
	BYTE* baseOfCode = addr + *(BYTE**)(offsetPESignature + 0x2C);
	if( !VirtualProtect(baseOfCode, sizeOfCode, PAGE_EXECUTE_READWRITE, &dw) )
	{
		log_msg("Failed to hook library : %s. (%08X,%08X)\n", libraryName ,baseOfCode, sizeOfCode);
		exit(-1);
	}
	log_msg("%s successfully hooked. (%08X,%08X)\n", libraryName ,baseOfCode, sizeOfCode);
}

void unhookLibrary(const char* libraryName, DWORD addr)
{
	DWORD dw=0;
	BYTE* offsetPESignature = addr + *(BYTE**)((BYTE*)addr + 0x3C);
	DWORD sizeOfCode = *(DWORD*)(offsetPESignature + 0x1C);
	BYTE* baseOfCode = addr + *(BYTE**)(offsetPESignature + 0x2C);
	if( !VirtualProtect(baseOfCode, sizeOfCode, PAGE_EXECUTE_READ, &dw) )
		log_msg("Failed to unhook library : %s. (%08X,%08X)\n", libraryName ,baseOfCode, sizeOfCode);
	else
		log_msg("%s successfully unhooked. (%08X,%08X)\n", libraryName ,baseOfCode, sizeOfCode);
}

void freeLibrary( DWORD library )
{
	if (library && library != offset_Game)
		FreeLibrary((HMODULE)library);
}

void freeD2Libraries()
{
	if (version_Game >= Versions::V114a)
		return;

	log_msg("***** Free Libraries *****\n");

	freeLibrary( offset_D2Client );
	freeLibrary( offset_D2CMP );
	freeLibrary( offset_D2Common );
	freeLibrary( offset_D2Game );
	freeLibrary( offset_D2gfx );
	freeLibrary( offset_D2Lang );
	freeLibrary( offset_D2Launch );
	freeLibrary( offset_D2Net );
	freeLibrary( offset_D2Win );
	freeLibrary( offset_Fog );
	freeLibrary( offset_Storm );

	log_msg("\n\n");
}

void hookLibraries()
{
	log_msg("***** Unprotect Libraries *****\n");

	hookLibrary(S_D2Client,	offset_D2Client);
	hookLibrary(S_D2Common,	offset_D2Common);
	hookLibrary(S_D2Game,	offset_D2Game);
	hookLibrary(S_D2gfx,	offset_D2gfx);
	hookLibrary(S_D2Lang,	offset_D2Lang);
	hookLibrary(S_D2Launch,	offset_D2Launch);
	hookLibrary(S_Fog,		offset_Fog);
	hookLibrary(S_Storm,	offset_Storm);

	log_msg("\n\n");
}

void unhookLibraries()
{
	log_msg("***** Reprotect Libraries *****\n");

	unhookLibrary(S_D2Client,	offset_D2Client);
	unhookLibrary(S_D2Common,	offset_D2Common);
	unhookLibrary(S_D2Game,		offset_D2Game);
	unhookLibrary(S_D2gfx,		offset_D2gfx);
	unhookLibrary(S_D2Lang,		offset_D2Lang);
	unhookLibrary(S_D2Launch,	offset_D2Launch);
	unhookLibrary(S_Fog,		offset_Fog);
	unhookLibrary(S_Storm,		offset_Storm);

	log_msg("\n\n");
}

void freeCustomLibraries()
{
	if (!customDlls)
		return;

	log_msg("***** Free custom libraries *****\n");

	TCustomDll* dll=customDlls;
	TCustomDll* nextDll;
	while (dll)
	{
		dll->release();
		freeLibrary(dll->offset);
		nextDll = dll->nextDll;
		D2FogMemDeAlloc(dll,__FILE__,__LINE__,0);
		dll = nextDll;
	}
}

void initCustomLibraries()
{
	log_msg("***** Init custom libraries *****\n");

	TCustomDll* dll=customDlls;
	while (dll)
	{
		dll->init();
		dll = dll->nextDll;
	}
}

void loadCustomLibraries()
{
	char* curString = NULL;
	TCustomDll* nextDll;
	DWORD offset_currentDll;

	log_msg("***** Custom libraries *****\n");

	if (dllFilenames)
		curString = strtok(dllFilenames,"|");

	if (!curString)
		log_msg("No custom libraries to load.\n");
	else
	{
		log_msg("Load custom libraries :\n");
		while (curString)
		{
			if (curString[0])
			{
				offset_currentDll = (DWORD)LoadLibrary(curString);
				if (!offset_currentDll)
				{
					log_msg("Load library %s failed:\n", curString);
					exit(0);
				}
				nextDll = customDlls;
				customDlls = new(TCustomDll);
				customDlls->nextDll = nextDll;
				customDlls->initialize(offset_currentDll);
			}
			curString=strtok(NULL,"|");
		}
	}
	if(dllFilenames)
		D2FogMemDeAlloc(dllFilenames,__FILE__,__LINE__,0);

	log_msg("\n\n");
}

void loadLibrary(LPCSTR libName, int* libVersion, DWORD* libOffset, int shift, DWORD v109b, DWORD v109d, DWORD v110, DWORD v111, DWORD v111b, DWORD v112, DWORD v113c)
{
	*libOffset = (DWORD)LoadLibrary(libName);
	if (*libOffset == NULL)
	{
		log_msg("Failed to load library : %s\n", libName);
		exit(-1);
	}
	log_msg("%s loaded at:\t%08X (", libName, *libOffset);

	DWORD addr = *(DWORD*)(*libOffset + shift);
	if (version_Game != Versions::UNKNOWN && (version_Game <= Versions::V108 || version_Game >= Versions::V113d))
		*libVersion = version_Game;
	else if (addr==v109b)
		*libVersion = Versions::V109b;
	else if (addr==v109d)
		*libVersion = Versions::V109d;
	else if (addr==v110)
		*libVersion = Versions::V110;
	else if (addr==v111)
		*libVersion = Versions::V111;
	else if (addr==v111b)
		*libVersion = Versions::V111b;
	else if (addr==v112)
		*libVersion = Versions::V112;
	else if (addr==v113c)
		*libVersion = Versions::V113c;
	else {
		*libVersion = version_Game != Versions::UNKNOWN ? version_Game : Versions::V113d;
		log_msg("unknown, try with ");
	}
	log_msg("%s)\n", VersionUtility::GetVersionAsString(*libVersion));
}

#define GET_VERSION(F,S,A,B,C,D,E,G,H) loadLibrary(S_##F, &version_##F, &offset_##F, 0x##S, 0x##A, 0x##B, 0x##C, 0x##D, 0x##E, 0x##G, 0x##H)
void initD2modules()
{
	log_msg("***** Get D2 Modules address and version *****\n");
	offset_Game = (DWORD)GetModuleHandle(NULL);
	version_Game = VersionUtility::GetVersion((HMODULE)offset_Game);
	log_msg("Game.exe loaded at:\t%08X (%s)\n", offset_Game, VersionUtility::GetVersionAsString(version_Game));

	if (version_Game >= Versions::V114a)
	{ 
		offset_D2Client		= offset_Game;	version_D2Client	= version_Game;
		offset_D2CMP		= offset_Game;	version_D2CMP		= version_Game;
		offset_D2Common		= offset_Game;	version_D2Common	= version_Game;
		offset_D2Game		= offset_Game;	version_D2Game		= version_Game;
		offset_D2gfx		= offset_Game;	version_D2gfx		= version_Game;
		offset_D2Lang		= offset_Game;	version_D2Lang		= version_Game;
		offset_D2Launch		= offset_Game;	version_D2Launch	= version_Game;
		offset_D2Net		= offset_Game;	version_D2Net		= version_Game;
		offset_D2Win		= offset_Game;	version_D2Win		= version_Game;
		offset_Fog			= offset_Game;	version_Fog			= version_Game;
		offset_Storm		= offset_Game;	version_Storm		= version_Game;
	}
	else
	{
		GET_VERSION(D2Client,	17F,	00000000, 14500000, 12500000, 0D814800, 0D812800, 0DA01000, 0DA03000);	//0xCC000	0x6FAA0000					0xCA000
		GET_VERSION(D2CMP,		1359,	3C686FE0, 38686FE0, 8BF78B56, 4C880424, 07C71824, CCCCCCCC, C7000005);	//0x18000	0x6FDF0000 Already Loaded	0x19000
		GET_VERSION(D2Common,	10CA,	A1E86FDC, B1E86FDC, 72D03B42, F883057E, 16746AC6, 00FE81C3, 74FE85DB);	//0x8D000	0x037A0000					0x7C000	
		GET_VERSION(D2Game,		1092,	18968BF1, 38968BF1, 28968BF1, F6335608, C690C5B9, 895FD713, 56535700);	//0xF6000	0x6FC30000					0xCF000
		GET_VERSION(D2gfx,		10D,	EB000000, 006FA700, 00000010, 2A000401, 19000401, 0B210E00, 00000000);	//0xB000	0x6FA70000 Already Loaded	-
		GET_VERSION(D2Lang,		126D,	FC45048B, F445048B, 02C18313, C4830000, 00C6E045, 8B48408B, 0C75FF0C);	//0x0A000	0x6FC10000 Already Loaded	-
		GET_VERSION(D2Launch,	109A,	81E8526F, 01E8526F, 85E8526F, 247C8B00, 00FC6583, 15FF0424, E850E045);	//0x20000	0x6FA10000 Already Loaded	0x1E000			?
		GET_VERSION(D2Net,		16E1,	78B8A73C, 68B8A73C, 10244C8B, 5349E808, 5EA9E808, 105D8B72, 53B9E808);	//0x6000	0x6FC00000 Already Loaded	-	
		GET_VERSION(D2Win,		1699,	88686F8C, 84686F8C, D094686F, F0030000, 001435E8, 8B088F44, 0013F5E8);	//0x19000	0x6F8A0000 Already Loaded	0x1C000
		GET_VERSION(Fog,		102,	D0000006, 10000001, 00000006, 000042E6, 00004302, 0000483C, 00004B95);	//0x20000	0x6FF50000 Already Loaded	0x1F000
		GET_VERSION(Storm,		1190,	19E85082, 59E85082, 13C103F6, 0474F685, 8B000321, 3B1074C9, 0D896404);	//0x30000	0x6FFB0000 Already Loaded	-

		if (version_Game == Versions::UNKNOWN)
			 version_Game = version_D2gfx;
	}

	log_msg("\n\n");
}
//////////////////////////////////// EXPORTS FUNCTIONS ////////////////////////////////////


extern "C" __declspec(dllexport) bool __stdcall Release()
{
	log_msg("\n***** ENDING DIABLO II *****\n\n" );

	freeCustomLibraries();
	freeD2Libraries();
	return true;
}

extern "C" __declspec(dllexport) void* __stdcall Init(LPSTR IniName)
{
	if (IniName) log_msg("* PlugY is called from D2mod.dll\n\n");

	static int isInstalled = false;
	if (isInstalled) return NULL;
	isInstalled=true;

	initD2modules();

	if (version_Game < Versions::V109 || version_Game > Versions::V113d)
	{
		log_box("PlugY isn't compatible with this version : %s", VersionUtility::GetVersionAsString(version_Game));
		Release();
		exit(0);
	}

	initD2functions();

	loadParameters();

	if (!active_plugin)	return NULL;

	loadCustomLibraries();

	hookLibraries();

	log_msg("***** INSTALL FUNCTIONS *****\n");

	Install_VariableOnRealm();

	if (active_Commands)
		Install_Commands();

	if (active_ChangeLanguage || active_LanguageManagement)
		Install_LanguageManagement();

	if (active_VersionTextChange)
		Install_VersionChange();

	if (active_PrintPlugYVersion || active_Windowed)
		Install_PrintPlugYVersion();

	if (active_DisplayBaseStatsValue)
		Install_DisplayBaseStatsValue();

	if (active_changingSavePath)
		Install_ChangingSavePath();

	if (active_StatsShiftClickLimit)
		Install_StatsLimitShiftClick();

	if (active_RunLODs)
		Install_RunLODs();

	if (active_bigStash)
		Install_BigStash();

	if (active_SkillPerLevelUpChange)
		Install_SkillPerLevelUp();

	if (active_StatPerLevelUpChange)
		Install_StatPerLevelUp();

	if (active_multiPageStash)
		Install_MultiPageStash();

	if (active_othersFeatures)
		Install_OthersFeatures();

	if (active_newInterfaces)
		Install_NewInterfaces();

	if (nbPlayersCommandByDefault)
		Install_SendPlayersCommand();

	if (active_DisplayItemLevel)
		Install_DisplayItemLevel();

	if (active_AlwaysDisplayLifeMana)
		Install_AlwaysDisplayLifeMana();

	if (active_EnabledTXTFilesWithMSExcel)
		Install_EnabledTXTFilesWithMSExcel();

	if (active_LadderRunewords)
		Install_LadderRunewords();

	log_msg("\nDLL patched sucessfully.\n\n\n");

	unhookLibraries();

	initCustomLibraries();

	loadLocalizedStrings(D2GetLang());

	log_msg("***** ENTERING DIABLO II *****\n\n" );

	active_logFile = active_logFile - 1;

	return NULL;
}

/*================================= END OF FILE =================================*/