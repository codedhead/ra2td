#include "ConstructionSprite.h"
#include "Define.h"
extern ConstructionInfo g_ciConstructionInfo[];
// extern POINT left;
// extern POINT right;
extern int g_iMoney;

ConstructionSprite::ConstructionSprite(Bitmap* pBitmap,KindOfCon kfcKind,POINT ptLeft,POINT ptRight)
:Sprite(pBitmap),m_kfcKind(kfcKind),m_ptLeft(ptLeft),m_ptRight(ptRight)
{
	

	m_ptCenter.x=(m_rcPosition.left+m_rcPosition.right)/2;
	m_ptCenter.y=(m_rcPosition.top+m_rcPosition.bottom)/2;//+g_ciConstructionInfo[m_kfoKind].PLACE_Y;

/*	m_rcMouseNotify=m_rcPosition;*/

	SetRect(&m_rcMouseNotify,m_ptCenter.x-g_ciConstructionInfo[m_kfcKind].Left,
		m_ptCenter.y-g_ciConstructionInfo[m_kfcKind].Top,
		m_ptCenter.x+g_ciConstructionInfo[m_kfcKind].Right,
		m_ptCenter.y+g_ciConstructionInfo[m_kfcKind].Bottom);

	m_ptBottomCenter=m_ptCenter;
	m_ptBottomCenter.x+=g_ciConstructionInfo[m_kfcKind].PLACE_X;
	m_ptBottomCenter.y+=g_ciConstructionInfo[m_kfcKind].PLACE_X;

	m_bSelling=FALSE;
	/*m_iZOrder=m_ptCenter.y;*/
	m_iZOrder=m_ptBottomCenter.y;
	m_stType=stCONSTRUCTION;
}

ConstructionSprite::~ConstructionSprite()
{
}

void ConstructionSprite::SetPosition(int x,int y)
{
	m_ptCenter.x=(m_rcPosition.left+m_rcPosition.right)/2;
	m_ptCenter.y=(m_rcPosition.top+m_rcPosition.bottom)/2;//+g_ciConstructionInfo[m_kfoKind].PLACE_Y;

	m_iZOrder=m_ptBottomCenter.y;
	OffsetRect(&m_rcPosition,x-m_ptCenter.x,y-m_ptCenter.y);
// 
// 	m_rcMouseNotify=m_rcPosition;

	/*m_ptCenter.x=x;m_ptCenter.y=y;*/
	m_ptCenter.x=(m_rcPosition.left+m_rcPosition.right)/2;
	m_ptCenter.y=(m_rcPosition.top+m_rcPosition.bottom)/2;
	m_ptBottomCenter=m_ptCenter;
	m_ptBottomCenter.x+=g_ciConstructionInfo[m_kfcKind].PLACE_X;
	m_ptBottomCenter.y+=g_ciConstructionInfo[m_kfcKind].PLACE_X;
	
	m_iZOrder=m_ptCenter.y;

	SetRect(&m_rcMouseNotify,m_ptCenter.x-g_ciConstructionInfo[m_kfcKind].Left,
		m_ptCenter.y-g_ciConstructionInfo[m_kfcKind].Top,
		m_ptCenter.x+g_ciConstructionInfo[m_kfcKind].Right,
		m_ptCenter.y+g_ciConstructionInfo[m_kfcKind].Bottom);

	CalcCollisionRect();
}

void ConstructionSprite::UpdateFrame()
{
	if((m_iFrameDelay>=0)&&(--m_iFrameTrigger<=0))
	{
		m_iFrameTrigger=m_iFrameDelay;	
		
		if(m_bSelling)
		{
			m_iCurFrame--;
			g_iMoney+=0.5*g_ciConstructionInfo[m_kfcKind].Money/(g_ciConstructionInfo[m_kfcKind].WorkFrame-
				g_ciConstructionInfo[m_kfcKind].BuildFrame);
			if(m_iCurFrame>g_ciConstructionInfo[m_kfcKind].WorkFrame-1)
				m_iCurFrame=g_ciConstructionInfo[m_kfcKind].WorkFrame-1;
			else if(m_iCurFrame<0)
				m_bDying=TRUE;

			return;
		}

		m_iCurFrame++;
		
		if(m_iCurFrame==m_iNumFrames)
			m_iCurFrame=g_ciConstructionInfo[m_kfcKind].WorkFrame-1;
	}
}

void ConstructionSprite::Draw(HDC hDC)
{
	if(m_pBitmap&&!m_bHidden)
		m_pBitmap->DrawPart(hDC,m_rcPosition.left,m_rcPosition.top,0,m_iCurFrame*GetHeight(),GetWidth(),GetHeight(),TRUE,RGB(0,0,252));
// 	
// 	HBRUSH hbr=CreateSolidBrush(RGB(0,252,0));
// 	FrameRect(hDC,&m_rcMouseNotify,hbr);
// 	SetPixel(hDC,m_ptCenter.x-1,m_ptCenter.y-1,RGB(252,0,0));
// 	SetPixel(hDC,m_ptCenter.x-1,m_ptCenter.y,RGB(252,0,0));
// 	SetPixel(hDC,m_ptCenter.x-1,m_ptCenter.y+1,RGB(252,0,0));
// 	SetPixel(hDC,m_ptCenter.x,m_ptCenter.y-1,RGB(252,0,0));
// 	SetPixel(hDC,m_ptCenter.x,m_ptCenter.y,RGB(252,0,0));
// 	SetPixel(hDC,m_ptCenter.x,m_ptCenter.y+1,RGB(252,0,0));
// 	SetPixel(hDC,m_ptCenter.x+1,m_ptCenter.y-1,RGB(252,0,0));
// 	SetPixel(hDC,m_ptCenter.x+1,m_ptCenter.y,RGB(252,0,0));
// 	SetPixel(hDC,m_ptCenter.x+1,m_ptCenter.y+1,RGB(252,0,0));
// 
// 	SetPixel(hDC,m_ptBottomCenter.x-1,m_ptBottomCenter.y-1,RGB(0,0,255));
// 	SetPixel(hDC,m_ptBottomCenter.x-1,m_ptBottomCenter.y,RGB(0,0,255));
// 	SetPixel(hDC,m_ptBottomCenter.x-1,m_ptBottomCenter.y+1,RGB(0,0,255));
// 	SetPixel(hDC,m_ptBottomCenter.x,m_ptBottomCenter.y-1,RGB(0,0,255));
// 	SetPixel(hDC,m_ptBottomCenter.x,m_ptBottomCenter.y,RGB(0,0,255));
// 	SetPixel(hDC,m_ptBottomCenter.x,m_ptBottomCenter.y+1,RGB(0,0,255));
// 	SetPixel(hDC,m_ptBottomCenter.x+1,m_ptBottomCenter.y-1,RGB(0,0,255));
// 	SetPixel(hDC,m_ptBottomCenter.x+1,m_ptBottomCenter.y,RGB(0,0,255));
// 	SetPixel(hDC,m_ptBottomCenter.x+1,m_ptBottomCenter.y+1,RGB(0,0,255));
// 
//	DeleteObject(hbr);
}

void ConstructionSprite::CalcCollisionRect()
{
	m_ptCenter.x=(m_rcPosition.left+m_rcPosition.right)/2;
 	m_ptCenter.y=(m_rcPosition.top+m_rcPosition.bottom)/2;//+g_ciConstructionInfo[m_kfoKind].PLACE_Y;
	m_ptBottomCenter=m_ptCenter;
	m_ptBottomCenter.x+=g_ciConstructionInfo[m_kfcKind].PLACE_X;
	m_ptBottomCenter.y+=g_ciConstructionInfo[m_kfcKind].PLACE_Y;
	
	/*m_iZOrder=m_ptCenter.y;*/
	m_iZOrder=m_ptBottomCenter.y;
	m_rcCollision.left=m_ptCenter.x-100;
	m_rcCollision.right=m_ptCenter.x+100;
	m_rcCollision.top=m_ptCenter.y-60;
	m_rcCollision.bottom=m_ptCenter.y+60;
}