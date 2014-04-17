#pragma once
#include "afx.h"

#include "Bitmap.h"
#include "Sprite.h"


extern HINSTANCE g_hInstance;

class CounterSprite:public Sprite
{
protected:
	BOOL m_bWarned;
	
public:
	int m_iKind;
	int m_iUsedMoney;
	CounterSprite(Bitmap* pBitmap,int i);
	virtual ~CounterSprite();
	
	virtual void UpdateFrame();
	virtual void Draw(HDC hDC);
};