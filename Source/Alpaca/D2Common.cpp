// Copyright (C) 2004-2017 Yohann Nicolas
// Copyright (C) 2017-2018 Jonathan Vasquez <jon@xyinn.org>
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

#include "D2Common.h"
#include "Fog.h"

void D2Common::Init()
{
	Name = "D2Common.dll";
	Offset = LoadDiabloLibrary();
	SetFunctions();
}

void D2Common::SetFunctions()
{
	D2InvAddItem = (TD2InvAddItem)GetAddress(0x3B640);
	D2InvRemoveItem = (TD2InvRemoveItem)GetAddress(0x3B370);
	D2InventoryGetFirstItem = (TD2InventoryGetFirstItem)GetAddress(0x37A00);
	D2UnitGetNextItem = (TD2UnitGetNextItem)GetAddress(0x38160);
	D2InitPlayerData = (TD2InitPlayerData)GetAddress(0x17090);
	D2GetPlayerData = (TD2GetPlayerData)GetAddress(0x153D0);
	D2ItemSetPage = (TD2ItemSetPage)GetAddress(0x42060);
	D2ItemGetPage = (TD2ItemGetPage)GetAddress(0x42080);
	D2SaveItem = (TD2SaveItem)GetAddress(0x485C0);
	D2GetItemLevel = (TD2GetItemLevel)GetAddress(0x420D0);
	D2GetRealItem = (TD2GetRealItem)D2GetRealItem_111;
	D2CompileTxtFile = (TD2CompileTxtFile)GetAddress(0xCAE0);
	D2GetItemQuality = (TD2GetItemQuality)GetAddress(0x42400);
	D2GetUniqueID = (TD2GetUniqueID)GetAddress(0x40F00);
	D2GetItemsBIN = (TD2GetItemsBIN)GetAddress(0x62C70);
	D2CanPutItemInInv = (TD2CanPutItemInInv)GetAddress(0x3B680);

	// Variables: Structure Management [Offset]
	ptPYPlayerDataOffset = 0x49;
	ptSpecificDataOffset = 0x14;
	ptGameOffset = 0x80;
	ptClientGameOffset = 0x1A8;
	ptInventoryOffset = 0x60;
	ptSkillsOffset = 0xA8;
	ptImageOffset = 0x34;
	ptFrameOffset = 0x0;

	SgptDataTablesOffset = GetAddress(0xA33F0);
}

DataTables* D2Common::GetDataTables()
{
	return *(DataTables**)D2Common::SgptDataTablesOffset;
}

Unit* __stdcall	D2Common::D2GetRealItem_111(Unit* ptItem)
{
	return ptItem;
}

DWORD D2Common::ptPYPlayerDataOffset;
DWORD D2Common::ptSpecificDataOffset;
DWORD D2Common::ptGameOffset;
DWORD D2Common::ptClientGameOffset;
DWORD D2Common::ptInventoryOffset;
DWORD D2Common::ptSkillsOffset;
DWORD D2Common::ptImageOffset;
DWORD D2Common::ptFrameOffset;
DWORD D2Common::SgptDataTablesOffset;

D2Common::TD2GetRealItem D2Common::D2GetRealItem;
D2Common::TD2InvAddItem D2Common::D2InvAddItem;
D2Common::TD2InvRemoveItem D2Common::D2InvRemoveItem;
D2Common::TD2InventoryGetFirstItem D2Common::D2InventoryGetFirstItem;
D2Common::TD2UnitGetNextItem D2Common::D2UnitGetNextItem;
D2Common::TD2InitPlayerData D2Common::D2InitPlayerData;
D2Common::TD2GetPlayerData D2Common::D2GetPlayerData;
D2Common::TD2CompileTxtFile D2Common::D2CompileTxtFile;
D2Common::TD2GetItemQuality D2Common::D2GetItemQuality;
D2Common::TD2GetUniqueID D2Common::D2GetUniqueID;
D2Common::TD2GetItemsBIN D2Common::D2GetItemsBIN;
D2Common::TD2ItemSetPage D2Common::D2ItemSetPage;
D2Common::TD2ItemGetPage D2Common::D2ItemGetPage;
D2Common::TD2SaveItem D2Common::D2SaveItem;
D2Common::TD2GetItemLevel D2Common::D2GetItemLevel;
D2Common::TD2CanPutItemInInv D2Common::D2CanPutItemInInv;