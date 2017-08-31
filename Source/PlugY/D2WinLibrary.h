#pragma once

#include "Library.h"

class D2WinLibrary : public Library
{
public:
	D2WinLibrary(DWORD gameOffset, int gameVersion) : Library(gameOffset, gameVersion)
	{
		DllName = "D2Win.dll";
		DllOffset = LoadDiabloLibrary();
		DllVersion = GameVersion;
		SetFunctions();
	};

private:
	void SetFunctions();
};