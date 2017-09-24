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

#include "extraOptions.h"
#include "windowed.h"
#include "common.h"

char* versionText = "";
bool active_VersionTextChange = 0;
BYTE modVersionColor = 0;
bool active_PrintGardeniaVersion = 1;
BYTE colorOfGardeniaVersion = 4;

DWORD newTextBoxData[]={4,0x237,0x243,0xC8,0x14,0,0,0,0,0,0,2};//type,x,y,l,h,?,?,?,?,?,?,?(0,257,C8,28)

void __stdcall printPlugYVersion(void** childrens, DWORD* sgnNumChildren)
{
	if (active_Windowed)
		SetWindowedOptions();
	if (active_PrintGardeniaVersion)
	{
		char buf[30];
		void* textbox = D2CreateTextBox(newTextBoxData);
		childrens[*sgnNumChildren] = textbox;
		d2_assert((*sgnNumChildren)++ >= 40, "sgnNumChildren < MAX_CHILDREN", __FILE__, __LINE__);
		sprintf(buf, "%s %s", GARDENIA_NAME, GARDENIA_VERSION);
		D2PrintLineOnTextBox(textbox, buf, colorOfGardeniaVersion);
	}
}

FCT_ASM ( caller_printPlugYVersion )
	POP ESI
	PUSH DWORD PTR [ESI+2]
	PUSH DWORD PTR [ESI+9]
	CALL printPlugYVersion
	CALL D2CreateTextBox
	JMP ESI
}}

void Install_PrintPlugYVersion()
{
	static int isInstalled = false;
	if (isInstalled) return;

	log_msg("[Patch] D2Launch to print Gardenia version. (PrintGardeniaVersion)\n");

	// Print Gardenia version.
	mem_seek(D2Launch::GetOffsetByAddition(0x7F5D));
	MEMJ_REF4(D2Win::D2CreateTextBox, caller_printPlugYVersion);

	log_msg("\n");

	isInstalled = true;
}

/*************************************************************************************/

void __fastcall versionChange(void* screen, char* text, DWORD color)
{
	D2PrintLineOnTextBox(screen,versionText,modVersionColor);
}

void Install_VersionChange()
{
	static int isInstalled = false;
	if (isInstalled) return;

	log_msg("[Patch] D2Launch to print Mod version. (VersionChange)\n");

	// Print LoD/Mod version.
	mem_seek(D2Launch::GetOffsetByAddition(0x801B));
	MEMJ_REF4(D2Win::D2PrintLineOnTextBox, versionChange);
	
	log_msg("\n");

	isInstalled = true;
}


