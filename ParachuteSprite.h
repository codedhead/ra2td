#pragma once

#include "afx.h"
#include "sprite.h"
#include "GameEngine.h"


#define FALLING 21
#define CLOSE 41

// extern POINT g_ptPR[8];
// extern int g_iParaNum;
// extern POINT g_ptToRelease;
extern GameEngine* g_pGame;
extern Bitmap* g_pParachuteBitmap;
extern Bitmap* g_pPersonBitmap[];
/*extern int g_iNextNode;*/

class PersonSprite;
class PlaneSprite;

class ParachuteSprite:public Sprite
{
protected:
	int m_iFallingV;
	int m_iCurDis;
	int m_iTotalDis;
	int m_iNextNode;
	PersonSprite* m_pHoldingPerson;
	PlaneSprite* m_pTakingPlane;
	
public:
	ParachuteSprite(PlaneSprite* pTakingPlane,PersonSprite* pHoldingPerson,int iTotalDis);
	virtual void UpdateFrame();
	virtual void Draw(HDC hDC);
	void ContinuFall();
};

