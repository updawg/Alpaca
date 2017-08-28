#pragma once

#include "../common.h"

// Used to load the libraries
class LibraryUtility
{
public:

	void LoadGame();
	void LoadDlls();
	
	DWORD LoadGameLibrary(LPCSTR libName);
	int GetDLLVersion(int shift, DWORD v109b, DWORD v109d, DWORD v110, DWORD v111, DWORD v111b, DWORD v112, DWORD v113c);

	// we will make the following private some other time
	//int version_Game;
	int Game_Version;
	int version_D2Client;
	int version_D2CMP;
	int version_D2Common;
	int version_D2Game;
	int version_D2gfx;
	int version_D2Lang;
	int version_D2Launch;
	int version_D2Net;
	int version_D2Win;
	int version_Fog;
	int version_Storm;

	// Address in memory of external DLL
	//DWORD offset_Game;
	DWORD Game_Offset;
	DWORD offset_D2Client;
	DWORD offset_D2CMP;
	DWORD D2Common_Offset;
	DWORD offset_D2Game;
	DWORD offset_D2gfx;
	DWORD offset_D2Lang;
	DWORD offset_D2Launch;
	DWORD offset_D2Net;
	DWORD offset_D2Win;
	DWORD offset_Fog;
	DWORD offset_Storm;

	// Game

	// D2Common
	const int D2Common_Shift = 0x10CA;
	int D2Common_Version;

	const DWORD D2Common_109B = 0x6FD410CA;
	const DWORD D2Common_109D = 0xB1E86FDC;
	const DWORD D2Common_110 = 0x72D03B42;
	const DWORD D2Common_111 = 0xF883057E;
	const DWORD D2Common_111B = 0x16746AC6;
	const DWORD D2Common_112 = 0x00FE81C3;
	const DWORD D2Common_113C = 0x74FE85DB;

	// D2Client

	const char* Game_Library_Name = "Game.exe";
	const char* S_D2Client = "D2Client.dll";
	const char* S_D2CMP = "D2CMP.dll";
	const char* D2Common_Library_Name = "D2Common.dll";
	const char* S_D2Game = "D2Game.dll";
	const char* S_D2gfx = "D2gfx.dll";
	const char* S_D2Lang = "D2Lang.dll";
	const char* S_D2Launch = "D2Launch.dll";
	const char* S_D2Net = "D2Net.dll";
	const char* S_D2Win = "D2Win.dll";
	const char* S_Fog = "Fog.dll";
	const char* S_Storm = "Storm.dll";

private:
	void LoadD2Common();
};