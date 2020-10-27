#include "main.h"
#include "menu.h"

#define SET_FONT_MENU intraFontSetStyle(Arial, 0.4f, clrs.white, 0, 0) // Тип Задать главный шрифт №1 Main Menu

void Run_MainMenu(void){
	Image* Logo = loadImage("Textures/Style Packs/Paint Pro Standart/Logo.png");
	Image* Button = loadImage("Textures/Style Packs/Paint Pro Standart/Main Menu/Button.png");
	Image* ButtonSel = loadImage("Textures/Style Packs/Paint Pro Standart/Main Menu/ButtonSel.png");
	
	Image* TopicPanel = loadImage("Textures/Style Packs/Paint Pro Standart/Main Menu/TopicPanel.png");
	Image* TopicPage = loadImage("Textures/Style Packs/Paint Pro Standart/Main Menu/TopicPage.png");
	Image* TopicPageSel = loadImage("Textures/Style Packs/Paint Pro Standart/Main Menu/TopicPageSel.png");
	
	SET_FONT_MENU;
	
	u8 Index = 0; // 0..6
	u8 BoxPage = 0; //0/1 (What's New/Recent Files (1) || Start a Project... (0))
	u8 Page = 0; //0/1 (What's New||Recent Files)
	u16 i = 0;
	
	char** textButtons = Array(char*, 7);
			textButtons[0] = "Start a Project\0";
			textButtons[1] = "Load a Project\0";
			textButtons[2] = "Style Settings\0";
			textButtons[3] = "Account Settings\0";
			textButtons[4] = "Editor Settings\0";
			textButtons[5] = "About\0";
			textButtons[6] = "Exit App\0";
	
	char** News = Array(char*, 8);
			News[0] = "Version 0.1 (2020.01.31) (Initial Release):\0";
			News[1] = "  * An Engine (Graphic, Font)\0";
			News[2] = "  * App Structure\0";
			News[3] = "  * Drawing: Pen and Eraser (Square Type),\0";
			News[4] = " Filling Tool";
			News[5] = "  * Different Panels \0";
			News[6] = "  * Speed and Brush Size Change\0";
			News[7] = "  * Main Menu\0";
	
	while(mGlobalState == 1){
		
		// Process
		
		pgeControlsUpdate();
		if (BoxPage == 0) {
			if(pgeControlsPressed(PGE_CTRL_DOWN)) {
				if (Index == 6) {
					Index = 0;
				}
				else {
					Index++;
				}
			}
			if(pgeControlsPressed(PGE_CTRL_UP)) {
				if (Index == 0) {
					Index = 6;
				}
				else {
					Index--;
				}
			}
		}
		else if (BoxPage == 1) {
			if (pgeControlsPressed(PGE_CTRL_LEFT)) { Page = 0; }
			if (pgeControlsPressed(PGE_CTRL_RIGHT)) { Page = 1; }
		}
		
		if (pgeControlsPressed(PGE_CTRL_LTRIGGER)) { BoxPage = 1; }
		if (pgeControlsPressed(PGE_CTRL_RTRIGGER)) { BoxPage = 0; }
		
		if(pgeControlsPressed(PGE_CTRL_CROSS)){
			if (BoxPage == 0) {
				switch (Index) {
					// Start Drawing
					case 0:
						mGlobalState = 2;
					break;
					// Load a Project
					case 1:
						
					break;
					// Style Settings
					case 2:
					
					break;
					// Account Settings
					case 3:
						
					break;
					// Editor Settings
					case 4:
						
					break;
					// About
					case 5:
						Run_About();
					break;
					// Exit App
					case 6:
						mGlobalState = 0;
					break;
				}
			}
		}
		
	////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////
		
	// Render
	
		startDrawing();
		clearScreen(clrs.black);
		
		drawImageEasy(Logo, 303, 15);
		
		for(i = 0; i < 7; i++) {
			drawImageEasy(Button, 303, 49 + (18*i) + (3*i));
			intraFontPrint(Arial, 315, 49-8 + (18*(i+1)) + (3*(i+1)), textButtons[i]);
		}
		
		intraFontPrint(Arial, 337, 215, "Welcome, User");
		
		drawImageEasy(TopicPanel, 11, 30);
		drawImageEasy(TopicPage, 25, 12);
		drawImageEasy(TopicPage, 158, 12);
		
		if (BoxPage == 0) {
			drawImageEasy(ButtonSel, 303, 49 + (18 * Index) + (3 * Index));
		}
		else if (BoxPage == 1) {
			if (Page == 0) {
				drawImageEasy(TopicPageSel, 25, 12);
			}
			else if (Page == 1) {
				drawImageEasy(TopicPageSel, 158, 12);
			}
		}
		
		intraFontPrint(Arial, 45, 26, "What's New?");
		intraFontPrint(Arial, 175, 26, "Recent Files");
		
		if (Page == 0) {
			for(i=0; i<7; i++)
				intraFontPrint(Arial, 22, 45+i*10, News[i]);
		}
		else if (Page == 1) {
			intraFontPrint(Arial, 22, 45, "There's Nothing");
		}
		
		intraFontPrintf(Arial, 14, 268, "Version %s %s (%s Build)", VERSION, DEV_STATE, BUILD_DATE);
		
		endDrawing();
		//sceDisplayWaitVblankStart(); //anti-image-blinking
		flipScreen();
	}
	
	freeImage(Logo);
	freeImage(Button);
	freeImage(ButtonSel);
	freeImage(TopicPanel);
	freeImage(TopicPage);
	freeImage(TopicPageSel);
}

void Run_About(void){
	Image* Logo = loadImage("Textures/Style Packs/Paint Pro Standart/Logo.png");
	
	while(mGlobalState == 1){
		
		// Process
		
		u8 YOffset = 0;
		
		pgeControlsUpdate();
		if(pgeControlsPressed(PGE_CTRL_CIRCLE)) {
			break;
		}
		
	////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////
	
		// Render
		
		startDrawing();
		clearScreen(clrs.black);
		drawImageEasy(Logo, 303, 15);
		intraFontPrintf(Arial, 303, 60, "Version: %s (%s)", VERSION, DEV_STATE);
		intraFontPrintf(Arial, 303, 80, "Date: %s", BUILD_DATE);
		intraFontPrintf(Arial, 303, 100, "By %s and %s", DEV_NAME1, DEV_NAME2);
		intraFontPrint(Arial, 303, 120, "Coded on C using PSPSDK");
		
		intraFontPrint(Arial, 25, 272 - 25, "| Circle |   Back");
		
		endDrawing();
		flipScreen();
	}
	freeImage(Logo);
}
