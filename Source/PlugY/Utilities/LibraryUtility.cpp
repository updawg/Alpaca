#include "LibraryUtility.h"

using Versions = VersionUtility::Versions;

// libname = "D2Common", etc
// libVersion = offset + shift
// libOffset = base address where library loaded in OS
// Shift = ?

LibraryUtility::LibraryUtility()
{
	// We need to load the game now so that we have the version base offsets for the rest of the Dlls.
	LoadGame();

	//Game = new Game();
	D2Common = new Library(D2Common_Library_Name, Game_Offset, Game_Version, D2Common_Shift, D2Common_109B, D2Common_109D, D2Common_110, D2Common_111, D2Common_111B, D2Common_112, D2Common_113C, D2Common_113C);
	//D2Common = new Library();
}

//void LibraryUtility::LoadDlls()
//{
//	LoadD2Common();
//}

void LibraryUtility::LoadGame()
{
	Game_Offset = (DWORD)GetModuleHandle(NULL);
	Game_Version = VersionUtility::GetVersion((HMODULE)Game_Offset);
	log_msg("(new) Game.exe loaded at:\t%08X (%s)\n", Game_Offset, VersionUtility::GetVersionAsString(Game_Version));
}

//void LibraryUtility::LoadD2Common()
//{
//	//D2Common_Offset = LoadGameLibrary(D2Common_Library_Name);
//	//D2Common_Version = GetDLLVersion(D2Common_Shift, D2Common_109B, D2Common_109D, D2Common_110, D2Common_111, D2Common_111B, D2Common_112, D2Common_113C);
//
//	//D2Common->DllOffset = D2Common_Offset;
//	//D2Common->DllVersion = D2Common_Version;
//
//	log_msg("offset: %d: \n", D2Common->DllVersion);
//	//log_msg("%s) NEW\n", VersionUtility::GetVersionAsString(D2Common->Version));
//}