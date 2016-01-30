/****************************************************************/
/*  Engine:			PROJECT: SCISEARCH							*/
/*  Version:		1.0											*/
/*	File:			main.cpp									*/
/*	Description:	Main control file							*/
/*	Last Modified:	04/19/2004									*/
/*	Author:			Dave Kahler									*/
/****************************************************************/


// ---------------------------------------------
// Header files
// ---------------------------------------------
#include "gba.h"        // GBA register definitions
#include "gbavars.h"
#include "dispcnt.h"    // REG_DISPCNT register definitions
#include "keypad.h"     // keypress #define's
#include "imagedata.h"	// holds the image information in an array
#include "precomp.h"    // ProjSS #define's
#include "extern.h"


// debug output
void dprints(const char *sz) 
{ 
asm volatile ( 
"mov r2, %0 
ldr r0, =0xc0ded00d 
mov r1, #0 
and r0, r0, r0" : 
/* No output */ : 
"r" (sz) : 
"r0", "r1", "r2"); 
} 


// interrupt handlers (only VBLANK is used)
void VBLANK(void);


void EnableInterrupts(u16 interupts);


// interrupt function table
typedef void (*fp)(void);

fp IntrTable[]  = 
{
	VBLANK,

};



#include <stdio.h>

#include "PSSInit.h"
#include "PSSInterface.h"


//#define DEBUG





// --------------------------------------------------------
// Function:		Flip
// Input:			-
// Output:			-
// Description:		Flips the front & back buffers
// --------------------------------------------------------
void Flip()
{

    if (REG_DISPCNT & BACKBUFFER) {
        REG_DISPCNT &= ~BACKBUFFER;
        VideoBuffer = BackBuffer;
		currentBackBuffer = FrontBuffer;
    }
    else {
        REG_DISPCNT |= BACKBUFFER;
        VideoBuffer = FrontBuffer;
		currentBackBuffer = BackBuffer;
    }
}


int vBlankCounter		 = 0;

int animDelay;

int keyDelay=0;

int colonBlink=0;

PSSDisplay	  *display;


// --------------------------------------------------------
// Function:		Main
// Input:			-
// Output:			-
// Description:		Setup and loop
// --------------------------------------------------------
int main()
{

	EnableInterrupts(INT_VBLANK);

	animDelay = 0;

	//PSSOAM_alloc *spriteMem  = new PSSOAM_alloc();

	PSSInit		  *init		 = new PSSInit();
	display					 = new PSSDisplay();
	
	init->thisInit();

	init->setupSpritesLogo();

	int logoPhase=0;
	int wheelRot=100;
	Point wheelPos;

	wheelPos.x=200;
	wheelPos.y=50;

	// Startup sequence
	while (isStartup) {

		switch (logoPhase) {

			case 0:

				// move and rotate wheel logo sprite
				sprites[1].attribute0 &= 0xFE00;
				sprites[1].attribute1 &= 0xFE00;

				sprites[1].attribute0 |= wheelPos.y;
				sprites[1].attribute1 |= wheelPos.x;

				sprites[1].attribute0 = COLOR_256 | SQUARE | ROTATION_FLAG | wheelPos.y;
				sprites[1].attribute1 = SIZE_64 | wheelPos.x | ROTDATA(0);

				if (animDelay>0) {
					
					wheelPos.x-=1;
					wheelRot-=2;
					animDelay=0;
				}

				

				if (wheelRot<0)
					wheelRot=359;

				s16 pa,pb,pc,pd;

				pa = COS[wheelRot];    //(do my fixed point multiplies and shift back down)
				pb = SIN[wheelRot];
				pc = -SIN[wheelRot];
				pd = COS[wheelRot];

				rotData[0].pa = pa; //put them in my data struct
				rotData[0].pb = pb;
				rotData[0].pc = pc;
				rotData[0].pd = pd;


				if (wheelPos.x<=20) {
					logoPhase++;
					isStartup=false;
				}


				break;

			case 1:



				break;

			case 2:



				break;



		};

		gFlipBuffers=true;

		display->render();

	}

	init->setupSpritesMain();


	PSSSimulation *sim		 = new PSSSimulation(display);
	PSSInterface  *iFace 	 = new PSSInterface(display,sim);

	
	bool colonOn=true;
	

	display->render();

	display->drawGround();
	Flip();
	display->drawGround();

	display->drawObjNPC();


	//////////////////////////////////////
	// MAIN GAME LOOP
	//////////////////////////////////////
	while (true) {

		//////////////////////////////////
		// Redraw display
		//////////////////////////////////
		if (gUpdateDisplay>=1) {

			currentSpriteNum = spriteVarStart;
			
			
			if (gUpdateBackground>0) {
				display->drawGround();
				
				gUpdateBackground--;
			}

			//if (!killDisplay)
			display->drawObjNPC();

			display->drawInterface();
	
			gFlipBuffers=true;
			


		}

		sim->updateTime();
		sim->moveNPCs();


		// control time colons blinking
		if (colonBlink>=60) {
			
			if (colonOn) {

				// turn off
				sprites[colonSprite].attribute2 = 512+8+32+8+8+16+32+64+128+16+16+16+16+8+8+16+16+8+8+8+8+8+16 | PRIORITY(1);
				sprites[colonSprite+1].attribute2 = 512+8+32+8+8+16+32+64+128+16+16+16+16+8+8+16+16+8+8+8+8+8+16 | PRIORITY(1);
				colonOn=false;
			}
			else {

				// turn on
				sprites[colonSprite].attribute2 = 512+8+32+8+8+16+32+64+128+16+16+16+16+8+8+16+16+8+8+8+8+8+16 | PRIORITY(0);
				sprites[colonSprite+1].attribute2 = 512+8+32+8+8+16+32+64+128+16+16+16+16+8+8+16+16+8+8+8+8+8+16 | PRIORITY(0);
				colonOn=true;
			}

			colonBlink=0;

		}


		// control mode wheel drift
		if (modeWheelDrift!=modeWheelAngle) {
			int wheelDiff = modeWheelAngle-modeWheelDrift;

			if (modeWheelAngle==60 && modeWheelDrift>60)
				wheelDiff=modeWheelAngle+(360-modeWheelDrift);
			
			if (modeWheelDrift>360)
				modeWheelDrift-=360;

			if (wheelDiff>20 || wheelDiff<-20)
				modeWheelDrift+=wheelDiff>>4;

			else if (wheelDiff>10 || wheelDiff<-10)
				modeWheelDrift+=wheelDiff>>2;

			else if (wheelDiff>2 || wheelDiff<-2)
				modeWheelDrift+=wheelDiff>>1;
			

			if (wheelDiff>-5 && wheelDiff<5)
				modeWheelDrift=modeWheelAngle;

			rotData[4].pa = (u16)(COS[modeWheelDrift]*.99); //put them in my data struct
			rotData[4].pb = (u16)(SIN[modeWheelDrift]*.99);
			rotData[4].pc = (u16)(-SIN[modeWheelDrift]*.99);
			rotData[4].pd = (u16)(COS[modeWheelDrift]*.99);

		}

		
		display->render();


		//////////////////////////////////////////
		// Check input
		//////////////////////////////////////////
		if (keyDelay>=10) {

			if (!(*KEYS & KEY_A)) {
				iFace->handleInput(KEY_A);
				keyDelay=0;
			}
			if (!(*KEYS & KEY_B)) {
				iFace->handleInput(KEY_B);
				keyDelay=0;
			}

		
			if (!(*KEYS & KEY_L)) {
				iFace->handleInput(KEY_L);
				keyDelay=0;
			}
			if (!(*KEYS & KEY_R)) {
				iFace->handleInput(KEY_R);
				keyDelay=0;
			}
		

			if (!(*KEYS & KEY_SELECT)) {
				iFace->handleInput(KEY_SELECT);
				keyDelay=0;
			}
			if (!(*KEYS & KEY_START)) {
				iFace->handleInput(KEY_START);
				keyDelay=0;
			}

			if (!(*KEYS & KEY_UP)) {
				iFace->handleInput(KEY_UP);
				keyDelay=0;
			}
			if (!(*KEYS & KEY_DOWN)) {
				iFace->handleInput(KEY_DOWN);
				keyDelay=0;
			}
			if (!(*KEYS & KEY_LEFT)) {
				iFace->handleInput(KEY_LEFT);
				keyDelay=0;
			}
			if (!(*KEYS & KEY_RIGHT)) {
				iFace->handleInput(KEY_RIGHT);
				keyDelay=0;
			}
		}

		/////////////////////////////////////////
		// Update simulation
		/////////////////////////////////////////
		sim->updateSimulation();


		
	}

}









void EnableInterrupts(u16 interrupts)
{
	REG_IME = 0;


	if(interrupts == INT_VBLANK)
		REG_DISPSTAT |= 0x8;

	REG_IE |= interrupts;

	REG_IME = 1;

}

void DissableInterupts(u16 interrupts)
{
	REG_IE &= ~interrupts;

	if(interrupts == INT_ALL)
		REG_IME = 0;
}






// VBLANK handler
void VBLANK()
{	
	
	if (!isStartup) {
		vBlankCounter++;

		if (keypressDelay<60)
			keypressDelay++;

		if (vBlankCounter>=5) {
			vBlankCounter=0;
			display->updateTimer();
		}
	}

	// logo animation delay
	animDelay++;

	// key delay
	keyDelay++;

	// colon blink
	colonBlink++;

	// game timer
	if (!isPaused)
		gameTimer++;

	// sim timer
	simTimer++;

	// help keypress delay
	if (helpDelay<20)
		helpDelay++;


	// npc movement delay
	if (npcTimer<20)
		npcTimer++;


	// work area change timer
	if (workAreaTimer<3600)
		workAreaTimer++;

	//display->render();

	
	if (blankMain>0) {
		display->drawInfoPane(PANE_BLANK);
		display->drawGround();
		Flip();
		display->drawInfoPane(PANE_BLANK);
		display->drawGround();
		gUpdateDisplay=1;
		gFlipBuffers=false;
		blankMain--;
	}


	if (gFlipBuffers) {
		Flip();
		//if (blankMain>0) {
		//	display->drawInfoPane(false);
		//	blankMain--;
		//}
	}

	//if (blankMain==0)
	gFlipBuffers=false;

	REG_IF |= INT_VBLANK;
		
}
