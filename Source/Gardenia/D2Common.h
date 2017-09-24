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

class D2Common : public Library<D2Common>
{
public:
	static void Init();

	// Structure Management
	static DWORD ptPYPlayerDataOffset;
	static DWORD ptSpecificDataOffset;
	static DWORD ptGameOffset;
	static DWORD ptClientGameOffset;
	static DWORD ptInventoryOffset;
	static DWORD ptSkillsOffset;
	static DWORD ptImageOffset;
	static DWORD ptFrameOffset;

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
	typedef CharStatsBIN* (__stdcall *TD2Common10581) (DWORD charID);
	typedef ItemStatCostBIN* (__stdcall *TD2Common10598) (DWORD itemStatCostID);
	typedef ItemTypesBIN* (__stdcall *TD2Common10673) (DWORD itemTypesID);

	static TD2Common10242 D2Common10242;
	static TD2CanPutItemInInv D2CanPutItemInInv;
	static TD2InvRemoveItem D2InvRemoveItem;
	static TD2InvAddItem D2InvAddItem;
	static TD2Common10250 D2Common10250;
	static TD2Common10273 D2Common10273;
	static TD2InventoryGetFirstItem D2InventoryGetFirstItem;
	static TD2UnitGetNextItem D2UnitGetNextItem;
	static TD2GetRealItem D2GetRealItem;
	static TD2GetPosX D2GetPosX;
	static TD2GetPosY D2GetPosY;
	static TD2GetMaxGoldBank D2GetMaxGoldBank;
	static TD2InitPlayerData D2InitPlayerData;
	static TD2GetPlayerData D2GetPlayerData;
	static TD2GetDefence D2GetDefence;
	static TD2GetChanceToBlock D2GetChanceToBlock;
	static TD2GetMaxGold D2GetMaxGold;
	static TD2isInState D2isInState;
	static TD2AddPlayerStat D2AddPlayerStat;
	static TD2GetPlayerStat D2GetPlayerStat;
	static TD2GetPlayerBaseStat D2GetPlayerBaseStat;
	static TD2haveDefenceBonus D2haveDefenceBonus;
	static TD2haveFireResBonus D2haveFireResBonus;
	static TD2haveColdResBonus D2haveColdResBonus;
	static TD2haveLightResBonus D2haveLightResBonus;
	static TD2havePoisonResBonus D2havePoisonResBonus;
	static TD2haveDefenceMalus D2haveDefenceMalus;
	static TD2haveFireResMalus D2haveFireResMalus;
	static TD2haveColdResMalus D2haveColdResMalus;
	static TD2haveLightResMalus D2haveLightResMalus;
	static TD2havePoisonResMalus D2havePoisonResMalus;

	// Some functions use the base function directly
	static TD2CompileTxtFile D2CompileTxtFileDirect;

	// Some functions use the wrapped version
	static TD2CompileTxtFile D2CompileTxtFile;

	static TD2GetItemsBIN D2GetItemsBIN;
	static TD2GetGemsBIN D2GetGemsBIN;
	static TD2GetCubeMainBIN D2GetCubeMainBIN;
	static TD2GetNbCubeMainBIN D2GetNbCubeMainBIN;
	static TD2GetNextLevelXP D2GetNextLevelXP;
	static TD2GetMaxLevel D2GetMaxLevel;
	static TD2GetDifficultyLevelsBIN D2GetDifficultyLevelsBIN;
	static TD2GetItemQuality D2GetItemQuality;
	static TD2GetItemLevel D2GetItemLevel;
	static TD2ItemGetPage D2ItemGetPage;
	static TD2ItemSetPage D2ItemSetPage;
	static TD2GetUniqueID D2GetUniqueID;
	static TD2SetAnim D2SetAnim;
	static TD2GetNbRunesBIN D2GetNbRunesBIN;
	static TD2GetRunesBIN D2GetRunesBIN;
	static TD2SaveItem D2SaveItem;
	static TD2GetCharStatsBIN D2GetCharStatsBIN;
	static TD2GetItemTypesBIN D2GetItemTypesBIN;
	static TD2GetItemStatCostBIN D2GetItemStatCostBIN;
	static TD2ReadFile D2ReadFile;
	static TD2LoadSuperuniques D2LoadSuperuniques;

	static TD2Common10581 D2Common10581;
	static TD2Common10598 D2Common10598;
	static TD2Common10673 D2Common10673;
private:
	static void SetFunctions();

	static char* CompileTxtFileName;
	static char* ErrorReadTxtFileName;
	static void* __stdcall compileTxtFile_9(DWORD unused, const char* filename, BINField* ptFields, DWORD* ptRecordCount, DWORD recordLength);

	static void D2AddPlayerStat_9();
	static void D2GetPlayerStat_9();
	static void D2GetPlayerBaseStat_9();
	static void D2GetCharStatsBIN_9();
	static void D2GetItemStatCostBIN_9();
	static void D2GetItemTypesBIN_9();

	// These values will only be used by the naked functions since it isn't recommended
	// to declare local variables inside of them.
	static TD2AddPlayerStat D2AddPlayerStatDirect;
	static TD2GetPlayerStat D2GetPlayerStatDirect;
	static TD2GetPlayerBaseStat D2GetPlayerBaseStatDirect;
};