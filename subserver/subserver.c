#include "sys/socket.h"
#include "netinet/in.h"
#include "pthread.h"
#include"sql.h"
#include"sqlext.h"
#include"myheader.h"
#include"fcntl.h"

extern struct xxx *b=0,*v=0;


int client_respond(int *l)
{
	
	 int nid=*l;
	int flag,index;
	int i,j,k;
	struct yyy d,*data;
	
			//data read....
			read(nid,&flag,sizeof(flag));
			if(flag==0)
			{
				insert_db_newdata();	
				pthread_exit(0);
			}
			else
			if(flag==1)
			{
				read(nid,&d,sizeof(struct yyy));			
				printf("%s  %d  %s  %s\n",d.name,d.roll,d.branch,d.mobno);		
					insert_tree(d.roll,&d,1);
					show_tree();
			}
			else
			if(flag==2)
			{
				read(nid,&index,sizeof(index));
					delete_tree(index);
					show_tree();	
				
			}
			else
			if(flag==3)
			{
				
				read(nid,&d,sizeof(struct yyy));			
				update_tree(d.roll,&d,1);
				show_tree();	

			}
			else
			if(flag==4)
			{
				read(nid,&index,sizeof(index));
				data=search_tree(index);			
				write(nid,data,sizeof(struct yyy));
				printf("%s %d  %s  %s\n",data->name,data->roll,data->branch,data->mobno);

			}
			

}
main(int argc,char *argv[])
{

	if(argc<2)
	{
		printf("Parameter Missing\n");
		exit(0);
	}
	if(argc>2)
	{
		printf("Too Many Parameter\n");
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
		p.sin_port=3501;
		p.sin_addr.s_addr=INADDR_ANY;
	
		
		bind(sid,&p,len);
		listen (sid, 5);
		
		fd=open("PID.txt",O_RDONLY);
		if(fd!=-1)
		{
			printf("Server is Already started\n");
			exit(0);
		}
			
		printf("Server Started Sucessfully                    [OK]\n");
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
		int fd,pid;
		//Stop lOgic
		fd=open("PID.txt",O_RDONLY);
		if(fd==-1)
		{
			printf("SUBServer is Not started\n");
			exit(0);
		}
		read(fd,&pid,sizeof(pid));
		kill(pid,9);
		close(fd);
		remove("PID.txt");
		printf("Subserver stopped Sucessfully            [OK]\n");
	}
	else
	{
		printf("Invalid Arguments(Please give start/stop)\n");
		exit(0);
	}
}
