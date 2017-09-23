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

class D2Client : public Library<D2Client>
{
public:
	static void Init();

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
	typedef DWORD(__fastcall *TD2isLODGame) ();

	// Until 1.10
	typedef BYTE(__fastcall *TD2GetDifficultyLevel) ();
	typedef DWORD(__stdcall *TD2GetMouseX) ();
	typedef DWORD(__stdcall *TD2GetMouseY) ();
	typedef Unit* (__stdcall *TD2GetClientPlayer) ();
	typedef void(__fastcall *TD2CleanStatMouseUp) ();
	typedef void(__fastcall *TD2SendToServer3) (BYTE type, WORD p);

	static TD2LoadImage D2LoadImage();
	static TD2FreeImage D2FreeImage();
	static TD2SendMsgToAll D2SendMsgToAll();
	static TD2GetLastMonsterIDFight D2GetLastMonsterIDFight;
	static TD2PrintStatsPage D2PrintStatsPage;
	static TD2PrintStat D2PrintStat();
	static TD2SetColorPopup D2SetColorPopup();
	static TD2PlaySound D2PlaySound();
	static TD2SendToServerXX D2SendToServerXX;
	static TD2TogglePage D2TogglePage;
	static TD2ClickOnStashButton D2ClickOnStashButton;
	static TD2LoadBuySelBtn D2LoadBuySelBtn;
	static TD2isLODGame IsExpansion();

	static TD2GetDifficultyLevel D2GetDifficultyLevel();
	static TD2GetMouseX D2GetMouseX();
	static TD2GetMouseY D2GetMouseY();
	static TD2GetClientPlayer D2GetClientPlayer();
	static TD2CleanStatMouseUp D2CleanStatMouseUp;
	static TD2SendToServer3 D2SendToServer3();

	static DWORD ResolutionX();
	static DWORD ResolutionY();

	// Variables
	static DWORD* ptResolutionY;
	static DWORD* ptResolutionX;
	static DWORD* ptNegWindowStartY;
	static DWORD* ptWindowStartX;
	static BYTE* ptDifficultyLevel;
	static DWORD* ptMouseY;
	static DWORD* ptMouseX;
	static Unit** ptptClientChar;
	static DWORD* ptNbStatDesc;
	static DWORD* ptStatDescTable;

	static WORD GetDescStrPos(DWORD statID);
private:
	static void SetFunctions();

	// C++ ISO Standards prohibit using a pointer-to-member address as a way to access the function in the instance.
	// There are workarounds available (static functions being one (They are essentially the same as non-member functions)
	// and the other workaround is to have a regular non-member (top level/non-class) function and then inside that function
	// we call our real instanced based member function. I'm going with this approach.
	// More info here: https://isocpp.org/wiki/faq/pointers-to-members#fnptr-vs-memfnptr-types
	static DWORD* StatMouse1;
	static DWORD* StatMouse2;
	static DWORD* StatMouse3;
	static DWORD* StatMouse4;

	static DWORD GetStatDescIDFrom(DWORD statID);
	static WORD GetDescStrPos_10(DWORD statID);
	static WORD GetDescStrPos_9(DWORD statID);

	static DWORD __fastcall D2PrintStat_9(Unit* ptItem, Stats* ptStats, DWORD statID, DWORD statIndex, DWORD statValue, LPWSTR lpText);

	static TD2PrintStat D2PrintStatDirect;
	static TD2SendMsgToAll D2SendMsgToAllDirect;
	static TD2SetColorPopup D2SetColorPopupDirect;
	static TD2LoadImage D2LoadImageDirect;
	static const char* D2Client::D2FreeImage_FILE;
	static TD2PlaySound D2PlaySoundDirect;

	// Remove these since they will no longer be called
	static void __fastcall D2CleanStatMouseUp_111();
	static BYTE __fastcall D2GetDifficultyLevel_111();
	static DWORD __stdcall	D2GetMouseX_111();
	static DWORD __stdcall	D2GetMouseY_111();
	static Unit* __stdcall	D2GetClientPlayer_111();
	static void D2SendMsgToAll_111();
	static DWORD __fastcall D2isLODGame_111();
	static void D2SetColorPopup_111();
	static void D2LoadImage_111();
	static void D2FreeImage_111();
	static void D2PlaySound_111();
	static void D2SendToServer3_111();
	static void D2PrintStat_111();
};