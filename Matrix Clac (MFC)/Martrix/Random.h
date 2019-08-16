#pragma once


// Random 对话框

class Random : public CDialogEx
{
	DECLARE_DYNAMIC(Random);

public:
	Random(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Random();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RANDOM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	CString Random_m1;
	CString Random_n1;
	CString Random_m2;
	CString Random_n2;
	CString result1;
	CString result2;
};
