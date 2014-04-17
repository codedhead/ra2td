#pragma once

#include "sprite.h"

class PadButtonSprite:public Sprite
{
public:
	PadButtonSprite(Bitmap* pBitmap,SpriteType stType);
	void Click(){m_iCurFrame=!m_iCurFrame;}
	void Click(int iFrame){m_iCurFrame=iFrame;}
	virtual void UpdateFrame();
};


PadButtonSprite::PadButtonSprite(Bitmap* pBitmap,SpriteType stType)
:Sprite(pBitmap)
{
	m_stType=stType;
	m_iZOrder=10000;
}

inline void PadButtonSprite::UpdateFrame()
{	
}
