#ifndef TBAR_H
#define TBAR_H

#include <stdio.h>
#include <string.h>
#include "DBOP.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <iomanip> 
#include <omp.h>
using namespace std;

class Tbar
{
private:
	double calA_DAIBAN;
	double calA_MIANBAN;
	double calA_FUBAN;
	double calA;

	double calZ_DAIBAN; //参考轴距
	double calZ_FUBAN;

	double calB_DAIBAN;
	double calB_FUBAN;
	double calB;

	double calC_DAIBAN;
	double calC_FUBAN_ZS;//自身惯性矩
	double calC_FUBAN;
	double calC;
	double calW;
	double calI;

	double FUBAN_t;
	double FUBAN_b;
	double MIANBAN_t;
	double MIANBAN_b;
	double DAIBAN_t;
	double DAIBAN_b;
	double FUBAN_t_min;
	double FUBAN_t_max;
	int FUBAN_t_num;
	double FUBAN_b_min;
	double FUBAN_b_max;
	int FUBAN_b_num;
	double MIANBAN_t_min;
	double MIANBAN_t_max;
	int MIANBAN_t_num;
	double MIANBAN_b_min;
	double MIANBAN_b_max;
	int MIANBAN_b_num;
	int count;
	WCHAR DBNAME[100];
	WCHAR TABLENAME[600];
	DBOP* DB;



public:
	Tbar();
	Tbar(double DAIBANt, double DAIBANb, double FUBANt_min, double FUBANt_max, int FUBANt_num, double FUBANb_min, double FUBANb_max, int FUBANb_num, double MIANBANt_min, double MIANBANt_max, int MIANBANt_num, double MIANBANb_min, double MIANBANb_max, int MIANBANb_num);
	int ifDBexist(DBOP DB1);
	int ifTABLEexist(DBOP DB1);
	int createDB(DBOP DB1);
	int createTABLE(DBOP DB1);
	int DelDB(DBOP DB1);
	int DelTABLE(DBOP DB1);
	int insert2DB(DBOP DB1);

	int SearchBest(DBOP DB1,double MOSHU, int num); //多少模数以上的，多少数量的备选

	~Tbar();
};

#endif