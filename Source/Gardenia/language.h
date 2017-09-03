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

extern bool active_ChangeLanguage;
extern DWORD selectedLanguage;

extern bool active_LanguageManagement;
extern DWORD defaultLanguage;

union t_availableLanguages
{
	DWORD all;
	struct {
		DWORD eng:1;
		DWORD esp:1;
		DWORD deu:1;
		DWORD fra:1;
		DWORD por:1;
		DWORD ita:1;
		DWORD jpn:1;
		DWORD kor:1;
		DWORD sin:1;
		DWORD chi:1;
		DWORD pol:1;
		DWORD rus:1;
	};
};
extern t_availableLanguages availableLanguages;

void Install_LanguageManagement();

