#include "Library.h"
#include "Error.h"
#include "Utilities/VersionUtility.h"

Library::Library(DWORD gameOffset, int gameVersion)
{
	// If we can refactor the LoadGame function so that we can safely retrieve its values, then we don't need
	// to pass them in as a parameter. I'm trying to avoid using global variables.
	GameOffset = gameOffset;
	GameVersion = gameVersion;
}

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
	log_msg("%s loaded at:\t%08X (%s)\n", DllName, proposedOffset, VersionUtility::GetVersionAsString(GameVersion));
	return proposedOffset;
}

// Return the offset for this specific version of Diablo II.
DWORD Library::GetOffsetForVersion(DWORD V109, DWORD V109D, DWORD V110, DWORD V111, DWORD V111B, DWORD V112, DWORD V113C, DWORD V113D)
{
	return GetOffsetForVersion(CreateOffsets(V109, V109D, V110, V111, V111B, V112, V113C, V113D));
}

DWORD Library::GetOffsetForVersion(const VersionOffsets& offsets)
{
	// properly convert the version to an enum in the future.
	VersionOffsets::const_iterator it = offsets.find((VersionUtility::Versions)GameVersion);
	
	if (it != offsets.end())
	{
		//log_msg("Found it: %i", it->second);
		return it->second;
	}
	
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

DWORD Library::RetrieveAddressByProc(const VersionOffsets moduleOffsets)
{
	DWORD proposedOffset = GetOffsetForVersion(moduleOffsets);
	if (proposedOffset != 0)
	{
		return GetFunctionAddress((LPCSTR)proposedOffset);
	}
	return NULL;
}

DWORD Library::RetrieveAddressByAddition(const VersionOffsets moduleOffsets)
{
	DWORD offset = GetOffsetForVersion(moduleOffsets);
	DWORD proposedOffset = DllOffset + offset;
	//log_msg("Retrieving %s function for offset %08X (%i) by Addition ... SUCCESS. Located at %08X.\n", DllName, offset, offset, proposedOffset);
	return proposedOffset;
}

DWORD Library::GetFunctionAddress(LPCSTR offset)
{
	HMODULE module = (HMODULE)DllOffset;
	log_msg("Retrieving %s function for offset %08X (%i) by Proc ...", DllName, offset, offset);

	DWORD locatedAddress;

	if (offset)
	{
		locatedAddress = (DWORD) GetProcAddress(module, offset);
		if (!locatedAddress)
		{
			// Don't exit here cause apparently the plugin still works even if some functions aren't found.
			log_msg("FAILED.\n");
			//log_msg("Failed to retrieve %s function for offset %08X (%i) by Proc ...\n", DllName, offset, offset);
		}
		else
		{
			log_msg("SUCCESS. Located at %08X.\n", locatedAddress);
		}
		return locatedAddress;
	}

	return NULL;
}