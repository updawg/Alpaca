#include "StormLibrary.h"

void StormLibrary::SetFunctions()
{
	D2StormMPQOpenFile = (TD2StormMPQOpenFile)GetOffsetByProc(268, 268, 268, 268, 268, 268, 268, 268);
	D2Storm503 = (TD2Storm503)GetOffsetByProc(503, 503, 503, 503, 503, 503, 503, 503);
	D2FreeWinMessage = (TD2FreeWinMessage)GetOffsetByProc(511, 511, 511, 511, 511, 511, 511, 511);
}