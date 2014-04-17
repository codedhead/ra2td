#include "afxwin.h"
#include "background.h"
extern HWND g_hWnd;
extern POINT left,right;

Background::Background(int iWidth,int iHeight,COLORREF crColor)
{
	m_iWidth=iWidth;
	m_iHeight=iHeight;
	m_crColor=crColor;
	m_pBitmap=NULL;
}

Background::Background(Bitmap* pBitmap)
{
	m_crColor=0;
	m_pBitmap=pBitmap;
	m_iWidth=pBitmap->GetWidth();
	m_iHeight=pBitmap->GetHeight();
}

Background::~Background(){}

void Background::Update(){}

void Background::Draw(HDC hDC)
{
	if(m_pBitmap)
	{
		m_pBitmap->Draw(hDC,0,0,TRUE);

// 		for(int i=0;i<15;i++)
// 		{
// // 			MoveToEx(hDC,i*60,0,NULL);
// // 			LineTo(hDC,840,420-i*30);
// // 			MoveToEx(hDC,i*60,0,NULL);
// // 			LineTo(hDC,0,i*30);
// 			MoveToEx(hDC,i*60,0,NULL);
// 			LineTo(hDC,840,420-i*30);
// 			MoveToEx(hDC,i*60,0,NULL);
// 			LineTo(hDC,0,i*30);
// 		}
// 		for(i=1;i<22;i++)
// 		{
// 			MoveToEx(hDC,840,i*30,NULL);
// 			LineTo(hDC,0,i*30+420);
//  			MoveToEx(hDC,0,i*30,NULL);
//  			LineTo(hDC,840,i*30+420);
// 		}
		RECT rt={30,634,826,662};
		int oldMode;
		COLORREF oldColor;
		CFont cf;
		cf.CreateFont(
			15,                        // nHeight
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

		CString tt;
// 		POINT t;
// 		GetCursorPos(&t);
// 		ScreenToClient(g_hWnd,&t);

/*		tt.Format("%d,%d   %d,%d",left.x,left.y,right.x,right.y);*/
// 		int ix,iy;
// 		ix=(t.x+t.y*2)/60;
// 		iy=(t.y-t.x/2+450)/30-15;
// 		tt.Format("%d,%d   %d,%d   %d,%d",ix,iy,left.x,left.y,  /*(ix-iy)*30,(ix+iy)*15);*/
// 			right.x,right.y);

		DrawText(hDC,TEXT("Yan Jun proudly presents."),-1,&rt,DT_LEFT|DT_SINGLELINE|DT_VCENTER);
		DrawText(hDC,TEXT("Version:1.0"),-1,&rt,DT_RIGHT|DT_SINGLELINE|DT_VCENTER);
/*		DrawText(hDC,tt,-1,&rt,DT_LEFT|DT_SINGLELINE|DT_VCENTER);*/
		
		SelectObject(hDC,oldFont);
		cf.DeleteObject();
		SetTextColor(hDC,oldColor);
			SetBkMode(hDC,oldMode);
	}
	else
	{
		RECT rect={0,0,m_iWidth,m_iHeight};
		HBRUSH hbr=CreateSolidBrush(m_crColor);
		FillRect(hDC,&rect,hbr);
		DeleteObject(hbr);
	}
}
