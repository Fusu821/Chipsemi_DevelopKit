#ifndef __BUFFER_POOL__
#define __BUFFER_POOL__
/**************************************************************************************/
#include "lock.h"
#include "link.h"
//#include <map>
//using namespace std;
#include <MmSystem.h>
#pragma comment(lib, "Winmm")

// static DWORD SysGetPageSize()
// {
// 	SYSTEM_INFO si;
// 	SysGetSystemInfo(&si);
// 
// 	return si.dwPageSize;
// }
// static DWORD GetTimeGap32(DWORD dwOriginal)
// {
// 	return ::timeGetTime() - dwOriginal;
// }

// const DWORD DEFAULT_ITEM_CAPACITY		        	= SysGetPageSize();
#define  DEFAULT_POOL_SIZE						      30
#define  DEFAULT_POOL_HOLD                            1200
#define  DEFAULT_BUFFER_LOCK_TIME	                  10 * 1000
#define  DEFAULT_BUFFER_POOL_SIZE	                  150
#define  DEFAULT_BUFFER_POOL_HOLD	                  600


#define GetTimeGap32( x )  ( ::timeGetTime() - (x) )

class CItemPool;
struct TItemList : public TSimpleList<TItem>
{
public: 
	int Cat( const BYTE* pData, int len );
	int Cat( const TItem* pItem );
	int Cat( const TItemList& other );
	int Fetch( BYTE* pData, int len );
	int Peek( BYTE* pData, int len );
	int Reduce( int len );
	void Release();
	TItemList( CItemPool& pool );
private:
	CItemPool& itemPool;
};

class CItemPool
{
private:
	CItemPool( const CItemPool& );
	CItemPool& operator = ( const CItemPool& );
public:
	CItemPool( unsigned int poolSize      = DEFAULT_POOL_SIZE,
		       unsigned int poolHold      = DEFAULT_POOL_HOLD,
			   unsigned int itemCapacity  = DEFAULT_ITEM_CAPACITY );
	~CItemPool();
	void PutFreeItem( TItem* pItem );
	void PutFreeItem( TItemList& listItem );
	TItem* PickFreeItem();
	inline void Clear();
	void CompressFreeItem( int size );
public:
	void SetItemCapacity(unsigned int dwItemCapacity)	{m_dwItemCapacity	= dwItemCapacity;}
	void SetPoolSize	(unsigned int dwPoolSize)		{m_dwPoolSize		= dwPoolSize;}
	void SetPoolHold	(unsigned int dwPoolHold)		{m_dwPoolHold		= dwPoolHold;}
	unsigned int GetItemCapacity	()					{return m_dwItemCapacity;}
	unsigned int GetPoolSize		()					{return m_dwPoolSize;}
	unsigned int GetPoolHold		()					{return m_dwPoolHold;}
private:
	CPrivateHeap          m_heap;
	unsigned int          m_dwItemCapacity;
	unsigned int          m_dwPoolSize;
	unsigned int          m_dwPoolHold;
	CCriSec               m_csFreeItem;
	TItemList             m_lsFreeItem;
};

struct TItemPtr
{
private:
	TItemPtr( const TItemPtr& );
	TItemPtr& operator = ( const TItemPtr& );
public:
	TItem* Reset( TItem* pItem = NULL )
	{
		if( thisItem != NULL )
			itemPool.PutFreeItem( thisItem );

		thisItem = pItem;

		return thisItem;
	}
	TItem* Attach( TItem* pItem )
	{
		return Reset( pItem );
	}
	TItem* Detach()
	{
		TItem* pItem = thisItem;
		thisItem = NULL;

		return pItem;
	}
	bool IsValid()                     { return NULL != thisItem; }
	TItem* operator->()                { return thisItem; }
	TItem* operator=( TItem* item )    { return Reset( item ); }
	operator TItem* ()                 { return thisItem; }
	TItem* Ptr()                       { return thisItem; }
	const TItem* Ptr() const           { return thisItem; }
	operator const TItem* () const     { return thisItem; }
public:
	TItemPtr( CItemPool& pool, TItem* item = NULL )
		:itemPool( pool ),thisItem(item)
	{

	}
	~TItemPtr(){ Reset(); }
private:
	CItemPool&   itemPool;
	TItem*       thisItem;
};

struct TBuffer
{
	template<typename T> friend struct TSimpleList;
	friend class CBufferPool;

public:
	static TBuffer* Construct(CBufferPool& pool, ULONG_PTR dwID);
	static void Destruct(TBuffer* pBuffer);

public:
	int Cat(const BYTE* pData, int len);
	int Cat(const TItem* pItem);
	int Cat(const TItemList& other);
	int Fetch(BYTE* pData, int length);
	int Peek(BYTE* pData, int length);
	int Reduce	(int len);

public:
	CCriSec&	CriSec	()	{return cs;}
	TItemList&	ItemList()	{return items;}

	ULONG_PTR ID		()	const	{return id;}
	int Length			()	const	{return length;}
	bool IsValid		()	const	{return id != 0;}

private:
	int IncreaseLength	(int len)	{return (length += len);}
	int DecreaseLength	(int len)	{return (length -= len);}
	inline void Reset();
private:
	TBuffer(CPrivateHeap& hp, CItemPool& itPool, ULONG_PTR dwID = 0)
		: heap(hp), items(itPool), id(dwID), length(0)
	{
	}

	~TBuffer()	{}

private:
	TBuffer( const TBuffer& );
	TBuffer& operator = ( const TBuffer& );

private:
	CPrivateHeap&	heap;

private:
	ULONG_PTR		id;
	int				length;
	DWORD			freeTime;

private:
	TBuffer*		next;
	TBuffer*		last;

	CCriSec			cs;
	TItemList		items;
};

typedef TSimpleList<TBuffer> TBufferList;
// typedef Dictionary<ULONG_PTR, TBuffer*>	TBufferPtrMap;
// typedef TBufferPtrMap::const_iterator		TBufferPtrMapCI;

class CBufferPool
{
private:
	CBufferPool( CBufferPool& );
	CBufferPool& operator = ( CBufferPool& );
public:
	CBufferPool(DWORD dwPoolSize	 = DEFAULT_BUFFER_POOL_SIZE,
		DWORD dwPoolHold	 = DEFAULT_BUFFER_POOL_HOLD,
		DWORD dwLockTime	 = DEFAULT_BUFFER_LOCK_TIME,
		DWORD dwItemCapacity = DEFAULT_ITEM_CAPACITY)
		: m_dwBufferPoolSize(dwPoolSize)
		, m_dwBufferPoolHold(dwPoolHold)
		, m_dwBufferLockTime(dwLockTime)
	{
		m_itPool.SetItemCapacity(dwItemCapacity);
	}

	~CBufferPool()	{Clear();}
public:
	void PutFreeBuffer(ULONG_PTR dwID);
	void PutCacheBuffer(ULONG_PTR dwID);
	TBuffer* PickFreeBuffer(ULONG_PTR dwID);
	TBuffer* FindCacheBuffer(ULONG_PTR dwID);
	void Clear();
public:
	void SetItemCapacity	(unsigned int dwItemCapacity)		{m_itPool.SetItemCapacity(dwItemCapacity);}
	void SetItemPoolSize	(unsigned int dwItemPoolSize)		{m_itPool.SetPoolSize(dwItemPoolSize);}
	void SetItemPoolHold	(unsigned int dwItemPoolHold)		{m_itPool.SetPoolHold(dwItemPoolHold);}

	void SetBufferLockTime	(unsigned int dwBufferLockTime)	    {m_dwBufferLockTime	= dwBufferLockTime;}
	void SetBufferPoolSize	(unsigned int dwBufferPoolSize)	    {m_dwBufferPoolSize	= dwBufferPoolSize;}
	void SetBufferPoolHold	(unsigned int dwBufferPoolHold)  	{m_dwBufferPoolHold	= dwBufferPoolHold;}

	DWORD GetItemCapacity	()							        {return m_itPool.GetItemCapacity();}
	DWORD GetItemPoolSize	()							        {return m_itPool.GetPoolSize();}
	DWORD GetItemPoolHold	()							        {return m_itPool.GetPoolHold();}

	DWORD GetBufferLockTime	()							        {return m_dwBufferLockTime;}
	DWORD GetBufferPoolSize	()							        {return m_dwBufferPoolSize;}
	DWORD GetBufferPoolHold	()							        {return m_dwBufferPoolHold;}
	CPrivateHeap& GetPrivateHeap()	                            {return m_heap;}
	CItemPool& GetItemPool()	                             	{return m_itPool;}

	TBuffer* operator []	(ULONG_PTR dwID)			        {return FindCacheBuffer(dwID);}
private:
	void PutFreeBuffer(TBuffer* pBuffer);
	void CompressFreeBuffer	(int size);
public:

private:
	unsigned int       m_dwBufferLockTime;
	unsigned int       m_dwBufferPoolSize;
	unsigned int       m_dwBufferPoolHold;
	CPrivateHeap	   m_heap;
	CItemPool		   m_itPool;
	CRWLock			   m_csBufferMap;
	//TBufferPtrMap	   m_mpBuffer;
	CCriSec			   m_csFreeBuffer;
    TBufferList		   m_lsFreeBuffer;
};
/**************************************************************************************/
#endif