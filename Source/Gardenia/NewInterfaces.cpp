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

#include "plugYFiles.h"		// Install_PlugYImagesFiles()
#include "globalVariable.h"
#include "updateServer.h"	// Install_UpdateServer()
#include "interface_Stats.h"// Install_InterfaceStats()
#include "newInterfaces.h"
#include "newInterface_StatsPageTwo.h"
#include "common.h"
#include <stdio.h>

bool active_newInterfaces=false;
bool selectMainPageOnOpening=true;
bool printBackgroundOnMainPage=true;

DWORD bDontPrintBorder=false;

int selectedPage=0;
int lastPage=0;
int extraHiddenPage=0;

void GoNextStatPage()
{
	selectedPage++;
	if ( selectedPage > lastPage)
		selectedPage = 0;
}

void GoPreviousStatPage()
{
	selectedPage--;
	if ( selectedPage < 0 )
		selectedPage = lastPage;
}

int GetCurrentPage()
{
	return selectedPage;
}

void __stdcall printCustomPage()
{
	if ( (selectedPage > 0) && (selectedPage<=lastPage) )
		printNewStatsPageTwo(selectedPage);
	else
		D2PrintStatsPage();
}

DWORD __stdcall mouseCustomPageLeftDown(sWinMessage* msg)
{
	if ( (selectedPage > 0) && (selectedPage<=lastPage) )
		return mouseNewStatsPageTwoLeftDown(msg);
	else
		return -1;
}

DWORD __stdcall mouseCustomPageLeftUp(sWinMessage* msg)
{
	if ( (selectedPage > 0) && (selectedPage <= lastPage) )
		return mouseNewStatsPageTwoLeftUp(msg);
	else
		return -1;
}

FCT_ASM ( caller_DontPrintBorder )
	MOV ECX,bDontPrintBorder
	TEST ECX,ECX
	JE printBorder
	MOV bDontPrintBorder,0
	ADD DWORD PTR SS:[ESP],0xB6
	RETN
printBorder:
	MOV ECX,0x12
	RETN
}}

FCT_ASM ( caller_mouseCustomPageLeftDown_9 )
	PUSH EAX
	PUSH EDI
	CALL mouseCustomPageLeftDown
	TEST EAX,EAX
	POP EAX
	JE end_mouseNewPageLDown
	JG continue_mouseNewPageLDown
	LEA ECX,DWORD PTR DS:[EAX+0x80]
	RETN
continue_mouseNewPageLDown:
	ADD DWORD PTR SS:[ESP],0x149
	RETN
end_mouseNewPageLDown:
	ADD ESP,4
	POP EDI
	POP ESI
	POP EBP
	POP EBX
	RETN 4
}}

FCT_ASM ( caller_mouseCustomPageLeftUp_9 )
	PUSH EBP
	CALL mouseCustomPageLeftUp
	TEST EAX,EAX
	JE end_mouseNewPageLUp
	JG continue_mouseNewPageLUp
	MOV EAX,DWORD PTR DS:[ptWindowStartX]
	MOV EAX,DWORD PTR DS:[EAX]
	RETN
continue_mouseNewPageLUp:
	ADD DWORD PTR SS:[ESP],0x16A
	RETN
end_mouseNewPageLUp:
	ADD ESP,4
	POP EDI
	POP ESI
	POP EBP
	POP EBX
	POP ECX
	RETN 4
}}

FCT_ASM ( caller_resetSelectedPage )
	TEST EAX,EAX
	SETE DL
	JNZ END_resetSelectedPage
	CMP ESI,2
	JNZ END_resetSelectedPage
	MOV selectedPage,0
END_resetSelectedPage:
	RETN
}}

void Install_NewInterfaces()
{
	static int isInstalled = false;
	if (isInstalled) return;

	Install_UpdateServer();
	Install_PlugYImagesFiles();
	Install_PlugYTxtFiles();
	Install_InterfaceStats();

	log_msg("[Patch] D2Client for new custom page interface. (NewInterfaces)\n");

	if (selectMainPageOnOpening)
	{
		// Reset selectedPage variable on opening stats page
		mem_seek(D2Client::GetOffsetByAddition(0x88B58));
		memt_byte(0x85, 0xE8);
		MEMT_REF4(0xC2940FC0, caller_resetSelectedPage);	
	}

	// Print custom page
	mem_seek(D2Client::GetOffsetByAddition(0x87697));
	MEMC_REF4(D2Client::D2PrintStatsPage, printCustomPage);

	// Don't print Border
	mem_seek(D2Client::GetOffsetByAddition(0x58EF6));
	memt_byte(0xB9, 0xE8);
	MEMT_REF4(0x00000012, caller_DontPrintBorder);

	// Manage mouse down (Play sound)
	mem_seek(D2Client::GetOffsetByAddition(0x2A9DC));
	memt_byte(0x8D, 0xE8);
	MEMT_REF4(0x00008088, caller_mouseCustomPageLeftDown_9);
	memt_byte(0, 0x90);

	// Manage mouse up
	mem_seek(D2Client::GetOffsetByAddition(0x2ABBB));
	memt_byte(0xA1, 0xE8);
	MEMT_REF4(ptWindowStartX, caller_mouseCustomPageLeftUp_9);

	log_msg("\n");

	isInstalled = true;
}