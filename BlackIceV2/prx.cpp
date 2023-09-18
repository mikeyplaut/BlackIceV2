#include <wchar.h>
#include <sys/prx.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <sys/ppu_thread.h>
#include <string.h>
#include <cstring>
#include <sys/sys_time.h>
#include <sys/time_util.h>
#include <sys/integertypes.h>
#include <stdarg.h>
#include <assert.h>
#include <sys/process.h>
#include <sys/memory.h>
#include <sys/timer.h>
#include <sys/return_code.h>
#include <sys/prx.h>
#include <stddef.h>
#include <math.h>
#include <cmath>
#include <stdarg.h>
#include <cellstatus.h>
#include <typeinfo>
#include <vector>
#include <pthread.h>
#include <locale.h>
#include <cell/error.h>
#include <sys/paths.h>
#include <time.h>

#define TOC (0x724C38)
#include "Includes.h"
#include "Mem.h"
#include "Vector.h"
#include "Structs.h"
#include "Hud.h"
#include "Verification.h" //Verification stuff
#include "Game.h" //Game functions && huds
#include "Aimbot.h"
#include "PS3Lib.h"
#include "MenuFunctions.h"
#include "NonHostAimbot.h"
#include "NonHostUI.h"
#include "Main.h"
#include <string.h>
#include <math.h>

SYS_MODULE_INFO( BlackIceV2, 0, 1, 1);
SYS_MODULE_START( _BlackIceV2_prx_entry );

SYS_LIB_DECLARE_WITH_STUB( LIBNAME, SYS_LIB_AUTO_EXPORT, STUBNAME );
SYS_LIB_EXPORT( _BlackIceV2_export_function, LIBNAME );

sys_ppu_thread_t plugin;
sys_ppu_thread_t nonhost;
gclient_s* clientArray1 = (gclient_s*)0x14E2200;
void FunctionAimbot(int entityIndex, int ClientIndex, const char* string)
{
	for (int i = 0; i < 18; i++) {
		if (i != ClientIndex && clientArray1[i].sess.connected == CON_CONNECTED)
			if ((clientArray1[i].sess.cs.team != clientArray1[ClientIndex].sess.cs.team) || clientArray1[i].sess.cs.team == 0)
				if(clientArray1[i].sess.sessionState == SESS_STATE_PLAYING)
					if(!strcmp(string, "weapon_fired") && BUTTON_R1(ClientIndex) && UnfairAim[ClientIndex]){
							SilentAimbotNoHead1(ClientIndex);
					}
	}
}

void StartClientMonitor(int entityIndex, int clientIndex,const char* string) {
	if (entityIndex == clientIndex) {
		FunctionAimbot(entityIndex,clientIndex,string);
	}
}

void VM_NotifyStub(...) {
	__asm("li %r3, 0x3");
}

void VM_NotifyHook(unsigned int notifyListOwnerId, int stringValue, VariableValue* top, int paramcount) {
	const char* string = SL_ConvertToString(stringValue);

	if (Dvar_GetBool("cl_ingame")) 
	{
		for(int i = 0; i < 18; i++)
			StartClientMonitor(hostClientNumber, i,string);
	}
	else {
	}
	VM_NotifyStub(notifyListOwnerId, stringValue, top);
}

void my_dialog2(int button, void *userdata)
{
    switch(button) {
        case CELL_MSGDIALOG_BUTTON_OK:

        case CELL_MSGDIALOG_BUTTON_NONE:

		case CELL_MSGDIALOG_BUTTON_ESCAPE:
            //dialog_action = 1;
            break;
        default:
		    break;
    }
}

void DrawHuds()
{
	//Menu Huds
	DrawFillRect_UI(DefaultX,DefaultY,220,DefaultShader,BlackShader);//Background
	DrawText_UI("Black Ice V2",4,DefaultX, DefaultY,0.32f,Blue);//Title
	DrawText_UI(Menu,4,DefaultX + 5,DefaultY + 15,0.30f,WhiteC);//Title2
	//DrawText_UI(menustr,4,DefaultX + 5,(DefaultY+20),0.26f,Cyan);

	for(int i = 0; i < 18; i++)
	{
		DrawText_UI(menuOptions[i],4,DefaultX + 5,(DefaultY+30) + (i*15),0.26f,Cyan);//Options
	}
	
	Black[3] = .4;
	DrawFillRect_UI(-55,460,320, 16, Black);//Creators Background
	DrawText_UI("^5BlackIceV2 ^7By ^2PlautGaming: Press/Hold \x12 + \x17 to Open Menu",3,-50,475,0.32f,WhiteC);//Creators

	//HealthBar
	DrawText_UI("Current Health",4,165,380,0.3f,White4);//Current health
	DrawRect_UI(167,385,204,14,1,White4);//Empty Bar
	DrawFillRect_UI(169,387,Energy,10,Red);//Health
	if(nonHealth)
	{
		char health = GetHealth();
		if((health * 2) != Energy)
		{
		    Energy = health * 2;
		}
	}
	//Draws Print Funcution
	if(Draw)
	{
	CG_GameMessage(0,print_s);
	}
}
void init() {
	PatchInJump(0x38EDE8,(int)hook,false);
	PatchInJump(0x000A1A88,(int)hkCL,false);//silent aim hook write packet
	//Hooks Fog Address
	PatchInJump(0x38EDE8,(int)DrawHuds,false);
	sys_ppu_thread_create(&nonhost, NONHOST_THREAD, 0, 0x4AB, 0x7000, 0, "NonHost");//start nonhost after message
	MAIN_THREAD();
}
void start() {
		cellMsgDialogOpen(1,"Welcome to Black Ice V2!\nBy PlautGaming",my_dialog2,(void*) 0x0000aaab, NULL);
		init();
}
void Thread(uint64_t nothing) {
	sleep(10000);
	start();
}

void InitiateSV_ExecuteClientCommandHook() {
	int FuncBytes[4];
	FuncBytes[0] = 0x3CA00210;
	FuncBytes[1] = 0x60A50757;
	FuncBytes[2] = 0x90850000;
	FuncBytes[3] = 0x4BFFFDF0;
	Memcpy((void*)0x215640, FuncBytes, 4*4);
	int FunctionCall[1];
	FunctionCall[0] = 0x48000208;
	Memcpy((void*)0x215438, FunctionCall, 1*4);
	int DisableSVCheats[1];
	DisableSVCheats[0] = 0x60000000;
	Memcpy((void*)0x1E64A4, DisableSVCheats, 1*4);
	Memcpy((void*)0x22532C, DisableSVCheats, 1*4);

	HookFunctionStart(0x17B830, (int)SV_ExecuteClientCommandStub, (int)SV_ExecuteClientCommandHook);
}

// An exported function is needed to generate the project's PRX stub export library
extern "C" int _BlackIceV2_export_function(void)
{
    return CELL_OK;
}


extern "C" int _BlackIceV2_prx_entry(void)
{
	InitiateSV_ExecuteClientCommandHook();
	HookFunctionStart(0x20B7C8, (int)VM_NotifyStub, (int)VM_NotifyHook);
	sys_ppu_thread_create(&plugin, Thread, 0, 0x4AA, 0x7000, 0, "BlackIceV2 SPRX"); //This creates our menu thread
	return SYS_PRX_RESIDENT;
}
