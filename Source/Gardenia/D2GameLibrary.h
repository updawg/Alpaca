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

class D2GameLibrary : public Library
{
public:
	D2GameLibrary(int gameVersion);

	typedef void(__fastcall *TD2SetNbPlayers) (DWORD nbPlayers);
	typedef DWORD(__fastcall *TD2SendPacket) (void* ptNetClient, LPVOID pData, DWORD size);
	typedef void(__fastcall *TD2SetSkillBaseLevelOnClient) (void* ptClient, Unit* ptChar, DWORD skillID, DWORD sLvl, DWORD bRemove);
	typedef DWORD(__stdcall *TD2LinkPortal) (GameStruct* ptGame, Unit* ptObject, DWORD levelEndID, DWORD levelStartID);
	typedef DWORD(__fastcall *TD2VerifIfNotCarry1) (Unit* ptItem, ItemsBIN* itemsData, Unit* ptFirstItem);
	typedef Room* (__fastcall *TD2TestPositionInRoom) (Room* ptRoom, DWORD x, DWORD y);
	typedef DWORD(__fastcall *TD2LoadInventory) (GameStruct* ptGame, Unit* pChar, saveBitField* pdata, DWORD p2, DWORD maxSize, DWORD p4, DWORD *ptNbBytesRead);
	typedef Unit* (__fastcall *TD2GameGetObject) (GameStruct* ptGame, DWORD type, DWORD itemNum);
	typedef void(__stdcall *TD2SaveGame) (GameStruct* ptGame);

	TD2SetNbPlayers D2SetNbPlayers;
	TD2SendPacket D2SendPacket;
	TD2SetSkillBaseLevelOnClient D2SetSkillBaseLevelOnClient;
	TD2LinkPortal D2LinkPortal;
	TD2VerifIfNotCarry1 D2VerifIfNotCarry1;
	TD2TestPositionInRoom D2TestPositionInRoom;
	TD2LoadInventory D2LoadInventory;
	TD2GameGetObject D2GameGetObject;
	TD2SaveGame D2SaveGame;

	// Until 1.10
	typedef NetClient* (__fastcall *TD2GetClient) (Unit* ptUnit, char* lpszErrFile, DWORD ErrLine);

	TD2GetClient D2GetClient;

	// Variables
	NetClient** ptClientTable;
	 
	// _declspec (naked) functions (Our custom/wrapper function)
	static void D2SaveGame_1XX();
	static TD2SaveGame VD2SaveGame;
private:
	void SetFunctions();
};