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

#include "FogLibrary.h"

FogLibrary::FogLibrary(int gameVersion) : Library()
{
	Name = "Fog.dll";
	Version = gameVersion;
	Offset = LoadDiabloLibrary();
	SetFunctions();
}

void FogLibrary::SetFunctions()
{
	D2FogAssertOld = (TD2FogAssertOld)GetOffsetByProc(10023, 10023, 10023, 0, 0, 0, 0, 0);
	D2FogAssert = (TD2FogAssert)GetOffsetByProc(0, 0, 0, 10024, 10024, 10024, 10024, 10024);
	D2FogMemAlloc = (TD2FogMemAlloc)GetOffsetByProc(10042, 10042, 10042, 10042, 10042, 10042, 10042, 10042);
	D2FogMemDeAlloc = (TD2FogMemDeAlloc)GetOffsetByProc(10043, 10043, 10043, 10043, 10043, 10043, 10043, 10043);
	D2AllocMem = (TD2AllocMem)GetOffsetByProc(10045, 10045, 10045, 10045, 10045, 10045, 10045, 10045);
	D2FreeMem = (TD2FreeMem)GetOffsetByProc(10046, 10046, 10046, 10046, 10046, 10046, 10046, 10046);
	D2MPQOpenFile = (TD2MPQOpenFile)GetOffsetByProc(10102, 10102, 10102, 10102, 10102, 10102, 10102, 10102);
	D2MPQCloseFile = (TD2MPQCloseFile)GetOffsetByProc(10103, 10103, 10103, 10103, 10103, 10103, 10103, 10103);
	D2MPQReadFile = (TD2MPQReadFile)GetOffsetByProc(10104, 10104, 10104, 10104, 10104, 10104, 10104, 10104);
	D2MPQGetSizeFile = (TD2MPQGetSizeFile)GetOffsetByProc(10105, 10105, 10105, 10105, 10105, 10105, 10105, 10105);
	D2FogGetSavePath = (TD2FogGetSavePath)GetOffsetByProc(10115, 10115, 10115, 10115, 10115, 10115, 10115, 10115);
	D2FogGetInstallPath = (TD2FogGetInstallPath)GetOffsetByProc(10116, 10116, 10116, 10116, 10116, 10116, 10116, 10116);
	D2Fog10212 = (TD2Fog10212)GetOffsetByProc(10212, 10212, 10212, 10212, 10212, 10212, 10212, 10212);
	D2GetInstructionPointer = (TD2GetInstructionPointer)GetOffsetByProc(0, 0, 0, 10265, 10265, 10265, 10265, 10265);
}