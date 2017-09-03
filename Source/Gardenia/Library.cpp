// Copyright (C) 2004-2017  Yohann Nicolas
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

#include "Library.h"
#include "Error.h"
#include "Utilities/VersionUtility.h"

Library::Library() {}

void Library::HookLibrary()
{
	DWORD dw = 0;
	BYTE* offsetPESignature = DllOffset + *(BYTE**)((BYTE*) DllOffset + 0x3C);
	DWORD sizeOfCode = *(DWORD*)(offsetPESignature + 0x1C);
	BYTE* baseOfCode = DllOffset + *(BYTE**)(offsetPESignature + 0x2C);
	if (!VirtualProtect(baseOfCode, sizeOfCode, PAGE_EXECUTE_READWRITE, &dw))
	{
		log_msg("Failed to hook library : %s. (%08X,%08X)\n", DllName, baseOfCode, sizeOfCode);
		exit(-1);
	}
	log_msg("%s successfully hooked. (%08X,%08X)\n", DllName, baseOfCode, sizeOfCode);
}

void Library::UnhookLibrary()
{
	DWORD dw = 0;
	BYTE* offsetPESignature = DllOffset + *(BYTE**)((BYTE*) DllOffset + 0x3C);
	DWORD sizeOfCode = *(DWORD*)(offsetPESignature + 0x1C);
	BYTE* baseOfCode = DllOffset + *(BYTE**)(offsetPESignature + 0x2C);
	if (!VirtualProtect(baseOfCode, sizeOfCode, PAGE_EXECUTE_READ, &dw))
		log_msg("Failed to unhook library : %s. (%08X,%08X)\n", DllName, baseOfCode, sizeOfCode);
	else
		log_msg("%s successfully unhooked. (%08X,%08X)\n", DllName, baseOfCode, sizeOfCode);
}

DWORD Library::LoadDiabloLibrary()
{
	DWORD proposedOffset = (DWORD)LoadLibrary(DllName);

	if (proposedOffset == NULL)
	{
		log_msg("Failed to load library : %s\n", DllName);
		exit(-1);
	}
	log_msg("%s loaded at:\t%08X (%s)\n", DllName, proposedOffset, VersionUtility::GetVersionAsString(DllVersion));
	return proposedOffset;
}

// Return the offset for this specific version of Diablo II.
DWORD Library::GetOffsetForVersion(DWORD V109, DWORD V109D, DWORD V110, DWORD V111, DWORD V111B, DWORD V112, DWORD V113C, DWORD V113D)
{
	return GetOffsetForVersion(CreateOffsets(V109, V109D, V110, V111, V111B, V112, V113C, V113D));
}

DWORD Library::GetOffsetForVersion(const VersionOffsets& offsets)
{
	//log_msg("For game version: %s\n", VersionUtility::GetVersionAsString(DllVersion));

	// properly convert the version to an enum in the future.
	VersionOffsets::const_iterator it = offsets.find((VersionUtility::Versions)DllVersion);
	
	if (it != offsets.end())
	{
		//log_msg("Found it: %s :: %08X\n", VersionUtility::GetVersionAsString(DllVersion), it->second);
		return it->second;
	}
	
	//log_msg("Falling back to 1.09A even though game version is: %s\n", VersionUtility::GetVersionAsString(DllVersion));
	// Existing behavior is to return 1.09 (lowest offset/version that we have)
	return offsets.find(VersionUtility::Versions::V109)->second;
}

VersionOffsets Library::CreateOffsets(DWORD V109, DWORD V109D, DWORD V110, DWORD V111, DWORD V111B, DWORD V112, DWORD V113C, DWORD V113D)
{
	VersionOffsets indexes =
	{
		{ VersionUtility::Versions::V113d, V113D },
		{ VersionUtility::Versions::V113c, V113C },
		{ VersionUtility::Versions::V112, V112 },
		{ VersionUtility::Versions::V111b, V111B },
		{ VersionUtility::Versions::V111, V111 },
		{ VersionUtility::Versions::V110, V110 },
		{ VersionUtility::Versions::V109d, V109D },
		{ VersionUtility::Versions::V109, V109 },
	};

	return indexes;
}

DWORD Library::GetOffsetByProc(DWORD V109, DWORD V109D, DWORD V110, DWORD V111, DWORD V111B, DWORD V112, DWORD V113C, DWORD V113D)
{
	return GetOffsetByProc(CreateOffsets(V109, V109D, V110, V111, V111B, V112, V113C, V113D));
}

DWORD Library::GetOffsetByProc(const VersionOffsets moduleOffsets)
{
	DWORD proposedOffset = GetOffsetForVersion(moduleOffsets);
	return GetFunctionAddress((LPCSTR)proposedOffset);
}

DWORD Library::GetOffsetByAddition(DWORD V109, DWORD V109D, DWORD V110, DWORD V111, DWORD V111B, DWORD V112, DWORD V113C, DWORD V113D)
{
	return GetOffsetByAddition(CreateOffsets(V109, V109D, V110, V111, V111B, V112, V113C, V113D));
}

DWORD Library::GetOffsetByAddition(const VersionOffsets moduleOffsets)
{
	DWORD offset = GetOffsetForVersion(moduleOffsets);
	DWORD proposedOffset = DllOffset + offset;
	//log_msg("Retrieving %s function for offset %08X (%i) by Addition (on base %08X) ... SUCCESS. Located at %08X.\n", DllName, offset, offset, DllOffset, proposedOffset);
	return proposedOffset;
}

DWORD Library::GetFunctionAddress(LPCSTR offset)
{
	HMODULE module = (HMODULE)DllOffset;
	//log_msg("Retrieving %s function for offset %08X (%i) by Proc ...", DllName, offset, offset);

	DWORD locatedAddress = (DWORD) GetProcAddress(module, offset);
	//if (!locatedAddress)
	//{
	//	// Don't exit here cause apparently the plugin still works even if some functions aren't found.
	//	//log_msg("FAILED.\n");
	//	log_msg("Failed to retrieve %s function for offset %08X (%i) by Proc ... Returning %08X\n", DllName, offset, offset, locatedAddress);
	//}
	/*else
	{
		log_msg("SUCCESS. Located at %08X.\n", locatedAddress);
	}*/

	return locatedAddress;
}