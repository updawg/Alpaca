#include "VersionUtility.h"
#include <map>
#include "../error.h"

using Versions = VersionUtility::Versions;

const char* UnknownVersion = "UNKNOWN";

const char* VersionUtility::GetVersionAsString(int version)
{
	 static std::map<int, const char*> versions = 
	 {
		 {15, "1.14d"},
		 {14, "1.14c"},
		 {13, "1.14b"},
		 {12, "1.14a"},
		 {11, "1.13d"},
		 {10, "1.13c"},
		 {9, "1.12"},
		 {8, "1.11b"},
		 {7, "1.11"},
		 {6, "1.10"},
		 {5, "1.09d"},
		 {4, "1.09b"},
		 {3, "1.09"},
		 {2, "1.08"},
		 {1, "1.07"},
		 {0, "1.00"}
	 };

	 std::map<int, const char*>::iterator iter = versions.find(version);

	 if (iter != versions.end())
	 {
		 return iter->second;
	 }

	 return UnknownVersion;
}

const bool VersionUtility::IsSupported(int version)
{
	static std::map<int, std::string> supportedVersions =
	{
		{ 11, "1.13d" },
		{ 10, "1.13c" },
		{ 9, "1.12" },
		{ 8, "1.11b" },
		{ 7, "1.11" },
		{ 6, "1.10" },
		{ 5, "1.09d" },
		{ 4, "1.09b" },
		{ 3, "1.09" }
	};

	std::map<int, std::string>::iterator iter = supportedVersions.find(version);

	if (iter != supportedVersions.end())
	{
		return true;
	}

	return false;
}

const bool VersionUtility::IsEqualOrGreaterThan114(int version)
{
	return version >= VersionUtility::Versions::V114a;
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