#pragma once
#include "afx.h"
#include "Bitmap.h"
#include "Sprite.h"

class MenuSprite;

class MenuItemSprite:public Sprite
{
protected:
	int m_bWithText;
	
	MenuSprite* m_pMenu;
public:
	MenuFunction m_mfFunc;
	CString m_strText;
	MenuItemSprite(MenuSprite* pMenu,BOOL bWithText,CString strText,MenuFunction mfFunc);
	virtual ~MenuItemSprite();
	
	virtual void UpdateFrame();
	virtual void Draw(HDC hDC);
};
