#pragma once

#include "Library.h"

class D2CMPLibrary : public Library
{
public:
	D2CMPLibrary(DWORD gameOffset, int gameVersion) : Library(gameOffset, gameVersion)
	{
		DllName = "D2CMP.dll";
		DllOffset = LoadDiabloLibrary();
		DllVersion = GameVersion;
		SetFunctions();
	};

private:
	void SetFunctions();
};