#include "Library.h"
#include "error.h"
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

//GET_VERSION(D2Client, 17F, 00000000, 14500000, 12500000, 0D814800, 0D812800, 0DA01000, 0DA03000);	//0xCC000	0x6FAA0000					0xCA000
//GET_VERSION(D2CMP, 1359, 3C686FE0, 38686FE0, 8BF78B56, 4C880424, 07C71824, CCCCCCCC, C7000005);	//0x18000	0x6FDF0000 Already Loaded	0x19000
//GET_VERSION(D2Common, 10CA, A1E86FDC, B1E86FDC, 72D03B42, F883057E, 16746AC6, 00FE81C3, 74FE85DB);	//0x8D000	0x037A0000					0x7C000	
//GET_VERSION(D2Game, 1092, 18968BF1, 38968BF1, 28968BF1, F6335608, C690C5B9, 895FD713, 56535700);	//0xF6000	0x6FC30000					0xCF000
//GET_VERSION(D2gfx, 10D, EB000000, 006FA700, 00000010, 2A000401, 19000401, 0B210E00, 00000000);	//0xB000	0x6FA70000 Already Loaded	-
//GET_VERSION(D2Lang, 126D, FC45048B, F445048B, 02C18313, C4830000, 00C6E045, 8B48408B, 0C75FF0C);	//0x0A000	0x6FC10000 Already Loaded	-
//GET_VERSION(D2Launch, 109A, 81E8526F, 01E8526F, 85E8526F, 247C8B00, 00FC6583, 15FF0424, E850E045);	//0x20000	0x6FA10000 Already Loaded	0x1E000			?
//GET_VERSION(D2Net, 16E1, 78B8A73C, 68B8A73C, 10244C8B, 5349E808, 5EA9E808, 105D8B72, 53B9E808);	//0x6000	0x6FC00000 Already Loaded	-	
//GET_VERSION(D2Win, 1699, 88686F8C, 84686F8C, D094686F, F0030000, 001435E8, 8B088F44, 0013F5E8);	//0x19000	0x6F8A0000 Already Loaded	0x1C000
//GET_VERSION(Fog, 102, D0000006, 10000001, 00000006, 000042E6, 00004302, 0000483C, 00004B95);	//0x20000	0x6FF50000 Already Loaded	0x1F000
//GET_VERSION(Storm, 1190, 19E85082, 59E85082, 13C103F6, 0474F685, 8B000321, 3B1074C9, 0D896404);	//0x30000	0x6FFB0000 Already Loaded	-

int Library::GetDllVersion()
{
	int proposedVersion;

	// You would think we would simply do the following and that's it..
	// Thing is it seems the correct math will make it so that all of our
	// values for every version, return identical values.
	// So we will keep the old way of calculating the versions by apparently
	// doing specific math that causes the numbers to either overflow or something
	// else in a way that gives us an unique result.

	// I don't really think we even need this code if you say "If game.exe is 1.13D,
	// then we will run PlugY assuming all of your dlls are 1.13D. If they aren't, then
	// you as the user will experience undesirable consequences..

	// Use *(DWORD*)([offset + shift])'s value for the "shiftedOffset" we are using to determine version.
	// Using the math directly will lead to identical values between different D2 versions.
	DWORD shiftedOffset = *(DWORD*)(DllOffset + ShiftValue);

	//log_msg("[New] Base Offset: %08X, Shift: %08X, Address: %08X, Version: %s\n", DllOffset, ShiftValue, shiftedOffset, VersionUtility::GetVersionAsString(GameVersion));

	if (GameVersion != VersionUtility::Versions::UNKNOWN && (GameVersion <= VersionUtility::Versions::V108 || GameVersion >= VersionUtility::Versions::V114a))
	{
		proposedVersion = GameVersion;
	}
	else if (shiftedOffset == Expected_Shifted_Offset_109B)
	{
		proposedVersion = VersionUtility::Versions::V109b;
	}
	else if (shiftedOffset == Expected_Shifted_Offset_109D)
	{
		proposedVersion = VersionUtility::Versions::V109d;
	}
	else if (shiftedOffset == Expected_Shifted_Offset_110)
	{
		proposedVersion = VersionUtility::Versions::V110;
	}
	else if (shiftedOffset == Expected_Shifted_Offset_111)
	{
		proposedVersion = VersionUtility::Versions::V111;
	}
	else if (shiftedOffset == Expected_Shifted_Offset_111B)
	{
		proposedVersion = VersionUtility::Versions::V111b;
	}
	else if (shiftedOffset == Expected_Shifted_Offset_112)
	{
		proposedVersion = VersionUtility::Versions::V112;
	}
	else if (shiftedOffset == Expected_Shifted_Offset_113C)
	{
		proposedVersion = VersionUtility::Versions::V113c;
	}
	else if (shiftedOffset == Expected_Shifted_Offset_113D)
	{
		proposedVersion = VersionUtility::Versions::V113d;
	}
	else
	{
		proposedVersion = GameVersion != VersionUtility::Versions::UNKNOWN ? GameVersion : VersionUtility::Versions::V113d;
		log_msg("unknown, try with ");
	}

	log_msg("%s)\n", VersionUtility::GetVersionAsString(proposedVersion));
	return proposedVersion;
}