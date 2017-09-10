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

	// These need to be initialized here, they cannot be inlined in the variable declaration
	// because they would be initialized before the class was able to set the Version variable
	// which are used in the GetOffsetForVersion function.
	ptPYPlayerDataOffset = GetOffsetForVersion(0x5D, 0x49);
	ptSpecificDataOffset = GetOffsetForVersion(0x70, 0x14);
	ptGameOffset = GetOffsetForVersion(0xA4, 0x80);
	ptClientGameOffset = GetOffsetForVersion(0x170, 0x1A8);
	ptInventoryOffset = GetOffsetForVersion(0x84, 0x60);
	ptSkillsOffset = GetOffsetForVersion(0xCC, 0xA8);
	ptImageOffset = GetOffsetForVersion(0x04, 0x34);
	ptFrameOffset = GetOffsetForVersion(0x08, 0);
}

void D2Common::SetFunctions()
{
	D2Common10242 = (TD2Common10242)GetOffsetByProc(10242, 0);
	D2CanPutItemInInv = (TD2CanPutItemInInv)GetOffsetByProc(10246, 10402);
	D2InvRemoveItem = (TD2InvRemoveItem)GetOffsetByProc(10243, 10490);
	D2InvAddItem = (TD2InvAddItem)GetOffsetByProc(10249, 10963);
	D2Common10250 = (TD2Common10250)GetOffsetByProc(10250, 0);
	D2Common10273 = (TD2Common10273)GetOffsetByProc(10273, 0);
	D2InventoryGetFirstItem = (TD2InventoryGetFirstItem)GetOffsetByProc(10277, 11040);
	D2UnitGetNextItem = (TD2UnitGetNextItem)GetOffsetByProc(10304, 10879);
	D2GetRealItem = (TD2GetRealItem)GetOffsetByProc(10305, 10897);
	D2GetPosX = (TD2GetPosX)GetOffsetByProc(10326, 0);
	D2GetPosY = (TD2GetPosY)GetOffsetByProc(10329, 0);
	D2GetMaxGoldBank = (TD2GetMaxGoldBank)GetOffsetByProc(10339, 11025);
	D2InitPlayerData = (TD2InitPlayerData)GetOffsetByProc(10420, 10404);
	D2GetPlayerData = (TD2GetPlayerData)GetOffsetByProc(10424, 11103);
	D2GetDefence = (TD2GetDefence)GetOffsetByProc(10431, 0);
	D2GetChanceToBlock = (TD2GetChanceToBlock)GetOffsetByProc(10433, 0);
	D2GetMaxGold = (TD2GetMaxGold)GetOffsetByProc(10439, 11159);
	D2isInState = (TD2isInState)GetOffsetByProc(10487, 0);
	D2AddPlayerStat = (TD2AddPlayerStat)GetOffsetByProc(10518, 10645);
	D2GetPlayerStat = (TD2GetPlayerStat)GetOffsetByProc(10519, 10550);
	D2GetPlayerBaseStat = (TD2GetPlayerBaseStat)GetOffsetByProc(10521, 10216);
	D2haveDefenceBonus = (TD2haveDefenceBonus)GetOffsetByProc(10539, 0);
	D2haveFireResBonus = (TD2haveFireResBonus)GetOffsetByProc(10540, 0);
	D2haveColdResBonus = (TD2haveColdResBonus)GetOffsetByProc(10541, 0);
	D2haveLightResBonus = (TD2haveLightResBonus)GetOffsetByProc(10542, 0);
	D2havePoisonResBonus = (TD2havePoisonResBonus)GetOffsetByProc(10543, 0);
	D2haveDefenceMalus = (TD2haveDefenceMalus)GetOffsetByProc(10546, 0);
	D2haveFireResMalus = (TD2haveFireResMalus)GetOffsetByProc(10547, 0);
	D2haveColdResMalus = (TD2haveColdResMalus)GetOffsetByProc(10548, 0);
	D2haveLightResMalus = (TD2haveLightResMalus)GetOffsetByProc(10549, 0);
	D2havePoisonResMalus = (TD2havePoisonResMalus)GetOffsetByProc(10550, 0);
	D2CompileTxtFileBase = (TD2CompileTxtFile)GetOffsetByProc(10578, 10037);
	D2GetItemsBIN = (TD2GetItemsBIN)GetOffsetByProc(10600, 10994);
	D2GetGemsBIN = (TD2GetGemsBIN)GetOffsetByProc(10616, 10619);
	D2GetCubeMainBIN = (TD2GetCubeMainBIN)GetOffsetByProc(11232, 10393);
	D2GetNbCubeMainBIN = (TD2GetNbCubeMainBIN)GetOffsetByProc(11233, 10235);
	D2GetNextLevelXP = (TD2GetNextLevelXP)GetOffsetByProc(10628, 0);
	D2GetMaxLevel = (TD2GetMaxLevel)GetOffsetByProc(10629, 0);
	D2GetDifficultyLevelsBIN = (TD2GetDifficultyLevelsBIN)GetOffsetByProc(10655, 10694);
	D2GetItemQuality = (TD2GetItemQuality)GetOffsetByProc(10695, 10911);
	D2GetItemLevel = (TD2GetItemLevel)GetOffsetByProc(10717, 10008);
	D2ItemGetPage = (TD2ItemGetPage)GetOffsetByProc(10719, 10810);
	D2ItemSetPage = (TD2ItemSetPage)GetOffsetByProc(10720, 11026);
	D2GetUniqueID = (TD2GetUniqueID)GetOffsetByProc(10732, 10075);
	D2SetAnim = (TD2SetAnim)GetOffsetByProc(10734, 0);
	D2GetNbRunesBIN = (TD2GetNbRunesBIN)GetOffsetByProc(10619, 10981);
	D2GetRunesBIN = (TD2GetRunesBIN)GetOffsetByProc(10620, 10405);
	D2SaveItem = (TD2SaveItem)GetOffsetByProc(10881, 10665);
	D2GetCharStatsBIN = (TD2GetCharStatsBIN)GetOffsetByAddition(0, 0x17B0);
	D2GetItemTypesBIN = (TD2GetItemTypesBIN)GetOffsetByAddition(0, 0x1160);
	D2GetItemStatCostBIN = (TD2GetItemStatCostBIN)GetOffsetByAddition(0, 0x17E0);
	D2ReadFile = (TD2ReadFile)GetOffsetByAddition(0x738A4, 0xB5E0);
	D2LoadSuperuniques = (TD2LoadSuperuniques)GetOffsetByAddition(0x1F500, 0x80C40);

	// Only 1.09
	D2Common10581 = (TD2Common10581)GetOffsetByProc(10581, 0);
	D2Common10598 = (TD2Common10598)GetOffsetByProc(10598, 0);
	D2Common10673 = (TD2Common10673)GetOffsetByProc(10673, 0);
}

D2Common::TD2CompileTxtFile D2Common::D2CompileTxtFile()
{
	if (VersionUtility::Is113D())
	{
		return (TD2CompileTxtFile)compileTxtFile_111;
	}
	else
	{
		return (TD2CompileTxtFile)compileTxtFile_9;
	}
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
		MOV ECX, D2CompileTxtFileBase
		ADD ECX, 0x305
		JMP ECX
	}
}

__declspec(naked) void* __stdcall D2Common::compileTxtFile_111(DWORD unused, const char* filename, BINField* ptFields, DWORD* ptRecordCount, DWORD recordLength)
{
	_asm {
		SUB ESP, 0x20C
		PUSH EBX
		PUSH EBP
		PUSH ESI
		PUSH EDI
		MOV DWORD PTR SS : [ESP + 0x10], 0
		MOV EBX, DWORD PTR SS : [ESP + 0x224]

		PUSH EBX
		LEA EAX, DWORD PTR SS : [ESP + 0x1C]
		PUSH EAX
		CALL DWORD PTR SS : [wsprintf]
		MOV EDX, DWORD PTR SS : [ESP + 0x228]
		ADD ESP, 8
		LEA EDX, DWORD PTR SS : [ESP + 0x10]
		PUSH EDX
		PUSH EAX
		LEA EAX, DWORD PTR SS : [ESP + 0x20]
		CALL D2ReadFile
		TEST EAX, EAX
		JNZ continue_compileTxtFile
		PUSH __LINE__
		CALL Fog::D2GetInstructionPointer
		PUSH EAX
		PUSH ErrorReadTxtFileName
		CALL Fog::D2FogAssert
		ADD ESP, 0xC
		PUSH - 1
		CALL exit
		continue_compileTxtFile :
		MOV ECX, D2CompileTxtFileBase
		ADD ECX, 0x1EC
		JMP ECX
	}
}

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
D2Common::TD2GetRealItem D2Common::D2GetRealItem;
D2Common::TD2GetPosX D2Common::D2GetPosX;
D2Common::TD2GetPosY D2Common::D2GetPosY;
D2Common::TD2GetMaxGoldBank D2Common::D2GetMaxGoldBank;
D2Common::TD2InitPlayerData D2Common::D2InitPlayerData;
D2Common::TD2GetPlayerData D2Common::D2GetPlayerData;
D2Common::TD2GetDefence D2Common::D2GetDefence;
D2Common::TD2GetChanceToBlock D2Common::D2GetChanceToBlock;
D2Common::TD2GetMaxGold D2Common::D2GetMaxGold;
D2Common::TD2isInState D2Common::D2isInState;
D2Common::TD2AddPlayerStat D2Common::D2AddPlayerStat;
D2Common::TD2GetPlayerStat D2Common::D2GetPlayerStat;
D2Common::TD2GetPlayerBaseStat D2Common::D2GetPlayerBaseStat;
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
D2Common::TD2CompileTxtFile D2Common::D2CompileTxtFileBase;
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
D2Common::TD2GetCharStatsBIN D2Common::D2GetCharStatsBIN;
D2Common::TD2GetItemTypesBIN D2Common::D2GetItemTypesBIN;
D2Common::TD2GetItemStatCostBIN D2Common::D2GetItemStatCostBIN;
D2Common::TD2ReadFile D2Common::D2ReadFile;
D2Common::TD2LoadSuperuniques D2Common::D2LoadSuperuniques;
D2Common::TD2Common10581 D2Common::D2Common10581;
D2Common::TD2Common10598 D2Common::D2Common10598;
D2Common::TD2Common10673 D2Common::D2Common10673;