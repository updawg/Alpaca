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

#include "D2WinLibrary.h"

D2WinLibrary::D2WinLibrary(int gameVersion) : Library()
{
	Name = "D2Win.dll";
	Version = gameVersion;
	Offset = LoadDiabloLibrary();
	SetFunctions();
}

void D2WinLibrary::SetFunctions()
{
	D2PrintLineOnTextBox = (TD2PrintLineOnTextBox)GetOffsetByProc(10046, 10051);
	D2PrintString = (TD2PrintString)GetOffsetByProc(10117, 10076);
	D2GetPixelLen = (TD2GetPixelLen)GetOffsetByProc(10121, 10150);
	D2SetFont = (TD2SetFont)GetOffsetByProc(10127, 10047);
	D2PrintPopup = (TD2PrintPopup)GetOffsetByProc(10129, 10137);
	D2GetPixelRect = (TD2GetPixelRect)GetOffsetByProc(10131, 0);
	D2PrintTextPopup = (TD2PrintTextPopup)GetOffsetByProc(10132, 0);
	D2CreateTextBox = (TD2CreateTextBox)GetOffsetByProc(10017, 10164);
}