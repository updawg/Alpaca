#pragma once

#include "Library.h"

class D2CommonLibrary : public Library
{
public:
	D2CommonLibrary(DWORD gameOffset, int gameVersion) : Library(gameOffset, gameVersion)
	{
		DllName = "D2Common.dll";
		DllOffset = LoadDiabloLibrary();
		DllVersion = GameVersion;

		// Function Pointers
		//#define F7(X, Z, A,B,C,D,E,F,G,H, R, N, P) setFctAddr((DWORD*)&N, (HMODULE)offset_##Z, (LPCSTR)(version_##Z == VersionUtility::Versions::V113d? H : (version_##Z == VersionUtility::Versions::V113c? G : (version_##Z == VersionUtility::Versions::V112? F : (version_##Z == VersionUtility::Versions::V111b? E : (version_##Z == VersionUtility::Versions::V111? D : (version_##Z == VersionUtility::Versions::V110? C : (version_##Z == VersionUtility::Versions::V109d? B : A))))))));
		//F7(STD,  D2Common,00000,00000,00000,10188,11084,11109,10346,10907,	DWORD,		D2Common11084, (Room* ptRoom, DWORD zero));
	};

	// Function Offsets
	DWORD GetD2Common11084()
	{

		VersionIndexes indexes = CreateIndexesUpTo113D(0x00000, 0x00000, 0x00000, 0x10188, 0x11084, 0x11109, 0x10346, 0x10907);
		int offset = GetIndexForVersion(indexes);
		log_msg("\nV2: For %s at version %s the offset is %08X\n", DllName, VersionUtility::GetVersionAsString(GameVersion), offset);
		return offset;
	}

	// Function Offsets
	TD2Common11084 D2Common11084;

	void SetD2Common11084Addr()
	{
		
		VersionIndexes indexes = CreateIndexesUpTo113D(00000, 00000, 00000, 10188, 11084, 11109, 10346, 10907);
		int offset = GetIndexForVersion(indexes);
		log_msg("Before: %08X\n", this->D2Common11084);
		GetFunctionAddress((DWORD*)&this->D2Common11084, (HMODULE)DllOffset, (LPCSTR)offset);
		log_msg("After: %08X :: %d\n", this->D2Common11084, this->D2Common11084);
		log_msg("\nV2: For %s at version %s the offset is %08X :: %d :: %d\n", DllName, VersionUtility::GetVersionAsString(GameVersion), offset, offset, offset);
		//return offset;
	}


};