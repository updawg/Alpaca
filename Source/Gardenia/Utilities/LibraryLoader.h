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

#include "../Error.h"

#include "../Game.h"
#include "../D2Client.h"
#include "../D2CMP.h"
#include "../D2Common.h"
#include "../D2Game.h"
#include "../D2gfx.h"
#include "../D2Lang.h"
#include "../D2Launch.h"
#include "../D2Net.h"
#include "../D2Win.h"
#include "../Fog.h"
#include "../Storm.h"

// Used to load the libraries
class LibraryLoader
{
public:
	static void Init();

	// Change the protection scheme of a loaded
	// DLL called libraryName in memory space at address addr+size to allow us to customize it.
	static void HookLibraries();
	static void UnhookLibraries();
};