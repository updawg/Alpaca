#include "D2GameLibrary.h"

void D2GameLibrary::SetFunctions()
{
	D2SetNbPlayers = GetD2SetNbPlayers();
	D2AddClient = GetD2AddClient();
	D2GetGameByClientID = GetD2GetGameByClientID();
	D2BroadcastFunction = GetD2BroadcastFunction();
	D2SendPacket = GetD2SendPacket();
	D2SetSkillBaseLevelOnClient = GetD2SetSkillBaseLevelOnClient();
	D2LinkPortal = GetD2LinkPortal();
	D2VerifIfNotCarry1 = GetD2VerifIfNotCarry1();
	D2TestPositionInRoom = GetD2TestPositionInRoom();
	D2SpawnMonster = GetD2SpawnMonster();
	D2Game235C0 = GetD2Game235C0();
	D2LoadInventory = GetD2LoadInventory();
	D2GameGetObject = GetD2GameGetObject();
	D2CreateUnit = GetD2CreateUnit();
	D2OpenPandPortal = GetD2OpenPandPortal();
	D2OpenPandFinalPortal = GetD2OpenPandFinalPortal();
	D2MephIA = GetD2MephIA();
	D2DiabloIA = GetD2DiabloIA();
	D2BaalIA = GetD2BaalIA();
	D2UberMephIA = GetD2UberMephIA();
	D2UberDiabloIA = GetD2UberDiabloIA();
	D2UberBaalIA = GetD2UberBaalIA();
	D2SaveGame = GetD2SaveGame();
	D2GetClient = GetD2GetClient();
}

D2GameLibrary::TD2SetNbPlayers D2GameLibrary::GetD2SetNbPlayers()
{
	return (TD2SetNbPlayers)RetrieveAddressByProc(CreateOffsets(10059, 10059, 10059, 10039, 10007, 10037, 10049, 10002));
}

D2GameLibrary::TD2AddClient D2GameLibrary::GetD2AddClient()
{
	return (TD2AddClient)RetrieveAddressByAddition(CreateOffsets(0, 0, 0x6C60, 0xE3DA0, 0xE8210, 0xEB060, 0x49930, 0xE5070));
}

D2GameLibrary::TD2GetGameByClientID D2GameLibrary::GetD2GetGameByClientID()
{
	return (TD2GetGameByClientID)RetrieveAddressByAddition(CreateOffsets(0, 0, 0x94E0, 0xE0520, 0xE49A0, 0xA6360, 0x2AAE0, 0xBC700));
}

D2GameLibrary::TD2BroadcastFunction D2GameLibrary::GetD2BroadcastFunction()
{
	return (TD2BroadcastFunction)RetrieveAddressByAddition(CreateOffsets(0, 0, 0xB0E0, 0xDF250, 0xE36D0, 0xA5080, 0x29820, 0xBB510));
}

D2GameLibrary::TD2SendPacket D2GameLibrary::GetD2SendPacket()
{
	return (TD2SendPacket)RetrieveAddressByAddition(CreateOffsets(0xC380, 0xC650, 0xC710, 0x41420, 0xA0D50, 0x7D220, 0x8A3E0, 0xDB780));
}

D2GameLibrary::TD2SetSkillBaseLevelOnClient D2GameLibrary::GetD2SetSkillBaseLevelOnClient()
{
	return (TD2SetSkillBaseLevelOnClient)RetrieveAddressByAddition(CreateOffsets(0xD650, 0xD920, 0xDB50, 0x44D00, 0xA3F20, 0x802E0, 0x8D5F0, 0xDD4F0));
}

D2GameLibrary::TD2LinkPortal D2GameLibrary::GetD2LinkPortal()
{
	return (TD2LinkPortal)RetrieveAddressByAddition(CreateOffsets(0, 0, 0, 0x27230, 0x109F0, 0xAE930, 0xA22E0, 0x15F40));
}

D2GameLibrary::TD2VerifIfNotCarry1 D2GameLibrary::GetD2VerifIfNotCarry1()
{
	return (TD2VerifIfNotCarry1)RetrieveAddressByAddition(CreateOffsets(0, 0, 0x128F0, 0x38D90, 0x43E60, 0x11FF0, 0xD2070, 0xB2F70));
}

D2GameLibrary::TD2TestPositionInRoom D2GameLibrary::GetD2TestPositionInRoom()
{
	return (TD2TestPositionInRoom)RetrieveAddressByAddition(CreateOffsets(0, 0, 0x22070, 0x1090, 0x1DF0, 0x11F0, 0x1280, 0x1340));
}

D2GameLibrary::TD2SpawnMonster D2GameLibrary::GetD2SpawnMonster()
{
	return (TD2SpawnMonster)RetrieveAddressByAddition(CreateOffsets(0, 0, 0x3F220, 0x4ABE0, 0xEC7E0, 0x40B90, 0x24950, 0xCDE20));
}

D2GameLibrary::TD2Game235C0 D2GameLibrary::GetD2Game235C0()
{
	return (TD2Game235C0)RetrieveAddressByAddition(CreateOffsets(0, 0, 0, 0xD6D10, 0x235C0, 0xD410, 0x200E0, 0x59980));
}

D2GameLibrary::TD2LoadInventory D2GameLibrary::GetD2LoadInventory()
{
	return (TD2LoadInventory)RetrieveAddressByAddition(CreateOffsets(0x4F100, 0x4F500, 0x5B8A0, 0xB9D70, 0x25D50, 0x44950, 0x54810, 0x3A4C0));
}

D2GameLibrary::TD2GameGetObject D2GameLibrary::GetD2GameGetObject()
{
	return (TD2GameGetObject)RetrieveAddressByAddition(CreateOffsets(0x7BAE0, 0x7BFD0, 0x8BB00, 0x97620, 0xBEF80, 0x93650, 0xE03A0, 0x6DC40));
}

D2GameLibrary::TD2CreateUnit D2GameLibrary::GetD2CreateUnit()
{
	return (TD2CreateUnit)RetrieveAddressByAddition(CreateOffsets(0, 0, 0, 0x99760, 0xC09E0, 0x94E70, 0xE1D90, 0x6FE10));
}

D2GameLibrary::TD2OpenPandPortal D2GameLibrary::GetD2OpenPandPortal()
{
	return (TD2OpenPandPortal)RetrieveAddressByAddition(CreateOffsets(0, 0, 0, 0x9B480, 0x34920, 0xD1AA0, 0x70180, 0x941E0));
}

D2GameLibrary::TD2OpenPandFinalPortal D2GameLibrary::GetD2OpenPandFinalPortal()
{
	return (TD2OpenPandFinalPortal)RetrieveAddressByAddition(CreateOffsets(0, 0, 0, 0x9B470, 0x34910, 0xD1A90, 0x70170, 0x941D0));
}

D2GameLibrary::TD2MephIA D2GameLibrary::GetD2MephIA()
{
	return (TD2MephIA)RetrieveAddressByAddition(CreateOffsets(0, 0, 0, 0x84730, 0x85AA0, 0xDBE90, 0xA9610, 0x31920));
}

D2GameLibrary::TD2DiabloIA D2GameLibrary::GetD2DiabloIA()
{
	return (TD2DiabloIA)RetrieveAddressByAddition(CreateOffsets(0, 0, 0, 0x75980, 0xD7BD0, 0xCD0F0, 0x85B60, 0x4EAD0));
}

D2GameLibrary::TD2BaalIA D2GameLibrary::GetD2BaalIA()
{
	return (TD2BaalIA)RetrieveAddressByAddition(CreateOffsets(0, 0, 0, 0xEAB20, 0x2BC80, 0xB3B90, 0xB8610, 0xC8850));
}

D2GameLibrary::TD2UberMephIA D2GameLibrary::GetD2UberMephIA()
{
	return (TD2UberMephIA)RetrieveAddressByAddition(CreateOffsets(0, 0, 0, 0x70320, 0xD2D70, 0xC2A90, 0x7B4E0, 0x49480));
}

D2GameLibrary::TD2UberDiabloIA D2GameLibrary::GetD2UberDiabloIA()
{
	return (TD2UberDiabloIA)RetrieveAddressByAddition(CreateOffsets(0, 0, 0, 0x7F200, 0x7FE60, 0xD6250, 0xA39D0, 0x2C3F0));
}

D2GameLibrary::TD2UberBaalIA D2GameLibrary::GetD2UberBaalIA()
{
	return (TD2UberBaalIA)RetrieveAddressByAddition(CreateOffsets(0, 0, 0, 0xE92B0, 0x2A300, 0xB2210, 0xB6C80, 0xC6EC0));
}

D2GameLibrary::TD2SaveGame D2GameLibrary::GetD2SaveGame()
{
	return (TD2SaveGame)RetrieveAddressByAddition(CreateOffsets(0, 0, 0x89C0, 0xE2390, 0xE66D0, 0xA8090, 0x2C830, 0xBE660));
}

D2GameLibrary::TD2GetClient D2GameLibrary::GetD2GetClient()
{
	return (TD2GetClient)RetrieveAddressByAddition(CreateOffsets(0x7C2C0, 0x7C7B0, 0x8C2E0, 0, 0, 0, 0, 0));
}