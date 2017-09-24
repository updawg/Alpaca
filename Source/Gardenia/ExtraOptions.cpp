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

/****************************************************************************************************/

void __stdcall displayItemlevel(LPWSTR popup, Unit* ptItem)
{
	if (onRealm && (selectModParam==MOD_NO)) return;
	WCHAR text[0x50];
	_snwprintf(text, sizeof(text), L"%s: %u\n", getLocalString(STR_ITEM_LEVEL), D2GetItemLevel(ptItem));
	D2SetColorPopup(text,WHITE);
	wcscat(popup,text);
}

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

	log_msg("[Patch] D2Client for display item popup. (DisplayPopup)\n");

	// print the text in the final buffer
	mem_seek(D2Client::GetOffsetByAddition(0x3D47C));
	memt_byte(0x68, 0xE8);
	MEMT_REF4(0x100, caller_displayItemlevel_9);

	// print the text in the final buffer (for set items)
	mem_seek(D2Client::GetOffsetByAddition(0x3C452));
	memt_byte(0x68, 0xE8);
	MEMT_REF4(0x100, caller_displayItemlevelSet_9);

	log_msg("\n");

	isInstalled = true;
}

/****************************************************************************************************/

char* msgNBPlayersString = "players %u";
DWORD* infoEnabledSendPlayersCommand;
void SendPlayersCommand()
{
	#pragma pack(1)

	typedef struct Data {
		BYTE displayType;//0x15 main msg;  0x14: char popup
		BYTE un;
		BYTE zero;
		char string[0xFF];
		char null;
	} Data;
	#pragma pack()

	if (!needToInit || onRealm) return;
	needToInit=0;

	DWORD info = *infoEnabledSendPlayersCommand;
	if ((info != 0) && (info != 1) && (info != 6) && (info != 8)) return;
	log_msg("SendPlayersCommand %u\n", nbPlayersCommand);

	D2SetNbPlayers(nbPlayersCommand);

	Data data;
	memset(&data,0,sizeof(data));
	data.displayType=0x14;
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

	log_msg("[Patch] D2Client for init default number of players. (SendPlayersCommand)\n");

	infoEnabledSendPlayersCommand = (DWORD*)D2Client::GetOffsetByAddition(0x111D60);

	// Set default number of players
	mem_seek(D2Client::GetOffsetByAddition(0x8723B));
	MEMJ_REF4(D2gfx::D2GetResolution, caller_SendPlayersCommand);

	log_msg("\n");

	isInstalled = true;
}

/****************************************************************************************************/

void Install_RunLODs()
{
	static int isInstalled = false;
	if (isInstalled) return;

	log_msg("[Patch] D2gfx for launch any number of Diablo II game in the same computer. (Run Multiple Diablos)\n");

	// execute if it's our packet else continue
	mem_seek(D2gfx::GetOffsetByAddition(0x447C));
	memt_byte(0x74, 0xEB);

	log_msg("\n");

	isInstalled = true;
}

/****************************************************************************************************/

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

	log_msg("[Patch] D2Client for always display life and mana. (AlwaysPrintLifeMana)\n");

	// Always display life.
	mem_seek(D2Client::GetOffsetByAddition(0x58B32));
	memt_byte(0xA1, 0xE8);
	MEMT_REF4(ptResolutionY, caller_AlwaysDisplayLife);

	// Always display mana.
	mem_seek(D2Client::GetOffsetByAddition(0x58C09));
	memt_byte(0xE9, 0xE8);
	MEMT_REF4(0xC2, caller_AlwaysDisplayMana_9);
	
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

	log_msg("[Patch] D2Client for enabled the opening of files already opened by MS Excel. (EnabledTXTFilesWithMSExcel)\n");

	mem_seek((DWORD)Storm::D2StormMPQOpenFile + 0xFF);
	memt_byte(0x01, 0x03);	//; |ShareMode = FILE_SHARE_READ|FILE_SHARE_WRITE					
	//6FC1C969  |. 6A 01          PUSH 1        ; |ShareMode = FILE_SHARE_READ

	log_msg("\n");

	isInstalled = true;
}