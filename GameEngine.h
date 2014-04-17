#pragma once
#include "afx.h"

#include <mmsystem.h>

#include "sprite.h"

#define OBMAXSIZE 1000

typedef WORD JOYSTATE;
const JOYSTATE JOY_NONE =0x0000L,
			   JOY_LEFT =0x0001L,
			   JOY_RIGHT=0x0002L,
			   JOY_UP   =0x0004L,
			   JOY_DOWN =0x0008L,
			   JOY_FIRE1=0x0010L,
			   JOY_FIRE2=0x0020L;

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow);
LRESULT CALLBACK WndProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam);

BOOL GameInitialize(HINSTANCE hInstance);
void GameStart(HWND hWnd);
void GameEnd();
void GameActivate(HWND hWnd);
void GameDeactivate(HWND hWnd);
void GamePaint(HDC hDC);
void HandleKeys();
void MouseButtonDown(int x,int y,BOOL bLeft);
void MouseButtonUp(int x,int y,BOOL bLeft);
void MouseMove(int x,int y);
void HandleJoystick(JOYSTATE jsJoystickState);
void GameCycle();
BOOL SpriteCollision(Sprite* pSpriteHitter,Sprite* pSpriteHittee);
BOOL SpriteDying(Sprite* pSpriteDying);

//Help Function
void QuickSort(Sprite* sp[],int p,int r);

class GameEngine
{
protected:
	static GameEngine* m_pGameEngine;
	HINSTANCE m_hInstance;
	HWND m_hWnd;
	TCHAR m_szWndCls[32];
	TCHAR m_szTitle[32];
	WORD m_wIcon,m_wSmallIcon;
	int m_iWidth,m_iHeight;
	int m_iFrameDelay;
	BOOL m_bSleep;
	UINT m_uiJoystickID;
	RECT m_rcJoystickTrip;
/*	vector<Sprite*> m_vSprites;*/
	Sprite* m_sAllSprites[OBMAXSIZE];
	int m_iCurNum;
	UINT m_uiMIDIPlayerID;

	BOOL CheckSpriteCollision(Sprite* pTestSprite);

public:
	GameEngine(HINSTANCE hInstance,LPTSTR szWndCls,LPTSTR szTitle,
		WORD wIcon,WORD wSmallIcon,int iWidth=640,int iHeight=480);
	virtual ~GameEngine();

	static GameEngine* GetEngine(){return m_pGameEngine;}
	BOOL Initialize(int iCmdShow);
	LRESULT HandleEvent(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam);
	void ErrorQuit(LPTSTR szErrorMsg);
	BOOL InitJoystick();
	void CaptureJoystick();
	void ReleaseJoystick();
	void CheckJoystick();
	void AddSprite(Sprite* pSprite);
	void DrawSprite(HDC hDC);
	void UpdateSprites();
	void SortSpritesByZorder();
	void CleanupSprites();
	Sprite* IsPointInSprite(int x,int y);
	void PlayMIDISong(LPTSTR szMIDIFileName=TEXT(""),
			BOOL bRestart=TRUE);
	void PauseMIDISong();
	void CloseMIDIPlayer();

	HINSTANCE GetInstance(){return m_hInstance;}
	HWND GetWindow(){return m_hWnd;}
	void SetWindow(HWND hWnd){m_hWnd=hWnd;}
	LPTSTR GetTitle(){return m_szTitle;}
	WORD GetIcon(){return m_wIcon;}
	WORD GetSmallIcon(){return m_wSmallIcon;}
	int GetWidth(){return m_iWidth;}
	int GetHeight(){return m_iHeight;}
	int GetFrameDelay(){return m_iFrameDelay;}
	void SetFrameRate(int iFrameRate){m_iFrameDelay=1000/iFrameRate;}
	BOOL GetSleep(){return m_bSleep;}
	void SetSleep(BOOL bSleep){m_bSleep=bSleep;}
};
