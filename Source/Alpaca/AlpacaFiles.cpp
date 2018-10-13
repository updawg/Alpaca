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

#include "AlpacaFiles.h"
#include "common.h"
#include <stdio.h>

extern bool active_multiPageStash;
extern bool active_sharedStash;

void* stashBtnsImages = NULL;
void* sharedGoldBtnsImages = NULL;

DWORD __stdcall isModFile (char* filename)
{
	if (strstr(filename, modDataDirectory) )
	{
		char fileTemp[0x104];
		log_msg("Loading Custom File : %s", filename);
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

void Install_AlpacaFiles()
{
	static int isInstalled = false;
	if (isInstalled) return;

	log_msg("[Patch] Storm to find custom file. (AlpacaFiles)\n");

	DWORD FindCustomFileOffset = Storm::GetOffsetByAddition(0x192C6);

	// Try in Diablo II\Alpaca\ if file not found
	mem_seek(FindCustomFileOffset);
	memt_byte(0xFF, 0x90);
	memt_byte(0x15, 0xE8);
	MEMD_REF4(LeaveCriticalSection, caller_isModFile);

	log_msg("\n" );

	isInstalled = true;
}

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

void __stdcall loadCustomImages()
{
	if ( active_multiPageStash ) loadImagesFile(&stashBtnsImages, "StashBtns");
	if ( active_sharedStash)		 loadImagesFile(&sharedGoldBtnsImages, "SharedGoldBtns");
}

#define freeImagesFile(I) if(I) {D2FreeImage(I);I=NULL;}

void __stdcall freeCustomImages()
{
	freeImagesFile(stashBtnsImages);
	freeImagesFile(sharedGoldBtnsImages);
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

void Install_AlpacaImagesFiles()
{
	static int isInstalled = false;
	if (isInstalled) return;

	Install_AlpacaFiles();

	log_msg("[Patch] D2Client to load/free custom images. (AlpacaImagesFiles)\n");

	DWORD LoadCustomImageOffset = D2Client::GetOffsetByAddition(0x57E21);
	DWORD FreeCustomImageOffset = D2Client::GetOffsetByAddition(0x57FA9);

	// Load custom images
	mem_seek(LoadCustomImageOffset);
	memt_byte(0xB9, 0xE8);
	MEMT_REF4(0xC, caller_loadCustomImages);

	// Free custom images
	mem_seek(FreeCustomImageOffset);
	memt_byte(0xB9, 0xE8);
	MEMT_REF4(0xC, caller_freeCustomImages);

	log_msg("\n");

	isInstalled = true;
}