
// SOFTWARE708_2.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CSOFTWARE708_2App: 
// �йش����ʵ�֣������ SOFTWARE708_2.cpp
//

class CSOFTWARE708_2App : public CWinApp
{
public:
	CSOFTWARE708_2App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CSOFTWARE708_2App theApp;