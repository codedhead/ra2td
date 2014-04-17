//   DigitalVideo.cpp:   implementation   of   the   CDigitalvideo   class.   
  //   
  //////////////////////////////////////////////////////////////////////   
  #include   "afx.h"   
  //#include   "VideoPlayer.h"   
  #include   "Digitalvideo.h"   
    
  #ifdef   _DEBUG   
  #undef   THIS_FILE   
  static   char   THIS_FILE[]=__FILE__;   
  #define   new   DEBUG_NEW   
  #endif   
    
  //////////////////////////////////////////////////////////////////////   
  //   Construction/Destruction   
  //////////////////////////////////////////////////////////////////////   
    
  CDigitalvideo::CDigitalvideo()   
  {   
  //   ��ʼ����Ա����   
  m_Open   =   m_Pause   =   m_Playing   =   FALSE;   
  m_DeviceID   =   0;   
  }   
    
  CDigitalvideo::~CDigitalvideo()   
  {   
  Close   ();   
  }   
  BOOL   CDigitalvideo::GetPause   ()//�Ƿ���ͣ   
  {   
  return   m_Pause;   
  }   
  BOOL   CDigitalvideo::Open   (CString   Filename,   HWND hWnd,   int   left,   int   top,int   width,int   height)   
  {   
  if   (!m_Open){//���m_Open=false��û�д��豸   
  //   ��ʼ����Ա����   
  m_Open   =   m_Pause   =   m_Playing   =   FALSE;   
  m_DeviceID   =   0;   
  //   �ļ��Ƿ����   
  CFileStatus   Status;   
  if   (!CFile::GetStatus   (Filename,   Status))   
  return   FALSE;   
  //   ���豸   
  MCI_DGV_OPEN_PARMS   MCIOpen;   
  MCIOpen.lpstrDeviceType   =   "avivideo";//���ò����豸Ϊ��Ƶ�����豸   
  MCIOpen.lpstrElementName   =   (LPSTR)   Filename.GetBuffer   (0);//�ļ���   
  MCIOpen.wDeviceID   =   NULL;   
  MCIOpen.hWndParent   =   hWnd;//�ɲ�����Ƶ�ļ�����ָ��   
  MCIOpen.dwStyle   =   WS_CHILD   |   WS_VISIBLE;   
  if   (mciSendCommand   (NULL,   MCI_OPEN,   MCI_WAIT   |   MCI_OPEN_TYPE   |   
  MCI_OPEN_ELEMENT   |   MCI_DGV_OPEN_PARENT   |   MCI_DGV_OPEN_WS,   (DWORD)(LPVOID)   &MCIOpen))   
  return   FALSE;   
  m_DeviceID   =   MCIOpen.wDeviceID;   
  m_Open   =   TRUE;   
  //   ���ļ���������Ϊ֡   
  MCI_DGV_SET_PARMS   MCISet;   
  MCISet.dwTimeFormat   =   MCI_FORMAT_FRAMES;   
  if   (mciSendCommand   (m_DeviceID,   MCI_SET,   MCI_SET_TIME_FORMAT,   (DWORD)(LPVOID)   &MCISet))
  {   
  Close   ();   
  return   FALSE;   
  }   
  //   �ҵ���Ƶ�ļ��Ŀ�ʼλ��   
  mciSendCommand   (m_DeviceID,   MCI_SEEK,   MCI_SEEK_TO_START,   NULL);   
  //�����Ż�������������֮��   
  MCI_DGV_PUT_PARMS   MCIPut;   
  MCIPut.rc.left   =   left;   
  MCIPut.rc.top     =   top;   
  MCIPut.rc.right   =   width;   
  MCIPut.rc.bottom   =   height;   
  if   (mciSendCommand   (m_DeviceID,   MCI_PUT,   MCI_WAIT   |   MCI_DGV_PUT_CLIENT   |   
  MCI_DGV_PUT_WINDOW   |   MCI_DGV_RECT,   (DWORD)(LPVOID)   &MCIPut)){   
  Close   ();   
  return   FALSE;   
  }   
  }   
  return   TRUE;   
  }   
  void   CDigitalvideo::Close   (void)   
  {   
  if   (m_Open){//   ֹͣ���Ų��ر��豸   
  if   (m_Playing   ||   m_Pause)   
  mciSendCommand   (m_DeviceID,   MCI_STOP,   NULL,   NULL);   
  mciSendCommand   (m_DeviceID,   MCI_CLOSE,   NULL,   NULL);   
  //   ��ճ�Ա����   
  m_Open   =   m_Pause   =   m_Playing   =   FALSE;   
  m_DeviceID   =   NULL;   
  }   
  }   
  //�����Ƶ�ļ����ڵĿ���   
  int   CDigitalvideo::GetWidth   (void)   
  {   
  if   (m_Open){   
  MCI_DGV_WHERE_PARMS   MCIWhere;   
  if   (mciSendCommand   (m_DeviceID,   MCI_WHERE,   MCI_DGV_WHERE_SOURCE,   
  (DWORD)(LPVOID)   &MCIWhere)){   
  return   0;   
  }   
  return   (int)   MCIWhere.rc.right;   
  }   
  return   0;   
  }   
  //�����Ƶ�ļ����ڵĸ߶�   
  int   CDigitalvideo::GetHeight   (void)   
  {   
  if   (m_Open){   
  MCI_DGV_WHERE_PARMS   MCIWhere;   
  if   (mciSendCommand   (m_DeviceID,   MCI_WHERE,   MCI_DGV_WHERE_SOURCE,     
  (DWORD)(LPVOID)   &MCIWhere)){   
  return   0;   
  }   
  return   (int)   MCIWhere.rc.bottom;   
  }   
  return   0;   
  }   
  BOOL   CDigitalvideo::Play   (BOOL   bLoop,   BOOL   bFullScreen)   
  {   
  if   (m_Open){   
  //   �������Ƶ��β�������¿�ʼ����   
  if   (GetFrame   ()   >=   GetFrames   ())   
  mciSendCommand   (m_DeviceID,   MCI_SEEK,   MCI_SEEK_TO_START,   NULL);   
  //   ����   
  MCI_DGV_PLAY_PARMS   MCIPlay;   
  MCIPlay.dwCallback   =   NULL;   
  MCIPlay.dwFrom   =   GetFrame   ();   
  DWORD   dwFlags   =   MCI_FROM;   
  if   (bLoop)   
  dwFlags   |=   MCI_DGV_PLAY_REPEAT;   
  if   (bFullScreen)   
  dwFlags   |=   MCI_MCIAVI_PLAY_FULLSCREEN;   
  if   (mciSendCommand   (m_DeviceID,   MCI_PLAY,   dwFlags,   (DWORD)(LPVOID)   &MCIPlay))   
  return   FALSE;   
  m_Pause   =   FALSE;   
  m_Playing   =   TRUE;   
  return   TRUE;   
  }   
  return   FALSE;   
  }   
  void   CDigitalvideo::Stop   (void)   
  {   
  if   (m_Open   &&   m_Playing){   
  mciSendCommand   (m_DeviceID,   MCI_STOP,   NULL,   NULL);   
  mciSendCommand   (m_DeviceID,   MCI_SEEK,   MCI_SEEK_TO_START,   NULL);   
  m_Playing   =   FALSE;   
  m_Pause   =   TRUE;   
  }   
  }   
  void   CDigitalvideo::Pause(   void   )   
  {   
  if   (m_Open   ){   
  MCI_DGV_PAUSE_PARMS   MCIPause;   
  if   (mciSendCommand   (m_DeviceID,   MCI_PAUSE,   0,   (DWORD)(LPVOID)   &MCIPause))   
  return;   
  m_Pause   =   TRUE;   
  }   
  }   
  int   CDigitalvideo::GetFrames   (void)   
  {   
  if   (m_Open){   
  MCI_DGV_STATUS_PARMS   MCIStatus;   
  MCIStatus.dwItem   =   MCI_STATUS_LENGTH;   
  if   (mciSendCommand   (m_DeviceID,   MCI_STATUS,   MCI_WAIT   |   
  MCI_STATUS_ITEM,   (DWORD)(LPVOID)   &MCIStatus))   
  return   0;   
  return   (int)   MCIStatus.dwReturn;   
  }   
  return   0;   
  }   
  int   CDigitalvideo::GetFrame   (void)   
  {   
  if   (m_Open){   
  MCI_DGV_STATUS_PARMS   MCIStatus;   
  MCIStatus.dwItem   =   MCI_STATUS_POSITION;   
  if   (mciSendCommand   (m_DeviceID,   MCI_STATUS,   MCI_WAIT   |   
  MCI_STATUS_ITEM,   (DWORD)(LPVOID)   &MCIStatus))   
  return   -1;   
  return   (int)   MCIStatus.dwReturn;   
  }   
  return   -1;   
  }   
  BOOL   CDigitalvideo::IsPlaying   ()   
  {   
  if   (m_Open)   
  {   
  MCI_DGV_STATUS_PARMS   MCIStatus;   
  MCIStatus.dwItem   =   MCI_STATUS_MODE;   
  if   (mciSendCommand   (m_DeviceID,   MCI_STATUS,   MCI_WAIT   |   
  MCI_STATUS_ITEM,   (DWORD)(LPVOID)   &MCIStatus))   
  return   FALSE;   
  if   (MCIStatus.dwReturn   ==   MCI_MODE_PLAY)   
  {   
  m_Playing   =   TRUE;   
  m_Pause   =   FALSE;   
  return   TRUE;   
  }   
  else   if   (MCIStatus.dwReturn   ==   MCI_MODE_PAUSE)   
  {   
  m_Playing   =   TRUE;   
  m_Pause   =   FALSE;   
  return   TRUE;   
  }   
  else   
  {   
  m_Playing   =   FALSE;   
  m_Pause   =   FALSE;   
  return   FALSE;   
  }   
  }   
  return   FALSE;   
  }   
  BOOL   CDigitalvideo::SeekTo   (int   nFrame)   
  {   
  if   (m_Open){   
  MCI_SEEK_PARMS   MCISeek;   
  MCISeek.dwTo   =   nFrame;   
  if   (m_Playing   &&   !m_Pause)   
  mciSendCommand   (m_DeviceID,   MCI_PAUSE,   0,   NULL);   
  if   (mciSendCommand   (m_DeviceID,   MCI_SEEK,   MCI_TO   |     
  MCI_WAIT,   (DWORD)(LPVOID)   &MCISeek))   
  return   FALSE;   
  if   (m_Playing   &&   !m_Pause)   
  Play   ();   
  return   TRUE;   
  }   
  return   FALSE;   
  }   
  void   CDigitalvideo::Forward   (int   nFrames)   
  {   
  if   (m_Open){   
  if   (m_Playing   &&   !m_Pause)   
  Pause   ();   
  MCI_DGV_STEP_PARMS   MCIStep;   
  MCIStep.dwFrames   =   nFrames;   
  mciSendCommand   (m_DeviceID,   MCI_STEP,   MCI_DGV_STEP_FRAMES,     
  (DWORD)(LPVOID)   &MCIStep);   
  }   
  }   
  void   CDigitalvideo::Backward   (int   nFrames)   
  {   
  if   (m_Open){   
  if   (m_Playing   &&   !m_Pause)   
  Pause   ();   
  MCI_DGV_STEP_PARMS   MCIStep;   
  MCIStep.dwFrames   =   nFrames;   
  mciSendCommand   (m_DeviceID,   MCI_STEP,   MCI_DGV_STEP_REVERSE   |   
  MCI_DGV_STEP_FRAMES,   (DWORD)(LPVOID)   &MCIStep);   
  }   
  }   
  int   CDigitalvideo::GetSpeed   (void)   
  {   
  if   (m_Open){   
  MCI_DGV_STATUS_PARMS   MCIStatus;   
  MCIStatus.dwItem   =   MCI_DGV_STATUS_SPEED;   
  if   (mciSendCommand   (m_DeviceID,   MCI_STATUS,   MCI_WAIT   |   
  MCI_STATUS_ITEM,   (DWORD)(LPVOID)   &MCIStatus))   
  return   -1;   
  return   (int)   MCIStatus.dwReturn;   
  }   
  return   -1;   
  }   
  void   CDigitalvideo::SetSpeed   (int   nSpeed)   
  {   
  if   (m_Open){   
  MCI_DGV_SET_PARMS   MCISet;   
  MCISet.dwSpeed   =   nSpeed;   
  mciSendCommand   (m_DeviceID,   MCI_SET,   MCI_WAIT   |   
  MCI_DGV_SET_SPEED,   (DWORD)(LPVOID)   &MCISet);   
  }   
  }