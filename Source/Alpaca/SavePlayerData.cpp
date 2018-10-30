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

#include "infinityStash.h"
#include "extendedSaveFile.h"
#include "sharedSaveFile.h"
#include "common.h"

void __stdcall SaveSPPlayerCustomData(Unit* ptChar)
{
	if (!D2isLODGame()) return;

	log_msg("\n--- Start SaveSPPlayerCustomData ---\n");

	if (PCPY->selfStashIsOpened)
	{
		DWORD curSizeExt = 0;
		DWORD maxSizeExt = 0x4000;
		BYTE* dataExt = (BYTE *)D2AllocMem(PCGame->memoryPool, maxSizeExt, __FILE__, __LINE__, 0);
		d2_assert(!dataExt, "Error : Memory allocation Extended SaveFile", __FILE__, __LINE__);
		saveExtendedSaveFile(ptChar, &dataExt, &maxSizeExt, &curSizeExt);
		writeExtendedSaveFile(PCPlayerData->name, dataExt, curSizeExt);
		D2FreeMem(PCGame->memoryPool, dataExt, __FILE__, __LINE__, 0);
	}

	if (PCPY->sharedStashIsOpened)
	{
		DWORD curSizeShr = 0;
		DWORD maxSizeShr = 0x4000;
		BYTE* dataShr = (BYTE *)D2AllocMem(PCGame->memoryPool, maxSizeShr, __FILE__, __LINE__, 0);
		d2_assert(!dataShr, "Error : Memory allocation Shared SaveFile", __FILE__, __LINE__);
		saveSharedSaveFile(ptChar, &dataShr, &maxSizeShr, &curSizeShr);

		NetClient* ptClient = D2GetClient(ptChar, __FILE__, __LINE__);
		writeSharedSaveFile(PCPlayerData->name, dataShr, curSizeShr, ptClient->isHardCoreGame);
		D2FreeMem(PCGame->memoryPool, dataShr, __FILE__, __LINE__, 0);
	}

	log_msg("End saving.\n\n");
}

//////////////////////////////////////////////////////////////////////////////////////////////////

#define TC_SAVE_PERSONAL 0
#define TC_SAVE_SHARED 1

#pragma pack(1)
typedef struct {
	BYTE	packID;
	BYTE	packSize;
	BYTE	init;
	DWORD	finalSize : 31;
	DWORD	isCustom : 1;
	BYTE	type;
	BYTE	data[0xFF];
} t_rcvMsg;
#pragma pack()

struct s_MPSaveFile
{
	int		sizeExtended;
	int		curExtended;
	BYTE*	dataExtended;
	int		sizeShared;
	int		curShared;
	BYTE*	dataShared;
};
static s_MPSaveFile receivedSaveFiles;
static BYTE customPackID = 0xB2;

struct s_dataToSend
{
	s_dataToSend*	next;
	int		clientID;
	int		sizeExtended;
	int		curExtended;
	BYTE*	dataExtended;
	int		sizeShared;
	int		curShared;
	BYTE*	dataShared;
	bool	init;
};
s_dataToSend* ptDataToSend = NULL;

void __stdcall SendSaveFilesToSave(Unit* ptChar)
{
	log_msg("\n--- Start SendSaveFilesToSave ---\n");
	if (!D2isLODGame()) return;

	DWORD curSizeExt = 0;
	BYTE* dataExt = NULL;
	DWORD curSizeShr = 0;
	BYTE* dataShr = NULL;

	if (PCPY->selfStashIsOpened)
	{
		DWORD maxSizeExt = 0x4000;
		dataExt = (BYTE *)D2AllocMem(PCGame->memoryPool, maxSizeExt, __FILE__, __LINE__, 0);
		d2_assert(!dataExt, "Error : Memory allocation Extended SaveFile", __FILE__, __LINE__);
		saveExtendedSaveFile(ptChar, &dataExt, &maxSizeExt, &curSizeExt);
	}

	if (PCPY->sharedStashIsOpened)
	{
		DWORD maxSizeShr = 0x4000;
		dataShr = (BYTE *)D2AllocMem(PCGame->memoryPool, maxSizeShr, __FILE__, __LINE__, 0);
		d2_assert(!dataShr, "Error : Memory allocation Shared SaveFile", __FILE__, __LINE__);
		saveSharedSaveFile(ptChar, &dataShr, &maxSizeShr, &curSizeShr);
	}

	NetClient* ptClient = D2GetClient(ptChar, __FILE__, __LINE__);
	s_dataToSend* dataToSend = ptDataToSend;
	while (dataToSend && (dataToSend->clientID != ptClient->clientID))
		dataToSend = dataToSend->next;
	if (!dataToSend)
	{
		dataToSend = (s_dataToSend*)D2AllocMem(PCGame->memoryPool, sizeof(s_dataToSend), __FILE__, __LINE__, 0);
		ZeroMemory(dataToSend, sizeof(s_dataToSend));
		dataToSend->next = ptDataToSend;
		ptDataToSend = dataToSend;
	}

	//Sending savefiles
	dataToSend->clientID = ptClient->clientID;
	dataToSend->init = 1;
	dataToSend->sizeExtended = curSizeExt;
	dataToSend->curExtended = 0;
	dataToSend->dataExtended = dataExt;
	dataToSend->sizeShared = curSizeShr;
	dataToSend->curShared = 0;
	dataToSend->dataShared = dataShr;
	log_msg("clientID=%d\t init=%d\t sizeExtended=%X\t curExtended=%X\t dataExtended=%X\t sizeShared=%X\t curShared=%X\t dataShared=%08X\n",
		dataToSend->clientID, dataToSend->init, dataToSend->sizeExtended, dataToSend->curExtended, dataToSend->dataExtended, dataToSend->sizeShared, dataToSend->curShared, dataToSend->dataShared);

	log_msg("End SendSaveFilesToSave.\n\n");
}

DWORD __stdcall ManageNextPacketToSend(NetClient* ptClient)
{
	log_msg("ManageNextPacketToSend: ");
	s_dataToSend* dataToSend = ptDataToSend;
	while (dataToSend && (dataToSend->clientID != ptClient->clientID))
		dataToSend = dataToSend->next;
	if (!dataToSend) return 1;

	log_msg("clientID=%d\t init=%d\t sizeExtended=%X\t curExtended=%X\t dataExtended=%X\n",
		dataToSend->clientID, dataToSend->init, dataToSend->sizeExtended, dataToSend->curExtended, dataToSend->dataExtended);

	if (dataToSend->sizeExtended && dataToSend->dataExtended && (dataToSend->curExtended < dataToSend->sizeExtended))
	{
		DWORD remainingData = dataToSend->sizeExtended - dataToSend->curExtended;
		t_rcvMsg* msg = (t_rcvMsg*)D2AllocMem(PClientGame->memoryPool, sizeof(t_rcvMsg), __FILE__, __LINE__, 0);
		msg->packID = customPackID;
		msg->init = dataToSend->init;
		msg->finalSize = dataToSend->sizeExtended;
		msg->isCustom = true;
		msg->packSize = remainingData > 0xFE ? 0xFF : (BYTE)remainingData + 1;
		CopyMemory(msg->data, &dataToSend->dataExtended[dataToSend->curExtended], msg->packSize);
		log_msg("Saving Send Packet: init=%d\t finalSize=%X\t packSize=%02X\t data=%08X\n", msg->init, msg->finalSize, msg->packSize, msg->data);
		D2SendToClient(0, dataToSend->clientID, msg, msg->packSize + 7);
		dataToSend->init = false;
		dataToSend->curExtended += msg->packSize - 1;
		D2FreeMem(PClientGame->memoryPool, msg, __FILE__, __LINE__, 0);
		if (dataToSend->curExtended == dataToSend->sizeExtended)
		{
			dataToSend->sizeExtended = 0;
			dataToSend->curExtended = 0;
			D2FreeMem(PClientGame->memoryPool, dataToSend->dataExtended, __FILE__, __LINE__, 0);
			dataToSend->dataExtended = NULL;
		}
		log_msg("End Send Packet\n");
		return 0;
	}

	log_msg("End Send Packet\n");
	return 1;
}


DWORD __stdcall ReceiveSaveFilesToSave(t_rcvMsg* msg)
{
	if ((msg->packID != customPackID) || !msg->isCustom) return 0;

	log_msg("Saving Receive Packet: init=%d\t finalSize=%X\t packSize=%02X\t data=%08X\n", msg->init, msg->finalSize, msg->packSize, msg->data);

	if (msg->init)
	{
		D2FogMemDeAlloc(receivedSaveFiles.dataExtended, __FILE__, __LINE__, 0);
		ZeroMemory(&receivedSaveFiles, sizeof(receivedSaveFiles));
	}

	log_msg("receivedSaveFiles: sizeExtended=%d\t curExtended=%d\t dataExtended=%08X\n", receivedSaveFiles.sizeExtended, receivedSaveFiles.curExtended, receivedSaveFiles.dataExtended);

	DWORD size = msg->packSize - 1;

	// Only the infinite personal stash is sent in lan games.
	if (receivedSaveFiles.sizeExtended == 0)
		receivedSaveFiles.sizeExtended = msg->finalSize;

	if (!receivedSaveFiles.dataExtended)
		receivedSaveFiles.dataExtended = (BYTE *)D2FogMemAlloc(receivedSaveFiles.sizeExtended, __FILE__, __LINE__, 0);

	CopyMemory(&receivedSaveFiles.dataExtended[receivedSaveFiles.curExtended], msg->data, size);
	receivedSaveFiles.curExtended += size;

	log_msg("End Save Receive Packet\n");
	return 1;
}


void __stdcall SaveMPPlayerCustomData(BYTE* dataD2Savefile)
{
	if (!D2isLODGame()) return;

	log_msg("[SaveMPPlayerCustomData] Function Started\n");

	Unit* ptChar = D2GetClientPlayer();
	if (ptChar)
	{
		if (receivedSaveFiles.sizeExtended && (receivedSaveFiles.sizeExtended == receivedSaveFiles.curExtended))
		{
			log_msg("[SaveMPPlayerCustomData] Saving Received Save File ...\n");

			writeExtendedSaveFile(PCPlayerData->name, receivedSaveFiles.dataExtended, receivedSaveFiles.sizeExtended);
			D2FogMemDeAlloc(receivedSaveFiles.dataExtended, __FILE__, __LINE__, 0);
			ZeroMemory(&receivedSaveFiles, sizeof(receivedSaveFiles));

			log_msg("[SaveMPPlayerCustomData] Received Save File Successfully Saved!\n\n");
		}
		else
		{
			log_box("[SaveMPPlayerCustomData] Connection error. Unable to save the received save file.");
		}
	}

	log_msg("[SaveMPPlayerCustomData] Function Completed\n\n");
}

FCT_ASM(caller_SaveSPPlayerCustomData_9)
CALL D2FogGetSavePath
PUSH ESI
CALL SaveSPPlayerCustomData
RETN
}}

FCT_ASM( caller_ManageNextPacketToSend_9 )
	PUSH ESI
	CALL ManageNextPacketToSend
	TEST EAX,EAX
	JNZ end_caller_ManageNextPacketToSend_9
	MOV DWORD PTR DS:[ESI+0x14C],5
	POP ESI
	POP ESI
	RETN
end_caller_ManageNextPacketToSend_9:
	MOV EAX,DWORD PTR DS:[ESI+0x150]
	RETN
}}

FCT_ASM( caller_SendSaveFilesToSave )
	PUSH EDI
	CALL SendSaveFilesToSave
	MOV EDI,DWORD PTR SS:[ESP+0x14]
	TEST EDI,EDI
	RETN
}}

FCT_ASM( caller_SendSaveFilesToSave_9 )
	PUSH ESI
	CALL SendSaveFilesToSave
	MOV ESI,DWORD PTR SS:[ESP+0x14]
	TEST ESI,ESI
	RETN
}}

FCT_ASM ( caller_ReceivedSaveFilesToSave )
	CMP EDX,-1
	JE continue_rcvFct
	PUSH ECX
	PUSH EDX
	PUSH ECX
	CALL ReceiveSaveFilesToSave
	POP EDX
	POP ECX
	TEST EAX,EAX
	JE continue_rcvFct
	XOR EAX,EAX
	ADD ESP,4
	RETN
continue_rcvFct:
	POP EAX
	SUB ESP,0x5F4//5F4
	JMP EAX
}}

FCT_ASM ( caller_SaveMPPlayerCustomData )
	PUSH ECX
	PUSH ECX
	CALL SaveMPPlayerCustomData
	POP ECX
	MOV EAX,DWORD PTR DS:[ECX]
	MOV EDX,DWORD PTR DS:[ECX+4]
	RETN
}}

void Install_SavePlayerData()
{
	static int isInstalled = false;
	if (isInstalled || !active_PlayerCustomData) return;

	log_msg("[Patch] D2Game & D2Client for save Player's custom data. (SavePlayerData)\n");

	DWORD SaveSinglePlayerCustomDataOffset = D2Game::GetOffsetByAddition(0x4DF04);
	DWORD SendSaveFilesOffset1 = D2Game::GetOffsetByAddition(0x4DFFA);
	DWORD SendSaveFilesOffset2 = D2Game::GetOffsetByAddition(0x7993);
	DWORD ReceivedSaveFilesOffset = D2Client::GetOffsetByAddition(0x116F0);
	DWORD SaveMultiplayerPlayerCustomDataOffset = D2Client::GetOffsetByAddition(0x117FC);

	//Save single player custom data.
	mem_seek(SaveSinglePlayerCustomDataOffset);
	MEMJ_REF4(Fog::D2FogGetSavePath, caller_SaveSPPlayerCustomData_9);

	//Send SaveFiles
	mem_seek(SendSaveFilesOffset1);
	memt_byte(0x8B, 0x90);
	memt_byte(0x74, 0xE8);
	MEMT_REF4(0xF6851024, caller_SendSaveFilesToSave_9);

	mem_seek(SendSaveFilesOffset2);
	memt_byte(0x8B, 0x90);
	memt_byte(0x86, 0xE8);
	MEMT_REF4(0x150, caller_ManageNextPacketToSend_9);
	
	// Received SaveFiles
	mem_seek(ReceivedSaveFilesOffset);
	memt_byte(0x81, 0x90);
	memt_byte(0xEC, 0xE8);
	MEMT_REF4(0x5F4, caller_ReceivedSaveFilesToSave);

	// Save multiplayer player custom data.
	mem_seek(SaveMultiplayerPlayerCustomDataOffset);
	memt_byte(0x8B, 0xE8);
	MEMT_REF4(0x04518B01, caller_SaveMPPlayerCustomData);
	
	customPackID = 0xAB;

	if (active_logFileMemory) log_msg("\n");
	isInstalled = true;
}