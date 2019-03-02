// Copyright (C) 2004-2017 Yohann Nicolas
// Copyright (C) 2017-2018 Jonathan Vasquez <jon@xyinn.org>
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

#include "CustomLibraries.h"

TCustomDll* customDlls = NULL;

void TCustomDll::Init()
{
	if (initFct)
		initFct();
};

void TCustomDll::Release()
{
	if (releaseFct)
		releaseFct();
};

void TCustomDll::Initialize(DWORD offsetDll)
{
	offset = offsetDll;

	initFct = GetProcAddress(module, (LPCSTR)"_Init@0");
	if (!initFct)
		initFct = GetProcAddress(module, (LPCSTR)10000);

	releaseFct = GetProcAddress(module, (LPCSTR)"_Release@0");
	if (!releaseFct)
		releaseFct = GetProcAddress(module, (LPCSTR)10001);
}
