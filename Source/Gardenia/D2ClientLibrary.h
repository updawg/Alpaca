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

		ResetSelectedPageBaseOffset1 = GetOffsetByAddition(0, 0, 0, 0x4B79E, 0x8F73E, 0x55E0E, 0x65F5E, 0xC41FE);
		ResetSelectedPageBaseOffset2 = GetOffsetByAddition(0, 0, 0, 0x1E55A, 0x6A8FA, 0xA31DA, 0x3C5EA, 0x3E39A);
		ResetSelectedPageBaseOffset3 = GetOffsetByAddition(0x88B58, 0x87ED8, 0x83478, 0xA1FBE, 0x6571E, 0x8EF8E, 0, 0);
		PrintCustomPageBaseOffset = GetOffsetByAddition(0x87697, 0x86A17, 0x81FAB, 0xA3759, 0x66B59, 0x902B9, 0xC3B49, 0x1D549);
		DontPrintBorderBaseOffset = GetOffsetByAddition(0x58EF6, 0x58EF6, 0x5F4C6, 0x2D366, 0xB5A46, 0x82166, 0x271C6, 0x6D2B6);
		ManageMouseDownBaseOffset = GetOffsetByAddition(0x2A9DC, 0x2A9CC, 0x312A5, 0x82736, 0x891B6, 0x6B116, 0xBCD36, 0xBF4D6);
		ManageMouseUpBaseOffset = GetOffsetByAddition(0x2ABBB, 0x2ABAB, 0x3148D, 0x836D9, 0x8A159, 0x6C0B9, 0xBDCB9, 0xC0459);
	};

	DWORD RetrieveStashBackgroundOffset();

	// Stat Button Related Functions
	DWORD DisplayBaseStatsBaseOffset1;
	DWORD DisplayBaseStatsBaseOffset2;
	BYTE DisplayBaseStatsModOffset1;
	BYTE DisplayBaseStatsModOffset2;

	DWORD ResetSelectedPageBaseOffset1;
	DWORD ResetSelectedPageBaseOffset2;
	DWORD ResetSelectedPageBaseOffset3;

	DWORD PrintCustomPageBaseOffset;
	DWORD DontPrintBorderBaseOffset;
	DWORD ManageMouseDownBaseOffset; // Play Sound
	DWORD ManageMouseUpBaseOffset;

	// Types
	typedef void* (__fastcall *TD2LoadImage) (const char* filename, DWORD filetype);
	typedef void(__fastcall *TD2FreeImage) (void* image);
	typedef void(__fastcall *TD2SendMsgToAll) (BYTE* data);
	typedef DWORD(__stdcall *TD2GetLastMonsterIDFight) ();
	typedef void(__stdcall *TD2PrintStatsPage) ();
	typedef DWORD(__fastcall *TD2PrintStat) (Unit* ptItem, Stats* ptStats, DWORD statID, DWORD statIndex, DWORD statValue, LPWSTR lpText);
	typedef LPWSTR(__fastcall *TD2SetColorPopup) (LPWSTR popupText, DWORD color);
	typedef DWORD(__fastcall *TD2PlaySound) (DWORD id, DWORD, DWORD, DWORD, DWORD);
	typedef void(__fastcall *TD2SendToServerXX) (DWORD size, BYTE * data);
	typedef void(__fastcall *TD2TogglePage) (DWORD a, DWORD b, DWORD c);
	typedef void(__fastcall *TD2ClickOnStashButton) (DWORD x, DWORD y);
	typedef void* (__stdcall *TD2LoadBuySelBtn) ();

	TD2LoadImage D2LoadImage;
	TD2FreeImage D2FreeImage;
	TD2SendMsgToAll D2SendMsgToAll;
	TD2GetLastMonsterIDFight D2GetLastMonsterIDFight;
	TD2PrintStatsPage D2PrintStatsPage;
	TD2PrintStat D2PrintStat;
	TD2SetColorPopup D2SetColorPopup;
	TD2PlaySound D2PlaySound;
	TD2SendToServerXX D2SendToServerXX;
	TD2TogglePage D2TogglePage;
	TD2ClickOnStashButton D2ClickOnStashButton;
	TD2LoadBuySelBtn D2LoadBuySelBtn;

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
