
// science_calcDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "science_calc.h"
#include "science_calcDlg.h"
#include "afxdialogex.h"
# include "core.h"
#include <exception>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedMore();
	afx_msg void OnBnClickedButton2();
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_BN_CLICKED(More, &CAboutDlg::OnBnClickedMore)
	ON_BN_CLICKED(IDC_BUTTON2, &CAboutDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// Cscience_calcDlg �Ի���




Cscience_calcDlg::Cscience_calcDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cscience_calcDlg::IDD, pParent)
	, UsrInput(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cscience_calcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, UsrInput);
}

BEGIN_MESSAGE_MAP(Cscience_calcDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT1, &Cscience_calcDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(CALC, &Cscience_calcDlg::OnBnClickedCalc)
	ON_BN_CLICKED(IDC_BUTTONC, &Cscience_calcDlg::OnBnClickedButtonc)
	ON_BN_CLICKED(IDC_BUTTON1, &Cscience_calcDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON7, &Cscience_calcDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON2, &Cscience_calcDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &Cscience_calcDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &Cscience_calcDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &Cscience_calcDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &Cscience_calcDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON8, &Cscience_calcDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &Cscience_calcDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON0, &Cscience_calcDlg::OnBnClickedButton0)
	ON_BN_CLICKED(IDC_BUTTONDot, &Cscience_calcDlg::OnBnClickedButtondot)
	ON_BN_CLICKED(IDC_BUTTONLeft, &Cscience_calcDlg::OnBnClickedButtonleft)
	ON_BN_CLICKED(IDC_BUTTONRight, &Cscience_calcDlg::OnBnClickedButtonright)
	ON_BN_CLICKED(IDC_BUTTONAdd, &Cscience_calcDlg::OnBnClickedButtonadd)
	ON_BN_CLICKED(IDC_BUTTONMinus, &Cscience_calcDlg::OnBnClickedButtonminus)
	ON_BN_CLICKED(IDC_BUTTONMul, &Cscience_calcDlg::OnBnClickedButtonmul)
	ON_BN_CLICKED(IDC_BUTTONDivision, &Cscience_calcDlg::OnBnClickedButtondivision)
	ON_BN_CLICKED(IDC_BUTTONFac, &Cscience_calcDlg::OnBnClickedButtonfac)
	ON_BN_CLICKED(IDC_BUTTONPow, &Cscience_calcDlg::OnBnClickedButtonpow)
	ON_BN_CLICKED(IDC_BUTTONsin, &Cscience_calcDlg::OnBnClickedButtonsin)
	ON_BN_CLICKED(IDC_BUTTONcos, &Cscience_calcDlg::OnBnClickedButtoncos)
	ON_BN_CLICKED(IDC_BUTTONtan, &Cscience_calcDlg::OnBnClickedButtontan)
	ON_BN_CLICKED(IDC_BUTTONsqr, &Cscience_calcDlg::OnBnClickedButtonsqr)
END_MESSAGE_MAP()


// Cscience_calcDlg ��Ϣ�������

BOOL Cscience_calcDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void Cscience_calcDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void Cscience_calcDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR Cscience_calcDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Cscience_calcDlg::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void Cscience_calcDlg::OnBnClickedCalc()
//"="Button. Click to calculate and output the result.
{
		UpdateData(TRUE);
		//If no input, return 0
		if(UsrInput.GetLength()==0)
		{
			UsrInput="0";
			UpdateData(FALSE);
		}
		//convert to char*
		char *ptr; 
		ptr=UsrInput.GetBuffer(UsrInput.GetLength()); 
		UsrInput.ReleaseBuffer();
		try	//call function, return double, convert to CString
		{
		double result=calc(ptr);
		UsrInput.Format("%.6f",result);
		}
		catch(std::exception e){
			UsrInput=e.what();}
		UpdateData(FALSE);
}


void Cscience_calcDlg::OnBnClickedButtonc()
// "C"Button: Clear
{
	UpdateData(TRUE);
	UsrInput="";
	UpdateData(FALSE);
}


void Cscience_calcDlg::OnBnClickedButton1()
{
	UpdateData(TRUE);
	UsrInput+="1";
	UpdateData(FALSE);
}

void Cscience_calcDlg::OnBnClickedButton2()
{
	UpdateData(TRUE);
	UsrInput+="2";
	UpdateData(FALSE);
}

void Cscience_calcDlg::OnBnClickedButton3()
{
	UpdateData(TRUE);
	UsrInput+="3";
	UpdateData(FALSE);
}

void Cscience_calcDlg::OnBnClickedButton4()
{
	UpdateData(TRUE);
	UsrInput+="4";
	UpdateData(FALSE);
}

void Cscience_calcDlg::OnBnClickedButton5()
{
	UpdateData(TRUE);
	UsrInput+="5";
	UpdateData(FALSE);
}

void Cscience_calcDlg::OnBnClickedButton6()
{
	UpdateData(TRUE);
	UsrInput+="6";
	UpdateData(FALSE);
}

void Cscience_calcDlg::OnBnClickedButton7()
{
	UpdateData(TRUE);
	UsrInput+="7";
	UpdateData(FALSE);
}

void Cscience_calcDlg::OnBnClickedButton8()
{
	UpdateData(TRUE);
	UsrInput+="8";
	UpdateData(FALSE);
}


void Cscience_calcDlg::OnBnClickedButton9()
{
	UpdateData(TRUE);
	UsrInput+="9";
	UpdateData(FALSE);
}


void Cscience_calcDlg::OnBnClickedButton0()
{
	UpdateData(TRUE);
	UsrInput+="0";
	UpdateData(FALSE);
}


void Cscience_calcDlg::OnBnClickedButtondot()
{
	UpdateData(TRUE);
	UsrInput+=".";
	UpdateData(FALSE);
}


void Cscience_calcDlg::OnBnClickedButtonleft()
{
	UpdateData(TRUE);
	UsrInput+="(";
	UpdateData(FALSE);
}


void Cscience_calcDlg::OnBnClickedButtonright()
{
	UpdateData(TRUE);
	UsrInput+=")";
	UpdateData(FALSE);
}


void Cscience_calcDlg::OnBnClickedButtonadd()
{
	UpdateData(TRUE);
	UsrInput+="+";
	UpdateData(FALSE);
}


void Cscience_calcDlg::OnBnClickedButtonminus()
{
	UpdateData(TRUE);
	UsrInput+="-";
	UpdateData(FALSE);
}


void Cscience_calcDlg::OnBnClickedButtonmul()
{
	UpdateData(TRUE);
	UsrInput+="*";
	UpdateData(FALSE);
}


void Cscience_calcDlg::OnBnClickedButtondivision()
{
	UpdateData(TRUE);
	UsrInput+="/";
	UpdateData(FALSE);
}


void Cscience_calcDlg::OnBnClickedButtonfac()
{
	UpdateData(TRUE);
	UsrInput+="!";
	UpdateData(FALSE);
}


void Cscience_calcDlg::OnBnClickedButtonpow()
{
	UpdateData(TRUE);
	UsrInput+="^";
	UpdateData(FALSE);
}


void Cscience_calcDlg::OnBnClickedButtonsin()
{
	UpdateData(TRUE);
	UsrInput+="sin";
	UpdateData(FALSE);
}


void Cscience_calcDlg::OnBnClickedButtoncos()
{
	UpdateData(TRUE);
	UsrInput+="cos";
	UpdateData(FALSE);
}


void Cscience_calcDlg::OnBnClickedButtontan()
{
	UpdateData(TRUE);
	UsrInput+="tan";
	UpdateData(FALSE);
}

void Cscience_calcDlg::OnBnClickedButtonsqr()
{
	UpdateData(TRUE);
	UsrInput+="sqrt";
	UpdateData(FALSE);
}


void CAboutDlg::OnBnClickedMore()
{
	ShellExecute(NULL, "open", "https://github.com/ColderCoder/MyCPP/blob/master/Claculator/MFC/Readme.md", NULL, NULL, SW_SHOWNORMAL);
}


void CAboutDlg::OnBnClickedButton2()
{
	ShellExecute(NULL, "open", "https://github.com/ColderCoder", NULL, NULL, SW_SHOWNORMAL);
}


