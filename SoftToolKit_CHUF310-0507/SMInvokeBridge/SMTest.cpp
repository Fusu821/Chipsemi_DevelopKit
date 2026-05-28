// 这是主 DLL 文件。

#include "stdafx.h"

using namespace System;
using namespace System::Collections::Generic;

#include "SMTest.h"
//#include "../Include/NativeTestInterface.h"
#include <stdlib.h>
#include <string.h>
#include <msclr\marshal_cppstd.h>
//..
using namespace msclr::interop;

namespace SMTestBridge{


	SMComplex::SMComplex()
		:m_TestProxyAddr(nullptr)
	{
		m_TestProxyAddr = GetTestWapperInterface();
	}
	SMComplex::~SMComplex()
	{
		ReleaseTestWrapperInterface(m_TestProxyAddr);
		m_TestProxyAddr = nullptr;
	}

	unsigned int SMComplex::StartTest()
	{
		return ERROR_CODE_OK;
	}

// 	void SMComplex::RegistSMTestCallBack(SMCallBack^ callBack)
// 	{
// 		NativeCallBack navCallBack;
// 		IntPtr itemChangeAddr = System::Runtime::InteropServices::Marshal::GetFunctionPointerForDelegate(callBack->onListItemChange);
// 		navCallBack.onListItemChange = reinterpret_cast<OnListItemChangeCallBack>(itemChangeAddr.ToInt32());
// 
// 		IntPtr processBarChangeAddr = System::Runtime::InteropServices::Marshal::GetFunctionPointerForDelegate(callBack->onProcessBarChanging);
// 		navCallBack.onProcssBarChanging = reinterpret_cast<OnProcessBarChangingCallBack>(processBarChangeAddr.ToInt32());
// 
// 		IntPtr initProcessBarAddr = System::Runtime::InteropServices::Marshal::GetFunctionPointerForDelegate(callBack->onInitProcessBar);
// 		navCallBack.onInitProcessBar = reinterpret_cast<OnInitProcessBarCallBack>(initProcessBarAddr.ToInt32());
// 
// 		IntPtr oneTestOverAddr = System::Runtime::InteropServices::Marshal::GetFunctionPointerForDelegate(callBack->onOneTestOver);
// 		navCallBack.onOneTestOver = reinterpret_cast<OnOneTestOverCallBack>(oneTestOverAddr.ToInt32());
// 
// 		m_TestProxyAddr->RegistComplexCallBack(navCallBack);
// 	}

}

