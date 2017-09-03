#pragma once

#include "Library.h"

class D2gfxLibrary : public Library
{
public:
	D2gfxLibrary(int gameVersion) : Library()
	{
		DllName = "D2gfx.dll";
		DllVersion = gameVersion;
		DllOffset = LoadDiabloLibrary();
		SetFunctions();
	};

	typedef DWORD(__stdcall *TD2GetResolution) ();
	typedef void(__stdcall *TD2FillArea) (DWORD x1, DWORD y1, DWORD x2, DWORD y2, DWORD color, DWORD transTbl);
	typedef void(__stdcall *TD2PrintImage) (sDrawImageInfo* data, DWORD x, DWORD y, DWORD p4, DWORD p5, DWORD p6);

	TD2GetResolution D2GetResolution;
	TD2FillArea D2FillArea;
	TD2PrintImage D2PrintImage;
private:
	void SetFunctions();
};