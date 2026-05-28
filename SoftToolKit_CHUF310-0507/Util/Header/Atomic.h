#ifndef __ATOMIC__
#define __ATOMIC__
/**************************************************************************************/

/**************************************************************************************
//定义原子操作函数 
**************************************************************************************/
#ifdef PLATFORM_PC
#define WIN32_LEAN_AND_MEAN	
#include <windows.h>
#define atomic_add( v, x )                  InterlockedExchangeAdd( (volatile long*)(x), v )
#define atomic_inc( x )                     InterlockedExchangeAdd( (volatile long*)(x), 1  )
#define atomic_dec( x )                     InterlockedExchangeAdd( (volatile long*)(x), -1 )
#define atomic_or( m, v )                   InterlockedExchange( (volatile long*)(v), ((m) | *(v)) )
#define atomic_cmpxchg( o, n, d )           (InterlockedCompareExchange( (volatile long*)(d), (n), (o) ) == *(d))
#define atomic_chg( o, d )                  InterlockedExchange( (volatile long*)(d), (0) )
#else
#define atomic_inc( x )
#endif
/**************************************************************************************/
#endif