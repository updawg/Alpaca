#pragma once

#include "Library.h"

class D2CMPLibrary : public Library
{
public:
	D2CMPLibrary(int gameVersion) : Library()
	{
		DllName = "D2CMP.dll";
		DllVersion = gameVersion;
		DllOffset = LoadDiabloLibrary();
		SetFunctions();
	};

	typedef DWORD(__stdcall *TD2CMP10014) (void* image);

	TD2CMP10014 D2CMP10014;
private:
	void SetFunctions();
};