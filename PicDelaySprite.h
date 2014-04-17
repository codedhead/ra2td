#pragma once


#include "Bitmap.h"
#include "Sprite.h"

class PicDelaySprite:public Sprite
{
protected:
	int m_iShowDelay;
	int m_iShowTrigger;
public:
	PicDelaySprite(Bitmap* pBitmap,int iShowDelay);
	
	virtual void UpdateFrame();
};

PicDelaySprite::PicDelaySprite(Bitmap* pBitmap,int iShowDelay)
:Sprite(pBitmap),m_iShowDelay(iShowDelay)
{
	m_iShowTrigger=m_iShowDelay;
	m_iZOrder=90000;
}

inline void PicDelaySprite::UpdateFrame()
{
	if(--m_iShowTrigger<0)
		m_bDying=TRUE;
}