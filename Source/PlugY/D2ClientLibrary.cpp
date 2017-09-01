#include "D2ClientLibrary.h"

void D2ClientLibrary::SetFunctions()
{
	D2LoadImage = GetD2LoadImage();
	D2FreeImage = GetD2FreeImage();
	D2SendMsgToAll = GetD2SendMsgToAll();
	D2GetLastMonsterIDFight = GetD2GetLastMonsterIDFight();
	D2PrintStatsPage = GetD2PrintStatsPage();
	D2PrintStat = GetD2PrintStat();
	D2SetColorPopup = GetD2SetColorPopup();
	D2PlaySound = GetD2PlaySound();
	D2GetCurrentNPC = GetD2GetCurrentNPC();
	D2SendToServerXX = GetD2SendToServerXX();
	D2TogglePage = GetD2TogglePage();
	D2ClickOnStashButton = GetD2ClickOnStashButton();
	D2LoadBuySelBtn = GetD2LoadBuySelBtn();
	D2ReloadGambleScreen = GetD2ReloadGambleScreen();
	D2isLODGame = GetD2isLODGame();
	D2GetDifficultyLevel = GetD2GetDifficultyLevel();
	D2GetMouseX = GetD2GetMouseX();
	D2GetMouseY = GetD2GetMouseY();
	D2GetClientPlayer = GetD2GetClientPlayer();
	D2CleanStatMouseUp = GetD2CleanStatMouseUp();
	D2SendToServer3 = GetD2SendToServer3();

	ptResolutionY = GetptResolutionY();
	ptResolutionX = GetptResolutionX();
	ptNegWindowStartY = GetptNegWindowStartY();
	ptWindowStartX = GetptWindowStartX();
	ptIsLodGame = GetptIsLodGame();
	ptDifficultyLevel = GetptDifficultyLevel();
	ptMouseY = GetptMouseY();
	ptMouseX = GetptMouseX();
	ptptClientChar = GetptptClientChar();
	ptNbStatDesc = GetptNbStatDesc();
	ptStatDescTable = GetptStatDescTable();
}

DWORD D2ClientLibrary::RetrieveStashBackgroundOffset()
{
	return GetOffsetByAddition(0x45B1C, 0x45B1C, 0x4C61C, 0xA643C, 0x749BC, 0xA9D7C, 0x8CC1C, 0x943FC);
}

D2ClientLibrary::TD2LoadImage D2ClientLibrary::GetD2LoadImage()
{
	return (TD2LoadImage)GetOffsetByAddition(0x1000, 0x1000, 0x1000, 0x75D00, 0xA9070, 0xBEF70, 0x2B420, 0xA9480);
}

D2ClientLibrary::TD2FreeImage D2ClientLibrary::GetD2FreeImage()
{
	return (TD2FreeImage)GetOffsetByAddition(0x1150, 0x1150, 0x1140, 0, 0, 0, 0, 0);
}

D2ClientLibrary::TD2SendMsgToAll D2ClientLibrary::GetD2SendMsgToAll()
{
	return (TD2SendMsgToAll)GetOffsetByAddition(0xD640, 0xD630, 0xDB50, 0x73620, 0x5E4E0, 0x79670, 0x147A0, 0xB6890);
}

D2ClientLibrary::TD2GetLastMonsterIDFight D2ClientLibrary::GetD2GetLastMonsterIDFight()
{
	return (TD2GetLastMonsterIDFight)GetOffsetByAddition(0, 0, 0x15A80, 0, 0, 0, 0, 0);
}

D2ClientLibrary::TD2PrintStatsPage D2ClientLibrary::GetD2PrintStatsPage()
{
	return (TD2PrintStatsPage)GetOffsetByAddition(0x29800, 0x297F0, 0x2FD60, 0x828A0, 0x89320, 0x6B280, 0xBCEA0, 0xBF640);
}

D2ClientLibrary::TD2PrintStat D2ClientLibrary::GetD2PrintStat()
{
	return (TD2PrintStat)GetOffsetByAddition(0x4BB20, 0x4BB20, 0x521C0, 0xB8CB0, 0x21250, 0x88EA0, 0x54E10, 0x2CE40);
}

D2ClientLibrary::TD2SetColorPopup D2ClientLibrary::GetD2SetColorPopup()
{
	return (TD2SetColorPopup)GetOffsetByAddition(0x85A60, 0x84DE0, 0x80430, 0x9EEB0, 0x62070, 0x8B7A0, 0xBF5F0, 0x18820);
}

D2ClientLibrary::TD2PlaySound D2ClientLibrary::GetD2PlaySound()
{
	return (TD2PlaySound)GetOffsetByAddition(0xB4360, 0xB36E0, 0xB5820, 0x3ACC0, 0x54210, 0x31FA0, 0x88A70, 0x26270);
}

D2ClientLibrary::TD2GetCurrentNPC D2ClientLibrary::GetD2GetCurrentNPC()
{
	return (TD2GetCurrentNPC)GetOffsetByAddition(0, 0, 0, 0, 0x571C0, 0x18450, 0x46150, 0x790D0);
}

D2ClientLibrary::TD2SendToServerXX D2ClientLibrary::GetD2SendToServerXX()
{
	return (TD2SendToServerXX)GetOffsetByAddition(0, 0, 0, 0x73260, 0x5DE40, 0x791A0, 0x143E0, 0xB61F0);
}

D2ClientLibrary::TD2TogglePage D2ClientLibrary::GetD2TogglePage()
{
	return (TD2TogglePage)GetOffsetByAddition(0x88940, 0x87CC0, 0x83260, 0xA1F30, 0x65690, 0x8EF00, 0xC2790, 0x1C190);
}

D2ClientLibrary::TD2ClickOnStashButton D2ClientLibrary::GetD2ClickOnStashButton()
{
	return (TD2ClickOnStashButton)GetOffsetByAddition(0, 0, 0, 0xA6520, 0x710C0, 0xA6640, 0x8CD00, 0x90C10);
}

D2ClientLibrary::TD2LoadBuySelBtn D2ClientLibrary::GetD2LoadBuySelBtn()
{
	return (TD2LoadBuySelBtn)GetOffsetByAddition(0x897B0, 0x88B30, 0x84110, 0x9E3B0, 0x621C0, 0x8B8F0, 0xBEAF0, 0x18AA0);
}

D2ClientLibrary::TD2ReloadGambleScreen D2ClientLibrary::GetD2ReloadGambleScreen()
{
	return (TD2ReloadGambleScreen)GetOffsetByAddition(0, 0, 0, 0x8E480, 0x5BA90, 0x1CC00, 0x4ABE0, 0x7DC60);
}

D2ClientLibrary::TD2isLODGame D2ClientLibrary::GetD2isLODGame()
{
	return (TD2isLODGame)GetOffsetByAddition(0xBA00, 0xB9F0, 0xC080, 0, 0, 0, 0, 0);
}

D2ClientLibrary::TD2GetDifficultyLevel D2ClientLibrary::GetD2GetDifficultyLevel()
{
	return (TD2GetDifficultyLevel)GetOffsetByAddition(0, 0, 0xC090, 0, 0, 0, 0, 0);
}

D2ClientLibrary::TD2GetMouseX D2ClientLibrary::GetD2GetMouseX()
{
	return (TD2GetMouseX)GetOffsetByAddition(0xB6670, 0xB59F0, 0xB7BC0, 0, 0, 0, 0, 0);
}

D2ClientLibrary::TD2GetMouseY D2ClientLibrary::GetD2GetMouseY()
{
	return (TD2GetMouseY)GetOffsetByAddition(0xB6680, 0xB5A00, 0xB7BD0, 0, 0, 0, 0, 0);
}

D2ClientLibrary::TD2GetClientPlayer D2ClientLibrary::GetD2GetClientPlayer()
{
	return (TD2GetClientPlayer)GetOffsetByAddition(0x8DC40, 0x8CFC0, 0x883D0, 0, 0, 0, 0, 0);
}

D2ClientLibrary::TD2CleanStatMouseUp D2ClientLibrary::GetD2CleanStatMouseUp()
{
	return (TD2CleanStatMouseUp)GetOffsetByAddition(0xB920, 0xB910, 0xBF60, 0, 0, 0, 0, 0);
}

D2ClientLibrary::TD2SendToServer3 D2ClientLibrary::GetD2SendToServer3()
{
	return (TD2SendToServer3)GetOffsetByAddition(0xD210, 0xD200, 0xD990, 0, 0, 0, 0, 0);
}

DWORD* D2ClientLibrary::GetptResolutionY()
{
	return (DWORD*)GetOffsetByAddition(0xD50E8, 0xD40E0, 0xD40F0, 0xF5C60, 0xF4FC8, 0xDC6E4, 0xDBC4C, 0xF7038);
}

DWORD* D2ClientLibrary::GetptResolutionX()
{
	return (DWORD*)GetOffsetByAddition(0xD50EC, 0xD40E4, 0xD40F4, 0xF5C5C, 0xF4FC4, 0xDC6E0, 0xDBC48, 0xF7034);
}

DWORD* D2ClientLibrary::GetptNegWindowStartY()
{
	return (DWORD*)GetOffsetByAddition(0x125AD8, 0x124958, 0x11A74C, 0x11BD28, 0x11BEFC, 0x11BD2C, 0x11B9A4, 0x11D358);
}

DWORD* D2ClientLibrary::GetptWindowStartX()
{
	return (DWORD*)GetOffsetByAddition(0x125AD4, 0x124954, 0x11A748, 0x11BD24, 0x11BEF8, 0x11BD28, 0x11B9A0, 0x11D354);
}

DWORD* D2ClientLibrary::GetptIsLodGame()
{
	return (DWORD*)GetOffsetByAddition(0, 0, 0, 0xFB3F4, 0x11A2F4, 0x10330C, 0x119854, 0x1087B4);
}

BYTE* D2ClientLibrary::GetptDifficultyLevel()
{
	return (BYTE*)GetOffsetByAddition(0, 0, 0x10795C, 0x11BFB8, 0x11C2A8, 0x11BFF4, 0, 0);
}

DWORD* D2ClientLibrary::GetptMouseY()
{
	return (DWORD*)GetOffsetByAddition(0, 0, 0, 0x10A40C, 0x11B414, 0x101634, 0x11B824, 0x11C94C);
}

DWORD* D2ClientLibrary::GetptMouseX()
{
	return (DWORD*)GetOffsetByAddition(0, 0, 0, 0x10A410, 0x11B418, 0x101638, 0x11B828, 0x11C950);
}

Unit** D2ClientLibrary::GetptptClientChar()
{
	return (Unit**)GetOffsetByAddition(0, 0, 0, 0x11C4F0, 0x11C1E0, 0x11C3D0, 0x11BBFC, 0x11D050);
}

DWORD* D2ClientLibrary::GetptNbStatDesc()
{
	return (DWORD*)GetOffsetByAddition(0xDB918, 0xDA828, 0, 0, 0, 0, 0, 0);
}

DWORD* D2ClientLibrary::GetptStatDescTable()
{
	return (DWORD*)GetOffsetByAddition(0xDAF98, 0xD9EA8, 0, 0, 0, 0, 0, 0);
}