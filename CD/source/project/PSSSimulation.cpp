/****************************************************************/
/*	File:			PSSSimulation.cpp							*/
/*	Description:	Simulation Module Class Implementation		*/
/*	Last Modified:	04/19/2004									*/
/*	Author:			Dave Kahler									*/
/****************************************************************/


// ---------------------------------------------
// Headers
// ---------------------------------------------
#include "gba.h"            // GBA register definitions
#include "dispcnt.h"        // REG_DISPCNT register definitions

#include "extern.h"         // various crucial extern vars
#include "precomp.h"    // ProjSS #define's

#include "PSSSimulation.h"  // Simulation interface

//#include "PSSDisplay.h"

#include <stdio.h>
#include <stdlib.h>

void dprints(const char *sz);

/// ---------------------------------------------
/// Member Function: PSSSimulation (constructor)
/// Input:			display pointer
/// Output:			***
/// Description:	Set start money, display pointer
/// ---------------------------------------------
PSSSimulation::PSSSimulation(PSSDisplay *myDisplay)
{

	grossMoney = 20000;

	display = myDisplay;

}


/// -------------------------------------------------
/// Public Member Function: updateSimulation
/// Input:			***
/// Output:			***
/// Description:	Updates environment/AI, as
///					described in design doc
/// -------------------------------------------------
void PSSSimulation::updateSimulation()
{

	objVisible *tempVisible = visibleObjs;
	
	// Loop through objects
//	while (tempVisible!=NULL) {
		
		
//		if (tempVisible->isObj) {
			updateEnvironment(tempVisible->object);
//		}
//		else {
			updateAI(tempVisible->npc);
//		}
		
//		tempVisible = tempVisible->next;
		
//	}
}


/// ---------------------------------------------
/// Member Function: updateEnvironment
/// Input:			objList (NOT USED)
/// Output:			***
/// Description:	Updates various env.
///					parameters
/// ---------------------------------------------
void PSSSimulation::updateEnvironment(objData *obj)
{

	// Update Time
	updateTime();

	// Update Money
	updateMoney();


	// Update Risk



	if (simTimer<30)
		return;
	else
		simTimer=0;

	if (!isPaused) {

		// Update Profitability
		manageObjNPCMoney();

		// Update Condition
		updateCondition();

		// Update Disaster
		updateDisaster();

	}




}


/// ---------------------------------------------
/// Member Function: updateAI
/// Input:			npcList pointer (NOT USED)
/// Output:			***
/// Description:	Subtracts NPCs salaries and
///					updates work area
/// ---------------------------------------------
void PSSSimulation::updateAI(npcData *npc)
{


	// Change work area (induces path finder)
	if (workAreaTimer>=1800 && !isPaused) {
		display->changeNPCWorkArea(NULL);
		workAreaTimer=0;
	}



}



/// ---------------------------------------------
/// Public Member Function: updateTime
/// Input:			***
/// Output:			***
/// Description:	Updates the displayed game
///					timer. Parses total ticks
///					into a running game time.
///					(1 tick = 1/60 second)
/// ---------------------------------------------
void PSSSimulation::updateTime()
{

	u32 totalSeconds = gameTimer/60;
	u32 totalMinutes = totalSeconds/60;
	u32 totalHours   = totalMinutes/60;

	int localSeconds = totalSeconds%60;
	int localMinutes = totalMinutes%60;
	int localHours   = totalHours;

	int localTenMin	 = localMinutes/10;
	int localOneMin  = localMinutes%10;

	int localTenSec  = localSeconds/10;
	int localOneSec  = localSeconds%10;


	struct timeData {
		int thisLocalTime,thisLocalOffset;
	};

	timeData myTime[5];

	myTime[0].thisLocalTime		= localHours;
	myTime[0].thisLocalOffset	= timeHourSpriteOffset;

	myTime[1].thisLocalTime		= localTenMin;
	myTime[1].thisLocalOffset	= timeMinTenSpriteOffset;

	myTime[2].thisLocalTime		= localOneMin;
	myTime[2].thisLocalOffset	= timeMinOneSpriteOffset;

	myTime[3].thisLocalTime		= localTenSec;
	myTime[3].thisLocalOffset	= timeSecTenSpriteOffset;

	myTime[4].thisLocalTime		= localOneSec;
	myTime[4].thisLocalOffset	= timeSecOneSpriteOffset;
	

	for (int i=0;i<5;i++) {

		const u16 *thisNumData = zeroData;

		switch (myTime[i].thisLocalTime) {

			case 0:
				thisNumData = zeroData;
				break;

			case 1:
				thisNumData = oneData;
				break;
				
			case 2:
				thisNumData = twoData;
				break;
				
			case 3:
				thisNumData = threeData;
				break;
				
			case 4:
				thisNumData = fourData;
				break;
				
			case 5:
				thisNumData = fiveData;
				break;
				
			case 6:
				thisNumData = sixData;
				break;
				
			case 7:
				thisNumData = sevenData;
				break;
				
			case 8:
				thisNumData = eightData;
				break;
				
			case 9:
				thisNumData = nineData;
				break;
				
		};
	
		for (int index=0; index < 32; index++)
			OAMData[index+myTime[i].thisLocalOffset] = thisNumData[index];

	}

}


/// ---------------------------------------------
/// Public Member Function: updateMoney
/// Input:			***
/// Output:			***
/// Description:	Updates money display, parses
///					grossMoney var into separate
///					numbers
/// ---------------------------------------------
void PSSSimulation::updateMoney()
{

	int tenThousandSlot = grossMoney/10000;
	int oneThousandSlot = (grossMoney%10000)/1000;
	int oneHundredSlot	= ((grossMoney%10000)%1000)/100;
	int tenSlot			= (((grossMoney%10000)%1000)%100)/10;
	int oneSlot			= ((((grossMoney%10000)%1000)%100)%10);


	struct moneyData {
		int thisLocalMoney,thisLocalOffset;
	};
	
	moneyData myMoney[5];
	
	myMoney[0].thisLocalMoney	= tenThousandSlot;
	myMoney[0].thisLocalOffset	= timeHourSpriteOffset+32;
	
	myMoney[1].thisLocalMoney	= oneThousandSlot;
	myMoney[1].thisLocalOffset	= timeMinTenSpriteOffset+32;
	
	myMoney[2].thisLocalMoney	= oneHundredSlot;
	myMoney[2].thisLocalOffset	= timeMinOneSpriteOffset+32;
	
	myMoney[3].thisLocalMoney	= tenSlot;
	myMoney[3].thisLocalOffset	= timeSecTenSpriteOffset+32;
	
	myMoney[4].thisLocalMoney	= oneSlot;
	myMoney[4].thisLocalOffset	= timeSecOneSpriteOffset+32;
	
	
	for (int i=0;i<5;i++) {
		
		const u16 *thisNumData = zeroData;
		
		switch (myMoney[i].thisLocalMoney) {
			
		case 0:
			thisNumData = zeroData;
			break;
			
		case 1:
			thisNumData = oneData;
			break;
			
		case 2:
			thisNumData = twoData;
			break;
			
		case 3:
			thisNumData = threeData;
			break;
			
		case 4:
			thisNumData = fourData;
			break;
			
		case 5:
			thisNumData = fiveData;
			break;
			
		case 6:
			thisNumData = sixData;
			break;
			
		case 7:
			thisNumData = sevenData;
			break;
			
		case 8:
			thisNumData = eightData;
			break;
			
		case 9:
			thisNumData = nineData;
			break;
			
		};
		
		for (int index=0; index < 32; index++)
			OAMData[index+myMoney[i].thisLocalOffset] = thisNumData[index];
		
	}

}


/// -------------------------------------------------
/// Public Member Function: deductMoney
/// Input:			amount to deduct
/// Output:			***
/// Description:	Self-explanatory
/// -------------------------------------------------
void PSSSimulation::deductMoney(int amount)
{

	grossMoney -= amount;

}


/// -------------------------------------------------
/// Public Member Function: addMoney
/// Input:			amount to add
/// Output:			***
/// Description:	Self-explanatory
/// -------------------------------------------------
void PSSSimulation::addMoney(int amount)
{
	
	grossMoney += amount;

	if (grossMoney>99999)
		grossMoney=99999;
	
}


/// -------------------------------------------------
/// Private Member Function: getMoney
/// Input:			***
/// Output:			grossMoney
/// Description:		Self-explanatory
/// -------------------------------------------------
int PSSSimulation::getMoney()
{
	return(grossMoney);
}


/// -----------------------------------------------------------------
/// Private Member Function: moveNPCs
/// Input:			***
/// Output:			***
/// Description:	This is the infamous pathfinder. I really don't
///					recommend trying to understand how it works.
///					It's magic.
/// -----------------------------------------------------------------
void PSSSimulation::moveNPCs()
{

	npcData* tempList = npcList;

	char tempString[100];

	//if (npcTimer<1)
		//return;

	while (tempList!=NULL) {

		if (!tempList->atWorkArea || tempList->isMoving) {

			gUpdateDisplay=1;


			// if this NPC is in motion (between tiles), preempt this code with
			// the smooth moving
			if (tempList->isMoving) {

				if (tempList->oldTile.x-tempList->location.x > 0) {
					tempList->percentLeft.x -= 0.2;

					if (tempList->percentLeft.x<=0.0)
						tempList->percentLeft.x = 0.0;
				}
				else {
					tempList->percentLeft.x += 0.2;

					if (tempList->percentLeft.x>=0.0)
						tempList->percentLeft.x = 0.0;
				}

				if (tempList->oldTile.y-tempList->location.y < 0) {
					tempList->percentLeft.y += 0.2;

					if (tempList->percentLeft.y>=0.0)
						tempList->percentLeft.y = 0.0;
				}
				else {
					tempList->percentLeft.y -= 0.2;

					if (tempList->percentLeft.y<=0.0)
						tempList->percentLeft.y = 0.0;
				}
				

				// done moving, reset
				if (tempList->percentLeft.x==0.0 && tempList->percentLeft.y==0.0) {
					tempList->isMoving=false;

					tempList->percentLeft.x=0.0;
					tempList->percentLeft.y=0.0;
				}

				tempList = tempList->next;
				continue;

			}


			tempList->isMoving = true;
			tempList->oldTile.x = tempList->location.x;
			tempList->oldTile.y = tempList->location.y;

			// find correct work area
			workArea *tempArea = tempList->workList;
			while (tempArea!=NULL) {

				if (tempArea->isCurrentArea) {
					break;
				}

				tempArea = tempArea->next;

			}

			

			// get difference between current position and desired position
			int diffX = tempArea->object->location.x - tempList->location.x;
			int diffY = tempArea->object->location.y - tempList->location.y;

			int diffIsoX = diffX + diffY;
			int diffIsoY = diffY - diffX;

			// case IN ROOM (part I of algorithm)
			if (tempList->foundObject==-1) {

				// handle this right here too

				tempList->location.x++;
				tempList->location.y++;

				tempList->percentLeft.x = -1.0;
				tempList->percentLeft.y = -1.0;
				
				siprintf(tempString,"    currInRoom: %d\n",tempList->currInRoom);
				dprints(tempString);

				siprintf(tempString,"    totalInRoom: %d\n",tempList->totalInRoom);
				dprints(tempString);
				

				if (tempList->currInRoom>=tempList->totalInRoom) {
					tempList->foundObject=0;
					tempList->currInRoom=0;
					
				}

				tempList->currInRoom++;

				//diffIsoX = -1;
				//diffIsoY = 0;

				tempList = tempList->next;
				continue;	

			}

			if (tempList->foundObject==-2) {

				// handle this right here instead of main algorithm code
				

				if (tempList->currInRoom>=tempList->totalInRoom) {
					tempList->atWorkArea=true;
					tempList->foundObject=-1;
					tempList->currInRoom=0;

					tempList = tempList->next;
					continue;
					
				}

				tempList->location.x--;
				tempList->location.y--;
				
				tempList->percentLeft.x = 1.0;
				tempList->percentLeft.y = 1.0;

				siprintf(tempString,"    currInRoom: %d\n",tempList->currInRoom);
				dprints(tempString);
				
				siprintf(tempString,"    totalInRoom: %d\n",tempList->totalInRoom);
				dprints(tempString);


				tempList->currInRoom++;
				


				tempList = tempList->next;
				continue;		
				
			}

			siprintf(tempString,"    POS: (%d, %d)\n",tempList->location2D.x,tempList->location2D.y);
			dprints(tempString);

			// Here is the case where an NPC gets added into a room, and needs to
			// align itself
			if (tempList->foundObject==-3) {

				// find the object it's in
				workArea *workTrav = tempList->workList;
				while (workTrav!=NULL) {

					if (workTrav->isCurrentArea)
						break;

					workTrav = workTrav->next;

				}

				int npcDiffX = tempList->location2D.x - workTrav->object->location2D.x;
				int npcDiffY = tempList->location2D.y - workTrav->object->location2D.y;



				tempList->totalInRoom = workTrav->object->size.x - npcDiffX - 1;
				tempList->currInRoom = 0;

				// move 1 down
				if (npcDiffY==0) {

					tempList->location.x--;
					tempList->location.y++;

					tempList->location2D.y++;
					
					tempList->percentLeft.x = 1.0;
					tempList->percentLeft.y = -1.0;

					tempList = tempList->next;
					continue;
				}

				// don't move at all
				if (npcDiffY==1) {

					tempList->foundObject=-1;
					tempList->atWorkArea = true;

					tempList = tempList->next;
					continue;
				}

				// move up
				if (npcDiffY>1) {

					tempList->location.x++;
					tempList->location.y--;

					tempList->location2D.y--;
					
					tempList->percentLeft.x = -1.0;
					tempList->percentLeft.y = 1.0;
					
					tempList = tempList->next;
					continue;
				}

			}


			if (tempList->foundObject==1 || tempList->foundObject==5) {
				diffIsoX=0;
				diffIsoY=1;
			}

			if (tempList->foundObject==2 || tempList->foundObject==3) {
				diffIsoX=1;
				diffIsoY=0;
			}

			if (tempList->foundObject==4) {
				diffIsoX=0;
				diffIsoY=-1;
			}

			siprintf(tempString,"diffIsoX: %d\n",diffIsoX);
			dprints(tempString);

			siprintf(tempString,"diffIsoY: %d\n\n",diffIsoY);
			dprints(tempString);


			objData *obstructResult;

			// move Y
			if (diffIsoY!=0 && !tempList->negotiatingX) {

				tempList->negotiatingX = false;

				if (diffIsoY<0) {

					// test for obstruction
					obstructResult = display->isObstructed(tempList->location.x+1,tempList->location.y,false);

					char tempString[100];
					siprintf(tempString,"MOVE TESTING (Y1):\n");
					dprints(tempString);

					siprintf(tempString,"  X: %d\n",tempList->location.x+1);
					dprints(tempString);

					siprintf(tempString,"  Y: %d\n",tempList->location.y);
					dprints(tempString);

					if (tempList->foundObject==4) {
						obstructResult = display->isObstructed(tempList->location.x-1,tempList->location.y,true);

						if (obstructResult!=NULL) {
							tempList->location.x++;
							tempList->location.y--;

							tempList->location2D.y--;

							tempList->percentLeft.x = -1.0;
							tempList->percentLeft.y = 1.0;

							siprintf(tempString,"  OBSTRUCT MAIN\n");
							dprints(tempString);

							tempList = tempList->next;
							continue;
						}
						else {
							tempList->location.x--;
							tempList->location.y--;

							tempList->percentLeft.x = 1.0;
							tempList->percentLeft.y = 1.0;

							siprintf(tempString,"  NO OBSTRUCT MAIN\n");
							dprints(tempString);
							
							tempList->foundObject=-2;

							tempList->totalInRoom = rand()%(tempArea->object->size.x);
							tempList->currInRoom = 0;

							//tempList->atWorkArea = true;
							tempList = tempList->next;
							continue;
						}
					}


					if (obstructResult==NULL) {
						tempList->location.x++;
						tempList->location.y--;

						tempList->location2D.y--;

						tempList->percentLeft.x = -1.0;
						tempList->percentLeft.y = 1.0;

						tempList = tempList->next;
						continue;
					}
					else {

						// check if collided with destination room
						if (tempArea->object==obstructResult) {
							
							// move right along wall
							tempList->foundObject=3;
		
							siprintf(tempString,"  FOUND DEST OBJ\n");
							dprints(tempString);

							tempList = tempList->next;
							continue;

							//if ((obstructResult==NULL && diffIsoX<0) || 
							//tempList->location.x++;
							//tempList->location.y++;
							
							
						}

						// NOT destination room, need to move around it
						else {

							tempList->location.x--;
							tempList->location.y--;
							
							tempList->percentLeft.x = 1.0;
							tempList->percentLeft.y = 1.0;
							
							tempList = tempList->next;
							continue;
						}
					}

					
				}
				else {

					// test for obstruction
					obstructResult = display->isObstructed(tempList->location.x-1,tempList->location.y+1,false);

					char tempString[100];
					siprintf(tempString,"  MOVE TESTING (Y2):\n");
					dprints(tempString);
					
					siprintf(tempString,"  X: %d\n",tempList->location.x-1);
					dprints(tempString);
					
					siprintf(tempString,"  Y: %d\n",tempList->location.y+1);
					dprints(tempString);

					// special room negotiating case
					if (tempList->foundObject==1) {
						obstructResult = display->isObstructed(tempList->location.x+1,tempList->location.y+1,true);

						if (obstructResult!=NULL) {
							tempList->location.x--;
							tempList->location.y++;

							tempList->location2D.y++;

							tempList->percentLeft.x = 1.0;
							tempList->percentLeft.y = -1.0;

							tempList = tempList->next;
							continue;
						}
						else {
							tempList->location.x++;
							tempList->location.y++;

							tempList->percentLeft.x = -1.0;
							tempList->percentLeft.y = -1.0;
							
							tempList->foundObject=3;
							tempList = tempList->next;
							continue;
						}
					}

					// special target right-wall case
					if (tempList->foundObject==5) {
						obstructResult = display->isObstructed(tempList->location.x-1,tempList->location.y,true);
						
						if (obstructResult!=NULL) {
							tempList->location.x--;
							tempList->location.y++;

							tempList->location2D.y++;

							tempList->percentLeft.x = 1.0;
							tempList->percentLeft.y = -1.0;
							
							tempList = tempList->next;
							continue;
						}
						else {
							tempList->location.x--;
							tempList->location.y--;

							tempList->percentLeft.x = 1.0;
							tempList->percentLeft.y = 1.0;
							
							// at target object
							tempList->foundObject=-2;

							tempList->totalInRoom = rand()%(tempArea->object->size.x);
							tempList->currInRoom = 0;
							
							//tempList->atWorkArea = true;
							tempList = tempList->next;
							continue;
						}
					}

					if (obstructResult==NULL) {
						tempList->location.x--;
						tempList->location.y++;

						tempList->location2D.y++;

						tempList->percentLeft.x = 1.0;
						tempList->percentLeft.y = -1.0;

						tempList = tempList->next;
						continue;
					}
					else {
						
						// check if collided with destination room
						if (tempArea->object==obstructResult) {
							
							// move right along wall
							tempList->foundObject=2;

							tempList->location.x++;
							tempList->location.y++;

							tempList->percentLeft.x = -1.0;
							tempList->percentLeft.y = -1.0;
							
							tempList = tempList->next;
							continue;
							
						}

						// NOT destination room, sidestep
						else {
							tempList->location.x--;
							tempList->location.y--;
							
							tempList->percentLeft.x = 1.0;
							tempList->percentLeft.y = 1.0;
							
							tempList = tempList->next;
							continue;
						}

					}

					
				}
				
			}

			// move X first
			
			if (diffIsoX!=0) {
				if (diffIsoX<0) {

					// test for obstruction
					obstructResult = display->isObstructed(tempList->location.x-1,tempList->location.y,true);

					char tempString[100];
					siprintf(tempString,"  MOVE TESTING (X1):\n");
					dprints(tempString);
					
					siprintf(tempString,"  X: %d\n",tempList->location.x-1);
					dprints(tempString);
					
					siprintf(tempString,"  Y: %d\n",tempList->location.y);
					dprints(tempString);


					// handle in-room movement
					if (tempList->foundObject==-1) {

						tempList->location.x++;
						tempList->location.y++;

						tempList->percentLeft.x = -1.0;
						tempList->percentLeft.y = -1.0;

						tempList->foundObject = 0;

						tempList->negotiatingX = false;
						
						tempList = tempList->next;
						continue;

					}


					if (obstructResult==NULL) {
						tempList->location.x--;
						tempList->location.y--;

						tempList->percentLeft.x = 1.0;
						tempList->percentLeft.y = 1.0;

						tempList = tempList->next;
						continue;
					}
					else {

						

						// check if collided with destination room
						if (tempArea->object==obstructResult) {

							// test for obstruction
							obstructResult = display->isObstructed(tempList->location.x-2,tempList->location.y+1,true);

							tempList->negotiatingX = false;

							if (obstructResult) {

								tempList->foundObject=4;
								
							}
							else {
								obstructResult = display->isObstructed(tempList->location.x,tempList->location.y-1,true);
								
								if (obstructResult) {
									tempList->foundObject=4;
								}
								else {
									tempList->foundObject=5;
								}
							}

							tempList = tempList->next;
							continue;


						}

						// NOT destination room, sidestep
						else {

							tempList->location.x--;
							tempList->location.y++;

							tempList->location2D.y++;
							
							tempList->percentLeft.x = 1.0;
							tempList->percentLeft.y = -1.0;

							tempList->negotiatingX = true;
							
							tempList = tempList->next;
							continue;
						}

					}
				}
				else {

					// test for obstruction
					obstructResult = display->isObstructed(tempList->location.x+1,tempList->location.y+1,true);

					char tempString[100];
					siprintf(tempString,"MOVE TESTING (X2):\n");
					dprints(tempString);
					
					siprintf(tempString,"  X: %d\n",tempList->location.x+1);
					dprints(tempString);
					
					siprintf(tempString,"  Y: %d\n",tempList->location.y+1);
					dprints(tempString);

					siprintf(tempString,"  foundObject: %d\n",tempList->foundObject);
					dprints(tempString);

					// special case
					if (tempList->foundObject==3) {
						obstructResult = display->isObstructed(tempList->location.x+1,tempList->location.y,false);

						tempList->negotiatingX = false;
						

						if (obstructResult!=NULL) {
							tempList->location.x++;
							tempList->location.y++;

							tempList->percentLeft.x = -1.0;
							tempList->percentLeft.y = -1.0;

							siprintf(tempString,"  OBSTRUCT MAIN\n");
							dprints(tempString);

							tempList = tempList->next;
							continue;
						}
						else {
							tempList->location.x++;
							tempList->location.y--;

							tempList->location2D.y--;

							tempList->percentLeft.x = -1.0;
							tempList->percentLeft.y = 1.0;

							siprintf(tempString,"  NO OBSTRUCT MAIN\n");
							dprints(tempString);
							
							tempList->foundObject=4;
							tempList = tempList->next;
							continue;
						}
					}

					// special case
					if (tempList->foundObject==2) {
						obstructResult = display->isObstructed(tempList->location.x-1,tempList->location.y+1,false);
						
						
						tempList->negotiatingX = false;
						
						if (obstructResult!=NULL) {
							tempList->location.x++;
							tempList->location.y++;

							tempList->percentLeft.x = -1.0;
							tempList->percentLeft.y = -1.0;
							
							siprintf(tempString,"  OBSTRUCT MAIN\n");
							dprints(tempString);
							
							tempList = tempList->next;
							continue;
						}
						else {
							tempList->location.x--;
							tempList->location.y++;

							tempList->location2D.y++;

							tempList->percentLeft.x = 1.0;
							tempList->percentLeft.y = -1.0;
							
							siprintf(tempString,"  NO OBSTRUCT MAIN\n");
							dprints(tempString);
							
							tempList->foundObject=5;
							tempList = tempList->next;
							continue;
						}
					}
					

					if (obstructResult==NULL) {
						tempList->location.x++;
						tempList->location.y++;

						tempList->percentLeft.x = -1.0;
						tempList->percentLeft.y = -1.0;

						tempList = tempList->next;
						continue;
					}
					else {
						
						// check if collided with destination room
						if (tempArea->object==obstructResult) {
							
							tempList->negotiatingX = false;
							
							//diffIsoY = 0;
							tempList->foundObject=1;

							//tempList->location.x--;
							//tempList->location.y++;

							tempList = tempList->next;
							continue;
							
						}

						// NOT destination room, sidestep
						else {
							
							tempList->location.x--;
							tempList->location.y++;

							tempList->location2D.y++;
							
							tempList->percentLeft.x = 1.0;
							tempList->percentLeft.y = -1.0;

							tempList->negotiatingX = true;
							
							tempList = tempList->next;
							continue;
						}
					}
				}

				// is obstructed, try to move along Y instead
				if (!obstructResult) {
					tempList = tempList->next;
					continue;
				}
			}

		}

		tempList = tempList->next;

	}


}


/// -------------------------------------------------
/// Private Member Function: manageObjNPCMoney
/// Input:			***
/// Output:			***
/// Description:	Uses formulas to calculate gross
///					gross money change
/// -------------------------------------------------
void PSSSimulation::manageObjNPCMoney()
{

	// loop through objects
	objData *objTrav = objList;

	while (objTrav!=NULL) {

		if (numNPCs>0)
			addMoney((int)((objTrav->condition*2)*(objTrav->risk*2)));

		addMoney(numNPCs/5);

		objTrav = objTrav->next;

	}

}


/// -------------------------------------------------
/// Private Member Function: updateDisaster
/// Input:			***
/// Output:			***
/// Description:	Determines if disaster should happen
///					based on risk/condition
/// -------------------------------------------------
void PSSSimulation::updateDisaster()
{

	// loop through objects
	objData *objTrav = objList;
	objData *objPrev = NULL;

	int i=1;

	while (objTrav!=NULL) {

		// calculate risk kill possibility

		// Risk Destroy is turned OFF for demo to keep anything
		// from destroying itself unexpectedly. Turn ON for turn-in
		
/*
		u32 riskRand = rand()%100000;
		if (riskRand<(objTrav->risk*100))
			objTrav->condition=0;
*/

		// kill this object
		if (objTrav->condition<=0) {

			currentMode = 6;

			isPaused=true;

			gUpdateBackground=2;
			gUpdateDisplay=1;


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
							
							display->changeNPCWorkArea(tempNPC);
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


			if (objTrav==objList) {
				objData *tempObj = objList;

				objList = objList->next;

				delete tempObj;
			}
			else {

				objPrev->next = objTrav->next;
				delete objTrav;
			}

			deductMoney(2000);

			disasterObj = i;

			return;

		}

		i++;

		objPrev = objTrav;
		objTrav = objTrav->next;

	}



}


/// -------------------------------------------------
/// Private Member Function: updateCondition
/// Input:			***
/// Output:			***
/// Description:	Subtracts condition from all objects
/// -------------------------------------------------
void PSSSimulation::updateCondition()
{

	objData *objTrav = objList;


	while (objTrav!=NULL) {

		double riskFactor = objTrav->risk/1000;
		double randFactor = (rand()%10)/10000;

		double average = (.0005+riskFactor+randFactor)/3;

		// update this obj's condition
		objTrav->condition -= average;

		objTrav = objTrav->next;
	}






}


/// -------------------------------------------------
/// Private Member Function: induceDisaster
/// Input:			***
/// Output:			***
/// Description:	Debug, quickens time to disaster
/// -------------------------------------------------
void PSSSimulation::induceDisaster()
{

	objList->condition=.02;

}
