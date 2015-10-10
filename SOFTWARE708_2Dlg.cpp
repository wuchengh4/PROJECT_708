
// SOFTWARE708_2Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SOFTWARE708_2.h"
#include "SOFTWARE708_2Dlg.h"
#include "afxdialogex.h"
#include "DBOP.h"
#include "Tbar.h"

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
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSOFTWARE708_2Dlg �Ի���



CSOFTWARE708_2Dlg::CSOFTWARE708_2Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSOFTWARE708_2Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSOFTWARE708_2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

}

BEGIN_MESSAGE_MAP(CSOFTWARE708_2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(INPUT_W, &CSOFTWARE708_2Dlg::OnEnChangeW)
	ON_BN_CLICKED(IDOK, &CSOFTWARE708_2Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CSOFTWARE708_2Dlg::OnBnClickedButton1)

END_MESSAGE_MAP()


// CSOFTWARE708_2Dlg ��Ϣ�������

BOOL CSOFTWARE708_2Dlg::OnInitDialog()
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������


	C_INPUT_W = (CEdit*)GetDlgItem(INPUT_W);
	C_INPUT_DAIBAN_t = (CEdit*)GetDlgItem(INPUT_DAIBAN_t);
	C_INPUT_DAIBAN_b = (CEdit*)GetDlgItem(INPUT_DAIBAN_b);
	C_INPUT_FUBAN_t_min = (CEdit*)GetDlgItem(INPUT_FUBAN_t_min);
	C_INPUT_FUBAN_t_max = (CEdit*)GetDlgItem(INPUT_FUBAN_t_max);
	C_INPUT_FUBAN_t_num = (CEdit*)GetDlgItem(INPUT_FUBAN_t_num);
	C_INPUT_FUBAN_b_min = (CEdit*)GetDlgItem(INPUT_FUBAN_b_min);
	C_INPUT_FUBAN_b_max = (CEdit*)GetDlgItem(INPUT_FUBAN_b_max);
	C_INPUT_FUBAN_b_num = (CEdit*)GetDlgItem(INPUT_FUBAN_b_num);
	C_INPUT_MIANBAN_t_min = (CEdit*)GetDlgItem(INPUT_MIANBAN_t_min);
	C_INPUT_MIANBAN_t_max = (CEdit*)GetDlgItem(INPUT_MIANBAN_t_max);
	C_INPUT_MIANBAN_t_num = (CEdit*)GetDlgItem(INPUT_MIANBAN_t_num);
	C_INPUT_MIANBAN_b_min = (CEdit*)GetDlgItem(INPUT_MIANBAN_b_min);
	C_INPUT_MIANBAN_b_max = (CEdit*)GetDlgItem(INPUT_MIANBAN_b_max);
	C_INPUT_MIANBAN_b_num = (CEdit*)GetDlgItem(INPUT_MIANBAN_b_num);
	C_INPUT_SEARCH_NUM = (CEdit*)GetDlgItem(INPUT_SEARCH_NUM);

	//��ֵ  

	//pBoxOne-> SetWindowText( _T("FOO ") );  

	//��ʼ�������
	C_INPUT_W->SetWindowText(_T("1000"));
	C_INPUT_DAIBAN_t->SetWindowText(_T("1.5"));
	C_INPUT_DAIBAN_b->SetWindowText(_T("300"));
	
	C_INPUT_FUBAN_t_min->SetWindowText(_T("0.6"));
	C_INPUT_FUBAN_t_max->SetWindowText(_T("2"));
	C_INPUT_FUBAN_t_num->SetWindowText(_T("20"));

	C_INPUT_FUBAN_b_min->SetWindowText(_T("20"));
	C_INPUT_FUBAN_b_max->SetWindowText(_T("250"));
	C_INPUT_FUBAN_b_num->SetWindowText(_T("50"));

	C_INPUT_MIANBAN_t_min->SetWindowText(_T("0.6"));
	C_INPUT_MIANBAN_t_max->SetWindowText(_T("2.4"));
	C_INPUT_MIANBAN_t_num->SetWindowText(_T("20"));

	C_INPUT_MIANBAN_b_min->SetWindowText(_T("5"));
	C_INPUT_MIANBAN_b_max->SetWindowText(_T("50"));
	C_INPUT_MIANBAN_b_num->SetWindowText(_T("20"));

	C_INPUT_SEARCH_NUM->SetWindowText(_T("10"));
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CSOFTWARE708_2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CSOFTWARE708_2Dlg::OnPaint()
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
HCURSOR CSOFTWARE708_2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSOFTWARE708_2Dlg::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CSOFTWARE708_2Dlg::OnEnChangeW()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CSOFTWARE708_2Dlg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	
	
	
	CDialogEx::OnOK();
}


void CSOFTWARE708_2Dlg::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������


		CString str;

		C_INPUT_W->GetWindowText(str);
		double MOSHU_REQUIRED = _ttol(str);
	
		C_INPUT_DAIBAN_t->GetWindowText(str);
		double DAIBAN_t = _ttol(str);
		C_INPUT_DAIBAN_b->GetWindowText(str);
		double DAIBAN_b = _ttol(str);


		C_INPUT_FUBAN_t_min->GetWindowText(str);
		double FUBAN_t_min = _ttol(str);

		C_INPUT_FUBAN_t_max->GetWindowText(str);
		double FUBAN_t_max = _ttol(str);

		C_INPUT_FUBAN_t_num->GetWindowText(str);
		int FUBAN_t_num = _ttoi(str);


		C_INPUT_FUBAN_b_min->GetWindowText(str);
		double FUBAN_b_min = _ttol(str);

		C_INPUT_FUBAN_b_max->GetWindowText(str);
		double FUBAN_b_max = _ttol(str);

		C_INPUT_FUBAN_b_num->GetWindowText(str);
		int FUBAN_b_num = _ttoi(str);


		C_INPUT_MIANBAN_t_min->GetWindowText(str);
		double MIANBAN_t_min = _ttol(str);

		C_INPUT_MIANBAN_t_max->GetWindowText(str);
		double MIANBAN_t_max = _ttol(str);

		C_INPUT_MIANBAN_t_num->GetWindowText(str);
		int MIANBAN_t_num = _ttoi(str);


		C_INPUT_MIANBAN_b_min->GetWindowText(str);
		double MIANBAN_b_min = _ttol(str);

		C_INPUT_MIANBAN_b_max->GetWindowText(str);
		double MIANBAN_b_max = _ttol(str);

		C_INPUT_MIANBAN_b_num->GetWindowText(str);
		int MIANBAN_b_num = _ttoi(str);


		C_INPUT_SEARCH_NUM->GetWindowText(str);

		int search_num = _ttoi(str);


		//��λCM
	//��ʼ��ֵ
		double FUBAN_t = FUBAN_t_min;
		double FUBAN_b = FUBAN_b_min;
		double MIANBAN_t = MIANBAN_t_min;
		double MIANBAN_b = MIANBAN_b_min;
		

		int COUNT = 0; //����

	//����ʼ
		DBOP DB1 = DBOP();
		int cl = DB1.close();
		int i = DB1.open(L"MSSQLSERVER", L"sa", L"sa");
		if (i == 1){
			GetDlgItem(IDC_DB_STATUS)->SetWindowText(_T("���ݿ⣺�ɹ�����"));
			//Tbar TB1(DAIBAN_t, DAIBAN_b, FUBAN_t_min, FUBAN_t_max, FUBAN_t_num, FUBAN_b_min, FUBAN_b_max, FUBAN_b_num, MIANBAN_t_min, MIANBAN_t_max, MIANBAN_t_num, MIANBAN_b_min, MIANBAN_b_max, MIANBAN_b_num);
			//GetDlgItem(IDC_ALL_STATUS)->SetWindowText(_T("����������"));

			//int suc = TB1.ifDBexist(DB1);
			//if (suc != 0){
			//	GetDlgItem(IDC_ALL_STATUS)->SetWindowText(_T("���ݿ��Ѿ�����"));
			//}
			//else{
			//	GetDlgItem(IDC_ALL_STATUS)->SetWindowText(_T("���ݿⲻ����"));
			//	suc = TB1.createDB(DB1);
			//	if (suc != 0){
			//		GetDlgItem(IDC_ALL_STATUS)->SetWindowText(_T("���ݿⴴ���ɹ�"));
			//	}
			//	else{
			//		GetDlgItem(IDC_ALL_STATUS)->SetWindowText(_T("���ݿⴴ��ʧ��"));
			//	}
			//}

			cout<<"Inserting..."<<endl;
			Tbar TB1(DAIBAN_t, DAIBAN_b, FUBAN_t_min, FUBAN_t_max, FUBAN_t_num, FUBAN_b_min, FUBAN_b_max, FUBAN_b_num, MIANBAN_t_min, MIANBAN_t_max, MIANBAN_t_num, MIANBAN_b_min, MIANBAN_b_max, MIANBAN_b_num);



			int suc = TB1.ifDBexist(DB1);
			if (suc != 0){
				cout << "���ݿ��Ѿ�����" << endl;
			}
			else{
				cout << "���ݿⲻ����" << endl;
				suc = TB1.createDB(DB1);
				if (suc != 0){
					cout << "���ݿ�ɹ�����" << endl;
				}
				else{
					cout << "���ݿⴴ��ʧ��" << endl;
				}
			}

			//	suc = TB1.DelDB(DB1);
			suc = TB1.ifTABLEexist(DB1);
			if (suc != 0){
				cout << "���Ѿ�����" << endl;
			}
			else{
				cout << "������" << endl;
				suc = TB1.createTABLE(DB1);
				if (suc != 0){
					cout << "��ɹ�����" << endl;
					time_t begin;
					time(&begin);

					COUNT = TB1.insert2DB(DB1);

					time_t end;
					time(&end);
					if ((end - begin) != 0)
					{
						printf("Inserted %d records in %lld seconds, average insert speed: %lld\n", COUNT, end - begin, COUNT / (end - begin));
					}
					else
					{
						printf("Inserted %d records in %lld seconds", COUNT, end - begin);

					}
				}
				else{
					cout << "����ʧ��" << endl;
				}
			}



			//printf("Insert %d records in %lld seconds\n", COUNT, end - begin);  



			time_t begin2;
			time(&begin2);


			COUNT = TB1.SearchBest(DB1, MOSHU_REQUIRED, search_num);


			time_t end2;
			time(&end2);

			printf("Searched in %lld seconds", end2 - begin2);




			cl = DB1.close();


		}
		else{
			GetDlgItem(IDC_DB_STATUS)->SetWindowText(_T("���ݿ⣺����ʧ��"));
			GetDlgItem(IDC_ALL_STATUS)->SetWindowText(_T("���棺����"));

		}






	//	MessageBox(str, _T("�������н��"), MB_OK);
str.ReleaseBuffer();

}

