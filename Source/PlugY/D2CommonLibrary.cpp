#include "D2CommonLibrary.h"

void D2CommonLibrary::SetFunctions()
{
	D2Common11084 = GetD2Common11084();
	D2GetLevelID = GetD2GetLevelID();
	D2GetDropRoom = GetD2GetDropRoom();
	D2Common10242 = GetD2Common10242();
	D2CanPutItemInInv = GetD2CanPutItemInInv();
	D2InvRemoveItem = GetD2InvRemoveItem();
	D2InvAddItem = GetD2InvAddItem();
	D2Common10250 = GetD2Common10250();
	D2Common10273 = GetD2Common10273();
	D2InventoryGetFirstItem = GetD2InventoryGetFirstItem();
	D2UnitGetNextItem = GetD2UnitGetNextItem();
	D2GetRealItem = GetD2GetRealItem();
	D2GetPosX = GetD2GetPosX();
	D2GetPosY = GetD2GetPosY();
	D2GetPosition = GetD2GetPosition();
	D2GetMaxGoldBank = GetD2GetMaxGoldBank();
	D2GetRoom = GetD2GetRoom();
	D2InitPlayerData = GetD2InitPlayerData();
	D2GetPlayerData = GetD2GetPlayerData();
	D2GetDefence = GetD2GetDefence();
	D2GetChanceToBlock = GetD2GetChanceToBlock();
	D2GetMaxGold = GetD2GetMaxGold();
	D2Common10572 = GetD2Common10572();
	D2GetObjectFlags = GetD2GetObjectFlags();
	D2SetObjectFlags = GetD2SetObjectFlags();
	D2isInState = GetD2isInState();
	D2AddPlayerStat = GetD2AddPlayerStat();
	D2GetPlayerStat = GetD2GetPlayerStat();
	D2GetPlayerBaseStat = GetD2GetPlayerBaseStat();
	D2haveDefenceBonus = GetD2haveDefenceBonus();
	D2haveFireResBonus = GetD2haveFireResBonus();
	D2haveColdResBonus = GetD2haveColdResBonus();
	D2haveLightResBonus = GetD2haveLightResBonus();
	D2havePoisonResBonus = GetD2havePoisonResBonus();
	D2haveDefenceMalus = GetD2haveDefenceMalus();
	D2haveFireResMalus = GetD2haveFireResMalus();
	D2haveColdResMalus = GetD2haveColdResMalus();
	D2haveLightResMalus = GetD2haveLightResMalus();
	D2havePoisonResMalus = GetD2havePoisonResMalus();
	D2CompileTxtFile = GetD2CompileTxtFile();
	D2GetItemsBIN = GetD2GetItemsBIN();
	D2GetGemsBIN = GetD2GetGemsBIN();
	D2GetCubeMainBIN = GetD2GetCubeMainBIN();
	D2GetNbCubeMainBIN = GetD2GetNbCubeMainBIN();
	D2GetNextLevelXP = GetD2GetNextLevelXP();
	D2GetMaxLevel = GetD2GetMaxLevel();
	D2GetDifficultyLevelsBIN = GetD2GetDifficultyLevelsBIN();
	D2GetItemQuality = GetD2GetItemQuality();
	D2TestFlags = GetD2TestFlags();
	D2GetItemLevel = GetD2GetItemLevel();
	D2ItemGetPage = GetD2ItemGetPage();
	D2ItemSetPage = GetD2ItemSetPage();
	D2CheckItemType = GetD2CheckItemType();
	D2GetUniqueID = GetD2GetUniqueID();
	D2SetAnim = GetD2SetAnim();
	D2GetNbRunesBIN = GetD2GetNbRunesBIN();
	D2GetRunesBIN = GetD2GetRunesBIN();
	D2isEtheral = GetD2isEtheral();
	D2SaveItem = GetD2SaveItem();
	D2SetSkillBaseLevel = GetD2SetSkillBaseLevel();
	D2GetSkillLevel = GetD2GetSkillLevel();
	D2GetSkillCost = GetD2GetSkillCost();
	D2GetCharStatsBIN = GetD2GetCharStatsBIN();
	D2CompileCubeInput = GetD2CompileCubeInput();
	D2CompileCubeOutput = GetD2CompileCubeOutput();
	D2GetItemTypesBIN = GetD2GetItemTypesBIN();
	D2GetItemStatCostBIN = GetD2GetItemStatCostBIN();
	D2ReadFile = GetD2ReadFile();
	D2LoadSuperuniques = GetD2LoadSuperuniques();
}

DWORD D2CommonLibrary::RetrieveStashGridOffset()
{
	return RetrieveAddressByAddition(CreateOffsets(0xC9F3, 0xCA03, 0x14ED3, 0x5FCB5, 0x2A505, 0x1BDB5, 0x82CA5, 0x6CC25));
}

D2CommonLibrary::TD2Common11084 D2CommonLibrary::GetD2Common11084()
{
	return (TD2Common11084)RetrieveAddressByProc(CreateOffsets(00000, 00000, 00000, 10188, 11084, 11109, 10346, 10907));
}

D2CommonLibrary::TD2GetLevelID D2CommonLibrary::GetD2GetLevelID()
{
	return (TD2GetLevelID)RetrieveAddressByProc(CreateOffsets(10057, 10057, 10057, 10332, 11021, 10511, 10826, 10691));
}

D2CommonLibrary::TD2GetDropRoom D2CommonLibrary::GetD2GetDropRoom()
{
	return (TD2GetDropRoom)RetrieveAddressByProc(CreateOffsets(10138, 10138, 10138, 10623, 10491, 11043, 10654, 10716));
}

D2CommonLibrary::TD2Common10242 D2CommonLibrary::GetD2Common10242()
{
	return (TD2Common10242)RetrieveAddressByProc(CreateOffsets(10242, 10242, 10242, 00000, 00000, 00000, 00000, 00000));
}

D2CommonLibrary::TD2CanPutItemInInv D2CommonLibrary::GetD2CanPutItemInInv()
{
	return (TD2CanPutItemInInv)RetrieveAddressByProc(CreateOffsets(10246, 10246, 10246, 10855, 10813, 10289, 10133, 10402));
}

D2CommonLibrary::TD2InvRemoveItem D2CommonLibrary::GetD2InvRemoveItem()
{
	return (TD2InvRemoveItem)RetrieveAddressByProc(CreateOffsets(10243, 10243, 10243, 10461, 10827, 10936, 10646, 10490));
}

D2CommonLibrary::TD2InvAddItem D2CommonLibrary::GetD2InvAddItem()
{
	return (TD2InvAddItem)RetrieveAddressByProc(CreateOffsets(10249, 10249, 10249, 10880, 11068, 10436, 11107, 10963));
}

D2CommonLibrary::TD2Common10250 D2CommonLibrary::GetD2Common10250()
{
	return (TD2Common10250)RetrieveAddressByProc(CreateOffsets(10250, 10250, 10250, 00000, 00000, 00000, 00000, 00000));
}

D2CommonLibrary::TD2Common10273 D2CommonLibrary::GetD2Common10273()
{
	return (TD2Common10273)RetrieveAddressByProc(CreateOffsets(10273, 10273, 10273, 00000, 00000, 00000, 00000, 00000));
}

D2CommonLibrary::TD2InventoryGetFirstItem D2CommonLibrary::GetD2InventoryGetFirstItem()
{
	return (TD2InventoryGetFirstItem)RetrieveAddressByProc(CreateOffsets(10277, 10277, 10277, 10402, 10535, 11151, 10460, 11040));
}

D2CommonLibrary::TD2UnitGetNextItem D2CommonLibrary::GetD2UnitGetNextItem()
{
	return (TD2UnitGetNextItem)RetrieveAddressByProc(CreateOffsets(10304, 10304, 10304, 10934, 11140, 10770, 10464, 10879));
}

D2CommonLibrary::TD2GetRealItem D2CommonLibrary::GetD2GetRealItem()
{
	return (TD2GetRealItem)RetrieveAddressByProc(CreateOffsets(10305, 10305, 10305, 11095, 10748, 10852, 11147, 10897));
}

// Not in 1.10
D2CommonLibrary::TD2GetPosX D2CommonLibrary::GetD2GetPosX()
{
	return (TD2GetPosX)RetrieveAddressByProc(CreateOffsets(10326, 10326, 00000, 00000, 00000, 00000, 00000, 00000));
}

// Not in 1.10
D2CommonLibrary::TD2GetPosY D2CommonLibrary::GetD2GetPosY()
{
	return (TD2GetPosY)RetrieveAddressByProc(CreateOffsets(10329, 10329, 00000, 00000, 00000, 00000, 00000, 00000));
}

D2CommonLibrary::TD2GetPosition D2CommonLibrary::GetD2GetPosition()
{
	return (TD2GetPosition)RetrieveAddressByProc(CreateOffsets(10332, 10332, 10332, 11080, 10056, 10543, 10141, 11166));
}

D2CommonLibrary::TD2GetMaxGoldBank D2CommonLibrary::GetD2GetMaxGoldBank()
{
	return (TD2GetMaxGoldBank)RetrieveAddressByProc(CreateOffsets(10339, 10339, 10339, 10455, 10864, 10941, 11060, 11025));
}

D2CommonLibrary::TD2GetRoom D2CommonLibrary::GetD2GetRoom()
{
	return (TD2GetRoom)RetrieveAddressByProc(CreateOffsets(10342, 10342, 10342, 10172, 10933, 10366, 10331, 10846));
}

D2CommonLibrary::TD2InitPlayerData D2CommonLibrary::GetD2InitPlayerData()
{
	return (TD2InitPlayerData)RetrieveAddressByProc(CreateOffsets(10420, 10420, 10420, 10218, 10079, 11097, 10356, 10404));
}

D2CommonLibrary::TD2GetPlayerData D2CommonLibrary::GetD2GetPlayerData()
{
	return (TD2GetPlayerData)RetrieveAddressByProc(CreateOffsets(10424, 10424, 10424, 10562, 10800, 10860, 10920, 11103));
}

D2CommonLibrary::TD2GetDefence D2CommonLibrary::GetD2GetDefence()
{
	return (TD2GetDefence)RetrieveAddressByProc(CreateOffsets(10431, 10431, 10431, 00000, 00000, 00000, 00000, 00000));
}

D2CommonLibrary::TD2GetChanceToBlock D2CommonLibrary::GetD2GetChanceToBlock()
{
	return (TD2GetChanceToBlock)RetrieveAddressByProc(CreateOffsets(10433, 10433, 10433, 00000, 00000, 00000, 00000, 00000));
}

D2CommonLibrary::TD2GetMaxGold D2CommonLibrary::GetD2GetMaxGold()
{
	return (TD2GetMaxGold)RetrieveAddressByProc(CreateOffsets(10439, 10439, 10439, 10343, 11131, 10729, 10049, 11159));
}

D2CommonLibrary::TD2Common10572 D2CommonLibrary::GetD2Common10572()
{
	return (TD2Common10572)RetrieveAddressByProc(CreateOffsets(00000, 00000, 00000, 10440, 10572, 10481, 11090, 10193));
}

D2CommonLibrary::TD2GetObjectFlags D2CommonLibrary::GetD2GetObjectFlags()
{
	return (TD2GetObjectFlags)RetrieveAddressByProc(CreateOffsets(00000, 00000, 00000, 10471, 11160, 10866, 10258, 10040));
}

D2CommonLibrary::TD2SetObjectFlags D2CommonLibrary::GetD2SetObjectFlags()
{
	return (TD2SetObjectFlags)RetrieveAddressByProc(CreateOffsets(00000, 00000, 00000, 10572, 11048, 10150, 10111, 10033));
}

D2CommonLibrary::TD2isInState D2CommonLibrary::GetD2isInState()
{
	return (TD2isInState)RetrieveAddressByProc(CreateOffsets(10487, 10487, 10487, 00000, 00000, 00000, 00000, 00000));
}

D2CommonLibrary::TD2AddPlayerStat D2CommonLibrary::GetD2AddPlayerStat()
{
	return (TD2AddPlayerStat)RetrieveAddressByProc(CreateOffsets(10518, 10518, 10518, 10109, 10627, 10762, 10551, 10645));
}

D2CommonLibrary::TD2GetPlayerStat D2CommonLibrary::GetD2GetPlayerStat()
{
	return (TD2GetPlayerStat)RetrieveAddressByProc(CreateOffsets(10519, 10519, 10519, 11092, 10061, 10658, 10973, 10550));
}

D2CommonLibrary::TD2GetPlayerBaseStat D2CommonLibrary::GetD2GetPlayerBaseStat()
{
	return (TD2GetPlayerBaseStat)RetrieveAddressByProc(CreateOffsets(10521, 10521, 10521, 10733, 10550, 10494, 10587, 10216));
}

D2CommonLibrary::TD2haveDefenceBonus D2CommonLibrary::GetD2haveDefenceBonus()
{
	return (TD2haveDefenceBonus)RetrieveAddressByProc(CreateOffsets(10539, 10539, 10539, 00000, 00000, 00000, 00000, 00000));
}

D2CommonLibrary::TD2haveFireResBonus D2CommonLibrary::GetD2haveFireResBonus()
{
	return (TD2haveFireResBonus)RetrieveAddressByProc(CreateOffsets(10540, 10540, 10540, 00000, 00000, 00000, 00000, 00000));
}

D2CommonLibrary::TD2haveColdResBonus D2CommonLibrary::GetD2haveColdResBonus()
{
	return (TD2haveColdResBonus)RetrieveAddressByProc(CreateOffsets(10541, 10541, 10541, 00000, 00000, 00000, 00000, 00000));
}

D2CommonLibrary::TD2haveLightResBonus D2CommonLibrary::GetD2haveLightResBonus()
{
	return (TD2haveLightResBonus)RetrieveAddressByProc(CreateOffsets(10542, 10542, 10542, 00000, 00000, 00000, 00000, 00000));
}

D2CommonLibrary::TD2havePoisonResBonus D2CommonLibrary::GetD2havePoisonResBonus()
{
	return (TD2havePoisonResBonus)RetrieveAddressByProc(CreateOffsets(10543, 10543, 10543, 00000, 00000, 00000, 00000, 00000));
}

D2CommonLibrary::TD2haveDefenceMalus D2CommonLibrary::GetD2haveDefenceMalus()
{
	return (TD2haveDefenceMalus)RetrieveAddressByProc(CreateOffsets(10546, 10546, 10546, 00000, 00000, 00000, 00000, 00000));
}

D2CommonLibrary::TD2haveFireResMalus D2CommonLibrary::GetD2haveFireResMalus()
{
	return (TD2haveFireResMalus)RetrieveAddressByProc(CreateOffsets(10547, 10547, 10547, 00000, 00000, 00000, 00000, 00000));
}

D2CommonLibrary::TD2haveColdResMalus D2CommonLibrary::GetD2haveColdResMalus()
{
	return (TD2haveColdResMalus)RetrieveAddressByProc(CreateOffsets(10548, 10548, 10548, 00000, 00000, 00000, 00000, 00000));
}

D2CommonLibrary::TD2haveLightResMalus D2CommonLibrary::GetD2haveLightResMalus()
{
	return (TD2haveLightResMalus)RetrieveAddressByProc(CreateOffsets(10549, 10549, 10549, 00000, 00000, 00000, 00000, 00000));
}

D2CommonLibrary::TD2havePoisonResMalus D2CommonLibrary::GetD2havePoisonResMalus()
{
	return (TD2havePoisonResMalus)RetrieveAddressByProc(CreateOffsets(10550, 10550, 10550, 00000, 00000, 00000, 00000, 00000));
}

D2CommonLibrary::TD2CompileTxtFile D2CommonLibrary::GetD2CompileTxtFile()
{
	return (TD2CompileTxtFile)RetrieveAddressByProc(CreateOffsets(10578, 10578, 10578, 10653, 10496, 10244, 10849, 10037));
}

D2CommonLibrary::TD2GetItemsBIN D2CommonLibrary::GetD2GetItemsBIN()
{
	return (TD2GetItemsBIN)RetrieveAddressByProc(CreateOffsets(10600, 10600, 10600, 10573, 10262, 10887, 10695, 10994));
}

D2CommonLibrary::TD2GetGemsBIN D2CommonLibrary::GetD2GetGemsBIN()
{
	return (TD2GetGemsBIN)RetrieveAddressByProc(CreateOffsets(10616, 10616, 10616, 10500, 10523, 10774, 10806, 10619));
}

D2CommonLibrary::TD2GetCubeMainBIN D2CommonLibrary::GetD2GetCubeMainBIN()
{
	return (TD2GetCubeMainBIN)RetrieveAddressByProc(CreateOffsets(11232, 11232, 11232, 10746, 10258, 10913, 10783, 10393));
}

D2CommonLibrary::TD2GetNbCubeMainBIN D2CommonLibrary::GetD2GetNbCubeMainBIN()
{
	return (TD2GetNbCubeMainBIN)RetrieveAddressByProc(CreateOffsets(11233, 11233, 11233, 10639, 11135, 10390, 10675, 10235));
}

D2CommonLibrary::TD2GetNextLevelXP D2CommonLibrary::GetD2GetNextLevelXP()
{
	return (TD2GetNextLevelXP)RetrieveAddressByProc(CreateOffsets(10628, 10628, 10628, 00000, 00000, 00000, 00000, 00000));
}

D2CommonLibrary::TD2GetMaxLevel D2CommonLibrary::GetD2GetMaxLevel()
{
	return (TD2GetMaxLevel)RetrieveAddressByProc(CreateOffsets(10629, 10629, 10629, 00000, 00000, 00000, 00000, 00000));
}

D2CommonLibrary::TD2GetDifficultyLevelsBIN D2CommonLibrary::GetD2GetDifficultyLevelsBIN()
{
	return (TD2GetDifficultyLevelsBIN)RetrieveAddressByProc(CreateOffsets(10655, 10655, 10655, 10655, 10309, 10297, 10218, 10694));
}

D2CommonLibrary::TD2GetItemQuality D2CommonLibrary::GetD2GetItemQuality()
{
	return (TD2GetItemQuality)RetrieveAddressByProc(CreateOffsets(10695, 10695, 10695, 10927, 10899, 10276, 10106, 10911));
}

D2CommonLibrary::TD2TestFlags D2CommonLibrary::GetD2TestFlags()
{
	return (TD2TestFlags)RetrieveAddressByProc(CreateOffsets(10707, 10707, 10707, 10911, 10303, 10989, 10202, 10458));
}

D2CommonLibrary::TD2GetItemLevel D2CommonLibrary::GetD2GetItemLevel()
{
	return (TD2GetItemLevel)RetrieveAddressByProc(CreateOffsets(10717, 10717, 10717, 10898, 10100, 10410, 10086, 10008));
}

D2CommonLibrary::TD2ItemGetPage D2CommonLibrary::GetD2ItemGetPage()
{
	return (TD2ItemGetPage)RetrieveAddressByProc(CreateOffsets(10719, 10719, 10719, 10820, 10505, 10370, 10020, 10810));
}

D2CommonLibrary::TD2ItemSetPage D2CommonLibrary::GetD2ItemSetPage()
{
	return (TD2ItemSetPage)RetrieveAddressByProc(CreateOffsets(10720, 10720, 10720, 10485, 10608, 10223, 10012, 11026));
}

D2CommonLibrary::TD2CheckItemType D2CommonLibrary::GetD2CheckItemType()
{
	return (TD2CheckItemType)RetrieveAddressByProc(CreateOffsets(10731, 10731, 10731, 11017, 10890, 10231, 10744, 10601));
}

D2CommonLibrary::TD2GetUniqueID D2CommonLibrary::GetD2GetUniqueID()
{
	return (TD2GetUniqueID)RetrieveAddressByProc(CreateOffsets(10732, 10732, 10732, 10692, 10685, 10280, 10620, 10075));
}

D2CommonLibrary::TD2SetAnim D2CommonLibrary::GetD2SetAnim()
{
	return (TD2SetAnim)RetrieveAddressByProc(CreateOffsets(10734, 10734, 10734, 00000, 00000, 00000, 00000, 00000));
}

D2CommonLibrary::TD2GetNbRunesBIN D2CommonLibrary::GetD2GetNbRunesBIN()
{
	return (TD2GetNbRunesBIN)RetrieveAddressByProc(CreateOffsets(10619, 10619, 10619, 10687, 10877, 10321, 11032, 10981));
}

D2CommonLibrary::TD2GetRunesBIN D2CommonLibrary::GetD2GetRunesBIN()
{
	return (TD2GetRunesBIN)RetrieveAddressByProc(CreateOffsets(10620, 10620, 10620, 10775, 10296, 10622, 10006, 10405));
}

D2CommonLibrary::TD2isEtheral D2CommonLibrary::GetD2isEtheral()
{
	return (TD2isEtheral)RetrieveAddressByProc(CreateOffsets(11163, 11163, 11163, 10880, 11068, 10436, 11107, 10963));
}

D2CommonLibrary::TD2SaveItem D2CommonLibrary::GetD2SaveItem()
{
	return (TD2SaveItem)RetrieveAddressByProc(CreateOffsets(10881, 10881, 10881, 10956, 11156, 10218, 10987, 10665));
}

D2CommonLibrary::TD2SetSkillBaseLevel D2CommonLibrary::GetD2SetSkillBaseLevel()
{
	return (TD2SetSkillBaseLevel)RetrieveAddressByProc(CreateOffsets(10953, 10953, 10953, 10099, 10255, 10210, 10302, 10335));
}

D2CommonLibrary::TD2GetSkillLevel D2CommonLibrary::GetD2GetSkillLevel()
{
	return (TD2GetSkillLevel)RetrieveAddressByProc(CreateOffsets(10968, 10968, 10968, 10700, 10109, 10904, 10306, 10007));
}

D2CommonLibrary::TD2GetSkillCost D2CommonLibrary::GetD2GetSkillCost()
{
	return (TD2GetSkillCost)RetrieveAddressByProc(CreateOffsets(11276, 11276, 11276, 10254, 10074, 10111, 10435, 11081));
}

D2CommonLibrary::TD2GetCharStatsBIN D2CommonLibrary::GetD2GetCharStatsBIN()
{
	return (TD2GetCharStatsBIN)RetrieveAddressByAddition(CreateOffsets(0, 0, 0x82C80, 0x15D0, 0x1800, 0x1220, 0x12D0, 0x17B0));
}

D2CommonLibrary::TD2CompileCubeInput D2CommonLibrary::GetD2CompileCubeInput()
{
	return (TD2CompileCubeInput)RetrieveAddressByAddition(CreateOffsets(0, 0, 0x12410, 0x5D7D0, 0x1A100, 0x116C0, 0x1C020, 0x5B0E0));
}

D2CommonLibrary::TD2CompileCubeOutput D2CommonLibrary::GetD2CompileCubeOutput()
{
	return (TD2CompileCubeOutput)RetrieveAddressByAddition(CreateOffsets(0, 0, 0x12910, 0x5D210, 0x19B40, 0x11100, 0x1BA60, 0x5AB20));
}

D2CommonLibrary::TD2GetItemTypesBIN D2CommonLibrary::GetD2GetItemTypesBIN()
{
	return (TD2GetItemTypesBIN)RetrieveAddressByAddition(CreateOffsets(0, 0, 0x2B1A0, 0x11F0, 0x1380, 0x1140, 0x1300, 0x1160));
}

D2CommonLibrary::TD2GetItemStatCostBIN D2CommonLibrary::GetD2GetItemStatCostBIN()
{
	return (TD2GetItemStatCostBIN)RetrieveAddressByAddition(CreateOffsets(0, 0, 0x642B0, 0x13F0, 0x12F0, 0x1540, 0x17A0, 0x17E0));
}

D2CommonLibrary::TD2ReadFile D2CommonLibrary::GetD2ReadFile()
{
	return (TD2ReadFile)RetrieveAddressByAddition(CreateOffsets(0x738A4, 0x739B4, 0x84268, 0x96E0, 0x98D0, 0x9900, 0x9900, 0xB5E0));
}

D2CommonLibrary::TD2LoadSuperuniques D2CommonLibrary::GetD2LoadSuperuniques()
{
	return (TD2LoadSuperuniques)RetrieveAddressByAddition(CreateOffsets(0x1F500, 0x1F510, 0x29FA0, 0x71EB0, 0x32AA0, 0x7D2A0, 0x59870, 0x80C40));
}