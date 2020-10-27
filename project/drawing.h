#ifndef __DRAWING_H__
#define __DRAWING_H__
#ifdef __cplusplus
extern "C" {
#endif

#define POINTER_SIZE 15

void Run_Paint(void);
void Activate_Panel(u8 Panel, u8 Mode);
/*Hidden_drawing_functions*/
void HDF_TC(u8 TCWh,u8 TCHh,u8 TCP,u8 TCA,u8 TCAh,u8 TCC2,u8 TCC1,u8 TCCh);//ToolCircle
void HDF_TCP(u8 TCW,u8 TCH,u8 TCWh,u8 TCHh,u8 TCP,u8 TCA,u8 TCAh,u8 TCC2,u8 TCC1,u8 TCCh);//ToolCircleParts
int HDF_TCC(int x,int y,int dx,int dy,u8 TCWh,u8 TCHh,u8 TCP,u8 TCA,u8 TCAh,u8 TCCh);//ToolCircleCollisions

#ifdef __cplusplus
}
#endif
#endif