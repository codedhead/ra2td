#pragma once

#include "afx.h"
#include "sprite.h"

class ChronoSprite:public Sprite
{
protected:
	int m_iSection;
public:
	ChronoSprite(Bitmap* pBitmap,int iSection);
	virtual void UpdateFrame();
};

