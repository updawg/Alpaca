#include "D2LangLibrary.h"

void D2LangLibrary::SetFunctions()
{
	D2GetStringFromString = GetD2GetStringFromString();
	D2GetStringFromIndex = GetD2GetStringFromIndex();
	D2GetLang = GetD2GetLang();
	D2PrintBigNumber = GetD2PrintBigNumber();
}

D2LangLibrary::TD2GetStringFromString D2LangLibrary::GetD2GetStringFromString()
{
	return (TD2GetStringFromString)RetrieveAddressByProc(CreateOffsets(10003, 10003, 10003, 10002, 10004, 10010, 10011, 10011));
}

D2LangLibrary::TD2GetStringFromIndex D2LangLibrary::GetD2GetStringFromIndex()
{
	return (TD2GetStringFromIndex)RetrieveAddressByProc(CreateOffsets(10004, 10004, 10004, 10005, 10000, 10005, 10003, 10004));
}

D2LangLibrary::TD2GetLang D2LangLibrary::GetD2GetLang()
{
	return (TD2GetLang)RetrieveAddressByProc(CreateOffsets(10007, 10007, 10007, 10009, 10013, 10002, 10009, 10001));
}

D2LangLibrary::TD2PrintBigNumber D2LangLibrary::GetD2PrintBigNumber()
{
	return (TD2PrintBigNumber)RetrieveAddressByProc(CreateOffsets(10010, 10010, 10010, 0, 0, 0, 0, 0));
}	