#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include "CvvImage.h"
// MySystem.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������

// CMySystemApp: 
// �йش����ʵ�֣������ MySystem.cpp
//

class CMySystemApp : public CWinApp
{
public:
	CMySystemApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMySystemApp theApp;