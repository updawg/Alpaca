#include "D2NetLibrary.h"

void D2NetLibrary::SetFunctions()
{
	D2SendToServer = GetD2SendToServer();
	D2SendToClient = GetD2SendToClient();
}

D2NetLibrary::TD2SendToServer D2NetLibrary::GetD2SendToServer()
{
	return (TD2SendToServer)RetrieveAddressByProc(CreateOffsets(10005, 10005, 10005, 10035, 10020, 10036, 10024, 10015));
}

D2NetLibrary::TD2SendToClient D2NetLibrary::GetD2SendToClient()
{
	return (TD2SendToClient)RetrieveAddressByProc(CreateOffsets(10006, 10006, 10006, 10018, 10018, 10015, 10002, 10012));
}