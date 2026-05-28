#include "bufferpool.h"
TItemList::TItemList( CItemPool& pool )
	:itemPool(pool)
{

}
int TItemList::Cat( const BYTE* pData, int len )
{
	int remain = len;

	while ( remain > 0 )
	{
		TItem* pItem = Back();

		if( NULL == pItem || pItem->IsFull() )
		{
			pItem = PushBack( itemPool.PickFreeItem() );
		}

		int cat = pItem->Cat( pData, remain );

		remain -= cat;
		pData  += cat;
	}

	return len;
}
int TItemList::Cat( const TItem* pItem )
{
	return Cat( pItem->Ptr(), pItem->Size() );
}
int TItemList::Cat( const TItemList& other )
{
	assert( this != &other );

	int len = 0;

	for( TItem* pItem = other.Front(); pItem != NULL; pItem = pItem->next )
		len += Cat( pItem );

	return len;
}
int TItemList::Fetch( BYTE* pData, int len )
{
	int remain = len;

	while ( remain > 0 && Size() > 0 )
	{
		TItem* pItem = Front();
		int fetch = pItem->Fetch( pData, remain );

		pData += fetch;
		remain -= fetch;

		if( pItem->IsEmpty() )
			itemPool.PutFreeItem( PopFront() );
	}

	return len - remain;
}
int TItemList::Peek( BYTE* pData, int len )
{
	int remain = len;
	TItem* pItem = Front();

	while( remain > 0 && pItem != NULL )
	{
		int peek = pItem->Peek( pData, remain );

		pData += peek;
		remain -= peek;
		pItem = pItem->next;
	}

	return len - remain;
}
int TItemList::Reduce( int len )
{
	int remain = len;

	while ( remain > 0 && Size() > 0 )
	{
		TItem* pItem = Front();
		remain -= pItem->Reduce( remain );
		if( pItem->IsEmpty() )
			itemPool.PutFreeItem( PopFront() );
	}

	return len - remain;
}
void TItemList::Release()
{
	itemPool.PutFreeItem( *this );
}
#pragma warning(disable:4355)
CItemPool::CItemPool( unsigned int poolSize /*= DEFUALT_POOL_SIZE*/,
	unsigned int poolHold /*= DEFAULT_POOL_HOLD*/,
	unsigned int itemCapacity /*= DEFAULT_ITEM_CAPACITY*/ )
	:m_dwPoolSize( poolSize )
	,m_dwPoolHold( poolHold )
	,m_dwItemCapacity( itemCapacity )
	,m_lsFreeItem( *this )
{

}
#pragma warning(default:4355)
CItemPool::~CItemPool() 
{ 
	Clear(); 
}
void CItemPool::PutFreeItem( TItem* pItem )
{
	assert( pItem != NULL );

	int size = m_lsFreeItem.Size();

	if( (unsigned int)size < m_dwPoolHold )
	{
		CCriSecLock localLock( m_csFreeItem );
		m_lsFreeItem.PushBack( pItem );
	}
	else 
	{
		TItem::Destruct( pItem );
		CompressFreeItem( m_dwPoolSize );
	}
}
void CItemPool::PutFreeItem( TItemList& listItem )
{
	int addsize = listItem.Size();

	if( addsize > 0 )
	{
		int localsize = m_lsFreeItem.Size();
		unsigned totalsize = localsize + addsize;
		if( totalsize <= m_dwPoolHold )
		{
			CCriSecLock localLock( m_csFreeItem );
			m_lsFreeItem.Shift( listItem );
		}
		else
		{
			listItem.Clear();
			if( (unsigned int)localsize >= m_dwPoolHold )
				CompressFreeItem( m_dwPoolSize );
		}
	}
}
TItem* CItemPool::PickFreeItem()
{
	TItem* item = NULL;

	if( m_lsFreeItem.Size() > 0 )
	{
		CCriSecLock localLock( m_csFreeItem );
		if( m_lsFreeItem.Size() > 0 ) 
			item = m_lsFreeItem.PopFront();
	}

	if( NULL == item )
		item = TItem::Construct( m_heap, m_dwItemCapacity );
	else
		item->Reset();

	return item;
}
void CItemPool::Clear()
{
	{
		CCriSecLock localLock( m_csFreeItem );
		m_lsFreeItem.Clear();
	}

	m_heap.Reset();
}
void CItemPool::CompressFreeItem( int size )
{
	CCriSecLock localLock( m_csFreeItem );

	while( m_lsFreeItem.Size() > size )
		TItem::Destruct( m_lsFreeItem.PopFront() );
}



TBuffer* TBuffer::Construct(CBufferPool& pool, ULONG_PTR dwID)
{
	assert(dwID != 0);

	CPrivateHeap& heap	= pool.GetPrivateHeap();
	TBuffer* pBuffer	= (TBuffer*)heap.Alloc(sizeof(TBuffer));

	pBuffer->TBuffer::TBuffer(heap, pool.GetItemPool(), dwID);

	return pBuffer;
}
void TBuffer::Destruct(TBuffer* pBuffer)
{
	assert(pBuffer != NULL);

	CPrivateHeap& heap = pBuffer->heap;
	pBuffer->TBuffer::~TBuffer();
	heap.Free(pBuffer);
}

int TBuffer::Cat(const BYTE* pData, int len)
{
	items.Cat(pData, len);
	return IncreaseLength(len);
}
int TBuffer::Cat(const TItem* pItem)
{
	items.Cat(pItem);
	return IncreaseLength(pItem->Size());
}
int TBuffer::Cat(const TItemList& other)
{
	assert(&items != &other);

	for(TItem* pItem = other.Front(); pItem != NULL; pItem = pItem->next)
		Cat(pItem);

	return length;
}
int TBuffer::Fetch(BYTE* pData, int length)
{
	int fetch = items.Fetch(pData, length);
	DecreaseLength(fetch);

	return fetch;
}
int TBuffer::Peek(BYTE* pData, int length)
{
	return items.Peek(pData, length);
}
int TBuffer::Reduce	(int len)
{
	int reduce = items.Reduce(len);
	DecreaseLength(reduce);

	return reduce;
}
void TBuffer::Reset()
{
	id		 = 0;
	length	 = 0;
	freeTime = ::timeGetTime();
}


void CBufferPool::PutFreeBuffer(ULONG_PTR dwID)
{
	assert(dwID != 0);

	TBuffer* pBuffer = FindCacheBuffer(dwID);

	if(pBuffer != NULL)
	{
		{
			CReentrantWriteLock locallock(m_csBufferMap);
			//m_mpBuffer.erase(dwID);
		}

		PutFreeBuffer(pBuffer);
	}
}
void CBufferPool::PutCacheBuffer(ULONG_PTR dwID)
{
	assert(dwID != 0);

	CReentrantWriteLock locallock(m_csBufferMap);
	//m_mpBuffer[dwID] = PickFreeBuffer(dwID);
}
TBuffer* CBufferPool::PickFreeBuffer(ULONG_PTR dwID)
{
	assert( dwID != 0);

	TBuffer* pBuffer = NULL;

	if(m_lsFreeBuffer.Size() > 0)
	{
		CCriSecLock locallock(m_csFreeBuffer);

		if(m_lsFreeBuffer.Size() > 0)
		{
			pBuffer = m_lsFreeBuffer.Front();

			if( GetTimeGap32(pBuffer->freeTime) >= m_dwBufferLockTime )
				m_lsFreeBuffer.PopFront();
			else
				pBuffer = NULL;
		}
	}

	if(pBuffer)	pBuffer->id	= dwID;
	else		pBuffer		= TBuffer::Construct(*this, dwID);

	assert(pBuffer);
	return pBuffer;
}
TBuffer* CBufferPool::FindCacheBuffer(ULONG_PTR dwID)
{
	assert(dwID != 0);

	TBuffer* pBuffer = NULL;

	CReentrantReadLock locallock(m_csBufferMap);

	//TBufferPtrMapCI it = m_mpBuffer.find(dwID);
	//if(it != m_mpBuffer.end())
	///	pBuffer = it->second;

	return pBuffer;
}
void CBufferPool::Clear()
{
	{
		CReentrantWriteLock locallock(m_csBufferMap);

		//for(TBufferPtrMapCI it = m_mpBuffer.begin(), end = m_mpBuffer.end(); it != end; ++it)
		//	TBuffer::Destruct(it->second);

		//m_mpBuffer.clear();
	}

	{
		CCriSecLock locallock(m_csFreeBuffer);
		m_lsFreeBuffer.Clear();
	}

	m_itPool.Clear();
	m_heap.Reset();
}
void CBufferPool::PutFreeBuffer(TBuffer* pBuffer)
{
	if(pBuffer->IsValid())
	{
		bool bOK = false;

		{
			CCriSecLock locallock(pBuffer->cs);

			if(pBuffer->IsValid())
			{
				pBuffer->Reset();
				bOK = true;
			}
		}

		if(bOK)
		{
			m_itPool.PutFreeItem(pBuffer->items);

			{
				CCriSecLock locallock(m_csFreeBuffer);
				m_lsFreeBuffer.PushBack(pBuffer);
			}

			if((DWORD)m_lsFreeBuffer.Size() > m_dwBufferPoolHold)
				CompressFreeBuffer(m_dwBufferPoolSize);
		}
	}
}
void CBufferPool::CompressFreeBuffer(int size)
{
	CCriSecLock locallock(m_csFreeBuffer);

	DWORD now = ::timeGetTime();

	while(m_lsFreeBuffer.Size() > size)
	{
		TBuffer* pBuffer = m_lsFreeBuffer.Front();

		if(now - pBuffer->freeTime >= m_dwBufferLockTime)
		{
			m_lsFreeBuffer.PopFront();
			TBuffer::Destruct(pBuffer);
		}
		else
			break;
	}
}