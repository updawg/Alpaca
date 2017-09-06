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

#include "common.h"
#include <stdio.h>

int active_DisplayItemLevel = false;
DWORD nbPlayersCommandByDefault = 0;
DWORD nbPlayersCommand = 0;
int active_RunLODs = false;
int active_AlwaysDisplayLifeMana = false;
int active_EnabledTXTFilesWithMSExcel = false;
int active_DisplayBaseStatsValue = false;
int active_LadderRunewords = false;

/****************************************************************************************************/

void __stdcall displayItemlevel(LPWSTR popup, Unit* ptItem)
{
	if (onRealm && (selectModParam==MOD_NO)) return;
	WCHAR text[0x50];
	_snwprintf(text, sizeof(text), L"%s: %u\n", getLocalString(STR_ITEM_LEVEL), D2GetItemLevel(ptItem));
	D2SetColorPopup(text,WHITE);
	wcscat(popup,text);
}

FCT_ASM ( caller_displayItemlevel_113 )
	PUSH ECX
	PUSH EAX
	PUSH EAX
	LEA EAX,DWORD PTR SS:[ESP+0x1E70]
	PUSH EAX
	CALL displayItemlevel
	POP EAX
	POP ECX
	POP EDX
	PUSH 0x100
	JMP EDX
}}

FCT_ASM ( caller_displayItemlevel_111 )
	PUSH ECX
	PUSH EDX
	PUSH ECX
	LEA EAX,DWORD PTR SS:[ESP+0x1E74]
	PUSH EAX
	CALL displayItemlevel
	POP EDX
	POP ECX
	POP EAX
	PUSH 0x100
	JMP EAX
}}

FCT_ASM ( caller_displayItemlevelSet_111 )
	PUSH ECX
	PUSH EDX
	PUSH ECX
	LEA EAX,DWORD PTR SS:[ESP+0x1958]
	PUSH EAX
	CALL displayItemlevel
	POP EDX
	POP ECX
	POP EAX
	PUSH 0x100
	JMP EAX
}}


FCT_ASM ( caller_displayItemlevel )
	PUSH ECX
	PUSH EDX
	PUSH ECX
	LEA EAX,DWORD PTR SS:[ESP+0x5018]
	PUSH EAX
	CALL displayItemlevel
	POP EDX
	POP ECX
	POP EAX
	PUSH 0x100
	JMP EAX
}}

FCT_ASM ( caller_displayItemlevelSet )
	PUSH ECX
	PUSH EDX
	PUSH ECX
	LEA EAX,DWORD PTR SS:[ESP+0x1220]
	PUSH EAX
	CALL displayItemlevel
	POP EDX
	POP ECX
	POP EAX
	PUSH 0x100
	JMP EAX
}}

FCT_ASM ( caller_displayItemlevel_9 )
	PUSH ECX
	PUSH EDX
	PUSH ECX
	LEA EAX,DWORD PTR SS:[ESP+0x501C]
	PUSH EAX
	CALL displayItemlevel
	POP EDX
	POP ECX
	POP EAX
	PUSH 0x100
	JMP EAX
}}

FCT_ASM ( caller_displayItemlevelSet_9 )
	PUSH ECX
	PUSH EDX
	PUSH ECX
	LEA EAX,DWORD PTR SS:[ESP+0x1224]
	PUSH EAX
	CALL displayItemlevel
	POP EDX
	POP ECX
	POP EAX
	PUSH 0x100
	JMP EAX
}}

// [Patch]
void Install_DisplayItemLevel()
{
	static int isInstalled = false;
	if (isInstalled) return;

	log_msg("Patch D2Client for display item popup. (DisplayPopup)\n");

	// print the text in the final buffer
	mem_seek(D2Client->GetOffsetByAddition(0x3D47C, 0x3D47C, 0x438A1, 0xADD0A, 0x789DA, 0xAE0AA, 0x941C0, 0x98590));
	memt_byte(0x68 , 0xE8);
	MEMT_REF4(0x100, Game->Version >= VersionUtility::Versions::V113c ? caller_displayItemlevel_113 : Game->Version >= VersionUtility::Versions::V111 ? caller_displayItemlevel_111 : Game->Version == VersionUtility::Versions::V110 ? caller_displayItemlevel : caller_displayItemlevel_9);

	// print the text in the final buffer (for set items)
	mem_seek(D2Client->GetOffsetByAddition(0x3C452, 0x3C452,	0x427BE, 0xAC773, 0x77773, 0xACEB3, 0x92FE3, 0x973B3));
	memt_byte(0x68 , 0xE8);
	MEMT_REF4(0x100, Game->Version >= VersionUtility::Versions::V111 ? caller_displayItemlevelSet_111 : Game->Version == VersionUtility::Versions::V110 ? caller_displayItemlevelSet : caller_displayItemlevelSet_9);

	log_msg("\n");

	isInstalled = true;
}

/****************************************************************************************************/

char* msgNBPlayersString = "players %u";
DWORD* infoEnabledSendPlayersCommand;
void SendPlayersCommand()
{
	#pragma pack(1)
	struct {
		BYTE displayType;//0x15 main msg;  0x14: char popup
		BYTE un;
		BYTE zero;
		char string[0xFF];
		char null;
	} data;
	#pragma pack()

	if (!needToInit || onRealm) return;
	needToInit=0;

	DWORD info = *infoEnabledSendPlayersCommand;
	if ((info != 0) && (info != 1) && (info != 6) && (info != 8)) return;
	log_msg("SendPlayersCommand %u\n", nbPlayersCommand);

	D2SetNbPlayers(nbPlayersCommand);

	memset(&data,0,sizeof(data));
	data.displayType=0x15;
	data.un=1;
	data.zero=0;
	data.null=NULL;
	sprintf(data.string, msgNBPlayersString, nbPlayersCommand);
	D2SendMsgToAll((BYTE*)&data);
}

FCT_ASM ( caller_SendPlayersCommand )
	CALL SendPlayersCommand
	JMP D2GetResolution
}}

// [Patch]
void Install_SendPlayersCommand()
{
	static int isInstalled = false;
	if (isInstalled) return;

	log_msg("Patch D2Client for init default nb /players. (SendPlayersCommand)\n");

	infoEnabledSendPlayersCommand = (DWORD*)D2Client->GetOffsetByAddition(0x111D60, 0x110BC0, 0x107960, 0x11BFBC, 0x11C2AC, 0x11BFF8, 0x11C394, 0x11D1DC);
	if (Game->Version >= VersionUtility::Versions::V110)
	{
		msgNBPlayersString = (char*)D2Client->GetOffsetByAddition(0, 0, 0xD8448, 0xD06A8, 0xD4748, 0xD4680, 0xD4E00, 0xD470C);
	}

	// Set nb Player to default
	mem_seek(D2Client->GetOffsetByAddition(0x8723B, 0x865BB, 0x81B8B, 0xA3602, 0x66A02, 0x90162, 0xC39F2, 0x1D3F2));
	MEMJ_REF4(D2gfx->D2GetResolution, caller_SendPlayersCommand);

	log_msg("\n");

	isInstalled = true;
}

/****************************************************************************************************/

// [Patch]
void Install_RunLODs()
{
	static int isInstalled = false;
	if (isInstalled) return;

	log_msg("Patch D2gfx for launch any number of Diablo II game in the same computer. (Run Multiple Diablos)\n");

	// execute if it's our packet else continue
	mem_seek(D2gfx->GetOffsetByAddition(0x447C, 0x447C, 0x446A, 0x84CF, 0x84AF, 0x894F, 0x85BF, 0xB6B0));
	memt_byte(0x74, 0xEB);

	log_msg("\n");

	isInstalled = true;
}

/****************************************************************************************************/


FCT_ASM (caller_AlwaysDisplayLife_113)
	POP EAX
	CMP onRealm,0
	JNZ normalDisplayLife
	CMP active_AlwaysDisplayLifeMana,0
	JE normalDisplayLife
	ADD EAX,0x28
	JMP EAX
normalDisplayLife:
	CMP EDX,0x1E
	JGE cont
	ADD EAX,0xBC
cont:
	JMP EAX
}}

FCT_ASM (caller_AlwaysDisplayLife_111)
	CMP onRealm,0
	JNZ normalDisplayLife
	CMP active_AlwaysDisplayLifeMana,0
	JE normalDisplayLife
	POP EAX
	ADD EAX,0x25
	JMP EAX
normalDisplayLife:
	MOV EAX,ptResolutionY
	MOV EAX,DWORD PTR DS:[EAX]
	RETN
}}

FCT_ASM (caller_AlwaysDisplayLife)
	CMP onRealm,0
	JNZ normalDisplayLife
	CMP active_AlwaysDisplayLifeMana,0
	JE normalDisplayLife
	POP EAX
	ADD EAX,0x28
	JMP EAX
normalDisplayLife:
	MOV EAX,ptResolutionY
	MOV EAX,DWORD PTR DS:[EAX]
	RETN
}}



FCT_ASM (caller_AlwaysDisplayMana_113)
	MOV EAX,DWORD PTR DS:[ptResolutionY]
	MOV EAX,DWORD PTR DS:[EAX]
	CMP onRealm,0
	JNZ normalDisplayMana
	CMP active_AlwaysDisplayLifeMana,0
	JE normalDisplayMana
	POP EAX
	ADD EAX,0x3C
	JMP EAX
normalDisplayMana:
	RETN
}}

FCT_ASM (caller_AlwaysDisplayMana)
	CMP onRealm,0
	JNZ normalDisplayMana
	CMP active_AlwaysDisplayLifeMana,0
	JE normalDisplayMana
	POP EAX
	MOV WORD PTR SS:[ESP+0x14],0
	ADD EAX,0x38
	JMP EAX
normalDisplayMana:
	POP EAX
	POP EDI
	POP ESI
	POP EBP
	POP EBX
	ADD ESP,0x25C
	RETN
}}

FCT_ASM (caller_AlwaysDisplayMana_9)
	CMP onRealm,0
	JNZ normalDisplayMana
	CMP active_AlwaysDisplayLifeMana,0
	JE normalDisplayMana
	ADD DWORD PTR SS:[ESP],0x32
	LEA ECX,DWORD PTR SS:[ESP+0x24]
	PUSH DWORD PTR SS:[ESP+0xC]
	PUSH DWORD PTR SS:[ESP+0xC]
	PUSH DWORD PTR SS:[ESP+0xC]
	CALL D2PrintString
	MOV WORD PTR SS:[ESP+0x24],0
	RETN 0xC
normalDisplayMana:
	POP EAX
	ADD EAX,0xC2
	JMP EAX
}}

// [Patch]
void Install_AlwaysDisplayLifeMana()
{
	static int isInstalled = false;
	if (isInstalled) return;

	log_msg("Patch D2Client for always display life and mana. (ALwaysPrintLifeMana)\n");

	if (Game->Version >= VersionUtility::Versions::V113c)
	{
		mem_seek(D2Client->GetOffsetByAddition(0, 0, 0, 0, 0, 0, 0x2764A, 0x6D6FA));
		memt_byte(0x0F, 0x90);
		memt_byte(0x8C, 0xE8);
		MEMT_REF4(0x000000BC, caller_AlwaysDisplayLife_113);
	}
	else
	{
		// Always display life.
		mem_seek(D2Client->GetOffsetByAddition(0x58B32, 0x58B32, 0x5F102, 0x2D713, 0xB5DF3, 0x81733, 0, 0));
		memt_byte(0xA1, 0xE8);
		MEMT_REF4(ptResolutionY, Game->Version >= VersionUtility::Versions::V111 ? caller_AlwaysDisplayLife_111 : caller_AlwaysDisplayLife);
	}

	// Always display mana.
	if (Game->Version >= VersionUtility::Versions::V113c)
	{
		mem_seek(D2Client->GetOffsetByAddition(0, 0, 0, 0, 0, 0, 0x2770C, 0x6D7BC));
		memt_byte(0xA1 , 0xE8);
		MEMT_REF4(ptResolutionY, caller_AlwaysDisplayMana_113);
	}
	else if (Game->Version >= VersionUtility::Versions::V110)
	{
		mem_seek(D2Client->GetOffsetByAddition(0, 0, 0x5F1E6, 0x2D7FB, 0xB5EDB, 0x8181B, 0, 0));
		memt_byte(0x5F, 0xE8);
		MEMT_REF4(0x815B5D5E , caller_AlwaysDisplayMana);
		memt_byte(0xC4, 0x90);
		memt_byte(0x5C, 0x90);
		memt_byte(0x02, 0x90);
		memt_byte(0x00, 0x90);
		memt_byte(0x00, 0x90);
	}
	else
	{
		mem_seek(D2Client->GetOffsetByAddition(0x58C09, 0x58C09, 0, 0, 0, 0, 0, 0));
		memt_byte(0xE9, 0xE8);
		MEMT_REF4(0x000000C2, caller_AlwaysDisplayMana_9);
	}

	if (active_AlwaysDisplayLifeMana == 2)
	{
		active_AlwaysDisplayLifeMana = 0;
	}

	log_msg("\n");

	isInstalled = true;
}

/****************************************************************************************************/

// [Patch]
void Install_EnabledTXTFilesWithMSExcel()
{
	static int isInstalled = false;
	if (isInstalled) return;

	log_msg("Patch D2Client for enabled the opening of files already opened by MS Excel. (EnabledTXTFilesWithMSExcel)\n");

	mem_seek((DWORD)Storm->D2StormMPQOpenFile + (Game->Version >= VersionUtility::Versions::V111 ? 0x12A : 0xFF));
	memt_byte(0x01, 0x03);	//; |ShareMode = FILE_SHARE_READ|FILE_SHARE_WRITE					
	//6FC1C969  |. 6A 01          PUSH 1        ; |ShareMode = FILE_SHARE_READ

	log_msg("\n");

	isInstalled = true;
}

/****************************************************************************************************/

void __stdcall printDisplayBaseStatsValue(WORD statID, sDrawImageInfo* data, DWORD x, DWORD y, DWORD p4, DWORD p5, DWORD p6)
{
	if ( onRealm || !D2isLODGame())
	{
		D2PrintImage(data,x,y,p4,p5,p6);
		return;
	}
	Unit* ptChar = D2GetClientPlayer();

	CharStatsBIN* charStats = D2GetCharStatsBIN(ptChar->nPlayerClass);
	int minValue=1;
	switch (statID)
	{
		case STATS_STRENGTH: minValue = charStats->baseSTR; break;
		case STATS_DEXTERITY: minValue = charStats->baseDEX; break;
		case STATS_VITALITY: minValue = charStats->baseVIT; break;
		case STATS_ENERGY: minValue = charStats->baseENE; break;
	}
	int statValue = D2GetPlayerBaseStat(ptChar, statID, 0);

	if (isOnRect(D2GetMouseX(),D2GetMouseY(),x+5,y+5,32,32))
	{
		WCHAR text[100];
		_snwprintf(text, sizeof(text), getLocalString(STR_STATS_BASE_MIN), statValue, minValue);
		D2SetFont(1);
		D2PrintPopup(text, x+18, y-32, WHITE, 1);
	}

	if ( D2GetPlayerBaseStat(ptChar, 4, 0) <= 0)
		setFrame(data, 2);
	D2PrintImage(data,x,y,p4,p5,p6);
}

FCT_ASM ( caller_displayBaseStatsValue )
	POP EAX
	XOR ECX,ECX
	MOV CX,WORD PTR DS:[ESI+8]
	PUSH ECX
	PUSH EAX
	JMP printDisplayBaseStatsValue
}}

// [Patch]
void Install_DisplayBaseStatsValue()
{
	static int isInstalled = false;
	if (isInstalled) return;

	log_msg("Patch D2Client for display base stats value. (DisplayBaseStatsValue)\n");

	// Always print stat button images.
	mem_seek(D2Client->GetOffsetByAddition(0x29B12, 0x29B02, 0x30073, 0x82BBA, 0x8963A, 0x6B59A, 0xBD1B5, 0xBF955));
	memt_byte(0x8B, 0xEB);
	memt_byte(0x4C, (BYTE)D2Client->GetOffsetForVersion(0x12, 0x12, 0x13, 0x13, 0x13, 0x13, 0x13, 0x13));
	memt_byte(0x24, 0x90);
	memt_byte((BYTE)D2Client->GetOffsetForVersion(0x20, 0x20, 0x14, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C), 0x90);

	mem_seek(D2Client->GetOffsetByAddition(0x29B9D, 0x29B8D, 0x300FD, 0x82C54, 0x896D4, 0x6B637, 0xBD23E, 0xBF9DE));

	MEMJ_REF4(D2gfx->D2PrintImage, caller_displayBaseStatsValue);

	log_msg("\n");

	isInstalled = true;
}

/****************************************************************************************************/

RunesBIN* __stdcall compileRunesTxt(DWORD unused, const char* filename, BINField* ptFields, DWORD* ptRecordCount, DWORD recordLength)
{
	RunesBIN* ptRunesBin = (RunesBIN*)D2CompileTxtFile(unused, filename, ptFields, ptRecordCount, recordLength);
	for (DWORD i=0; i < *ptRecordCount; i++)
		ptRunesBin[i].Server=0;
	return ptRunesBin;
}

// [Patch]
void Install_LadderRunewords()
{
	static int isInstalled = false;
	if (isInstalled) return;
	if (Game->Version < VersionUtility::Versions::V110) return;

	log_msg("Patch D2Common for enabled the ladder only runewords. (LadderRunewords)\n");

	mem_seek(D2Common->GetOffsetByAddition(0, 0, 0x1E965, 0x61762, 0x43A72, 0x5D492, 0x724B2, 0x63782));
	MEMC_REF4(D2Common->D2CompileTxtFile, compileRunesTxt);

	log_msg("\n");

	isInstalled = true;
}