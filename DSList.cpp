///////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                             DirectSound Mixer                             //
//                                                                           //
//                      V1.0 by lob_b@hotmail.com 1999                       //
//                                                                           //
//                           with core inputs from                           //
//                                 Stack-Up                                  //
//                    V1.0 ?Tool@theWaterCooler.com 1998                    //
//                    http://www.theWaterCooler.com/Tool                     //
//                        also Petr.Stejskal@vslib.cz                        //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

// DSList.cpp : Implementation of CDSList class
//

#include "DSList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern HWND g_hWnd;

/////////////////////////////////////////////////////////////////////////////
// CDSList

CDSList::CDSList()
{
	// Reset the DirectSound pointer
	m_lpDS = NULL;
}


CDSList::~CDSList()
{
	// Stop all playing buffers
	StopAllBuffers();
	
	if(m_lpDS)
	{
		m_lpDS->Release();
	}
}


BOOL CDSList::Init()
{
	// Create DirectSound Object
	if (DS_OK != DirectSoundCreate(NULL, &m_lpDS, NULL))
	{
		MessageBox(g_hWnd,"Error - DS - Create\nAudio cannot be used","Error",MB_OK);
		return FALSE;
	}
	
	// Set Cooperative Level
	if (DS_OK != m_lpDS->SetCooperativeLevel(g_hWnd, DSSCL_NORMAL))
	{
		MessageBox(g_hWnd,"Error - DS - SetCooperativeLevel","Error",MB_OK);
		return FALSE;
	}
	
	return TRUE;
}


BOOL CDSList::AddNewBuffer(const char* FileName)
{
	// Make sure that audio is initialized
	if (!m_lpDS)
	{
		MessageBox(g_hWnd,"Error - DS - Audio not initialized","Error",MB_OK);
		return FALSE;
	}
	
	// Try creating the new buffer
	CDSBuffer* pNewBuffer = new CDSBuffer(FileName, m_lpDS);
	
	// If succesfull add to playlist
	if (pNewBuffer->IsValid())
	{
		AddTail(pNewBuffer);
		return TRUE;
	}
	
	// Else forget it 
	else
	{
		delete(pNewBuffer);
		return FALSE;
	}
}


BOOL CDSList::RemoveBuffer(int nBuffer)
{
	// Make sure that the buffer index is valid
	if ((nBuffer < 0) || (nBuffer >= GetCount()))
	{
		MessageBox(g_hWnd,"Error - DS - Invalid buffer selection index","Error",MB_OK);
		return FALSE;
	}
	
	// First stop the buffer
	if (StopBuffer(nBuffer))
	{
		// Find the buffer
		POSITION Pos = FindIndex(nBuffer);
		
		// Remove it
		RemoveAt(Pos);
		return TRUE;
	}
	return FALSE;
}


BOOL CDSList::PlayBuffer(int nBuffer, DWORD dwFlags)
{
	// Make sure that the buffer index is valid
	if ((nBuffer < 0) || (nBuffer >= GetCount()))
	{
		MessageBox(g_hWnd,"Error - DS - Invalid buffer selection index","Error",MB_OK);
		return FALSE;
	}
	
	// Find the buffer
	POSITION Pos = FindIndex(nBuffer);
	
	// Retrieve a pointer
	CDSBuffer* DSBuffer = (CDSBuffer *)GetAt(Pos);
	
	// Try playing it
	return DSBuffer->PlaySound(dwFlags);
}


BOOL CDSList::StopBuffer(int nBuffer)
{
	// Make sure that the buffer index is valid
	if ((nBuffer < 0) || (nBuffer >= GetCount()))
	{
		MessageBox(g_hWnd,"Error - DS - Invalid buffer selection index","Error",MB_OK);
		return FALSE;
	}
	
	// Find the buffer
	POSITION Pos = FindIndex(nBuffer);
	
	// Retrieve a pointer
	CDSBuffer* DSBuffer = (CDSBuffer *)GetAt(Pos);
	
	// Try stopping it
	return DSBuffer->StopSound();
}


BOOL CDSList::StopAllBuffers()
{
	for (POSITION Pos = GetHeadPosition(); Pos != NULL; )
	{
		CDSBuffer* DSBuffer = (CDSBuffer *)GetNext(Pos);
		DSBuffer->StopSound();
	}
	return TRUE;
}
