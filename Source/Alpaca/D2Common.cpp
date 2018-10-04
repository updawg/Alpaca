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
	D2Common10242 = (TD2Common10242)GetOffsetByProc(10242);
	D2InvAddItem = (TD2InvAddItem)GetOffsetByProc(10249);
	D2Common10250 = (TD2Common10250)GetOffsetByProc(10250);
	D2InventoryGetFirstItem = (TD2InventoryGetFirstItem)GetOffsetByProc(10277);
	D2UnitGetNextItem = (TD2UnitGetNextItem)GetOffsetByProc(10304);
	D2GetPosX = (TD2GetPosX)GetOffsetByProc(10326);
	D2GetPosY = (TD2GetPosY)GetOffsetByProc(10329);
	D2GetMaxGoldBank = (TD2GetMaxGoldBank)GetOffsetByProc(10339);
	D2InitPlayerData = (TD2InitPlayerData)GetOffsetByProc(10420);
	D2GetMaxGold = (TD2GetMaxGold)GetOffsetByProc(10439);
	D2ItemGetPage = (TD2ItemGetPage)GetOffsetByProc(10719);
	D2SetAnim = (TD2SetAnim)GetOffsetByProc(10734);
	D2SaveItem = (TD2SaveItem)GetOffsetByProc(10881);
	D2ReadFile = (TD2ReadFile)GetOffsetByAddition(0x738A4);
	D2Common10581 = (TD2Common10581)GetOffsetByProc(10581);
	D2Common10598 = (TD2Common10598)GetOffsetByProc(10598);
	D2Common10673 = (TD2Common10673)GetOffsetByProc(10673);
	D2CompileTxtFile = (TD2CompileTxtFile)compileTxtFile_9;
	D2AddPlayerStat = (TD2AddPlayerStat)D2AddPlayerStat_9;
	D2GetPlayerStat = (TD2GetPlayerStat)D2GetPlayerStat_9;
	D2GetRealItem = (TD2GetRealItem)GetOffsetByProc(10305);

	D2CompileTxtFileDirect = (TD2CompileTxtFile)GetOffsetByProc(10578);
	D2AddPlayerStatDirect = (TD2AddPlayerStat)GetOffsetByProc(10518);
	D2GetPlayerStatDirect = (TD2GetPlayerStat)GetOffsetByProc(10519);

	ptPYPlayerDataOffset = 0x5D;
	ptSpecificDataOffset = 0x70;
	ptGameOffset = 0xA4;
	ptClientGameOffset = 0x170;
	ptInventoryOffset = 0x84;
	ptSkillsOffset = 0xCC;
	ptImageOffset = 0x04;
	ptFrameOffset = 0x08;
}

char* D2Common::CompileTxtFileName = "D2CompileTxtFile";
char* D2Common::ErrorReadTxtFileName = "pbData";

__declspec(naked) void* __stdcall D2Common::compileTxtFile_9(DWORD unused, const char* filename, BINField* ptFields, DWORD* ptRecordCount, DWORD recordLength)
{
	_asm {
		SUB ESP, 0x210
		PUSH EBX
		PUSH EBP
		PUSH ESI
		PUSH EDI
		MOV ESI, DWORD PTR SS : [ESP + 0x228]
		MOV DWORD PTR SS : [ESP + 0x10], 0

		MOV EDI, wsprintf
		PUSH ESI
		LEA EAX, DWORD PTR SS : [ESP + 0x20]
		PUSH EAX
		CALL EDI
		ADD ESP, 8

		LEA EDX, DWORD PTR SS : [ESP + 0x10]
		PUSH 0
		PUSH CompileTxtFileName
		PUSH EDX
		MOV ECX, DWORD PTR SS : [ESP + 0x230]
		LEA EDX, DWORD PTR SS : [ESP + 0x28]
		CALL D2ReadFile
		TEST EAX, EAX
		JNZ continue_compileTxtFile
		PUSH 0
		PUSH CompileTxtFileName
		PUSH ErrorReadTxtFileName
		CALL Fog::D2FogAssertOld
		PUSH - 1
		CALL exit
		continue_compileTxtFile :
		MOV ECX, D2CompileTxtFileDirect
		ADD ECX, 0x305
		JMP ECX
	}
}

__declspec(naked) void D2Common::D2AddPlayerStat_9()
{
	__asm {
		PUSH DWORD PTR SS : [ESP + 0xC]
		PUSH DWORD PTR SS : [ESP + 0xC]
		PUSH DWORD PTR SS : [ESP + 0xC]
		CALL D2AddPlayerStatDirect
		RETN 0x10
	}
}

__declspec(naked) void D2Common::D2GetPlayerStat_9()
{
	__asm {
		PUSH DWORD PTR SS : [ESP + 0x8]
		PUSH DWORD PTR SS : [ESP + 0x8]
		CALL D2GetPlayerStatDirect
		RETN 0x0C
	}
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

D2Common::TD2Common10242 D2Common::D2Common10242;
D2Common::TD2InvAddItem D2Common::D2InvAddItem;
D2Common::TD2Common10250 D2Common::D2Common10250;
D2Common::TD2InventoryGetFirstItem D2Common::D2InventoryGetFirstItem;
D2Common::TD2UnitGetNextItem D2Common::D2UnitGetNextItem;
D2Common::TD2GetPosX D2Common::D2GetPosX;
D2Common::TD2GetPosY D2Common::D2GetPosY;
D2Common::TD2GetMaxGoldBank D2Common::D2GetMaxGoldBank;
D2Common::TD2InitPlayerData D2Common::D2InitPlayerData;
D2Common::TD2GetMaxGold D2Common::D2GetMaxGold;
D2Common::TD2CompileTxtFile D2Common::D2CompileTxtFileDirect;
D2Common::TD2ItemGetPage D2Common::D2ItemGetPage;
D2Common::TD2SetAnim D2Common::D2SetAnim;
D2Common::TD2SaveItem D2Common::D2SaveItem;
D2Common::TD2ReadFile D2Common::D2ReadFile;

D2Common::TD2Common10581 D2Common::D2Common10581;
D2Common::TD2Common10598 D2Common::D2Common10598;
D2Common::TD2Common10673 D2Common::D2Common10673;

D2Common::TD2AddPlayerStat D2Common::D2AddPlayerStatDirect;
D2Common::TD2GetPlayerStat D2Common::D2GetPlayerStatDirect;