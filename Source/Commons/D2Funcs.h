/*======================================================================
	File created by Yohann NICOLAS.
	Add support 1.13d by L'Autour.

  Declares the type for a STDCALL or FASTCALL function pointer
  called N with arguments list P, returning R, namedInDLL D and at @A

======================================================================*/

// D2Common

F7(STD,  D2Common,00000,00000,00000,10188,11084,11109,10346,10907,	DWORD,		D2Common11084, (Room* ptRoom, DWORD zero));
F7(STD,  D2Common,10057,10057,10057,10332,11021,10511,10826,10691,	DWORD,		D2GetLevelID, (Room* ptRoom));
F7(STD,  D2Common,10138,10138,10138,10623,10491,11043,10654,10716,	Room*,		D2GetDropRoom, (Room* ptRoom, Position*, Position*, DWORD, DWORD, DWORD, DWORD));
F7(STD,  D2Common,10242,10242,10242,00000,00000,00000,00000,00000,	Unit*,		D2Common10242, (Inventory* ptInventory, Unit* ptItem, DWORD bIsClient));
F7(STD,  D2Common,10246,10246,10246,10855,10813,10289,10133,10402,	Unit*,		D2CanPutItemInInv, (Inventory* ptInventory, Unit* ptItem, DWORD p3, DWORD zero, Unit* ptUnit, const char* file, DWORD line));
F7(STD,  D2Common,10243,10243,10243,10461,10827,10936,10646,10490,	Unit*,		D2InvRemoveItem, (Inventory* ptInventory, Unit* ptItem));
F7(STD,  D2Common,10249,10249,10249,10880,11068,10436,11107,10963,	DWORD,		D2InvAddItem, (Inventory* ptInventory, Unit* ptItem, DWORD posX, DWORD posY, DWORD vValueC, DWORD bIsClient, BYTE page));//result : boolean 0=echec  ; vValueC = 0 for Game.dll, 1 for Clientdll
F7(STD,  D2Common,10250,10250,10250,00000,00000,00000,00000,00000,	DWORD,		D2Common10250, (const char* file, DWORD line, Inventory* ptInventory, DWORD posX, DWORD posY, DWORD vValueC, DWORD bIsClient, BYTE page));// result : boolean 0=echec  ; vValueC = 0 for Game.dll, 1 for Clientdll
F7(STD,  D2Common,10273,10273,10273,00000,00000,00000,00000,00000,	DWORD,		D2Common10273, (Inventory* ptInventory, void* unknow));
F7(STD,  D2Common,10277,10277,10277,10402,10535,11151,10460,11040,	Unit*,		D2InventoryGetFirstItem, (Inventory* ptInventory));
F7(STD,  D2Common,10304,10304,10304,10934,11140,10770,10464,10879,	Unit*,		D2UnitGetNextItem, (Unit* ptItem));
F7(STD,  D2Common,10305,10305,10305,11095,10748,10852,11147,10897,	Unit*,		D2GetRealItem, (Unit* ptUnit));
F7(STD,  D2Common,10326,10326,00000,00000,00000,00000,00000,00000,	DWORD,		D2GetPosX, (Unit* ptUnit)); //NOT IN 1.10
F7(STD,  D2Common,10329,10329,00000,00000,00000,00000,00000,00000,	DWORD,		D2GetPosY, (Unit* ptUnit)); //NOT IN 1.10
F7(STD,  D2Common,10332,10332,10332,11080,10056,10543,10141,11166,	void,		D2GetPosition, (Unit* ptUnit, Position* pos));
F7(STD,  D2Common,10339,10339,10339,10455,10864,10941,11060,11025,	DWORD,		D2GetMaxGoldBank, (Unit* ptUnit));
F7(STD,  D2Common,10342,10342,10342,10172,10933,10366,10331,10846,	Room*,		D2GetRoom, (Unit* ptUnit));
F7(STD,  D2Common,10420,10420,10420,10218,10079,11097,10356,10404,	PlayerData*,D2InitPlayerData, (Unit* ptChar));
F7(STD,  D2Common,10424,10424,10424,10562,10800,10860,10920,11103,	PlayerData*,D2GetPlayerData, (Unit* ptChar));
F7(STD,  D2Common,10431,10431,10431,00000,00000,00000,00000,00000,	DWORD,		D2GetDefence, (Unit* ptChar));
F7(STD,  D2Common,10433,10433,10433,00000,00000,00000,00000,00000,	DWORD,		D2GetChanceToBlock, (Unit* ptChar, DWORD isLODGame));
F7(STD,  D2Common,10439,10439,10439,10343,11131,10729,10049,11159,	DWORD,		D2GetMaxGold, (Unit* ptUnit));
F7(STD,  D2Common,00000,00000,00000,10440,10572,10481,11090,10193,	DWORD,		D2Common10572, (Unit* ptObject, DWORD value));
F7(STD,  D2Common,00000,00000,00000,10471,11160,10866,10258,10040,	BYTE,		D2GetObjectFlags, (Unit* ptObject));
F7(STD,  D2Common,00000,00000,00000,10572,11048,10150,10111,10033,	void,		D2SetObjectFlags, (Unit* ptObject, BYTE flags));
F7(STD,  D2Common,10487,10487,10487,00000,00000,00000,00000,00000,	DWORD,		D2isInState, (Unit* ptChar, DWORD isLODGame));
F7(STD,  D2Common,10518,10518,10518,10109,10627,10762,10551,10645,	void,		D2AddPlayerStat, (Unit* ptChar, DWORD statID, int amount, DWORD index)); //ONLY 1.11b
F7(STD,  D2Common,10519,10519,10519,11092,10061,10658,10973,10550,	int,		D2GetPlayerStat, (Unit* ptChar, DWORD statID, DWORD index)); //ONLY 1.11b
F7(STD,  D2Common,10521,10521,10521,10733,10550,10494,10587,10216,	int,		D2GetPlayerBaseStat, (Unit* ptChar, DWORD statID, DWORD index)); //ONLY 1.11b
F7(STD,  D2Common,10539,10539,10539,00000,00000,00000,00000,00000,	DWORD,		D2haveDefenceBonus, (Unit* ptChar));
F7(STD,  D2Common,10540,10540,10540,00000,00000,00000,00000,00000,	DWORD,		D2haveFireResBonus, (Unit* ptChar));
F7(STD,  D2Common,10541,10541,10541,00000,00000,00000,00000,00000,	DWORD,		D2haveColdResBonus, (Unit* ptChar));
F7(STD,  D2Common,10542,10542,10542,00000,00000,00000,00000,00000,	DWORD,		D2haveLightResBonus, (Unit* ptChar));
F7(STD,  D2Common,10543,10543,10543,00000,00000,00000,00000,00000,	DWORD,		D2havePoisonResBonus, (Unit* ptChar));
F7(STD,  D2Common,10546,10546,10546,00000,00000,00000,00000,00000,	DWORD,		D2haveDefenceMalus, (Unit* ptChar));
F7(STD,  D2Common,10547,10547,10547,00000,00000,00000,00000,00000,	DWORD,		D2haveFireResMalus, (Unit* ptChar));
F7(STD,  D2Common,10548,10548,10548,00000,00000,00000,00000,00000,	DWORD,		D2haveColdResMalus, (Unit* ptChar));
F7(STD,  D2Common,10549,10549,10549,00000,00000,00000,00000,00000,	DWORD,		D2haveLightResMalus, (Unit* ptChar));
F7(STD,  D2Common,10550,10550,10550,00000,00000,00000,00000,00000,	DWORD,		D2havePoisonResMalus, (Unit* ptChar));
F7(STD,  D2Common,10578,10578,10578,10653,10496,10244,10849,10037,	void*,		D2CompileTxtFile, (DWORD unused, const char* filename, BINField* ptFields, DWORD* ptRecordCount, DWORD recordLength));
F7(STD,  D2Common,10600,10600,10600,10573,10262,10887,10695,10994,	ItemsBIN*,	D2GetItemsBIN, (DWORD itemID));
F7(STD,  D2Common,10616,10616,10616,10500,10523,10774,10806,10619,	GemsBIN*,	D2GetGemsBIN, (DWORD gemID));
F7(STD,  D2Common,11232,11232,11232,10746,10258,10913,10783,10393,	CubeMainBIN*,D2GetCubeMainBIN, (DWORD cubemainID));
F7(STD,  D2Common,11233,11233,11233,10639,11135,10390,10675,10235,	int,		D2GetNbCubeMainBIN, ());
F7(STD,  D2Common,10628,10628,10628,00000,00000,00000,00000,00000,	DWORD,		D2GetNextLevelXP, (DWORD classID, DWORD level));
F7(STD,  D2Common,10629,10629,10629,00000,00000,00000,00000,00000,	DWORD,		D2GetMaxLevel, (DWORD classID));
F7(STD,  D2Common,10655,10655,10655,10655,10309,10297,10218,10694,	DifficultyLevelsBIN*,	D2GetDifficultyLevelsBIN, (DWORD difficultyLevel));
F7(STD,  D2Common,10695,10695,10695,10927,10899,10276,10106,10911,	DWORD,		D2GetItemQuality, (Unit* ptItem));
F7(STD,  D2Common,10707,10707,10707,10911,10303,10989,10202,10458,	DWORD,		D2TestFlags, (Unit* ptUnit, DWORD flags, DWORD line, const char* file));
F7(STD,  D2Common,10717,10717,10717,10898,10100,10410,10086,10008,	DWORD,		D2GetItemLevel, (Unit* ptItem));
F7(STD,  D2Common,10719,10719,10719,10820,10505,10370,10020,10810,	BYTE,		D2ItemGetPage, (Unit* ptUnit));
F7(STD,  D2Common,10720,10720,10720,10485,10608,10223,10012,11026,	void,		D2ItemSetPage, (Unit* ptItem, BYTE page));
F7(STD,  D2Common,10731,10731,10731,11017,10890,10231,10744,10601,	DWORD,		D2CheckItemType, (Unit* ptItem, DWORD itype));
F7(STD,  D2Common,10732,10732,10732,10692,10685,10280,10620,10075,	int,		D2GetUniqueID, (Unit* ptItem));
F7(STD,  D2Common,10734,10734,10734,00000,00000,00000,00000,00000,	void,		D2SetAnim, (Unit* ptUnit, int anim));
F7(STD,  D2Common,10619,10619,10619,10687,10877,10321,11032,10981,	int*,		D2GetNbRunesBIN, ()); //return the point on the number
F7(STD,  D2Common,10620,10620,10620,10775,10296,10622,10006,10405,	RunesBIN*,	D2GetRunesBIN, (int runesID));
F7(STD,  D2Common,11163,11163,11163,10880,11068,10436,11107,10963,	DWORD,		D2isEtheral, (Unit* ptItem)); //ONLY UNTIL 1.10
F7(STD,  D2Common,10881,10881,10881,10956,11156,10218,10987,10665,	DWORD,		D2SaveItem, (Unit* ptItem, saveBitField* data, DWORD startSize, DWORD p4, DWORD p5, DWORD p6));
F7(STD,  D2Common,10953,10953,10953,10099,10255,10210,10302,10335,	void,		D2SetSkillBaseLevel,(Unit* ptChar, DWORD skillID, DWORD slvl, DWORD bRemove, char*, DWORD));
F7(STD,  D2Common,10968,10968,10968,10700,10109,10904,10306,10007,	DWORD,		D2GetSkillLevel, (Unit* ptChar, SkillData* ptSkill, DWORD includingBonus));
F7(STD,  D2Common,11276,11276,11276,10254,10074,10111,10435,11081,	DWORD,		D2GetSkillCost, (Unit* ptChar, int skpoints, DWORD skillID, DWORD curSkillLevel)); //not 10447
A7(FAST, D2Common,00000,00000,82C80, 15D0, 1800, 1220, 12D0, 17B0,	CharStatsBIN*,	D2GetCharStatsBIN, (DWORD charID));
A7(FAST, D2Common,00000,00000,12410,5D7D0,1A100,116C0,1C020,5B0E0,	DWORD,			D2CompileCubeInput, (CubeInput* cubeinput, char* s, DWORD p1, DWORD p2));
A7(FAST, D2Common,00000,00000,12910,5D210,19B40,11100,1BA60,5AB20,	DWORD,			D2CompileCubeOutput, (CubeOutput* cubeoutput, char* s, DWORD p1, DWORD p2));
A7(FAST, D2Common,00000,00000,2B1A0, 11F0, 1380, 1140, 1300, 1160,	ItemTypesBIN*,	D2GetItemTypesBIN, (DWORD itemTypesId));
A7(FAST, D2Common,00000,00000,642B0, 13F0, 12F0, 1540, 17A0, 17E0,	ItemStatCostBIN*,D2GetItemStatCostBIN, (DWORD id));
A7(FAST, D2Common,738A4,739B4,84268, 96E0, 98D0, 9900, 9900, B5E0,	void*,			D2ReadFile,(DWORD unused, char* filename, DWORD* size, const char*, DWORD));
A7(STD,  D2Common,1F500,1F510,29FA0,71EB0,32AA0,7D2A0,59870,80C40,	void,			D2LoadSuperuniques,(DWORD mempool)); //FASTCALL UNTIL 1.10

// D2Client

A7(FAST, D2Client, 1000, 1000, 1000,75D00,A9070,BEF70,2B420,A9480,	void*,		D2LoadImage, (const char* filename, DWORD filetype));
A7(FAST, D2Client, 1150, 1150, 1140,00000,00000,00000,00000,00000,	void,		D2FreeImage, (void* image));//6FAA1140
A7(FAST, D2Client, D640, D630, DB50,73620,5E4E0,79670,147A0,B6890,	void,		D2SendMsgToAll,(BYTE* data));//1.11 and 1.11b by ESI !!
A7(STD,  D2Client,00000,00000,15A80,00000,00000,00000,00000,00000,	DWORD,		D2GetLastMonsterIDFight, ());//6FAB5A80
A7(STD,  D2Client,29800,297F0,2FD60,828A0,89320,6B280,BCEA0,BF640,	void,		D2PrintStatsPage, ());
A7(FAST, D2Client,4BB20,4BB20,521C0,B8CB0,21250,88EA0,54E10,2CE40,	DWORD,		D2PrintStat,(Unit* ptItem, Stats* ptStats, DWORD statID, DWORD statIndex, DWORD statValue, LPWSTR lpText));//statID=EAX, lpText=ESI 1.11b
A7(FAST, D2Client,85A60,84DE0,80430,9EEB0,62070,8B7A0,BF5F0,18820,	LPWSTR,		D2SetColorPopup, (LPWSTR popupText, DWORD color));//1.11 and 1.11b BY EDI
A7(FAST, D2Client,B4360,B36E0,B5820,3ACC0,54210,31FA0,88A70,26270,	DWORD,		D2PlaySound, (DWORD id, DWORD, DWORD, DWORD, DWORD));
A7(FAST, D2Client,00000,00000,00000,00000,571C0,18450,46150,790D0,	Unit*,		D2GetCurrentNPC, ());
A7(FAST, D2Client,00000,00000,00000,73260,5DE40,791A0,143E0,B61F0,	void,		D2SendToServerXX,(DWORD size, BYTE * data));//by EBX
A7(FAST, D2Client,88940,87CC0,83260,A1F30,65690,8EF00,C2790,1C190,	void,		D2TogglePage, (DWORD a, DWORD b, DWORD c));
A7(FAST, D2Client,00000,00000,00000,A6520,710C0,A6640,8CD00,90C10,	void,		D2ClickOnStashButton, (DWORD x, DWORD y));//BY x=ESI y=EDI
A7(STD,  D2Client,897B0,88B30,84110,9E3B0,621C0,8B8F0,BEAF0,18AA0,	void*,		D2LoadBuySelBtn, ());
A7(FAST, D2Client,00000,00000,00000,8E480,5BA90,1CC00,4ABE0,7DC60,	void,		D2ReloadGambleScreen, ());

// D2Game

F7(FAST, D2Game,10059,10059,10059,10039,10007,10037,10049,10002,	void,		D2SetNbPlayers, (DWORD nbPlayers));
A7(FAST, D2Game,00000,00000, 6C60,E3DA0,E8210,EB060,49930,E5070,	void,		D2AddClient, (DWORD clientID));//BY EAX
A7(STD,  D2Game,00000,00000, 94E0,E0520,E49A0,A6360,2AAE0,BC700,	Game*,		D2GetGameByClientID, (DWORD clientID));//6FC394E0
A7(FAST, D2Game,00000,00000, B0E0,DF250,E36D0,A5080,29820,BB510,	void,		D2BroadcastFunction, (Game* ptGame, void* fct, void* param));//00DAB0E0
A7(FAST, D2Game, C380, C650, C710,41420,A0D50,7D220,8A3E0,DB780,	DWORD,		D2SendPacket, (void* ptNetClient, LPVOID pData, DWORD size));//EAX=ptNetClient [ESP]=pData
A7(FAST, D2Game, D650, D920, DB50,44D00,A3F20,802E0,8D5F0,DD4F0,	void,		D2SetSkillBaseLevelOnClient, (void* ptClient, Unit* ptChar, DWORD skillID, DWORD sLvl, DWORD bRemove));//by EAX,ESI,EBX
A7(STD,  D2Game,00000,00000,00000,27230,109F0,AE930,A22E0,15F40,	DWORD,		D2LinkPortal, (Game* ptGame, Unit* ptObject, DWORD levelEndID, DWORD levelStartID));
A7(FAST, D2Game,00000,00000,128F0,38D90,43E60,11FF0,D2070,B2F70,	DWORD,		D2VerifIfNotCarry1, (Unit* ptItem, ItemsBIN* itemsData, Unit* ptFirstItem));// BY EBX=itemsData EAX=ptFirstItem [ESP]=ptItem
A7(FAST, D2Game,00000,00000,22070, 1090, 1DF0, 11F0, 1280, 1340,	Room*,		D2TestPositionInRoom, (Room* ptRoom, DWORD x, DWORD y));
A7(FAST, D2Game,00000,00000,3F220,4ABE0,EC7E0,40B90,24950,CDE20,	DWORD,		D2SpawnMonster, (Game* ptGame, Room* ptRoom, DWORD zero1, DWORD x, DWORD y, DWORD minusOne, DWORD superuniqueID, DWORD zero2));//wrong param
A7(STD,  D2Game,00000,00000,00000,D6D10,235C0, D410,200E0,59980,	void,		D2Game235C0, (Game* ptGame, Room* ptRoom));
A7(FAST, D2Game,4F100,4F500,5B8A0,B9D70,25D50,44950,54810,3A4C0,	DWORD,		D2LoadInventory, (Game* ptGame, Unit* pChar, saveBitField* pdata, DWORD p2, DWORD maxSize, DWORD p4, DWORD *ptNbBytesRead));//6FC8B8A0
A7(FAST, D2Game,7BAE0,7BFD0,8BB00,97620,BEF80,93650,E03A0,6DC40,	Unit*,		D2GameGetObject, (Game* ptGame, DWORD type, DWORD itemNum));//6FCBBB00
A7(FAST, D2Game,00000,00000,00000,99760,C09E0,94E70,E1D90,6FE10,	Unit*,		D2CreateUnit, (DWORD type, DWORD id, DWORD x, DWORD y, Game* ptGame, Room* ptRoom, DWORD uk1, DWORD uk2, DWORD uk3));
A7(FAST, D2Game,00000,00000,00000,9B480,34920,D1AA0,70180,941E0,	void,		D2OpenPandPortal, (Game* ptGame, Unit* ptChar));
A7(FAST, D2Game,00000,00000,00000,9B470,34910,D1A90,70170,941D0,	void,		D2OpenPandFinalPortal, (Game* ptGame, Unit* ptChar));
A7(FAST, D2Game,00000,00000,00000,84730,85AA0,DBE90,A9610,31920,	void,		D2MephIA, (Game* ptGame, Unit* ptMonster, DWORD*));
A7(FAST, D2Game,00000,00000,00000,75980,D7BD0,CD0F0,85B60,4EAD0,	void,		D2DiabloIA, (Game* ptGame, Unit* ptMonster, DWORD*));
A7(FAST, D2Game,00000,00000,00000,EAB20,2BC80,B3B90,B8610,C8850,	void,		D2BaalIA, (Game* ptGame, Unit* ptMonster, DWORD*));
A7(FAST, D2Game,00000,00000,00000,70320,D2D70,C2A90,7B4E0,49480,	void,		D2UberMephIA, (Game* ptGame, Unit* ptMonster, DWORD*));
A7(FAST, D2Game,00000,00000,00000,7F200,7FE60,D6250,A39D0,2C3F0,	void,		D2UberDiabloIA, (Game* ptGame, Unit* ptMonster, DWORD*));
A7(FAST, D2Game,00000,00000,00000,E92B0,2A300,B2210,B6C80,C6EC0,	void,		D2UberBaalIA, (Game* ptGame, Unit* ptMonster, DWORD*));
A7(STD,  D2Game,00000,00000, 89C0,E2390,E66D0,A8090,2C830,BE660,	void,		D2SaveGame, (Game* ptGame) );

// D2Net

F7(STD,  D2Net,	10005,10005,10005,10035,10020,10036,10024,10015,	DWORD,		D2SendToServer, (DWORD size, DWORD one, void* data));//(DWORD zero, void* data, DWORD size) for 1.10 and before
F7(STD,  D2Net,	10006,10006,10006,10018,10018,10015,10002,10012,	DWORD,		D2SendToClient, (DWORD zero, DWORD clientID, void* data, DWORD size));

// Fog

F7(STD,  Fog,	10023,10023,10023,00000,00000,00000,00000,00000,	void,		D2FogAssertOld, (const char* ptMessage, DWORD eip, DWORD line));//(STDCALL until 1.10)
F7(FAST, Fog,	00000,00000,00000,10024,10024,10024,10024,10024,	void,		D2FogAssert, (const char* ptMessage, DWORD eip, DWORD line));
F7(FAST, Fog,	10042,10042,10042,10042,10042,10042,10042,10042,	void*,		D2FogMemAlloc, (DWORD dwMemSize, LPCSTR lpszErrFile, DWORD ErrLine, DWORD Zero));
F7(FAST, Fog,	10043,10043,10043,10043,10043,10043,10043,10043,	void*,		D2FogMemDeAlloc, (void* ptMemLoc, LPCSTR lpszErrFile, DWORD ErrLine, DWORD Zero));
F7(FAST, Fog,	10045,10045,10045,10045,10045,10045,10045,10045,	void*,		D2AllocMem, (DWORD,DWORD dwMemSize, LPCSTR lpszErrFile, DWORD ErrLine, DWORD Zero));
F7(FAST, Fog,	10046,10046,10046,10046,10046,10046,10046,10046,	void*,		D2FreeMem, (DWORD,void* ptMemLoc, LPCSTR lpszErrFile, DWORD ErrLine, DWORD Zero));
F7(FAST, Fog,	10102,10102,10102,10102,10102,10102,10102,10102,	DWORD,		D2MPQOpenFile, (char* ptPath, void** buf));
F7(FAST, Fog,	10103,10103,10103,10103,10103,10103,10103,10103,	DWORD,		D2MPQCloseFile, (void* mpqfile));
F7(FAST, Fog,	10104,10104,10104,10104,10104,10104,10104,10104,	DWORD,		D2MPQReadFile, (void* mpqfile, BYTE* buffer, DWORD nbToRead, DWORD* nbRead,DWORD,DWORD,DWORD));
F7(FAST, Fog,	10105,10105,10105,10105,10105,10105,10105,10105,	DWORD,		D2MPQGetSizeFile, (void* mpqfile, DWORD* toReset));
F7(FAST, Fog,	10115,10115,10115,10115,10115,10115,10115,10115,	void,		D2FogGetSavePath, (char* ptPath, DWORD maxsize));
F7(FAST, Fog,	10116,10116,10116,10116,10116,10116,10116,10116,	void,		D2FogGetInstallPath, (char* ptPath, DWORD maxsize));
F7(STD,  Fog,	10212,10212,10212,10212,10212,10212,10212,10212,	void,		D2Fog10212, (DWORD unknow));
F7(STD,  Fog,	00000,00000,00000,10265,10265,10265,10265,10265,	int,		D2GetInstructionPointer, ());


// D2Lang

F7(FAST, D2Lang,	10003,10003,10003,10002,10004,10010,10011,10011,	LPWSTR,		D2GetStringFromString, (const char* ptString));//6FC13BC0 LAutour
F7(FAST, D2Lang,	10004,10004,10004,10005,10000,10005,10003,10004,	LPWSTR,		D2GetStringFromIndex, (WORD dwIndexNum));
F7(STD,  D2Lang,	10007,10007,10007,10009,10013,10002,10009,10001,	DWORD,		D2GetLang, ());//14b  00522A20
F7(STD,  D2Lang,	10010,10010,10010,00000,00000,00000,00000,00000,	DWORD,		D2PrintBigNumber, (LPWSTR ptBuf , DWORD number, DWORD size));//6FC14210

// Storm

F7(STD,  Storm,	  268,  268,  268,  268,  268,  268,  268,  268,	DWORD,		D2StormMPQOpenFile, (DWORD zero, LPCSTR fileName, DWORD dwSearchScope, void** buffer))
F7(STD,  Storm,	  503,  503,  503,  503,  503,  503,  503,  503,	void,		D2Storm503, (DWORD, DWORD, DWORD));
F7(STD,  Storm,	  511,  511,  511,  511,  511,  511,  511,  511,	void,		D2FreeWinMessage, (sWinMessage* msg));

// D2gfx

F7(STD,  D2gfx,	10005,10005,10005,10000,10063,10043,10031,10012,	DWORD,		D2GetResolution,() );
F7(STD,  D2gfx,	10055,10055,10055,10028,10000,10062,10014,10028,	void,		D2FillArea,(DWORD x1, DWORD y1, DWORD x2, DWORD y2, DWORD color, DWORD transTbl));
F7(STD,  D2gfx,	10072,10072,10072,10047,10044,10024,10041,10042,	void,		D2PrintImage,(sDrawImageInfo* data, DWORD x, DWORD y, DWORD p4, DWORD p5, DWORD p6) );


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