#pragma once

#include "Library.h"

class D2CommonLibrary : public Library
{
public:
	D2CommonLibrary(DWORD gameOffset, int gameVersion) : Library(gameOffset, gameVersion)
	{
		DllName = "D2Common.dll";
		//ShiftValue = 0x10CA;

		//Expected_Shifted_Offset_109B = 0xA1E86FDC;
		//Expected_Shifted_Offset_109D = 0xB1E86FDC;
		//Expected_Shifted_Offset_110 = 0x72D03B42;
		//Expected_Shifted_Offset_111 = 0xF883057E;
		//Expected_Shifted_Offset_111B = 0x16746AC6;
		//Expected_Shifted_Offset_112 = 0x00FE81C3;
		//Expected_Shifted_Offset_113C = 0x74FE85DB;
		//Expected_Shifted_Offset_113D = 0x5EC0335F;

		DllOffset = LoadDiabloLibrary();
		//DllVersion = GetDllVersion();
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
};
