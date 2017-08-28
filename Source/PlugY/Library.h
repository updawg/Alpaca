#pragma once

#include "common.h"

class Library
{
public:
	Library();

	int DllVersion;
	DWORD DllOffset;

	// Offsets for Versions (these are constants for that version)
	DWORD Offset_109B;
	DWORD Offset_109D;
	DWORD Offset_110;
	DWORD Offset_111;
	DWORD Offset_111B;
	DWORD Offset_112;
	DWORD Offset_113C;
private:

};