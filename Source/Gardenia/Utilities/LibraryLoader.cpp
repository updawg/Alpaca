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

#include "LibraryLoader.h"

void LibraryLoader::Init()
{
	log_msg("***** Get D2 Modules address and version *****\n\n");

	// We need to load the game now so that we have the game version for the rest of the Dlls.
	Game::Init();
	
	if (VersionUtility::Is114D())
	{
		log_msg("1.14d support is not implemented.\n");
		//exit(-1);
	}
	else
	{
		// Initialize static class variables
		D2Client::Init();
		D2CMP::Init();
		D2Common::Init();
		D2Game::Init();
		D2gfx::Init();
		D2Lang::Init();
		D2Launch::Init();
		D2Net::Init();
		D2Win::Init();
		Fog::Init();
		Storm::Init();
	}
	log_msg("\n");
}

void LibraryLoader::HookLibraries()
{
	log_msg("***** Unprotect Libraries *****\n");

	if (VersionUtility::Is114D())
	{
		log_msg("Hooking 1.14 libraries");
	}
	else
	{
		D2Client::HookLibrary();
		//D2CMP::HookLibrary();
		D2Common::HookLibrary();
		D2Game::HookLibrary();
		D2gfx::HookLibrary();
		D2Lang::HookLibrary();
		D2Launch::HookLibrary();
		//D2Net::HookLibrary();
		//D2Win::HookLibrary();
		Fog::HookLibrary();
		Storm::HookLibrary();
	}

	log_msg("\n");
}

void LibraryLoader::UnhookLibraries()
{
	log_msg("***** Reprotect Libraries *****\n");

	if (VersionUtility::Is114D())
	{
		log_msg("Unhooking 1.14 libraries");
	}
	else
	{
		D2Client::UnhookLibrary();
		//D2CMP::UnhookLibrary();
		D2Common::UnhookLibrary();
		D2Game::UnhookLibrary();
		D2gfx::UnhookLibrary();
		D2Lang::UnhookLibrary();
		D2Launch::UnhookLibrary();
		//D2Net::UnhookLibrary();
		//D2Win::UnhookLibrary();
		Fog::UnhookLibrary();
		Storm::UnhookLibrary();
	}

	log_msg("\n");
}