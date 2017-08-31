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
DWORD Library::GetOffsetForVersion(const VersionOffsets& offsets)
{
	// properly convert the version to an enum in the future.
	VersionOffsets::const_iterator it = offsets.find((VersionUtility::Versions)GameVersion);
	
	if (it != offsets.end())
	{
		//log_msg("Found it: %i", it->second);
		return it->second;
	}
	else
	{
		log_msg("error finding the address for module %s", DllName);
		return 0;
	}
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

DWORD Library::RetrieveAddress(const char* moduleName, const DWORD moduleBaseAddress, const VersionOffsets moduleOffsets)
{
	return GetFunctionAddress(moduleName, (HMODULE) moduleBaseAddress, (LPCSTR) GetOffsetForVersion(moduleOffsets));
}

DWORD Library::GetFunctionAddress(const char* moduleName, HMODULE module, LPCSTR offset)
{
	log_msg("Searching for %s (%08X) function at %08X (%i) ... ", moduleName, module, offset, offset);

	DWORD locatedAddress;

	if (offset)
	{
		locatedAddress = (DWORD) GetProcAddress(module, offset);
		if (!locatedAddress)
		{
			log_msg("FAILED.\n");
			// Don't exit here cause apparently the plugin still works even if some functions aren't found.
		}
		log_msg("SUCCESS. Located at %08X.\n", locatedAddress);
		return locatedAddress;
	}
	
	return NULL;
}