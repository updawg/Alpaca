#include "StormLibrary.h"

void StormLibrary::SetFunctions()
{
	D2StormMPQOpenFile = GetD2StormMPQOpenFile();
	D2Storm503 = GetD2Storm503();
	D2FreeWinMessage = GetD2FreeWinMessage();
}

StormLibrary::TD2StormMPQOpenFile StormLibrary::GetD2StormMPQOpenFile()
{
	return (TD2StormMPQOpenFile)RetrieveAddressByProc(CreateOffsets(268, 268, 268, 268, 268, 268, 268, 268));
}

StormLibrary::TD2Storm503 StormLibrary::GetD2Storm503()
{
	return (TD2Storm503)RetrieveAddressByProc(CreateOffsets(503, 503, 503, 503, 503, 503, 503, 503));
}

StormLibrary::TD2FreeWinMessage StormLibrary::GetD2FreeWinMessage()
{
	return (TD2FreeWinMessage)RetrieveAddressByProc(CreateOffsets(511, 511, 511, 511, 511, 511, 511, 511));
}