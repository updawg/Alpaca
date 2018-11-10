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

void TCustomDll::init()
{
	if (initFct)
		initFct();
};

void TCustomDll::release()
{
	if (releaseFct)
		releaseFct();
};

void TCustomDll::saveExtendedSaveFile(Unit* ptChar, BYTE** data, DWORD* maxSize, DWORD* curSize)
{
	if (saveExtendedSaveFileFct)
		saveExtendedSaveFileFct(ptChar, data, maxSize, curSize);
};

int TCustomDll::loadExtendedSaveFile(Unit* ptChar, BYTE* data, DWORD maxSize, DWORD* curSize)
{
	if (loadExtendedSaveFileFct)
		return loadExtendedSaveFileFct(ptChar, data, maxSize, curSize);
	return 0;
};

int TCustomDll::initExtendedSaveFile(BYTE** data, DWORD* maxSize, DWORD* curSize)
{
	if (initExtendedSaveFileFct)
		return initExtendedSaveFileFct(data, maxSize, curSize);
	return 0;
};

void TCustomDll::saveSharedSaveFile(Unit* ptChar, BYTE** data, DWORD* maxSize, DWORD* curSize)
{
	if (saveSharedSaveFileFct)
		saveSharedSaveFileFct(ptChar, data, maxSize, curSize);
};

int TCustomDll::loadSharedSaveFile(Unit* ptChar, BYTE data[], DWORD maxSize, DWORD* curSize)
{
	if (loadSharedSaveFileFct)
		return loadSharedSaveFileFct(ptChar, data, maxSize, curSize);
	return 0;
};

int TCustomDll::initSharedSaveFile(BYTE** data, DWORD* maxSize, DWORD* curSize)
{
	if (initSharedSaveFileFct)
		return initSharedSaveFileFct(data, maxSize, curSize);
	return 0;
};

void TCustomDll::initialize(DWORD offsetDll)
{
	offset = offsetDll;

	initFct = GetProcAddress(module, (LPCSTR)"_Init@0");
	if (!initFct)
		initFct = GetProcAddress(module, (LPCSTR)10000);

	releaseFct = GetProcAddress(module, (LPCSTR)"_Release@0");
	if (!releaseFct)
		releaseFct = GetProcAddress(module, (LPCSTR)10001);

	saveExtendedSaveFileFct = (TsaveSaveFile)GetProcAddress(module, "_saveExtendedSaveFile@16");
	loadExtendedSaveFileFct = (TloadSaveFile)GetProcAddress(module, "_loadExtendedSaveFile@16");
	initExtendedSaveFileFct = (TinitSaveFile)GetProcAddress(module, "_initExtendedSaveFile@12");
	saveSharedSaveFileFct = (TsaveSaveFile)GetProcAddress(module, "_saveSharedSaveFile@16");
	loadSharedSaveFileFct = (TloadSaveFile)GetProcAddress(module, "_loadSharedSaveFile@16");
	initSharedSaveFileFct = (TinitSaveFile)GetProcAddress(module, "_initSharedSaveFile@12");
}