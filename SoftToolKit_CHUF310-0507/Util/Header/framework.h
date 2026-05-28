/////////////////////////////////////////////////////////////////////////////
//@remarks: 管理动态创建对话框的类，包括对话框的创建 位置显示 析构
//代码使用了Lazy原则  只有在使用时才创建 一旦创建 就缓存
//使用前 先使用宏 REGIST_RUNTIME_DIALOG 将对话框动态创建信息注册到管理器
//使用时 使用RunTimeDialog( name )来获取相应的对话框
//author：  wuxun
//DataTime: 2014-6-12 
/////////////////////////////////////////////////////////////////////////////
#pragma once
#include <map>
using namespace std;
#define RunTimeClassFactoryInst(X) RunTimeClassFactory<X>::GetInstance()
#define RunTimeClassFactoryInstEx(X) RunTimeClassFactoryEx<X>::GetInstance()
typedef void* ( *pFunCreater )( void );
typedef void* ( *pFunCreaterEx )( unsigned long );
template<typename T>
class RunTimeClassFactory
{
public:
	static RunTimeClassFactory& GetInstance()
	{
		static RunTimeClassFactory instance;
		return instance;
	}
	void RegistClassToFactory( const T& type, pFunCreater function )
	{
		m_mapTypeToCreater.insert( make_pair( type, function ) );
	}
	void* CreateObject( const T& key )
	{
	    typename map<T,pFunCreater>::iterator it = m_mapTypeToCreater.find( key );
		if( it == m_mapTypeToCreater.end() ) return NULL;
		if( NULL == it->second ) return NULL;
		return (it->second)();
	}
	~RunTimeClassFactory() {} 
private:
	RunTimeClassFactory(){}
private:
	map<T,pFunCreater> m_mapTypeToCreater;
};

template<typename T>
class RunTimeClassFactoryEx
{
public:
	static RunTimeClassFactoryEx& GetInstance()
	{
		static RunTimeClassFactoryEx instance;
		return instance;
	}
	void RegistClassToFactory( const T& type, pFunCreaterEx function )
	{
		m_mapTypeToCreater.insert( make_pair( type, function ) );
	}
	void* CreateObject( const T& key, unsigned long param )
	{
		typename map<T,pFunCreaterEx>::iterator it = m_mapTypeToCreater.find( key );
		if( it == m_mapTypeToCreater.end() ) return NULL;
		if( it->second == NULL) return NULL;
		return (it->second)( param );
	}
	~RunTimeClassFactoryEx() {} 
private:
	RunTimeClassFactoryEx(){}
private:
	map<T,pFunCreaterEx> m_mapTypeToCreater;
};

template<typename X, typename T>
class RunTimeClassHelper
{
public:
	RunTimeClassHelper( const X& xType )
	{
		RunTimeClassFactory<X>::GetInstance().RegistClassToFactory( xType, pFunCreater(&RunTimeClassHelper<X,T>::Create) );
	}
	static T* Create( )
	{
		return new T;
	}
};

template<typename X, typename T, typename P>
class RunTimeClassHelperEx
{
public:
	RunTimeClassHelperEx( const X& xType )
	{
		RunTimeClassFactoryEx<X>::GetInstance().RegistClassToFactory( xType, pFunCreaterEx(&RunTimeClassHelperEx<X,T,P>::Create) );
	}
	static T* Create( unsigned long param )
	{
		return new T( (P)param );
	}
};

// class CRunTimeDlgBuilder
// {
// public:
// 	static CRunTimeDlgBuilder& GetInstance( );
// 	CDialog* GetRunTimeDialog( const CString& strName, UINT32 uid, CWnd* parent = NULL );
// 	void HideAllCreateDialog(  );
// 	void SetWindowSize( const CRect& rect, const CWnd* pWndInsertAfter = NULL );
// 	void SetWindowPos( CDialog* pDialog );
// private:
// 	CRunTimeDlgBuilder();
// 	virtual ~CRunTimeDlgBuilder();
// 	CRunTimeDlgBuilder( const CRunTimeDlgBuilder& copy );
// private:
// 	map<CString, CDialog*> m_mapRunTimeDialog;
// 	CRect m_rectShow;
// 	const CWnd* m_pWinAfter;
// };

enum TEST_TYPE {};
enum CONFIG_TYPE {};
enum GRAPH_TYPE{};
#define RunTimeDialogBuilder CRunTimeDlgBuilder::GetInstance()
#define REGIST_RUNTIME_CLASS( KEY, K, T )   RunTimeClassHelper<KEY,T> _help_##T(K);
#define REGIST_RUNTIME_CLASS_CHAR( KEY, K, T )   RunTimeClassHelperEx<KEY,T, unsigned char> _help_##T(K);
#define REGIST_RUNTIME_CLASS_USHORT( KEY, K, T )   RunTimeClassHelperEx<KEY,T, unsigned short> _help_##T(K);
#define REGIST_RUNTIME_CLASS_PVOID( KEY, K, T )  RunTimeClassHelperEx<KEY,T, LPVOID> _help_##T(K);
#define REGIST_RUNTIME_DIALOG( T ) RunTimeClassHelper<CString, T> _help_##T( #T );
#define RunTimeDialog( X ) \
	dynamic_cast<X*>( CRunTimeDlgBuilder::GetInstance().GetRunTimeDialog( #X, X::IDD, this ) ) 
	