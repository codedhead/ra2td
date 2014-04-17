#pragma once

#include "sprite.h"

class NuclearMissileSprite:public Sprite
{
protected:
	int m_iVy;
public:
	NuclearMissileSprite(Bitmap* pBitmap);
	virtual void UpdateFrame();
	virtual void Draw(HDC hDC);
};


NuclearMissileSprite::NuclearMissileSprite(Bitmap* pBitmap)
:Sprite(pBitmap)
{
	m_iVy=5;
	m_stType=stNMISSILE;
}

inline void NuclearMissileSprite::UpdateFrame()
{

	if(m_rcPosition.bottom>0)
		OffsetPosition(0,-m_iVy);
	else
		m_bDying=TRUE;
	
}

inline void NuclearMissileSprite::Draw(HDC hDC)
{
	if(m_pBitmap&&!m_bHidden)
		m_pBitmap->Draw(hDC,m_rcPosition.left,m_rcPosition.top,TRUE,RGB(0,0,252));
}