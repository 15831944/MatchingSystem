// Dlg1.cpp : 实现文件
//

#include "stdafx.h"
#include "MySystem.h"
#include "Dlg1.h"
#include "Dlg2.h"
#include "afxdialogex.h"
#include "atlimage.h"
#include <time.h> 

using namespace cv;
using namespace std;
// CDlg1 对话框


Mat src;
int ii1 = 0, ii2 = 0;
clock_t startTime, endTime;


IMPLEMENT_DYNAMIC(CDlg1, CDialog)

CDlg1::CDlg1(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg1::IDD, pParent)
{
	if (if_read != 0)
	{
		ShowMat(showpic);
	}
}

CDlg1::~CDlg1()
{
}

void CDlg1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edit1);
	DDX_Control(pDX, IDC_EDIT2, m_edit2);
}


BEGIN_MESSAGE_MAP(CDlg1, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlg1::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDlg1::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON5, &CDlg1::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON8, &CDlg1::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON11, &CDlg1::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON12, &CDlg1::OnBnClickedButton12)
	ON_BN_CLICKED(IDC_BUTTON13, &CDlg1::OnBnClickedButton13)
	ON_BN_CLICKED(IDC_BUTTON7, &CDlg1::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON9, &CDlg1::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &CDlg1::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON14, &CDlg1::OnBnClickedButton14)
	ON_BN_CLICKED(IDC_BUTTON15, &CDlg1::OnBnClickedButton15)
	ON_BN_CLICKED(IDC_BUTTON16, &CDlg1::OnBnClickedButton16)
	ON_BN_CLICKED(IDC_BUTTON17, &CDlg1::OnBnClickedButton17)
	ON_BN_CLICKED(IDC_BUTTON19, &CDlg1::OnBnClickedButton19)
	ON_BN_CLICKED(IDC_BUTTON4, &CDlg1::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON20, &CDlg1::OnBnClickedButton20)
	ON_BN_CLICKED(IDC_BUTTON3, &CDlg1::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON18, &CDlg1::OnBnClickedButton18)
	ON_BN_CLICKED(IDC_BUTTON6, &CDlg1::OnBnClickedButton6)
END_MESSAGE_MAP()


// CDlg1 消息处理程序




void CDlg1::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	CString filter;
	filter = "All Files (*.*)|*.*|JPG图片(*.jpg)|*.jpg|BMP图像(*.bmp)|*.bmp|PNG图片(*.png)|*.png||";
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, filter);
	dlg.m_ofn.lpstrTitle = _T("打开图片");  //打开对话窗口标题名
	if (dlg.DoModal() != IDOK)
	{
		MessageBoxA(NULL, "未打开图片", "提示", IDOK);
		return;
	}
	CString path = dlg.GetPathName();
	std::string tpath = (LPCSTR)CStringA(path);
	const char* mpath = tpath.c_str();
    src = imread(mpath);
	ShowMat(src);
	showpic = src.clone();
	if_read = 1;
}


void CDlg1::ShowMat(Mat img)
{
	// TODO: 在此处添加实现代码.
	CDC* pDC = GetDlgItem(IDC_STATIC)->GetDC();
	HDC hDC = pDC->GetSafeHdc();
	IplImage Img = img;
	CvvImage cimg;
	cimg.CopyOf(&Img);
	CRect rect;
	GetDlgItem(IDC_STATIC)->GetClientRect(&rect);
	cimg.DrawToHDC(hDC, &rect);
	ReleaseDC(pDC);
}


void CDlg1::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	SaveMat();
}


void CDlg1::SaveMat()
{
	// TODO: 在此处添加实现代码.
	CWnd* bmpShow = GetDlgItem(IDC_STATIC);
	CDC *pdc = bmpShow->GetDC();
	ATL::CImage imag;
	CRect rect;
	GetClientRect(&rect);        //获取画布大小  
	bmpShow->GetWindowRect(&rect);
	imag.Create(rect.Width(), rect.Height(), 32);
	::BitBlt(imag.GetDC(), 0, 0, rect.Width(), rect.Height(), pdc->m_hDC, 0, 0, SRCCOPY);
	TCHAR szFilter[] = _T("jpg file(*.jpg)|*.jpg|bmp file(*.bmp)|*.bmp|png file(*.png)|*.png|所有文件(*.*)|*.*||");  //文件格式过滤  
	// 构造保存文件对话框      
	CFileDialog fileDlg(FALSE, _T("bmp"), _T("*.bmp"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);
	fileDlg.m_ofn.lpstrTitle = _T("保存图片");  //保存对话窗口标题名 
	if (fileDlg.DoModal() != IDOK)
	{
		MessageBoxA(NULL, "未保存图片", "提示", IDOK);
		return;
	}
	CString path = fileDlg.GetPathName();
	imag.Save(path); //保存图片  
	ReleaseDC(pdc);
	imag.ReleaseDC();
}



void CDlg1::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	if (if_read == 0)
	{
		MessageBoxA(NULL, "未打开图片", "提示", IDOK);
		return;
	}
	Mat gray;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	ShowMat(gray);
	showpic = gray.clone();
	//imwrite("C:\\Users\\明友\\Desktop\\全部程序\\采集图片\\gray_weight.bmp", gray);
}


void CDlg1::OnBnClickedButton8()
{
	// TODO: 在此添加控件通知处理程序代码
	if (if_read == 0)
	{
		MessageBoxA(NULL, "未打开图片", "提示", IDOK);
		return;
	}
	Mat dst, dst1;
	cvtColor(src, dst, COLOR_BGR2GRAY);
	blur(dst, dst1, Size(3, 3), Point(-1, -1));
	ShowMat(dst1);
	showpic = dst1.clone();
	//imwrite("C:\\Users\\明友\\Desktop\\全部程序\\采集图片\\均值滤波s.bmp", dst1);
}


void CDlg1::OnBnClickedButton11()
{
	// TODO: 在此添加控件通知处理程序代码
	if (if_read == 0)
	{
		MessageBoxA(NULL, "未打开图片", "提示", IDOK);
		return;
	}
	Mat dst, dst1;
	cvtColor(src, dst, COLOR_BGR2GRAY);
	GaussianBlur(dst, dst1, Size(3, 3), 1);
	ShowMat(dst1);
	showpic = dst1.clone();
	//imwrite("C:\\Users\\明友\\Desktop\\全部程序\\采集图片\\高斯滤波s.bmp", dst1);
}


void CDlg1::OnBnClickedButton12()
{
	// TODO: 在此添加控件通知处理程序代码
	if (if_read == 0)
	{
		MessageBoxA(NULL, "未打开图片", "提示", IDOK);
		return;
	}
	Mat dst, dst1;
	cvtColor(src, dst, COLOR_BGR2GRAY);
	medianBlur(dst, dst1, 3);
	ShowMat(dst1);
	showpic = dst1.clone();
	//imwrite("C:\\Users\\明友\\Desktop\\全部程序\\采集图片\\中值滤波s.bmp", dst1);
}


void CDlg1::OnBnClickedButton13()
{
	// TODO: 在此添加控件通知处理程序代码
	if (if_read == 0)
	{
		MessageBoxA(NULL, "未打开图片", "提示", IDOK);
		return;
	}
	Mat dst, dst1;
	cvtColor(src, dst, COLOR_BGR2GRAY);
	bilateralFilter(dst, dst1, 30, 30*2, 30/2);
	ShowMat(dst1);
	showpic = dst1.clone();
	//imwrite("C:\\Users\\明友\\Desktop\\全部程序\\采集图片\\双边滤波s.bmp", dst1);
}


void CDlg1::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	if (if_read == 0)
	{
		MessageBoxA(NULL, "未打开图片", "提示", IDOK);
		return;
	}
	Mat dst, dst1;
	cvtColor(src, dst, COLOR_RGB2GRAY);
	threshold(dst, dst1, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);//大津法
	ShowMat(dst1);
	showpic = dst1.clone();
	//imwrite("C:\\Users\\明友\\Desktop\\全部程序\\采集图片\\OTSU.bmp", dst1);
}


void CDlg1::OnBnClickedButton9()
{
	// TODO: 在此添加控件通知处理程序代码
	if (if_read == 0)
	{
		MessageBoxA(NULL, "未打开图片", "提示", IDOK);
		return;
	}
	Mat dst, dst1, dst2, dst3;
	cvtColor(src, dst, COLOR_BGR2GRAY);
	medianBlur(dst, dst1, 3);
	dst2 = dst1.clone();
	int nRows = dst.rows;
	int nCols = dst.cols;
	for (int i = 0; i < nRows - 1; i++)
	{
		for (int j = 0; j < nCols - 1; j++)
		{
			int t1 = dst1.at<uchar>(i, j) -
				dst1.at<uchar>(i + 1, j + 1);
			int t2 = dst1.at<uchar>(i + 1, j) -
				dst1.at<uchar>(i, j + 1);
			dst2.at<uchar>(i, j) = abs(t1) + abs(t2);
		}
	}
	for (int i = 0; i < nRows; i++)
	{
		dst2.at<uchar>(i, nCols - 1) = 0;
	}
	for (int j = 0; j < nCols; j++)
	{
		dst2.at<uchar>(nRows-1, j) = 0;
	}
	if (dst.at<uchar>(src.rows / 2, src.cols / 2) < 100)
	{
		threshold(dst2, dst3, 50, 255, CV_THRESH_BINARY_INV);
	}
	else
	{
		threshold(dst2, dst3, 0, 255, CV_THRESH_BINARY_INV | CV_THRESH_OTSU);
	}
	ShowMat(dst3);
	showpic = dst3.clone();
	//imwrite("C:\\Users\\明友\\Desktop\\全部程序\\采集图片\\Roberts.bmp", dst3);
}


void CDlg1::OnBnClickedButton10()
{
	// TODO: 在此添加控件通知处理程序代码
	if (if_read == 0)
	{
		MessageBoxA(NULL, "未打开图片", "提示", IDOK);
		return;
	}
	Mat src_gray, grad, dst, dst1;
	cvtColor(src, src_gray, COLOR_BGR2GRAY);
	medianBlur(src_gray, dst, 3);
	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y;
	Sobel(dst, grad_x, CV_16S, 1, 0, 3);
	Sobel(dst, grad_y, CV_16S, 0, 1, 3);
	convertScaleAbs(grad_x, abs_grad_x);
	convertScaleAbs(grad_y, abs_grad_y);
	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);
	threshold(grad, dst1, 0, 255, CV_THRESH_BINARY_INV | CV_THRESH_OTSU);
	ShowMat(dst1);
	showpic = dst1.clone();
	//imwrite("C:\\Users\\明友\\Desktop\\全部程序\\采集图片\\Sobel.bmp", dst1);
}


void CDlg1::OnBnClickedButton14()
{
	// TODO: 在此添加控件通知处理程序代码
	if (if_read == 0)
	{
		MessageBoxA(NULL, "未打开图片", "提示", IDOK);
		return;
	}
	Mat gray, Kernelx, Kernely, dst;
	cvtColor(src, gray, CV_RGB2GRAY);
	medianBlur(gray, dst, 3);
	Kernelx = (Mat_<double>(3, 3) << 1, 1, 1, 0, 0, 0, -1, -1, -1);
	Kernely = (Mat_<double>(3, 3) << -1, 0, 1, -1, 0, 1, -1, 0, 1);
	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y, grad, dst1;
	filter2D(dst, grad_x, CV_16S, Kernelx, Point(-1, -1));
	filter2D(dst, grad_y, CV_16S, Kernely, Point(-1, -1));
	convertScaleAbs(grad_x, abs_grad_x);
	convertScaleAbs(grad_y, abs_grad_y);
	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);
	threshold(grad, dst1, 0, 255, CV_THRESH_BINARY_INV | CV_THRESH_OTSU);
	ShowMat(dst1);
	showpic = dst1.clone();
	//imwrite("C:\\Users\\明友\\Desktop\\全部程序\\采集图片\\Prewitt.bmp", dst1);
}


void CDlg1::OnBnClickedButton15()
{
	// TODO: 在此添加控件通知处理程序代码
	if (if_read == 0)
	{
		MessageBoxA(NULL, "未打开图片", "提示", IDOK);
		return;
	}
	Mat src_gray, dst, dst1, dst2, dst3;
	cvtColor(src, src_gray, COLOR_BGR2GRAY);
	medianBlur(src_gray, dst, 3);
	Laplacian(dst, dst1, CV_16S, 3);
	convertScaleAbs(dst1, dst2);
	threshold(dst2, dst3, 0, 255, CV_THRESH_BINARY_INV | CV_THRESH_OTSU);
	ShowMat(dst3);
	showpic = dst3.clone();
	//imwrite("C:\\Users\\明友\\Desktop\\全部程序\\采集图片\\Laplacian.bmp", dst3);
}


void CDlg1::OnBnClickedButton16()
{
	// TODO: 在此添加控件通知处理程序代码
	if (if_read == 0)
	{
		MessageBoxA(NULL, "未打开图片", "提示", IDOK);
		return;
	}
	Mat Kernel, dst, dst1, dst2;
	cvtColor(src, dst, CV_RGB2GRAY);
	medianBlur(dst, dst1, 3);
	Kernel = (Mat_<double>(5, 5) << 0, 0, -1, 0, 0, 0, -1, -2, -1, 0, -1, -2, 16, -2, -1, 0, -1, -2, -1, 0, 0, 0, -1, 0, 0);
	Mat grad, abs_grad;
	filter2D(dst1, grad, CV_16S, Kernel, Point(-1, -1));
	convertScaleAbs(grad, abs_grad);
	threshold(abs_grad, dst2, 254, 255, CV_THRESH_BINARY_INV);
	ShowMat(dst2);
	showpic = dst2.clone();
	//imwrite("C:\\Users\\明友\\Desktop\\全部程序\\采集图片\\LoG.bmp", dst2);
}


void CDlg1::OnBnClickedButton17()
{
	// TODO: 在此添加控件通知处理程序代码
	if (if_read == 0)
	{
		MessageBoxA(NULL, "未打开图片", "提示", IDOK);
		return;
	}
	Mat src_gray, grad, dst, dst1;
	cvtColor(src, src_gray, COLOR_BGR2GRAY);
	medianBlur(src_gray, dst, 3);
	Canny(dst, dst1, 100, 40);
	dst1 = MatReverse(dst1);
	ShowMat(dst1);
	showpic = dst1.clone();
	//imwrite("C:\\Users\\明友\\Desktop\\全部程序\\采集图片\\Canny.bmp", dst1);
}


Mat CDlg1::grayju(Mat img, double T, double q)
{
	// TODO: 在此处添加实现代码.
	//Mat_<double> I;
	//img.convertTo(I, CV_64F);
	//int flag = 0;
	//int h = I.rows;
	//int v = I.cols;
	//Mat w = (Mat_<double>(7, 7) << 0, 0.00913767235, 0.021840193, 0.02567188, 0.021840193, 0.00913767235, 0,  
 //          0.00913767235, 0.02595156, 0.025984481, 0.025984481, 0.025984481, 0.02595156, 0.00913767235, 
 //          0.021840193, 0.025984481, 0.025984481, 0.025984481, 0.025984481, 0.025984481, 0.021840193, 
 //          0.02567188, 0.025984481, 0.025984481, 0.025984481, 0.025984481, 0.025984481, 0.02567188, 
 //          0.021840193, 0.025984481, 0.025984481, 0.025984481, 0.025984481, 0.025984481, 0.021840193, 
 //          0.00913767235, 0.02595156, 0.025984481, 0.025984481, 0.025984481, 0.02595156, 0.00913767235, 
 //             0, 0.00913767235, 0.021840193, 0.02567188, 0.021840193, 0.00913767235, 0);  
	//int k = 1;
	//double Pi = 3.1415926;
	//Mat_<double> I2, I3, m1, m2, m3;
	//pow(I, 2, I2);
	//pow(I, 3, I3);
	//filter2D(I, m1, CV_64F, w, Point(-1, -1));
	//filter2D(I2, m2, CV_64F, w, Point(-1, -1));
	//filter2D(I3, m3, CV_64F, w, Point(-1, -1));
	//Mat A, B;
	//sqrt(m2 - m1.dot(m1), B);
	//convertScaleAbs(B, A);
	//Mat s, p1, p2, h1, h2, P;
	//s = (m3 + 2 * m1.dot(m1.dot(m1)) - 3 * m1.dot(m2)) / A.dot(A.dot(A));
	//Mat t1, t2, t3;
	//sqrt(1 / (4 + s.dot(s)), t1);
	//p1 = 0.5*(1 + s * t1);
	//p2 = 0.5*(1 - s * t1);
	//sqrt(p2 / p1, t2);
	//sqrt(p1 / p2, t3);
	//h1 = m1 - A.dot(t2);
	//h2 = m1 - A.dot(t3);
	//min(p1, p2, P);




	return Mat();
}


void CDlg1::OnBnClickedButton19()
{
	// TODO: 在此添加控件通知处理程序代码
	if (if_read == 0)
	{
		MessageBoxA(NULL, "未打开图片", "提示", IDOK);
		return;
	}
	Mat src_gray, grad, dst, dst1, dst2, dst3, dst4;
	cvtColor(src, src_gray, COLOR_BGR2GRAY);
	medianBlur(src_gray, dst, 3);
	Canny(dst, dst1, 100, 40);
	Mat sub = ZernikeJu(dst, dst1);

}


Mat CDlg1::AtanMat(Mat img1, Mat img2)
{
	// TODO: 在此处添加实现代码.
	Mat_<double> dst;
	img1.convertTo(dst, CV_64F);
	for (int i = 0; i < img1.rows; i++)
	{
		for (int j = 0; j < img1.cols; j++)
		{
			dst.at<double>(i, j) = atan2(img1.at<double>(i, j), img2.at<double>(i, j));
		}
	}
	return dst;
}


Mat CDlg1::SinMat(Mat img)
{
	// TODO: 在此处添加实现代码.
	Mat_<double> dst;
	img.convertTo(dst, CV_64F);
	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			dst.at<double>(i, j) = sin(img.at<double>(i, j));
		}
	}
	return dst;
}


Mat CDlg1::CosMat(Mat img)
{
	// TODO: 在此处添加实现代码.
	Mat_<double> dst;
	img.convertTo(dst, CV_64F);
	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			dst.at<double>(i, j) = cos(img.at<double>(i, j));
		}
	}
	return dst;
}


double CDlg1::SumMat(Mat img)
{
	// TODO: 在此处添加实现代码.
	double sum = 0.0;
	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			sum = img.at<uchar>(i, j) + sum;
		}
	}
	return sum;
}


double CDlg1::CircleFitting(Mat img)
{
	// TODO: 在此处添加实现代码.
	int i = 0;

	double X1 = 0;
	double Y1 = 0;
	double X2 = 0;
	double Y2 = 0;
	double X3 = 0;
	double Y3 = 0;
	double X1Y1 = 0;
	double X1Y2 = 0;
	double X2Y1 = 0;

	for (i = 0; i < img.rows; i++)
	{
		double ff1 = img.at<double>(i, 1), ff2 = img.at<double>(i, 2);
		X1 = X1 + ff2;
		Y1 = Y1 + ff1;
		X2 = X2 + ff2 * ff2;
		Y2 = Y2 + ff1 * ff1;
		X3 = X3 + ff2 * ff2 * ff2;
		Y3 = Y3 + ff1 * ff1 * ff1;
		X1Y1 = X1Y1 + ff2 * ff1;
		X1Y2 = X1Y2 + ff2 * ff1 * ff1;
		X2Y1 = X2Y1 + ff2 * ff2 * ff1;
	}

	double C, D, E, G, H, N;
	double a, b, c;
	N = img.rows;
	C = N * X2 - X1 * X1;
	D = N * X1Y1 - X1 * Y1;
	E = N * X3 + N * X1Y2 - (X2 + Y2)*X1;
	G = N * Y2 - Y1 * Y1;
	H = N * X2Y1 + N * Y3 - (X2 + Y2)*Y1;
	a = (H*D - E * G) / (C*G - D * D);
	b = (H*C - E * D) / (D*D - G * C);
	c = -(a*X1 + b * Y1 + X2 + Y2) / N;

	double A, B, R;
	A = a / (-2);
	B = b / (-2);
	R = sqrt(a*a + b * b - 4 * c) / 2;
	double Radius = R;
	double pi = 3.1415926;
	double pp = sin(pi / 4);
	double tt = 0.5 / pp;
	
	Mat img1 = Mat::zeros(src.rows, src.cols, CV_8U);
	for (int i = 0; i < src.rows; i++)
	{
		for (int j = 0; j < src.cols; j++)
		{
			int distance = floor(sqrt(pow(i - A, 2) + pow(j - B, 2)) - R);
			if (distance == 0)
			{
				img1.at<uchar>(i, j) = 255;
			}
		}
	}
	img1 = MatReverse(img1);
	ShowMat(img1);
	showpic = img1.clone();
	//imwrite("C:\\Users\\明友\\Desktop\\全部程序\\采集图片\\孔拟合.bmp", img1);
	return Radius;
}


void CDlg1::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	if (if_read == 0)
	{
		MessageBoxA(NULL, "未打开图片", "提示", IDOK);
		return;
	}
	Mat src_gray, grad, dst, dst1, dst2, dst3, dst4;
	cvtColor(src, src_gray, COLOR_BGR2GRAY);
	if (src_gray.at<uchar>(src.rows / 2, src.cols / 2) < 100)
	{
		MessageBoxA(NULL, "该对象不是孔类零件", "提示", IDOK);
		return;
	}
	startTime = clock();
	medianBlur(src_gray, dst, 3);
	Canny(dst, dst1, 80, 40);
	Mat sub = ZernikeJu(dst, dst1);
	double Radius = CircleFitting(sub);
	double kong = 0.022527 * 2 * Radius + 0.2245;
	endTime = clock();
	cout << "Totle Time : " << (double)(endTime - startTime) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
	CString str;
	str.Format(_T("%lf"), kong);
	m_edit1.SetWindowText(NULL);
	m_edit2.SetWindowText(str);
}



Mat CDlg1::ZernikeJu(Mat img, Mat img1)
{
	// TODO: 在此处添加实现代码.
	Mat M11R = (Mat_<double>(7, 7) << 0, -0.015, -0.019, 0, 0.019, 0.015, 0,
		-0.0224, -0.0466, -0.0233, 0, 0.0233, 0.0466, 0.0224,
		-0.0573, -0.0466, -0.0233, 0, 0.0233, 0.0466, 0.0573,
		-0.069, -0.0466, -0.0233, 0, 0.0233, 0.0466, 0.069,
		-0.0573, -0.0466, -0.0233, 0, 0.0233, 0.0466, 0.0573,
		-0.0224, -0.0466, -0.0233, 0, 0.0233, 0.0466, 0.0224,
		0, -0.015, -0.019, 0, 0.019, 0.015, 0);
	Mat M11I = (Mat_<double>(7, 7) << 0, -0.0224, -0.0573, -0.069, -0.0573, -0.0224, 0,
		-0.015, -0.0466, -0.0466, -0.0466, -0.0466, -0.0466, -0.015,
		-0.019, -0.0233, -0.0233, -0.0233, -0.0233, -0.0233, -0.019,
		0, 0, 0, 0, 0, 0, 0,
		0.019, 0.0233, 0.0233, 0.0233, 0.0233, 0.0233, 0.019,
		0.015, 0.0466, 0.0466, 0.0466, 0.0466, 0.0466, 0.015,
		0, 0.0224, 0.0573, 0.069, 0.0573, 0.0224, 0);
	Mat M20 = (Mat_<double>(7, 7) << 0, 0.0225, 0.0394, 0.0396, 0.0394, 0.0225, 0,
		0.0225, 0.0271, -0.0128, -0.0261, -0.0128, 0.0271, 0.0225,
		0.0394, -0.0128, -0.0528, -0.0661, -0.0528, -0.0128, 0.0394,
		0.0396, -0.0261, -0.0661, -0.0794, -0.0661, -0.0261, 0.0396,
		0.0394, -0.0128, -0.0528, -0.0661, -0.0528, -0.0128, 0.0394,
		0.0225, 0.0271, -0.0128, -0.0261, -0.0128, 0.0271, 0.0225,
		0, 0.0225, 0.0394, 0.0396, 0.0394, 0.0225, 0);
	double minv = 0, maxv = 0;
	double* minp = &minv;
	double* maxp = &maxv;
	minMaxIdx(img, minp, maxp);
	Mat J = Mat::zeros(img.rows, img.cols, CV_8U);
	double lt, kt;
	lt = 0.7; kt = maxv / 3;
	Mat m11I = Mat::zeros(img.rows, img.cols, CV_64F);
	Mat m11R, m20, theta, m11C, k;
	m11R.create(img.rows, img.cols, CV_64F);
	m20.create(img.rows, img.cols, CV_64F);
	theta.create(img.rows, img.cols, CV_64F);
	m11C.create(img.rows, img.cols, CV_64F);
	k.create(img.rows, img.cols, CV_64F);
	Mat l = Mat::ones(img.rows, img.cols, CV_64F);
	Mat sub1 = Mat::zeros(img.rows*img.cols, 2, CV_64F);
	Mat i1; int v = 0;
	i1.create(img.rows, img.cols, CV_16U);
	findNonZero(img1, i1);
	double a, b, c, d, e, f, g;
	for (int i = 0; i < i1.rows; i++)
	{
		int ff1 = i1.at<int>(i, 1), ff2 = i1.at<int>(i, 0);
		if (ff1 < 3 || ff1 > img.rows - 4 || ff2 < 3 || ff2 > img.cols - 4)
			continue;
		Mat mu = (Mat_<double>(7, 7) << img.at<uchar>(ff1 - 3, ff2 - 3),
			img.at<uchar>(ff1 - 3, ff2 - 2), img.at<uchar>(ff1 - 3, ff2 - 1),
			img.at<uchar>(ff1 - 3, ff2), img.at<uchar>(ff1 - 3, ff2 + 1),
			img.at<uchar>(ff1 - 3, ff2 + 2), img.at<uchar>(ff1 - 3, ff2 + 3),

			img.at<uchar>(ff1 - 2, ff2 - 3),
			img.at<uchar>(ff1 - 2, ff2 - 2), img.at<uchar>(ff1 - 2, ff2 - 1),
			img.at<uchar>(ff1 - 2, ff2), img.at<uchar>(ff1 - 2, ff2 + 1),
			img.at<uchar>(ff1 - 2, ff2 + 2), img.at<uchar>(ff1 - 2, ff2 + 3),

			img.at<uchar>(ff1 - 1, ff2 - 3),
			img.at<uchar>(ff1 - 1, ff2 - 2), img.at<uchar>(ff1 - 1, ff2 - 1),
			img.at<uchar>(ff1 - 1, ff2), img.at<uchar>(ff1 - 1, ff2 + 1),
			img.at<uchar>(ff1 - 1, ff2 + 2), img.at<uchar>(ff1 - 1, ff2 + 3),

			img.at<uchar>(ff1, ff2 - 3),
			img.at<uchar>(ff1, ff2 - 2), img.at<uchar>(ff1, ff2 - 1),
			img.at<uchar>(ff1, ff2), img.at<uchar>(ff1, ff2 + 1),
			img.at<uchar>(ff1, ff2 + 2), img.at<uchar>(ff1, ff2 + 3),

			img.at<uchar>(ff1 + 1, ff2 - 3),
			img.at<uchar>(ff1 + 1, ff2 - 2), img.at<uchar>(ff1 + 1, ff2 - 1),
			img.at<uchar>(ff1 + 1, ff2), img.at<uchar>(ff1 + 1, ff2 + 1),
			img.at<uchar>(ff1 + 1, ff2 + 2), img.at<uchar>(ff1 + 1, ff2 + 3),

			img.at<uchar>(ff1 + 2, ff2 - 3),
			img.at<uchar>(ff1 + 2, ff2 - 2), img.at<uchar>(ff1 + 2, ff2 - 1),
			img.at<uchar>(ff1 + 2, ff2), img.at<uchar>(ff1 + 2, ff2 + 1),
			img.at<uchar>(ff1 + 2, ff2 + 2), img.at<uchar>(ff1 + 2, ff2 + 3),

			img.at<uchar>(ff1 + 3, ff2 - 3),
			img.at<uchar>(ff1 + 3, ff2 - 2), img.at<uchar>(ff1 + 3, ff2 - 1),
			img.at<uchar>(ff1 + 3, ff2), img.at<uchar>(ff1 + 3, ff2 + 1),
			img.at<uchar>(ff1 + 3, ff2 + 2), img.at<uchar>(ff1 + 3, ff2 + 3));

		m11I.at<double>(ff1, ff2) = M11I.dot(mu);
		m11R.at<double>(ff1, ff2) = M11R.dot(mu);
		m20.at<double>(ff1, ff2) = M20.dot(mu);

		a = m11I.at<double>(ff1, ff2);
		b = m11R.at<double>(ff1, ff2);
		c = m20.at<double>(ff1, ff2);
		theta.at<double>(ff1, ff2) = atan(a / b);
		d = theta.at<double>(ff1, ff2);
		m11C.at<double>(ff1, ff2) = b * cos(d) + a * sin(d);
		e = m11C.at<double>(ff1, ff2);
		l.at<double>(ff1, ff2) = c / e;
		f = l.at<double>(ff1, ff2);
		k.at<double>(ff1, ff2) = 1.5 * e / pow(1 - pow(f, 2), 1.5);
		g = k.at<double>(ff1, ff2);
		if (abs(f) < lt && abs(g) > kt)
		{
			double w1 = ff1 + 7 / 2 * f * sin(d);
			double w2 = ff2 + 7 / 2 * f * cos(d);
			J.at<uchar>(floor(w1), floor(w2)) = 255;
			sub1.at<double>(v, 0) = w1;
			sub1.at<double>(v, 1) = w2;
			v++;
		}
	}
	Mat sub = sub1.rowRange(0, v - 1).clone();

	//Mat img2, img3, img4;
	//filter2D(img, img2, CV_64F, M11I, Point(-1, -1));
	//filter2D(img, img3, CV_64F, M11R, Point(-1, -1));
	//filter2D(img, img4, CV_64F, M20, Point(-1, -1));
	//Mat theta = AtanMat(img2, img3);
	//Mat M11C = img3.mul(CosMat(theta)) + img2.mul(SinMat(theta));
	//Mat l = img4 / M11C;
	//Mat t1;
	//sqrt(1 - l.mul(l), t1);
	//Mat k = 1.5*M11C / ((1 - l.mul(l)).mul(t1));
	//Mat Idx, t2, t4, a, b, c, d;
	//convertScaleAbs(l, t2);
	//convertScaleAbs(k, t4);
	//a = t2 < lt;
	//b = t4 > kt;
	//c = a & b;
	//d = c > 0;
	//Idx.create(d.rows, d.cols, CV_16U);
	//findNonZero(d, Idx);
	//Mat sub;
	//sub.create(Idx.rows, 2, CV_64F);
	//for(int i = 0; i < Idx.rows; i++)
	//{
	//	int ff1 = Idx.at<int>(i, 1), ff2 = Idx.at<int>(i, 0);
	//  if (ff2 < 3 || ff2 > img.rows - 4 || ff1 < 3 || ff1 > img.cols - 4)
	//		continue;
	//	double w1 = ff1 + 7 / 2 * l.at<double>(ff1, ff2)*sin(theta.at<double>(ff1, ff2));
	//	double w2 = ff2 + 7 / 2 * l.at<double>(ff1, ff2)*cos(theta.at<double>(ff1, ff2));
	//	J.at<uchar>(floor(w1), floor(w2)) = 255;
	//	sub.at<double>(i, 0) = w1;
	//	sub.at<double>(i, 1) = w2;
	//}
	
	J = MatReverse(J);
	ShowMat(J);
	showpic = J.clone();
	//imwrite("C:\\Users\\明友\\Desktop\\全部程序\\采集图片\\ZernikeJu.bmp", J);
	return sub;
}


void CDlg1::OnBnClickedButton20()
{
	// TODO: 在此添加控件通知处理程序代码
	Mat img;
	img.create(400, 400, CV_8UC1);
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				for (int t = 0; t < 4; t++)
				{
					if (((k + t) % 2) == 0)
					{
						img.at<uchar>(i + k * 100, j + t * 100) = 0;
					}
					else
					{
						img.at<uchar>(i + k * 100, j + t * 100) = 255;
					}
				}
			}
		}
	}
	//imwrite("C:\\Users\\明友\\Desktop\\全部程序\\采集图片\\人为生成二值图像.bmp", img);
	Mat img1;
	Canny(img, img1, 100, 40);
	for (int i = 0; i < img1.rows; i++)
	{
		for (int j = 0; j < img1.cols; j++)
		{
			if (img1.at<uchar>(i, j) == 255)
			{
				if (i == 49)
					cout << j << endl;
			}
			if (img1.at<uchar>(i, j) == 255)
			{
				if (i == 149)
					cout << j << endl;
			}
			if (img1.at<uchar>(i, j) == 255)
			{
				if (j == 49)
					cout << i << endl;
			}
			if (img1.at<uchar>(i, j) == 255)
			{
				if (j == 49)
					cout << i << endl;
			}
		}
	}
	Mat sub = ZernikeJu(img, img1);
	for (int i = 0; i < sub.rows; i++)
	{
		if(floor(sub.at<double>(i, 0)) == 49)
		cout << setprecision(5) << setiosflags(ios::fixed) << sub.at<double>(i, 0) << ' ' << setprecision(5) << setiosflags(ios::fixed) << sub.at<double>(i, 1) << endl;
	}
	for (int i = 0; i < sub.rows; i++)
	{
		if (floor(sub.at<double>(i, 0)) == 149)
			cout << setprecision(5) << setiosflags(ios::fixed) << sub.at<double>(i, 0) << ' ' << setprecision(5) << setiosflags(ios::fixed) << sub.at<double>(i, 1) << endl;
	}
	for (int i = 0; i < sub.rows; i++)
	{
		if (floor(sub.at<double>(i, 1)) == 49)
			cout << setprecision(5) << setiosflags(ios::fixed) << sub.at<double>(i, 0) << ' ' << setprecision(5) << setiosflags(ios::fixed) << sub.at<double>(i, 1) << endl;
	}
	for (int i = 0; i < sub.rows; i++)
	{
		if (floor(sub.at<double>(i, 1)) == 149)
			cout << setprecision(5) << setiosflags(ios::fixed) << sub.at<double>(i, 0) << ' ' << setprecision(5) << setiosflags(ios::fixed) << sub.at<double>(i, 1) << endl;
	}
}


double CDlg1::LineFitting(Mat img)
{
	// TODO: 在此处添加实现代码.
	double XX1 = 0, XX2 = 0;
	double X1 = 0, X2 = 0;
	double XY1 = 0, XY2 = 0;
	double Y1 = 0, Y2 = 0;
	int v1 = 0, v2 = 0;
	for (int i = 0; i < img.rows; i++)
	{
		double ff1 = img.at<double>(i, 1), ff2 = img.at<double>(i, 0);
		if (ff2 < src.rows / 2)
		{
			XX1 += ff1 * ff1;
			X1 += ff1;
			XY1 += ff1 * ff2;
			Y1 += ff2;
			v1++;
		}
		else
		{
			XX2 += ff1 * ff1;
			X2 += ff1;
			XY2 += ff1 * ff2;
			Y2 += ff2;
			v2++;
		}
	}
	double t = v1*XX1 - X1 * X1;
	double tt = v2*XX2 - X2 * X2;
	double c0 = (XX1*Y1 - X1 * XY1) / t;
	double c1 = (v1*XY1 - X1 * Y1) / t;
	double cc0 = (XX2*Y2 - X2 * XY2) / tt;
	double cc1 = (v2*XY2 - X2 * Y2) / tt;
	double x0 = src.cols / 2;
	double y0 = c1 * x0 + c0;
	double D = abs(cc1*x0 - y0 + cc0) / sqrt(cc1*cc1 + 1);

	Mat img1 = Mat::zeros(src.rows, src.cols, CV_8U);
	for (int i = 0; i < src.rows; i++)
	{
		for (int j = 0; j < src.cols; j++)
		{
			if (i < src.rows / 2)
			{
				int distance1 = floor(i - c1 * j - c0);
				if (distance1 == 0)
					img1.at<uchar>(i, j) = 255;
			}
			else
			{
				int distance2 = floor(i - cc1 * j - cc0);
				if (distance2 == 0)
					img1.at<uchar>(i, j) = 255;
			}
		}
	}
	img1 = MatReverse(img1);
	ShowMat(img1);
	showpic = img1.clone();
	//imwrite("C:\\Users\\明友\\Desktop\\全部程序\\采集图片\\轴拟合.bmp", img1);
	return D;
}


void CDlg1::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	if (if_read == 0)
	{
		MessageBoxA(NULL, "未打开图片", "提示", IDOK);
		return;
	}
	Mat src_gray, grad, dst, dst1, dst2, dst3, dst4;
	cvtColor(src, src_gray, COLOR_BGR2GRAY);
	if (src_gray.at<uchar>(src.rows / 2, src.cols / 2) > 100)
	{
		MessageBoxA(NULL, "该对象不是轴类零件", "提示", IDOK);
		return;
	}
	startTime = clock();
	medianBlur(src_gray, dst, 3);
	Canny(dst, dst1, 70, 35);
	Mat sub = ZernikeJu(dst, dst1);
	double D = LineFitting(sub);
	double zhou = 0.022671*D + 0.1968;
	endTime = clock();
	cout << "Totle Time : " << (double)(endTime - startTime) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
	CString str;
	str.Format(_T("%lf"), zhou);
	m_edit2.SetWindowText(NULL);
	m_edit1.SetWindowText(str);
}


Mat CDlg1::MatReverse(Mat img)
{
	// TODO: 在此处添加实现代码.
	Mat dst = img < 100;
	return dst;
}


void CDlg1::OnBnClickedButton18()
{
	// TODO: 在此添加控件通知处理程序代码
	if (if_read == 0)
	{
		MessageBoxA(NULL, "未打开图片", "提示", IDOK);
		return;
	}
	Mat src_gray, grad, dst, dst1, dst2, dst3, dst4;
	cvtColor(src, src_gray, COLOR_BGR2GRAY);
	medianBlur(src_gray, dst, 3);
	if (dst.at<uchar>(dst.rows / 2, dst.cols / 2) > 50)
	{
		Canny(dst, dst1, 80, 40);
	}
	else
	{
		Canny(dst, dst1, 70, 35);
	}
	Mat sub = ZernikeJu(dst, dst1);
}


void CDlg1::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	if (if_read == 0)
	{
		MessageBoxA(NULL, "未打开图片", "提示", IDOK);
		return;
	}
	Mat src_gray, grad, dst, dst1, dst2, dst3, dst4;
	cvtColor(src, src_gray, COLOR_BGR2GRAY);
	medianBlur(src_gray, dst, 3);
	if (dst.at<uchar>(dst.rows / 2, dst.cols / 2) > 50)
	{
		Canny(dst, dst1, 80, 40);
	}
	else
	{
		Canny(dst, dst1, 70, 35);
	}
	Mat sub = ZernikeJu(dst, dst1);
}
