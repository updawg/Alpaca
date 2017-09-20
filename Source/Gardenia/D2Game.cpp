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

#include "D2Game.h"
#include "D2Common.h"

void D2Game::Init()
{
	Name = "D2Game.dll";
	Offset = LoadDiabloLibrary();
	SetFunctions();
}

void D2Game::SetFunctions()
{
	D2SetNbPlayers = (TD2SetNbPlayers)GetOffsetByProc(10059, 10002);
	D2LinkPortal = (TD2LinkPortal)GetOffsetByAddition(0, 0x15F40);

	ptClientTable = (NetClient**)GetOffsetByAddition(0xF2A80, 0x1105E0);

	D2SendPacketDirect = (TD2SendPacket)GetOffsetByAddition(0xC380, 0xDB780);
	D2LoadInventoryDirect = (TD2LoadInventory)GetOffsetByAddition(0x4F100, 0x3A4C0);
	D2VerifIfNotCarry1Direct = (TD2VerifIfNotCarry1)GetOffsetByAddition(0, 0xB2F70);
	D2GameGetObjectDirect = (TD2GameGetObject)GetOffsetByAddition(0x7BAE0, 0x6DC40);
}

D2Game::TD2SaveGame D2Game::D2SaveGame()
{
	if (VersionUtility::Is113D())
	{
		return GetD2SaveGameOffset();
	}
	else
	{
		return (TD2SaveGame)D2SaveGame_1XX;
	}
}

D2Game::TD2SaveGame D2Game::GetD2SaveGameOffset()
{
	return (TD2SaveGame)GetOffsetByAddition(0, 0xBE660);
}

__declspec (naked) void D2Game::D2SaveGame_1XX()
{
	__asm {
		POP EAX
		POP ECX
		PUSH EAX
		JMP GetD2SaveGameOffset
	};
}

D2Game::TD2GetClient D2Game::D2GetClient()
{
	if (VersionUtility::Is113D())
	{
		return (TD2GetClient)D2GetClient_111;
	}
	else
	{
		return (TD2GetClient)GetOffsetByAddition(0x7C2C0, 0);
	}
}

__declspec (naked) void D2Game::D2GetClient_111()
{
	__asm {
		PUSH ECX
		CALL D2Common::D2GetPlayerData
		MOV EAX, DWORD PTR DS : [EAX + 0x9C]
		RETN 4
	}
}

D2Game::TD2SendPacket D2Game::D2SendPacket()
{
	if (VersionUtility::Is113D())
	{
		return (TD2SendPacket)D2SendPacket_111;
	}
	else
	{
		return D2SendPacketDirect;
	}
}

__declspec (naked) void D2Game::D2SendPacket_111()
{
	__asm {
		POP EAX
		PUSH EDX
		PUSH EAX
		MOV EAX,ECX
		JMP D2SendPacketDirect
	}
}

D2Game::TD2LoadInventory D2Game::D2LoadInventory()
{
	if (VersionUtility::Is113D())
	{
		return (TD2LoadInventory)D2LoadInventory_111;
	}
	else
	{
		return D2LoadInventoryDirect;
	}
}

__declspec (naked) void D2Game::D2LoadInventory_111()
{
	__asm {
		MOV EAX, DWORD PTR SS : [ESP + 4]
		MOV DWORD PTR SS : [ESP + 4], EDX
		JMP D2LoadInventoryDirect
	}
}


D2Game::TD2VerifIfNotCarry1 D2Game::D2VerifIfNotCarry1()
{
	if (VersionUtility::Is113D())
	{
		return (TD2VerifIfNotCarry1)D2VerifIfNotCarry1_111;
	}
	else
	{
		return D2VerifIfNotCarry1Direct;
	}
}

__declspec (naked) void D2Game::D2VerifIfNotCarry1_111()
{
	__asm {
		PUSH EBX
		PUSH ECX
		MOV EBX,EDX
		MOV EAX,DWORD PTR SS : [ESP + 0xC]
		CALL D2VerifIfNotCarry1Direct
		POP EBX
		RETN 4
	}
}


D2Game::TD2GameGetObject D2Game::D2GameGetObject()
{
	if (VersionUtility::Is113D())
	{
		return (TD2GameGetObject)D2GameGetObject_111;
	}
	else
	{
		return D2GameGetObjectDirect;
	}
}

__declspec (naked) void D2Game::D2GameGetObject_111()
{
	__asm {
		MOV EAX,EDX
		MOV EDX,DWORD PTR SS : [ESP + 4]
		CALL D2GameGetObjectDirect
		RETN 4
	}
}

D2Game::TD2SetNbPlayers D2Game::D2SetNbPlayers;
D2Game::TD2LinkPortal D2Game::D2LinkPortal;

NetClient** D2Game::ptClientTable;

D2Game::TD2SendPacket D2Game::D2SendPacketDirect;
D2Game::TD2LoadInventory D2Game::D2LoadInventoryDirect;
D2Game::TD2VerifIfNotCarry1 D2Game::D2VerifIfNotCarry1Direct;
D2Game::TD2GameGetObject D2Game::D2GameGetObjectDirect;