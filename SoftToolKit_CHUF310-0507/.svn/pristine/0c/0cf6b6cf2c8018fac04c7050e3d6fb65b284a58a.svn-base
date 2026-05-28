
// AlgsTestDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "AlgsTest.h"
#include "AlgsTestDlg.h"
#include "afxdialogex.h"

#include "../Include/Algorithm.h"

#include "fftTest.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAlgsTestDlg 对话框




CAlgsTestDlg::CAlgsTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAlgsTestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAlgsTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAlgsTestDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CAlgsTestDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CAlgsTestDlg 消息处理程序

BOOL CAlgsTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CAlgsTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CAlgsTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CAlgsTestDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	float* input = new float[128];

	double data[] = {860, 828, 824, 837, 856, 828, 844, 824, 841, 849, 854, 831, 846, 836, 837, 824, 
		810, 826, 825, 818, 836, 820, 805, 826, 832, 822, 816, 827, 835, 848, 813, 839, 848, 841, 
		863, 823, 840, 840, 821, 835, 808, 799, 817, 803, 829, 823, 815, 811, 822, 827, 820, 806, 
		818, 834, 819, 827, 831, 842, 849, 836, 831, 846, 808, 829, 826, 815, 825, 799, 818, 783, 
		808, 835, 833, 825, 814, 844, 818, 834, 852, 860, 838, 837, 816, 863, 840, 847, 853, 868, 
		834, 862, 844, 840, 866, 806, 814, 821, 817, 852, 847, 833, 827, 839, 823, 843, 846, 806, 
		832, 853, 826, 848, 816, 830, 809, 839, 814, 830, 829, 814, 805, 830, 819, 831, 814, 817, 
		817, 820, 827, 837, 836, 829, 814, 807, 803, 828, 827, 823, 817, 812, 829, 807, 808, 825, 
		815, 825, 803, 798, 804, 802, 833, 810, 788, 806, 819, 790, 806, 812, 812, 808, 825, 810, 
		808, 801, 828, 827, 809, 807, 836, 827, 826, 823, 823, 812, 862, 814, 826, 817, 807, 810, 
		832, 829, 837, 844, 821, 817, 820, 802, 807, 802, 814, 827, 833, 810, 804, 808, 831, 820, 
		829, 825, 819, 816, 807, 776, 813, 814, 792, 827, 803, 799, 816, 800, 825, 811, 833, 806, 
		816, 815, 828, 811, 839, 838, 830, 832, 824, 837, 818, 832, 826, 857, 830, 819, 842, 840, 
		834, 838, 828, 846, 820, 843, 833, 833, 845, 849, 826, 828, 844, 825, 859, 823, 848, 847, 
		842, 835, 850, 816, 843, 834, 847, 839, 862, 833, 844, 820, 825, 839, 823, 809, 842, 828, 
		844, 854, 817, 820, 837, 850};

	for(int index = 0; index < 128; index++)
	{
		//input[index] = (float)(1 * 64);
		x[index][0] = (int)data[index];
		x[index][1] = 0;

		input[index] = (float)data[index];
	}



	fft2();

	fft_test( input, 128 );

	
}
