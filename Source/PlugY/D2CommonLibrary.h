#pragma once

#include "Library.h"

class D2CommonLibrary : public Library
{
public:
	D2CommonLibrary(DWORD gameOffset, int gameVersion) : Library(gameOffset, gameVersion)
	{
		DllName = "D2Common.dll";
		ShiftValue = 0x10CA;

		Expected_Shifted_Offset_109B = 0xA1E86FDC;
		Expected_Shifted_Offset_109D = 0xB1E86FDC;
		Expected_Shifted_Offset_110 = 0x72D03B42;
		Expected_Shifted_Offset_111 = 0xF883057E;
		Expected_Shifted_Offset_111B = 0x16746AC6;
		Expected_Shifted_Offset_112 = 0x00FE81C3;
		Expected_Shifted_Offset_113C = 0x74FE85DB;
		Expected_Shifted_Offset_113D = 0x5EC0335F;

		DllOffset = LoadDiabloLibrary();
		//DllVersion = GetDllVersion();
		DllVersion = GameVersion;
	};
};
