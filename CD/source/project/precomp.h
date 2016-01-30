/****************************************************************/
/*	File:			precomp.h									*/
/*	Description:	ProjSS #define's							*/
/*	Last Modified:	2/8/2003									*/
/*	Author:			Dave Kahler									*/
/****************************************************************/


#ifndef PSS_DEFINES
#define PSS_DEFINES

#define NULL				0

#define GRID_SIZE_X			250			// Game grid max x
#define GRID_SIZE_Y			250			// Game grid max y

#define SCREEN_X_MAX		240
#define SCREEN_X_MAX_HALF	120
#define SCREEN_Y_MAX		160

#define TILE_WIDTH			32
#define TILE_WIDTH_HALF		16
#define TILE_HEIGHT			16
#define TILE_HEIGHT_HALF	8

#define NUM_TILES_WIDE		15
#define NUM_TILES_HIGH		15

#define IN_IWRAM __attribute__ ((section (".iwram")))//functions only 

#define IN_EWRAM __attribute__ ((section (".ewram"))) 

#define FarCall(FUNCTION) \
    ({ \
        typeof (FUNCTION) *volatile _POINTER; \
        \
        _POINTER = &(FUNCTION); \
    }) 



#define assert(cond) (void(0)) 


//attribute0 #defines
#define ROTATION_FLAG		0x100
#define SIZE_DOUBLE		0x200
#define MODE_NORMAL		0x0
#define MODE_TRANSPARENT	0x400
#define MODE_WINDOWED		0x800
#define MOSAIC			0x1000
#define COLOR_16		0x0000
#define COLOR_256		0x2000
#define SQUARE			0x0
#define TALL			0x4000
#define WIDE			0x8000


#define CharMem ((u16*)0x6010000)

//attribute1 #defines
#define ROTDATA(n)		((n)<<9)
#define HORIZONTAL_FLIP		0x1000
#define VERTICAL_FLIP		0x2000
#define SIZE_8			0x0
#define SIZE_16			0x4000
#define SIZE_32			0x8000
#define SIZE_64			0xC000

//atrribute2 #defines
#define PRIORITY(n)	        ((n)<<10)
#define PALETTE(n)		((n)<<12)

#define RADIAN(n) (((float)n)/(float)180*3.141592)





// INTERRUPT DEFINES

#define INT_VBLANK 0x0001
#define INT_HBLANK 0x0002 
#define INT_VCOUNT 0x0004 //you can set the display to generate an interrupt when it reaches a particular line on the screen
#define INT_TIMMER0 0x0008
#define INT_TIMMER1 0x0010
#define INT_TIMMER2 0x0020 
#define INT_TIMMER3 0x0040
#define INT_COMUNICATION 0x0080 //serial communication interupt
#define INT_DMA0 0x0100
#define INT_DMA1 0x0200
#define INT_DMA2 0x0400
#define INT_DMA3 0x0800
#define INT_KEYBOARD 0x1000
#define INT_CART 0x2000 //the cart can actually generate an interupt
#define INT_ALL 0x4000 //this is just a flag we can set to allow the my function to enable or disable all interrupts. Doesn't actually correspond to a bit in REG_IE 


#define  helpbk_WIDTH   186
#define  helpbk_HEIGHT  136


#define PANE_BLANK		0
#define PANE_HELP		1
#define PANE_OBJINFO	2
#define PANE_NPCINFO	3
#define PANE_DISASTER	4




#endif
