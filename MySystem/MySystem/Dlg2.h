#pragma once


// CDlg2 �Ի���

class CDlg2 : public CDialog
{
	DECLARE_DYNAMIC(CDlg2)

public:
	CDlg2(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlg2();

// �Ի�������
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ListCtr1;
	CListCtrl m_ListCtr2;
};
