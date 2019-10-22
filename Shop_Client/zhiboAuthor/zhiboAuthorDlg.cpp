
// zhiboAuthorDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MyAes.h"
#include "zhiboAuthor.h"
#include "zhiboAuthorDlg.h"
#include "afxdialogex.h"
#include"packdef.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CzhiboAuthorDlg �Ի���



CzhiboAuthorDlg::CzhiboAuthorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CzhiboAuthorDlg::IDD, pParent)
	, m_tel(1577)
	, m_name(_T("zz001"))
	, m_password(_T("123456"))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CzhiboAuthorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_tel);
	DDX_Text(pDX, IDC_EDIT2, m_name);
	DDX_Text(pDX, IDC_EDIT3, m_password);
}

BEGIN_MESSAGE_MAP(CzhiboAuthorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CzhiboAuthorDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CzhiboAuthorDlg ��Ϣ�������

BOOL CzhiboAuthorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CzhiboAuthorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CzhiboAuthorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CzhiboAuthorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//ע��
void CzhiboAuthorDlg::OnBnClickedButton1()
{
	UpdateData();
	if(m_tel<0 ||m_tel>99999999999)
	{
		MessageBox(_T("��������ȷ���ֻ�����"));
		return;
	}
	int nlen=m_password.GetLength();
	if(nlen<6||nlen>16)
	{
		MessageBox(_T("������6-16λ�ַ�"));
		return;
	}

	STRU_REGISTER_RQ srr;
	srr.m_nType = _DEF_PROTOCOL_REGISTER_RQ;
	srr.m_brole= user_purchaser;
	srr.m_userid=m_tel;
	//memcpy(srr.m_szName,m_name,sizeof(srr.m_szName));
	//memcpy(srr.m_szPassWord,m_password,sizeof(srr.m_szPassWord));
	WideCharToMultiByte(CP_ACP,0,m_name,-1,srr.m_szName,sizeof(srr.m_szName),0,0);
	WideCharToMultiByte(CP_ACP,0,m_password,-1,srr.m_szPassWord,sizeof(srr.m_szPassWord),0,0);

	//�������
	//MyAes e;
	//Mybyte key[16] = {0x2b, 0x7e, 0x15, 0x16,   
	//				0x28, 0xae, 0xd2, 0xa6,   
	//				0xab, 0xf7, 0x15, 0x88,   
	//				0x09, 0xcf, 0x4f, 0x3c};  
	//Mybyte plain[16] ;
	//int nSize = sizeof(plain);
	//for(int i = 0;i <16;i++)
	//{
	//	plain[i] = srr.m_szPassWord[i];

	//}
	//

	//word w[4*(Nr+1)];  
	//e.KeyExpansion(key, w);  

	//// ���ܣ��������  
	//e.encrypt(plain, w); 
	//memcpy(srr.m_szPassWord,plain,sizeof(plain));
	char *str = "abab";
	if(!theApp.m_pKernel->SendData((char *)&srr,sizeof(srr)))
	{
		MessageBox(_T("ע��ʧ��"));
	}
	int len = sizeof(srr);
	
}
