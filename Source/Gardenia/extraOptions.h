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

extern int active_DisplayItemLevel;
extern DWORD nbPlayersCommandByDefault;
extern DWORD nbPlayersCommand;
extern int active_RunLODs;
extern int active_AlwaysDisplayLifeMana;
extern int active_EnabledTXTFilesWithMSExcel;

void Install_DisplayItemLevel();
void Install_SendPlayersCommand();
void Install_RunLODs();
void Install_AlwaysDisplayLifeMana();
void Install_EnabledTXTFilesWithMSExcel();