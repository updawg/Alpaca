#pragma once

#include "Library.h"

class D2LaunchLibrary : public Library
{
public:
	D2LaunchLibrary(int gameVersion) : Library()
	{
		DllName = "D2Launch.dll";
		DllVersion = gameVersion;
		DllOffset = LoadDiabloLibrary();
		SetFunctions();
	};

private:
	void SetFunctions();
};