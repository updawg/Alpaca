#pragma once

#include "Library.h"

class StormLibrary : public Library
{
public:
	StormLibrary(DWORD gameOffset, int gameVersion) : Library(gameOffset, gameVersion)
	{
		DllName = "Storm.dll";
		DllOffset = LoadDiabloLibrary();
		DllVersion = GameVersion;
		SetFunctions();
	};

	typedef DWORD(__stdcall *TD2StormMPQOpenFile) (DWORD zero, LPCSTR fileName, DWORD dwSearchScope, void** buffer);
	typedef void(__stdcall *TD2Storm503) (DWORD, DWORD, DWORD);
	typedef void(__stdcall *TD2FreeWinMessage) (sWinMessage* msg);

	TD2StormMPQOpenFile D2StormMPQOpenFile;
	TD2Storm503 D2Storm503;
	TD2FreeWinMessage D2FreeWinMessage;
private:
	void SetFunctions();

	TD2StormMPQOpenFile GetD2StormMPQOpenFile();
	TD2Storm503 GetD2Storm503();
	TD2FreeWinMessage GetD2FreeWinMessage();
};