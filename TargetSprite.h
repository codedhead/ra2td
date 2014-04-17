#pragma once
#include "afx.h"

#include "Define.h"
#include "Bitmap.h"
#include "Sprite.h"

enum TargetState
{
	tsBuild,tsStand,tsOpen,tsReady,tsClose,tsDestroy
};


//做成数组，初始化传名字宏
class TargetSprite:public Sprite
{
protected:
	POINT m_ptCenter;
	TargetState m_tsState;
	int		m_iCurHP;
	int m_iOrgHP;
	FrameName NBuild,NStand,NRuinStand,NOpen,NRuinOpen,NReady,NRuinReady,NLaunch,NRuinLaunch,NClose,NRuinClose,NDestroy;
	FrameCount CBuild,CStand,COpen,CReady,CLaunch,CClose,CDestroy;
	
public:
	TargetSprite(Bitmap* pBitmap);
	virtual ~TargetSprite();
	
	/*virtual void SetPosition(int x,int y);*/
	virtual void UpdateFrame();
	virtual void Draw(HDC hDC);
	void Open(){m_tsState=tsOpen;}
	void Lauch(){m_tsState=tsClose;}
	virtual void CalcCollisionRect();
	void Destroy(int iHurt);
	BOOL Dying(){return m_iCurHP<=0;}
	POINT GetCenter(){return m_ptCenter;}
	int GetCurHP(){return m_iCurHP;}
	int GetOrgHP(){return m_iOrgHP;}
//	void SetCenter(int x,int y){m_ptCenter.x=x;m_ptCenter.y=y;}
};

