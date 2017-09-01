#include "D2WinLibrary.h"

void D2WinLibrary::SetFunctions()
{
	D2PrintLineOnTextBox = GetD2PrintLineOnTextBox();
	D2PrintString = GetD2PrintString();
	D2GetPixelLen = GetD2GetPixelLen();
	D2SetFont = GetD2SetFont();
	D2PrintPopup = GetD2PrintPopup();
	D2GetPixelRect = GetD2GetPixelRect();
	D2PrintTextPopup = GetD2PrintTextPopup();
	D2CreateTextBox = GetD2CreateTextBox();
}

D2WinLibrary::TD2PrintLineOnTextBox D2WinLibrary::GetD2PrintLineOnTextBox()
{
	return (TD2PrintLineOnTextBox)GetOffsetByProc(10046, 10046, 10046, 10061, 10075, 10015, 10022, 10051);
}

D2WinLibrary::TD2PrintString D2WinLibrary::GetD2PrintString()
{
	return (TD2PrintString)GetOffsetByProc(10117, 10117, 10117, 10020, 10064, 10001, 10150, 10076);
}

D2WinLibrary::TD2GetPixelLen D2WinLibrary::GetD2GetPixelLen()
{
	return (TD2GetPixelLen)GetOffsetByProc(10121, 10121, 10121, 10034, 10128, 10132, 10028, 10150);
}

D2WinLibrary::TD2SetFont D2WinLibrary::GetD2SetFont()
{
	return (TD2SetFont)GetOffsetByProc(10127, 10127, 10127, 10141, 10170, 10010, 10184, 10047);
}

D2WinLibrary::TD2PrintPopup D2WinLibrary::GetD2PrintPopup()
{
	return (TD2PrintPopup)GetOffsetByProc(10129, 10129, 10129, 10118, 10039, 10031, 10085, 10137);
}

D2WinLibrary::TD2GetPixelRect D2WinLibrary::GetD2GetPixelRect()
{
	return (TD2GetPixelRect)GetOffsetByProc(10131, 10131, 10131, 0, 0, 0, 0, 0);
}

D2WinLibrary::TD2PrintTextPopup D2WinLibrary::GetD2PrintTextPopup()
{
	return (TD2PrintTextPopup)GetOffsetByProc(10132, 10132, 10132, 0, 0, 0, 0, 0);
}

D2WinLibrary::TD2CreateTextBox D2WinLibrary::GetD2CreateTextBox()
{
	return (TD2CreateTextBox)GetOffsetByProc(10017, 10017, 10017, 10147, 10113, 10098, 10098, 10164);
}