#pragma once

#include "Library.h"

class D2LaunchLibrary : public Library
{
public:
	D2LaunchLibrary(DWORD gameOffset, int gameVersion) : Library(gameOffset, gameVersion)
	{
		DllName = "D2Launch.dll";
		DllOffset = LoadDiabloLibrary();
		DllVersion = GameVersion;
		SetFunctions();
	};

private:
	void SetFunctions();
};