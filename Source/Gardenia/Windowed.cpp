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

#include "windowed.h"
#include "common.h"

int active_Windowed = true;
int setWindowedOptionsDone = false;
int active_RemoveBorder = true;
int active_WindowOnTop = true;
int active_Maximized = true;
int active_SetWindowPos = true;
int windowedX = 240;
int windowedY = 0;
int windowedWidth = 1440;
int windowedHeight = 1080;
int active_LockMouseOnStartup = true;

void unlockMouseCursor()
{
	ClipCursor(NULL);
}

void lockMouseCursor(int width, int height)
{
	RECT clientRect;
	RECT rect;
	HWND hwnd = GetActiveWindow();
	GetClientRect(hwnd, &clientRect);
	GetWindowRect(hwnd, &rect);
	int shiftX = (rect.right - rect.left - clientRect.right) / 2;
	int shiftY = rect.bottom - rect.top - clientRect.bottom - shiftX;
	log_msg("Windows size : %i, %i, %i, %i\n", rect.left, rect.top, rect.right, rect.bottom);
	rect.left += shiftX;
	rect.right = rect.left + width;
	rect.top += shiftY;
	rect.bottom = rect.top + height;
	//no resize : 560, 231, 1360, 831
	//resized : 240, 0, 1040, 600
	log_msg("Lock Mouse Cursor : %i, %i, %i, %i\n", rect.left, rect.top, rect.right, rect.bottom);
	ClipCursor(&rect);
}

void lockMouseCursor() { lockMouseCursor(ResolutionX, ResolutionY); }

void SetWindowedOptions()
{
	if (setWindowedOptionsDone)
		return;
	HWND hwnd = GetActiveWindow();
	RECT clientRect;
	GetClientRect(hwnd, &clientRect);

	if (active_RemoveBorder)
	{
		LONG lStyle = GetWindowLong(hwnd, GWL_STYLE);
		lStyle &= ~(WS_CAPTION | WS_THICKFRAME | WS_MINIMIZE | WS_MAXIMIZE | WS_SYSMENU);
		SetWindowLong(hwnd, GWL_STYLE, lStyle);
		SetWindowPos(hwnd, NULL, 0, 0, clientRect.right, clientRect.bottom, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER);
	}

	if (active_Maximized && !active_SetWindowPos)
	{
		RECT screen;
		GetWindowRect(GetDesktopWindow(), &screen);
		log_msg("Screen size : %i, %i, %i, %i\n", screen.left, screen.top, screen.right, screen.bottom);
		int w = screen.bottom * clientRect.right / clientRect.bottom;
		int h = w * clientRect.bottom / clientRect.right;
		if (screen.right < w)
		{
			h = screen.right * clientRect.bottom / clientRect.right;
			w = h * clientRect.right / clientRect.bottom;
		}
		windowedX = (screen.right - w) / 2;
		windowedY = (screen.bottom - h) / 2;
		windowedWidth = w;
		windowedHeight = h;
	}

	if (active_SetWindowPos || active_Maximized)
	{
		if (active_WindowOnTop)
			SetWindowPos(hwnd, HWND_TOPMOST, windowedX, windowedY, windowedWidth, windowedHeight, SWP_FRAMECHANGED);
		else
			SetWindowPos(hwnd, NULL, windowedX, windowedY, windowedWidth, windowedHeight, SWP_FRAMECHANGED | SWP_NOZORDER | SWP_NOOWNERZORDER);
	}
	else if (active_WindowOnTop)
		SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, clientRect.right, clientRect.bottom, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE);

	if (active_LockMouseOnStartup)
		lockMouseCursor(clientRect.right, clientRect.bottom);

	setWindowedOptionsDone = true;
}