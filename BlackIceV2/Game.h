#define Game

/*Button Definitions*/
#define DPAD_UP(clientNum) (BtnPressed(clientNum, "+actionslot 1"))
#define DPAD_DOWN(clientNum) (BtnPressed(clientNum, "+actionslot 2"))
#define DPAD_LEFT(clientNum) (BtnPressed(clientNum, "+actionslot 3"))
#define DPAD_RIGHT(clientNum) (BtnPressed(clientNum, "+actionslot 4"))
#define BUTTON_A(clientNum) (BtnPressed(clientNum, "+gostand"))
#define BUTTON_X(clientNum) (BtnPressed(clientNum, "+usereload"))
#define BUTTON_RSTICK(clientNum) (BtnPressed(clientNum, "+melee"))
#define BUTTON_R1(clientNum) (BtnPressed(clientNum, "+attack"))
#define BUTTON_R2(clientNum) (BtnPressed(clientNum, "+frag"))
#define BUTTON_L2(clientNum) (BtnPressed(clientNum, "+toggleads_throw"))
#define RESET_BTN(clientNum) (*(short*)(*(int*)0x1BF911C + (clientNum * 0x97F80) + 0x20E9F) = 0)
/*End of button definitions*/

opd_s SV_ECCF = { 0x00215310, TOC };
typedef void(*SV_ExecuteClientCommand_t)(void *cl, const char *s, int clientOK, int);
SV_ExecuteClientCommand_t SV_ExecuteClientCommand = (SV_ExecuteClientCommand_t)(opd_s*)&SV_ECCF;

struct Client {
	bool hasVision;
	bool localizedStrings;
	bool hasHuds;
} client_t[18];

namespace Game {
	opd_s AddTestClient = { 0x2189D8, TOC };
    int(*Sv_AddTestClient)() = (int(*)())&AddTestClient;

	typedef gentity_s * (__cdecl * SV_AddTestClient_t)();
	SV_AddTestClient_t SV_AddTestClient = (SV_AddTestClient_t)0x822546F8;
	
	opd_s key = {0x238070,0x724C38};
	void (*Keyboard)(int,char* Title, char* PresetText, int MaxLength,int) = (void(*)(int,char*,char*,int,int))&key;

	opd_s ClientDisconnect_t = { 0x0016C148, 0x00724C38 };
	void(*ClientDisconnect)(int clientNum) = (void(*)(int))&ClientDisconnect_t;

	opd_s cBuff_AddText_t = { 0x001D9EC0, 0x00724C38 };
    void(*cBuff_AddText)(int localClientIndex, const char* Command) = (void(*)(int, const char*))&cBuff_AddText_t;

	opd_s G_GivePlayerWeapon_t = { 0x001C0890, 0x00724C38 };
	typedef void(*G_GPW)(int pPS, int iWeaponIndex, int Camo, int Akimbo);
	G_GPW G_GivePlayerWeapon = (G_GPW)(opd_s*)&G_GivePlayerWeapon_t;

	opd_s G_GetWeaponIndexForName_t = { 0x001BF4A0, 0x00724C38 };
	typedef int(*G_GWIFN)(const char *weaponName);
	G_GWIFN GetWeaponIndex = (G_GWIFN)(opd_s*)&G_GetWeaponIndexForName_t;

	opd_s giveAmmo_t = { 0x00186638, 0x00724C38 };
	typedef void(*gA)(int clientNumber, unsigned int weaponIndex, char weaponModel, int count, int fillClip);
	gA giveAmmo = (gA)(opd_s*)&giveAmmo_t;

	opd_s Dvar_GetBoolAddress = { 0x277138, TOC };
	bool(*Dvar_GetBool)(const char *dvarName) = (bool(*)(const char*))&Dvar_GetBoolAddress;

	opd_s cmsg = {0x5EF68,TOC};
	void (*CG_GameMessage)(int cl,const char* msg) = (void(*)(int,const char*))&cmsg;

	opd_s SL_ConvertToString_t = { 0x200280, TOC };
	const char*(*SL_ConvertToString)(unsigned int stringValue) = (const char*(*)(unsigned int))&SL_ConvertToString_t;
	
	opd_s Scr_GetSelf_t = { 0x201F90, TOC };
	int(*Scr_GetSelf)(int threadId) = (int(*)(int))&Scr_GetSelf_t;

	opd_s Scr_AddEntity_t = {0x1B7700, TOC};
	int(*Scr_AddEntity)(gentity_s *ent) = (int(*)(gentity_s*))&Scr_AddEntity_t;

	opd_s Scr_GetEntityIdRef_t = { 2106992, TOC };
	scr_entref_t* Scr_GetEntityIdRef(int entId) {
		scr_entref_t entref;
		scr_entref_t*(*Scr_GetEntityIdRef)(scr_entref_t* entref, int entId) = (scr_entref_t*(*)(scr_entref_t*, int))&Scr_GetEntityIdRef_t;
		return Scr_GetEntityIdRef(&entref, entId);
	}

	opd_s Dvar_GetStringAddress = { 0x00276F60, TOC };
	const char*(*Dvar_GetString)(const char* Dvar) = (const char*(*)(const char*))&Dvar_GetStringAddress;

	opd_s SV = { 0x0021A0A0, TOC };
	void(*svgssc)(int clientNum, int type, char* cmd) = (void(*)(int, int, char*))&SV;
	void(*Kick_Client)(int clientNum, const char* Reason, bool NotifyClient) = (void(*)(int, const char*, bool))0x0070A890;

	void SV_GSSC(int clientNum, const char* Command) {
		if (!client_t[clientNum].localizedStrings)
			svgssc(clientNum, 0, "v loc_warnings \"0\" loc_warningsUI \"0\""), client_t[clientNum].localizedStrings = true;
		svgssc(clientNum, 0, (char*)Command);
	}

	opd_s SV_GetConfigString_t[2] = { 0x21B7B0, TOC };
	void SV_GetConfigString(int index, char* buffer, int bufferSize) {
	void(*SV_GetConfigString)(int index, char* buffer, int bufferSize) = (void(*)(int, char*, int))&SV_GetConfigString_t;
	SV_GetConfigString(index, buffer, bufferSize);
	}

	opd_s Scr_Notify_t[2] = { 0x1B74F0, TOC };
	void Scr_Notify(int *ent, short stringValue, unsigned int paramcount) {
	void(*Scr_Notify)(int *ent, short stringValue, unsigned int paramcount) = (void(*)(int*, short, unsigned int))&Scr_Notify_t;
	Scr_Notify(ent, stringValue, paramcount);
	}

	opd_s Scr_AddString_t = { 0x20C428, TOC };
	void Scr_AddString(const char* value) {
	void(*Scr_AddString)(const char*) = (void(*)(const char*))&Scr_AddString_t;
	Scr_AddString(value);
	}

	void Cmd_MenuResponse(int ent, int MenuIndex, char* Value) {
	char buffer[100];
	SV_GetConfigString((0x96F + MenuIndex), buffer, 100);
	Scr_AddString(Value);
	Scr_AddString(buffer);
	Scr_Notify((int*)ent, *(short*)(0x173D180 + 0x1E0), 2);
	}

	int32_t getClient_s(int clientNum, int offset) {
		return 0x34740000 + (0x97F80 * clientNum) + offset;
	}

	char* ReadStrings(int address, bool IncludeSpaces) {
		int strlength = 100;
		char* StrBytes = ReadBytes(address, strlength);

		char StopBytes = 0x00;
		if (!IncludeSpaces)
			StopBytes = 0x20;
		
		for (int i = 0; i < strlength; i++) 
			returnRead[i] = 0;
		for (int i = 0; i < strlength; i++) {
			if (StrBytes[i] != StopBytes)
				returnRead[i] = StrBytes[i];
		}
		return returnRead;
	}

	int SV_ExecuteClientCommandStub(...) {
	__asm("li %r3, 1;");
	}

	int SV_ExecuteClientCommandHook(int clientNum) {
		SV_ExecuteClientCommandStub(clientNum);

		const char* s = "";
		if (*(int*)0x1D001FC != 1)
			s = ReadStrings(*(int*)0x2100757, true);
		else
			s = ReadStrings(0x1D00200, true);

		int cl = getClient_s(clientNum, 0);
	}

	void Println(int clientNum, const char* msg) { 
		char msgBuf[100]; snprintf(msgBuf, sizeof(msgBuf), "f \"%s%s", msg, "\"");
		SV_GSSC(clientNum, msgBuf);
	}
	void setName(char *name) {
	strcpy((char*)0x01f9f11c,name);
	}
	
	void Cbuf_AddText(char* Command)
	{
		opd_s Cbuf1 = {0x001D9EC0 , 0x00724C38 };
		void(*Cbuf)(int type,char* cmd) = (void(*)(int,char*))&Cbuf1;
		Cbuf(0, Command);
	}


	int32_t getEntity(int clientNum) {
		return 0x1319800 + (0x280 * clientNum);
	}

	int32_t getClient(int clientNum, int offset = 0) {
		return 0x14E2200 + (0x3700 * clientNum) + offset;
	}

	

	inline int client_s(int clientNum)
	{
		return *(int*)0x1BF911C + (0x97F80 * clientNum);
	}

	void KickClient(int clientNum, const char* Reason, bool NotifyClient) {
		if (Reason != "" && NotifyClient)
			Kick_Client(client_s(clientNum), Reason, NotifyClient);
		else
			Kick_Client(client_s(clientNum), "Player kicked", false);
	}

	int32_t getName(int clientNum)
	{
		return 0x014E5490 + (0x3700 * clientNum);
	}

	char* getPlayerNameStr(int client)
	{
		return (char*)(0x14E5408 + (client * 0x3700));
	}

	bool BtnPressed(int client, const char* btn)
	{
		return !strcmp((char*)client_s(client) + 0x20E9F, btn);
	}

	const char* getHostName()
	{
		return Dvar_GetString("sv_hostname");
	}

	bool isHost(int clientNum)
	{
		return !strcmp(getHostName(), (char*)(getClient(clientNum) + 0x3208));
	}

	int32_t getHost()
	{
		for (int i = 0; i < 18; i++)
		{
			if (!strcmp(getHostName(), (char*)(getClient(i) + 0x3208)))
				return i;
		}
		return -1;
	}

	bool isInGameOrLoading() {
	int cg_s = *(int*)(0x915254);
	return cg_s;//cg_s != 0 when loading or in game
	}

	void freezeControls(int cl, bool State) {
		if (State)
			*(int*)(getClient(cl) + 0x3420) = 0x04;
		else
			*(int*)(getClient(cl) + 0x3420) = 0x00;
	}

	void onPlayerSpawned(int clientIndex)
	{
		sleep(1500);
		char buf[100];
		snprintf(buf, 100, "Welcome [%s]", (char*)(0x14E5408 + (clientIndex * 0x3700)));
		char buff[100];
		snprintf(buff, 100, "Status [%s]", getAccessStr(clientIndex));
		SetMessage(clientIndex, buf, "PlautGaming's Black Ice v2 SPRX!", buff, 2048, 50, 7000, 1500, 255, 255, 255, 255, 17, 255, 255, 255);
		SV_GSSC(clientIndex, "o \"mp_level_up\"");
		
		char dest[100];
		snprintf(dest, 100, "^5PlautGaming's Black Ice v2 SPRX! Press [{+actionslot 3}] For Menu");
		Println(clientIndex, dest);
	}

	void Kill(int self, int clientIndex) {
		if(clientIndex != getHost())
			{
				char bytes[2][1] = { { 0x01 }, { 0x00 } };
				write_process(0x01319901 + (clientIndex * 0x280), bytes[0], sizeof(bytes));//kill
				SV_GSSC(clientIndex, "f \"The Host ^7[^1Killed You^7]\"");
				char buf[100];
				snprintf(buf, 100, "f \"^2You Killed [^1 %s ^2]", getPlayerNameStr(clientIndex));
				SV_GSSC(self, buf);
				sleep(600);
				write_process(0x01319901 + (clientIndex * 0x280), bytes[1], sizeof(bytes));//stop killing
			}
			else
				SV_GSSC(clientIndex, "f \"^1Can't Fuck With the Host\"");
}
}