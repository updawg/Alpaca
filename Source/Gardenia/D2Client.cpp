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

#include "D2Client.h"
#include "D2Common.h"
#include "D2CMP.h"
#include "Fog.h"

void D2Client::Init()
{
	Name = "D2Client.dll";
	Offset = LoadDiabloLibrary();
	SetFunctions();
}

void D2Client::SetFunctions()
{
	D2GetLastMonsterIDFight = (TD2GetLastMonsterIDFight)GetOffsetByAddition(0, 0);
	D2PrintStatsPage = (TD2PrintStatsPage)GetOffsetByAddition(0x29800, 0xBF640);
	D2SetColorPopupDirect = (TD2SetColorPopup)GetOffsetByAddition(0x85A60, 0x18820);
	D2SendToServerXX = (TD2SendToServerXX)GetOffsetByAddition(0, 0xB61F0);
	D2TogglePage = (TD2TogglePage)GetOffsetByAddition(0x88940, 0x1C190);
	D2ClickOnStashButton = (TD2ClickOnStashButton)GetOffsetByAddition(0, 0x90C10);
	D2LoadBuySelBtn = (TD2LoadBuySelBtn)GetOffsetByAddition(0x897B0, 0x18AA0);
	D2SendMsgToAllDirect = (TD2SendMsgToAll)GetOffsetByAddition(0xD640, 0xB6890);

	// Variables
	ptResolutionY = (DWORD*)GetOffsetByAddition(0xD50E8, 0xF7038);
	ptResolutionX = (DWORD*)GetOffsetByAddition(0xD50EC, 0xF7034);
	ptNegWindowStartY = (DWORD*)GetOffsetByAddition(0x125AD8, 0x11D358);
	ptWindowStartX = (DWORD*)GetOffsetByAddition(0x125AD4, 0x11D354);
	ptDifficultyLevel = (BYTE*)GetOffsetByAddition(0, 0);
	ptMouseY = (DWORD*)GetOffsetByAddition(0, 0x11C94C);
	ptMouseX = (DWORD*)GetOffsetByAddition(0, 0x11C950);
	ptptClientChar = (Unit**)GetOffsetByAddition(0, 0x11D050);
	ptNbStatDesc = (DWORD*)GetOffsetByAddition(0xDB918, 0);
	ptStatDescTable = (DWORD*)GetOffsetByAddition(0xDAF98, 0);

	StatMouse1 = (DWORD*)GetOffsetByAddition(0, 0x11D224);
	StatMouse2 = (DWORD*)GetOffsetByAddition(0, 0x11D228);
	StatMouse3 = (DWORD*)GetOffsetByAddition(0, 0x11D240);
	StatMouse4 = (DWORD*)GetOffsetByAddition(0, 0x11D244);

	D2PrintStatDirect = (TD2PrintStat)GetOffsetByAddition(0x4BB20, 0x2CE40);
	D2LoadImageDirect = (TD2LoadImage)GetOffsetByAddition(0x1000, 0xA9480);
	D2PlaySoundDirect = (TD2PlaySound)GetOffsetByAddition(0xB4360, 0x26270);
}

DWORD D2Client::ResolutionX()
{
	return *ptResolutionX;
}

DWORD D2Client::ResolutionY()
{
	return *ptResolutionY;
}

void __fastcall D2Client::D2CleanStatMouseUp_111()
{
	*StatMouse1 = 0;
	*StatMouse2 = 0;
	*StatMouse3 = 0;
	*StatMouse4 = 0;
}

D2Client::TD2CleanStatMouseUp D2Client::D2CleanStatMouseUp()
{
	DWORD location;

	if (VersionUtility::Is113D())
	{
		location = (DWORD)&D2Client::D2CleanStatMouseUp_111;
	}
	else
	{
		location = GetOffsetByAddition(0xB920, 0);
	}

	return (TD2CleanStatMouseUp)location;
}

D2Client::TD2PrintStat D2Client::D2PrintStat()
{
	if (VersionUtility::Is113D())
	{
		return (TD2PrintStat)D2PrintStat_111;
	}
	else
	{
		return (TD2PrintStat)D2PrintStat_9;
	}
}

__declspec(naked) void D2Client::D2PrintStat_111()
{
	__asm {
		PUSH ESI
		MOV ESI, DWORD PTR SS : [ESP + 0x14]
		MOV EAX, DWORD PTR SS : [ESP + 0x08]
		PUSH DWORD PTR SS : [ESP + 0x10]
		PUSH DWORD PTR SS : [ESP + 0x10]
		PUSH EDX
		PUSH ECX
		CALL D2PrintStatDirect
		POP ESI
		RETN 0x10
	}
}

DWORD __fastcall D2Client::D2PrintStat_9(Unit* ptItem, Stats* ptStats, DWORD statID, DWORD statIndex, DWORD statValue, LPWSTR lpText)
{
	DWORD curDesc = GetStatDescIDFrom(statID);
	if (curDesc < *ptNbStatDesc)
		return D2PrintStatDirect(ptItem, (Stats*)curDesc, statValue, 0, 0, lpText);
	return 0;
}

DWORD D2Client::GetStatDescIDFrom(DWORD statID) //FOR 1.09
{
	DWORD* desc = ptStatDescTable;
	DWORD curDesc = 0;
	while (curDesc < *ptNbStatDesc)
	{
		if (*desc == statID)
			return curDesc;
		desc += 4;
		curDesc++;
	}
	return curDesc;
}

WORD D2Client::GetDescStrPos(DWORD statID)
{
	if (VersionUtility::Is113D())
	{
		return GetDescStrPos_10(statID);
	}
	else
	{
		return GetDescStrPos_9(statID);
	}
}

WORD D2Client::GetDescStrPos_10(DWORD statID)
{
ItemStatCostBIN* itemStatCost = D2Common::D2GetItemStatCostBIN()(statID);
return itemStatCost->descstrpos;
}

WORD D2Client::GetDescStrPos_9(DWORD statID)
{
	DWORD* desc = &ptStatDescTable[GetStatDescIDFrom(statID) * 4];
	return (WORD)*(desc + 2);
}

D2Client::TD2isLODGame D2Client::IsExpansion()
{
	if (VersionUtility::Is113D())
	{
		return (TD2isLODGame)D2isLODGame_111;
	}
	else
	{
		return (TD2isLODGame)GetOffsetByAddition(0xBA00, 0);
	}
}

DWORD __fastcall D2Client::D2isLODGame_111()
{
	DWORD* func = (DWORD*)GetOffsetByAddition(0, 0x1087B4);
	return *func;
}

D2Client::TD2SendMsgToAll D2Client::D2SendMsgToAll()
{
	if (VersionUtility::Is113D())
	{
		return (TD2SendMsgToAll)D2SendMsgToAll_111;
	}
	else
	{
		return D2SendMsgToAllDirect;
	}
}

__declspec(naked) void D2Client::D2SendMsgToAll_111()
{
	__asm {
		PUSH ESI
		MOV ESI, ECX
		CALL D2SendMsgToAllDirect
		POP ESI
		RETN
	}
}

D2Client::TD2SetColorPopup D2Client::D2SetColorPopup()
{
	if (VersionUtility::Is113D())
	{
		return (TD2SetColorPopup)D2SetColorPopup_111;
	}
	else
	{
		return D2SetColorPopupDirect;
	}
}

__declspec(naked) void D2Client::D2SetColorPopup_111()
{
	__asm {
		PUSH EDI
		PUSH EDX
		MOV EDI, ECX
		CALL D2SetColorPopupDirect
		POP EDI
		RETN
	}
}

D2Client::TD2LoadImage D2Client::D2LoadImage()
{
	if (VersionUtility::Is113D())
	{
		return (TD2LoadImage)D2LoadImage_111;
	}
	else
	{
		return D2LoadImageDirect;
	}
}

__declspec(naked) void D2Client::D2LoadImage_111()
{
	__asm {
		PUSH EDX
		MOV EAX, ECX
		CALL D2LoadImageDirect
		RETN
	}
}

D2Client::TD2FreeImage D2Client::D2FreeImage()
{
	if (VersionUtility::Is113D())
	{
		return (TD2FreeImage)D2FreeImage_111;
	}
	else
	{
		return (TD2FreeImage)GetOffsetByAddition(0x1150, 0);
	}
}

const char* D2Client::D2FreeImage_FILE = __FILE__;
__declspec(naked) void D2Client::D2FreeImage_111()
{
	__asm {
		PUSH ESI
		MOV ESI,ECX
		PUSH ESI
		CALL D2CMP::D2CMP10014
		TEST ESI,ESI
		JE END_D2Free
		PUSH 0
		PUSH __LINE__
		MOV EDX,D2FreeImage_FILE;  ASCII "C:\projects\D2\head\Diablo2\Source\D2Client\CORE\ARCHIVE.CPP"
		MOV ECX,ESI
		CALL Fog::D2FogMemDeAlloc
		END_D2Free :
		POP ESI
		RETN
	}
}

D2Client::TD2PlaySound D2Client::D2PlaySound()
{
	if (VersionUtility::Is113D())
	{
		return (TD2PlaySound)D2PlaySound_111;
	}
	else
	{
		return D2PlaySoundDirect;
	}
}

__declspec(naked) void D2Client::D2PlaySound_111()
{
	__asm {
		PUSH EBX
		PUSH DWORD PTR SS : [ESP + 0x10]
		PUSH DWORD PTR SS : [ESP + 0x10]
		PUSH DWORD PTR SS : [ESP + 0x10]
		PUSH EDX
		MOV EBX,ECX
		CALL D2PlaySoundDirect
		POP EBX
		RETN 0xC
	}
}

D2Client::TD2SendToServer3 D2Client::D2SendToServer3()
{
	if (VersionUtility::Is113D())
	{
		return (TD2SendToServer3)D2SendToServer3_111;
	}
	else
	{
		return (TD2SendToServer3)GetOffsetByAddition(0xD210, 0);
	}
}

__declspec (naked) void D2Client::D2SendToServer3_111()
{
	__asm {
		PUSH EBX
		PUSH ECX
		MOV BYTE PTR SS : [ESP], CL
		MOV WORD PTR SS : [ESP + 1], DX
		MOV EBX, 3
		LEA EDX, DWORD PTR SS : [ESP]
		PUSH EDX
		CALL D2SendToServerXX
		POP ECX
		POP EBX
		RETN
	}
}

D2Client::TD2GetDifficultyLevel D2Client::D2GetDifficultyLevel()
{
	if (VersionUtility::Is113D())
	{
		return (TD2GetDifficultyLevel)D2GetDifficultyLevel_111;
	}
	else
	{
		return (TD2GetDifficultyLevel)GetOffsetByAddition(0, 0);
	}
}

BYTE __fastcall D2Client::D2GetDifficultyLevel_111()
{
	return *ptDifficultyLevel;
}

D2Client::TD2GetMouseX D2Client::D2GetMouseX()
{
	if (VersionUtility::Is113D())
	{
		return (TD2GetMouseX)D2GetMouseX_111;
	}
	else
	{
		return (TD2GetMouseX)GetOffsetByAddition(0xB6670, 0);
	}
}

DWORD __stdcall	D2Client::D2GetMouseX_111()
{
	return *ptMouseX;
}

D2Client::TD2GetMouseY D2Client::D2GetMouseY()
{
	if (VersionUtility::Is113D())
	{
		return (TD2GetMouseY)D2GetMouseY_111;
	}
	else
	{
		return (TD2GetMouseY)GetOffsetByAddition(0xB6680, 0);
	}
}

DWORD __stdcall	D2Client::D2GetMouseY_111()
{
	return *ptMouseY;
}

D2Client::TD2GetClientPlayer D2Client::D2GetClientPlayer()
{
	if (VersionUtility::Is113D())
	{
		return (TD2GetClientPlayer)D2GetClientPlayer_111;
	}
	else
	{
		return (TD2GetClientPlayer)GetOffsetByAddition(0x8DC40, 0);
	}
}

Unit* __stdcall	D2Client::D2GetClientPlayer_111()
{
	return *ptptClientChar;
}

D2Client::TD2GetLastMonsterIDFight D2Client::D2GetLastMonsterIDFight;
D2Client::TD2PrintStatsPage D2Client::D2PrintStatsPage;
D2Client::TD2SendToServerXX D2Client::D2SendToServerXX;
D2Client::TD2TogglePage D2Client::D2TogglePage;
D2Client::TD2ClickOnStashButton D2Client::D2ClickOnStashButton;
D2Client::TD2LoadBuySelBtn D2Client::D2LoadBuySelBtn;

DWORD* D2Client::ptResolutionY;
DWORD* D2Client::ptResolutionX;
DWORD* D2Client::ptNegWindowStartY;
DWORD* D2Client::ptWindowStartX;
BYTE* D2Client::ptDifficultyLevel;
DWORD* D2Client::ptMouseY;
DWORD* D2Client::ptMouseX;
Unit** D2Client::ptptClientChar;
DWORD* D2Client::ptNbStatDesc;
DWORD* D2Client::ptStatDescTable;

DWORD* D2Client::StatMouse1;
DWORD* D2Client::StatMouse2;
DWORD* D2Client::StatMouse3;
DWORD* D2Client::StatMouse4;

D2Client::TD2PrintStat D2Client::D2PrintStatDirect;
D2Client::TD2SendMsgToAll D2Client::D2SendMsgToAllDirect;
D2Client::TD2SetColorPopup D2Client::D2SetColorPopupDirect;
D2Client::TD2LoadImage D2Client::D2LoadImageDirect;
D2Client::TD2PlaySound D2Client::D2PlaySoundDirect;