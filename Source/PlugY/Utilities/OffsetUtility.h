#pragma once

#include "../common.h"

// Offsets:



// 1.09d

class Offsets
{
public:
	DWORD D2Common_Base_Offset = 0;

	// Stash Grid
	DWORD StashGrid_113D = 0x6CC25;
	DWORD StashGrid_113C = 0x82CA5;
	DWORD StashGrid_112 = 0x1BDB5;
	DWORD StashGrid_111B = 0x2A505;
	DWORD StashGrid_110 = 0x14ED3;
	DWORD StashGrid_109D = 0xCA03;
	DWORD StashGrid_Other = 0xC9F3;
};

class OffsetUtility
{
public:
	DWORD GetBigStashOffset(DWORD version);


	// Retreival

	//DWORD GetOffset();
};