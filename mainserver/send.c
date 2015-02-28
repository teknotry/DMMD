#include"sys/socket.h"
#include"netinet/in.h"

#include"myheader.h"


int send_subserver_exit(char *ip)
{

	int sid,st;
        struct sockaddr_in s;
        pthread_t t;
	int flag;
        sid=socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);
                s.sin_family=PF_INET;
                s.sin_port=3501;
                s.sin_addr.s_addr=inet_addr(ip);

        int len=sizeof(struct sockaddr_in);
	st=connect(sid,&s,len);

	if(st==-1)
	{
		printf("Connection to subserver fail\n");
	}
	else
	{
		flag=0;
		write(sid,&flag,sizeof(flag));

	}
}



int send_subserver_insert(struct yyy *d,char *ip)
{

	int sid,st;
        struct sockaddr_in s;
        pthread_t t;
	int flag;
        sid=socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);
                s.sin_family=PF_INET;
                s.sin_port=3501;
                s.sin_addr.s_addr=inet_addr(ip);

        int len=sizeof(struct sockaddr_in);
	st=connect(sid,&s,len);

	if(st==-1)
	{
		printf("Connection to subserver fail\n");
	}
	else
	{
		flag=1;
		write(sid,&flag,sizeof(flag));
		write(sid,d,sizeof(struct yyy));

	}
}
int send_subserver_update(struct yyy *d,char *ip)
{

	int sid,st;
        struct sockaddr_in s;
        pthread_t t;
	int flag;
        sid=socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);
                s.sin_family=PF_INET;
                s.sin_port=3501;
                s.sin_addr.s_addr=inet_addr(ip);

        int len=sizeof(struct sockaddr_in);
	st=connect(sid,&s,len);

	if(st==-1)
	{
		printf("Connection to subserver fail\n");
	}
	else
	{
		flag=3;
		write(sid,&flag,sizeof(flag));
		write(sid,d,sizeof(struct yyy));

	}
}
int send_subserver_delete(int index,char *ip)
{

	int sid,st;
        struct sockaddr_in s;
        pthread_t t;
	int flag;
        sid=socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);
                s.sin_family=PF_INET;
                s.sin_port=3501;
                s.sin_addr.s_addr=inet_addr(ip);

        int len=sizeof(struct sockaddr_in);
	st=connect(sid,&s,len);

	if(st==-1)
	{
		printf("Connection to subserver fail\n");
	}
	else
	{
		flag=2;
		write(sid,&flag,sizeof(flag));
		write(sid,&index,sizeof(index));

	}

}
int send_subserver_search(int index,char *ip,int nid)
{

	struct yyy d;
	int sid,st;
        struct sockaddr_in s;
        pthread_t t;
	int flag;
        sid=socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);
                s.sin_family=PF_INET;
                s.sin_port=3501;
                s.sin_addr.s_addr=inet_addr(ip);

        int len=sizeof(struct sockaddr_in);
	st=connect(sid,&s,len);

	if(st==-1)
	{
		printf("Connection to subserver fail\n");
		memset(&d,0,sizeof(struct yyy));
		write(nid,&d,sizeof(struct yyy));
		
	}
	else
	{
		flag=4;
		write(sid,&flag,sizeof(flag));
		write(sid,&index,sizeof(index));
		read(sid,&d,sizeof(struct yyy));
		write(nid,&d,sizeof(struct yyy));

	}

}
