// Copyright (C) 2004 - 2017  Yohann Nicolas
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
// along with this program.If not, see <http://www.gnu.org/licenses/>.

#include "common.h"
s_shifting shifting;

// D2Common
D2CommonLibrary::TD2Common11084 D2Common11084;
D2CommonLibrary::TD2GetLevelID D2GetLevelID;
D2CommonLibrary::TD2GetDropRoom D2GetDropRoom;
D2CommonLibrary::TD2Common10242 D2Common10242;
D2CommonLibrary::TD2CanPutItemInInv D2CanPutItemInInv;
D2CommonLibrary::TD2InvRemoveItem D2InvRemoveItem;
D2CommonLibrary::TD2InvAddItem D2InvAddItem;
D2CommonLibrary::TD2Common10250 D2Common10250;
D2CommonLibrary::TD2Common10273 D2Common10273;
D2CommonLibrary::TD2InventoryGetFirstItem D2InventoryGetFirstItem;
D2CommonLibrary::TD2UnitGetNextItem D2UnitGetNextItem;
D2CommonLibrary::TD2GetRealItem D2GetRealItem;
D2CommonLibrary::TD2GetPosX D2GetPosX;
D2CommonLibrary::TD2GetPosY D2GetPosY;
D2CommonLibrary::TD2GetPosition D2GetPosition;
D2CommonLibrary::TD2GetMaxGoldBank D2GetMaxGoldBank;
D2CommonLibrary::TD2GetRoom D2GetRoom;
D2CommonLibrary::TD2InitPlayerData D2InitPlayerData;
D2CommonLibrary::TD2GetPlayerData D2GetPlayerData;
D2CommonLibrary::TD2GetDefence D2GetDefence;
D2CommonLibrary::TD2GetChanceToBlock D2GetChanceToBlock;
D2CommonLibrary::TD2GetMaxGold D2GetMaxGold;
D2CommonLibrary::TD2Common10572 D2Common10572;
D2CommonLibrary::TD2GetObjectFlags D2GetObjectFlags;
D2CommonLibrary::TD2SetObjectFlags D2SetObjectFlags;
D2CommonLibrary::TD2isInState D2isInState;
D2CommonLibrary::TD2AddPlayerStat D2AddPlayerStat;
D2CommonLibrary::TD2GetPlayerStat D2GetPlayerStat;
D2CommonLibrary::TD2GetPlayerBaseStat D2GetPlayerBaseStat;
D2CommonLibrary::TD2haveDefenceBonus D2haveDefenceBonus;
D2CommonLibrary::TD2haveFireResBonus D2haveFireResBonus;
D2CommonLibrary::TD2haveColdResBonus D2haveColdResBonus;
D2CommonLibrary::TD2haveLightResBonus D2haveLightResBonus;
D2CommonLibrary::TD2havePoisonResBonus D2havePoisonResBonus;
D2CommonLibrary::TD2haveDefenceMalus D2haveDefenceMalus;
D2CommonLibrary::TD2haveFireResMalus D2haveFireResMalus;
D2CommonLibrary::TD2haveColdResMalus D2haveColdResMalus;
D2CommonLibrary::TD2haveLightResMalus D2haveLightResMalus;
D2CommonLibrary::TD2havePoisonResMalus D2havePoisonResMalus;
D2CommonLibrary::TD2CompileTxtFile D2CompileTxtFile;
D2CommonLibrary::TD2GetItemsBIN D2GetItemsBIN;
D2CommonLibrary::TD2GetGemsBIN D2GetGemsBIN;
D2CommonLibrary::TD2GetCubeMainBIN D2GetCubeMainBIN;
D2CommonLibrary::TD2GetNbCubeMainBIN D2GetNbCubeMainBIN;
D2CommonLibrary::TD2GetNextLevelXP D2GetNextLevelXP;
D2CommonLibrary::TD2GetMaxLevel D2GetMaxLevel;
D2CommonLibrary::TD2GetDifficultyLevelsBIN D2GetDifficultyLevelsBIN;
D2CommonLibrary::TD2GetItemQuality D2GetItemQuality;
D2CommonLibrary::TD2TestFlags D2TestFlags;
D2CommonLibrary::TD2GetItemLevel D2GetItemLevel;
D2CommonLibrary::TD2ItemGetPage D2ItemGetPage;
D2CommonLibrary::TD2ItemSetPage D2ItemSetPage;
D2CommonLibrary::TD2CheckItemType D2CheckItemType;
D2CommonLibrary::TD2GetUniqueID D2GetUniqueID;
D2CommonLibrary::TD2SetAnim D2SetAnim;
D2CommonLibrary::TD2GetNbRunesBIN D2GetNbRunesBIN;
D2CommonLibrary::TD2GetRunesBIN D2GetRunesBIN;
D2CommonLibrary::TD2isEtheral D2isEtheral;
D2CommonLibrary::TD2SaveItem D2SaveItem;
D2CommonLibrary::TD2SetSkillBaseLevel D2SetSkillBaseLevel;
D2CommonLibrary::TD2GetSkillLevel D2GetSkillLevel;
D2CommonLibrary::TD2GetSkillCost D2GetSkillCost;
D2CommonLibrary::TD2GetCharStatsBIN D2GetCharStatsBIN;
D2CommonLibrary::TD2CompileCubeInput D2CompileCubeInput;
D2CommonLibrary::TD2CompileCubeOutput D2CompileCubeOutput;
D2CommonLibrary::TD2GetItemTypesBIN D2GetItemTypesBIN;
D2CommonLibrary::TD2GetItemStatCostBIN D2GetItemStatCostBIN;
D2CommonLibrary::TD2ReadFile D2ReadFile;
D2CommonLibrary::TD2LoadSuperuniques D2LoadSuperuniques;

// D2Common: Only 1.09
D2CommonLibrary::TD2Common10581 D2Common10581;
D2CommonLibrary::TD2Common10598 D2Common10598;
D2CommonLibrary::TD2Common10673 D2Common10673;

// D2Client
D2ClientLibrary::TD2LoadImage D2LoadImage;
D2ClientLibrary::TD2FreeImage D2FreeImage;
D2ClientLibrary::TD2SendMsgToAll D2SendMsgToAll;
D2ClientLibrary::TD2GetLastMonsterIDFight D2GetLastMonsterIDFight;
D2ClientLibrary::TD2PrintStatsPage D2PrintStatsPage;
D2ClientLibrary::TD2PrintStat D2PrintStat;
D2ClientLibrary::TD2SetColorPopup D2SetColorPopup;
D2ClientLibrary::TD2PlaySound D2PlaySound;
D2ClientLibrary::TD2GetCurrentNPC D2GetCurrentNPC;
D2ClientLibrary::TD2SendToServerXX D2SendToServerXX;
D2ClientLibrary::TD2TogglePage D2TogglePage;
D2ClientLibrary::TD2ClickOnStashButton D2ClickOnStashButton;
D2ClientLibrary::TD2LoadBuySelBtn D2LoadBuySelBtn;
D2ClientLibrary::TD2ReloadGambleScreen D2ReloadGambleScreen;

// D2Client: Only 1.10
D2ClientLibrary::TD2isLODGame D2isLODGame;
D2ClientLibrary::TD2GetDifficultyLevel D2GetDifficultyLevel;
D2ClientLibrary::TD2GetMouseX D2GetMouseX;
D2ClientLibrary::TD2GetMouseY D2GetMouseY;
D2ClientLibrary::TD2GetClientPlayer D2GetClientPlayer;
D2ClientLibrary::TD2CleanStatMouseUp D2CleanStatMouseUp;
D2ClientLibrary::TD2SendToServer3 D2SendToServer3;

// D2Client: Variables
DWORD* ptResolutionY;
DWORD* ptResolutionX;
DWORD* ptNegWindowStartY;
DWORD* ptWindowStartX;
DWORD* ptIsLodGame;
BYTE* ptDifficultyLevel;
DWORD* ptMouseY;
DWORD* ptMouseX;
Unit** ptptClientChar;
DWORD* ptNbStatDesc;
DWORD* ptStatDescTable;

// D2Game
D2GameLibrary::TD2SetNbPlayers D2SetNbPlayers;
D2GameLibrary::TD2AddClient D2AddClient;
D2GameLibrary::TD2GetGameByClientID D2GetGameByClientID;
D2GameLibrary::TD2BroadcastFunction D2BroadcastFunction;
D2GameLibrary::TD2SendPacket D2SendPacket;
D2GameLibrary::TD2SetSkillBaseLevelOnClient D2SetSkillBaseLevelOnClient;
D2GameLibrary::TD2LinkPortal D2LinkPortal;
D2GameLibrary::TD2VerifIfNotCarry1 D2VerifIfNotCarry1;
D2GameLibrary::TD2TestPositionInRoom D2TestPositionInRoom;
D2GameLibrary::TD2SpawnMonster D2SpawnMonster;
D2GameLibrary::TD2Game235C0 D2Game235C0;
D2GameLibrary::TD2LoadInventory D2LoadInventory;
D2GameLibrary::TD2GameGetObject D2GameGetObject;
D2GameLibrary::TD2CreateUnit D2CreateUnit;
D2GameLibrary::TD2OpenPandPortal D2OpenPandPortal;
D2GameLibrary::TD2OpenPandFinalPortal D2OpenPandFinalPortal;
D2GameLibrary::TD2MephIA D2MephIA;
D2GameLibrary::TD2DiabloIA D2DiabloIA;
D2GameLibrary::TD2BaalIA D2BaalIA;
D2GameLibrary::TD2UberMephIA D2UberMephIA;
D2GameLibrary::TD2UberDiabloIA D2UberDiabloIA;
D2GameLibrary::TD2UberBaalIA D2UberBaalIA;
D2GameLibrary::TD2SaveGame D2SaveGame;

// D2Game: Only 1.10
D2GameLibrary::TD2GetClient D2GetClient;

// D2Game: Variables
NetClient** ptClientTable;

// D2Net
D2NetLibrary::TD2SendToServer D2SendToServer;
D2NetLibrary::TD2SendToClient D2SendToClient;

// Fog
FogLibrary::TD2FogAssertOld D2FogAssertOld;
FogLibrary::TD2FogAssert D2FogAssert;
FogLibrary::TD2FogMemAlloc D2FogMemAlloc;
FogLibrary::TD2FogMemDeAlloc D2FogMemDeAlloc;
FogLibrary::TD2AllocMem D2AllocMem;
FogLibrary::TD2FreeMem D2FreeMem;
FogLibrary::TD2MPQOpenFile D2MPQOpenFile;
FogLibrary::TD2MPQCloseFile D2MPQCloseFile;
FogLibrary::TD2MPQReadFile D2MPQReadFile;
FogLibrary::TD2MPQGetSizeFile D2MPQGetSizeFile;
FogLibrary::TD2FogGetSavePath D2FogGetSavePath;
FogLibrary::TD2FogGetInstallPath D2FogGetInstallPath;
FogLibrary::TD2Fog10212 D2Fog10212;
FogLibrary::TD2GetInstructionPointer D2GetInstructionPointer;

// D2Lang
D2LangLibrary::TD2GetStringFromString D2GetStringFromString;
D2LangLibrary::TD2GetStringFromIndex D2GetStringFromIndex;
D2LangLibrary::TD2GetLang D2GetLang;
D2LangLibrary::TD2PrintBigNumber D2PrintBigNumber;

// Storm
StormLibrary::TD2StormMPQOpenFile D2StormMPQOpenFile;
StormLibrary::TD2Storm503 D2Storm503;
StormLibrary::TD2FreeWinMessage D2FreeWinMessage;

// D2gfx
D2gfxLibrary::TD2GetResolution D2GetResolution;
D2gfxLibrary::TD2FillArea D2FillArea;
D2gfxLibrary::TD2PrintImage D2PrintImage;

// D2Win
D2WinLibrary::TD2PrintLineOnTextBox D2PrintLineOnTextBox;
D2WinLibrary::TD2PrintString D2PrintString;
D2WinLibrary::TD2GetPixelLen D2GetPixelLen;
D2WinLibrary::TD2SetFont D2SetFont;
D2WinLibrary::TD2PrintPopup D2PrintPopup;
D2WinLibrary::TD2GetPixelRect D2GetPixelRect;
D2WinLibrary::TD2PrintTextPopup D2PrintTextPopup;
D2WinLibrary::TD2CreateTextBox D2CreateTextBox;

// D2CMP
D2CMPLibrary::TD2CMP10014 D2CMP10014;

DataTables* SgptDataTables;

using Versions = VersionUtility::Versions;

// D2Common
D2CommonLibrary::TD2AddPlayerStat			 V2AddPlayerStat;
D2CommonLibrary::TD2GetPlayerStat			 V2GetPlayerStat;
D2CommonLibrary::TD2GetPlayerBaseStat		 V2GetPlayerBaseStat;
D2CommonLibrary::TD2SetSkillBaseLevel		 V2SetSkillBaseLevel;
D2CommonLibrary::TD2CompileCubeInput	     V2CompileCubeInput;
D2CommonLibrary::TD2CompileCubeOutput		 V2CompileCubeOutput;
D2CommonLibrary::TD2GetItemTypesBIN			 V2GetItemTypesBIN;
D2CommonLibrary::TD2CompileTxtFile			 compileTxtFile;
D2CommonLibrary::TD2GetCharStatsBIN			 V2GetCharStatsBIN;
D2CommonLibrary::TD2GetItemStatCostBIN		 V2GetItemStatCostBIN;

// D2Client
D2ClientLibrary::TD2PrintStat				 V2PrintStat;
D2ClientLibrary::TD2SendMsgToAll		     V2SendMsgToAll;
D2ClientLibrary::TD2SetColorPopup			 V2SetColorPopup;
D2ClientLibrary::TD2LoadImage				 V2LoadImage;
D2ClientLibrary::TD2PlaySound				 V2PlaySound;

// D2Game
D2GameLibrary::TD2SetSkillBaseLevelOnClient	 V2SetSkillBaseLevelOnClient;
D2GameLibrary::TD2BroadcastFunction			 V2BroadcastFunction;
D2GameLibrary::TD2GetGameByClientID			 V2GetGameByClientID;
D2GameLibrary::TD2SpawnMonster				 V2SpawnMonster;
D2GameLibrary::TD2VerifIfNotCarry1			 V2VerifIfNotCarry1;
D2GameLibrary::TD2GameGetObject				 V2GameGetObject;
D2GameLibrary::TD2TestPositionInRoom		 V2TestPositionInRoom;
D2GameLibrary::TD2SendPacket				 V2SendPacket;
D2GameLibrary::TD2LoadInventory				 V2LoadInventory;
D2GameLibrary::TD2SaveGame					 V2SaveGame;

WORD (*getDescStrPos) (DWORD statID);

// D2Net
D2NetLibrary::TD2SendToServer				 V2SendToServer;

DWORD getStatDescIDFrom (DWORD statID)//FOR 1.09
{
	DWORD* desc = ptStatDescTable;
	DWORD curDesc = 0;
	while (curDesc < *ptNbStatDesc)
	{
		if (*desc == statID)
			return curDesc;
		desc+=4;
		curDesc++;
	}
	return curDesc;
}

FCT_ASM ( D2AddPlayerStat_9 )//(Unit* ptChar, DWORD statID, DWORD amount, DWORD index)
	PUSH DWORD PTR SS:[ESP+0xC]
	PUSH DWORD PTR SS:[ESP+0xC]
	PUSH DWORD PTR SS:[ESP+0xC]
	CALL V2AddPlayerStat
	RETN 0x10
}}

FCT_ASM ( D2GetPlayerStat_9 )//(Unit* ptChar, DWORD statID, DWORD index)
	PUSH DWORD PTR SS:[ESP+0x8]
	PUSH DWORD PTR SS:[ESP+0x8]
	CALL V2GetPlayerStat
	RETN 0x0C
}}

FCT_ASM ( D2GetPlayerBaseStat_9 )//(Unit* ptChar, DWORD statID, DWORD index)
	PUSH DWORD PTR SS:[ESP+0x8]
	PUSH DWORD PTR SS:[ESP+0x8]
	CALL V2GetPlayerBaseStat
	RETN 0x0C
}}

FCT_ASM ( D2SetSkillBaseLevel_9 )//(Unit* ptChar, DWORD skillID, DWORD slvl, DWORD bRemove, char*, DWORD));
	PUSH DWORD PTR SS:[ESP+0x10]
	PUSH DWORD PTR SS:[ESP+0x10]
	PUSH DWORD PTR SS:[ESP+0x10]
	PUSH DWORD PTR SS:[ESP+0x10]
	CALL V2SetSkillBaseLevel
	RETN 0x18
}}

FCT_ASM ( D2SetSkillBaseLevelOnClient_9 )//(void* ptClient, Unit* ptChar, DWORD skillID, DWORD newValue, DWORD zero)
	POP EAX
	MOV ECX,EDX
	POP EDX
	PUSH EAX
	JMP V2SetSkillBaseLevelOnClient
}}

FCT_ASM ( D2GetCharStatsBIN_9 )
	PUSH ECX
	CALL D2Common10581
	RETN
}}

FCT_ASM ( D2GetItemStatCostBIN_9 )
	PUSH ECX
	CALL D2Common10598
	RETN
}}

FCT_ASM ( D2GetItemTypesBIN_9 )
	PUSH ECX
	CALL D2Common10673
	RETN
}}

DWORD FASTCALL D2PrintStat_9 (Unit* ptItem, Stats* ptStats, DWORD statID, DWORD statIndex, DWORD statValue, LPWSTR lpText)
{
	DWORD curDesc = getStatDescIDFrom(statID);
	if (curDesc < *ptNbStatDesc)
		return V2PrintStat(ptItem, (Stats*)curDesc, statValue, 0, 0, lpText);
	return 0;
}

void setImage(sDrawImageInfo* data, void* image){((void**)data)[shifting.ptImage/4]=image;}//0x4 0x8 0x3C
void setFrame(sDrawImageInfo* data, DWORD frame){((DWORD*)data)[shifting.ptFrame/4]=frame;}//0x8 0x44 0x40

WORD getDescStrPos_9 (DWORD statID)
{
	DWORD* desc = &ptStatDescTable[getStatDescIDFrom(statID)*4];
	return (WORD)*(desc+2);
}
WORD getDescStrPos_10 (DWORD statID)
{
	ItemStatCostBIN* itemStatCost = D2GetItemStatCostBIN(statID);
	return itemStatCost->descstrpos;
}

const char* S_compileTxtFile = "compileTxtFile";
const char* S_errorReadTxtFile = "pbData";
__declspec(naked) void* STDCALL compileTxtFile_9(DWORD unused, const char* filename, BINField* ptFields, DWORD* ptRecordCount, DWORD recordLength)
{_asm{
	SUB ESP,0x210
//	MOV EAX,DWORD PTR DS:[1BEA28C]
	PUSH EBX
	PUSH EBP
	PUSH ESI
	PUSH EDI
	MOV ESI,DWORD PTR SS:[ESP+0x228]
	MOV DWORD PTR SS:[ESP+0x10],0

	MOV EDI,wsprintf
	PUSH ESI
	LEA EAX,DWORD PTR SS:[ESP+0x20]
	PUSH EAX
	CALL EDI
	ADD ESP,8

	LEA EDX,DWORD PTR SS:[ESP+0x10]
	PUSH 0
	PUSH S_compileTxtFile
	PUSH EDX
	MOV ECX,DWORD PTR SS:[ESP+0x230]
	LEA EDX,DWORD PTR SS:[ESP+0x28]
	CALL D2ReadFile
	TEST EAX,EAX
	JNZ continue_compileTxtFile
	PUSH 0
	PUSH S_compileTxtFile
	PUSH S_errorReadTxtFile
	CALL D2FogAssertOld
	PUSH -1
	CALL exit
continue_compileTxtFile:
	MOV ECX,D2CompileTxtFile
	ADD ECX,0x305
	JMP ECX
}}

__declspec(naked) void* STDCALL compileTxtFile_10(DWORD unused, const char* filename, BINField* ptFields, DWORD* ptRecordCount, DWORD recordLength)
{_asm{
	SUB ESP,0x210
//	MOV EAX,DWORD PTR DS:[1BEA28C]
	PUSH EBX
	PUSH EBP
	MOV EBP,DWORD PTR SS:[ESP+0x220]
	PUSH ESI
	PUSH EDI
	MOV DWORD PTR SS:[ESP+0x10],0

	MOV EBX,wsprintf
	PUSH EBP
	LEA EAX,DWORD PTR SS:[ESP+0x20]
	PUSH EAX
	CALL EBX
	ADD ESP,8

	LEA EDX,DWORD PTR SS:[ESP+0x10]
	PUSH 0
	PUSH S_compileTxtFile
	PUSH EDX
	MOV ECX,DWORD PTR SS:[ESP+0x230]
	LEA EDX,DWORD PTR SS:[ESP+0x28]
	CALL D2ReadFile
	TEST EAX,EAX
	JNZ continue_compileTxtFile
	PUSH 0
	PUSH S_compileTxtFile
	PUSH S_errorReadTxtFile
	CALL D2FogAssertOld
	PUSH -1
	CALL exit
continue_compileTxtFile:
	MOV ECX,D2CompileTxtFile
	ADD ECX,0x2ED
	JMP ECX
}}

__declspec(naked) void* STDCALL compileTxtFile_111(DWORD unused, const char* filename, BINField* ptFields, DWORD* ptRecordCount, DWORD recordLength)
{_asm{
	SUB ESP,0x20C
//	MOV EAX,DWORD PTR DS:[6FDF1464]
	PUSH EBX
	PUSH EBP
	PUSH ESI
	PUSH EDI
	MOV DWORD PTR SS:[ESP+0x10],0
	MOV EBX,DWORD PTR SS:[ESP+0x224]

	PUSH EBX
	LEA EAX,DWORD PTR SS:[ESP+0x1C]
	PUSH EAX
	CALL DWORD PTR SS:[wsprintf]
	MOV EDX,DWORD PTR SS:[ESP+0x228]
	ADD ESP,8
	LEA EDX,DWORD PTR SS:[ESP+0x10]
	PUSH EDX
	PUSH EAX
	LEA EAX,DWORD PTR SS:[ESP+0x20]
	CALL D2ReadFile
	TEST EAX,EAX
	JNZ continue_compileTxtFile
	PUSH __LINE__
	CALL D2GetInstructionPointer
	PUSH EAX
	PUSH S_errorReadTxtFile
	CALL D2FogAssert
	ADD ESP,0xC
	PUSH -1
	CALL exit
continue_compileTxtFile:
	MOV ECX,D2CompileTxtFile
	ADD ECX,0x1EC
	JMP ECX
}}

DWORD FASTCALL	D2isLODGame_111(){return IsLodGame;}
BYTE  FASTCALL	D2GetDifficultyLevel_111(){return DifficultyLevel;}
DWORD STDCALL	D2GetMouseX_111(){return MouseX;}
DWORD STDCALL	D2GetMouseY_111(){return MouseY;}
Unit* STDCALL	D2GetClientPlayer_111(){return ptClientChar;}

DWORD *StatMouse1, *StatMouse2, *StatMouse3, *StatMouse4;
void FASTCALL D2CleanStatMouseUp_111(){*StatMouse1=*StatMouse2=*StatMouse3=*StatMouse4=0;}

Unit* STDCALL	D2GetRealItem_111(Unit* ptItem){return ptItem;}

FCT_ASM ( D2SendMsgToAll_111 )
	PUSH ESI
	MOV ESI,ECX
	CALL V2SendMsgToAll
	POP ESI
	RETN
}}

FCT_ASM ( D2SetColorPopup_111 )
	PUSH EDI
	PUSH EDX
	MOV EDI,ECX
	CALL V2SetColorPopup
	POP EDI
	RETN
}}

FCT_ASM ( D2LoadImage_111 )
	PUSH EDX
	MOV EAX,ECX
	CALL V2LoadImage
	RETN
}}

const char* D2FreeImage_FILE = __FILE__;
FCT_ASM ( D2FreeImage_111 )
	PUSH ESI
	MOV ESI,ECX
	PUSH ESI
	CALL D2CMP10014
	TEST ESI,ESI
	JE END_D2Free
	PUSH 0
	PUSH __LINE__
	MOV EDX,D2FreeImage_FILE                ;  ASCII "C:\projects\D2\head\Diablo2\Source\D2Client\CORE\ARCHIVE.CPP"
	MOV ECX,ESI
	CALL D2FogMemDeAlloc
END_D2Free:
	POP ESI
	RETN
}}

FCT_ASM ( D2PlaySound_111 )
	PUSH EBX
	PUSH DWORD PTR SS:[ESP+0x10]
	PUSH DWORD PTR SS:[ESP+0x10]
	PUSH DWORD PTR SS:[ESP+0x10]
	PUSH EDX
	MOV EBX,ECX
	CALL V2PlaySound
	POP EBX
	RETN 0xC
}}

FCT_ASM ( D2GetClient_111 )
	PUSH ECX
	CALL D2GetPlayerData
	MOV EAX,DWORD PTR DS:[EAX+0x9C]
	RETN 4
}}


FCT_ASM ( D2SetSkillBaseLevelOnClient_111 )
	PUSH EBX
	PUSH ESI
	PUSH DWORD PTR SS:[ESP+0x14]
	PUSH DWORD PTR SS:[ESP+0x14]
	MOV EBX, DWORD PTR SS:[ESP+0x14]
	MOV EAX,ECX
	MOV ESI,EDX
	CALL V2SetSkillBaseLevelOnClient
	POP ESI
	POP EBX
	RETN 0xC
}}

FCT_ASM ( D2GetCharStatsBIN_111 )
	MOV EAX,ECX
	JMP V2GetCharStatsBIN
}}

FCT_ASM ( D2GetItemStatCostBIN_111 )
	MOV EAX,ECX
	JMP V2GetItemStatCostBIN
}}

FCT_ASM ( D2SendToServer3_111 )
	PUSH EBX
	PUSH ECX
	MOV BYTE PTR SS:[ESP],CL
	MOV WORD PTR SS:[ESP+1],DX
	MOV EBX,3
	LEA EDX,DWORD PTR SS:[ESP]
	PUSH EDX
	CALL D2SendToServerXX
	POP ECX
	POP EBX
	RETN
}}

FCT_ASM ( D2PrintStat_111 )
	PUSH ESI
	MOV ESI,DWORD PTR SS:[ESP+0x14]
	MOV EAX,DWORD PTR SS:[ESP+0x08]
	PUSH DWORD PTR SS:[ESP+0x10]
	PUSH DWORD PTR SS:[ESP+0x10]
	PUSH EDX
	PUSH ECX
	CALL V2PrintStat
	POP ESI
	RETN 0x10
}}

FCT_ASM ( D2SendPacket_111 )
	POP EAX
	PUSH EDX
	PUSH EAX
	MOV EAX,ECX
	JMP V2SendPacket
}}

FCT_ASM ( D2LoadInventory_111 )
	MOV EAX,DWORD PTR SS:[ESP+4]
	MOV DWORD PTR SS:[ESP+4],EDX
	JMP V2LoadInventory
}}

FCT_ASM ( D2CompileCubeInput_111 )
	PUSH EBX
	MOV EBX,ECX
	MOV EAX,EDX
	CALL V2CompileCubeInput
	POP EBX
	RETN 8
}}

FCT_ASM ( D2CompileCubeOutput_111 )
	PUSH EBX
	MOV EBX,ECX
	PUSH EDX
	CALL V2CompileCubeOutput
	POP EBX
	RETN 8
}}

FCT_ASM ( D2BroadcastFunction_111 )
	PUSH EDI
	PUSH EBX
	MOV EAX,ECX
	MOV EDI,EDX
	MOV EBX,DWORD PTR SS:[ESP+0xC]
	CALL V2BroadcastFunction
	POP EBX
	POP EDI
	RETN 4
}}

FCT_ASM ( D2SpawnMonster_111 )
	PUSH DWORD PTR SS:[ESP+0x18]
	PUSH DWORD PTR SS:[ESP+0x14]
	PUSH DWORD PTR SS:[ESP+0x14]
	PUSH DWORD PTR SS:[ESP+0x14]
	PUSH ECX
	MOV ECX,DWORD PTR SS:[ESP+0x18]
	MOV EAX,DWORD PTR SS:[ESP+0x28]
	CALL V2SpawnMonster
	RETN 0x18
}}

FCT_ASM ( D2SpawnMonster_111b )
	PUSH DWORD PTR SS:[ESP+0x10]
	PUSH DWORD PTR SS:[ESP+0x10]
	PUSH DWORD PTR SS:[ESP+0x10]
	PUSH EDX
	PUSH ECX
	MOV EAX,DWORD PTR SS:[ESP+0x18]
	MOV EDX,DWORD PTR SS:[ESP+0x2C]
	MOV ECX,DWORD PTR SS:[ESP+0x28]//superuniqueID
	CALL V2SpawnMonster
	RETN 0x18
}}

FCT_ASM ( D2VerifIfNotCarry1_111 )
	PUSH EBX
	PUSH ECX
	MOV EBX,EDX
	MOV EAX,DWORD PTR SS:[ESP+0xC]
	CALL V2VerifIfNotCarry1
	POP EBX
	RETN 4
}}

FCT_ASM ( D2GameGetObject_111 )
	MOV EAX,EDX
	MOV EDX,DWORD PTR SS:[ESP+4]
	CALL V2GameGetObject
	RETN 4
}}

FCT_ASM ( D2TestPositionInRoom_111 )
	PUSH EDI
	PUSH EBX
	MOV EDI,DWORD PTR SS:[ESP+0xC]
	MOV EAX,ECX
	MOV EBX,EDX
	CALL V2TestPositionInRoom
	POP EBX
	POP EDI
	RETN 4
}}

FCT_ASM ( D2GetItemTypesBIN_111)
	MOV EAX,ECX
	JMP V2GetItemTypesBIN
}}

FCT_ASM ( D2SendToServer_1XX )
	PUSH DWORD PTR SS:[ESP+0x4]
	PUSH DWORD PTR SS:[ESP+0x10]
	PUSH 0
	CALL V2SendToServer
	RETN 0xC
}}

FCT_ASM ( D2GetGameByClientID_1XX )
	POP EAX
	POP ECX
	PUSH EAX
	JMP V2GetGameByClientID
}}

FCT_ASM ( D2SaveGame_1XX )
	POP EAX
	POP ECX
	PUSH EAX
	JMP V2SaveGame
}}

#include "Utilities\LibraryUtility.h"
extern LibraryUtility* lu;

void initD2functions()
{
	// D2Common
	D2Common11084 = lu->D2Common->D2Common11084;
	D2GetLevelID = lu->D2Common->D2GetLevelID;
	D2GetDropRoom = lu->D2Common->D2GetDropRoom;
	D2Common10242 = lu->D2Common->D2Common10242;
	D2CanPutItemInInv = lu->D2Common->D2CanPutItemInInv;
	D2InvRemoveItem = lu->D2Common->D2InvRemoveItem;
	D2InvAddItem = lu->D2Common->D2InvAddItem;
	D2Common10250 = lu->D2Common->D2Common10250;
	D2Common10273 = lu->D2Common->D2Common10273;
	D2InventoryGetFirstItem = lu->D2Common->D2InventoryGetFirstItem;
	D2UnitGetNextItem = lu->D2Common->D2UnitGetNextItem;
	D2GetRealItem = lu->D2Common->D2GetRealItem;
	D2GetPosX = lu->D2Common->D2GetPosX;
	D2GetPosY = lu->D2Common->D2GetPosY;
	D2GetPosition = lu->D2Common->D2GetPosition;
	D2GetMaxGoldBank = lu->D2Common->D2GetMaxGoldBank;
	D2GetRoom = lu->D2Common->D2GetRoom;
	D2InitPlayerData = lu->D2Common->D2InitPlayerData;
	D2GetPlayerData = lu->D2Common->D2GetPlayerData;
	D2GetDefence = lu->D2Common->D2GetDefence;
	D2GetChanceToBlock = lu->D2Common->D2GetChanceToBlock;
	D2GetMaxGold = lu->D2Common->D2GetMaxGold;
	D2Common10572 = lu->D2Common->D2Common10572;
	D2GetObjectFlags = lu->D2Common->D2GetObjectFlags;
	D2SetObjectFlags = lu->D2Common->D2SetObjectFlags;
	D2isInState = lu->D2Common->D2isInState;
	D2AddPlayerStat = lu->D2Common->D2AddPlayerStat;
	D2GetPlayerStat = lu->D2Common->D2GetPlayerStat;
	D2GetPlayerBaseStat = lu->D2Common->D2GetPlayerBaseStat;
	D2haveDefenceBonus = lu->D2Common->D2haveDefenceBonus;
	D2haveFireResBonus = lu->D2Common->D2haveFireResBonus;
	D2haveColdResBonus = lu->D2Common->D2haveColdResBonus;
	D2haveLightResBonus = lu->D2Common->D2haveLightResBonus;
	D2havePoisonResBonus = lu->D2Common->D2havePoisonResBonus;
	D2haveDefenceMalus = lu->D2Common->D2haveDefenceMalus;
	D2haveFireResMalus = lu->D2Common->D2haveFireResMalus;
	D2haveColdResMalus = lu->D2Common->D2haveColdResMalus;
	D2haveLightResMalus = lu->D2Common->D2haveLightResMalus;
	D2havePoisonResMalus = lu->D2Common->D2havePoisonResMalus;
	D2CompileTxtFile = lu->D2Common->D2CompileTxtFile;
	D2GetItemsBIN = lu->D2Common->D2GetItemsBIN;
	D2GetGemsBIN = lu->D2Common->D2GetGemsBIN;
	D2GetCubeMainBIN = lu->D2Common->D2GetCubeMainBIN;
	D2GetNbCubeMainBIN = lu->D2Common->D2GetNbCubeMainBIN;
	D2GetNextLevelXP = lu->D2Common->D2GetNextLevelXP;
	D2GetMaxLevel = lu->D2Common->D2GetMaxLevel;
	D2GetDifficultyLevelsBIN = lu->D2Common->D2GetDifficultyLevelsBIN;
	D2GetItemQuality = lu->D2Common->D2GetItemQuality;
	D2TestFlags = lu->D2Common->D2TestFlags;
	D2GetItemLevel = lu->D2Common->D2GetItemLevel;
	D2ItemGetPage = lu->D2Common->D2ItemGetPage;
	D2ItemSetPage = lu->D2Common->D2ItemSetPage;
	D2CheckItemType = lu->D2Common->D2CheckItemType;
	D2GetUniqueID = lu->D2Common->D2GetUniqueID;
	D2SetAnim = lu->D2Common->D2SetAnim;
	D2GetNbRunesBIN = lu->D2Common->D2GetNbRunesBIN;
	D2GetRunesBIN = lu->D2Common->D2GetRunesBIN;
	D2isEtheral = lu->D2Common->D2isEtheral;
	D2SaveItem = lu->D2Common->D2SaveItem;
	D2SetSkillBaseLevel = lu->D2Common->D2SetSkillBaseLevel;
	D2GetSkillLevel = lu->D2Common->D2GetSkillLevel;
	D2GetSkillCost = lu->D2Common->D2GetSkillCost;
	D2GetCharStatsBIN = lu->D2Common->D2GetCharStatsBIN;
	D2CompileCubeInput = lu->D2Common->D2CompileCubeInput;
	D2CompileCubeOutput = lu->D2Common->D2CompileCubeOutput;
	D2GetItemTypesBIN = lu->D2Common->D2GetItemTypesBIN;
	D2GetItemStatCostBIN = lu->D2Common->D2GetItemStatCostBIN;
	D2ReadFile = lu->D2Common->D2ReadFile;
	D2LoadSuperuniques = lu->D2Common->D2LoadSuperuniques;

	// D2Client
	D2LoadImage = lu->D2Client->D2LoadImage;
	D2FreeImage = lu->D2Client->D2FreeImage;
	D2SendMsgToAll = lu->D2Client->D2SendMsgToAll;
	D2GetLastMonsterIDFight = lu->D2Client->D2GetLastMonsterIDFight;
	D2PrintStatsPage = lu->D2Client->D2PrintStatsPage;
	D2PrintStat = lu->D2Client->D2PrintStat;
	D2SetColorPopup = lu->D2Client->D2SetColorPopup;
	D2PlaySound = lu->D2Client->D2PlaySound;
	D2GetCurrentNPC = lu->D2Client->D2GetCurrentNPC;
	D2SendToServerXX = lu->D2Client->D2SendToServerXX;
	D2TogglePage = lu->D2Client->D2TogglePage;
	D2ClickOnStashButton = lu->D2Client->D2ClickOnStashButton;
	D2LoadBuySelBtn = lu->D2Client->D2LoadBuySelBtn;
	D2ReloadGambleScreen = lu->D2Client->D2ReloadGambleScreen;

	// D2Client: Only 1.10
	D2isLODGame = lu->D2Client->D2isLODGame;
	D2GetDifficultyLevel = lu->D2Client->D2GetDifficultyLevel;
	D2GetMouseX = lu->D2Client->D2GetMouseX;
	D2GetMouseY = lu->D2Client->D2GetMouseY;
	D2GetClientPlayer = lu->D2Client->D2GetClientPlayer;
	D2CleanStatMouseUp = lu->D2Client->D2CleanStatMouseUp;
	D2SendToServer3 = lu->D2Client->D2SendToServer3;

	// D2Client: Variables
	ptResolutionY = lu->D2Client->ptResolutionY;
	ptResolutionX = lu->D2Client->ptResolutionX;
	ptNegWindowStartY = lu->D2Client->ptNegWindowStartY;
	ptWindowStartX = lu->D2Client->ptWindowStartX;
	ptIsLodGame = lu->D2Client->ptIsLodGame;
	ptDifficultyLevel = lu->D2Client->ptDifficultyLevel;
	ptMouseY = lu->D2Client->ptMouseY;
	ptMouseX = lu->D2Client->ptMouseX;
	ptptClientChar = lu->D2Client->ptptClientChar;
	ptNbStatDesc = lu->D2Client->ptNbStatDesc;
	ptStatDescTable = lu->D2Client->ptStatDescTable;

	// D2Game
	D2SetNbPlayers = lu->D2Game->D2SetNbPlayers;
	D2AddClient = lu->D2Game->D2AddClient;
	D2GetGameByClientID = lu->D2Game->D2GetGameByClientID;
	D2BroadcastFunction = lu->D2Game->D2BroadcastFunction;
	D2SendPacket = lu->D2Game->D2SendPacket;
	D2SetSkillBaseLevelOnClient = lu->D2Game->D2SetSkillBaseLevelOnClient;
	D2LinkPortal = lu->D2Game->D2LinkPortal;
	D2VerifIfNotCarry1 = lu->D2Game->D2VerifIfNotCarry1;
	D2TestPositionInRoom = lu->D2Game->D2TestPositionInRoom;
	D2SpawnMonster = lu->D2Game->D2SpawnMonster;
	D2Game235C0 = lu->D2Game->D2Game235C0;
	D2LoadInventory = lu->D2Game->D2LoadInventory;
	D2GameGetObject = lu->D2Game->D2GameGetObject;
	D2CreateUnit = lu->D2Game->D2CreateUnit;
	D2OpenPandPortal = lu->D2Game->D2OpenPandPortal;
	D2OpenPandFinalPortal = lu->D2Game->D2OpenPandFinalPortal;
	D2MephIA = lu->D2Game->D2MephIA;
	D2DiabloIA = lu->D2Game->D2DiabloIA;
	D2BaalIA = lu->D2Game->D2BaalIA;
	D2UberMephIA = lu->D2Game->D2UberMephIA;
	D2UberDiabloIA = lu->D2Game->D2UberDiabloIA;
	D2UberBaalIA = lu->D2Game->D2UberBaalIA;
	D2SaveGame = lu->D2Game->D2SaveGame;

	// D2Game: Only 1.10
	D2GetClient = lu->D2Game->D2GetClient;

	// D2Game: Variables
	ptClientTable = lu->D2Game->ptClientTable;

	// D2Net
	D2SendToServer = lu->D2Net->D2SendToServer;
	D2SendToClient = lu->D2Net->D2SendToClient;

	// Fog
	D2FogAssertOld = lu->Fog->D2FogAssertOld;
	D2FogAssert = lu->Fog->D2FogAssert;
	D2FogMemAlloc = lu->Fog->D2FogMemAlloc;
	D2FogMemDeAlloc = lu->Fog->D2FogMemDeAlloc;
	D2AllocMem = lu->Fog->D2AllocMem;
	D2FreeMem = lu->Fog->D2FreeMem;
	D2MPQOpenFile = lu->Fog->D2MPQOpenFile;
	D2MPQCloseFile = lu->Fog->D2MPQCloseFile;
	D2MPQReadFile = lu->Fog->D2MPQReadFile;
	D2MPQGetSizeFile = lu->Fog->D2MPQGetSizeFile;
	D2FogGetSavePath = lu->Fog->D2FogGetSavePath;
	D2FogGetInstallPath = lu->Fog->D2FogGetInstallPath;
	D2Fog10212 = lu->Fog->D2Fog10212;
	D2GetInstructionPointer = lu->Fog->D2GetInstructionPointer;

	// D2Lang
	D2GetStringFromString = lu->D2Lang->D2GetStringFromString;
	D2GetStringFromIndex = lu->D2Lang->D2GetStringFromIndex;
	D2GetLang = lu->D2Lang->D2GetLang;
	D2PrintBigNumber = lu->D2Lang->D2PrintBigNumber;

	// Storm
	D2StormMPQOpenFile = lu->Storm->D2StormMPQOpenFile;
	D2Storm503 = lu->Storm->D2Storm503;
	D2FreeWinMessage = lu->Storm->D2FreeWinMessage;

	// D2gfx
	D2GetResolution = lu->D2gfx->D2GetResolution;
	D2FillArea = lu->D2gfx->D2FillArea;
	D2PrintImage = lu->D2gfx->D2PrintImage;

	// D2Win
	D2PrintLineOnTextBox = lu->D2Win->D2PrintLineOnTextBox;
	D2PrintString = lu->D2Win->D2PrintString;
	D2GetPixelLen = lu->D2Win->D2GetPixelLen;
	D2SetFont = lu->D2Win->D2SetFont;
	D2PrintPopup = lu->D2Win->D2PrintPopup;
	D2GetPixelRect = lu->D2Win->D2GetPixelRect;
	D2PrintTextPopup = lu->D2Win->D2PrintTextPopup;
	D2CreateTextBox = lu->D2Win->D2CreateTextBox;

	// D2CMP
	D2CMP10014 = lu->D2CMP->D2CMP10014;

	SgptDataTables = *(DataTables**) R7(D2Common, 0000, 0000, 96A20, 9B74C, 9EE8C, 9B500, 99E1C, A33F0);
	if (version_D2Common < Versions::V110)
	{
		D2Common10581 = lu->D2Common->D2Common10581;
		D2Common10598 = lu->D2Common->D2Common10598;
		D2Common10673 = lu->D2Common->D2Common10673;
	}

	//////////////// MISC FCT ////////////////
	getDescStrPos = version_D2Common >= Versions::V110  ? getDescStrPos_10 : getDescStrPos_9;
	compileTxtFile = version_D2Common >= Versions::V111 ? compileTxtFile_111 : version_D2Common == Versions::V110 ? compileTxtFile_10 : compileTxtFile_9;

	V2AddPlayerStat = D2AddPlayerStat;
	V2GetPlayerStat = D2GetPlayerStat;
	V2GetPlayerBaseStat = D2GetPlayerBaseStat;
	V2SetSkillBaseLevel = D2SetSkillBaseLevel;
	V2SetSkillBaseLevelOnClient = D2SetSkillBaseLevelOnClient;
	V2PrintStat = D2PrintStat;
	V2SendMsgToAll = D2SendMsgToAll;
	V2SetColorPopup = D2SetColorPopup;
	V2LoadImage = D2LoadImage;
	V2PlaySound = D2PlaySound;
	V2GetCharStatsBIN = D2GetCharStatsBIN;
	V2GetItemStatCostBIN = D2GetItemStatCostBIN;
	V2SendToServer = D2SendToServer;
	V2SendPacket = D2SendPacket;
	V2LoadInventory = D2LoadInventory;
	V2CompileCubeInput = D2CompileCubeInput;
	V2CompileCubeOutput = D2CompileCubeOutput;
	V2BroadcastFunction = D2BroadcastFunction;
	V2GetGameByClientID = D2GetGameByClientID;
	V2SpawnMonster = D2SpawnMonster;
	V2VerifIfNotCarry1 = D2VerifIfNotCarry1;
	V2GameGetObject = D2GameGetObject;
	V2TestPositionInRoom = D2TestPositionInRoom;
	V2GetItemTypesBIN = D2GetItemTypesBIN;
	V2SaveGame = D2SaveGame;

	//////////////// REDIRECT ON CUSTOM FUNCTIONS ////////////////

	if ( version_D2Client >= Versions::V111 )
	{
		D2SendMsgToAll = (D2ClientLibrary::TD2SendMsgToAll) D2SendMsgToAll_111;
		D2SetColorPopup = (D2ClientLibrary::TD2SetColorPopup) D2SetColorPopup_111;
		D2LoadImage = (D2ClientLibrary::TD2LoadImage) D2LoadImage_111;
		D2FreeImage = (D2ClientLibrary::TD2FreeImage) D2FreeImage_111;
		D2PlaySound = (D2ClientLibrary::TD2PlaySound) D2PlaySound_111;
		D2GetClient = (D2GameLibrary::TD2GetClient) D2GetClient_111;
		D2SendToServer3 = (D2ClientLibrary::TD2SendToServer3) D2SendToServer3_111;
		D2SetSkillBaseLevelOnClient = (D2GameLibrary::TD2SetSkillBaseLevelOnClient) D2SetSkillBaseLevelOnClient_111;
		D2GetCharStatsBIN = (D2CommonLibrary::TD2GetCharStatsBIN) D2GetCharStatsBIN_111;
		D2GetItemStatCostBIN = (D2CommonLibrary::TD2GetItemStatCostBIN) D2GetItemStatCostBIN_111;
		D2PrintStat = (D2ClientLibrary::TD2PrintStat) D2PrintStat_111;
		D2SendPacket = (D2GameLibrary::TD2SendPacket) D2SendPacket_111;
		D2LoadInventory = (D2GameLibrary::TD2LoadInventory) D2LoadInventory_111;
		D2CompileCubeInput = (D2CommonLibrary::TD2CompileCubeInput) D2CompileCubeInput_111;
		D2CompileCubeOutput = (D2CommonLibrary::TD2CompileCubeOutput) D2CompileCubeOutput_111;
		D2BroadcastFunction = (D2GameLibrary::TD2BroadcastFunction) D2BroadcastFunction_111;
		D2SpawnMonster = version_D2Game >= Versions::V111b ? (D2GameLibrary::TD2SpawnMonster)D2SpawnMonster_111b : (D2GameLibrary::TD2SpawnMonster)D2SpawnMonster_111;
		D2VerifIfNotCarry1 = (D2GameLibrary::TD2VerifIfNotCarry1) D2VerifIfNotCarry1_111;
		D2GameGetObject = (D2GameLibrary::TD2GameGetObject) D2GameGetObject_111;
		D2GetItemTypesBIN = (D2CommonLibrary::TD2GetItemTypesBIN) D2GetItemTypesBIN_111;
		D2TestPositionInRoom = (D2GameLibrary::TD2TestPositionInRoom) D2TestPositionInRoom_111;
		D2isLODGame = D2isLODGame_111;
		D2GetDifficultyLevel = D2GetDifficultyLevel_111;
		D2GetMouseX = D2GetMouseX_111;
		D2GetMouseY = D2GetMouseY_111;
		D2GetClientPlayer = D2GetClientPlayer_111;
		D2GetRealItem = D2GetRealItem_111;
		D2CleanStatMouseUp = D2CleanStatMouseUp_111;
		StatMouse1 = (DWORD*)R7(D2Client, 0000, 0000, 0000, 11C004, 11C2F4, 11C040, 11C3DC, 11D224);
		StatMouse2 = (DWORD*)R7(D2Client, 0000, 0000, 0000, 11C008, 11C2F8, 11C044, 11C3E0, 11D228);
		StatMouse3 = (DWORD*)R7(D2Client, 0000, 0000, 0000, 11C020, 11C310, 11C05C, 11C3F8, 11D240);
		StatMouse4 = (DWORD*)R7(D2Client, 0000, 0000, 0000, 11C024, 11C314, 11C060, 11C3FC, 11D244);
	} 
	else
	{
		D2SendToServer = (D2NetLibrary::TD2SendToServer) D2SendToServer_1XX;
		D2GetGameByClientID = (D2GameLibrary::TD2GetGameByClientID) D2GetGameByClientID_1XX;
		D2SaveGame = (D2GameLibrary::TD2SaveGame) D2SaveGame_1XX;
	}

	if ( version_D2Common <= Versions::V109d )
	{
		D2AddPlayerStat =				(D2CommonLibrary::TD2AddPlayerStat) D2AddPlayerStat_9;
		D2GetPlayerStat =				(D2CommonLibrary::TD2GetPlayerStat) D2GetPlayerStat_9;
		D2GetPlayerBaseStat =			(D2CommonLibrary::TD2GetPlayerBaseStat) D2GetPlayerBaseStat_9;
		D2SetSkillBaseLevel =			(D2CommonLibrary::TD2SetSkillBaseLevel) D2SetSkillBaseLevel_9;
		D2GetCharStatsBIN =				(D2CommonLibrary::TD2GetCharStatsBIN) D2GetCharStatsBIN_9;
		D2GetItemStatCostBIN =			(D2CommonLibrary::TD2GetItemStatCostBIN) D2GetItemStatCostBIN_9;
		D2GetItemTypesBIN =				(D2CommonLibrary::TD2GetItemTypesBIN) D2GetItemTypesBIN_9;
	}

	if (version_D2Client <= Versions::V109d)
	{
		D2PrintStat = (D2ClientLibrary::TD2PrintStat)D2PrintStat_9;
	}

	if (version_D2Game <= Versions::V109d)
	{
		D2SetSkillBaseLevelOnClient = (D2GameLibrary::TD2SetSkillBaseLevelOnClient)D2SetSkillBaseLevelOnClient_9;
	}

	//////////////// STRUCTURE MANAGEMENT ////////////////

	shifting.ptPYPlayerData = *(DWORD*)((DWORD)D2InitPlayerData + lu->D2Common->ptPYPlayerDataOffset);
	shifting.ptSpecificData = lu->D2Common->ptSpecificDataOffset;
	shifting.ptGame = lu->D2Common->ptGameOffset;
	shifting.ptClientGame = lu->D2Common->ptClientGameOffset;
	shifting.ptInventory = lu->D2Common->ptInventoryOffset;
	shifting.ptSkills = lu->D2Common->ptSkillsOffset;
	shifting.ptImage = lu->D2Common->ptImageOffset;
	shifting.ptFrame = lu->D2Common->ptFrameOffset;
}