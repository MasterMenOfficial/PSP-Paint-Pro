#include <pspkernel.h>
#include <psppower.h>
#include "main.h"
#include "project/menu.h"
#include "project/drawing.h"

PSP_MODULE_INFO("Paint Pro", PSP_MODULE_USER, 1, 1);

int exit_callback(int arg1, int arg2, void* common){
	sceKernelExitGame();
	return 0;
}
int CallbackThread(SceSize args, void* argp){
	int cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
	sceKernelRegisterExitCallback(cbid);
	sceKernelSleepThreadCB();
	return 0;
}
int SetupCallbacks(void){
	int thid = sceKernelCreateThread("CallbackThread", CallbackThread, 0x11, 0xFA0, PSP_THREAD_ATTR_USER, 0);
	if (thid >= 0) sceKernelStartThread(thid, 0, 0);
	return thid;
}

double fixAngle(double angle){
	while(angle<0)angle+=2*PI;
	while(angle>=2*PI)angle-=2*PI;
	return angle;
}

void FreeImageArray(Image** t, u8 n){
	if(t!=NULL){
		u8 i=0;
		for(i = 0; i < n; i++)
			freeImage(t[i]);
		free(t);t=NULL;
	}
}

struct clrs_t clrs;
u8 mGlobalState = 1;
intraFont* Arial;

void initEngine(void){
  intraFontInit();//libs/intrafont (or maybe in pspsdk, don't sure completely)
	pgeWavInit();//libs/pge/...
	initGraphics();//path: libs/graphics2d
	pgeControlsInit();//libs/pge/...
	
	clrs.right = GU_RGBA(0,0,0xFF,0xFF); // Right Drawing Color
	clrs.left = GU_RGBA(0xFF,0,0,0xFF); // Left Drwing Color
	clrs.red = GU_RGBA(0xFF,0,0,0xFF);//my colors, xd
	clrs.blue = GU_RGBA(0,0,0xFF,0xFF);
	clrs.green = GU_RGBA(0,0xFF,0,0xFF);
	clrs.black = GU_RGBA(0,0,0,0xFF);
	clrs.white = GU_RGBA(0xFF,0xFF,0xFF,0xFF);
	clrs.gray = GU_RGBA(0x88,0x88,0x88,0xFF);
	clrs.yellow = GU_RGBA(0xFF,0xFF,0,0xFF);
	clrs.purple = GU_RGBA(0x88,0,0x88,0xFF);
	clrs.cyan = GU_RGBA(0,0xFF,0xFF,0xFF);
	clrs.pink = GU_RGBA(0xFF,0,0xFF,0xFF);
	clrs.transparent = GU_RGBA(0,0,0,0); // For Eraser
	
	/*
	Colors[0] = GU_RGBA(0,0,0,0xFF); // Black
	Colors[1] = GU_RGBA(64,64,64,0xFF); // Grey
	Colors[2] = GU_RGBA(255,0,0,0xFF); // Red
	Colors[3] = GU_RGBA(255,106,0,0xFF); // Orange
	Colors[4] = GU_RGBA(255,216,0,0xFF); // Yellow
	Colors[5] = GU_RGBA(182,255,0,0xFF); // Lime
	Colors[6] = GU_RGBA(76,255,0,0xFF); // Green
	Colors[7] = GU_RGBA(148,255,0,0xFF); // Cyan
	Colors[8] = GU_RGBA(0,38,255,0xFF); // Blue
	Colors[9] = GU_RGBA(72,0,255,0xFF); // Violet
	Colors[10] = GU_RGBA(178,0,255,0xFF); // Purple
	Colors[11] = GU_RGBA(255,0,110,0xFF); // Pink
	
	Colors[12] = GU_RGBA(255,255,255,0xFF); // White
	Colors[13] = GU_RGBA(128,128,128,0xFF); // LightGrey
	Colors[14] = GU_RGBA(127,0,0,0xFF); // DarkRed
	Colors[15] = GU_RGBA(127,51,0,0xFF); // DarkOrange
	Colors[16] = GU_RGBA(127,106,0,0xFF); // DarkYellow
	Colors[17] = GU_RGBA(91,127,0,0xFF); // DarkLime
	Colors[18] = GU_RGBA(38,127,0,0xFF); // DarkGreen
	Colors[19] = GU_RGBA(0,74,128,0xFF); // DarkCyan
	Colors[20] = GU_RGBA(0,19,127,0xFF); // DarkBlue
	Colors[21] = GU_RGBA(33,0,127,0xFF); // DarkViolet
	Colors[22] = GU_RGBA(87,0,127,0xFF); // DarkPurple
	Colors[23] = GU_RGBA(127,0,55,0xFF); // DarkPink
	*/
}

void shutdownEngine(void){
	pgeWavShutdown();
	endGraphics();
}

int main(){
	SetupCallbacks();
	initEngine();

	//scePowerSetClockFrequency(333, 333, 166);//еее, разгооон (обычно стоит 222,222,111 без разгона)
	
	Arial = intraFontLoad("Fonts/Arial.pgf",INTRAFONT_STRING_UTF8);
	intraFontSetStyle(Arial, 0.6f, clrs.black, 0, 0);	
	mGlobalState = 1;
	
	while(mGlobalState){
		switch(mGlobalState){
			case 1:
				Run_MainMenu();
			break;
			case 2:
				Run_Paint();
			break;
			default:
				sceKernelExitGame();
				shutdownEngine();
				return 0;
			break;
		}
	}
	
	shutdownEngine();
	sceKernelExitGame();
	return 0;
}