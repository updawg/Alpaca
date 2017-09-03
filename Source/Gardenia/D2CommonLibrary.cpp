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

void D2CommonLibrary::SetFunctions()
{
	D2Common10242 = (TD2Common10242)GetOffsetByProc(10242, 10242, 10242, 0, 0, 0, 0, 0);
	D2CanPutItemInInv = (TD2CanPutItemInInv)GetOffsetByProc(10246, 10246, 10246, 10855, 10813, 10289, 10133, 10402);
	D2InvRemoveItem = (TD2InvRemoveItem)GetOffsetByProc(10243, 10243, 10243, 10461, 10827, 10936, 10646, 10490);
	D2InvAddItem = (TD2InvAddItem)GetOffsetByProc(10249, 10249, 10249, 10880, 11068, 10436, 11107, 10963);
	D2Common10250 = (TD2Common10250)GetOffsetByProc(10250, 10250, 10250, 0, 0, 0, 0, 0);
	D2Common10273 = (TD2Common10273)GetOffsetByProc(10273, 10273, 10273, 0, 0, 0, 0, 0);
	D2InventoryGetFirstItem = (TD2InventoryGetFirstItem)GetOffsetByProc(10277, 10277, 10277, 10402, 10535, 11151, 10460, 11040);
	D2UnitGetNextItem = (TD2UnitGetNextItem)GetOffsetByProc(10304, 10304, 10304, 10934, 11140, 10770, 10464, 10879);
	D2GetRealItem = (TD2GetRealItem)GetOffsetByProc(10305, 10305, 10305, 11095, 10748, 10852, 11147, 10897);
	D2GetPosX = (TD2GetPosX)GetOffsetByProc(10326, 10326, 0, 0, 0, 0, 0, 0);
	D2GetPosY = (TD2GetPosY)GetOffsetByProc(10329, 10329, 0, 0, 0, 0, 0, 0);
	D2GetMaxGoldBank = (TD2GetMaxGoldBank)GetOffsetByProc(10339, 10339, 10339, 10455, 10864, 10941, 11060, 11025);
	D2InitPlayerData = (TD2InitPlayerData)GetOffsetByProc(10420, 10420, 10420, 10218, 10079, 11097, 10356, 10404);
	D2GetPlayerData = (TD2GetPlayerData)GetOffsetByProc(10424, 10424, 10424, 10562, 10800, 10860, 10920, 11103);
	D2GetDefence = (TD2GetDefence)GetOffsetByProc(10431, 10431, 10431, 0, 0, 0, 0, 0);
	D2GetChanceToBlock = (TD2GetChanceToBlock)GetOffsetByProc(10433, 10433, 10433, 0, 0, 0, 0, 0);
	D2GetMaxGold = (TD2GetMaxGold)GetOffsetByProc(10439, 10439, 10439, 10343, 11131, 10729, 10049, 11159);
	D2isInState = (TD2isInState)GetOffsetByProc(10487, 10487, 10487, 0, 0, 0, 0, 0);
	D2AddPlayerStat = (TD2AddPlayerStat)GetOffsetByProc(10518, 10518, 10518, 10109, 10627, 10762, 10551, 10645);
	D2GetPlayerStat = (TD2GetPlayerStat)GetOffsetByProc(10519, 10519, 10519, 11092, 10061, 10658, 10973, 10550);
	D2GetPlayerBaseStat = (TD2GetPlayerBaseStat)GetOffsetByProc(10521, 10521, 10521, 10733, 10550, 10494, 10587, 10216);
	D2haveDefenceBonus = (TD2haveDefenceBonus)GetOffsetByProc(10539, 10539, 10539, 0, 0, 0, 0, 0);
	D2haveFireResBonus = (TD2haveFireResBonus)GetOffsetByProc(10540, 10540, 10540, 0, 0, 0, 0, 0);
	D2haveColdResBonus = (TD2haveColdResBonus)GetOffsetByProc(10541, 10541, 10541, 0, 0, 0, 0, 0);
	D2haveLightResBonus = (TD2haveLightResBonus)GetOffsetByProc(10542, 10542, 10542, 0, 0, 0, 0, 0);
	D2havePoisonResBonus = (TD2havePoisonResBonus)GetOffsetByProc(10543, 10543, 10543, 0, 0, 0, 0, 0);
	D2haveDefenceMalus = (TD2haveDefenceMalus)GetOffsetByProc(10546, 10546, 10546, 0, 0, 0, 0, 0);
	D2haveFireResMalus = (TD2haveFireResMalus)GetOffsetByProc(10547, 10547, 10547, 0, 0, 0, 0, 0);
	D2haveColdResMalus = (TD2haveColdResMalus)GetOffsetByProc(10548, 10548, 10548, 0, 0, 0, 0, 0);
	D2haveLightResMalus = (TD2haveLightResMalus)GetOffsetByProc(10549, 10549, 10549, 0, 0, 0, 0, 0);
	D2havePoisonResMalus = (TD2havePoisonResMalus)GetOffsetByProc(10550, 10550, 10550, 0, 0, 0, 0, 0);
	D2CompileTxtFile = (TD2CompileTxtFile)GetOffsetByProc(10578, 10578, 10578, 10653, 10496, 10244, 10849, 10037);
	D2GetItemsBIN = (TD2GetItemsBIN)GetOffsetByProc(10600, 10600, 10600, 10573, 10262, 10887, 10695, 10994);
	D2GetGemsBIN = (TD2GetGemsBIN)GetOffsetByProc(10616, 10616, 10616, 10500, 10523, 10774, 10806, 10619);
	D2GetCubeMainBIN = (TD2GetCubeMainBIN)GetOffsetByProc(11232, 11232, 11232, 10746, 10258, 10913, 10783, 10393);
	D2GetNbCubeMainBIN = (TD2GetNbCubeMainBIN)GetOffsetByProc(11233, 11233, 11233, 10639, 11135, 10390, 10675, 10235);
	D2GetNextLevelXP = (TD2GetNextLevelXP)GetOffsetByProc(10628, 10628, 10628, 0, 0, 0, 0, 0);
	D2GetMaxLevel = (TD2GetMaxLevel)GetOffsetByProc(10629, 10629, 10629, 0, 0, 0, 0, 0);
	D2GetDifficultyLevelsBIN = (TD2GetDifficultyLevelsBIN)GetOffsetByProc(10655, 10655, 10655, 10655, 10309, 10297, 10218, 10694);
	D2GetItemQuality = (TD2GetItemQuality)GetOffsetByProc(10695, 10695, 10695, 10927, 10899, 10276, 10106, 10911);
	D2GetItemLevel = (TD2GetItemLevel)GetOffsetByProc(10717, 10717, 10717, 10898, 10100, 10410, 10086, 10008);
	D2ItemGetPage = (TD2ItemGetPage)GetOffsetByProc(10719, 10719, 10719, 10820, 10505, 10370, 10020, 10810);
	D2ItemSetPage = (TD2ItemSetPage)GetOffsetByProc(10720, 10720, 10720, 10485, 10608, 10223, 10012, 11026);
	D2GetUniqueID = (TD2GetUniqueID)GetOffsetByProc(10732, 10732, 10732, 10692, 10685, 10280, 10620, 10075);
	D2SetAnim = (TD2SetAnim)GetOffsetByProc(10734, 10734, 10734, 0, 0, 0, 0, 0);
	D2GetNbRunesBIN = (TD2GetNbRunesBIN)GetOffsetByProc(10619, 10619, 10619, 10687, 10877, 10321, 11032, 10981);
	D2GetRunesBIN = (TD2GetRunesBIN)GetOffsetByProc(10620, 10620, 10620, 10775, 10296, 10622, 10006, 10405);
	D2SaveItem = (TD2SaveItem)GetOffsetByProc(10881, 10881, 10881, 10956, 11156, 10218, 10987, 10665);
	D2GetCharStatsBIN = (TD2GetCharStatsBIN)GetOffsetByAddition(0, 0, 0x82C80, 0x15D0, 0x1800, 0x1220, 0x12D0, 0x17B0);
	D2GetItemTypesBIN = (TD2GetItemTypesBIN)GetOffsetByAddition(0, 0, 0x2B1A0, 0x11F0, 0x1380, 0x1140, 0x1300, 0x1160);
	D2GetItemStatCostBIN = (TD2GetItemStatCostBIN)GetOffsetByAddition(0, 0, 0x642B0, 0x13F0, 0x12F0, 0x1540, 0x17A0, 0x17E0);
	D2ReadFile = (TD2ReadFile)GetOffsetByAddition(0x738A4, 0x739B4, 0x84268, 0x96E0, 0x98D0, 0x9900, 0x9900, 0xB5E0);
	D2LoadSuperuniques = (TD2LoadSuperuniques)GetOffsetByAddition(0x1F500, 0x1F510, 0x29FA0, 0x71EB0, 0x32AA0, 0x7D2A0, 0x59870, 0x80C40);

	// Only 1.09
	D2Common10581 = (TD2Common10581)GetOffsetByProc(10581, 10581, 0, 0, 0, 0, 0, 0);
	D2Common10598 = (TD2Common10598)GetOffsetByProc(10598, 10598, 0, 0, 0, 0, 0, 0);
	D2Common10673 = (TD2Common10673)GetOffsetByProc(10673, 10673, 0, 0, 0, 0, 0, 0);
}

DWORD D2CommonLibrary::RetrieveStashGridOffset()
{
	return GetOffsetByAddition(0xC9F3, 0xCA03, 0x14ED3, 0x5FCB5, 0x2A505, 0x1BDB5, 0x82CA5, 0x6CC25);
}

DWORD D2CommonLibrary::RetrieveSgptDataTables()
{
	return GetOffsetByAddition(0, 0, 0x96A20, 0x9B74C, 0x9EE8C, 0x9B500, 0x99E1C, 0xA33F0);
}