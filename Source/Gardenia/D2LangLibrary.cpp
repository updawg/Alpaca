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

#include "D2LangLibrary.h"

D2LangLibrary::D2LangLibrary(int gameVersion) : Library()
{
	Name = "D2Lang.dll";
	Version = gameVersion;
	Offset = LoadDiabloLibrary();
	SetFunctions();
}

void D2LangLibrary::SetFunctions()
{
	D2GetStringFromString = (TD2GetStringFromString)GetOffsetByProc(10003, 10003, 10003, 10002, 10004, 10010, 10011, 10011);
	D2GetStringFromIndex = (TD2GetStringFromIndex)GetOffsetByProc(10004, 10004, 10004, 10005, 10000, 10005, 10003, 10004);
	D2GetLang = (TD2GetLang)GetOffsetByProc(10007, 10007, 10007, 10009, 10013, 10002, 10009, 10001);
	D2PrintBigNumber = (TD2PrintBigNumber)GetOffsetByProc(10010, 10010, 10010, 0, 0, 0, 0, 0);
}