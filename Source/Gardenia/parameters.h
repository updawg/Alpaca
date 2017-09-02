/*=================================================================
	File created by Yohann NICOLAS.

  Loading parameters from ini file.

=================================================================*/
#pragma once

#define GARDENIA_NAME "Gardenia"
#define GARDENIA_VERSION "0.05"
#define GARDENIA_AUTHOR_NAME "Jonathan Vasquez"
#define GARDENIA_AUTHOR_EMAIL "jon@xyinn.org"
#define GARDENIA_BUILD_DATE "September 2, 2017 @ 11:10 ET"

enum TargetMod
{
	MOD_NO = 0,
};

// Global variable (user parameters)
extern char* modDataDirectory;
extern bool active_plugin;
extern bool active_DisableBattleNet;
extern bool active_CheckMemory;
extern char* dllFilenames;
extern bool active_D2Mod;
extern TargetMod selectModParam;

void loadParameters();