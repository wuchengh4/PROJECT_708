#include "stdafx.h"
#include "Tbar.h"

Tbar::Tbar()
{
}

Tbar::Tbar(double DAIBANt, double DAIBANb, double FUBANt_min, double FUBANt_max, int FUBANt_num, double FUBANb_min, double FUBANb_max, int FUBANb_num, double MIANBANt_min, double MIANBANt_max, int MIANBANt_num, double MIANBANb_min, double MIANBANb_max, int MIANBANb_num){


	calA_DAIBAN = 0;
	calA_MIANBAN = 0;
	calA_FUBAN = 0;
	calA = 0;

	calZ_DAIBAN = 0; //参考轴距
	calZ_FUBAN = 0;

	calB_DAIBAN = 0;
	calB_FUBAN = 0;
	calB = 0;

	calC_DAIBAN = 0;
	calC_FUBAN_ZS = 0;//自身惯性矩
	calC_FUBAN = 0;
	calC = 0;
	calW = 0;
	calI = 0;

	DAIBAN_t = DAIBANt;
	DAIBAN_b = DAIBANb;
	FUBAN_t_min = FUBANt_min;
	FUBAN_t_max = FUBANt_max;
	FUBAN_t_num = FUBANt_num;
	FUBAN_b_min = FUBANb_min;
	FUBAN_b_max = FUBANb_max;
	FUBAN_b_num = FUBANb_num;
	MIANBAN_t_min = MIANBANt_min;
	MIANBAN_t_max = MIANBANt_max;
	MIANBAN_t_num = MIANBANt_num;
	MIANBAN_b_min = MIANBANb_min;
	MIANBAN_b_max = MIANBANb_max;
	MIANBAN_b_num = MIANBANb_num;

	swprintf(DBNAME, L"DB_%.0lf_%.0lf",DAIBAN_t*1000, DAIBAN_b*1000);
	swprintf(TABLENAME, L"TABLE_%.0lf_%.0lf_%d_%.0lf_%.0lf_%d_%.0lf_%.0lf_%d_%.0lf_%.0lf_%d",
		FUBAN_t_min * 1000, FUBAN_t_max * 1000, FUBAN_t_num * 1000, FUBAN_b_min * 1000, FUBAN_b_max * 1000, FUBAN_b_num * 1000,
		MIANBAN_t_min * 1000, MIANBAN_t_max * 1000, MIANBAN_t_num * 1000, MIANBAN_b_min * 1000, MIANBAN_b_max * 1000, MIANBAN_b_num * 1000);
	count = 0;
}

int  Tbar::ifDBexist(DBOP DB1){
	WCHAR sqlDBNAME[60];
	swprintf(sqlDBNAME, L"%s%s%s", L"name='", DBNAME, L"'");
	int ret = DB1.select(L"master.dbo.sysdatabases", 0, L"*",sqlDBNAME, NULL,0);
	char   fe[60];
	int ret2 = DB1.getvalues(fe);

	//SQLINTEGER   columnLen = 0;
	//SQLCHAR   fe[60];
	//RETCODE  retcode = SQLBindCol(hstmt1, 1, SQL_C_CHAR, fe, 10, &columnLen);
	//while ((retcode = SQLFetch(hstmt1)) != SQL_NO_DATA)
	//{
	//	if (columnLen > 0)
	//		return 1;
	//	else
	//		return 0;
	//}
	return ret2;
}
int Tbar::ifTABLEexist(DBOP DB1){
	WCHAR sqlTABLENAME[600];
	WCHAR sqlSYSOBJECT[600];
	swprintf(sqlSYSOBJECT, L"%s.%s.%s", DBNAME, L"dbo", L"sysObjects");
	swprintf(sqlTABLENAME, L"%s%s%s", L"name='", TABLENAME, L"'");
	
	//int suc = DB1.select(sqlSYSOBJECT, 0, "*", sqlTABLENAME, 0);
	int ret = DB1.select(sqlSYSOBJECT, 0, L"*", sqlTABLENAME, NULL,0);
	WCHAR   fe[600];
	int ret2 = DB1.getvalues(fe);
	wprintf(L"%s", fe);
	return ret2;
}
int Tbar::createDB(DBOP DB1){
	int ret = DB1.createDATABASE(DBNAME);

	return ret;
}

int Tbar::createTABLE(DBOP DB1){

	int ret = DB1.createTABLE(DBNAME, TABLENAME,
		L"FUBANt float Not Null,FUBANb float Not Null,MIANBANt float Not Null,MIANBANb float Not Null,MIANJI float Not Null,I float Not Null,MOSHU float Not Null,PRIMARY KEY (FUBANt,FUBANb,MIANBANt,MIANBANb)");
	return ret;
}
int Tbar::DelDB(DBOP DB1){
	int ret=DB1.delDATABASE(DBNAME);

	return ret;
}
int Tbar::DelTABLE(DBOP DB1){
	int ret = DB1.delTABLE(DBNAME,TABLENAME);

	return ret;
}


int Tbar::SearchBest(DBOP DB1, double MOSHU, int num){

	WCHAR sqlTABLE[600];
	WCHAR sqlcondition[600];
	swprintf(sqlTABLE, L"%s.%s.%s", DBNAME, L"dbo", TABLENAME);
	swprintf(sqlcondition, L"(%s%lf AND  MIANBANb<FUBANb and MIANBANt>FUBANt)",L"MOSHU>=", MOSHU);

	//int suc = DB1.select(sqlSYSOBJECT, 0, "*", sqlTABLENAME, 0);
	int ret = DB1.select(sqlTABLE, 0, L"*", sqlcondition, L"MIANJI",num);
	char   result_FUBANt[6000];
	char   result_FUBANb[6000];
	char   result_MIANBANt[6000];
	char   result_MIANBANb[6000];
	char   result_MIANJI[6000];
	char   result_I[6000];
	char   result_MOSHU[6000];
	int ret2 = 1;

	cout << setw(15) << "FUBANt"
		<< setw(15) << "FUBANb"
		<< setw(15) << "MIANBANt"
		<< setw(15) << "MIANBANb"
		<< setw(15) << "MIANJI"
		<< setw(15) << "I"
		<< setw(15) << "MOSHU" << endl;

	while (ret2 == 1){
		ret2= DB1.getvalues(result_FUBANt, result_FUBANb, result_MIANBANt, result_MIANBANb, result_MIANJI, result_I, result_MOSHU);
		//double   result_FUBANt_double = _ttol(result_FUBANt);
		//double   result_FUBANb_double = _ttol(result_FUBANb);
		//double   result_MIANBANt_double = _ttol(result_MIANBANt);
		//double   result_MIANBANb_double = _ttol(result_MIANBANb);
		//double   result_MIANJI_double = _ttol(result_MIANJI);
		//double   result_I_double = _ttol(result_I);
		//double   result_MOSHU_double = _ttol(result_MOSHU);
		CFile FILEOUTPUT;
		CFileException e;
		TCHAR* pszFileName = L"test.txt";
		if (!FILEOUTPUT.Open(pszFileName, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite, &e))//建立、打开txt文件
		{
			AfxMessageBox(L"File could not be opened %d\n", e.m_cause);
		}

		//FILEOUTPUT.Write(result_FUBANt, sizeof(result_FUBANt));
		//FILEOUTPUT.Write(result_FUBANb, sizeof(result_FUBANb));
		//FILEOUTPUT.Write(result_MIANBANt, sizeof(result_MIANBANt));
		//FILEOUTPUT.Write(result_MIANBANb, sizeof(result_MIANBANb));
		//FILEOUTPUT.Write(result_MIANJI, sizeof(result_MIANJI));
		//FILEOUTPUT.Write(result_I, sizeof(result_I));
		//FILEOUTPUT.Write(result_MOSHU, sizeof(result_MOSHU));

		FILEOUTPUT.Write(result_FUBANt, 15);
		FILEOUTPUT.Write(result_FUBANb, 15);
		FILEOUTPUT.Write(result_MIANBANt, 15);
		FILEOUTPUT.Write(result_MIANBANb, 15);
		FILEOUTPUT.Write(result_MIANJI,15);
		FILEOUTPUT.Write(result_I, 15);
		FILEOUTPUT.Write(result_MOSHU, 15);

		FILEOUTPUT.Close();

		//cout << setw(15) << 
		//	<< setw(15) <<  result_FUBANb_double
		//	<< setw(15) << result_MIANBANt_double
		//	<< setw(15) <<result_MIANBANb_double
		//	<< setw(15) << result_MIANJI_double
		//	<< setw(15) << result_I_double
		//	<< setw(15) <<  result_MOSHU_double << endl;
	}
	return 0;



}

int Tbar::insert2DB(DBOP DB1){

	int FUBAN_t_i;
	int num_threads;

#pragma omp parallel
	num_threads = omp_get_num_procs();
	omp_set_num_threads(num_threads);
#pragma omp parallel for private (FUBAN_t_i)


	//第一层 腹板T
	for (FUBAN_t_i = 0; FUBAN_t_i < FUBAN_t_num + 1; FUBAN_t_i++)
	{
		FUBAN_t = FUBAN_t_min + FUBAN_t_i*(FUBAN_t_max - FUBAN_t_min) / FUBAN_t_num;
		//第二层 腹板B
		for (int FUBAN_b_i = 0; FUBAN_b_i < FUBAN_b_num + 1; FUBAN_b_i++)
		{
			FUBAN_b = FUBAN_b_min + FUBAN_b_i*(FUBAN_b_max - FUBAN_b_min) / FUBAN_b_num;
			//第三层 面板T
			for (int MIANBAN_t_i = 0; MIANBAN_t_i < MIANBAN_t_num + 1; MIANBAN_t_i++)
			{
				MIANBAN_t = MIANBAN_t_min + MIANBAN_t_i*(MIANBAN_t_max - MIANBAN_t_min) / MIANBAN_t_num;

				//第四层 面板B
				for (int MIANBAN_b_i = 0; MIANBAN_b_i < MIANBAN_b_num + 1; MIANBAN_b_i++)
				{
					MIANBAN_b = MIANBAN_b_min + MIANBAN_b_i*(MIANBAN_b_max - MIANBAN_b_min) / MIANBAN_b_num;

					//计算剖面积A
					calA_DAIBAN = DAIBAN_b*DAIBAN_t;
					calA_FUBAN = FUBAN_b*FUBAN_t;
					calA_MIANBAN = MIANBAN_b*MIANBAN_t;
					calA = calA_DAIBAN + calA_FUBAN + calA_MIANBAN;

					//计算参考轴距
					calZ_DAIBAN = FUBAN_b + DAIBAN_t / 2 + MIANBAN_t / 2;
					calZ_FUBAN = MIANBAN_t / 2 + FUBAN_b / 2;

					//计算静力矩B
					calB_DAIBAN = calZ_DAIBAN*calA_DAIBAN;
					calB_FUBAN = calZ_FUBAN*calA_FUBAN;
					calB = calB_DAIBAN + calB_FUBAN;

					//计算惯性矩C
					calC_DAIBAN = calZ_DAIBAN*calB_DAIBAN;
					calC_FUBAN = calZ_FUBAN*calB_FUBAN;
					calC_FUBAN_ZS = FUBAN_t*pow(FUBAN_b, 3) / 12;
					calC = calC_DAIBAN + calC_FUBAN + calC_FUBAN_ZS;

					//计算I
					calI = calC - calB*calB/calA;
					
					//计算模数W
					calW = calC*calA / calB - calB;

					


					WCHAR OUTPUT[100];
					swprintf(OUTPUT, L"%.4lf,%.4lf,%.4lf,%.4lf,%.4lf,%.4lf,%.4lf", FUBAN_t, FUBAN_b, MIANBAN_t, MIANBAN_b, calA,calI, calW);             // 将整数转换成字符串，满足SQL语句格式

					WCHAR baseandtable[100];
					wcscpy((WCHAR *)baseandtable, L"[");
					wcscat((WCHAR *)baseandtable, DBNAME);
					wcscat((WCHAR *)baseandtable, L"].[dbo].[");
					wcscat((WCHAR *)baseandtable, TABLENAME);
					wcscat((WCHAR *)baseandtable, L"] ");

					int SUC = DB1.insert(baseandtable, L"FUBANt,FUBANb,MIANBANt,MIANBANb,MIANJI,I,MOSHU", OUTPUT);
					if (SUC != 0)
					{
						count++;

					}
				}

			}

		}

	}
	return count;



}

Tbar::~Tbar()
{
}
