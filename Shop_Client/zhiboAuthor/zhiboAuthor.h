
// zhiboAuthor.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include"IKernel.h"


// CzhiboAuthorApp:
// �йش����ʵ�֣������ zhiboAuthor.cpp
//

class CzhiboAuthorApp : public CWinApp
{
public:
	CzhiboAuthorApp();

// ��д
public:
	virtual BOOL InitInstance();
public:
	IKernel * m_pKernel;

// ʵ��

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CzhiboAuthorApp theApp;