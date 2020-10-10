#pragma once

using namespace cv;
// CDlg1 对话框

class CDlg1 : public CDialog
{
	DECLARE_DYNAMIC(CDlg1)

public:
	CDlg1(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlg1();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	void ShowMat(Mat img);
	afx_msg void OnBnClickedButton2();
	void SaveMat();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton12();
	afx_msg void OnBnClickedButton13();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton14();
	afx_msg void OnBnClickedButton15();
	afx_msg void OnBnClickedButton16();
	afx_msg void OnBnClickedButton17();
	Mat grayju(Mat img, double T, double q);
	afx_msg void OnBnClickedButton19();
	Mat AtanMat(Mat img1, Mat img2);
	Mat SinMat(Mat img);
	Mat CosMat(Mat img);
	double SumMat(Mat img);
	double CircleFitting(Mat img);
	afx_msg void OnBnClickedButton4();
	Mat ZernikeJu(Mat img, Mat img1);
	CEdit m_edit1;
	CEdit m_edit2;
	int if_read = 0;
	Mat showpic;
	afx_msg void OnBnClickedButton20();
	double LineFitting(Mat img);
	afx_msg void OnBnClickedButton3();
	Mat MatReverse(Mat img);
	afx_msg void OnBnClickedButton18();
	afx_msg void OnBnClickedButton6();
};
