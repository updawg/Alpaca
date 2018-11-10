// Copyright (C) 2004-2017 Yohann Nicolas
// Copyright (C) 2017-2018 Jonathan Vasquez <jon@xyinn.org>
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

#include "Commands.h"
#include "MainScreen.h"
#include "BigStash.h"
#include "InfinityStash.h"
#include "Common.h"
#include "ExtraPatches.h"
#include "CustomLibraries.h"

void FreeLibrary(DWORD library)
{
	if (library && library != Game::Offset)
		FreeLibrary((HMODULE)library);
}

void FreeD2Libraries()
{
	log_msg("\nFree Libraries\n");
	log_msg("====================================\n");

	FreeLibrary(D2Client::Offset);
	FreeLibrary(D2Common::Offset);
	FreeLibrary(D2Game::Offset);
	FreeLibrary(D2gfx::Offset);
	FreeLibrary(D2Launch::Offset);
	FreeLibrary(D2Net::Offset);
	FreeLibrary(D2Win::Offset);
	FreeLibrary(Fog::Offset);
	FreeLibrary(Storm::Offset);
}

void LoadCustomLibraries()
{
	char* curString = NULL;
	TCustomDll* nextDll;
	DWORD offset_currentDll;

	log_msg("Custom Libraries\n");
	log_msg("====================================\n");

	if (dllFilenames)
	{
		curString = strtok(dllFilenames, "|");
	
		if (curString)
		{
			while (curString)
			{
				if (curString[0])
				{
					log_msg("Loading Library: %s\n", curString);
					offset_currentDll = (DWORD)LoadLibrary(curString);
					if (!offset_currentDll)
					{
						log_msg("Failed to load library: %s\n", curString);
						exit(0);
					}

					nextDll = customDlls;
					customDlls = new(TCustomDll);
					customDlls->nextDll = nextDll;
					customDlls->initialize(offset_currentDll);
				}
				curString = strtok(NULL, "|");
			}
		}

		D2FogMemDeAlloc(dllFilenames, __FILE__, __LINE__, 0);
	}
		
	log_msg("\n");
}

void FreeCustomLibraries()
{
	if (!customDlls) return;

	TCustomDll* dll = customDlls;
	TCustomDll* nextDll;

	log_msg("\nFree Custom Libraries\n");
	log_msg("====================================\n");

	while (dll)
	{
		dll->release();
		FreeLibrary(dll->offset);
		nextDll = dll->nextDll;
		D2FogMemDeAlloc(dll, __FILE__, __LINE__, 0);
		dll = nextDll;
	}
}

//////////////////////////////////// EXPORTS FUNCTIONS ////////////////////////////////////

void InstallAlpacaFunctions();

extern "C" __declspec(dllexport) bool __stdcall Release()
{
	active_logFile = true;
	log_msg("\nExiting Diablo II\n");
	log_msg("====================================\n");

	FreeCustomLibraries();
	FreeD2Libraries();
	return true;
}

extern "C" __declspec(dllexport) void* __stdcall Init(LPSTR IniName)
{
	if (IniName)
	{
		log_msg("Alpaca was called from D2Mod.dll\n\n");
	}

	// If you want to debug all of the initialization code
	// you can uncomment the below MessageBox and put a breakpoint after it.
	// Reason for this is that this code happens quickly and very early before D2
	// fully starts, thus by the time you can attach your debugger to Game.exe,
	// all of this code already finished. So we can use the MessageBox trick.
	// Thanks to Necrolis @ PhrozenKeep for bringing this trick up.
	//MessageBox(GetActiveWindow(), "The Alpacas have arrived!", "Alpaca", MB_APPLMODAL);

	LibraryLoader::Init();
	InitializeDiabloFunctions();
	LoadParameters();
	InstallAlpacaFunctions();
	LoadCustomLibraries();

	log_msg("Entering Diablo II\n");
	log_msg("====================================\n");

	active_logFile = active_logFileIniOriginal;

	return NULL;
}

void InstallAlpacaFunctions()
{
	LibraryLoader::HookLibraries();

	log_msg("Alpaca Patches\n");
	log_msg("====================================\n");

	Install_Commands();

	if (active_DiabloVersionTextChange)
	{
		Install_VersionChange();
	}
	
	if (active_PrintAlpacaVersion)
	{
		Install_PrintAlpacaVersion();
	}
	
	Install_BigStash();
	Install_MultiPageStash();
	ExtraPatches::DisplayItemLevel();

	log_msg("\n");

	LibraryLoader::UnhookLibraries();
}