// Dlg3.cpp : 实现文件
//

#include "stdafx.h"
#include "MySystem.h"
#include "Dlg3.h"
#include "afxdialogex.h"


// CDlg3 对话框

IMPLEMENT_DYNAMIC(CDlg3, CDialog)

CDlg3::CDlg3(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg3::IDD, pParent)
{

}

CDlg3::~CDlg3()
{
}

void CDlg3::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListCtr3);
}


BEGIN_MESSAGE_MAP(CDlg3, CDialog)
END_MESSAGE_MAP()


// CDlg3 消息处理程序
