#include "menusprite.h"
#include "MenuItemSprite.h"
#include "GameEngine.h"
extern GameEngine* g_pGame;

MenuSprite::MenuSprite()
{
	for(int i=0;i<NUMOFMENUS;i++)
	{
		m_bWithText[i]=FALSE;
		m_strText[i]=TEXT("");
		m_mfFunc[i]=mfNone;
		m_pItemSprite[i]=NULL;
	}
	m_bWithText[0]=TRUE;m_strText[0]=TEXT("é_Ê¼ß[‘ò");m_mfFunc[0]=mfGameStart;
	m_bWithText[1]=TRUE;m_strText[1]=TEXT("ß[‘òÕfÃ÷");m_mfFunc[1]=mfGameIntro;
	m_bWithText[2]=TRUE;m_strText[2]=TEXT("êPì¶");m_mfFunc[2]=mfGameAbout;

	m_bWithText[NUMOFMENUS-1]=TRUE;m_strText[NUMOFMENUS-1]=TEXT("ÍË³öß[‘ò");m_mfFunc[NUMOFMENUS-1]=mfGameEnd;
	m_iCurItem=0;

	m_pStart.x=868;m_pStart.y=199;
	AddItem();
//	g_dsWavList.PlayBuffer(PrismPow,0);
	PlaySound("res\\wav\\uslidein.wav",NULL,SND_FILENAME|SND_ASYNC);
}

MenuSprite::~MenuSprite(){}

void MenuSprite::AddItem()
{
	if(m_iCurItem>=NUMOFMENUS) return;
	
	m_pItemSprite[m_iCurItem]=new MenuItemSprite(this,m_bWithText[m_iCurItem],m_strText[m_iCurItem],m_mfFunc[m_iCurItem]);
	m_pItemSprite[m_iCurItem]->SetPosition(m_pStart.x,m_pStart.y+m_iCurItem*50);
	g_pGame->AddSprite(m_pItemSprite[m_iCurItem]);
	m_iCurItem++;
}

void MenuSprite::ClearItems()
{
	for(int i=0;i<m_iCurItem;i++)
	{
		m_pItemSprite[i]->Kill();
		m_pItemSprite[i]=NULL;
	}
}