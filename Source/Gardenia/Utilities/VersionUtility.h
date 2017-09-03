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

class VersionUtility
{
public:
	enum Versions
	{
		UNKNOWN = -1,
		V100 = 0,
		V107,
		V108,
		V109,
		V109b,
		V109d,
		V110,
		V111,
		V111b,
		V112,
		V113c,
		V113d,
		V114a,
		V114b,
		V114c,
		V114d
	};

	static const bool VersionUtility::IsSupported(const int version);
	static const char* GetVersionAsString(const int version);
	static const bool VersionUtility::IsEqualOrGreaterThan114(const int version);

	static Versions GetVersion(const LPCVOID pVersionResource);
	static Versions GetVersion(const char* gameExeName);
	static Versions GetVersion(const HMODULE hModule);
};