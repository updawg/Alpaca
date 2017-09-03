#include "FogLibrary.h"

void FogLibrary::SetFunctions()
{
	D2FogAssertOld = (TD2FogAssertOld)GetOffsetByProc(10023, 10023, 10023, 0, 0, 0, 0, 0);
	D2FogAssert = (TD2FogAssert)GetOffsetByProc(0, 0, 0, 10024, 10024, 10024, 10024, 10024);
	D2FogMemAlloc = (TD2FogMemAlloc)GetOffsetByProc(10042, 10042, 10042, 10042, 10042, 10042, 10042, 10042);
	D2FogMemDeAlloc = (TD2FogMemDeAlloc)GetOffsetByProc(10043, 10043, 10043, 10043, 10043, 10043, 10043, 10043);
	D2AllocMem = (TD2AllocMem)GetOffsetByProc(10045, 10045, 10045, 10045, 10045, 10045, 10045, 10045);
	D2FreeMem = (TD2FreeMem)GetOffsetByProc(10046, 10046, 10046, 10046, 10046, 10046, 10046, 10046);
	D2MPQOpenFile = (TD2MPQOpenFile)GetOffsetByProc(10102, 10102, 10102, 10102, 10102, 10102, 10102, 10102);
	D2MPQCloseFile = (TD2MPQCloseFile)GetOffsetByProc(10103, 10103, 10103, 10103, 10103, 10103, 10103, 10103);
	D2MPQReadFile = (TD2MPQReadFile)GetOffsetByProc(10104, 10104, 10104, 10104, 10104, 10104, 10104, 10104);
	D2MPQGetSizeFile = (TD2MPQGetSizeFile)GetOffsetByProc(10105, 10105, 10105, 10105, 10105, 10105, 10105, 10105);
	D2FogGetSavePath = (TD2FogGetSavePath)GetOffsetByProc(10115, 10115, 10115, 10115, 10115, 10115, 10115, 10115);
	D2FogGetInstallPath = (TD2FogGetInstallPath)GetOffsetByProc(10116, 10116, 10116, 10116, 10116, 10116, 10116, 10116);
	D2Fog10212 = (TD2Fog10212)GetOffsetByProc(10212, 10212, 10212, 10212, 10212, 10212, 10212, 10212);
	D2GetInstructionPointer = (TD2GetInstructionPointer)GetOffsetByProc(0, 0, 0, 10265, 10265, 10265, 10265, 10265);
}