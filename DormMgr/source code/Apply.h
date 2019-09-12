#pragma once


// Apply 对话框

class Apply : public CDialogEx
{
	DECLARE_DYNAMIC(Apply)

public:
	Apply(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Apply();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_APPLY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CString appName;
	CComboBox appFor;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
	CString appList;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedCancel();
};
