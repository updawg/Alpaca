#include "VersionUtility.h"

using Versions = VersionUtility::Versions;

const char* VersionUtility::GetVersionAsString(int version)
{
	const char* VersionStrings[16] = { "1.00","1.07","1.08","1.09","1.09b","1.09d","1.10","1.11","1.11b","1.12","1.13c","1.13d","1.14a","1.14b","1.14c","1.14d" };

	if (version < Versions::V100 || version >= sizeof(VersionStrings))
		return "UNKNOWN";
	return VersionStrings[version];
}

VersionUtility::Versions VersionUtility::GetVersion(LPCVOID pVersionResource)
{
	if (!pVersionResource) return Versions::UNKNOWN;

	UINT uLen;
	VS_FIXEDFILEINFO* ptFixedFileInfo;
	if (!VerQueryValue(pVersionResource, "\\", (LPVOID*)&ptFixedFileInfo, &uLen))
		return Versions::UNKNOWN;

	if (uLen == 0)
		return Versions::UNKNOWN;

	WORD major = HIWORD(ptFixedFileInfo->dwFileVersionMS);
	WORD minor = LOWORD(ptFixedFileInfo->dwFileVersionMS);
	WORD revision = HIWORD(ptFixedFileInfo->dwFileVersionLS);
	WORD subrevision = LOWORD(ptFixedFileInfo->dwFileVersionLS);

	if (major != 1)
		return Versions::UNKNOWN;
	if (minor == 0 && revision == 7 && subrevision == 0) return Versions::V107;
	if (minor == 0 && revision == 8 && subrevision == 28) return Versions::V108;
	if (minor == 0 && revision == 9 && subrevision == 19) return Versions::V109;
	if (minor == 0 && revision == 9 && subrevision == 20) return Versions::V109b;
	if (minor == 0 && revision == 9 && subrevision == 22) return Versions::V109d;
	if (minor == 0 && revision == 10 && subrevision == 39) return Versions::V110;
	if (minor == 0 && revision == 11 && subrevision == 45) return Versions::V111;
	if (minor == 0 && revision == 11 && subrevision == 46) return Versions::V111b;
	if (minor == 0 && revision == 12 && subrevision == 49) return Versions::V112;
	if (minor == 0 && revision == 13 && subrevision == 60) return Versions::V113c;
	if (minor == 0 && revision == 13 && subrevision == 64) return Versions::V113d;
	if (minor == 14 && revision == 0 && subrevision == 64) return Versions::V114a;
	if (minor == 14 && revision == 1 && subrevision == 68) return Versions::V114b;
	if (minor == 14 && revision == 2 && subrevision == 70) return Versions::V114c;
	if (minor == 14 && revision == 3 && subrevision == 71) return Versions::V114d;
	return Versions::UNKNOWN;
}

Versions VersionUtility::GetVersion(char* gameExe)
{
	DWORD len = GetFileVersionInfoSize(gameExe, NULL);
	if (len == 0)
		return Versions::UNKNOWN;

	BYTE* pVersionResource = new BYTE[len];
	GetFileVersionInfo(gameExe, NULL, len, pVersionResource);
	Versions version = GetVersion(pVersionResource);
	delete pVersionResource;

	return version;
}

Versions VersionUtility::GetVersion(HMODULE hModule)
{
	HRSRC hResInfo = FindResource(hModule, MAKEINTRESOURCE(VS_VERSION_INFO), RT_VERSION);
	if (!hResInfo) return Versions::UNKNOWN;
	HGLOBAL hResData = LoadResource(hModule, hResInfo);
	if (!hResData) return Versions::UNKNOWN;
	LPVOID pVersionResource = LockResource(hResData);
	Versions version = GetVersion(pVersionResource);
	FreeResource(hResData);
	return version;
}