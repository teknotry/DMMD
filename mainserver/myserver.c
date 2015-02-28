#include "sys/socket.h"
#include "netinet/in.h"
#include "pthread.h"
#include"sql.h"
#include"sqlext.h"
#include"myheader.h"
#include"fcntl.h"

extern struct xxx *b=0,*v=0;

#define SUBIP "192.168.1.31"

int validate(char *us,char *ps)
{
	char user[20];
	char pass[20];
	

	SQLHENV p;
	SQLHDBC q;
	SQLHSTMT r;

	SQLAllocHandle(SQL_HANDLE_ENV,0,&p);
	SQLSetEnvAttr(p,SQL_ATTR_ODBC_VERSION,SQL_OV_ODBC3,0);
	SQLAllocHandle(SQL_HANDLE_DBC,p,&q);
	SQLAllocHandle(SQL_HANDLE_STMT,q,&r);

	SQLConnect(q,"cutm",strlen("cutm"),"root",strlen("root"),"",strlen(""));

	char x[]="use cutm";
	char y[]="select *from login;";


	SQLPrepare(r,x,strlen(x));
	SQLExecute(r);

	SQLPrepare(r,y,strlen(y));
	SQLBindCol(r,1,SQL_C_CHAR,user,20,0);	
	SQLBindCol(r,2,SQL_C_CHAR,pass,20,0);	
	SQLExecute(r);

	while(!SQLFetch(r))
	{
		if(strcmp(user,us)==0 && strcmp(pass,ps)==0)
			return 1;
	}

	return 0;

	SQLFreeHandle(SQL_HANDLE_STMT,r);
	SQLDisconnect(q);
	SQLFreeHandle(SQL_HANDLE_DBC,q);
	SQLFreeHandle(SQL_HANDLE_ENV,p);

}

int client_respond(int *l)
{
	char user[2][20];
	char userpass[40];
	 int nid=*l;
	int flag,index;
	int i,j,k;
	struct yyy d;
	while(1)				// LOgin While   start
	{

		read(nid,&flag,sizeof(flag));
		printf("%d\n",flag);
		if(flag ==0)
		{
			pthread_exit(0);
		}
		else
		{
			j=0;k=0;
			memset(userpass,0,sizeof(userpass));
			read(nid,userpass,sizeof(userpass));
			printf("%s\n",userpass);

			memset(user,0,sizeof(user));
			for(i=0;i<strlen(userpass);i++)
			{	
				if(userpass[i]!=';')
				{						
					user[j][k]=userpass[i];
					k++;
				}
				else
				{
					j++;
					k=0;
				}
			}	

			printf("User: %s  Pass:  %s\n",user[0],user[1]);
			if(validate(user[0],user[1]))
			{
				printf("Login Sucess\n");
				flag=1;
				write(nid,&flag,sizeof(flag));
				break;
			}
			else
			{
				flag=0;
				write(nid,&flag,sizeof(flag));
				printf("Login Fail\n");
			}
		}					//LOGIN  While End ..
	}
	
		while(1)
		{
			//data read....
			read(nid,&flag,sizeof(flag));
			if(flag==0)
			{
				insert_db_newdata();
				send_subserver_exit(SUBIP);
				break;
			}			
			else
			if(flag==1)
			{
				
				read(nid,&d,sizeof(struct yyy));			
				
				
				printf("%s  %d  %s  %s\n",d.name,d.roll,d.branch,d.mobno);		
				if(d.roll>400)
				{
					d.roll=d.roll%400;
					send_subserver_insert(&d,SUBIP);
					flag=1;
					write(nid,&flag,sizeof(flag));
					
					
				}
				else
				{
					flag=insert_tree(d.roll,&d,1);
					
					write(nid,&flag,sizeof(flag));
					show_tree();
				}
			}
			else
			if(flag==2)
			{
				//delete LOGIC start................................
				read(nid,&index,sizeof(index));
				if(index>400)
				{
					index=index%400;
					send_subserver_delete(index,SUBIP);
				}
				else
				{
					delete_tree(index);
					show_tree();	
				}
				
			}
			else
			if(flag==3)
			{
				//Update Logic STRAT....................
				read(nid,&d,sizeof(struct yyy));			
				if(d.roll>400)
				{
					d.roll=d.roll%400;
					send_subserver_update(&d,SUBIP);
				}
				else
				{
					update_tree(d.roll,&d,1);
				}
				show_tree();	

			}
			else
			if(flag==4)
			{
				struct yyy *d;
				//Search Logic Start				
				read(nid,&index,sizeof(index));
				printf("For Search INDEX\n");
				printf("%d\n",index);
				if(index>400)
				{
					index=index%400;
					send_subserver_search(index,SUBIP,nid);
				}
				else
				{
					d=search_tree(index);
					write(nid,d,sizeof(struct yyy));
					//show_tree();	
				}
				
				

			}
			

		}


}
main(int argc,char *argv[])
{
	if(argc<2)
	{
		printf("Parameter Missing (start/stop) \n");
		exit(0);
	}

	if(argc>2)
	{
		printf("Toomany parameters\n");
		exit(0);
	}
	if(strcmp(argv[1],"start")==0)
	{
		int fd,pid;
		int sid,nid;
		pthread_t k;
		struct sockaddr_in p;
		int len=sizeof(struct sockaddr_in);
		sid=socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);
			p.sin_family=PF_INET;
			p.sin_port=3500;
			p.sin_addr.s_addr=INADDR_ANY;
		bind(sid,&p,len);
		listen (sid, 5);


		fd=open("PID.txt",O_RDONLY);
		if(fd!=-1)
		{
			printf("Server Already Started   [OK]\n");
			exit(0);
		}

		printf("Server Started Sucessfully       [OK]\n");
	       //daemon(1,0);
		fd=open("PID.txt",O_CREAT|O_RDWR);
		pid=getpid();
		write(fd,&pid,sizeof(pid));
		close(fd);
	
		create_tree();
		retrive_db_insert_tree();	
		show_tree();	
	
		while (1)
		{
			nid=accept(sid,&p,&len);
			printf("connection from:%s\n",inet_ntoa(p.sin_addr.s_addr));
			pthread_create(&k,0,client_respond,&nid);
		}
		pthread_join(k,0);
	
	}
	else
	if(strcmp(argv[1],"stop")==0)
	{
		int pid;
		int fd=open("PID.txt",O_RDONLY);
		if(fd==-1)
		{
			printf("Server is Not Started \n");
			exit(0);
		}
		read(fd,&pid,sizeof(pid));
		kill(pid,9);
		close(fd);
		remove("PID.txt");
		printf("Server is Stopped    [OK]\n");
	}
	else
	{
		printf("Invalid Parameter.\n");
	}
}


