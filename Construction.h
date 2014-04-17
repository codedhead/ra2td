#pragma once
#include "afxwin.h"


#include "GameEngine.h"
#include "Bitmap.h"
#include "Background.h"
#include "Sprite.h"
#include "ConstructionSprite.h"
#include "CounterSprite.h"
#include "PersonSprite.h"
#include "DefendSprite.h"
#include "TeslaSprite.h"
#include "IcoSprite.h"
#include "MenuSprite.h"
#include "TargetSprite.h"
#include "MissionEndSprite.h"
#include "PadButtonSprite.h"
#include "MouseSprite.h"
#include "PicDelaySprite.h"



HINSTANCE g_hInstance;
HWND g_hWnd;
GameEngine* g_pGame;

HDC g_hOffscreenDC;
HBITMAP g_hOffscreenBitmap;

Bitmap* g_pBGBitmap;//游戏中背景
Background* g_pBackground;

Bitmap* g_pSideBitmap;//建筑侧栏
Sprite* g_pSideSprite;

Bitmap* g_pMainBitmap;//主界面
Background* g_pMain;

Bitmap* g_pMission1Bitmap;
PicDelaySprite* g_pMission1Sprite;

Bitmap* g_pMission2Bitmap;
PicDelaySprite* g_pMission2Sprite;
// Bitmap* g_pMainBottomBitmap;//主界面
// Background* g_pMainBottom;
// Bitmap* g_pMainSideBitmap;//主界面
// Background* g_pMainSide;


Bitmap* g_pMouseBitmap;

Bitmap* g_pMenuTextBitmap;
Bitmap* g_pMenuNullBitmap;

MenuSprite* g_msMainMenu;//主菜单

Bitmap* g_pMovingPointerBitmap;
Sprite* g_pMovingPointerSprite;

Bitmap* g_pAboutBitmap;
Bitmap* g_pIntroBitmap;

Bitmap* g_pRadarBitmap;

BOOL g_bWin;

int g_iStartSection;

/////////////////////////////////////////////////
////Bitmap///////////////////////////////////////

//ConstructionIco
Bitmap* g_pIcoBitmap[KINDSOFCON];

//Construction
Bitmap* g_pConstructionBitmap[KINDSOFCON];

//Person
Bitmap* g_pPersonBitmap[KINDOFPER];

//Other Stuff
Bitmap* g_pCounterBitmap;
Bitmap* g_pEvanBombBitmap;
Bitmap* g_pSealBombBitmap;
Bitmap* g_pManBurnedBitmap;
Bitmap* g_pManRadiumBitmap;
Bitmap* g_pManShockedBitmap;
Bitmap* g_pManToAshBitmap;

Bitmap* g_pChronoBitmap;
Bitmap* g_pPlaneBitmap;
Bitmap* g_pParachuteBitmap;

Bitmap* g_pNMSBitmap;
TargetSprite* g_pNMSSprite;

Bitmap* g_pMissionEndBitmap;
MissionEndSprite* g_pMissionEndSprite;

Bitmap* g_pNMissileBitmap;

int g_iTElectricity=0;
int g_iUElectricity=0;
int g_iMoney=8000;
BOOL g_bLowPower=TRUE;


Bitmap* g_pFixBitmap;
Bitmap* g_pSellBitmap;
PadButtonSprite* g_pFixSprite;
PadButtonSprite* g_pSellSprite;

MouseSprite* g_pMouseSprite;

BOOL g_bShowInfo=FALSE;
struct _ShowInfo
{
	
	CString strInfo;
	POINT ptShowPos;
}g_siShowInfo;


/////////////////////////////////////////////////
////Sprite///////////////////////////////////////

//Normal(ico)
IcoSprite* g_pIcoSprite[KINDSOFCON];

//CounterSprite
CounterSprite* g_pCounterSprite;

int g_iPowerPlantCount=0;
int g_iBattleLabCount=0;

POINT left={0,0},right={0,0};
int length,width;
BOOL g_bSelecting=FALSE;

CFont g_cfFont;




KindOfCon ReadyToBuild;//将要建


POINT Node[9][2]=
{
	{{3,3},{13,5}},
	{{11,5},{13,12}},
	{{13,10},{19,12}},
	{{17,-1},{19,10}},
	{{7,-1},{17,1}},
	{{7,-6},{9,-1}},
	{{9,-6},{24,-4}},
	{{22,-4},{24,11}},
	{{24,9},{29,11}}
};
POINT Path[]={
	{-18,123},
	{217,245},
	{37,346},
	{200,436},
	{517,275},
	{251,126},
	{382,56},
	{821,275},
	{407,487},
	{547,564}
};
int g_iPathLength=10;

ConstructionInfo g_ciConstructionInfo[KINDSOFCON];
PersonInfo g_piPersonInfo[KINDOFPER];

CDSList g_dsWavList;

BOOL g_bGameOver;
GameState g_gsGameState;

// POINT g_ptPR[8];
// int g_iParaNum;
// POINT g_ptToRelease;
// int g_iNextNode;

int g_iPassFrames;
int g_iStudyTime;
int g_iLaunchTime;
BOOL g_bNotStudy;
BOOL g_bNotLaunch;

int g_iPlaneTrigger;
int g_iPlaneDelay;
int g_iChronoTrigger;
int g_iChronoDelay;
int g_iEnimyTrigger;
int g_iEnimyDelay;


//Help Function
void Construct(int x,int y);

void LoadAllBitmaps(HWND hWnd);
void SetIcoSprite();
void LoadWavFile();
void ClearAllBitmaps();

void InitConstructionInfo();
void InitPersonInfo();
void AddEnimies();
void PlaneEnimies();
void ChronoEnimies();

BOOL CanPutHere();
void InitPath();

void MovePlaceRect(int x,int y);

void NewMenu();
void NewGame();
