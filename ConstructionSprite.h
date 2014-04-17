#pragma once
#include "afx.h"

#include "Define.h"
#include "Bitmap.h"
#include "Sprite.h"


//做成数组，初始化传名字宏
class ConstructionSprite:public Sprite
{
protected:
	
	
	BOOL m_bSelling;

	
// 	FrameName NBuild,NWork;
// 	FrameCount CBuild,CWork;
//	int m_iBuildTime;//与counter,ico结合



public:
	POINT m_ptCenter;
/*	POINT m_ptLeft;*/
	POINT m_ptLeft,m_ptRight;

	POINT m_ptBottomCenter;
	KindOfCon m_kfcKind;
	ConstructionSprite(Bitmap* pBitmap,KindOfCon kfcKind,POINT ptLeft,POINT ptRight);
	virtual ~ConstructionSprite();
	
	virtual void SetPosition(int x,int y);
	virtual void UpdateFrame();
	virtual void Draw(HDC hDC);
	BOOL IsSelling(){return m_bSelling;}
	void Sell(){m_bSelling=TRUE;}
/*	void SetArea(POINT ptLeft){m_ptLeft=ptLeft;}*/
	virtual void CalcCollisionRect();
	void SetCenter(int x,int y){m_ptCenter.x=x;m_ptCenter.y=y;}
};
