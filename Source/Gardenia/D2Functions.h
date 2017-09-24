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

#include "Utilities\LibraryLoader.h"

// Conversion to 1.09
struct s_shifting {
	DWORD ptInventory;
	DWORD ptSpecificData;
	DWORD ptPYPlayerData;
	DWORD ptGame;
	DWORD ptClientGame;
	DWORD ptSkills;
	DWORD ptImage;
	DWORD ptFrame;
};
extern s_shifting shifting;

#define FCT_ASM(N) __declspec(naked) void N() {__asm{
#define RANDOM(V) ((int)(rand()/(RAND_MAX+1.0)*(V)))

#define PCPlayerData (*(PlayerData**)((DWORD)(ptChar)+shifting.ptSpecificData)) //->ptPlayerData
#define PCGame (*(GameStruct**)((DWORD)(ptChar)+shifting.ptGame)) //->ptGame
#define PClientGame (*(GameStruct**)((DWORD)(ptClient)+shifting.ptClientGame)) //ptClient->ptGame
#define PCInventory (*(Inventory**)((DWORD)(ptChar)+shifting.ptInventory)) //->ptInventory
#define PCPY ((PYPlayerData*)((DWORD)PCPlayerData+shifting.ptPYPlayerData)) //->ptPYPlayerData
#define PCSkills (*(Skills**)((DWORD)(ptChar)+shifting.ptSkills)) //->ptSkills

#define RX(v) (*ptWindowStartX + (v))
#define RY(v) (D2Client::ResolutionY() + *ptNegWindowStartY - (v))

// D2Common
extern D2Common::TD2Common10242 D2Common10242;
extern D2Common::TD2CanPutItemInInv D2CanPutItemInInv;
extern D2Common::TD2InvRemoveItem D2InvRemoveItem;
extern D2Common::TD2InvAddItem D2InvAddItem;
extern D2Common::TD2Common10250 D2Common10250;
extern D2Common::TD2Common10273 D2Common10273;
extern D2Common::TD2InventoryGetFirstItem D2InventoryGetFirstItem;
extern D2Common::TD2UnitGetNextItem D2UnitGetNextItem;
extern D2Common::TD2GetRealItem D2GetRealItem;
extern D2Common::TD2GetPosX D2GetPosX;
extern D2Common::TD2GetPosY D2GetPosY;
extern D2Common::TD2GetMaxGoldBank D2GetMaxGoldBank;
extern D2Common::TD2InitPlayerData D2InitPlayerData;
extern D2Common::TD2GetPlayerData D2GetPlayerData;
extern D2Common::TD2GetDefence D2GetDefence;
extern D2Common::TD2GetChanceToBlock D2GetChanceToBlock;
extern D2Common::TD2GetMaxGold D2GetMaxGold;
extern D2Common::TD2isInState D2isInState;
extern D2Common::TD2AddPlayerStat D2AddPlayerStat;
extern D2Common::TD2GetPlayerStat D2GetPlayerStat;
extern D2Common::TD2GetPlayerBaseStat D2GetPlayerBaseStat;
extern D2Common::TD2haveDefenceBonus D2haveDefenceBonus;
extern D2Common::TD2haveFireResBonus D2haveFireResBonus;
extern D2Common::TD2haveColdResBonus D2haveColdResBonus;
extern D2Common::TD2haveLightResBonus D2haveLightResBonus;
extern D2Common::TD2havePoisonResBonus D2havePoisonResBonus;
extern D2Common::TD2haveDefenceMalus D2haveDefenceMalus;
extern D2Common::TD2haveFireResMalus D2haveFireResMalus;
extern D2Common::TD2haveColdResMalus D2haveColdResMalus;
extern D2Common::TD2haveLightResMalus D2haveLightResMalus;
extern D2Common::TD2havePoisonResMalus D2havePoisonResMalus;
extern D2Common::TD2CompileTxtFile D2CompileTxtFileDirect;
extern D2Common::TD2GetItemsBIN D2GetItemsBIN;
extern D2Common::TD2GetGemsBIN D2GetGemsBIN;
extern D2Common::TD2GetCubeMainBIN D2GetCubeMainBIN;
extern D2Common::TD2GetNbCubeMainBIN D2GetNbCubeMainBIN;
extern D2Common::TD2GetNextLevelXP D2GetNextLevelXP;
extern D2Common::TD2GetMaxLevel D2GetMaxLevel;
extern D2Common::TD2GetDifficultyLevelsBIN D2GetDifficultyLevelsBIN;
extern D2Common::TD2GetItemQuality D2GetItemQuality;
extern D2Common::TD2GetItemLevel D2GetItemLevel;
extern D2Common::TD2ItemGetPage D2ItemGetPage;
extern D2Common::TD2ItemSetPage D2ItemSetPage;
extern D2Common::TD2GetUniqueID D2GetUniqueID;
extern D2Common::TD2SetAnim D2SetAnim;
extern D2Common::TD2GetNbRunesBIN D2GetNbRunesBIN;
extern D2Common::TD2GetRunesBIN D2GetRunesBIN;
extern D2Common::TD2SaveItem D2SaveItem;
extern D2Common::TD2GetCharStatsBIN D2GetCharStatsBIN;
extern D2Common::TD2GetItemTypesBIN D2GetItemTypesBIN;
extern D2Common::TD2GetItemStatCostBIN D2GetItemStatCostBIN;
extern D2Common::TD2ReadFile D2ReadFile;
extern D2Common::TD2LoadSuperuniques D2LoadSuperuniques;

// D2Common: Only 1.09
extern D2Common::TD2Common10581 D2Common10581;
extern D2Common::TD2Common10598 D2Common10598;
extern D2Common::TD2Common10673 D2Common10673;

// D2Client
extern D2Client::TD2LoadImage D2LoadImage;
extern D2Client::TD2FreeImage D2FreeImage;
extern D2Client::TD2SendMsgToAll D2SendMsgToAll;
extern D2Client::TD2PrintStatsPage D2PrintStatsPage;
extern D2Client::TD2PrintStat D2PrintStat;
extern D2Client::TD2SetColorPopup D2SetColorPopup;
extern D2Client::TD2PlaySound D2PlaySound;
extern D2Client::TD2TogglePage D2TogglePage;
extern D2Client::TD2LoadBuySelBtn D2LoadBuySelBtn;

// D2Client: Only 1.10
extern D2Client::TD2isLODGame D2isLODGame;
extern D2Client::TD2GetMouseX D2GetMouseX;
extern D2Client::TD2GetMouseY D2GetMouseY;
extern D2Client::TD2GetClientPlayer D2GetClientPlayer;
extern D2Client::TD2CleanStatMouseUp D2CleanStatMouseUp;
extern D2Client::TD2SendToServer3 D2SendToServer3;

// D2Client: Variables
extern DWORD* ptResolutionY;
extern DWORD* ptResolutionX;
extern DWORD* ptNegWindowStartY;
extern DWORD* ptWindowStartX;

extern DWORD* ptNbStatDesc;
extern DWORD* ptStatDescTable;

// D2Game
extern D2Game::TD2SetNbPlayers D2SetNbPlayers;
extern D2Game::TD2SendPacket D2SendPacket;
extern D2Game::TD2LoadInventory D2LoadInventory;
extern D2Game::TD2GameGetObject D2GameGetObject;

// D2Game: Only 1.10
extern D2Game::TD2GetClient D2GetClient;

// D2Game: Variables
extern NetClient** ptClientTable;

// D2Net
extern D2Net::TD2SendToServer D2SendToServer;
extern D2Net::TD2SendToClient D2SendToClient;

// Fog
extern Fog::TD2FogAssertOld D2FogAssertOld;
extern Fog::TD2FogMemAlloc D2FogMemAlloc;
extern Fog::TD2FogMemDeAlloc D2FogMemDeAlloc;
extern Fog::TD2AllocMem D2AllocMem;
extern Fog::TD2FreeMem D2FreeMem;
extern Fog::TD2MPQOpenFile D2MPQOpenFile;
extern Fog::TD2MPQCloseFile D2MPQCloseFile;
extern Fog::TD2MPQReadFile D2MPQReadFile;
extern Fog::TD2MPQGetSizeFile D2MPQGetSizeFile;
extern Fog::TD2FogGetSavePath D2FogGetSavePath;
extern Fog::TD2FogGetInstallPath D2FogGetInstallPath;
extern Fog::TD2Fog10212 D2Fog10212;

// D2Lang
extern D2Lang::TD2GetStringFromString D2GetStringFromString;
extern D2Lang::TD2GetStringFromIndex D2GetStringFromIndex;
extern D2Lang::TD2GetLang D2GetLang;
extern D2Lang::TD2PrintBigNumber D2PrintBigNumber;

// Storm
extern Storm::TD2StormMPQOpenFile D2StormMPQOpenFile;
extern Storm::TD2Storm503 D2Storm503;
extern Storm::TD2FreeWinMessage D2FreeWinMessage;

// D2gfx
extern D2gfx::TD2GetResolution D2GetResolution;
extern D2gfx::TD2FillArea D2FillArea;
extern D2gfx::TD2PrintImage D2PrintImage;

// D2Win
extern D2Win::TD2PrintLineOnTextBox D2PrintLineOnTextBox;
extern D2Win::TD2PrintString D2PrintString;
extern D2Win::TD2GetPixelLen D2GetPixelLen;
extern D2Win::TD2SetFont D2SetFont;
extern D2Win::TD2PrintPopup D2PrintPopup;
extern D2Win::TD2GetPixelRect D2GetPixelRect;
extern D2Win::TD2PrintTextPopup D2PrintTextPopup;
extern D2Win::TD2CreateTextBox D2CreateTextBox;

// D2CMP
extern D2CMP::TD2CMP10014 D2CMP10014;

extern void* (__stdcall *D2CompileTxtFile)(DWORD unused, const char* filename, BINField* ptFields, DWORD* ptRecordCount, DWORD recordLength);
void setImage(sDrawImageInfo* data, void* image);
void setFrame(sDrawImageInfo* data, DWORD frame);
void __inline fillRect(DWORD x, DWORD y, DWORD Width, DWORD Height, DWORD color, DWORD transTbl){D2FillArea(x,y,x+Width,y+Height,color,transTbl);};

#define GameTypeMode (*ptGameTypeMode)
#define ClientTable (*ptClientTable)

void initD2functions();