#pragma once

#include "Library.h"

class D2ClientLibrary : public Library
{
public:
	D2ClientLibrary(DWORD gameOffset, int gameVersion) : Library(gameOffset, gameVersion)
	{
		DllName = "D2Client.dll";
		DllOffset = LoadDiabloLibrary();
		DllVersion = GameVersion;
		SetFunctions();
	};

	DWORD RetrieveStashBackgroundOffset();

	typedef void* (__fastcall *TD2LoadImage) (const char* filename, DWORD filetype);
	typedef void(__fastcall *TD2FreeImage) (void* image);
	typedef void(__fastcall *TD2SendMsgToAll) (BYTE* data);
	typedef DWORD(__stdcall *TD2GetLastMonsterIDFight) ();
	typedef void(__stdcall *TD2PrintStatsPage) ();
	typedef DWORD(__fastcall *TD2PrintStat) (Unit* ptItem, Stats* ptStats, DWORD statID, DWORD statIndex, DWORD statValue, LPWSTR lpText);
	typedef LPWSTR(__fastcall *TD2SetColorPopup) (LPWSTR popupText, DWORD color);
	typedef DWORD(__fastcall *TD2PlaySound) (DWORD id, DWORD, DWORD, DWORD, DWORD);
	typedef Unit* (__fastcall *TD2GetCurrentNPC) ();
	typedef void(__fastcall *TD2SendToServerXX) (DWORD size, BYTE * data);
	typedef void(__fastcall *TD2TogglePage) (DWORD a, DWORD b, DWORD c);
	typedef void(__fastcall *TD2ClickOnStashButton) (DWORD x, DWORD y);
	typedef void* (__stdcall *TD2LoadBuySelBtn) ();
	typedef void(__fastcall *TD2ReloadGambleScreen) ();

	TD2LoadImage D2LoadImage;
	TD2FreeImage D2FreeImage;
	TD2SendMsgToAll D2SendMsgToAll;
	TD2GetLastMonsterIDFight D2GetLastMonsterIDFight;
	TD2PrintStatsPage D2PrintStatsPage;
	TD2PrintStat D2PrintStat;
	TD2SetColorPopup D2SetColorPopup;
	TD2PlaySound D2PlaySound;
	TD2GetCurrentNPC D2GetCurrentNPC;
	TD2SendToServerXX D2SendToServerXX;
	TD2TogglePage D2TogglePage;
	TD2ClickOnStashButton D2ClickOnStashButton;
	TD2LoadBuySelBtn D2LoadBuySelBtn;
	TD2ReloadGambleScreen D2ReloadGambleScreen;

	// Until 1.10
	typedef DWORD(__fastcall *TD2isLODGame) ();
	typedef BYTE(__fastcall *TD2GetDifficultyLevel) ();
	typedef DWORD(__stdcall *TD2GetMouseX) ();
	typedef DWORD(__stdcall *TD2GetMouseY) ();
	typedef Unit* (__stdcall *TD2GetClientPlayer) ();
	typedef void(__fastcall *TD2CleanStatMouseUp) ();
	typedef void(__fastcall *TD2SendToServer3) (BYTE type, WORD p);

	TD2isLODGame D2isLODGame;
	TD2GetDifficultyLevel D2GetDifficultyLevel;
	TD2GetMouseX D2GetMouseX;
	TD2GetMouseY D2GetMouseY;
	TD2GetClientPlayer D2GetClientPlayer;
	TD2CleanStatMouseUp D2CleanStatMouseUp;
	TD2SendToServer3 D2SendToServer3;

	// Variables
	DWORD* ptResolutionY;
	DWORD* ptResolutionX;
	DWORD* ptNegWindowStartY;
	DWORD* ptWindowStartX;
	DWORD* ptIsLodGame;
	BYTE* ptDifficultyLevel;
	DWORD* ptMouseY;
	DWORD* ptMouseX;
	Unit** ptptClientChar;
	DWORD* ptNbStatDesc;
	DWORD* ptStatDescTable;
private:
	void SetFunctions();

	TD2LoadImage GetD2LoadImage();
	TD2FreeImage GetD2FreeImage();
	TD2SendMsgToAll GetD2SendMsgToAll();
	TD2GetLastMonsterIDFight GetD2GetLastMonsterIDFight();
	TD2PrintStatsPage GetD2PrintStatsPage();
	TD2PrintStat GetD2PrintStat();
	TD2SetColorPopup GetD2SetColorPopup();
	TD2PlaySound GetD2PlaySound();
	TD2GetCurrentNPC GetD2GetCurrentNPC();
	TD2SendToServerXX GetD2SendToServerXX();
	TD2TogglePage GetD2TogglePage();
	TD2ClickOnStashButton GetD2ClickOnStashButton();
	TD2LoadBuySelBtn GetD2LoadBuySelBtn();
	TD2ReloadGambleScreen GetD2ReloadGambleScreen();

	// Until 1.10
	TD2isLODGame GetD2isLODGame();
	TD2GetDifficultyLevel GetD2GetDifficultyLevel();
	TD2GetMouseX GetD2GetMouseX();
	TD2GetMouseY GetD2GetMouseY();
	TD2GetClientPlayer GetD2GetClientPlayer();
	TD2CleanStatMouseUp GetD2CleanStatMouseUp();
	TD2SendToServer3 GetD2SendToServer3();
};
