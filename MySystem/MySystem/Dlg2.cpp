// Dlg2.cpp : 实现文件
//

#include "stdafx.h"
#include "MySystem.h"
#include "Dlg2.h"
#include "afxdialogex.h"


// CDlg2 对话框

IMPLEMENT_DYNAMIC(CDlg2, CDialog)

CDlg2::CDlg2(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg2::IDD, pParent)
{

}

CDlg2::~CDlg2()
{
}

void CDlg2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST7, m_ListCtr1);
	DDX_Control(pDX, IDC_LIST6, m_ListCtr2);
}


BEGIN_MESSAGE_MAP(CDlg2, CDialog)
END_MESSAGE_MAP()


// CDlg2 消息处理程序
