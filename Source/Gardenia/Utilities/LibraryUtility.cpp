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

#include "LibraryUtility.h"

LibraryUtility::LibraryUtility()
{
	log_msg("***** Get D2 Modules address and version *****\n");

	// We need to load the game now so that we have the version base offsets for the rest of the Dlls.
	Game = new GameLibrary();

	if (VersionUtility::IsEqualOrGreaterThan114(Game->DllVersion))
	{
		log_msg("1.14d support is not implemented.\n");
		//exit(-1);
	}
	else
	{
		D2Client = new D2ClientLibrary(Game->DllVersion);
		D2CMP = new D2CMPLibrary(Game->DllVersion);
		D2Common = new D2CommonLibrary(Game->DllVersion);
		D2Game = new D2GameLibrary(Game->DllVersion);
		D2gfx = new D2gfxLibrary(Game->DllVersion);
		D2Lang = new D2LangLibrary(Game->DllVersion);
		D2Launch = new D2LaunchLibrary(Game->DllVersion);
		D2Net = new D2NetLibrary(Game->DllVersion);
		D2Win = new D2WinLibrary(Game->DllVersion);
		Fog = new FogLibrary(Game->DllVersion);
		Storm = new StormLibrary(Game->DllVersion);
	}
}

void LibraryUtility::HookLibraries()
{
	log_msg("***** Unprotect Libraries *****\n");

	if (VersionUtility::IsEqualOrGreaterThan114(Game->DllVersion))
	{
		log_msg("Hooking 1.14 libraries");
	}
	else
	{
		D2Client->HookLibrary();
		D2Common->HookLibrary();
		D2Game->HookLibrary();
		D2gfx->HookLibrary();
		D2Lang->HookLibrary();
		D2Launch->HookLibrary();
		Fog->HookLibrary();
		Storm->HookLibrary();
	}

	log_msg("\n\n");
}

void LibraryUtility::UnhookLibraries()
{
	log_msg("***** Reprotect Libraries *****\n");

	if (VersionUtility::IsEqualOrGreaterThan114(Game->DllVersion))
	{
		log_msg("Unhooking 1.14 libraries");
	}
	else
	{
		D2Client->UnhookLibrary();
		D2Common->UnhookLibrary();
		D2Game->UnhookLibrary();
		D2gfx->UnhookLibrary();
		D2Lang->UnhookLibrary();
		D2Launch->UnhookLibrary();
		Fog->UnhookLibrary();
		Storm->UnhookLibrary();
	}

	log_msg("\n\n");
}