
// science_calc.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Cscience_calcApp:
// �йش����ʵ�֣������ science_calc.cpp
//

class Cscience_calcApp : public CWinApp
{
public:
	Cscience_calcApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Cscience_calcApp theApp;