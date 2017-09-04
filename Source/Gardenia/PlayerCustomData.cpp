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
#include "savePlayerData.h" //Install_SavePlayerData()
#include "loadPlayerData.h" //Install_LoadPlayerData()
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


Unit* FASTCALL updateItem(GameStruct* ptGame, DWORD type, DWORD itemNum, Unit* ptChar)
{
	Unit* ptItem = D2GameGetObject(ptGame, type, itemNum);
	if (ptGame->isLODGame && (D2ItemGetPage(ptItem) == 4))
	{
		Stash* ptStash = getStashFromItem(ptChar, ptItem);
		if (!ptStash) return NULL;
		selectStash(ptChar, ptStash);
	}
	return ptItem;
}


void STDCALL updateClientPlayerOnLoading(Unit* ptChar)
{
	log_msg("--- Start updateClientPlayerOnLoading ---\n");
	if (PCGame->isLODGame)
	{
		PCPY->showSharedStash = openSharedStashOnLoading;
		selectStash(ptChar, openSharedStashOnLoading ? PCPY->sharedStash : PCPY->selfStash);

		log_msg("End update client on loading.\n\n");
	}
	updateClient(ptChar, UC_SHARED_GOLD, PCPY->sharedGold, 0, 0);
}

/**************************** INIT CUSTOM DATA ****************************/

PlayerData* FASTCALL init_PlayerCustomData(DWORD p1, DWORD size, LPCSTR file, DWORD line, DWORD p5)
{
	log_msg("init_PlayerCustomData\n");
	PlayerData* playerData = (PlayerData*)D2AllocMem(p1,size+sizeof(PYPlayerData),file,line,p5);
	ZeroMemory((BYTE*)playerData + shifting.ptPYPlayerData, sizeof(PYPlayerData));
	return playerData;
}

/**************************** FREE CUSTOM DATA ****************************/


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


void FASTCALL free_PlayerCustomData(DWORD p1, PlayerData* playerData, LPCSTR file, DWORD line, DWORD p5)
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

Unit* STDCALL getNextItemToFree(Unit* ptChar, Unit* ptItem)
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
			return item;//->nUnitType == 4 ? item : NULL;
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


/************************ INSTALL PLAYER CUSTOM DATA ****************************/

void FASTCALL updateItem_111(Unit* ptItem, Unit* ptChar)
{
	if (PCGame->isLODGame && (D2ItemGetPage(ptItem) == 4))
	{
		Stash* ptStash = getStashFromItem(ptChar, ptItem);
		if (ptStash)
			selectStash(ptChar, ptStash);
	}
}

FCT_ASM ( caller_updateItem_111 )
	MOV ECX,ESI
	MOV EDX,EBP
	CALL updateItem_111
	POP EAX
	MOV EDX,DWORD PTR SS:[ESP+0x18]
	PUSH EDX
	JMP EAX
}}

FCT_ASM ( caller_updateItemB_111 )
	MOV EDX,EBP
	CALL updateItem_111
	POP EAX
	MOV EDX,DWORD PTR SS:[ESP+0x18]
	PUSH EDX
	JMP EAX
}}

FCT_ASM ( caller_updateItem )
	PUSH EBP
	PUSH DWORD PTR SS:[ESP+0x8]
	CALL updateItem
	RETN 4
}}

FCT_ASM ( caller_updateItem_9 )
	PUSH EBX
	PUSH DWORD PTR SS:[ESP+0x8]
	CALL updateItem
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

FCT_ASM ( callerServer_getNextItemToFree_111 )
	PUSH DWORD PTR SS:[ESP+4]
	PUSH DWORD PTR SS:[ESP+0x30]
	CALL getNextItemToFree
	RETN 4
}}

FCT_ASM ( callerServer_getNextItemToFree )
	PUSH DWORD PTR SS:[ESP+4]
	PUSH DWORD PTR SS:[ESP+0x28]
	CALL getNextItemToFree
	RETN 4
}}

FCT_ASM ( callerServer_getNextItemToFree_9 )
	PUSH DWORD PTR SS:[ESP+4]
	PUSH DWORD PTR SS:[ESP+0x1C]
	CALL getNextItemToFree
	RETN 4
}}


FCT_ASM ( callerClient_getNextItemToFree_111 )
	PUSH DWORD PTR SS:[ESP+4]
	PUSH EBX
	CALL getNextItemToFree
	RETN 4
}}

FCT_ASM ( callerClient_getNextItemToFree )
	PUSH DWORD PTR SS:[ESP+4]
	PUSH DWORD PTR SS:[ESP+0x24]
	CALL getNextItemToFree
	RETN 4
}}

FCT_ASM ( callerClient_getNextItemToFree_9 )
	PUSH DWORD PTR SS:[ESP+4]
	PUSH DWORD PTR SS:[ESP+0x28]
	CALL getNextItemToFree
	RETN 4
}}

// [Patch]
void Install_PlayerCustomData()
{
	static int isInstalled = false;
	if (isInstalled || !active_PlayerCustomData) return;

	Install_SavePlayerData();
	Install_LoadPlayerData();
	Install_UpdateClient();

	log_msg("Patch D2Game & D2Client & D2Common for Player's custom data. (PlayerCustomData)\n");

	// Initialize custom data.
	mem_seek(D2Common->GetOffsetByAddition(0x70462, 0x70562, 0x80382, 0x4ED5E, 0x5BFCE, 0x585EE, 0x309BE, 0x170DE));
	MEMJ_REF4(Fog->D2AllocMem, init_PlayerCustomData);

	if (Game->Version >= VersionUtility::Versions::V111 )
	{
		// update item
		mem_seek(D2Game->GetOffsetByAddition(0x10933, 0x10C03, 0x1100D, 0x8BC71, 0xC3C51, 0x5F2A1, 0x9BB91, 0x75C81));
		memt_byte(0x8B, 0xE8);
		MEMT_REF4(0x52182454, caller_updateItem_111);

		mem_seek(D2Game->GetOffsetByAddition(0x1097B, 0x10C4B, 0x11058, 0x8BCD1, 0xC3CB1, 0x5F301, 0x9BBF1, 0x75CE1));
		memt_byte(0x8B, 0xE8);
		MEMT_REF4(0x52182454, caller_updateItemB_111);
	}
	else
	{
		// update item
		mem_seek(D2Game->GetOffsetByAddition(0x10933, 0x10C03, 0x1100D, 0x8BC71, 0xC3C51, 0x5F2A1, 0, 0));
		MEMC_REF4(D2Game->D2GameGetObject, Game->Version == VersionUtility::Versions::V110? caller_updateItem: caller_updateItem_9);

		mem_seek(D2Game->GetOffsetByAddition(0x1097B, 0x10C4B, 0x11058, 0x8BCD1, 0xC3CB1, 0x5F301, 0, 0));
		MEMC_REF4(D2Game->D2GameGetObject, Game->Version == VersionUtility::Versions::V110? caller_updateItem: caller_updateItem_9);
	}

	// Update client on loading
	mem_seek(D2Game->GetOffsetByAddition(0x23EB, 0x2426, 0x25D4, 0x53482, 0xC6A32, 0xED502, 0x4BF12, 0xE7548));
	memt_byte(0x5F, 0xE8);
	MEMT_REF4(0xC0335D5E, caller_updateClientPlayerOnLoading);

	// Free custom data.
	mem_seek(D2Common->GetOffsetByAddition(0x7055C, 0x7065C, 0x80483, 0x4F82D, 0x5C9CD, 0x5856D, 0x3093D, 0x1705D));
	MEMJ_REF4(Fog->D2FreeMem, free_PlayerCustomData);

	// Free item in Stash (Server-side)
	mem_seek(D2Game->GetOffsetByAddition(0x7D12B, 0x7D62B, 0x8D5A4, 0x99112, 0xBFDB2, 0x94242, 0xE1162, 0x6F7C2));
	MEMJ_REF4(D2Common->D2UnitGetNextItem, Game->Version >= VersionUtility::Versions::V111 ? callerServer_getNextItemToFree_111 : Game->Version == VersionUtility::Versions::V110 ? callerServer_getNextItemToFree : callerServer_getNextItemToFree_9);

	// Free item in Stash (Client-side)
	mem_seek(D2Client->GetOffsetByAddition(0x8EF8F, 0x8E30F, 0x89B32, 0x26404, 0x4C264, 0x1F2D4, 0xA5C94, 0x621E4));
	MEMJ_REF4(D2Common->D2UnitGetNextItem, Game->Version >= VersionUtility::Versions::V111 ? callerClient_getNextItemToFree_111 : Game->Version == VersionUtility::Versions::V110 ? callerClient_getNextItemToFree : callerClient_getNextItemToFree_9);

	if (Game->Version >= VersionUtility::Versions::V110)
	{
		// Test if it's already removed from inventory
		mem_seek(D2Common->GetOffsetByAddition(0, 0, 0x4E689, 0x26E33, 0x42133, 0x6AE93, 0x21B23, 0x3B393));
		memt_byte(0x0D, 0x07);
	}
	else
	{
		mem_seek(D2Game->GetOffsetByAddition(0x7D176, 0x7D676, 0, 0, 0, 0, 0, 0));
		memt_byte(0x74, 0x90);
		memt_byte(0x35, 0x90);

		mem_seek(D2Client->GetOffsetByAddition(0x8F0CA, 0x8E44A, 0, 0, 0, 0, 0, 0));
		memt_byte(0x0F, 0x90);
		memt_byte(0x84, 0x90);
		memt_dword(0x000000BF , 0x90909090);

		mem_seek(D2Client->GetOffsetByAddition(0x8F13C, 0x8E4BC, 0, 0, 0, 0, 0, 0));
		memt_byte(0x74 , 0x90);
		memt_byte(0x6F , 0x90);
	}

	log_msg("\n");

	isInstalled = true;
}

