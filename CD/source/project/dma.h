//The DMA stuff is stolen from pern-project.com
//I just put the functions into an better fashion

//#ifndef DMA_H
//#define DMA_H

//these defines let you control individual bit in the control register
#define DMA_ENABLE					0x80000000
#define DMA_INTERUPT_ENABLE			0x40000000
#define DMA_TIMEING_IMMEDIATE		0x00000000
#define DMA_TIMEING_VBLANK			0x10000000
#define DMA_TIMEING_HBLANK			0x20000000
#define DMA_TIMEING_SYNC_TO_DISPLAY 0x30000000
#define DMA_16						0x00000000
#define DMA_32						0x04000000
#define DMA_REPEATE					0x02000000
#define DMA_SOURCE_INCREMENT		0x00000000
#define DMA_SOURCE_DECREMENT		0x00800000
#define DMA_SOURCE_FIXED			0x01000000
#define DMA_DEST_INCREMENT			0x00000000
#define DMA_DEST_DECREMENT			0x00200000
#define DMA_DEST_FIXED				0x00400000
#define DMA_DEST_RELOAD				0x00600000

//these defines group common options to save typing. You may notice that I don't have to include the option to increment the source and address register as that is the default.
#define DMA_32NOW					DMA_ENABLE | DMA_TIMEING_IMMEDIATE |DMA_32 
#define DMA_16NOW					DMA_ENABLE | DMA_TIMEING_IMMEDIATE |DMA_16 

//#ifndef DMA_C
 extern void DMACopyCH0(void* source, void* dest, u32 WordCount, u32 mode);
 extern void DMACopyCH1(void* source, void* dest, u32 WordCount, u32 mode);
 extern void DMACopyCH2(void* source, void* dest, u32 WordCount, u32 mode);
 extern void DMACopyCH3(void* source, void* dest, u32 WordCount, u32 mode);

 extern void DMAClearMemory16(void* dest, u32 WordCount);
 extern void DMAClearMemory32(void* dest, u32 WordCount);
//#endif

//#endif //end dma.h


