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

#include "updateClient.h"
#include "infinityStash.h"
#include "interface_Stash.h"
#include "savePlayerData.h"
#include "loadPlayerData.h"
#include "common.h"

bool active_PlayerCustomData = true;
bool openSharedStashOnLoading = false;

Stash* getStashFromItem(Unit* ptChar, Unit* ptItem)
{
	Stash* curStash = PCPY->selfStash;
	Unit* curItem;
	while (curStash)
	{
		if (curStash == PCPY->currentStash)
			 curItem = D2InventoryGetFirstItem(PCInventory);
		else curItem = curStash->ptListItem;
		while (curItem)
		{
			if (D2GetRealItem(curItem) == ptItem) return curStash;
			curItem = D2UnitGetNextItem(curItem);
		}
		curStash = curStash->nextStash;
	}
	
	curStash = PCPY->sharedStash;
	while (curStash)
	{
		if (curStash == PCPY->currentStash)
			 curItem = D2InventoryGetFirstItem(PCInventory);
		else curItem = curStash->ptListItem;
		while (curItem)
		{
			if (D2GetRealItem(curItem) == ptItem) return curStash;
			curItem = D2UnitGetNextItem(curItem);
		}
		curStash = curStash->nextStash;
	}
	return NULL;
}


Unit* __fastcall updateItem(GameStruct* ptGame, DWORD type, DWORD itemNum, Unit* ptChar)
{
	Unit* ptItem = D2GameGetObject(ptGame, type, itemNum);
	if (ptGame->isLODGame && (D2ItemGetPage(ptItem) == 4))
	{
		Stash* ptStash = getStashFromItem(ptChar, ptItem);
		if (!ptStash) return NULL;
		selectStash(ptChar, ptStash, true);
	}
	return ptItem;
}


void __stdcall updateClientPlayerOnLoading(Unit* ptChar)
{
	log_msg("--- Start update client on loading ---\n");
	if (PCGame->isLODGame)
	{
		// The shared stash option is disabled in multiplayer. Thus override parameter if needed.
		bool actuallyOpenSharedStashOnLoading = !inMultiplayerGame(ptChar) ? openSharedStashOnLoading : 0;
		PCPY->showSharedStash = actuallyOpenSharedStashOnLoading;
		selectStash(ptChar, actuallyOpenSharedStashOnLoading ? PCPY->sharedStash : PCPY->selfStash);
	}
	if (!inMultiplayerGame(ptChar))
	{
		updateClient(ptChar, UC_SHARED_GOLD, PCPY->sharedGold, 0, 0);
	}
	log_msg("--- End update client on loading ---\n\n");
}

PlayerData* __fastcall init_PlayerCustomData(DWORD p1, DWORD size, LPCSTR file, DWORD line, DWORD p5)
{
	log_msg("init_PlayerCustomData\n");
	PlayerData* playerData = (PlayerData*)D2AllocMem(p1,size+sizeof(PYPlayerData),file,line,p5);
	ZeroMemory((BYTE*)playerData + shifting.ptPYPlayerData, sizeof(PYPlayerData));
	return playerData;
}

void freeStash(Stash* ptStash)
{
	if (!ptStash) return;
	freeStash(ptStash->nextStash);
	free(ptStash->nextStash);//	D2FogMemDeAlloc(ptStash->nextStash,__FILE__,__LINE__,0);
	if(ptStash->name)
	{
		free(ptStash->name);//D2FogMemDeAlloc(ptStash->name,__FILE__,__LINE__,0);
		ptStash->name = NULL;
	}
	ptStash->nextStash = NULL;
}


void __fastcall free_PlayerCustomData(DWORD p1, PlayerData* playerData, LPCSTR file, DWORD line, DWORD p5)
{
	log_msg("free_PlayerCustomData\n");
	PYPlayerData* ptPYPlayerData = (PYPlayerData*)((DWORD)playerData + shifting.ptPYPlayerData);

	freeStash(ptPYPlayerData->selfStash);
	free(ptPYPlayerData->selfStash);//D2FogMemDeAlloc(ptPYPlayerData->selfStash,__FILE__,__LINE__,0);
	ptPYPlayerData->selfStash = NULL;

	freeStash(ptPYPlayerData->sharedStash);
	free(ptPYPlayerData->sharedStash);//D2FogMemDeAlloc(ptPYPlayerData->sharedStash,__FILE__,__LINE__,0);
	ptPYPlayerData->sharedStash = NULL;

	D2FreeMem(p1,playerData,file,line,p5);
}

Unit* __stdcall getNextItemToFree(Unit* ptChar, Unit* ptItem)
{
	Unit* item = D2UnitGetNextItem(ptItem);
	if (item) return item;

	if (ptChar->nUnitType != UNIT_PLAYER) return NULL;
	if (!PCPlayerData) return NULL;
	if (!PCPY) return NULL;

	Stash* curStash = PCPY->selfStash;
	while ( curStash )
	{
		if (curStash->ptListItem)
		{
			item = curStash->ptListItem;
			curStash->ptListItem = NULL;
			return item;
		}
		curStash = curStash->nextStash;
	}	

	curStash = PCPY->sharedStash;
	while ( curStash )
	{
		if (curStash->ptListItem)
		{
			item = curStash->ptListItem;
			curStash->ptListItem = NULL;
			return item->nUnitType == 4 ? item : NULL;
		}
		curStash = curStash->nextStash;
	}

	return NULL;
}

void __fastcall updateItem_111(Unit* ptItem, Unit* ptChar)
{
	if (PCGame->isLODGame && (D2ItemGetPage(ptItem) == 4))
	{
		Stash* ptStash = getStashFromItem(ptChar, ptItem);
		if (ptStash)
		{
			selectStash(ptChar, ptStash, true);
		}
	}
}

FCT_ASM(caller_updateItem_111)
	MOV ECX, ESI
	MOV EDX, EBP
	CALL updateItem_111
	POP EAX
	MOV EDX, DWORD PTR SS : [ESP + 0x18]
	PUSH EDX
	JMP EAX
}}

FCT_ASM(caller_updateItemB_111)
	MOV EDX, EBP
	CALL updateItem_111
	POP EAX
	MOV EDX, DWORD PTR SS : [ESP + 0x18]
	PUSH EDX
	JMP EAX
}}

FCT_ASM(callerServer_getNextItemToFree_111)
	PUSH DWORD PTR SS : [ESP + 4]
	PUSH DWORD PTR SS : [ESP + 0x30]
	CALL getNextItemToFree
	RETN 4
}}

FCT_ASM(callerClient_getNextItemToFree_111)
	PUSH DWORD PTR SS : [ESP + 4]
	PUSH EBX
	CALL getNextItemToFree
	RETN 4
}}

FCT_ASM ( caller_updateClientPlayerOnLoading )
	PUSH DWORD PTR SS:[ESP+0x14]
	CALL updateClientPlayerOnLoading
	POP ECX
	POP EDI
	POP ESI
	POP EBP
	XOR EAX,EAX
	JMP ECX
}}

void Install_PlayerCustomData()
{
	static int isInstalled = false;
	if (isInstalled || !active_PlayerCustomData) return;

	Install_SavePlayerData();
	Install_LoadPlayerData();
	Install_UpdateClient();

	log_msg("[Patch] D2Game & D2Client & D2Common for Player's custom data. (PlayerCustomData)\n");

	DWORD InitializeCustomDataOffset = D2Common::GetOffsetByAddition(0x170DE);
	DWORD UpdateItemOffset1 = D2Game::GetOffsetByAddition(0x75C81);
	DWORD UpdateItemOffset2 = D2Game::GetOffsetByAddition(0x75CE1);
	DWORD UpdateClientOnLoadingOffset = D2Game::GetOffsetByAddition(0xE7548);
	DWORD FreeCustomDataOffset = D2Common::GetOffsetByAddition(0x1705D);
	DWORD FreeItemInStashServerSideOffset = D2Game::GetOffsetByAddition(0x6F7C2);
	DWORD FreeItemInStashClientSideOffset = D2Client::GetOffsetByAddition(0x621E4);
	DWORD TestIfAlreadyRemovedFromInventoryOffset = D2Common::GetOffsetByAddition(0x3B393);

	// Initialize custom data.
	mem_seek(InitializeCustomDataOffset);
	MEMJ_REF4(Fog::D2AllocMem, init_PlayerCustomData);

	// update item
	mem_seek(UpdateItemOffset1);
	memt_byte(0x8B, 0xE8);
	MEMT_REF4(0x52182454, caller_updateItem_111);

	// TODO: Not sure if this variable is actually needed since I haven't been able to get a breakpoint to hit this.
	// Will do more testing at a future date.
	mem_seek(UpdateItemOffset2);
	memt_byte(0x8B, 0xE8);
	MEMT_REF4(0x52182454, caller_updateItemB_111);
	
	// Update client on loading
	mem_seek(UpdateClientOnLoadingOffset);
	memt_byte(0x5F, 0xE8);
	MEMT_REF4(0xC0335D5E, caller_updateClientPlayerOnLoading);

	// Free custom data.
	mem_seek(FreeCustomDataOffset);
	MEMJ_REF4(Fog::D2FreeMem, free_PlayerCustomData);

	// Free item in Stash (Server-side)
	mem_seek(FreeItemInStashServerSideOffset);
	MEMJ_REF4(D2Common::D2UnitGetNextItem, callerServer_getNextItemToFree_111);

	// Free item in Stash (Client-side)
	mem_seek(FreeItemInStashClientSideOffset);
	MEMJ_REF4(D2Common::D2UnitGetNextItem, callerClient_getNextItemToFree_111);

	// Test if it's already removed from inventory
	mem_seek(TestIfAlreadyRemovedFromInventoryOffset);
	memt_byte(0x0D, 0x07);

	if (active_logFileMemory) log_msg("\n");
	isInstalled = true;
}