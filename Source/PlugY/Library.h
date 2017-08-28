#pragma once

#include "common.h"

class Library
{
public:
	// Load the Library (This is the DLLs base Offset that we can use to
	// determine the game version for the dll). This should be identical
	// to the Game Version of the .exe.
	DWORD LoadDiabloLibrary();

	// Set dll version (should be same as Game)
	int GetDllVersion();
	
	void HookLibrary();
	void UnhookLibrary();

	int DllVersion;
	DWORD DllOffset;
	LPCTSTR DllName;

	DWORD GameOffset;
	int GameVersion;

	// A value that we are using to determine what version the DLLs are.
	// We need this since simply loading the DLL for most versions gives us the same Base Offset.
	int ShiftValue;

	// Offsets for Versions (these are constants for that version)
	DWORD Expected_Shifted_Offset_109B;
	DWORD Expected_Shifted_Offset_109D;
	DWORD Expected_Shifted_Offset_110;
	DWORD Expected_Shifted_Offset_111;
	DWORD Expected_Shifted_Offset_111B;
	DWORD Expected_Shifted_Offset_112;
	DWORD Expected_Shifted_Offset_113C;
	DWORD Expected_Shifted_Offset_113D;

protected:
	// Prevent this class from being instantiated.
	//Library(LPCSTR libraryName, DWORD gameOffset, int gameVersion, DWORD V109B, DWORD V109D, DWORD V110, DWORD V111, DWORD V111B, DWORD V112, DWORD V113C, DWORD V113D);
	Library(DWORD gameOffset, int gameVersion);
};