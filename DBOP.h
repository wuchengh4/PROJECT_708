#ifndef DBOP_H
#define DBOP_H
#pragma once
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <sql.h>

#include <sqltypes.h>
#include <odbcss.h>
#pragma comment(lib, "odbc32.lib")
#include <sqlext.h>


#define DISTINCT 1

//��ʱ֧�ֵ���������
#define money double
#define bigint __int64  //output"%lld"
#define nchar char
#define varchar char
#define date char //array length=11
/*
ʧ�ܷ���0���ɹ�����1
�����ַ�������������''
ʹ�÷�������������DBOP var=DBOP();
          var.open(DSN,UID,AuthStr);
		  var.***();���ù�����䣬����var.getsql(sql),��ֱ����������sql���ִ��
		  �����һ��ʹ��var.select()��var.getsql(sql)��sql��select����
		  ѭ������var.getvalues(**)���ܣ�������Ҫ�������������ǰ����߸�
*/
class DBOP{
private:
	SQLHENV henv;
    SQLHDBC hdbc;
    SQLHSTMT hstmt;
	RETCODE retcode;
	WCHAR sql[300];
	bool flags;
	int gettype(int var);
	int gettype(char* var);
	int gettype(WCHAR* var);
	int gettype(bigint var);
	int gettype(money var);
public:
	DBOP();
	//DSN ODBC����Դ����UID�û�����AuthStr��֤��
	int open(WCHAR* DSN,WCHAR* UID,WCHAR* AuthStr);
	//table������distinct=DISTINCT��������ظ���col��ȡ���У�cond=NULL�����������ã�order=NULL ������
	int select(WCHAR* table, int distinct, WCHAR* col, WCHAR* cond, WCHAR* order = NULL, int num = 0);
	int insert(WCHAR* table,WCHAR* col,WCHAR* value);
	int insert(WCHAR* table,WCHAR* value);
	int update(WCHAR* table,WCHAR* set,WCHAR* cond);
	int delDATABASE(WCHAR* DB);
	int delTABLE(WCHAR* DB,WCHAR* table);
	int createDATABASE(WCHAR* DB);
	int createTABLE(WCHAR* DB, WCHAR* table, WCHAR* cons);
	//if cond=NULL,delete all
	int _delete(WCHAR* table,WCHAR* cond=NULL);
	int getsql(WCHAR* sql);
	//T��֧��ָ���������֧�����飬֧���ַ���������0��������������ȫ����ȡ
	template <class T1>
	int getvalues(T1& value1);
	template <class T1,class T2>
	int getvalues(T1& value1,T2& value2);
	template <class T1,class T2,class T3>
	int getvalues(T1& value1,T2& value2,T3& value3);
	template <class T1,class T2,class T3,class T4>
	int getvalues(T1& value1,T2& value2,T3& value3,T4& value4);
	template <class T1,class T2,class T3,class T4,class T5>
	int getvalues(T1& value1,T2& value2,T3& value3,T4& value4,T5& value5);
	template <class T1,class T2,class T3,class T4,class T5,class T6>
	int getvalues(T1& value1,T2& value2,T3& value3,T4& value4,T5& value5,T6& value6);
	template <class T1,class T2,class T3,class T4,class T5,class T6,class T7>
	int getvalues(T1& value1,T2& value2,T3& value3,T4& value4,T5& value5,T6& value6,T7& value7);
	int close();
};
template <class T1>
int DBOP::getvalues(T1& value1){
	int len;
	if(flags){
		len=gettype(value1);
		SQLBindCol(hstmt, 1, len, &value1, sizeof(value1), 0);
		flags=false;
	}
	retcode=SQLFetch(hstmt); 
	if(retcode!=SQL_SUCCESS&&retcode!=SQL_SUCCESS_WITH_INFO){
		return 0;
	}
	return 1;
}
template <class T1,class T2>
int DBOP::getvalues(T1& value1,T2& value2){
	int len;
	if(flags){
		len=gettype(value1);
		SQLBindCol(hstmt, 1, len, &value1, sizeof(value1), 0);
		len=gettype(value2);
		SQLBindCol(hstmt, 2, len, &value2, sizeof(value2), 0);
		flags=false;
	}
	retcode=SQLFetch(hstmt); 
	if(retcode!=SQL_SUCCESS&&retcode!=SQL_SUCCESS_WITH_INFO){
		return 0;
	}
	return 1;
}
template <class T1,class T2,class T3>
int DBOP::getvalues(T1& value1,T2& value2,T3& value3){
	int len;
	if(flags){
		len=gettype(value1);
		SQLBindCol(hstmt, 1, len, &value1, sizeof(value1), 0);
		len=gettype(value2);
		SQLBindCol(hstmt, 2, len, &value2, sizeof(value2), 0);
		len=gettype(value3);
		SQLBindCol(hstmt, 3, len, &value3, sizeof(value3), 0);
		flags=false;
	}
	retcode=SQLFetch(hstmt); 
	if(retcode!=SQL_SUCCESS&&retcode!=SQL_SUCCESS_WITH_INFO){
		return 0;
	}
	return 1;
}
template <class T1,class T2,class T3,class T4>
int DBOP::getvalues(T1& value1,T2& value2,T3& value3,T4& value4){
	int len;
	if(flags){
		len=gettype(value1);
		SQLBindCol(hstmt, 1, len, &value1, sizeof(value1), 0);
		len=gettype(value2);
		SQLBindCol(hstmt, 2, len, &value2, sizeof(value2), 0);
		len=gettype(value3);
		SQLBindCol(hstmt, 3, len, &value3, sizeof(value3), 0);
		len=gettype(value4);
		SQLBindCol(hstmt, 4, len, &value4, sizeof(value4), 0);
		flags=false;
	}
	retcode=SQLFetch(hstmt); 
	if(retcode!=SQL_SUCCESS&&retcode!=SQL_SUCCESS_WITH_INFO){
		return 0;
	}
	return 1;
}
template <class T1,class T2,class T3,class T4,class T5>
int DBOP::getvalues(T1& value1,T2& value2,T3& value3,T4& value4,T5& value5){
	int len;
	if(flags){
		len=gettype(value1);
		SQLBindCol(hstmt, 1, len, &value1, sizeof(value1), 0);
		len=gettype(value2);
		SQLBindCol(hstmt, 2, len, &value2, sizeof(value2), 0);
		len=gettype(value3);
		SQLBindCol(hstmt, 3, len, &value3, sizeof(value3), 0);
		len=gettype(value4);
		SQLBindCol(hstmt, 4, len, &value4, sizeof(value4), 0);
		len=gettype(value5);
		SQLBindCol(hstmt, 5, len, &value5, sizeof(value5), 0);
		flags=false;
	}
	retcode=SQLFetch(hstmt); 
	if(retcode!=SQL_SUCCESS&&retcode!=SQL_SUCCESS_WITH_INFO){
		return 0;
	}
	return 1;
}
template <class T1,class T2,class T3,class T4,class T5,class T6>
int DBOP::getvalues(T1& value1,T2& value2,T3& value3,T4& value4,T5& value5,T6& value6){
	int len;
	if(flags){
		len=gettype(value1);
		SQLBindCol(hstmt, 1, len, &value1, sizeof(value1), 0);
		len=gettype(value2);
		SQLBindCol(hstmt, 2, len, &value2, sizeof(value2), 0);
		len=gettype(value3);
		SQLBindCol(hstmt, 3, len, &value3, sizeof(value3), 0);
		len=gettype(value4);
		SQLBindCol(hstmt, 4, len, &value4, sizeof(value4), 0);
		len=gettype(value5);
		SQLBindCol(hstmt, 5, len, &value5, sizeof(value5), 0);
		len=gettype(value6);
		SQLBindCol(hstmt, 6, len, &value6, sizeof(value6), 0);
		flags=false;
	}
	retcode=SQLFetch(hstmt); 
	if(retcode!=SQL_SUCCESS&&retcode!=SQL_SUCCESS_WITH_INFO){
		return 0;
	}
	return 1;
}
template <class T1,class T2,class T3,class T4,class T5,class T6,class T7>
int DBOP::getvalues(T1& value1,T2& value2,T3& value3,T4& value4,T5& value5,T6& value6,T7& value7){
	int len;
	if(flags){
		len=gettype(value1);
		SQLBindCol(hstmt, 1, len, &value1, sizeof(value1), 0);
		len=gettype(value2);
		SQLBindCol(hstmt, 2, len, &value2, sizeof(value2), 0);
		len=gettype(value3);
		SQLBindCol(hstmt, 3, len, &value3, sizeof(value3), 0);
		len=gettype(value4);
		SQLBindCol(hstmt, 4, len, &value4, sizeof(value4), 0);
		len=gettype(value5);
		SQLBindCol(hstmt, 5, len, &value5, sizeof(value5), 0);
		len=gettype(value6);
		SQLBindCol(hstmt, 6, len, &value6, sizeof(value6), 0);
		len=gettype(value7);
		SQLBindCol(hstmt, 7, len, &value7, sizeof(value7), 0);
		flags=false;
	}
	retcode=SQLFetch(hstmt); 
	if(retcode!=SQL_SUCCESS&&retcode!=SQL_SUCCESS_WITH_INFO){
		return 0;
	}
	return 1;
}
#endif // EXPRESSIV_CONTROL_H