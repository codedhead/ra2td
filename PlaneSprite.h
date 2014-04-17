#pragma once

#include "afx.h"
#include "sprite.h"

class PlaneSprite:public Sprite
{
protected:
/*	int m_iSection;*/
	POINT m_ptV;
	
	BOOL m_bNotYet;

	
public:
	POINT m_ptToRelease;
	POINT m_ptPR[8];
	int m_iParaNum;
	int m_iNextNode;
	
	PlaneSprite(Bitmap* pBitmap,POINT ptToRelease);
	virtual void UpdateFrame();
	virtual void Draw(HDC hDC);
	void SetNextNode(int iNextNode){m_iNextNode=iNextNode;}
};
