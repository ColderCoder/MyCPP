
// Martrix.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once
# include "stdafx.h"
#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMartrixApp:
// �йش����ʵ�֣������ Martrix.cpp
//

class CMartrixApp : public CWinApp
{
public:
	CMartrixApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMartrixApp theApp;