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

void D2Game::Init()
{
	Name = "D2Game.dll";
	Offset = LoadDiabloLibrary();
	SetFunctions();
}

void D2Game::SetFunctions()
{
	D2SetNbPlayers = (TD2SetNbPlayers)GetOffsetByProc(10059, 10002);
	D2SendPacket = (TD2SendPacket)GetOffsetByAddition(0xC380, 0xDB780);
	D2LinkPortal = (TD2LinkPortal)GetOffsetByAddition(0, 0x15F40);
	D2VerifIfNotCarry1 = (TD2VerifIfNotCarry1)GetOffsetByAddition(0, 0xB2F70);
	D2TestPositionInRoom = (TD2TestPositionInRoom)GetOffsetByAddition(0, 0x1340);
	D2LoadInventory = (TD2LoadInventory)GetOffsetByAddition(0x4F100, 0x3A4C0);
	D2GameGetObject = (TD2GameGetObject)GetOffsetByAddition(0x7BAE0, 0x6DC40);
	D2GetClient = (TD2GetClient)GetOffsetByAddition(0x7C2C0, 0);

	ptClientTable = (NetClient**)GetOffsetByAddition(0xF2A80, 0x1105E0);
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

D2Game::TD2SetNbPlayers D2Game::D2SetNbPlayers;
D2Game::TD2SendPacket D2Game::D2SendPacket;
D2Game::TD2LinkPortal D2Game::D2LinkPortal;
D2Game::TD2VerifIfNotCarry1 D2Game::D2VerifIfNotCarry1;
D2Game::TD2TestPositionInRoom D2Game::D2TestPositionInRoom;
D2Game::TD2LoadInventory D2Game::D2LoadInventory;
D2Game::TD2GameGetObject D2Game::D2GameGetObject;

D2Game::TD2GetClient D2Game::D2GetClient;
NetClient** D2Game::ptClientTable;