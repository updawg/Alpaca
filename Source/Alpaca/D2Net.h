// Copyright (C) 2004-2017 Yohann Nicolas
// Copyright (C) 2017-2018 Jonathan Vasquez <jon@xyinn.org>
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

#include "Library.h"

class D2Net : public Library<D2Net>
{
public:
	static void Init();

	typedef DWORD(__stdcall* TD2SendToServer) (DWORD size, DWORD one, void* data);
	typedef DWORD(__stdcall* TD2SendToClient) (DWORD zero, DWORD clientID, void* data, DWORD size);

	static TD2SendToServer D2SendToServer;
	static TD2SendToClient D2SendToClient;
private:
	static void SetFunctions();
};