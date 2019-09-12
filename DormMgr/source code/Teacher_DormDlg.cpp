
// Teacher_DormDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "Teacher_Dorm.h"
#include "Teacher_DormDlg.h"
#include "afxdialogex.h"
#include <fstream>
#include"Login.h"
#include"EditInfo.h"
#include"Apply.h"
#include<string>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()



// CTeacherDormDlg 对话框



CTeacherDormDlg::CTeacherDormDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TEACHER_DORM_DIALOG, pParent)
	, Relatives_num(_T(""))
	, Teacher_num(_T(""))
	/*, App_num(_T(""))*/
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTeacherDormDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_RELATIVE, Relatives_num);
	DDX_Text(pDX, IDC_TEACHER, Teacher_num);
	/*DDX_Text(pDX, IDC_APPLICATION, App_num);*/
}

BEGIN_MESSAGE_MAP(CTeacherDormDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CTeacherDormDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON2, &CTeacherDormDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_APPLY, &CTeacherDormDlg::OnBnClickedApply)
END_MESSAGE_MAP()


// CTeacherDormDlg 消息处理程序

BOOL CTeacherDormDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	/////////////////////////////////
	int teacher_num = 0, relative_num = 0;
	Teacher_num = "";
	Relatives_num = "";
	std::fstream getinfo("info.txt");
	if (!getinfo) {
		getinfo << "0 0";
	}
	getinfo >> teacher_num;
	getinfo >> relative_num;
	if (teacher_num == 0) {
		Teacher_num = "N/A";
		Relatives_num = "N/A";
		MessageBox(_T("No info added, please click \"Edit Info\" to start"));
	}
	else
	{
		Teacher_num.Format(_T("%d"), teacher_num);
		Relatives_num.Format(_T("%d"), relative_num);
	}
	getinfo.close();
	UpdateData(FALSE);
	// end

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTeacherDormDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTeacherDormDlg::OnPaint()
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
HCURSOR CTeacherDormDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CTeacherDormDlg::OnBnClickedOk()
{
	// DO NOTHINGG
	//CDialogEx::OnOK();
}




//////////////////////////////////////////
void CTeacherDormDlg::OnBnClickedButton2()
{	//Edit Info
	//Password Authentication
	std::ifstream key("key", std::ios::binary);
	if (!key) {//password not set
		MessageBox(_T("Password not set. Please input a password."));
		key.close();
		Login l;
		if (IDOK == l.DoModal()) {
			//initialize password file
			CString passwd = l.Passwd;
			std::ofstream key("key", std::ios::binary);
			std::string outkey(CT2A(passwd.GetBuffer()));
			for (int i = 0; i < outkey.length(); i++) {
				outkey[i] += 21;
			}
			key << outkey; key.close();
			MessageBox(_T("Password has successfully set."));
			//initialize data
			std::ofstream data("data", std::ios::trunc);//encrypted
			std::ofstream plain("plain", std::ios::trunc);//decrypted
			data.close(); plain.close();
			//open infoDlg
			EditInfo infoDlg;
			infoDlg.DoModal();
		}
	}
	else {//password already set
		Login l;
		if (IDOK == l.DoModal()) {
			//verify password
			CString input = l.Passwd;
			std::string passwdString;
			CString passwd;
			key >> passwdString; key.close();
			for (int i = 0; i < passwdString.length(); i++) {
				passwdString[i] -= 21;
			}
			passwd = passwdString.c_str();
			if (passwd == input) {//Verified
				MessageBox(_T("Login success."));
				//check if data exists
				std::ifstream readData("data");
				if (!readData) {
					MessageBox(_T("Seems that data is lost. Initializing..."));
					std::ofstream data("data", std::ios::trunc);//encrypted
					std::ofstream plain("plain", std::ios::trunc);//decrypted
					data.close(); plain.close();
				}
				else {
					//decrypt data
					std::ofstream plain("plain", std::ios::trunc);
					char buffer;
					while (readData.get(buffer)) {
						buffer = buffer ^ 010;
						plain << buffer;
					}
					plain.close();
				}
				readData.close();
				//open Dlg
				EditInfo infoDlg;
				infoDlg.DoModal();
			}
			else {//Forbidden
				MessageBox(_T("Wrong password. Access denied."));
			}
		}
	}
	int teacher_num = 0, relative_num = 0;
	Teacher_num = "";
	Relatives_num = "";
	std::fstream getinfo("info.txt");
	if (!getinfo) {
		getinfo << "0 0";
	}
	getinfo >> teacher_num;
	getinfo >> relative_num;
	if (teacher_num == 0) {
		Teacher_num = "N/A";
		Relatives_num = "N/A";
		MessageBox(_T("No info added, please click \"Edit Info\" to start"));
	}
	else
	{
		Teacher_num.Format(_T("%d"), teacher_num);
		Relatives_num.Format(_T("%d"), relative_num);
	}
	getinfo.close();
	UpdateData(FALSE);
}


void CTeacherDormDlg::OnBnClickedApply()//APPLY
{
	//decrypt data
	std::ifstream readData("data");
	if (!readData) {
		MessageBox(_T("No data found. Please initialize first."));
	}
	else {
		std::ofstream plain("plain", std::ios::trunc);
		char buffer;
		while (readData.get(buffer)) {
			buffer = buffer ^ 010;
			plain << buffer;
		}
		plain.close();
		readData.close();
		//open Dlg
		Apply application;
		application.DoModal();

	}

}
