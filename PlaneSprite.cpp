#include "planesprite.h"
#include "GameEngine.h"
#include "ParachuteSprite.h"
#include "PersonSprite.h"

#include "math.h"
extern GameEngine* g_pGame;
// extern POINT g_ptPR[8];
// extern int g_iParaNum;

PlaneSprite::PlaneSprite(Bitmap* pBitmap,POINT ptToRelease)
:Sprite(pBitmap),m_ptToRelease(ptToRelease)
{
	int y=rand()%600;
	float rate;

	m_iZOrder=1500;

	m_bNotYet=TRUE;

	m_iParaNum=0;
	
	m_ptToRelease=ptToRelease;
	
	m_iNumFrames=2;
	RECT rect=GetPosition();
	rect.bottom=rect.top+(rect.bottom-rect.top)/2;
	SetPosition(rect);
	
	SetPosition(-GetWidth(),y);
	
	m_ptV.x=7;
	rate=(m_ptToRelease.y-200.0-y-GetHeight()/2.0)/(m_ptToRelease.x+GetWidth()/2.0);
	if(rate<0)
	{
		m_ptV.y=-ceil(-rate*m_ptV.x);
		m_iCurFrame++;
	}
	else
		m_ptV.y=floor(rate*m_ptV.x); 
}

void PlaneSprite::UpdateFrame()
{

	if(m_rcPosition.left>856||m_rcPosition.bottom<0||m_rcPosition.top>630)
		g_dsWavList.StopBuffer(PlaneOver);
	
	if(m_rcPosition.left>856)
	{
		m_bDying=TRUE;
		return;
	}

	
	
	OffsetPosition(m_ptV.x,m_ptV.y);
	if(abs((m_rcPosition.left+m_rcPosition.right)/2-m_ptToRelease.x)<4&&m_bNotYet)			
	{
		m_bNotYet=FALSE;
		for(int i=0;i<8;i++)
		{
			m_ptPR[i].x=m_ptToRelease.x+(rand()%8-3)*3;
			m_ptPR[i].y=(m_rcPosition.top+m_rcPosition.bottom)/2+10;//+(rand()%8-3)*5;	
		}
		
		int j;
		while((j=rand()%((int)TESLA_TROOPER+1))==EVAN);
		PersonSprite* pHolding=new PersonSprite(g_pPersonBitmap[j],m_ptPR[0].x-102/2+9,m_ptPR[0].y-186/2+66,(KindOfPerson)j);
		pHolding->SetNumFrames(g_piPersonInfo[j].NumFrames);
		pHolding->SetFalling(TRUE);
		g_pGame->AddSprite(pHolding);
		
		ParachuteSprite* paraSprite=new ParachuteSprite(this,pHolding,m_ptToRelease.y-m_ptPR[0].y);
		paraSprite->SetNumFrames(70);
		paraSprite->SetPosition(m_ptPR[0].x-102/2,m_ptPR[0].y-186/2);
		g_pGame->AddSprite(paraSprite);
		m_iParaNum=1;
	}
	
	
}

void PlaneSprite::Draw(HDC hDC)
{
	if(m_pBitmap&&!m_bHidden)
	{
		m_pBitmap->DrawPart(hDC,m_rcPosition.left,m_rcPosition.top,0,m_iCurFrame*GetHeight(),GetWidth(),GetHeight(),TRUE,RGB(140,170,235));
		
// 		SetPixel(hDC,m_ptToRelease.x-1,m_ptToRelease.y-1,RGB(252,0,0));
// 		SetPixel(hDC,m_ptToRelease.x-1,m_ptToRelease.y,RGB(252,0,0));
// 		SetPixel(hDC,m_ptToRelease.x-1,m_ptToRelease.y+1,RGB(252,0,0));
// 		SetPixel(hDC,m_ptToRelease.x,m_ptToRelease.y-1,RGB(252,0,0));
// 		SetPixel(hDC,m_ptToRelease.x,m_ptToRelease.y,RGB(252,0,0));
// 		SetPixel(hDC,m_ptToRelease.x,m_ptToRelease.y+1,RGB(252,0,0));
// 		SetPixel(hDC,m_ptToRelease.x+1,m_ptToRelease.y-1,RGB(252,0,0));
// 		SetPixel(hDC,m_ptToRelease.x+1,m_ptToRelease.y,RGB(252,0,0));
// 		SetPixel(hDC,m_ptToRelease.x+1,m_ptToRelease.y+1,RGB(252,0,0));
	}	
}