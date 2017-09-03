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

#include "common.h"

typedef int (STDCALL *TsaveSaveFile) (Unit* ptChar, BYTE** data, DWORD* maxSize, DWORD* curSize);
typedef int (STDCALL *TloadSaveFile) (Unit* ptChar, BYTE* data, DWORD maxSize, DWORD* curSize);
typedef int (STDCALL *TinitSaveFile) (BYTE** data, DWORD* maxSize, DWORD* curSize);

class TCustomDll
{
public:
	union {
		HMODULE module;
		DWORD offset;
	};
	TCustomDll* nextDll;
	void initialize(DWORD offsetDll);
	void init();
	void release();
	void saveExtendedSaveFile (Unit* ptChar, BYTE** data, DWORD* maxSize, DWORD* curSize);
	int loadExtendedSaveFile (Unit* ptChar, BYTE* data, DWORD maxSize, DWORD* curSize);
	int initExtendedSaveFile (BYTE** data, DWORD* maxSize, DWORD* curSize);
	void saveSharedSaveFile (Unit* ptChar, BYTE** data, DWORD* maxSize, DWORD* curSize);
	int loadSharedSaveFile (Unit* ptChar, BYTE* data, DWORD maxSize, DWORD* curSize);
	int initSharedSaveFile (BYTE** data, DWORD* maxSize, DWORD* curSize);
//	__inline TCustomDll() {ZeroMemory(this,sizeof(this));}
private:
	FARPROC initFct;
	FARPROC releaseFct;
	TsaveSaveFile saveExtendedSaveFileFct;
	TloadSaveFile loadExtendedSaveFileFct;
	TinitSaveFile initExtendedSaveFileFct;
	TsaveSaveFile saveSharedSaveFileFct;
	TloadSaveFile loadSharedSaveFileFct;
	TinitSaveFile initSharedSaveFileFct;
};

extern TCustomDll* customDlls;

