
// zhiboAuthorDlg.cpp : 实现文件
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


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CzhiboAuthorDlg 对话框



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


// CzhiboAuthorDlg 消息处理程序

BOOL CzhiboAuthorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CzhiboAuthorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CzhiboAuthorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//注册
void CzhiboAuthorDlg::OnBnClickedButton1()
{
	UpdateData();
	if(m_tel<0 ||m_tel>99999999999)
	{
		MessageBox(_T("请输入正确的手机号码"));
		return;
	}
	int nlen=m_password.GetLength();
	if(nlen<6||nlen>16)
	{
		MessageBox(_T("请输入6-16位字符"));
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

	//密码加密
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

	//// 加密，输出密文  
	//e.encrypt(plain, w); 
	//memcpy(srr.m_szPassWord,plain,sizeof(plain));
	char *str = "abab";
	if(!theApp.m_pKernel->SendData((char *)&srr,sizeof(srr)))
	{
		MessageBox(_T("注册失败"));
	}
	int len = sizeof(srr);
	
}
