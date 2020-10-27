#ifndef __MAIN_H__
#define __MAIN_H__

#include <stdio.h>
#include <string.h>
#include <pspdisplay.h>
#include <pspgu.h>
#include <pspgum.h>
#include <math.h>
#include "libs/intraFont.h"
#include "libs/graphics2d.h"
#include "libs/pge/pgeWav.h"
#include "libs/pge/pgeControls.h"
#include "project/texturepack.h"

#define PI 3.1415926535f
#define GTR(a) a*PI/180.0f
#define RTG(a) a*180.0f/PI
#define Array(t,n) (t*)malloc(sizeof(t)*n)
#define ScaleArray(s,t,n) (t*)realloc(s,sizeof(t)*n)

#define DEV_NAME1 "MasterMen"
#define DEV_NAME2 "Exnonull"
#define VERSION "0.1"
#define DEV_STATE "Pre-Alpha"
#define BUILD_DATE "2020.01.31"

#ifdef __cplusplus
extern "C" {
#endif

struct clrs_t {
	u32 right, left, red, blue, green, black, white, gray ,yellow ,purple ,cyan ,pink , transparent;
};

//extern Colors[24];

double fixAngle(double angle);

void freeImagesArray(Image**, u8);
void initEngine(void);
void shutdownEngine(void);

extern u8 mGlobalState;
extern struct clrs_t clrs;
extern intraFont* Arial;

#ifdef __cplusplus
}
#endif
#endif