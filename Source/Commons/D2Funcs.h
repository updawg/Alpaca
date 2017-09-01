/*======================================================================
	File created by Yohann NICOLAS.
	Add support 1.13d by L'Autour.

  Declares the type for a STDCALL or FASTCALL function pointer
  called N with arguments list P, returning R, namedInDLL D and at @A

======================================================================*/

// D2Net

F7(STD,  D2Net,	10005,10005,10005,10035,10020,10036,10024,10015,	DWORD,		D2SendToServer, (DWORD size, DWORD one, void* data));//(DWORD zero, void* data, DWORD size) for 1.10 and before
F7(STD,  D2Net,	10006,10006,10006,10018,10018,10015,10002,10012,	DWORD,		D2SendToClient, (DWORD zero, DWORD clientID, void* data, DWORD size));

// D2Lang

F7(FAST, D2Lang,	10003,10003,10003,10002,10004,10010,10011,10011,	LPWSTR,		D2GetStringFromString, (const char* ptString));//6FC13BC0 LAutour
F7(FAST, D2Lang,	10004,10004,10004,10005,10000,10005,10003,10004,	LPWSTR,		D2GetStringFromIndex, (WORD dwIndexNum));
F7(STD,  D2Lang,	10007,10007,10007,10009,10013,10002,10009,10001,	DWORD,		D2GetLang, ());//14b  00522A20
F7(STD,  D2Lang,	10010,10010,10010,00000,00000,00000,00000,00000,	DWORD,		D2PrintBigNumber, (LPWSTR ptBuf , DWORD number, DWORD size));//6FC14210

// Storm

F7(STD,  Storm,	  268,  268,  268,  268,  268,  268,  268,  268,	DWORD,		D2StormMPQOpenFile, (DWORD zero, LPCSTR fileName, DWORD dwSearchScope, void** buffer))
F7(STD,  Storm,	  503,  503,  503,  503,  503,  503,  503,  503,	void,		D2Storm503, (DWORD, DWORD, DWORD));
F7(STD,  Storm,	  511,  511,  511,  511,  511,  511,  511,  511,	void,		D2FreeWinMessage, (sWinMessage* msg));

// D2Win

F7(FAST, D2Win, 10046,10046,10046,10061,10075,10015,10022,10051,	void,		D2PrintLineOnTextBox,(void* screen, char* s, DWORD color) );
F7(FAST, D2Win, 10117,10117,10117,10020,10064,10001,10150,10076,	void,		D2PrintString,(LPWSTR s, DWORD x, DWORD y, DWORD color, DWORD bfalse) );
F7(FAST, D2Win, 10121,10121,10121,10034,10128,10132,10028,10150,	DWORD,		D2GetPixelLen,(LPWSTR s) );
F7(FAST, D2Win, 10127,10127,10127,10141,10170,10010,10184,10047,	DWORD,		D2SetFont,(DWORD fontID) );
F7(FAST, D2Win, 10129,10129,10129,10118,10039,10031,10085,10137,	void,		D2PrintPopup,(LPWSTR s, DWORD x, DWORD y, DWORD color, DWORD center) );
F7(FAST, D2Win, 10131,10131,10131,00000,00000,00000,00000,00000,	void,		D2GetPixelRect,(LPWSTR s, DWORD* x, DWORD* y) );//6F8AB260
F7(FAST, D2Win, 10132,10132,10132,00000,00000,00000,00000,00000,	DWORD,		D2PrintTextPopup,(LPWSTR s, DWORD x, DWORD y, DWORD uk, DWORD type, DWORD color) );//6F8AB080
F7(STD,  D2Win, 10017,10017,10017,10147,10113,10098,10098,10164,	void*,		D2CreateTextBox,(DWORD* data) );


// D2CMP

F7(STD,  D2CMP,	10032,10032,10032,10021,10014,10106,10065,10020,	DWORD,		D2CMP10014, (void* image) );

// Other

//ONLY UNTIL 1.10 :
A7(FAST, D2Client,	 BA00, B9F0, C080,00000,00000,00000,00000,00000,	DWORD,		D2isLODGame, ());//6FAAC080
A7(FAST, D2Client,	00000,00000, C090,00000,00000,00000,00000,00000,	BYTE,		D2GetDifficultyLevel, ());//6FAAC090  1.09 should be BA10 (b) BA00 (d)
A7(STD,  D2Client,	B6670,B59F0,B7BC0,00000,00000,00000,00000,00000,	DWORD,		D2GetMouseX, ());//6FB57BC0
A7(STD,  D2Client,	B6680,B5A00,B7BD0,00000,00000,00000,00000,00000,	DWORD,		D2GetMouseY, ());//6FB57BD0
A7(STD,  D2Client,	8DC40,8CFC0,883D0,00000,00000,00000,00000,00000,	Unit*,		D2GetClientPlayer, ());//6FB283D0
A7(FAST, D2Client,	 B920, B910, BF60,00000,00000,00000,00000,00000,	void,		D2CleanStatMouseUp, ());//6FAABF60
A7(FAST, D2Client,	 D210, D200, D990,00000,00000,00000,00000,00000,	void,		D2SendToServer3, (BYTE type, WORD p));//6FAAD990
A7(FAST, D2Game,	7C2C0,7C7B0,8C2E0,00000,00000,00000,00000,00000,	NetClient*,	D2GetClient, (Unit* ptUnit, char* lpszErrFile, DWORD ErrLine));//6FCBC2E0

// Variables

C7(D2Client, D50E8, D40E0, D40F0, F5C60, F4FC8, DC6E4, DBC4C, F7038,	DWORD,		ResolutionY);//0x258 = 600
C7(D2Client, D50EC, D40E4, D40F4, F5C5C, F4FC4, DC6E0, DBC48, F7034,	DWORD,		ResolutionX);//0x320 = 800
C7(D2Client,125AD8,124958,11A74C,11BD28,11BEFC,11BD2C,11B9A4,11D358,	DWORD,		NegWindowStartY);//0xFFFFFFC4 = -60
C7(D2Client,125AD4,124954,11A748,11BD24,11BEF8,11BD28,11B9A0,11D354,	DWORD,		WindowStartX);//0x50 = 80
C7(D2Game,   F2A80, F2918,113FB8,111718,1115E0,1105E0,1107B8,1105E0,	NetClient*,	ClientTable);
C7(D2Client,000000,000000,000000, FB3F4,11A2F4,10330C,119854,1087B4,	DWORD,		IsLodGame);
C7(D2Client,000000,000000,10795C,11BFB8,11C2A8,11BFF4,000000,000000,	BYTE,		DifficultyLevel);
C7(D2Client,000000,000000,000000,10A40C,11B414,101634,11B824,11C94C,	DWORD,		MouseY);//0x258 = 600
C7(D2Client,000000,000000,000000,10A410,11B418,101638,11B828,11C950,	DWORD,		MouseX);//0x320 = 800
C7(D2Client,000000,000000,000000,11C4F0,11C1E0,11C3D0,11BBFC,11D050,	Unit*,		ptClientChar);
C7(D2Client, DB918, DA828,000000,000000,000000,000000,000000,000000,	DWORD,		NbStatDesc);
C7(D2Client, DAF98, D9EA8,000000,000000,000000,000000,000000,000000,	DWORD,		StatDescTable);