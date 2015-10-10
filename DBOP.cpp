#include "stdafx.h"
#include "DBOP.h"
DBOP::DBOP(){
	SQLHENV henv = SQL_NULL_HENV;
    SQLHDBC hdbc = SQL_NULL_HDBC;
    SQLHSTMT hstmt = SQL_NULL_HSTMT;
	flags=false;
}
int DBOP::open(WCHAR *DSN,WCHAR *UID,WCHAR *AuthStr){
	retcode = SQLAllocHandle (SQL_HANDLE_ENV, NULL, &henv);
	retcode = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION,(SQLPOINTER)SQL_OV_ODBC3,SQL_IS_INTEGER);
	retcode = SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);
	//WCHAR* WDSN = new WCHAR[2*sizeof(DSN[0])];
	//WCHAR* WUID = new WCHAR[2*sizeof(UID[0]) ];
	//WCHAR* WAUTHSTR = new WCHAR[sizeof(AuthStr[0]) + 1];

	//MultiByteToWideChar(CP_ACP, 0, DSN, strlen(DSN) + 1, WDSN, sizeof(WDSN[0]));
	//MultiByteToWideChar(CP_ACP, 0, UID, strlen(UID) + 1, WUID, sizeof(WUID[0]));
	//MultiByteToWideChar(CP_ACP, 0, AuthStr, strlen(AuthStr) + 1, WAUTHSTR, sizeof(WAUTHSTR[0]));

	retcode = SQLConnect(hdbc, (SQLWCHAR*)DSN, wcslen((SQLWCHAR*)DSN), (SQLWCHAR*)UID, wcslen((SQLWCHAR*)UID), (SQLWCHAR*)AuthStr, wcslen((SQLWCHAR*)AuthStr));
	if ( (retcode != SQL_SUCCESS) && (retcode != SQL_SUCCESS_WITH_INFO) ) {
		SQLDisconnect(hdbc);
        SQLFreeHandle(SQL_HANDLE_DBC, hdbc);
        SQLFreeHandle(SQL_HANDLE_ENV, henv);
		return 0;
	}
	retcode = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
	if((retcode != SQL_SUCCESS) && (retcode != SQL_SUCCESS_WITH_INFO)){
		return 0;
	}
	return 1;
}
//distinct=DISTINCT：结果无重复，cond=NULL：无条件设置，order=NULL 不排序,num=0 全部列出
int DBOP::select(WCHAR *table, int distinct, WCHAR *col, WCHAR *cond, WCHAR *order, int num){
    SQLCloseCursor (hstmt);
	wcscpy((WCHAR *)sql, L"select ");
	if(distinct==1){
		wcscat((WCHAR *)sql, L"distinct ");
	}
	if (num >0){
		wcscat((WCHAR *)sql, L"TOP ");
		WCHAR numbers[60];
		swprintf(numbers, L"%d ", num);

		wcscat((WCHAR *)sql, numbers);
	}

	wcscat((WCHAR *)sql, col);
	wcscat((WCHAR *)sql, L" from ");
	wcscat((WCHAR *)sql, table);
	if(cond!=NULL){
		wcscat((WCHAR *)sql, L" where ");
		wcscat((WCHAR *)sql, cond);
	}
	if(order!=NULL){
		wcscat((WCHAR *)sql, L" order by ");
		wcscat((WCHAR *)sql, order);
	}
	retcode = SQLExecDirect(hstmt, sql, wcslen((WCHAR*)sql));
	if((retcode != SQL_SUCCESS) && (retcode != SQL_SUCCESS_WITH_INFO)){
		return 0;
	}
	flags=true;
	return 1;
}

int DBOP::insert(WCHAR *table, WCHAR *value){
	SQLCloseCursor (hstmt);
	wcscpy((WCHAR *)sql, L"insert into ");
	wcscat((WCHAR *)sql,table);
	wcscat((WCHAR *)sql,L" values(");
	wcscat((WCHAR *)sql,value);
	wcscat((WCHAR *)sql,L")");
	

    retcode=SQLExecDirect (hstmt,sql,wcslen((WCHAR*)sql));
	if((retcode != SQL_SUCCESS) && (retcode != SQL_SUCCESS_WITH_INFO)){
		return 0;
	}
	return 1;
}
int DBOP::insert(WCHAR* table,WCHAR* col,WCHAR* value){

	SQLCloseCursor (hstmt);
	wcscpy((WCHAR *)sql,L"insert into ");
	wcscat((WCHAR *)sql,table);
	wcscat((WCHAR *)sql,L" (");
	wcscat((WCHAR *)sql,col);
	wcscat((WCHAR *)sql,L")");
	wcscat((WCHAR *)sql,L" values(");
	wcscat((WCHAR *)sql,value);
	wcscat((WCHAR *)sql,L")");
    retcode=SQLExecDirect (hstmt,sql,wcslen((const WCHAR*)sql));
	if((retcode != SQL_SUCCESS) && (retcode != SQL_SUCCESS_WITH_INFO)){
		return 0;
	}
	return 1;
}
int DBOP::update(WCHAR* table,WCHAR* set,WCHAR* cond){
	SQLCloseCursor (hstmt);
	wcscpy((WCHAR *)sql,L"update ");
	wcscat((WCHAR *)sql,table);
	wcscat((WCHAR *)sql,L" set ");
	wcscat((WCHAR *)sql,set);
	wcscat((WCHAR *)sql,L" where ");
	wcscat((WCHAR *)sql,cond);
	retcode=SQLExecDirect (hstmt,sql,wcslen((const WCHAR*)sql));
	if((retcode != SQL_SUCCESS) && (retcode != SQL_SUCCESS_WITH_INFO)){
		return 0;
	}
	return 1;
}
int DBOP::createDATABASE(WCHAR* DB){
	SQLCloseCursor(hstmt);
	wcscpy((WCHAR *)sql, L"CREATE DATABASE ");
	wcscat((WCHAR *)sql, DB);
	retcode = SQLExecDirect(hstmt, sql, wcslen((const WCHAR*)sql));
	if ((retcode != SQL_SUCCESS) && (retcode != SQL_SUCCESS_WITH_INFO)){
		return 0;
	}
	return 1;

}
int DBOP::createTABLE(WCHAR* DB,WCHAR* table,WCHAR* cons){//cons 创建条件
	SQLCloseCursor(hstmt);
	wcscpy((WCHAR *)sql, L"CREATE TABLE [");
	wcscat((WCHAR *)sql, DB);
	wcscat((WCHAR *)sql, L"].[dbo].[");
	wcscat((WCHAR *)sql, table);
	wcscat((WCHAR *)sql, L"] (");
	wcscat((WCHAR *)sql, cons);
	wcscat((WCHAR *)sql, L")");
	retcode = SQLExecDirect(hstmt, sql, wcslen((const WCHAR*)sql));
	if ((retcode != SQL_SUCCESS) && (retcode != SQL_SUCCESS_WITH_INFO)){
		return 0;
	}
	return 1;
}
int DBOP::delDATABASE(WCHAR* DB){
	SQLCloseCursor(hstmt);
	wcscpy((WCHAR *)sql, L"DROP DATABASE [");
	wcscat((WCHAR *)sql, DB);
	wcscat((WCHAR *)sql, L"]");
	retcode = SQLExecDirect(hstmt, sql, wcslen((const WCHAR*)sql));
	if ((retcode != SQL_SUCCESS) && (retcode != SQL_SUCCESS_WITH_INFO)){
		return 0;
	}
	return 1;
}
int DBOP::delTABLE(WCHAR* DB,WCHAR* table){
	SQLCloseCursor(hstmt);
	wcscpy((WCHAR *)sql, L"DROP TABLE [");
	wcscat((WCHAR *)sql, DB);
	wcscat((WCHAR *)sql, L"].[dbo].[");
	wcscat((WCHAR *)sql, table);
	wcscat((WCHAR *)sql, L"]");
	retcode = SQLExecDirect(hstmt, sql, wcslen((const WCHAR*)sql));
	if ((retcode != SQL_SUCCESS) && (retcode != SQL_SUCCESS_WITH_INFO)){
		return 0;
	}
	return 1;
}
//if cond=NULL,delete all
int DBOP::_delete(WCHAR* table,WCHAR* cond){
	SQLCloseCursor (hstmt);
	wcscpy((WCHAR *)sql,L"delete from ");
    wcscat((WCHAR *)sql,table);
	if(cond!=NULL){
		wcscat((WCHAR *)sql,L" where ");
		wcscat((WCHAR *)sql,cond);
	}
	retcode=SQLExecDirect (hstmt,sql,wcslen((const WCHAR*)sql));
	if((retcode != SQL_SUCCESS) && (retcode != SQL_SUCCESS_WITH_INFO)){
		return 0;
	}
	return 1;
}
int DBOP::close(){
	SQLCloseCursor (hstmt);
	SQLFreeHandle (SQL_HANDLE_STMT, hstmt);
	SQLDisconnect(hdbc);
    SQLFreeHandle(SQL_HANDLE_DBC, hdbc);
    SQLFreeHandle(SQL_HANDLE_ENV, henv);
	return 1;
}
int DBOP::getsql(WCHAR *sql){
	SQLCloseCursor (hstmt);

//	WCHAR* WSQL = new WCHAR[sizeof(sql[0]) + 1];

//	MultiByteToWideChar(CP_ACP, 0, sql, wcslen(*sql) + 1, WSQL, sizeof(sql[0]));

	retcode = SQLExecDirect(hstmt, (SQLWCHAR*)sql, SQL_NTS);
	if((retcode != SQL_SUCCESS) && (retcode != SQL_SUCCESS_WITH_INFO)){
		return 0;
	}
	if(sql[0]=='s'||sql[0]=='S'){ 
		flags=true;
	}
	return 1;
}
int DBOP::gettype(int var){
	return 4;
}
int DBOP::gettype(char* var){
	return 1;
}
int DBOP::gettype(WCHAR* var){
	return 1;
}
int DBOP::gettype(bigint var){
	//or return -25;
	return SQL_C_SBIGINT;
}
int DBOP::gettype(money var){
	return 8;
}