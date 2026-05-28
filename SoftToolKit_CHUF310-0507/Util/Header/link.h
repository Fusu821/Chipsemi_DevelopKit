#pragma once
#include "heap.h"

#define DEFAULT_ITEM_CAPACITY		        	4096

struct TItem 
{
	template <typename T>
	friend struct TSimpleList;
	friend struct TItemList;
	friend struct TItemPool;
	friend struct TBuffer;
public:
	int Remain()            const { return capacity - (int)(end - begin); }
	BYTE* Ptr()                   { return begin; }
	const BYTE* Ptr()       const { return begin; }
	int Size()              const { return (int)( end - begin ); }
	int Capacity()          const { return capacity; }
	bool IsEmpty()          const { return Size() == 0; }
	bool IsFull()           const { return Remain() == 0; }
	operator BYTE* ()             { return Ptr(); }
	operator const BYTE* () const { return Ptr(); }
	inline int Cat( const BYTE* pData, int length )                
	{
		assert( pData != NULL && length > 0 );
		int cat  = min( Remain(), length );
		if( cat > 0 )
		{
			memcpy_s( end, cat, pData, cat );
			end += cat;
		}
		return cat;
	}
	inline int Cat( const TItem& other )
	{
		assert( this != &other );
		return Cat( other.Ptr(), other.Size() );
	}
	inline int Fetch( BYTE* pData, int lenth )
	{
		assert( pData != NULL && lenth > 0 );

		int fetch = min( Size(), lenth );
		memcpy_s( pData, lenth, begin, fetch );
		begin += fetch;

		return fetch;
	}
	inline int Peek( BYTE* pData, int lenth )
	{
		assert( pData != NULL && lenth > 0 );

		int peek = min( Size(), lenth );
		memcpy_s( pData, lenth, begin, peek );

		return peek;
	}
	inline int Reduce( int lenth )
	{
		assert( lenth > 0 );

		int reduce = min( Size(), lenth );
		begin += reduce;

		return reduce;
	}
	inline void Reset( int first = 0, int last = 0 )
	{
		assert( first >= -1 && first <= capacity );
		assert( last >= -1 && last <= capacity );

		if( first >= 0 )     begin = head + min( first, capacity );
		if( last >= 0 )      end   = head + min( last, capacity );
	}
public:
	static TItem* Construct( CPrivateHeap& heap, int icap = DEFAULT_ITEM_CAPACITY, BYTE* pData = NULL, int lenth = 0 )
	{
		assert( icap > 0 );

		int itemSize = sizeof( TItem );
		TItem* pItem = (TItem*)heap.Alloc( itemSize + icap );
		pItem->head = (BYTE*)pItem + itemSize;

		pItem->TItem::TItem( heap, icap, pData, lenth );

		return pItem;
	}
	static void Destruct( TItem* pItem )
	{
		assert( pItem != NULL );

		CPrivateHeap& heap = pItem->heap;
		pItem->TItem::~TItem();
		heap.Free( pItem );
	}
private:
	TItem( const TItem& );
	TItem& operator = ( const TItem& );
	TItem( CPrivateHeap& hp, int cap = DEFAULT_ITEM_CAPACITY, const BYTE* pd = NULL, int len = 0 )
		:heap(hp)
		,capacity(cap)
		,begin(head)
		,end(head)
		,next(NULL)
		,last(NULL)
	{
		if( NULL != pd && len > 0 )
			Cat( pd, len );
	}
	~TItem(){}
private:
	TItem*    next;
	TItem*    last;
	int       capacity;
	BYTE*     head;
	BYTE*     begin;
	BYTE*     end;
private:
	CPrivateHeap& heap;
};

template<typename T>
struct TSimpleList
{
public: 
	T* PushFront( T* pItem )
	{
		if( NULL != pFront )
		{
			pFront->last = pItem;
			pItem->next = pFront;
		}
		else
		{
			pItem->next = pItem->last = NULL;
			pBack = pItem;
		}

		pFront = pItem;
		++size;

		return pItem;
	}
	T* PushBack( T* pItem )
	{
		if( NULL != pBack )
		{
			pItem->last = pBack;
			pBack->next = pItem;
		}
		else
		{
			pItem->next = pItem->last = NULL;
			pFront = pItem;
		}

		pBack = pItem;
		++size;

		return pItem;
	}
	T* PopFront()
	{
		T* pItem = pFront;

		if( pFront != pBack )
		{
			pFront = pFront->next;
			pFront->last = NULL;
		}
		else if( pFront != NULL )
		{
			pFront = pBack = NULL;
		}

		if( NULL != pItem )
		{
			pItem->next = pItem->last = NULL;
			--size;
		}
		return pItem;
	}
	T* PopBack()
	{
		T* pItem = pBack;

		if( pBack != pFront )
		{
			pBack = pBack->last;
			pBack->next = NULL;
		}
		else if( pBack != NULL )
		{
			pFront = pBack = NULL;
		}

		if( pItem != NULL )
		{
			pItem->next = pItem->last = NULL;
			--size;
		}

		return pItem;
	}
	TSimpleList<T>& Shift( TSimpleList<T>& other )
	{
		if( &other != this && other.size > 0 )
		{
			if( size > 0 )
			{
				pBack->next = other.pFront;
				other.pFront = pBack;
			}
			else 
			{
				pFront = other.pFront;
			}
			pBack = other.pBack;
			size += other.size;

			other.Reset();
		}
		return *this;
	}
	void Clear()
	{
		if( size > 0 )
		{
			T* pItem = NULL;
			while( pItem = PopFront() )
				T::Destruct( pItem );
		}
	}	
	T* Front()     const { return pFront; }
	T* Back()      const { return pBack; }
	int Size()     const { return size; }
	bool IsEmpty() const { return size == 0; }
public:
	TSimpleList() { Reset(); }
	~TSimpleList() { Clear(); }
private:
	TSimpleList( const TSimpleList& );
	TSimpleList& operator = ( const TSimpleList& );
	void Reset()
	{
		size = 0;
		pFront = pBack = NULL;
	}
private:
	int size;
	T* pFront;
	T* pBack;
};