#pragma once

#include "sprite.h"

class DieAshSprite:public Sprite
{
protected:
	int m_iKillCount;
public:
	DieAshSprite(Bitmap* pBitmap,int x,int y,DIRECTION dir);
	virtual void UpdateFrame();
};


DieAshSprite::DieAshSprite(Bitmap* pBitmap,int x,int y,DIRECTION dir)
:Sprite(pBitmap,x,y)
{
	m_iKillCount=2;
	switch(dir)
	{
	case UP:
	case LEFTUP:
		m_iCurFrame=0;
		break;
	case LEFT:
		m_iCurFrame=2;
		break;
	case LEFTDOWN:
		m_iCurFrame=4;
		break;
	case DOWN:
	case RIGHTDOWN:
		m_iCurFrame=6;
		break;
	case RIGHT:
		m_iCurFrame=8;
		break;
	case RIGHTUP:
		m_iCurFrame=10;
		break;
	}
}

inline void DieAshSprite::UpdateFrame()
{	
	if((m_iFrameDelay>=0)&&(--m_iFrameTrigger<=0))
	{
		m_iFrameTrigger=m_iFrameDelay;
		if(--m_iKillCount<0)
		{
			m_bDying=TRUE;
			return;
		}
		m_iCurFrame++;
	}
}
