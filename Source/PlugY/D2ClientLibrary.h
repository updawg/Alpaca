#pragma once

#include "Library.h"

class D2ClientLibrary : public Library
{
public:
	D2ClientLibrary(DWORD gameOffset, int gameVersion) : Library(gameOffset, gameVersion)
	{
		DllName = "D2Client.dll";
		ShiftValue = 0x17F;

		Expected_Shifted_Offset_109B = 0x00000000;
		Expected_Shifted_Offset_109D = 0x14500000;
		Expected_Shifted_Offset_110 = 0x12500000;
		Expected_Shifted_Offset_111 = 0x0D814800;
		Expected_Shifted_Offset_111B = 0x0D812800;
		Expected_Shifted_Offset_112 = 0x0DA01000;
		Expected_Shifted_Offset_113C = 0x0DA03000;
		Expected_Shifted_Offset_113D = 0x5EC0335F;

		DllOffset = LoadDiabloLibrary();
		//DllVersion = GetDllVersion();
		DllVersion = GameVersion;
	};
};
