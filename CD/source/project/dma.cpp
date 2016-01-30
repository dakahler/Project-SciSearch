/************************************\
* DMA.c by dovoto *
\************************************/
//#define DMA_C
#include "gba.h"
#include "dma.h"

//DMA registers
#define REG_DMA0SAD     *(u32*)0x40000B0
#define REG_DMA0SAD_L   *(u16*)0x40000B0
#define REG_DMA0SAD_H   *(u16*)0x40000B2
#define REG_DMA0DAD     *(u32*)0x40000B4
#define REG_DMA0DAD_L   *(u16*)0x40000B4
#define REG_DMA0DAD_H   *(u16*)0x40000B6
#define REG_DMA0CNT     *(u32*)0x40000B8
#define REG_DMA0CNT_L   *(u16*)0x40000B8
#define REG_DMA0CNT_H   *(u16*)0x40000BA
#define REG_DMA1SAD     *(u32*)0x40000BC
#define REG_DMA1SAD_L   *(u16*)0x40000BC
#define REG_DMA1SAD_H   *(u16*)0x40000BE
#define REG_DMA1DAD     *(u32*)0x40000C0
#define REG_DMA1DAD_L   *(u16*)0x40000C0
#define REG_DMA1DAD_H   *(u16*)0x40000C2
#define REG_DMA1CNT     *(u32*)0x40000C4
#define REG_DMA1CNT_L   *(u16*)0x40000C4
#define REG_DMA1CNT_H   *(u16*)0x40000C6
#define REG_DMA2SAD     *(u32*)0x40000C8
#define REG_DMA2SAD_L   *(u16*)0x40000C8
#define REG_DMA2SAD_H   *(u16*)0x40000CA
#define REG_DMA2DAD     *(u32*)0x40000CC
#define REG_DMA2DAD_L   *(u16*)0x40000CC
#define REG_DMA2DAD_H   *(u16*)0x40000CE
#define REG_DMA2CNT     *(u32*)0x40000D0
#define REG_DMA2CNT_L   *(u16*)0x40000D0
#define REG_DMA2CNT_H   *(u16*)0x40000D2
#define REG_DMA3SAD     *(u32*)0x40000D4
#define REG_DMA3SAD_L   *(u16*)0x40000D4
#define REG_DMA3SAD_H   *(u16*)0x40000D6
#define REG_DMA3DAD     *(u32*)0x40000D8
#define REG_DMA3DAD_L   *(u16*)0x40000D8
#define REG_DMA3DAD_H   *(u16*)0x40000DA
#define REG_DMA3CNT     *(u32*)0x40000DC
#define REG_DMA3CNT_L   *(u16*)0x40000DC
#define REG_DMA3CNT_H   *(u16*)0x40000DE

//just an little bit of empty memory
u32 clear = 0;

void DMACopyCH0(void* source, void* dest, u32 WordCount, u32 mode) {
    REG_DMA0SAD = (u32)source;      //Tell the gba our source address
    REG_DMA0DAD = (u32)dest;        //Tell the gba where the data should get copied to
    REG_DMA0CNT = WordCount | mode; //Set the mode
}

void DMACopyCH1(void* source, void* dest, u32 WordCount, u32 mode) {
    REG_DMA1SAD = (u32)source;
    REG_DMA1DAD = (u32)dest;
    REG_DMA1CNT = WordCount | mode;
}

void DMACopyCH2(void* source, void* dest, u32 WordCount, u32 mode) {
    REG_DMA2SAD = (u32)source;
    REG_DMA2DAD = (u32)dest;
    REG_DMA2CNT = WordCount | mode;
}

void DMACopyCH3(void* source, void* dest, u32 WordCount, u32 mode) {
    REG_DMA3SAD = (u32)source;
    REG_DMA3DAD = (u32)dest;
    REG_DMA3CNT = WordCount | mode;
}

//these functions are very handy for cleaning ploted text
//since the source is fixed, the function will always copy 0
void DMAClearMemory16(void* dest, u32 WordCount) {
    REG_DMA0SAD = (u32)&clear; //get the address of "clear" and pass it to the DMA controller as our source
    REG_DMA0DAD = (u32)dest;
    REG_DMA0CNT = WordCount | DMA_ENABLE | DMA_TIMEING_IMMEDIATE | DMA_16 | DMA_SOURCE_FIXED;
}

void DMAClearMemory32(void* dest, u32 WordCount) {
    REG_DMA0SAD = (u32)&clear;
    REG_DMA0DAD = (u32)dest;
    REG_DMA0CNT = WordCount | DMA_ENABLE | DMA_TIMEING_IMMEDIATE | DMA_32 | DMA_SOURCE_FIXED;
}
