#include "ParachuteSprite.h"
#include "PersonSprite.h"
#include "PlaneSprite.h"

ParachuteSprite::ParachuteSprite(PlaneSprite* pTakingPlane,PersonSprite* pHoldingPerson,int iTotalDis)
:Sprite(g_pParachuteBitmap),m_iTotalDis(iTotalDis),m_pHoldingPerson(pHoldingPerson),m_pTakingPlane(pTakingPlane)
{
	m_iCurDis=0;
	m_iFallingV=5;
	m_iNextNode=pTakingPlane->m_iNextNode;
	/*	SetPosition(ptStart);*/
}

void ParachuteSprite::ContinuFall()
{		
	m_iCurFrame++;
	if(m_iCurFrame<FALLING||m_iCurFrame>=CLOSE)
		m_iCurFrame=FALLING;
}

void ParachuteSprite::UpdateFrame()
{
	if(m_iCurFrame>=m_iNumFrames)
	{
		m_bDying=TRUE;
		return;
	}
	m_iCurFrame++;
	if(m_iCurFrame==2)
	{
		if(m_pTakingPlane->m_iParaNum<8)
		{			
			int j;
			while((j=rand()%((int)TESLA_TROOPER+1))==EVAN);
			PersonSprite* pHolding=new PersonSprite(g_pPersonBitmap[j],m_pTakingPlane->m_ptPR[m_pTakingPlane->m_iParaNum].x-GetWidth()/2+9,m_pTakingPlane->m_ptPR[m_pTakingPlane->m_iParaNum].y-GetHeight()/2+66,(KindOfPerson)j);
			pHolding->SetNumFrames(g_piPersonInfo[j].NumFrames);
			pHolding->SetFalling(TRUE);
			g_pGame->AddSprite(pHolding);
			
			ParachuteSprite* paraSprite=new ParachuteSprite(m_pTakingPlane,pHolding,m_pTakingPlane->m_ptToRelease.y-m_pTakingPlane->m_ptPR[m_pTakingPlane->m_iParaNum-1].y);
			paraSprite->SetNumFrames(70);
			paraSprite->SetPosition(m_pTakingPlane->m_ptPR[m_pTakingPlane->m_iParaNum].x-GetWidth()/2,m_pTakingPlane->m_ptPR[m_pTakingPlane->m_iParaNum].y-GetHeight()/2);
			g_pGame->AddSprite(paraSprite);
			m_pTakingPlane->m_iParaNum++;
		}
	}
	
	if(m_iTotalDis-m_iCurDis>m_iFallingV)
	{
		m_pHoldingPerson->OffsetPosition(0,m_iFallingV);
		OffsetPosition(0,m_iFallingV);
		m_iCurDis+=m_iFallingV;
		if(m_iCurFrame>=FALLING-1)
			ContinuFall();
	}
	else
	{
		m_pHoldingPerson->SetFalling(FALSE);
		m_pHoldingPerson->SetNextNode(m_iNextNode);
		if(m_iCurFrame<CLOSE-1)
			m_iCurFrame=CLOSE-1;
	}
}

inline void ParachuteSprite::Draw(HDC hDC)
{
	if(m_pBitmap&&!m_bHidden)
	{
		m_pBitmap->DrawPart(hDC,m_rcPosition.left,m_rcPosition.top,0,m_iCurFrame*GetHeight(),GetWidth(),GetHeight(),TRUE,RGB(0,0,252));
	}	
}