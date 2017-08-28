/******************************************************************************
File modified by Yohann NICOLAS.

NAME
inifile.h

DESCRIPTION
Memory cached INI file read/write class to replace legacy MS code

COPYRIGHT
©1999-2004 Ultrafunk (www.ultrafunk.com) - info@ultrafunk.com

******************************************************************************/
#pragma once

#include <windows.h>
// New library loading stuff
//#include "Utilities/LibraryUtility.h"

// Forward declare so we can make our 'lu' an extern.
class LibraryUtility;

extern int version_Game;
extern int version_D2Client;
extern int version_D2CMP;
extern int version_D2Common;
extern int version_D2Game;
extern int version_D2gfx;
extern int version_D2Lang;
extern int version_D2Launch;
extern int version_D2Net;
extern int version_D2Win;
extern int version_Fog;
extern int version_Storm;

// Address in memory of external DLL
extern DWORD offset_Game;
extern DWORD offset_D2Client;
extern DWORD offset_D2CMP;
extern DWORD offset_D2Common;
extern DWORD offset_D2Game;
extern DWORD offset_D2gfx;
extern DWORD offset_D2Lang;
extern DWORD offset_D2Launch;
extern DWORD offset_D2Net;
extern DWORD offset_D2Win;
extern DWORD offset_Fog;
extern DWORD offset_Storm;

extern LibraryUtility* lu;