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
#include "Utilities/LibraryUtility.h"

using Versions = VersionUtility::Versions;

char* versionText = "";
bool active_VersionTextChange = 0;
BYTE modVersionColor = 0;
bool active_PrintPlugYVersion = 1;
BYTE colorOfPlugYVersion = 4;

DWORD newTextBoxData[]={4,0x237,0x243,0xC8,0x14,0,0,0,0,0,0,2};//type,x,y,l,h,?,?,?,?,?,?,?(0,257,C8,28)

void STDCALL printPlugYVersion(void** childrens, DWORD* sgnNumChildren)
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


void Install_PrintPlugYVersion()
{
	static int isInstalled = false;
	if (isInstalled) return;

	log_msg("Patch D2Launch to print PlugY version. (PrintPlugYVersion)\n");

	// Print PlugY version.
	mem_seek R7(D2Launch, 7F5D, 7F7D, 9639, 117C7, 178A7, 16AF7, 18061, 10A11);
	MEMJ_REF4( D2CreateTextBox, caller_printPlugYVersion);
	//6FA19638  |. E8 1BED0000    CALL <JMP.&D2Win.#10017>
	//6FA517C6  |. E8 6F81FFFF    CALL <JMP.&D2Win.#10147>
	//6FA578A6  |. E8 D71FFFFF    CALL <JMP.&D2Win.#10113>
	//6FA56B1F  |. E8 1A2EFFFF    CALL <JMP.&D2Win.#10098>
	//6FA56AF6  |. E8 432EFFFF    CALL <JMP.&D2Win.#10098>
	//6FA58060  |. E8 ED18FFFF    CALL <JMP.&D2Win.#10098>
	//6FA50A10  |. E8 218FFFFF    CALL <JMP.&D2Win.#10164>


	log_msg("\n");

	isInstalled = true;
}

/*************************************************************************************/

void FASTCALL versionChange(void* screen, char* text, DWORD color)
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

void Install_VersionChange()// BUG WITH 2MOD if D2Mod started before PlugY ????
{
	static int isInstalled = false;
	if (isInstalled) return;

	log_msg("Patch D2Launch to print Mod version. (VersionChange)\n");

//6FA18012  |. 8D5424 0C      LEA EDX,DWORD PTR SS:[ESP+C]
//6FA18016  |. 8BCE           MOV ECX,ESI
//6FA18018  |. 6A 00          PUSH 0

	if (lu->Game->DllVersion == VersionUtility::Versions::V114d)
	{
		log_msg("Patch here");
	}
	// Print LoD/Mod version.
	else if (version_D2Launch >= Versions::V110)
	{
		mem_seek R7(D2Launch, 00000, 00000, 9723, 1189B, 1797B, 16BCB, 18134, 10AE4);//6FA19721-6FA10000
		memt_byte( 0x8D, 0xE8 );	// CALL
		MEMT_REF4( 0x8B102454 , caller_VersionChange_10);
		memt_byte( 0xCF, 0x90 );	// NOP
		//6FA19723  |. 8D5424 10      LEA EDX,DWORD PTR SS:[ESP+10]
		//6FA19727  |. 8BCF           MOV ECX,EDI
		//6FA5189B  |. 8D5424 10      LEA EDX,DWORD PTR SS:[ESP+10]
		//6FA5189F  |. 8BCF           MOV ECX,EDI
		//6FA5797B  |. 8D5424 10      LEA EDX,DWORD PTR SS:[ESP+10]
		//6FA5797F  |. 8BCF           MOV ECX,EDI
		//6FA56BCB  |. 8D5424 10      LEA EDX,DWORD PTR SS:[ESP+10]
		//6FA56BCF  |. 8BCF           MOV ECX,EDI
		//6FA58134  |. 8D5424 10      LEA EDX,DWORD PTR SS:[ESP+10]
		//6FA58138  |. 8BCF           MOV ECX,EDI
		//6FA50AE4  |. 8D5424 10      LEA EDX,DWORD PTR SS:[ESP+10]
		//6FA50AE8  |. 8BCF           MOV ECX,EDI
	} else {
		mem_seek R7(D2Launch, 801B, 803B, 972A, 118A2, 17982, 16BD2, 1813B, 10AEB);
		MEMJ_REF4( D2PrintLineOnTextBox, versionChange);
		//6FA19729  |. E8 88EB0000    CALL <JMP.&D2Win.#10046>
		//6FA518A1  |. E8 267FFFFF    CALL <JMP.&D2Win.#10061>
		//6FA57981  |. E8 781EFFFF    CALL <JMP.&D2Win.#10075>
		//6FA56BD1  |. E8 EA2CFFFF    CALL <JMP.&D2Win.#10015>
		//6FA5813A  |. E8 8F17FFFF    CALL <JMP.&D2Win.#10022>
		//6FA50AEA  |. E8 DF8CFFFF    CALL <JMP.&D2Win.#10051>
	}
	log_msg("\n");

	isInstalled = true;
}


