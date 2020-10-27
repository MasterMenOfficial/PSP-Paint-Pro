TARGET = paint_pro
OBJS = libs/graphics2d.o \
libs/pge/pgeMath.o\
libs//pge/pgeControls.o\
libs/pge/pgeWav.o\
project/drawing.o \
project/texturepack.o\
project/menu.o \
main.o

INCDIR =
CFLAGS = -O2 -G0 -Wall -g
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR =
LDFLAGS = 
LIBS = -lpsphprm -lpsppower -lpspaudiocodec -lpspaudiolib -lpspaudio -lpng -lz -lintraFont -lpspgum -lpspgu -lm

PSP_LARGE_MEMORY=1

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = Paint Pro 0.1 (Pre-Alpha)
PSP_EBOOT_ICON = ICON0.png
PSP_EBOOT_PIC1 = PIC1.png

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak

