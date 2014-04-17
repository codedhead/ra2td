#include "Construction.h"
#include "resource.h"
#include "PrismSprite.h"
#include "MenuItemSprite.h"
#include "ChronoSprite.h"
#include "PlaneSprite.h"
#include "NuclearMissileSprite.h"
#include "DieAshSprite.h"
#include "DigitalVideo.h"

CDigitalvideo g_dvVideo;

#pragma comment (lib,"winmm.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"dsound.lib")

#define STUDY_TIME_LENGTH 120*30
#define LAUNCH_TIME_LENGTH 65*30
#define ENIMY_TIME_LENGTH 15*30
#define PLANE_TIME_LENGTH 12*30
#define CHRONO_TIME_LENGTH 15*30

BOOL g_bIsTaken[50][50];

BOOL GameInitialize(HINSTANCE hInstance)
{
	g_pGame=new GameEngine(hInstance,TEXT("RA2"),
		TEXT("RA2"),IDI_RA2,IDI_RA2_SM,1024,662);
	if(g_pGame==NULL)
		return FALSE;

	g_pGame->SetFrameRate(30);

	g_hInstance=hInstance;

	g_bGameOver=TRUE;


	return TRUE;
}

void LoadAllBitmaps(HWND hWnd)
{
	//////////////////////////////////////////////////////////////
	//Load Dll
	LoadImageFunc m_funLoadAtlImage=NULL;
	HMODULE m_hModule=LoadLibrary("AtlImage.dll");
	if(!m_hModule)
	{
		MessageBox(hWnd,"装载动态链接库失败:AtlImage.dll","Error",MB_OK);
		m_hModule=NULL;
		PostQuitMessage(0);
		return;
	}
	m_funLoadAtlImage=(LoadImageFunc)GetProcAddress(m_hModule,"LoadAtlImage");
	if (!m_funLoadAtlImage)
	{
		MessageBox(hWnd,"无法找到函数入口:LoadAtlImage","Error",MB_OK);
		m_funLoadAtlImage=NULL;
		PostQuitMessage(0);
		return;
	}

	HBITMAP hBitmap;
	//////////////////////////////////////////////////////////////
	//Background

	hBitmap=m_funLoadAtlImage("res\\BG.png");
	g_pBGBitmap=new Bitmap(hBitmap);	
	g_pBackground=new Background(g_pBGBitmap);

	hBitmap=m_funLoadAtlImage("res\\Side.png");
	g_pSideBitmap=new Bitmap(hBitmap);	
/*	g_pSide=new Background(g_pSideBitmap);*/

	//UI

 	hBitmap=m_funLoadAtlImage("res\\Main.png");
	g_pMainBitmap=new Bitmap(hBitmap);	
	g_pMain=new Background(g_pMainBitmap);

// 	hBitmap=m_funLoadAtlImage("res\\MainBottom.png");
// 	g_pMainBottomBitmap=new Bitmap(hBitmap);	
/*	g_pMainBottom=new Background(g_pMainBottomBitmap);*/

// 	hBitmap=m_funLoadAtlImage("res\\MainSide.png");
// 	g_pMainSideBitmap=new Bitmap(hBitmap);	
/*	g_pMainSide=new Background(g_pMainSideBitmap);*/


	hBitmap=m_funLoadAtlImage("res\\Other\\MenuText.png"); 
	g_pMenuTextBitmap=new Bitmap(hBitmap);
	
	hBitmap=m_funLoadAtlImage("res\\Other\\MenuNull.png"); 
	g_pMenuNullBitmap=new Bitmap(hBitmap);

	hBitmap=m_funLoadAtlImage("res\\Other\\MovingPointer.png"); 
	g_pMovingPointerBitmap=new Bitmap(hBitmap);	

	hBitmap=m_funLoadAtlImage("res\\Other\\radar.png"); 
	g_pRadarBitmap=new Bitmap(hBitmap);	

	hBitmap=m_funLoadAtlImage("res\\Other\\fix.png"); 
	g_pFixBitmap=new Bitmap(hBitmap);	

	hBitmap=m_funLoadAtlImage("res\\Other\\sell.png"); 
	g_pSellBitmap=new Bitmap(hBitmap);	

	hBitmap=m_funLoadAtlImage("res\\Other\\mouse.png"); 
	g_pMouseBitmap=new Bitmap(hBitmap);


	hBitmap=m_funLoadAtlImage("res\\Mission1.png"); 
	g_pMission1Bitmap=new Bitmap(hBitmap);
	/*g_pMission1Sprite=new Sprite(g_pMission1Bitmap);*/

	hBitmap=m_funLoadAtlImage("res\\Mission2.png"); 
	g_pMission2Bitmap=new Bitmap(hBitmap);
	/*g_pMission2Sprite=new Sprite(g_pMission2Bitmap);*/

	hBitmap=m_funLoadAtlImage("res\\About.png"); 
	g_pAboutBitmap=new Bitmap(hBitmap);
	
	hBitmap=m_funLoadAtlImage("res\\Intro.png"); 
	g_pIntroBitmap=new Bitmap(hBitmap);
	

	hBitmap=m_funLoadAtlImage("res\\Construction\\NuclearMissleSlot.png"); 
	g_pNMSBitmap=new Bitmap(hBitmap);	
	//////////////////////////////////////////////////////////////
	//Other Stuff
	hBitmap=m_funLoadAtlImage("res\\Other\\Counter.png");
	g_pCounterBitmap=new Bitmap(hBitmap);

	hBitmap=m_funLoadAtlImage("res\\Other\\EvanBomb.png");
	g_pEvanBombBitmap=new Bitmap(hBitmap);

	hBitmap=m_funLoadAtlImage("res\\Other\\SealBomb.png");
	g_pSealBombBitmap=new Bitmap(hBitmap);

	hBitmap=m_funLoadAtlImage("res\\Other\\ManBurned.png");
	g_pManBurnedBitmap=new Bitmap(hBitmap);

	hBitmap=m_funLoadAtlImage("res\\Other\\ManRadium.png");
	g_pManRadiumBitmap=new Bitmap(hBitmap);

	hBitmap=m_funLoadAtlImage("res\\Other\\ManShocked.png");
	g_pManShockedBitmap=new Bitmap(hBitmap);

	hBitmap=m_funLoadAtlImage("res\\Other\\ManToAsh.png");
	g_pManToAshBitmap=new Bitmap(hBitmap);

	hBitmap=m_funLoadAtlImage("res\\Other\\Chrono.png");
	g_pChronoBitmap=new Bitmap(hBitmap);	

	hBitmap=m_funLoadAtlImage("res\\Other\\Plane.png");
	g_pPlaneBitmap=new Bitmap(hBitmap);

	hBitmap=m_funLoadAtlImage("res\\Other\\Parachute.png");
	g_pParachuteBitmap=new Bitmap(hBitmap);	

	hBitmap=m_funLoadAtlImage("res\\Other\\MissionEnd.png");
	g_pMissionEndBitmap=new Bitmap(hBitmap);		

	hBitmap=m_funLoadAtlImage("res\\Other\\NMissile.png");
	g_pNMissileBitmap=new Bitmap(hBitmap);
	
	//////////////////////////////////////////////////////////////
	//ConstructionIco
	hBitmap=m_funLoadAtlImage("res\\ConstructionIco\\ABattleLabIco.png");
	g_pIcoBitmap[A_BATTLE_LAB]=new Bitmap(hBitmap);

// 	hBitmap=m_funLoadAtlImage("res\\ConstructionIco\\GattlingCannonIco.png");
// 	g_pIcoBitmap[GATTLING_CANON_ICO]=new Bitmap(hBitmap);

	hBitmap=m_funLoadAtlImage("res\\ConstructionIco\\NuclearReactorIco.png");
	g_pIcoBitmap[NUCLEAR_REACTOR]=new Bitmap(hBitmap);

	hBitmap=m_funLoadAtlImage("res\\ConstructionIco\\PillBoxIco.png");
	g_pIcoBitmap[PILL_BOX]=new Bitmap(hBitmap);

	hBitmap=m_funLoadAtlImage("res\\ConstructionIco\\PowerPlantIco.png");
	g_pIcoBitmap[POWER_PLANT]=new Bitmap(hBitmap);

	hBitmap=m_funLoadAtlImage("res\\ConstructionIco\\PrismTowerIco.png");
	g_pIcoBitmap[PRISM_TOWER]=new Bitmap(hBitmap);

	hBitmap=m_funLoadAtlImage("res\\ConstructionIco\\SentryGunIco.png");
	g_pIcoBitmap[SENTRY_GUN]=new Bitmap(hBitmap);

	hBitmap=m_funLoadAtlImage("res\\ConstructionIco\\TeslaCoilIco.png");
	g_pIcoBitmap[TESLA_COIL]=new Bitmap(hBitmap);

	//////////////////////////////////////////////////////////////
	//Construction
	hBitmap=m_funLoadAtlImage("res\\Construction\\ABattleLab.png"); 
	g_pConstructionBitmap[A_BATTLE_LAB]=new Bitmap(hBitmap);	

	hBitmap=m_funLoadAtlImage("res\\Construction\\NuclearReactor.png"); 
	g_pConstructionBitmap[NUCLEAR_REACTOR]=new Bitmap(hBitmap);

	hBitmap=m_funLoadAtlImage("res\\Construction\\PillBox.png"); 
	g_pConstructionBitmap[PILL_BOX]=new Bitmap(hBitmap);

	hBitmap=m_funLoadAtlImage("res\\Construction\\PowerPlant.png"); 
	g_pConstructionBitmap[POWER_PLANT]=new Bitmap(hBitmap);

	hBitmap=m_funLoadAtlImage("res\\Construction\\PrismTower.png"); 
	g_pConstructionBitmap[PRISM_TOWER]=new Bitmap(hBitmap);
	
	hBitmap=m_funLoadAtlImage("res\\Construction\\SentryGun.png"); 
	g_pConstructionBitmap[SENTRY_GUN]=new Bitmap(hBitmap);

	hBitmap=m_funLoadAtlImage("res\\Construction\\TeslaCoil.png"); 
	g_pConstructionBitmap[TESLA_COIL]=new Bitmap(hBitmap);

	//////////////////////////////////////////////////////////////
	//Person
	hBitmap=m_funLoadAtlImage("res\\Unit\\Conscript.png"); 
	g_pPersonBitmap[CONSCRIPT]=new Bitmap(hBitmap);

	hBitmap=m_funLoadAtlImage("res\\Unit\\Desolator.png"); 
	g_pPersonBitmap[DESOLATOR]=new Bitmap(hBitmap);

	hBitmap=m_funLoadAtlImage("res\\Unit\\Evan.png"); 
	g_pPersonBitmap[EVAN]=new Bitmap(hBitmap);

	hBitmap=m_funLoadAtlImage("res\\Unit\\FlakTrooper.png"); 
	g_pPersonBitmap[FLAK_TROOPER]=new Bitmap(hBitmap);

	hBitmap=m_funLoadAtlImage("res\\Unit\\LandRocketeer.png"); 
	g_pPersonBitmap[LAND_ROCKETEER]=new Bitmap(hBitmap);

	hBitmap=m_funLoadAtlImage("res\\Unit\\Rocketeer.png"); 
	g_pPersonBitmap[ROCKETEER]=new Bitmap(hBitmap);

	hBitmap=m_funLoadAtlImage("res\\Unit\\Sniper.png"); 
	g_pPersonBitmap[SNIPER]=new Bitmap(hBitmap);

	hBitmap=m_funLoadAtlImage("res\\Unit\\TeslaTrooper.png"); 
	g_pPersonBitmap[TESLA_TROOPER]=new Bitmap(hBitmap);

	hBitmap=m_funLoadAtlImage("res\\Unit\\USSoldier.png"); 
	g_pPersonBitmap[US_SOLDIER]=new Bitmap(hBitmap);

	hBitmap=m_funLoadAtlImage("res\\Unit\\WhiteSeal.png"); 
	g_pPersonBitmap[WHITE_SEAL]=new Bitmap(hBitmap);

	hBitmap=m_funLoadAtlImage("res\\Unit\\YellowSeal.png"); 
	g_pPersonBitmap[YELLOW_SEAL]=new Bitmap(hBitmap);

	
	//////////////////////////////////////////////////////////////
	//Release
	FreeLibrary(m_hModule);
}

void SetIcoSprite()
{
	//3个数组对应三个版面,存储个数确定位置
	int x=878,y=227;

	for(int i=(int)POWER_PLANT;i<=(int)NUCLEAR_REACTOR;i++)
	{
		g_pIcoSprite[i]=new IcoSprite(g_pIcoBitmap[i],(KindOfCon)i);
		if(i%2) x=940;
		else x=878;
		g_pIcoSprite[i]->SetPosition(x,y);
		if(i%2) y+=50;
		
		g_pGame->AddSprite(g_pIcoSprite[i]);
	}
	for(int i=(int)A_BATTLE_LAB;i<=(int)NUCLEAR_REACTOR;i++)
		g_pIcoSprite[i]->SetHidden(TRUE);
// 	g_pIcoSprite[GATTLING_CANON_ICO]->SetHidden(TRUE);
// 	g_pIcoSprite[LIGHTENING_STORM_ICO]->SetHidden(TRUE);
// 	g_pIcoSprite[NUCLEAR_MISSILE_SLOT_ICO]->SetHidden(TRUE);
// 	g_pIcoSprite[PSYCHIC_TOWER_ICO]->SetHidden(TRUE);
// 	g_pIcoSprite[S_BATTLE_LAB_ICO]->SetHidden(TRUE);
// 	g_pIcoSprite[TESLA_REACTOR_ICO]->SetHidden(TRUE);
// 	g_pIcoSprite[WEATHER_CONTROL_DEVICE_ICO]->SetHidden(TRUE);
}

void LoadWavFile()
{
	g_dsWavList.Init();
	g_dsWavList.AddNewBuffer("res\\wav\\Building.wav");
	g_dsWavList.AddNewBuffer("res\\wav\\ConstructionComplete.wav");
	g_dsWavList.AddNewBuffer("res\\wav\\PillAt4.wav");
	g_dsWavList.AddNewBuffer("res\\wav\\PrismAt.wav");
	g_dsWavList.AddNewBuffer("res\\wav\\PrismPow.wav");
	g_dsWavList.AddNewBuffer("res\\wav\\SentryAt3.wav");
	g_dsWavList.AddNewBuffer("res\\wav\\TeslaAt1.wav");
	g_dsWavList.AddNewBuffer("res\\wav\\TeslaPow.wav");
	g_dsWavList.AddNewBuffer("res\\wav\\Uplace.wav");
	g_dsWavList.AddNewBuffer("res\\wav\\Uslidein.wav");
	g_dsWavList.AddNewBuffer("res\\wav\\Uradaron.wav");
	g_dsWavList.AddNewBuffer("res\\wav\\Ucheer.wav");
	g_dsWavList.AddNewBuffer("res\\wav\\Nukread.wav");
	g_dsWavList.AddNewBuffer("res\\wav\\Nuklaun.wav");
	g_dsWavList.AddNewBuffer("res\\wav\\Chrono.wav");
	g_dsWavList.AddNewBuffer("res\\wav\\Plane.wav");
	g_dsWavList.AddNewBuffer("res\\wav\\AtRocketeer.wav");
	g_dsWavList.AddNewBuffer("res\\wav\\AtTesla.wav");
	g_dsWavList.AddNewBuffer("res\\wav\\AtGun1.wav");
	g_dsWavList.AddNewBuffer("res\\wav\\AtGun2.wav");
	g_dsWavList.AddNewBuffer("res\\wav\\AtGun3.wav");
	g_dsWavList.AddNewBuffer("res\\wav\\AtGun4.wav");
	g_dsWavList.AddNewBuffer("res\\wav\\AtGun5.wav");
	g_dsWavList.AddNewBuffer("res\\wav\\Usell.wav");

}

void GameStart(HWND hWnd)
{
	srand(GetTickCount());

	g_hWnd=hWnd;

	HDC hDC=GetDC(hWnd);//双缓冲
	g_hOffscreenDC=CreateCompatibleDC(hDC);
	g_hOffscreenBitmap=CreateCompatibleBitmap(hDC,
		g_pGame->GetWidth(),g_pGame->GetHeight());
	SelectObject(g_hOffscreenDC,g_hOffscreenBitmap);
	ReleaseDC(hWnd,hDC);

	g_cfFont.CreateFont(
		15,                        // nHeight
		0,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		FW_NORMAL,                 // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		ANSI_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
			"宋体"); 


	
	LoadAllBitmaps(hWnd);
	LoadWavFile();

	InitConstructionInfo();
	InitPersonInfo();
	

	g_bGameOver=FALSE;
	g_gsGameState=gsMainMenu;

	g_pMouseSprite=new MouseSprite(g_pMouseBitmap);
	g_pMouseSprite->SetNumFrames(31);
	ShowCursor(FALSE);
	
	
	NewMenu();
	
// 	g_dvVideo.Open(TEXT("res\\1.avi"),hWnd,0,0,856,630);
// 	g_dvVideo.Play(TRUE);

//	g_pGame->AddSprite(g_pMouseSprite);
	//	SetIcoSprite();
}

void ClearAllBitmaps()//删除游戏中相关位图
{
	for(int i=(int)POWER_PLANT;i<=(int)NUCLEAR_REACTOR;i++)
	{
		delete g_pIcoBitmap[i];
		delete g_pConstructionBitmap[i];
	}
	
	//Construction
// 	for(i=(int)A_BATTLE_LAB;i<=(int)NUCLEAR_REACTOR;i++)
// 		delete g_pConstructionBitmap[i];
	
	//Person
	for(int i=(int)CONSCRIPT;i<=(int)YELLOW_SEAL;i++)
		delete g_pPersonBitmap[i];
	
	//Other Stuff
	delete g_pCounterBitmap;
	delete g_pEvanBombBitmap;
	delete g_pSealBombBitmap;
	delete g_pManBurnedBitmap;
	delete g_pManRadiumBitmap;
	delete g_pManShockedBitmap;
	delete g_pManToAshBitmap;

	delete g_pChronoBitmap;
	delete g_pPlaneBitmap;
	delete g_pParachuteBitmap;

	delete g_pFixBitmap;
	delete g_pSellBitmap;
}

void GameEnd()
{
	DeleteObject(g_hOffscreenBitmap);
	DeleteDC(g_hOffscreenDC);

	ClearAllBitmaps();
/*	g_dvVideo.Close();*/

	delete g_pBGBitmap;
	delete g_pBackground;

	delete g_pSideBitmap;
/*	delete g_pSide;*/

	delete g_pMainBitmap;
 	delete g_pMain;
// 	delete g_pMainBottomBitmap;
// 	delete g_pMainSideBitmap;

	delete g_pMenuTextBitmap;
	delete g_pMenuNullBitmap;
	delete g_pMovingPointerBitmap;
	delete g_pRadarBitmap;
	delete g_pNMSBitmap;
	delete g_pMissionEndBitmap;
	delete g_pNMissileBitmap;

	delete g_pMouseBitmap;

	if(g_msMainMenu!=NULL) delete g_msMainMenu;

	g_cfFont.DeleteObject();

	g_pGame->CleanupSprites();
	delete g_pGame;
}

void GameActivate(HWND hWnd)
{

}

void GameDeactivate(HWND hWnd)
{

}

void GamePaint(HDC hDC)
{
	switch(g_gsGameState)
	{
	case gsIntro:
		g_pIntroBitmap->Draw(hDC,0,0);
		break;
	case gsAbout:
		g_pAboutBitmap->Draw(hDC,0,0);
		break;
	case gsMainMenu:
		g_pMain->Draw(hDC);
		g_pGame->DrawSprite(hDC);
		g_pMouseSprite->Draw(hDC);
		break;
	case gsMission1:
	case gsMission2:
		g_pGame->DrawSprite(hDC);
		//	g_pMouseSprite->Draw(hDC);
		break;
	case gsGaming:
		
		g_pBackground->Draw(hDC);
		g_pGame->DrawSprite(hDC);

		RECT rt={920,0,1020,20};
		int oldMode;
		COLORREF oldColor;		
		HFONT oldFont=(HFONT)SelectObject(hDC,g_cfFont.m_hObject);		
		oldColor=SetTextColor(hDC,RGB(252,252,56));
		oldMode=SetBkMode(hDC,TRANSPARENT);
		
		CString tt;
		tt.Format("%d",g_iMoney);
	
		DrawText(hDC,tt,-1,&rt,DT_LEFT|DT_SINGLELINE|DT_VCENTER);

		SetRect(&rt,560,634,820,662);
		if(g_iPassFrames<=STUDY_TIME_LENGTH)
		{
			int iTime=(STUDY_TIME_LENGTH-g_iPassFrames)/30;
			if(iTime/60>9)
			{
				if(iTime%60>9)
					tt.Format("正在研制核弹,预计还需时间 %d:%d",iTime/60,iTime%60);
				else
					tt.Format("正在研制核弹,预计还需时间 %d:0%d",iTime/60,iTime%60);
			}
			else
			{
				if(iTime%60>9)
					tt.Format("正在研制核弹,预计还需时间 0%d:%d",iTime/60,iTime%60);
				else
					tt.Format("正在研制核弹,预计还需时间 0%d:0%d",iTime/60,iTime%60);
			}
			DrawText(hDC,tt,-1,&rt,DT_RIGHT|DT_SINGLELINE|DT_VCENTER);
		}
		else if(!g_bNotStudy&&g_iPassFrames<STUDY_TIME_LENGTH+LAUNCH_TIME_LENGTH)
		{
			int iTime=(STUDY_TIME_LENGTH+LAUNCH_TIME_LENGTH-g_iPassFrames)/30;
			if(iTime/60>9)
			{
				if(iTime%60>9)
					tt.Format("核弹预计发射时间 %d:%d",iTime/60,iTime%60);
				else
					tt.Format("核弹预计发射时间 %d:0%d",iTime/60,iTime%60);
			}
			else
			{
				if(iTime%60>9)
					tt.Format("核弹预计发射时间 0%d:%d",iTime/60,iTime%60);
				else
					tt.Format("核弹预计发射时间 0%d:0%d",iTime/60,iTime%60);
			}
			DrawText(hDC,tt,-1,&rt,DT_RIGHT|DT_SINGLELINE|DT_VCENTER);
		}
		
		
		SelectObject(hDC,oldFont);

		SetTextColor(hDC,oldColor);
		SetBkMode(hDC,oldMode);

		if(g_bShowInfo&&!g_bSelecting)
		{
			TextOut(hDC,g_siShowInfo.ptShowPos.x,g_siShowInfo.ptShowPos.y,g_siShowInfo.strInfo,g_siShowInfo.strInfo.GetLength());
		}

		
		if(g_bSelecting)
		{
			HPEN oldPen,newPen;
			int rux,rdx,lux,ldx;
			int ruy,rdy,luy,ldy;
			int w=g_ciConstructionInfo[ReadyToBuild].BottomWidth;
			int l=g_ciConstructionInfo[ReadyToBuild].BottomLength;

			rux=left.x;ruy=left.y;
			rdx=left.x+l;rdy=ruy;
			ldx=right.x;ldy=right.y;
			lux=right.x-l;luy=ldy;
			
			if(CanPutHere())
				newPen=CreatePen(1,2,RGB(0,255,0));
			else
				newPen=CreatePen(1,2,RGB(255,0,0));
			oldPen=(HPEN)SelectObject(hDC,newPen);

			MoveToEx(hDC,30*(lux-luy),15*(lux+luy),NULL);
			LineTo(hDC,30*(rux-ruy),15*(rux+ruy));
			LineTo(hDC,30*(rdx-rdy),15*(rdx+rdy));
			LineTo(hDC,30*(ldx-ldy),15*(ldx+ldy));
			LineTo(hDC,30*(lux-luy),15*(lux+luy));

			if(ReadyToBuild==TESLA_COIL||
				ReadyToBuild==PRISM_TOWER||
				ReadyToBuild==PILL_BOX||
				ReadyToBuild==SENTRY_GUN)
			{
				SelectObject(hDC,oldPen);
				DeleteObject(newPen);
				

				int iAttackArea=1;
				if(ReadyToBuild==TESLA_COIL) iAttackArea++;

				rux=left.x-iAttackArea;ruy=left.y-iAttackArea;
				rdx=left.x+l+iAttackArea;rdy=ruy;
				ldx=right.x+iAttackArea;ldy=right.y+iAttackArea;
				lux=right.x-l-iAttackArea;luy=ldy;
			
				newPen=CreatePen(1,2,RGB(0,0,255));
				oldPen=(HPEN)SelectObject(hDC,newPen);
				
				MoveToEx(hDC,30*(lux-luy),15*(lux+luy),NULL);
				LineTo(hDC,30*(rux-ruy),15*(rux+ruy));
				LineTo(hDC,30*(rdx-rdy),15*(rdx+rdy));
				LineTo(hDC,30*(ldx-ldy),15*(ldx+ldy));
				LineTo(hDC,30*(lux-luy),15*(lux+luy));
			}


			SelectObject(hDC,oldPen);
			DeleteObject(newPen);
		}
		else
			g_pMouseSprite->Draw(hDC);
		break;	
	}	
}

void GameCycle()
{
	if(!g_bGameOver)
		g_pGame->UpdateSprites();
	
	if(g_gsGameState==gsGaming)
	{
		if(g_bNotLaunch)
		{
			g_iPassFrames++;
			if(g_iPassFrames>g_iStudyTime&&g_bNotStudy)
			{
				g_bNotStudy=FALSE;
		 		g_pNMSSprite->Open();
				g_dsWavList.PlayBuffer(NuclearReady,0);
			}
			else if(!g_bNotStudy&&g_iPassFrames>g_iStudyTime+g_iLaunchTime&&g_bNotLaunch)
			{
				g_bNotLaunch=FALSE;
				g_pNMSSprite->Lauch();
				g_dsWavList.PlayBuffer(NuclearLaunch,0);
				NuclearMissileSprite* pSprite=new NuclearMissileSprite(g_pNMissileBitmap);
				pSprite->SetPosition(585,455);
				g_pGame->AddSprite(pSprite);			
			}
		}

		if(--g_iEnimyTrigger<0)
		{
			g_iEnimyTrigger=g_iEnimyDelay=max(90,g_iEnimyDelay-rand()%30-10);
			AddEnimies();
		}

		if(--g_iPlaneTrigger<0)
		{
			g_iPlaneTrigger=g_iPlaneDelay=max(120,g_iPlaneDelay-rand()%30-10);
			PlaneEnimies();
		}

		if(--g_iChronoTrigger<0)
		{
			g_iChronoTrigger=g_iChronoDelay=max(120,g_iChronoDelay-rand()%30-10);
			g_iStartSection=min(8,max(CHRONO_TIME_LENGTH/30-g_iChronoDelay/30,1));
			ChronoEnimies();
		}
	}

	g_pMouseSprite->UpdateFrame();
	
	//双缓冲
	HDC hDC=GetDC(g_hWnd);	
	GamePaint(g_hOffscreenDC);	
	BitBlt(hDC,0,0,g_pGame->GetWidth(),g_pGame->GetHeight(),
		g_hOffscreenDC,0,0,SRCCOPY);	

	ReleaseDC(g_hWnd,hDC);
}

void HandleKeys()
{
	if(GetAsyncKeyState(VK_ESCAPE)<0)
		if(g_gsGameState==gsAbout||g_gsGameState==gsIntro)
		{
			g_gsGameState=gsMainMenu;
			NewMenu();
		}
}

void MouseButtonDown(int x, int y, BOOL bLeft)
{
	if(g_bGameOver) return;
	if(!bLeft) {g_pMouseSprite->SetCur(msNORMAL);g_pSellSprite->Click(0);}
	Sprite* pHit=g_pGame->IsPointInSprite(x,y);
	if(g_bSelecting)
	{
		if(!bLeft) g_bSelecting=FALSE;
		else if(bLeft&&CanPutHere())
		{
			for(int i=left.x;i<left.x+g_ciConstructionInfo[ReadyToBuild].BottomLength;i++)
				for(int j=left.y;j<left.y+g_ciConstructionInfo[ReadyToBuild].BottomWidth;j++)
				{
					g_bIsTaken[i][j+15]=TRUE;
				}
			
			int lx,ly,rx,ry;
			lx=30*(left.x-left.y);ly=15*(left.x+left.y);
			rx=30*(right.x-right.y);ry=15*(right.x+right.y);
			Construct((lx+rx)/2,(ly+ry)/2);
		}
	}
	if(pHit!=NULL)
	{
		IcoSprite* iSprite;KindOfCon kfc;

		switch(g_gsGameState)
		{
		case gsMainMenu:
			if(pHit->m_stType==stMENUITEM)
			{
				switch(((MenuItemSprite*)pHit)->m_mfFunc)
				{
				case mfGameStart:
					g_msMainMenu->ClearItems();
					g_pMovingPointerSprite->Kill();
					delete g_msMainMenu;					
					g_msMainMenu=NULL;
					
				//	NewGame();
					g_pGame->CleanupSprites();
					g_gsGameState=gsMission1;
					g_pMission1Sprite=new PicDelaySprite(g_pMission1Bitmap,66);
					g_pGame->AddSprite(g_pMission1Sprite);
// 				
					break;
				case mfGameEnd:
					ShowCursor(TRUE);
					if(IDYES==MessageBox(g_hWnd,"真的要退出嗎?","RA2",MB_YESNO))
					{
						PostQuitMessage(0);
					}
					ShowCursor(FALSE);
					break;
				case mfGameIntro:
					g_gsGameState=gsIntro;
					g_pGame->CleanupSprites();
					break;
				case mfGameAbout:
					g_gsGameState=gsAbout;
					g_pGame->CleanupSprites();
					break;
				}					
			}
			break;
		case gsGaming:	

			if(!bLeft&&pHit->m_stType==stCOUNTER)
			{
				CounterSprite* cSprite=(CounterSprite*)pHit;
				g_pIcoSprite[cSprite->m_iKind]->m_bsState=bsNone;
				cSprite->Kill();
				g_pIcoSprite[cSprite->m_iKind]->m_csCounter=NULL;
				g_iMoney+=cSprite->m_iUsedMoney;
				break;
			}

// 			if(pHit->m_stType==stFIX)
// 			{
// 				g_pFixSprite->Click();
// 				g_pSellSprite->Click(0);
// 				g_pMouseSprite->SetCur(msFIX);
// 				break;
// 			}
// 			else 
			if(pHit->m_stType==stSELL)
			{
				g_pSellSprite->Click();
		/*		g_pFixSprite->Click(0);*/
				g_pMouseSprite->SetCur(msSELL);
				break;
			}

			if(g_pMouseSprite->GetCur()==msSELL&&(pHit->m_stType==stCONSTRUCTION||pHit->m_stType==stDEFEND))
			{
				g_pMouseSprite->SetCur(msNORMAL);
				g_pSellSprite->Click();
		
				ConstructionSprite* cSprite=(ConstructionSprite*)pHit;
				cSprite->Sell();
		

				g_dsWavList.PlayBuffer(Usell,0);

				if(g_ciConstructionInfo[cSprite->m_kfcKind].Electricity>0) g_iTElectricity-=g_ciConstructionInfo[cSprite->m_kfcKind].Electricity;
				else g_iUElectricity-=g_ciConstructionInfo[cSprite->m_kfcKind].Electricity;

				if(g_iTElectricity+g_iUElectricity<=0)
				{
					g_bLowPower=TRUE;
					if(g_ciConstructionInfo[cSprite->m_kfcKind].Electricity>0)
						PlaySound(TEXT("res\\wav\\low power.wav"),NULL,SND_FILENAME|SND_ASYNC);
				}
				else
					g_bLowPower=FALSE;
				
				if(cSprite->m_kfcKind==POWER_PLANT||cSprite->m_kfcKind==NUCLEAR_REACTOR)
				{
					g_iPowerPlantCount--;
					if(g_iPowerPlantCount<=0)
					{
						for(int i=int(A_BATTLE_LAB);i<=int(NUCLEAR_REACTOR-1);i++)
							g_pIcoSprite[i]->SetHidden(TRUE);
					}
				}
				else if(cSprite->m_kfcKind==A_BATTLE_LAB)
				{
					g_iBattleLabCount--;
					if(g_iBattleLabCount<=0)
						g_pIcoSprite[NUCLEAR_REACTOR]->SetHidden(TRUE);
				}
				

				for(int i=cSprite->m_ptLeft.x;i<cSprite->m_ptLeft.x+g_ciConstructionInfo[cSprite->m_kfcKind].BottomLength;i++)
					for(int j=cSprite->m_ptLeft.y;j<cSprite->m_ptLeft.y+g_ciConstructionInfo[cSprite->m_kfcKind].BottomWidth;j++)
					{
						g_bIsTaken[i][j+15]=FALSE;
					}

				break;
			}

			if(pHit->m_stType!=stICO) break;
			iSprite=(IcoSprite*)pHit;
			kfc=iSprite->m_kfcKind;

			if(iSprite->m_bsState==bsNone&&bLeft&&g_pMouseSprite->GetCur()==msNORMAL)
			{
				iSprite->m_bsState=bsBuilding;
				RECT rt=iSprite->GetPosition();
				g_pCounterSprite=new CounterSprite(g_pCounterBitmap,kfc);
				g_pCounterSprite->SetPosition(rt.left,rt.top);
				g_pCounterSprite->SetFrameDelay((g_ciConstructionInfo[iSprite->m_kfcKind].Money+400)/1000+1);
				g_pCounterSprite->SetNumFrames(55,TRUE);
				iSprite->m_csCounter=g_pCounterSprite;
				g_pGame->AddSprite(g_pCounterSprite);
				
				g_dsWavList.PlayBuffer(Building,0);
			}
			else if(iSprite->m_bsState==bsComplete)
			{
				if(bLeft)
				{
					g_bSelecting=TRUE;
					ReadyToBuild=(KindOfCon)kfc;
					MovePlaceRect(x,y);
				}
				else
				{
					iSprite->m_bsState=bsNone;
					g_iMoney+=g_ciConstructionInfo[iSprite->m_kfcKind].Money;
				}
			}			
		//	AddEnimies();			
		}
		
	}
}

void MouseButtonUp(int x, int y, BOOL bLeft)
{
}

void MovePlaceRect(int x,int y)
{
	int ix,iy;
	
	ix=(x+y*2)/60;iy=(y-x/2+450)/30-15;
	int uselen,usewid;
	uselen=(g_ciConstructionInfo[ReadyToBuild].BottomLength)/2;usewid=(g_ciConstructionInfo[ReadyToBuild].BottomWidth)/2;
	
	left.x=ix-uselen;
	left.y=iy-usewid;
	
	uselen=g_ciConstructionInfo[ReadyToBuild].BottomLength-uselen;
	usewid=g_ciConstructionInfo[ReadyToBuild].BottomWidth-usewid;
	
	right.x=ix+uselen;
		right.y=iy+usewid;
}

void MouseMove(int x, int y)
{
	if(g_bGameOver) return;
	if(g_bSelecting)
	{	
		MovePlaceRect(x,y);		
	}
	else
	{
		if(g_pMouseSprite->GetCur()==msNORMAL)
			g_pMouseSprite->SetPosition(x,y);
		else
			g_pMouseSprite->SetPosition(x-g_pMouseSprite->GetWidth()/2,y-g_pMouseSprite->GetHeight()/2);
	}

	g_bShowInfo=FALSE;
	if(g_gsGameState==gsGaming)
	{
		Sprite* pHit=g_pGame->IsPointInSprite(x,y);
		if(pHit!=NULL&&g_pMouseSprite->GetCur()==msNORMAL)
		{
			if(pHit->m_stType==stICO)
			{
				g_siShowInfo.ptShowPos.x=x+15;
				g_siShowInfo.ptShowPos.y=y+13;
				g_siShowInfo.strInfo.Format("造价: %d",g_ciConstructionInfo[((IcoSprite*)pHit)->m_kfcKind].Money);
				g_bShowInfo=TRUE;
			}
			else if(pHit->m_stType==stTARGET)
			{
				g_siShowInfo.ptShowPos.x=x+15;
				g_siShowInfo.ptShowPos.y=y+13;
				g_siShowInfo.strInfo.Format("%d/%d",((TargetSprite*)pHit)->GetCurHP(),((TargetSprite*)pHit)->GetOrgHP());
				g_bShowInfo=TRUE;
			}
			else if(pHit->m_stType==stCONSTRUCTION)
			{
				if(((ConstructionSprite*)pHit)->m_kfcKind==POWER_PLANT||
					((ConstructionSprite*)pHit)->m_kfcKind==NUCLEAR_REACTOR)
				{
					g_siShowInfo.ptShowPos.x=x+15;
					g_siShowInfo.ptShowPos.y=y+13;
					g_siShowInfo.strInfo.Format("总电量:%d   负载:%d",g_iTElectricity,-g_iUElectricity);
					g_bShowInfo=TRUE;
				}
			}
		}

	}

}

void HandleJoystick(JOYSTATE jsJoystickState)
{
}

BOOL SpriteCollision(Sprite* pSpriteHitter,Sprite* pSpriteHittee)
{
	if(g_bGameOver) return FALSE;
	if((pSpriteHitter->m_stType==stDEFEND&&pSpriteHittee->m_stType==stPERSON)||
	   (pSpriteHittee->m_stType==stDEFEND&&pSpriteHitter->m_stType==stPERSON))
	{
		DefendSprite* dSprite;
		PersonSprite* pSprite;
		if(pSpriteHitter->m_stType==stDEFEND)
		{
			dSprite=(DefendSprite*)pSpriteHitter;
			pSprite=(PersonSprite*)pSpriteHittee;
		}
		else
		{
			dSprite=(DefendSprite*)pSpriteHittee;
			pSprite=(PersonSprite*)pSpriteHitter;
		}



// 		int px,py,dx,dy;
// 		
// 		px=(pSprite->m_ptCenter.x+pSprite->m_ptCenter.y*2)/60;py=(pSprite->m_ptCenter.y-pSprite->m_ptCenter.x/2+450)/30-15;
// 		dx=(dSprite->m_ptCenter.x+dSprite->m_ptCenter.y*2)/60;
// 		dy=(dSprite->m_ptCenter.y-dSprite->m_ptCenter.x/2+450)/30-15;
// 		int atarea=1;
// 		if(dSprite->m_kfcKind==TESLA_COIL) atarea++;
// 		if(abs(px-dx)>atarea+1||abs(py-dy)>atarea+1) return FALSE;
		

		int iAttackArea=1;
		if(dSprite->m_kfcKind==TESLA_COIL) iAttackArea++;

		int w=g_ciConstructionInfo[dSprite->m_kfcKind].BottomWidth;
		int l=g_ciConstructionInfo[dSprite->m_kfcKind].BottomLength;
		int rux,ruy,rdx,rdy,ldx,ldy,lux,luy;
		rux=dSprite->m_ptLeft.x-iAttackArea;ruy=dSprite->m_ptLeft.y-iAttackArea;
		rdx=dSprite->m_ptLeft.x+l+iAttackArea;rdy=ruy;
		ldx=dSprite->m_ptRight.x+iAttackArea;ldy=dSprite->m_ptRight.y+iAttackArea;
		lux=dSprite->m_ptRight.x-l-iAttackArea;luy=ldy;
		POINT pt[4]={{30*(lux-luy),15*(lux+luy)-10},{30*(rux-ruy)+10,15*(rux+ruy)},
			{30*(rdx-rdy),15*(rdx+rdy)+10},{30*(ldx-ldy)-10,15*(ldx+ldy)}};
		HRGN hRgn=CreatePolygonRgn(pt,4,ALTERNATE);
		if(!PtInRegion(hRgn,pSprite->m_ptCenter.x,pSprite->m_ptCenter.y))
		{
			DeleteObject(hRgn);
			return FALSE;
		}
		DeleteObject(hRgn);		
	

		if(pSprite->Dying()||pSprite->m_bFalling||dSprite->IsSelling()) return FALSE;
		if(g_bLowPower&&(dSprite->m_kfcKind==TESLA_COIL||dSprite->m_kfcKind==PRISM_TOWER))
			return FALSE;

		if(dSprite->GetState()==DS_WAIT)
		{
			dSprite->SetAttack(pSprite);
			dSprite->GetReady();
			switch (dSprite->m_kfcKind)
			{
			case TESLA_COIL:
				pSprite->m_dwDieWay=dwSHOCKED;
				g_dsWavList.PlayBuffer(TeslaPow,0);
				break;
			case PRISM_TOWER:
				pSprite->m_dwDieWay=dwSHOCKED;
				g_dsWavList.PlayBuffer(PrismPow,0);
				break;
			case PILL_BOX:
			case SENTRY_GUN:
				pSprite->m_dwDieWay=(rand()%3>=1)?dwNORMAL:dwBURNED;
			}
		}

	}
	else if((pSpriteHitter->m_stType==stTARGET&&pSpriteHittee->m_stType==stPERSON)||
	   (pSpriteHittee->m_stType==stTARGET&&pSpriteHitter->m_stType==stPERSON))
	{
		TargetSprite* tSprite;
		PersonSprite* pSprite;
		if(pSpriteHitter->m_stType==stTARGET)
		{
			tSprite=(TargetSprite*)pSpriteHitter;
			pSprite=(PersonSprite*)pSpriteHittee;
		}
		else
		{
			tSprite=(TargetSprite*)pSpriteHittee;
			pSprite=(PersonSprite*)pSpriteHitter;
		}
		
		if(pSprite->Dying()||pSprite->m_bFalling) return FALSE;
		if(tSprite->Dying())
		{
			pSprite->Stop(RIGHTDOWN);
			return FALSE;
		}
		if(pSprite->m_gsState==gsNoGoal)		
			pSprite->Attack(tSprite->GetCenter());

	}
	
	return FALSE;
}

BOOL SpriteDying(Sprite* pSpriteDying)
{

	if(pSpriteDying->m_stType==stTESLA)
	{
		if(((TeslaSprite*)pSpriteDying)->dsParentSprite!=NULL)
			((TeslaSprite*)pSpriteDying)->dsParentSprite->Work();
	}
	else if(pSpriteDying->m_stType==stPRISM)
	{
		if(((PrismSprite*)pSpriteDying)->dsParentSprite!=NULL)
			((PrismSprite*)pSpriteDying)->dsParentSprite->Work();
	}
	else if(pSpriteDying->m_stType==stPERSON)
	{
		PersonSprite* pPSprite=(PersonSprite*)pSpriteDying;
		POINT ptPos=((PersonSprite*)pSpriteDying)->GetCenter();
		Sprite* pSprite;

		switch(pPSprite->m_dwDieWay)
		{
		case dwNORMAL:			
			pSprite=new DieAshSprite(g_pManToAshBitmap,ptPos.x-26,ptPos.y-26,pPSprite->olddir);
			pSprite->SetNumFrames(12,TRUE);
			pSprite->SetZOrder(pPSprite->GetZOrder());
			pSprite->SetFrameDelay(5);
			break;
		case dwBURNED:
			pSprite=new Sprite(g_pManBurnedBitmap,ptPos.x-26,ptPos.y-26);
			pSprite->SetZOrder(pPSprite->GetZOrder());
			pSprite->SetNumFrames(108,TRUE);
			break;
		case dwRADIUM:
			pSprite=new Sprite(g_pManRadiumBitmap,ptPos.x-26,ptPos.y-26);
			pSprite->SetZOrder(pPSprite->GetZOrder());
			pSprite->SetNumFrames(60,TRUE);
			break;
		case dwSHOCKED:
			pSprite=new Sprite(g_pManShockedBitmap,ptPos.x-26,ptPos.y-26);
			pSprite->SetZOrder(pPSprite->GetZOrder());
			pSprite->SetNumFrames(15,TRUE);
			break;		
		}
		g_pGame->AddSprite(pSprite);
		g_iMoney+=100;
	}
	else if(pSpriteDying->m_stType==stTARGET)
	{
		PlaySound(TEXT("res\\wav\\Mission Failed.wav"),NULL,SND_FILENAME|SND_ASYNC);
		
		g_bWin=FALSE;
		g_pMissionEndSprite=new MissionEndSprite(g_pMissionEndBitmap,1,65);
		g_pMissionEndSprite->SetNumFrames(2);
		g_pMissionEndSprite->SetPosition(210,203);
		g_pGame->AddSprite(g_pMissionEndSprite);
		
		//don't add to gameengine
	}
	else if(pSpriteDying->m_stType==stNMISSILE)
	{
		g_dsWavList.PlayBuffer(Ucheer,0);

		PlaySound(TEXT("res\\wav\\Mission Accomplished.wav"),NULL,SND_FILENAME|SND_ASYNC);
		g_bWin=TRUE;
		g_pMissionEndSprite=new MissionEndSprite(g_pMissionEndBitmap,0,65);
		g_pMissionEndSprite->SetNumFrames(2);
		g_pMissionEndSprite->SetPosition(210,203);
		g_pGame->AddSprite(g_pMissionEndSprite);
	}
	else if(pSpriteDying->m_stType==stMISSIONEND)
	{
	//	g_bGameOver=FALSE;
		if(g_bWin)
		{
			g_pGame->CleanupSprites();
			g_pMissionEndSprite=NULL;
			g_gsGameState=gsMission2;
			g_pMission2Sprite=new PicDelaySprite(g_pMission2Bitmap,66);
			g_pGame->AddSprite(g_pMission2Sprite);	
			g_dsWavList.StopAllBuffers();
			
		}
		else
		{
			g_gsGameState=gsMainMenu;
		
			NewMenu();
			g_pMissionEndSprite=NULL;
			PlaySound(TEXT("res\\wav\\B Control Term.wav"),NULL,SND_FILENAME);
		}
		return FALSE;
	}
	else if(pSpriteDying->GetBitmap()==g_pMission1Bitmap)
	{
		NewGame();
		return FALSE;
	}
	else if(pSpriteDying->GetBitmap()==g_pMission2Bitmap)
	{

		NewMenu();
		return FALSE;
	}
	return TRUE;
}

void Construct(int x,int y)
{
	ConstructionSprite* newSprite;
	if(g_ciConstructionInfo[ReadyToBuild].AttackFrame==-1)	
		newSprite=new ConstructionSprite(g_pConstructionBitmap[ReadyToBuild],ReadyToBuild,left,right);
	else
		newSprite=(ConstructionSprite*)(new DefendSprite(g_pConstructionBitmap[ReadyToBuild],ReadyToBuild,left,right));
//	x-=g_ciConstructionInfo[ReadyToBuild].PLACE_X;
	y-=g_ciConstructionInfo[ReadyToBuild].PLACE_Y;
	
	newSprite->SetNumFrames(g_ciConstructionInfo[ReadyToBuild].NumFrames);
	newSprite->SetPosition(x,y);

/*	newSprite->SetArea(left);*/

	g_pGame->AddSprite(newSprite);

	if(g_ciConstructionInfo[ReadyToBuild].Electricity>0) g_iTElectricity+=g_ciConstructionInfo[ReadyToBuild].Electricity;
	else g_iUElectricity+=g_ciConstructionInfo[ReadyToBuild].Electricity;
	if(g_iTElectricity+g_iUElectricity<=0)
	{
		g_bLowPower=TRUE;
		if(g_ciConstructionInfo[ReadyToBuild].Electricity<0)
			PlaySound(TEXT("res\\wav\\low power.wav"),NULL,SND_FILENAME|SND_ASYNC);
	}

	else
		g_bLowPower=FALSE;


	g_pIcoSprite[ReadyToBuild]->m_bsState=bsNone;
	g_bSelecting=FALSE;
	g_dsWavList.PlayBuffer(Uplace,0);

	if(ReadyToBuild==POWER_PLANT||ReadyToBuild==NUCLEAR_REACTOR)
	{
		g_iPowerPlantCount++;
		for(int i=int(POWER_PLANT+1);i<=int(NUCLEAR_REACTOR-1);i++)
			g_pIcoSprite[i]->SetHidden(FALSE);
	}
	else if(ReadyToBuild==A_BATTLE_LAB)
	{
		g_iBattleLabCount++;
		g_pIcoSprite[NUCLEAR_REACTOR]->SetHidden(FALSE);
	}


	//reset readytobuild
}

void InitConstructionInfo()
{
	g_ciConstructionInfo[A_BATTLE_LAB].PLACE_X=3;
	g_ciConstructionInfo[A_BATTLE_LAB].PLACE_Y=30;
	g_ciConstructionInfo[A_BATTLE_LAB].Left=28;
	g_ciConstructionInfo[A_BATTLE_LAB].Right=35;
	g_ciConstructionInfo[A_BATTLE_LAB].Top=50;
	g_ciConstructionInfo[A_BATTLE_LAB].Bottom=50;
	g_ciConstructionInfo[A_BATTLE_LAB].BottomLength=3;
	g_ciConstructionInfo[A_BATTLE_LAB].BottomWidth=2;
	g_ciConstructionInfo[A_BATTLE_LAB].BuildTime=10;
	g_ciConstructionInfo[A_BATTLE_LAB].NumFrames=25;
	g_ciConstructionInfo[A_BATTLE_LAB].BuildFrame=1;
	g_ciConstructionInfo[A_BATTLE_LAB].WorkFrame=25;
	g_ciConstructionInfo[A_BATTLE_LAB].AttackFrame=-1;
	g_ciConstructionInfo[A_BATTLE_LAB].Money=2000;
	g_ciConstructionInfo[A_BATTLE_LAB].Electricity=-100;

	g_ciConstructionInfo[TESLA_COIL].PLACE_X=0;
	g_ciConstructionInfo[TESLA_COIL].PLACE_Y=10;
	g_ciConstructionInfo[TESLA_COIL].Left=10;
	g_ciConstructionInfo[TESLA_COIL].Right=10;
	g_ciConstructionInfo[TESLA_COIL].Top=45;
	g_ciConstructionInfo[TESLA_COIL].Bottom=20;
	g_ciConstructionInfo[TESLA_COIL].BottomLength=1;
	g_ciConstructionInfo[TESLA_COIL].BottomWidth=1;
	g_ciConstructionInfo[TESLA_COIL].BuildTime=10;
	g_ciConstructionInfo[TESLA_COIL].NumFrames=45;
	g_ciConstructionInfo[TESLA_COIL].BuildFrame=1;
	g_ciConstructionInfo[TESLA_COIL].WorkFrame=26;
	g_ciConstructionInfo[TESLA_COIL].AttackFrame=36;
	g_ciConstructionInfo[TESLA_COIL].Money=1500;
	g_ciConstructionInfo[TESLA_COIL].Electricity=-75;

	g_ciConstructionInfo[NUCLEAR_REACTOR].PLACE_X=9;
	g_ciConstructionInfo[NUCLEAR_REACTOR].PLACE_Y=52;
	g_ciConstructionInfo[NUCLEAR_REACTOR].Left=50;
	g_ciConstructionInfo[NUCLEAR_REACTOR].Right=75;
	g_ciConstructionInfo[NUCLEAR_REACTOR].Top=10;
	g_ciConstructionInfo[NUCLEAR_REACTOR].Bottom=70;
	g_ciConstructionInfo[NUCLEAR_REACTOR].BottomLength=4;
	g_ciConstructionInfo[NUCLEAR_REACTOR].BottomWidth=4;
	g_ciConstructionInfo[NUCLEAR_REACTOR].BuildTime=10;
	g_ciConstructionInfo[NUCLEAR_REACTOR].NumFrames=36;
	g_ciConstructionInfo[NUCLEAR_REACTOR].BuildFrame=1;
	g_ciConstructionInfo[NUCLEAR_REACTOR].WorkFrame=26;
	g_ciConstructionInfo[NUCLEAR_REACTOR].AttackFrame=-1;
	g_ciConstructionInfo[NUCLEAR_REACTOR].Money=1000;
	g_ciConstructionInfo[NUCLEAR_REACTOR].Electricity=1000;

	g_ciConstructionInfo[SENTRY_GUN].PLACE_X=-2;
	g_ciConstructionInfo[SENTRY_GUN].PLACE_Y=14;
	g_ciConstructionInfo[SENTRY_GUN].Left=14;
	g_ciConstructionInfo[SENTRY_GUN].Right=14;
	g_ciConstructionInfo[SENTRY_GUN].Top=4;
	g_ciConstructionInfo[SENTRY_GUN].Bottom=23;
	g_ciConstructionInfo[SENTRY_GUN].BottomLength=1;
	g_ciConstructionInfo[SENTRY_GUN].BottomWidth=1;
	g_ciConstructionInfo[SENTRY_GUN].BuildTime=10;
	g_ciConstructionInfo[SENTRY_GUN].NumFrames=13;
	g_ciConstructionInfo[SENTRY_GUN].BuildFrame=1;
	g_ciConstructionInfo[SENTRY_GUN].WorkFrame=13;
	g_ciConstructionInfo[SENTRY_GUN].AttackFrame=13;
	g_ciConstructionInfo[SENTRY_GUN].Money=500;
	g_ciConstructionInfo[SENTRY_GUN].Electricity=0;

	g_ciConstructionInfo[PILL_BOX].PLACE_X=-1;
	g_ciConstructionInfo[PILL_BOX].PLACE_Y=9;
	g_ciConstructionInfo[PILL_BOX].Left=17;
	g_ciConstructionInfo[PILL_BOX].Right=17;
	g_ciConstructionInfo[PILL_BOX].Top=2;
	g_ciConstructionInfo[PILL_BOX].Bottom=21;
	g_ciConstructionInfo[PILL_BOX].BottomLength=1;
	g_ciConstructionInfo[PILL_BOX].BottomWidth=1;
	g_ciConstructionInfo[PILL_BOX].BuildTime=10;
	g_ciConstructionInfo[PILL_BOX].NumFrames=9;
	g_ciConstructionInfo[PILL_BOX].BuildFrame=1;
	g_ciConstructionInfo[PILL_BOX].WorkFrame=9;
	g_ciConstructionInfo[PILL_BOX].AttackFrame=9;
	g_ciConstructionInfo[PILL_BOX].Money=500;
	g_ciConstructionInfo[PILL_BOX].Electricity=0;

	g_ciConstructionInfo[PRISM_TOWER].PLACE_X=-1;
	g_ciConstructionInfo[PRISM_TOWER].PLACE_Y=10;
	g_ciConstructionInfo[PRISM_TOWER].Left=10;
	g_ciConstructionInfo[PRISM_TOWER].Right=10;
	g_ciConstructionInfo[PRISM_TOWER].Top=61;
	g_ciConstructionInfo[PRISM_TOWER].Bottom=21;
	g_ciConstructionInfo[PRISM_TOWER].BottomLength=1;
	g_ciConstructionInfo[PRISM_TOWER].BottomWidth=1;
	g_ciConstructionInfo[PRISM_TOWER].BuildTime=10;
	g_ciConstructionInfo[PRISM_TOWER].NumFrames=27;
	g_ciConstructionInfo[PRISM_TOWER].BuildFrame=1;
	g_ciConstructionInfo[PRISM_TOWER].WorkFrame=9;
	g_ciConstructionInfo[PRISM_TOWER].AttackFrame=18;
	g_ciConstructionInfo[PRISM_TOWER].Money=1500;
	g_ciConstructionInfo[PRISM_TOWER].Electricity=-75;

	g_ciConstructionInfo[POWER_PLANT].PLACE_X=-3;
	g_ciConstructionInfo[POWER_PLANT].PLACE_Y=28;
	g_ciConstructionInfo[POWER_PLANT].Left=23;
	g_ciConstructionInfo[POWER_PLANT].Right=23;
	g_ciConstructionInfo[POWER_PLANT].Top=27;
	g_ciConstructionInfo[POWER_PLANT].Bottom=38;
	g_ciConstructionInfo[POWER_PLANT].BottomLength=2;
	g_ciConstructionInfo[POWER_PLANT].BottomWidth=2;
	g_ciConstructionInfo[POWER_PLANT].BuildTime=10;
	g_ciConstructionInfo[POWER_PLANT].NumFrames=33;
	g_ciConstructionInfo[POWER_PLANT].BuildFrame=1;
	g_ciConstructionInfo[POWER_PLANT].WorkFrame=26;
	g_ciConstructionInfo[POWER_PLANT].AttackFrame=-1;
	g_ciConstructionInfo[POWER_PLANT].Money=800;
	g_ciConstructionInfo[POWER_PLANT].Electricity=200;
}

void InitPersonInfo()
{
	g_piPersonInfo[CONSCRIPT].NumFrames=261;
	g_piPersonInfo[CONSCRIPT].StandFrame=1;
	g_piPersonInfo[CONSCRIPT].StandCount=1;
	g_piPersonInfo[CONSCRIPT].WalkFrame=9;
	g_piPersonInfo[CONSCRIPT].WalkCount=6;
	g_piPersonInfo[CONSCRIPT].CreepFrame=87;
	g_piPersonInfo[CONSCRIPT].CreepCount=6;
	g_piPersonInfo[CONSCRIPT].DieFrame=135;
	g_piPersonInfo[CONSCRIPT].DieCount=15;
	g_piPersonInfo[CONSCRIPT].AttackFrame=165;
	g_piPersonInfo[CONSCRIPT].AttackCount=6;
	g_piPersonInfo[CONSCRIPT].LayAttackFrame=213;
	g_piPersonInfo[CONSCRIPT].LayAttackCount=6;
	g_piPersonInfo[CONSCRIPT].FallingFrame=261;

	g_piPersonInfo[DESOLATOR]=g_piPersonInfo[CONSCRIPT];

	g_piPersonInfo[EVAN]=g_piPersonInfo[CONSCRIPT];
	g_piPersonInfo[EVAN].NumFrames=212;
	g_piPersonInfo[EVAN].LayAttackFrame=g_piPersonInfo[EVAN].LayAttackCount=0;
	g_piPersonInfo[EVAN].FallingFrame=0;

	g_piPersonInfo[FLAK_TROOPER].NumFrames=294;
	g_piPersonInfo[FLAK_TROOPER].StandFrame=1;
	g_piPersonInfo[FLAK_TROOPER].StandCount=1;
	g_piPersonInfo[FLAK_TROOPER].WalkFrame=9;
	g_piPersonInfo[FLAK_TROOPER].WalkCount=6;
	g_piPersonInfo[FLAK_TROOPER].DieFrame=87;
	g_piPersonInfo[FLAK_TROOPER].DieCount=15;
	g_piPersonInfo[FLAK_TROOPER].AttackFrame=117;
	g_piPersonInfo[FLAK_TROOPER].AttackCount=6;
	g_piPersonInfo[FLAK_TROOPER].CreepFrame=166;
	g_piPersonInfo[FLAK_TROOPER].CreepCount=6;
	g_piPersonInfo[FLAK_TROOPER].LayAttackFrame=246;
	g_piPersonInfo[FLAK_TROOPER].LayAttackCount=6;
	g_piPersonInfo[FLAK_TROOPER].FallingFrame=294;

	g_piPersonInfo[LAND_ROCKETEER]=g_piPersonInfo[CONSCRIPT];

	g_piPersonInfo[ROCKETEER].NumFrames=127;
	g_piPersonInfo[ROCKETEER].StandFrame=1;
	g_piPersonInfo[ROCKETEER].StandCount=1;
	g_piPersonInfo[ROCKETEER].WalkFrame=1;
	g_piPersonInfo[ROCKETEER].WalkCount=6;
	g_piPersonInfo[ROCKETEER].CreepFrame=0;
	g_piPersonInfo[ROCKETEER].CreepCount=0;
	g_piPersonInfo[ROCKETEER].DieFrame=49;
	g_piPersonInfo[ROCKETEER].DieCount=15;
	g_piPersonInfo[ROCKETEER].AttackFrame=79;
	g_piPersonInfo[ROCKETEER].AttackCount=6;
	g_piPersonInfo[ROCKETEER].LayAttackFrame=0;
	g_piPersonInfo[ROCKETEER].LayAttackCount=0;
	g_piPersonInfo[ROCKETEER].FallingFrame=127;

	g_piPersonInfo[SNIPER]=g_piPersonInfo[CONSCRIPT];

	g_piPersonInfo[TESLA_TROOPER]=g_piPersonInfo[CONSCRIPT];
}

BOOL CanPutHere()
{
	int lx,ly,rx,ry;
	lx=30*(left.x-left.y);ly=15*(left.x+left.y);
	rx=30*(right.x-right.y);ry=15*(right.x+right.y);
	lx=(lx+rx)/2;
	ly=(ly+ry)/2;
	if(lx<0||ly<0||lx>856||ly>630) return FALSE;
	for(int i=left.x;i<left.x+g_ciConstructionInfo[ReadyToBuild].BottomLength;i++)
		for(int j=left.y;j<left.y+g_ciConstructionInfo[ReadyToBuild].BottomWidth;j++)
		{
			if(g_bIsTaken[i][j+15]==TRUE)
				return FALSE;
		}

	return TRUE;
}

void NewMenu()
{
	g_gsGameState=gsMainMenu;
	g_dsWavList.StopAllBuffers();
	g_bSelecting=FALSE;
	g_pGame->CleanupSprites();
	g_pMouseSprite->SetCur(msNORMAL);

	g_msMainMenu=new MenuSprite();
	g_pMovingPointerSprite=new Sprite(g_pMovingPointerBitmap);
	g_pMovingPointerSprite->SetPosition(894,48);
	g_pMovingPointerSprite->SetNumFrames(91,FALSE);
	g_pGame->AddSprite(g_pMovingPointerSprite);
}


void ConstructNMS()
{
	g_pNMSSprite=new TargetSprite(g_pNMSBitmap);
	g_pNMSSprite->SetNumFrames(94);
	g_pNMSSprite->SetPosition(500,455);
	g_pGame->AddSprite(g_pNMSSprite);
	g_dsWavList.PlayBuffer(Uplace,0);
}

void NewGame()
{
// 	g_dvVideo.Stop();
// 	g_dvVideo.Close();

/*	if(g_gsGameState!=gsMission1)*/
	g_gsGameState=gsGaming;
		g_pGame->CleanupSprites();

		g_iStartSection=1;
	for(int i=0;i<50;i++)
		for(int j=0;j<50;j++)
			g_bIsTaken[i][j]=FALSE;
	InitPath();
	

	g_iPassFrames=0;
	g_iStudyTime=STUDY_TIME_LENGTH+rand()%(10*30);
	g_iLaunchTime=LAUNCH_TIME_LENGTH+rand()%(10*30);
	g_bNotStudy=TRUE;
	g_bNotLaunch=TRUE;

	g_iPlaneTrigger=g_iPlaneDelay=PLANE_TIME_LENGTH;
	g_iChronoTrigger=g_iChronoDelay=CHRONO_TIME_LENGTH;
	g_iEnimyTrigger=g_iEnimyDelay=ENIMY_TIME_LENGTH;

	g_iMoney=8000;
	g_iTElectricity=g_iUElectricity=0;

	SetIcoSprite();
	ConstructNMS();

	Sprite* pSprite=new Sprite(g_pRadarBitmap);
	pSprite->SetPosition(856,47);
	pSprite->SetZOrder(10000);
	pSprite->SetNumFrames(33,TRUE);
	g_pGame->AddSprite(pSprite);
	g_dsWavList.PlayBuffer(RadarOn,0);

	g_pSideSprite=new Sprite(g_pSideBitmap);
	g_pSideSprite->SetZOrder(2000);
	g_pGame->AddSprite(g_pSideSprite);

// 	g_pFixSprite=new PadButtonSprite(g_pFixBitmap,stFIX);
// 	g_pFixSprite->SetNumFrames(2);
// 	g_pFixSprite->SetPosition(888,165);
// 	g_pGame->AddSprite(g_pFixSprite);

	g_pSellSprite=new PadButtonSprite(g_pSellBitmap,stSELL);
	g_pSellSprite->SetNumFrames(2);
	g_pSellSprite->SetPosition(940,165);
	g_pGame->AddSprite(g_pSellSprite);

	g_gsGameState=gsGaming;
}



void InitPath()
{
	int i,j,k;
	for(i=0;i<9;i++)
	{
		for(j=Node[i][0].x;j<Node[i][1].x;j++)
			for(k=Node[i][0].y;k<Node[i][1].y;k++)
				g_bIsTaken[j][k+15]=TRUE;
	}
	for(j=29;j<32;j++)
		for(k=8;k<11;k++)
				g_bIsTaken[j][k+15]=TRUE;

}

void AddEnimies()
{
	for(int i=0;i<6;i++)
	{
		PersonSprite* newSprite;
		int j=rand()%((int)TESLA_TROOPER+1);
		newSprite=new PersonSprite(g_pPersonBitmap[j],Path[0].x+15*(rand()%5-2),Path[0].y+15*(rand()%5-2),(KindOfPerson)j);
		newSprite->SetNumFrames(g_piPersonInfo[j].NumFrames);
		g_pGame->AddSprite(newSprite);
	}
}

void PlaneEnimies()
{
	int section=g_iStartSection+rand()%(10-g_iStartSection);//3-7
	POINT ptCenter;
	int rm,rz;

	rm=rand()%10+1;
	rz=rand()%rm;
	
	ptCenter.x=Path[section-1].x+(Path[section].x-Path[section-1].x)*rz/rm;
	ptCenter.y=Path[section-1].y+(Path[section].y-Path[section-1].y)*rz/rm;

	PlaneSprite* Plane=new PlaneSprite(g_pPlaneBitmap,ptCenter);
	Plane->SetNextNode(section);
	g_pGame->AddSprite(Plane);

	g_dsWavList.PlayBuffer(PlaneOver,DSBPLAY_LOOPING);
}

void ChronoEnimies()
{
	int section=g_iStartSection+rand()%(10-g_iStartSection);//3-7
	POINT ptCenter;
	int rm,rz;

	rm=rand()%10+1;
	rz=rand()%rm;

	ptCenter.x=Path[section-1].x+(Path[section].x-Path[section-1].x)*rz/rm;
	ptCenter.y=Path[section-1].y+(Path[section].y-Path[section-1].y)*rz/rm;

	ChronoSprite* Chrono=new ChronoSprite(g_pChronoBitmap,section);
	Chrono->SetNumFrames(17,TRUE);
	Chrono->SetPosition(ptCenter.x-Chrono->GetWidth()/2-25,ptCenter.y-Chrono->GetHeight()/2-30);
	g_pGame->AddSprite(Chrono);
	//Wav here
	g_dsWavList.PlayBuffer(ChronoLaunch,0);
}