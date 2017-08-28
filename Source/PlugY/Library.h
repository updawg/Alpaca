#pragma once

#include "common.h"

class Library
{
public:
	//Library();
	Library(LPCSTR libraryName, DWORD gameOffset, int gameVersion, int shift, DWORD V109B, DWORD V109D, DWORD V110, DWORD V111, DWORD V111B, DWORD V112, DWORD V113C, DWORD V113D);
	int GetDllVersion();
	DWORD LoadGameLibrary();

	int DllVersion;
	DWORD DllOffset;
	int DllShift;
	LPCTSTR DllName;

	DWORD GameOffset;
	int GameVersion;

	// Offsets for Versions (these are constants for that version)
	DWORD Offset_109B;
	DWORD Offset_109D;
	DWORD Offset_110;
	DWORD Offset_111;
	DWORD Offset_111B;
	DWORD Offset_112;
	DWORD Offset_113C;
	DWORD Offset_113D;
private:

};