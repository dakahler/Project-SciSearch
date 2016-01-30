/****************************************************************/
/*	File:			PSSSimulation.h								*/
/*	Description:	Simulation class interface					*/
/*	Last Modified:	04/19/2004									*/
/*	Author:			Dave Kahler									*/
/****************************************************************/

#include "PSSDisplay.h"

class PSSSimulation
{
	
public:
	
	PSSSimulation(PSSDisplay *myDisplay);

	void updateSimulation();
	void updateTime();

	void deductMoney(int amount);
	void addMoney(int amount);
	int getMoney();

	void moveNPCs();

	void induceDisaster();


private:
	
	void updateEnvironment(objData *obj);
	void updateAI(npcData *npc);

	void updateMoney();

	void manageObjNPCMoney();

	void updateDisaster();
	void updateCondition();

	int grossMoney;

	PSSDisplay *display;


};
