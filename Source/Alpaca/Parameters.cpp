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

#include "mainScreen.h"
#include "bigStash.h"
#include "infinityStash.h"
#include "commands.h"

char* modDataDirectory = "Alpaca";
bool active_plugin = true;
bool active_CheckMemory = true;
bool active_D2Mod = false;
char* dllFilenames;
char* parametersFileName = "Alpaca.ini";

const int BUFFER_SIZE = 1024;

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
const char* S_maxSelfPages = "MaxPersonalPages";
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

// Convert 4 char code in a DWORD code
#define BIN(A,B,C,D) ((DWORD)A) + (((DWORD)B) << 8) + (((DWORD)C) << 16) + (((DWORD)D) << 24)

bool IsEnabled(char* symbol)
{
	return atoi(symbol) != 0;
}

void GetValueFromIni(INIFile* iniFile, const char* areaName, const char* optionName, const char* defaultValue, char* buffer, DWORD maxSize)
{
	if (!iniFile->GetPrivateProfileString(areaName, optionName, defaultValue, buffer, maxSize))
	{
		log_msg("[Error] Failed to load \"%s\" from configuration file. Defaulting to %s ...", optionName, defaultValue);
	}
}

void LogParameterBooleanValue(const char* parameterName, bool parameterValue)
{
	log_msg("%s = %u\n", parameterName, parameterValue);
}

void LogParameterIntegerValue(const char* parameterName, DWORD parameterValue)
{
	log_msg("%s = %d\n", parameterName, parameterValue);
}

void LogParameterStringValue(const char* parameterName, const char* parameterValue)
{
	log_msg("%s = %s\n", parameterName, parameterValue);
}

void init_ActivePlugin(INIFile* iniFile, char* buffer, DWORD maxSize)
{
	GetValueFromIni(iniFile, S_GENERAL, S_active_plugin, "0", buffer, maxSize);
	active_plugin = IsEnabled(buffer);
	LogParameterBooleanValue(S_active_plugin, active_plugin);
}

void init_General(INIFile* iniFile, char* buffer, DWORD maxSize)
{
	GetValueFromIni(iniFile, S_GENERAL, S_active_logFile, "0", buffer, maxSize);

	// Temporarily save the log value into this value since we are still logging data
	// during initialization. We will turn off logging at the end before we go into D2 if needed.
	active_logFileIniOriginal = IsEnabled(buffer);

	LogParameterIntegerValue(S_active_logFile, active_logFileIniOriginal);

	GetValueFromIni(iniFile, S_GENERAL, S_active_CheckMemory, "1", buffer, maxSize);
	active_CheckMemory = IsEnabled(buffer);
	LogParameterIntegerValue(S_active_CheckMemory, active_CheckMemory);

	GetValueFromIni(iniFile, S_GENERAL, S_dllFilenames, "", buffer, maxSize);
	strcat(buffer,"|");
	char* buf = &buffer[strlen(buffer)];

	if (!iniFile->GetPrivateProfileString(S_GENERAL, S_dllFilenames2, NULL, buf, maxSize))
	{
		log_msg("No DLL filenames retrieved from configuration file ...");
	}

	dllFilenames = (char*)D2FogMemAlloc(strlen(buffer)+1,__FILE__,__LINE__,0);
	strcpy(dllFilenames, buffer);

	LogParameterStringValue(S_dllFilenames, dllFilenames);
}

void init_VersionText(INIFile* iniFile, char* buffer, DWORD maxSize)
{
	GetValueFromIni(iniFile, S_MAIN_SCREEN, S_active_DiabloVersionTextChange, "0", buffer, maxSize);
	active_DiabloVersionTextChange = IsEnabled(buffer);
	LogParameterBooleanValue(S_active_DiabloVersionTextChange, active_DiabloVersionTextChange);

	if (active_DiabloVersionTextChange)
	{
		GetValueFromIni(iniFile, S_MAIN_SCREEN, S_DiabloVersionText, DiabloVersionText, buffer, maxSize);
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
		LogParameterStringValue(S_DiabloVersionText, DiabloVersionText);

		GetValueFromIni(iniFile, S_MAIN_SCREEN, S_DiabloVersionColor, "0", buffer, maxSize);
		DiabloVersionColor = atoi(buffer);
		LogParameterIntegerValue(S_DiabloVersionColor, DiabloVersionColor);
	}

	GetValueFromIni(iniFile, S_MAIN_SCREEN, S_active_PrintAlpacaVersion, "1", buffer, maxSize);
	active_PrintAlpacaVersion = IsEnabled(buffer);
	LogParameterBooleanValue(S_active_PrintAlpacaVersion, active_PrintAlpacaVersion);

	if (active_PrintAlpacaVersion)
	{
		GetValueFromIni(iniFile, S_MAIN_SCREEN, S_AlpacaVersionColor, "4", buffer, maxSize);
		AlpacaVersionColor = atoi(buffer);
		LogParameterIntegerValue(S_AlpacaVersionColor, AlpacaVersionColor);
	}
}

void init_Stash(INIFile* iniFile, char* buffer, DWORD maxSize)
{
	active_PlayerCustomData = true;

	GetValueFromIni(iniFile, S_STASH, S_maxSelfPages, "-1", buffer, maxSize);
	maxSelfPages = atoi(buffer);
	LogParameterIntegerValue(S_maxSelfPages, maxSelfPages);

	GetValueFromIni(iniFile, S_STASH, S_nbPagesPerIndex, "10", buffer, maxSize);
	nbPagesPerIndex = atoi(buffer);
	if (!nbPagesPerIndex) nbPagesPerIndex = 10;
	LogParameterIntegerValue(S_nbPagesPerIndex, nbPagesPerIndex);

	GetValueFromIni(iniFile, S_STASH, S_nbPagesPerIndex2, "100", buffer, maxSize);
	nbPagesPerIndex2 = atoi(buffer);
	if (!nbPagesPerIndex2) nbPagesPerIndex2 = 100;
	LogParameterIntegerValue(S_nbPagesPerIndex2, nbPagesPerIndex2);

	GetValueFromIni(iniFile, S_STASH, S_active_sharedStash, "0", buffer, maxSize);
	active_sharedStash = IsEnabled(buffer);
	LogParameterBooleanValue(S_active_sharedStash, active_sharedStash);

	// Button positions don't really need to be exposed to the user.
	const int defaultButtonPositionValue = -1;
	posXPreviousBtn = defaultButtonPositionValue;
	posYPreviousBtn = defaultButtonPositionValue;
	posXNextBtn = defaultButtonPositionValue;
	posYNextBtn = defaultButtonPositionValue;
	posXSharedBtn = defaultButtonPositionValue;
	posYSharedBtn = defaultButtonPositionValue;
	posXPreviousIndexBtn = defaultButtonPositionValue;
	posYPreviousIndexBtn = defaultButtonPositionValue;
	posXNextIndexBtn = defaultButtonPositionValue;
	posYNextIndexBtn = defaultButtonPositionValue;
	posXPutGoldBtn = defaultButtonPositionValue;
	posYPutGoldBtn = defaultButtonPositionValue;
	posXTakeGoldBtn = defaultButtonPositionValue;
	posYTakeGoldBtn = defaultButtonPositionValue;

	if (active_sharedStash)
	{
		GetValueFromIni(iniFile, S_STASH, S_openSharedStashOnLoading, "0", buffer, maxSize);
		openSharedStashOnLoading = IsEnabled(buffer);
		LogParameterBooleanValue(S_openSharedStashOnLoading, openSharedStashOnLoading);

		GetValueFromIni(iniFile, S_STASH, S_maxSharedPages, "-1", buffer, maxSize);
		maxSharedPages = atoi(buffer);
		LogParameterIntegerValue(S_maxSharedPages, maxSharedPages);

		GetValueFromIni(iniFile, S_STASH, S_sharedStashFilename, "SharedStashSave", buffer, maxSize);
		sharedStashFilename = (char*)D2FogMemAlloc(strlen(buffer)+1,__FILE__,__LINE__,0);
		strcpy(sharedStashFilename, buffer);
		LogParameterStringValue(S_sharedStashFilename, sharedStashFilename);

		// Mixing items between hardcore and softcore is not allowed in the SPF.
		separateHardSoftStash = true;

		GetValueFromIni(iniFile, S_STASH, S_displaySharedSetItemNameInGreen, "1", buffer, maxSize);
		displaySharedSetItemNameInGreen = IsEnabled(buffer);
		LogParameterBooleanValue(S_displaySharedSetItemNameInGreen, displaySharedSetItemNameInGreen);

		GetValueFromIni(iniFile, S_STASH, S_active_sharedGold, "1", buffer, maxSize);
		active_sharedGold = IsEnabled(buffer);
		LogParameterBooleanValue(S_active_sharedGold, active_sharedGold);
	}
}

void LoadParameters()
{
	char buffer[BUFFER_SIZE];
	INIFile *iniFile = new INIFile;

	srand((UINT)time(NULL));

	log_msg("Parameters\n");
	log_msg("====================================\n");

	bool wasFileSuccessfullyOpened = iniFile->InitReadWrite(parametersFileName, INIFILE_READ, 0);
	if (wasFileSuccessfullyOpened)
	{
		init_ActivePlugin(iniFile, buffer, BUFFER_SIZE);
		if (active_plugin)
		{
			init_General(iniFile, buffer, BUFFER_SIZE);
			init_VersionText(iniFile, buffer, BUFFER_SIZE);
			init_Stash(iniFile, buffer, BUFFER_SIZE);
		}
	}
	else
	{
		log_msg("There was an error opening the configuration file. Aborting.\n\n");
		active_plugin = false;
	}

	if (iniFile)
	{
		iniFile->close();
	}

	delete iniFile;
}