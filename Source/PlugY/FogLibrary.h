#pragma once

#include "Library.h"

class FogLibrary : public Library
{
public:
	FogLibrary(DWORD gameOffset, int gameVersion) : Library(gameOffset, gameVersion)
	{
		DllName = "Fog.dll";
		DllOffset = LoadDiabloLibrary();
		DllVersion = GameVersion;
	};

private:
	void SetFunctions();
};