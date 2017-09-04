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

#include "statsPoints.h"
#include "plugYFiles.h"		// Install_PlugYImagesFiles()
#include "newInterfaces.h"
#include "common.h"
#include <stdio.h>

static struct
{
	union{
		DWORD all;
		struct{
			DWORD previousPage:1;
			DWORD nextPage:1;
		};
	};
} isDownBtn;

#define	getXPreviousPageBtn()		RX(0x19)//0x70
#define	getLPreviousPageBtn()		32
#define	getYPreviousPageBtn()		RY(0x40)
#define	getHPreviousPageBtn()		32
#define isOnPreviousPageBtn(x,y)	isOnRect(x, y, getXPreviousPageBtn(), getYPreviousPageBtn(), getLPreviousPageBtn(), getHPreviousPageBtn())

#define	getXNextPageBtn()		RX(D2GetResolution()?0x43:0x8A)
#define	getLNextPageBtn()		32
#define	getYNextPageBtn()		RY(D2GetResolution()?0x40:0x70)
#define	getHNextPageBtn()		32
#define isOnNextPageBtn(x,y)	isOnRect(x, y, getXNextPageBtn(), getYNextPageBtn(), getLNextPageBtn(), getHNextPageBtn())

void STDCALL printStatsPageBtns()
{
	if (!active_newInterfaces || !D2isLODGame() ) return;

	LPWSTR lpText;
	DWORD mx = D2GetMouseX();
	DWORD my = D2GetMouseY();

	sDrawImageInfo data;
	ZeroMemory(&data,sizeof(data));

	if (printBackgroundOnMainPage && D2GetResolution())
	{
		setImage(&data, statsBackgroundImages);
		setFrame(&data, 1);
		D2PrintImage(&data, getXPreviousPageBtn()-7, getYPreviousPageBtn()+8, -1, 5, 0);
	}

	setImage(&data, D2LoadBuySelBtn());
	if (D2GetResolution())
	{
		setFrame(&data, 12 + isDownBtn.previousPage);
		D2PrintImage(&data, getXPreviousPageBtn(), getYPreviousPageBtn(), -1, 5, 0);
	}
	setFrame(&data, 14 + isDownBtn.nextPage);
	D2PrintImage(&data, getXNextPageBtn(), getYNextPageBtn(), -1, 5, 0);

	D2SetFont(1);
	if (D2GetResolution() && isOnPreviousPageBtn(mx,my))	//print popup "previous page"
	{
		lpText = getLocalString(STR_PREVIOUS_PAGE);
		D2PrintPopup(lpText, getXPreviousPageBtn()+getLPreviousPageBtn()/2, getYPreviousPageBtn()-getHPreviousPageBtn(), WHITE, 1);
	}
	else if ( isOnNextPageBtn(mx,my))
	{
		lpText = getLocalString(STR_NEXT_PAGE);
		D2PrintPopup(lpText, getXNextPageBtn()+getLNextPageBtn()/2, getYNextPageBtn()-getHNextPageBtn(), WHITE, 1);
	}
}

Unit* STDCALL statsPageMouseDown(sWinMessage* msg)
{
	Unit* ptChar = D2GetClientPlayer();

	if (!active_newInterfaces || !D2isLODGame() ) return ptChar;

	if (D2GetResolution() && isOnPreviousPageBtn(msg->x,msg->y))
	{
		log_msg("push down left button previous page\n");
		isDownBtn.previousPage = 1;
		D2PlaySound(4,0,0,0,0);
		freeMessage(msg);
		return NULL;
	}
	else if (isOnNextPageBtn(msg->x,msg->y))
	{
		log_msg("push down left button next page\n");
		isDownBtn.nextPage = 1;
		D2PlaySound(4,0,0,0,0);
		freeMessage(msg);
		return NULL;
	}
	return ptChar;
}


Unit* STDCALL statsPageMouseUp(sWinMessage* msg)
{
	Unit* ptChar = D2GetClientPlayer();

	if (!active_newInterfaces || !D2isLODGame() ) return ptChar;

	if (D2GetResolution() && isOnPreviousPageBtn(msg->x,msg->y))
	{
		log_msg("push up left button previous page\n");
		if (isDownBtn.previousPage)
		{
			GoPreviousStatPage();
			log_msg("previous page press\n");
			isDownBtn.all=0;
			freeMessage(msg);
			return NULL;
		}
	}
	else if (isOnNextPageBtn(msg->x,msg->y))
	{
		log_msg("push up left button next page\n");
		if (isDownBtn.nextPage)
		{
			GoNextStatPage();
			log_msg("next page press\n");
			isDownBtn.all=0;
			freeMessage(msg);
			return NULL;
		}
	}

	isDownBtn.all=0;
	return ptChar;
}

FCT_ASM ( caller_printStatsPageBtns_111 )
	CALL printStatsPageBtns
	POP EDI
	POP ESI
	POP EBP
	POP EBX
	ADD ESP,0x370
	RETN
}}


FCT_ASM ( caller_printStatsPageBtns )
	CALL printStatsPageBtns
	POP EDI
	POP ESI
	POP EBP
	POP EBX
	ADD ESP,0x3B0
	RETN
}}

FCT_ASM ( caller_printStatsPageBtns_9 )
	CALL printStatsPageBtns
	POP EDI
	POP ESI
	POP EBP
	POP EBX
	ADD ESP,0x374
	RETN
}}



FCT_ASM ( caller_statsPageMouseDown_111 )
	PUSH DWORD PTR SS:[ESP+0x20]
	CALL statsPageMouseDown
	TEST EAX,EAX
	JE fin_statsPageMouseDown
	RETN
fin_statsPageMouseDown:
	ADD ESP,4
	POP EDI
	POP ESI
	POP EBP
	POP EBX
	RETN 4
}}

FCT_ASM ( caller_statsPageMouseDown )
	PUSH DWORD PTR SS:[ESP+0x18]
	CALL statsPageMouseDown
	TEST EAX,EAX
	JE fin_statsPageMouseDown
	RETN
fin_statsPageMouseDown:
	ADD ESP,4
	POP EDI
	POP ESI
	POP EBP
	POP EBX
	RETN 4
}}

FCT_ASM ( caller_statsPageMouseUp )
	PUSH EBP
	CALL statsPageMouseUp
	TEST EAX,EAX
	JE fin_statsPageMouseUp
	RETN
fin_statsPageMouseUp:
	ADD ESP,4
	POP EDI
	POP ESI
	POP EBP
	POP EBX
	ADD ESP,8
	RETN 4
}}

FCT_ASM ( caller_statsPageMouseUp_9 )
	PUSH EBP
	CALL statsPageMouseUp
	TEST EAX,EAX
	JE fin_statsPageMouseUp
	RETN
fin_statsPageMouseUp:
	ADD ESP,4
	POP EDI
	POP ESI
	POP EBP
	POP EBX
	POP ECX
	RETN 4
}}

// [Patch]
void Install_InterfaceStats()
{
	static int isInstalled = false;
	if (isInstalled) return;
	
	Install_PlugYImagesFiles();

	log_msg("Patch D2Client for stats interface. (InterfaceStats)\n");

	// Print new buttons images
	mem_seek(D2Client->GetOffsetByAddition(0x2A7BE, 0x2A7AE, 0x30F86, 0x83636, 0x8A0B6, 0x6C016, 0xBDC16, 0xC03B6));
	memt_byte(0x5F, 0xE9);
	MEMT_REF4(0x815B5D5E, Game->Version >= VersionUtility::Versions::V111 ? caller_printStatsPageBtns_111: Game->Version == VersionUtility::Versions::V110 ? caller_printStatsPageBtns : caller_printStatsPageBtns_9);

	if ( Game->Version >= VersionUtility::Versions::V111 )
	{
		// Manage mouse down (Play sound)
		mem_seek(D2Client->GetOffsetByAddition(0x2AA6D, 0x2AA5D, 0x3133D, 0x827C8, 0x89248, 0x6B1A8, 0xBCDC8, 0xBF568));
		memt_byte(0xA1, 0xE8);
		MEMT_REF4(D2Client->ptptClientChar, caller_statsPageMouseDown);

		// Manage mouse up
		mem_seek(D2Client->GetOffsetByAddition(0x2AC43, 0x2AC33, 0x3151A, 0x83853, 0x8A2D3, 0x6C233, 0xBDE33, 0xC05D3));
		memt_byte(0xA1, 0xE8);
		MEMT_REF4(D2Client->ptptClientChar, caller_statsPageMouseUp);
	}
	else
	{
		// Manage mouse down (Play sound)
		mem_seek(D2Client->GetOffsetByAddition(0x2AA6D, 0x2AA5D, 0x3133D, 0x827C8, 0x89248, 0x6B1A8, 0, 0));
		MEMC_REF4(D2Client->D2GetClientPlayer, caller_statsPageMouseDown);

		// Manage mouse up
		mem_seek(D2Client->GetOffsetByAddition(0x2AC43, 0x2AC33, 0x3151A, 0x83853, 0x8A2D3, 0x6C233, 0, 0));
		MEMC_REF4(D2Client->D2GetClientPlayer, Game->Version == VersionUtility::Versions::V110 ? caller_statsPageMouseUp : caller_statsPageMouseUp_9);
	}

	log_msg("\n");

	isInstalled = true;
}

