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

#include "D2Common.h"
#include "Fog.h"

void D2Common::Init()
{
	Name = "D2Common.dll";
	Offset = LoadDiabloLibrary();
	SetFunctions();
}

void D2Common::SetFunctions()
{
	D2InvAddItem = (TD2InvAddItem)GetOffsetByProc(10963);
	D2InvRemoveItem = (TD2InvRemoveItem)GetOffsetByProc(10490);
	D2InventoryGetFirstItem = (TD2InventoryGetFirstItem)GetOffsetByProc(11040);
	D2UnitGetNextItem = (TD2UnitGetNextItem)GetOffsetByProc(10879);
	D2GetMaxGoldBank = (TD2GetMaxGoldBank)GetOffsetByProc(11025);
	D2InitPlayerData = (TD2InitPlayerData)GetOffsetByProc(10404);
	D2GetPlayerData = (TD2GetPlayerData)GetOffsetByProc(11103);
	D2GetMaxGold = (TD2GetMaxGold)GetOffsetByProc(11159);
	D2ItemGetPage = (TD2ItemGetPage)GetOffsetByProc(10810);
	D2SaveItem = (TD2SaveItem)GetOffsetByProc(10665);
	D2ReadFile = (TD2ReadFile)GetOffsetByAddition(0xB5E0);

	D2CompileTxtFile = (TD2CompileTxtFile)compileTxtFile_111;
	D2AddPlayerStat = (TD2AddPlayerStat)GetOffsetByProc(10645);
	D2GetPlayerStat = (TD2GetPlayerStat)GetOffsetByProc(10550);
	
	D2GetRealItem = (TD2GetRealItem)D2GetRealItem_111;

	D2CompileTxtFileDirect = (TD2CompileTxtFile)GetOffsetByProc(10037);
	D2AddPlayerStatDirect = (TD2AddPlayerStat)GetOffsetByProc(10645);
	D2GetPlayerStatDirect = (TD2GetPlayerStat)GetOffsetByProc(10550);

	ptPYPlayerDataOffset = 0x49;
	ptSpecificDataOffset = 0x14;
	ptGameOffset = 0x80;
	ptClientGameOffset = 0x1A8;
	ptInventoryOffset = 0x60;
	ptSkillsOffset = 0xA8;
	ptImageOffset = 0x34;
	ptFrameOffset = 0x0;
}

char* D2Common::CompileTxtFileName = "D2CompileTxtFile";
char* D2Common::ErrorReadTxtFileName = "pbData";

__declspec(naked) void* __stdcall D2Common::compileTxtFile_111(DWORD unused, const char* filename, BINField* ptFields, DWORD* ptRecordCount, DWORD recordLength)
{
	_asm {
		SUB ESP, 0x20C
		PUSH EBX
		PUSH EBP
		PUSH ESI
		PUSH EDI
		MOV DWORD PTR SS : [ESP + 0x10], 0
		MOV EBX, DWORD PTR SS : [ESP + 0x224]

		PUSH EBX
		LEA EAX, DWORD PTR SS : [ESP + 0x1C]
		PUSH EAX
		CALL DWORD PTR SS : [wsprintf]
		MOV EDX, DWORD PTR SS : [ESP + 0x228]
		ADD ESP, 8
		LEA EDX, DWORD PTR SS : [ESP + 0x10]
		PUSH EDX
		PUSH EAX
		LEA EAX, DWORD PTR SS : [ESP + 0x20]
		CALL D2ReadFile
		TEST EAX, EAX
		JNZ continue_compileTxtFile
		PUSH __LINE__
		CALL Fog::D2GetInstructionPointer
		PUSH EAX
		PUSH ErrorReadTxtFileName
		CALL Fog::D2FogAssert
		ADD ESP, 0xC
		PUSH - 1
		CALL exit
		continue_compileTxtFile :
		MOV ECX, D2CompileTxtFileDirect
			ADD ECX, 0x1EC
			JMP ECX
	}
}

Unit* __stdcall	D2Common::D2GetRealItem_111(Unit* ptItem)
{
	return ptItem;
}

D2Common::TD2CompileTxtFile D2Common::D2CompileTxtFile;
D2Common::TD2AddPlayerStat D2Common::D2AddPlayerStat;
D2Common::TD2GetPlayerStat D2Common::D2GetPlayerStat;
D2Common::TD2GetRealItem D2Common::D2GetRealItem;

DWORD D2Common::ptPYPlayerDataOffset;
DWORD D2Common::ptSpecificDataOffset;
DWORD D2Common::ptGameOffset;
DWORD D2Common::ptClientGameOffset;
DWORD D2Common::ptInventoryOffset;
DWORD D2Common::ptSkillsOffset;
DWORD D2Common::ptImageOffset;
DWORD D2Common::ptFrameOffset;

D2Common::TD2InvAddItem D2Common::D2InvAddItem;
D2Common::TD2InvRemoveItem D2Common::D2InvRemoveItem;
D2Common::TD2InventoryGetFirstItem D2Common::D2InventoryGetFirstItem;
D2Common::TD2UnitGetNextItem D2Common::D2UnitGetNextItem;
D2Common::TD2GetMaxGoldBank D2Common::D2GetMaxGoldBank;
D2Common::TD2InitPlayerData D2Common::D2InitPlayerData;
D2Common::TD2GetPlayerData D2Common::D2GetPlayerData;
D2Common::TD2GetMaxGold D2Common::D2GetMaxGold;
D2Common::TD2CompileTxtFile D2Common::D2CompileTxtFileDirect;
D2Common::TD2ItemGetPage D2Common::D2ItemGetPage;
D2Common::TD2SaveItem D2Common::D2SaveItem;
D2Common::TD2ReadFile D2Common::D2ReadFile;

D2Common::TD2AddPlayerStat D2Common::D2AddPlayerStatDirect;
D2Common::TD2GetPlayerStat D2Common::D2GetPlayerStatDirect;