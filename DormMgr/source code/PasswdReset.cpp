// PasswdReset.cpp: 实现文件
//

#include "pch.h"
#include "Teacher_Dorm.h"
#include "PasswdReset.h"
#include "afxdialogex.h"
#include<fstream>

// PasswdReset 对话框

IMPLEMENT_DYNAMIC(PasswdReset, CDialogEx)

PasswdReset::PasswdReset(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PASSWORD_RESET, pParent)
	, Current(_T(""))
	, New(_T(""))
{

}

PasswdReset::~PasswdReset()
{
}

void PasswdReset::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, Current);
	DDX_Text(pDX, IDC_EDIT2, New);
}


BEGIN_MESSAGE_MAP(PasswdReset, CDialogEx)
	ON_BN_CLICKED(IDOK, &PasswdReset::OnBnClickedOk)
END_MESSAGE_MAP()


// PasswdReset 消息处理程序


void PasswdReset::OnBnClickedOk()
//OK to reset password
{
	UpdateData(TRUE);
	std::ifstream key("key", std::ios::binary);
	CString currentPasswd;
	std::string tmp;
	key >> tmp; key.close();
	for (int i = 0; i < tmp.length(); i++) {
		tmp[i]-=21;
	}
	currentPasswd = tmp.c_str();
	if (currentPasswd == Current) {
		std::ofstream key("key", std::ios::binary|std::ios::trunc);
		std::string outkey(CT2A(New.GetBuffer()));
		for (int i = 0; i < outkey.length(); i++) {
			outkey[i]+=21;
		}
		key << outkey;
		MessageBox(_T("Successfully modified the password."));
		CDialogEx::OnOK();
	}
	else {
		MessageBox(_T("Password not match. Please try again."));
		Current = New = "";
		UpdateData(FALSE);
	}
}
