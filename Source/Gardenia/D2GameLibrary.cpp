#include "D2GameLibrary.h"

void D2GameLibrary::SetFunctions()
{
	D2SetNbPlayers = (TD2SetNbPlayers)GetOffsetByProc(10059, 10059, 10059, 10039, 10007, 10037, 10049, 10002);
	D2AddClient = (TD2AddClient)GetOffsetByAddition(0, 0, 0x6C60, 0xE3DA0, 0xE8210, 0xEB060, 0x49930, 0xE5070);
	D2GetGameByClientID = (TD2GetGameByClientID)GetOffsetByAddition(0, 0, 0x94E0, 0xE0520, 0xE49A0, 0xA6360, 0x2AAE0, 0xBC700);
	D2BroadcastFunction = (TD2BroadcastFunction)GetOffsetByAddition(0, 0, 0xB0E0, 0xDF250, 0xE36D0, 0xA5080, 0x29820, 0xBB510);
	D2SendPacket = (TD2SendPacket)GetOffsetByAddition(0xC380, 0xC650, 0xC710, 0x41420, 0xA0D50, 0x7D220, 0x8A3E0, 0xDB780);
	D2SetSkillBaseLevelOnClient = (TD2SetSkillBaseLevelOnClient)GetOffsetByAddition(0xD650, 0xD920, 0xDB50, 0x44D00, 0xA3F20, 0x802E0, 0x8D5F0, 0xDD4F0);
	D2LinkPortal = (TD2LinkPortal)GetOffsetByAddition(0, 0, 0, 0x27230, 0x109F0, 0xAE930, 0xA22E0, 0x15F40);
	D2VerifIfNotCarry1 = (TD2VerifIfNotCarry1)GetOffsetByAddition(0, 0, 0x128F0, 0x38D90, 0x43E60, 0x11FF0, 0xD2070, 0xB2F70);
	D2TestPositionInRoom = (TD2TestPositionInRoom)GetOffsetByAddition(0, 0, 0x22070, 0x1090, 0x1DF0, 0x11F0, 0x1280, 0x1340);
	D2SpawnMonster = (TD2SpawnMonster)GetOffsetByAddition(0, 0, 0x3F220, 0x4ABE0, 0xEC7E0, 0x40B90, 0x24950, 0xCDE20);
	D2Game235C0 = (TD2Game235C0)GetOffsetByAddition(0, 0, 0, 0xD6D10, 0x235C0, 0xD410, 0x200E0, 0x59980);
	D2LoadInventory = (TD2LoadInventory)GetOffsetByAddition(0x4F100, 0x4F500, 0x5B8A0, 0xB9D70, 0x25D50, 0x44950, 0x54810, 0x3A4C0);
	D2GameGetObject = (TD2GameGetObject)GetOffsetByAddition(0x7BAE0, 0x7BFD0, 0x8BB00, 0x97620, 0xBEF80, 0x93650, 0xE03A0, 0x6DC40);
	D2CreateUnit = (TD2CreateUnit)GetOffsetByAddition(0, 0, 0, 0x99760, 0xC09E0, 0x94E70, 0xE1D90, 0x6FE10);
	D2OpenPandPortal = (TD2OpenPandPortal)GetOffsetByAddition(0, 0, 0, 0x9B480, 0x34920, 0xD1AA0, 0x70180, 0x941E0);
	D2OpenPandFinalPortal = (TD2OpenPandFinalPortal)GetOffsetByAddition(0, 0, 0, 0x9B470, 0x34910, 0xD1A90, 0x70170, 0x941D0);
	D2MephIA = (TD2MephIA)GetOffsetByAddition(0, 0, 0, 0x84730, 0x85AA0, 0xDBE90, 0xA9610, 0x31920);
	D2DiabloIA = (TD2DiabloIA)GetOffsetByAddition(0, 0, 0, 0x75980, 0xD7BD0, 0xCD0F0, 0x85B60, 0x4EAD0);
	D2BaalIA = (TD2BaalIA)GetOffsetByAddition(0, 0, 0, 0xEAB20, 0x2BC80, 0xB3B90, 0xB8610, 0xC8850);
	D2UberMephIA = (TD2UberMephIA)GetOffsetByAddition(0, 0, 0, 0x70320, 0xD2D70, 0xC2A90, 0x7B4E0, 0x49480);
	D2UberDiabloIA = (TD2UberDiabloIA)GetOffsetByAddition(0, 0, 0, 0x7F200, 0x7FE60, 0xD6250, 0xA39D0, 0x2C3F0);
	D2UberBaalIA = (TD2UberBaalIA)GetOffsetByAddition(0, 0, 0, 0xE92B0, 0x2A300, 0xB2210, 0xB6C80, 0xC6EC0);
	D2SaveGame = (TD2SaveGame)GetOffsetByAddition(0, 0, 0x89C0, 0xE2390, 0xE66D0, 0xA8090, 0x2C830, 0xBE660);

	// Until 1.10
	D2GetClient = (TD2GetClient)GetOffsetByAddition(0x7C2C0, 0x7C7B0, 0x8C2E0, 0, 0, 0, 0, 0);

	// Variables
	ptClientTable = (NetClient**)GetOffsetByAddition(0xF2A80, 0xF2918, 0x113FB8, 0x111718, 0x1115E0, 0x1105E0, 0x1107B8, 0x1105E0);
}