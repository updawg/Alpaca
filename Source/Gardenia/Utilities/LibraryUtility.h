#pragma once

#include "../common.h"

#include "../Library.h"
#include "../GameLibrary.h"
#include "../D2ClientLibrary.h"
#include "../D2CMPLibrary.h"
#include "../D2CommonLibrary.h"
#include "../D2GameLibrary.h"
#include "../D2GfxLibrary.h"
#include "../D2LangLibrary.h"
#include "../D2LaunchLibrary.h"
#include "../D2NetLibrary.h"
#include "../D2WinLibrary.h"
#include "../FogLibrary.h"
#include "../StormLibrary.h"

// Used to load the libraries
class LibraryUtility
{
public:
	LibraryUtility();

	// Change the protection scheme of a loaded
	// DLL called libraryName in memory space at address addr+size to allow us to customize it.
	void HookLibraries();
	void UnhookLibraries();

	// Libraries
	GameLibrary* Game;
	D2ClientLibrary* D2Client;
	D2CMPLibrary* D2CMP;
	D2CommonLibrary* D2Common;
	D2GameLibrary* D2Game;
	D2gfxLibrary* D2gfx;
	D2LangLibrary* D2Lang;
	D2LaunchLibrary* D2Launch;
	D2NetLibrary* D2Net;
	D2WinLibrary* D2Win;
	FogLibrary* Fog;
	StormLibrary* Storm;
};