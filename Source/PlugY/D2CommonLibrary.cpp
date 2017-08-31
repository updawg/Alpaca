#include "D2CommonLibrary.h"

void D2CommonLibrary::SetFunctions()
{
	this->D2Common11084 = GetD2Common11084();
	this->D2GetLevelID = GetD2GetLevelID();
	this->D2GetDropRoom = GetD2GetDropRoom();
	this->D2Common10242 = GetD2Common10242();
}

D2CommonLibrary::TD2Common11084 D2CommonLibrary::GetD2Common11084()
{
	return (TD2Common11084) RetrieveAddress(DllName, DllOffset,
		CreateOffsets(00000, 00000, 00000, 10188, 11084, 11109, 10346, 10907));
}

D2CommonLibrary::TD2GetLevelID D2CommonLibrary::GetD2GetLevelID()
{
	return (TD2GetLevelID) RetrieveAddress(DllName, DllOffset,
		CreateOffsets(10057, 10057, 10057, 10332, 11021, 10511, 10826, 10691));
}

D2CommonLibrary::TD2GetDropRoom D2CommonLibrary::GetD2GetDropRoom()
{
	return (TD2GetDropRoom)RetrieveAddress(DllName, DllOffset,
		CreateOffsets(10138, 10138, 10138, 10623, 10491, 11043, 10654, 10716));
}

D2CommonLibrary::TD2Common10242 D2CommonLibrary::GetD2Common10242()
{
	return (TD2Common10242)RetrieveAddress(DllName, DllOffset,
		CreateOffsets(10138, 10138, 10138, 10623, 10491, 11043, 10654, 10716));
}