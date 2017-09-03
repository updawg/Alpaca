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

class D2CommonLibrary : public Library
{
public:
	D2CommonLibrary(int gameVersion) : Library()
	{
		Name = "D2Common.dll";
		Version = gameVersion;
		Offset = LoadDiabloLibrary();
		SetFunctions();

		// These need to be initialized here, they cannot be inlined in the variable declaration
		// because they would be initialized before the class was able to set the Version variable
		// which are used in the GetOffsetForVersion function.
		ptPYPlayerDataOffset = GetOffsetForVersion(0x5D, 0x5D, 0x5D, 0x49, 0x49, 0x49, 0x49, 0x49);
		ptSpecificDataOffset = GetOffsetForVersion(0x70, 0x70, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14);
		ptGameOffset = GetOffsetForVersion(0xA4, 0xA4, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80);
		ptClientGameOffset = GetOffsetForVersion(0x170, 0x194, 0x1A8, 0x1A8, 0x1A8, 0x1A8, 0x1A8, 0x1A8);
		ptInventoryOffset = GetOffsetForVersion(0x84, 0x84, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60);
		ptSkillsOffset = GetOffsetForVersion(0xCC, 0xCC, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8, 0xA8);
		ptImageOffset = GetOffsetForVersion(0x04, 0x04, 0x04, 0x08, 0x08, 0x3C, 0x34, 0x34);
		ptFrameOffset = GetOffsetForVersion(0x08, 0x08, 0x08, 0x44, 0x44, 0x40, 0, 0);
	};

	DWORD RetrieveStashGridOffset();
	DWORD RetrieveSgptDataTables();

	// Structure Management
	DWORD ptPYPlayerDataOffset;
	DWORD ptSpecificDataOffset;
	DWORD ptGameOffset;
	DWORD ptClientGameOffset;
	DWORD ptInventoryOffset;
	DWORD ptSkillsOffset;
	DWORD ptImageOffset;
	DWORD ptFrameOffset;

	// Types
	typedef Unit* (__stdcall *TD2Common10242) (Inventory* ptInventory, Unit* ptItem, DWORD bIsClient);
	typedef Unit* (__stdcall *TD2CanPutItemInInv) (Inventory* ptInventory, Unit* ptItem, DWORD p3, DWORD zero, Unit* ptUnit, const char* file, DWORD line);
	typedef Unit* (__stdcall *TD2InvRemoveItem) (Inventory* ptInventory, Unit* ptItem);
	typedef DWORD(__stdcall *TD2InvAddItem) (Inventory* ptInventory, Unit* ptItem, DWORD posX, DWORD posY, DWORD vValueC, DWORD bIsClient, BYTE page);
	typedef DWORD(__stdcall *TD2Common10250) (const char* file, DWORD line, Inventory* ptInventory, DWORD posX, DWORD posY, DWORD vValueC, DWORD bIsClient, BYTE page);
	typedef DWORD(__stdcall *TD2Common10273) (Inventory* ptInventory, void* unknow);
	typedef Unit* (__stdcall *TD2InventoryGetFirstItem) (Inventory* ptInventory);
	typedef Unit* (__stdcall *TD2UnitGetNextItem) (Unit* ptItem);
	typedef Unit* (__stdcall *TD2GetRealItem) (Unit* ptUnit);
	typedef DWORD(__stdcall *TD2GetPosX) (Unit* ptUnit);
	typedef DWORD(__stdcall *TD2GetPosY) (Unit* ptUnit);
	typedef DWORD(__stdcall *TD2GetMaxGoldBank) (Unit* ptUnit);
	typedef PlayerData* (__stdcall *TD2InitPlayerData) (Unit* ptChar);
	typedef PlayerData* (__stdcall *TD2GetPlayerData) (Unit* ptChar);
	typedef DWORD(__stdcall *TD2GetDefence) (Unit* ptChar);
	typedef DWORD(__stdcall *TD2GetChanceToBlock) (Unit* ptChar, DWORD isLODGame);
	typedef DWORD(__stdcall *TD2GetMaxGold) (Unit* ptUnit);
	typedef DWORD(__stdcall *TD2isInState) (Unit* ptChar, DWORD isLODGame);
	typedef void(__stdcall *TD2AddPlayerStat) (Unit* ptChar, DWORD statID, int amount, DWORD index);
	typedef int(__stdcall *TD2GetPlayerStat) (Unit* ptChar, DWORD statID, DWORD index);
	typedef int(__stdcall *TD2GetPlayerBaseStat) (Unit* ptChar, DWORD statID, DWORD index);
	typedef DWORD(__stdcall *TD2haveDefenceBonus) (Unit* ptChar);
	typedef DWORD(__stdcall *TD2haveFireResBonus) (Unit* ptChar);
	typedef DWORD(__stdcall *TD2haveColdResBonus) (Unit* ptChar);
	typedef DWORD(__stdcall *TD2haveLightResBonus) (Unit* ptChar);
	typedef DWORD(__stdcall *TD2havePoisonResBonus) (Unit* ptChar);
	typedef DWORD(__stdcall *TD2haveDefenceMalus) (Unit* ptChar);
	typedef DWORD(__stdcall *TD2haveFireResMalus) (Unit* ptChar);
	typedef DWORD(__stdcall *TD2haveColdResMalus) (Unit* ptChar);
	typedef DWORD(__stdcall *TD2haveLightResMalus) (Unit* ptChar);
	typedef DWORD(__stdcall *TD2havePoisonResMalus) (Unit* ptChar);
	typedef void* (__stdcall *TD2CompileTxtFile) (DWORD unused, const char* filename, BINField* ptFields, DWORD* ptRecordCount, DWORD recordLength);
	typedef ItemsBIN* (__stdcall *TD2GetItemsBIN) (DWORD itemID);
	typedef GemsBIN* (__stdcall *TD2GetGemsBIN) (DWORD gemID);
	typedef CubeMainBIN* (__stdcall *TD2GetCubeMainBIN) (DWORD cubemainID);
	typedef int(__stdcall *TD2GetNbCubeMainBIN) ();
	typedef DWORD(__stdcall *TD2GetNextLevelXP) (DWORD classID, DWORD level);
	typedef DWORD(__stdcall *TD2GetMaxLevel) (DWORD classID);
	typedef DifficultyLevelsBIN* (__stdcall *TD2GetDifficultyLevelsBIN) (DWORD difficultyLevel);
	typedef DWORD(__stdcall *TD2GetItemQuality) (Unit* ptItem);
	typedef DWORD(__stdcall *TD2GetItemLevel) (Unit* ptItem);
	typedef BYTE(__stdcall *TD2ItemGetPage) (Unit* ptUnit);
	typedef void(__stdcall *TD2ItemSetPage) (Unit* ptItem, BYTE page);
	typedef int(__stdcall *TD2GetUniqueID) (Unit* ptItem);
	typedef void(__stdcall *TD2SetAnim) (Unit* ptUnit, int anim);
	typedef int* (__stdcall *TD2GetNbRunesBIN) ();
	typedef RunesBIN* (__stdcall *TD2GetRunesBIN) (int runesID);
	typedef DWORD(__stdcall *TD2SaveItem) (Unit* ptItem, saveBitField* data, DWORD startSize, DWORD p4, DWORD p5, DWORD p6);
	typedef CharStatsBIN* (__fastcall *TD2GetCharStatsBIN) (DWORD charID);
	typedef ItemTypesBIN* (__fastcall *TD2GetItemTypesBIN) (DWORD itemTypesId);
	typedef ItemStatCostBIN* (__fastcall *TD2GetItemStatCostBIN) (DWORD id);
	typedef void* (__fastcall *TD2ReadFile) (DWORD unused, char* filename, DWORD* size, const char*, DWORD);
	typedef void(__stdcall *TD2LoadSuperuniques) (DWORD mempool);

	TD2Common10242 D2Common10242;
	TD2CanPutItemInInv D2CanPutItemInInv;
	TD2InvRemoveItem D2InvRemoveItem;
	TD2InvAddItem D2InvAddItem;
	TD2Common10250 D2Common10250;
	TD2Common10273 D2Common10273;
	TD2InventoryGetFirstItem D2InventoryGetFirstItem;
	TD2UnitGetNextItem D2UnitGetNextItem;
	TD2GetRealItem D2GetRealItem;
	TD2GetPosX D2GetPosX;
	TD2GetPosY D2GetPosY;
	TD2GetMaxGoldBank D2GetMaxGoldBank;
	TD2InitPlayerData D2InitPlayerData;
	TD2GetPlayerData D2GetPlayerData;
	TD2GetDefence D2GetDefence;
	TD2GetChanceToBlock D2GetChanceToBlock;
	TD2GetMaxGold D2GetMaxGold;
	TD2isInState D2isInState;
	TD2AddPlayerStat D2AddPlayerStat;
	TD2GetPlayerStat D2GetPlayerStat;
	TD2GetPlayerBaseStat D2GetPlayerBaseStat;
	TD2haveDefenceBonus D2haveDefenceBonus;
	TD2haveFireResBonus D2haveFireResBonus;
	TD2haveColdResBonus D2haveColdResBonus;
	TD2haveLightResBonus D2haveLightResBonus;
	TD2havePoisonResBonus D2havePoisonResBonus;
	TD2haveDefenceMalus D2haveDefenceMalus;
	TD2haveFireResMalus D2haveFireResMalus;
	TD2haveColdResMalus D2haveColdResMalus;
	TD2haveLightResMalus D2haveLightResMalus;
	TD2havePoisonResMalus D2havePoisonResMalus;
	TD2CompileTxtFile D2CompileTxtFile;
	TD2GetItemsBIN D2GetItemsBIN;
	TD2GetGemsBIN D2GetGemsBIN;
	TD2GetCubeMainBIN D2GetCubeMainBIN;
	TD2GetNbCubeMainBIN D2GetNbCubeMainBIN;
	TD2GetNextLevelXP D2GetNextLevelXP;
	TD2GetMaxLevel D2GetMaxLevel;
	TD2GetDifficultyLevelsBIN D2GetDifficultyLevelsBIN;
	TD2GetItemQuality D2GetItemQuality;
	TD2GetItemLevel D2GetItemLevel;
	TD2ItemGetPage D2ItemGetPage;
	TD2ItemSetPage D2ItemSetPage;
	TD2GetUniqueID D2GetUniqueID;
	TD2SetAnim D2SetAnim;
	TD2GetNbRunesBIN D2GetNbRunesBIN;
	TD2GetRunesBIN D2GetRunesBIN;
	TD2SaveItem D2SaveItem;
	TD2GetCharStatsBIN D2GetCharStatsBIN;
	TD2GetItemTypesBIN D2GetItemTypesBIN;
	TD2GetItemStatCostBIN D2GetItemStatCostBIN;
	TD2ReadFile D2ReadFile;
	TD2LoadSuperuniques D2LoadSuperuniques;

	// Only 1.09
	typedef CharStatsBIN* (__stdcall *TD2Common10581) (DWORD charID);
	typedef ItemStatCostBIN* (__stdcall *TD2Common10598) (DWORD itemStatCostID);
	typedef ItemTypesBIN* (__stdcall *TD2Common10673) (DWORD itemTypesID);

	TD2Common10581 D2Common10581;
	TD2Common10598 D2Common10598;
	TD2Common10673 D2Common10673;
private:
	void SetFunctions();
};