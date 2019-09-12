#pragma once


// PasswdReset 对话框

class PasswdReset : public CDialogEx
{
	DECLARE_DYNAMIC(PasswdReset)

public:
	PasswdReset(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~PasswdReset();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PASSWORD_RESET };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CString Current;
	CString New;
};
