
// zhiboAuthorDlg.h : ͷ�ļ�
//

#pragma once


// CzhiboAuthorDlg �Ի���
class CzhiboAuthorDlg : public CDialogEx
{
// ����
public:
	CzhiboAuthorDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_ZHIBOAUTHOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
