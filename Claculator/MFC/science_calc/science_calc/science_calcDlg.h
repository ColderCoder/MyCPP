
// science_calcDlg.h : ͷ�ļ�
//

#pragma once


// Cscience_calcDlg �Ի���
class Cscience_calcDlg : public CDialogEx
{
// ����
public:
	Cscience_calcDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SCIENCE_CALC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
	CString UsrInput;
	afx_msg void OnBnClickedCalc();
	afx_msg void OnBnClickedButtonc();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton0();
	afx_msg void OnBnClickedButtondot();
	afx_msg void OnBnClickedButtonleft();
	afx_msg void OnBnClickedButtonright();
	afx_msg void OnBnClickedButtonadd();
	afx_msg void OnBnClickedButtonminus();
	afx_msg void OnBnClickedButtonmul();
	afx_msg void OnBnClickedButtondivision();
	afx_msg void OnBnClickedButtonfac();
	afx_msg void OnBnClickedButtonpow();
	afx_msg void OnBnClickedButtonsin();
	afx_msg void OnBnClickedButtoncos();
	afx_msg void OnBnClickedButtontan();
	afx_msg void OnBnClickedButtonsqr();
};
