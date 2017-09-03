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

#include <windows.h>

// Forward declare so we can make our 'lu' an extern.
class LibraryUtility;

//extern int version_Game;
extern int version_D2Client;
extern int version_D2CMP;
extern int version_D2Common;
extern int version_D2Game;
extern int version_D2gfx;
extern int version_D2Lang;
extern int version_D2Launch;
extern int version_D2Net;
extern int version_D2Win;
extern int version_Fog;
extern int version_Storm;

// Address in memory of external DLL
extern DWORD offset_Game;
extern DWORD offset_D2Client;
extern DWORD offset_D2CMP;
extern DWORD offset_D2Common;
extern DWORD offset_D2Game;
extern DWORD offset_D2gfx;
extern DWORD offset_D2Lang;
extern DWORD offset_D2Launch;
extern DWORD offset_D2Net;
extern DWORD offset_D2Win;
extern DWORD offset_Fog;
extern DWORD offset_Storm;

extern LibraryUtility* lu;