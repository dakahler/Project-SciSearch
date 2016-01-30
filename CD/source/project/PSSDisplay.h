/****************************************************************/
/*	File:			PSSDisplay.h								*/
/*	Description:	Interface for Display class					*/
/*	Last Modified:	04/19/2004									*/
/*	Author:			Dave Kahler									*/
/****************************************************************/


#include "precomp.h"
#include "extern.h"


class PSSDisplay
{

public:

	PSSDisplay();
	void drawGround();
	void drawObjNPC();
	void drawInterface();
	void drawDebug();
	void render();
	void updateTimer();

	void changeScrollOffset(double x,double y);
	void drawInfoPane(int paneType);

	Point getDisplayOffset();

	int addObject();
	void deleteObject();

	void addNPC();
	void deleteNPC();

	void changeVisibleObj(int direction);
	void changeVisibleNPC(int direction);

	void changeNPCWorkArea(npcData *npcTrav);
	void changeNPCLocation(int x,int y);

	Point getNPCLocation();

	objData* isObstructed(int x,int y,bool isYWall);




private:


	// struct to hold sorted obj/npc list
	struct objNPCList {
		void* pObjNPC;
		int isObj;
		bool isSelected;
		objNPCList *next;
	};


	

	
	typedef struct wallList {
		Point location;
		int flip;
		int isObj;

		Point location2D;

		double moveOffsetX,moveOffsetY;

		int pOffsetX,pOffsetY;

		int wallType;

		int isYWall;
		
		objData *object;
		npcData *npc;
	};
	
	
	
	
	
	

	// instance variables
	Point *iDisplayOffset;
	PointD *iScrollOffset;

	Point *iSquareOffset;


	void plotPixel(u8 x,u8 y, u8 c);
	void drawTiles(u8 xOffset,u8 yOffset);

	void resetDynamicSprites();
	void deleteVisibleObjNPCList();
	objNPCList* addVisibleObj(objData *tempObj,objNPCList *tempList);
	objNPCList* addVisibleNPC(npcData *tempNPC,objNPCList *tempList);
	void sortVisibleObjNPC(objNPCList *tempList);
	int finalizeSprites(objNPCList *tempList);

	void drawSoftSprite(const u16* imageData,int width,int height,int offsetX,int offsetY);

	const u16* getNumGraphic(int num);


	objNPCList* rebuildWallList(objData *tempObj,objNPCList *tempList);


	// 0=main
	int helpLevel;

	int numObjects;

	int groundFlip;

	//PSSOAM_alloc *spriteMem;

	objNPCList *tempList;

	objNPCList *fullWallList;



};
