// Copyright (C) 2004-2017  Yohann Nicolas
// Copyright (C) 2017 L'Autour
// Copyright (C) 2017 Jonathan Vasquez <jon@xyinn.org>
//
// This program is free software : you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.

#pragma once

#include "Library.h"

class D2ClientLibrary : public Library
{
public:
	D2ClientLibrary(int gameVersion) : Library()
	{
		DllName = "D2Client.dll";
		DllVersion = gameVersion;
		DllOffset = LoadDiabloLibrary();
		SetFunctions();

		// These need to be initialized here, they cannot be inlined in the variable declaration
		// because they would be initialized before the class was able to set the DllVersion variable
		// which are used in the GetOffsetForVersion function.
		DisplayBaseStatsBaseOffset1 = GetOffsetByAddition(0x29B12, 0x29B02, 0x30073, 0x82BBA, 0x8963A, 0x6B59A, 0xBD1B5, 0xBF955);
		DisplayBaseStatsBaseOffset2 = GetOffsetByAddition(0x29B9D, 0x29B8D, 0x300FD, 0x82C54, 0x896D4, 0x6B637, 0xBD23E, 0xBF9DE);
		DisplayBaseStatsModOffset1 = (BYTE)GetOffsetForVersion(0x12, 0x12, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13);
		DisplayBaseStatsModOffset2 = (BYTE)GetOffsetForVersion(0x20, 0x20, 0x14, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C);
	};

	DWORD RetrieveStashBackgroundOffset();

	// Stat Button Related Functions
	DWORD DisplayBaseStatsBaseOffset1;
	DWORD DisplayBaseStatsBaseOffset2;
	BYTE DisplayBaseStatsModOffset1;
	BYTE DisplayBaseStatsModOffset2;

	// Types
	typedef void* (__fastcall *TD2LoadImage) (const char* filename, DWORD filetype);
	typedef void(__fastcall *TD2FreeImage) (void* image);
	typedef void(__fastcall *TD2SendMsgToAll) (BYTE* data);
	typedef DWORD(__stdcall *TD2GetLastMonsterIDFight) ();
	typedef void(__stdcall *TD2PrintStatsPage) ();
	typedef DWORD(__fastcall *TD2PrintStat) (Unit* ptItem, Stats* ptStats, DWORD statID, DWORD statIndex, DWORD statValue, LPWSTR lpText);
	typedef LPWSTR(__fastcall *TD2SetColorPopup) (LPWSTR popupText, DWORD color);
	typedef DWORD(__fastcall *TD2PlaySound) (DWORD id, DWORD, DWORD, DWORD, DWORD);
	typedef Unit* (__fastcall *TD2GetCurrentNPC) ();
	typedef void(__fastcall *TD2SendToServerXX) (DWORD size, BYTE * data);
	typedef void(__fastcall *TD2TogglePage) (DWORD a, DWORD b, DWORD c);
	typedef void(__fastcall *TD2ClickOnStashButton) (DWORD x, DWORD y);
	typedef void* (__stdcall *TD2LoadBuySelBtn) ();
	typedef void(__fastcall *TD2ReloadGambleScreen) ();

	TD2LoadImage D2LoadImage;
	TD2FreeImage D2FreeImage;
	TD2SendMsgToAll D2SendMsgToAll;
	TD2GetLastMonsterIDFight D2GetLastMonsterIDFight;
	TD2PrintStatsPage D2PrintStatsPage;
	TD2PrintStat D2PrintStat;
	TD2SetColorPopup D2SetColorPopup;
	TD2PlaySound D2PlaySound;
	TD2GetCurrentNPC D2GetCurrentNPC;
	TD2SendToServerXX D2SendToServerXX;
	TD2TogglePage D2TogglePage;
	TD2ClickOnStashButton D2ClickOnStashButton;
	TD2LoadBuySelBtn D2LoadBuySelBtn;
	TD2ReloadGambleScreen D2ReloadGambleScreen;

	// Until 1.10
	typedef DWORD(__fastcall *TD2isLODGame) ();
	typedef BYTE(__fastcall *TD2GetDifficultyLevel) ();
	typedef DWORD(__stdcall *TD2GetMouseX) ();
	typedef DWORD(__stdcall *TD2GetMouseY) ();
	typedef Unit* (__stdcall *TD2GetClientPlayer) ();
	typedef void(__fastcall *TD2CleanStatMouseUp) ();
	typedef void(__fastcall *TD2SendToServer3) (BYTE type, WORD p);

	TD2isLODGame D2isLODGame;
	TD2GetDifficultyLevel D2GetDifficultyLevel;
	TD2GetMouseX D2GetMouseX;
	TD2GetMouseY D2GetMouseY;
	TD2GetClientPlayer D2GetClientPlayer;
	TD2CleanStatMouseUp D2CleanStatMouseUp;
	TD2SendToServer3 D2SendToServer3;

	// Variables
	DWORD* ptResolutionY;
	DWORD* ptResolutionX;
	DWORD* ptNegWindowStartY;
	DWORD* ptWindowStartX;
	DWORD* ptIsLodGame;
	BYTE* ptDifficultyLevel;
	DWORD* ptMouseY;
	DWORD* ptMouseX;
	Unit** ptptClientChar;
	DWORD* ptNbStatDesc;
	DWORD* ptStatDescTable;
private:
	void SetFunctions();
};
