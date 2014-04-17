#pragma once

#include "afx.h"
#include "Define.h"

class MenuItemSprite;

#define NUMOFMENUS 8


class MenuSprite
{
protected:
	BOOL m_bWithText[NUMOFMENUS];
	CString m_strText[NUMOFMENUS];
	MenuItemSprite* m_pItemSprite[NUMOFMENUS];
	int m_iCurItem;
	POINT m_pStart;
public:
	MenuFunction m_mfFunc[NUMOFMENUS];
	MenuSprite();
	~MenuSprite();
	void AddItem();
	void ClearItems();
	BOOL IsFull(){return m_iCurItem>=NUMOFMENUS;}
};

