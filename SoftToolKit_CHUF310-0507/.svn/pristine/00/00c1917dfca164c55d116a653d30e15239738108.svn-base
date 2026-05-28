#pragma once
#include <malloc.h>
#include "basic.h"
class CPrivateHeapImp
{
public:
	CPrivateHeapImp( DWORD dwOptions = 0, unsigned int initSize = 0, unsigned int maxSize = 0 )
		:m_dwOptions( dwOptions )
		,m_dwInitSize( initSize )
		,m_dwMaxSize( maxSize )
	{
		m_hHeap = ::HeapCreate( m_dwOptions, m_dwInitSize, m_dwMaxSize );
	}
	~CPrivateHeapImp() { if( IsValid() )  ::HeapDestroy( m_hHeap ); }
	operator HANDLE () { return m_hHeap; }
private:
	CPrivateHeapImp( const CPrivateHeapImp* );
	CPrivateHeapImp& operator = ( const CPrivateHeapImp& );
public:
	PVOID Alloc( unsigned int iSize, DWORD dwFlags = 0 )
	{
		return ::HeapAlloc( m_hHeap, dwFlags, iSize );
	}
	PVOID ReAlloc( PVOID pMemory, unsigned int iSize, DWORD dwFlags = 0 )
	{
		return ::HeapReAlloc( m_hHeap, dwFlags, pMemory, iSize );
	}
	unsigned int Size( PVOID pMemory, DWORD dwFlags = 0 )
	{
		return (unsigned int)::HeapSize( m_hHeap, dwFlags, pMemory );
	}
	bool Free( PVOID pMemory, DWORD dwFlags = 0 )
	{
		return TRUE == ::HeapFree( m_hHeap, dwFlags, pMemory );
	}
	unsigned int Compact( DWORD dwFlags = 0 )
	{
		return (unsigned int)::HeapCompact( m_hHeap, dwFlags );
	}
	bool IsValid()
	{
		return m_hHeap != NULL;
	}
	bool Reset()
	{
		if( IsValid() ) ::HeapDestroy( m_hHeap );

		m_hHeap = ::HeapCreate( m_dwOptions, m_dwInitSize, m_dwMaxSize );

		return IsValid();
	}
private:
	HANDLE	      m_hHeap;
	DWORD         m_dwOptions;
	unsigned int  m_dwInitSize;
	unsigned int  m_dwMaxSize;
};

class CGlobalHeapImp
{
public:
	CGlobalHeapImp( DWORD dwOptions, unsigned int initSize = 0, unsigned int maxSize = 0 ){}
	~CGlobalHeapImp() {}
	operator HANDLE () { return NULL; }
public:
	PVOID Alloc(unsigned int iSize, DWORD dwFlags = 0)
	{
		PVOID pv = malloc( iSize );
		if( pv && ( dwFlags | HEAP_ZERO_MEMORY ) )
			ZeroMemory( pv, iSize );

		return pv;
	}
	PVOID ReAlloc( PVOID pvMemory, unsigned int iSize, DWORD dwFlags = 0 )
	{
		PVOID pv = realloc( pvMemory, iSize );

		if( pv && ( dwFlags | HEAP_ZERO_MEMORY ) )
			ZeroMemory( pv, iSize );
		//else if( !pv )
		//	free( pvMemory );

		return pv;
	}
	bool Free( PVOID pMemory, DWORD dwFlags = 0 )
	{
		if( pMemory )
		{
			free( pMemory );
			return true;
		}
		return false;
	}
	unsigned int Compact( DWORD dwFlags = 0 ) { return -1; }
	unsigned int Size( PVOID pMemory, DWORD dwFlags = 0 ) { return (unsigned int)_msize( pMemory ); }
	bool IsValid() { return true; }
	bool Reset( )  { return true; }
};

#ifndef _NOT_USE_PRIVATE_HEAP
typedef CPrivateHeapImp	CPrivateHeap;
#else
typedef CGlobalHeapImp		CPrivateHeap;
#endif