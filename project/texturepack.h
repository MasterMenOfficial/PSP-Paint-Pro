#ifndef __TEXTUREPACK_H__
#define __TEXTUREPACK_H__
#ifdef __cplusplus
extern "C" {
#endif

#define PANEL_PACK 0
#define CURSOR_PACK 1
#define CURSOR_ICON_PACK 2
#define RINGMENU_CURSOR_PACK 3
Image** TexturePack(u8 name);

#ifdef __cplusplus
}
#endif
#endif