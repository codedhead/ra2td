#include "sprite.h"
#include "ParachuteSprite.h"
#include "gameengine.h"
extern GameEngine* g_pGame;

extern POINT g_ptPR[];

class DelayRelease:public Sprite
{

protected:
	int m_iRy;
public:
	DelayRelease(int iRy);
	~DelayRelease();
	virtual void Draw(HDC hDC);
	virtual void UpdateFrame();
};

DelayRelease::DelayRelease(int iRy)
:Sprite(),m_iRy(iRy)
{
}

DelayRelease::~DelayRelease()
{
}

void DelayRelease::Draw(HDC hDC)
{
}

void DelayRelease::UpdateFrame()
{
	if(m_iCurFrame>=m_iNumFrames)
	{
		m_bDying=TRUE;
		return;
	}
	

	ParachuteSprite* paraSprite=new ParachuteSprite(g_ptPR[m_iCurFrame],m_iRy-g_ptPR[m_iCurFrame].y);
	paraSprite->SetNumFrames(70);
	g_pGame->AddSprite(paraSprite);
	m_iCurFrame++;
}