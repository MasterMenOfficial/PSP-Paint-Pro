#include "main.h"
#include "drawing.h"

/*
trigonometry explain:
school: sin,cos,...: arcImage
cos(a): cos(-a): cos(-a+PI/2)
0: 0: 90
90: 270: 0
180: 180: 270
270: 90: 180
*/


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct{
	short int X,Y;
	short int SX,SY;
	float Spd;
	u8 Mode, PostMode, PointerBool, Pointer, DrawCursor; 
	Image** Image;
}Cursor;
Image* ToolCircle;
Image** Panel;
Image** ToolIcon;
Image** ToolCircleP;
Image** ToolCircleI;

struct {
	u16 Pen, Brush, Eraser;
	
}DrawSize;

void Run_Paint(void){
	int i,i2;
	Image* Layer1 = newImage(480, 272, 0);//x,y,color
	Image* ColPal = newImage(480, 272, 0);
	Image* PreDraw = newImage(150, 150, 0);//x,y,color
	Image* AlphaBG = loadImage("Textures/Style Packs/Paint Pro Standart/Alpha1.png");
	
	unswizzleImage(PreDraw);//Activate image
	fillRectImage(PreDraw, Cursor.X - DrawSize.Pen/2, Cursor.Y - DrawSize.Pen/2, DrawSize.Pen+1, DrawSize.Pen+1, 0);
	swizzleImage(PreDraw);
	
	u8 TCW = 105; u8 TCH = 105; u8 TCP = 5; u8 TCC2 = 50; u8 TCC1  =25;
	//size,parts,circles radiuse - optional
	
	u8 SpdMod = 0;
	
	// u8 = 255
	// u16 = 
	// u32 = 
	u8 PanelLock = 0;
	
	u8 TCV=0;u8 TCS=0;
	//visible,stay cursor(bool)
	u8 TCCh=(TCC2+TCC1)/2;
	u8 TCA=360/TCP;u8 TCAh=TCA/2;
	u8 TCWh=TCW/2;u8 TCHh=TCH/2;
	
	ToolCircle = newImage(TCW, TCH, 0);
	HDF_TC(TCWh, TCHh, TCP, TCA, TCAh, TCC2, TCC1, TCCh);
	
	ToolCircleP = Array(Image*, TCP);//fragments
	HDF_TCP(TCW, TCH, TCWh, TCHh, TCP, TCA, TCAh, TCC2, TCC1, TCCh);
	
	ToolCircleI = Array(Image*, TCP);//action-icons
	ToolCircleI = TexturePack(RINGMENU_CURSOR_PACK);
	
	Panel = Array(Image*, 5);//action-icons
	Panel = TexturePack(PANEL_PACK);
	
	ToolIcon = Array(Image*, 5);
	ToolIcon = TexturePack(CURSOR_ICON_PACK);
	
	//Cursor = { 240, 138, 240, 138, 0.04f, 0, TexturePack(CURSOR_PACK) };
	
	char** PaintText = Array(char*, 2);
		PaintText[0] = "Color Configuration\0";
		PaintText[1] = "Tool Attribute\0";
	
	DrawSize.Pen = 20;
	DrawSize.Brush = 20;
	DrawSize.Eraser = 20;
	
	Cursor.X = 240;
	Cursor.Y = 138;
	Cursor.SX = 240;
	Cursor.SY = 138;
	Cursor.Spd = 0.06f;
	Cursor.Mode = 0;
	Cursor.PostMode = 0; // For Circle and Rectangle (0 - 1 - 2)
	Cursor.PointerBool = 0; // 0 / 1 (Pointer - ON / OFF)
	Cursor.Pointer = 0; // 0 / 1 (Not Drawing / Drawing)
	Cursor.DrawCursor = 0;
	Cursor.Image = TexturePack(CURSOR_PACK);
	
	u8 bAL = 32;//base analog limit
	u8 State = 0;
	//0-draw, 1-interface
	u16 LockTimer = 0;
	u8 LockTime = 0;
	
	while(mGlobalState==2){
		pgeControlsUpdate();
		//if(pgeControlsPressed(PGE_CTRL_START)){mGlobalState = 1; Run_MainMenu();}
		if(!TCS&&!TCV && (pgeControlsAnalogX()<-bAL || pgeControlsAnalogX()>bAL))Cursor.X += pgeControlsAnalogX()*Cursor.Spd;
		if(!TCS&&!TCV && (pgeControlsAnalogY()<-bAL || pgeControlsAnalogY()>bAL))Cursor.Y += pgeControlsAnalogY()*Cursor.Spd;
		if(!(pgeControlsAnalogY()<-bAL || pgeControlsAnalogY()>bAL || pgeControlsAnalogX()<-bAL || pgeControlsAnalogX()>bAL))TCS=0;
		if(Cursor.X<0)Cursor.X = 0;if(Cursor.X>SCR_WIDTH)Cursor.X = SCR_WIDTH-1;
		if(Cursor.Y<0)Cursor.Y = 0;if(Cursor.Y>SCR_HEIGHT)Cursor.Y = SCR_HEIGHT-1;
		
		startDrawing();
		//clearScreen(clrs.white);
		drawImageEasy(AlphaBG, 0, 0);
		drawImageEasy(Layer1, 0, 0);
    
		switch(State){
			case 0:// Drawing State
				if(pgeControlsHeldAny()||pgeControlsPressedAny())
					unswizzleImage(Layer1);//Activate image
				
				if(pgeControlsHeld(PGE_CTRL_SQUARE)){
					TCV=1;TCS=1;
					if(pgeControlsPressed(PGE_CTRL_SQUARE)){
						Cursor.SX=Cursor.X;//save position
						Cursor.SY=Cursor.Y;
					}
					int dx=0;int dy=0;
					if(pgeControlsAnalogX()<-bAL || pgeControlsAnalogX()>bAL)dx=pgeControlsAnalogX();
					if(pgeControlsAnalogY()<-bAL || pgeControlsAnalogY()>bAL)dy=pgeControlsAnalogY();
				  int choose=HDF_TCC(Cursor.SX, Cursor.SY, dx, dy, TCWh, TCHh, TCP, TCA, TCAh, TCCh);
				  
				  if(pgeControlsReleased(PGE_CTRL_SQUARE)){
					switch(choose){
						case 1: //left-up (Color Panel)
							State = 2;
						break; //left-down (Redo)
						case 2:
							State = 2;
						break;
						case 3: //right-down (Undo)
							State = 2;
						break;
						case 4: //right-up (Parameters Panel)
							State = 3;
						break;
						case 5: //down (Cancel Ring Menu)
							State = 2;
						break;
					}
				  }
				} else {
					TCV = 0;
				}
        
				if(pgeControlsPressed(PGE_CTRL_UP)){
					if (DrawSize.Pen <= 150 && DrawSize.Eraser <= 150) {
						DrawSize.Pen++;
						DrawSize.Eraser++;
					} else {
						DrawSize.Pen = 0;
						DrawSize.Eraser = 0;
					}
				} else if (pgeControlsPressed(PGE_CTRL_DOWN)) {
					if (DrawSize.Pen > 0 && DrawSize.Eraser > 0) {
						DrawSize.Pen--;
						DrawSize.Eraser--;
					} else {
						DrawSize.Pen = 0;
						DrawSize.Eraser = 0;
					}
				}
				
				if(pgeControlsPressed(PGE_CTRL_RIGHT)){
					if (SpdMod < 7) {
						SpdMod++;
					}
				} else if (pgeControlsPressed(PGE_CTRL_LEFT)) {
					if (0 < SpdMod) {
						SpdMod--;
					}
				}
				
				switch (SpdMod) {
					case 1:
						Cursor.Spd = 0.01f;
					break;
					case 2:
						Cursor.Spd = 0.02f;
					break;
					case 3:
						Cursor.Spd = 0.03f;
					break;
					case 4:
						Cursor.Spd = 0.04f;
					break;
					case 5:
						Cursor.Spd = 0.06f;
					break;
					case 6:
						Cursor.Spd = 0.08f;
					break;
				}
				
				if (LockTime == 1) {
					if (LockTimer <= 0) {
						LockTimer--;
						if (Cursor.X >= 0 && Cursor.X < 30) {
							drawImageEasy(Panel[7], 30, 251);
						} else {
							drawImageEasy(Panel[7], 1, 251);
						}
					} else {
						LockTime = 0;
					}
				}
				
				if(pgeControlsPressed(PGE_CTRL_CIRCLE)){
					//changeColorImage(Layer1,getPixelImage(Layer1,Cursor.X,Cursor.Y),clrs.yellow);
					State = 2;
					swizzleImage(Layer1);
				}
				
				if(pgeControlsPressed(PGE_CTRL_TRIANGLE)){
					LockTimer = 50; // Set the Timer for a Locker
					LockTime = 1; // Set LockTimer to be equal to 0
					
					if (PanelLock == 0) {
						PanelLock = 1;
					} else if (PanelLock == 1){
						PanelLock = 0;
					}
					//swapColorImage(Layer1,getPixelImage(Layer1,Cursor.X,Cursor.Y),clrs.black);
				}
				
				if(pgeControlsPressed(PGE_CTRL_SELECT)){
					clearImage(Layer1,0);
				} else if (pgeControlsPressed(PGE_CTRL_START)){
					mGlobalState = 1;
				}
				
				if (Cursor.Mode == 0 || Cursor.Mode == 1) {
					//fillRectImage(Layer1, Cursor.X - DrawSize.Pen/2, Cursor.Y - DrawSize.Pen/2, DrawSize.Pen+1, DrawSize.Pen+1, clrs.black);
					//fillRectImage(Layer1, 1 + Cursor.X - (DrawSize.Pen-1)/2, 1 + Cursor.Y - (DrawSize.Pen-1)/2, DrawSize.Pen+1, DrawSize.Pen+1, clrs.transparent);
					drawImageEasy(PreDraw, Cursor.X - DrawSize.Pen/2, Cursor.Y - DrawSize.Pen/2);
				}
				
				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				///////////////////////////////////////////////////// A C T I O N S /////////////////////////////////////////////////////
				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				
				if(pgeControlsHeld(PGE_CTRL_LTRIGGER)){
					switch(Cursor.Mode) {
						case 0:
							fillRectImage(Layer1, Cursor.X-DrawSize.Pen/2, Cursor.Y-DrawSize.Pen/2, DrawSize.Pen, DrawSize.Pen, clrs.left);
						break;
						case 1:
							fillRectImage(Layer1, Cursor.X-DrawSize.Eraser/2, Cursor.Y-DrawSize.Eraser/2, DrawSize.Eraser, DrawSize.Eraser, clrs.transparent);
						break;
						case 2:
							changeColorImage(Layer1,getPixelImage(Layer1,Cursor.X,Cursor.Y),clrs.left);
						break;
					}
					Cursor.Pointer = 1;
				} else if(pgeControlsHeld(PGE_CTRL_RTRIGGER)){
					switch(Cursor.Mode) {
						case 0:
							fillRectImage(Layer1, Cursor.X-DrawSize.Pen/2, Cursor.Y-DrawSize.Pen/2, DrawSize.Pen, DrawSize.Pen, clrs.right);
						break;
						case 1:
							fillRectImage(Layer1, Cursor.X-DrawSize.Eraser/2, Cursor.Y-DrawSize.Eraser/2, DrawSize.Eraser, DrawSize.Eraser, clrs.transparent);
						break;
						case 2:
							changeColorImage(Layer1,getPixelImage(Layer1,Cursor.X,Cursor.Y),clrs.right);
						break;
					}
					Cursor.Pointer = 1;
				} else {
					Cursor.Pointer = 0;
				}
				/*
					fillCircleImage(Layer1, Cursor.X, Cursor.Y, 5, clrs.blue);
					lineImage(Layer1, Cursor.X-20, Cursor.Y-20, Cursor.X+20, Cursor.Y+20, clrs.green);
					lineImage(Layer1, Cursor.X+20, Cursor.Y-20, Cursor.X-20, Cursor.Y+20, clrs.green);
					strokeRectImage(Layer1, Cursor.X-20, Cursor.Y-20, 41, 41, clrs.cyan);
				*/
				
				if(pgeControlsHeldAny()||pgeControlsPressedAny())
					swizzleImage(Layer1);//for next fast drawing
				
				if (pgeControlsHeld(PGE_CTRL_UP) || pgeControlsHeld(PGE_CTRL_DOWN) )
					swizzleImage(PreDraw);
				
				//if (pgeControlsHeld(PGE_CTRL_UP) || pgeControlsHeld(PGE_CTRL_DOWN)) {
				//	intraFontPrint(Arial, 40, 7, DrawSize.Pen);
				//}
				
				if (PanelLock == 1) {
					if (Cursor.X >= 0 && Cursor.X < 30) {
						Activate_Panel(0, 0);
						Activate_Panel(0, 1);
						Cursor.DrawCursor = 1;
						Cursor.PointerBool = 0;
					} else {
						Cursor.DrawCursor = 0;
					}
					
					if (Cursor.X > 395-4 && Cursor.X < 482) {
						if (Cursor.Y < 137 - 3) {
							Activate_Panel(1, 0); // Init
							Activate_Panel(1, 1); // Render
							Cursor.PointerBool = 0;
						} else if (Cursor.Y > 137 + 3) {
							Activate_Panel(2, 0); // Init
							Activate_Panel(2, 1); // Render
							Cursor.PointerBool = 0;
						} else if (Cursor.Y > 137 - 3 && Cursor.Y < 137 + 3) {
							Activate_Panel(1, 0); // Render
							Activate_Panel(2, 0); // Render
							Cursor.PointerBool = 0;
						}
						Cursor.DrawCursor = 1;
						Cursor.PointerBool = 0;
					} else {
						Cursor.DrawCursor = 0;
					}
				}
				
				
				
			break;
			
			case 1: // Menu
				
				
				
			break;
			case 2: // Color Panel
				
				drawImageEasy(ColPal, 0, 0);
				
				if(pgeControlsHeldAny()||pgeControlsPressedAny())
					unswizzleImage(ColPal);//Activate image
				
				drawImageEasy(Panel[3], 14, 14);
				//drawImageEasy(Panel[8], 50, 70);
				intraFontSetStyle(Arial, 0.8f, clrs.white, 0, 0);
				intraFontPrint(Arial, 180, 35, PaintText[0]);
				drawImageEasy(Panel[9], 280, 21);
				drawImageEasy(Panel[10], 58, 161);
				
				if (pgeControlsHeld(PGE_CTRL_LTRIGGER)) {
					
				}
				if (pgeControlsHeld(PGE_CTRL_RTRIGGER)) {
					
				}
				
				fillRectImage(Panel[9], 248, 120, 35, 35, clrs.left);
				fillRectImage(Panel[9], 308, 120, 35, 35, clrs.right);
				
				if(pgeControlsPressed(PGE_CTRL_CIRCLE))State = 0;
				
				
				if(pgeControlsHeldAny()||pgeControlsPressedAny())
					swizzleImage(ColPal); //for next fast drawing
				
				for(i=0;i<12;i++) {
					if( (Cursor.X > 59 + (i * (29+1) )) && (Cursor.Y > 162) && (Cursor.Y < 162 + 29) ){
						if (pgeControlsPressed(PGE_CTRL_LTRIGGER)) {
							//clrs.left = Colors[i];
							clrs.left = getPixelImage(Panel[8], Cursor.X, Cursor.Y);
						}
					}
				}
				
				for(i=12;i<24;i++) {
					if( (Cursor.X > 59 + (i * (29+1)) ) && (Cursor.Y > 162 + 29 + 1) && (Cursor.Y < 162 + 29 + 1 + 29) ){
						if (pgeControlsPressed(PGE_CTRL_RTRIGGER)) {
							//clrs.right = Colors[i];
							clrs.right = getPixelImage(Panel[8], Cursor.X, Cursor.Y);
						}
					}
				}
				
				
			break;
			case 3: // Parameters Panel
				drawImageEasy(Panel[4], 14, 14);
				intraFontPrint(Arial, 200, 35, PaintText[1]);
				
				if(pgeControlsPressed(PGE_CTRL_CIRCLE))State = 0;
			break;
		} // State Switch-Case End
		
		if(TCV) {
			drawImageEasy(Cursor.Image[10], Cursor.SX, Cursor.SY);
		} else {
			if (Cursor.DrawCursor == 0) {
				switch(Cursor.Mode){
					case 0:
						drawImageEasy(Cursor.Image[0], Cursor.X + 6, Cursor.Y - 20 - 6);
						
						Cursor.PointerBool = 1;
					break;
					case 1:
						drawImageEasy(Cursor.Image[1], Cursor.X + 6, Cursor.Y - 20 - 6);
						Cursor.PointerBool = 1;
					break;
					case 2:
						drawImageEasy(Cursor.Image[2], Cursor.X, Cursor.Y - 20 - 6);
						Cursor.PointerBool = 0;
					break;
					case 3:
					
					break;
					case 4:
					
					break;
				}
			} else if (Cursor.DrawCursor == 1) {
				drawImageEasy(Cursor.Image[10], Cursor.X, Cursor.Y);
			}
		}
		
		if (Cursor.PointerBool == 1) {
			if (Cursor.Pointer == 0) {
				drawImageEasy(Cursor.Image[11], Cursor.X - POINTER_SIZE/2, Cursor.Y - POINTER_SIZE/2);
			} else if (Cursor.Pointer == 1) {
				drawImageEasy(Cursor.Image[12], Cursor.X - POINTER_SIZE/2, Cursor.Y - POINTER_SIZE/2);
			}
		}
		
		endDrawing();
		flipScreen();
	}
	freeImage(AlphaBG);
	freeImage(Layer1);
	freeImage(ToolCircle);
	freeImage(PreDraw);
	FreeImageArray(Cursor.Image, 13);
	FreeImageArray(ToolCircleP, 5);
	FreeImageArray(ToolCircleI, TCP);
	FreeImageArray(Panel, 10);
	FreeImageArray(ToolIcon, 10);
}

void Activate_Panel(u8 aPanel, u8 Mode) {
	
	u8 i = 0;
	
	switch(aPanel) {
		case 0: // Tool Panel
			if (Mode == 0) { // Init
				for(i=0;i<3;i++) {
					if ((Cursor.X >= 3 && Cursor.X <= 24) && (Cursor.Y > 3 + (i * (22+2)) && Cursor.Y < 3 + ( (i+1) * (20+2) )) && pgeControlsPressed(PGE_CTRL_CROSS)) {
						Cursor.Mode = i;
					}
				}
			} else if (Mode == 1) { // Render
				drawImageEasy(Panel[0], 1, 1);
				drawImageEasy(Panel[6], 3, 3 + (Cursor.Mode * (22+2)) );
				for(i=0;i<3;i++) { // i<10
					if (i != Cursor.Mode) {
						drawImageEasy(Panel[5], 3, 3 + (i * (22+2)) );
					}
					drawImageEasy(ToolIcon[i], 4, 4 + (i * (22+2)) );
				}
			}
		break;
		case 1: // Actions Panel
			if (Mode == 0) {
				
			} else if (Mode == 1) {
				drawImageEasy(Panel[1], 394, 2);
			}
		break;
		case 2: // Layers Panel
			if (Mode == 0) {
				
			} else if (Mode == 1) {
				drawImageEasy(Panel[2], 394, 138);
			}
		break;
		default:
		
		break;
	}
	
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void HDF_TC(u8 TCWh,u8 TCHh,u8 TCP,u8 TCA,u8 TCAh,u8 TCC2,u8 TCC1,u8 TCCh){
	u8 i;
	unswizzleImage(ToolCircle);
	strokeCircleImage(ToolCircle, TCWh, TCHh, TCC2, clrs.black);
	strokeCircleImage(ToolCircle, TCWh, TCHh, TCC1, clrs.black);
	
	for(i=0; i<TCP; i++)
		lineImage(ToolCircle, 
			TCWh+cos(-GTR((90+TCA*i)))*(TCC1+1), TCHh+sin(-GTR((90+TCA*i)))*TCC1+1, 
			TCWh+cos(-GTR((90+TCA*i)))*(TCC2+1), TCHh+sin(-GTR((90+TCA*i)))*TCC2+1,
		clrs.black);
	for(i=0; i<TCP; i++)
		changeNearColorImage(ToolCircle, 
			TCWh+cos(-GTR((90+TCA*i+TCAh)))*TCCh, 
			TCHh+sin(-GTR((90+TCA*i+TCAh)))*TCCh, 
		0,GU_RGBA(0,0,0,0xAA));
	swizzleImage(ToolCircle);
}

void HDF_TCP(u8 TCW,u8 TCH,u8 TCWh,u8 TCHh,u8 TCP,u8 TCA,u8 TCAh,u8 TCC2,u8 TCC1,u8 TCCh){
	u8 i;
	for(i=0;i<TCP;i++){
		ToolCircleP[i]=newImage(TCW,TCH,0);
		unswizzleImage(ToolCircleP[i]);
		strokeCircleImage(ToolCircleP[i], TCWh, TCHh, TCC2, clrs.black);
		strokeCircleImage(ToolCircleP[i], TCWh, TCHh, TCC1, clrs.black);
		lineImage(ToolCircleP[i], 
			TCWh+cos(-GTR((90+TCA*i)))*(TCC1+1), TCHh+sin(-GTR((90+TCA*i)))*(TCC1+1), 
			TCWh+cos(-GTR((90+TCA*i)))*(TCC2+1), TCHh+sin(-GTR((90+TCA*i)))*(TCC2+1),
		clrs.black);
		lineImage(ToolCircleP[i], 
			TCWh+cos(-GTR((90+TCA*(i+1))))*(TCC1+1), TCHh+sin(-GTR((90+TCA*(i+1))))*(TCC1+1), 
			TCWh+cos(-GTR((90+TCA*(i+1))))*(TCC2+1), TCHh+sin(-GTR((90+TCA*(i+1))))*(TCC2+1),
		clrs.black);
		changeNearColorImage(ToolCircleP[i], 
			TCWh+cos(-GTR((90+TCA*i+TCAh)))*TCCh, 
			TCHh+sin(-GTR((90+TCA*i+TCAh)))*TCCh, 
		0,clrs.yellow);
		swizzleImage(ToolCircleP[i]);
	}
}

int HDF_TCC(int x,int y,int dx,int dy,u8 TCWh,u8 TCHh,u8 TCP,u8 TCA,u8 TCAh,u8 TCCh){
	int choose=0;u8 i;
	double angle=atan2(dy,dx);
	angle=-angle;fixAngle(angle);
	if(angle<PI/2)angle+=2*PI;
	for(i=0; i<TCP; i++){
		if(angle>=PI/2 && angle<PI/2+GTR(((i+1)*TCA)) ){//collision
			choose=i+1;
			break;
		}
	}
	drawImageEasy(ToolCircle, x-TCWh, y-TCHh);
	if(choose!=0)
		drawImageEasy(ToolCircleP[choose-1], x-TCWh, y-TCHh);
	for(i=0;i<TCP;i++)
		drawImageEasy(ToolCircleI[i],
			x-4+(TCCh-9+(ToolCircleI[i]->width+ToolCircleI[i]->height)/4)*cos(-GTR((90+i*TCA+TCAh))),
			y-5+(TCCh-9+(ToolCircleI[i]->width+ToolCircleI[i]->height)/4)*sin(-GTR((90+i*TCA+TCAh))) );
	return choose;
}