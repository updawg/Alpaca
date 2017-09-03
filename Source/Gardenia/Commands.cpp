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

#include "updateServer.h"
#include "updateClient.h"
#include "infinityStash.h"
#include "newInterfaces.h"
#include "newInterface_CubeListing.h"
#include "extraOptions.h"
#include "windowed.h"
#include "common.h"

using Versions = VersionUtility::Versions;

bool active_Commands=true;

bool active_listAllCubeFormula=true;
bool active_savegame=false;

#define MAX_CMD_SIZE 200

const char * CMD_PLAYERS="players set to";

const char * CMD_SAVE="/save";
const char * CMD_SELECTPAGE="/page";

const char * CMD_LOCK_MOUSE = "/lockmouse";
const char * CMD_LOCK_MOUSE2 = "/lock";
const char * CMD_UNLOCK_MOUSE = "/unlockmouse";
const char * CMD_UNLOCK_MOUSE2 = "/unlock";

const char * CMD_RENAME_CHAR="/renamechar";

const char * CMD_REPAGE_NAME = "/renamepage";
const char * CMD_SET_INDEX = "/setindex";
const char * CMD_SET_MAIN_INDEX = "/setmainindex";
const char * CMD_RESET_INDEX = "/resetindex";
const char * CMD_INSERT_PAGE = "/insertpage";
const char * CMD_DELETE_PAGE = "/deletepage";
const char * CMD_SWAP = "/swap";
const char * CMD_TOGGLE = "/toggle";

const char * CMD_DISPLAY_MANA_LIFE = "/dml";
const char * CMD_DISPLAY_LIFE_MANA = "/dlm";
const char * CMD_DISPLAY_LIFE = "/dl";
const char * CMD_DISPLAY_MANA = "/dm";

const char * CMD_LISTCUBEFORMULA="/listcube";

void savePlayers(Unit* ptChar)
{
	if (active_savegame)
		D2SaveGame(PCGame);
}

void maxGold(Unit* ptChar)
{
	log_msg("maxGold\n");

	DWORD maxGold =     D2GetMaxGold(ptChar);
	DWORD maxGoldBank = D2GetMaxGoldBank(ptChar);
	DWORD playerGold = D2GetPlayerStat(ptChar, STATS_GOLD, 0);
	DWORD playerGoldBank = D2GetPlayerStat(ptChar, STATS_GOLDBANK, 0);
	if ( (playerGold < maxGold) || (playerGoldBank < maxGoldBank) ) {
		D2AddPlayerStat( ptChar, STATS_GOLD,	 maxGold-playerGold, 0 );
		D2AddPlayerStat( ptChar, STATS_GOLDBANK, maxGoldBank-playerGoldBank, 0 );
	} else {
		D2AddPlayerStat( ptChar, STATS_GOLD,	 100000, 0 );
	}
	if (active_sharedGold)
	{
		PCPY->sharedGold = 0xFFFFFFFF;
		updateClient(ptChar, UC_SHARED_GOLD, PCPY->sharedGold, 0, 0);
	}
}

void putGold(Unit* ptChar, DWORD amount)
{
	if (!active_sharedGold) return;
	log_msg("putGold : %d\n", amount);

	DWORD playerGold = D2GetPlayerStat(ptChar, STATS_GOLD, 0);
	DWORD toAdd = 0xFFFFFFFF - PCPY->sharedGold;
	if (playerGold < toAdd)
		toAdd = playerGold;
	if (amount && (toAdd > amount))
		toAdd = amount;
	D2AddPlayerStat(ptChar, STATS_GOLD, 0-toAdd, 0);
	PCPY->sharedGold += toAdd;
	updateClient(ptChar, UC_SHARED_GOLD, PCPY->sharedGold, 0, 0);
}

void takeGold(Unit* ptChar, DWORD amount)
{
	if (!active_sharedGold) return;
	log_msg("takeGold : %d\n", amount);

	DWORD maxGold =     D2GetMaxGold(ptChar) - D2GetPlayerStat(ptChar, STATS_GOLD, 0);
//	DWORD maxGoldBank = D2GetMaxGoldBank(ptChar) - D2GetPlayerStat(ptChar, STATS_GOLDBANK, 0);
	DWORD toAdd = maxGold < PCPY->sharedGold ? maxGold : PCPY->sharedGold;
	if (amount && (toAdd > amount))
		toAdd = amount;
	D2AddPlayerStat( ptChar, STATS_GOLD, toAdd, 0 );
	PCPY->sharedGold -= toAdd;
	updateClient(ptChar, UC_SHARED_GOLD, PCPY->sharedGold, 0, 0);
}


void updateSharedGold(DWORD goldAmount)
{
	Unit* ptChar = D2GetClientPlayer();
	log_msg("SharedGold = %d\n",goldAmount);
	PCPY->sharedGold = goldAmount;
}

bool renameCharacter(Unit* ptChar, const char* newName)
{
	int len = strlen(newName);
	if (len < 2 || len > 15)
		return 0;
	for (int i = 0; i < len; i++)
	{
		char c = newName[i];
		if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_')))
			return 1;
	}
	// Move current save file
	{
		char szCurrentFile[MAX_PATH];
		char szNewFile[MAX_PATH];

		//Get temporary savefile name.
		D2FogGetSavePath(szCurrentFile, MAX_PATH);
		D2FogGetSavePath(szNewFile, MAX_PATH);
		strcat(szCurrentFile, ptChar->ptPlayerData->name);
		strcat(szNewFile, newName);
		strcat(szCurrentFile, ".");
		strcat(szNewFile, ".");
		int curLen = strlen(szCurrentFile);
		int newLen = strlen(szNewFile);
		strcpy(&szCurrentFile[curLen], "d2s");
		strcpy(&szNewFile[newLen], "d2s");
		MoveFile(szCurrentFile, szNewFile);
		strcpy(&szCurrentFile[curLen], "d2x");
		strcpy(&szNewFile[newLen], "d2x");
		MoveFile(szCurrentFile, szNewFile);
		strcpy(&szCurrentFile[curLen], "key");
		strcpy(&szNewFile[newLen], "key");
		MoveFile(szCurrentFile, szNewFile);
		strcpy(&szCurrentFile[curLen], "ma0");
		strcpy(&szNewFile[newLen], "ma0");
		MoveFile(szCurrentFile, szNewFile);
		strcpy(&szCurrentFile[curLen], "ma1");
		strcpy(&szNewFile[newLen], "ma1");
		MoveFile(szCurrentFile, szNewFile);
		strcpy(&szCurrentFile[curLen], "ma2");
		strcpy(&szNewFile[newLen], "ma2");
		MoveFile(szCurrentFile, szNewFile);
		strcpy(&szCurrentFile[curLen], "ma3");
		strcpy(&szNewFile[newLen], "ma3");
		MoveFile(szCurrentFile, szNewFile);
		strcpy(&szCurrentFile[curLen], "ma4");
		strcpy(&szNewFile[newLen], "ma4");
		MoveFile(szCurrentFile, szNewFile);
		strcpy(&szCurrentFile[curLen], "map");
		strcpy(&szNewFile[newLen], "map");
		MoveFile(szCurrentFile, szNewFile);
	}
	// Update server
	for (int i = 0; i <= len; i++)
		updateServer(US_RENAME + (newName[i] << 8));

	// Update client
	log_msg("Rename on Client : %s -> %s\n", ptChar->ptPlayerData->name, newName);
	strcpy(ptChar->ptPlayerData->name, newName);
	updateServer(US_SAVE);
	return 0;
}
/****************************************************************************************************/

int STDCALL commands (char* ptText)
{
	log_msg("Command : %s\n", ptText);
	Unit* ptChar = D2GetClientPlayer();

	char command[MAX_CMD_SIZE];
	ZeroMemory(command,MAX_CMD_SIZE);
	strncpy(command,ptText,MAX_CMD_SIZE-1);
	_strlwr(command);

	if (!strncmp(command, CMD_PLAYERS, strlen(CMD_PLAYERS)))
	{
		int nb = atoi(&command[strlen(CMD_PLAYERS)]);
		if (nb > 0 && nb <= 64)
			nbPlayersCommand = nb;
		return 1;
	}

	if (!strcmp(command, CMD_SAVE))
	{
		if (onRealm) return 1;
		updateServer(US_SAVE);
		return 0;
	}

	if (!strncmp(command, CMD_SELECTPAGE, strlen(CMD_SELECTPAGE)))
	{
		if (!active_newInterfaces) return 1;
		GoStatPage(atoi(&command[strlen(CMD_SELECTPAGE)]) - 1);
		return 0;
	}

	if (!strcmp(command, CMD_LOCK_MOUSE) || !strcmp(command, CMD_LOCK_MOUSE2))
	{
		if (onRealm) return 1;
		lockMouseCursor();
		return 0;
	}

	if (!strcmp(command, CMD_UNLOCK_MOUSE) || !strcmp(command, CMD_UNLOCK_MOUSE2))
	{
		if (onRealm) return 1;
		unlockMouseCursor();
		return 0;
	}

	if (!strncmp(command, CMD_RENAME_CHAR, strlen(CMD_RENAME_CHAR)))
	{
		const char* param = &ptText[strlen(CMD_RENAME_CHAR)];
		if (param[0] != ' ')
			return 1;
		param++;
		return renameCharacter(ptChar, param);
	}

	if (!strncmp(command, CMD_REPAGE_NAME,strlen(CMD_REPAGE_NAME)))
	{
		if (!active_multiPageStash) return 1;
		char* param = &ptText[strlen(CMD_REPAGE_NAME)];
		Stash* ptStash = PCPY->currentStash;
		if (!ptStash)
			return 0;

		int len = strlen(param);
		while (len > 0 && param[0] == ' ')
		{
			param++;
			len--;
		}
		if (len > 0 && len <= 15)
		{
			log_msg("Rename current page on Client : %s -> %s\n", ptStash->name, param);
			renameCurrentStash(ptChar, param);
			for (int i = 0; i <= len; i++)
				updateServer(US_PAGENAME + (param[i] << 8));
		}
		else if (len == 0)
		{
			log_msg("Rename current page on Client: %s\n", ptStash->name);
			renameCurrentStash(ptChar, NULL);
			updateServer(US_PAGENAME);
		}
		return 0;
	}

	if (!strcmp(command, CMD_SET_INDEX))
	{
		if (!active_multiPageStash) return 1;
		updateServer(US_SET_INDEX);
		return 0;
	}

	if (!strcmp(command, CMD_SET_MAIN_INDEX))
	{
		if (!active_multiPageStash) return 1;
		updateServer(US_SET_MAIN_INDEX);
		return 0;
	}

	if (!strcmp(command, CMD_RESET_INDEX))
	{
		if (!active_multiPageStash) return 1;
		updateServer(US_RESET_INDEX);
		return 0;
	}

	if (!strcmp(command, CMD_INSERT_PAGE))
	{
		if (!active_multiPageStash) return 1;
		insertStash(ptChar);
		updateServer(US_INSERT_PAGE);
		return 0;
	}

	if (!strcmp(command, CMD_DELETE_PAGE))
	{
		if (!active_multiPageStash) return 1;
		if (deleteStash(ptChar, true))
			updateServer(US_DELETE_PAGE);
		return 0;
	}

	if (!strncmp(command, CMD_SWAP, strlen(CMD_SWAP)))
	{
		if (!active_multiPageStash) return 1;
		int page = atoi(&command[strlen(CMD_SWAP)]) - 1;
		if (page < 0 && PCPY->currentStash->nextStash)
			page = PCPY->currentStash->nextStash->id;
		if (page < 0)
			return 1;
		updateServer(US_SWAP3 + ((page & 0xFF000000) >> 16));
		updateServer(US_SWAP2 + ((page & 0xFF0000) >> 8));
		updateServer(US_SWAP1 + (page & 0xFF00));
		updateServer(US_SWAP0 + ((page & 0xFF) << 8));
		return 0;
	}

	if (!strncmp(command, CMD_TOGGLE, strlen(CMD_TOGGLE)))
	{
		if (!active_sharedStash) return 1;
		int page = atoi(&command[strlen(CMD_TOGGLE)]) - 1;
		if (page < 0)
			return 1;
		updateServer(US_SWAP3 + ((page & 0xFF000000) >> 16));
		updateServer(US_SWAP2 + ((page & 0xFF0000) >> 8));
		updateServer(US_SWAP1 + (page & 0xFF00));
		updateServer(US_SWAP0_TOGGLE + ((page & 0xFF) << 8));
		return 0;
	}

	if (!strcmp(command,CMD_DISPLAY_LIFE))
	{
		active_AlwaysDisplayLifeMana = !active_AlwaysDisplayLifeMana;
		return 0;
	}

	if (!strcmp(command,CMD_DISPLAY_MANA))
	{
		active_AlwaysDisplayLifeMana = !active_AlwaysDisplayLifeMana;
		return 0;
	}

	if (!strcmp(command,CMD_DISPLAY_LIFE_MANA) || !strcmp(command,CMD_DISPLAY_MANA_LIFE))
	{
		active_AlwaysDisplayLifeMana = !active_AlwaysDisplayLifeMana;
		return 0;
	}

	if (!strcmp(command, CMD_LISTCUBEFORMULA))
	{
		if (!active_listAllCubeFormula) return 1;
		listAllCubeFormula();
		return 0;
	}

	return 1;
}

FCT_ASM ( caller_Commands )
	TEST EAX,EAX
	JE MANAGESOUNDCHAOSDEBUG
	PUSH DWORD PTR SS:[ESP+0x1C]
	CALL commands
	TEST EAX,EAX
	JNZ MANAGESOUNDCHAOSDEBUG
	ADD DWORD PTR SS:[ESP],7
MANAGESOUNDCHAOSDEBUG:
	RETN 8
}}

FCT_ASM ( caller_Commands_111 )
	TEST EAX,EAX
	JE MANAGESOUNDCHAOSDEBUG
	PUSH ESI
	CALL commands
	TEST EAX,EAX
	JNZ MANAGESOUNDCHAOSDEBUG
	ADD DWORD PTR SS:[ESP],7
MANAGESOUNDCHAOSDEBUG:
	RETN 8
}}

FCT_ASM ( caller_Commands_113d )
	TEST EAX,EAX
	JE MANAGESOUNDCHAOSDEBUG
	PUSH EDI
	CALL commands
	TEST EAX,EAX
	JNZ MANAGESOUNDCHAOSDEBUG
	ADD DWORD PTR SS:[ESP],7
MANAGESOUNDCHAOSDEBUG:
	RETN 8
}}


void Install_Commands()
{
	static int isInstalled = false;
	if (isInstalled) return;

	Install_UpdateServer();

	log_msg("Patch D2Client for install commands. (Commands)\n");

	active_listAllCubeFormula = version_D2Common >= Versions::V110;
	active_savegame = version_D2Common >= Versions::V111;

	// Run custom commmand
	mem_seek R7(D2Client, 2C120, 2C110, 32BDD, C1EE6, 91C16, 86926, 70AE6, B1FD6);
	memt_byte( 0x83, 0xE8 );	// CALL 
	MEMT_REF4( 0xC08508C4 , version_D2Client == Versions::V113d ? caller_Commands_113d : version_D2Client >= Versions::V111 ? caller_Commands_111 : caller_Commands);
	//6FB71EE6   . 83C4 08        ADD ESP,8
	//6FB71EE7   . 85C0           TEST EAX,EAX
	//6FB41C16  |. 83C4 08        ADD ESP,8
	//6FB41C19  |. 85C0           TEST EAX,EAX
	//6FB36926  |. 83C4 08        ADD ESP,8
	//6FB36929  |. 85C0           TEST EAX,EAX
	//6FB20AE6  |. 83C4 08        ADD ESP,8
	//6FB20AE9  |. 85C0           TEST EAX,EAX
	//6FB20AE6  |. 83C4 08        ADD ESP,8
	//6FB20AE9  |. 85C0           TEST EAX,EAX
	//6FB61FD6  |. 83C4 08        ADD ESP,8
	//6FB61FD9  |. 85C0           TEST EAX,EAX

	log_msg("\n");

	isInstalled = true;
}
