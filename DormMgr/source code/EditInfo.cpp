// EditInfo.cpp: 实现文件
//

#include "pch.h"
#include "Teacher_Dorm.h"
#include "EditInfo.h"
#include "afxdialogex.h"
#include<fstream>
#include<string>



// EditInfo 对话框

IMPLEMENT_DYNAMIC(EditInfo, CDialogEx)

EditInfo::EditInfo(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_INFO, pParent)
	, Name(_T(""))
	, Gender(_T(""))
	, Birth(_T(""))
	, Work(_T(""))
	, Dorm_area(_T(""))
	, dependentName(_T(""))
	, dependentGender(_T(""))
	, D_Birth(_T(""))
{

}

BOOL EditInfo::OnInitDialog() {
	//init dialog
	CDialogEx::OnInitDialog();
	//disable family dependent (default)
	ifFD.SetCurSel(0);
	D_Name.EnableWindow(FALSE);
	D_Gender.EnableWindow(FALSE);
	dependentBirth.EnableWindow(FALSE);
	//decrypt data
	char tmp;
	std::ofstream outPlain("plain", std::ios::trunc);
	std::ifstream readData("data");
	while (readData.get(tmp)) {
		tmp = tmp ^ 010;
		outPlain << tmp;
	}
	readData.close(); outPlain.close();	

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


EditInfo::~EditInfo()
{
}

void EditInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, Name);
	DDX_Text(pDX, IDC_EDIT2, Gender);
	DDX_Text(pDX, IDC_EDIT3, Birth);
	DDX_Text(pDX, IDC_EDIT4, Work);
	DDX_Control(pDX, IDC_COMBO1, JOB);
	DDX_Control(pDX, IDC_COMBO2, EDU);

	DDX_Control(pDX, IDC_COMBO4, DORMTYPE);
	DDX_Text(pDX, IDC_EDIT8, Dorm_area);
	DDX_Text(pDX, IDC_EDIT5, dependentName);
	DDX_Text(pDX, IDC_EDIT6, dependentGender);
	DDX_Control(pDX, IDC_EDIT7, dependentBirth);
	DDX_Control(pDX, IDC_COMBO3, ifFD);
	DDX_Control(pDX, IDC_EDIT5, D_Name);
	DDX_Control(pDX, IDC_EDIT6, D_Gender);
	DDX_Text(pDX, IDC_EDIT7, D_Birth);


}


BEGIN_MESSAGE_MAP(EditInfo, CDialogEx)
	ON_BN_CLICKED(IDOK, &EditInfo::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &EditInfo::OnBnClickedButton1)
	ON_BN_CLICKED(IDCANCEL, &EditInfo::OnBnClickedCancel)
	ON_CBN_SELCHANGE(IDC_COMBO3, &EditInfo::OnSeleChange)
END_MESSAGE_MAP()


// EditInfo 消息处理程序


void EditInfo::OnBnClickedOk()
{/*CDialogEx::OnOK();*/}


void EditInfo::OnBnClickedButton1()//Add
{
	UpdateData(TRUE);
	std::ofstream outInfo(_T("plain"),std::ios::app);
	if (!outInfo) {
		MessageBox(_T("Critical Error! Exit and Try Again!"));
		CDialogEx::OnCancel();
	}
	std::string tmp;
	//validate input
	if (Name == "" || Gender == "" || Birth == "" || Work == "" || Dorm_area == "" || JOB.GetCurSel() == -1 || EDU.GetCurSel() == -1 || DORMTYPE.GetCurSel() == -1) {
		MessageBox(_T("Not a complete info record. Please check if you input everything."));
	}
	else {
		//read statics
		std::ifstream getinfo("info.txt");
		getinfo >> teacher_num;
		getinfo >> relative_num;
		getinfo.close();
		teacher_num++;
		//adding a record
		tmp = CT2A(Name.GetBuffer());
		outInfo << tmp << " ";
		tmp = CT2A(Gender.GetBuffer());
		outInfo << tmp << " ";
		tmp = CT2A(Birth.GetBuffer());
		outInfo << tmp << " ";
		tmp = CT2A(Work.GetBuffer());
		outInfo << tmp << " ";
		tmp = std::to_string(JOB.GetCurSel());
		outInfo << tmp << " ";
		tmp = std::to_string(EDU.GetCurSel());
		outInfo << tmp << " ";
		tmp = std::to_string(DORMTYPE.GetCurSel());
		outInfo << tmp << " ";
		tmp = CT2A(Dorm_area.GetBuffer());
		outInfo << tmp << " ";
		if (ifFD.GetCurSel()) {
			relative_num++;
			outInfo << "1 ";
			tmp = CT2A(dependentName.GetBuffer());
			outInfo << tmp << " ";
			tmp = CT2A(dependentGender.GetBuffer());
			outInfo << tmp << " ";
			tmp = CT2A(D_Birth.GetBuffer());
			outInfo << tmp << std::endl;
		}
		else {
			outInfo << "0" << std::endl;
		}
		//success, re-init input
		Name = Gender = Birth = Work = Dorm_area = D_Birth = dependentGender = dependentName = "";
		JOB.SetCurSel(-1); EDU.SetCurSel(-1);
		DORMTYPE.SetCurSel(-1); ifFD.SetCurSel(-1);
		MessageBox(_T("Successfully added."));
		//update statistics
		std::ofstream updateInfo("info.txt", std::ios::trunc);
		updateInfo << teacher_num << " " << relative_num;
		updateInfo.close();
	}
	//Done
	outInfo.close();
	UpdateData(FALSE);
}


void EditInfo::OnBnClickedCancel()
{
	//encrypt plain data
	char buffer;
	std::ifstream readPlain("plain");
	std::ofstream data("data", std::ios::trunc);
	while (readPlain.get(buffer)) {
		buffer = 010 ^ buffer;
		data << buffer;
	}
	readPlain.close();
	data.close();
	//delete plain data
	CFile R;
	R.Remove(_T("plain"));

	CDialogEx::OnCancel();
}





void EditInfo::OnSeleChange()
//change if has family dependent
//enable/disable family denpendent info input
{
	if (!ifFD.GetCurSel()) {
		D_Name.EnableWindow(FALSE);
		D_Gender.EnableWindow(FALSE);
		dependentBirth.EnableWindow(FALSE);
	}
	else {
		D_Name.EnableWindow(TRUE);
		D_Gender.EnableWindow(TRUE);
		dependentBirth.EnableWindow(TRUE);
	}
}
