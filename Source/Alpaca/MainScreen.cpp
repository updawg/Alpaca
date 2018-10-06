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

char* DiabloVersionText = "";
bool active_DiabloVersionTextChange = 0;
BYTE DiabloVersionColor = 0;
bool active_PrintAlpacaVersion = 1;
BYTE AlpacaVersionColor = 4;

DWORD newTextBoxData[]={4,0x237,0x243,0xC8,0x14,0,0,0,0,0,0,2}; //type,x,y,l,h,?,?,?,?,?,?,?(0,257,C8,28)

void __stdcall PrintVersion(void** childrens, DWORD* sgnNumChildren)
{
	if (active_PrintAlpacaVersion)
	{
		char buf[30];
		void* textbox = D2CreateTextBox(newTextBoxData);
		childrens[*sgnNumChildren] = textbox;
		d2_assert((*sgnNumChildren)++ >= 40, "sgnNumChildren < MAX_CHILDREN", __FILE__, __LINE__);
		sprintf(buf, "%s %s", PROGRAM_NAME, PROGRAM_VERSION);
		D2PrintLineOnTextBox(textbox, buf, AlpacaVersionColor);
	}
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

	DWORD PrintVersionOffset = D2Launch::GetOffsetByAddition(0x7F5D);

	mem_seek(PrintVersionOffset);
	MEMJ_REF4(D2Win::D2CreateTextBox, caller_PrintVersion);

	log_msg("\n");

	isInstalled = true;
}

void __fastcall versionChange(void* screen, char* text, DWORD color)
{
	D2PrintLineOnTextBox(screen, DiabloVersionText, DiabloVersionColor);
}

void Install_VersionChange()
{
	static int isInstalled = false;
	if (isInstalled) return;

	log_msg("[Patch] D2Launch to print Mod version. (VersionChange)\n");

	DWORD PrintLodModVersionOffset = D2Launch::GetOffsetByAddition(0x801B);

	// Print LoD/Mod version.
	mem_seek(PrintLodModVersionOffset);
	MEMJ_REF4(D2Win::D2PrintLineOnTextBox, versionChange);
	
	log_msg("\n");

	isInstalled = true;
}


