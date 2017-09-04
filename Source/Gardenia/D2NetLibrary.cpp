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

#include "D2NetLibrary.h"

D2NetLibrary::D2NetLibrary(int gameVersion) : Library()
{
	Name = "D2Net.dll";
	Version = gameVersion;
	Offset = LoadDiabloLibrary();
	SetFunctions();
}

void D2NetLibrary::SetFunctions()
{
	D2SendToServer = (TD2SendToServer)GetOffsetByProc(10005, 10005, 10005, 10035, 10020, 10036, 10024, 10015);
	D2SendToClient = (TD2SendToClient)GetOffsetByProc(10006, 10006, 10006, 10018, 10018, 10015, 10002, 10012);
}