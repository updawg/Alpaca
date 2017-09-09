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

void __stdcall BtnPress()
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

void Install_VariableOnRealm()
{
	static int isInstalled = false;
	if (isInstalled) return;

	log_msg("[Patch] D2Launch for disabling online buttons. (VariableonRealm)\n");

	// click on Battle.net button
	mem_seek(D2Launch::GetOffsetByAddition(0x8195, 0x11C65));
	memt_byte(0x81, 0xE8);
	MEMT_REF4(0x400EC, caller_BnetBtnPress);
	memt_byte(0, 0x90);

	// click on TCP/IP button
	mem_seek(D2Launch::GetOffsetByAddition(0x87B9, 0x1053E));
	if (VersionUtility::Is113D())
	{
		memt_byte(0xBE, 0xE8);
		MEMT_REF4(0x40, caller_TCPIPBtnPress111);
	}
	else
	{
		memt_byte(0xBD, 0xE8);
		MEMT_REF4(1, caller_TCPIPBtnPress);
	}

	// click on SinglePlayer button
	mem_seek(D2Launch::GetOffsetByAddition(0xD1F6, 0xA906));
	memt_byte(0xBA, 0xE8);
	MEMT_REF4(0x400, caller_SinglePlayerBtnPress);

	log_msg("\n");

	isInstalled = true;
}