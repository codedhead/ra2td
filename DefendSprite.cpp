#include "DefendSprite.h"
#include "TeslaSprite.h"
#include "PrismSprite.h"
#include "GameEngine.h"
#include "Define.h"

extern int g_iBattleLabCount;
extern ConstructionInfo g_ciConstructionInfo[];

extern HINSTANCE g_hInstance;
extern GameEngine* g_pGame;
extern BOOL g_bLowPower;
extern int g_iMoney;

DefendSprite::DefendSprite(Bitmap* pBitmap,KindOfCon kfcKind,POINT ptLeft,POINT ptRight)
:ConstructionSprite(pBitmap,kfcKind,ptLeft,ptRight)
{
	m_dsState=DS_WAIT;
	m_stType=stDEFEND;
	switch(kfcKind)
	{
	case TESLA_COIL:
	//	m_iAttackTrigger=m_iAttackDelay=0;
		m_iAttackArea=2;
		break;
	case PRISM_TOWER:
		m_iAttackArea=1;
		break;
	case SENTRY_GUN:
		m_iAttackTrigger=m_iAttackDelay=3;
		m_iAttackArea=1;
		break;
	case PILL_BOX:
		m_iAttackTrigger=m_iAttackDelay=5;
		m_iAttackArea=1;
		break;
	}
}

DefendSprite::~DefendSprite()
{
}

void DefendSprite::CalcCollisionRect()
{
	int w=g_ciConstructionInfo[m_kfcKind].BottomWidth;
	int l=g_ciConstructionInfo[m_kfcKind].BottomLength;
	int rux,ruy,rdx,rdy,ldx,ldy,lux,luy;
	rux=m_ptLeft.x-m_iAttackArea;ruy=m_ptLeft.y-m_iAttackArea;
	rdx=m_ptLeft.x+l+m_iAttackArea;rdy=ruy;
	ldx=m_ptRight.x+m_iAttackArea;ldy=m_ptRight.y+m_iAttackArea;
	lux=m_ptRight.x-l-m_iAttackArea;luy=ldy;

	SetRect(&m_rcCollision,30*(lux-luy),15*(rux+ruy),30*(rdx-rdy),15*(ldx+ldy));
}

void DefendSprite::GetReady()
{
	m_iCurFrame=g_ciConstructionInfo[m_kfcKind].AttackFrame-1;
	m_dsState=DS_READY;
}

void DefendSprite::Work()
{
	m_iCurFrame=g_ciConstructionInfo[m_kfcKind].WorkFrame-1;
	m_dsState=DS_WAIT;	
}

void DefendSprite::Recover()
{
	if(m_kfcKind==PRISM_TOWER)
	{
		m_iCurFrame++;
		if(m_iCurFrame<g_ciConstructionInfo[m_kfcKind].WorkFrame-1||
			m_iCurFrame>=g_ciConstructionInfo[m_kfcKind].AttackFrame-1)
			m_iCurFrame=g_ciConstructionInfo[m_kfcKind].WorkFrame-1;
	}

}

void DefendSprite::UpdateFrame()
{
	if((m_iFrameDelay>=0)&&(--m_iFrameTrigger<=0))
	{
		m_iFrameTrigger=m_iFrameDelay;
// 
// 		if(m_bSelling)
// 		{
// 			m_iCurFrame--;
// 			if(m_iCurFrame>g_ciConstructionInfo[m_kfcKind].WorkFrame-1)
// 				m_iCurFrame=g_ciConstructionInfo[m_kfcKind].WorkFrame-1;
// 			else if(m_iCurFrame<0)
// 				m_bDying=TRUE;
// 			
// 			return;
// 		}

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

		if(g_bLowPower&&(m_kfcKind==TESLA_COIL||m_kfcKind==PRISM_TOWER))
		{
			m_iCurFrame=g_ciConstructionInfo[m_kfcKind].WorkFrame-2;
			return;
		}
		
		if(m_dsState==DS_ATTACK)
		{
			Recover();
			return;
		}

		m_iCurFrame++;
		if(m_dsState==DS_WAIT&&m_iCurFrame==g_ciConstructionInfo[m_kfcKind].AttackFrame)
			m_iCurFrame=g_ciConstructionInfo[m_kfcKind].WorkFrame-1;
		else if(m_dsState==DS_READY&&m_iCurFrame==m_iNumFrames)
		{
			m_iCurFrame=g_ciConstructionInfo[m_kfcKind].WorkFrame-2;

			if(m_psToAttack->Dying()||m_psToAttack->m_bFalling)
			{
				Work();
				return;
			}
			switch(m_kfcKind)
			{
			case TESLA_COIL:
				{
				POINT pt=m_psToAttack->GetCenter();
				
				RECT rcPosition={m_ptBottomCenter.x,m_ptBottomCenter.y-55,pt.x,pt.y};
				TeslaSprite* pSprite=new TeslaSprite(rcPosition,this,m_psToAttack);
				pSprite->SetNumFrames(16,TRUE);
				g_pGame->AddSprite(pSprite);
			/*	PlaySound(TEXT("res\\wav\\TeslaAt1.wav"),NULL,SND_FILENAME|SND_ASYNC);*/
				g_dsWavList.PlayBuffer(TeslaAt1,0);
				m_dsState=DS_ATTACK;
				break;
				}
			case PRISM_TOWER:
				{				
					POINT pt=m_psToAttack->GetCenter();
					
					RECT rcPosition={m_ptBottomCenter.x,m_ptBottomCenter.y-62,pt.x,pt.y};
					PrismSprite* pSprite=new PrismSprite(rcPosition,this,m_psToAttack);
					pSprite->SetNumFrames(8,TRUE);
					g_pGame->AddSprite(pSprite);
				/*	PlaySound(TEXT("res\\wav\\PrismAt.wav"),NULL,SND_FILENAME|SND_ASYNC);*/
					g_dsWavList.PlayBuffer(PrismAt,0);
					m_dsState=DS_ATTACK;
					break;
				}
			case PILL_BOX:
			/*	m_dsState=DS_ATTACK;*/
				if(--m_iAttackTrigger<=0)
					m_iAttackTrigger=m_iAttackDelay;
				else break;
				if(g_iBattleLabCount>0)
					m_psToAttack->Hurt(25);
				else
					m_psToAttack->Hurt(20);

				g_dsWavList.PlayBuffer(PillAt1,0);
				m_dsState=DS_WAIT;
				break;
			case SENTRY_GUN:
				/*m_dsState=DS_ATTACK;*/
				if(--m_iAttackTrigger<=0)
					m_iAttackTrigger=m_iAttackDelay;
				else break;
				if(g_iBattleLabCount>0)
					m_psToAttack->Hurt(20);
				else
					m_psToAttack->Hurt(15);

				g_dsWavList.PlayBuffer(SentryAt3,0);
				m_dsState=DS_WAIT;
				break;
			}				
		}
	}
}

void DefendSprite::Draw(HDC hDC)
{
	if(m_pBitmap&&!m_bHidden)
		m_pBitmap->DrawPart(hDC,m_rcPosition.left,m_rcPosition.top,0,m_iCurFrame*GetHeight(),GetWidth(),GetHeight(),TRUE,RGB(0,0,252));
	
// 	RECT rc={m_ptCenter.x-90,m_ptCenter.x-45,m_ptCenter.x+90,m_ptCenter.x+45};
// 	HBRUSH hbr=CreateSolidBrush(RGB(0,252,0));
//	FrameRect(hDC,&rc,hbr);
// 	FrameRect(hDC,&m_rcCollision,hbr);
// 	FrameRect(hDC,&m_rcMouseNotify,hbr);
// 	SetPixel(hDC,m_ptBottomCenter.x-1,m_ptCenter.y-1,RGB(0,0,0));
// 	SetPixel(hDC,m_ptCenter.x-1,m_ptCenter.y,RGB(0,0,0));
// 	SetPixel(hDC,m_ptCenter.x-1,m_ptCenter.y+1,RGB(0,0,0));
// 	SetPixel(hDC,m_ptCenter.x,m_ptCenter.y-1,RGB(0,0,0));
// 	SetPixel(hDC,m_ptCenter.x,m_ptCenter.y,RGB(0,0,0));
// 	SetPixel(hDC,m_ptCenter.x,m_ptCenter.y+1,RGB(0,0,0));
// 	SetPixel(hDC,m_ptCenter.x+1,m_ptCenter.y-1,RGB(0,0,0));
// 	SetPixel(hDC,m_ptCenter.x+1,m_ptCenter.y,RGB(0,0,0));
// 	SetPixel(hDC,m_ptCenter.x+1,m_ptCenter.y+1,RGB(0,0,0));
// 	SetPixel(hDC,m_ptBottomCenter.x-1,m_ptBottomCenter.y-1,RGB(0,0,0));
// 	SetPixel(hDC,m_ptBottomCenter.x-1,m_ptBottomCenter.y,RGB(0,0,0));
// 	SetPixel(hDC,m_ptBottomCenter.x-1,m_ptBottomCenter.y+1,RGB(0,0,0));
// 	SetPixel(hDC,m_ptBottomCenter.x,m_ptBottomCenter.y-1,RGB(0,0,0));
// 	SetPixel(hDC,m_ptBottomCenter.x,m_ptBottomCenter.y,RGB(0,0,0));
// 	SetPixel(hDC,m_ptBottomCenter.x,m_ptBottomCenter.y+1,RGB(0,0,0));
// 	SetPixel(hDC,m_ptBottomCenter.x+1,m_ptBottomCenter.y-1,RGB(0,0,0));
// 	SetPixel(hDC,m_ptBottomCenter.x+1,m_ptBottomCenter.y,RGB(0,0,0));
// 	SetPixel(hDC,m_ptBottomCenter.x+1,m_ptBottomCenter.y+1,RGB(0,0,0));
// 
// 	DeleteObject(hbr);
// 
// 
// 	HPEN oldPen,newPen;
// 	int rux,rdx,lux,ldx;
// 	int ruy,rdy,luy,ldy;
// 	int w=g_ciConstructionInfo[m_kfcKind].BottomWidth;
// 	int l=g_ciConstructionInfo[m_kfcKind].BottomLength;
// 	
// 	rux=m_ptLeft.x-m_iAttackArea;ruy=m_ptLeft.y-m_iAttackArea;
// 	rdx=m_ptLeft.x+l+m_iAttackArea;rdy=ruy;
// 	ldx=m_ptRight.x+m_iAttackArea;ldy=m_ptRight.y+m_iAttackArea;
// 	lux=m_ptRight.x-l-m_iAttackArea;luy=ldy;
// 	
// 	newPen=CreatePen(1,2,RGB(0,255,0));
// 	oldPen=(HPEN)SelectObject(hDC,newPen);
// 	
// 	MoveToEx(hDC,30*(lux-luy),15*(lux+luy),NULL);
// 	LineTo(hDC,30*(rux-ruy),15*(rux+ruy));
// 	LineTo(hDC,30*(rdx-rdy),15*(rdx+rdy));
// 	LineTo(hDC,30*(ldx-ldy),15*(ldx+ldy));
// 	LineTo(hDC,30*(lux-luy),15*(lux+luy));
// 	
// 	SelectObject(hDC,oldPen);
// 	DeleteObject(newPen);
}