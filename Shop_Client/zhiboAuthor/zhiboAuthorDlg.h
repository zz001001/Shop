
// zhiboAuthorDlg.h : 头文件
//

#pragma once


// CzhiboAuthorDlg 对话框
class CzhiboAuthorDlg : public CDialogEx
{
// 构造
public:
	CzhiboAuthorDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_ZHIBOAUTHOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	LONGLONG m_tel;
	CString m_name;
	CString m_password;
	afx_msg void OnBnClickedButton1();
};
