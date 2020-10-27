#include "main.h"
#include "texturepack.h"

Image** TexturePack(u8 name){
	Image** rez=NULL;
	switch(name){
		case PANEL_PACK:
			rez=ScaleArray(rez,Image*,11);
			rez[0] = loadImage("Textures/Style Packs/Paint Pro Standart/Interface/ToolsPanel.png");
			rez[1] = loadImage("Textures/Style Packs/Paint Pro Standart/Interface/ActionsPanel.png");
			rez[2] = loadImage("Textures/Style Packs/Paint Pro Standart/Interface/LayersPanel.png");
			rez[3] = loadImage("Textures/Style Packs/Paint Pro Standart/Interface/ColorPanel.png");
			rez[4] = loadImage("Textures/Style Packs/Paint Pro Standart/Interface/ParamsPanel.png");
			rez[5] = loadImage("Textures/Style Packs/Paint Pro Standart/Interface/ToolsPanelButton.png");
			rez[6] = loadImage("Textures/Style Packs/Paint Pro Standart/Interface/ToolsPanelButtonSel.png");
			rez[7] = loadImage("Textures/Style Packs/Paint Pro Standart/Interface/Locker.png");
			rez[8] = loadImage("Textures/Style Packs/Paint Pro Standart/Interface/ColorPalette.png");
			rez[9] = loadImage("Textures/Style Packs/Paint Pro Standart/Interface/ColorSlots.png");
			rez[10] = loadImage("Textures/Style Packs/Paint Pro Standart/Interface/ColorPaletteSel.png");
		break;
		case CURSOR_PACK:
			rez=ScaleArray(rez,Image*,13);
			rez[0] = loadImage("Textures/Tool Packs/Paint Pro Standart/Pencil.png");
			rez[1] = loadImage("Textures/Tool Packs/Paint Pro Standart/Eraser.png");
			rez[2] = loadImage("Textures/Tool Packs/Paint Pro Standart/Fill.png");
			rez[3] = loadImage("Textures/Tool Packs/Paint Pro Standart/Line.png");
			rez[4] = loadImage("Textures/Tool Packs/Paint Pro Standart/Rect.png");
			rez[5] = loadImage("Textures/Tool Packs/Paint Pro Standart/Circle.png");
			rez[6] = loadImage("Textures/Tool Packs/Paint Pro Standart/ColorPick.png");
			rez[7] = loadImage("Textures/Tool Packs/Paint Pro Standart/Selection.png");
			rez[8] = loadImage("Textures/Tool Packs/Paint Pro Standart/MoveSelection.png");
			rez[9] = loadImage("Textures/Tool Packs/Paint Pro Standart/Move.png");
			rez[10]= loadImage("Textures/Tool Packs/Paint Pro Standart/Cursor.png");
			rez[11]= loadImage("Textures/Tool Packs/Paint Pro Standart/Pointer.png");
			rez[12]= loadImage("Textures/Tool Packs/Paint Pro Standart/PointerUse.png");
		break;
		case CURSOR_ICON_PACK:
			rez=ScaleArray(rez,Image*,10);
			rez[0] = loadImage("Textures/Tool Packs/Paint Pro Standart/Icon/Pencil.png");
			rez[1] = loadImage("Textures/Tool Packs/Paint Pro Standart/Icon/Eraser.png");
			rez[2] = loadImage("Textures/Tool Packs/Paint Pro Standart/Icon/Fill.png");
			rez[3] = loadImage("Textures/Tool Packs/Paint Pro Standart/Icon/Line.png");
			rez[4] = loadImage("Textures/Tool Packs/Paint Pro Standart/Icon/Rect.png");
			rez[5] = loadImage("Textures/Tool Packs/Paint Pro Standart/Icon/Circle.png");
			rez[6] = loadImage("Textures/Tool Packs/Paint Pro Standart/Icon/ColorPick.png");
			rez[7] = loadImage("Textures/Tool Packs/Paint Pro Standart/Icon/Selection.png");
			rez[8] = loadImage("Textures/Tool Packs/Paint Pro Standart/Icon/MoveSelection.png");
			rez[9] = loadImage("Textures/Tool Packs/Paint Pro Standart/Icon/Move.png");
		break;
		case RINGMENU_CURSOR_PACK:
			rez=ScaleArray(rez,Image*,7);
			rez[0] = loadImage("Textures/Tool Packs/Paint Pro Standart/Ring Menu/RGBIcon.png"); // Param
			rez[1] = loadImage("Textures/Tool Packs/Paint Pro Standart/Ring Menu/UndoIcon.png");
			rez[2] = loadImage("Textures/Tool Packs/Paint Pro Standart/Ring Menu/CrossIcon.png");
			rez[3] = loadImage("Textures/Tool Packs/Paint Pro Standart/Ring Menu/RedoIcon.png");
			rez[4] = loadImage("Textures/Tool Packs/Paint Pro Standart/Ring Menu/PencilIcon.png");
			rez[5] = loadImage("Textures/Tool Packs/Paint Pro Standart/Ring Menu/BrushIcon.png"); // Param
			rez[6] = loadImage("Textures/Tool Packs/Paint Pro Standart/Ring Menu/EraserIcon.png"); // Param
		break;
		default:
			sceKernelExitGame();
			return NULL;
		break;
	}
	return rez;
}