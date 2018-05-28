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

/****************************************************************************************************/

void __stdcall displayItemlevel(LPWSTR popup, Unit* ptItem)
{
	if (selectModParam == MOD_NO) return;
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