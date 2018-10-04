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

void LoadLocalizedStrings();
LPWSTR getLocalString(int stringId);
LPCWSTR getLocalTypeString(DWORD code);
LPWSTR StripGender(LPWSTR text);
LPCWSTR StripGender(LPCWSTR text);

enum eStringList
{
	STR_STATS_UNASSIGN_WITH_LIMIT = 0,
	STR_STATS_UNASSIGN_WITHOUT_LIMIT,
	STR_STATS_BASE_MIN,
	STR_SKILLS_UNASSIGN,
	STR_STASH_PREVIOUS_PAGE,
	STR_STASH_NEXT_PAGE,
	STR_TOGGLE_TO_PERSONAL,
	STR_TOGGLE_TO_SHARED,
	STR_STASH_PREVIOUS_INDEX,
	STR_STASH_NEXT_INDEX,
	STR_PUT_GOLD,
	STR_TAKE_GOLD,
	STR_PERSONAL_PAGE_NUMBER,
	STR_SHARED_PAGE_NUMBER,
	STR_NO_SELECTED_PAGE,
	STR_SHARED_GOLD_QUANTITY,
	STR_PREVIOUS_PAGE,
	STR_NEXT_PAGE,
	STR_ITEM_LEVEL,
	//
	STR_COW_PORTAL,
	STR_PANDEMONIUM_PORTAL,
	STR_PANDEMONIUM_FINAL_PORTAL,
	STR_FULL,
	STR_REPAIR,
	STR_AND,
	STR_RECHARGE,
	STR_DESTROY_FILLERS,
	STR_REMOVE_FILLERS,
	STR_REGENERATE,
	STR_UPGRADE_TO_EXCEPTIONAL,
	STR_UPGRADE_TO_ELITE,
	STR_ETHERAL,
	STR_NOT_ETHERAL,
	STR_NOT_RUNEWORD,
	STR_BASIC,
	STR_EXCEPTIONAL,
	STR_ELITE,
	STR_CRACKED,
	STR_NORMAL,
	STR_SUPERIOR,
	STR_MAGIC,
	STR_SET,
	STR_RARE,
	STR_UNIQUE,
	STR_CRAFTED,
	STR_TEMPERED,
	STR_ITEM,
	STR_ITEM_SAME_TYPE,
	STR_INCLUDE_UPGRADED,
	STR_WITHOUT_SOCKET,
	STR_WITH_SOCKETS,
	STR_WITH_N_SOCKETS,
	STR_ONLY_N_H,
	STR_ONLY_HELL,
	STR_ONLY_CLASS,
};

