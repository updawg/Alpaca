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

#pragma once

#include "Library.h"

class D2Common : public Library<D2Common>
{
public:
	static void Init();

	typedef Unit* (__stdcall* TD2InvRemoveItem) (Inventory* ptInventory, Unit* ptItem);
	typedef DWORD(__stdcall* TD2InvAddItem) (Inventory* ptInventory, Unit* ptItem, DWORD posX, DWORD posY, DWORD vValueC, DWORD bIsClient, BYTE page);
	typedef Unit* (__stdcall* TD2InventoryGetFirstItem) (Inventory* ptInventory);
	typedef Unit* (__stdcall* TD2UnitGetNextItem) (Unit* ptItem);
	typedef Unit* (__stdcall* TD2GetRealItem) (Unit* ptUnit);
	typedef PlayerData* (__stdcall* TD2InitPlayerData) (Unit* ptChar);
	typedef PlayerData* (__stdcall* TD2GetPlayerData) (Unit* ptChar);
	typedef void* (__stdcall* TD2CompileTxtFile) (DWORD unused, const char* filename, BINField* ptFields, DWORD* ptRecordCount, DWORD recordLength);
	typedef void(__stdcall* TD2ItemSetPage) (Unit* ptItem, BYTE page);
	typedef BYTE(__stdcall* TD2ItemGetPage) (Unit* ptUnit);
	typedef DWORD(__stdcall* TD2SaveItem) (Unit* ptItem, saveBitField* data, DWORD startSize, DWORD p4, DWORD p5, DWORD p6);
	typedef DWORD(__stdcall* TD2GetItemLevel) (Unit* ptItem);
	typedef DWORD(__stdcall* TD2GetItemQuality) (Unit* ptItem);
	typedef int(__stdcall* TD2GetUniqueID) (Unit* ptItem);
	typedef ItemsBIN* (__stdcall* TD2GetItemsBIN) (DWORD itemID);
	typedef Unit* (__stdcall* TD2CanPutItemInInv) (Inventory* ptInventory, Unit* ptItem, DWORD p3, DWORD zero, Unit* ptUnit, const char* file, DWORD line);

	static TD2InvAddItem D2InvAddItem;
	static TD2InvRemoveItem D2InvRemoveItem;
	static TD2InventoryGetFirstItem D2InventoryGetFirstItem;
	static TD2UnitGetNextItem D2UnitGetNextItem;
	static TD2GetRealItem D2GetRealItem;
	static TD2InitPlayerData D2InitPlayerData;
	static TD2GetPlayerData D2GetPlayerData;
	static TD2GetItemLevel D2GetItemLevel;
	static TD2GetItemQuality D2GetItemQuality;
	static TD2GetUniqueID D2GetUniqueID;
	static TD2GetItemsBIN D2GetItemsBIN;
	static TD2CanPutItemInInv D2CanPutItemInInv;
	static TD2CompileTxtFile D2CompileTxtFile;

	// Some functions use the wrapped version
	static TD2ItemSetPage D2ItemSetPage;
	static TD2ItemGetPage D2ItemGetPage;
	static TD2SaveItem D2SaveItem;

	// Variables: Structure Management
	static DWORD ptPYPlayerDataOffset;
	static DWORD ptSpecificDataOffset;
	static DWORD ptGameOffset;
	static DWORD ptClientGameOffset;
	static DWORD ptInventoryOffset;
	static DWORD ptSkillsOffset;
	static DWORD ptImageOffset;
	static DWORD ptFrameOffset;

	static DataTables* D2Common::GetDataTables();
private:
	static void SetFunctions();
	static Unit* __stdcall D2GetRealItem_111(Unit* ptItem);
	static DWORD SgptDataTablesOffset;
};