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

#include "bigStash.h" // active_bigStash_tested
#include "common.h"
#include <stdio.h>

bool onRealm=false;
bool needToInit=false;
int previouslyOnRealm = -1;

void STDCALL BtnPress()
{
	needToInit = 1;
	d2_assert(active_bigStash_tested && onRealm && (previouslyOnRealm==0), "Need to restart after play an open game with the Big Stash",__FILE__,__LINE__);
	d2_assert(active_bigStash_tested && !onRealm && (previouslyOnRealm>0), "Need to restart after play an closed game with the Big Stash",__FILE__,__LINE__);
	previouslyOnRealm = onRealm;
}

FCT_ASM ( caller_BnetBtnPress )
	CMP active_DisableBattleNet,1
	JE disableBattleNet
	MOV onRealm,1
	PUSH EAX
	CALL BtnPress
	POP EAX
	SUB ESP,0x3FC //400
	JMP DWORD PTR SS:[ESP+0x3FC]
disableBattleNet:
	POP EAX
	RETN
}}

FCT_ASM ( caller_TCPIPBtnPress111 )
	MOV onRealm,0
	CALL BtnPress
	MOV ESI,0x40
	RETN
}}

FCT_ASM ( caller_TCPIPBtnPress )
	MOV onRealm,0
	CALL BtnPress
	MOV EBP,1
	RETN
}}

FCT_ASM ( caller_SinglePlayerBtnPress )
	MOV onRealm,0
	CALL BtnPress
	MOV EDX,0x400
	RETN
}}


FCT_ASM ( caller_fixClientRemovingBug )
	TEST ECX,ECX
	JE notFound
	CMP DWORD PTR DS:[ECX],EBP
	JE found
next:
	MOV EAX,ECX
	MOV ECX,DWORD PTR DS:[EAX+0x4A8]
	TEST ECX,ECX
	JE notFound
	CMP DWORD PTR DS:[ECX],EBP
	JNZ next
found:
	ADD DWORD PTR SS:[ESP],0xB
	RETN
notFound:
	ADD DWORD PTR SS:[ESP],0x1D
	RETN
}}

// [Patch]
void Install_VariableOnRealm()
{
	static int isInstalled = false;
	if (isInstalled) return;

	log_msg("Patch D2Launch for disabling online buttons. (VariableonRealm)\n");

	// click on Battle.net button
	mem_seek(D2Launch->GetOffsetByAddition(0x8195, 0x81A5, 0x9915, 0x129E5, 0x18AA5, 0x17D15, 0x19295, 0x11C65));
	memt_byte(0x81, 0xE8);
	MEMT_REF4(0x000400EC, caller_BnetBtnPress);
	memt_byte(0, 0x90);

	// click on TCP/IP button
	mem_seek(D2Launch->GetOffsetByAddition(0x87B9, 0x87C9, 0x9F99, 0x11329, 0x17409, 0x16659, 0x17B8E, 0x1053E));
	if (Game->Version == VersionUtility::Versions::V109b || Game->Version == VersionUtility::Versions::V109d || Game->Version == VersionUtility::Versions::V110)
	{
		memt_byte(0xBD, 0xE8);
		MEMT_REF4(1, caller_TCPIPBtnPress);
	}
	else
	{
		memt_byte(0xBE, 0xE8);
		MEMT_REF4(0x40, caller_TCPIPBtnPress111);
	}

	// click on SinglePlayer button
	mem_seek(D2Launch->GetOffsetByAddition(0xD1F6, 0xD1E6, 0xEC16, 0xB726, 0x117E6, 0x10A56, 0x11F36, 0xA906));
	memt_byte(0xBA, 0xE8);
	MEMT_REF4(0x400, caller_SinglePlayerBtnPress);

	if (Game->Version == VersionUtility::Versions::V110)
	{
		log_msg("\nPatch D2Game for fixing ptClient removing bug. (VariableonRealm)\n");
		//Bug crash ptClient search fix (for Megalixir Mod).
		mem_seek(D2Game->GetOffsetByAddition(0, 0, 0x2B97, 0, 0, 0, 0, 0));
		memt_byte(0x39, 0xE8);
		MEMT_REF4(0x8B0C7429, caller_fixClientRemovingBug);
		memt_byte(0xC1, 0x90);
	}

	log_msg("\n");

	isInstalled = true;
}