#pragma once

#include "Library.h"

class D2NetLibrary : public Library
{
public:
	D2NetLibrary(DWORD gameOffset, int gameVersion) : Library(gameOffset, gameVersion)
	{
		DllName = "D2Net.dll";
		DllOffset = LoadDiabloLibrary();
		DllVersion = GameVersion;
	};

private:
	void SetFunctions();
};