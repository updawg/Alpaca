/*=================================================================
	File created by Yohann NICOLAS.
	Add support 1.13d by L'Autour.

    @file D2wrapper.cpp
    @brief Main Diablo II extra DLL handler.

    This is the sources of the D2DLL class.

=================================================================*/

#include "globalVariable.h"		// Install_VariableOnRealm()
#include "commands.h"			// Install_Commands()
#include "mainScreen.h"			// Install_PrintPlugYVersion() Install_VersionChange()
#include "savePath.h"			// Install_ChangingSavePath()
#include "bigStash.h"			// Install_BigStash()
#include "statsPoints.h"		// Install_StatsPoints() Install_StatsLimitShiftClick()
#include "infinityStash.h"		// Install_MultiPageStash()
#include "newInterfaces.h"		// Install_NewInterfaces()
#include "extraOptions.h"		// Install_AlwaysRegenMapInSP()
#include "language.h"			// Install_LanguageManagement()
#include "windowed.h"			// installed with Install_PrintPlugYVersion()
#include "customLibraries.h"
#include "common.h"

// New library loading stuff
#include "Utilities/LibraryUtility.h"

using Versions = VersionUtility::Versions;

// Required Files
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

// Make this global so people can use it.
LibraryUtility* lu;

void freeLibrary( DWORD library )
{
	if (library && library != offset_Game)
		FreeLibrary((HMODULE)library);
}

void freeD2Libraries()
{
	if (lu->Game_Version >= Versions::V114a)
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

void initD2modules()
{
	// I'm just leaving this values because I don't want to spend time at the moment repointing and
	// testing all of the existing code that re-uses these externs. So for now, just give them the data
	// that they want but use the LibraryUtility as the backend database.
	offset_Game = lu->Game_Offset;

	if (VersionUtility::IsEqualOrGreaterThan114(lu->Game_Version))
	{
		// It's all in Game.exe so the offset is the same.
		offset_D2Client = lu->Game_Offset;
		offset_D2CMP = lu->Game_Offset;
		offset_D2Common = lu->Game_Offset;;
		offset_D2Game = lu->Game_Offset;
		offset_D2gfx = lu->Game_Offset;
		offset_D2Lang = lu->Game_Offset;
		offset_D2Launch = lu->Game_Offset;
		offset_D2Net = lu->Game_Offset;
		offset_D2Win = lu->Game_Offset;
		offset_Fog = lu->Game_Offset;
		offset_Storm = lu->Game_Offset;
	}
	else
	{
		offset_D2Client = lu->D2Client->DllOffset;
		offset_D2CMP = lu->D2CMP->DllOffset;
		offset_D2Common = lu->D2Common->DllOffset;
		offset_D2Game = lu->D2Game->DllOffset;
		offset_D2gfx = lu->D2gfx->DllOffset;
		offset_D2Lang = lu->D2Lang->DllOffset;
		offset_D2Launch = lu->D2Launch->DllOffset;
		offset_D2Net = lu->D2Net->DllOffset;
		offset_D2Win = lu->D2Win->DllOffset;
		offset_Fog = lu->Fog->DllOffset;
		offset_Storm = lu->Storm->DllOffset;
	}

	// All DLLs should match same version as game or problems will happen.
	version_D2Client = lu->Game_Version;
	version_D2CMP = lu->Game_Version;
	version_D2Common = lu->Game_Version;
	version_D2Game = lu->Game_Version;
	version_D2gfx = lu->Game_Version;
	version_D2Lang = lu->Game_Version;
	version_D2Launch = lu->Game_Version;
	version_D2Net = lu->Game_Version;
	version_D2Win = lu->Game_Version;
	version_Fog = lu->Game_Version;
	version_Storm = lu->Game_Version;

	log_msg("\n\n");
}
//////////////////////////////////// EXPORTS FUNCTIONS ////////////////////////////////////

void Install_Functions();

extern "C" __declspec(dllexport) bool __stdcall Release()
{
	log_msg("\n***** ENDING DIABLO II *****\n\n" );

	freeCustomLibraries();
	freeD2Libraries();
	return true;
}

extern "C" __declspec(dllexport) void* __stdcall Init(LPSTR IniName)
{
	if (IniName) log_msg("* Gardenia is called from D2mod.dll\n\n");

	static int isInstalled = false;
	if (isInstalled) return NULL;
	isInstalled=true;

	// Initialize/Load Libraries
	lu = new LibraryUtility();

	if (!VersionUtility::IsSupported(lu->Game_Version))
	{
		log_box("Gardenia isn't compatible with this version : %s", VersionUtility::GetVersionAsString(lu->Game_Version));
		Release();
		exit(0);
	}

	initD2modules();

	initD2functions();

	loadParameters();

	if (!active_plugin)	return NULL;

	loadCustomLibraries();

	// Hook DLLs
	lu->HookLibraries();

	// Install Functions (All the offsets in here need to be regathered on a new D2 version)
	Install_Functions();

	// Unhook DLLs
	lu->UnhookLibraries();

	initCustomLibraries();

	loadLocalizedStrings(D2GetLang());

	log_msg("***** ENTERING DIABLO II *****\n\n" );

	active_logFile = active_logFile - 1;

	return NULL;
}

void Install_Functions()
{
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

	if (active_multiPageStash)
		Install_MultiPageStash();

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
}