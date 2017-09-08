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

#include "D2ClientLibrary.h"

D2ClientLibrary::D2ClientLibrary(int gameVersion) : Library()
{
	Name = "D2Client.dll";
	Version = gameVersion;
	Offset = LoadDiabloLibrary();
	SetFunctions();
}

void D2ClientLibrary::SetFunctions()
{
	D2LoadImage = (TD2LoadImage)GetOffsetByAddition(0x1000, 0xA9480);
	D2FreeImage = (TD2FreeImage)GetOffsetByAddition(0x1150, 0);
	D2SendMsgToAll = (TD2SendMsgToAll)GetOffsetByAddition(0xD640, 0xB6890);
	D2GetLastMonsterIDFight = (TD2GetLastMonsterIDFight)GetOffsetByAddition(0, 0);
	D2PrintStatsPage = (TD2PrintStatsPage)GetOffsetByAddition(0x29800, 0xBF640);
	D2PrintStat = (TD2PrintStat)GetOffsetByAddition(0x4BB20, 0x2CE40);
	D2SetColorPopup = (TD2SetColorPopup)GetOffsetByAddition(0x85A60, 0x18820);
	D2PlaySound = (TD2PlaySound)GetOffsetByAddition(0xB4360, 0x26270);
	D2SendToServerXX = (TD2SendToServerXX)GetOffsetByAddition(0, 0xB61F0);
	D2TogglePage = (TD2TogglePage)GetOffsetByAddition(0x88940, 0x1C190);
	D2ClickOnStashButton = (TD2ClickOnStashButton)GetOffsetByAddition(0, 0x90C10);
	D2LoadBuySelBtn = (TD2LoadBuySelBtn)GetOffsetByAddition(0x897B0, 0x18AA0);
	
	// Until 1.10
	D2isLODGame = (TD2isLODGame)GetOffsetByAddition(0xBA00, 0);
	D2GetDifficultyLevel = (TD2GetDifficultyLevel)GetOffsetByAddition(0, 0);
	D2GetMouseX = (TD2GetMouseX)GetOffsetByAddition(0xB6670, 0);
	D2GetMouseY = (TD2GetMouseY)GetOffsetByAddition(0xB6680, 0);
	D2GetClientPlayer = (TD2GetClientPlayer)GetOffsetByAddition(0x8DC40, 0);
	D2CleanStatMouseUp = GetD2CleanStatMouseUp();
	D2SendToServer3 = (TD2SendToServer3)GetOffsetByAddition(0xD210, 0);

	// Variables
	ptResolutionY = (DWORD*)GetOffsetByAddition(0xD50E8, 0xF7038);
	ptResolutionX = (DWORD*)GetOffsetByAddition(0xD50EC, 0xF7034);
	ptNegWindowStartY = (DWORD*)GetOffsetByAddition(0x125AD8, 0x11D358);
	ptWindowStartX = (DWORD*)GetOffsetByAddition(0x125AD4, 0x11D354);
	ptIsLodGame = (DWORD*)GetOffsetByAddition(0, 0x1087B4);
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
}

DWORD* D2ClientLibrary::StatMouse1;
DWORD* D2ClientLibrary::StatMouse2;
DWORD* D2ClientLibrary::StatMouse3;
DWORD* D2ClientLibrary::StatMouse4;

void __fastcall D2ClientLibrary::D2CleanStatMouseUp_111()
{
	*StatMouse1 = 0;
	*StatMouse2 = 0;
	*StatMouse3 = 0;
	*StatMouse4 = 0;
}

D2ClientLibrary::TD2CleanStatMouseUp D2ClientLibrary::GetD2CleanStatMouseUp()
{
	DWORD location;

	if (Version >= VersionUtility::Versions::V111)
	{
		location = (DWORD)&D2ClientLibrary::D2CleanStatMouseUp_111;
	}
	else
	{
		location = GetOffsetByAddition(0xB920, 0);
	}

	return (TD2CleanStatMouseUp)location;
}