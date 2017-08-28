#include "LibraryUtility.h"

using Versions = VersionUtility::Versions;

// libname = "D2Common", etc
// libVersion = offset + shift
// libOffset = base address where library loaded in OS
// Shift = ?

LibraryUtility::LibraryUtility()
{
	//D2Common = new Library();
}

void LibraryUtility::LoadDlls()
{
	LoadD2Common();
}

void LibraryUtility::LoadGame()
{
	Game_Offset = (DWORD)GetModuleHandle(NULL);
	Game_Version = VersionUtility::GetVersion((HMODULE)Game_Offset);
	log_msg("(new) Game.exe loaded at:\t%08X (%s)\n", Game_Offset, VersionUtility::GetVersionAsString(Game_Version));
}

void LibraryUtility::LoadD2Common()
{
	D2Common_Offset = LoadGameLibrary(D2Common_Library_Name);
	D2Common_Version = GetDLLVersion(D2Common_Shift, D2Common_109B, D2Common_109D, D2Common_110, D2Common_111, D2Common_111B, D2Common_112, D2Common_113C);
	log_msg("offset: %d: \n", D2Common_Version);
	log_msg("%s) NEW\n", VersionUtility::GetVersionAsString(D2Common_Version));
}

int LibraryUtility::GetDLLVersion(int shift, DWORD v109b, DWORD v109d, DWORD v110, DWORD v111, DWORD v111b, DWORD v112, DWORD v113c)
{
	int proposedVersion;

	DWORD addr = D2Common_Offset + shift;
	//log_msg("(new) offset common: %d, shift: %d, addr: %d\n, compared to: %d, game version: %d", D2Common_Offset, shift, addr, v109b, version_Game);

	if (Game_Version != Versions::UNKNOWN && (Game_Version <= Versions::V108 || Game_Version >= Versions::V113d))
		proposedVersion = Game_Version;

	else if (addr == v109b)
	{
			proposedVersion = Versions::V109b;
	}
	else if (addr == v109d)
	{
		proposedVersion = Versions::V109d;
	}
	else if (addr == v110)
		proposedVersion = Versions::V110;
	else if (addr == v111)
		proposedVersion = Versions::V111;
	else if (addr == v111b)
		proposedVersion = Versions::V111b;
	else if (addr == v112)
		proposedVersion = Versions::V112;
	else if (addr == v113c)
		proposedVersion = Versions::V113c;
	else {
		proposedVersion = version_Game != Versions::UNKNOWN ? version_Game : Versions::V113d;
		log_msg("unknown, try with ");
	}

	log_msg("returning: %d", proposedVersion);
	return proposedVersion;
}

DWORD LibraryUtility::LoadGameLibrary(LPCSTR libName)
{
	DWORD proposedOffset = (DWORD) LoadLibrary(libName);

	log_msg("New library loading function for %s\n", libName);

	//*libOffset = D2Common_Offset;

	if (proposedOffset == NULL)
	{
		log_msg("New Failed to load library : %s\n", libName);
		exit(-1);
	}
	log_msg("New %s loaded at:\t%08X (", libName, proposedOffset);
	
	return proposedOffset;
		
}