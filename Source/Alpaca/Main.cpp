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

#include "commands.h"
#include "mainScreen.h"
#include "bigStash.h"
#include "infinityStash.h"
#include "customLibraries.h"
#include "common.h"

void freeLibrary(DWORD library)
{
	if (library && library != Game::Offset)
		FreeLibrary((HMODULE)library);
}

void freeD2Libraries()
{
	log_msg("***** Free Libraries *****\n");

	freeLibrary(D2Client::Offset);
	freeLibrary(D2CMP::Offset);
	freeLibrary(D2Common::Offset);
	freeLibrary(D2Game::Offset);
	freeLibrary(D2gfx::Offset);
	freeLibrary(D2Lang::Offset);
	freeLibrary(D2Launch::Offset);
	freeLibrary(D2Net::Offset);
	freeLibrary(D2Win::Offset);
	freeLibrary(Fog::Offset);
	freeLibrary(Storm::Offset);

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

void InitializeCustomLibraries()
{
	log_msg("***** Init custom libraries *****\n");

	TCustomDll* dll=customDlls;
	while (dll)
	{
		dll->init();
		dll = dll->nextDll;
	}
}

void LoadCustomLibraries()
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

void InstallAlpacaFunctions();

extern "C" __declspec(dllexport) bool __stdcall Release()
{
	log_msg("\n***** ENDING DIABLO II *****\n\n" );
	freeCustomLibraries();
	freeD2Libraries();
	return true;
}

extern "C" __declspec(dllexport) void* __stdcall Init(LPSTR IniName)
{
	// If you want to debug all of the initialization code
	// you can uncomment the below MessageBox and put a breakpoint after it.
	// Reason for this is that this code happens quickly and very early before D2
	// fully starts, thus by the time you can attach your debugger to Game.exe,
	// all of this code already finished. So we can use the MessageBox trick.
	// Thanks to Necrolis @ PhrozenKeep for bringing this trick up.
	//MessageBox(GetActiveWindow(), (LPCSTR)L"Alpaca is Loaded", (LPCSTR)L"Alpaca", MB_APPLMODAL);

	if (IniName) log_msg("* Alpaca is called from D2Mod.dll\n\n");

	static int isInstalled = false;
	if (isInstalled) return NULL;
	isInstalled=true;

	// Initialize/Load Libraries
	LibraryLoader::Init();

	if (!VersionUtility::IsSupported())
	{
		log_box("Alpaca isn't compatible with this version : %s\n", VersionUtility::GetVersionAsString());
		Release();
		exit(0);
	}

	InitializeDiabloFunctions();
	LoadParameters();

	if (!active_plugin)	return NULL;

	LoadCustomLibraries();
	InstallAlpacaFunctions();
	InitializeCustomLibraries();
	LoadLocalizedStrings();

	log_msg("***** ENTERING DIABLO II *****\n");

	active_logFile = 0;

	return NULL;
}

void InstallAlpacaFunctions()
{
	LibraryLoader::HookLibraries();

	log_msg("***** INSTALL FUNCTIONS *****\n");

	Install_Commands();

	if (active_DiabloVersionTextChange)
		Install_VersionChange();

	if (active_PrintAlpacaVersion)
		Install_PrintVersion();

	if (active_bigStash)
		Install_BigStash();

	if (active_multiPageStash)
		Install_MultiPageStash();

	log_msg("DLL patched sucessfully.\n\n");

	LibraryLoader::UnhookLibraries();
}