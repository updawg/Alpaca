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
	D2PrintStatsPage = (TD2PrintStatsPage)GetOffsetByAddition(0x29800);
	D2SetColorPopup = (TD2SetColorPopup)GetOffsetByAddition(0x85A60);
	D2TogglePage = (TD2TogglePage)GetOffsetByAddition(0x88940);
	D2LoadBuySelBtn = (TD2LoadBuySelBtn)GetOffsetByAddition(0x897B0);
	D2SendMsgToAll = (TD2SendMsgToAll)GetOffsetByAddition(0xD640);
	D2CleanStatMouseUp = (TD2CleanStatMouseUp)GetOffsetByAddition(0xB920);
	D2GetClientPlayer = (TD2GetClientPlayer)GetOffsetByAddition(0x8DC40);
	D2LoadImage = (TD2LoadImage)GetOffsetByAddition(0x1000);
	D2PlaySound = (TD2PlaySound)GetOffsetByAddition(0xB4360);
	IsExpansion = (TD2isLODGame)GetOffsetByAddition(0xBA00);
	D2FreeImage = (TD2FreeImage)GetOffsetByAddition(0x1150);
	D2SendToServer3 = (TD2SendToServer3)GetOffsetByAddition(0xD210);
	D2GetMouseX = (TD2GetMouseX)GetOffsetByAddition(0xB6670);
	D2GetMouseY = (TD2GetMouseY)GetOffsetByAddition(0xB6680);
	D2PrintStat = (TD2PrintStat)D2PrintStat_9;
	D2PrintStatDirect = (TD2PrintStat)GetOffsetByAddition(0x4BB20);

	// Variables
	ptResolutionY = (DWORD*)GetOffsetByAddition(0xD50E8);
	ptResolutionX = (DWORD*)GetOffsetByAddition(0xD50EC);
	ptNegWindowStartY = (DWORD*)GetOffsetByAddition(0x125AD8);
	ptWindowStartX = (DWORD*)GetOffsetByAddition(0x125AD4);

	ptNbStatDesc = (DWORD*)GetOffsetByAddition(0xDB918);
	ptStatDescTable = (DWORD*)GetOffsetByAddition(0xDAF98);

	CustomCommandOffset = GetOffsetByAddition(0x2C120);
}

DWORD D2Client::ResolutionX()
{
	return *ptResolutionX;
}

DWORD D2Client::ResolutionY()
{
	return *ptResolutionY;
}

DWORD __fastcall D2Client::D2PrintStat_9(Unit* ptItem, Stats* ptStats, DWORD statID, DWORD statIndex, DWORD statValue, LPWSTR lpText)
{
	DWORD curDesc = GetStatDescIDFrom(statID);
	if (curDesc < *ptNbStatDesc)
		return D2PrintStatDirect(ptItem, (Stats*)curDesc, statValue, 0, 0, lpText);
	return 0;
}

DWORD D2Client::GetStatDescIDFrom(DWORD statID)
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
	DWORD* desc = &ptStatDescTable[GetStatDescIDFrom(statID) * 4];
	return (WORD)*(desc + 2);
}

D2Client::TD2PrintStat D2Client::D2PrintStat;
D2Client::TD2isLODGame D2Client::IsExpansion;
D2Client::TD2SendMsgToAll D2Client::D2SendMsgToAll;
D2Client::TD2SetColorPopup D2Client::D2SetColorPopup;
D2Client::TD2LoadImage D2Client::D2LoadImage;
D2Client::TD2FreeImage D2Client::D2FreeImage;
D2Client::TD2PlaySound D2Client::D2PlaySound;
D2Client::TD2SendToServer3 D2Client::D2SendToServer3;
D2Client::TD2GetMouseX D2Client::D2GetMouseX;
D2Client::TD2GetMouseY D2Client::D2GetMouseY;
D2Client::TD2GetClientPlayer D2Client::D2GetClientPlayer;
D2Client::TD2PrintStatsPage D2Client::D2PrintStatsPage;
D2Client::TD2TogglePage D2Client::D2TogglePage;
D2Client::TD2LoadBuySelBtn D2Client::D2LoadBuySelBtn;
D2Client::TD2CleanStatMouseUp D2Client::D2CleanStatMouseUp;
D2Client::TD2PrintStat D2Client::D2PrintStatDirect;

DWORD* D2Client::ptResolutionY;
DWORD* D2Client::ptResolutionX;
DWORD* D2Client::ptNegWindowStartY;
DWORD* D2Client::ptWindowStartX;

DWORD* D2Client::ptNbStatDesc;
DWORD* D2Client::ptStatDescTable;

DWORD D2Client::CustomCommandOffset;