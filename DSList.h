// DSList.h : Definition of CDSList class
//
#pragma once

#include "DSBuffer.h"

class CDSList : virtual protected CObList
{
	// Attribute
private:
	LPDIRECTSOUND m_lpDS;   // DirectSound Object
	
	// Construction / Destruction
public:
	CDSList();
	~CDSList();
	
	// Methods
public:
	BOOL Init();
	BOOL StopAllBuffers();
	BOOL AddNewBuffer(const char* FileName);
	BOOL RemoveBuffer(int nBuffer);
	BOOL PlayBuffer(int nBuffer, DWORD dwFlags);
	BOOL StopBuffer(int nBuffer);
	LPDIRECTSOUND GetDSObject() {return m_lpDS;}
};
