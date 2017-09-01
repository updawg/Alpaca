#include "D2CMPLibrary.h"

void D2CMPLibrary::SetFunctions()
{
	D2CMP10014 = GetD2CMP10014();
}

D2CMPLibrary::TD2CMP10014 D2CMPLibrary::GetD2CMP10014()
{
	return (TD2CMP10014)RetrieveAddressByProc(CreateOffsets(10032, 10032, 10032, 10021, 10014, 10106, 10065, 10020));
}