#include "TargetSprite.h"


TargetSprite::TargetSprite(Bitmap* pBitmap)
:Sprite(pBitmap)
{
	m_tsState=tsBuild;
	m_iOrgHP=m_iCurHP=5000;

	NBuild=1;
	NStand=27;
	NRuinStand=28;
	NOpen=29;NRuinOpen=44;
	NReady=61;
	NRuinReady=62;
	NClose=63;
	NRuinClose=79;
	NDestroy=94;
	CBuild=26;
	CStand=1;
	COpen=16;
	CReady=1;
	CClose=16;
	CDestroy=0;

	m_ptCenter.x=616;
	m_ptCenter.y=590;
	
	m_iFrameDelay=m_iFrameTrigger=1;
	
	m_iZOrder=m_ptCenter.y;

	m_stType=stTARGET;
/*	m_iZOrder=m_ptBottomCenter.y;*/
/*	m_stType=stCONSTRUCTION;*/
}

TargetSprite::~TargetSprite()
{
}

void TargetSprite::UpdateFrame()
{
	if((m_iFrameDelay>=0)&&(--m_iFrameTrigger<=0))
	{
		m_iFrameTrigger=m_iFrameDelay;		

		if(m_iCurHP<=0) m_tsState=tsDestroy;
		
		int c;
		switch(m_tsState)
		{
		case tsBuild:				
			m_iCurFrame++;
			if(m_iCurFrame<NBuild-1)
				m_iCurFrame=NBuild-1;
			else if(m_iCurFrame>=NBuild+CBuild-2)
				m_tsState=tsStand;
			break;
		case tsStand:
			if(m_iCurHP<=300)
				m_iCurFrame=NRuinStand-1;
			else
				m_iCurFrame=NStand-1;
			break;
		case tsOpen:
			if(m_iCurHP<=300)
				c=NRuinOpen-1;
			else
				c=NOpen-1;
			m_iCurFrame++;
			if(m_iCurFrame<c)
				m_iCurFrame=c;
			else if(m_iCurFrame>=c+COpen-1)
				m_tsState=tsReady;
			break;
		case tsReady:
			if(m_iCurHP<=300)
				m_iCurFrame=NRuinReady-1;
			else
				m_iCurFrame=NReady-1;
			break;
		case tsClose:
			if(m_iCurHP<=300)
				c=NRuinClose-1;
			else
				c=NClose-1;
			m_iCurFrame++;
			if(m_iCurFrame<c)
				m_iCurFrame=c;
			else if(m_iCurFrame>=c+CClose-1)
				m_tsState=tsStand;
			break;
		case tsDestroy:
			m_iCurFrame--;
			if(m_iCurFrame>NStand-1)
				m_iCurFrame=NStand-1;
			else if(m_iCurFrame<0)
				m_bDying=TRUE;
			break;		
		}
	}
}

void TargetSprite::Destroy(int iHurt)
{
	m_iCurHP-=iHurt;
}

void TargetSprite::Draw(HDC hDC)
{
	if(m_pBitmap&&!m_bHidden)
		m_pBitmap->DrawPart(hDC,m_rcPosition.left,m_rcPosition.top,0,m_iCurFrame*GetHeight(),GetWidth(),GetHeight(),TRUE,RGB(0,0,252));

// 	HBRUSH hbr=CreateSolidBrush(RGB(0,252,0));
// 	FrameRect(hDC,&m_rcMouseNotify,hbr);
// 	SetPixel(hDC,m_ptCenter.x-1,m_ptCenter.y-1,RGB(0,252,0));
// 	SetPixel(hDC,m_ptCenter.x-1,m_ptCenter.y,RGB(0,252,0));
// 	SetPixel(hDC,m_ptCenter.x-1,m_ptCenter.y+1,RGB(0,252,0));
// 	SetPixel(hDC,m_ptCenter.x,m_ptCenter.y-1,RGB(0,252,0));
// 	SetPixel(hDC,m_ptCenter.x,m_ptCenter.y,RGB(0,252,0));
// 	SetPixel(hDC,m_ptCenter.x,m_ptCenter.y+1,RGB(0,252,0));
// 	SetPixel(hDC,m_ptCenter.x+1,m_ptCenter.y-1,RGB(0,252,0));
// 	SetPixel(hDC,m_ptCenter.x+1,m_ptCenter.y,RGB(0,252,0));
// 	SetPixel(hDC,m_ptCenter.x+1,m_ptCenter.y+1,RGB(0,252,0));
/* 	DeleteObject(hbr);*/
}

void TargetSprite::CalcCollisionRect()
{
	m_rcCollision.left=m_ptCenter.x-100;
	m_rcCollision.right=m_ptCenter.x+100;
	m_rcCollision.top=m_ptCenter.y-100;
	m_rcCollision.bottom=m_ptCenter.y+100;

	SetRect(&m_rcMouseNotify,m_ptCenter.x-30,
		m_ptCenter.y-70,
		m_ptCenter.x+30,
		m_ptCenter.y+20);
}
