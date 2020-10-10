
// MySystemDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MySystem.h"
#include "MySystemDlg.h"
#include "afxdialogex.h"
#include "Dlg1.h"
#include "Dlg2.h"
#include "Dlg3.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CDlg1 m_page1;
CDlg2 m_page2;
CDlg3 m_page3;

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMySystemDlg 对话框



CMySystemDlg::CMySystemDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMySystemDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMySystemDlg::DoDataExchange(CDataExchange* pDX)
{
	DDX_Control(pDX, IDC_TAB1, m_tab);
}

BEGIN_MESSAGE_MAP(CMySystemDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CMySystemDlg::OnTcnSelchangeTab1)
END_MESSAGE_MAP()


// CMySystemDlg 消息处理程序

BOOL CMySystemDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码

	// 为TabCtrl控件插入标签
	m_tab.InsertItem(0, _T("图像处理与测量"));
	m_tab.InsertItem(1, _T("尺寸测量结果"));
	m_tab.InsertItem(2, _T("轴孔选配结果"));

	// 创建三个子对话框
	m_page1.Create(IDD_DIALOG1, &m_tab);
	m_page2.Create(IDD_DIALOG2, &m_tab);
	m_page3.Create(IDD_DIALOG3, &m_tab);

	// 调整子对话框大小及位置
	CRect rc;
	m_tab.GetClientRect(&rc);
	CRect rcTabItem;
	m_tab.GetItemRect(0, rcTabItem);
	rc.top += rcTabItem.Height() + 4;
	rc.left += 4;
	rc.bottom -= 4;
	rc.right -= 4;
	m_page1.MoveWindow(&rc);
	m_page2.MoveWindow(&rc);
	m_page3.MoveWindow(&rc);

	// 默认标签选中
	m_page1.ShowWindow(true);
	m_page2.ShowWindow(false);
	m_page3.ShowWindow(false);
	m_tab.SetCurSel(0);

	//设置列表控件风格为网格线，选中高亮
	m_page2.m_ListCtr1.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_page2.m_ListCtr2.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_page3.m_ListCtr3.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	//设置表头
	CString strHeader1[3] = { L"编号",L"尺寸(mm)",L"备注" };
	CString strHeader2[3] = { L"编号",L"尺寸(mm)",L"备注" };
	CString strHeader3[5] = { L"轴编号",L"轴尺寸(mm)",L"孔编号",L"孔尺寸(mm)",L"配合间隙(mm)" };
	for (int nCol = 0; nCol < 3; nCol++)
	{
		m_page2.m_ListCtr1.InsertColumn(nCol, strHeader1[nCol], LVCFMT_LEFT, 100);
		m_page2.m_ListCtr2.InsertColumn(nCol, strHeader2[nCol], LVCFMT_LEFT, 100);
	}
	for (int nCol = 0; nCol < 5; nCol++)
	{
		m_page3.m_ListCtr3.InsertColumn(nCol, strHeader3[nCol], LVCFMT_LEFT, 120);
	}

	CStdioFile file1(_T(".\\轴尺寸.txt"), CFile::modeRead | CFile::typeText);
	CString str1, sLeft1, sRight1;
	int nLine1 = 0;
	while(file1.ReadString(str1))
	{
		sLeft1 = str1.Left(str1.Find(L"     ", 0));
		sRight1 = str1.Mid(str1.Find(L"     ", 0) + strlen("     "));
		m_page2.m_ListCtr1.InsertItem(nLine1, sLeft1);
		m_page2.m_ListCtr1.SetItemText(nLine1, 1, sRight1);
		nLine1++;
	}
	file1.Close();

	CStdioFile file2(_T(".\\孔尺寸.txt"), CFile::modeRead | CFile::typeText);
	CString str2, sLeft2, sRight2;
	int nLine2 = 0;
	while (file2.ReadString(str2))
	{
		sLeft2 = str2.Left(str2.Find(L"     ", 0));
		sRight2 = str2.Mid(str2.Find(L"     ", 0) + strlen("     "));
		m_page2.m_ListCtr2.InsertItem(nLine2, sLeft2);
		m_page2.m_ListCtr2.SetItemText(nLine2, 1, sRight2);
		nLine2++;
	}
	file2.Close();

	CStdioFile file3(_T(".\\轴孔选配.txt"), CFile::modeRead | CFile::typeText);
	CString str3, ss1, ss2, ss3, ss4, ss5;
	int nLine3 = 0;
	while (file3.ReadString(str3))
	{
		ss1 = str3.Mid(0, 4);
		ss2 = str3.Mid(9, 7);
		ss3 = str3.Mid(21, 4);
		ss4 = str3.Mid(30, 7);
		ss5 = str3.Mid(42, 7);
		m_page3.m_ListCtr3.InsertItem(nLine3, ss1);
		m_page3.m_ListCtr3.SetItemText(nLine3, 1, ss2);
		m_page3.m_ListCtr3.SetItemText(nLine3, 2, ss3);
		m_page3.m_ListCtr3.SetItemText(nLine3, 3, ss4);
		m_page3.m_ListCtr3.SetItemText(nLine3, 4, ss5);
		nLine3++;
	}
	file3.Close();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMySystemDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMySystemDlg::OnPaint()
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
HCURSOR CMySystemDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMySystemDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  在此添加控件通知处理程序代码
	switch (m_tab.GetCurSel())
	{
	case 0:
		m_page1.UpdateWindow();
		m_page1.ShowWindow(true);
		m_page2.ShowWindow(false);
		m_page3.ShowWindow(false);
		break;
	case 1:
		m_page2.ShowWindow(true);
		m_page1.ShowWindow(false);
		m_page3.ShowWindow(false);
		break;
	case 2:
		m_page3.ShowWindow(true);
		m_page2.ShowWindow(false);
		m_page1.ShowWindow(false);
		break;
	default:
		break;
	}
	*pResult = 0;
}