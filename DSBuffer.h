// DSBuffer.h : Definition of CDSBuffer class
//
#pragma once

// #ifndef DWORD_PTR
// #define DWORD_PTR DWORD*
// #endif

#include "afx.h"

#include <mmsystem.h>
#include <dsound.h>



struct WaveHeader
{
	BYTE        RIFF[4];          // "RIFF"
	DWORD       dwSize;           // Size of data to follow
	BYTE        WAVE[4];          // "WAVE"
	BYTE        fmt_[4];          // "fmt "
	DWORD       dw16;             // 16
	WORD        wOne_0;           // 1
	WORD        wChnls;           // Number of Channels
	DWORD       dwSRate;          // Sample Rate
	DWORD       BytesPerSec;      // Sample Rate
	WORD        wBlkAlign;        // 1
	WORD        BitsPerSample;    // Sample size
	BYTE        DATA[4];          // "DATA"
	DWORD       dwDSize;          // Number of Samples
};

class CDSBuffer:public CObject
{
	// Attribute
protected:
	LPDIRECTSOUNDBUFFER  m_lpDSBuffer;   // Sound buffer
	LPDIRECTSOUND3DBUFFER m_lpDS3DBuffer;   // 3D buffer
	
	// Construction / Destruction
public:
	CDSBuffer();
	CDSBuffer(const char* FileName, LPDIRECTSOUND lpDS, DWORD dwFlags = DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLFREQUENCY);
	~CDSBuffer();
	
	// Methods
public:
	BOOL PlaySound(DWORD dwFlags);
	BOOL StopSound();
	BOOL CreateSoundBuffer(LPDIRECTSOUND lpDS, DWORD dwFlags, DWORD dwBufSize, DWORD dwFreq, DWORD dwBitsPerSample, DWORD dwBlkAlign, BOOL bStereo);
	BOOL ReadData(FILE* pFile, DWORD dwSize, DWORD dwPos);
	BOOL IsValid();
	LPDIRECTSOUNDBUFFER  GetBuffer() { return m_lpDSBuffer;}
	LPDIRECTSOUND3DBUFFER Get3DBuffer() { return m_lpDS3DBuffer;}
};
