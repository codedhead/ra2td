#include "gameengine.h"
#pragma comment(lib,"winmm.lib")

GameEngine *GameEngine::m_pGameEngine=NULL;

class Sprite;
extern Sprite* g_pSideSprite;

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
	MSG msg;
	static int iTickTrigger=0;
	int iTickCount;

	if(GameInitialize(hInstance))
	{
		if(!GameEngine::GetEngine()->Initialize(nCmdShow))
			return FALSE;

		while(TRUE)
		{
			if(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
			{
				if(msg.message==WM_QUIT)
					break;
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				if(!GameEngine::GetEngine()->GetSleep())
				{
					iTickCount=GetTickCount();
					if(iTickCount>iTickTrigger)
					{
						iTickTrigger=iTickCount+GameEngine::GetEngine()->GetFrameDelay();
						HandleKeys();
						GameEngine::GetEngine()->CheckJoystick();
						GameCycle();
					}
				}
			}
		}
		return (int)msg.wParam;
	}

	GameEnd();
	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	return GameEngine::GetEngine()->HandleEvent(hwnd,uMsg,wParam,lParam);
}

BOOL GameEngine::CheckSpriteCollision(Sprite* pTestSprite)
{
	for(int i=0;i<m_iCurNum;i++)
	{
		if(pTestSprite==m_sAllSprites[i])
			continue;

		if(pTestSprite->TestCollision(m_sAllSprites[i]))
			SpriteCollision(m_sAllSprites[i],pTestSprite);
	}

	return FALSE;
}

GameEngine::GameEngine(HINSTANCE hInstance,LPTSTR szWndCls,LPTSTR szTitle,
		WORD wIcon,WORD wSmallIcon,int iWidth,int iHeight)
{
	m_pGameEngine=this;
	m_hInstance=hInstance;
	m_hWnd=NULL;
	if(lstrlen(szWndCls)>0)
		lstrcpy(m_szWndCls,szWndCls);
	if(lstrlen(szTitle)>0)
		lstrcpy(m_szTitle,szTitle);
	m_wIcon=wIcon;
	m_wSmallIcon=wSmallIcon;
	m_iWidth=iWidth;
	m_iHeight=iHeight;
	m_iFrameDelay=50;
	m_bSleep=TRUE;
	m_uiJoystickID=0;
	m_uiMIDIPlayerID=0;
	m_iCurNum=0;
}

GameEngine::~GameEngine()
{
}

BOOL GameEngine::Initialize(int iCmdShow)
{
	WNDCLASSEX wndcls;

	wndcls.cbSize=sizeof(wndcls);
	wndcls.style=CS_HREDRAW|CS_VREDRAW;
	wndcls.lpfnWndProc=WndProc;
	wndcls.cbClsExtra=0;
	wndcls.cbWndExtra=0;
	wndcls.hInstance=m_hInstance;
	wndcls.hIcon=LoadIcon(m_hInstance,MAKEINTRESOURCE(GetIcon()));
	wndcls.hIconSm=LoadIcon(m_hInstance,MAKEINTRESOURCE(GetSmallIcon()));
	wndcls.hCursor=LoadCursor(NULL,IDC_ARROW);
	wndcls.hbrBackground=(HBRUSH)(COLOR_WINDOW+1);
	wndcls.lpszMenuName=NULL;
	wndcls.lpszClassName=m_szWndCls;

	if(!RegisterClassEx(&wndcls))
		return FALSE;

	int iWindowWidth=m_iWidth+GetSystemMetrics(SM_CXFIXEDFRAME)*2;
	int iWindowHeight=m_iHeight+GetSystemMetrics(SM_CYFIXEDFRAME)*2+GetSystemMetrics(SM_CYCAPTION);

	if(wndcls.lpszMenuName)
		iWindowHeight+=GetSystemMetrics(SM_CYMENU);
	
	int iXWindowPos=(GetSystemMetrics(SM_CXSCREEN)-iWindowWidth)/2;
	int iYWindowPos=(GetSystemMetrics(SM_CYSCREEN)-iWindowHeight)/2;

	m_hWnd=CreateWindow(m_szWndCls,m_szTitle,WS_POPUPWINDOW|WS_CAPTION|WS_MINIMIZEBOX,
		iXWindowPos,iYWindowPos,iWindowWidth,iWindowHeight,NULL,NULL,m_hInstance,NULL);

	if(!m_hWnd)
		return FALSE;

	ShowWindow(m_hWnd,iCmdShow);
	UpdateWindow(m_hWnd);

	return TRUE;
}

LRESULT GameEngine::HandleEvent(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_CREATE:
		SetWindow(hwnd);
		GameStart(hwnd);
		return 0;

	case WM_SETFOCUS:
		GameActivate(hwnd);
		SetSleep(FALSE);
		return 0;

	case WM_KILLFOCUS:
		GameDeactivate(hwnd);
		SetSleep(TRUE);
		return 0;

	case WM_LBUTTONDOWN:
		MouseButtonDown(LOWORD(lParam),HIWORD(lParam),TRUE);
		return 0;

	case WM_LBUTTONUP:
		MouseButtonUp(LOWORD(lParam),HIWORD(lParam),TRUE);
		return 0;

	case WM_RBUTTONDOWN:
		MouseButtonDown(LOWORD(lParam),HIWORD(lParam),FALSE);
		return 0;

	case WM_RBUTTONUP:
		MouseButtonUp(LOWORD(lParam),HIWORD(lParam),FALSE);
		return 0;

	case WM_MOUSEMOVE:
		MouseMove(LOWORD(lParam),HIWORD(lParam));
		return 0;

	case WM_PAINT:
		HDC hDC;
		PAINTSTRUCT ps;
		hDC=BeginPaint(hwnd,&ps);

		GamePaint(hDC);

		EndPaint(hwnd,&ps);
		return 0;

	case WM_DESTROY:
		GameEnd();
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd,uMsg,wParam,lParam);
}

void GameEngine::ErrorQuit(LPTSTR szErrorMsg)
{
	MessageBox(GetWindow(),szErrorMsg,TEXT("Critical Error"),MB_OK|MB_ICONERROR);
	PostQuitMessage(0);
}

BOOL GameEngine::InitJoystick()
{
	UINT uiNumJoysticks;
	if((uiNumJoysticks=joyGetNumDevs())==0)
		return FALSE;

	JOYINFO jiInfo;
	if(joyGetPos(JOYSTICKID1,&jiInfo)!=JOYERR_UNPLUGGED)
		m_uiJoystickID=JOYSTICKID1;
	else 
		return FALSE;

	JOYCAPS jcCaps;
	joyGetDevCaps(m_uiJoystickID,&jcCaps,sizeof(JOYCAPS));
	
	m_rcJoystickTrip.left=jcCaps.wXmin+(jcCaps.wXmax-jcCaps.wXmin)/4;
	m_rcJoystickTrip.right=jcCaps.wXmax-(jcCaps.wXmax-jcCaps.wXmin)/4;
	m_rcJoystickTrip.top=jcCaps.wYmin+(jcCaps.wYmax-jcCaps.wYmin)/4;
	m_rcJoystickTrip.bottom=jcCaps.wYmax-(jcCaps.wYmax-jcCaps.wYmin)/4;

	return TRUE;
}

void GameEngine::CaptureJoystick()
{
	if(m_uiJoystickID==JOYSTICKID1)
		joySetCapture(m_hWnd,m_uiJoystickID,NULL,TRUE);
}

void GameEngine::ReleaseJoystick()
{
	if(m_uiJoystickID==JOYSTICKID1)
		joyReleaseCapture(m_uiJoystickID);
}

void GameEngine::CheckJoystick()
{
	if(m_uiJoystickID==JOYSTICKID1)
	{
		JOYINFO jiInfo;
		JOYSTATE jsJoystickState=0;
		if(joyGetPos(m_uiJoystickID,&jiInfo)==JOYERR_NOERROR)
		{
			if(jiInfo.wXpos<(WORD)m_rcJoystickTrip.left)
				jsJoystickState|=JOY_LEFT;
			else if(jiInfo.wXpos>(WORD)m_rcJoystickTrip.right)
				jsJoystickState|=JOY_RIGHT;

			if(jiInfo.wYpos<(WORD)m_rcJoystickTrip.top)
				jsJoystickState|=JOY_UP;
			else if(jiInfo.wYpos>(WORD)m_rcJoystickTrip.bottom)
				jsJoystickState|=JOY_DOWN;

			if(jiInfo.wButtons&JOY_BUTTON1)
				jsJoystickState|=JOY_FIRE1;
			if(jiInfo.wButtons&JOY_BUTTON2)
				jsJoystickState|=JOY_FIRE2;
		}

		HandleJoystick(jsJoystickState);
	}
}
			
void GameEngine::AddSprite(Sprite* pSprite)
{
	if(pSprite&&m_iCurNum<OBMAXSIZE)
		m_sAllSprites[m_iCurNum++]=pSprite;
}

void GameEngine::DrawSprite(HDC hDC)
{
	SortSpritesByZorder();
	for(int i=0;i<m_iCurNum;i++)
		m_sAllSprites[i]->Draw(hDC);
}

void GameEngine::UpdateSprites()
{
	//need resize?

	RECT rcOldSpritePos;
	SPRITEACTION saSpriteAction;

	SortSpritesByZorder();

	for(int i=0;i<m_iCurNum;i++)
	{
		rcOldSpritePos=m_sAllSprites[i]->GetPosition();
		saSpriteAction=m_sAllSprites[i]->Update();

		if(saSpriteAction&SA_ADDSPRITE)
			AddSprite(m_sAllSprites[i]->AddSprite());

		

		if(saSpriteAction&SA_KILL)
		{
			
			if(SpriteDying(m_sAllSprites[i]))
			{
				delete (m_sAllSprites[i]);
				m_sAllSprites[i]=m_sAllSprites[m_iCurNum-1];
				m_iCurNum--;/////////////////////////////need delete here///////////////////////////////////
			}
				continue;
		}

		

		if(CheckSpriteCollision(m_sAllSprites[i]))
			m_sAllSprites[i]->SetPosition(rcOldSpritePos);
	}
}

Sprite* GameEngine::IsPointInSprite(int x,int y)
{
	for(int i=m_iCurNum-1;i>=0;i--)
		if(!m_sAllSprites[i]->IsHidden()&&m_sAllSprites[i]!=(Sprite*)g_pSideSprite
			&&m_sAllSprites[i]->IsPointInside(x,y))
			return m_sAllSprites[i];
	return NULL;
}

void GameEngine::CleanupSprites()
{
	for(int i=0;i<m_iCurNum;i++)
	{
		delete (m_sAllSprites[i]);
		m_sAllSprites[i]=NULL;
	}
	m_iCurNum=0;
}

void GameEngine::PlayMIDISong(LPTSTR szMIDIFileName,BOOL bRestart)
{
	if(m_uiMIDIPlayerID==0)
	{
		MCI_OPEN_PARMS mciOpenParms;
		mciOpenParms.lpstrDeviceType="sequencer";
		mciOpenParms.lpstrElementName=szMIDIFileName;
		if(mciSendCommand(NULL,MCI_OPEN,MCI_OPEN_TYPE|MCI_OPEN_ELEMENT,
			(DWORD)&mciOpenParms)==0)
			m_uiMIDIPlayerID=mciOpenParms.wDeviceID;
		else
			return;
	}
	if(bRestart)
	{
		MCI_SEEK_PARMS mciSeekParms;
		if(mciSendCommand(m_uiMIDIPlayerID,MCI_SEEK,MCI_SEEK_TO_START,
			(DWORD)&mciSeekParms))
			CloseMIDIPlayer();//?return?
	}

	MCI_PLAY_PARMS mciPlayParms;
	if(mciSendCommand(m_uiMIDIPlayerID,MCI_PLAY,0,
		(DWORD)&mciPlayParms))
		CloseMIDIPlayer();
}

void GameEngine::PauseMIDISong()
{
	if(m_uiMIDIPlayerID)
		mciSendCommand(m_uiMIDIPlayerID,MCI_PAUSE,0,NULL);
}

void GameEngine::CloseMIDIPlayer()
{
	if(m_uiMIDIPlayerID)
	{
		mciSendCommand(m_uiMIDIPlayerID,MCI_CLOSE,0,NULL);
		m_uiMIDIPlayerID=0;
	}
}

void QuickSort(Sprite* a[],int p,int r)
{
	Sprite* t;
	int i,j,x;
	if(p<r)
	{
		x=rand()%(r-p+1)+p;
		t=a[x];
		a[x]=a[r];
		a[r]=t;
		x=a[r]->GetZOrder();
		i=p-1;j=p;
		for(;j<r;j++)
			if(a[j]->GetZOrder()<x)
			{
				i++;
				t=a[i];a[i]=a[j];a[j]=t;
			}
			t=a[i+1];a[i+1]=a[r];a[r]=t;
			
			QuickSort(a,p,i);
			QuickSort(a,i+2,r);
	}
}

void GameEngine::SortSpritesByZorder()
{
	QuickSort(m_sAllSprites,0,m_iCurNum-1);
}