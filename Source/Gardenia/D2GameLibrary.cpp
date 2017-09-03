#include "D2GameLibrary.h"

void D2GameLibrary::SetFunctions()
{
	D2SetNbPlayers = (TD2SetNbPlayers)GetOffsetByProc(10059, 10059, 10059, 10039, 10007, 10037, 10049, 10002);
	D2SendPacket = (TD2SendPacket)GetOffsetByAddition(0xC380, 0xC650, 0xC710, 0x41420, 0xA0D50, 0x7D220, 0x8A3E0, 0xDB780);
	D2SetSkillBaseLevelOnClient = (TD2SetSkillBaseLevelOnClient)GetOffsetByAddition(0xD650, 0xD920, 0xDB50, 0x44D00, 0xA3F20, 0x802E0, 0x8D5F0, 0xDD4F0);
	D2LinkPortal = (TD2LinkPortal)GetOffsetByAddition(0, 0, 0, 0x27230, 0x109F0, 0xAE930, 0xA22E0, 0x15F40);
	D2VerifIfNotCarry1 = (TD2VerifIfNotCarry1)GetOffsetByAddition(0, 0, 0x128F0, 0x38D90, 0x43E60, 0x11FF0, 0xD2070, 0xB2F70);
	D2TestPositionInRoom = (TD2TestPositionInRoom)GetOffsetByAddition(0, 0, 0x22070, 0x1090, 0x1DF0, 0x11F0, 0x1280, 0x1340);
	D2LoadInventory = (TD2LoadInventory)GetOffsetByAddition(0x4F100, 0x4F500, 0x5B8A0, 0xB9D70, 0x25D50, 0x44950, 0x54810, 0x3A4C0);
	D2GameGetObject = (TD2GameGetObject)GetOffsetByAddition(0x7BAE0, 0x7BFD0, 0x8BB00, 0x97620, 0xBEF80, 0x93650, 0xE03A0, 0x6DC40);
	D2SaveGame = (TD2SaveGame)GetOffsetByAddition(0, 0, 0x89C0, 0xE2390, 0xE66D0, 0xA8090, 0x2C830, 0xBE660);

	// Until 1.10
	D2GetClient = (TD2GetClient)GetOffsetByAddition(0x7C2C0, 0x7C7B0, 0x8C2E0, 0, 0, 0, 0, 0);

	// Variables
	ptClientTable = (NetClient**)GetOffsetByAddition(0xF2A80, 0xF2918, 0x113FB8, 0x111718, 0x1115E0, 0x1105E0, 0x1107B8, 0x1105E0);
}