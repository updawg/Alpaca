#include "Library.h"

Library::Library(LPCSTR libraryName, DWORD gameOffset, int gameVersion, int shift, DWORD V109B, DWORD V109D, DWORD V110, DWORD V111, DWORD V111B, DWORD V112, DWORD V113C, DWORD V113D)
{
	GameOffset = gameOffset;
	GameVersion = gameVersion;
	DllName = libraryName;

	DllShift = shift;
	Offset_109B = V109B;
	Offset_109D = V109D;
	Offset_110 = V110;
	Offset_111 = V111;
	Offset_111B = V111B;
	Offset_112 = V112;
	Offset_113C = V113C;
	Offset_113D = V113D;

	// Load the Library
	DllOffset = LoadGameLibrary();

	// Set game version
	DllVersion = GetDllVersion();
}

DWORD Library::LoadGameLibrary()
{
	DWORD proposedOffset = (DWORD)LoadLibrary(DllName);

	log_msg("New library loading function for %s\n", DllName);

	//*libOffset = D2Common_Offset;

	if (proposedOffset == NULL)
	{
		log_msg("New Failed to load library : %s\n", DllName);
		exit(-1);
	}
	log_msg("New %s loaded at:\t%08X (", DllName, proposedOffset);

	return proposedOffset;

}

int Library::GetDllVersion()
{
	int proposedVersion;

	DWORD addr = DllOffset + DllShift;
	//log_msg("(newer) offset common: %d, shift: %d, addr: %d\n, compared to: %d, game version: %d", DllOffset, DllShift, addr, Offset_109B, GameVersion);

	if (GameVersion != VersionUtility::Versions::UNKNOWN && (GameVersion <= VersionUtility::Versions::V108 || GameVersion > VersionUtility::Versions::V113d))
	{
		proposedVersion = GameVersion;
	}
	else if (addr == Offset_109B)
	{
		proposedVersion = VersionUtility::Versions::V109b;
	}
	else if (addr == Offset_109D)
	{
		proposedVersion = VersionUtility::Versions::V109d;
	}
	else if (addr == Offset_110)
	{
		proposedVersion = VersionUtility::Versions::V110;
	}
	else if (addr == Offset_111)
	{
		proposedVersion = VersionUtility::Versions::V111;
	}
	else if (addr == Offset_111B)
	{
		proposedVersion = VersionUtility::Versions::V111b;
	}
	else if (addr == Offset_112)
	{
		proposedVersion = VersionUtility::Versions::V112;
	}
	else if (addr == Offset_113C || addr == Offset_113D)
	{
		proposedVersion = VersionUtility::Versions::V113c;
	}
	else
	{
		proposedVersion = GameVersion != VersionUtility::Versions::UNKNOWN ? GameVersion : VersionUtility::Versions::V113d;
		log_msg("unknown, try with ");
	}

	//log_msg("returning: %d", proposedVersion);
	log_msg("%s)\n", VersionUtility::GetVersionAsString(proposedVersion));
	return proposedVersion;
}