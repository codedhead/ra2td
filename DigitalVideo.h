#if   !defined(AFX_VIDEO_H__B35A40D1_7DB7_11D3_860F_F6E44D6C9F3C__INCLUDED_)   
  #define   AFX_VIDEO_H__B35A40D1_7DB7_11D3_860F_F6E44D6C9F3C__INCLUDED_   
    
  #if   _MSC_VER   >   1000   
  #pragma   once   
  #endif   //   _MSC_VER   >   1000   
    
    
  #include   <afxwin.h>   
  #include   <mmsystem.h>   
  #include   <mciavi.h>   
  #include   <digitalv.h>   
    
  class   CDigitalvideo     //������Ƶ��   
  {   
  public:   
  CDigitalvideo();//���캯��   
  virtual   ~CDigitalvideo();//������   
  //��Ƶ��������   
  //��������-����Ƶ�ļ���pWnd--��Ҫ������Ƶ���Ŵ��ڵ������ڣ�   
  //left��top-��Ƶ���Ŵ������������е����Ͻ�����   
  BOOL   Open   (CString,   HWND   hWnd,   int   left   =   0,   //��������-����Ƶ�ļ�   
  int   top   =   0,int   width   =   20,int   height   =   20);   
  void   Close   (void);//�ر���Ƶ�ļ�   
  BOOL   Play   (BOOL   bLoop   =   FALSE,   BOOL   bFullScreen   =   FALSE);//��������-������Ƶ�ļ�   
  void   Stop   (void);       //ֹͣ����   
  void   Pause   (void);     //��ͣ����   
  void   Forward   (int);//���   
  void   Backward   (int);//����   
  BOOL   SeekTo   (int);//����ĳһλ��,������ͣ״̬   
  //��Ƶ״̬���غ���   
  int   GetWidth   (void);//�õ���Ƶ����   
  int   GetHeight   (void);//�����Ƶ�߶�   
  int   GetFrames   (void);//�����Ƶ��֡��   
  int   GetFrame   (void);//��õ�ǰ֡   
  BOOL   IsPlaying   ();//�Ƿ����ڲ���   
  int   GetSpeed   (void);//��ò����ٶ�   
  void   SetSpeed   (int);//���ò����ٶ�   
  BOOL   GetPause   (void);//�Ƿ���ͣ   
  private://���ݳ�Ա   
  BOOL   m_Open;//�Ƿ���ý���ļ���   
  BOOL   m_Pause;//�Ƿ���ͣ   
  BOOL   m_Playing;//�Ƿ����ڲ���   
  WORD   m_DeviceID;//�����豸ID   
  };   
    
  #endif   //   !defined(AFX_VIDEO_H__B35A40D1_7DB7_11D3_860F_F6E44D6C9F3C__INCLUDED_)   
  