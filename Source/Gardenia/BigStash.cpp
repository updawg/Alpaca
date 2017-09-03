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

#include "plugYFiles.h"		// Install_PlugYFiles()
#include "common.h"
#include "Utilities\LibraryUtility.h"

extern LibraryUtility* lu;

using Versions = VersionUtility::Versions;

bool active_bigStash = false;
bool active_bigStash_tested = false;

const char* tradeStash_RefFile= "%s\\TradeStash";
const BYTE gridX_BB = 10;
const BYTE gridY_BB = 10;
const DWORD gridLeft_BB = 16;
const DWORD gridRight_BB = 302;
const DWORD gridTop_BB = 82;
const DWORD gridbottom_BB = 371;

InventoryBIN* STDCALL modifStashGrid(InventoryBIN* ptInventoryBin)
{
	active_bigStash_tested = true;
	if ( onRealm || !active_bigStash) return ptInventoryBin;

	InventoryBIN* inventory=ptInventoryBin+12;
	inventory->gridX = gridX_BB;
	inventory->gridY = gridY_BB;
	inventory->gridLeft = gridLeft_BB;
	inventory->gridRight = gridRight_BB;
	inventory->gridTop = gridTop_BB;
	inventory->gridBottom = gridbottom_BB;

	inventory = ptInventoryBin+28;
	inventory->gridX = gridX_BB;
	inventory->gridY = gridY_BB;
	inventory->gridLeft = gridLeft_BB + 80;
	inventory->gridRight = gridRight_BB + 80;
	inventory->gridTop = gridTop_BB + 60;
	inventory->gridBottom = gridbottom_BB + 60;

	return ptInventoryBin;
}


FCT_ASM ( caller_modifStashGrid )
	POP ESI
	CALL D2CompileTxtFile
	PUSH EAX
	CALL modifStashGrid
	JMP ESI
}}

FCT_ASM ( caller_changeTradeStash )
	CMP onRealm,0
	JNZ normalTradeStash
	MOV EAX,modDataDirectory
	MOV DWORD PTR SS:[ESP+0x8],EAX
	MOV EAX,tradeStash_RefFile
	MOV DWORD PTR SS:[ESP+0x4],EAX
normalTradeStash:
	POP EAX
	PUSH 0x104
	JMP EAX
}}


void Install_BigStash()
{
	static int isInstalled = false;
	if (isInstalled) return;

	Install_PlugYFiles();

	log_msg("Patch D2Common & D2Client for make 10x10 squares in the stash. (BigStash)\n");

	// modification of stash grid
	mem_seek(lu->D2Common->RetrieveStashGridOffset());
	MEMC_REF4(D2CompileTxtFile, caller_modifStashGrid);
	//01B64ED2  |. E8 99AEFFFF    CALL D2Common.#10578
	//6FDAFCB4  |. E8 A7C3FCFF    CALL D2Common.#10653
	//6FD7A504  |. E8 5743FEFF    CALL D2Common.#10496                     ; \#10496
	//6FD6BDB4  |. E8 97600200    CALL D2Common.#10244                     ; \#10244
	//6FDD2CA4  |. E8 97C2FDFF    CALL D2Common.#10849                     ; \#10849
	//6FDBCC24  |. E8 B7FEF9FF    CALL D2Common.#10037                     ; \#10037

	// modification of stash background
	mem_seek(lu->D2Client->RetrieveStashBackgroundOffset());
	memt_byte( 0x68, 0xE8 );	// CALL caller_changeTradeStash
	MEMT_REF4( 0x00000104, caller_changeTradeStash);
	//6FAEC61C  |. 68 04010000    PUSH 104
	//6FB5643C  |. 68 04010000    PUSH 104
	//6FB249BC  |. 68 04010000    PUSH 104
	//6FB59D7C  |. 68 04010000    PUSH 104
	//6FB3CC1C  |. 68 04010000    PUSH 104
	//6FB443FC  |. 68 04010000    PUSH 104

	log_msg("\n");

	isInstalled = true;
}

