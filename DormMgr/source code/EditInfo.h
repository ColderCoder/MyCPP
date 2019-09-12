#pragma once


// EditInfo 对话框

class EditInfo : public CDialogEx
{
	DECLARE_DYNAMIC(EditInfo)

public:
	EditInfo(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~EditInfo();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INFO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString Name;
	CString Gender;
	CString Birth;
	CString Work;
	afx_msg void OnBnClickedOk();
	CComboBox JOB;
	CComboBox EDU;
	afx_msg void OnBnClickedButton1();
	CComboBox DORMTYPE;
	CString Dorm_area;
	CString dependentName;
	CString dependentGender;
	CEdit dependentBirth;
	afx_msg void OnBnClickedCancel();
	CComboBox ifFD;
	virtual BOOL OnInitDialog();
	CEdit D_Name;
	CEdit D_Gender;
	CString D_Birth;
	afx_msg void OnSeleChange();
	int teacher_num;
	int relative_num;
};
