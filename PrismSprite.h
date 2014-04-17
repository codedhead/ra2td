#pragma once
#include "afx.h"

#include "Define.h"
#include "Bitmap.h"
#include "Sprite.h"
#include "PersonSprite.h"

class DefendSprite;

class PrismSprite:public Sprite
{
protected:
	POINT m_ptStart,m_ptEnd;
	POINT m_ptLinePos[TESLANODE];
	PersonSprite* m_psToAttack;
public:
	DefendSprite* dsParentSprite;
	PrismSprite(RECT& rcPosition,DefendSprite* tcSprite,PersonSprite* psToAttack);
	virtual ~PrismSprite();
	
	virtual void UpdateFrame();
	virtual void Draw(HDC hDC);
};
