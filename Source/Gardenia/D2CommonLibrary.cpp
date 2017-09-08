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

#include "D2CommonLibrary.h"

D2CommonLibrary::D2CommonLibrary(int gameVersion) : Library()
{
	Name = "D2Common.dll";
	Version = gameVersion;
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

void D2CommonLibrary::SetFunctions()
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
	D2CompileTxtFile = (TD2CompileTxtFile)GetOffsetByProc(10578, 10037);
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