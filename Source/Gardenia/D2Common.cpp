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
	D2Common10242 = (TD2Common10242)GetOffsetByProc(10242);
	D2CanPutItemInInv = (TD2CanPutItemInInv)GetOffsetByProc(10246);
	D2InvRemoveItem = (TD2InvRemoveItem)GetOffsetByProc(10243);
	D2InvAddItem = (TD2InvAddItem)GetOffsetByProc(10249);
	D2Common10250 = (TD2Common10250)GetOffsetByProc(10250);
	D2Common10273 = (TD2Common10273)GetOffsetByProc(10273);
	D2InventoryGetFirstItem = (TD2InventoryGetFirstItem)GetOffsetByProc(10277);
	D2UnitGetNextItem = (TD2UnitGetNextItem)GetOffsetByProc(10304);
	D2GetPosX = (TD2GetPosX)GetOffsetByProc(10326);
	D2GetPosY = (TD2GetPosY)GetOffsetByProc(10329);
	D2GetMaxGoldBank = (TD2GetMaxGoldBank)GetOffsetByProc(10339);
	D2InitPlayerData = (TD2InitPlayerData)GetOffsetByProc(10420);
	D2GetPlayerData = (TD2GetPlayerData)GetOffsetByProc(10424);
	D2GetDefence = (TD2GetDefence)GetOffsetByProc(10431);
	D2GetChanceToBlock = (TD2GetChanceToBlock)GetOffsetByProc(10433);
	D2GetMaxGold = (TD2GetMaxGold)GetOffsetByProc(10439);
	D2isInState = (TD2isInState)GetOffsetByProc(10487);
	D2haveDefenceBonus = (TD2haveDefenceBonus)GetOffsetByProc(10539);
	D2haveFireResBonus = (TD2haveFireResBonus)GetOffsetByProc(10540);
	D2haveColdResBonus = (TD2haveColdResBonus)GetOffsetByProc(10541);
	D2haveLightResBonus = (TD2haveLightResBonus)GetOffsetByProc(10542);
	D2havePoisonResBonus = (TD2havePoisonResBonus)GetOffsetByProc(10543);
	D2haveDefenceMalus = (TD2haveDefenceMalus)GetOffsetByProc(10546);
	D2haveFireResMalus = (TD2haveFireResMalus)GetOffsetByProc(10547);
	D2haveColdResMalus = (TD2haveColdResMalus)GetOffsetByProc(10548);
	D2haveLightResMalus = (TD2haveLightResMalus)GetOffsetByProc(10549);
	D2havePoisonResMalus = (TD2havePoisonResMalus)GetOffsetByProc(10550);
	D2GetItemsBIN = (TD2GetItemsBIN)GetOffsetByProc(10600);
	D2GetGemsBIN = (TD2GetGemsBIN)GetOffsetByProc(10616);
	D2GetCubeMainBIN = (TD2GetCubeMainBIN)GetOffsetByProc(11232);
	D2GetNbCubeMainBIN = (TD2GetNbCubeMainBIN)GetOffsetByProc(11233);
	D2GetNextLevelXP = (TD2GetNextLevelXP)GetOffsetByProc(10628);
	D2GetMaxLevel = (TD2GetMaxLevel)GetOffsetByProc(10629);
	D2GetDifficultyLevelsBIN = (TD2GetDifficultyLevelsBIN)GetOffsetByProc(10655);
	D2GetItemQuality = (TD2GetItemQuality)GetOffsetByProc(10695);
	D2GetItemLevel = (TD2GetItemLevel)GetOffsetByProc(10717);
	D2ItemGetPage = (TD2ItemGetPage)GetOffsetByProc(10719);
	D2ItemSetPage = (TD2ItemSetPage)GetOffsetByProc(10720);
	D2GetUniqueID = (TD2GetUniqueID)GetOffsetByProc(10732);
	D2SetAnim = (TD2SetAnim)GetOffsetByProc(10734);
	D2GetNbRunesBIN = (TD2GetNbRunesBIN)GetOffsetByProc(10619);
	D2GetRunesBIN = (TD2GetRunesBIN)GetOffsetByProc(10620);
	D2SaveItem = (TD2SaveItem)GetOffsetByProc(10881);
	D2ReadFile = (TD2ReadFile)GetOffsetByAddition(0x738A4);
	D2LoadSuperuniques = (TD2LoadSuperuniques)GetOffsetByAddition(0x1F500);
	D2Common10581 = (TD2Common10581)GetOffsetByProc(10581);
	D2Common10598 = (TD2Common10598)GetOffsetByProc(10598);
	D2Common10673 = (TD2Common10673)GetOffsetByProc(10673);
	D2CompileTxtFile = (TD2CompileTxtFile)compileTxtFile_9;
	D2AddPlayerStat = (TD2AddPlayerStat)D2AddPlayerStat_9;
	D2GetPlayerStat = (TD2GetPlayerStat)D2GetPlayerStat_9;
	D2GetPlayerBaseStat = (TD2GetPlayerBaseStat)D2GetPlayerBaseStat_9;
	D2GetCharStatsBIN = (TD2GetCharStatsBIN)D2GetCharStatsBIN_9;
	D2GetItemStatCostBIN = (TD2GetItemStatCostBIN)D2GetItemStatCostBIN_9;
	D2GetItemTypesBIN = (TD2GetItemTypesBIN)D2GetItemTypesBIN_9;
	D2GetRealItem = (TD2GetRealItem)GetOffsetByProc(10305);

	D2CompileTxtFileDirect = (TD2CompileTxtFile)GetOffsetByProc(10578);
	D2AddPlayerStatDirect = (TD2AddPlayerStat)GetOffsetByProc(10518);
	D2GetPlayerStatDirect = (TD2GetPlayerStat)GetOffsetByProc(10519);
	D2GetPlayerBaseStatDirect = (TD2GetPlayerBaseStat)GetOffsetByProc(10521);

	ptPYPlayerDataOffset = 0x5D;
	ptSpecificDataOffset = 0x70;
	ptGameOffset = 0xA4;
	ptClientGameOffset = 0x170;
	ptInventoryOffset = 0x84;
	ptSkillsOffset = 0xCC;
	ptImageOffset = 0x04;
	ptFrameOffset = 0x08;
}

char* D2Common::CompileTxtFileName = "D2CompileTxtFile";
char* D2Common::ErrorReadTxtFileName = "pbData";

__declspec(naked) void* __stdcall D2Common::compileTxtFile_9(DWORD unused, const char* filename, BINField* ptFields, DWORD* ptRecordCount, DWORD recordLength)
{
	_asm {
		SUB ESP, 0x210
		PUSH EBX
		PUSH EBP
		PUSH ESI
		PUSH EDI
		MOV ESI, DWORD PTR SS : [ESP + 0x228]
		MOV DWORD PTR SS : [ESP + 0x10], 0

		MOV EDI, wsprintf
		PUSH ESI
		LEA EAX, DWORD PTR SS : [ESP + 0x20]
		PUSH EAX
		CALL EDI
		ADD ESP, 8

		LEA EDX, DWORD PTR SS : [ESP + 0x10]
		PUSH 0
		PUSH CompileTxtFileName
		PUSH EDX
		MOV ECX, DWORD PTR SS : [ESP + 0x230]
		LEA EDX, DWORD PTR SS : [ESP + 0x28]
		CALL D2ReadFile
		TEST EAX, EAX
		JNZ continue_compileTxtFile
		PUSH 0
		PUSH CompileTxtFileName
		PUSH ErrorReadTxtFileName
		CALL Fog::D2FogAssertOld
		PUSH - 1
		CALL exit
		continue_compileTxtFile :
		MOV ECX, D2CompileTxtFileDirect
		ADD ECX, 0x305
		JMP ECX
	}
}

__declspec(naked) void D2Common::D2AddPlayerStat_9()
{
	__asm {
		PUSH DWORD PTR SS : [ESP + 0xC]
		PUSH DWORD PTR SS : [ESP + 0xC]
		PUSH DWORD PTR SS : [ESP + 0xC]
		CALL D2AddPlayerStatDirect
		RETN 0x10
	}
}

__declspec(naked) void D2Common::D2GetPlayerStat_9()
{
	__asm {
		PUSH DWORD PTR SS : [ESP + 0x8]
		PUSH DWORD PTR SS : [ESP + 0x8]
		CALL D2GetPlayerStatDirect
		RETN 0x0C
	}
}

__declspec(naked) void D2Common::D2GetPlayerBaseStat_9()
{
	__asm {
		PUSH DWORD PTR SS : [ESP + 0x8]
		PUSH DWORD PTR SS : [ESP + 0x8]
		CALL D2GetPlayerBaseStatDirect
		RETN 0x0C
	}
}

__declspec(naked) void D2Common::D2GetCharStatsBIN_9()
{
	__asm {
		PUSH ECX
		CALL D2Common10581
		RETN
	}
}

__declspec(naked) void D2Common::D2GetItemStatCostBIN_9()
{
	__asm {
		PUSH ECX
		CALL D2Common10598
		RETN
	}
}

__declspec(naked) void D2Common::D2GetItemTypesBIN_9()
{
	__asm {
		PUSH ECX
		CALL D2Common10673
		RETN
	}
}

D2Common::TD2CompileTxtFile D2Common::D2CompileTxtFile;
D2Common::TD2AddPlayerStat D2Common::D2AddPlayerStat;
D2Common::TD2GetPlayerStat D2Common::D2GetPlayerStat;
D2Common::TD2GetPlayerBaseStat D2Common::D2GetPlayerBaseStat;
D2Common::TD2GetCharStatsBIN D2Common::D2GetCharStatsBIN;
D2Common::TD2GetItemStatCostBIN D2Common::D2GetItemStatCostBIN;
D2Common::TD2GetItemTypesBIN D2Common::D2GetItemTypesBIN;
D2Common::TD2GetRealItem D2Common::D2GetRealItem;

DWORD D2Common::ptPYPlayerDataOffset;
DWORD D2Common::ptSpecificDataOffset;
DWORD D2Common::ptGameOffset;
DWORD D2Common::ptClientGameOffset;
DWORD D2Common::ptInventoryOffset;
DWORD D2Common::ptSkillsOffset;
DWORD D2Common::ptImageOffset;
DWORD D2Common::ptFrameOffset;

D2Common::TD2Common10242 D2Common::D2Common10242;
D2Common::TD2CanPutItemInInv D2Common::D2CanPutItemInInv;
D2Common::TD2InvRemoveItem D2Common::D2InvRemoveItem;
D2Common::TD2InvAddItem D2Common::D2InvAddItem;
D2Common::TD2Common10250 D2Common::D2Common10250;
D2Common::TD2Common10273 D2Common::D2Common10273;
D2Common::TD2InventoryGetFirstItem D2Common::D2InventoryGetFirstItem;
D2Common::TD2UnitGetNextItem D2Common::D2UnitGetNextItem;
D2Common::TD2GetPosX D2Common::D2GetPosX;
D2Common::TD2GetPosY D2Common::D2GetPosY;
D2Common::TD2GetMaxGoldBank D2Common::D2GetMaxGoldBank;
D2Common::TD2InitPlayerData D2Common::D2InitPlayerData;
D2Common::TD2GetPlayerData D2Common::D2GetPlayerData;
D2Common::TD2GetDefence D2Common::D2GetDefence;
D2Common::TD2GetChanceToBlock D2Common::D2GetChanceToBlock;
D2Common::TD2GetMaxGold D2Common::D2GetMaxGold;
D2Common::TD2isInState D2Common::D2isInState;
D2Common::TD2haveDefenceBonus D2Common::D2haveDefenceBonus;
D2Common::TD2haveFireResBonus D2Common::D2haveFireResBonus;
D2Common::TD2haveColdResBonus D2Common::D2haveColdResBonus;
D2Common::TD2haveLightResBonus D2Common::D2haveLightResBonus;
D2Common::TD2havePoisonResBonus D2Common::D2havePoisonResBonus;
D2Common::TD2haveDefenceMalus D2Common::D2haveDefenceMalus;
D2Common::TD2haveFireResMalus D2Common::D2haveFireResMalus;
D2Common::TD2haveColdResMalus D2Common::D2haveColdResMalus;
D2Common::TD2haveLightResMalus D2Common::D2haveLightResMalus;
D2Common::TD2havePoisonResMalus D2Common::D2havePoisonResMalus;
D2Common::TD2CompileTxtFile D2Common::D2CompileTxtFileDirect;
D2Common::TD2GetItemsBIN D2Common::D2GetItemsBIN;
D2Common::TD2GetGemsBIN D2Common::D2GetGemsBIN;
D2Common::TD2GetCubeMainBIN D2Common::D2GetCubeMainBIN;
D2Common::TD2GetNbCubeMainBIN D2Common::D2GetNbCubeMainBIN;
D2Common::TD2GetNextLevelXP D2Common::D2GetNextLevelXP;
D2Common::TD2GetMaxLevel D2Common::D2GetMaxLevel;
D2Common::TD2GetDifficultyLevelsBIN D2Common::D2GetDifficultyLevelsBIN;
D2Common::TD2GetItemQuality D2Common::D2GetItemQuality;
D2Common::TD2GetItemLevel D2Common::D2GetItemLevel;
D2Common::TD2ItemGetPage D2Common::D2ItemGetPage;
D2Common::TD2ItemSetPage D2Common::D2ItemSetPage;
D2Common::TD2GetUniqueID D2Common::D2GetUniqueID;
D2Common::TD2SetAnim D2Common::D2SetAnim;
D2Common::TD2GetNbRunesBIN D2Common::D2GetNbRunesBIN;
D2Common::TD2GetRunesBIN D2Common::D2GetRunesBIN;
D2Common::TD2SaveItem D2Common::D2SaveItem;
D2Common::TD2ReadFile D2Common::D2ReadFile;
D2Common::TD2LoadSuperuniques D2Common::D2LoadSuperuniques;

D2Common::TD2Common10581 D2Common::D2Common10581;
D2Common::TD2Common10598 D2Common::D2Common10598;
D2Common::TD2Common10673 D2Common::D2Common10673;

D2Common::TD2AddPlayerStat D2Common::D2AddPlayerStatDirect;
D2Common::TD2GetPlayerStat D2Common::D2GetPlayerStatDirect;
D2Common::TD2GetPlayerBaseStat D2Common::D2GetPlayerBaseStatDirect;