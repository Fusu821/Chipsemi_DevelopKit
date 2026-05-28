#ifndef __WAIT_LOCK__
#define __WAIT_LOCK__
/**************************************************************************************/
#include "Basic.h"
#include <intrin.h>
#pragma intrinsic(_ReadBarrier)
#pragma intrinsic(_WriteBarrier)
#pragma intrinsic(_ReadWriteBarrier)

class CSpinGuard
{
private:
	CSpinGuard( const CSpinGuard& );
	CSpinGuard& operator=( const CSpinGuard& );
public:
	CSpinGuard() : m_uFlag( 0 )
	{

	}
	~CSpinGuard() 
	{
		assert( m_uFlag == 0 );
	}
	void Lock()
	{
		for( int iTry = 0; !TryLock(); ++iTry )
			Pause( iTry );
	}
	bool TryLock()
	{
		if( 0 == ::InterlockedCompareExchange( &m_uFlag, 1, 0 ) )
		{
			::_ReadWriteBarrier();
			return true;
		}
		return false;
	}
	void Unlock()
	{
		assert( 1 == m_uFlag );
		m_uFlag = 0;
	}
	static void Pause( int tryTime )
	{
		if( tryTime < DEFAULT_PAUSE_YIELD )          { YieldProcessor(  ); }
		else if( tryTime < DEFAULT_PAUSE_CYCLE - 1 ) { Sleep( 0 ); }
		else if( tryTime < DEFAULT_PAUSE_CYCLE )     { Sleep( 1 ); }
		else                                         { Pause( tryTime & (DEFAULT_PAUSE_CYCLE - 1) ); }
	}
private:
	volatile long m_uFlag;
};
class CInterCriSec
{
public:
	enum{  DEFAULT_CRISEC_SPIN_COUNT = 4096, };
	CInterCriSec( DWORD dwSpinCount = DEFAULT_CRISEC_SPIN_COUNT )
	{::InitializeCriticalSectionAndSpinCount(&m_crisec, dwSpinCount);}
	~CInterCriSec()
	{::DeleteCriticalSection(&m_crisec);}

	void Lock()								{::EnterCriticalSection(&m_crisec);}
	void Unlock()							{::LeaveCriticalSection(&m_crisec);}
	BOOL TryLock()							{return ::TryEnterCriticalSection(&m_crisec);}
	DWORD SetSpinCount(DWORD dwSpinCount)	{return ::SetCriticalSectionSpinCount(&m_crisec, dwSpinCount);}

	CRITICAL_SECTION* GetObject()			{return &m_crisec;}

private:
	CInterCriSec(const CInterCriSec& cs);
	CInterCriSec operator = (const CInterCriSec& cs);

private:
	CRITICAL_SECTION m_crisec;
};

template<class CLockObj> 
class CLocalLock
{
public:
	CLocalLock( CLockObj& obj ):m_lockObj(obj){ m_lockObj.Lock(); }
	~CLocalLock(){ m_lockObj.Unlock(); }
private:
	CLockObj& m_lockObj;
};

class CSEM
{
public:
	CSEM(LONG lMaximumCount, LONG lInitialCount = 0, LPCTSTR lpName = NULL, LPSECURITY_ATTRIBUTES pSecurity = NULL)
	{
		m_hsem = ::CreateSemaphore(pSecurity, lInitialCount, lMaximumCount, lpName);
		assert(IsValid());
	}

	~CSEM()
	{
		if(IsValid()) 
			::CloseHandle(m_hsem);
	}

	BOOL Open(DWORD dwAccess, BOOL bInheritHandle, LPCTSTR pszName)
	{
		if(IsValid())
			::CloseHandle(m_hsem);

		m_hsem = ::OpenSemaphore(dwAccess, bInheritHandle, pszName);
		return(IsValid());
	}

	void Wait(DWORD dwMilliseconds = INFINITE)
	{
		::WaitForSingleObject(m_hsem, dwMilliseconds);
	}

	BOOL Release(LONG lReleaseCount = 1, LPLONG lpPreviousCount = NULL)
	{
		return ::ReleaseSemaphore(m_hsem, lReleaseCount, lpPreviousCount);
	}

	HANDLE& GetHandle	() 	{return m_hsem;}
	operator HANDLE		()	{return m_hsem;}
	BOOL IsValid		()	{return m_hsem != NULL;}

private:
	CSEM(const CSEM& sem);
	CSEM operator = (const CSEM& sem);
private:
	HANDLE m_hsem;
};



typedef CInterCriSec				 CCriSec;
typedef CLocalLock<CCriSec>			 CCriSecLock;
typedef CLocalLock<CSpinGuard>       CSpinLock;


//////////////////////////////////////////////////////////////////////////

class CRWLock
{
public:
	void WaitToRead()
	{
		bool bWait = false;

		{
			CSpinLock locallock(m_cs);

			if(m_nActive > 0)
				++m_nActive;
			else if(m_nActive == 0)
			{
				if(m_nWaitingWriters == 0)
					++m_nActive;
				else
				{
					++m_nWaitingReaders;
					bWait = true;
				}
			}
			else
			{
				if(!IsOwner())
				{
					++m_nWaitingReaders;
					bWait = true;
				}
			}
		}

		if(bWait)
		{
			m_smRead.Wait();
		}
	}
	void WaitToWrite()
	{
		bool bWait = false;

		{
			CSpinLock locallock(m_cs);

			if(m_nActive > 0)
			{
				++m_nWaitingWriters;
				bWait = true;
			}
			else if(m_nActive == 0)
			{
				--m_nActive;
				SetOwner();
			}
			else
			{
				if(IsOwner())
					--m_nActive;
				else
				{
					++m_nWaitingWriters;
					bWait = true;
				}
			}
		}

		if(bWait)
		{
			m_smWrite.Wait();
			SetOwner();
		}
	}
	void ReadDone()
	{
		CSEM* pSem	 = NULL;
		LONG  lCount = 0;

		{
			CSpinLock locallock(m_cs);

			assert(m_nActive != 0);

			if(m_nActive > 0)
			{
				if(--m_nActive == 0)
					Done(&pSem, lCount);
			}
			else
				assert(IsOwner());
		}

		if(pSem != NULL)
			pSem->Release(lCount);
	}
	void WriteDone()
	{
		CSEM* pSem	 = NULL;
		LONG  lCount = 0;

		{
			CSpinLock locallock(m_cs);

			assert(m_nActive < 0);

			if(++m_nActive == 0)
			{
				DetachOwner();
				Done(&pSem, lCount);
			}
			else
				assert(IsOwner());
		}

		if(pSem != NULL)
			pSem->Release(lCount);
	}

private:
	void Done(CSEM** ppSem, LONG& lCount)
	{
		assert(m_nActive	 == 0);
		assert(m_dwWriterTID == 0);

		if(m_nWaitingWriters > 0)
		{
			--m_nActive;
			--m_nWaitingWriters;

			lCount = 1;
			*ppSem = &m_smWrite;
		}
		else if(m_nWaitingReaders > 0)
		{
			m_nActive			= m_nWaitingReaders;
			m_nWaitingReaders	= 0;
			lCount				= m_nActive;
			*ppSem				= &m_smRead;
		}
	}
	bool IsOwner()		{return m_dwWriterTID == ::GetCurrentThreadId();}
	void SetOwner()		{m_dwWriterTID = ::GetCurrentThreadId();}
	void DetachOwner()	{m_dwWriterTID = 0;}

public:
	CRWLock()
		: m_smRead			(MAXLONG)
		, m_smWrite			(1)
		, m_nWaitingReaders	(0)
		, m_nWaitingWriters	(0)
		, m_nActive			(0)
		, m_dwWriterTID		(0)
	{

	}
	~CRWLock()
	{
		assert(m_nActive	 == 0);
		assert(m_dwWriterTID == 0);
	}

private:
	CRWLock(const CRWLock&);
	CRWLock operator = (const CRWLock&);

private:
	int m_nWaitingReaders;
	int m_nWaitingWriters;
	int m_nActive;
	DWORD m_dwWriterTID;

	CSpinGuard	m_cs;
	CSEM		m_smRead;
	CSEM		m_smWrite;
};


template<class CLockObj> class CLocalReadLock
{
public:
	CLocalReadLock(CLockObj& obj) : m_wait(obj) {m_wait.WaitToRead();}
	~CLocalReadLock() {m_wait.ReadDone();}
private:
	CLocalReadLock(const CLocalReadLock&);
	CLocalReadLock operator = (const CLocalReadLock&);
private:
	CLockObj& m_wait;
};

template<class CLockObj> class CLocalWriteLock
{
public:
	CLocalWriteLock(CLockObj& obj) : m_wait(obj) {m_wait.WaitToWrite();}
	~CLocalWriteLock() {m_wait.WriteDone();}
private:
	CLocalWriteLock(const CLocalWriteLock&);
	CLocalWriteLock operator = (const CLocalWriteLock&);
private:
	CLockObj& m_wait;
};

class CReentrantSpinGuard
{
public:
	CReentrantSpinGuard()
		: m_dwThreadID	(0)
		, m_iCount		(0)
	{

	}

	~CReentrantSpinGuard()
	{
		assert(m_dwThreadID	== 0);
		assert(m_iCount		== 0);
	}

	void Lock()
	{
		for(UINT32 i = 0; !_TryLock(i == 0); ++i)
			Pause(i);
	}

	BOOL TryLock()
	{
		return _TryLock(TRUE);
	}

	void Unlock()
	{
		assert(m_dwThreadID == ::GetCurrentThreadId());

		if((--m_iCount) == 0)
			m_dwThreadID = 0;
	}

	static void Pause(UINT32 i)
	{
		if(i < DEFAULT_PAUSE_YIELD){
			YieldProcessor();
		}else if(i < DEFAULT_PAUSE_CYCLE - 1){	
			SwitchToThread();
		}else if(i < DEFAULT_PAUSE_CYCLE){
			Sleep(1);
		}else{
			Pause(i & (DEFAULT_PAUSE_CYCLE - 1));
		}
	}

private:
	CReentrantSpinGuard(const CReentrantSpinGuard& cs);
	CReentrantSpinGuard operator = (const CReentrantSpinGuard& cs);

	BOOL _TryLock(BOOL bFirst)
	{
		DWORD dwCurrentThreadID = ::GetCurrentThreadId();

		if(bFirst && m_dwThreadID == dwCurrentThreadID)
		{
			++m_iCount;
			return TRUE;
		}

		if(::InterlockedCompareExchange(&m_dwThreadID, dwCurrentThreadID, 0) == 0)
		{
			::_ReadWriteBarrier();
			assert(m_iCount == 0);

			m_iCount = 1;

			return TRUE;
		}

		return FALSE;
	}

private:
	volatile LONG	m_dwThreadID;
	int				m_iCount;
};



typedef CLocalReadLock<CRWLock>			CReentrantReadLock;
typedef CLocalWriteLock<CRWLock>		CReentrantWriteLock;
typedef CLocalLock<CReentrantSpinGuard>	CReentrantSpinLock;

/**************************************************************************************/
#endif