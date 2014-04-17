#pragma once

#include "afx.h"

#include "bitmap.h"

class Background
{
protected:
	int m_iWidth,m_iHeight;
	COLORREF m_crColor;
	Bitmap* m_pBitmap;

public:
	Background(int iWidth,int iHeight,COLORREF crColor);
	Background(Bitmap* pBitmap);
	virtual ~Background();

	virtual void Update();
	virtual void Draw(HDC hDC);

	int GetWidth(){return m_iWidth;}
	int GetHeight(){return m_iHeight;}
};
