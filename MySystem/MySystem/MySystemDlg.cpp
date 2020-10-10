
// MySystemDlg.cpp : ʵ���ļ�
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

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CMySystemDlg �Ի���



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


// CMySystemDlg ��Ϣ�������

BOOL CMySystemDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	// ΪTabCtrl�ؼ������ǩ
	m_tab.InsertItem(0, _T("ͼ���������"));
	m_tab.InsertItem(1, _T("�ߴ�������"));
	m_tab.InsertItem(2, _T("���ѡ����"));

	// ���������ӶԻ���
	m_page1.Create(IDD_DIALOG1, &m_tab);
	m_page2.Create(IDD_DIALOG2, &m_tab);
	m_page3.Create(IDD_DIALOG3, &m_tab);

	// �����ӶԻ����С��λ��
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

	// Ĭ�ϱ�ǩѡ��
	m_page1.ShowWindow(true);
	m_page2.ShowWindow(false);
	m_page3.ShowWindow(false);
	m_tab.SetCurSel(0);

	//�����б�ؼ����Ϊ�����ߣ�ѡ�и���
	m_page2.m_ListCtr1.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_page2.m_ListCtr2.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_page3.m_ListCtr3.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	//���ñ�ͷ
	CString strHeader1[3] = { L"���",L"�ߴ�(mm)",L"��ע" };
	CString strHeader2[3] = { L"���",L"�ߴ�(mm)",L"��ע" };
	CString strHeader3[5] = { L"����",L"��ߴ�(mm)",L"�ױ��",L"�׳ߴ�(mm)",L"��ϼ�϶(mm)" };
	for (int nCol = 0; nCol < 3; nCol++)
	{
		m_page2.m_ListCtr1.InsertColumn(nCol, strHeader1[nCol], LVCFMT_LEFT, 100);
		m_page2.m_ListCtr2.InsertColumn(nCol, strHeader2[nCol], LVCFMT_LEFT, 100);
	}
	for (int nCol = 0; nCol < 5; nCol++)
	{
		m_page3.m_ListCtr3.InsertColumn(nCol, strHeader3[nCol], LVCFMT_LEFT, 120);
	}

	CStdioFile file1(_T(".\\��ߴ�.txt"), CFile::modeRead | CFile::typeText);
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

	CStdioFile file2(_T(".\\�׳ߴ�.txt"), CFile::modeRead | CFile::typeText);
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

	CStdioFile file3(_T(".\\���ѡ��.txt"), CFile::modeRead | CFile::typeText);
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

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMySystemDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMySystemDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMySystemDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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