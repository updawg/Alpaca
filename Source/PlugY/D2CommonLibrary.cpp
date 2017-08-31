#include "D2CommonLibrary.h"
#include "Error.h"

void D2CommonLibrary::SetFunctions()
{
	Library::SetFunctions();
	this->D2Common11084 = GetD2Common11084();
}

D2CommonLibrary::TD2Common11084 D2CommonLibrary::GetD2Common11084()
{
	const char* functionName = "GetD2Common11084";
	VersionOffsets offsets = CreateOffsetsUpTo113D(00000, 00000, 00000, 10188, 11084, 11109, 10346, 10907);
	return (TD2Common11084)RetrieveAddress(functionName, DllName, DllOffset, GetOffsetForVersion(offsets));
}