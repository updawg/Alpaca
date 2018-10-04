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

extern int active_Windowed;
extern int active_LockMouseCursor;
extern int active_RemoveBorder;
extern int active_WindowOnTop;
extern int active_Maximized;
extern int active_SetWindowPos;
extern int windowedX;
extern int windowedY;
extern int windowedWidth;
extern int windowedHeight;
extern int active_LockMouseOnStartup;

void SetWindowedOptions();
void lockMouseCursor();
void unlockMouseCursor();

