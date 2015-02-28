#include"sql.h"
#include"sqlext.h"
#include"myheader.h"



int update_db(char *name,int roll,char *branch,char *mobno)
{
	SQLHENV p;
        SQLHDBC q;
        SQLHSTMT r;

        SQLAllocHandle(SQL_HANDLE_ENV,0,&p);
        SQLSetEnvAttr(p,SQL_ATTR_ODBC_VERSION,SQL_OV_ODBC3,0);
        SQLAllocHandle(SQL_HANDLE_DBC,p,&q);
        SQLAllocHandle(SQL_HANDLE_STMT,q,&r);

        SQLConnect(q,"college",strlen("college"),"root",strlen("root"),"",strlen(""));

        char x[]="use college";
        char y[]="update student_info set name=?,branch=?,mobno=? where roll=?;";


	

	SQLPrepare(r,x,strlen(x));
	SQLExecute(r);
 

	SQLPrepare(r,y,strlen(y));
	SQLBindParameter(r,1,SQL_PARAM_INPUT,SQL_CHAR,SQL_C_CHAR,50,0,name,strlen(name),0);	
	SQLBindParameter(r,2,SQL_PARAM_INPUT,SQL_CHAR,SQL_C_CHAR,50,0,branch,strlen(branch),0);	
	SQLBindParameter(r,3,SQL_PARAM_INPUT,SQL_CHAR,SQL_C_CHAR,50,0,mobno,strlen(mobno),0);	
	SQLBindParameter(r,4,SQL_PARAM_INPUT,SQL_INTEGER,SQL_C_SLONG,4,0,&roll,sizeof(roll),0);	
	SQLExecute(r);
	SQLTransact(p,q,SQL_COMMIT);


	SQLFreeHandle(SQL_HANDLE_STMT,r);
        SQLDisconnect(q);
        SQLFreeHandle(SQL_HANDLE_DBC,q);
        SQLFreeHandle(SQL_HANDLE_ENV,p);


}

int insert_db(char *name,int roll,char *branch,char *mobno)
{

	printf("MEWDATA--------\n");


	printf("-- %s  %d  %s  %s\n",name,roll,branch,mobno);

	SQLHENV p;
        SQLHDBC q;
        SQLHSTMT r;

        SQLAllocHandle(SQL_HANDLE_ENV,0,&p);
        SQLSetEnvAttr(p,SQL_ATTR_ODBC_VERSION,SQL_OV_ODBC3,0);
        SQLAllocHandle(SQL_HANDLE_DBC,p,&q);
        SQLAllocHandle(SQL_HANDLE_STMT,q,&r);

        SQLConnect(q,"college",strlen("college"),"root",strlen("root"),"",strlen(""));

        char x[]="use college";
        char y[]="insert into student_info values(?,?,?,?);";


	

	SQLPrepare(r,x,strlen(x));
	SQLExecute(r);
 

	SQLPrepare(r,y,strlen(y));
	SQLBindParameter(r,1,SQL_PARAM_INPUT,SQL_CHAR,SQL_C_CHAR,50,0,name,strlen(name),0);	
	SQLBindParameter(r,2,SQL_PARAM_INPUT,SQL_INTEGER,SQL_C_SLONG,4,0,&roll,sizeof(roll),0);	
	SQLBindParameter(r,3,SQL_PARAM_INPUT,SQL_CHAR,SQL_C_CHAR,50,0,branch,strlen(branch),0);	
	SQLBindParameter(r,4,SQL_PARAM_INPUT,SQL_CHAR,SQL_C_CHAR,50,0,mobno,strlen(mobno),0);	
	SQLExecute(r);
	SQLTransact(p,q,SQL_COMMIT);



	SQLFreeHandle(SQL_HANDLE_STMT,r);
        SQLDisconnect(q);
        SQLFreeHandle(SQL_HANDLE_DBC,q);
        SQLFreeHandle(SQL_HANDLE_ENV,p);




}

int delete_db(int index)
{
	SQLHENV p;
        SQLHDBC q;
        SQLHSTMT r;

        SQLAllocHandle(SQL_HANDLE_ENV,0,&p);
        SQLSetEnvAttr(p,SQL_ATTR_ODBC_VERSION,SQL_OV_ODBC3,0);
        SQLAllocHandle(SQL_HANDLE_DBC,p,&q);
        SQLAllocHandle(SQL_HANDLE_STMT,q,&r);

        SQLConnect(q,"college",strlen("college"),"root",strlen("root"),"",strlen(""));

        char x[]="use college";
        char y[]="delete from student_info where roll=?";
	
	SQLPrepare(r,x,strlen(x));
	SQLExecute(r);

	SQLPrepare(r,y,strlen(y));
	SQLBindParameter(r,1,SQL_PARAM_INPUT,SQL_INTEGER,SQL_C_SLONG,4,0,&index,sizeof(index),0);	
	SQLExecute(r);
	
	SQLFreeHandle(SQL_HANDLE_STMT,r);
        SQLDisconnect(q);
        SQLFreeHandle(SQL_HANDLE_DBC,q);
        SQLFreeHandle(SQL_HANDLE_ENV,p);

}


retrive_db_insert_tree()
{
	struct yyy d;

	SQLHENV p;
        SQLHDBC q;
        SQLHSTMT r;

        SQLAllocHandle(SQL_HANDLE_ENV,0,&p);
        SQLSetEnvAttr(p,SQL_ATTR_ODBC_VERSION,SQL_OV_ODBC3,0);
        SQLAllocHandle(SQL_HANDLE_DBC,p,&q);
        SQLAllocHandle(SQL_HANDLE_STMT,q,&r);

        SQLConnect(q,"college",strlen("college"),"root",strlen("root"),"",strlen(""));

        char x[]="use college";
	char y[]="select *from student_info;";

	SQLPrepare(r,x,strlen(x));
	SQLExecute(r);


	SQLPrepare(r,y,strlen(y));
	SQLBindCol(r,1,SQL_C_CHAR,d.name,50,0);
	SQLBindCol(r,2,SQL_C_SLONG,&d.roll,4,0);
	SQLBindCol(r,3,SQL_C_CHAR,d.branch,50,0);
	SQLBindCol(r,4,SQL_C_CHAR,d.mobno,50,0);
	SQLExecute(r);	

	while(!SQLFetch(r))
	{
		printf("%s  %d  %s  %s\n",d.name,d.roll,d.branch,d.mobno);
		insert_tree(d.roll,&d,0);
	}

	SQLFreeHandle(SQL_HANDLE_STMT,r);
	SQLDisconnect(q);
	SQLFreeHandle(SQL_HANDLE_DBC,q);
	SQLFreeHandle(SQL_HANDLE_ENV,p);



}




