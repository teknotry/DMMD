#define level 2
#define no 20
#include"myheader.h"

struct data
{
	char name[50];
        int roll;
        char branch[50];
        char mobno[50];
	int st;
};
struct node
{	
	int index[no];
	struct data *data[no];
	struct node *ad[no];
};

	struct node *root,*v;

int create_tree()
{
	int i,j,start;
	root=malloc(sizeof(struct node));
	for(i=0;i<no;i++)
	{
		v=root;
		v->index[i]=i*no;
		v->ad[i]=malloc(sizeof(struct node));
		
		start=v->index[i];
		v=v->ad[i];	
		for(j=0;j<no;j++)
		{
			v->index[j]=start;
			start++;
			v->ad[j]=0;
			v->data[j]=0;	
		}
	}

}

int show_tree()
{
	int i,j,start;
	for(i=0;i<no;i++)
	{
		v=root;
		printf("Label2: %d ",v->index[i]);
		v=v->ad[i];
		for(j=0;j<no;j++)
		{
			if(v->data[j]==0)
			{
				printf("%d  %d | ",v->index[j],v->data[j]);
			}
			else
			{
				printf("%d  %s %d  %s  %s %d| ",v->index[j],v->data[j]->name,v->data[j]->roll,v->data[j]->branch,v->data[j]->mobno,v->data[j]->st);

			}
		}
		printf("\n");
	}	
}
int search_tree(int index)
{
	struct yyy d;
	memset(&d,0,sizeof(struct yyy));	
	int i,j,start;
	for(i=0;i<no;i++)
	{
		v=root;
		printf("Label2: %d ",v->index[i]);
		v=v->ad[i];
		for(j=0;j<no;j++)
		{
			if(v->data[j]==0)
			{
				printf("%d  %d | ",v->index[j],v->data[j]);
			}
			else
			{
				printf("%d  %s %d  %s  %s %d| ",v->index[j],v->data[j]->name,v->data[j]->roll,v->data[j]->branch,v->data[j]->mobno,v->data[j]->st);
				if(index==v->index[j])
				{
					d.roll=v->data[j]->roll;
					strcpy(d.name,v->data[j]->name);			
					strcpy(d.branch,v->data[j]->branch);			
					strcpy(d.mobno,v->data[j]->mobno);
					return &d;			
				}
			}
		}
		printf("\n");
	}	
	return &d;
}



int insert_db_newdata()
{
	int i,j,start;
	for(i=0;i<no;i++)
	{
		v=root;
		printf("Label2: %d ",v->index[i]);
		v=v->ad[i];
		for(j=0;j<no;j++)
		{
			if(v->data[j]==0)
			{
				printf("%d  %d | ",v->index[j],v->data[j]);
			}
			else
			{
				//printf("%d  %s %d  %s  %s %d| ",v->index[j],v->data[j]->name,v->data[j]->roll,v->data[j]->branch,v->data[j]->mobno,v->data[j]->st);
				if(v->data[j]->st==1)
				{
					insert_db(v->data[j]->name,v->data[j]->roll,v->data[j]->branch,v->data[j]->mobno);			
					v->data[j]->st=0;
				}
	

			}
		}
		printf("\n");
	}	
}




int insert_tree(int index,struct yyy *d,int st)
{
	
	int i,j,start;
	if(index>no*no)
	{
		printf("Invalid Index\n");
		return 0;
	}

	v=root;
	i=0;
	while(v->index[i]<index)
	{
		if(i==no)
			break;
	//	printf("%d  %d\n",v->index[i],i);
		i++;
	//	sleep(1);
	}
	if(v->index[i]!=index)
	{
		i--;
	}
	
	v=v->ad[i];
	v->data[index%no]=malloc(sizeof(struct data));
	
	//Data assignment............
	v->data[index%no]->roll=d->roll;
	v->data[index%no]->st=st;
	strcpy(v->data[index%no]->name,d->name);
	strcpy(v->data[index%no]->branch,d->branch);
	strcpy(v->data[index%no]->mobno,d->mobno);

}


int update_tree(int index,struct yyy *d,int st)
{
	
	int i,j,start;
	if(index>no*no)
	{
		printf("Invalid Index\n");
		return 0;
	}

	v=root;
	i=0;
	while(v->index[i]<index)
	{
		if(i==no)
			break;
	//	printf("%d  %d\n",v->index[i],i);
		i++;
	//	sleep(1);
	}
	if(v->index[i]!=index)
	{
		i--;
	}
	
	v=v->ad[i];

	if(v->data[index%no]->st==1)
	{	
		v->data[index%no]=malloc(sizeof(struct data));
		//Data assignment............
	
	
		v->data[index%no]->roll=d->roll;
		v->data[index%no]->st=st;
		strcpy(v->data[index%no]->name,d->name);
		strcpy(v->data[index%no]->branch,d->branch);
		strcpy(v->data[index%no]->mobno,d->mobno);
		v->data[index%no]->st=1;
		printf("NOT IN DB\n");
	}
	else
	{
		
		strcpy(v->data[index%no]->name,d->name);
		strcpy(v->data[index%no]->branch,d->branch);
		strcpy(v->data[index%no]->mobno,d->mobno);
		v->data[index%no]->st=0;
		update_db(d->name,d->roll,d->branch,d->mobno);
		printf(" IN DB\n");
	}
}

int delete_tree(int index)
{
	int i,j,start;
	if(index>no*no)
	{
		printf("Invalid Index\n");
		return 0;
	}

	v=root;
	i=0;
	while(v->index[i]<index)
	{
		if(i==no)
			break;
		//printf("%d  %d\n",v->index[i],i);
		i++;
	}
	if(v->index[i]!=index)
	{
		i--;
	}
	
	v=v->ad[i];

	if(v->data[index%no]->st==0)
	{
		delete_db(index);
	}
	free(v->data[index%no]);
	v->data[index%no]=0;
	
}






