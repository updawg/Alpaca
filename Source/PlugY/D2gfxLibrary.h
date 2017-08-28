#pragma once

#include "Library.h"

class D2gfxLibrary : public Library
{
public:
	D2gfxLibrary(DWORD gameOffset, int gameVersion) : Library(gameOffset, gameVersion)
	{
		DllName = "D2gfx.dll";
		DllOffset = LoadDiabloLibrary();
		DllVersion = GameVersion;
	};
};