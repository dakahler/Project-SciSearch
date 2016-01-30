/****************************************************************/
/*	File:			PSSOAM_alloc.h								*/
/*	Description:	Interface for OAM_alloc class				*/
/*	Last Modified:	2/13/2004									*/
/*	Author:			Dave Kahler									*/
/****************************************************************/


#include "precomp.h"
#include "extern.h"


class PSSOAM_alloc
{

public:

	PSSOAM_alloc();
	
	void addSprite(char* spriteName,int memOffset,int priority,u16 attrib0,u16 attrib1,int width,int height,int x,int y);
	int copyToOAM(const u16 imgData[],int width,int height);

	int getMemOffset();

	int getSprMemOffset(char* spriteName);

	int getDynamicPos();

	void changeSpriteOAM(char* spriteName,u16 imgData[]);

	void changeMemOffset(char* spriteName,int offset);
	void changeAttrib0(char* spriteName,u16 attrib0);
	void changeAttrib1(char* spriteName,u16 attrib1);

	void changePosX(char* spriteName,int newX);
	void changePosY(char* spriteName,int newY);

	int getX(char* spriteName);
	int getY(char* spriteName);

	void changePriority(char* spriteName,int priority);

	void setDynamicPos();

	void resetDynamicSys();


private:


	

	typedef struct spriteList {

		u16 attrib0,attrib1;

		int OAMoffset,priority,width,height,spriteNum,x,y;

		char spriteName[25];

		spriteList *next;

	};

	spriteList* getSpriteNode(char* spriteName);

	spriteList *sprList;

	int currentSpriteNum;

	int dynamicPos;

	int currentMemOffset;
	int currentSprMemOffset;


};
