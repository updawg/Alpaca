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

#include "plugYFiles.h"			// Install_PlugYImagesFiles()
#include "interface_Stats.h"	// Install_InterfaceStats()
#include "updateServer.h"
#include "common.h"
#include <stdio.h>

bool active_StatsShiftClickLimit=1;
DWORD limitValueToShiftClick=5;

//////////////////////////////////

void STDCALL printDisabledStatsBtn(WORD statID, sDrawImageInfo* data, DWORD x, DWORD y, DWORD p4, DWORD p5, DWORD p6)
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
		if (active_StatsShiftClickLimit)
			_snwprintf(text, sizeof(text) - 1, getLocalString(STR_STATS_UNASSIGN_WITH_LIMIT), limitValueToShiftClick);
		else
			_snwprintf(text, sizeof(text) - 1, getLocalString(STR_STATS_UNASSIGN_WITHOUT_LIMIT));
		wcscat(text,L"\n");
		int len = wcslen(text);
		_snwprintf(text + len, sizeof(text) - len, getLocalString(STR_STATS_BASE_MIN), statValue, minValue);
		D2SetFont(1);
		D2PrintPopup(text, x+18, y-32, WHITE, 1);
	}

	// TODO: Do we still need this if?
	if (minValue >= statValue)
	{
		setFrame(data, 2);
	}

	D2PrintImage(data,x,y,p4,p5,p6);
}

FCT_ASM ( caller_printUnassignStatsBtn )
	POP EAX
	XOR ECX,ECX
	MOV CX,WORD PTR DS:[ESI+8]
	PUSH ECX
	PUSH EAX
	JMP printDisabledStatsBtn
}}

BYTE currentMsgID=0;

FCT_ASM ( caller_setValue_111 )
	ADD CL,currentMsgID
	MOV WORD PTR SS:[ESP+0x19],CX
	RETN
}}

FCT_ASM ( caller_setValue )
	ADD DL,currentMsgID
	JMP D2SendToServer3
}}

DWORD STDCALL pushDown (DWORD num)
{
	Unit* ptChar = D2GetClientPlayer();

	if ( !D2isLODGame() )
	{
		if ( D2GetPlayerBaseStat(ptChar, 4, 0) > 0)
			return 1;
	} else {
		CharStatsBIN* charStats = D2GetCharStatsBIN(ptChar->nPlayerClass);
		switch (num)
		{
			case 0: if ((DWORD)charStats->baseSTR < (DWORD)D2GetPlayerBaseStat(ptChar, STATS_STRENGTH, 0))
				return 1; break;
			case 1: if ((DWORD)charStats->baseDEX < (DWORD)D2GetPlayerBaseStat(ptChar, STATS_DEXTERITY, 0))
				return 1; break;
			case 2: if ((DWORD)charStats->baseVIT < (DWORD)D2GetPlayerBaseStat(ptChar, STATS_VITALITY, 0))
				return 1; break;
			case 3: if ((DWORD)charStats->baseENE < (DWORD)D2GetPlayerBaseStat(ptChar, STATS_ENERGY, 0))
				return 1; break;
		}
	}
	return 0;
}

FCT_ASM ( caller_pushDown_111 )
	PUSH EDX
	PUSH EDX
	CALL pushDown
	POP EDX
	TEST EAX,EAX
	JNZ end_pushDown
	SUB DWORD PTR SS:[ESP],0x22
	RETN
end_pushDown:
	MOV EDI,1
	RETN
}}

FCT_ASM ( caller_pushDown )
	PUSH EDX
	PUSH EDX
	CALL pushDown
	POP EDX
	TEST EAX,EAX
	JNZ end_pushDown
	SUB DWORD PTR SS:[ESP],0x22
	RETN
end_pushDown:
	LEA EAX,DWORD PTR DS:[EDX*8]
	RETN
}}

FCT_ASM ( caller_LimitShift_111 )
	CMP EDI,limitValueToShiftClick
	JL DontTruncTheValue
	MOV EDI,limitValueToShiftClick
DontTruncTheValue:
	JMP DWORD PTR DS:[GetKeyState]
}}

FCT_ASM ( caller_LimitShift )
	CMP ESI,limitValueToShiftClick
	JL DontTruncTheValue
	MOV ESI,limitValueToShiftClick
DontTruncTheValue:
	JMP DWORD PTR DS:[GetKeyState]
}}

void Install_StatsLimitShiftClick()
{
	static int isInstalled = false;
	if (isInstalled) return;

	log_msg("Patch D2Client for limit the assigment of stat points when shift is used. (LimitShift)\n");

	// Limit the assigment of stat points.
	mem_seek(D2Client->GetOffsetByAddition(0x2ACD0, 0x2ACC0, 0x315CD, 0x83915, 0x8A395, 0x6C2F5, 0xBDEF5, 0xC0695));
	memt_byte(0xFF, 0x90);
	memt_byte(0x15, 0xE8);
	MEMD_REF4(GetKeyState, Game->Version >= VersionUtility::Versions::V111 ? caller_LimitShift_111 : caller_LimitShift);

	log_msg("\n");

	isInstalled = true;
}