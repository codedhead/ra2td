#include "personsprite.h"
#include "Define.h"
#include "TargetSprite.h"
#include "ParachuteSprite.h"

extern TargetSprite* g_pNMSSprite;
extern PersonInfo g_piPersonInfo[];

PersonSprite::PersonSprite(Bitmap* pBitmap,int x,int y,KindOfPerson kopKind,ParachuteSprite* pParachute)
:Sprite(pBitmap,x,y),m_kfpKind(kopKind),m_pParachute(pParachute)
{
	m_iNextNode=1;
	m_iTotalVelocity=3+rand()%3;
	m_iHurtVelocity=m_iTotalVelocity-1;
	m_ptCenter.x=(m_rcPosition.left+m_rcPosition.right)/2;
	m_ptCenter.y=(m_rcPosition.top+m_rcPosition.bottom)/2;
	m_iCurHP=m_iTotalHP=100+rand()%25;
	m_iFrameDelay=2;

	m_iOffsexX=5*(rand()%7-3);
	m_iOffsexY=5*(rand()%7-3);

	m_bFalling=FALSE;
	m_stType=stPERSON;
	m_dwDieWay=dwRADIUM;//dwNORMAL;//(DieWay)(rand()%4);//
	m_gsState=gsPathGoal;
// 	SetPosition(Path[0]);
// 	OffsetPosition(rand()%10-5,rand()%10-5);
//	SetBoundsAction(BA_NONE);
}

PersonSprite::~PersonSprite()
{
}

void PersonSprite::Walk(DIRECTION dir)
{
// 	if(m_iWalkDelay++<WALKDELAY) return;
// 	else m_iWalkDelay=0;

	int c=g_piPersonInfo[m_kfpKind].WalkFrame+dir*g_piPersonInfo[m_kfpKind].WalkCount-1;
	m_iCurFrame++;
	if(m_iCurFrame<c||m_iCurFrame>=c+g_piPersonInfo[m_kfpKind].WalkCount)
		m_iCurFrame=c;
}

void PersonSprite::Creep(DIRECTION dir)
{
	int c=g_piPersonInfo[m_kfpKind].CreepFrame+dir*g_piPersonInfo[m_kfpKind].CreepCount-1;
	m_iCurFrame++;
	if(m_iCurFrame<c||m_iCurFrame>=c+g_piPersonInfo[m_kfpKind].CreepCount)
		m_iCurFrame=c;
}

void PersonSprite::Attack(POINT ptToAttack)
{
// 	if(rand()%4==0)
// 	{
// 		Stop(DIRECTIOc x cccv cvN(rand()%8));
// 		return;
// 	}
	int signx=SIGN(ptToAttack.x-m_ptCenter.x);
	int signy=SIGN(ptToAttack.y-m_ptCenter.y);
	int dir;
	if(signx>0)
	{
		if(signy>0)
			dir=RIGHTDOWN;
		else if(signy=0)
			dir=RIGHT;
		else
			dir=RIGHTUP;
	}
	else if(signx==0)
	{
		if(signy<0)
			dir=UP;
		else
			dir=DOWN;
	}
	else
	{
		if(signy>0)
			dir=LEFTDOWN;
		else if(signy=0)
			dir=LEFT;
		else
			dir=LEFTUP;
	}

	int c=g_piPersonInfo[m_kfpKind].AttackFrame+dir*g_piPersonInfo[m_kfpKind].AttackCount-1;
	m_iCurFrame++;
	if(m_iCurFrame<c)
		m_iCurFrame=c;
	else if(m_iCurFrame>=c+g_piPersonInfo[m_kfpKind].AttackCount-1)
	{
		m_iCurFrame=c;
		g_pNMSSprite->Destroy(1);

		switch(m_kfpKind)
		{
		case ROCKETEER:
		case LAND_ROCKETEER:
			g_dsWavList.PlayBuffer(AtRocketeer,0);
			break;
		case TESLA_TROOPER:
			g_dsWavList.PlayBuffer(AtTesla,0);
			break;
		default:
			g_dsWavList.PlayBuffer(AtGun1+rand()%5,0);
			break;
		}
	}
}

void PersonSprite::Stop(DIRECTION dir)
{
	m_iCurFrame=g_piPersonInfo[m_kfpKind].StandFrame+dir*g_piPersonInfo[m_kfpKind].StandCount;
	m_ptVelocity.x=m_ptVelocity.y=0;
}

void PersonSprite::Die()
{
	m_iCurFrame++;
	if(m_iCurFrame<g_piPersonInfo[m_kfpKind].DieFrame)		
		m_iCurFrame=g_piPersonInfo[m_kfpKind].DieFrame;
	else if(m_iCurFrame>=g_piPersonInfo[m_kfpKind].DieFrame+g_piPersonInfo[m_kfpKind].DieCount-1)
	{
		m_iCurFrame--,m_bDying=TRUE;
		if(m_pParachute!=NULL)
			m_pParachute->Kill();
	}
}

void PersonSprite::SetPosition(int x,int y)
{
	OffsetRect(&m_rcPosition,x-m_ptCenter.x,y-m_ptCenter.y);
// 	m_ptCenter.x=x;m_ptCenter.y=y;
// 	SetRect(&m_rcPosition,x-GetWidth()/2,x+GetWidth()/2,y-)
// 	m_rcPosition.left=GetWidth()/2
	CalcCollisionRect();
}


void PersonSprite::UpdateFrame()
{
	if((m_iFrameDelay>=0)&&(--m_iFrameTrigger<=0))
	{
	/*	static DIRECTION olddir=RIGHTDOWN;*/
		m_iFrameTrigger=m_iFrameDelay;

		if(m_iCurHP<=0)
		{
			m_ptVelocity.x=m_ptVelocity.y=0;
			if(m_dwDieWay!=dwNORMAL)
			{
				m_bDying=TRUE;
				if(m_pParachute!=NULL)
					m_pParachute->Kill();
				return;
			}
			Die();
			return;
		}

		if(m_bFalling)
		{
			m_iCurFrame=g_piPersonInfo[m_kfpKind].FallingFrame-1;
			return;
		}

		if(m_gsState==gsNoGoal)
		{
		//	Stop(olddir);
			return;
		}

		if(m_iNextNode>=g_iPathLength)
		{
			/*Attack(olddir);*/
			m_gsState=gsNoGoal;
			return;
		}

		m_iZOrder=m_ptCenter.y;
		
		POINT CurPos,NextPos;
		
		CurPos.x=m_ptCenter.x;CurPos.y=m_ptCenter.y;
		NextPos=Path[m_iNextNode];

// 		NextPos.x+=5*(rand()%5-2);
// 		NextPos.y+=5*(rand()%5-2);
		NextPos.x+=m_iOffsexX;
		NextPos.y+=m_iOffsexY;
		if((CurPos.x-NextPos.x)*(CurPos.x-NextPos.x)+(CurPos.y-NextPos.y)*(CurPos.y-NextPos.y)
			<=m_iTotalVelocity*m_iTotalVelocity)
		{
			m_iNextNode++;
			if(m_iNextNode>=g_iPathLength) 
			{	
				//m_iNextNode--;
				m_ptVelocity.x=m_ptVelocity.y=0;
				return;
			}
			
		}
		NextPos=Path[m_iNextNode];
		NextPos.x+=m_iOffsexX;
		NextPos.y+=m_iOffsexY;
		{
			float disx=NextPos.x-CurPos.x;
			float disy=NextPos.y-CurPos.y;
			float dis=disx*disx+disy*disy;
			int signx=SIGN(disx);
			int signy=SIGN(disy);
			m_ptVelocity.x=signx*sqrt(disx*disx/dis)*m_iTotalVelocity;
			m_ptVelocity.y=signy*sqrt(disy*disy/dis)*m_iTotalVelocity;
			
			
			if(signx==0)
			{
				if(signy==1)
					olddir=DOWN;
				else//include 0
					olddir=UP;
			}
			else if(signx==1)
			{
				if(signy==0)
					olddir=RIGHT;
				else if(signy==-1)
					olddir=RIGHTUP;
				else if(signy==1)
					olddir=RIGHTDOWN;
			}
			else
			{
				if(signy==0)
					olddir=LEFT;
				else if(signy==-1)
					olddir=LEFTUP;
				else if(signy==1)
					olddir=LEFTDOWN;
			}		
		}
		if(m_iCurHP<=30&&g_piPersonInfo[m_kfpKind].CreepFrame!=0)
		{
			Creep(olddir);
			m_iTotalVelocity=m_iHurtVelocity;
		}
		else
			Walk(olddir);
	}
	
}

void PersonSprite::Draw(HDC hDC)
{
	if(m_pBitmap&&!m_bHidden)
		m_pBitmap->DrawPart(hDC,m_rcPosition.left,m_rcPosition.top,0,m_iCurFrame*GetHeight(),GetWidth(),GetHeight(),TRUE,RGB(0,0,252));
	
// 	HBRUSH hbr=CreateSolidBrush(RGB(0,252,0));
// 	FrameRect(hDC,&m_rcCollision,hbr);
// 	SetPixel(hDC,m_ptCenter.x-1,m_ptCenter.y-1,RGB(252,0,0));
// 	SetPixel(hDC,m_ptCenter.x-1,m_ptCenter.y,RGB(252,0,0));
// 	SetPixel(hDC,m_ptCenter.x-1,m_ptCenter.y+1,RGB(252,0,0));
// 	SetPixel(hDC,m_ptCenter.x,m_ptCenter.y-1,RGB(252,0,0));
// 	SetPixel(hDC,m_ptCenter.x,m_ptCenter.y,RGB(252,0,0));
// 	SetPixel(hDC,m_ptCenter.x,m_ptCenter.y+1,RGB(252,0,0));
// 	SetPixel(hDC,m_ptCenter.x+1,m_ptCenter.y-1,RGB(252,0,0));
// 	SetPixel(hDC,m_ptCenter.x+1,m_ptCenter.y,RGB(252,0,0));
// 	SetPixel(hDC,m_ptCenter.x+1,m_ptCenter.y+1,RGB(252,0,0));
// 	DeleteObject(hbr);
}

void PersonSprite::CalcCollisionRect()
{
 	m_ptCenter.x=(m_rcPosition.left+m_rcPosition.right)/2;
 	m_ptCenter.y=(m_rcPosition.top+m_rcPosition.bottom)/2;

	m_rcCollision.left=m_ptCenter.x-10;
	m_rcCollision.right=m_ptCenter.x+10;
	m_rcCollision.top=m_ptCenter.y-10;
	m_rcCollision.bottom=m_ptCenter.y+10;
}