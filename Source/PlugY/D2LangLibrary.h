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
		SetFunctions();
	};

	typedef LPWSTR(__fastcall *TD2GetStringFromString) (const char* ptString);
	typedef LPWSTR(__fastcall *TD2GetStringFromIndex) (WORD dwIndexNum);
	typedef DWORD(__stdcall *TD2GetLang) ();
	typedef DWORD(__stdcall *TD2PrintBigNumber) (LPWSTR ptBuf, DWORD number, DWORD size);

	TD2GetStringFromString D2GetStringFromString;
	TD2GetStringFromIndex D2GetStringFromIndex;
	TD2GetLang D2GetLang;
	TD2PrintBigNumber D2PrintBigNumber;
private:
	void SetFunctions();
};