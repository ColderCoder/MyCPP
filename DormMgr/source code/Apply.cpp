// Apply.cpp: 实现文件
//

#include "pch.h"
#include "Teacher_Dorm.h"
#include "Apply.h"
#include "afxdialogex.h"
#include<fstream>
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

/////////////////////////////////////////////////////////////
struct info {
	std::string name, job, eduExp, preDormtype,apply4;
	float jobScore, ageScore, workScore, eduScore, overall;
	int workMM, workYY;
};
std::vector<info>List;
std::vector<info>Applied;

bool descending(info a, info b) { return(a.overall > b.overall);}


// Apply 对话框

IMPLEMENT_DYNAMIC(Apply, CDialogEx)

Apply::Apply(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_APPLY, pParent)
	, appName(_T(""))
	, appList(_T(""))
{

}

Apply::~Apply()
{
}

void Apply::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, appName);
	DDX_Control(pDX, IDC_COMBO1, appFor);
	DDX_Text(pDX, IDC_EDIT2, appList);
}


BEGIN_MESSAGE_MAP(Apply, CDialogEx)
	ON_BN_CLICKED(IDOK, &Apply::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &Apply::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &Apply::OnBnClickedButton2)
	ON_BN_CLICKED(IDCANCEL, &Apply::OnBnClickedCancel)
END_MESSAGE_MAP()


// Apply 消息处理程序


void Apply::OnBnClickedOk()
{/*CDialogEx::OnOK();*/}


BOOL Apply::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	appList = "";
	//decrypt data
	std::ifstream readData("data");
	std::ofstream plain("plain", std::ios::trunc);
	char buffer;
	while (readData.get(buffer)) {
		buffer = buffer ^ 010;
		plain << buffer;
	}
	plain.close();
	readData.close();
	//get localTime
	CTime now;
	int YY, MM;//current year & month
	now= CTime::GetCurrentTime();
	YY = _ttoi(now.Format(_T("%Y")));
	MM = _ttoi(now.Format(_T("%m")));
	//time to read
	int tempYY, tempMM;
	//readData
	std::ifstream read("plain");
	info temp; 
	std::string dump;
	while (read >> temp.name) {
		read >> dump;
		//dump gender
		read >> tempMM>>tempYY;//read birth date
		temp.ageScore = ((YY - tempYY) * 12 + MM - tempMM) * 0.0083;
		//read work date
		std::string tmp1, tmp2;
		read >> tmp1 >> tmp2;
		temp.workMM = std::stoi(tmp1); 
		temp.workYY = std::stoi(tmp2);
		temp.workScore = ((YY - temp.workYY) * 12 + MM - temp.workMM) * 0.0416;
		int jobtitle; read >> tmp1; jobtitle=std::stoi(tmp1); //read job title
		switch (jobtitle) {
		case 0:
			temp.jobScore = 20;
			temp.job = "Professor";
			break;
		case 1:
			temp.jobScore = 16;
			temp.job = "Associate Professor";
			break;
		case 2:
			temp.jobScore = 12;
			temp.job = "Lecturer";
			break;
		case 3:
			temp.jobScore = 8;
			temp.job = "Teaching Assistant";
			break;
		default:
			temp.jobScore = 0;
			temp.job = "N/A";
			break;
		}
		int edu; read >> tmp1; edu=std::stoi(tmp1);//read education condition
		switch(edu) {
		case 0:
			temp.eduScore = 20;
			temp.eduExp = "Doctor";
			break;
		case 1:
			temp.eduScore = 16;
			temp.eduExp = "Master";
			break;
		case 2:
			temp.eduScore = 12;
			temp.eduExp = "Bachelor";
			break;
		case 3:
			temp.eduScore = 8;
			temp.eduExp = "Others";
			break;
		default:
			temp.eduScore = 0;
			temp.eduExp = "N/A";
			break;
		}
		int original; read >> tmp1; original = std::stoi(tmp1);//previous Dorm type
		switch (original) {
		case 0:
			temp.preDormtype = "Collective";
			break;
		case 1:
			temp.preDormtype = "1bdr";
			break;
		case 2:
			temp.preDormtype = "1bdr & lr";
			break;
		case 3:
			temp.preDormtype = "2bdr";
			break;
		case 4:
			temp.preDormtype = "2bdr & lr";
			break;
		case 5:
			temp.preDormtype = "3bdr";
			break;
		case 6:
			temp.preDormtype = "3bdr & lr";
			break;
		default:
			break;
		}
		temp.overall = temp.eduScore + temp.jobScore + temp.workScore + temp.ageScore;
		while (read.peek() != '\n')read.get(); read.get();//dump useless infos
		List.push_back(temp);
	}
	read.close();


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void Apply::OnBnClickedButton1()//ADD
{
	UpdateData(TRUE);
	std::string name = CT2A(appName.GetBuffer());
	//check if selected apply type
	if (appFor.GetCurSel() == -1) {
		MessageBox(_T("Please choose what to apply for."));
	}
	else {
		//search by the name
		int i = 0;
		for (; i < List.size(); i++) {
			if (name == List[i].name) break;
		}
		if (i == List.size()) {//not found
			appName = "";
			MessageBox(_T("specified name not exists!"));
		}
		else {//name found
			name = name + " - " + List[i].job + " - " + List[i].eduExp + " -work since: " + std::to_string(List[i].workYY) + "." + std::to_string(List[i].workMM) + " -original: " + List[i].preDormtype + " -Apply for: ";
			CString addNew(name.c_str());
			switch (appFor.GetCurSel()) {
			case 1:
				addNew += "Collective";
				List[i].apply4 = "Collective";
				break;
			case 2:
				addNew += "1bdr";
				List[i].apply4 = "1bdr";
				break;
			case 3:
				addNew += "1bdr & lr";
				List[i].apply4 = "1bdr & lr";
				break;
			case 4:
				addNew += "2bdr";
				List[i].apply4 = "2bdr";
				break;
			case 5:
				addNew += "2bdr & lr";
				List[i].apply4 = "2bdr & lr";
				break;
			case 6:
				addNew += "3bdr";
				List[i].apply4 = "3bdr";
				break;
			case 7:
				addNew += "3bdr & lr";
				List[i].apply4 = "3bdr & lr";
				break;
			default:
				break;
			}
			std::string score=" -Score: "+std::to_string(List[i].overall)+" ("+std::to_string(List[i].jobScore) +" job score + "+ std::to_string(List[i].workScore)+" work score + " + std::to_string(List[i].eduScore)+" edu score)";
			CString Score(score.c_str());
			appList = appList + addNew + Score+_T("\r\n");
			Applied.push_back(List[i]);
		}
		UpdateData(FALSE);
	}
	
}



void Apply::OnBnClickedButton2()//Sort
{
	appList = "";//clear
	std::sort(Applied.begin(), Applied.end(), descending);//do sort
	for (int i = 0; i < Applied.size(); i++) {
		std::string temp= Applied[i].name + " - " + Applied[i].job + " - " + Applied[i].eduExp + " -work since: " + std::to_string(Applied[i].workYY) + "." + std::to_string(Applied[i].workMM) + " -original: " + Applied[i].preDormtype + " -Apply for: "+Applied[i].apply4+ " -Score: " + std::to_string(Applied[i].overall) + " (" + std::to_string(Applied[i].jobScore) + " job score + " + std::to_string(Applied[i].workScore) + " work score + " + std::to_string(Applied[i].eduScore) + " edu score)";
		CString addNew(temp.c_str());
		appList = appList + addNew + _T("\r\n");
	}
	UpdateData(FALSE);
}


void Apply::OnBnClickedCancel()
{
	//delete plain data
	CFile R;
	R.Remove(_T("plain"));
	CDialogEx::OnCancel();
}
