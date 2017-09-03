#include "D2WinLibrary.h"

void D2WinLibrary::SetFunctions()
{
	D2PrintLineOnTextBox = (TD2PrintLineOnTextBox)GetOffsetByProc(10046, 10046, 10046, 10061, 10075, 10015, 10022, 10051);
	D2PrintString = (TD2PrintString)GetOffsetByProc(10117, 10117, 10117, 10020, 10064, 10001, 10150, 10076);
	D2GetPixelLen = (TD2GetPixelLen)GetOffsetByProc(10121, 10121, 10121, 10034, 10128, 10132, 10028, 10150);
	D2SetFont = (TD2SetFont)GetOffsetByProc(10127, 10127, 10127, 10141, 10170, 10010, 10184, 10047);
	D2PrintPopup = (TD2PrintPopup)GetOffsetByProc(10129, 10129, 10129, 10118, 10039, 10031, 10085, 10137);
	D2GetPixelRect = (TD2GetPixelRect)GetOffsetByProc(10131, 10131, 10131, 0, 0, 0, 0, 0);
	D2PrintTextPopup = (TD2PrintTextPopup)GetOffsetByProc(10132, 10132, 10132, 0, 0, 0, 0, 0);
	D2CreateTextBox = (TD2CreateTextBox)GetOffsetByProc(10017, 10017, 10017, 10147, 10113, 10098, 10098, 10164);
}