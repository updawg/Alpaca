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

#include "Error.h"
#include "INIfile.h"
#include "parameters.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

#define PARAMETERS_FILENAME "Alpaca.ini"
#define PARAM_FIXED_FILENAME "Alpaca\\AlpacaFixed.ini"
#define PARAM_DEFAULT_FILENAME "Alpaca\\AlpacaDefault.ini"

#define BUFSIZE 0x400

#include "mainScreen.h"
#include "bigStash.h"
#include "infinityStash.h"
#include "commands.h"

char* modDataDirectory = "Alpaca";
bool active_plugin = true;
bool active_CheckMemory = true;
bool active_D2Mod = false;
char* dllFilenames;

TargetMod selectModParam = MOD_NO;

const char* S_GENERAL = "GENERAL";
const char* S_dllFilenames = "DllToLoad";
const char* S_dllFilenames2 = "DllToLoad2";
const char* S_active_plugin = "ActivePlugin";
const char* S_active_logFile = "ActiveLogFile";
const char* S_active_CheckMemory = "ActiveCheckMemory";

const char* S_MAIN_SCREEN = "MAIN SCREEN";
const char* S_active_DiabloVersionTextChange = "ActiveDiabloVersionTextChange";
const char* S_DiabloVersionText = "DiabloVersionText";
const char* S_active_PrintAlpacaVersion = "ActivePrintAlpacaVersion";
const char* S_DiabloVersionColor = "ColorOfDiabloVersionText";
const char* S_AlpacaVersionColor = "ColorOfAlpacaVersionText";

const char* S_STASH = "STASH";
const char* S_maxSelfPages = "MaxPersonnalPages";
const char* S_nbPagesPerIndex = "NbPagesPerIndex";
const char* S_nbPagesPerIndex2 = "NbPagesPerIndex2";
const char* S_active_sharedStash = "ActiveSharedStash";
const char* S_openSharedStashOnLoading = "OpenSharedStashOnLoading";
const char* S_maxSharedPages = "MaxSharedPages";
const char* S_sharedStashFilename = "SharedStashFilename";
const char* S_displaySharedSetItemNameInGreen = "DisplaySharedSetItemNameInGreen";
const char* S_active_sharedGold = "ActiveSharedGold";

const char* S_posXPreviousBtn = "PosXPreviousBtn";
const char* S_posYPreviousBtn = "PosYPreviousBtn";
const char* S_posXNextBtn = "PosXNextBtn";
const char* S_posYNextBtn = "PosYNextBtn";
const char* S_posXSharedBtn = "PosXSharedBtn";
const char* S_posYSharedBtn = "PosYSharedBtn";
const char* S_posXPreviousIndexBtn = "PosXPreviousIndexBtn";
const char* S_posYPreviousIndexBtn = "PosYPreviousIndexBtn";
const char* S_posXNextIndexBtn = "PosXNextIndexBtn";
const char* S_posYNextIndexBtn = "PosYNextIndexBtn";
const char* S_posXPutGoldBtn = "PosXPutGoldBtn";
const char* S_posYPutGoldBtn = "PosYPutGoldBtn";
const char* S_posXTakeGoldBtn = "PosXTakeGoldBtn";
const char* S_posYTakeGoldBtn = "PosYTakeGoldBtn";

const char* S_DLL = "DLL:\t";
const char* S_DEFAULT = "DEFAULT:";
const char* S_USER = "USER:\t";
const char* S_FIXED = "FIXED:\t";

// Convert 4 char code in a DWORD code
#define BIN(A,B,C,D) ((DWORD)A) + (((DWORD)B) << 8) + (((DWORD)C) << 16) + (((DWORD)D) << 24)

#define GET_PRIVATE_PROFILE_STRING(S,F,D)\
if (!iniFixedFile->GetPrivateProfileString(S, F, NULL, buffer, maxSize)) \
if (!iniFile->GetPrivateProfileString(S, F, NULL, buffer, maxSize)) \
if (!iniDefaultFile->GetPrivateProfileString(S, F, D, buffer, maxSize)) \
	 log_msg(S_DLL); \
else log_msg(S_DEFAULT); \
else log_msg(S_USER); \
else log_msg(S_FIXED)

#define GET_PRIVATE_PROFILE_STRING2(S,F,D)\
if (!iniFile->GetPrivateProfileString(S, F, NULL, buffer, maxSize)) \
if (!iniDefaultFile->GetPrivateProfileString(S, F, D, buffer, maxSize)) \
	 log_msg(S_DLL); \
else log_msg(S_DEFAULT); \
else log_msg(S_USER)

#define GET_PRIVATE_PROFILE_STRING3(S,F,D)\
if (!iniFile->GetPrivateProfileString(S, F, NULL, buffer, maxSize)) \
if (!iniFixedFile->GetPrivateProfileString(S, F, NULL, buffer, maxSize)) \
if (!iniDefaultFile->GetPrivateProfileString(S, F, D, buffer, maxSize)) \
	 log_msg(S_DLL); \
else log_msg(S_DEFAULT); \
else log_msg(S_FIXED); \
else log_msg(S_USER)

void init_ActivePlugin(INIFile* iniFile, INIFile* iniFixedFile, INIFile* iniDefaultFile, char* buffer, DWORD maxSize)
{
	iniFixedFile->GetPrivateProfileString(S_GENERAL, S_active_plugin, "0", buffer, maxSize);
	active_plugin = atoi(buffer) != 0;
	if (!active_plugin)
	{
		GET_PRIVATE_PROFILE_STRING2(S_GENERAL, S_active_plugin, "1");
		active_plugin = atoi(buffer) != 0;
	} else log_msg(S_FIXED);
	log_msg("active_plugin\t\t\t\t= %u\n", active_plugin);
}

void init_General(INIFile* iniFile, INIFile* iniFixedFile, INIFile* iniDefaultFile, char* buffer, DWORD maxSize)
{
	GET_PRIVATE_PROFILE_STRING(S_GENERAL, S_active_logFile, "0");
	active_logFile = atoi(buffer)+1;
	log_msg("active_logFile\t\t\t\t= %d\n", active_logFile-1);

	GET_PRIVATE_PROFILE_STRING(S_GENERAL, S_active_CheckMemory, "1");
	active_CheckMemory = atoi(buffer) != 0;
	log_msg("active_CheckMemory\t\t\t= %d\n", active_CheckMemory);

	GET_PRIVATE_PROFILE_STRING(S_GENERAL,S_dllFilenames,"");
	strcat(buffer,"|");
	char* buf = &buffer[strlen(buffer)];
	if (!iniFixedFile->GetPrivateProfileString(S_GENERAL, S_dllFilenames2, NULL, buf, maxSize))
	if (!iniFile->GetPrivateProfileString(S_GENERAL, S_dllFilenames2, NULL, buf, maxSize))
		iniDefaultFile->GetPrivateProfileString(S_GENERAL, S_dllFilenames2, NULL, buf, maxSize);
	dllFilenames = (char*)D2FogMemAlloc(strlen(buffer)+1,__FILE__,__LINE__,0);
	strcpy(dllFilenames,buffer);

	log_msg("dllFilenames\t\t\t\t= %s\n",dllFilenames);

	log_msg("\n");
}

void init_VersionText(INIFile* iniFile, INIFile* iniFixedFile, INIFile* iniDefaultFile, char* buffer, DWORD maxSize)
{
	GET_PRIVATE_PROFILE_STRING(S_MAIN_SCREEN, S_active_DiabloVersionTextChange, "0");
	active_DiabloVersionTextChange = atoi(buffer) != 0;
	log_msg("active_VersionTextChange\t\t= %u\n", active_DiabloVersionTextChange);

	if (active_DiabloVersionTextChange)
	{
		GET_PRIVATE_PROFILE_STRING(S_MAIN_SCREEN, S_DiabloVersionText, DiabloVersionText);
		if (!buffer[0])
		{
			if (active_DiabloVersionTextChange == 1)
			{
				strcpy(buffer, "v ");
				strcat(buffer, VersionUtility::GetVersionAsString());
			}
		}

		DiabloVersionText = (char*)D2FogMemAlloc(strlen(buffer)+1,__FILE__,__LINE__,0);
		strcpy(DiabloVersionText, buffer);
		log_msg("DiabloVersionText\t\t\t\t= %s\n", DiabloVersionText);

		GET_PRIVATE_PROFILE_STRING(S_MAIN_SCREEN, S_DiabloVersionColor, "0");
		DiabloVersionColor = atoi(buffer);
		log_msg("DiabloVersionColor\t\t\t\t= %u\n", DiabloVersionColor);
	}

	GET_PRIVATE_PROFILE_STRING(S_MAIN_SCREEN, S_active_PrintAlpacaVersion, "1");
	active_PrintAlpacaVersion = atoi(buffer) != 0;
	log_msg("active_PrintAlpacaVersion\t\t\t= %u\n", active_PrintAlpacaVersion);

	if (active_PrintAlpacaVersion)
	{
		GET_PRIVATE_PROFILE_STRING(S_MAIN_SCREEN, S_AlpacaVersionColor, "4");
		AlpacaVersionColor = atoi(buffer);
		log_msg("AlpacaVersionColor\t\t\t= %u\n", AlpacaVersionColor);
	}
	
	log_msg("\n");
}

void init_Stash(INIFile* iniFile, INIFile* iniFixedFile, INIFile* iniDefaultFile, char* buffer, DWORD maxSize)
{
	active_PlayerCustomData = true;

	GET_PRIVATE_PROFILE_STRING(S_STASH, S_maxSelfPages, "0");
	maxSelfPages = atoi(buffer) - 1;
	log_msg("maxSelfPages\t\t\t\t= %u\n", maxSelfPages);

	GET_PRIVATE_PROFILE_STRING(S_STASH, S_nbPagesPerIndex, "10");
	nbPagesPerIndex = atoi(buffer);
	if (!nbPagesPerIndex) nbPagesPerIndex=10;
	log_msg("nbPagesPerIndex\t\t\t\t= %u\n", nbPagesPerIndex);

	GET_PRIVATE_PROFILE_STRING(S_STASH, S_nbPagesPerIndex2, "100");
	nbPagesPerIndex2 = atoi(buffer);
	if (!nbPagesPerIndex2) nbPagesPerIndex2=100;
	log_msg("nbPagesPerIndex2\t\t\t= %u\n", nbPagesPerIndex2);

	GET_PRIVATE_PROFILE_STRING(S_STASH, S_active_sharedStash, "0");
	active_sharedStash = atoi(buffer) != 0;
	log_msg("active_sharedStash\t\t\t= %u\n", active_sharedStash);

	GET_PRIVATE_PROFILE_STRING(S_STASH, S_posXPreviousBtn,"-1");
	posXPreviousBtn = atoi(buffer);
	GET_PRIVATE_PROFILE_STRING(S_STASH, S_posYPreviousBtn,"-1");
	posYPreviousBtn = atoi(buffer);
	GET_PRIVATE_PROFILE_STRING(S_STASH, S_posXNextBtn,"-1");
	posXNextBtn = atoi(buffer);
	GET_PRIVATE_PROFILE_STRING(S_STASH, S_posYNextBtn,"-1");
	posYNextBtn = atoi(buffer);
	GET_PRIVATE_PROFILE_STRING(S_STASH, S_posXSharedBtn,"-1");
	posXSharedBtn = atoi(buffer);
	GET_PRIVATE_PROFILE_STRING(S_STASH, S_posYSharedBtn,"-1");
	posYSharedBtn = atoi(buffer);
	GET_PRIVATE_PROFILE_STRING(S_STASH, S_posXPreviousIndexBtn,"-1");
	posXPreviousIndexBtn = atoi(buffer);
	GET_PRIVATE_PROFILE_STRING(S_STASH, S_posYPreviousIndexBtn,"-1");
	posYPreviousIndexBtn = atoi(buffer);
	GET_PRIVATE_PROFILE_STRING(S_STASH, S_posXNextIndexBtn,"-1");
	posXNextIndexBtn = atoi(buffer);
	GET_PRIVATE_PROFILE_STRING(S_STASH, S_posYNextIndexBtn,"-1");
	posYNextIndexBtn = atoi(buffer);
	GET_PRIVATE_PROFILE_STRING(S_STASH, S_posXPutGoldBtn,"-1");
	posXPutGoldBtn = atoi(buffer);
	GET_PRIVATE_PROFILE_STRING(S_STASH, S_posYPutGoldBtn,"-1");
	posYPutGoldBtn = atoi(buffer);
	GET_PRIVATE_PROFILE_STRING(S_STASH, S_posXTakeGoldBtn,"-1");
	posXTakeGoldBtn = atoi(buffer);
	GET_PRIVATE_PROFILE_STRING(S_STASH, S_posYTakeGoldBtn,"-1");
	posYTakeGoldBtn = atoi(buffer);

	log_msg("\t\nButtons Positions: %d %d %d %d %d %d %d %d %d %d\n",posXPreviousBtn,posYPreviousBtn,posXNextBtn,posYNextBtn,posXSharedBtn,posYSharedBtn,posXPreviousIndexBtn,posYPreviousIndexBtn,posXNextIndexBtn,posYNextIndexBtn);

	if (active_sharedStash)
	{
		GET_PRIVATE_PROFILE_STRING(S_STASH, S_openSharedStashOnLoading, "0");
		openSharedStashOnLoading = atoi(buffer) != 0;
		log_msg("openSharedStashOnLoading\t\t= %u\n", openSharedStashOnLoading);

		GET_PRIVATE_PROFILE_STRING(S_STASH, S_maxSharedPages, "0");
		maxSharedPages = atoi(buffer) - 1;
		log_msg("maxSharedPages\t\t\t\t= %u\n", maxSharedPages);

		GET_PRIVATE_PROFILE_STRING(S_STASH, S_sharedStashFilename, "SharedStashSave");
		sharedStashFilename = (char*)D2FogMemAlloc(strlen(buffer)+1,__FILE__,__LINE__,0);
		strcpy(sharedStashFilename, buffer);
		log_msg("sharedStashFilename\t\t\t= %s\n", sharedStashFilename);

		// Mixing items between hardcore and softcore is not allowed in the SPF.
		separateHardSoftStash = true;

		GET_PRIVATE_PROFILE_STRING(S_STASH, S_displaySharedSetItemNameInGreen, "1");
		displaySharedSetItemNameInGreen = atoi(buffer) != 0;
		log_msg("displaySharedSetItemNameInGreen\t\t= %u\n", displaySharedSetItemNameInGreen);

		GET_PRIVATE_PROFILE_STRING(S_STASH, S_active_sharedGold, "1");
		active_sharedGold = atoi(buffer) != 0;
		log_msg("active_sharedGold\t\t\t= %u\n", active_sharedGold);
	}

	log_msg("\n");
}

void LoadParameters()
{
	char buffer[BUFSIZE];
	int loading=0;
	INIFile *iniFile = new INIFile;
	INIFile *iniFixedFile = new INIFile;
	INIFile *iniDefaultFile = new INIFile;

	srand((UINT)time(NULL));

	log_msg("***** PARAMETERS *****\n");
	if (iniFile->InitReadWrite(PARAMETERS_FILENAME, INIFILE_READ, 0))
	{
		log_msg("Parameters file is opened.\n\n");
		loading = 1;
	}
	if (iniFixedFile->InitReadWrite(PARAM_FIXED_FILENAME, INIFILE_MPQREAD, 0))
	{
		log_msg("Fixed Parameters file is opened.\n\n");
		loading = 1;
	}
	if (iniDefaultFile->InitReadWrite(PARAM_DEFAULT_FILENAME, INIFILE_MPQREAD, 0))
	{
		log_msg("Default Parameters file is opened.\n\n");
		loading = 1;
	}

	if(loading)
	{
		log_msg("Reading parameters.\n\n");
		init_ActivePlugin(iniFile, iniFixedFile, iniDefaultFile, buffer, BUFSIZE);
		if (active_plugin)
		{
			init_General(iniFile, iniFixedFile, iniDefaultFile, buffer, BUFSIZE);
			init_VersionText(iniFile, iniFixedFile, iniDefaultFile, buffer, BUFSIZE);
			init_Stash(iniFile, iniFixedFile, iniDefaultFile, buffer, BUFSIZE);
		}
		log_msg("Reading parameters end.\n\n");
	} else {
		log_msg("\nCan't open parameters files: Default values used.\n\n");
		active_plugin = false;
	}

	if (iniFile)
		iniFile->close();
	if (iniFixedFile)
		iniFixedFile->close();
	if (iniDefaultFile)
		iniDefaultFile->close();

	delete iniFile;
	delete iniDefaultFile;
	delete iniFixedFile;
}