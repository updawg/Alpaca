#include "D2ClientLibrary.h"

DWORD D2ClientLibrary::RetrieveStashBackgroundOffset()
{
	return RetrieveAddressByAddition(CreateOffsets(0x45B1C, 0x45B1C, 0x4C61C, 0xA643C, 0x749BC, 0xA9D7C, 0x8CC1C, 0x943FC));
}

void D2ClientLibrary::SetFunctions()
{
	
}