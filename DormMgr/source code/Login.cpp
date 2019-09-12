// Login.cpp: 实现文件
//

#include "pch.h"
#include "Teacher_Dorm.h"
#include "Login.h"
#include "afxdialogex.h"
#include"PasswdReset.h"
#include<fstream>


// Login 对话框

IMPLEMENT_DYNAMIC(Login, CDialogEx)

Login::Login(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LOGIN, pParent)
	, Passwd(_T(""))
{

}

Login::~Login()
{
}

void Login::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_KEY, Passwd);
}


BEGIN_MESSAGE_MAP(Login, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &Login::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &Login::OnBnClickedOk)
END_MESSAGE_MAP()


// Login 消息处理程序



void Login::OnBnClickedButton1()
{
	//Password Reset
	std::ifstream key("key", std::ios::binary);
	if (key) {
		key.close();
		PasswdReset reset;
		reset.DoModal();
	}
	else
		MessageBox(_T("Password not set. Please input directly."));
}


void Login::OnBnClickedOk()
{
	CDialogEx::OnOK();
}
