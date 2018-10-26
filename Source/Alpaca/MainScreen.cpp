// Copyright (C) 2004-2017 Yohann Nicolas
// Copyright (C) 2017-2018 Jonathan Vasquez <jon@xyinn.org>
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

#include <stdio.h>
#include "Common.h"

char* DiabloVersionText = "v 1.13d";
BYTE DiabloVersionColor = 0;
BYTE AlpacaVersionColor = 4;

DWORD newTextBoxData[]={4, 0x237, 0x243, 0xC8, 0x14, 0, 0, 0, 0, 0, 0, 2};

void __stdcall PrintVersion(void** childrens, DWORD* sgnNumChildren)
{
	char buf[30];
	void* textbox = D2CreateTextBox(newTextBoxData);
	childrens[*sgnNumChildren] = textbox;
	d2_assert((*sgnNumChildren)++ >= 40, "sgnNumChildren < MAX_CHILDREN", __FILE__, __LINE__);
	sprintf(buf, "%s %s", PROGRAM_NAME, PROGRAM_VERSION);
	D2PrintLineOnTextBox(textbox, buf, AlpacaVersionColor);
}

FCT_ASM ( caller_PrintVersion )
	POP ESI
	PUSH DWORD PTR [ESI+2]
	PUSH DWORD PTR [ESI+9]
	CALL PrintVersion
	CALL D2CreateTextBox
	JMP ESI
}}

void Install_PrintVersion()
{
	static int isInstalled = false;
	if (isInstalled) return;

	log_msg("[Patch] D2Launch to print Alpaca version. (PrintVersion)\n");

	DWORD PrintVersionOffset = D2Launch::GetAddress(0x10A11);

	mem_seek(PrintVersionOffset);
	MEMJ_REF4(D2Win::D2CreateTextBox, caller_PrintVersion);

	if (active_logFileMemory) log_msg("\n");
	isInstalled = true;
}

FCT_ASM(caller_VersionChange_10)
MOV CL, BYTE PTR DS : [DiabloVersionColor]
MOV BYTE PTR SS : [ESP + 4], CL
MOV EDX, DiabloVersionText
MOV ECX, EDI
RETN
}}

void Install_VersionChange()
{
	static int isInstalled = false;
	if (isInstalled) return;

	log_msg("[Patch] D2Launch to print Mod version. (VersionChange)\n");

	DWORD PrintLodModVersionOffset = D2Launch::GetAddress(0x10AE4);

	// Print LoD/Mod version.
	mem_seek(PrintLodModVersionOffset);
	memt_byte(0x8D, 0xE8);
	MEMT_REF4(0x8B102454, caller_VersionChange_10);
	memt_byte(0xCF, 0x90);
	
	if (active_logFileMemory) log_msg("\n");
	isInstalled = true;
}