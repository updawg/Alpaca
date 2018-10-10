// Copyright (C) 2004-2017 Yohann Nicolas
// Copyright (C) 2017 L'Autour
// Copyright (C) 2017-2018 Jonathan Vasquez <jon@xyinn.org>
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

#include "Resource.h"
#include <stdlib.h>
#include <stdio.h>
#include "../Alpaca/Utilities/VersionUtility.h"

#define MAX_LOADSTRING 100
#define SUBKEY "Software\\Blizzard Entertainment\\Diablo II"
#define GAMEFILE "Game.exe"
#define INIFILE "Alpaca.ini"
#define LAUNCHING "LAUNCHING"
#define LOD_VERSION "LodVersionFolder"
#define PARAM "Param"
#define WINDOWED "Windowed"
#define ACTIVE_WINDOWED "ActiveWindowed"
#define LIBRARY_NAME "Library"

const char* PROGRAM_NAME = "Alpaca";

BYTE loadDll[] = {
	0xFF,0x74,0x24,0x04,			//PUSH DWORD PTR SS:[ESP+4]
	0xFF,0x15,0x40,0xC0,0xA7,0x6F,  //CALL DWORD PTR DS:[<&KERNEL32.LoadLibraryA>]      ; kernel32.LoadLibraryA
	0x50,							//PUSH EAX
	0x68,0x80,0xBE,0xA7,0x6F,		//PUSH d2gfx.6FA7BE80                               ; ASCII "PlugY.dll"
	0xFF,0x15,0x40,0xC0,0xA7,0x6F,  //CALL DWORD PTR DS:[<&KERNEL32.LoadLibraryA>]      ; kernel32.LoadLibraryA
	0xA3,0xFC,0xEF,0xA8,0x6F,		//MOV DWORD PTR DS:[6FA8EFFC],EAX
	0x85,0xC0,						//TEST EAX,EAX
	0x74,0x2B,						//JE SHORT d2gfx.6FA7BE33
	0x50,							//PUSH EAX
	0x68,0x90,0xBE,0xA7,0x6F,		//PUSH d2gfx.6FA7BE10                            ;Init String
	0x50,							//PUSH EAX
	0xFF,0x15,0x3C,0xC0,0xA7,0x6F,	//CALL DWORD PTR DS:[<&KERNEL32.GetProcAddress>]    ; kernel32.GetProcAddress
	0x85,0xC0,						//TEST EAX,EAX
	0x74,0x04,						//JE SHORT d2gfx.6FA7BDC1
	0x6A,0x00,						//PUSH 0
	0xEB,0x13,						//JMP SHORT d2gfx.6FA7BDC1
	0x68,0x10,0x27,0x00,0x00,		//PUSH 2710	                                     ;Init Ordinal(10000)
	0xFF,0x74,0x24,0x04,			//PUSH DWORD PTR SS:[ESP+4]
	0xFF,0x15,0x3C,0xC0,0xA7,0x6F,	//CALL DWORD PTR DS:[<&KERNEL32.GetProcAddress>]    ; kernel32.GetProcAddress
	0x85,0xC0,						//TEST EAX,EAX
	0x74,0x02,						//JE SHORT d2gfx.6FA7BDC1
	0xFF,0xD0,						//CALL EAX
	0x58,							//POP EAX
	0x58,							//POP EAX
	0xC2,0x04,0x00,					//RETN 4
	0x00,0x00,0x00,0x00 };			//HANDLE var;

BYTE freeDll[] = {
	0xFF,0x74,0x24,0x04,			//PUSH DWORD PTR SS:[ESP+4]
	0xFF,0x15,0x48,0xC0,0xA7,0x6F,  //CALL DWORD PTR DS:[<&KERNEL32.FreeLibrary>]       ; kernel32.FreeLibrary
	0x50,							//PUSH EAX
	0xA1,0xFC,0xEF,0xA8,0x6F,		//MOV EAX,DWORD PTR DS:[6FA8EFFC]
	0x85,0xC0,						//TEST EAX,EAX
	0x74,0x2D,						//JE SHORT d2gfx.6FA7BE74
	0x50,							//PUSH EAX
	0x68,0xA0,0xBE,0xA7,0x6F,		//PUSH d2gfx.6FA7BE20                            ;Release String
	0x50,							//PUSH EAX
	//0x33,0xC0,					//XOR EAX,EAX
	//0xA3,0xFC,0xEF,0xA8,0x6F,		//MOV DWORD PTR DS:[6FA8EFFC],EAX
	0xFF,0x15,0x3C,0xC0,0xA7,0x6F,	//CALL DWORD PTR DS:[<&KERNEL32.GetProcAdd>; kernel32.GetProcAddress
	0x85,0xC0,						//TEST EAX,EAX
	0x75,0x13,						//JNZ SHORT d2gfx.6FA7BDEF
	0x68,0x11,0x27,0x00,0x00,		//PUSH 2711	                                     ;Release Ordinal(10001)
	0xFF,0x74,0x24,0x04,			//PUSH DWORD PTR SS:[ESP+4]
	0xFF,0x15,0x3C,0xC0,0xA7,0x6F,	//CALL DWORD PTR DS:[<&KERNEL32.GetProcAdd>; kernel32.GetProcAddress
	0x85,0xC0,						//TEST EAX,EAX
	0x74,0x02,						//JE SHORT d2gfx.6FA7BDEF
	0xFF,0xD0,						//CALL EAX
	0xFF,0x15,0x48,0xC0,0xA7,0x6F,  //CALL DWORD PTR DS:[<&KERNEL32.FreeLibrar>; kernel32.FreeLibrary
	0x58,							//POP EAX
	0xC2,0x04,0x00 };				//RETN 4

LPCSTR initFctName = "_Init@4";
LPCSTR releaseFctName = "_Release@0";

typedef int(__stdcall* tDebugActiveProcessStop)(DWORD);
tDebugActiveProcessStop debugActiveProcessStop;

void assertion(const char* pFormat, ...)
{
	char msg[200];
	va_list lArgs;
	va_start(lArgs, pFormat);

	vsprintf(&msg[0], pFormat, lArgs);

	va_end(lArgs);
	MessageBox(0, msg, PROGRAM_NAME, MB_OK | MB_ICONASTERISK);
	exit(1);
}

bool installPlugY(HANDLE h, LPBYTE addr, char* libraryName, VersionUtility::Versions version)
{
	LPBYTE loadCallerAddr = addr;
	LPBYTE freeCallerAddr = addr;
	LPBYTE loadLibraryAddr = addr;
	LPBYTE freeLibraryAddr = addr;
	LPBYTE getProcAddressAddr = addr;

	if (version != VersionUtility::Versions::V109b) return false;
	
	loadCallerAddr += 0x389B;
	freeCallerAddr += 0x3A8C;
	loadLibraryAddr += 0xC03C;
	freeLibraryAddr += 0xC044;
	getProcAddressAddr += 0xC038;
	
	BYTE buf[200];
	DWORD pos = 0;
	SIZE_T nb = 0;
	int res;

	// Verify if memory are ok.
	bool alreadyInstalled = false;
	res = ReadProcessMemory(h, (LPVOID)loadCallerAddr, buf, 6, &nb);
	if (!res || nb < 6)
	{
		assertion("Alpaca: Read process memory failed. [1]");
	}

	if (buf[0] != 0xFF || buf[1] != 0x15 || *(LPBYTE*)(buf + 2) != loadLibraryAddr)
	{
		if (buf[0] != 0xE8 || buf[3] != 0x00 || buf[4] != 0x00 || buf[5] != 0x90)
		{
			assertion("Alpaca: Read process memory failed. [2]");
		}
		else
		{
			alreadyInstalled = true;
		}
	}
		
	res = ReadProcessMemory(h, (LPVOID)freeCallerAddr, buf, 6, &nb);
	if (!res || nb < 6)
	{
		assertion("Alpaca: Read process memory failed. [3]");
	}

	if (buf[0] != 0xFF || buf[1] != 0x15 || *(LPBYTE*)(buf + 2) != freeLibraryAddr)
	{
		if (buf[0] != 0xE8 || buf[3] != 0x00 || buf[4] != 0x00 || buf[5] != 0x90)
		{
			if (!alreadyInstalled)
			{
				assertion("Alpaca: Read process memory failed. [4]");
			}
		}
	}	

	if (alreadyInstalled) return true;

	// Alloc custom memory data.
	LPBYTE memory =  (LPBYTE)VirtualAllocEx(h, NULL, 200, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	DWORD oldProtect = -1;
	if (!memory)
	{
		res = ReadProcessMemory(h, addr, buf, 0x40, &nb);
		if (!res || nb < 0x40)
		{
			assertion("Alpaca: Read process memory failed. [5]");
		}

		DWORD offsetPESignature = *(WORD*)(buf + 0x3C);
		res = ReadProcessMemory(h, addr + offsetPESignature, buf, 0x30, &nb);

		if (!res || nb < 0x30)
		{
			assertion("Alpaca: Read process memory failed. [6]");
		}

		DWORD sizeOfCode = *(DWORD*)(buf + 0x1C);
		DWORD baseOfCode = *(DWORD*)(buf + 0x2C);

		memory = addr + baseOfCode + sizeOfCode - 200;
		if (!VirtualProtectEx(h, memory, 200, PAGE_EXECUTE_READWRITE, &oldProtect))
		{
			assertion("Alpaca: Failed to get memory pool in game thread");
		}
	}

	// Make memory data
	int len;
	pos = 0;

	// Dll name
	LPBYTE dllNameAddr = memory + pos;
	len = strlen(libraryName) + 1;
	res = WriteProcessMemory(h, dllNameAddr, libraryName, len, &nb);
	if (!res || (nb != len)) assertion("Alpaca: Write custom data in memory failed");
	pos += pos % 16 ? len + 16 - pos % 16 : len;

	// Init name
	LPBYTE initNameAddr = memory + pos;
	len = strlen(initFctName) + 1;
	res = WriteProcessMemory(h, initNameAddr, initFctName, len, &nb);
	if (!res || (nb != len)) assertion("Alpaca: Write custom data in memory failed");
	pos += pos % 16 ? len + 16 - pos % 16 : len;

	// Release name
	LPBYTE releaseNameAddr = memory + pos;
	len = strlen(releaseFctName) + 1;
	res = WriteProcessMemory(h, releaseNameAddr, releaseFctName, len, &nb);
	if (!res || (nb != len)) assertion("Alpaca: Write custom data in memory failed");
	pos += pos % 16 ? len + 16 - pos % 16 : len;

	// Load fct
	LPBYTE loadDllAddr = memory + pos;
	LPBYTE handleAddr = loadDllAddr + sizeof(loadDll) - 4;
	*(LPBYTE*)&loadDll[6] = loadLibraryAddr;
	*(LPBYTE*)&loadDll[12] = dllNameAddr;
	*(LPBYTE*)&loadDll[18] = loadLibraryAddr;
	*(LPBYTE*)&loadDll[23] = handleAddr;
	*(LPBYTE*)&loadDll[33] = initNameAddr;
	*(LPBYTE*)&loadDll[40] = getProcAddressAddr;
	*(LPBYTE*)&loadDll[63] = getProcAddressAddr;
	len = sizeof(loadDll);
	res = WriteProcessMemory(h, loadDllAddr, loadDll, len, &nb);
	if (!res || (nb != len)) assertion("Alpaca: Write custom data in memory failed");
	pos += pos % 16 ? len + 16 - pos % 16 : len;

	// Free fct
	LPBYTE freeDllAddr = memory + pos;
	*(LPBYTE*)&freeDll[6] = freeLibraryAddr;
	*(LPBYTE*)&freeDll[12] = handleAddr;
	*(LPBYTE*)&freeDll[22] = releaseNameAddr;
	*(LPBYTE*)&freeDll[29] = getProcAddressAddr;
	*(LPBYTE*)&freeDll[48] = getProcAddressAddr;
	*(LPBYTE*)&freeDll[60] = freeLibraryAddr;
	len = sizeof(freeDll);
	res = WriteProcessMemory(h, freeDllAddr, freeDll, len, &nb);
	if (!res || (nb != len)) assertion("Alpaca: Write custom data in memory failed");
	pos += pos % 16 ? len + 16 - pos % 16 : len;

	// Patch load library
	buf[0] = 0x90;
	buf[1] = 0xE8;
	*(DWORD*)(buf + 2) = (DWORD)loadDllAddr - (DWORD)loadCallerAddr - 6;
	len = 6;
	res = WriteProcessMemory(h, loadCallerAddr, buf, len, &nb);
	if (!res || (nb != len)) assertion("Alpaca: Write load library in memory failed");

	// Patch free library
	*(DWORD*)(buf + 2) = (DWORD)freeDllAddr - (DWORD)freeCallerAddr - 6;
	res = WriteProcessMemory(h, freeCallerAddr, buf, len, &nb);
	if (!res || (nb != len)) assertion("Alpaca: Write free library in memory failed");

	return true;
}

#define BUF_SIZE 0x300
bool isD2gfxLoaded(HANDLE hProcess, LPVOID addr)
{
	SIZE_T nbRead;
	BYTE buf[BUF_SIZE];
	ReadProcessMemory(hProcess, addr, buf, BUF_SIZE, &nbRead);
	if (nbRead < 0x60) return false;
	int offsetPESignature = *(DWORD*)(buf + 0x3C);
	if (offsetPESignature + 0x5C >= BUF_SIZE) return false;
	DWORD ImageBase = *(DWORD*)(buf + offsetPESignature + 0x34);
	DWORD SizeOfImage = *(DWORD*)(buf + offsetPESignature + 0x50);
	DWORD CheckSum = *(DWORD*)(buf + offsetPESignature + 0x58);

	if (ImageBase == 0x6FA70000 && SizeOfImage == 0x00021000 && CheckSum == 0x00000000) return true; // 1.09 - 1.09b - 1.09d - 1.10

	return false;
}

bool getRegistryD2Directory(LPSTR buf, DWORD bufsize)
{
	HKEY hKey;
	DWORD type;
	int res;
	DWORD len = bufsize - 1;
	if (RegOpenKeyEx(HKEY_CURRENT_USER, SUBKEY, 0, KEY_READ, &hKey) == ERROR_SUCCESS)
	{
		res = RegQueryValueEx(hKey, "InstallPath", NULL, &type, (LPBYTE)buf, &len);
		RegCloseKey(hKey);
		if (res != ERROR_SUCCESS) return false;
	}
	else if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, SUBKEY, 0, KEY_READ, &hKey) == ERROR_SUCCESS)
	{
		res = RegQueryValueEx(hKey, "InstallPath", NULL, &type, (LPBYTE)buf, &len);
		RegCloseKey(hKey);
		if (res != ERROR_SUCCESS) return false;
	}
	else
		return false;

	if (len <= 1)
		return false;
	if (buf[len - 1] != NULL)
		buf[len] = NULL;
	else
		len--;
	if (buf[len - 1] != '\\')
	{
		buf[len++] = '\\';
		buf[len] = NULL;
	}
	return true;
}

bool launchNormal(LPSTR commandLine, LPSTR currentDirectory)
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	BOOL success = CreateProcess(NULL, commandLine, NULL, NULL, false, 0, NULL, currentDirectory, &si, &pi); //DEBUG_ONLY_THIS_PROCESS
	return success ? true : false;
}

bool launchGame98(LPSTR commandLine, LPSTR currentDirectory, LPSTR libraryName, VersionUtility::Versions version)
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	BOOL success = CreateProcess(0, commandLine, 0, 0, false, 0, 0, currentDirectory, &si, &pi); //DEBUG_ONLY_THIS_PROCESS
	if (!success) return false;
	DWORD ret;

	Sleep(10);
	while (true)
	{
		SuspendThread(pi.hThread);

		if (!GetExitCodeProcess(pi.hProcess, &ret) || (ret != STILL_ACTIVE))
			exit(0);
		if (isD2gfxLoaded(pi.hProcess, (LPVOID)0x6FA80000))
		{
			installPlugY(pi.hProcess, (LPBYTE)0x6FA80000, libraryName, version);
			ResumeThread(pi.hThread);
			return true;
		}
		if (isD2gfxLoaded(pi.hProcess, (LPVOID)0x6FA70000))
		{
			installPlugY(pi.hProcess, (LPBYTE)0x6FA70000, libraryName, version);
			ResumeThread(pi.hThread);
			return true;
		}
		if (isD2gfxLoaded(pi.hProcess, (LPVOID)0x6FAA0000))
		{
			installPlugY(pi.hProcess, (LPBYTE)0x6FAA0000, libraryName, version);
			ResumeThread(pi.hThread);
			return true;
		}
		ResumeThread(pi.hThread);
	}
	return false;
}

bool launchGameXP(LPSTR commandLine, LPSTR currentDirectory, LPSTR libraryName, VersionUtility::Versions version)
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	BOOL success = CreateProcess(0, commandLine, 0, 0, false, DEBUG_PROCESS, 0, currentDirectory, &si, &pi); //DEBUG_ONLY_THIS_PROCESS
	if (!success) return false;
	DEBUG_EVENT DebugEvent;
	DWORD status;
	while (WaitForDebugEvent(&DebugEvent, INFINITE))
	{
		status = DBG_CONTINUE;
		switch (DebugEvent.dwDebugEventCode)
		{
		case CREATE_THREAD_DEBUG_EVENT:
		case CREATE_PROCESS_DEBUG_EVENT:
			CloseHandle(DebugEvent.u.CreateThread.hThread);
			break;
		case EXIT_PROCESS_DEBUG_EVENT:
			exit(0);
		case EXCEPTION_DEBUG_EVENT:
			if (DebugEvent.u.Exception.ExceptionRecord.ExceptionCode == EXCEPTION_ACCESS_VIOLATION)
			{
				MessageBox(0, "EXCEPTION_ACCESS_VIOLATION", "Alpaca", MB_OK | MB_ICONASTERISK);
			}
			break;
		case LOAD_DLL_DEBUG_EVENT:
			// Only 1.09b is supported.
			if (version == VersionUtility::Versions::V109b && isD2gfxLoaded(pi.hProcess, DebugEvent.u.LoadDll.lpBaseOfDll))
			{
				installPlugY(pi.hProcess, (LPBYTE)DebugEvent.u.LoadDll.lpBaseOfDll, libraryName, version);
				CloseHandle(DebugEvent.u.LoadDll.hFile);
				CloseHandle(pi.hProcess);
				CloseHandle(pi.hThread);
				debugActiveProcessStop(DebugEvent.dwProcessId);
				return true;
			}
			else
			{
				CloseHandle(DebugEvent.u.LoadDll.hFile);
			}
			break;
		}
		ContinueDebugEvent(DebugEvent.dwProcessId, DebugEvent.dwThreadId, status);
	}
	MessageBox(0, "ERROR : Alpaca isn't installed", "Alpaca", MB_OK | MB_ICONASTERISK);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	return false;
}

int APIENTRY WinMain (
    __in HINSTANCE hInstance,
    __in_opt HINSTANCE hPrevInstance,
    __in_opt LPSTR lpCmdLine,
    __in int nShowCmd
    )
{
	char currrentDirectory[MAX_PATH];
	char iniFileName[MAX_PATH + sizeof(INIFILE) - 1];
	char command[MAX_PATH + sizeof(GAMEFILE) + 200];
	VersionUtility::Versions version;

	// Get Current Directory.
	if (!GetCurrentDirectory(MAX_PATH - 1, currrentDirectory))
		assertion("Current directory not found");

	int len = strlen(currrentDirectory);
	if (len == 0)
		assertion("Current directory not found");

	if (currrentDirectory[len - 1] != '\\')
	{
		currrentDirectory[len++] = '\\';
		currrentDirectory[len] = NULL;
	}

	// Get ini full path name.
	strcpy(iniFileName, currrentDirectory);
	strcat(iniFileName, INIFILE);

	// Get game.exe path.
	strcpy(command, currrentDirectory);
	strcat(command, GAMEFILE);

	if (GetFileAttributes(command) == INVALID_FILE_ATTRIBUTES)
	{
		if (!getRegistryD2Directory(command, MAX_PATH - sizeof(GAMEFILE)))
		{
			assertion("The Diablo II install path was not found.");
			return 1;
		}
		strcat(command, GAMEFILE);
		if (GetFileAttributes(command) == INVALID_FILE_ATTRIBUTES)
		{
			assertion("Game.exe was not found.");
			return 1;
		}
	}

	// Get Game.exe version.
	version = VersionUtility::GetVersion(command);

	// Add params.
	len = strlen(command);
	int windowed = GetPrivateProfileInt(WINDOWED, ACTIVE_WINDOWED, 0, iniFileName);
	if (windowed)
	{
		len += 3;
		if (len > sizeof(command))
			assertion("Command too long");
		strcat(command, " -w");
	}
	int paramLen = strlen(lpCmdLine);
	if (paramLen > 0)
	{
		len += 1 + paramLen;
		if (len > sizeof(command))
			assertion("Command too long");
		strcat(command, " ");
		strcat(command, lpCmdLine);
	}
	len++;
	if (len >= sizeof(command))
		assertion("Command too long");
	strcat(command, " ");
	GetPrivateProfileString(LAUNCHING, PARAM, NULL, command + len, sizeof(command) - len, iniFileName);

	// Check if Alpaca must be started.
	char libraryName[50];
	if (!GetPrivateProfileString(LAUNCHING, LIBRARY_NAME, "", libraryName, 50, iniFileName) || !libraryName[0])
		return !launchNormal(command, currrentDirectory);

	// Check version
	if (version != VersionUtility::Versions::V109b)
	{
		VersionUtility::SetVersion(version);
		assertion("Alpaca isn't compatible with this version of Diablo II: %s", VersionUtility::GetVersionAsString());
	}

	// Launch LoD and install PlugY
	HMODULE module = GetModuleHandle("Kernel32.dll");
	if (module)
	{
		debugActiveProcessStop = (tDebugActiveProcessStop)GetProcAddress(module, "DebugActiveProcessStop");
		if (debugActiveProcessStop)
		{
			return !launchGameXP(command, currrentDirectory, libraryName, version);
		}
	}
	return !launchGame98(command, currrentDirectory, libraryName, version);
}