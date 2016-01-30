/****************************************************************/
/*	File:			extern.h									*/
/*	Description:	Various extern's needed throughout			*/
/*					the program									*/
/*	Last Modified:	04/19/2004									*/
/*	Author:			Dave Kahler									*/
/****************************************************************/


#ifndef EXTERNS
#define EXTERNS

/////////////////////////////////////////////////////
// CORE GBA VARS
/////////////////////////////////////////////////////
extern u16 *OAMmem;
extern volatile u16 *VideoBuffer;
extern u16 *FrontBuffer;
extern u16 *BackBuffer;
extern u16 *OAMData;
extern u16 *BGPaletteMem;
extern u16 *OBJPaletteMem;
extern u16* currentBackBuffer;



/////////////////////////////////////////////////////
// GBA-SPECIFIC GLOBAL STRUCTS
/////////////////////////////////////////////////////


//sprite structure definitions
typedef struct tagOAMEntry
{
	u16 attribute0;
	u16 attribute1;
	u16 attribute2;
	u16 attribute3;
}OAMEntry, *pOAMEntry;

extern OAMEntry sprites[128];


typedef struct tagRotData
{
	u16 filler1[3];
	u16 pa;
	u16 filler2[3];
	u16 pb; 
	u16 filler3[3];
	u16 pc; 
	u16 filler4[3];
	u16 pd;
}RotData,*pRotData;

extern pRotData rotData;




/////////////////////////////////////////////////////
// GAME-SPECIFIC GLOBAL STRUCTS
/////////////////////////////////////////////////////


struct Point {
	int x,y;
};

struct PointD {
	double x,y;
};


// This stores a single obj and all the info it needs
// to operate
typedef struct objData {
	Point location,size,location2D;
	int isVisible,isSelected;
	
	int profit;

	double risk,condition;
	
	objData *next;
};


// This is used by every NPC to control path finder
struct workArea {
	
	objData *object;
	
	bool isCurrentArea;
	
	workArea *next;
};

// Every NPC gets one of these, everything needed for
// it to operate
struct npcData {
	Point location,location2D;
	int type,direction;
	int isVisible,isSelected;
	
	int salary,risk;
	
	bool atWorkArea;
	
	bool isMoving;

	bool negotiatingX;

	int totalInRoom,currInRoom;
	
	struct movePercent {
		double x,y;
	};
	
	movePercent percentLeft;
	
	Point oldTile;
	
	int foundObject;
	
	workArea *workList;
	
	npcData *next;
};

// Refreshed on each frame, contains all dynamic sprites
typedef struct objVisible {
	objData *object;
	npcData *npc;
	
	bool isObj;
	
	objVisible *next;
};





/////////////////////////////////////////////////////
// GAME GRAPHICS DATA
/////////////////////////////////////////////////////
extern const u16 mytile_Bitmap[];
extern const u16 master_Palette[];

extern const u16 ifaceDataMidLeft[];
extern const u16 ifaceDataBottomLeft[];
extern const u16 ifaceDataTopLeft[];
extern const u16 ifaceDataTopMidLeft[];
extern const u16 ifaceDataTopMidRight[];
extern const u16 ifaceDataTopRight[];
extern const u16 ifaceDataMidRight[];
extern const u16 ifaceDataBottomRight[];
extern const u16 ifaceDataBottomMidRight[];
extern const u16 ifaceDataBottomMidLeft[];

extern const u16 iFaceDataSelect[];

extern const u16 wallData[];
extern const u16 wallLowerData[];

extern const u16 wallSelectData[];
extern const u16 wallLowerSelectData[];

extern const u16 intCurve[];
extern const u16 timerCirc[];

extern const u16 intCurveSelect[];

extern const u16 helpButtonData[];
extern const u16 helpButtonSelectData[];

extern const u16 logoData[];

extern const u16 modeWheel[];
extern const u16 modeWheelSelect[];

extern const u16 helpbkData[];
extern const u16 helpDotData[];

extern const u16 obj_itemData[];
extern const u16 obj_item_selectData[];

extern const u16 npc_itemData[];
extern const u16 npc_item_selectData[];

extern const u16 obj_item_minusData[];
extern const u16 obj_item_select_minusData[];

extern const u16 npc_item_minusData[];
extern const u16 npc_item_select_minusData[];

extern const u16 objCreate1Data[];
extern const u16 objCreate2Data[];

extern const u16 logo_dkwheelData[];

extern const u16 npcCharData[];
extern const u16 npcCharSelectData[];

extern const u16 help_controlsData[];

extern const u16 npc_item_infoData[];
extern const u16 obj_item_infoData[];
extern const u16 obj_item_info_selectData[];
extern const u16 npc_item_info_selectData[];

extern const u16 cashData[];
extern const u16 dollarData[];

extern const u16 zeroData[];
extern const u16 oneData[];
extern const u16 twoData[];
extern const u16 threeData[];
extern const u16 fourData[];
extern const u16 fiveData[];
extern const u16 sixData[];
extern const u16 sevenData[];
extern const u16 eightData[];
extern const u16 nineData[];

extern const u16 timeData[];
extern const u16 colonData[];

extern const u16 npcInfoData[];
extern const u16 objInfoData[];

extern const u16 simZeroData[];
extern const u16 simOneData[];
extern const u16 simTwoData[];
extern const u16 simThreeData[];
extern const u16 simFourData[];
extern const u16 simFiveData[];
extern const u16 simSixData[];
extern const u16 simSevenData[];
extern const u16 simEightData[];
extern const u16 simNineData[];

extern const u16 disasterScreenData[];

extern const u16 help_objnpcData[];
extern const u16 help_simData[];

extern const u16 percentData[];

extern const u16 commaData[];



/////////////////////////////////////////////////////
// VARIOUS GLOBALS
/////////////////////////////////////////////////////
extern int addObjLevel;

extern int helpRow;
extern int helpMode;
extern int helpDelay;

extern int itemMode;


extern int colonSprite;

// game timer
extern u32 gameTimer;

// sim timer
extern u32 simTimer;

// num NPCs in world
extern int numNPCs;


extern const u16* modeWheelOff,*modeWheelOn,
			*intCurveOff,*intCurveOn,
			*helpOff,*helpOn;


extern int helpButtonSpriteOffset;
extern int modeWheelSpriteOffset;
extern int intCurveSpriteOffset;
extern int objItemSpriteOffset;
extern int npcItemSpriteOffset;

extern int timeHourSpriteOffset;
extern int timeMinTenSpriteOffset;
extern int timeMinOneSpriteOffset;
extern int timeSecTenSpriteOffset;
extern int timeSecOneSpriteOffset;

extern int itemSelectSpriteOffset;

extern int leftSelectFillSprite;

extern int iFaceSpriteOffset;


// main select graphics (to turn on/off)
extern int mainSelectors[6];


extern bool isHelpSelected;
extern bool isModeWheelSelected;
extern bool isScreenSelected;

extern int currentSelection;

extern int gFlipBuffers;

extern int gUpdateBackground;

extern int modeWheelAngle;
extern int modeWheelMode;

extern const u16 *objItemPtr,
		   *objItemSelectPtr,
		   *npcItemPtr,
		   *npcItemSelectPtr;

extern int volatile keypressDelay;

extern int currentMode;

extern int blankMain;

extern int* KEYS;

extern int spriteVarStart;
extern int currentSpriteNum;

extern int modeWheelSprite;

extern int clockRot;

extern int clockSpriteNum;

extern const s16 SIN[360];
extern const s16 COS[360];

extern int gUpdateDisplay;


extern Point firstSelector,secondSelector;

extern bool isStartup;


// universal game pause
extern bool isPaused;

// work area change timer
extern u32 workAreaTimer;


// obj that was just deleted by disaster
extern int disasterObj;


// DEBUG
extern bool killDisplay;


extern objVisible *visibleObjs;

extern npcData *npcList;
extern objData *objList;


extern u32 npcTimer;



#endif
