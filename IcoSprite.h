#pragma once
#include "afx.h"
#include "Bitmap.h"
#include "Sprite.h"
#include "CounterSprite.h"


extern HINSTANCE g_hInstance;

class IcoSprite:public Sprite
{
public:
	KindOfCon m_kfcKind;
	CounterSprite* m_csCounter;
	BuildingState m_bsState;
	IcoSprite(Bitmap* pBitmap,KindOfCon kfcKind);
	virtual ~IcoSprite();
	virtual void Draw(HDC hDC);
	void SetCounter(CounterSprite* csCounter){m_csCounter=csCounter;}
	virtual void CalcCollisionRect();
};

