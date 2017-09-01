#pragma once

#include "Library.h"

class D2NetLibrary : public Library
{
public:
	D2NetLibrary(DWORD gameOffset, int gameVersion) : Library(gameOffset, gameVersion)
	{
		DllName = "D2Net.dll";
		DllOffset = LoadDiabloLibrary();
		DllVersion = GameVersion;
		SetFunctions();
	};

	typedef DWORD(__stdcall *TD2SendToServer) (DWORD size, DWORD one, void* data);
	typedef DWORD(__stdcall *TD2SendToClient) (DWORD zero, DWORD clientID, void* data, DWORD size);

	TD2SendToServer D2SendToServer;
	TD2SendToClient D2SendToClient;
private:
	void SetFunctions();

	TD2SendToServer GetD2SendToServer();
	TD2SendToClient GetD2SendToClient();
};