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
#include "infinityStash.h"
#include "commands.h"
#include "common.h"

int renameIndex = 0;
char renameString[16];
DWORD PageSwap;
DWORD PageSelect;

int __stdcall handleServerUpdate(Unit* ptChar, WORD param)
{
	int type = param & 0xFF;
	DWORD arg = (param & 0xFF00) >> 8;
	log_msg("Received custom message: type=%i, arg=%i\n", type, arg);
	switch(type)
	{
		case US_SET_INDEX:				setCurrentStashIndex(ptChar, 1); return 1;
		case US_UNSET_INDEX:			setCurrentStashIndex(ptChar, 0); return 1;
		case US_SET_MAIN_INDEX:			setCurrentStashIndex(ptChar, 2); return 1;
		case US_SELECT_PREVIOUS :		selectPreviousStash( ptChar ); return 1;
		case US_SELECT_NEXT :			selectNextStash( ptChar ); return 1;
		case US_SELECT_SELF :			if (active_sharedStash) toggleToSelfStash( ptChar ); return 1;
		case US_SELECT_SHARED :			if (active_sharedStash) toggleToSharedStash( ptChar ); return 1;
		case US_SELECT_PREVIOUS_INDEX :	selectPreviousIndexStash( ptChar ); return 1;
		case US_SELECT_NEXT_INDEX :		selectNextIndexStash( ptChar ); return 1;
		case US_SELECT_PREVIOUS2 :		selectPrevious2Stash( ptChar ); return 1;
		case US_SELECT_NEXT2 :			selectNext2Stash( ptChar ); return 1;
		case US_SELECT_PREVIOUS_INDEX2:	selectPreviousIndex2Stash( ptChar ); return 1;
		case US_SELECT_NEXT_INDEX2 :	selectNextIndex2Stash( ptChar ); return 1;
		case US_INSERT_PAGE:			insertStash(ptChar); selectNextStash(ptChar); return 1;
		case US_DELETE_PAGE:			deleteStash(ptChar, false); return 1;
		case US_SELECT_PAGE3:			PageSelect = arg << 24; return 1;
		case US_SELECT_PAGE2:			PageSelect |= arg << 16; return 1;
		case US_SELECT_PAGE1:			PageSelect |= arg << 8; return 1;
		case US_SELECT_PAGE:			jumpToPage(ptChar, PageSelect | arg); PageSelect = 0; return 1;
		case US_MAXGOLD :				maxGold(ptChar); return 1;
		case US_PUTGOLD :				putGold(ptChar, 0); return 1;
		case US_TAKEGOLD :				takeGold(ptChar, 0); return 1;
		case US_SWAP3 :					PageSwap = arg << 24; return 1;
		case US_SWAP2 :					PageSwap |= arg << 16; return 1;
		case US_SWAP1 :					PageSwap |= arg << 8; return 1;
		case US_SWAP0:					swapStash(ptChar, PageSwap | arg, false); PageSwap = 0; return 1;
		case US_SWAP0_TOGGLE :			swapStash(ptChar, PageSwap | arg, true); PageSwap = 0; return 1;
		case US_PAGENAME:
			if (renameIndex == 0)
				for (int i = 0; i < 16; i++)
					renameString[i] = 0;
			renameString[renameIndex++] = (char)arg;
			if (arg == 0)
			{
				renameIndex = 0;
				log_msg("Rename current page on Server : %s -> %s\n", PCPY->currentStash->name, renameString);
				renameCurrentStash(ptChar, renameString);
			}
			return 1;
		default :
			return 0;
	}
}

FCT_ASM( caller_handleServerUpdate_9)
	XOR EDX,EDX
	MOV DX,WORD PTR DS:[EAX+1]
	PUSH ECX
	PUSH EDX
	PUSH EDX
	PUSH ECX
	CALL handleServerUpdate
	POP EDX
	POP ECX
	TEST EAX,EAX
	JNZ END_RCM
	RETN
END_RCM:
	POP EAX
	XOR EAX,EAX
	RETN 8
}}

void Install_UpdateServer()
{
	static int isInstalled = false;
	if (isInstalled) return;

	log_msg("[Patch] D2Game for received button click message. (UpdateServer)\n");

	DWORD ManageButtonClickMessageFromClientOffset = D2Game::GetOffsetByAddition(0x4A702);

	// manage button click message from Client.
	mem_seek(ManageButtonClickMessageFromClientOffset);
	memt_byte(0x33, 0xE8);
	MEMT_REF4(0x508B66D2, caller_handleServerUpdate_9);
	memt_byte(0x01, 0x90);
	
	if (active_logFileMemory) log_msg("\n");
	isInstalled = true;
}