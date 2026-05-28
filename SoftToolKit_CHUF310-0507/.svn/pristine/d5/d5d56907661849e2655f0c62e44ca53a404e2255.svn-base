// SMTestApp.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "SMTestApp.h"

#include <ShellAPI.h>
#include <com-loader.hpp>
#include "CMainWnd.h"

//#include "../controls.extend/SMcListViewEx/SMCListViewEx.h"
#include <../components/render-gdi/render-gdi.h>
#include <../components/imgdecoder-wic/imgdecoder-wic.h>
#include "FrameLayOut/ImageGraph.h"
#include "FrameLayOut/TestPacker.h"
#include "FrameLayOut/SMCListView2.h"

//#include "onlinelog.h"

// #ifdef _DEBUG
// #define SYS_NAMED_RESOURCE _T("soui-sys-resourced.dll")
// #else
#define SYS_NAMED_RESOURCE _T("soui-sys-resource.dll")
//#endif

#define MAX_LOADSTRING          100
#define APP_ALREAD_EXIST		183

// 全局变量:
HINSTANCE hInst;								// 当前实例
TCHAR szTitle[MAX_LOADSTRING];					// 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING];			// 主窗口类名

// 此代码模块中包含的函数的前向声明:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT32, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT32, WPARAM, LPARAM);


// static HINSTANCE hDll1 = LoadLibrary( _T("SMCP\\BSPR.dll") );
// static HINSTANCE hDll2 = LoadLibrary( _T("SMCP\\HalUSBLayerSrv.dll") );
// static HINSTANCE hDll3 = LoadLibrary( _T("SMCP\\SEMITouch.dll") );
// static HINSTANCE hDll4 = LoadLibrary( _T("SMCP\\SEMITest.dll") );


// BOOL CheckDotNetInstallation( LPTSTR lpCmdLine )
// {
//     //HKEY ck;
// 	//BOOLEAN bNetInatallOk = TRUE;
// 
// 	OSVERSIONINFO osver = { sizeof(OSVERSIONINFO) };  
// 	GetVersionEx( &osver ); 
// 
// 	TCHAR chTemp[MAX_PATH] = {0};
// 	transformat( chTemp, _T("OS Main Ver = %d, Minor Ver = %d"), osver.dwMajorVersion, osver.dwMinorVersion );
// 	OnLineLogApp.AppendLogMessage( chTemp );
// 
// 	stuCommandLine.ParseCommandLine( tstring(lpCmdLine) );
// 	if( stuCommandLine.HaveCommnd( _T("-XP") ) )
// 	{
// 		OnLineLogApp.AppendLogMessage( _T("Force Start Native App") );
// 		return FALSE;
// 	}
// 	else if( stuCommandLine.HaveCommnd( _T("-NET") ) )
// 	{
// 		OnLineLogApp.AppendLogMessage( _T("Force Start Net App") );
// 		return TRUE;
// 	}
// 
// 	//vista
// 	if( osver.dwMajorVersion == 5 && osver.dwMinorVersion == 2 )
// 		return TRUE;
// 	//win 7
// 	else if ( osver.dwMajorVersion == 6 && osver.dwMinorVersion == 1 )  
// 		return TRUE;
// 	//win 8
// 	else if( osver.dwMajorVersion == 6 && osver.dwMinorVersion == 2 )  
// 		return TRUE;
// 	//win 10
// 	else if( osver.dwMajorVersion == 10 )
// 		return TRUE;
// 	else 
// 		return FALSE;
// 
// 	//return bNetInatallOk;
// }

// LPCTSTR GetExecutePath()
// {
// 	static TCHAR chPath[MAX_PATH] = {0};
// 	::GetModuleFileName( NULL, chPath, MAX_PATH );
// 	*(_tcsrchr( chPath, _T('\\') )) = 0;
// 	//*(_tcsrchr( chPath, _T('\\') )) = 0;
// 
// 	return chPath;
// }

// bool StartPrcess( LPCTSTR szDir, LPCTSTR strProcessName, LPTSTR lpCmdLine )
// {
// 	//启动程序
// 	//ShellExecute(NULL, _T("open"), strProcessName, NULL, NULL, SW_SHOWNORMAL);
// 	PROCESS_INFORMATION ProcessInfo; 
// 	STARTUPINFO StartupInfo; //This is an [in] parameter 
// 	ZeroMemory(&StartupInfo, sizeof(StartupInfo)); 
// 	StartupInfo.cb = sizeof StartupInfo ; //Only compulsory field 
// 	if(CreateProcess(strProcessName, lpCmdLine, 
// 		NULL,NULL,FALSE,CREATE_BREAKAWAY_FROM_JOB,NULL, 
// 		szDir,&StartupInfo,&ProcessInfo)) 
// 	{
// 
// 	}
// 	else
// 	{
// 		DWORD dwErr = GetLastError();
// 		TCHAR chTemp[100] = {0};
// 		transformat( chTemp, _T("Create Process, ErrorCode = %d"), dwErr );
// 		OnLineLogApp.AppendLogMessage( chTemp );
// 	}
// 
// 	return true;
// }

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
// 	OnLineLogApp.OnInitLogParam( NULL, _T("SMCP\\") );
// 	{
// 		OnLineLogApp.AppendLogMessage( _T("Check Dot Net Installation") );
// 	}

// 	if( CheckDotNetInstallation( lpCmdLine ) )
// 	{
// 		OnLineLogApp.AppendLogMessage("Start Dot Net SMApp");
// 
// 		tstring szDir = GetExecutePath();
// 		tstring szPath = szDir;
// 
// 		szDir += _T("\\SMCP");
// 		szPath += _T("\\SMCP\\SEMITestApp.smp");
// 		StartPrcess( szDir.c_str(), szPath.c_str(), lpCmdLine );
// 
// 		return -1;
// 	}

	CreateMutex(NULL, TRUE, _T("CHIP_SEMI_TESTER"));
	if(GetLastError() == APP_ALREAD_EXIST)	//only one app is running
	{
		MessageBox( NULL, _T("A Instance of SMTest has been on"), _T("Info"), 0 );
		return FALSE;
	}

	//OnLineLogApp.AppendLogMessage("Start Native C++ SMApp");

	HRESULT hRes = OleInitialize(NULL);
	SASSERT(SUCCEEDED(hRes));

	//SetDllDirectory(_T("..\\SMCP\\"));

 	int nRet = 0; 
 	TCHAR szCurrentDir[MAX_PATH]={0};
 	GetModuleFileName( NULL, szCurrentDir, sizeof(szCurrentDir) );
 	LPTSTR lpInsertPos = _tcsrchr( szCurrentDir, _T('\\') );
	*lpInsertPos = 0;
 	//_tcscpy(lpInsertPos+1,_T("SMCP"));
 	SetCurrentDirectory(szCurrentDir);
 
 	{
 		CAutoRefPtr<SOUI::IImgDecoderFactory> pImgDecoderFactory;
 		CAutoRefPtr<SOUI::IRenderFactory> pRenderFactory;

		SOUI::RENDER_GDI::SCreateInstance((IObjRef**)&pRenderFactory);
		SOUI::IMGDECODOR_WIC::SCreateInstance((IObjRef**)&pImgDecoderFactory);

 		pRenderFactory->SetImgDecoderFactory(pImgDecoderFactory);
 
 		SApplication *theApp=new SApplication(pRenderFactory,hInstance);

		theApp->RegisterWindowClass<SHeaderCtrl2>();
		theApp->RegisterWindowClass<CImageGraph>();
		theApp->RegisterWindowClass<CTestPacket>();

		//theApp->RegisterWindowClass<SMCListViewEx>();
 		HMODULE hSysResource=LoadLibrary(SYS_NAMED_RESOURCE);
 		if(hSysResource)
 		{
 			CAutoRefPtr<IResProvider> sysSesProvider;
 			CreateResProvider(RES_PE,(IObjRef**)&sysSesProvider);
 			sysSesProvider->Init((WPARAM)hSysResource,0);
 			theApp->LoadSystemNamedResource(sysSesProvider);
 		}


		CAutoRefPtr<IResProvider>   pResProvider;
		CreateResProvider(RES_FILE,(IObjRef**)&pResProvider);
		if(!pResProvider->Init((LPARAM)_T("uires"),0))
		{
			SASSERT(0);
			return 1;
		}
		theApp->AddResProvider(pResProvider);
		//2.x版本已经不需要下面这行。
		//theApp->Init(_T("XML_INIT")); 

		{   //在这里加入主窗口运行代码
			CMainWnd wndMain( lpCmdLine );  
			wndMain.Create(GetActiveWindow(),0,0,0,0);
			wndMain.SendMessage(WM_INITDIALOG);
			wndMain.CenterWindow(wndMain.m_hWnd);
			wndMain.ShowWindow(SW_SHOWNORMAL);
			nRet=theApp->Run(wndMain.m_hWnd);
		}

		delete theApp;
 	}
 
 	OleUninitialize();
	return nRet;
}



////
////  函数: MyRegisterClass()
////
////  目的: 注册窗口类。
////
////  注释:
////
////    仅当希望
////    此代码与添加到 Windows 95 中的“RegisterClassEx”
////    函数之前的 Win32 系统兼容时，才需要此函数及其用法。调用此函数十分重要，
////    这样应用程序就可以获得关联的
////    “格式正确的”小图标。
////
//ATOM MyRegisterClass(HINSTANCE hInstance)
//{
//	WNDCLASSEX wcex;
//
//	wcex.cbSize = sizeof(WNDCLASSEX);
//
//	wcex.style			= CS_HREDRAW | CS_VREDRAW;
//	wcex.lpfnWndProc	= WndProc;
//	wcex.cbClsExtra		= 0;
//	wcex.cbWndExtra		= 0;
//	wcex.hInstance		= hInstance;
//	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SMTESTAPP));
//	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
//	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
//	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_SMTESTAPP);
//	wcex.lpszClassName	= szWindowClass;
//	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
//
//	return RegisterClassEx(&wcex);
//}
//
////
////   函数: InitInstance(HINSTANCE, int)
////
////   目的: 保存实例句柄并创建主窗口
////
////   注释:
////
////        在此函数中，我们在全局变量中保存实例句柄并
////        创建和显示主程序窗口。
////
//BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
//{
//   HWND hWnd;
//
//   hInst = hInstance; // 将实例句柄存储在全局变量中
//
//   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
//      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
//
//   if (!hWnd)
//   {
//      return FALSE;
//   }
//
//   ShowWindow(hWnd, nCmdShow);
//   UpdateWindow(hWnd);
//
//   return TRUE;
//}
//
////
////  函数: WndProc(HWND, UINT32, WPARAM, LPARAM)
////
////  目的: 处理主窗口的消息。
////
////  WM_COMMAND	- 处理应用程序菜单
////  WM_PAINT	- 绘制主窗口
////  WM_DESTROY	- 发送退出消息并返回
////
////
//LRESULT CALLBACK WndProc(HWND hWnd, UINT32 message, WPARAM wParam, LPARAM lParam)
//{
//	int wmId, wmEvent;
//	PAINTSTRUCT ps;
//	HDC hdc;
//
//	switch (message)
//	{
//	case WM_COMMAND:
//		wmId    = LOWORD(wParam);
//		wmEvent = HIWORD(wParam);
//		// 分析菜单选择:
//		switch (wmId)
//		{
//		case IDM_ABOUT:
//			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
//			break;
//		case IDM_EXIT:
//			DestroyWindow(hWnd);
//			break;
//		default:
//			return DefWindowProc(hWnd, message, wParam, lParam);
//		}
//		break;
//	case WM_PAINT:
//		hdc = BeginPaint(hWnd, &ps);
//		// TODO: 在此添加任意绘图代码...
//		EndPaint(hWnd, &ps);
//		break;
//	case WM_DESTROY:
//		PostQuitMessage(0);
//		break;
//	default:
//		return DefWindowProc(hWnd, message, wParam, lParam);
//	}
//	return 0;
//}
//
//// “关于”框的消息处理程序。
//INT_PTR CALLBACK About(HWND hDlg, UINT32 message, WPARAM wParam, LPARAM lParam)
//{
//	UNREFERENCED_PARAMETER(lParam);
//	switch (message)
//	{
//	case WM_INITDIALOG:
//		return (INT_PTR)TRUE;
//
//	case WM_COMMAND:
//		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
//		{
//			EndDialog(hDlg, LOWORD(wParam));
//			return (INT_PTR)TRUE;
//		}
//		break;
//	}
//	return (INT_PTR)FALSE;
//}
