/* NOTE: This is old code, not used anymore, but I don't like to
just throw code away so it goes here */





	// Setup ground tile graphic array (probably won't be used)
/*	for (int i=0;i<GRID_SIZE_X;i++) {
		for (int j=0;j<GRID_SIZE_Y;j++) {
			groundTiles[i][j].tileGraphic=mytile_Bitmap;
		}
	}*/




/*	iScrollOffset->x+=x;
	iScrollOffset->y+=y;

	if (iScrollOffset->x <-TILE_WIDTH/2) {
		iScrollOffset->x+=(TILE_WIDTH<<1);
		iDisplayOffset->x++;
	}

	if (iScrollOffset->x >(TILE_WIDTH*2)) {
		iScrollOffset->x-=((TILE_WIDTH)<<1);
		iDisplayOffset->x--;
	}

	if (iScrollOffset->y <-TILE_HEIGHT/2) {
		iScrollOffset->y+=TILE_HEIGHT;
		iDisplayOffset->y++;
	}

	if (iScrollOffset->y >(TILE_HEIGHT/2)) {
		iScrollOffset->y-=(TILE_HEIGHT);
		iDisplayOffset->y--;
	}

	int tempScrollX = (int)iScrollOffset->x;
	int tempScrollY = (int)iScrollOffset->y;


	int count=0;

	for (int x=0; x<4; x++) {
		for (int y=0;y<5;y++) {

			//if (x==0)
			//	continue;

			//sprites[count].attribute0 &= 0xFE00;
			//sprites[count].attribute1 &= 0xFE00;

			int newX = ((x)*TILE_WIDTH*2)+tempScrollX;
			int newY = ((y)*TILE_HEIGHT*2)+tempScrollY;


			if (newX>=240)
				newX=239;

			if (newY>=160)
				newY=159;

			if (newX<0)
				newX+=512;

			if (newY<0)
				newY+=255;

			

			//sprites[count].attribute0 |= newY;
			//sprites[count].attribute1 |= newX;

			count++;
		}
	}

	for (int x=0; x<4; x++) {
		for (int y=0;y<5;y++) {

			//sprites[count].attribute0 &= 0xFE00;
			//sprites[count].attribute1 &= 0xFE00;

			int newY = ((y)*TILE_HEIGHT*2)-(TILE_HEIGHT/2)+tempScrollY;
			int newX = ((x)*TILE_WIDTH*2)-(TILE_WIDTH/2)+tempScrollX;


			if (newX>=240)
				newX=239;

			if (newY>=160)
				newY=159;

			if (newX<0)
				newX+=512;

			if (newY<0)
				newY+=255;

			//sprites[count].attribute0 |= newY;
			//sprites[count].attribute1 |= newX;

			count++;
		}
	}


	//sprites[0].attribute1 = sprites[0].attribute1 & 0xFE00;  //clear the old x value
	//sprites[0].attribute1 = sprites[0].attribute1 | (100+iScrollOffset->x);
*/



/*	int X=x;
	int Y=y;
	unsigned int Color=c;
  unsigned short Temp; 
  unsigned short *Addr; 

  // prevent out of bounds ploting 
  if (X >= 240)  return; 
  if (Y >= 160)  return; 
  // set Addr to VRAM 
  Addr = (unsigned short *) VideoBuffer; // page 0 mode 4 
  // add the number of lines to the address 
  Addr += Y * 120; 
  // count the number of words horizontally 
  Addr += (X >> 1); 
  // read the VRAM location 
  Temp = *Addr; 
  // modify the hi or low byte 
  if (X & 1) 
  { 
    Temp &= 0x00FF; 
    Temp |=  Color << 8; 
  } 
  else 
  { 
    Temp &= 0xFF00; 
    Temp |= Color; 
  } 
  // write back the VRAM location 
  *Addr = Temp; */



					//if (!groundFlip && xOffset!=0)
					//	flipTextureX=TILE_WIDTH_HALF-x-1;

					//if (groundFlip && xOffset==0)
					//	flipTextureX=TILE_WIDTH_HALF-x-1;




						//*(VideoBuffer+((y+heightOffset) * 120) + (x+1+tempOffset)) = tempColor2;


					//*(VideoBuffer+((y+100) * 120) + (x+50)) = mytile_Bitmap[(y*16)+x];

					//plotPixel(x+50,y+100,mytile_Bitmap[(y*16)+x]);




/*	u16 loop;
	u16* temp;
	temp = (u16*)sprites;
	for(loop = 0; loop < 128*4; loop++)
	{
		OAMmem[loop] = temp[loop];
	}
*/
/*
	int index=0;


	for(int y_loop = 0; y_loop < 8; y_loop++)
	{
			for(int x_loop = 0; x_loop < 128; x_loop++)
			{
					CharMem[x_loop + y_loop * 512] = mytile_Bitmap[index]; 
					index++;
			} //end for x_loop
	} //end for y_loop*/


	//for (int i=0;i<100;i++)
	//	plotPixel(i,i,0xCFCF);




/*	for (int i=spriteVarStart;i<128;i++) {
		sprites[i].attribute0 &= 0xFE00;
		sprites[i].attribute1 &= 0xFE00;
	}
*/




	/*	if (((((wallList*)(dispList->pObjNPC))->location.x - iDisplayOffset->x)*TILE_WIDTH)>=SCREEN_X_MAX*2) {
			dispList=dispList->next;
			i--;
			continue;
		}

		if (((((wallList*)(dispList->pObjNPC))->location.y - iDisplayOffset->y)*TILE_HEIGHT)>=SCREEN_Y_MAX) {
			dispList=dispList->next;
			i--;
			continue;
		}*/



/*
		itos(iDisplayOffset->x,buffer);

		// display pos
		text(buffer,26,2,0x2B2B);

		itos(iDisplayOffset->y,buffer);

		text(buffer,26,1,0x2B2B);
*/





	//if (REG_TM3D>40000) {

		//REG_TM3D = 0;
		//REG_TM3CNT = TIME_FREQUENCY_1024 | TIME_ENABLE;







	// update graphics



/*
	// this is the ten-minute-pos time graphic
	for (int index=0; index < 128; index++)
	{
		OAMData[index+128+512+128+128+256+512+1024+2048+256+256+256+256+128+128+256+256+128+(512*16)] = zeroData[index];
	}

	// this is the minute-pos time graphic
	for (int index=0; index < 128; index++)
	{
		OAMData[index+128+512+128+128+256+512+1024+2048+256+256+256+256+128+128+256+256+128+128+(512*16)] = zeroData[index];
	}

	// this is the ten-second-pos time graphic
	for (int index=0; index < 128; index++)
	{
		OAMData[index+128+512+128+128+256+512+1024+2048+256+256+256+256+128+128+256+256+128+128+128+(512*16)] = zeroData[index];
	}

	// this is the second-pos time graphic
	for (int index=0; index < 128; index++)
	{
		OAMData[index+128+512+128+128+256+512+1024+2048+256+256+256+256+128+128+256+256+128+128+128+128+(512*16)] = zeroData[index];
	}


*/


/*

// --------------------------------------------------
// Function: itos
// Input:			int, char*
// Output:			-
// Description:		This is just a helper function
//					for drawDebug below
// --------------------------------------------------
void itos(int thisInt,char *buffer)
{
	int tempInt,pos=0;

	tempInt = thisInt/1000;

	bool atNumber=false;

	if (tempInt!=0) {
		buffer[pos++] = (char)(tempInt+48);
		atNumber=true;
	}

	tempInt = (thisInt/100)%10;

	if (tempInt!=0 || atNumber) {
		buffer[pos++] = (char)(tempInt+48);
		atNumber=true;
	}

	tempInt = (thisInt/10)%10;

	if (tempInt!=0 || atNumber) {
		buffer[pos++] = (char)(tempInt+48);
		atNumber=true;
	}

	tempInt = thisInt%10;

	buffer[pos++] = (char)(tempInt+48);

	if (pos<4)
		buffer[pos]='\0';
}


// ---------------------------------------------
// Member Function: drawDebug
// Input:			-
// Output:			-
// Description:		Draws some debugging info
//					if DEBUG is #define'd
// ---------------------------------------------
void PSSDisplay::drawDebug()
{

		// wipe output area
		for (int i=100;i<120;i++) {
			for (int j=0;j<30;j++) {
				plotPixel(i,j,0xCECE);
			}
		}

		// version num
		text("v0.1f",25,19,0x2B2B);


}



*/


/*
	u16 loop;
	u16* temp;
	temp = (u16*)sprites;
	for(loop = 0; loop < 128*4; loop++)
	{
		OAMmem[loop] = temp[loop];
	}*/




// --------------------------------------------------------
// Function: WaitVblank
// Input:			-
// Output:			-
// Description:		This asm function loops until vblank
//					(after line 160 is drawn) - have to
//					wait to flip the buffers or shearing
//					could occur
// --------------------------------------------------------
//extern "C" {
//	void WaitVblank();
//}


/*
 *	void VBlankIntrWait() 
{ 
  asm volatile("mov r2, #0; swi 0x05" ::: "r0", "r1", "r2", "r3"); 
  return; 
}
 */



/*
	// add even row ground sprites into system
	for (int x=0; x<4; x++) {
		for (int y=0;y<5;y++) {
			sprites[count].attribute0 = COLOR_256 | TALL | (y*TILE_HEIGHT*2);
			sprites[count].attribute1 = SIZE_64 | (x*TILE_WIDTH*2);
			sprites[count].attribute2 = 512 | PRIORITY(3);
			count++;
		}
	}

	// add odd row ground sprites into system
	for (int x=0; x<4; x++) {
		for (int y=0;y<5;y++) {

			int posX = ((x*(TILE_WIDTH*2))-(TILE_WIDTH/2));
			int posY = ((y*(TILE_HEIGHT*2))-(TILE_HEIGHT/2));

			if (posY<0)
				posY+=255;

			if (posX<0)
				posX+=512;


			sprites[count].attribute0 = COLOR_256 | TALL | posY;
			sprites[count].attribute1 = SIZE_64 | posX;
			sprites[count].attribute2 = 512 | PRIORITY(3);
			count++;
		}
	}
*/
	// create some interface sprites (place holders)

	// timer circ (32x32)
	//sprites[count].attribute0 = COLOR_256 | SQUARE | 120 | ROTATION_FLAG | SIZE_DOUBLE;
	//sprites[count].attribute1 = SIZE_32 | 208 | ROTDATA(0);




/*
		siprintf(tempString,"  Testing object at (%d, %d) (Size=%d)...\n",objTrav->location.x,objTrav->location.y,objTrav->size.x);
		dprints(tempString);

		int testX = objTrav->location.x-objTrav->location.y;

		siprintf(tempString,"  TestX: %d %d\n",objTrav->location.x-locationX,locationY-objTrav->location.y);
		dprints(tempString);

		int diffSize = ((locationY-objTrav->location.y)-(objTrav->location.x-locationX))/2;

		int diffY;

		if (objTrav->location.x-locationX<0) {
			
			siprintf(tempString,"    NEGATIVE\n");
			dprints(tempString);

			//if ((objTrav->location.x-locationX)%2==0)

				diffY = (locationY-objTrav->location.y);

				if (diffY>=objTrav->size.x*2)
					diffY-=(objTrav->location.x-locationX)*2;
				
				//else
			//	diffY = (locationY-objTrav->location.y);// + ((objTrav->location.x-locationX+1)/2);
		}
		else {

			siprintf(tempString,"    POSITIVE\n");
			dprints(tempString);

			//if ((objTrav->location.x-locationX)%2==0)
				diffY = (locationY-objTrav->location.y);

				if (diffY>=objTrav->size.x*2)
					diffY+=(objTrav->location.x-locationX)*2;

			//else
			//	diffY = (locationY-objTrav->location.y);// - ((objTrav->location.x-locationX+1)/2);
		}

//		if (diffY>=objTrav->size.x*2)
//			diffY-=objTrav->location.x-locationX;

		siprintf(tempString,"  diffY: %d\n",diffY);
		dprints(tempString);
*/



/*
		// case 2: overlapping top
		if ( (objTrav->location.x-2)	<=	locationX				&&
			 (objTrav->location.x+objTrav->size.x+2)>= locationX	&&

			 (objTrav->location.y-2)	<=	locationY				&&
			 (objTrav->location.y+objTrav->size.x+2)>= locationY )	{

			
			siprintf(tempString,"    Bad position! (2)\n\n");
			dprints(tempString);

			return(0);

		}
*/




/*
						// check for threshold
						obstructResult = display->isObstructed(tempList->location.x-3,tempList->location.y-4,true);

						if (obstructResult) {

							siprintf(tempString,"  THRESHOLD 1 %d %d\n",tempList->location.x-3,tempList->location.y-4);
							dprints(tempString);

							obstructResult = display->isObstructed(tempList->location.x-5,tempList->location.y-2,true);

							if (obstructResult) {

								siprintf(tempString,"  THRESHOLD 2 %d %d\n",tempList->location.x-5,tempList->location.y-2);
								dprints(tempString);

								tempList->location.x++;
								tempList->location.y++;

								tempList->foundObject = 0;

								tempList = tempList->next;
								continue;
							}
						}


						// check right
						obstructResult = display->isObstructed(tempList->location.x+2,tempList->location.y+2,true);

						if (obstructResult) {

							// if top, move down one
							obstructResult = display->isObstructed(tempList->location.x+1,tempList->location.y,false);
							if (obstructResult) {
								tempList->location.x--;
								tempList->location.y++;

								tempList = tempList->next;
								continue;
							}


							// otherwise, move up one
							obstructResult = display->isObstructed(tempList->location.x-1,tempList->location.y+1,false);
							if (obstructResult) {
								tempList->location.x++;
								tempList->location.y--;

								tempList = tempList->next;
								continue;
							}

						}

						// otherwise, move right
						else {

							tempList->location.x++;
							tempList->location.y++;

							tempList = tempList->next;
							continue;
						}
*/




