/*=================================================================
	File created by Yohann NICOLAS.
	Add support 1.13d by L'Autour.

	Unassign Stats Point for futher re-assignment.

=================================================================*/

#include "plugYFiles.h"			// Install_PlugYImagesFiles()
#include "interface_Stats.h"	// Install_InterfaceStats()
#include "updateServer.h"
#include "common.h"
#include <stdio.h>

using Versions = VersionUtility::Versions;

bool active_StatsShiftClickLimit=1;
DWORD limitValueToShiftClick=5;

void UnassignStr(Unit* ptChar, int nb)
{
	log_msg("Start Unassign Strengh\n");

	int currentStr, removePtsNb;
	CharStatsBIN* charStats = D2GetCharStatsBIN(ptChar->nPlayerClass);

	currentStr = D2GetPlayerBaseStat( ptChar, STATS_STRENGTH, 0 );
	if (currentStr <= charStats->baseSTR) return;
	removePtsNb = currentStr - charStats->baseSTR >= nb ? nb : currentStr - charStats->baseSTR;
	if (currentStr - removePtsNb < 1) removePtsNb = currentStr - 1;

	log_msg("Start Unassign Strengh (cur %d, base %d, rem %d)\n",currentStr,charStats->baseSTR,removePtsNb);
	D2AddPlayerStat( ptChar, STATS_STRENGTH,	-removePtsNb ,0 );
	D2AddPlayerStat( ptChar, STATS_STATPTS,		removePtsNb ,0 );
}

void UnassignDex(Unit* ptChar, int nb)
{
	log_msg("Start Unassign Dexterity\n");

	int currentDex, removePtsNb;
	CharStatsBIN* charStats = D2GetCharStatsBIN(ptChar->nPlayerClass);
	
	currentDex = D2GetPlayerBaseStat( ptChar, STATS_DEXTERITY, 0 );
	if (currentDex <= charStats->baseDEX) return;
	removePtsNb = currentDex - charStats->baseDEX >= nb ? nb : currentDex - charStats->baseDEX;
	if (currentDex - removePtsNb < 1) removePtsNb = currentDex - 1;

	log_msg("Start Unassign Dexterity (cur %d, base %d, rem %d)\n",currentDex,charStats->baseDEX,removePtsNb);
	D2AddPlayerStat( ptChar, STATS_DEXTERITY,	-removePtsNb ,0 );
	D2AddPlayerStat( ptChar, STATS_STATPTS,		removePtsNb ,0 );
}

void UnassignVit(Unit* ptChar, int nb)
{
	log_msg("Start Unassign Vitality\n");

	int currentVit, removePtsNb, removeVitNb, removeStaNb;
	CharStatsBIN* charStats = D2GetCharStatsBIN(ptChar->nPlayerClass);
	
	currentVit = D2GetPlayerBaseStat( ptChar, STATS_VITALITY, 0 );
	if (currentVit <= charStats->baseVIT) return;
	removePtsNb = currentVit - charStats->baseVIT >= nb ? nb : currentVit - charStats->baseVIT;
	if (currentVit - removePtsNb < 1) removePtsNb = currentVit - 1;
	removeVitNb = removePtsNb * (charStats->lifePerVitality << 6);
	removeStaNb = removePtsNb * (charStats->staminaPerVitality << 6);
	
	log_msg("Start Unassign Vitality (cur %d, base %d, rem %d)\n",currentVit,charStats->baseVIT,removePtsNb);
	D2AddPlayerStat( ptChar, STATS_VITALITY,	-removePtsNb ,0 );
	D2AddPlayerStat( ptChar, STATS_MAXHP,		-removeVitNb ,0 );
	D2AddPlayerStat( ptChar, STATS_MAXSTAMINA,	-removeStaNb ,0 );
	D2AddPlayerStat( ptChar, STATS_STATPTS,		removePtsNb ,0 );
}

void UnassignEne(Unit* ptChar, int nb)
{
	log_msg("Start Unassign Energy\n");

	int currentEne, removePtsNb, removeManNb;
	CharStatsBIN* charStats = D2GetCharStatsBIN(ptChar->nPlayerClass);
	
	currentEne = D2GetPlayerBaseStat( ptChar, STATS_ENERGY, 0);
	if (currentEne <= charStats->baseENE) return;
	removePtsNb = currentEne - charStats->baseENE >= nb ? nb : currentEne - charStats->baseENE;
	if (currentEne - removePtsNb < 1) removePtsNb = currentEne - 1;
	removeManNb = removePtsNb * (charStats->manaPerMagic << 6);
	
	log_msg("Start Unassign Energy (cur %d, base %d, rem %d)\n",currentEne,charStats->baseENE,removePtsNb);
	D2AddPlayerStat( ptChar, STATS_ENERGY,		-removePtsNb ,0 );
	D2AddPlayerStat( ptChar, STATS_MAXMANA,		-removeManNb ,0 );
	D2AddPlayerStat( ptChar, STATS_STATPTS,		removePtsNb ,0 );
}

void UnassignStrPoint(Unit* ptChar)
{
	UnassignStr(ptChar, 1);
}

void UnassignStrPoints(Unit* ptChar)
{
	UnassignStr(ptChar, active_StatsShiftClickLimit ? limitValueToShiftClick: 0x7FFFFFFF);
}

void UnassignDexPoint(Unit* ptChar)
{
	UnassignDex(ptChar, 1);
}

void UnassignDexPoints(Unit* ptChar)
{
	UnassignDex(ptChar, active_StatsShiftClickLimit ? limitValueToShiftClick: 0x7FFFFFFF);
}

void UnassignVitPoint(Unit* ptChar)
{
	UnassignVit(ptChar, 1);
}

void UnassignVitPoints(Unit* ptChar)
{
	UnassignVit(ptChar, active_StatsShiftClickLimit ? limitValueToShiftClick: 0x7FFFFFFF);
}

void UnassignEnePoint(Unit* ptChar)
{
	UnassignEne(ptChar, 1);
}

void UnassignEnePoints(Unit* ptChar)
{
	UnassignEne(ptChar, active_StatsShiftClickLimit ? limitValueToShiftClick: 0x7FFFFFFF);
}


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
	mem_seek R7(D2Client, 2ACD0, 2ACC0, 315CD, 83915, 8A395, 6C2F5, BDEF5, C0695);
	memt_byte( 0xFF, 0x90 );	// NOP
	memt_byte( 0x15, 0xE8 );	// CALL
	MEMD_REF4( GetKeyState, version_D2Client >= Versions::V111 ? caller_LimitShift_111 : caller_LimitShift);
	//6FAD15CD   . FF15 68E0B66F  CALL DWORD PTR DS:[<&USER32.GetKeyState>]
	//6FB33915   . FF15 CCF0B76F  CALL DWORD PTR DS:[<&USER32.GetKeyState>]
	//6FB3A395   . FF15 08F1B76F  CALL DWORD PTR DS:[<&USER32.GetKeyState>]
	//6FB1C2F5   . FF15 10F1B76F  CALL DWORD PTR DS:[<&USER32.GetKeyState>>; \GetKeyState
	//6FB6DEF5   . FF15 04F1B76F  CALL DWORD PTR DS:[<&USER32.GetKeyState>>; \GetKeyState
	//6FB70695   . FF15 2001B86F  CALL DWORD PTR DS:[<&USER32.GetKeyState>>; \GetKeyState

	log_msg("\n");

	isInstalled = true;
}