#ifndef __WAIT_BASIC_DEF__
#define __WAIT_BASIC_DEF__
/**************************************************************************************/
#include <assert.h>
#include <windows.h>

#if defined (_WIN64)
#define DEFAULT_PAUSE_YIELD		32
#define DEFAULT_PAUSE_CYCLE		8192
#else
#define DEFAULT_PAUSE_YIELD		8
#define DEFAULT_PAUSE_CYCLE		4096
#endif

// #ifndef ASSERT
// #define ASSERT(f)	ATLASSERT(f)
// #endif
// #ifndef VERIFY
// #define VERIFY(f)	ATLVERIFY(f)
// #endif
// #ifndef TRACE
// #include <atltrace.h>
// #define TRACE							AtlTrace
// #define TRACE0(f)						TRACE(f)
// #define TRACE1(f, p1)					TRACE(f, p1)
// #define TRACE2(f, p1, p2)				TRACE(f, p1, p2)
// #define TRACE3(f, p1, p2, p3)			TRACE(f, p1, p2, p3)
// #define TRACE4(f, p1, p2, p3, p4)		TRACE(f, p1, p2, p3, p4)
// #define TRACE5(f, p1, p2, p3, p4, p5)	TRACE(f, p1, p2, p3, p4, p5)
// #endif

template<typename T>
struct KeyType
{
public:
	typedef T Type;

	static T GetKeyValue(const T& value)
	{
		return value;
	}
};

template<typename T>
struct POD
{
	static const bool Result=false;
};

template<>struct POD<bool>{static const bool Result=true;};
template<>struct POD<INT8>{static const bool Result=true;};
template<>struct POD<UINT8>{static const bool Result=true;};
template<>struct POD<INT16>{static const bool Result=true;};
template<>struct POD<UINT16>{static const bool Result=true;};
template<>struct POD<INT32>{static const bool Result=true;};
template<>struct POD<UINT32>{static const bool Result=true;};
template<>struct POD<INT64>{static const bool Result=true;};
template<>struct POD<UINT64>{static const bool Result=true;};
template<>struct POD<char>{static const bool Result=true;};
template<>struct POD<wchar_t>{static const bool Result=true;};
template<typename T>struct POD<T*>{static const bool Result=true;};
template<typename T>struct POD<T&>{static const bool Result=true;};
template<typename T, typename C>struct POD<T C::*>{static const bool Result=true;};
template<typename T, int _Size>struct POD<T[_Size]>{static const bool Result=POD<T>::Result;};
template<typename T>struct POD<const T>{static const bool Result=POD<T>::Result;};
template<typename T>struct POD<volatile T>{static const bool Result=POD<T>::Result;};
template<typename T>struct POD<const volatile T>{static const bool Result=POD<T>::Result;};


class NotCopyable
{
private:
	NotCopyable(const NotCopyable&);
	NotCopyable& operator=(const NotCopyable&);
public:
	NotCopyable();
};

class Interface : private NotCopyable
{
public:
	virtual ~Interface();
};

template<typename T>
class IEnumerator : public virtual Interface
{
public:
	typedef T									ElementType;

	virtual IEnumerator<T>*						Clone()const=0;
	virtual const T&							Current()const=0;
	virtual int								Index()const=0;
	virtual bool								Next()=0;
	virtual void								Reset()=0;

	virtual bool								Evaluated()const{return false;}
};

template<typename T>
class IEnumerable : public virtual Interface
{
public:
	typedef T									ElementType;

	virtual IEnumerator<T>*						CreateEnumerator()const=0;
};

/***********************************************************************
Ëæ»ú´æÈ¡
***********************************************************************/

namespace randomaccess_internal
{
	template<typename T>
	struct RandomAccessable
	{
		static const bool							CanRead = false;
		static const bool							CanResize = false;
	};

	template<typename T>
	struct RandomAccess
	{
		static int GetCount(const T& t)
		{
			return t.Count();
		}

		static const typename T::ElementType& GetValue(const T& t, int index)
		{
			return t.Get(index);
		}

		static void SetCount(T& t, int count)
		{
			t.Resize(count);
		}

		static void SetValue(T& t, int index, const typename T::ElementType& value)
		{
			t.Set(index, value);
		}

		static void AppendValue(T& t, const typename T::ElementType& value)
		{
			t.Add(value);
		}
	};
}

/**************************************************************************************/
#endif