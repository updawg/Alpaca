#pragma once

#include "Library.h"

class D2LangLibrary : public Library
{
public:
	D2LangLibrary(DWORD gameOffset, int gameVersion) : Library(gameOffset, gameVersion)
	{
		DllName = "D2Lang.dll";
		DllOffset = LoadDiabloLibrary();
		DllVersion = GameVersion;
	};
};