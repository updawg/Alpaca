#pragma once

#include "Library.h"

class D2WinLibrary : public Library
{
public:
	D2WinLibrary(DWORD gameOffset, int gameVersion) : Library(gameOffset, gameVersion)
	{
		DllName = "D2Win.dll";
		DllOffset = LoadDiabloLibrary();
		DllVersion = GameVersion;
		SetFunctions();
	};

	typedef void(__fastcall *TD2PrintLineOnTextBox) (void* screen, char* s, DWORD color);
	typedef void(__fastcall *TD2PrintString) (LPWSTR s, DWORD x, DWORD y, DWORD color, DWORD bfalse);
	typedef DWORD(__fastcall *TD2GetPixelLen) (LPWSTR s);
	typedef DWORD(__fastcall *TD2SetFont) (DWORD fontID);
	typedef void(__fastcall *TD2PrintPopup) (LPWSTR s, DWORD x, DWORD y, DWORD color, DWORD center);
	typedef void(__fastcall *TD2GetPixelRect) (LPWSTR s, DWORD* x, DWORD* y);
	typedef DWORD(__fastcall *TD2PrintTextPopup) (LPWSTR s, DWORD x, DWORD y, DWORD uk, DWORD type, DWORD color);
	typedef void* (__stdcall *TD2CreateTextBox) (DWORD* data);

	TD2PrintLineOnTextBox D2PrintLineOnTextBox;
	TD2PrintString D2PrintString;
	TD2GetPixelLen D2GetPixelLen;
	TD2SetFont D2SetFont;
	TD2PrintPopup D2PrintPopup;
	TD2GetPixelRect D2GetPixelRect;
	TD2PrintTextPopup D2PrintTextPopup;
	TD2CreateTextBox D2CreateTextBox;
private:
	void SetFunctions();
};