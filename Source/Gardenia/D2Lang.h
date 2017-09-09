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

class D2Lang : public Library<D2Lang>
{
public:
	static void Init();

	typedef LPWSTR(__fastcall *TD2GetStringFromString) (const char* ptString);
	typedef LPWSTR(__fastcall *TD2GetStringFromIndex) (WORD dwIndexNum);
	typedef DWORD(__stdcall *TD2GetLang) ();
	typedef DWORD(__stdcall *TD2PrintBigNumber) (LPWSTR ptBuf, DWORD number, DWORD size);

	static TD2GetStringFromString D2GetStringFromString;
	static TD2GetStringFromIndex D2GetStringFromIndex;
	static TD2GetLang D2GetLang;
	static TD2PrintBigNumber D2PrintBigNumber;
private:
	static void SetFunctions();
};