/****************************************************************/
/*	File:			PSSDisplay.cpp								*/
/*	Description:	Display Module Class Implementation			*/
/*	Last Modified:	04/19/2004									*/
/*	Author:			Dave Kahler									*/
/****************************************************************/


// ---------------------------------------------
// Header files
// ---------------------------------------------
#include "gba.h"        // GBA register definitions
#include "dispcnt.h"    // REG_DISPCNT register definitions

#include "extern.h"     // various crucial extern vars
#include "precomp.h"    // ProjSS #define's

#include "PSSDisplay.h" // display interface

#include <stdio.h>
#include <stdlib.h>



void dprints(const char *sz);



/// -------------------------------------------------
/// Public Member Function: PSSDisplay (constructor)
/// Input:			***
/// Output:			***
/// Description:	Sets up various display elements, 
///					creates some initial objects
/// -------------------------------------------------
PSSDisplay::PSSDisplay()
{

	iDisplayOffset = new Point;
	iScrollOffset  = new PointD;
	iSquareOffset = new Point;

	iDisplayOffset->x	= GRID_SIZE_X/2;
	iDisplayOffset->y	= GRID_SIZE_Y/2;

	iSquareOffset->x = iDisplayOffset->x;
	iSquareOffset->y = iDisplayOffset->y;

	iScrollOffset->x	= 0.0;
	iScrollOffset->y	= 0.0;

	helpLevel=0;

	firstSelector.x=1;
	firstSelector.y=-2;


	objList		= NULL;
	npcList		= NULL;
	visibleObjs	= NULL;

	fullWallList = NULL;



	/////////////////////////////////////////////////////////////////////////////
	// SETUP INIT OBJECTS
	/////////////////////////////////////////////////////////////////////////////
	

	firstSelector.x=0;
	firstSelector.y=0;

	secondSelector.x=3;
	secondSelector.y=3;

	addObject();
	

	
	firstSelector.x=5;
	firstSelector.y=5;

	secondSelector.x=9;
	secondSelector.y=9;

	addObject();

	
	firstSelector.x=-2;
	firstSelector.y=-6;

	secondSelector.x=1;
	secondSelector.y=-3;

	addObject();

	

	firstSelector.x=5;
	firstSelector.y=-8;

	secondSelector.x=8;
	secondSelector.y=-5;

	addObject();



	firstSelector.x=0;
	firstSelector.y=0;
	
	secondSelector.x=3;
	secondSelector.y=3;
	
	

	npcList = NULL;



}


/// -------------------------------------------------
/// Public Member Function: getDisplayOffset
/// Input:			***
/// Output:			Points representing current offset
/// Description:	Returns display offset
/// -------------------------------------------------
Point PSSDisplay::getDisplayOffset()
{

	Point temp;

	temp.x=iDisplayOffset->x;
	temp.y=iDisplayOffset->y;

	return(temp);
}


/// -------------------------------------------------
/// Public Member Function: changeScrollOffset
/// Input:			Incremental change to display offset
/// Output:			***
/// Description:	Shifts (scrolls) the display offset
///					one unit
/// -------------------------------------------------
void PSSDisplay::changeScrollOffset(double x,double y)
{
	
	if ((int)x==1 && (int)y==1 && iSquareOffset->x<300) {
		iSquareOffset->x++;
	}
	else if (iSquareOffset->x>=300) {
		return;
	}


	if ((int)x==-1 && (int)y==-1 && iSquareOffset->x>0) {
		iSquareOffset->x--;
	}
	else if (iSquareOffset->x<=0) {
		return;
	}


	if ((int)x==-1 && (int)y==1 && iSquareOffset->y<300) {
		iSquareOffset->y++;
	}
	else if (iSquareOffset->y>=300) {
		return;
	}

	
	if ((int)x==1 && (int)y==-1 && iSquareOffset->y>0) {
		iSquareOffset->y--;
	}
	else if (iSquareOffset->y<=0) {
		return;
	}

	
	iDisplayOffset->x+=(int)x;
	iDisplayOffset->y+=(int)y;

}


/// -------------------------------------------------
/// Public Member Function: addObject
/// Input:			***
/// Output:			Size of object
/// Description:	Add a new object into the world. The object
///					is placed at the current selector locations.
///					This also induces a rebuild of all object
///					walls for use by the path finder obstruction
///					function
/// -------------------------------------------------
int PSSDisplay::addObject()
{
	
	// add object, reset


	// max 80 objects constraint
	if (numObjects>=80)
		return(0);
	
	char tempString[100];

	int size = (secondSelector.x-firstSelector.x)+1;
	int locationX = getDisplayOffset().x+6+firstSelector.x-firstSelector.y;
	int locationY = getDisplayOffset().y+2+firstSelector.y+firstSelector.x;

	int x2D = iSquareOffset->x+firstSelector.x;//+1;
	int y2D = iSquareOffset->y+firstSelector.y;//-2;


	siprintf(tempString,"Trying to add object at: (%d, %d)\n",x2D,y2D);
	dprints(tempString);

	// check against other objects, make sure there are no overlaps
	objData *objTrav = objList;
	while (objTrav!=NULL) {



		// loop around candidate object square, test all tiles

		// test top and bottom walls
		// this also tests a middle row to prevent fully embedding a smaller
		// room within a larger one
		for (int x=0;x<=size;x++) {

			for (int i=0;i<3;i++) {

				int y=0;

				switch(i) {
					case 0:
						y=0;
						break;
					case 1:
						y=size/2;
						break;
					case 2:
						y=size;
						break;
				};

				// case 1: overlapping bottom
				if ( ((x2D+x)-objTrav->location2D.x) <= objTrav->size.x			&&
					 ((x2D+x)-objTrav->location2D.x) >= 0		&&

					 ((y2D+y)-objTrav->location2D.y) <= objTrav->size.x		&&
					 ((y2D+y)-objTrav->location2D.y) >= 0 )						{

					 siprintf(tempString,"    Bad position! (1)\n\n");
					 dprints(tempString);

					 return(0);

				}
			}
		}

		// test left and right walls
		for (int y=0;y<=size;y++) {
			
			for (int x=0;x<=size;x+=size) {
				
				// case 1: overlapping bottom
				if ( ((x2D+x)-objTrav->location2D.x) <= objTrav->size.x			&&
					((x2D+x)-objTrav->location2D.x) >= 0		&&
					
					((y2D+y)-objTrav->location2D.y) <= objTrav->size.x		&&
					((y2D+y)-objTrav->location2D.y) >= 0 )						{
					
					siprintf(tempString,"    Bad position! (2)\n\n");
					dprints(tempString);
					
					return(0);
					
				}
			}
		}


		objTrav = objTrav->next;

	}


	objData *tempObj = new objData;
	
	tempObj->location.x = locationX;
	tempObj->location.y = locationY;

	tempObj->location2D.x = x2D;
	tempObj->location2D.y = y2D;

	siprintf(tempString,"Added object at: (%d, %d)\n",x2D,y2D);
	dprints(tempString);
	
	tempObj->size.x = size;
	tempObj->size.y = size;

	tempObj->condition = 1.0;
	tempObj->profit = tempObj->size.x*100;
	tempObj->risk = 1.0-(1.0/(double)(tempObj->size.x-1));

	tempObj->isSelected = false;
	
	tempObj->next = objList;
	objList = tempObj;

	numObjects++;



	////////////////////////////////////////////////
	// Delete fullWallList
	////////////////////////////////////////////////
	objNPCList *tempListDel = fullWallList;
	while (tempListDel!=NULL) {
		
		tempListDel=tempListDel->next;
		delete (wallList*)(fullWallList->pObjNPC);
		delete fullWallList;
		fullWallList = tempListDel;
	}
	
	fullWallList = NULL;


	fullWallList = rebuildWallList(objList,fullWallList);

	return(tempObj->size.x);


}


/// -------------------------------------------------
/// Public Member Function: addNPC
/// Input:			***
/// Output:			***
/// Description:	Adds a new NPC at the current firstSelector
///					location. Induces path finder if NPC is
///					determined to be outside of an object
/// -------------------------------------------------
void PSSDisplay::addNPC()
{

	// add npc
	

	// max 20 NPCs constraint
	if (numNPCs>=20)
		return;

	int locationX = iSquareOffset->x+firstSelector.x;
	int locationY = iSquareOffset->y+firstSelector.y;


	char tempString[100];
	siprintf(tempString,"TESTING: (%d, %d)\n",locationX,locationY);
	dprints(tempString);

	// check to see if NPC is within a room
	objData *objTrav = objList;
	while (objTrav!=NULL) {

		char tempString[100];
		siprintf(tempString,"  AGAINST: (%d, %d)\n",objTrav->location2D.x,objTrav->location2D.y);
		dprints(tempString);

		// check bounds
		if ( (objTrav->location2D.x<=locationX) &&
			 (objTrav->location2D.x+objTrav->size.x>locationX) &&

			 (objTrav->location2D.y<=locationY) &&
			 (objTrav->location2D.y+objTrav->size.x>locationY) ) {

			break;

		}

		objTrav = objTrav->next;

	}





	npcData *tempNPC = new npcData;
	
	tempNPC->location.x = getDisplayOffset().x+6+firstSelector.x-firstSelector.y;
	tempNPC->location.y = getDisplayOffset().y+2+firstSelector.y+firstSelector.x;

	tempNPC->location2D.x = locationX;
	tempNPC->location2D.y = locationY;
	
	tempNPC->risk=100;
	tempNPC->salary=100;

	tempNPC->negotiatingX = false;

	bool isAreaCurrent;

	if (objTrav!=NULL) {

		// make NPC properly align itself in the room
		tempNPC->atWorkArea = false;
		tempNPC->foundObject=-3;

		workArea *tempArea = new workArea;
		tempArea->object = objTrav;
		tempArea->isCurrentArea=true;

		char tempString[100];
		siprintf(tempString,"NPC in work area\n");
		dprints(tempString);

		isAreaCurrent = true;
		
		tempArea->next = NULL;
		tempNPC->workList = tempArea;

		
	}
	else {
		tempNPC->atWorkArea = false;
		tempNPC->foundObject=0;

		char tempString[100];
		siprintf(tempString,"NPC NOT in work area\n");
		dprints(tempString);

		isAreaCurrent = false;

		tempNPC->workList = NULL;
	}

	tempNPC->isSelected = false;

	tempNPC->isMoving = false;

	tempNPC->percentLeft.x = 0.0;
	tempNPC->percentLeft.y = 0.0;

	tempNPC->currInRoom=0;

	tempNPC->totalInRoom=1;

	tempNPC->oldTile.x = 0;
	tempNPC->oldTile.y = 0;

	objData *objTemp = objList;




	// set up work area(s) for this NPC


	while (objTemp!=NULL) {

		if (objTemp==objTrav) {
			objTemp=objTemp->next;
			continue;
		}


		workArea *tempArea = new workArea;

		tempArea->object = objTemp;

		if (!isAreaCurrent) {
			tempArea->isCurrentArea=true;
			isAreaCurrent=true;
		}
		else {
			tempArea->isCurrentArea=false;
		}

		if (tempNPC->workList == NULL) {
			tempArea->next = NULL;
			tempNPC->workList = tempArea;
		}
		else {
			tempArea->next = tempNPC->workList;
			tempNPC->workList = tempArea;
		}


		objTemp=objTemp->next;
	}

	tempNPC->next = npcList;
	npcList = tempNPC;

	numNPCs++;

}


/// -------------------------------------------------
/// Public Member Function: isObstructed
/// Input:			Point to test for wall, and whether
///					it wants to test x or y walls
/// Output:			Object that is causing obstruction,
///					or NULL if no obstruction
/// Description:	This is called by the path finder.
///					It determines if a wall is blocking
///					an NPC.
/// -------------------------------------------------
/// take test point, return if wall is blocking
objData* PSSDisplay::isObstructed(int x,int y,bool isYWall)
{

	// run through wall list
	objNPCList *listTrav = fullWallList;
	while (listTrav!=NULL) {

		//if (!((wallList*)(listTrav->pObjNPC))->isYWall==isYWall) {
			

		if (((wallList*)(listTrav->pObjNPC))->isObj &&
			((wallList*)(listTrav->pObjNPC))->location.x == x &&
			((wallList*)(listTrav->pObjNPC))->location.y == y &&
			((wallList*)(listTrav->pObjNPC))->isYWall==isYWall) {

			return(((wallList*)(listTrav->pObjNPC))->object);

		}

		listTrav = listTrav->next;

	}

	return(NULL);

}


/// -------------------------------------------------
/// Public Member Function: changeNPCWorkArea
/// Input:			***
/// Output:			***
/// Description:	This induces a work area change
///					for ALL NPCs if npcTrav is NULL,
///					otherwise for just one NPC. 
///					A work area change causes the
///					path finder to go into action, as well
/// -------------------------------------------------
void PSSDisplay::changeNPCWorkArea(npcData *npcTrav)
{

	bool isSingleNPC=true;

	if (npcTrav==NULL) {
		npcTrav = npcList;
		isSingleNPC=false;
	}

	while (npcTrav!=NULL) {

		workArea *tempWorkList = npcTrav->workList;
		while(tempWorkList!=NULL) {

			if (tempWorkList->isCurrentArea) {
				tempWorkList->isCurrentArea=false;
				npcTrav->atWorkArea = false;
				npcTrav->foundObject = -1;
				npcTrav->isMoving=false;
				npcTrav->negotiatingX=false;

				if (tempWorkList->next!=NULL) {
					tempWorkList->next->isCurrentArea=true;
				}
				else {
					npcTrav->workList->isCurrentArea=true;
				}

				break;
			}

			tempWorkList = tempWorkList->next;

		}

		if (isSingleNPC) {
			npcTrav->foundObject = 0;
			break;
		}

		npcTrav = npcTrav->next;

	}

}


/// -------------------------------------------------
/// Public Member Function: changeNPCLocation
/// Input:			New location (x,y)
/// Output:			***
/// Description:	This changes the location of the currently
///					selected NPC. I don't think this is used anymore
/// -------------------------------------------------
void PSSDisplay::changeNPCLocation(int x,int y)
{

	npcData *tempList = npcList;

	while (tempList!=NULL) {

		if (tempList->isSelected) {

			tempList->location.x = x;
			tempList->location.y = y;

			break;
		}

		tempList = tempList->next;

	}

}


/// -------------------------------------------------
/// Public Member Function: deleteObject
/// Input:			***
/// Output:			***
/// Description:	This deletes the currently selected
///					object. Also rebuilds full wall list
///					and deletes this object out of any
///					NPC work areas
/// -------------------------------------------------
void PSSDisplay::deleteObject()
{

	objData *objTrav = objList;
	objData *objLast = NULL;
	
	// always need at least one obj
	if (numObjects==1)
		return;

	// find selected object
	while (objTrav!=NULL) {
		
		if (objTrav->isSelected)
			break;
		
		objLast=objTrav;
		objTrav=objTrav->next;
		
	}
	

	// delete any NPC workArea node referencing this object
	npcData *tempNPC = npcList;
	while (tempNPC!=NULL) {

		// run through this NPC's workareas
		workArea *workTrav = tempNPC->workList;
		workArea *workLast = NULL;
		while (workTrav!=NULL) {

			// found one, delete it
			if (workTrav->object==objTrav) {

				// if NPC is HERE, must induce a workArea change!
				if (workTrav->isCurrentArea) {

					changeNPCWorkArea(tempNPC);
				}

				// delete this workArea
				if (workLast==NULL) {
					tempNPC->workList = tempNPC->workList->next;
					delete workTrav;
				}
				else {
					workLast->next = workTrav->next;
					delete workTrav;
				}

				break;
			}

			workLast=workTrav;
			workTrav=workTrav->next;
		}

		tempNPC=tempNPC->next;

	}


	// delete object
	if (objTrav!=NULL) {
		
		if (objLast!=NULL) {
			objLast->next=objTrav->next;
			delete objTrav;
		}
		else {
			objTrav=objList;
			objList=objList->next;
			
			delete objTrav;
			
		}
		
		gUpdateDisplay++;
	}
	
	/*
	objTrav=objList;
	int i=0;
	while (true) {
		if (objTrav!=NULL)
			i++;
		else
			break;
		
		objTrav=objTrav->next;
	}
	*/

	numObjects--;

}


/// -------------------------------------------------
/// Public Member Function: changeVisibleObj
/// Input:			Direction (forward or backward
///					in the linked list)
/// Output:			***
/// Description:	Changes the currently selected obj,
///					scrolling through the objs currently
///					on screen
/// -------------------------------------------------
void PSSDisplay::changeVisibleObj(int direction)
{

	if (direction==0) {

		objVisible *visibleTrav = visibleObjs;
		
		// set visibleLast to end of list
		objVisible *visibleLast = visibleObjs;
		if (visibleLast!=NULL) {
			while (visibleLast->next!=NULL)
				visibleLast=visibleLast->next;
		}
		
		// cycle through visibleObjs
		while (visibleTrav!=NULL) {
			
			if (!visibleTrav->isObj) {
				visibleTrav=visibleTrav->next;
				continue;
			}

			if (visibleTrav->object!=NULL) {
				if (visibleTrav->object->isSelected) {
					
					// found the selected obj, change to PREVIOUS obj
					visibleTrav->object->isSelected=false;
					visibleLast->object->isSelected=true;
					
					break;
				}
			}
			
			visibleLast=visibleTrav;
			visibleTrav=visibleTrav->next;	
			
		}

	}
	
	else {

		objVisible *visibleTrav = visibleObjs;
		
		// cycle through visibleObjs
		while (visibleTrav!=NULL) {
			
			if (!visibleTrav->isObj) {
				visibleTrav=visibleTrav->next;
				continue;
			}

			if (visibleTrav->object!=NULL) {
				if (visibleTrav->object->isSelected) {
					
					// found the selected obj, change to NEXT obj
					visibleTrav->object->isSelected=false;
					
					// if at end of list, set first visibleObj to selected
					if (visibleTrav->next!=NULL)
						visibleTrav->next->object->isSelected=true;
					else
						visibleObjs->object->isSelected=true;
					
					break;
				}
			}
			
			visibleTrav=visibleTrav->next;
			
		}

	}

}


/// -------------------------------------------------
/// Public Member Function: changeVisibleNPC
/// Input:			Direction (left or right in
///					linked list)
/// Output:			***
/// Description:	Same as the obj one, only for NPCs
/// -------------------------------------------------
void PSSDisplay::changeVisibleNPC(int direction)
{

	if (direction==0) {
		
		objVisible *visibleTrav = visibleObjs;
		
		// set visibleLast to end of list
		objVisible *visibleLast = visibleObjs,*visibleTemp = visibleObjs;
		if (visibleLast!=NULL) {
			while (visibleLast!=NULL) {
				
				if (!visibleLast->isObj)
					visibleTemp=visibleLast;

				visibleLast=visibleLast->next;
			}
			visibleLast=visibleTemp;
		}
		
		// cycle through visibleObjs
		while (visibleTrav!=NULL) {
			
			if (visibleTrav->isObj) {
				visibleTrav=visibleTrav->next;
				continue;
			}
			
			if (visibleTrav->npc!=NULL) {
				if (visibleTrav->npc->isSelected) {
					
					// found the selected obj, change to PREVIOUS obj
					visibleTrav->npc->isSelected=false;
					visibleLast->npc->isSelected=true;
					
					break;
				}
			}
			
			visibleLast=visibleTrav;
			visibleTrav=visibleTrav->next;	
			
		}
		
	}
	
	else {
		
		objVisible *visibleTrav = visibleObjs;
		
		// cycle through visibleObjs
		while (visibleTrav!=NULL) {
			
			if (visibleTrav->isObj) {
				visibleTrav=visibleTrav->next;
				continue;
			}
			
			if (visibleTrav->npc!=NULL) {
				if (visibleTrav->npc->isSelected) {
					
					// found the selected obj, change to NEXT obj
					visibleTrav->npc->isSelected=false;

					// fast forward to next npc
					visibleTrav=visibleTrav->next;
					bool isWrappedAround=false;
					while (true) {
						if (!visibleTrav->isObj)
							break;

						visibleTrav=visibleTrav->next;

						if (visibleTrav==NULL) {
							visibleTrav=visibleObjs;
							if (isWrappedAround)
								return;
							isWrappedAround=true;
						}
					}

					visibleTrav->npc->isSelected=true;

					
					break;
				}
			}
			
			visibleTrav=visibleTrav->next;
			
		}
		
	}

}


/// -------------------------------------------------
/// Public Member Function: deleteNPC
/// Input:			***
/// Output:			***
/// Description:	Deletes the currently selected NPC
/// -------------------------------------------------
void PSSDisplay::deleteNPC()
{

	npcData *npcTrav = npcList;
	npcData *npcLast = NULL;
	
	// find selected NPC
	while (npcTrav!=NULL) {
		
		if (npcTrav->isSelected)
			break;
		
		npcLast=npcTrav;
		npcTrav=npcTrav->next;
		
	}
	
	
	// delete this NPC's workarea pointers
	workArea *workTrav = npcTrav->workList;
	while (workTrav!=NULL) {

		workArea *tempWork = workTrav;
		workTrav = workTrav->next;
		delete tempWork;
	}


	// delete this NPC
	if (npcTrav!=NULL) {
		
		if (npcLast!=NULL) {
			npcLast->next=npcTrav->next;
			delete npcTrav;
		}
		else {
			npcTrav=npcList;
			npcList=npcList->next;
			
			delete npcTrav;
			
		}
		
		gUpdateDisplay++;
	}
	

	/*
	npcTrav=npcList;
	int i=0;
	while (true) {
		if (npcTrav!=NULL)
			i++;
		else
			break;
		
		npcTrav=npcTrav->next;
	}
	*/

	numNPCs--;

}



/// ---------------------------------------------
/// Member Function: plotPixel
/// Input:			screen x, screen y, color
/// Output:			***
/// Description:	Raw pixel plotter to buffer
/// ---------------------------------------------
void PSSDisplay::plotPixel(u8 x,u8 y, u8 c)
{
	VideoBuffer[(y) * 120 + (x)] = (c);
}


/// ---------------------------------------------
/// Member Function: drawTiles
/// Input:			screen x, screen y offsets
/// Output:			***
/// Description:	Draws the ground tiles, one by
///					one looping through
/// ---------------------------------------------
void PSSDisplay::drawTiles(u8 xOffset,u8 yOffset)
{

	for (int widthOffset=20+xOffset+(0);widthOffset<120;widthOffset+=16) {
		for (int heightOffset=20+yOffset+0;heightOffset<SCREEN_Y_MAX;heightOffset+=16) {

			for(int y = 0; y < TILE_HEIGHT; y++)                  //screen height
			{
				for(int x = 0; x < (TILE_WIDTH_HALF); x++)          //screen width
				{
					
					int flipTextureX=x;

					unsigned int tempColor  = mytile_Bitmap[(y<<4)+flipTextureX];

					int tempOffset=widthOffset>>1;

					if ( ((tempColor & 0xff00) != 0x0000) && (tempColor!=0x0000) &&
						(x+tempOffset<SCREEN_X_MAX_HALF) && (y+heightOffset<SCREEN_Y_MAX)) {

						*(VideoBuffer+((y+heightOffset) * 120) + (x+widthOffset)) = mytile_Bitmap[(y<<4)+flipTextureX];

					}
				}					
			}
		}
	}

}


/// -------------------------------------------------
/// Public Member Function: drawInfoPane
/// Input:			The pane type to draw
/// Output:			***
/// Description:	This handles the various panes that
///					need to be drawn for different events
///					(help invocation, disaster, etc)
/// -------------------------------------------------
void PSSDisplay::drawInfoPane(int paneType)
{

	int helpOffsetX=30,helpOffsetY=32;

	const u16* paneData = helpbkData;

	if (paneType == PANE_HELP) {

		switch (helpMode) {

			// main
			case 0:

				paneData = helpbkData;
				break;

			// controls
			case 1:

				paneData = help_controlsData;
				break;

			// obj/npc
			case 2:

				paneData = help_objnpcData;
				break;

			// environment
			case 3:

				paneData = help_simData;
				break;

		};
	}

	if (paneType == PANE_OBJINFO) {

		paneData = objInfoData;




	}

	if (paneType == PANE_NPCINFO) {

		paneData = npcInfoData;




	}

	// Draw disaster frame
	if (paneType == PANE_DISASTER) {
		
		paneData = disasterScreenData;
		
		
		
	}

	

	// draw pane
	for (int j=0;j<=helpbk_HEIGHT;j++) {

		for (int i=0;i<=helpbk_WIDTH/2;i++) {

			if (paneType)
				*(VideoBuffer+((j+helpOffsetY)*120)+(i+helpOffsetX)) = paneData[(j*(helpbk_WIDTH/2))+i];
			else
				*(VideoBuffer+((j+helpOffsetY)*120)+(i+helpOffsetX)) = 0x0000;

		}
	}


	// Draw OBJ statistics
	if (paneType == PANE_OBJINFO) {

		// grab selected obj
		objData *objTrav = objList;
		while (objTrav!=NULL) {

			if (objTrav->isSelected)
				break;

			objTrav = objTrav->next;

		}

		// draw RISK

		int riskPercent = (int)(objTrav->risk*100);

		char tempString[100];
		siprintf(tempString,"  RISK: %d\n",(int)(objTrav->risk*100));
		dprints(tempString);

		int numTen,numOne;

		numTen = riskPercent/10;
		numOne = riskPercent%10;

		drawSoftSprite(getNumGraphic(numTen),16,16,96,53);
		drawSoftSprite(getNumGraphic(numOne),16,16,103,53);
		drawSoftSprite(percentData,16,16,110,53);


		int profitPercent = (int)(((objTrav->condition)*(objTrav->risk))*100.0);

		if (profitPercent>=100)
			profitPercent=99;

		numTen = profitPercent/10;
		numOne = profitPercent%10;

		// draw PROFIT
		drawSoftSprite(getNumGraphic(numTen),16,16,96,68);
		drawSoftSprite(getNumGraphic(numOne),16,16,103,68);
		drawSoftSprite(percentData,16,16,110,68);


		int size = objTrav->size.x;

		// draw SIZE
		drawSoftSprite(getNumGraphic(size),16,16,103,85);


		int condition = (int)(objTrav->condition*100);

		numTen = condition/10;
		numOne = condition%10;

		// draw CONDITION
		drawSoftSprite(getNumGraphic(numTen),16,16,96,100);
		drawSoftSprite(getNumGraphic(numOne),16,16,103,100);
		drawSoftSprite(percentData,16,16,110,102);



	}

	// Draw NPC statistics
	if (paneType == PANE_NPCINFO) {

		// draw TOTAL NUM NPCs

		int numTen,numOne;

		numTen = numNPCs/10;
		numOne = numNPCs%10;


		if (numTen!=0)
			drawSoftSprite(getNumGraphic(numTen),16,16,96,69);

		drawSoftSprite(getNumGraphic(numOne),16,16,102,69);


		// iterate to get NPC num
		int i=1;
		npcData *npcTrav = npcList;

		workArea *workTrav = NULL;

		while (npcTrav!=NULL) {

			if (npcTrav->isSelected) {
				workTrav = npcTrav->workList;
				break;
			}

			i++;

			npcTrav = npcTrav->next;

		}

		numTen = i/10;
		numOne = i%10;

		// draw THIS NUM NPC
		if (numTen!=0)
			drawSoftSprite(getNumGraphic(numTen),16,16,96,86);

		drawSoftSprite(getNumGraphic(numOne),16,16,102,86);


		// find work area
		while (workTrav!=NULL) {

			if (workTrav->isCurrentArea)
				break;

			workTrav = workTrav->next;

		}

		// look for this work area
		objData *objTrav = objList;
		i=1;
		while (objTrav!=NULL) {

			if (objTrav==workTrav->object)
				break;

			objTrav = objTrav->next;
			i++;

		}

		numTen = i/10;
		numOne = i%10;

		// draw WORK AREA NUM
		if (numTen!=0)
			drawSoftSprite(getNumGraphic(numTen),16,16,96,104);
		
		drawSoftSprite(getNumGraphic(numOne),16,16,102,104);


		
	}


	// Draw disaster frame number
	if (paneType == PANE_DISASTER) {
		
		int numTen,numOne;

		numTen = disasterObj/10;
		numOne = disasterObj%10;

		// draw obj num
		if (numTen!=0)
			drawSoftSprite(getNumGraphic(numTen),16,16,100,76);

		drawSoftSprite(getNumGraphic(numOne),16,16,106,76);
		
		
		
	}



	
	int helpDotOffsetX=36;
	int helpDotOffsetY=58+(helpRow<<4);

	// draw help dot
	if (paneType==PANE_HELP && helpMode==0) {
		for (int j=0;j<16;j++) {
			for (int i=0;i<8;i++) {

				*(VideoBuffer+((j+helpDotOffsetY)*120)+(i+helpDotOffsetX)) = helpDotData[(j<<3)+i];

			}
		}
	}


}


/// ---------------------------------------------
/// Member Function: getNumGraphic
/// Input:			number (0-9)
/// Output:			Pointer to num graphic
/// Description:	Takes a number 0-9 and returns
///					the correct graphic pointer corresponding
///					to that number
/// ---------------------------------------------
const u16* PSSDisplay::getNumGraphic(int num)
{

	switch (num) {

		case 0:
			return(simZeroData);
		case 1:
			return(simOneData);
		case 2:
			return(simTwoData);
		case 3:
			return(simThreeData);
		case 4:
			return(simFourData);
		case 5:
			return(simFiveData);
		case 6:
			return(simSixData);
		case 7:
			return(simSevenData);
		case 8:
			return(simEightData);
		case 9:
			return(simNineData);

	};

	return(NULL);

}


/// -------------------------------------------------
/// Public Member Function: drawSoftSprite
/// Input:			graphic pointer, image size, screen offsets
/// Output:			***
/// Description:	Draws a sprite onto the screen using
///					raw pixel plotting. This is mostly used
///					for drawing the various numbers
/// -------------------------------------------------
void PSSDisplay::drawSoftSprite(const u16* imageData,int width,int height,int offsetX,int offsetY)
{

	for(int y = 0; y < height; y++)                  //screen height
	{
		for(int x = 0; x < (width>>1); x++)          //screen width
		{
			
			unsigned int tempColor  = imageData[(y*(width>>1))+x];
			
			if ( ((tempColor & 0xff00) != 0x0000) && (tempColor!=0x0000) &&
				(x<SCREEN_X_MAX_HALF) && (y<SCREEN_Y_MAX)) {
				
				*(VideoBuffer+((y+offsetY) * 120) + (x+offsetX)) = tempColor;
				
			}
		}					
	}

}



/// ---------------------------------------------
/// Public Member Function: drawGround
/// Input:			***
/// Output:			***
/// Description:	This actually handles drawing
///					anything that is drawn to the background,
///					which is anything but hardware sprites
/// ---------------------------------------------
void PSSDisplay::drawGround()
{




	// Draw tiles if NOT in help mode, otherwise draw help background

	switch (currentMode) {

		case -1:
		case 0:
		case 1:
		case 2:

			// Draw even rows
			drawTiles(0,0);
			
			// Draw odd rows
			drawTiles(TILE_WIDTH_HALF>>1,TILE_HEIGHT_HALF);

			break;

		case 3:

			drawInfoPane(PANE_HELP);

			break;

		case 4:

			drawInfoPane(PANE_OBJINFO);

			break;

		case 5:
			
			drawInfoPane(PANE_NPCINFO);

			break;

		case 6:

			drawInfoPane(PANE_DISASTER);

			break;

	};

}


/// ---------------------------------------------
/// Public Member Function: drawObjNPC
/// Input:			***
/// Output:			***
/// Description:	Beefiest algorithm in the engine.
///					Goes from determining which objects
///					and NPCs are on screen, all the way
///					through sorting them by depth (y),
///					and then feeding them into sprite memory
/// ---------------------------------------------
void PSSDisplay::drawObjNPC()
{



	// various local vars
	objData *tempObj		= objList;
	npcData *tempNPC		= npcList;



	////////////////////////////////////////////////
	// Delete tempList
	////////////////////////////////////////////////
	objNPCList *tempListDel = tempList;
	while (tempListDel!=NULL) {
		
		tempListDel=tempListDel->next;
		delete (wallList*)(tempList->pObjNPC);
		delete tempList;
		tempList = tempListDel;
	}

	tempList = NULL;
	

	//char tempString[100];
	
	

	////////////////////////////////////////////////
	// Reset sprite X,Y positions
	////////////////////////////////////////////////
	resetDynamicSprites();


	////////////////////////////////////////////////
	// Delete visibleObj list
	////////////////////////////////////////////////
	deleteVisibleObjNPCList();


	////////////////////////////////////////////////
	// Add Objs to ObjNPC List
	////////////////////////////////////////////////
	tempList = addVisibleObj(tempObj,tempList);


	////////////////////////////////////////////////
	// Add NPCs to ObjNPC List
	////////////////////////////////////////////////
	tempList = addVisibleNPC(tempNPC,tempList);


	//////////////////////////////////////////////////
	// Sort ObjNPC List
	//////////////////////////////////////////////////
	sortVisibleObjNPC(tempList);


	//////////////////////////////////////////////////
	// Finalize sprite settings so they can be
	// written to OAMmem on next pass
	//////////////////////////////////////////////////
	int spriteNum = finalizeSprites(tempList);

	spriteNum++;

	u16 attrib0,attrib1;


	//////////////////////////////////////////////////
	// Check for selector (obj creation) visibility,
	// add to OAMmem if necessary
	//////////////////////////////////////////////////
	if (addObjLevel>0) {

		// setup sprite
		attrib0 = COLOR_256 | TALL;
		attrib1 = SIZE_32;

		int newX=((firstSelector.x<<4)-(firstSelector.y<<4))+72;
		int newY=((firstSelector.y<<3)+(firstSelector.x<<3))+36;

		// set y,x
		attrib0 |= newY;
		attrib1 |= newX;

		// set partial transparency
		attrib0 |= MODE_TRANSPARENT;

		//int memOffset=spriteMem->getSprMemOffset("ObjSelector1");
		int memOffset=512+8+32+8+8+16+32+64+128+16+16+16+16+8+8;
		int priority=0;

		// add sprite
		//spriteMem->addSprite("Dynamic",memOffset,priority,attrib0,attrib1,32,16,newX,newY);
		sprites[spriteNum].attribute0=attrib0;
		sprites[spriteNum].attribute1=attrib1;
		sprites[spriteNum].attribute2 = memOffset | PRIORITY(priority);
		spriteNum++;
	}
	if (addObjLevel>1) {

		// setup sprite
		attrib0 = COLOR_256 | TALL;
		attrib1 = SIZE_32;

		int newX=((secondSelector.x<<4)-(secondSelector.y<<4))+72;
		int newY=((secondSelector.y<<3)+(secondSelector.x<<3))+36;

		// set y,x
		attrib0 |= newY;
		attrib1 |= newX;

		// set partial transparency
		attrib0 |= MODE_TRANSPARENT;

		//int memOffset=spriteMem->getSprMemOffset("ObjSelector2");
		int memOffset=512+8+32+8+8+16+32+64+128+16+16+16+16+8+8+16;
		int priority=0;

		// add sprite
		sprites[spriteNum].attribute0=attrib0;
		sprites[spriteNum].attribute1=attrib1;
		sprites[spriteNum].attribute2 = memOffset | PRIORITY(priority);

	}




}


/// ---------------------------------------------
/// Public Member Function: drawInterface
/// Input:			***
/// Output:			***
/// Description:	This just decrements the display
///					update flag. Relic from initial skeleton
///					structure of code. The interface is all
///					hardware sprites, and as such is handled
///					by the render() function below
/// ---------------------------------------------
void PSSDisplay::drawInterface()
{

	gUpdateDisplay--;

	if (gUpdateDisplay<0)
		gUpdateDisplay=0;
}



/// ---------------------------------------------
/// Public Member Function: render
/// Input:			***
/// Output:			***
/// Description:	Uses the GBA's DMA3 channel to
///					write sprite data into OAMMem.
///					CPU and DMA share the same bus,
///					so CPU is automatically halted for
///					this operation. It's still the fastest
///					way to do it, though
/// ---------------------------------------------
void PSSDisplay::render()
{

	/////////////////////////////////////////////////////
	// Use DMA controller to write new OAMmem values
	/////////////////////////////////////////////////////
	REG_DM3SAD = (u32)sprites;
	REG_DM3DAD = (u32)OAMmem;
	REG_DM3CNT = 512 |DMA_16NOW;

}


/// ---------------------------------------------
/// Public Member Function: updateTimer
/// Input:			***
/// Output:			***
/// Description:	This updates the spinning "PSS"
///					logo that used to be in the bottom right
///					corner. It is just hidden now, but I think
///					this is still called
/// ---------------------------------------------
void PSSDisplay::updateTimer()
{



		clockRot+=5;

		if (clockRot>359)
			clockRot-=360;

		s16 pa,pb,pc,pd;

        pa = COS[clockRot];    //(do my fixed point multiplies and shift back down)
		pb = SIN[clockRot];
		pc = -SIN[clockRot];
		pd = COS[clockRot];

        rotData[clockSpriteNum].pa = pa; //put them in my data struct
        rotData[clockSpriteNum].pb = pb;
        rotData[clockSpriteNum].pc = pc;
        rotData[clockSpriteNum].pd = pd;

}





/////////////////////////////////////////////////////////////////////////
// PRIVATE METHOD FUNCTIONS
/////////////////////////////////////////////////////////////////////////


/// -------------------------------------------------
/// Private Member Function: resetDynamicSprites
/// Input:			***
/// Output:			***
/// Description:	Sets the x,y positions of all dynamic
///					sprites (walls, NPCs, etc) off-screen.
///					This is so if the next frame has less
///					dynamic sprites, old ones won't hang
///					around and confuse people
/// -------------------------------------------------
void PSSDisplay::resetDynamicSprites()
{

	////////////////////////////////////////////////
	// Reset sprite X,Y positions
	////////////////////////////////////////////////
	for (int i=spriteVarStart;i<128;i++) {
		sprites[i].attribute0 &= 0xFE00;
		sprites[i].attribute1 &= 0xFE00;
	}
}


/// -------------------------------------------------
/// Private Member Function: deleteVisibleObjNPCList
/// Input:			***
/// Output:			***
/// Description:	This resets the visible dynamic sprite
///					list. This list is rebuilt in the below
///					functions
/// -------------------------------------------------
void PSSDisplay::deleteVisibleObjNPCList()
{

	////////////////////////////////////////////////
	// Delete visibleObj list from last frame
	////////////////////////////////////////////////
	objVisible *tempObjDel = visibleObjs;
	while (tempObjDel!=NULL) {
		
		//visibleObjs->object->isVisible=false;
		tempObjDel=tempObjDel->next;
		delete visibleObjs;
		visibleObjs = tempObjDel;
	}
	
	visibleObjs=NULL;
}


/// -------------------------------------------------
/// Private Member Function: addVisibleObj
/// Input:			objList pointer, main objNPCList pointer
/// Output:			modified objNPCList pointer
/// Description:	This adds all walls for objs determined
///					to be on-screen to the dynamic sprite
///					rotation. The results of this function are
///					NOT used for the path finder, since NPCs
///					could walk through walls if they are
///					off-screen (oops)
/// -------------------------------------------------
PSSDisplay::objNPCList* PSSDisplay::addVisibleObj(objData *tempObj,objNPCList *tempList)
{


	bool isObjectSelected=false;

	wallList *wall;

	////////////////////////////////////////////////
	// Add all walls to obj/npc list
	////////////////////////////////////////////////
	while (tempObj!=NULL) {

		if ( (tempObj->location.x>iDisplayOffset->x-5)						&&
			 (tempObj->location.x<iDisplayOffset->x+NUM_TILES_WIDE+5)		&&
			 (tempObj->location.y>iDisplayOffset->y-5)						&&
			 (tempObj->location.y<iDisplayOffset->y+NUM_TILES_HIGH+5))		{


			////////////////////////////////////////////////
			// Add this obj to visibleObjs list
			////////////////////////////////////////////////
			if (visibleObjs==NULL) {
					visibleObjs = new objVisible;
					visibleObjs->object = tempObj;
					visibleObjs->isObj = true;
					visibleObjs->next=NULL;
			}
			else {
				objVisible *temp = new objVisible;
				temp->object = tempObj;
				temp->isObj = true;
				temp->next=visibleObjs;
				visibleObjs=temp;
			}

			tempObj->isVisible=true;


			////////////////////////////////////////////////
			// Control selections
			////////////////////////////////////////////////
			if (tempObj->isSelected && isObjectSelected)
				tempObj->isSelected=false;

			if (tempObj->isSelected)
				isObjectSelected=true;


			//////////////////////////////////////////////////
			// Cycle through walls for this objects, add
			// to wall list -
			// The two rear walls are left and top in 2D grid
			// These four wall stretches (left,right,top,bottom)
			// could probably be rolled up into a loop. I found
			// it's easier to understand/debug if they are
			// separated like this.
			//////////////////////////////////////////////////

			// add left walls
			for (int i=0;i<tempObj->size.y;i++) {

				wall = new wallList;

				wall->location.x = tempObj->location.x-i;
				wall->location.y = tempObj->location.y+i;

				wall->location2D.x = tempObj->location.x;
				wall->location2D.y = tempObj->location.y+i;

				wall->wallType = 0;


				if (tempList==NULL) {
					tempList = new objNPCList;
					tempList->pObjNPC = wall;

					if (tempObj->isSelected)
						tempList->isSelected=true;
					else
						tempList->isSelected=false;

					tempList->isObj=1;
					((wallList*)(tempList->pObjNPC))->flip = 1;
					((wallList*)(tempList->pObjNPC))->isObj = 1;
					((wallList*)(tempList->pObjNPC))->isYWall = true;
					((wallList*)(tempList->pObjNPC))->object = tempObj;

					tempList->next=NULL;
				}
				else {
					objNPCList *temp = new objNPCList;
					temp->pObjNPC = wall;

					if (tempObj->isSelected)
						temp->isSelected=true;
					else
						temp->isSelected=false;

					temp->isObj=1;
					((wallList*)(temp->pObjNPC))->flip = 1;
					((wallList*)(temp->pObjNPC))->isObj = 1;
					((wallList*)(temp->pObjNPC))->isYWall = true;
					((wallList*)(temp->pObjNPC))->object = tempObj;
					temp->next=tempList;
					tempList=temp;
				}

			}


			// add top walls
			for (int i=0;i<tempObj->size.x;i++) {

				wall = new wallList;

				wall->location.x = tempObj->location.x+i;
				wall->location.y = tempObj->location.y+i;

				wall->location2D.x = tempObj->location.x+i;
				wall->location2D.y = tempObj->location.y;

				wall->wallType = 1;


				if (tempList==NULL) {
					tempList = new objNPCList;
					tempList->pObjNPC = wall;

					if (tempObj->isSelected)
						tempList->isSelected=true;
					else
						tempList->isSelected=false;


					tempList->isObj=1;
					((wallList*)(tempList->pObjNPC))->flip = 0;
					((wallList*)(tempList->pObjNPC))->isObj = 1;
					((wallList*)(tempList->pObjNPC))->isYWall = false;
					((wallList*)(tempList->pObjNPC))->object = tempObj;
					tempList->next=NULL;
				}
				else {
					objNPCList *temp = new objNPCList;
					temp->pObjNPC = wall;

					if (tempObj->isSelected)
						temp->isSelected=true;
					else
						temp->isSelected=false;


					temp->isObj=1;
					((wallList*)(temp->pObjNPC))->flip = 0;
					((wallList*)(temp->pObjNPC))->isObj = 1;
					((wallList*)(temp->pObjNPC))->isYWall = false;
					((wallList*)(temp->pObjNPC))->object = tempObj;
					temp->next=tempList;
					tempList=temp;

				}



			}


			// add right walls
			for (int i=0;i<tempObj->size.y;i++) {

				if (i==1)
					continue;

				wall = new wallList;

				wall->location.x = tempObj->location.x-i+tempObj->size.x-1;
				wall->location.y = tempObj->location.y+i+tempObj->size.y;

				wall->location2D.x = tempObj->location.x+tempObj->size.x-1;
				wall->location2D.y = tempObj->location.y+i;

				wall->wallType = 2;
				

				if (tempList==NULL) {
					tempList = new objNPCList;
					tempList->pObjNPC = wall;

					if (tempObj->isSelected)
						tempList->isSelected=true;
					else
						tempList->isSelected=false;

					tempList->isObj=2;
					((wallList*)(tempList->pObjNPC))->flip = 0;
					((wallList*)(tempList->pObjNPC))->isObj = 1;
					((wallList*)(tempList->pObjNPC))->isYWall = true;
					((wallList*)(tempList->pObjNPC))->object = tempObj;
					tempList->next=NULL;
				}
				else {
					objNPCList *temp = new objNPCList;
					temp->pObjNPC = wall;

					if (tempObj->isSelected)
						temp->isSelected=true;
					else
						temp->isSelected=false;

					temp->isObj=2;
					((wallList*)(temp->pObjNPC))->flip = 0;
					((wallList*)(temp->pObjNPC))->isObj = 1;
					((wallList*)(temp->pObjNPC))->isYWall = true;
					((wallList*)(temp->pObjNPC))->object = tempObj;
					temp->next=tempList;
					tempList=temp;
				}



			}


			// add bottom walls
			for (int i=0;i<tempObj->size.y;i++) {
				wall = new wallList;

				wall->location.x = tempObj->location.x-tempObj->size.x+i+1;
				wall->location.y = tempObj->location.y+tempObj->size.y+i;

				wall->location2D.x = tempObj->location.x+tempObj->size.x+i+1;
				wall->location2D.y = tempObj->location.y+tempObj->size.y;

				wall->wallType = 3;
				

				if (tempList==NULL) {
					tempList = new objNPCList;
					tempList->pObjNPC = wall;

					if (tempObj->isSelected)
						tempList->isSelected=true;
					else
						tempList->isSelected=false;

					tempList->isObj=2;
					((wallList*)(tempList->pObjNPC))->flip = 1;
					((wallList*)(tempList->pObjNPC))->isObj = 1;
					((wallList*)(tempList->pObjNPC))->isYWall = false;
					((wallList*)(tempList->pObjNPC))->object = tempObj;
					tempList->next=NULL;
				}
				else {
					objNPCList *temp = new objNPCList;
					temp->pObjNPC = wall;

					if (tempObj->isSelected)
						temp->isSelected=true;
					else
						temp->isSelected=false;

					temp->isObj=2;
					((wallList*)(temp->pObjNPC))->flip = 1;
					((wallList*)(temp->pObjNPC))->isObj = 1;
					((wallList*)(temp->pObjNPC))->isYWall = false;
					((wallList*)(temp->pObjNPC))->object = tempObj;
					temp->next=tempList;
					tempList=temp;
				}


			}


		}

		else {
			tempObj->isVisible=false;
		}

		tempObj=tempObj->next;
	}


	//////////////////////////////////////////////////
	// Default this obj to selected if no other objs
	// are already selected
	//////////////////////////////////////////////////
	if (!isObjectSelected && visibleObjs!=NULL && visibleObjs->object!=NULL) {
		visibleObjs->object->isSelected=true;
	}

	return tempList;

}


/// -------------------------------------------------
/// Private Member Function: addVisibleNPC
/// Input:			NPCList pointer, main objNPCList pointer
/// Output:			modified objNPCList pointer
/// Description:	Adds in NPCs determined to be visible,
///					very similar to adding in objects
/// -------------------------------------------------
PSSDisplay::objNPCList* PSSDisplay::addVisibleNPC(npcData *tempNPC,objNPCList *tempList)
{

	wallList *wall;

	bool isObjectSelected=false;

	//char tempString[100];

	////////////////////////////////////////////////
	// Add all NPCs to obj/npc list and wallList
	////////////////////////////////////////////////
	while (tempNPC!=NULL) {
		
		// test if this NPC is in the visual range
		if ( (tempNPC->location.x>iDisplayOffset->x-5)						&&
			(tempNPC->location.x<iDisplayOffset->x+NUM_TILES_WIDE+5)		&&
			(tempNPC->location.y>iDisplayOffset->y-5)						&&
			(tempNPC->location.y<iDisplayOffset->y+NUM_TILES_HIGH+5))		{
			
		
			////////////////////////////////////////////////
			// Add this npc to visibleObjs list
			////////////////////////////////////////////////
			if (visibleObjs==NULL) {
				visibleObjs = new objVisible;
				visibleObjs->npc = tempNPC;
				visibleObjs->isObj = false;
				visibleObjs->next=NULL;
			}
			else {
				objVisible *temp = new objVisible;
				temp->npc = tempNPC;
				temp->isObj = false;
				temp->next=visibleObjs;
				visibleObjs=temp;
			}

			////////////////////////////////////////////////
			// Control selections
			////////////////////////////////////////////////
			if (tempNPC->isSelected && isObjectSelected)
				tempNPC->isSelected=false;
			
			if (tempNPC->isSelected)
				isObjectSelected=true;


			wall = new wallList;
			
			wall->location.x = tempNPC->location.x;
			wall->location.y = tempNPC->location.y+2;

			wall->location2D.x = tempNPC->location2D.x;
			wall->location2D.y = tempNPC->location2D.y;

			wall->isObj = 0;

			wall->pOffsetX = (int)(tempNPC->percentLeft.x*100.0);
			wall->pOffsetY = (int)(tempNPC->percentLeft.y*100.0);

			wall->moveOffsetX = tempNPC->percentLeft.x;
			wall->moveOffsetY = tempNPC->percentLeft.y;

			wall->wallType = 4;
			
			// add this NPC to display list
			if (tempList==NULL) {
				tempList = new objNPCList;
				tempList->pObjNPC = wall;
				
				if (tempNPC->isSelected)
					tempList->isSelected=true;
				else
					tempList->isSelected=false;

				tempList->isObj=0;
				((wallList*)(tempList->pObjNPC))->flip = 0;
				((wallList*)(tempList->pObjNPC))->isObj = 0;
				tempList->next=NULL;
			}
			else {
				objNPCList *temp = new objNPCList;
				temp->pObjNPC = wall;
				
				
				if (tempNPC->isSelected)
					temp->isSelected=true;
				else
					temp->isSelected=false;
				
				
				temp->isObj=0;
				((wallList*)(temp->pObjNPC))->flip = 0;
				((wallList*)(temp->pObjNPC))->isObj = 0;
				temp->next=tempList;
				tempList=temp;
			}
		}

		tempNPC=tempNPC->next;
	}

	//////////////////////////////////////////////////
	// Default this npc to selected if no other npcs
	// are already selected
	//////////////////////////////////////////////////
	if (!isObjectSelected && visibleObjs!=NULL) {

		objVisible* visTemp;
		for (visTemp=visibleObjs; visTemp!=NULL; visTemp=visTemp->next) {
			if (!visTemp->isObj)
				break;
		}

		if (visTemp!=NULL)
			visTemp->npc->isSelected=true;
	}

	return(tempList);
}


/// -------------------------------------------------
/// Private Member Function: sortVisibleObjNPC
/// Input:			main objNPCList
/// Output:			***
/// Description:	Sorts all dynamic sprites by y-order
///					Keeps things looking "right"
/// -------------------------------------------------
void PSSDisplay::sortVisibleObjNPC(objNPCList *tempList)
{

	////////////////////////////////////////////////
	// Sort wallList by decreasing y-value
	// Currently bubble-sort
	////////////////////////////////////////////////
	bool isSwapped=true;
	while (isSwapped && tempList!=NULL) {
		isSwapped=false;
		
		objNPCList *sortTrav = tempList->next;
		objNPCList *sortLast = tempList;
		
		while (sortTrav!=NULL) {
			
			wallList *wallCurr = ((wallList*)(sortTrav->pObjNPC));
			wallList *wallLast = ((wallList*)(sortLast->pObjNPC));

			int tempYLast,tempYCurr;

			if (wallLast->isObj) {
				tempYLast = wallLast->location2D.y;

				// correct for left-wall one-off depth problem
				if (wallLast->isYWall)
					tempYLast++;

			}
			else {
				tempYLast = wallLast->location2D.y+7;

				if (wallLast->pOffsetX>0 && wallLast->pOffsetY<0)
					tempYLast--;

				if (wallLast->pOffsetX<0 && wallLast->pOffsetY>0)
					tempYLast++;
			}

			if (wallCurr->isObj) {
				tempYCurr = wallCurr->location2D.y;

				// correct for left-wall one-off depth problem
				if (wallCurr->isYWall)
					tempYCurr++;

			}
			else {
				tempYCurr = wallCurr->location2D.y+7;

				if (wallCurr->pOffsetX>0 && wallCurr->pOffsetY<0)
					tempYCurr--;

				if (wallCurr->pOffsetX<0 && wallCurr->pOffsetY>0)
					tempYCurr++;
			}
			
			if (tempYLast<tempYCurr) {
				
				sortLast->pObjNPC = wallCurr;
				sortTrav->pObjNPC = wallLast;
				
				int tempObj=sortLast->isObj;
				sortLast->isObj=sortTrav->isObj;
				sortTrav->isObj=tempObj;
				
				int tempSelect=sortLast->isSelected;
				sortLast->isSelected=sortTrav->isSelected;
				sortTrav->isSelected=tempSelect;
				
				isSwapped=true;
			}
			
			sortLast=sortTrav;
			sortTrav=sortTrav->next;
			
		}
	}
}


/// -------------------------------------------------
/// Private Member Function: finalizeSprites
/// Input:			main objNPCList pointer
/// Output:			***
/// Description:	Actually writes all the finalized
///					dynamic sprites into the sprites
///					array
/// -------------------------------------------------
int PSSDisplay::finalizeSprites(objNPCList *tempList)
{

	////////////////////////////////////////////////////////////
	// Write all visible objs and NPCs sprite values to OAMmem
	////////////////////////////////////////////////////////////
	objNPCList *dispList = tempList;
	int i;
	for (i=currentSpriteNum;i<128;i++) {


		u16 attrib0,attrib1;

		if (dispList==NULL)
			break;


		////////////////////////////////////////////////
		// Set X,Y coords for this sprite
		////////////////////////////////////////////////

		int newX,newY;

		if (((wallList*)(dispList->pObjNPC))->isObj) {
			newY = ((((wallList*)(dispList->pObjNPC))->location.y - iDisplayOffset->y)*(TILE_HEIGHT>>1));
			newX = ((((wallList*)(dispList->pObjNPC))->location.x - iDisplayOffset->x)*(TILE_WIDTH>>1));
		}
		else {
			newY = (int)(((((double)((wallList*)(dispList->pObjNPC))->location.y) + 
					 (((wallList*)(dispList->pObjNPC))->moveOffsetY)) - (double)(iDisplayOffset->y))*(double)(TILE_HEIGHT>>1));
			
			newX = (int)(((((double)((wallList*)(dispList->pObjNPC))->location.x) +
					 (((wallList*)(dispList->pObjNPC))->moveOffsetX)) - (double)(iDisplayOffset->x))*(double)(TILE_WIDTH>>1));
		}


		////////////////////////////////////////////////
		// Set init attrib's for OBJs and NPCs
		////////////////////////////////////////////////
		if (dispList->isObj!=0) {
			attrib0 = COLOR_256 | WIDE;
			attrib1 = SIZE_32;
		}
		else {
			attrib0 = COLOR_256 | WIDE;
			attrib1 = SIZE_8;
		}


		////////////////////////////////////////////////
		// Flip this sprite if necessary
		// (left walls get flipped)
		////////////////////////////////////////////////
		if (((wallList*)(dispList->pObjNPC))->flip==1) {
			attrib1 |= HORIZONTAL_FLIP;
			newY-=4;
			newX-=22;
		}
		else {
			attrib1 &= ~HORIZONTAL_FLIP;
			newY-=4;
			newX-=6;
		}


		////////////////////////////////////////////////
		// Compensate for screen wrap-around
		////////////////////////////////////////////////
		if (newX>=250)
			newX=250;

		if (newY>=170)
			newY=170;

		if (newX<0)
			newX+=512;

		if (newY<0)
			newY+=255;



		//////////////////////////////////////////////////
		// Kill all obj/npc sprite delay if in pane modes,
		// otherwise set the X,Y coords
		//////////////////////////////////////////////////
		if (currentMode<3) {
			attrib0 |= newY;
			attrib1 |= newX;
		}

		int memOffset=512,priority=0;


		//////////////////////////////////////////////////
		// Set correct graphic/transparency for this
		// sprite (3 types: wall upper, wall lower, npc)
		//////////////////////////////////////////////////
		if (dispList->isObj==0) {

			// normal npc
			memOffset = 512+8+32+8+8+16+32+64+128+16+16+16+16+8+8+16+16+8+8+8+8+8+16+8;

			// selected npc
			if (dispList->isSelected)
				memOffset = 512+8+32+8+8+16+32+64+128+16+16+16+16+8+8+16+16+8+8+8+8+8+16+8+4;

			attrib0 &= ~MODE_TRANSPARENT;

		}
		else if (dispList->isObj==1) {
			if (!dispList->isSelected)
				// not selected, top
				//memOffset = spriteMem->getSprMemOffset("WallUpper");
				memOffset = 512+8+32+8+8;
			else
				// selected, top
				//memOffset = spriteMem->getSprMemOffset("WallUpperSelect");
				memOffset = 512+8+32+8+8+16+32+64+128+16+16;

			attrib0 &= ~MODE_TRANSPARENT;
		}
		else if (dispList->isObj==2) {
			if (!dispList->isSelected)
				// not selected, bottom
				//memOffset = spriteMem->getSprMemOffset("WallLower");
				memOffset = 512+8+32+8+8+16+32+64+128+16;
			else
				// selected, bottom
				//memOffset = spriteMem->getSprMemOffset("WallLowerSelect");
				memOffset = 512+8+32+8+8+16+32+64+128+16+16+16;

			attrib0 |= MODE_TRANSPARENT;
		}


		////////////////////////////////////////////////
		// Set this sprite's attrib's
		////////////////////////////////////////////////

		//spriteMem->addSprite("Dynamic",memOffset,priority,attrib0,attrib1,16,32,newX,newY);
		sprites[i].attribute0 = attrib0;
		sprites[i].attribute1 = attrib1;
		sprites[i].attribute2 = memOffset | PRIORITY(priority);


		dispList=dispList->next;
	}

	return(i);
}





/// -------------------------------------------------
/// Private Member Function: rebuildWallList
/// Input:			objList pointer, main objNPCList pointer
/// Output:			updated objNPCList pointer
/// Description:	This is a final addition to correct a
///					bug with the path finder. It creates a
///					wallList representing ALL walls in the game.
///					It is rebuilt on obj creation/deletion.
///					It is almost identical to addVisibleObj,
///					with some stuff removed to add ALL objs
/// -------------------------------------------------
PSSDisplay::objNPCList* PSSDisplay::rebuildWallList(objData *tempObj,objNPCList *tempList)
{

	wallList *wall;

	////////////////////////////////////////////////
	// Add all walls to obj/npc list
	////////////////////////////////////////////////
	while (tempObj!=NULL) {




			//////////////////////////////////////////////////
			// Cycle through walls for this objects, add
			// to wall list -
			// The two rear walls are left and top in 2D grid
			//////////////////////////////////////////////////

			// add left walls
			for (int i=0;i<tempObj->size.y;i++) {

				wall = new wallList;

				wall->location.x = tempObj->location.x-i;
				wall->location.y = tempObj->location.y+i;

				wall->location2D.x = tempObj->location.x;
				wall->location2D.y = tempObj->location.y+i;

				wall->wallType = 0;

				if (tempObj->size.x==5) {
					char tempString[100];
					siprintf(tempString,"    wall: (%d, %d)\n",wall->location2D.x,wall->location2D.y);
					dprints(tempString);
				}

				if (tempList==NULL) {
					tempList = new objNPCList;
					tempList->pObjNPC = wall;

					if (tempObj->isSelected)
						tempList->isSelected=true;
					else
						tempList->isSelected=false;

					tempList->isObj=1;
					((wallList*)(tempList->pObjNPC))->flip = 1;
					((wallList*)(tempList->pObjNPC))->isObj = 1;
					((wallList*)(tempList->pObjNPC))->isYWall = true;
					((wallList*)(tempList->pObjNPC))->object = tempObj;

					tempList->next=NULL;
				}
				else {
					objNPCList *temp = new objNPCList;
					temp->pObjNPC = wall;

					if (tempObj->isSelected)
						temp->isSelected=true;
					else
						temp->isSelected=false;

					temp->isObj=1;
					((wallList*)(temp->pObjNPC))->flip = 1;
					((wallList*)(temp->pObjNPC))->isObj = 1;
					((wallList*)(temp->pObjNPC))->isYWall = true;
					((wallList*)(temp->pObjNPC))->object = tempObj;
					temp->next=tempList;
					tempList=temp;
				}

			}


			// add top walls
			for (int i=0;i<tempObj->size.x;i++) {

				wall = new wallList;

				wall->location.x = tempObj->location.x+i;
				wall->location.y = tempObj->location.y+i;

				wall->location2D.x = tempObj->location.x+i;
				wall->location2D.y = tempObj->location.y;

				wall->wallType = 1;


				if (tempList==NULL) {
					tempList = new objNPCList;
					tempList->pObjNPC = wall;

					if (tempObj->isSelected)
						tempList->isSelected=true;
					else
						tempList->isSelected=false;


					tempList->isObj=1;
					((wallList*)(tempList->pObjNPC))->flip = 0;
					((wallList*)(tempList->pObjNPC))->isObj = 1;
					((wallList*)(tempList->pObjNPC))->isYWall = false;
					((wallList*)(tempList->pObjNPC))->object = tempObj;
					tempList->next=NULL;
				}
				else {
					objNPCList *temp = new objNPCList;
					temp->pObjNPC = wall;

					if (tempObj->isSelected)
						temp->isSelected=true;
					else
						temp->isSelected=false;


					temp->isObj=1;
					((wallList*)(temp->pObjNPC))->flip = 0;
					((wallList*)(temp->pObjNPC))->isObj = 1;
					((wallList*)(temp->pObjNPC))->isYWall = false;
					((wallList*)(temp->pObjNPC))->object = tempObj;
					temp->next=tempList;
					tempList=temp;

				}



			}


			// add right walls
			for (int i=0;i<tempObj->size.y;i++) {

				if (i==1)
					continue;

				wall = new wallList;

				wall->location.x = tempObj->location.x-i+tempObj->size.x-1;
				wall->location.y = tempObj->location.y+i+tempObj->size.y;

				wall->location2D.x = tempObj->location.x+tempObj->size.x-1;
				wall->location2D.y = tempObj->location.y+i;

				wall->wallType = 2;
				

				if (tempList==NULL) {
					tempList = new objNPCList;
					tempList->pObjNPC = wall;

					if (tempObj->isSelected)
						tempList->isSelected=true;
					else
						tempList->isSelected=false;

					tempList->isObj=2;
					((wallList*)(tempList->pObjNPC))->flip = 0;
					((wallList*)(tempList->pObjNPC))->isObj = 1;
					((wallList*)(tempList->pObjNPC))->isYWall = true;
					((wallList*)(tempList->pObjNPC))->object = tempObj;
					tempList->next=NULL;
				}
				else {
					objNPCList *temp = new objNPCList;
					temp->pObjNPC = wall;

					if (tempObj->isSelected)
						temp->isSelected=true;
					else
						temp->isSelected=false;

					temp->isObj=2;
					((wallList*)(temp->pObjNPC))->flip = 0;
					((wallList*)(temp->pObjNPC))->isObj = 1;
					((wallList*)(temp->pObjNPC))->isYWall = true;
					((wallList*)(temp->pObjNPC))->object = tempObj;
					temp->next=tempList;
					tempList=temp;
				}



			}


			// add bottom walls
			for (int i=0;i<tempObj->size.y;i++) {
				wall = new wallList;

				wall->location.x = tempObj->location.x-tempObj->size.x+i+1;
				wall->location.y = tempObj->location.y+tempObj->size.y+i;

				wall->location2D.x = tempObj->location.x+tempObj->size.x+i+1;
				wall->location2D.y = tempObj->location.y+tempObj->size.y;

				wall->wallType = 3;
				

				if (tempList==NULL) {
					tempList = new objNPCList;
					tempList->pObjNPC = wall;

					if (tempObj->isSelected)
						tempList->isSelected=true;
					else
						tempList->isSelected=false;

					tempList->isObj=2;
					((wallList*)(tempList->pObjNPC))->flip = 1;
					((wallList*)(tempList->pObjNPC))->isObj = 1;
					((wallList*)(tempList->pObjNPC))->isYWall = false;
					((wallList*)(tempList->pObjNPC))->object = tempObj;
					tempList->next=NULL;
				}
				else {
					objNPCList *temp = new objNPCList;
					temp->pObjNPC = wall;

					if (tempObj->isSelected)
						temp->isSelected=true;
					else
						temp->isSelected=false;

					temp->isObj=2;
					((wallList*)(temp->pObjNPC))->flip = 1;
					((wallList*)(temp->pObjNPC))->isObj = 1;
					((wallList*)(temp->pObjNPC))->isYWall = false;
					((wallList*)(temp->pObjNPC))->object = tempObj;
					temp->next=tempList;
					tempList=temp;
				}


			}


		tempObj=tempObj->next;
	}

	return tempList;

}
