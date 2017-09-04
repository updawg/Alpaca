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

DWORD STDCALL LoadSPCustomData(Unit* ptChar)
{
	DWORD size = 0;
	BYTE* data;

	log_msg("--- Start LoadSPCustomData ---\n");

	if (!ptChar)
		{log_msg("LoadSPCustomData : ptChar == NULL\n");return 0x1B;}//Unknow failure
	if (ptChar->nUnitType != UNIT_PLAYER)
		{log_msg("LoadSPCustomData : ptChar->nUnitType != UNIT_PLAYER\n");return 0x1B;}//Unknow failure
	if (!PCPlayerData)
		{log_msg("LoadSPCustomData : PCPlayerData == NULL\n");return 0x1B;}//Unknow failure
	if (!PCGame)
		{log_msg("LoadSPCustomData : PCGame == NULL\n");return 0x1B;}//Unknow failure

	DWORD ret=0;
	if (PCGame->isLODGame)
	{
		log_msg("is LOD Game\n");
		data = readExtendedSaveFile(PCPlayerData->name, &size);
		ret = loadExtendedSaveFile(ptChar, data, size);
		D2FogMemDeAlloc(data,__FILE__,__LINE__,0);
		if (!ret)
		{
			data = readSharedSaveFile(PCPlayerData->name, &size);
			ret = loadSharedSaveFile(ptChar, data, size);
			D2FogMemDeAlloc(data,__FILE__,__LINE__,0);
		}
	} else {
		log_msg("is not LOD Game\n");
	}

	log_msg("End LoadSPCustomData.\n\n");
	return ret;
}


FCT_ASM (caller_LoadSPPlayerCustomData )
	MOV ESI,EAX
	TEST ESI,ESI
	JNZ JMP_LoadSPPlayerCustomData
	PUSH DWORD PTR SS:[ESP+0x14]
	CALL LoadSPCustomData
	MOV ESI,EAX
	TEST ESI,ESI
	JNZ JMP_LoadSPPlayerCustomData
	RETN
JMP_LoadSPPlayerCustomData:
	ADD DWORD PTR SS:[ESP],0x17
	RETN
}}


/*
return value :
0:ok
1:Unable to enter game. Bad character version
2:Unable to enter game. Bad character quest data
3:Unable to enter game. Bad character waypoint data
4:Unable to enter game. Bad character stats data
5:Unable to enter game. Bad character skills data
6:Unable to enter game
7:Unable to enter game. Bad inventory data
8:Unable to enter game. Bad dead bodies
9:Unable to enter game. Bad header
0A:Unable to enter game. bad hireables
0B:Unable to enter game, bad intro data
0C:Unable to enter game. bad item
0D:Unable to enter game, bad dead body item
0E:Unable to enter game, generic bad file
0F:Game is full
10:Version do not match....
11:Unable to enter game,Your character must kill Baal to play nightmare game
12:Unable to enter game,Your character must kill Baal in nightmare difficulty to play hell game
13:Unable to enter game, a normal character cannot join a game create an harcore character.
14:Unable to enter game, an harcore character cannot join a game create by a normal character.
15:A dead character cannot join or create any game
16:unknow failure
17:Unable to enter game. A D2 Character cannot join an expansion character
18:Expansion cannot join D2
19:Failures to join game
1A:Unable to enter game
1B:unknow failure
*/
enum {
	TS_SAVE_PERSONAL=0,
	TS_SAVE_SHARED,
	TS_PUTGOLD,
	TS_TAKEGOLD
};

#pragma pack(1)
typedef struct {
	BYTE	packID;
	BYTE	packSize;
	DWORD	finalSize:31;
	DWORD	isCustom:1;
	BYTE	type;
	BYTE	data[0xFF];
} t_rcvMsg;
#pragma pack()

struct s_MPSaveFile
{
	DWORD clientID;
	int sizeExtended;
	int curExtended;
	BYTE* dataExtended;
	int sizeShared;
	int curShared;
	BYTE* dataShared;
	s_MPSaveFile* prev;
	s_MPSaveFile* next;
	bool completed;
};

static BYTE customPackID = 0x6C;
static s_MPSaveFile * receivedSaveFiles = NULL;

void freeCurrentCF(DWORD memoryPool, s_MPSaveFile** curSF)
{
	if (*curSF == NULL) return;
	D2FreeMem(memoryPool, (*curSF)->dataExtended,__FILE__,__LINE__,0);
	D2FreeMem(memoryPool, (*curSF)->dataShared,__FILE__,__LINE__,0);
	if ((*curSF)->next)
		(*curSF)->next->prev = (*curSF)->prev;
	if ((*curSF)->prev)
		(*curSF)->prev->next = (*curSF)->next;
	else
		receivedSaveFiles = (*curSF)->next;
	D2FreeMem(memoryPool, *curSF,__FILE__,__LINE__,0);
	*curSF = NULL;
}


void sendData(BYTE* data, DWORD size, bool isShared)
{
	t_rcvMsg pack;
//	d2_assert(size >= 0x40000000, "size of file > 0x40000000", __FILE__, __LINE__);

	pack.packID = customPackID;
	pack.finalSize = size;
	pack.isCustom = true;
	pack.type = isShared ? TS_SAVE_SHARED : TS_SAVE_PERSONAL;

	DWORD sended = 0;
	while (sended < size)
	{
		pack.packSize = (BYTE) (size - sended > 0xFE ? 0xFF : size - sended + 1);
		CopyMemory(pack.data, &data[sended], pack.packSize);
		log_msg("Loading Send Packet: \ttype=%X\t finalSize=%X\t packSize=%02X\t data=%08X\n", pack.type, pack.finalSize, pack.packSize, pack.data);
		D2SendToServer(pack.packSize+7, 0, &pack);
		sended += pack.packSize -1;
	}
	log_msg("\n");
}

static DWORD	sizeExtended;
static BYTE*	dataExtended;
static DWORD	sizeShared;
static BYTE*	dataShared;

void FASTCALL SendSaveFiles (char* ptPath, DWORD maxsize, char* name)
{
//	DWORD size;
//	BYTE* data;

	D2FogGetSavePath(ptPath,maxsize);

	log_msg("\n--- Start SendSaveFiles ---\n");

	// Send Extended Save File
	log_msg("Send Extended Save File\n");
	dataExtended = readExtendedSaveFile(name, &sizeExtended);
	sendData(dataExtended, sizeExtended, false);
	D2FogMemDeAlloc(dataExtended,__FILE__,__LINE__,0);

	// Send Shared Save File
	log_msg("Send Shared Save File\n");
	dataShared = readSharedSaveFile(name, &sizeShared);
	sendData(dataShared, sizeShared, true);
	D2FogMemDeAlloc(dataShared,__FILE__,__LINE__,0);

	// Ending load
	log_msg("End SendSaveFiles.\n\n");
}



DWORD STDCALL ReceiveSaveFiles (DWORD clientID, t_rcvMsg* msg)
{
	if( (msg->packID != customPackID) || !msg->isCustom) return msg->packID;

	log_msg("Loading Receive Packet: clientID=%d\t type=%X\t finalSize=%X\t packSize=%02X\t data=%08X\n", clientID, msg->type, msg->finalSize, msg->packSize, msg->data);

	bool isShared;

	switch (msg->type)
	{
	case TS_SAVE_PERSONAL :	isShared = false;break;
	case TS_SAVE_SHARED :	isShared = true;break;
//	case TS_PUTGOLD :		putGold(ptChar, (DWORD)msg->data); return 0;
//	case TS_TAKEGOLD :		takeGold(ptChar, (DWORD)msg->data); return 0;
	default: return 0;//return msg->packID;
	}

	NetClient* ptClient = ptClientTable[clientID & 0xFF];

	s_MPSaveFile* curSF = receivedSaveFiles;
	while (curSF && (clientID != curSF->clientID) )
		curSF = curSF->next;

	if (curSF && curSF->completed)
		freeCurrentCF(0 * PClientGame->memoryPool, &curSF);


	if (!curSF)
	{
		curSF = (s_MPSaveFile *)D2AllocMem(0 * PClientGame->memoryPool, sizeof(s_MPSaveFile),__FILE__,__LINE__,0);
		ZeroMemory(curSF, sizeof(s_MPSaveFile));
		curSF->clientID = clientID;
		curSF->next = receivedSaveFiles;
		if (receivedSaveFiles) receivedSaveFiles->prev = curSF;
		receivedSaveFiles = curSF;
	}

	log_msg("curSF = %08X\tcurSF->completed = %d\n", curSF, curSF->completed);


	DWORD size = msg->packSize - 1;
	if (isShared)
	{
		if (curSF->sizeShared == 0)
			curSF->sizeShared = msg->finalSize;
		d2_assert(curSF->sizeShared != msg->finalSize, "Size of shared file has change", __FILE__, __LINE__);

		if (!curSF->dataShared)
			curSF->dataShared = (BYTE *)D2AllocMem(0 * PClientGame->memoryPool, curSF->sizeShared,__FILE__,__LINE__,0);//		d2_assert(!curSF->dataShared, "Can't malloc data", __FILE__, __LINE__);

		CopyMemory(&curSF->dataShared[curSF->curShared], msg->data, size);
		curSF->curShared += size;

	} else {

		if (curSF->sizeExtended == 0)
			curSF->sizeExtended = msg->finalSize;
		d2_assert(curSF->sizeExtended != msg->finalSize, "Size of extented file has change", __FILE__, __LINE__);

		if (!curSF->dataExtended)
			curSF->dataExtended = (BYTE *)D2AllocMem( 0 * PClientGame->memoryPool, curSF->sizeExtended,__FILE__,__LINE__,0);//		d2_assert(!curSF->dataExtended, "Can't malloc data", __FILE__, __LINE__);

		CopyMemory(&curSF->dataExtended[curSF->curExtended], msg->data, size);
		curSF->curExtended += size;
	}

	if( curSF->sizeExtended && (curSF->sizeExtended == curSF->curExtended) && curSF->sizeShared && (curSF->sizeShared == curSF->curShared) )
	{
		curSF->completed = true;
		log_msg("ReceiveSaveFiles completed.\n");
	}
	log_msg("End Load Receive Packet\n");

	return msg->packID+10;
}

/*
typedef int (STDCALL * t_fct_recv)(SOCKET s, char *buf, int len, int flags);
t_fct_recv fct_recv;
int STDCALL ReceiveSaveFiles_9(DWORD clientID, SOCKET s, char *buf, int len, int flags)
{
	t_rcvMsg* msg = (t_rcvMsg*) buf;
	int nb = fct_recv(s,buf,len,flags);
	if ((nb<6) || (msg->packID != customPackID) || !msg->isCustom || (msg->packSize+7 != nb))
		return nb;
	ReceiveSaveFiles(clientID,msg);
	msg->packSize = 1;
	return 7;
}*/

DWORD STDCALL LoadMPCustomData(Unit* ptChar)
{
	log_msg("Start LoadMPCustomData\n");

	if (!ptChar) return NULL;
	if (!ptChar)
		{log_msg("LoadMPCustomData : ptChar == NULL\n");return 0x1B;}//Unknow failure
	if (ptChar->nUnitType != UNIT_PLAYER)
		{log_msg("LoadMPCustomData : ptChar->nUnitType != UNIT_PLAYER\n");return 0x1B;}//Unknow failure
	if (!PCPlayerData)
		{log_msg("LoadMPCustomData : PCPlayerData == NULL\n");return 0x1B;}//Unknow failure

	NetClient* ptClient = D2GetClient(ptChar,__FILE__,__LINE__);

	s_MPSaveFile* curSF = receivedSaveFiles;
	while (curSF && (ptClient->clientID != curSF->clientID) )
		curSF = curSF->next;

	DWORD ret=0;

	if (!curSF)
	{
		log_msg("Server has received no data from extra save files of character %s\n", PCPlayerData->name);
		ret = 0xE;//Unable to enter game, generic bad file
	}

	if (!ret && !curSF->completed)
	{
		log_msg("Server hasn't receive all data from extra save files of character %s\n",PCPlayerData->name);
		ret = 0xE;//Unable to enter game, generic bad file
	}

	if (!ret && !PCGame)
	{
		log_msg("LoadMPCustomData : PCGame == NULL\n");
		ret = 0x1B;//Unknow failure
	}

	if (PCGame->isLODGame)
	{
		log_msg("is LOD Game\n");
		if (!ret)
			ret = loadExtendedSaveFile(ptChar, curSF->dataExtended, curSF->sizeExtended);
		if (!ret)
			ret = loadSharedSaveFile(ptChar, curSF->dataShared, curSF->sizeShared);
	} else {
		log_msg("is not LOD Game\n");
	}

	freeCurrentCF(PCGame->memoryPool, &curSF);

	log_msg("--- End LoadMPCustomData. ---\n\n");

	return ret;
}



FCT_ASM ( caller_LoadMPPlayerCustomData_111 )
	PUSH DWORD PTR SS:[EBX]
	CALL LoadMPCustomData
	TEST EAX,EAX
	JNZ JMP_LoadMPlayerCustomData
	CMP DWORD PTR DS:[EBX],0
	JNZ Continue_LoadMP
	ADD DWORD PTR SS:[ESP],0x21
Continue_LoadMP:
	RETN
JMP_LoadMPlayerCustomData:
	SUB DWORD PTR SS:[ESP],0x12
	RETN
}}


FCT_ASM ( caller_LoadMPPlayerCustomData )
	PUSH DWORD PTR SS:[EDI]
	CALL LoadMPCustomData
	TEST EAX,EAX
	JNZ JMP_LoadMPlayerCustomData
	CMP DWORD PTR DS:[EDI],0
	JNZ Continue_LoadMP
	ADD DWORD PTR SS:[ESP],0x46
Continue_LoadMP:
	RETN
JMP_LoadMPlayerCustomData:
	SUB DWORD PTR SS:[ESP],0xD
	RETN
}}

FCT_ASM ( caller_LoadMPPlayerCustomData_9 )
	PUSH DWORD PTR SS:[EDI]
	CALL LoadMPCustomData
	TEST EAX,EAX
	JNZ JMP_LoadMPlayerCustomData
	CMP DWORD PTR DS:[EDI],0
	JNZ Continue_LoadMP
	ADD DWORD PTR SS:[ESP],0x1D
Continue_LoadMP:
	RETN
JMP_LoadMPlayerCustomData:
	SUB DWORD PTR SS:[ESP],0x13
	RETN
}}


FCT_ASM ( caller_SendSaveFiles_111 )
	POP EAX
	PUSH DWORD PTR CS:[EAX+0x01] //"name"
	PUSH EAX
	JMP SendSaveFiles
}}

FCT_ASM ( caller_SendSaveFiles )
	POP EAX
	PUSH DWORD PTR CS:[EAX+0x0F] //"name"
	PUSH EAX
	JMP SendSaveFiles
}}



FCT_ASM ( caller_ReceiveSaveFiles_111 )
	PUSH ECX
	PUSH EDX
	LEA EBX,DWORD PTR DS:[EBP+4]
	PUSH EBX		//Message
	MOV EBX,DWORD PTR SS:[EBP]
	PUSH EBX		//ID client
	CALL ReceiveSaveFiles
	POP EDX
	POP ECX
	RETN
}}


FCT_ASM ( caller_ReceiveSaveFiles )
	PUSH ECX
	PUSH EDX
	LEA EDI,DWORD PTR DS:[ESI+4]
	PUSH EDI		//Message
	MOV EDI,DWORD PTR DS:[ESI]
	PUSH EDI		//ID client
	CALL ReceiveSaveFiles
	POP EDX
	POP ECX
	RETN
}}


FCT_ASM ( caller_BugFix109b )
	MOV EAX,DWORD PTR DS:[EDI+0xBD0]
	TEST EAX,EAX
	JE go_to_default
	MOV EAX,DWORD PTR SS:[ESP+0x20]
	MOV DWORD PTR SS:[ESP+0x24],EAX
	RETN
go_to_default:
	SUB DWORD PTR SS:[ESP],0x4B
	RETN
}}

FCT_ASM ( caller_BugFix109d )
	MOV EAX,DWORD PTR DS:[ESI+0xAB0]
	TEST EAX,EAX
	JE go_to_default
	MOV EAX,DWORD PTR SS:[ESP+0x20]
	MOV DWORD PTR SS:[ESP+0x24],EAX
	RETN
go_to_default:
	SUB DWORD PTR SS:[ESP],0x4B
	RETN
}}

// [Patch]
void Install_LoadPlayerData()
{
	static int isInstalled = false;
	if (isInstalled || !active_PlayerCustomData) return;

	log_msg("Patch D2Game & D2Client for load Player's custom data. (LoadPlayerData)\n");

	// Load SP player custom data.
	mem_seek(D2Game->GetOffsetByAddition(0x5046F, 0x5086F, 0x5CB0F, 0xBB8ED, 0x278CD, 0x465BD, 0x5638D, 0x3BCCD));
	memt_byte(0x8B, 0xE8);
	MEMT_REF4(0x75F685F0 , caller_LoadSPPlayerCustomData);
	memt_byte(0x16, 0x90);

	// Load MP player custom data.
	mem_seek(D2Game->GetOffsetByAddition(0x50790, 0x50B90, 0x5CC66, 0xBB777, 0x27757, 0x46447, 0x56217, 0x3BB57));
	memt_byte(0x83, 0xE8);
	MEMT_REF4(Game->Version >= VersionUtility::Versions::V111 ? 0x2174003B : Game->Version == VersionUtility::Versions::V110 ? 0x4674003F : 0x1D74003F, Game->Version >= VersionUtility::Versions::V111 ? caller_LoadMPPlayerCustomData_111 : Game->Version == VersionUtility::Versions::V110 ? caller_LoadMPPlayerCustomData: caller_LoadMPPlayerCustomData_9);

	// Send save files to Server.
	mem_seek(D2Client->GetOffsetByAddition(0xCF42, 0xCF32, 0xD5A2, 0x733FC, 0x5DFDC, 0x7933C, 0x1457C, 0xB638C));
	MEMJ_REF4(Fog->D2FogGetSavePath, Game->Version >= VersionUtility::Versions::V111 ? caller_SendSaveFiles_111 : caller_SendSaveFiles);

	// Receive save files from client.
	mem_seek(D2Game->GetOffsetByAddition(0x183A, 0x183A, 0x191A, 0x376E9, 0x703D9, 0x624D9, 0xCAF39, 0xD53E9));
	memt_byte(0x8B, 0xE8);
	if (Game->Version >= VersionUtility::Versions::V111 ) {
		MEMT_REF4(0xB60F005D, caller_ReceiveSaveFiles_111);
		memt_byte(0x45, 0x90);
		memt_byte(0x04, 0x90);
	}
	else
	{
		MEMT_REF4(0x04468A3E, caller_ReceiveSaveFiles);
	}

	if (Game->Version <= VersionUtility::Versions::V109d )
	{
		mem_seek(Fog->GetOffsetByAddition(0x47DE, 0x45AE, 0, 0, 0, 0, 0, 0));
		memt_byte(0x8B, 0xE8);
		MEMT_REF4(0x891C2444, Game->Version == VersionUtility::Versions::V109b ? caller_BugFix109b : caller_BugFix109d);
		memt_byte(0x44 ,0x90);
		memt_byte(0x24 ,0x90);
		memt_byte(0x20 ,0x90);
	}

	if (Game->Version == VersionUtility::Versions::V109b || Game->Version == VersionUtility::Versions::V109d)
	{
		customPackID -= 3;
	}
	else if (Game->Version == VersionUtility::Versions::V110)
	{
		customPackID--;
	}

	log_msg("\n");

	isInstalled = true;
}

