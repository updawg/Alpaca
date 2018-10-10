// Copyright (C) 2004-2017 Yohann Nicolas
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

#include "parameters.h"
#include "Error.h"
#include <windows.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <direct.h>

DWORD active_logFile = 1;

// This value is just used in order to decide whether or
// not we will keep logging enable since logging will be
// stopped if we log and then read the ini file with a disabled
// logging value.
DWORD active_logFileIniOriginal = 0;

static char log_file[MAX_PATH] = "";
static bool log_init = false;

void log_initfile()
{
	if (log_init) return;
	
	_getcwd( log_file, MAX_PATH );
	if( log_file[strlen(log_file)] != '\\')
		strcat(log_file, "\\");
	strcat(log_file, "Alpaca.log");
	
	FILE* lLog = fopen( log_file, "w" );
	
	if( lLog != NULL )
    {
	    fclose(lLog);
	    log_init = true;
	}
	
	log_msg("%s %s\n"
		"%s (%s)\n"
		    "%s\n"
			"====================================\n\n"
			, PROGRAM_NAME, PROGRAM_VERSION, PROGRAM_AUTHOR_NAME, PROGRAM_AUTHOR_ALIAS, PROGRAM_BUILD_DATE);
}

void log_box( const char* pFormat, ... )
{
	char buffer[300];
	va_list lArgs;
	va_start( lArgs, pFormat );
	vsprintf( buffer, pFormat, lArgs );
	va_end(lArgs);

	log_msg(buffer);
	MessageBox(NULL, buffer, PROGRAM_NAME, MB_OK|MB_ICONEXCLAMATION);
}


void log_msg( const char* pFormat, ... )
{
	if (!active_logFile) return;

	if( !log_init )
		log_initfile();

	if( log_init )
	{
		va_list lArgs;
		va_start( lArgs, pFormat );

		FILE *lDebug = fopen( log_file, "a" );

		if( lDebug != NULL )
		{
			vfprintf( lDebug, pFormat, lArgs );
			fclose( lDebug );
	    }
		else
			log_init = false;

		va_end(lArgs);
	}
}

void d2_assert( bool pCondition, char* pMessage, char* pLocation, int pLineNbr )
{
	if( pCondition )
	{
		log_msg("\n"
			"*-----------------------*\n"
			"Assertion fail at line %d of %s :\n"
			"%s\n"
			"*-----------------------*\n",
			pLineNbr, pLocation, pMessage);
		MessageBox(NULL, pMessage, "Diablo 2 Error", MB_OK|MB_ICONEXCLAMATION);
		exit(1);
	}
}

