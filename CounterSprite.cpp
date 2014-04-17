#include "countersprite.h"
#include "IcoSprite.h"

extern IcoSprite* g_pIcoSprite[];
extern int g_iMoney;

CounterSprite::CounterSprite(Bitmap* pBitmap,int i)
:Sprite(pBitmap),m_iKind(i)
{
	m_iUsedMoney=0;
	m_stType=stCOUNTER;
	m_iZOrder=20000;
	m_bWarned=FALSE;
}

CounterSprite::~CounterSprite()
{
}

void CounterSprite::Draw(HDC hDC)
{
	HDC hMemDC=CreateCompatibleDC(hDC);
	HDC hMemDC2=CreateCompatibleDC(hMemDC);
	HBITMAP hMemBitmap,hOldBmp,hOldBmp2;

	hOldBmp2=(HBITMAP)SelectObject(hMemDC2,m_pBitmap->GetBitmap());
	
	hMemBitmap=CreateCompatibleBitmap(hDC,GetWidth(),GetHeight());
	hOldBmp=(HBITMAP)SelectObject(hMemDC,hMemBitmap);
	
	TransparentBlt(hMemDC,0,0,GetWidth(),GetHeight(),hMemDC2,0,m_iCurFrame*GetHeight(),GetWidth(),GetHeight(),RGB(252,0,252));
	
	BLENDFUNCTION   blendFunction;   
	blendFunction.BlendFlags=0;   
	blendFunction.BlendOp=AC_SRC_OVER;   
	blendFunction.SourceConstantAlpha=128;   
	blendFunction.AlphaFormat=0; 
	
	AlphaBlend(hDC,m_rcPosition.left,m_rcPosition.top,GetWidth(),
		GetHeight(),hMemDC,0,0,GetWidth(),GetHeight(),blendFunction);
	
	SelectObject(hMemDC,hOldBmp);
	SelectObject(hMemDC2,hOldBmp2);

	DeleteObject(hMemBitmap);
	DeleteDC(hMemDC2);
	DeleteDC(hMemDC);
}

void CounterSprite::UpdateFrame()
{
	if((m_iFrameDelay>=0)&&(--m_iFrameTrigger<=0))
	{
		m_iFrameTrigger=m_iFrameDelay;

		if(g_iMoney<=0)
		{
			if(!m_bWarned)
			{
				m_bWarned=TRUE;
				PlaySound(TEXT("res\\wav\\insufficient funds.wav"),NULL,SND_ASYNC|SND_FILENAME|SND_NOSTOP);
			}
			return;
		}

		g_iMoney+=m_iUsedMoney;
		m_iUsedMoney=g_ciConstructionInfo[m_iKind].Money*(m_iCurFrame+1)/55;
		if(m_iUsedMoney>g_iMoney) m_iUsedMoney=g_iMoney;
		g_iMoney-=m_iUsedMoney;

		m_iCurFrame++;
		if(m_iCurFrame>=m_iNumFrames)
		{
			m_bDying=TRUE;
			g_pIcoSprite[m_iKind]->m_bsState=bsComplete;
			g_dsWavList.PlayBuffer(ConstructionComplete,0);
		}
	}
}
