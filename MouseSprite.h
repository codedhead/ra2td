#pragma once

#include "Bitmap.h"
#include "Sprite.h"

enum MouseState
{
	msNORMAL,msFIX,msSELL
};


//做成数组，初始化传名字宏
class MouseSprite:public Sprite
{
protected:
	MouseState m_msState;
	FrameName NNormal,NFix,NSell;
	FrameCount CFix,CSell;
	
public:
	MouseSprite(Bitmap* pBitmap);

	MouseState GetCur(){return m_msState;}
	void SetCur(MouseState msState){m_msState=msState;}
	virtual void Draw(HDC hDC);
	virtual void UpdateFrame();
};

MouseSprite::MouseSprite(Bitmap* pBitmap)
:Sprite(pBitmap)
{
	m_msState=msNORMAL;
	m_iZOrder=80000;
	NNormal=1;
	NSell=2;CSell=10;
	NFix=12;CFix=20;
}

void MouseSprite::UpdateFrame()
{
	if((m_iFrameDelay>=0)&&(--m_iFrameTrigger<=0))
	{
		m_iFrameTrigger=m_iFrameDelay;

		switch(m_msState)
		{
		case msNORMAL:
			m_iCurFrame=NNormal-1;
			break;
		case msFIX:
			m_iCurFrame++;
			if(m_iCurFrame<NFix-1||m_iCurFrame>NFix+CFix-2)
				m_iCurFrame=NFix-1;
			break;
		case msSELL:
			m_iCurFrame++;
			if(m_iCurFrame<NSell-1||m_iCurFrame>NSell+CSell-2)
				m_iCurFrame=NSell-1;
			break;
		}
	}
}

inline void MouseSprite::Draw(HDC hDC)
{
	if(m_pBitmap&&!m_bHidden)
		m_pBitmap->DrawPart(hDC,m_rcPosition.left,m_rcPosition.top,0,m_iCurFrame*GetHeight(),GetWidth(),GetHeight(),TRUE,RGB(0,0,88));
}