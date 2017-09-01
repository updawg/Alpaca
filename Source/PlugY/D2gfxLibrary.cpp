#include "D2gfxLibrary.h"

void D2gfxLibrary::SetFunctions()
{
	D2GetResolution = GetD2GetResolution();
	D2FillArea = GetD2FillArea();
	D2PrintImage = GetD2PrintImage();
}

D2gfxLibrary::TD2GetResolution D2gfxLibrary::GetD2GetResolution()
{
	return (TD2GetResolution)RetrieveAddressByProc(CreateOffsets(10005, 10005, 10005, 10000, 10063, 10043, 10031, 10012));
}

D2gfxLibrary::TD2FillArea D2gfxLibrary::GetD2FillArea()
{
	return (TD2FillArea)RetrieveAddressByProc(CreateOffsets(10055, 10055, 10055, 10028, 10000, 10062, 10014, 10028));
}

D2gfxLibrary::TD2PrintImage D2gfxLibrary::GetD2PrintImage()
{
	return (TD2PrintImage)RetrieveAddressByProc(CreateOffsets(10072, 10072, 10072, 10047, 10044, 10024, 10041, 10042));
}