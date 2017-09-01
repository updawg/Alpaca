#pragma once

#include "Library.h"

class D2gfxLibrary : public Library
{
public:
	D2gfxLibrary(DWORD gameOffset, int gameVersion) : Library(gameOffset, gameVersion)
	{
		DllName = "D2gfx.dll";
		DllOffset = LoadDiabloLibrary();
		DllVersion = GameVersion;
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

	TD2GetResolution GetD2GetResolution();
	TD2FillArea GetD2FillArea();
	TD2PrintImage GetD2PrintImage();
};