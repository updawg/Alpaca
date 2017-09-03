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

//#include "../common.h"

#include "../Error.h"

#include "../Library.h"
#include "../GameLibrary.h"
#include "../D2ClientLibrary.h"
#include "../D2CMPLibrary.h"
#include "../D2CommonLibrary.h"
#include "../D2GameLibrary.h"
#include "../D2GfxLibrary.h"
#include "../D2LangLibrary.h"
#include "../D2LaunchLibrary.h"
#include "../D2NetLibrary.h"
#include "../D2WinLibrary.h"
#include "../FogLibrary.h"
#include "../StormLibrary.h"

// Used to load the libraries
class LibraryUtility
{
public:
	LibraryUtility();

	// Change the protection scheme of a loaded
	// DLL called libraryName in memory space at address addr+size to allow us to customize it.
	void HookLibraries();
	void UnhookLibraries();

	// Libraries
	GameLibrary* Game;
	D2ClientLibrary* D2Client;
	D2CMPLibrary* D2CMP;
	D2CommonLibrary* D2Common;
	D2GameLibrary* D2Game;
	D2gfxLibrary* D2gfx;
	D2LangLibrary* D2Lang;
	D2LaunchLibrary* D2Launch;
	D2NetLibrary* D2Net;
	D2WinLibrary* D2Win;
	FogLibrary* Fog;
	StormLibrary* Storm;
};