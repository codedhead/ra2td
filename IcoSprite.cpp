#include "icosprite.h"

IcoSprite::IcoSprite(Bitmap* pBitmap,KindOfCon kfcKind):Sprite(pBitmap),m_kfcKind(kfcKind)
{
	m_bsState=bsNone;
	m_csCounter=NULL;
	m_stType=stICO;
	m_iZOrder=10000;
	m_rcMouseNotify=m_rcPosition;
}

void IcoSprite::CalcCollisionRect()
{
	int iXShrink=(m_rcPosition.left-m_rcPosition.right)/12;
	int iYShrink=(m_rcPosition.top-m_rcPosition.bottom)/12;
	CopyRect(&m_rcCollision,&m_rcPosition);
	InflateRect(&m_rcCollision,iXShrink,iYShrink);
	m_rcMouseNotify=m_rcPosition;
}

IcoSprite::~IcoSprite(){}

void IcoSprite::Draw(HDC hDC)
{
	if(m_pBitmap&&!m_bHidden)
	{
		m_pBitmap->Draw(hDC,m_rcPosition.left,m_rcPosition.top,TRUE);
		
		if(m_bsState==bsComplete)
		{
			HPEN oldPen,newPen;
			newPen=CreatePen(1,2,RGB(0,252,0));
			oldPen=(HPEN)SelectObject(hDC,newPen);
			MoveToEx(hDC,m_rcPosition.left,m_rcPosition.top,NULL);
			LineTo(hDC,m_rcPosition.right,m_rcPosition.top);
			LineTo(hDC,m_rcPosition.right,m_rcPosition.bottom);
			LineTo(hDC,m_rcPosition.left,m_rcPosition.bottom);
			LineTo(hDC,m_rcPosition.left,m_rcPosition.top);
			SelectObject(hDC,oldPen);
			DeleteObject(newPen);
		}
	}
}