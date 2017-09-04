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

#include "plugYFiles.h"
#include "common.h"
#include <stdio.h>

extern bool active_newInterfaces;
extern bool active_multiPageStash;
extern bool active_sharedGold;

void* stashBtnsImages = NULL;
void* newStatsInterfaceImages = NULL;
void* statsBackgroundImages = NULL;
void* sharedGoldBtnsImages = NULL;

DWORD STDCALL isModFile (char* filename)
{
	if (strstr(filename, modDataDirectory) )
	{
		char fileTemp[0x104];
		log_msg("Load custom file : %s", filename);
		strcpy(fileTemp,filename);
		D2FogGetInstallPath(filename,0x104-strlen(filename));
		strcat(filename,fileTemp);
		log_msg("-> %s\n\n", filename);
		if ((GetFileAttributesA(filename) & 0x10) == 0)
			return true;
	}
	return false;
}


FCT_ASM ( caller_isModFile )
	TEST ESI,ESI
	JNZ ISNOTMODDATA
	MOV EBP, DWORD PTR SS:[ESP+0x140]
	PUSH EBP
	CALL isModFile
	TEST EAX,EAX
	JE ISNOTMODDATA
	MOV BL, BYTE PTR SS:[ESP+0x144]
	POP EAX
	POP EAX
	MOV EAX,D2StormMPQOpenFile
	ADD EAX,0x9A
	JMP EAX
ISNOTMODDATA:
	JMP DWORD PTR CS:[LeaveCriticalSection]
}}

FCT_ASM ( caller_isModFile_111 )
	TEST EDI,EDI
	JNZ ISNOTMODDATA
	MOV ESI, DWORD PTR SS:[ESP+0x130]
	PUSH ESI
	CALL isModFile
	TEST EAX,EAX
	JE ISNOTMODDATA
	MOV BL, BYTE PTR SS:[ESP+0x134]
	POP EAX
	POP EAX
	MOV EAX,D2StormMPQOpenFile
	ADD EAX,0xBD
	MOV EBP,GetFileAttributesA
	JMP EAX
ISNOTMODDATA:
	JMP DWORD PTR CS:[LeaveCriticalSection]
}}

// [Patch]
void Install_PlugYFiles()
{
	static int isInstalled = false;
	if (isInstalled) return;

	log_msg("Patch Storm to found custom file. (PlugYFiles)\n");

	// Try in Diablo II\Gardenia\ if file not found
	mem_seek(Storm->GetOffsetByAddition(0x192C6, 0x19296, 0x18677, 0x2CC69, 0x14259, 0x121E9, 0x28D89, 0x2DA79));
	memt_byte(0xFF, 0x90);
	memt_byte(0x15, 0xE8);
	MEMD_REF4(LeaveCriticalSection, Game->Version >= VersionUtility::Versions::V111 ? caller_isModFile_111 : caller_isModFile);

	log_msg("\n" );

	isInstalled = true;
}

/****************************************************************************************************/


void loadImagesFile(void** images, const char* name)
{
	if(!images || !name) return;
	if(!*images)
	{
		char buffer[MAX_PATH];
		sprintf(buffer, "%s\\%s", modDataDirectory, name);

		*images = D2LoadImage(buffer,0);
		if (!*images)
		{
			sprintf(buffer, "Don't find Buttons Images File : %s.dc6", name);
			d2_assert(!*images, buffer, __FILE__, __LINE__);
		}
	}
}

void STDCALL loadCustomImages()
{
	if ( active_multiPageStash || active_newInterfaces) loadImagesFile(&stashBtnsImages, "StashBtns");
	if ( active_sharedGold)		 loadImagesFile(&sharedGoldBtnsImages, "SharedGoldBtns");
	if ( active_newInterfaces )	 loadImagesFile(&newStatsInterfaceImages, "EmptyPage");	
	if ( active_newInterfaces )	 loadImagesFile(&statsBackgroundImages, "StatsBackground");	
}

#define freeImagesFile(I) if(I) {D2FreeImage(I);I=NULL;}

void STDCALL freeCustomImages()
{
	freeImagesFile(stashBtnsImages);
	freeImagesFile(sharedGoldBtnsImages);
	freeImagesFile(newStatsInterfaceImages);
	freeImagesFile(statsBackgroundImages);
}

FCT_ASM ( caller_loadCustomImages )
	CALL loadCustomImages
	MOV ECX,0x0C
	RETN
}}

FCT_ASM ( caller_freeCustomImages )
	CALL freeCustomImages
	MOV ECX,0x0C
	RETN
}}

// [Patch]
void Install_PlugYImagesFiles()
{
	static int isInstalled = false;
	if (isInstalled) return;

	Install_PlugYFiles();

	log_msg("Patch D2Client to load/free custom images. (PlugYImagesFiles)\n");

	// Load custom images
	mem_seek(D2Client->GetOffsetByAddition(0x57E21, 0x57E21, 0x5E4B1, 0x2E101, 0xB67E1, 0x82761, 0x27EAE, 0x6E0BE));
	memt_byte(0xB9 ,0xE8);
	MEMT_REF4(0xC, caller_loadCustomImages);

	// Free custom images
	mem_seek(D2Client->GetOffsetByAddition(0x57FA9, 0x57FA9, 0x5E639, 0x2D12D, 0xB580D, 0x8158D, 0x26F8D, 0x6D07D));
	memt_byte(0xB9 ,0xE8);
	MEMT_REF4(0xC, caller_freeCustomImages);

	log_msg("\n" );

	isInstalled = true;
}


/****************************************************************************************************/

void loadStatsInterfaceDesc(DWORD mempool);
void freeStatsInterfaceDesc();



void FASTCALL loadTxtFiles(DWORD mempool)
{
	loadStatsInterfaceDesc(mempool);
}

void FASTCALL freeTxtFiles()
{
	freeStatsInterfaceDesc();
}

FCT_ASM ( caller_loadTxtFiles_111 )
	MOV ECX,DWORD PTR SS:[ESP+4]
	CALL loadTxtFiles
	JMP D2LoadSuperuniques
}}

FCT_ASM ( caller_loadTxtFiles )
	PUSH ECX
	CALL loadTxtFiles
	POP ECX
	JMP D2LoadSuperuniques
}}

FCT_ASM ( caller_freeTxtFiles )
	CALL freeTxtFiles
	JMP D2Fog10212
}}

// [Patch]
void Install_PlugYTxtFiles()
{
	static int isInstalled = false;
	if (isInstalled) return;

	Install_PlugYFiles();

	log_msg("Patch D2Common to load/free custom txt files. (PlugYTxtFiles)\n");

	// Load custom txt files
	mem_seek(D2Common->GetOffsetByAddition(0x7F4B, 0x7F4B, 0x2F7D7, 0x76854, 0x37444, 0x81C44, 0x5D6E4, 0x855E4));
	MEMC_REF4(D2Common->D2LoadSuperuniques, Game->Version >= VersionUtility::Versions::V111 ? caller_loadTxtFiles_111 : caller_loadTxtFiles );
	//6FD47F4A  |. E8 B1750100    CALL D2Common.6FD5F500
	//6FD47F4A  |. E8 C1750100    CALL D2Common.6FD5F510
	//01B6F7D6  |. E8 C5A7FFFF    CALL D2Common.01B69FA0
	//6FDC6853  |. E8 58B6FFFF    CALL D2Common.6FDC1EB0                   ; \D2Common.6FDC1EB0
	//6FD87443  |. E8 58B6FFFF    CALL D2Common.6FD82AA0                   ; \D2Common.6FD82AA0
	//6FDD1C43  |. E8 58B6FFFF    CALL D2Common.6FDCD2A0                   ; \D2Common.6FDCD2A0
	//6FDAD6E3  |. E8 88C1FFFF    CALL D2Common.6FDA9870                   ; \D2Common.6FDA9870
	//6FDD55E3  |. E8 58B6FFFF    CALL D2Common.6FDD0C40                   ; \D2Common.6FDD0C40

	// Free custom txt files
	mem_seek(D2Common->GetOffsetByAddition(0x79EC, 0x79EC, 0x10186, 0x332B3, 0x15AB3, 0x44E13, 0x5E8B3, 0xFAA3));
	MEMJ_REF4(Fog->D2Fog10212, caller_freeTxtFiles);

	log_msg("\n" );

	isInstalled = true;
}


