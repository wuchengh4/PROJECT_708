
// SOFTWARE708_2Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CSOFTWARE708_2Dlg �Ի���
class CSOFTWARE708_2Dlg : public CDialogEx
{
// ����
public:
	CSOFTWARE708_2Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SOFTWARE708_2_DIALOG };

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
	// W�����
	afx_msg void OnEnChangeW();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnStnClickedStaticW();
	afx_msg void OnStnClickedStaticW3();
	CEdit* C_INPUT_W;
	CEdit* C_INPUT_DAIBAN_t;
	CEdit* C_INPUT_DAIBAN_b;
	CEdit* C_INPUT_FUBAN_t_min;
	CEdit* C_INPUT_FUBAN_t_max;
	CEdit* C_INPUT_FUBAN_t_num;
	CEdit* C_INPUT_FUBAN_b_min;
	CEdit* C_INPUT_FUBAN_b_max;
	CEdit* C_INPUT_FUBAN_b_num;
	CEdit* C_INPUT_MIANBAN_t_min;
	CEdit* C_INPUT_MIANBAN_t_max;
	CEdit* C_INPUT_MIANBAN_t_num;
	CEdit* C_INPUT_MIANBAN_b_min;
	CEdit* C_INPUT_MIANBAN_b_max;
	CEdit* C_INPUT_MIANBAN_b_num;
	CEdit* C_INPUT_SEARCH_NUM;

};
