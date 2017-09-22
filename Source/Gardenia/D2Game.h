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

#pragma once

#include "Library.h"

class D2Game : public Library<D2Game>
{
public:
	static void Init();

	typedef void(__fastcall *TD2SetNbPlayers) (DWORD nbPlayers);
	typedef DWORD(__fastcall *TD2SendPacket) (void* ptNetClient, LPVOID pData, DWORD size);
	typedef DWORD(__stdcall *TD2LinkPortal) (GameStruct* ptGame, Unit* ptObject, DWORD levelEndID, DWORD levelStartID);
	typedef DWORD(__fastcall *TD2VerifIfNotCarry1) (Unit* ptItem, ItemsBIN* itemsData, Unit* ptFirstItem);
	typedef DWORD(__fastcall *TD2LoadInventory) (GameStruct* ptGame, Unit* pChar, saveBitField* pdata, DWORD p2, DWORD maxSize, DWORD p4, DWORD *ptNbBytesRead);
	typedef Unit* (__fastcall *TD2GameGetObject) (GameStruct* ptGame, DWORD type, DWORD itemNum);
	typedef void(__stdcall *TD2SaveGame) (GameStruct* ptGame);

	// Until 1.10
	typedef NetClient* (__fastcall *TD2GetClient) (Unit* ptUnit, char* lpszErrFile, DWORD ErrLine);

	static TD2SetNbPlayers D2SetNbPlayers;
	static TD2SendPacket D2SendPacket();
	static TD2LinkPortal D2LinkPortal;
	static TD2VerifIfNotCarry1 D2VerifIfNotCarry1();
	static TD2LoadInventory D2LoadInventory();
	static TD2GameGetObject D2GameGetObject();
	static TD2SaveGame D2SaveGame();

	static TD2GetClient D2GetClient();
	static NetClient** ptClientTable;
private:
	static void SetFunctions();

	static TD2SaveGame GetD2SaveGameOffset();
	static void D2SaveGame_1XX();

	static void D2Game::D2GetClient_111();

	static TD2SendPacket D2SendPacketDirect;
	static void D2SendPacket_111();

	static TD2LoadInventory D2LoadInventoryDirect;
	static void D2LoadInventory_111();

	static TD2VerifIfNotCarry1 D2VerifIfNotCarry1Direct;
	static void D2VerifIfNotCarry1_111();

	static TD2GameGetObject D2GameGetObjectDirect;
	static void D2GameGetObject_111();
};