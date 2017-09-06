// Copyright (C) 2004-2017 Yohann Nicolas
// Copyright (C) 2017 L'Autour
// Copyright (C) 2017 Jonathan Vasquez <jon@xyinn.org>
//
// This program is free software : you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.

#include "globalVariable.h"		// Install_VariableOnRealm()
#include "commands.h"			// Install_Commands()
#include "mainScreen.h"			// Install_PrintPlugYVersion() Install_VersionChange()
#include "bigStash.h"			// Install_BigStash()
#include "statsPoints.h"		// Install_StatsPoints() Install_StatsLimitShiftClick()
#include "infinityStash.h"		// Install_MultiPageStash()
#include "newInterfaces.h"		// Install_NewInterfaces()
#include "extraOptions.h"		// Install_AlwaysRegenMapInSP()
#include "language.h"			// Install_LanguageManagement()
#include "windowed.h"			// installed with Install_PrintPlugYVersion()
#include "customLibraries.h"
#include "common.h"				// Includes "d2wrapper.h"

// Make this global so people can use it.
LibraryUtility* lu;
GameLibrary* Game;
D2ClientLibrary* D2Client;
D2CMPLibrary* D2CMP;
D2CommonLibrary* D2Common;
D2GameLibrary* D2Game;
D2gfxLibrary* D2gfx;
D2LangLibrary* D2Lang;
D2LaunchLibrary* D2Launch;
D2NetLibrary* D2Net;
D2WinLibrary* D2Win;
FogLibrary* Fog;
StormLibrary* Storm;

void freeLibrary(DWORD library)
{
	if (library && library != Game->Offset)
		FreeLibrary((HMODULE)library);
}

void freeD2Libraries()
{
	if (Game->Version >= VersionUtility::Versions::V114a)
		return;

	log_msg("***** Free Libraries *****\n");

	freeLibrary(D2Client->Offset);
	freeLibrary(D2CMP->Offset);
	freeLibrary(D2Common->Offset);
	freeLibrary(D2Game->Offset);
	freeLibrary(D2gfx->Offset);
	freeLibrary(D2Lang->Offset);
	freeLibrary(D2Launch->Offset);
	freeLibrary(D2Net->Offset);
	freeLibrary(D2Win->Offset);
	freeLibrary(Fog->Offset);
	freeLibrary(Storm->Offset);

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

	log_msg("\n");
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

	// Expose libraries so its easier to reference.
	Game = lu->Game;
	D2Client = lu->D2Client;
	D2CMP = lu->D2CMP;
	D2Common = lu->D2Common;
	D2Game = lu->D2Game;
	D2gfx = lu->D2gfx;
	D2Lang = lu->D2Lang;
	D2Launch = lu->D2Launch;
	D2Net = lu->D2Net;
	D2Win = lu->D2Win;
	Fog = lu->Fog;
	Storm = lu->Storm;

	if (!VersionUtility::IsSupported(Game->Version))
	{
		log_box("Gardenia isn't compatible with this version : %s", VersionUtility::GetVersionAsString(Game->Version));
		Release();
		exit(0);
	}

	initD2functions();
	loadParameters();

	if (!active_plugin)	return NULL;

	loadCustomLibraries();

	lu->HookLibraries();
	Install_Functions();
	lu->UnhookLibraries();

	initCustomLibraries();

	loadLocalizedStrings(D2Lang->D2GetLang());

	log_msg("***** ENTERING DIABLO II *****\n");

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

	log_msg("DLL patched sucessfully.\n\n");
}