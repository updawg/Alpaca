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

#include "D2Lang.h"

void D2Lang::Init()
{
	Name = "D2Lang.dll";
	Offset = LoadDiabloLibrary();
	SetFunctions();
}

void D2Lang::SetFunctions()
{
	D2GetStringFromString = (TD2GetStringFromString)GetOffsetByProc(10003);
	D2GetStringFromIndex = (TD2GetStringFromIndex)GetOffsetByProc(10004);
	D2GetLang = (TD2GetLang)GetOffsetByProc(10007);
	D2PrintBigNumber = (TD2PrintBigNumber)GetOffsetByProc(10010);
}

D2Lang::TD2GetStringFromString D2Lang::D2GetStringFromString;
D2Lang::TD2GetStringFromIndex D2Lang::D2GetStringFromIndex;
D2Lang::TD2GetLang D2Lang::D2GetLang;
D2Lang::TD2PrintBigNumber D2Lang::D2PrintBigNumber;