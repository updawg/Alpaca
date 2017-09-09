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
#include <map>
#include "Error.h"
#include "Utilities/VersionUtility.h"

#include "../Commons/D2UnitStruct.h"
#include "../Commons/d2BinFile.h"
#include "../Commons/d2Struct.h"

#include "modifMemory.h"

using VersionOffsets = std::map<VersionUtility::Versions, DWORD>;

template <class Child>
class Library
{
public:
	static char* Name;
	static DWORD Offset;

	// Load the Library (This is the DLLs base Offset that we can use to
	// determine the game version for the dll). This should be identical
	// to the Game Version of the .exe.
	static DWORD LoadDiabloLibrary()
	{
		DWORD proposedOffset = (DWORD)LoadLibrary(Name);

		if (proposedOffset == NULL)
		{
			log_msg("Failed to load library : %s\n", Name);
			exit(-1);
		}
		log_msg("%s loaded at:\t%08X (%s)\n", Name, proposedOffset, VersionUtility::GetVersionAsString());
		return proposedOffset;
	}

	static void HookLibrary()
	{
		DWORD dw = 0;
		BYTE* offsetPESignature = Offset + *(BYTE**)((BYTE*)Offset + 0x3C);
		DWORD sizeOfCode = *(DWORD*)(offsetPESignature + 0x1C);
		BYTE* baseOfCode = Offset + *(BYTE**)(offsetPESignature + 0x2C);
		if (!VirtualProtect(baseOfCode, sizeOfCode, PAGE_EXECUTE_READWRITE, &dw))
		{
			log_msg("Failed to hook library : %s. (%08X,%08X)\n", Name, baseOfCode, sizeOfCode);
			exit(-1);
		}
		log_msg("%s successfully hooked. (%08X,%08X)\n", Name, baseOfCode, sizeOfCode);
	}

	static void UnhookLibrary()
	{
		DWORD dw = 0;
		BYTE* offsetPESignature = Offset + *(BYTE**)((BYTE*)Offset + 0x3C);
		DWORD sizeOfCode = *(DWORD*)(offsetPESignature + 0x1C);
		BYTE* baseOfCode = Offset + *(BYTE**)(offsetPESignature + 0x2C);
		if (!VirtualProtect(baseOfCode, sizeOfCode, PAGE_EXECUTE_READ, &dw))
			log_msg("Failed to unhook library : %s. (%08X,%08X)\n", Name, baseOfCode, sizeOfCode);
		else
			log_msg("%s successfully unhooked. (%08X,%08X)\n", Name, baseOfCode, sizeOfCode);
	}

	// Retrieves the address by using GetProcAddress
	static DWORD GetOffsetByProc(const VersionOffsets moduleOffsets)
	{
		DWORD proposedOffset = GetOffsetForVersion(moduleOffsets);
		return GetFunctionAddress((LPCSTR)proposedOffset);
	}
	static DWORD GetOffsetByProc(DWORD V109B, DWORD V113D)
	{
		return GetOffsetByProc(CreateOffsets(V109B, V113D));
	}

	// Retrieves the address by adding the DLLs base offset to the recorded offset
	static DWORD GetOffsetByAddition(const VersionOffsets moduleOffsets)
	{
		DWORD offset = GetOffsetForVersion(moduleOffsets);
		DWORD proposedOffset = Offset + offset;
		//log_msg("Retrieving %s function for offset %08X (%i) by Addition (on base %08X) ... SUCCESS. Located at %08X.\n", Name, offset, offset, Offset, proposedOffset);
		return proposedOffset;
	}
	static DWORD GetOffsetByAddition(DWORD V109B, DWORD V113D)
	{
		return GetOffsetByAddition(CreateOffsets(V109B, V113D));
	}

	// Offsets for functions in these specific versions. When updating to a new diablo version, you will
	// want to add an entry to each of the function sets in each library that require an update.
	static DWORD GetOffsetForVersion(const VersionOffsets& offsets)
	{
		//log_msg("For game version: %s, %d\n", VersionUtility::GetVersionAsString(), VersionUtility::GetVersion());

		// properly convert the version to an enum in the future.
		VersionOffsets::const_iterator it = offsets.find((VersionUtility::Versions)VersionUtility::GetVersion());

		if (it != offsets.end())
		{
			//log_msg("Found it: %s :: %08X\n", VersionUtility::GetVersionAsString(), it->second);
			return it->second;
		}

		//log_msg("Falling back to 1.09B even though game version is: %s\n", VersionUtility::GetVersionAsString());
		// Existing behavior is to return 1.09 (lowest offset/version that we have)
		return offsets.find(VersionUtility::Versions::V109b)->second;
	}

	static DWORD GetOffsetForVersion(DWORD V109B, DWORD V113D)
	{
		return GetOffsetForVersion(CreateOffsets(V109B, V113D));
	}

	// Contains all offsets that are possible for this particular function pointer.
	static VersionOffsets CreateOffsets(DWORD V109B, DWORD V113D)
	{
		VersionOffsets indexes =
		{
			{ VersionUtility::Versions::V109b, V109B },
			{ VersionUtility::Versions::V113d, V113D }
		};

		return indexes;
	}

protected:
	// Retrieves the address using GetProcAddress
	static DWORD GetFunctionAddress(LPCSTR offset)
	{
		HMODULE module = (HMODULE)Offset;
		//log_msg("Retrieving %s function for offset %08X (%i) by Proc ...", Name, offset, offset);

		DWORD locatedAddress = (DWORD)GetProcAddress(module, offset);
		//if (!locatedAddress)
		//{
		//	// Don't exit here cause apparently the plugin still works even if some functions aren't found.
		//	//log_msg("FAILED.\n");
		//	log_msg("Failed to retrieve %s function for offset %08X (%i) by Proc ... Returning %08X\n", Name, offset, offset, locatedAddress);
		//}
		/*else
		{
		log_msg("SUCCESS. Located at %08X.\n", locatedAddress);
		}*/

		return locatedAddress;
	}
};

template <class Child>
char* Library<Child>::Name;

template <class Child>
DWORD Library<Child>::Offset;