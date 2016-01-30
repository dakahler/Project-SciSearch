/****************************************************************/
/*	File:			PSSOAM_alloc.cpp							*/
/*	Description:	sprite mem alloc Class Implementation		*/
/*	Last Modified:	2/13/2004									*/
/*	Author:			Dave Kahler									*/
/****************************************************************/



//////////////////////////////////////////////////////////////////
// This is the memory manager I wrote at one point. It is not used
// but is included for historial/reference purposes. The memory
// manager itself took up too much memory and slowed performance.
// Thus, memory is managed by hand instead
//////////////////////////////////////////////////////////////////



// ---------------------------------------------
// Header files
// ---------------------------------------------
#include "gba.h"        // GBA register definitions
#include "dispcnt.h"    // REG_DISPCNT register definitions

#include "extern.h"     // various crucial extern vars
#include "precomp.h"    // ProjSS #define's

#include <string.h>
#include <stdio.h>
#include <stdarg.h>

#include <malloc.h>

#include "PSSOAM_alloc.h" // oam_alloc interface




void dprints(const char *sz);



PSSOAM_alloc::PSSOAM_alloc()
{

	sprList = NULL;

	currentSpriteNum=0;
	currentMemOffset=(512*16);
	currentSprMemOffset=512;

	dynamicPos=0;


}


void PSSOAM_alloc::addSprite(char *spriteName,int memOffset,int priority,u16 attrib0,u16 attrib1,int width,int height,int x,int y)
{

	char tempString[100];
	siprintf(tempString,"Adding sprite %s... ",spriteName);
	dprints(tempString);

	//spriteList *tempSpr = new spriteList;

	spriteList *tempSpr = (spriteList*)malloc(sizeof(spriteList));

	tempSpr->OAMoffset=memOffset;
	tempSpr->attrib0=attrib0;
	tempSpr->attrib1=attrib1;



	tempSpr->width=width;
	tempSpr->height=height;

	tempSpr->x=x;
	tempSpr->y=y;

	tempSpr->priority=priority;

	//tempSpr->spriteName=new char[50];
	strcpy(tempSpr->spriteName,spriteName);

	tempSpr->spriteNum=currentSpriteNum;

	tempSpr->next = NULL;

	siprintf(tempString,"   Here 1");
	dprints(tempString);

	if (sprList==NULL) {
		sprList=tempSpr;
	}
	else {

		spriteList *sprTrav = sprList;

		int i=0;
		while (sprTrav->next!=NULL && sprTrav!=NULL) {

			siprintf(tempString,"   i: %d  :::  spriteNum: %d\n",i,sprTrav->spriteNum);
			dprints(tempString);

			sprTrav=sprTrav->next;
			i++;
		}

		sprTrav->next=tempSpr;

	}

	siprintf(tempString,"   Here 2");
	dprints(tempString);

	// add sprite into OAMmem
	sprites[currentSpriteNum].attribute0 = attrib0;

	//sprites[currentSpriteNum].attribute0 = COLOR_256 | SQUARE | 50;
	//sprites[currentSpriteNum].attribute1 = SIZE_32 | 50;


	sprites[currentSpriteNum].attribute1 = attrib1;
	sprites[currentSpriteNum].attribute2 = memOffset | PRIORITY(priority);

	siprintf(tempString,"   Here 3");
	dprints(tempString);

	currentSpriteNum++;

	siprintf(tempString,"Done.\n");
	dprints(tempString);

}


int PSSOAM_alloc::copyToOAM(const u16 imgData[],int width,int height)
{

	int memLength = (width*height)/2;

	// /16

	// copy into OAM
	for (int i=0; i < memLength; i++)
	{
		OAMData[i+currentMemOffset] = imgData[i];
	}

	currentMemOffset+=memLength;

	currentSprMemOffset+=(memLength/16);

	return(currentSprMemOffset-(memLength/16));

}


void PSSOAM_alloc::changeSpriteOAM(char* spriteName,u16 imgData[])
{


	spriteList* thisSprite = getSpriteNode(spriteName);

	int memLength = (thisSprite->width*thisSprite->height)/2;

	// copy new data into OAM
	for (int i=0;i<memLength;i++) {
		OAMData[i+thisSprite->OAMoffset] = imgData[i];
	}

}


int PSSOAM_alloc::getMemOffset()
{

	return(currentMemOffset);

}


void PSSOAM_alloc::changeAttrib0(char* spriteName,u16 attrib0)
{

	spriteList* thisSprite = getSpriteNode(spriteName);

	thisSprite->attrib0=attrib0;

	sprites[thisSprite->spriteNum].attribute0=attrib0;

}


void PSSOAM_alloc::changeAttrib1(char* spriteName,u16 attrib1)
{

	spriteList* thisSprite = getSpriteNode(spriteName);

	thisSprite->attrib1=attrib1;

	sprites[thisSprite->spriteNum].attribute1=attrib1;

}


void PSSOAM_alloc::changePriority(char* spriteName,int priority)
{

	spriteList* thisSprite = getSpriteNode(spriteName);

	thisSprite->priority=priority;

	sprites[thisSprite->spriteNum].attribute2=thisSprite->OAMoffset | PRIORITY(priority);

}


void PSSOAM_alloc::changeMemOffset(char* spriteName,int offset)
{

	spriteList* thisSprite = getSpriteNode(spriteName);
	
	thisSprite->OAMoffset=offset;

	sprites[thisSprite->spriteNum].attribute2=offset | PRIORITY(thisSprite->priority);

}


int PSSOAM_alloc::getSprMemOffset(char* spriteName)
{

	spriteList* thisSprite = getSpriteNode(spriteName);

	return(thisSprite->OAMoffset);

}


void PSSOAM_alloc::changePosX(char* spriteName,int newX)
{

	spriteList* thisSprite = getSpriteNode(spriteName);

	thisSprite->x=newX;

	sprites[thisSprite->spriteNum].attribute1 &= 0xFE00;
	sprites[thisSprite->spriteNum].attribute1 |= newX;

}


void PSSOAM_alloc::changePosY(char* spriteName,int newY)
{

	spriteList* thisSprite = getSpriteNode(spriteName);

	thisSprite->y=newY;

	sprites[thisSprite->spriteNum].attribute1 &= 0xFE00;
	sprites[thisSprite->spriteNum].attribute1 |= newY;

}


int PSSOAM_alloc::getX(char* spriteName)
{

	spriteList* thisSprite = getSpriteNode(spriteName);

	return(thisSprite->x);

}

int PSSOAM_alloc::getY(char* spriteName)
{

	spriteList* thisSprite = getSpriteNode(spriteName);

	return(thisSprite->y);

}


void PSSOAM_alloc::setDynamicPos()
{

	dynamicPos=currentSpriteNum;

}


int PSSOAM_alloc::getDynamicPos()
{
	return(dynamicPos);
}


void PSSOAM_alloc::resetDynamicSys()
{

	char tempString[100];
	siprintf(tempString,"Called resetDynamicSys()...\n");
	dprints(tempString);

	siprintf(tempString,"Resetting sprite positions (%d)...\n",dynamicPos);
	dprints(tempString);

	// clear dynamic sprite pos's
	for (int i=dynamicPos;i<128;i++) {
		sprites[i].attribute0 &= 0xFE00;
		sprites[i].attribute1 &= 0xFE00;
	}


	siprintf(tempString,"Deleting dynamic sprites...\n");
	dprints(tempString);

	// delete dynamic sprites from list
	spriteList* spriteTrav = sprList;
	spriteList* spriteLast = NULL;

	bool deletedSprite;

	while (spriteTrav!=NULL) {

		deletedSprite=false;

		if (strcmp(spriteTrav->spriteName,"Dynamic1")==0) {

			siprintf(tempString,"   Found dynamic sprite:\n");
			dprints(tempString);

			siprintf(tempString,"      memOffset: %d\n",spriteTrav->OAMoffset);
			dprints(tempString);

			siprintf(tempString,"      spriteNum: %d\n",spriteTrav->spriteNum);
			dprints(tempString);


			// delete this node
			if (spriteLast==NULL) {
				spriteList* spriteTemp=spriteTrav;
				spriteTrav=spriteTrav->next;
				sprList=sprList->next;

				siprintf(tempString,"   UNEXPECTED DELETE");
				dprints(tempString);

				//delete spriteLast->spriteName;
				//delete spriteTemp;
				free(spriteTemp);
			}
			else {
				spriteLast->next=spriteTrav->next;
				//delete spriteTrav->spriteName;
				//delete spriteTrav;
				free(spriteTrav);
				spriteTrav=spriteLast->next;

			}
			deletedSprite=true;
		}

		if (spriteTrav!=NULL && !deletedSprite) {
			spriteLast=spriteTrav;
			spriteTrav=spriteTrav->next;
		}

	}

	currentSpriteNum=dynamicPos;

	siprintf(tempString,"Done.\n");
	dprints(tempString);

}


PSSOAM_alloc::spriteList* PSSOAM_alloc::getSpriteNode(char* spriteName)
{

	spriteList* spriteTrav = sprList;

	while (spriteTrav!=NULL) {

		if (strcmp(spriteName,spriteTrav->spriteName)==0)
			break;

		spriteTrav=spriteTrav->next;

	}

	return(spriteTrav);

}










