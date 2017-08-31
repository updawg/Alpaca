#include "LibraryUtility.h"

// libname = "D2Common", etc
// libVersion = offset + shift
// libOffset = base address where library loaded in OS
// Shift = ?

LibraryUtility::LibraryUtility()
{
	log_msg("***** Get D2 Modules address and version *****\n");

	// We need to load the game now so that we have the version base offsets for the rest of the Dlls.
	LoadGame();

	if (VersionUtility::IsEqualOrGreaterThan114(Game_Version))
	{
		log_msg("1.14d support is not implemented.\n");
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

		//D2Common->GetD2Common11084();
		//D2Common->SetD2Common11084Addr();
		//DWORD off= D2Common->GetD2Common11084_FunctionAddress();
		//D2Common->D2Common11084 = (TD2Common11084)off;
		//log_msg("Function address located at: %08X :: %08X", D2Common->GetD2Common11084_FunctionAddress(), D2Common->D2Common11084);
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

	if (VersionUtility::IsEqualOrGreaterThan114(Game_Version))
	{
		log_msg("Hooking 1.14 libraries");
	}
	else
	{
		D2Client->HookLibrary();
		D2Common->HookLibrary();
		D2Game->HookLibrary();
		D2gfx->HookLibrary();
		D2Lang->HookLibrary();
		D2Launch->HookLibrary();
		Fog->HookLibrary();
		Storm->HookLibrary();
	}

	log_msg("\n\n");
}

void LibraryUtility::UnhookLibraries()
{
	log_msg("***** Reprotect Libraries *****\n");

	if (VersionUtility::IsEqualOrGreaterThan114(Game_Version))
	{
		log_msg("Unhooking 1.14 libraries");
	}
	else
	{
		D2Client->UnhookLibrary();
		D2Common->UnhookLibrary();
		D2Game->UnhookLibrary();
		D2gfx->UnhookLibrary();
		D2Lang->UnhookLibrary();
		D2Launch->UnhookLibrary();
		Fog->UnhookLibrary();
		Storm->UnhookLibrary();
	}

	log_msg("\n\n");
}