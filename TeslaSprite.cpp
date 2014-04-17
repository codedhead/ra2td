#include "TeslaSprite.h"
#include "DefendSprite.h"

extern int g_iBattleLabCount;

TeslaSprite::TeslaSprite(RECT& rcPosition,DefendSprite* tcSprite,PersonSprite* psToAttack)
:Sprite(rcPosition)
{
	m_ptStart.x=rcPosition.left;
	m_ptStart.y=rcPosition.top;
	m_ptEnd.x=rcPosition.right;
	m_ptEnd.y=rcPosition.bottom;
	dsParentSprite=tcSprite;
	m_psToAttack=psToAttack;
	m_stType=stTESLA;
}

TeslaSprite::~TeslaSprite()
{
}

void TeslaSprite::RandomizeLine()
{
	int ofx,ofy;
	int i;
	for(i=0;i<TESLANODE;i++)
	{
		m_ptLinePos[i].x=m_ptStart.x+(m_ptEnd.x-m_ptStart.x)*i/(TESLANODE-1);
		m_ptLinePos[i].y=m_ptStart.y+(m_ptEnd.y-m_ptStart.y)*i/(TESLANODE-1);
	}
	for(i=1;i<6;i++)
	{
		ofx=rand()%6+2;
		ofy=rand()%6+2;
		if(rand()%2) ofx=-ofx;
		if(rand()%2) ofy=-ofy;
		m_ptLinePos[i].x+=ofx;
		m_ptLinePos[i].y+=ofy;
	}
}

void TeslaSprite::UpdateFrame()
{
	if((m_iFrameDelay>=0)&&(--m_iFrameTrigger<=0))
	{
		m_iFrameTrigger=m_iFrameDelay;
		m_iZOrder=m_ptEnd.y;
		if(m_psToAttack!=NULL&&m_psToAttack->Dying())
			m_psToAttack=NULL;
		else if(m_psToAttack!=NULL&&!m_psToAttack->Dying())
		{
			m_ptEnd=m_psToAttack->GetCenter();
			if(g_iBattleLabCount>0)
				m_psToAttack->Hurt(5);
			else
				m_psToAttack->Hurt(3);
		}

		if(++m_iCurFrame>=m_iNumFrames)
		{
			if(m_bOneCycle)
				m_bDying=TRUE;
		}		
	}
}

void TeslaSprite::Draw(HDC hDC)
{
	int flag=6;
// 
// 	ASSERT((m_ptLinePos[TESLANODE-1].x-m_ptLinePos[0].x)*(m_ptLinePos[TESLANODE-1].x-m_ptLinePos[0].x)
// 		+(m_ptLinePos[TESLANODE-1].y-m_ptLinePos[0].y)*(m_ptLinePos[TESLANODE-1].y-m_ptLinePos[0].y)<40000);

	HPEN oldPen,newPen;
	newPen=CreatePen(1,1,RGB(252,252,252));
	oldPen=(HPEN)SelectObject(hDC,newPen);

	RandomizeLine();

	for(int i=0;i<TESLANODE-1;i++)
	{
		MoveToEx(hDC,m_ptLinePos[i].x,m_ptLinePos[i].y,NULL);
		LineTo(hDC,m_ptLinePos[i+1].x,m_ptLinePos[i+1].y);
	}

	RandomizeLine();

	m_ptLinePos[0].x+=rand()%5-2;
	m_ptLinePos[0].y+=rand()%5-2;
	m_ptLinePos[TESLANODE-1].x+=rand()%9-4;
	m_ptLinePos[TESLANODE-1].y+=rand()%9-4;

	for(int i=0;i<TESLANODE-1;i++)
	{
		MoveToEx(hDC,m_ptLinePos[i].x,m_ptLinePos[i].y,NULL);
		LineTo(hDC,m_ptLinePos[i+1].x,m_ptLinePos[i+1].y);
	}

	DeleteObject(newPen);
	newPen=CreatePen(1,1,RGB(152,152,252));
	SelectObject(hDC,newPen);

	RandomizeLine();

	m_ptLinePos[0].x+=rand()%5-2;
	m_ptLinePos[0].y+=rand()%5-2;
	m_ptLinePos[TESLANODE-1].x+=rand()%9-4;
	m_ptLinePos[TESLANODE-1].y+=rand()%9-4;

	for(int i=0;i<TESLANODE-1;i++)
	{
		MoveToEx(hDC,m_ptLinePos[i].x,m_ptLinePos[i].y,NULL);
		LineTo(hDC,m_ptLinePos[i+1].x,m_ptLinePos[i+1].y);
	}

	SelectObject(hDC,oldPen);
	DeleteObject(newPen);
}