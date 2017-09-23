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
#include "plugYFiles.h"
#include "newInterfaces.h"
#include "common.h"
#include <stdio.h>

#define	getXCloseBtn()			RX(0x110)
#define	getLCloseBtn()			32
#define	getYCloseBtn()			RY(0x40)
#define	getHCloseBtn()			32
#define isOnCloseBtn(x,y) isOnRect(x, y, getXCloseBtn(), getYCloseBtn(), getLCloseBtn(), getHCloseBtn())

#define	getXPreviousPageBtn()		RX(D2GetResolution()?0x19:0x77)//0x70
#define	getLPreviousPageBtn()		32
#define	getYPreviousPageBtn()		RY(0x40)
#define	getHPreviousPageBtn()		32
#define isOnPreviousPageBtn(x,y)	isOnRect(x, y, getXPreviousPageBtn(), getYPreviousPageBtn(), getLPreviousPageBtn(), getHPreviousPageBtn())

#define	getXNextPageBtn()		RX(D2GetResolution()?0x43:0xA1)//0x70
#define	getLNextPageBtn()		32
#define	getYNextPageBtn()		RY(0x40)
#define	getHNextPageBtn()		32
#define isOnNextPageBtn(x,y)	isOnRect(x, y, getXNextPageBtn(), getYNextPageBtn(), getLNextPageBtn(), getHNextPageBtn())


#define BUFSIZE 0x80

static struct
{
	union{
		DWORD all;
		struct{
			DWORD close:1;
			DWORD previousPage:1;
			DWORD nextPage:1;
		};
	};
} isDownBtn;


struct statsInterfaceBIN
{
	WORD enabled;
	WORD page;
	WORD x;
	WORD y;
	WORD color;
	WORD font;
	WORD statsID;
};

extern int lastPage;
int nbStatsInterface;
statsInterfaceBIN* statsInterface;

void loadStatsInterfaceDesc(DWORD mempool)
{
	log_msg("loadStatsInterfaceDesc(%d)\n",mempool);

	CREATE_TABLE_DESCRIPTION(8);
	ADD_WORD_FIELD(0,	"enabled");
	ADD_WORD_FIELD(2,	"page");
	ADD_WORD_FIELD(4,	"x");
	ADD_WORD_FIELD(6,	"y");
	ADD_WORD_FIELD(8,	"color");
	ADD_WORD_FIELD(10,	"font");
//	ADD_LOOKUP_WORD(10,	"stat", lookupItemStatCost);
	ADD_WORD_FIELD(12,	"statID");
	ADD_TERM_FIELD();

	const char* statsInterfaceFileName = "statsinterface.txt";
	char filePath[MAX_PATH];
	sprintf(filePath, "%s\\%s", modDataDirectory, statsInterfaceFileName);

	BUILD_BIN(statsInterfaceBIN, statsInterface, nbStatsInterface, filePath);

	lastPage = 0;
	for (i=0; i<nbStatsInterface; i++)
		if (statsInterface[i].page > lastPage)
			lastPage = statsInterface[i].page;
}

void freeStatsInterfaceDesc()
{
	log_msg("freeStatsInterfaceDesc()\n");

	if (statsInterface)
	{
		D2FogMemDeAlloc(statsInterface,__FILE__,__LINE__,0);
		statsInterface = NULL;
		nbStatsInterface = 0;
	}
}

void printStat(Unit* ptChar, DWORD statID, DWORD x, DWORD y, DWORD color, LPWSTR lpText)
{
	LPWSTR text;
	log_msg("printStat : %d\n", statID);
	switch (statID)
	{
	case STATS_FIRERESIST:
	case STATS_COLDRESIST:
	case STATS_LIGHTRESIST:
	case STATS_POISONRESIST:
		text = D2GetStringFromIndex(D2Client::GetDescStrPos(statID));
		if (wcslen(text) > 50) return;
		swprintf(lpText, L"%s +%i%%", text, D2GetPlayerStat(ptChar,statID,0));
		break;
	default:
		D2PrintStat(ptChar, NULL, statID, 0, D2GetPlayerStat(ptChar, statID, 0), lpText);//param2=ptChar->ptStats->ptItemStats
	}
	D2PrintString(lpText, x, y, color, 0);
}

void manageStatLine(Unit* ptChar, statsInterfaceBIN* statLine, int currentPage, LPWSTR lpText)
{
	if (!statLine->enabled)
		return;

	if (statLine->page != currentPage)
		return;

	if (statLine->font)
		D2SetFont(statLine->font);

	printStat(ptChar, statLine->statsID, RX(statLine->x), RY(statLine->y), statLine->color, lpText);
}

void __stdcall printNewStatsPageTwo(int currentPage)
{
	if (!D2isLODGame()) return D2PrintStatsPage();

	WCHAR text[BUFSIZE];
	LPWSTR lpText;
	bDontPrintBorder = false;

	Unit* ptChar = D2GetClientPlayer();

	d2_assert(!ptChar, "Printing stats page : no character selected",__FILE__,__LINE__);
	d2_assert(ptChar->nUnitType != UNIT_PLAYER, "Printing stats page : bad unit type",__FILE__,__LINE__);

	//Init data for print image
	sDrawImageInfo data;
	ZeroMemory(&data,sizeof(data));

	//print background
	fillRect(RX(0),RY(480),320,432,0,5);//552
	setImage(&data, newStatsInterfaceImages);
	setFrame(&data, 0);
	D2PrintImage(&data, RX(0),	RY(224), -1, 5, 0);
	setFrame(&data, 1);
	D2PrintImage(&data, RX(256),RY(224), -1, 5, 0);//256
	setFrame(&data, 2);
	D2PrintImage(&data, RX(0),	RY(48), -1, 5, 0);//432
	setFrame(&data, 3);
	D2PrintImage(&data, RX(256),RY(48), -1, 5, 0);

	D2SetFont(1);
	for (int i=0; i<nbStatsInterface; i++)
		manageStatLine(ptChar, &statsInterface[i], currentPage, text);

	//print background previous/next page buttons
	setImage(&data, statsBackgroundImages);
	setFrame(&data, D2GetResolution()?1:0);
	D2PrintImage(&data, getXPreviousPageBtn()-7, getYPreviousPageBtn()+8, -1, 5, 0);

	//print button close
	setImage(&data, D2LoadBuySelBtn());
	setFrame(&data, 10 + isDownBtn.close);
	D2PrintImage(&data, getXCloseBtn(), getYCloseBtn(), -1, 5, 0);
	
	//print previous page button
	setFrame(&data, 12 + isDownBtn.previousPage);
	D2PrintImage(&data, getXPreviousPageBtn(), getYPreviousPageBtn(), -1, 5, 0);

	//print next page button
	setFrame(&data, 14 + isDownBtn.nextPage);
	D2PrintImage(&data, getXNextPageBtn(), getYNextPageBtn(), -1, 5, 0);

//////////////////// POPUP PRINTING ////////////////////
	//set MouseX & MouseY
	DWORD mx = D2GetMouseX();
	DWORD my = D2GetMouseY();
	
	D2SetFont(1);

	if (isOnCloseBtn(mx,my))			// print popup "close"
	{
		D2PrintPopup(D2GetStringFromIndex(0x1030), getXCloseBtn()+getLCloseBtn()/2, getYCloseBtn()-getHCloseBtn(), WHITE, 1);
	}
	else if (isOnPreviousPageBtn(mx,my))	//print popup "previous page"
	{
		lpText = getLocalString(STR_PREVIOUS_PAGE);
		D2PrintPopup(lpText, getXPreviousPageBtn()+getLPreviousPageBtn()/2, getYPreviousPageBtn()-getHPreviousPageBtn(), WHITE, 1);
	}
	else if (isOnNextPageBtn(mx,my))	//print popup "next page"
	{
		lpText = getLocalString(STR_NEXT_PAGE);
		D2PrintPopup(lpText, getXNextPageBtn()+getLNextPageBtn()/2, getYNextPageBtn()-getHNextPageBtn(), WHITE, 1);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////

DWORD __stdcall mouseNewStatsPageTwoLeftDown(sWinMessage* msg)
{
	if (!D2isLODGame()) return -1;

	DWORD x = D2GetMouseX();
	DWORD y = D2GetMouseY();
	if (!isOnStatsPage(x,y)) return 1;

	if (isOnCloseBtn(x,y))
	{
		log_msg("push down left button close\n");
		isDownBtn.close = 1;
		D2PlaySound(4,0,0,0,0);
	}
	else if (isOnPreviousPageBtn(x,y))
	{
		log_msg("push down left button previous page\n");
		isDownBtn.previousPage = 1;
		D2PlaySound(4,0,0,0,0);
	}
	else if (isOnNextPageBtn(x,y))
	{
		log_msg("push down left button next page\n");
		isDownBtn.nextPage = 1;
		D2PlaySound(4,0,0,0,0);
	}

	freeMessage(msg);
	return 0;
}


DWORD __stdcall mouseNewStatsPageTwoLeftUp(sWinMessage* msg)
{
	if (!D2isLODGame()) return -1;

	DWORD x = D2GetMouseX();
	DWORD y = D2GetMouseY();
	if (!isOnStatsPage(x,y)) return 1;

	if (isOnCloseBtn(x,y))
	{
		log_msg("push up left button close\n");
		if (isDownBtn.close)
			D2TogglePage(2,1,0);
	}
	else if (isOnPreviousPageBtn(x,y))
	{
		log_msg("push up left button previous page\n");
		if (isDownBtn.previousPage)
			GoPreviousStatPage();
	}
	else if (isOnNextPageBtn(x,y))
	{
		log_msg("push up left button next page\n");
		if (isDownBtn.nextPage)
			GoNextStatPage();
	}
	D2CleanStatMouseUp();
	freeMessage(msg);
	isDownBtn.all=0;
	return 0;
}