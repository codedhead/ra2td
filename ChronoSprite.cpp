#include "chronosprite.h"
#include "gameengine.h"
#include "PersonSprite.h"

extern GameEngine* g_pGame;
extern Bitmap* g_pPersonBitmap[];

ChronoSprite::ChronoSprite(Bitmap* pBitmap,int iSection)
:Sprite(pBitmap),m_iSection(iSection)
{

}

void ChronoSprite::UpdateFrame()
{
	if((m_iFrameDelay>=0)&&(--m_iFrameTrigger<=0))
	{
		m_iFrameTrigger=m_iFrameDelay;
		m_iCurFrame++;
		if(m_iCurFrame==13)
		{
			POINT ptCenter={(m_rcPosition.left+m_rcPosition.right)/2,(m_rcPosition.top+m_rcPosition.bottom)/2};
			for(int i=0;i<10;i++)
			{
				PersonSprite* newSprite;
				int j=rand()%((int)TESLA_TROOPER+1);
				//newSprite=new PersonSprite(g_pPersonBitmap[j],ptCenter.x+5*(rand()%5-2),ptCenter.y+5*(rand()%5-2),(KindOfPerson)j);
				newSprite=new PersonSprite(g_pPersonBitmap[j],ptCenter.x,ptCenter.y,(KindOfPerson)j);
				newSprite->SetNextNode(m_iSection);
				newSprite->SetNumFrames(g_piPersonInfo[j].NumFrames);		
				g_pGame->AddSprite(newSprite);
			}
		}
		else if(m_iCurFrame>=m_iNumFrames)
			if(m_bOneCycle)
				m_bDying=TRUE;
			else
				m_iCurFrame=0;
	}
}