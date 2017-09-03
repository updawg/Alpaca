#include "D2gfxLibrary.h"

void D2gfxLibrary::SetFunctions()
{
	D2GetResolution = (TD2GetResolution)GetOffsetByProc(10005, 10005, 10005, 10000, 10063, 10043, 10031, 10012);
	D2FillArea = (TD2FillArea)GetOffsetByProc(10055, 10055, 10055, 10028, 10000, 10062, 10014, 10028);
	D2PrintImage = (TD2PrintImage)GetOffsetByProc(10072, 10072, 10072, 10047, 10044, 10024, 10041, 10042);
}