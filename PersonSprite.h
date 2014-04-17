#pragma once
#include "afx.h"

#include <math.h>
#include "Define.h"
#include "Bitmap.h"
#include "Sprite.h"

extern POINT Path[];
extern int g_iPathLength;

enum GoalState{gsPathGoal,gsNoGoal};

class ParachuteSprite;

class PersonSprite:public Sprite
{
protected:
	int m_iNextNode;
	int m_iTotalVelocity;
	int m_iHurtVelocity;
	
	int m_iTotalHP;
	int m_iCurHP;
	COLORREF m_crTrans;
	KindOfPerson m_kfpKind;
	int m_iOffsexX,m_iOffsexY;

	ParachuteSprite* m_pParachute;
	
public:
	GoalState m_gsState;
	POINT m_ptCenter;
	DIRECTION olddir;
	DieWay m_dwDieWay;
	BOOL m_bFalling;
	PersonSprite(Bitmap* pBitmap,int x,int y,KindOfPerson kopKind,ParachuteSprite* pParachute=NULL);
	virtual ~PersonSprite();
	virtual void UpdateFrame();
	virtual void Draw(HDC hDC);
	virtual void CalcCollisionRect();
	virtual void SetPosition(int x,int y);
	void Walk(DIRECTION dir);
	void Attack(POINT ptToAttack);
	void Creep(DIRECTION dir);
	void Stop(DIRECTION dir);
	void Die();
	void SetNextNode(int iNode){m_iNextNode=iNode;}
	POINT GetCenter(){return m_ptCenter;}
	void Hurt(int iDamage){if(iDamage>1&&m_iCurHP<=30)iDamage>>=1; m_iCurHP-=iDamage;}//≈øµΩºıµÕ…À∫¶
	BOOL Dying(){return m_iCurHP<=0;}
	void SetFalling(BOOL bFalling){m_bFalling=bFalling;}
//	virtual RECT& GetFoot();
};

