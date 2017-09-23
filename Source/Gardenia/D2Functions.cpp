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

// This file should be used when attempting to access any of the functions provided
// in the libraries. The reason for this is the following:
// 1. Most of the existing code currently attempts to find the global function reference to the function.
// 2. Some of the mem_seek operations (and possibly more) pass a function pointer to its call.
//    However, if the function has been redirected internally, then passing a function pointer to this
//    redirected library function will cause the application to crash or lead to unintended behavior.
// If you really want to use the library function directly (ideally we would), you should make sure
// that nothing breaks.
#include "common.h"

s_shifting shifting;

// D2Common
D2Common::TD2Common10242 D2Common10242;
D2Common::TD2CanPutItemInInv D2CanPutItemInInv;
D2Common::TD2InvRemoveItem D2InvRemoveItem;
D2Common::TD2InvAddItem D2InvAddItem;
D2Common::TD2Common10250 D2Common10250;
D2Common::TD2Common10273 D2Common10273;
D2Common::TD2InventoryGetFirstItem D2InventoryGetFirstItem;
D2Common::TD2UnitGetNextItem D2UnitGetNextItem;
D2Common::TD2GetRealItem D2GetRealItem;
D2Common::TD2GetPosX D2GetPosX;
D2Common::TD2GetPosY D2GetPosY;
D2Common::TD2GetMaxGoldBank D2GetMaxGoldBank;
D2Common::TD2InitPlayerData D2InitPlayerData;
D2Common::TD2GetPlayerData D2GetPlayerData;
D2Common::TD2GetDefence D2GetDefence;
D2Common::TD2GetChanceToBlock D2GetChanceToBlock;
D2Common::TD2GetMaxGold D2GetMaxGold;
D2Common::TD2isInState D2isInState;
D2Common::TD2AddPlayerStat D2AddPlayerStat;
D2Common::TD2GetPlayerStat D2GetPlayerStat;
D2Common::TD2GetPlayerBaseStat D2GetPlayerBaseStat;
D2Common::TD2haveDefenceBonus D2haveDefenceBonus;
D2Common::TD2haveFireResBonus D2haveFireResBonus;
D2Common::TD2haveColdResBonus D2haveColdResBonus;
D2Common::TD2haveLightResBonus D2haveLightResBonus;
D2Common::TD2havePoisonResBonus D2havePoisonResBonus;
D2Common::TD2haveDefenceMalus D2haveDefenceMalus;
D2Common::TD2haveFireResMalus D2haveFireResMalus;
D2Common::TD2haveColdResMalus D2haveColdResMalus;
D2Common::TD2haveLightResMalus D2haveLightResMalus;
D2Common::TD2havePoisonResMalus D2havePoisonResMalus;
D2Common::TD2CompileTxtFile D2CompileTxtFileDirect;
D2Common::TD2CompileTxtFile D2CompileTxtFile;
D2Common::TD2GetItemsBIN D2GetItemsBIN;
D2Common::TD2GetGemsBIN D2GetGemsBIN;
D2Common::TD2GetCubeMainBIN D2GetCubeMainBIN;
D2Common::TD2GetNbCubeMainBIN D2GetNbCubeMainBIN;
D2Common::TD2GetNextLevelXP D2GetNextLevelXP;
D2Common::TD2GetMaxLevel D2GetMaxLevel;
D2Common::TD2GetDifficultyLevelsBIN D2GetDifficultyLevelsBIN;
D2Common::TD2GetItemQuality D2GetItemQuality;
D2Common::TD2GetItemLevel D2GetItemLevel;
D2Common::TD2ItemGetPage D2ItemGetPage;
D2Common::TD2ItemSetPage D2ItemSetPage;
D2Common::TD2GetUniqueID D2GetUniqueID;
D2Common::TD2SetAnim D2SetAnim;
D2Common::TD2GetNbRunesBIN D2GetNbRunesBIN;
D2Common::TD2GetRunesBIN D2GetRunesBIN;
D2Common::TD2SaveItem D2SaveItem;
D2Common::TD2GetCharStatsBIN D2GetCharStatsBIN;
D2Common::TD2GetItemTypesBIN D2GetItemTypesBIN;
D2Common::TD2GetItemStatCostBIN D2GetItemStatCostBIN;
D2Common::TD2ReadFile D2ReadFile;
D2Common::TD2LoadSuperuniques D2LoadSuperuniques;

// D2Common: Only 1.09
D2Common::TD2Common10581 D2Common10581;
D2Common::TD2Common10598 D2Common10598;
D2Common::TD2Common10673 D2Common10673;

// D2Client
D2Client::TD2LoadImage D2LoadImage;
D2Client::TD2FreeImage D2FreeImage;
D2Client::TD2SendMsgToAll D2SendMsgToAll;
D2Client::TD2GetLastMonsterIDFight D2GetLastMonsterIDFight;
D2Client::TD2PrintStatsPage D2PrintStatsPage;
D2Client::TD2PrintStat D2PrintStat;
D2Client::TD2SetColorPopup D2SetColorPopup;
D2Client::TD2PlaySound D2PlaySound;
D2Client::TD2SendToServerXX D2SendToServerXX;
D2Client::TD2TogglePage D2TogglePage;
D2Client::TD2ClickOnStashButton D2ClickOnStashButton;
D2Client::TD2LoadBuySelBtn D2LoadBuySelBtn;
D2Client::TD2isLODGame D2isLODGame;

// D2Client: Only 1.10
D2Client::TD2GetDifficultyLevel D2GetDifficultyLevel;
D2Client::TD2GetMouseX D2GetMouseX;
D2Client::TD2GetMouseY D2GetMouseY;
D2Client::TD2GetClientPlayer D2GetClientPlayer;
D2Client::TD2CleanStatMouseUp D2CleanStatMouseUp;
D2Client::TD2SendToServer3 D2SendToServer3;

// D2Client: Variables
DWORD* ptResolutionY;
DWORD* ptResolutionX;
DWORD* ptNegWindowStartY;
DWORD* ptWindowStartX;
BYTE* ptDifficultyLevel;
DWORD* ptMouseY;
DWORD* ptMouseX;
Unit** ptptClientChar;
DWORD* ptNbStatDesc;
DWORD* ptStatDescTable;

// D2Game
D2Game::TD2SetNbPlayers D2SetNbPlayers;
D2Game::TD2SendPacket D2SendPacket;
D2Game::TD2LinkPortal D2LinkPortal;
D2Game::TD2VerifIfNotCarry1 D2VerifIfNotCarry1;
D2Game::TD2LoadInventory D2LoadInventory;
D2Game::TD2GameGetObject D2GameGetObject;

// D2Game: Only 1.10
D2Game::TD2GetClient D2GetClient;

// D2Game: Variables
NetClient** ptClientTable;

// D2Net
D2Net::TD2SendToServer D2SendToServer;
D2Net::TD2SendToClient D2SendToClient;

// Fog
Fog::TD2FogAssertOld D2FogAssertOld;
Fog::TD2FogAssert D2FogAssert;
Fog::TD2FogMemAlloc D2FogMemAlloc;
Fog::TD2FogMemDeAlloc D2FogMemDeAlloc;
Fog::TD2AllocMem D2AllocMem;
Fog::TD2FreeMem D2FreeMem;
Fog::TD2MPQOpenFile D2MPQOpenFile;
Fog::TD2MPQCloseFile D2MPQCloseFile;
Fog::TD2MPQReadFile D2MPQReadFile;
Fog::TD2MPQGetSizeFile D2MPQGetSizeFile;
Fog::TD2FogGetSavePath D2FogGetSavePath;
Fog::TD2FogGetInstallPath D2FogGetInstallPath;
Fog::TD2Fog10212 D2Fog10212;
Fog::TD2GetInstructionPointer D2GetInstructionPointer;

// D2Lang
D2Lang::TD2GetStringFromString D2GetStringFromString;
D2Lang::TD2GetStringFromIndex D2GetStringFromIndex;
D2Lang::TD2GetLang D2GetLang;
D2Lang::TD2PrintBigNumber D2PrintBigNumber;

// Storm
Storm::TD2StormMPQOpenFile D2StormMPQOpenFile;
Storm::TD2Storm503 D2Storm503;
Storm::TD2FreeWinMessage D2FreeWinMessage;

// D2gfx
D2gfx::TD2GetResolution D2GetResolution;
D2gfx::TD2FillArea D2FillArea;
D2gfx::TD2PrintImage D2PrintImage;

// D2Win
D2Win::TD2PrintLineOnTextBox D2PrintLineOnTextBox;
D2Win::TD2PrintString D2PrintString;
D2Win::TD2GetPixelLen D2GetPixelLen;
D2Win::TD2SetFont D2SetFont;
D2Win::TD2PrintPopup D2PrintPopup;
D2Win::TD2GetPixelRect D2GetPixelRect;
D2Win::TD2PrintTextPopup D2PrintTextPopup;
D2Win::TD2CreateTextBox D2CreateTextBox;

// D2CMP
D2CMP::TD2CMP10014 D2CMP10014;

DataTables* SgptDataTables;

void setImage(sDrawImageInfo* data, void* image){((void**)data)[shifting.ptImage/4]=image;}//0x4 0x8 0x3C
void setFrame(sDrawImageInfo* data, DWORD frame){((DWORD*)data)[shifting.ptFrame/4]=frame;}//0x8 0x44 0x40

void initD2functions()
{
	// D2Common
	D2Common10242 = D2Common::D2Common10242;
	D2CanPutItemInInv = D2Common::D2CanPutItemInInv;
	D2InvRemoveItem = D2Common::D2InvRemoveItem;
	D2InvAddItem = D2Common::D2InvAddItem;
	D2Common10250 = D2Common::D2Common10250;
	D2Common10273 = D2Common::D2Common10273;
	D2InventoryGetFirstItem = D2Common::D2InventoryGetFirstItem;
	D2UnitGetNextItem = D2Common::D2UnitGetNextItem;
	D2GetRealItem = D2Common::D2GetRealItem();
	D2GetPosX = D2Common::D2GetPosX;
	D2GetPosY = D2Common::D2GetPosY;
	D2GetMaxGoldBank = D2Common::D2GetMaxGoldBank;
	D2InitPlayerData = D2Common::D2InitPlayerData;
	D2GetPlayerData = D2Common::D2GetPlayerData;
	D2GetDefence = D2Common::D2GetDefence;
	D2GetChanceToBlock = D2Common::D2GetChanceToBlock;
	D2GetMaxGold = D2Common::D2GetMaxGold;
	D2isInState = D2Common::D2isInState;
	D2AddPlayerStat = D2Common::D2AddPlayerStat();
	D2GetPlayerStat = D2Common::D2GetPlayerStat();
	D2GetPlayerBaseStat = D2Common::D2GetPlayerBaseStat();
	D2haveDefenceBonus = D2Common::D2haveDefenceBonus;
	D2haveFireResBonus = D2Common::D2haveFireResBonus;
	D2haveColdResBonus = D2Common::D2haveColdResBonus;
	D2haveLightResBonus = D2Common::D2haveLightResBonus;
	D2havePoisonResBonus = D2Common::D2havePoisonResBonus;
	D2haveDefenceMalus = D2Common::D2haveDefenceMalus;
	D2haveFireResMalus = D2Common::D2haveFireResMalus;
	D2haveColdResMalus = D2Common::D2haveColdResMalus;
	D2haveLightResMalus = D2Common::D2haveLightResMalus;
	D2havePoisonResMalus = D2Common::D2havePoisonResMalus;
	D2CompileTxtFileDirect = D2Common::D2CompileTxtFileDirect;
	D2CompileTxtFile = D2Common::D2CompileTxtFile();
	D2GetItemsBIN = D2Common::D2GetItemsBIN;
	D2GetGemsBIN = D2Common::D2GetGemsBIN;
	D2GetCubeMainBIN = D2Common::D2GetCubeMainBIN;
	D2GetNbCubeMainBIN = D2Common::D2GetNbCubeMainBIN;
	D2GetNextLevelXP = D2Common::D2GetNextLevelXP;
	D2GetMaxLevel = D2Common::D2GetMaxLevel;
	D2GetDifficultyLevelsBIN = D2Common::D2GetDifficultyLevelsBIN;
	D2GetItemQuality = D2Common::D2GetItemQuality;
	D2GetItemLevel = D2Common::D2GetItemLevel;
	D2ItemGetPage = D2Common::D2ItemGetPage;
	D2ItemSetPage = D2Common::D2ItemSetPage;
	D2GetUniqueID = D2Common::D2GetUniqueID;
	D2SetAnim = D2Common::D2SetAnim;
	D2GetNbRunesBIN = D2Common::D2GetNbRunesBIN;
	D2GetRunesBIN = D2Common::D2GetRunesBIN;
	D2SaveItem = D2Common::D2SaveItem;
	D2GetCharStatsBIN = D2Common::D2GetCharStatsBIN();
	D2GetItemTypesBIN = D2Common::D2GetItemTypesBIN();
	D2GetItemStatCostBIN = D2Common::D2GetItemStatCostBIN();
	D2ReadFile = D2Common::D2ReadFile;
	D2LoadSuperuniques = D2Common::D2LoadSuperuniques;

	// D2Client
	D2LoadImage = D2Client::D2LoadImage();
	D2FreeImage = D2Client::D2FreeImage();
	D2SendMsgToAll = D2Client::D2SendMsgToAll();
	D2GetLastMonsterIDFight = D2Client::D2GetLastMonsterIDFight;
	D2PrintStatsPage = D2Client::D2PrintStatsPage;
	D2PrintStat = D2Client::D2PrintStat();
	D2SetColorPopup = D2Client::D2SetColorPopup();
	D2PlaySound = D2Client::D2PlaySound();
	D2SendToServerXX = D2Client::D2SendToServerXX;
	D2TogglePage = D2Client::D2TogglePage;
	D2ClickOnStashButton = D2Client::D2ClickOnStashButton;
	D2LoadBuySelBtn = D2Client::D2LoadBuySelBtn;
	D2isLODGame = D2Client::IsExpansion();
	
	// D2Client: Only 1.10
	D2GetDifficultyLevel = D2Client::D2GetDifficultyLevel();
	D2GetMouseX = D2Client::D2GetMouseX();
	D2GetMouseY = D2Client::D2GetMouseY();
	D2GetClientPlayer = D2Client::D2GetClientPlayer();
	D2CleanStatMouseUp = D2Client::D2CleanStatMouseUp;
	D2SendToServer3 = D2Client::D2SendToServer3();

	// D2Client: Variables
	ptResolutionY = D2Client::ptResolutionY;
	ptResolutionX = D2Client::ptResolutionX;
	ptNegWindowStartY = D2Client::ptNegWindowStartY;
	ptWindowStartX = D2Client::ptWindowStartX;
	ptDifficultyLevel = D2Client::ptDifficultyLevel;
	ptMouseY = D2Client::ptMouseY;
	ptMouseX = D2Client::ptMouseX;
	ptptClientChar = D2Client::ptptClientChar;
	ptNbStatDesc = D2Client::ptNbStatDesc;
	ptStatDescTable = D2Client::ptStatDescTable;

	// D2Game
	D2SetNbPlayers = D2Game::D2SetNbPlayers;
	D2SendPacket = D2Game::D2SendPacket();
	D2LinkPortal = D2Game::D2LinkPortal;
	D2VerifIfNotCarry1 = D2Game::D2VerifIfNotCarry1();
	D2LoadInventory = D2Game::D2LoadInventory();
	D2GameGetObject = D2Game::D2GameGetObject();

	// D2Game: Only 1.10
	D2GetClient = D2Game::D2GetClient();

	// D2Game: Variables
	ptClientTable = D2Game::ptClientTable;

	// D2Net
	D2SendToServer = D2Net::D2SendToServer();
	D2SendToClient = D2Net::D2SendToClient;

	// Fog
	D2FogAssertOld = Fog::D2FogAssertOld;
	D2FogAssert = Fog::D2FogAssert;
	D2FogMemAlloc = Fog::D2FogMemAlloc;
	D2FogMemDeAlloc = Fog::D2FogMemDeAlloc;
	D2AllocMem = Fog::D2AllocMem;
	D2FreeMem = Fog::D2FreeMem;
	D2MPQOpenFile = Fog::D2MPQOpenFile;
	D2MPQCloseFile = Fog::D2MPQCloseFile;
	D2MPQReadFile = Fog::D2MPQReadFile;
	D2MPQGetSizeFile = Fog::D2MPQGetSizeFile;
	D2FogGetSavePath = Fog::D2FogGetSavePath;
	D2FogGetInstallPath = Fog::D2FogGetInstallPath;
	D2Fog10212 = Fog::D2Fog10212;
	D2GetInstructionPointer = Fog::D2GetInstructionPointer;

	// D2Lang
	D2GetStringFromString = D2Lang::D2GetStringFromString;
	D2GetStringFromIndex = D2Lang::D2GetStringFromIndex;
	D2GetLang = D2Lang::D2GetLang;
	D2PrintBigNumber = D2Lang::D2PrintBigNumber;

	// Storm
	D2StormMPQOpenFile = Storm::D2StormMPQOpenFile;
	D2Storm503 = Storm::D2Storm503;
	D2FreeWinMessage = Storm::D2FreeWinMessage;

	// D2gfx
	D2GetResolution = D2gfx::D2GetResolution;
	D2FillArea = D2gfx::D2FillArea;
	D2PrintImage = D2gfx::D2PrintImage;

	// D2Win
	D2PrintLineOnTextBox = D2Win::D2PrintLineOnTextBox;
	D2PrintString = D2Win::D2PrintString;
	D2GetPixelLen = D2Win::D2GetPixelLen;
	D2SetFont = D2Win::D2SetFont;
	D2PrintPopup = D2Win::D2PrintPopup;
	D2GetPixelRect = D2Win::D2GetPixelRect;
	D2PrintTextPopup = D2Win::D2PrintTextPopup;
	D2CreateTextBox = D2Win::D2CreateTextBox;
	
	// D2CMP
	D2CMP10014 = D2CMP::D2CMP10014;

	SgptDataTables = *(DataTables**)D2Common::GetOffsetByAddition(0, 0xA33F0);

	if (VersionUtility::Is109B())
	{
		D2Common10581 = D2Common::D2Common10581;
		D2Common10598 = D2Common::D2Common10598;
		D2Common10673 = D2Common::D2Common10673;
	}

	//////////////// STRUCTURE MANAGEMENT ////////////////

	shifting.ptPYPlayerData = *(DWORD*)((DWORD)D2InitPlayerData + D2Common::ptPYPlayerDataOffset);
	shifting.ptSpecificData = D2Common::ptSpecificDataOffset;
	shifting.ptGame = D2Common::ptGameOffset;
	shifting.ptClientGame = D2Common::ptClientGameOffset;
	shifting.ptInventory = D2Common::ptInventoryOffset;
	shifting.ptSkills = D2Common::ptSkillsOffset;
	shifting.ptImage = D2Common::ptImageOffset;
	shifting.ptFrame = D2Common::ptFrameOffset;
}