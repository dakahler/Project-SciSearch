/****************************************************************/
/*	File:			PSSInterface.cpp							*/
/*	Description:	Interface Module Class Implementation		*/
/*	Last Modified:	04/19/2004									*/
/*	Author:			Dave Kahler									*/
/****************************************************************/

// ---------------------------------------------
// Headers
// ---------------------------------------------
#include "gba.h"           // GBA register definitions
#include "dispcnt.h"       // REG_DISPCNT register definitions

#include "keypad.h"

#include "extern.h"        // various crucial extern vars
#include "precomp.h"    // ProjSS #define's

#include "PSSInterface.h"  // Interface interface

#include <stdio.h>

void text(char* text, u16 x, u16 y , u16 color);


/// ---------------------------------------------
/// Member Function: PSSInterface (constructor)
/// Input:			display pointer, sim pointer
/// Output:			***
/// Description:	Sets these pointers
/// ---------------------------------------------
PSSInterface::PSSInterface(PSSDisplay *myDisplay,PSSSimulation *mySim)
{
	display=myDisplay;
	sim=mySim;


}




void changeMainStatus(bool isOn);
void changeWheelStatus(bool isOn);
void changeItemStatus(bool isOn);
void changeItemHighlight(bool isOn);
void changeHelpStatus(bool isOn);

void dprints(const char *sz);


/// ---------------------------------------------
/// Member Function: handleInput
/// Input:		 	 Key that was pressed
/// Output:		 	 ***
/// Description:	 Handles all input sent by
///					 the main function.
/// ---------------------------------------------
void PSSInterface::handleInput(int inputType)
{

	//char tempString[100];


	if (currentMode!=3) {
		switch (inputType) {


			case KEY_START:

				// invoke/destroy help menu
				currentMode=3;
				helpDelay=0;

				gUpdateBackground=2;

				isPaused=true;

				break;

			case KEY_SELECT:

				// this key is set to handle various debug cheats
				// chances are one of these will be enabled for the
				// final demo


				//display->changeNPCWorkArea();

				sim->induceDisaster();

				break;


			case KEY_UP:

				switch (addObjLevel) {

					case 0:
						display->changeScrollOffset(1,-1);
						break;

					case 1:
						//firstSelector.x--;

						if (firstSelector.y>=-3)
							firstSelector.y--;

						break;

					case 2:

						if (secondSelector.x>=0 && secondSelector.y>=0) {
							secondSelector.x--;
							secondSelector.y--;
						}

						break;

				}

				break;

			case KEY_DOWN:

				switch (addObjLevel) {

					case 0:
						display->changeScrollOffset(-1,1);
						break;
						
					case 1:
						
						if (firstSelector.y<=6)
							firstSelector.y++;

						break;

					case 2:

						if (secondSelector.x<=8 && secondSelector.y<=8) {
							secondSelector.x++;
							secondSelector.y++;
						}
						
						break;

				};

				break;

			case KEY_LEFT:

				switch (addObjLevel) {

					case 0:
						display->changeScrollOffset(-1,-1);
						break;
						
					case 1:

						if (firstSelector.x>=0)
							firstSelector.x--;
						
						break;

					case 2:
						//secondSelector.x--;
						break;

				};

				break;

			case KEY_RIGHT:

				switch (addObjLevel) {

					case 0:
						display->changeScrollOffset(1,1);
						break;
						
					case 1:

						if (firstSelector.x<=10)
							firstSelector.x++;

						break;

					case 2:
						//secondSelector.x++;
						break;

				};

				break;

			case KEY_L:


				// NOT main
				if (currentMode!=0) {
					switch (currentSelection) {

						case 0:

						// turn off main selection and flip to modeWheel
							changeMainStatus(false);
							changeItemHighlight(true);

							currentSelection++;

							break;

						case 1:

							changeItemHighlight(false);
							changeWheelStatus(true);

							currentSelection++;

							break;

						case 2:

							changeWheelStatus(false);
							changeMainStatus(true);

							currentSelection=0;

							break;

					};
				}

				//////////////////////////////////////////////////////
				// MAIN MODE
				// Cycle current visible obj
				//////////////////////////////////////////////////////
				else {

					if (itemMode==0)
						display->changeVisibleObj(0);
					else
						display->changeVisibleNPC(0);

				}

				break;

			case KEY_R:

				// NOT main
				if (currentMode!=0) {
					switch (currentSelection) {

						case 0:

						// turn off main selection and flip to modeWheel
							changeMainStatus(false);
							changeWheelStatus(true);

							currentSelection=2;

							break;

						case 1:

							changeItemHighlight(false);
							changeMainStatus(true);

							currentSelection--;

							break;

						case 2:

							changeWheelStatus(false);
							changeItemHighlight(true);
							

							currentSelection--;

							break;

					};
				}

				// main
				else {

					if (itemMode==0)
						display->changeVisibleObj(1);
					else
						display->changeVisibleNPC(1);

				}


				break;

			case KEY_A:


				// NOT in mode0
				if (currentMode!=0 && currentMode!=4 && currentMode!=5) {
					switch (currentSelection) {

						// test for main
						case 0:
							currentMode=0;

							// change out select graphics to indicate mode change
							for (int index=0; index < 512; index++)
							{
								if (OAMData[index+iFaceSpriteOffset]==0xFA17)
									OAMData[index+iFaceSpriteOffset] = 0xDD17;

								if (OAMData[index+iFaceSpriteOffset]==0x17FA)
									OAMData[index+iFaceSpriteOffset] = 0x17DD;

								if (OAMData[index+iFaceSpriteOffset]==0xFAFA)
									OAMData[index+iFaceSpriteOffset] = 0xDDDD;
							}


							break;

						// test for mode wheel
						case 2:

							currentMode=1;

							if (keypressDelay>=20) {
								modeWheelAngle+=120;

								modeWheelMode++;

								if (modeWheelMode>2)
									modeWheelMode=0;

								// change out item graphics for new mode
								switch (modeWheelMode) {





									case 0:

										objItemPtr=obj_itemData,
										objItemSelectPtr=obj_item_selectData,
										npcItemPtr=npc_itemData,
										npcItemSelectPtr=npc_item_selectData;

										// swap out selection graphics
										if (itemMode==0) {
											changeItemStatus(0);
										}
										else {
											changeItemStatus(1);
										}

										break;

									case 1:

										objItemPtr=obj_item_minusData,
										objItemSelectPtr=obj_item_select_minusData,
										npcItemPtr=npc_item_minusData,
										npcItemSelectPtr=npc_item_select_minusData;

										// swap out selection graphics
										if (itemMode==0) {
											changeItemStatus(0);
										}
										else {
											changeItemStatus(1);
										}


										break;



									case 2:

										objItemPtr=obj_item_infoData,
										objItemSelectPtr=obj_item_info_selectData,
										npcItemPtr=npc_item_infoData,
										npcItemSelectPtr=npc_item_info_selectData;

										// swap out selection graphics
										if (itemMode==0) {
											changeItemStatus(0);
										}
										else {
											changeItemStatus(1);
										}



										break;

								};

								if (modeWheelAngle>360)
									modeWheelAngle-=360;

								keypressDelay=0;
							}


							break;

						// test for items
						case 1:
							currentMode=2;

							// change item mode and swap out selection graphics
							if (itemMode==0) {
								itemMode=1;
								changeItemStatus(1);
							}
							else {
								itemMode=0;
								changeItemStatus(0);
							}


							break;
					
						// test for help invocation (OLD)
						case 3:
							currentMode=3;
							helpDelay=0;

							break;

					};
				}

				// IS mode0
				else {

					// handle obj condition increase
					if (currentMode==4) {

						// find selected obj
						objData *objTrav = objList;
						while (objTrav!=NULL) {

							if (objTrav->isSelected)
								break;

							objTrav = objTrav->next;

						}

						if (sim->getMoney()>=100 &&
							objTrav->condition<.99) {

							objTrav->condition+=.01;

							sim->deductMoney(100);

							gUpdateBackground=2;
							gUpdateDisplay=1;
						}

					}


					// modeWheel=build
					if (modeWheelMode==0) {


						switch (addObjLevel) {

							case 0:

								// make first selector visible

								addObjLevel++;
								break;

							case 1:

								// set pos of second selector, make visible

								if (itemMode==0) {
									secondSelector.x=firstSelector.x+2;
									secondSelector.y=firstSelector.y+2;

									addObjLevel++;
								}

								// npc creation
								else {
									
									if (sim->getMoney()>=1000) {
										display->addNPC();
										sim->deductMoney(1000);
									}

									addObjLevel=0;

								}

								break;

							case 2:


								// test for error cases
								if ((secondSelector.x-firstSelector.x)+1<3 ||
									(secondSelector.x-firstSelector.x)+1>6) {
									addObjLevel=0;
									break;
								}

								if ((secondSelector.y-firstSelector.y)+1<3 ||
									(secondSelector.y-firstSelector.y)+1>6) {
									addObjLevel=0;
									break;
								}


								// add this object
								int size = (secondSelector.x-firstSelector.x)+1;
								if (sim->getMoney()>=size*1000)
									sim->deductMoney(display->addObject()*1000);

								addObjLevel=0;
								break;


						};

					}


					// modeWheel=destroy, item=obj
					if (modeWheelMode==1 && itemMode==0) {

						display->deleteObject();
						sim->deductMoney(1000);
					}



					// modeWheel=destroy, item=npc
					if (modeWheelMode==1 && itemMode==1) {

						display->deleteNPC();
						sim->deductMoney(500);


					}


					// INFO mode, OBJ
					if (modeWheelMode==2 && itemMode==0) {

						currentMode=4;

						isPaused=true;

						gUpdateBackground=2;


					}


					// INFO mode, NPC
					if (modeWheelMode==2 && itemMode==1) {

						currentMode=5;

						isPaused=true;

						gUpdateBackground=2;


					}


				}

				break;


			case KEY_B:

				

				if (currentMode==0 && addObjLevel==0) {

					// change out select graphics to indicate mode change
					for (int index=0; index < 512; index++)
					{
						if (OAMData[index+iFaceSpriteOffset]==0xDD17)
							OAMData[index+iFaceSpriteOffset] = 0xFA17;

						if (OAMData[index+iFaceSpriteOffset]==0x17DD)
							OAMData[index+iFaceSpriteOffset] = 0x17FA;

						if (OAMData[index+iFaceSpriteOffset]==0xDDDD)
							OAMData[index+iFaceSpriteOffset] = 0xFAFA;


					}

				}


				isPaused=false;

				if (currentMode>3) {
					gFlipBuffers=true;
					
					// blank screen
					blankMain=1;

					

					currentMode=0;
				}
				else {
					currentMode=-1;
				}



				break;

				

		};
	}
	else {

		if (helpDelay<20)
			return;

		switch (inputType) {


			case KEY_START:
			
				// invoke/destroy help menu
				currentMode=-1;
				
				gUpdateBackground=2;
				
				gFlipBuffers=true;

				isPaused=false;
				
				// blank screen
				blankMain=1;
			
				break;

			case KEY_DOWN:

				if (helpRow<2)
					helpRow++;

				gUpdateBackground=2;


				break;

			case KEY_UP:

				if (helpRow>0)
					helpRow--;

				gUpdateBackground=2;



				break;


			case KEY_A:

				switch (helpMode) {

					// main help
					case 0:

						switch (helpRow) {

							// controls
							case 0:

								helpMode=1;
								gUpdateBackground=2;
								//helpRow=0;
								break;

							// obj/npc
							case 1:
								
								helpMode=2;
								gUpdateBackground=2;
								//helpRow=0;
								break;

							// environment
							case 2:

								helpMode=3;
								gUpdateBackground=2;
								//helpRow=0;
								break;

						};

					// controls
					case 1:
						break;

					// obj/npc
					case 2:
						break;

					// environment
					case 3:
						break;

				};


				break;

			case KEY_B:


				if (helpMode==0) {
					currentMode=-1;
					isPaused=false;
				}
				else {
					helpMode=0;
				}

				gUpdateBackground=2;

				gFlipBuffers=true;

				// blank screen
				blankMain=1;

				break;


		};
		helpDelay=0;
	}

	gUpdateDisplay++;


}


/// -------------------------------------------------
/// Private Member Function: changeMainStatus
/// Input:			on or off
/// Output:			***
/// Description:	Turns main on or off
///					(changes yellow to none, etc)
/// -------------------------------------------------
void changeMainStatus(bool isOn)
{

	if (!isOn) {

		// turn off main selection

		rotData[1].pa = 64; //put them in my data struct
		rotData[1].pb = 0;
		rotData[1].pc = 0;
		rotData[1].pd = 64;

		rotData[2].pa = 32; //put them in my data struct
		rotData[2].pb = 0;
		rotData[2].pc = 0;
		rotData[2].pd = 32;

		rotData[3].pa = COS[180]>>2; //put them in my data struct
		rotData[3].pb = SIN[180]>>2;
		rotData[3].pc = -SIN[180]>>2;
		rotData[3].pd = COS[180]>>2;

		// filler graphics
		for (int i=0;i<6;i++)
			sprites[mainSelectors[i]].attribute2 = 512+8 | PRIORITY(1);


		// left filler
		sprites[leftSelectFillSprite].attribute2 = 512+8 | PRIORITY(1);

	}
	else {

		// turn on main

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

		// filler graphics
		for (int i=0;i<6;i++)
			sprites[mainSelectors[i]].attribute2 = 512+8 | PRIORITY(0);


		// left filler
		sprites[leftSelectFillSprite].attribute2 = 512+8 | PRIORITY(0);

	}

}


/// -------------------------------------------------
/// Private Member Function: changeWheelStatus
/// Input:			on or off
/// Output:			***
/// Description:	Changes wheel selection (yellow)
/// -------------------------------------------------
void changeWheelStatus(bool isOn)
{

	if (!isOn) {

		// turn off modeWheel selection

		// this is the help modeWheel graphic
		for (int index=0; index < 2048; index++)
		{
			OAMData[index+modeWheelSpriteOffset] = modeWheel[index];
		}

	}
	else {

		// this is the modeWheel select graphic
		for (int index=0; index < 2048; index++)
		{
			OAMData[index+modeWheelSpriteOffset] = modeWheelSelect[index];
		}

	}

}


/// -------------------------------------------------
/// Private Member Function: changeItemStatus
/// Input:			left or right
/// Output:			***
/// Description:	Changes item graphic (obj/npc)
/// -------------------------------------------------
void changeItemStatus(bool isNPC)
{

	if (!isNPC) {

		// change obj item to selected, change npc item to not selected
		for (int index=0; index < 256; index++)
		{
			OAMData[index+objItemSpriteOffset] = objItemSelectPtr[index];
		}

		for (int index=0; index < 256; index++)
		{
			OAMData[index+npcItemSpriteOffset] = npcItemPtr[index];
		}

	}
	else {

		// change npc item to selected, change obj item to not selected
		for (int index=0; index < 256; index++)
		{
			OAMData[index+objItemSpriteOffset] = objItemPtr[index];
		}

		for (int index=0; index < 256; index++)
		{
			OAMData[index+npcItemSpriteOffset] = npcItemSelectPtr[index];
		}


	}

}


/// -------------------------------------------------
/// Private Member Function: changeItemHighlight
/// Input:			on or off
/// Output:			***
/// Description:	Change item highlight (yellow)
/// -------------------------------------------------
void changeItemHighlight(bool isOn)
{

	if (!isOn) {

		sprites[itemSelectSpriteOffset].attribute2 = 512+8 | PRIORITY(1);
		sprites[itemSelectSpriteOffset+1].attribute2 = 512+8 | PRIORITY(1);
	}
	else {

		sprites[itemSelectSpriteOffset].attribute2 = 512+8 | PRIORITY(0);
		sprites[itemSelectSpriteOffset+1].attribute2 = 512+8 | PRIORITY(0);
	}

}


/// -------------------------------------------------
/// Private Member Function: changeHelpStatus
/// Input:			on or off
/// Output:			***
/// Description:	change help selection (deprecated)
/// -------------------------------------------------
void changeHelpStatus(bool isOn)
{

	if (!isOn) {

		// this is the help button graphic
		for (int index=0; index < 256; index++)
		{
			OAMData[index+helpButtonSpriteOffset] = helpButtonData[index];
		}

	}
	else {

		// turn on help selection
		
		// this is the help button select graphic
		for (int index=0; index < 256; index++)
		{
			OAMData[index+helpButtonSpriteOffset] = helpButtonSelectData[index];
		}

	}

}
