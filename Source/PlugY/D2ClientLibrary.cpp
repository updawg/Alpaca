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
}

DWORD D2ClientLibrary::RetrieveStashBackgroundOffset()
{
	return RetrieveAddressByAddition(CreateOffsets(0x45B1C, 0x45B1C, 0x4C61C, 0xA643C, 0x749BC, 0xA9D7C, 0x8CC1C, 0x943FC));
}

D2ClientLibrary::TD2LoadImage D2ClientLibrary::GetD2LoadImage()
{
	return (TD2LoadImage)RetrieveAddressByAddition(CreateOffsets(0x1000, 0x1000, 0x1000, 0x75D00, 0xA9070, 0xBEF70, 0x2B420, 0xA9480));
}

D2ClientLibrary::TD2FreeImage D2ClientLibrary::GetD2FreeImage()
{
	return (TD2FreeImage)RetrieveAddressByAddition(CreateOffsets(0x1150, 0x1150, 0x1140, 0, 0, 0, 0, 0));
}

D2ClientLibrary::TD2SendMsgToAll D2ClientLibrary::GetD2SendMsgToAll()
{
	return (TD2SendMsgToAll)RetrieveAddressByAddition(CreateOffsets(0xD640, 0xD630, 0xDB50, 0x73620, 0x5E4E0, 0x79670, 0x147A0, 0xB6890));
}

D2ClientLibrary::TD2GetLastMonsterIDFight D2ClientLibrary::GetD2GetLastMonsterIDFight()
{
	return (TD2GetLastMonsterIDFight)RetrieveAddressByAddition(CreateOffsets(0, 0, 0x15A80, 0, 0, 0, 0, 0));
}

D2ClientLibrary::TD2PrintStatsPage D2ClientLibrary::GetD2PrintStatsPage()
{
	return (TD2PrintStatsPage)RetrieveAddressByAddition(CreateOffsets(0x29800, 0x297F0, 0x2FD60, 0x828A0, 0x89320, 0x6B280, 0xBCEA0, 0xBF640));
}

D2ClientLibrary::TD2PrintStat D2ClientLibrary::GetD2PrintStat()
{
	return (TD2PrintStat)RetrieveAddressByAddition(CreateOffsets(0x4BB20, 0x4BB20, 0x521C0, 0xB8CB0, 0x21250, 0x88EA0, 0x54E10, 0x2CE40));
}

D2ClientLibrary::TD2SetColorPopup D2ClientLibrary::GetD2SetColorPopup()
{
	return (TD2SetColorPopup)RetrieveAddressByAddition(CreateOffsets(0x85A60, 0x84DE0, 0x80430, 0x9EEB0, 0x62070, 0x8B7A0, 0xBF5F0, 0x18820));
}

D2ClientLibrary::TD2PlaySound D2ClientLibrary::GetD2PlaySound()
{
	return (TD2PlaySound)RetrieveAddressByAddition(CreateOffsets(0xB4360, 0xB36E0, 0xB5820, 0x3ACC0, 0x54210, 0x31FA0, 0x88A70, 0x26270));
}

D2ClientLibrary::TD2GetCurrentNPC D2ClientLibrary::GetD2GetCurrentNPC()
{
	return (TD2GetCurrentNPC)RetrieveAddressByAddition(CreateOffsets(0, 0, 0, 0, 0x571C0, 0x18450, 0x46150, 0x790D0));
}

D2ClientLibrary::TD2SendToServerXX D2ClientLibrary::GetD2SendToServerXX()
{
	return (TD2SendToServerXX)RetrieveAddressByAddition(CreateOffsets(0, 0, 0, 0x73260, 0x5DE40, 0x791A0, 0x143E0, 0xB61F0));
}

D2ClientLibrary::TD2TogglePage D2ClientLibrary::GetD2TogglePage()
{
	return (TD2TogglePage)RetrieveAddressByAddition(CreateOffsets(0x88940, 0x87CC0, 0x83260, 0xA1F30, 0x65690, 0x8EF00, 0xC2790, 0x1C190));
}

D2ClientLibrary::TD2ClickOnStashButton D2ClientLibrary::GetD2ClickOnStashButton()
{
	return (TD2ClickOnStashButton)RetrieveAddressByAddition(CreateOffsets(0, 0, 0, 0xA6520, 0x710C0, 0xA6640, 0x8CD00, 0x90C10));
}

D2ClientLibrary::TD2LoadBuySelBtn D2ClientLibrary::GetD2LoadBuySelBtn()
{
	return (TD2LoadBuySelBtn)RetrieveAddressByAddition(CreateOffsets(0x897B0, 0x88B30, 0x84110, 0x9E3B0, 0x621C0, 0x8B8F0, 0xBEAF0, 0x18AA0));
}

D2ClientLibrary::TD2ReloadGambleScreen D2ClientLibrary::GetD2ReloadGambleScreen()
{
	return (TD2ReloadGambleScreen)RetrieveAddressByAddition(CreateOffsets(0, 0, 0, 0x8E480, 0x5BA90, 0x1CC00, 0x4ABE0, 0x7DC60));
}