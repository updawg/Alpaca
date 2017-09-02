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
	typedef void(__fastcall *TD2AddClient) (DWORD clientID);
	typedef Game* (__stdcall *TD2GetGameByClientID) (DWORD clientID);
	typedef void(__fastcall *TD2BroadcastFunction) (Game* ptGame, void* fct, void* param);
	typedef DWORD(__fastcall *TD2SendPacket) (void* ptNetClient, LPVOID pData, DWORD size);
	typedef void(__fastcall *TD2SetSkillBaseLevelOnClient) (void* ptClient, Unit* ptChar, DWORD skillID, DWORD sLvl, DWORD bRemove);
	typedef DWORD(__stdcall *TD2LinkPortal) (Game* ptGame, Unit* ptObject, DWORD levelEndID, DWORD levelStartID);
	typedef DWORD(__fastcall *TD2VerifIfNotCarry1) (Unit* ptItem, ItemsBIN* itemsData, Unit* ptFirstItem);
	typedef Room* (__fastcall *TD2TestPositionInRoom) (Room* ptRoom, DWORD x, DWORD y);
	typedef DWORD(__fastcall *TD2SpawnMonster) (Game* ptGame, Room* ptRoom, DWORD zero1, DWORD x, DWORD y, DWORD minusOne, DWORD superuniqueID, DWORD zero2);
	typedef void(__stdcall *TD2Game235C0) (Game* ptGame, Room* ptRoom);
	typedef DWORD(__fastcall *TD2LoadInventory) (Game* ptGame, Unit* pChar, saveBitField* pdata, DWORD p2, DWORD maxSize, DWORD p4, DWORD *ptNbBytesRead);
	typedef Unit* (__fastcall *TD2GameGetObject) (Game* ptGame, DWORD type, DWORD itemNum);
	typedef Unit* (__fastcall *TD2CreateUnit) (DWORD type, DWORD id, DWORD x, DWORD y, Game* ptGame, Room* ptRoom, DWORD uk1, DWORD uk2, DWORD uk3);
	typedef void(__fastcall *TD2OpenPandPortal) (Game* ptGame, Unit* ptChar);
	typedef void(__fastcall *TD2OpenPandFinalPortal) (Game* ptGame, Unit* ptChar);
	typedef void(__fastcall *TD2MephIA) (Game* ptGame, Unit* ptMonster, DWORD*);
	typedef void(__fastcall *TD2DiabloIA) (Game* ptGame, Unit* ptMonster, DWORD*);
	typedef void(__fastcall *TD2BaalIA) (Game* ptGame, Unit* ptMonster, DWORD*);
	typedef void(__fastcall *TD2UberMephIA) (Game* ptGame, Unit* ptMonster, DWORD*);
	typedef void(__fastcall *TD2UberDiabloIA) (Game* ptGame, Unit* ptMonster, DWORD*);
	typedef void(__fastcall *TD2UberBaalIA) (Game* ptGame, Unit* ptMonster, DWORD*);
	typedef void(__stdcall *TD2SaveGame) (Game* ptGame);

	TD2SetNbPlayers D2SetNbPlayers;
	TD2AddClient D2AddClient;
	TD2GetGameByClientID D2GetGameByClientID;
	TD2BroadcastFunction D2BroadcastFunction;
	TD2SendPacket D2SendPacket;
	TD2SetSkillBaseLevelOnClient D2SetSkillBaseLevelOnClient;
	TD2LinkPortal D2LinkPortal;
	TD2VerifIfNotCarry1 D2VerifIfNotCarry1;
	TD2TestPositionInRoom D2TestPositionInRoom;
	TD2SpawnMonster D2SpawnMonster;
	TD2Game235C0 D2Game235C0;
	TD2LoadInventory D2LoadInventory;
	TD2GameGetObject D2GameGetObject;
	TD2CreateUnit D2CreateUnit;
	TD2OpenPandPortal D2OpenPandPortal;
	TD2OpenPandFinalPortal D2OpenPandFinalPortal;
	TD2MephIA D2MephIA;
	TD2DiabloIA D2DiabloIA;
	TD2BaalIA D2BaalIA;
	TD2UberMephIA D2UberMephIA;
	TD2UberDiabloIA D2UberDiabloIA;
	TD2UberBaalIA D2UberBaalIA;
	TD2SaveGame D2SaveGame;

	// Until 1.10
	typedef NetClient* (__fastcall *TD2GetClient) (Unit* ptUnit, char* lpszErrFile, DWORD ErrLine);

	TD2GetClient D2GetClient;

	// Variables
	NetClient** ptClientTable;
private:
	void SetFunctions();

	TD2SetNbPlayers GetD2SetNbPlayers();
	TD2AddClient GetD2AddClient();
	TD2GetGameByClientID GetD2GetGameByClientID();
	TD2BroadcastFunction GetD2BroadcastFunction();
	TD2SendPacket GetD2SendPacket();
	TD2SetSkillBaseLevelOnClient GetD2SetSkillBaseLevelOnClient();
	TD2LinkPortal GetD2LinkPortal();
	TD2VerifIfNotCarry1 GetD2VerifIfNotCarry1();
	TD2TestPositionInRoom GetD2TestPositionInRoom();
	TD2SpawnMonster GetD2SpawnMonster();
	TD2Game235C0 GetD2Game235C0();
	TD2LoadInventory GetD2LoadInventory();
	TD2GameGetObject GetD2GameGetObject();
	TD2CreateUnit GetD2CreateUnit();
	TD2OpenPandPortal GetD2OpenPandPortal();
	TD2OpenPandFinalPortal GetD2OpenPandFinalPortal();
	TD2MephIA GetD2MephIA();
	TD2DiabloIA GetD2DiabloIA();
	TD2BaalIA GetD2BaalIA();
	TD2UberMephIA GetD2UberMephIA();
	TD2UberDiabloIA GetD2UberDiabloIA();
	TD2UberBaalIA GetD2UberBaalIA();
	TD2SaveGame GetD2SaveGame();

	// Until 1.10
	TD2GetClient GetD2GetClient();

	// Variables
	NetClient** GetptClientTable();
};