#pragma once

#include "Library.h"

class GameLibrary : public Library
{
public:
	GameLibrary() : Library()
	{
		DllName = "Game.exe";
		DllOffset = (DWORD)GetModuleHandle(NULL);
		DllVersion = VersionUtility::GetVersion("Game.exe");
		log_msg("Game.exe loaded at:\t%08X (%s)\n", DllOffset, VersionUtility::GetVersionAsString(DllVersion));
		SetFunctions();
	};
private:
	void SetFunctions();
};