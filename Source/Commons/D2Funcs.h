/*======================================================================
	File created by Yohann NICOLAS.
	Add support 1.13d by L'Autour.

  Declares the type for a STDCALL or FASTCALL function pointer
  called N with arguments list P, returning R, namedInDLL D and at @A

======================================================================*/

// Variables

C7(D2Client, D50E8, D40E0, D40F0, F5C60, F4FC8, DC6E4, DBC4C, F7038,	DWORD,		ResolutionY);//0x258 = 600
C7(D2Client, D50EC, D40E4, D40F4, F5C5C, F4FC4, DC6E0, DBC48, F7034,	DWORD,		ResolutionX);//0x320 = 800
C7(D2Client,125AD8,124958,11A74C,11BD28,11BEFC,11BD2C,11B9A4,11D358,	DWORD,		NegWindowStartY);//0xFFFFFFC4 = -60
C7(D2Client,125AD4,124954,11A748,11BD24,11BEF8,11BD28,11B9A0,11D354,	DWORD,		WindowStartX);//0x50 = 80
C7(D2Client,000000,000000,000000, FB3F4,11A2F4,10330C,119854,1087B4,	DWORD,		IsLodGame);
C7(D2Client,000000,000000,10795C,11BFB8,11C2A8,11BFF4,000000,000000,	BYTE,		DifficultyLevel);
C7(D2Client,000000,000000,000000,10A40C,11B414,101634,11B824,11C94C,	DWORD,		MouseY);//0x258 = 600
C7(D2Client,000000,000000,000000,10A410,11B418,101638,11B828,11C950,	DWORD,		MouseX);//0x320 = 800
C7(D2Client,000000,000000,000000,11C4F0,11C1E0,11C3D0,11BBFC,11D050,	Unit*,		ptClientChar);
C7(D2Client, DB918, DA828,000000,000000,000000,000000,000000,000000,	DWORD,		NbStatDesc);
C7(D2Client, DAF98, D9EA8,000000,000000,000000,000000,000000,000000,	DWORD,		StatDescTable);

C7(D2Game, F2A80, F2918, 113FB8, 111718, 1115E0, 1105E0, 1107B8, 1105E0, NetClient*, ClientTable);