#pragma once

#include "Library.h"

class D2GameLibrary : public Library
{
public:
	D2GameLibrary(DWORD gameOffset, int gameVersion) : Library(gameOffset, gameVersion)
	{
		DllName = "D2Game.dll";
		DllOffset = LoadDiabloLibrary();
		DllVersion = GameVersion;
	};
};