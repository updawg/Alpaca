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

#include "D2gfxLibrary.h"

void D2gfxLibrary::SetFunctions()
{
	D2GetResolution = (TD2GetResolution)GetOffsetByProc(10005, 10005, 10005, 10000, 10063, 10043, 10031, 10012);
	D2FillArea = (TD2FillArea)GetOffsetByProc(10055, 10055, 10055, 10028, 10000, 10062, 10014, 10028);
	D2PrintImage = (TD2PrintImage)GetOffsetByProc(10072, 10072, 10072, 10047, 10044, 10024, 10041, 10042);
}