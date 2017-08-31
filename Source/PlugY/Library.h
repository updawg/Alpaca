#pragma once

#include <windows.h>
#include <map>
#include "Utilities/VersionUtility.h"

using VersionIndexes = std::map<VersionUtility::Versions, DWORD>;

class Library
{
public:
	// Load the Library (This is the DLLs base Offset that we can use to
	// determine the game version for the dll). This should be identical
	// to the Game Version of the .exe.
	DWORD LoadDiabloLibrary();

	// Set dll version (should be same as Game)
	//int GetDllVersion();
	
	void HookLibrary();
	void UnhookLibrary();

	int DllVersion;
	DWORD DllOffset;
	LPCTSTR DllName;

	DWORD GameOffset;
	int GameVersion;

	// Offsets for functions in these specific versions. When updating to a new diablo version, you will want to add an entry to each of the function sets
	// In each library that require an update.
	DWORD GetIndexForVersion(const VersionIndexes& indexes);	

	VersionIndexes CreateIndexesUpTo113D(DWORD V109, DWORD V109D, DWORD V110, DWORD V111, DWORD V111B, DWORD V112, DWORD V113C, DWORD V113D);

	// On a new version we can do something like this:
	//VersionIndexes CreateIndexesUpTo114D(DWORD V109, DWORD V109D, DWORD V110, DWORD V111, DWORD V111B, DWORD V112, DWORD V113C, DWORD V113D, DWORD V114D);
	// and then in the function implementation for that function we can re-use our existing "UpTo113D" version to create the most of the map, and we can add the new
	// version to it. This allows us not to have to change the function signature for every single call simply because we added a new version. Also the logic for
	// the code to retrieve the offsets uses the maps key property which is to access elements by key rather than by index, so if the key isn't found, the code will
	// still do what it is suppose to.

protected:
	// Prevent this class from being instantiated.
	//Library(LPCSTR libraryName, DWORD gameOffset, int gameVersion, DWORD V109B, DWORD V109D, DWORD V110, DWORD V111, DWORD V111B, DWORD V112, DWORD V113C, DWORD V113D);
	Library(DWORD gameOffset, int gameVersion);
};