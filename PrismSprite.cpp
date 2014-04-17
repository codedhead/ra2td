#include "PrismSprite.h"
#include "DefendSprite.h"

extern int g_iBattleLabCount;

PrismSprite::PrismSprite(RECT& rcPosition,DefendSprite* tcSprite,PersonSprite* psToAttack)
:Sprite(rcPosition)
{

	m_ptStart.x=rcPosition.left;
	m_ptStart.y=rcPosition.top;
	m_ptEnd.x=rcPosition.right;
	m_ptEnd.y=rcPosition.bottom;

	dsParentSprite=tcSprite;
	m_psToAttack=psToAttack;
	m_iZOrder=m_ptEnd.y;
	m_stType=stPRISM;
}

PrismSprite::~PrismSprite()
{
}

void PrismSprite::UpdateFrame()
{
	if((m_iFrameDelay>=0)&&(--m_iFrameTrigger<=0))
	{
		m_iFrameTrigger=m_iFrameDelay;
		if(m_psToAttack!=NULL&&m_psToAttack->Dying())
			m_psToAttack=NULL;
		else if(m_psToAttack!=NULL&&!m_psToAttack->Dying())
		{
			m_ptEnd=m_psToAttack->GetCenter();
			if(g_iBattleLabCount>0)
				m_psToAttack->Hurt(14);
			else
				m_psToAttack->Hurt(10);
		}
		
		if(++m_iCurFrame>=m_iNumFrames)
		{
			if(m_bOneCycle)
				m_bDying=TRUE;
		}
	}
}

void PrismSprite::Draw(HDC hDC)
{
// 	int iWidth,iHeight;
// 	iWidth=abs(m_ptEnd.x-m_ptStart.x);
// 	iHeight=abs(m_ptEnd.y-m_ptStart.y);
// 	HPEN oldPen,newPen;
// 	HDC hMemDC=CreateCompatibleDC(hDC);
// 	HBITMAP oldBmp,hMemBmp=CreateCompatibleBitmap(hDC,iWidth,iHeight);
// 	newPen=CreatePen(1,3,RGB(252,252,252));
// 	oldPen=(HPEN)SelectObject(hMemDC,newPen);
// 	oldBmp=(HBITMAP)SelectObject(hMemDC,hMemBmp);
// 	
// 	if(m_ptStart.x<m_ptEnd.x)
// 	{
// 		MoveToEx(hMemDC,0,0,NULL);
// 		LineTo(hMemDC,iWidth,iHeight);
// 	}
// 	else
// 	{
// 		MoveToEx(hMemDC,iWidth,0,NULL);
// 		LineTo(hMemDC,0,iHeight);
// 	}	
// 
// 	BLENDFUNCTION   blendFunction;   
// 	blendFunction.BlendFlags=0;   
// 	blendFunction.BlendOp=AC_SRC_OVER;   
// 	blendFunction.SourceConstantAlpha=128;   
// 	blendFunction.AlphaFormat=0; 
// 	
// 	if(m_ptStart.x<m_ptEnd.x)
// 		AlphaBlend(hDC,m_ptStart.x,m_ptStart.y,iWidth,
// 			iHeight,hMemDC,0,0,iWidth,iHeight,blendFunction);
// 	else
// 		AlphaBlend(hDC,m_ptEnd.x,m_ptStart.y,iWidth,
// 			iHeight,hMemDC,0,0,iWidth,iHeight,blendFunction);
// 
// 	SelectObject(hMemDC,oldPen);
// 	SelectObject(hMemDC,oldBmp);
// 	DeleteObject(hMemBmp);
// 	DeleteObject(newPen);
// 	DeleteDC(hMemDC);
	HPEN oldPen,newPen;
	newPen=CreatePen(1,2,RGB(252,252,252));
 	oldPen=(HPEN)SelectObject(hDC,newPen);

	MoveToEx(hDC,m_ptStart.x,m_ptStart.y,NULL);
	LineTo(hDC,m_ptEnd.x,m_ptEnd.y);

	SelectObject(hDC,oldPen);
	DeleteObject(newPen);
}