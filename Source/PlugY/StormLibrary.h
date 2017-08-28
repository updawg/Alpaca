#pragma once

#include "Library.h"

class StormLibrary : public Library
{
public:
	StormLibrary(DWORD gameOffset, int gameVersion) : Library(gameOffset, gameVersion)
	{
		DllName = "Storm.dll";
		DllOffset = LoadDiabloLibrary();
		DllVersion = GameVersion;
	};
};