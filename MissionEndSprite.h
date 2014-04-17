#pragma once


#include "Bitmap.h"
#include "Sprite.h"


extern HINSTANCE g_hInstance;

class MissionEndSprite:public Sprite
{
protected:
	int m_iShowDelay;
	int m_iShowTrigger;
public:
	MissionEndSprite(Bitmap* pBitmap,int iType,int iShowDelay);
	virtual ~MissionEndSprite();
	
	virtual void UpdateFrame();
};

MissionEndSprite::MissionEndSprite(Bitmap* pBitmap,int iType,int iShowDelay)
:Sprite(pBitmap),m_iShowDelay(iShowDelay)
{
	m_iCurFrame=iType;
	m_iShowTrigger=m_iShowDelay;
	m_stType=stMISSIONEND;
	m_iZOrder=90000;
}

MissionEndSprite::~MissionEndSprite(){}

inline void MissionEndSprite::UpdateFrame()
{
	if(--m_iShowTrigger<0)
		m_bDying=TRUE;
}