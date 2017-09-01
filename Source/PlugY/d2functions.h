/*================================================
	File created by Yohann NICOLAS.
	Add support 1.13d by L'Autour.

    This file implements some common and useful
    function related to some Diablo II mechanisms.

================================================*/
#pragma once

#include "D2CommonLibrary.h"
#include "D2ClientLibrary.h"
#include "D2GameLibrary.h"
#include "D2NetLibrary.h"
#include "FogLibrary.h"
#include "D2LangLibrary.h"
#include "StormLibrary.h"
#include "D2gfxLibrary.h"
#include "D2WinLibrary.h"
#include "D2CMPLibrary.h"

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

#define FASTCALL __fastcall
#define STDCALL		__stdcall
#define FCT_ASM(N) __declspec(naked) void N() {__asm{
#define RANDOM(V) ((int)(rand()/(RAND_MAX+1.0)*(V)))

#define PCPlayerData (*(PlayerData**)((DWORD)(ptChar)+shifting.ptSpecificData)) //->ptPlayerData
#define PCGame (*(Game**)((DWORD)(ptChar)+shifting.ptGame)) //->ptGame
#define PClientGame (*(Game**)((DWORD)(ptClient)+shifting.ptClientGame)) //ptClient->ptGame
#define PCInventory (*(Inventory**)((DWORD)(ptChar)+shifting.ptInventory)) //->ptInventory
#define PCPY ((PYPlayerData*)((DWORD)PCPlayerData+shifting.ptPYPlayerData)) //->ptPYPlayerData
#define PCSkills (*(Skills**)((DWORD)(ptChar)+shifting.ptSkills)) //->ptSkills

// offset of dll + corresponding offset depending on version
#define R7(Z,A,B,C,D,E,F,G,H) (offset_##Z + (version_##Z == VersionUtility::Versions::V113d? 0x##H : (version_##Z == VersionUtility::Versions::V113c? 0x##G : (version_##Z == VersionUtility::Versions::V112? 0x##F : (version_##Z == VersionUtility::Versions::V111b? 0x##E : (version_##Z == VersionUtility::Versions::V111? 0x##D : (version_##Z == VersionUtility::Versions::V110? 0x##C : (version_##Z == VersionUtility::Versions::V109d? 0x##B : 0x##A))))))))

// offset depends on version
#define V7(Z,A,B,C,D,E,F,G,H) (version_##Z == VersionUtility::Versions::V113d? 0x##H : (version_##Z == VersionUtility::Versions::V113c? 0x##G : (version_##Z == VersionUtility::Versions::V112? 0x##F : (version_##Z == VersionUtility::Versions::V111b? 0x##E : (version_##Z == VersionUtility::Versions::V111? 0x##D : (version_##Z == VersionUtility::Versions::V110? 0x##C : (version_##Z == VersionUtility::Versions::V109d? 0x##B : 0x##A)))))))

#define RX(v) (WindowStartX+(v))
#define RY(v) (ResolutionY+NegWindowStartY-(v))

#define D2S(F, I, R, N, P)	typedef R (STDCALL  *T##N) P; extern T##N N; //static D N = (D)(A);
#define D2F(F, I, R, N, P)	typedef R (FASTCALL *T##N) P; extern T##N N; //static D N = (D)(A);
#define E2S(F, A, R, N, P)	typedef R (STDCALL  *T##N) P; extern T##N N;
#define E2F(F, A, R, N, P)	typedef R (FASTCALL *T##N) P; extern T##N N;
#define E2C(F, A, T, N)		extern T* pt##N;
#define F7(X, Z, A,B,C,D,E,F,G,H, R, N, P) typedef R (X##CALL  *T##N) P;extern T##N N;
#define A7(X, Z, A,B,C,D,E,F,G,H, R, N, P) typedef R (X##CALL  *T##N) P; extern T##N N;
#define C7(Z, A,B,C,D,E,F,G,H, T, N)       extern T* pt##N;

// At this point only typedef and externs are implemented
#include "../Commons/D2Funcs.h"

// D2Common
extern D2CommonLibrary::TD2Common11084 D2Common11084;
extern D2CommonLibrary::TD2GetLevelID D2GetLevelID;
extern D2CommonLibrary::TD2GetDropRoom D2GetDropRoom;
extern D2CommonLibrary::TD2Common10242 D2Common10242;
extern D2CommonLibrary::TD2CanPutItemInInv D2CanPutItemInInv;
extern D2CommonLibrary::TD2InvRemoveItem D2InvRemoveItem;
extern D2CommonLibrary::TD2InvAddItem D2InvAddItem;
extern D2CommonLibrary::TD2Common10250 D2Common10250;
extern D2CommonLibrary::TD2Common10273 D2Common10273;
extern D2CommonLibrary::TD2InventoryGetFirstItem D2InventoryGetFirstItem;
extern D2CommonLibrary::TD2UnitGetNextItem D2UnitGetNextItem;
extern D2CommonLibrary::TD2GetRealItem D2GetRealItem;
extern D2CommonLibrary::TD2GetPosX D2GetPosX;
extern D2CommonLibrary::TD2GetPosY D2GetPosY;
extern D2CommonLibrary::TD2GetPosition D2GetPosition;
extern D2CommonLibrary::TD2GetMaxGoldBank D2GetMaxGoldBank;
extern D2CommonLibrary::TD2GetRoom D2GetRoom;
extern D2CommonLibrary::TD2InitPlayerData D2InitPlayerData;
extern D2CommonLibrary::TD2GetPlayerData D2GetPlayerData;
extern D2CommonLibrary::TD2GetDefence D2GetDefence;
extern D2CommonLibrary::TD2GetChanceToBlock D2GetChanceToBlock;
extern D2CommonLibrary::TD2GetMaxGold D2GetMaxGold;
extern D2CommonLibrary::TD2Common10572 D2Common10572;
extern D2CommonLibrary::TD2GetObjectFlags D2GetObjectFlags;
extern D2CommonLibrary::TD2SetObjectFlags D2SetObjectFlags;
extern D2CommonLibrary::TD2isInState D2isInState;
extern D2CommonLibrary::TD2AddPlayerStat D2AddPlayerStat;
extern D2CommonLibrary::TD2GetPlayerStat D2GetPlayerStat;
extern D2CommonLibrary::TD2GetPlayerBaseStat D2GetPlayerBaseStat;
extern D2CommonLibrary::TD2haveDefenceBonus D2haveDefenceBonus;
extern D2CommonLibrary::TD2haveFireResBonus D2haveFireResBonus;
extern D2CommonLibrary::TD2haveColdResBonus D2haveColdResBonus;
extern D2CommonLibrary::TD2haveLightResBonus D2haveLightResBonus;
extern D2CommonLibrary::TD2havePoisonResBonus D2havePoisonResBonus;
extern D2CommonLibrary::TD2haveDefenceMalus D2haveDefenceMalus;
extern D2CommonLibrary::TD2haveFireResMalus D2haveFireResMalus;
extern D2CommonLibrary::TD2haveColdResMalus D2haveColdResMalus;
extern D2CommonLibrary::TD2haveLightResMalus D2haveLightResMalus;
extern D2CommonLibrary::TD2havePoisonResMalus D2havePoisonResMalus;
extern D2CommonLibrary::TD2CompileTxtFile D2CompileTxtFile;
extern D2CommonLibrary::TD2GetItemsBIN D2GetItemsBIN;
extern D2CommonLibrary::TD2GetGemsBIN D2GetGemsBIN;
extern D2CommonLibrary::TD2GetCubeMainBIN D2GetCubeMainBIN;
extern D2CommonLibrary::TD2GetNbCubeMainBIN D2GetNbCubeMainBIN;
extern D2CommonLibrary::TD2GetNextLevelXP D2GetNextLevelXP;
extern D2CommonLibrary::TD2GetMaxLevel D2GetMaxLevel;
extern D2CommonLibrary::TD2GetDifficultyLevelsBIN D2GetDifficultyLevelsBIN;
extern D2CommonLibrary::TD2GetItemQuality D2GetItemQuality;
extern D2CommonLibrary::TD2TestFlags D2TestFlags;
extern D2CommonLibrary::TD2GetItemLevel D2GetItemLevel;
extern D2CommonLibrary::TD2ItemGetPage D2ItemGetPage;
extern D2CommonLibrary::TD2ItemSetPage D2ItemSetPage;
extern D2CommonLibrary::TD2CheckItemType D2CheckItemType;
extern D2CommonLibrary::TD2GetUniqueID D2GetUniqueID;
extern D2CommonLibrary::TD2SetAnim D2SetAnim;
extern D2CommonLibrary::TD2GetNbRunesBIN D2GetNbRunesBIN;
extern D2CommonLibrary::TD2GetRunesBIN D2GetRunesBIN;
extern D2CommonLibrary::TD2isEtheral D2isEtheral;
extern D2CommonLibrary::TD2SaveItem D2SaveItem;
extern D2CommonLibrary::TD2SetSkillBaseLevel D2SetSkillBaseLevel;
extern D2CommonLibrary::TD2GetSkillLevel D2GetSkillLevel;
extern D2CommonLibrary::TD2GetSkillCost D2GetSkillCost;
extern D2CommonLibrary::TD2GetCharStatsBIN D2GetCharStatsBIN;
extern D2CommonLibrary::TD2CompileCubeInput D2CompileCubeInput;
extern D2CommonLibrary::TD2CompileCubeOutput D2CompileCubeOutput;
extern D2CommonLibrary::TD2GetItemTypesBIN D2GetItemTypesBIN;
extern D2CommonLibrary::TD2GetItemStatCostBIN D2GetItemStatCostBIN;
extern D2CommonLibrary::TD2ReadFile D2ReadFile;
extern D2CommonLibrary::TD2LoadSuperuniques D2LoadSuperuniques;

// D2Client
extern D2ClientLibrary::TD2LoadImage D2LoadImage;
extern D2ClientLibrary::TD2FreeImage D2FreeImage;
extern D2ClientLibrary::TD2SendMsgToAll D2SendMsgToAll;
extern D2ClientLibrary::TD2GetLastMonsterIDFight D2GetLastMonsterIDFight;
extern D2ClientLibrary::TD2PrintStatsPage D2PrintStatsPage;
extern D2ClientLibrary::TD2PrintStat D2PrintStat;
extern D2ClientLibrary::TD2SetColorPopup D2SetColorPopup;
extern D2ClientLibrary::TD2PlaySound D2PlaySound;
extern D2ClientLibrary::TD2GetCurrentNPC D2GetCurrentNPC;
extern D2ClientLibrary::TD2SendToServerXX D2SendToServerXX;
extern D2ClientLibrary::TD2TogglePage D2TogglePage;
extern D2ClientLibrary::TD2ClickOnStashButton D2ClickOnStashButton;
extern D2ClientLibrary::TD2LoadBuySelBtn D2LoadBuySelBtn;
extern D2ClientLibrary::TD2ReloadGambleScreen D2ReloadGambleScreen;

// D2Client: Only 1.10
extern D2ClientLibrary::TD2isLODGame D2isLODGame;
extern D2ClientLibrary::TD2GetDifficultyLevel D2GetDifficultyLevel;
extern D2ClientLibrary::TD2GetMouseX D2GetMouseX;
extern D2ClientLibrary::TD2GetMouseY D2GetMouseY;
extern D2ClientLibrary::TD2GetClientPlayer D2GetClientPlayer;
extern D2ClientLibrary::TD2CleanStatMouseUp D2CleanStatMouseUp;
extern D2ClientLibrary::TD2SendToServer3 D2SendToServer3;

// D2Client: Variables
extern DWORD* ptResolutionY;
extern DWORD* ptResolutionX;
extern DWORD* ptNegWindowStartY;
extern DWORD* ptWindowStartX;
extern DWORD* ptIsLodGame;
extern BYTE* ptDifficultyLevel;
extern DWORD* ptMouseY;
extern DWORD* ptMouseX;
extern Unit** ptptClientChar;
extern DWORD* ptNbStatDesc;
extern DWORD* ptStatDescTable;

// D2Game
extern D2GameLibrary::TD2SetNbPlayers D2SetNbPlayers;
extern D2GameLibrary::TD2AddClient D2AddClient;
extern D2GameLibrary::TD2GetGameByClientID D2GetGameByClientID;
extern D2GameLibrary::TD2BroadcastFunction D2BroadcastFunction;
extern D2GameLibrary::TD2SendPacket D2SendPacket;
extern D2GameLibrary::TD2SetSkillBaseLevelOnClient D2SetSkillBaseLevelOnClient;
extern D2GameLibrary::TD2LinkPortal D2LinkPortal;
extern D2GameLibrary::TD2VerifIfNotCarry1 D2VerifIfNotCarry1;
extern D2GameLibrary::TD2TestPositionInRoom D2TestPositionInRoom;
extern D2GameLibrary::TD2SpawnMonster D2SpawnMonster;
extern D2GameLibrary::TD2Game235C0 D2Game235C0;
extern D2GameLibrary::TD2LoadInventory D2LoadInventory;
extern D2GameLibrary::TD2GameGetObject D2GameGetObject;
extern D2GameLibrary::TD2CreateUnit D2CreateUnit;
extern D2GameLibrary::TD2OpenPandPortal D2OpenPandPortal;
extern D2GameLibrary::TD2OpenPandFinalPortal D2OpenPandFinalPortal;
extern D2GameLibrary::TD2MephIA D2MephIA;
extern D2GameLibrary::TD2DiabloIA D2DiabloIA;
extern D2GameLibrary::TD2BaalIA D2BaalIA;
extern D2GameLibrary::TD2UberMephIA D2UberMephIA;
extern D2GameLibrary::TD2UberDiabloIA D2UberDiabloIA;
extern D2GameLibrary::TD2UberBaalIA D2UberBaalIA;
extern D2GameLibrary::TD2SaveGame D2SaveGame;

// D2Game: Only 1.10
extern D2GameLibrary::TD2GetClient D2GetClient;

// D2Game: Variables
extern NetClient** ptClientTable;

// D2Net
extern D2NetLibrary::TD2SendToServer D2SendToServer;
extern D2NetLibrary::TD2SendToClient D2SendToClient;

// Fog
extern FogLibrary::TD2FogAssertOld D2FogAssertOld;
extern FogLibrary::TD2FogAssert D2FogAssert;
extern FogLibrary::TD2FogMemAlloc D2FogMemAlloc;
extern FogLibrary::TD2FogMemDeAlloc D2FogMemDeAlloc;
extern FogLibrary::TD2AllocMem D2AllocMem;
extern FogLibrary::TD2FreeMem D2FreeMem;
extern FogLibrary::TD2MPQOpenFile D2MPQOpenFile;
extern FogLibrary::TD2MPQCloseFile D2MPQCloseFile;
extern FogLibrary::TD2MPQReadFile D2MPQReadFile;
extern FogLibrary::TD2MPQGetSizeFile D2MPQGetSizeFile;
extern FogLibrary::TD2FogGetSavePath D2FogGetSavePath;
extern FogLibrary::TD2FogGetInstallPath D2FogGetInstallPath;
extern FogLibrary::TD2Fog10212 D2Fog10212;
extern FogLibrary::TD2GetInstructionPointer D2GetInstructionPointer;

// D2Lang
extern D2LangLibrary::TD2GetStringFromString D2GetStringFromString;
extern D2LangLibrary::TD2GetStringFromIndex D2GetStringFromIndex;
extern D2LangLibrary::TD2GetLang D2GetLang;
extern D2LangLibrary::TD2PrintBigNumber D2PrintBigNumber;

// Storm
extern StormLibrary::TD2StormMPQOpenFile D2StormMPQOpenFile;
extern StormLibrary::TD2Storm503 D2Storm503;
extern StormLibrary::TD2FreeWinMessage D2FreeWinMessage;

// D2gfx
extern D2gfxLibrary::TD2GetResolution D2GetResolution;
extern D2gfxLibrary::TD2FillArea D2FillArea;
extern D2gfxLibrary::TD2PrintImage D2PrintImage;

// D2Win
extern D2WinLibrary::TD2PrintLineOnTextBox D2PrintLineOnTextBox;
extern D2WinLibrary::TD2PrintString D2PrintString;
extern D2WinLibrary::TD2GetPixelLen D2GetPixelLen;
extern D2WinLibrary::TD2SetFont D2SetFont;
extern D2WinLibrary::TD2PrintPopup D2PrintPopup;
extern D2WinLibrary::TD2GetPixelRect D2GetPixelRect;
extern D2WinLibrary::TD2PrintTextPopup D2PrintTextPopup;
extern D2WinLibrary::TD2CreateTextBox D2CreateTextBox;

// D2CMP
extern D2CMPLibrary::TD2CMP10014 D2CMP10014;

//#undef F7
//#define F7(X, Z, A,B,C,D,E,F,G,H, R, N, P) 
// Provide the function pointer types and say that they are going to be found externally.
//typedef DWORD(STDCALL *TD2Common11084) (Room* ptRoom, DWORD zero); extern TD2Common11084 D2Common11084;

extern DataTables* SgptDataTables;

#undef F7
#undef A7
#undef C7
#undef D2S
#undef D2F
#undef E2S
#undef E2F
#undef E2C

extern D2CommonLibrary::TD2AddPlayerStat			V2AddPlayerStat;
extern D2GameLibrary::TD2GetGameByClientID			V2GetGameByClientID;
extern D2GameLibrary::TD2SpawnMonster				V2SpawnMonster;

extern WORD (*getDescStrPos)	(DWORD statID);
extern void* (STDCALL *compileTxtFile)(DWORD unused, const char* filename, BINField* ptFields, DWORD* ptRecordCount, DWORD recordLength);
void setImage(sDrawImageInfo* data, void* image);
void setFrame(sDrawImageInfo* data, DWORD frame);
void __inline fillRect(DWORD x, DWORD y, DWORD Width, DWORD Height, DWORD color, DWORD transTbl){D2FillArea(x,y,x+Width,y+Height,color,transTbl);};

#define ResolutionY (*ptResolutionY)
#define ResolutionX (*ptResolutionX)
#define NegWindowStartY (*ptNegWindowStartY)
#define WindowStartX (*ptWindowStartX)
#define GameTypeMode (*ptGameTypeMode)
#define ClientTable (*ptClientTable)

#define IsLodGame (*ptIsLodGame)
#define DifficultyLevel (*ptDifficultyLevel)
#define MouseY (*ptMouseY)
#define MouseX (*ptMouseX)
#define ptClientChar (*ptptClientChar)

void initD2functions();