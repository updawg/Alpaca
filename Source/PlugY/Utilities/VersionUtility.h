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

	// , "1.14a", "1.14b", "1.14c", "1.14d"

	static const bool VersionUtility::IsSupported(int version);
	static const char* GetVersionAsString(int version);
	static const bool VersionUtility::IsEqualOrGreaterThan114(int version);

	static Versions GetVersion(LPCVOID pVersionResource);
	static Versions GetVersion(char* gamePath);
	static Versions GetVersion(HMODULE hModule);
};