#include "afxwin.h"
#include "menuitemsprite.h"
#include "MenuSprite.h"



extern Bitmap* g_pMenuTextBitmap;
extern Bitmap* g_pMenuNullBitmap;

MenuItemSprite::MenuItemSprite(MenuSprite* pMenu,BOOL bWithText,CString strText,MenuFunction mfFunc)
:Sprite(bWithText?g_pMenuTextBitmap:g_pMenuNullBitmap),m_bWithText(bWithText),m_strText(strText),m_pMenu(pMenu),m_mfFunc(mfFunc)
{
	if(bWithText)
		m_stType=stMENUITEM;
	if(bWithText)
		SetNumFrames(10);
 	else 
		SetNumFrames(7);
}

MenuItemSprite::~MenuItemSprite(){}

void MenuItemSprite::UpdateFrame()
{
	if((m_iFrameDelay>=0)&&(--m_iFrameTrigger<=0))
	{
		m_iFrameTrigger=m_iFrameDelay;
		m_iCurFrame++;
		if(m_iCurFrame==2&&!m_pMenu->IsFull())
			m_pMenu->AddItem();
		else if(m_iCurFrame>=7+m_bWithText)
			m_iCurFrame--;
	}
	
}

void MenuItemSprite::Draw(HDC hDC)
{
	if(m_pBitmap&&!m_bHidden)
	{
		m_pBitmap->DrawPart(hDC,m_rcPosition.left,m_rcPosition.top,0,m_iCurFrame*GetHeight(),GetWidth(),GetHeight(),FALSE);
		if(m_iCurFrame==7&&m_bWithText)
		{
			int oldMode;
			COLORREF oldColor;
			CFont cf;
			cf.CreateFont(
				19,                        // nHeight
				0,                         // nWidth
				0,                         // nEscapement
				0,                         // nOrientation
				FW_NORMAL,                 // nWeight
				FALSE,                     // bItalic
				FALSE,                     // bUnderline
				0,                         // cStrikeOut
				ANSI_CHARSET,              // nCharSet
				OUT_DEFAULT_PRECIS,        // nOutPrecision
				CLIP_DEFAULT_PRECIS,       // nClipPrecision
				DEFAULT_QUALITY,           // nQuality
				DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
				"ËÎÌו"); 

			HFONT oldFont=(HFONT)SelectObject(hDC,cf.m_hObject);

			oldColor=SetTextColor(hDC,RGB(252,252,56));
			oldMode=SetBkMode(hDC,TRANSPARENT);
			RECT rt=m_rcPosition;
			rt.left-=4;rt.right-=4;
			rt.top++;rt.bottom++;
			DrawText(hDC,m_strText,-1,&rt,DT_CENTER|DT_SINGLELINE|DT_VCENTER);
			
			SelectObject(hDC,oldFont);
			cf.DeleteObject();
			SetTextColor(hDC,oldColor);
			SetBkMode(hDC,oldMode);
		}
	}
}