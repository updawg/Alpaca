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

#include "language.h"
#include "common.h"
#include <stdio.h>

bool active_ChangeLanguage = true;
DWORD selectedLanguage = LNG_ENG;

bool active_LanguageManagement = false;
DWORD defaultLanguage = LNG_ENG;
t_availableLanguages availableLanguages;

DWORD* ptCurrentLanguage;

DWORD __stdcall languageManagement ()
{
	if (active_ChangeLanguage) *ptCurrentLanguage = selectedLanguage;
	if (active_LanguageManagement)
	if ((*ptCurrentLanguage > LNG_RUS) || !((1 << *ptCurrentLanguage) & availableLanguages.all))
		*ptCurrentLanguage = defaultLanguage;
	return *ptCurrentLanguage;
}

// [Patch]
void Install_LanguageManagement()
{
	static int isInstalled = false;
	if (isInstalled) return;
	
	log_msg("Patch D2Lang for language management. (LanguageManagement)\n");

	ptCurrentLanguage = *(DWORD**)((DWORD)D2Lang->D2GetLang + (Game->Version >= VersionUtility::Versions::V111 ? 0x51: 0x5C));

	// Language management
	mem_seek((DWORD)D2GetLang + (Game->Version >= VersionUtility::Versions::V111 ? 0x3E : 0x49));
	memt_byte(0xA1, 0xE8);
	MEMT_REF4(ptCurrentLanguage, languageManagement);

	log_msg("\n");

	isInstalled = true;
}


