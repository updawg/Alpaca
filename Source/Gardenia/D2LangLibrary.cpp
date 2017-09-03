#include "D2LangLibrary.h"

void D2LangLibrary::SetFunctions()
{
	D2GetStringFromString = (TD2GetStringFromString)GetOffsetByProc(10003, 10003, 10003, 10002, 10004, 10010, 10011, 10011);
	D2GetStringFromIndex = (TD2GetStringFromIndex)GetOffsetByProc(10004, 10004, 10004, 10005, 10000, 10005, 10003, 10004);
	D2GetLang = (TD2GetLang)GetOffsetByProc(10007, 10007, 10007, 10009, 10013, 10002, 10009, 10001);
	D2PrintBigNumber = (TD2PrintBigNumber)GetOffsetByProc(10010, 10010, 10010, 0, 0, 0, 0, 0);
}