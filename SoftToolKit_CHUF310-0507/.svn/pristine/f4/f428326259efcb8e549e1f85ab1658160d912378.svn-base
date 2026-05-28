#ifndef __WAIT_SYNC__
#define __WAIT_SYNC__
/**************************************************************************************/
#ifdef _MSC_VER
#include <Windows.h>
class CEvt
{
public:
	CEvt(BOOL bManualReset = FALSE, BOOL bInitialState = FALSE, LPCTSTR pszName = NULL, LPSECURITY_ATTRIBUTES pSecurity = NULL)
	{
		m_hEvent = ::CreateEvent(pSecurity, bManualReset, bInitialState, pszName);
	}

	~CEvt()
	{

	}

	BOOL Open(DWORD dwAccess, BOOL bInheritHandle, LPCTSTR pszName)
	{
		m_hEvent = ::OpenEvent(dwAccess, bInheritHandle, pszName);
		return(IsValid());
	}

	BOOL Pulse()	{return(::PulseEvent(m_hEvent));}
	BOOL Reset()	{return(::ResetEvent(m_hEvent));}
	BOOL Set()		{return(::SetEvent(m_hEvent));}

	HANDLE& GetHandle	() 	{return m_hEvent;}
	operator HANDLE		()	{return m_hEvent;}
	BOOL IsValid		()	{return m_hEvent != NULL;}

private:
	CEvt(const CEvt&);
	CEvt operator = (const CEvt&);

private:
	HANDLE m_hEvent;
};

class SpinLock
{
public:
	SpinLock() : m_lock( 0 ) {}
	~SpinLock(){}
	inline void Lock()
	{
		while( InterlockedExchange( &m_lock, 1 ) == 1 )
		{ 
			Sleep( 0 ); 
		}
	}
	inline void Unlock()
	{
		InterlockedExchange( &m_lock, 0 );
	}
	inline bool Locked()
	{
		return m_lock == 1;
	}
private:
	volatile long m_lock;
};
#else
#include <pthread.h>
//#include <Windows.h>
//class CEvt
//{
//public:
//	CEvt(BOOL bManualReset = FALSE, BOOL bInitialState = FALSE, LPCTSTR pszName = NULL, LPSECURITY_ATTRIBUTES pSecurity = NULL)
//	{
//		m_hEvent = ::CreateEvent(pSecurity, bManualReset, bInitialState, pszName);
//	}
//
//	~CEvt()
//	{
//
//	}
//
//	BOOL Open(DWORD dwAccess, BOOL bInheritHandle, LPCTSTR pszName)
//	{
//		m_hEvent = ::OpenEvent(dwAccess, bInheritHandle, pszName);
//		return(IsValid());
//	}
//
//	BOOL Pulse()	{return(::PulseEvent(m_hEvent));}
//	BOOL Reset()	{return(::ResetEvent(m_hEvent));}
//	BOOL Set()		{return(::SetEvent(m_hEvent));}
//
//	HANDLE& GetHandle	() 	{return m_hEvent;}
//	operator HANDLE		()	{return m_hEvent;}
//	BOOL IsValid		()	{return m_hEvent != NULL;}
//
//private:
//	CEvt(const CEvt&);
//	CEvt operator = (const CEvt&);
//
//private:
//	HANDLE m_hEvent;
//};

class SpinLock
{
public:
	SpinLock()
	{
		pthread_rwlock_init(&m_lock, NULL);
	}
	~SpinLock()
	{
		pthread_rwlock_destroy(&m_lock);
	}
	inline void Lock()
	{
		pthread_rwlock_wrlock(&m_lock);
	}
	inline void Unlock()
	{
		pthread_rwlock_unlock(&m_lock);
	}
private:
	//volatile long m_lock;
	pthread_rwlock_t     m_lock;
};
#endif

/**************************************************************************************/
#endif