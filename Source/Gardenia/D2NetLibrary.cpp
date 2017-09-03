#include "D2NetLibrary.h"

void D2NetLibrary::SetFunctions()
{
	D2SendToServer = (TD2SendToServer)GetOffsetByProc(10005, 10005, 10005, 10035, 10020, 10036, 10024, 10015);
	D2SendToClient = (TD2SendToClient)GetOffsetByProc(10006, 10006, 10006, 10018, 10018, 10015, 10002, 10012);
}