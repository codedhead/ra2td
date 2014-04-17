#pragma once



#include "DSList.h"





#define KINDSOFCON 7
/*#define KINDOFICO 7*/
#define KINDOFPER 11
#define SIZEOFWAVLIST 9

#define TESLANODE 7
// #define OFFSET_CENTER_X_EXP 10
// #define OFFSET_CENTER_Y_EXP 32
// #define OFFSET_PLACE_X_EXP (346/2+14)
// #define OFFSET_PLACE_Y_EXP 187

#define SIGN(number) (number>0?1:(number==0?0:-1))

typedef HBITMAP (*LoadImageFunc)(const char *pStrFileName);

typedef int Offset;
typedef WORD FrameName;
typedef WORD FrameCount;
typedef WORD DIRECTION;
typedef WORD DefendState;

enum BuildingState
{
	bsNone,bsBuilding,bsComplete
};

enum MenuFunction
{
	mfNone,mfGameStart,mfGameEnd,mfGameAbout,mfGameIntro
};

enum WavList
{
	Building,ConstructionComplete,PillAt1,PrismAt,PrismPow,
	SentryAt3,TeslaAt1,TeslaPow,Uplace,SlideIn,RadarOn,Ucheer,NuclearReady,
	NuclearLaunch,ChronoLaunch,PlaneOver,
	AtRocketeer,AtTesla,AtGun1,AtGun2,AtGun3,AtGun4,AtGun5,Usell
};
// 
// enum AttackWav
// {
// 	CONSCRIPT,DESOLATOR,EVAN,FLAK_TROOPER,
// 		LAND_ROCKETEER,ROCKETEER,SNIPER,
// 		TESLA_TROOPER,US_SOLDIER,WHITE_SEAL,
// 	YELLOW_SEAL
// };

enum SpriteType
{
	stNORMAL,stPERSON,stCONSTRUCTION,stDEFEND,stTESLA,stPRISM,stMENUITEM,stICO,stCOUNTER,stTARGET,stMISSIONEND,stNMISSILE,
	stFIX,stSELL
};

enum DieWay
{
	dwNORMAL,dwBURNED,dwRADIUM,dwSHOCKED
};

enum KindOfCon
{
		POWER_PLANT,
		SENTRY_GUN,PILL_BOX,A_BATTLE_LAB,TESLA_COIL,PRISM_TOWER,
		NUCLEAR_REACTOR,/*GATTLING_CANON,*/		
};
// 			TESLA_COIL/*´Å±©ÏßÈ¦*/,S_BATTLE_LAB,
// 		S_WALL,SENTRY_GUN/*ÉÚ½äÅÚ*/,FLAK_CANNON/*·À¿ÕÅÚ*/,
// 		TESLA_REACTOR/*´ÅÄÜ·´Ó¦Â¯*/,NUCLEAR_REACTOR,
// 		S_BASE,PSYCHIC_TOWER,A_WALL,INDUSTRIAL_PLANT,
// 		PATRIOT_MISSILE/*°®¹úÕß*/,PILL_BOX/*»úÇ¹µï±¤*/,
// 		PRISM_TOWER/*¹âÀâËþ*/,SPYSAT_UPLINK/*¼äµýÎÀÐÇ*/,
// 		WEATHER_CONTROL_DEVICE
// 
// enum KindOfIco
// {
// 	A_BATTLE_LAB_ICO,TESLA_COIL_ICO,GATTLING_CANON_ICO,
// 	NUCLEAR_MISSILE_SLOT_ICO,NUCLEAR_REACTOR_ICO,
// 	PILL_BOX_ICO,POWER_PLANT_ICO,
// 	PRISM_TOWER_ICO,PSYCHIC_TOWER_ICO,S_BATTLE_LAB_ICO,
// 	SENTRY_GUN_ICO,TESLA_REACTOR_ICO,WEATHER_CONTROL_DEVICE_ICO,
// 	LIGHTENING_STORM_ICO
// };

enum KindOfPerson
{
	CONSCRIPT,FLAK_TROOPER,
	LAND_ROCKETEER,ROCKETEER,SNIPER,
	TESLA_TROOPER,DESOLATOR,EVAN,US_SOLDIER,WHITE_SEAL,
	YELLOW_SEAL
};


struct ConstructionInfo
{
	Offset PLACE_X,PLACE_Y;
	int Left,Right,Top,Bottom;
	int BottomLength,BottomWidth;
	int BuildTime;
	int NumFrames;
	int BuildFrame;
	int WorkFrame;
	int AttackFrame;
	int Money;
	int Electricity;
};

struct PersonInfo
{
	int NumFrames;
	FrameName StandFrame;
	FrameName WalkFrame;
	FrameName CreepFrame;
	FrameName DieFrame;
	FrameName AttackFrame;
	FrameName LayAttackFrame;
	FrameName FallingFrame;
	FrameCount StandCount;
	FrameCount WalkCount;
	FrameCount CreepCount;
	FrameCount DieCount;
	FrameCount AttackCount;
	FrameCount LayAttackCount;
};

enum GameState
{
	gsMainMenu,gsLoadMission,gsGaming,gsMission1,gsMission2,gsIntro,gsAbout
};

extern GameState g_gsGameState;

extern ConstructionInfo g_ciConstructionInfo[KINDSOFCON];
extern PersonInfo g_piPersonInfo[KINDOFPER];
extern CDSList g_dsWavList;

const DIRECTION 
	UP=0,
	LEFTUP=1,
	LEFT=2,
	LEFTDOWN=3,
	DOWN=4,
	RIGHTDOWN=5,
	RIGHT=6,
	RIGHTUP=7;
const int WALKDELAY=0;
const WORD STEP=15/3;

const WORD CON_NORMAL=0,
		   CON_DEFEND=1;

const DefendState
	DS_WAIT=0,
	DS_READY=1,
	DS_ATTACK=2;
