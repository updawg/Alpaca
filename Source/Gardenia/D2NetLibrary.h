#pragma once

#include "Library.h"

class D2NetLibrary : public Library
{
public:
	D2NetLibrary(int gameVersion) : Library()
	{
		DllName = "D2Net.dll";
		DllVersion = gameVersion;
		DllOffset = LoadDiabloLibrary();
		SetFunctions();
	};

	typedef DWORD(__stdcall *TD2SendToServer) (DWORD size, DWORD one, void* data);
	typedef DWORD(__stdcall *TD2SendToClient) (DWORD zero, DWORD clientID, void* data, DWORD size);

	TD2SendToServer D2SendToServer;
	TD2SendToClient D2SendToClient;
private:
	void SetFunctions();
};