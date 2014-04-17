#pragma once
#include "afx.h"

#include "Define.h"
#include "Bitmap.h"
#include "Sprite.h"
#include "PersonSprite.h"

class DefendSprite;

class TeslaSprite:public Sprite
{
protected:
	POINT m_ptStart,m_ptEnd;
	POINT m_ptLinePos[TESLANODE];
	PersonSprite* m_psToAttack;
	void RandomizeLine();
public:
	DefendSprite* dsParentSprite;
	TeslaSprite(RECT& rcPosition,DefendSprite* tcSprite,PersonSprite* psToAttack);
	virtual ~TeslaSprite();
	
	virtual void UpdateFrame();
	virtual void Draw(HDC hDC);
};

