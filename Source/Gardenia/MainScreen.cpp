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
bool active_PrintPlugYVersion = 1;
BYTE colorOfPlugYVersion = 4;

DWORD newTextBoxData[]={4,0x237,0x243,0xC8,0x14,0,0,0,0,0,0,2};//type,x,y,l,h,?,?,?,?,?,?,?(0,257,C8,28)

void __stdcall printPlugYVersion(void** childrens, DWORD* sgnNumChildren)
{
	if (active_Windowed)
		SetWindowedOptions();
	if (active_PrintPlugYVersion)
	{
		char buf[30];
		void* textbox = D2CreateTextBox(newTextBoxData);
		childrens[*sgnNumChildren] = textbox;
		d2_assert((*sgnNumChildren)++ >= 40, "sgnNumChildren < MAX_CHILDREN", __FILE__, __LINE__);
		sprintf(buf, "%s %s", GARDENIA_NAME, GARDENIA_VERSION);
		D2PrintLineOnTextBox(textbox, buf, colorOfPlugYVersion);
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

// [Patch]
void Install_PrintPlugYVersion()
{
	static int isInstalled = false;
	if (isInstalled) return;

	log_msg("Patch D2Launch to print PlugY version. (PrintPlugYVersion)\n");

	// Print PlugY version.
	mem_seek(D2Launch->GetOffsetByAddition(0x7F5D, 0x7F7D, 0x9639, 0x117C7, 0x178A7, 0x16AF7, 0x18061, 0x10A11));
	MEMJ_REF4(D2Win->D2CreateTextBox, caller_printPlugYVersion);

	log_msg("\n");

	isInstalled = true;
}

/*************************************************************************************/

void __fastcall versionChange(void* screen, char* text, DWORD color)
{
	D2PrintLineOnTextBox(screen,versionText,modVersionColor);
}

FCT_ASM ( caller_VersionChange_10 )
	MOV CL, BYTE PTR DS:[modVersionColor]
	MOV BYTE PTR SS:[ESP+4], CL
	MOV EDX,versionText
	MOV ECX,EDI
	RETN
}}

// [Patch]
void Install_VersionChange()// BUG WITH 2MOD if D2Mod started before PlugY ????
{
	static int isInstalled = false;
	if (isInstalled) return;

	log_msg("Patch D2Launch to print Mod version. (VersionChange)\n");

	// Print LoD/Mod version.
	if (Game->Version >= VersionUtility::Versions::V110)
	{
		mem_seek(D2Launch->GetOffsetByAddition(0, 0, 0x9723, 0x1189B, 0x1797B, 0x16BCB, 0x18134, 0x10AE4));
		memt_byte(0x8D, 0xE8);
		MEMT_REF4(0x8B102454, caller_VersionChange_10);
		memt_byte(0xCF, 0x90);
	}
	else
	{
		mem_seek(D2Launch->GetOffsetByAddition(0x801B, 0x803B, 0x972A, 0x118A2, 0x17982, 0x16BD2, 0x1813B, 0x10AEB));
		MEMJ_REF4(D2Win->D2PrintLineOnTextBox, versionChange);
	}
	log_msg("\n");

	isInstalled = true;
}


