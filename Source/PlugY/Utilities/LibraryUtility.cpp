#include "LibraryUtility.h"

// libname = "D2Common", etc
// libVersion = offset + shift
// libOffset = base address where library loaded in OS
// Shift = ?

LibraryUtility::LibraryUtility()
{
	// We need to load the game now so that we have the version base offsets for the rest of the Dlls.
	LoadGame();

	if (!VersionUtility::IsSupported(Game_Version))
	{
		log_msg("Unsupported version: %s. Exiting.\n", VersionUtility::GetVersionAsString(version_Game));
		exit(-1);
	}

	if (VersionUtility::IsEqualOrGreaterThan114(Game_Version))
	{
		log_msg("1.14d support is still being implemented!");
		//exit(-1);
	}
	else
	{
		D2Client = new D2ClientLibrary(Game_Offset, Game_Version);
		D2CMP = new D2CMPLibrary(Game_Offset, Game_Version);
		D2Common = new D2CommonLibrary(Game_Offset, Game_Version);
		D2Game = new D2GameLibrary(Game_Offset, Game_Version);
		D2gfx = new D2gfxLibrary(Game_Offset, Game_Version);
		D2Lang = new D2LangLibrary(Game_Offset, Game_Version);
		D2Launch = new D2LaunchLibrary(Game_Offset, Game_Version);
		D2Net = new D2NetLibrary(Game_Offset, Game_Version);
		D2Win = new D2WinLibrary(Game_Offset, Game_Version);
		Fog = new FogLibrary(Game_Offset, Game_Version);
		Storm = new StormLibrary(Game_Offset, Game_Version);
	}
}

void LibraryUtility::LoadGame()
{
	Game_Offset = (DWORD)GetModuleHandle(NULL);
	Game_Version = VersionUtility::GetVersion("Game.exe");

	log_msg("Game.exe loaded at:\t%08X (%s)\n", Game_Offset, VersionUtility::GetVersionAsString(Game_Version));
}

void LibraryUtility::HookLibraries()
{
	log_msg("***** Unprotect Libraries *****\n");

	D2Client->HookLibrary();
	D2Common->HookLibrary();
	D2Game->HookLibrary();
	D2gfx->HookLibrary();
	D2Lang->HookLibrary();
	D2Launch->HookLibrary();
	Fog->HookLibrary();
	Storm->HookLibrary();

	log_msg("\n\n");
}

void LibraryUtility::UnhookLibraries()
{
	log_msg("***** Reprotect Libraries *****\n");

	D2Client->UnhookLibrary();
	D2Common->UnhookLibrary();
	D2Game->UnhookLibrary();
	D2gfx->UnhookLibrary();
	D2Lang->UnhookLibrary();
	D2Launch->UnhookLibrary();
	Fog->UnhookLibrary();
	Storm->UnhookLibrary();

	log_msg("\n\n");
}