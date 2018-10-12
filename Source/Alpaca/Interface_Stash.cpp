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

#include "interface_Stash.h"
#include "updateServer.h"
#include "infinityStash.h"
#include "plugYFiles.h"	
#include "common.h"
#include <stdio.h>

static struct
{
	union{
		DWORD all;
		struct{
			DWORD previous:1;
			DWORD next:1;
			DWORD toggleToSharedStash:1;
			DWORD previousIndex:1;
			DWORD nextIndex:1;
			DWORD putGold:1;
			DWORD takeGold:1;
		};
	};
} isDownBtn;

bool displaySharedSetItemNameInGreen = true;
int posXPreviousBtn=-1;
int posYPreviousBtn=-1;
int posXNextBtn=-1;
int posYNextBtn=-1;
int posXSharedBtn=-1;
int posYSharedBtn=-1;
int posXPreviousIndexBtn=-1;
int posYPreviousIndexBtn=-1;
int posXNextIndexBtn=-1;
int posYNextIndexBtn=-1;
int posXPutGoldBtn=-1;
int posYPutGoldBtn=-1;
int posXTakeGoldBtn=-1;
int posYTakeGoldBtn=-1;

DWORD	getXPreviousBtn()		{return RX(posXPreviousBtn<0? D2GetResolution()?0x80:0xAF : posXPreviousBtn);}
#define	getLPreviousBtn()		32
DWORD	getYPreviousBtn()		{return RY(posYPreviousBtn<0 ? 0x40 : posYPreviousBtn);}
#define	getHPreviousBtn()		32

DWORD	getXNextBtn()			{return RX(posXNextBtn<0 ? D2GetResolution()?0xA0:0xCF :posXNextBtn);}
#define	getLNextBtn()			32
DWORD	getYNextBtn()			{return RY(posYNextBtn<0 ? 0x40 : posYNextBtn);}
#define	getHNextBtn()			32

DWORD	getXSharedBtn()			{return RX(posXSharedBtn<0 ? D2GetResolution()?0x10:0x6F :posXSharedBtn);}
#define	getLSharedBtn()			32
DWORD	getYSharedBtn()			{return RY(posYSharedBtn<0 ? 0x40 : posYSharedBtn);}
#define	getHSharedBtn()			32

DWORD	getXPreviousIndexBtn()	{return RX(posXPreviousIndexBtn<0 ?  D2GetResolution()?0x60:0x8F :posXPreviousIndexBtn);}
#define	getLPreviousIndexBtn()	32
DWORD	getYPreviousIndexBtn()	{return RY(posYPreviousIndexBtn<0 ? 0x40 : posYPreviousIndexBtn);}
#define	getHPreviousIndexBtn()	32

DWORD	getXNextIndexBtn()		{return RX(posXNextIndexBtn<0? D2GetResolution()?0xC0:0xEF : posXNextIndexBtn);}
#define	getLNextIndexBtn()		32
DWORD	getYNextIndexBtn()		{return RY(posYNextIndexBtn<0 ? 0x40 : posYNextIndexBtn);}
#define	getHNextIndexBtn()		32

DWORD	getXPutGoldBtn()		{return RX(posXPutGoldBtn<0? 0x1C : posXPutGoldBtn);}
#define	getLPutGoldBtn()		32
DWORD	getYPutGoldBtn()		{return RY(posYPutGoldBtn<0 ? 0x1A8 : posYPutGoldBtn);}
#define	getHPutGoldBtn()		32

DWORD	getXTakeGoldBtn()		{return RX(posXTakeGoldBtn<0? 0x105 : posXTakeGoldBtn);}
#define	getLTakeGoldBtn()		32
DWORD	getYTakeGoldBtn()		{return RY(posYTakeGoldBtn<0 ? 0x1A8 : posYTakeGoldBtn);}
#define	getHTakeGoldBtn()		32

#define isOnButtonNextStash(x,y) isOnRect(x, y, getXNextBtn(), getYNextBtn(), getLNextBtn(), getHNextBtn())
#define isOnButtonPreviousStash(x,y) isOnRect(x, y, getXPreviousBtn(), getYPreviousBtn(), getLPreviousBtn(), getHPreviousBtn())
#define isOnButtonToggleSharedStash(x,y) isOnRect(x, y, getXSharedBtn(), getYSharedBtn(), getLSharedBtn(), getHSharedBtn())
#define isOnButtonNextIndexStash(x,y) isOnRect(x, y, getXNextIndexBtn(), getYNextIndexBtn(), getLNextIndexBtn(), getHNextIndexBtn())
#define isOnButtonPreviousIndexStash(x,y) isOnRect(x, y, getXPreviousIndexBtn(), getYPreviousIndexBtn(), getLPreviousIndexBtn(), getHPreviousIndexBtn())
#define isOnButtonPutGold(x,y) isOnRect(x, y, getXPutGoldBtn(), getYPutGoldBtn(), getLPutGoldBtn(), getHPutGoldBtn())
#define isOnButtonTakeGold(x,y) isOnRect(x, y, getXTakeGoldBtn(), getYTakeGoldBtn(), getLTakeGoldBtn(), getHTakeGoldBtn())

void* __stdcall printBtns()
{
	if (!D2isLODGame()) return D2LoadBuySelBtn();

	Unit* ptChar = D2GetClientPlayer();

	sDrawImageInfo data;
	ZeroMemory(&data,sizeof(data));
	setImage(&data, stashBtnsImages);

	setFrame(&data, 0 + isDownBtn.previous);
	D2PrintImage(&data, getXPreviousBtn(), getYPreviousBtn(), -1, 5, 0);

	setFrame(&data, 2 + isDownBtn.next);
	D2PrintImage(&data, getXNextBtn(), getYNextBtn(), -1, 5, 0);

	if (active_sharedStash)
	{
		setFrame(&data, 4 + isDownBtn.toggleToSharedStash + (PCPY->showSharedStash?2:0) );
		D2PrintImage(&data, getXSharedBtn(), getYSharedBtn(), -1, 5, 0);
	}

	setFrame(&data, 8 + isDownBtn.previousIndex);
	D2PrintImage(&data, getXPreviousIndexBtn(), getYPreviousIndexBtn(), -1, 5, 0);

	setFrame(&data, 10 + isDownBtn.nextIndex);
	D2PrintImage(&data, getXNextIndexBtn(), getYNextIndexBtn(), -1, 5, 0);

	if (active_sharedGold)
	{
		setImage(&data, sharedGoldBtnsImages);
		setFrame(&data, 0 + isDownBtn.putGold);
		D2PrintImage(&data, getXPutGoldBtn(), getYPutGoldBtn(), -1, 5, 0);

		setFrame(&data, 2 + isDownBtn.takeGold);
		D2PrintImage(&data, getXTakeGoldBtn(), getYTakeGoldBtn(), -1, 5, 0);
	}

	LPWSTR lpText;
	WCHAR text[100];
	DWORD mx = D2GetMouseX();
	DWORD my = D2GetMouseY();

	D2SetFont(1);

	if (isOnButtonPreviousStash(mx,my))
	{
		lpText = getLocalString(STR_STASH_PREVIOUS_PAGE);
		D2PrintPopup(lpText, getXPreviousBtn()+getLPreviousBtn()/2, getYPreviousBtn()-getHPreviousBtn(), WHITE, 1);
	}
	else if (isOnButtonNextStash(mx,my))
	{
		lpText = getLocalString(STR_STASH_NEXT_PAGE);
		D2PrintPopup(lpText, getXNextBtn()+getLNextBtn()/2, getYNextBtn()-getHNextBtn(), WHITE, 1);
	} 
	else if (active_sharedStash && isOnButtonToggleSharedStash(mx,my))
	{
		lpText = getLocalString(PCPY->showSharedStash ? STR_TOGGLE_TO_PERSONAL : STR_TOGGLE_TO_SHARED);
		D2PrintPopup(lpText, getXSharedBtn()+getLSharedBtn()/2, getYSharedBtn()-getHSharedBtn(), WHITE, 1);
	}
	else if (!active_sharedStash && isOnButtonToggleSharedStash(mx, my))
	{
		LPWSTR disabledStash = L"The shared stash is disabled";
		lpText = disabledStash;
		D2PrintPopup(lpText, getXSharedBtn() + getLSharedBtn() / 2, getYSharedBtn() - getHSharedBtn(), WHITE, 1);
	}
	else if (isOnButtonPreviousIndexStash(mx,my))
	{
		_snwprintf(text, sizeof(text), getLocalString(STR_STASH_PREVIOUS_INDEX) ,nbPagesPerIndex,nbPagesPerIndex2);
		D2PrintPopup(text, getXPreviousIndexBtn()+getLPreviousIndexBtn()/2, getYPreviousIndexBtn()-getHPreviousIndexBtn(), 0, 0);
	} 
	else if (isOnButtonNextIndexStash(mx,my))
	{
		_snwprintf(text, sizeof(text), getLocalString(STR_STASH_NEXT_INDEX) ,nbPagesPerIndex,nbPagesPerIndex2);
		D2PrintPopup(text, getXNextIndexBtn()+getLNextIndexBtn()/2, getYNextIndexBtn()-getHNextIndexBtn(), WHITE, 1);
	} 
	else if (active_sharedGold && isOnButtonPutGold(mx,my))
	{
		lpText = getLocalString(STR_PUT_GOLD);
		D2PrintPopup(lpText, getXPutGoldBtn()+getLPutGoldBtn()/2, getYPutGoldBtn()-getHPutGoldBtn(), WHITE, 1);
	} 
	else if (active_sharedGold && isOnButtonTakeGold(mx,my))
	{
		lpText = getLocalString(STR_TAKE_GOLD);
		D2PrintPopup(lpText, getXTakeGoldBtn()+getLTakeGoldBtn()/2, getYTakeGoldBtn()-getHTakeGoldBtn(), WHITE, 1);
	}

	return D2LoadBuySelBtn();
}


DWORD __stdcall manageBtnDown(sWinMessage* msg)
{
	if (!D2isLODGame()) return 0;

	if (isOnButtonPreviousStash(msg->x,msg->y))
		isDownBtn.previous = 1;
	else if (isOnButtonNextStash(msg->x,msg->y))
		isDownBtn.next = 1;
	else if (active_sharedStash && isOnButtonToggleSharedStash(msg->x,msg->y))
		isDownBtn.toggleToSharedStash = 1;
	else if (isOnButtonPreviousIndexStash(msg->x,msg->y))
		isDownBtn.previousIndex = 1;
	else if (isOnButtonNextIndexStash(msg->x,msg->y))
		isDownBtn.nextIndex = 1;
	else if (active_sharedGold && isOnButtonPutGold(msg->x,msg->y))
		isDownBtn.putGold = 1;
	else if (active_sharedGold && isOnButtonTakeGold(msg->x,msg->y))
		isDownBtn.takeGold = 1;
	else return 0;

	D2PlaySound(4,0,0,0,0);
	freeMessage(msg);
	return 1;
}

	
DWORD __stdcall manageBtnUp(sWinMessage* msg)
{
	if (!D2isLODGame()) return 0;

	Unit* ptChar = D2GetClientPlayer();

	if (isOnButtonPreviousStash(msg->x,msg->y))
	{
		log_msg("push up left button previous\n");
		if (isDownBtn.previous)
			if (GetKeyState(VK_SHIFT)<0)
				updateServer(US_SELECT_PREVIOUS2);
			else
				updateServer(US_SELECT_PREVIOUS);
	}
	else if (isOnButtonNextStash(msg->x,msg->y))
	{
		log_msg("push up left button next\n");
		if (isDownBtn.next)
			if (GetKeyState(VK_SHIFT)<0)
				updateServer(US_SELECT_NEXT2);
			else
				updateServer(US_SELECT_NEXT);
	}
	else if (active_sharedStash && isOnButtonToggleSharedStash(msg->x,msg->y))
	{
		log_msg("push up left button shared\n");
		if (isDownBtn.toggleToSharedStash)
			if (PCPY->showSharedStash)
				updateServer(US_SELECT_SELF);
			 else
				updateServer(US_SELECT_SHARED);
	}
	else if (!active_sharedStash && isOnButtonToggleSharedStash(msg->x, msg->y))
	{
		log_msg("push up left button shared but shared stash is disabled.\n");
	}
	else if (isOnButtonPreviousIndexStash(msg->x,msg->y))
	{
		log_msg("select left button previous index\n");
		if (isDownBtn.previousIndex)
			if (GetKeyState(VK_SHIFT)<0)
				updateServer(US_SELECT_PREVIOUS_INDEX2);
			else
				updateServer(US_SELECT_PREVIOUS_INDEX);
	}
	else if (isOnButtonNextIndexStash(msg->x,msg->y))
	{
		log_msg("push up left button next index\n");
		if (isDownBtn.nextIndex)
			if (GetKeyState(VK_SHIFT)<0)
				updateServer(US_SELECT_NEXT_INDEX2);
			else
				updateServer(US_SELECT_NEXT_INDEX);
	}
	else if (active_sharedGold && isOnButtonPutGold(msg->x,msg->y))
	{
		log_msg("push up left put gold\n");
		if (isDownBtn.putGold)
			updateServer(US_PUTGOLD);
	}
	else if (active_sharedGold && isOnButtonTakeGold(msg->x,msg->y))
	{
		log_msg("push up left take gold\n");
		if (isDownBtn.takeGold)
			updateServer(US_TAKEGOLD);
	}
	else
	{
		return 0;
	}

	return 1;
}

void __fastcall printPageNumber(LPWSTR maxGoldText, DWORD x, DWORD y, DWORD color, DWORD bfalse)
{
	if (!D2isLODGame() )
	{
		D2PrintString(maxGoldText,x,y,color,bfalse);
		return;
	}

	Unit* ptChar = D2GetClientPlayer();
	WCHAR popupText[100];

	if (PCPY->currentStash)
	{
		bool isShared = PCPY->currentStash->isShared;
		bool isIndex = PCPY->currentStash->isIndex;
		DWORD currentId = PCPY->currentStash->id;

		// Display the appropriate stash name (If custom display that, if not display
		// the default stash name for the appropriate language, retrieved from the
		// LocalizedStrings file.
		if (PCPY->currentStash->name && PCPY->currentStash->name[0])
		{
			const int BUFFER_MAX = 50;

			// Convert the custom page number to a string and concat
			// it at the end of the custom name. This code is ugly,
			// there should be a more efficient/safer C way of doing this.
			char pageAsString[BUFFER_MAX];
			char customNameWithPage[100];

			// Convert the integer to a string
			sprintf(pageAsString, "%d", currentId + 1);

			// Concat page number to the end of the custom stash name
			strcpy(customNameWithPage, PCPY->currentStash->name);
			strcat(customNameWithPage, " [");
			strcat(customNameWithPage, pageAsString);
			strcat(customNameWithPage, "]");

			// Display the custom page name with the page number
			mbstowcs(popupText, customNameWithPage, BUFFER_MAX);
		}
		else
		{
			_snwprintf(popupText, sizeof(popupText), getLocalString(isShared ? STR_SHARED_PAGE_NUMBER : STR_PERSONAL_PAGE_NUMBER), currentId + 1);
		}

		int stashNameColor = isShared ? (isIndex ? GREEN : RED) : (isIndex ? GREEN : WHITE);
		D2PrintString(popupText, x, y, stashNameColor, bfalse);
	} else {
		_snwprintf(popupText, sizeof(popupText), getLocalString(STR_NO_SELECTED_PAGE));
		D2PrintString(popupText, x, y, WHITE, bfalse);
	}

	//printGoldMaxPopup
	DWORD mx = D2GetMouseX();
	DWORD my = D2GetMouseY();
	if ((RX(0x5E) < mx) && (mx < RX(0xF8)) && (RY(0x1C8) < my) && (my < RY(0x1B6)) )
	{
		if (active_sharedGold)
		{
			_snwprintf(popupText, sizeof(popupText), L"%s\n%s: %u", maxGoldText, getLocalString(STR_SHARED_GOLD_QUANTITY), PCPY->sharedGold);
			DWORD x = D2GetPixelLen(maxGoldText);
			DWORD x2 = D2GetPixelLen(popupText) - x;
			D2PrintPopup(popupText, RX(0xA8-max(x,x2)/2), RY(0x1CA), WHITE, 0);
		} else 
			D2PrintPopup(maxGoldText, RX(0xA8), RY(0x1CA), WHITE, 1);
	}
}


static Stash* curStash=NULL;
static DWORD currentSawStash=0;
Unit* __stdcall getNextItemForSet(Unit* ptItem)
{
	Unit* item = ptItem?D2UnitGetNextItem(ptItem):NULL;
	if (item) return item;

	if (!curStash)
	{
		Unit* ptChar = D2GetClientPlayer();
		switch (currentSawStash)
		{
		case 0:
			curStash = PCPY->selfStash;
			currentSawStash = displaySharedSetItemNameInGreen ? 1 : 2;
			break;
		case 1:
			curStash = PCPY->sharedStash;
			currentSawStash = 2;
			break;
		default:
			return NULL;
		}
	}
	else
	{
		curStash = curStash->nextStash;
	}
	if (curStash)
	{
		item = curStash->ptListItem;
		if (item) return item;
	}
	return getNextItemForSet(item);
}

Unit* __stdcall initGetNextItemForSet(Inventory* ptInventory)
{
	Unit* ptChar = D2GetClientPlayer();
	if (ptChar->nUnitType != UNIT_PLAYER) return NULL;
	if (!PCPY) return NULL;

	curStash = NULL;
	currentSawStash = 0;
	Unit* item = D2InventoryGetFirstItem(ptInventory);
	if (item) return item;
	return getNextItemForSet(item);
}

FCT_ASM( caller_manageBtnDown )
	PUSH EDI
	CALL manageBtnDown
	TEST EAX,EAX
	JE IS_NOT_ON_BUTTON
	POP EDX
	MOV EDX, DWORD PTR DS:[EDX+0xF3]
	MOV DWORD PTR DS:[EDX],1
	POP EDI
	POP ESI
	POP EBP
	POP EBX
	RETN 4
IS_NOT_ON_BUTTON:
	JMP D2isLODGame
}}

FCT_ASM( caller_manageBtnUp )
	PUSH EBP
	CALL manageBtnUp
	MOV isDownBtn.all,0
	TEST EAX,EAX
	JE IS_NOT_ON_BUTTON
	POP EDX
	MOV EDX, DWORD PTR DS:[EDX+0xEA]
	MOV DWORD PTR DS:[EDX],0
	SUB EDX,8
	MOV DWORD PTR DS:[EDX],0
	ADD EDX,4
	MOV DWORD PTR DS:[EDX],0
	ADD EDX,0x68
	MOV DWORD PTR DS:[EDX],0
	POP EDI
	POP ESI
	POP EBP
	POP EBX
	RETN 4
IS_NOT_ON_BUTTON:
	JMP D2isLODGame
}}

FCT_ASM ( initBtnsStates )
	MOV isDownBtn.all,0
	ADD ESP,0x104
	RETN
}}

void Install_InterfaceStash()
{
	static int isInstalled = false;
	if (isInstalled) return;

	Install_UpdateServer();
	Install_PlugYImagesFiles();

	log_msg("[Patch] D2Client for stash interface. (InterfaceStash)\n");

	DWORD ButtonImagesOffset = D2Client::GetOffsetByAddition(0x39060);
	DWORD PageNumberOffset = D2Client::GetOffsetByAddition(0x3903C);
	DWORD MouseDownSoundOffset = D2Client::GetOffsetByAddition(0x45091);
	DWORD MouseUpSoundOffset = D2Client::GetOffsetByAddition(0x455F9);
	DWORD OpenStashPageInitStateOffset = D2Client::GetOffsetByAddition(0x45B3A);
	DWORD GreenSetItemSearchOffset = D2Client::GetOffsetByAddition(0x3F098);
	DWORD GreenSetItemNextSearchOffset = D2Client::GetOffsetByAddition(0x3F0FA);
	
	// Print button images
	mem_seek(ButtonImagesOffset);
	MEMC_REF4(D2Client::D2LoadBuySelBtn, printBtns);

	// print page number
	mem_seek(PageNumberOffset);
	MEMJ_REF4(D2Win::D2PrintString, printPageNumber);

	// Manage mouse down (Play sound)
	mem_seek(MouseDownSoundOffset);
	MEMC_REF4((DWORD)D2isLODGame, caller_manageBtnDown);

	// Manage mouse up
	mem_seek(MouseUpSoundOffset);
	MEMC_REF4((DWORD)D2isLODGame, caller_manageBtnUp);

	// init state of button on open stash page
	mem_seek(OpenStashPageInitStateOffset);
	memt_byte(0x81, 0xE9);
	MEMT_REF4(0x104C4, initBtnsStates);
	memt_byte(0, 0x90);

	// init the search of print in green the item set name we have in stash
	mem_seek(GreenSetItemSearchOffset);
	MEMJ_REF4(D2Common::D2InventoryGetFirstItem, initGetNextItemForSet);

	// Get next item for print in green the item set name we have in stash
	mem_seek(GreenSetItemNextSearchOffset);
	MEMJ_REF4(D2Common::D2UnitGetNextItem, getNextItemForSet);

	log_msg("\n");

	isInstalled = true;
}

