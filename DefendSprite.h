#pragma once
#include "afx.h"

#include "Define.h"
#include "Bitmap.h"
#include "ConstructionSprite.h"
#include "PersonSprite.h"

class TeslaSprite;

class DefendSprite:public ConstructionSprite
{
protected:
	DefendState m_dsState;
	PersonSprite* m_psToAttack;
	int m_iAttackDelay;
	int m_iAttackTrigger;
	int m_iAttackArea;

	
public:
	DefendSprite(Bitmap* pBitmap,KindOfCon kfcKind,POINT ptLeft,POINT ptRight);
	virtual ~DefendSprite();
	virtual void UpdateFrame();
	void GetReady();
	void Work();
	void Recover();
	void SetState(DefendState dsState){m_dsState=dsState;}
	DefendState GetState(){return m_dsState;}
	void SetAttack(PersonSprite* psToAttack){m_psToAttack=psToAttack;}
	virtual void Draw(HDC hDC);
	virtual void CalcCollisionRect();
};
