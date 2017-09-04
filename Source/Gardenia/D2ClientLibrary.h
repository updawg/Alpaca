// Copyright (C) 2004-2017 Yohann Nicolas
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
	D2ClientLibrary(int gameVersion);

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

	// C++ ISO Standards prohibit using a pointer-to-member address as a way to access the function in the instance.
	// There are workarounds available (static functions being one (They are essentially the same as non-member functions)
	// and the other workaround is to have a regular non-member (top level/non-class) function and then inside that function
	// we call our real instanced based member function. I'm going with this approach.
	// More info here: https://isocpp.org/wiki/faq/pointers-to-members#fnptr-vs-memfnptr-types
	static DWORD* StatMouse1;
	static DWORD* StatMouse2;
	static DWORD* StatMouse3;
	static DWORD* StatMouse4;

	static void __fastcall D2CleanStatMouseUp_111();
private:
	void SetFunctions();

	// Redirected Functions
	TD2CleanStatMouseUp GetD2CleanStatMouseUp();
};
