// Random.cpp: 实现文件
//

#include "stdafx.h"
#include "Martrix.h"
#include "Random.h"
#include "afxdialogex.h"
#include <ctime>
#include "MartrixDlg.h"



// Random 对话框

IMPLEMENT_DYNAMIC(Random, CDialogEx)

Random::Random(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_RANDOM, pParent)
	, Random_m1(_T(""))
	, Random_n1(_T(""))
	, Random_m2(_T(""))
	, Random_n2(_T(""))
	, result1(_T(""))
	, result2(_T(""))
{
}

Random::~Random()
{
}

void Random::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, Random_m1);
	DDX_Text(pDX, IDC_EDIT2, Random_n1);
	DDX_Text(pDX, IDC_EDIT3, Random_m2);
	DDX_Text(pDX, IDC_EDIT4, Random_n2);
	DDX_Text(pDX, IDC_RESULT1, result1);
	DDX_Text(pDX, IDC_RESULT2, result2);
}


BEGIN_MESSAGE_MAP(Random, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &Random::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &Random::OnBnClickedOk)
END_MESSAGE_MAP()


// Random 消息处理程序


void Random::OnBnClickedCancel()
{
	CDialogEx::OnCancel();
}


void Random::OnBnClickedOk()
{
	// return randomized matrices and close current Dlg
	UpdateData(TRUE);
	CMartrixDlg* mainDlg = (CMartrixDlg*)AfxGetMainWnd();//get mainDlg's ptr
	int dataType = mainDlg->data_type;//get data type
	srand((unsigned)time(0));
	int m1 = _ttoi(Random_m1);
	int n1 = _ttoi(Random_n1);
	int m2 = _ttoi(Random_m2);
	int n2 = _ttoi(Random_n2);
	CString tmp;
	if (m1 * m2 * n1 * n2 == 0) {
		AfxMessageBox(_T("invalid size!"));
		goto do_nothing;//do not hit IDOK
	}
	switch (dataType) {
	case 0://int
		for (int i = 0; i < m1 * n1; i++) {
			tmp.Format("%d", rand());
			result1 += tmp;
			if (i + 1 != m1 * n1 && (i + 1) % n1 == 0)
				result1 += "\r\n";
			else result1 += " ";
		}

		for (int i = 0; i < m2 * n2; i++) {
			tmp.Format("%d", rand());
			result2 += tmp;
			if (i + 1 != m2 * n2 && (i + 1) % n2 == 0)
				result2 += "\r\n";
			else result2 += " ";
		}
		break;
	case 1://float
		for (int i = 0; i < m1 * n1; i++) {
			tmp.Format("%f", (float)(rand())/1000);
			result1 += tmp;
			if (i + 1 != m1 * n1 && (i + 1) % n1 == 0)
				result1 += "\r\n";
			else result1 += " ";
		}

		for (int i = 0; i < m2 * n2; i++) {
			tmp.Format("%f", (float)(rand())/1000);
			result2 += tmp;
			if ( i + 1 != m2 * n2 && (i + 1) % n2 == 0)
				result2 += "\r\n";
			else result2 += " ";
		}
		break;
	case 2://bool
		for (int i = 0; i < m1 * n1; i++) {
			tmp.Format("%d", rand()%2);
			result1 += tmp;
			if ( i + 1 != m1 * n1 && (i + 1) % n1 == 0)
				result1 += "\r\n";
			else result1 += " ";
		}

		for (int i = 0; i < m2 * n2; i++) {
			tmp.Format("%d", rand()%2);
			result2 += tmp;
			if ( i + 1 != m2 * n2 && (i + 1) % n2 == 0)
				result2 += "\r\n";
			else result2 += " ";
		}
		break;
	default:
		break;
	}
	UpdateData(FALSE);
	CDialogEx::OnOK();
do_nothing:
	m1 = m2 = n1 = n2 = 0;
	Random_m1 = Random_m2 = Random_n1 = Random_n2 = "";
	UpdateData(FALSE);
}


