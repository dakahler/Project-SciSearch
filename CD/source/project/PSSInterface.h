/****************************************************************/
/*	File:			PSSInterface.h								*/
/*	Description:	Interface class interface					*/
/*	Last Modified:	11/8/2003									*/
/*	Author:			Dave Kahler									*/
/****************************************************************/


#include "PSSSimulation.h"

class PSSInterface
{
public:
	
	PSSInterface(PSSDisplay *myDisplay,PSSSimulation *mySim);
	void handleInput(int inputType);
	




private:

	PSSDisplay *display;
	PSSSimulation *sim;




};
