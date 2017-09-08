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

#include "StormLibrary.h"

StormLibrary::StormLibrary(int gameVersion) : Library()
{
	Name = "Storm.dll";
	Version = gameVersion;
	Offset = LoadDiabloLibrary();
	SetFunctions();
}

void StormLibrary::SetFunctions()
{
	D2StormMPQOpenFile = (TD2StormMPQOpenFile)GetOffsetByProc(268, 268);
	D2Storm503 = (TD2Storm503)GetOffsetByProc(503, 503);
	D2FreeWinMessage = (TD2FreeWinMessage)GetOffsetByProc(511, 511);
}