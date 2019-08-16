
// MartrixDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Martrix.h"
#include "MartrixDlg.h"
#include "afxdialogex.h"

#include "Random.h"

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
public:
	afx_msg void OnBnClickedButton1();
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CAboutDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CMartrixDlg 对话框




CMartrixDlg::CMartrixDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMartrixDlg::IDD, pParent)
	, input1(_T(""))
	, input2(_T(""))
	, data_type(0)
	, output(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMartrixDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, input1);
	DDX_Text(pDX, IDC_EDIT3, input2);
	DDX_Radio(pDX, IDC_RADIO1, data_type);
	DDX_Text(pDX, IDC_EDIT2, output);
}

BEGIN_MESSAGE_MAP(CMartrixDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMartrixDlg::OnBnClickedOk)

	ON_BN_CLICKED(IDC_BUTTON5, &CMartrixDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CMartrixDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON1, &CMartrixDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMartrixDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMartrixDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMartrixDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON7, &CMartrixDlg::OnBnClickedButton7)
END_MESSAGE_MAP()


// CMartrixDlg 消息处理程序

BOOL CMartrixDlg::OnInitDialog()
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

void CMartrixDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMartrixDlg::OnPaint()
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
HCURSOR CMartrixDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMartrixDlg::OnBnClickedOk()
{
	//CDialogEx::OnOK();
}





void CMartrixDlg::OnBnClickedButton5()
{
	//Transpose
	UpdateData(TRUE);
	try {
		output = matrix_API(input1.GetBuffer(), input2.GetBuffer(), data_type, 5).c_str();
	}
	catch (std::exception e) { output = e.what(); }
	input2 = "In transpose mode, \r\nwhat you input in this box will be ignored.";
	UpdateData(FALSE);
}

void CMartrixDlg::OnBnClickedButton6()
{
	//clear
	input1=input2=output="";
	UpdateData(FALSE);
}

void CMartrixDlg::OnBnClickedButton1()
{
	//add
	UpdateData(TRUE);
	try {
		output = matrix_API(input1.GetBuffer(), input2.GetBuffer(), data_type , 1).c_str();
	}
	catch (std::exception e) { output= e.what(); }
	UpdateData(FALSE);
}

void CMartrixDlg::OnBnClickedButton2()
{
	//minus
	UpdateData(TRUE);
	try {
		output = matrix_API(input1.GetBuffer(), input2.GetBuffer(), data_type, 2).c_str();
	}
	catch (std::exception e) { output = e.what(); }
	UpdateData(FALSE);
}

void CMartrixDlg::OnBnClickedButton3()
{
	//multiply 
	UpdateData(TRUE);
	try {
		output = matrix_API(input1.GetBuffer(), input2.GetBuffer(), data_type, 3).c_str();
	}
	catch (std::exception e) { output = e.what(); }
	UpdateData(FALSE);
}

void CMartrixDlg::OnBnClickedButton4()
{
	//num-multiply
	UpdateData(TRUE);
	try {
		output = matrix_API(input1.GetBuffer(), input2.GetBuffer(), data_type, 4).c_str();
	}
	catch (std::exception e) { output = e.what(); }
	UpdateData(FALSE);
}

void CMartrixDlg::OnBnClickedButton7()
{
	//random matrices generate
	UpdateData(TRUE);
	Random r;
	if (IDOK == r.DoModal()) {
		input1 = r.result1;
		input2 = r.result2;
		output = "";
	}
	UpdateData(FALSE);
}


void CAboutDlg::OnBnClickedButton1()
{
	ShellExecute(0, NULL, _T("https://github.com/ColderCoder/MyCPP/tree/master/Matrix%20Clac%20(MFC)"), NULL, NULL, SW_NORMAL);
}
