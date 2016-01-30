/*******************************************************************/
/*	File:			PSSInit.cpp									   */
/*	Description:	Initialization procedures class implementation */
/*	Last Modified:	04/19/2004									   */
/*	Author:			Dave Kahler								       */
/*******************************************************************/




// ---------------------------------------------
// Headers
// ---------------------------------------------
#include "gba.h"        // GBA register definitions
#include "dispcnt.h"    // REG_DISPCNT register definitions

#include "extern.h"     // various crucial extern vars
#include "precomp.h"    // ProjSS #define's

#include "PSSOAM_alloc.h"
#include "PSSInit.h"    // Init interface



// ---------------------------------------------
// Member Function: PSSInit (constructor)
// Input:			***
// Output:			***
// Description:		***
// ---------------------------------------------
PSSInit::PSSInit()
{

}


/// ---------------------------------------------
/// Member Function: thisInit
/// Input:			***
/// Output:			***
/// Description:	Sets up various parameters the
///					GBA needs to get up and running
/// ---------------------------------------------
void PSSInit::thisInit()
{

    SetMode(MODE_4 | BG2_ENABLE | OBJ_ENABLE | OBJ_MAP_1D); //set mode 4 and enable background 2


	REG_TM3CNT = TIME_FREQUENCY_1024 | TIME_ENABLE;
	REG_TM3D=0;


	REG_BLDMOD = (1<<4) | (1<<10);
	REG_COLEV = (8) + (8<<8);



	for (int i = 0; i < 256; i++)                 //256 entries allowed
		BGPaletteMem[i] = master_Palette[i];	  //load the palette into palette memory

	for (int i=0; i<256; i++)
		OBJPaletteMem[i]= master_Palette[i];

	// init sprites
	for (int i=0; i<128; i++) {
		sprites[i].attribute0 = 160;
		sprites[i].attribute1 = 240;
	}


	for(int i = 0; i < 32; i++) { 

		rotData[i].pa = 0x0100;
		rotData[i].pb = 0x0000;
		rotData[i].pc = 0x0000;
		rotData[i].pd = 0x0100;

	}
}


/// -------------------------------------------------
/// Public Member Function: setupSpritesLogo
/// Input:			***
/// Output:			***
/// Description:	This is setup for the logo animation
///					played at the beginning. I never
///					had time to complete it and it is turned
///					off. Set isStartup to true to see the
///					incomplete logo animation
/// -------------------------------------------------
void PSSInit::setupSpritesLogo()
{

	// setup wheelLogo sprite
	sprites[1].attribute0 = COLOR_256 | SQUARE | ROTATION_FLAG | 100;
	sprites[1].attribute1 = SIZE_64 | 100 | ROTDATA(0);
	sprites[1].attribute2 = 512 | PRIORITY(0);


	// wheelLogo init
	for (int index=0; index < 2048; index++)
	{
		OAMData[index+(512*16)] = logo_dkwheelData[index];
	}




}


/// -------------------------------------------------
/// Public Member Function: setupSpritesMain
/// Input:			***
/// Output:			***
/// Description:	Main game setup. There was a memory
///					manager written to make this more intuitive,
///					but the memory manager itself sucked up
///					too much memory and took a hit on performance.
///					So, memory management is done by HAND. It's
///					a pain, but it works and runs fast
/// -------------------------------------------------
void PSSInit::setupSpritesMain()
{


	int count=0;

	// clock bottom-right


	sprites[count].attribute0 = COLOR_256 | SQUARE | ROTATION_FLAG | 128;
	sprites[count].attribute1 = SIZE_32 | 0 | ROTDATA(0);
	sprites[count++].attribute2 = 512+8+32+8+8+16 | PRIORITY(1);

	clockSpriteNum = 0;






	// time number HOUR
	sprites[count].attribute0 = COLOR_256 | SQUARE | 1;
	sprites[count].attribute1 = SIZE_8 | 110;
	sprites[count++].attribute2 = 512+8+32+8+8+16+32+64+128+16+16+16+16+8+8+16+16 | PRIORITY(0);




	// time number TEN_MINUTE
	sprites[count].attribute0 = COLOR_256 | SQUARE | 1;
	sprites[count].attribute1 = SIZE_8 | 125;
	sprites[count++].attribute2 = 512+8+32+8+8+16+32+64+128+16+16+16+16+8+8+16+16+8 | PRIORITY(0);




	// time number ONE_MINUTE
	sprites[count].attribute0 = COLOR_256 | SQUARE | 1;
	sprites[count].attribute1 = SIZE_8 | 137;
	sprites[count++].attribute2 = 512+8+32+8+8+16+32+64+128+16+16+16+16+8+8+16+16+8+8 | PRIORITY(0);

	

	// time number TEN_SECOND
	sprites[count].attribute0 = COLOR_256 | SQUARE | 1;
	sprites[count].attribute1 = SIZE_8 | 153;
	sprites[count++].attribute2 = 512+8+32+8+8+16+32+64+128+16+16+16+16+8+8+16+16+8+8+8 | PRIORITY(0);

	

	// time number ONE_SECOND
	sprites[count].attribute0 = COLOR_256 | SQUARE | 1;
	sprites[count].attribute1 = SIZE_8 | 165;
	sprites[count++].attribute2 = 512+8+32+8+8+16+32+64+128+16+16+16+16+8+8+16+16+8+8+8+8 | PRIORITY(0);

	



	// time colon
	sprites[count].attribute0 = COLOR_256 | SQUARE | 1;
	sprites[count].attribute1 = SIZE_8 | 118;
	sprites[count++].attribute2 = 512+8+32+8+8+16+32+64+128+16+16+16+16+8+8+16+16+8+8+8+8+8+16 | PRIORITY(0);
	
	colonSprite=count-1;

	// time colon 2
	sprites[count].attribute0 = COLOR_256 | SQUARE | 1;
	sprites[count].attribute1 = SIZE_8 | 146;
	sprites[count++].attribute2 = 512+8+32+8+8+16+32+64+128+16+16+16+16+8+8+16+16+8+8+8+8+8+16 | PRIORITY(0);
	

	// time text
	sprites[count].attribute0 = COLOR_256 | TALL | 1;
	sprites[count].attribute1 = SIZE_8 | 75;
	sprites[count++].attribute2 = 512+8+32+8+8+16+32+64+128+16+16+16+16+8+8+16+16+8+8+8+8+8 | PRIORITY(0);

	// cash text
	sprites[count].attribute0 = COLOR_256 | TALL | 16;
	sprites[count].attribute1 = SIZE_8 | 76;
	sprites[count++].attribute2 = 512+8+32+8+8+16+32+64+128+16+16+16+16+8+8+16+16+8+8+8+8+8+4 | PRIORITY(0);


	// dollar sign text
	sprites[count].attribute0 = COLOR_256 | SQUARE | 16;
	sprites[count].attribute1 = SIZE_8 | 100;
	sprites[count++].attribute2 = 512+8+32+8+8+16+32+64+128+16+16+16+16+8+8+16+16+8+8+8+8+8+4+4 | PRIORITY(0);


	// COMMA
	sprites[count].attribute0 = COLOR_256 | SQUARE | 18;
	sprites[count].attribute1 = SIZE_8 | 126;
	sprites[count++].attribute2 = 512+8+32+8+8+16+32+64+128+16+16+16+16+8+8+16+16+8+8+8+8+8+16+2 | PRIORITY(0);

	// money TEN THOUSANDS
	sprites[count].attribute0 = COLOR_256 | SQUARE | 16;
	sprites[count].attribute1 = SIZE_8 | 110;
	sprites[count++].attribute2 = 512+8+32+8+8+16+32+64+128+16+16+16+16+8+8+16+16+2 | PRIORITY(0);
	
	// money THOUSANDS
	sprites[count].attribute0 = COLOR_256 | SQUARE | 16;
	sprites[count].attribute1 = SIZE_8 | 120;
	sprites[count++].attribute2 = 512+8+32+8+8+16+32+64+128+16+16+16+16+8+8+16+16+8+2 | PRIORITY(0);

	// money HUNDREDS
	sprites[count].attribute0 = COLOR_256 | SQUARE | 16;
	sprites[count].attribute1 = SIZE_8 | 133;
	sprites[count++].attribute2 = 512+8+32+8+8+16+32+64+128+16+16+16+16+8+8+16+16+8+8+2 | PRIORITY(0);

	// money TENS
	sprites[count].attribute0 = COLOR_256 | SQUARE | 16;
	sprites[count].attribute1 = SIZE_8 | 143;
	sprites[count++].attribute2 = 512+8+32+8+8+16+32+64+128+16+16+16+16+8+8+16+16+8+8+8+2 | PRIORITY(0);

	// money ONES
	sprites[count].attribute0 = COLOR_256 | SQUARE | 16;
	sprites[count].attribute1 = SIZE_8 | 153;
	sprites[count++].attribute2 = 512+8+32+8+8+16+32+64+128+16+16+16+16+8+8+16+16+8+8+8+8+2 | PRIORITY(0);




/*
	// help button top-right
	sprites[count].attribute0 = COLOR_256 | TALL | 8;
	sprites[count].attribute1 = SIZE_32 | 200;
	sprites[count++].attribute2 = 512+8+32+8+8+16+32+64+128 | PRIORITY(0);
*/

	
	// obj item
	sprites[count].attribute0 = COLOR_256 | WIDE | 60;
	sprites[count].attribute1 = SIZE_32 | 15;
	sprites[count++].attribute2 = 512+8+32+8+8+16+32+64+128+16+16+16+16+8+8+16+16+8+8+8+8+8+16+16 | PRIORITY(0);

	// npc item
	sprites[count].attribute0 = COLOR_256 | WIDE | 60;
	sprites[count].attribute1 = SIZE_32 | 33;
	sprites[count++].attribute2 = 512+8+32+8+8+16+32+64+128+16+16+16+16+8+8+16+16+8+8+8+8+8+16+16+16 | PRIORITY(0);


	// bottom left (MODE WHEEL) (64x64)
	sprites[count].attribute0 = COLOR_256 | SQUARE | 98 | ROTATION_FLAG;
	sprites[count].attribute1 = SIZE_64 | 510 | ROTDATA(4);
	sprites[count++].attribute2 = 512+8+32+8+8+16+32+64 | PRIORITY(0);
	
	rotData[4].pa = (u16)(COS[modeWheelAngle]*.99); //put them in my data struct
    rotData[4].pb = (u16)(SIN[modeWheelAngle]*.99);
    rotData[4].pc = (u16)(-SIN[modeWheelAngle]*.99);
    rotData[4].pd = (u16)(COS[modeWheelAngle]*.99);
	
	modeWheelSprite = count-1;


	// item select bar 1 (32x32)
	sprites[count].attribute0 = COLOR_256 | SQUARE | 90 | SIZE_DOUBLE | ROTATION_FLAG;
	sprites[count].attribute1 = SIZE_32 | 5 | ROTDATA(5);
	sprites[count++].attribute2 = 512+8 | PRIORITY(1);

	itemSelectSpriteOffset=count-1;

	// item select bar 2 (32x32)
	sprites[count].attribute0 = COLOR_256 | SQUARE | 50 | SIZE_DOUBLE | ROTATION_FLAG;
	sprites[count].attribute1 = SIZE_32 | 5 | ROTDATA(5);
	sprites[count++].attribute2 = 512+8 | PRIORITY(1);


	// main mode select bar 4
	sprites[count].attribute0 = COLOR_256 | SQUARE | 225 | SIZE_DOUBLE | ROTATION_FLAG;
	sprites[count].attribute1 = SIZE_32 | 196 | ROTDATA(6);
	sprites[count++].attribute2 = 512+8 | PRIORITY(0);

	mainSelectors[0] = count-1;

	// main mode select bar 3
	sprites[count].attribute0 = COLOR_256 | SQUARE | 225 | SIZE_DOUBLE | ROTATION_FLAG;
	sprites[count].attribute1 = SIZE_32 | 160 | ROTDATA(6);
	sprites[count++].attribute2 = 512+8 | PRIORITY(0);

	mainSelectors[1] = count-1;

	// main mode select bar 2
	sprites[count].attribute0 = COLOR_256 | SQUARE | 225 | SIZE_DOUBLE | ROTATION_FLAG;
	sprites[count].attribute1 = SIZE_32 | 112 | ROTDATA(6);
	sprites[count++].attribute2 = 512+8 | PRIORITY(0);

	mainSelectors[2] = count-1;

	// main mode select bar 1
	sprites[count].attribute0 = COLOR_256 | SQUARE | 225 | SIZE_DOUBLE | ROTATION_FLAG;
	sprites[count].attribute1 = SIZE_32 | 64 | ROTDATA(6);
	sprites[count++].attribute2 = 512+8 | PRIORITY(0);

	mainSelectors[3] = count-1;

	// main mode select bar 5
	sprites[count].attribute0 = COLOR_256 | SQUARE | 112 | SIZE_DOUBLE | ROTATION_FLAG;
	sprites[count].attribute1 = SIZE_32 | 0 | ROTDATA(1);
	sprites[count++].attribute2 = 512+8 | PRIORITY(0);

	mainSelectors[4] = count-1;








	// left main select fill (32x32)
	sprites[count].attribute0 = COLOR_256 | TALL | 80 | SIZE_DOUBLE | ROTATION_FLAG;
	sprites[count].attribute1 = SIZE_32 | 0 | ROTDATA(1);
	sprites[count++].attribute2 = 512+8 | PRIORITY(0);

	leftSelectFillSprite = count-1;



	// bottom left (INT FILLER) (32x32)
	sprites[count].attribute0 = COLOR_256 | SQUARE | 96 | ROTATION_FLAG | SIZE_DOUBLE;
	sprites[count].attribute1 = SIZE_32 | 0 | ROTDATA(2);
	sprites[count++].attribute2 = 512 | PRIORITY(0);




	// logo (64x32)
	sprites[count].attribute0 = COLOR_256 | TALL | 0;
	sprites[count].attribute1 = SIZE_64 | 0;
	sprites[count++].attribute2 = 512+8+32+8+8+16+32 | PRIORITY(0);
	
	// main mode select bar 6
	sprites[count].attribute0 = COLOR_256 | SQUARE | 32 | SIZE_DOUBLE | ROTATION_FLAG;
	sprites[count].attribute1 = SIZE_32 | 0 | ROTDATA(1);
	sprites[count++].attribute2 = 512+8 | PRIORITY(0);

	mainSelectors[5] = count-1;

	// mid left (32x32)
	sprites[count].attribute0 = COLOR_256 | SQUARE | ROTATION_FLAG | SIZE_DOUBLE | 32;
	sprites[count].attribute1 = SIZE_32 | 0 | ROTDATA(1);
	sprites[count++].attribute2 = 512 | PRIORITY(0);

	rotData[1].pa = 128; //put them in my data struct
    rotData[1].pb = 0;
    rotData[1].pc = 0;
    rotData[1].pd = 128;

	rotData[2].pa = 64; //put them in my data struct
    rotData[2].pb = 0;
    rotData[2].pc = 0;
    rotData[2].pd = 64;

	rotData[3].pa = COS[180]>>1; //put them in my data struct
    rotData[3].pb = SIN[180]>>1;
    rotData[3].pc = -SIN[180]>>1;
    rotData[3].pd = COS[180]>>1;

	rotData[5].pa = (u16)(COS[270]*.6); //put them in my data struct
    rotData[5].pb = (u16)(SIN[270]*.6);
    rotData[5].pc = (u16)(-SIN[270]*.6);
    rotData[5].pd = (u16)(COS[270]*.6);

	rotData[6].pa = 0; //put them in my data struct
    rotData[6].pb = 128;
    rotData[6].pc = 128;
    rotData[6].pd = 0;

	// top left (64x32)
	//sprites[count].attribute0 = COLOR_256 | TALL | 0;
	//sprites[count].attribute1 = SIZE_64 | 0;
	//sprites[count++].attribute2 = 512+64 | PRIORITY(0);

	// top middle-left (64x32)
	sprites[count].attribute0 = COLOR_256 | SQUARE | 226 | SIZE_DOUBLE | ROTATION_FLAG;
	sprites[count].attribute1 = SIZE_32 | 64 | ROTDATA(2);
	sprites[count++].attribute2 = 512+8 | PRIORITY(0);

	// top middle-right (64x32)
	sprites[count].attribute0 = COLOR_256 | SQUARE | 226 | SIZE_DOUBLE | ROTATION_FLAG;
	sprites[count].attribute1 = SIZE_32 | 128 | ROTDATA(2);
	sprites[count++].attribute2 = 512+8 | PRIORITY(0);

	// top right (64x32)
	sprites[count].attribute0 = COLOR_256 | SQUARE | 226 | SIZE_DOUBLE | ROTATION_FLAG;
	sprites[count].attribute1 = SIZE_32 | 192 | ROTDATA(2);
	sprites[count++].attribute2 = 512+8 | PRIORITY(0);






	// set where variable sprites can start
	spriteVarStart = count;
	currentSpriteNum = count;


	///////////////////////////////////////////////////////
	// START copying static sprite graphics into memory
	///////////////////////////////////////////////////////

	int currentMemPos=512*16;



	// Interface background graphic
	for (int index=0; index < 128; index++)
	{
		OAMData[index+currentMemPos] = iFaceDataSelect[384+index];
	}

	currentMemPos+=128;

	// Interface background graphic SELECT
	for (int index=0; index < 512; index++)
	{
		OAMData[index+currentMemPos] = iFaceDataSelect[index];
	}
	
	iFaceSpriteOffset = 128+(512*16);

	currentMemPos+=512+128+128;

	// object wall graphic UPPER
	for (int index=0; index < 256; index++)
	{
		OAMData[index+currentMemPos] = wallData[index];
	}


	currentMemPos+=256;

	// "PSS" spinning circle (no longer shown)
	for (int index=0; index < 512; index++)
	{
		OAMData[index+currentMemPos] = timerCirc[index];
	}


	currentMemPos+=512;
	
	//  logo graphic
	for (int index=0; index < 1024; index++)
	{
		OAMData[index+currentMemPos] = logoData[index];
	}
	
	
	currentMemPos+=1024;

	// mode wheel
	for (int index=0; index < 2048; index++)
	{
		OAMData[index+currentMemPos] = modeWheel[index];
	}

	modeWheelSpriteOffset=currentMemPos;
	
	
	currentMemPos+=2048;

	// help button
	for (int index=0; index < 256; index++)
	{
		OAMData[index+currentMemPos] = helpButtonData[index];
	}

	helpButtonSpriteOffset=currentMemPos;
	

	currentMemPos+=256;

	// object wall graphic LOWER
	for (int index=0; index < 256; index++)
	{
		OAMData[index+currentMemPos] = wallLowerData[index];
	}
	

	currentMemPos+=256;

	// object wall graphic UPPER SELECT
	for (int index=0; index < 256; index++)
	{
		OAMData[index+currentMemPos] = wallSelectData[index];
	}
	

	currentMemPos+=256;

	// object wall graphic LOWER SELECT
	for (int index=0; index < 256; index++)
	{
		OAMData[index+currentMemPos] = wallLowerSelectData[index];
	}


	currentMemPos+=256;




	currentMemPos+=128;


	

	currentMemPos+=128;

	// first selector graphic
	for (int index=0; index < 256; index++)
	{
		OAMData[index+currentMemPos] = objCreate1Data[index];
	}
	

	currentMemPos+=256;

	// second selector graphic
	for (int index=0; index < 256; index++)
	{
		OAMData[index+currentMemPos] = objCreate2Data[index];
	}



	currentMemPos+=256;

	// time hour slot
	for (int index=0; index < 32; index++)
	{
		OAMData[index+currentMemPos] = zeroData[index];
	}

	timeHourSpriteOffset=currentMemPos;


	currentMemPos+=32;

	// money ten thousands slot
	for (int index=0; index < 32; index++)
	{
		OAMData[index+currentMemPos] = zeroData[index];
	}


	currentMemPos+=96;

	// this is the ten-minute-pos time graphic
	for (int index=0; index < 32; index++)
	{
		OAMData[index+currentMemPos] = zeroData[index];
	}

	timeMinTenSpriteOffset=currentMemPos;


	currentMemPos+=32;

	// money one thousands slot
	for (int index=0; index < 32; index++)
	{
		OAMData[index+currentMemPos] = zeroData[index];
	}


	currentMemPos+=96;

	// this is the minute-pos time graphic
	for (int index=0; index < 32; index++)
	{
		OAMData[index+currentMemPos] = zeroData[index];
	}

	timeMinOneSpriteOffset=currentMemPos;


	currentMemPos+=32;

	// money one hundreds slot
	for (int index=0; index < 32; index++)
	{
		OAMData[index+currentMemPos] = zeroData[index];
	}


	currentMemPos+=96;

	// this is the ten-second-pos time graphic
	for (int index=0; index < 32; index++)
	{
		OAMData[index+currentMemPos] = zeroData[index];
	}

	timeSecTenSpriteOffset=currentMemPos;


	currentMemPos+=32;

	// money tens slot
	for (int index=0; index < 32; index++)
	{
		OAMData[index+currentMemPos] = zeroData[index];
	}


	currentMemPos+=96;

	// this is the second-pos time graphic
	for (int index=0; index < 32; index++)
	{
		OAMData[index+currentMemPos] = zeroData[index];
	}
	
	timeSecOneSpriteOffset=currentMemPos;


	//currentMemPos+32;

	// money ones slot
	for (int index=0; index < 32; index++)
	{
		OAMData[index+currentMemPos+32] = zeroData[index];
	}


	currentMemPos+=128;

	// time text graphic
	for (int index=0; index < 64; index++)
	{
		OAMData[index+currentMemPos] = timeData[index];
	}


	currentMemPos+=64;

	// cash text graphic
	for (int index=0; index < 64; index++)
	{
		OAMData[index+currentMemPos] = cashData[index];
	}


	currentMemPos+=64;

	// dollar sign text graphic
	for (int index=0; index < 32; index++)
	{
		OAMData[index+currentMemPos] = dollarData[index];
	}

	

	currentMemPos+=128;

	// colon graphic
	for (int index=0; index < 32; index++)
	{
		OAMData[index+currentMemPos] = colonData[index];
	}

	// comma sign graphic
	for (int index=0; index < 32; index++)
	{
		OAMData[index+currentMemPos+32] = commaData[index];
	}


	currentMemPos+=128;

	// NPC character
	for (int index=0; index < 64; index++)
	{
		OAMData[index+currentMemPos] = npcCharData[index];
	}


	currentMemPos+=64;

	// NPC character SELECT
	for (int index=0; index < 64; index++)
	{
		OAMData[index+currentMemPos] = npcCharSelectData[index];
	}

	currentMemPos+=64;


	// obj item graphic
	for (int index=0; index < 256; index++)
	{
		OAMData[index+currentMemPos] = obj_item_selectData[index];
	}
	
	objItemSpriteOffset=currentMemPos;

	currentMemPos+=256;

	// npc item graphic
	for (int index=0; index < 256; index++)
	{
		OAMData[index+currentMemPos] = npc_itemData[index];
	}
	
	npcItemSpriteOffset=currentMemPos;

	currentMemPos+=256;

}
