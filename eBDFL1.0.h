
// eBDFL1.0.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CeBDFL10App:
// �йش����ʵ�֣������ eBDFL1.0.cpp
//

class CeBDFL10App : public CWinApp
{
public:
	CeBDFL10App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CeBDFL10App theApp;