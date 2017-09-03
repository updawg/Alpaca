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
#include "Utilities\LibraryUtility.h"

extern LibraryUtility* lu;

using Versions = VersionUtility::Versions;

int active_DisplayItemLevel = false;
DWORD nbPlayersCommandByDefault = 0;
DWORD nbPlayersCommand = 0;
int active_RunLODs = false;
int active_AlwaysDisplayLifeMana = false;
int active_EnabledTXTFilesWithMSExcel = false;
int active_DisplayBaseStatsValue = false;
int active_LadderRunewords = false;

/****************************************************************************************************/

void STDCALL displayItemlevel(LPWSTR popup, Unit* ptItem)
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


void Install_DisplayItemLevel()
{
	static int isInstalled = false;
	if (isInstalled) return;

	log_msg("Patch D2Client for display item popup. (DisplayPopup)\n");

	// print the text in the final buffer
	mem_seek R7(D2Client,	3D47C,	3D47C,	438A1, ADD0A, 789DA, AE0AA, 941C0, 98590);
	memt_byte( 0x68 , 0xE8);
	MEMT_REF4( 0x100, GameLib->Version >= Versions::V113c ? caller_displayItemlevel_113 : GameLib->Version >= Versions::V111 ? caller_displayItemlevel_111 : GameLib->Version == Versions::V110 ? caller_displayItemlevel : caller_displayItemlevel_9);
	//6FAE38A1   . 68 00010000        PUSH 100
	//6FB5DD0A  |. 68 00010000        PUSH 100
	//6FB289DA  |. 68 00010000	      PUSH 100
	//6FB5E0AA  |. 68 00010000    PUSH 100
	//6FB441C0  |. 68 00010000    PUSH 100
	//6FB48590  |. 68 00010000    PUSH 100

	// print the text in the final buffer (for set items)
	mem_seek R7(D2Client,	3C452,	3C452,	427BE, AC773, 77773, ACEB3, 92FE3, 973B3);
	memt_byte( 0x68 , 0xE8);
	MEMT_REF4( 0x100, GameLib->Version >= Versions::V111  ? caller_displayItemlevelSet_111 : GameLib->Version == Versions::V110 ? caller_displayItemlevelSet : caller_displayItemlevelSet_9);
	//6FAE27BE   . 68 00010000        PUSH 100
	//6FB5C773  |. 68 00010000        PUSH 100
	//6FB27773  |. 68 00010000        PUSH 100
	//6FB5CEB3  |. 68 00010000    PUSH 100
	//6FB42FE3  |. 68 00010000    PUSH 100
	//6FB473B3  |. 68 00010000    PUSH 100

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

void Install_SendPlayersCommand()
{
	static int isInstalled = false;
	if (isInstalled) return;

	log_msg("Patch D2Client for init default nb /players. (SendPlayersCommand)\n");

	infoEnabledSendPlayersCommand = (DWORD*)R7(D2Client, 111D60, 110BC0, 107960, 11BFBC, 11C2AC, 11BFF8, 11C394, 11D1DC);
	if ( GameLib->Version >= Versions::V110 )
		msgNBPlayersString = (char*)R7(D2Client, 0000, 0000, D8448, D06A8, D4748, D4680, D4E00, D470C);

	// Set nb Player to default
	mem_seek R7(D2Client,	8723B, 865BB, 81B8B, A3602, 66A02, 90162, C39F2, 1D3F2);//6FB1C7B7-6FAA0000
	MEMJ_REF4( D2GetResolution , caller_SendPlayersCommand);
	//6FB2723A  |. E8 7D8E0300    CALL <JMP.&D2gfx.#10005>
	//6FB265BA  |. E8 7D8E0300    CALL <JMP.&D2gfx.#10005>
	//6FB21B8A   . E8 4F9C0400    CALL <JMP.&D2gfx.#10005>
	//6FB53601  |. E8 E099F6FF    CALL <JMP.&D2gfx.#10000>
	//6FB16A01  |. E8 AA65FAFF    CALL <JMP.&D2gfx.#10063>
	//6FB40161  |. E8 1ECFF7FF    CALL <JMP.&D2gfx.#10043>
	//6FB739F1  |. E8 B896F4FF    CALL <JMP.&D2gfx.#10031>
	//6FACD3F1  |. E8 EAFBFEFF    CALL <JMP.&D2gfx.#10012>

	log_msg("\n");

	isInstalled = true;
}

/****************************************************************************************************/


void Install_AlwaysRegenMapInSP()
{
	static int isInstalled = false;
	if (isInstalled) return;
	
	log_msg("Patch D2Game for always regenerate maps in Single player. (AlwaysRegenMapInSP)\n");

	// Always regenerate maps in Single player
	mem_seek R7(D2Game,	517ED,	51BFA,	5DE88, 6235D, 2966D, 1E1FE, ED3BE, 26D7E);
	memt_byte( 0x74 , 0xEB);		// JMP SHORT D2Game.01FE2368
	//6FC8DE88  |. 74 09          JE SHORT D2Game.6FC8DE93
	//01FE235D  |. 74 09		  JE SHORT D2Game.01FE2368
	//01F9966D  |. 74 09          JE SHORT D2Game.01F99678
	//6FC3E1FE  |. 74 09          JE SHORT D2Game.6FC3E209
	//6FD0D3BE  |. 74 09          JE SHORT D2Game.6FD0D3C9
	//6FC46D7E  |. 74 09          JE SHORT D2Game.6FC46D89

	log_msg("\n");

	isInstalled = true;
}

/****************************************************************************************************/

void Install_RunLODs()
{
	static int isInstalled = false;
	if (isInstalled) return;

	log_msg("Patch D2gfx for launch any number of Diablo II game in the same computer. (RunLODs)\n");

	// execute if it's our packet else continue
	mem_seek R7(D2gfx, 447C, 447C, 446A, 84CF, 84AF, 894F, 85BF, B6B0);
	memt_byte( 0x74, 0xEB );	// JMP SHORT D2gfx.6FA884F6
	//6FA884AF  |. 74 45          JE SHORT D2gfx.6FA884F6
	//6FA8894F  |. 74 45          JE SHORT D2gfx.6FA88996
	//6FA885BF  |. 74 45          JE SHORT D2gfx.6FA88606
	//6FA8B6B0  |. 74 45          JE SHORT D2gfx.6FA8B6F7

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

void Install_AlwaysDisplayLifeMana()
{
	static int isInstalled = false;
	if (isInstalled) return;

	log_msg("Patch D2Client for always display life and mana. (ALwaysPrintLifeMana)\n");

	if ( GameLib->Version >= Versions::V113c )
	{
		mem_seek R7(D2Client, 0000, 0000, 0000, 0000, 0000, 0000, 2764A, 6D6FA);
		memt_byte( 0x0F , 0x90);
		memt_byte( 0x8C , 0xE8);
		MEMT_REF4( 0x000000BC, caller_AlwaysDisplayLife_113);
	}
	else
	{
		// Always display life.
		mem_seek R7(D2Client, 58B32, 58B32, 5F102, 2D713, B5DF3, 81733, 0000, 0000);
		memt_byte( 0xA1 , 0xE8);
		MEMT_REF4( ptResolutionY , GameLib->Version >= Versions::V111 ? caller_AlwaysDisplayLife_111 : caller_AlwaysDisplayLife);
	}

	// Always display mana.
	if ( GameLib->Version >= Versions::V113c )
	{
		mem_seek R7(D2Client, 0000, 0000, 0000, 0000, 0000, 0000, 2770C, 6D7BC);
		memt_byte( 0xA1 , 0xE8);
		MEMT_REF4( ptResolutionY , caller_AlwaysDisplayMana_113);
	}
	else if ( GameLib->Version >= Versions::V110 )
	{
		mem_seek R7(D2Client, 0000, 0000, 5F1E6, 2D7FB, B5EDB, 8181B, 0000, 0000);
		memt_byte( 0x5F , 0xE8);
		MEMT_REF4( 0x815B5D5E , caller_AlwaysDisplayMana);
		memt_byte( 0xC4 , 0x90);	// NOP
		memt_byte( 0x5C , 0x90);	// NOP
		memt_byte( 0x02 , 0x90);	// NOP
		memt_byte( 0x00 , 0x90);	// NOP
		memt_byte( 0x00 , 0x90);	// NOP
	}
	else
	{
		mem_seek R7(D2Client, 58C09, 58C09, 0000, 0000, 0000, 0000, 0000, 0000);
		memt_byte( 0xE9 , 0xE8);
		MEMT_REF4( 0x000000C2 , caller_AlwaysDisplayMana_9);
	}

	if (active_AlwaysDisplayLifeMana == 2)
	{
		active_AlwaysDisplayLifeMana = 0;
	}

	log_msg("\n");

	isInstalled = true;
}

/****************************************************************************************************/

void Install_EnabledTXTFilesWithMSExcel()
{
	static int isInstalled = false;
	if (isInstalled) return;

	log_msg("Patch D2Client for enabled the opening of files already opened by MS Excel. (EnabledTXTFilesWithMSExcel)\n");

	mem_seek( (DWORD)D2StormMPQOpenFile + (version_Storm >= Versions::V111 ? 0x12A : 0xFF) );
	memt_byte( 0x01 , 0x03);	//; |ShareMode = FILE_SHARE_READ|FILE_SHARE_WRITE									
	//6FC1C969  |. 6A 01          PUSH 1        ; |ShareMode = FILE_SHARE_READ

	log_msg("\n");

	isInstalled = true;
}


/****************************************************************************************************/

void STDCALL printDisplayBaseStatsValue(WORD statID, sDrawImageInfo* data, DWORD x, DWORD y, DWORD p4, DWORD p5, DWORD p6)
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

void Install_DisplayBaseStatsValue()
{
	static int isInstalled = false;
	if (isInstalled) return;

	log_msg("Patch D2Client for display base stats value. (DisplayBaseStatsValue)\n");

	// Always print stat button images.
	mem_seek (lu->D2Client->DisplayBaseStatsBaseOffset1);
	memt_byte( 0x8B, 0xEB );	// JMP SHORT D2Client.6FAD0088
	memt_byte( 0x4C, lu->D2Client->DisplayBaseStatsModOffset1 );
	memt_byte( 0x24, 0x90 );	// NOP
	memt_byte(lu->D2Client->DisplayBaseStatsModOffset2, 0x90 );			// NOP (V109d:0x20 , V110:0x14
	//6FAD0073     8B4C24 14         MOV ECX,DWORD PTR SS:[ESP+14]
	//6FB32BBA   > 8B4C24 1C         MOV ECX,DWORD PTR SS:[ESP+1C]
	//6FB3963A   > 8B4C24 1C         MOV ECX,DWORD PTR SS:[ESP+1C]
	//6FB1B59A   > 8B4C24 1C      MOV ECX,DWORD PTR SS:[ESP+1C]
	//6FB6D1B5  |> 8B4C24 1C      MOV ECX,DWORD PTR SS:[ESP+1C]
	//6FB6F955  |> 8B4C24 1C      MOV ECX,DWORD PTR SS:[ESP+1C]

	mem_seek(lu->D2Client->DisplayBaseStatsBaseOffset2);
	MEMJ_REF4( D2PrintImage, caller_displayBaseStatsValue);
	//6FB32C53   . E8 82A3F8FF    CALL <JMP.&D2gfx.#10047>
	//6FB396D3   . E8 D238F8FF    CALL <JMP.&D2gfx.#10044>
	//6FB1B636   . E8 431AFAFF    CALL <JMP.&D2gfx.#10024>
	//6FB6D23D  |. E8 54FEF4FF    |CALL <JMP.&D2gfx.#10041>
	//6FB6F9DD  |. E8 54FEF4FF    |CALL <JMP.&D2gfx.#10042>

	log_msg("\n");

	isInstalled = true;
}


/****************************************************************************************************/

RunesBIN* STDCALL compileRunesTxt(DWORD unused, const char* filename, BINField* ptFields, DWORD* ptRecordCount, DWORD recordLength)
{
	RunesBIN* ptRunesBin = (RunesBIN*)D2CompileTxtFile(unused, filename, ptFields, ptRecordCount, recordLength);
	for (DWORD i=0; i < *ptRecordCount; i++)
		ptRunesBin[i].Server=0;
	return ptRunesBin;
}

void Install_LadderRunewords()
{
	static int isInstalled = false;
	if (isInstalled) return;

	if ( version_D2Common < Versions::V110 )
		return;

	log_msg("Patch D2Common for enabled the ladder only runewords. (LadderRunewords)\n");

	mem_seek R7(D2Common, 0000, 0000, 1E965, 61762, 43A72, 5D492, 724B2, 63782);
	MEMC_REF4( D2CompileTxtFile, compileRunesTxt);
	//01B6E964  |. E8 0714FFFF    CALL D2Common.#10578                     ; \#10578
	//6FDB1761  |. E8 FAA8FCFF    CALL D2Common.#10653                     ; \#10653
	//6FD93A71  |. E8 EAADFCFF    CALL D2Common.#10496                     ; \#10496
	//6FDAD491  |. E8 BA49FEFF    CALL D2Common.#10244                     ; \#10244
	//6FDC24B1  |. E8 8ACAFEFF    CALL D2Common.#10849                     ; \#10849
	//6FDB3781  |. E8 5A93FAFF    CALL D2Common.#10037                     ; \#10037

	log_msg("\n");

	isInstalled = true;
}