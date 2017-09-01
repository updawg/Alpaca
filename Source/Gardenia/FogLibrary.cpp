#include "FogLibrary.h"

void FogLibrary::SetFunctions()
{
	D2FogAssertOld = GetD2FogAssertOld();
	D2FogAssert = GetD2FogAssert();
	D2FogMemAlloc = GetD2FogMemAlloc();
	D2FogMemDeAlloc = GetD2FogMemDeAlloc();
	D2AllocMem = GetD2AllocMem();
	D2FreeMem = GetD2FreeMem();
	D2MPQOpenFile = GetD2MPQOpenFile();
	D2MPQCloseFile = GetD2MPQCloseFile();
	D2MPQReadFile = GetD2MPQReadFile();
	D2MPQGetSizeFile = GetD2MPQGetSizeFile();
	D2FogGetSavePath = GetD2FogGetSavePath();
	D2FogGetInstallPath = GetD2FogGetInstallPath();
	D2Fog10212 = GetD2Fog10212();
	D2GetInstructionPointer = GetD2GetInstructionPointer();
}

FogLibrary::TD2FogAssertOld FogLibrary::GetD2FogAssertOld()
{
	return (TD2FogAssertOld)GetOffsetByProc(10023, 10023, 10023, 0, 0, 0, 0, 0);
}

FogLibrary::TD2FogAssert FogLibrary::GetD2FogAssert()
{
	return (TD2FogAssert)GetOffsetByProc(0, 0, 0, 10024, 10024, 10024, 10024, 10024);
}

FogLibrary::TD2FogMemAlloc FogLibrary::GetD2FogMemAlloc()
{
	return (TD2FogMemAlloc)GetOffsetByProc(10042, 10042, 10042, 10042, 10042, 10042, 10042, 10042);
}

FogLibrary::TD2FogMemDeAlloc FogLibrary::GetD2FogMemDeAlloc()
{
	return (TD2FogMemDeAlloc)GetOffsetByProc(10043, 10043, 10043, 10043, 10043, 10043, 10043, 10043);
}

FogLibrary::TD2AllocMem FogLibrary::GetD2AllocMem()
{
	return (TD2AllocMem)GetOffsetByProc(10045, 10045, 10045, 10045, 10045, 10045, 10045, 10045);
}

FogLibrary::TD2FreeMem FogLibrary::GetD2FreeMem()
{
	return (TD2FreeMem)GetOffsetByProc(10046, 10046, 10046, 10046, 10046, 10046, 10046, 10046);
}

FogLibrary::TD2MPQOpenFile FogLibrary::GetD2MPQOpenFile()
{
	return (TD2MPQOpenFile)GetOffsetByProc(10102, 10102, 10102, 10102, 10102, 10102, 10102, 10102);
}

FogLibrary::TD2MPQCloseFile FogLibrary::GetD2MPQCloseFile()
{
	return (TD2MPQCloseFile)GetOffsetByProc(10103, 10103, 10103, 10103, 10103, 10103, 10103, 10103);
}

FogLibrary::TD2MPQReadFile FogLibrary::GetD2MPQReadFile()
{
	return (TD2MPQReadFile)GetOffsetByProc(10104, 10104, 10104, 10104, 10104, 10104, 10104, 10104);
}

FogLibrary::TD2MPQGetSizeFile FogLibrary::GetD2MPQGetSizeFile()
{
	return (TD2MPQGetSizeFile)GetOffsetByProc(10105, 10105, 10105, 10105, 10105, 10105, 10105, 10105);
}

FogLibrary::TD2FogGetSavePath FogLibrary::GetD2FogGetSavePath()
{
	return (TD2FogGetSavePath)GetOffsetByProc(10115, 10115, 10115, 10115, 10115, 10115, 10115, 10115);
}

FogLibrary::TD2FogGetInstallPath FogLibrary::GetD2FogGetInstallPath()
{
	return (TD2FogGetInstallPath)GetOffsetByProc(10116, 10116, 10116, 10116, 10116, 10116, 10116, 10116);
}

FogLibrary::TD2Fog10212 FogLibrary::GetD2Fog10212()
{
	return (TD2Fog10212)GetOffsetByProc(10212, 10212, 10212, 10212, 10212, 10212, 10212, 10212);
}

FogLibrary::TD2GetInstructionPointer FogLibrary::GetD2GetInstructionPointer()
{
	return (TD2GetInstructionPointer)GetOffsetByProc(0, 0, 0, 10265, 10265, 10265, 10265, 10265);
}