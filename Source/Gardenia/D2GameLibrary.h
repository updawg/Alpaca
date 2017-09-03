#pragma once

#include "Library.h"

class D2GameLibrary : public Library
{
public:
	D2GameLibrary(int gameVersion) : Library()
	{
		DllName = "D2Game.dll";
		DllVersion = gameVersion;
		DllOffset = LoadDiabloLibrary();
		SetFunctions();
	};

	typedef void(__fastcall *TD2SetNbPlayers) (DWORD nbPlayers);
	typedef Game* (__stdcall *TD2GetGameByClientID) (DWORD clientID);
	typedef void(__fastcall *TD2BroadcastFunction) (Game* ptGame, void* fct, void* param);
	typedef DWORD(__fastcall *TD2SendPacket) (void* ptNetClient, LPVOID pData, DWORD size);
	typedef void(__fastcall *TD2SetSkillBaseLevelOnClient) (void* ptClient, Unit* ptChar, DWORD skillID, DWORD sLvl, DWORD bRemove);
	typedef DWORD(__stdcall *TD2LinkPortal) (Game* ptGame, Unit* ptObject, DWORD levelEndID, DWORD levelStartID);
	typedef DWORD(__fastcall *TD2VerifIfNotCarry1) (Unit* ptItem, ItemsBIN* itemsData, Unit* ptFirstItem);
	typedef Room* (__fastcall *TD2TestPositionInRoom) (Room* ptRoom, DWORD x, DWORD y);
	typedef DWORD(__fastcall *TD2LoadInventory) (Game* ptGame, Unit* pChar, saveBitField* pdata, DWORD p2, DWORD maxSize, DWORD p4, DWORD *ptNbBytesRead);
	typedef Unit* (__fastcall *TD2GameGetObject) (Game* ptGame, DWORD type, DWORD itemNum);
	typedef void(__stdcall *TD2SaveGame) (Game* ptGame);

	TD2SetNbPlayers D2SetNbPlayers;
	TD2SendPacket D2SendPacket;
	TD2SetSkillBaseLevelOnClient D2SetSkillBaseLevelOnClient;
	TD2LinkPortal D2LinkPortal;
	TD2VerifIfNotCarry1 D2VerifIfNotCarry1;
	TD2TestPositionInRoom D2TestPositionInRoom;
	TD2LoadInventory D2LoadInventory;
	TD2GameGetObject D2GameGetObject;
	TD2SaveGame D2SaveGame;

	// Until 1.10
	typedef NetClient* (__fastcall *TD2GetClient) (Unit* ptUnit, char* lpszErrFile, DWORD ErrLine);

	TD2GetClient D2GetClient;

	// Variables
	NetClient** ptClientTable;
private:
	void SetFunctions();
};