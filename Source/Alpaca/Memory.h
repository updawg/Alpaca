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

#pragma once

#include <Windows.h>

extern void* currentMemoryPos;
DWORD mem_seek(DWORD newPos);

void memt_byte(BYTE old, BYTE val);

#define MEMT_DWORD(O, R) memt_dword((DWORD)(O), (DWORD)(R))
void memt_dword(DWORD old, DWORD val);

#define MEMT_REF4(O, R) memt_ref4((DWORD)(O), (DWORD)(R))
void memt_ref4(DWORD old, DWORD ref);

//CALL <JMP.&D2gfx.#10047>
#define MEMJ_REF4(O, R) memj_ref4((DWORD)(O), (DWORD)(R))
void memj_ref4(DWORD old, DWORD ref);

//CALL D2Common.6FD5F500
#define MEMC_REF4(O, R) memc_ref4((DWORD)(O), (DWORD)(R))
void memc_ref4(DWORD old, DWORD ref);

//CALL DWORD PTR DS:[<&USER32.GetKeyState>]
#define MEMD_REF4(O, R) memd_ref4((DWORD)(O), (DWORD)(R))
void memd_ref4(DWORD old, DWORD ref);

