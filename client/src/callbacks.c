#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"

struct data
{
	char name[50];
	int roll;
	char branch[50];
	char mobno[50];
};


extern int sid;
extern GtkWidget *window2,*window1,*window_option,*window_delete,*window_update,*window_update_index;

int flag;
void
on_login_destroy                       (GtkObject       *object,
                                        gpointer         user_data)
{

	flag=0;
	write(sid,&flag,sizeof(flag));
	gtk_main_quit();

}


void
on_login_clicked                       (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *e1,*e2,*l1;
	char *user,*pass;
	char userpass[40];


	flag=1;
	write(sid,&flag,sizeof(flag));

	e1=lookup_widget(GTK_WIDGET(button),"entry1");
	user=gtk_entry_get_text(e1);

	e2=lookup_widget(GTK_WIDGET(button),"entry2");
	pass=gtk_entry_get_text(e2);
	
	strcpy(userpass,user);
	strcat(userpass,";");
	strcat(userpass,pass);


	write(sid,userpass,strlen(userpass));
	read(sid,&flag,sizeof(flag));
	if(flag==0)
	{
		l1=lookup_widget(GTK_WIDGET(button),"label_st");
		gtk_label_set_text(l1,"LOGIN FAIL");
		printf("Login Fail\n");
	}
	else
	{
		l1=lookup_widget(GTK_WIDGET(button),"label_st");
		gtk_label_set_text(l1,"LOGIN Sucess");
		printf("Login Sucess\n");
		gtk_widget_show(window_option);	
		gtk_widget_hide(window1);	
	}

	gtk_entry_set_text(e1,"");
        gtk_entry_set_text(e2,"");

        gtk_widget_grab_focus(e1);


}


void
on_exit_clicked                        (GtkButton       *button,
                                        gpointer         user_data)
{
	flag=0;
	write(sid,&flag,sizeof(flag));
	gtk_main_quit();

}


void
on_Exit_clicked                        (GtkButton       *button,
                                        gpointer         user_data)
{
	
	gtk_widget_show(window_option);
	gtk_widget_hide(window2);	


}


void
on_Save_clicked                        (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *e_name,*e_roll,*e_branch,*e_mobno,*l1;
	char *name,*roll,*branch,*mobno;
	struct data d;	

	flag=1;
	write(sid,&flag,sizeof(flag));

	e_name=lookup_widget(GTK_WIDGET(button),"entry_name");
	e_roll=lookup_widget(GTK_WIDGET(button),"entry_roll");
	e_branch=lookup_widget(GTK_WIDGET(button),"entry_branch");
	e_mobno=lookup_widget(GTK_WIDGET(button),"entry_mobno");
	
	name=gtk_entry_get_text(e_name);
	roll=gtk_entry_get_text(e_roll);
	branch=gtk_entry_get_text(e_branch);
	mobno=gtk_entry_get_text(e_mobno);
	
	l1=lookup_widget(GTK_WIDGET(button),"label3");
	

	strcpy(d.name,name);
	d.roll=atoi(roll);
	strcpy(d.branch,branch);
	strcpy(d.mobno,mobno);

	write(sid,&d,sizeof(struct data));
	read(sid,&flag,sizeof(flag));
	if(flag==1)
	{
		gtk_label_set_text(l1,"Sucessfully Send");
		gtk_entry_set_text(e_name,"");
		gtk_entry_set_text(e_roll,"");
		gtk_entry_set_text(e_branch,"");
		gtk_entry_set_text(e_mobno,"");
	}
	if(flag==2)
	{
		gtk_label_set_text(l1,"Data Already Exist Please Select update");

	}
	
	
	
	gtk_widget_grab_focus(e_name);

}


void
on_main_window_destroy                 (GtkObject       *object,
                                        gpointer         user_data)
{
	window_option=create_window_option();
	gtk_widget_show(window_option);
	gtk_widget_hide(window2);	

}


void
on_option_destroy                      (GtkObject       *object,
                                        gpointer         user_data)
{
	flag=0;
	write(sid,&flag,sizeof(flag));
	gtk_main_quit();

}


void
on_button__insert_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{	

	gtk_widget_show(window2);
	gtk_widget_hide(window_option);
}




void
on_button_update_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
	window_update=create_window_update();
	window_delete=create_window_delete();
	gtk_widget_show(window_update);	
	gtk_widget_hide(window_option);
	
}


void
on_window_delete_destroy               (GtkObject       *object,
                                        gpointer         user_data)
{
	gtk_widget_hide(window_delete);	
	gtk_widget_show(window_option);

}


void
on_button_delete_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{

	gtk_widget_show(window_delete);	
	gtk_widget_hide(window_option);


}


void
on_window_update_destroy               (GtkObject       *object,
                                        gpointer         user_data)
{
	gtk_widget_hide(window_update);	
	gtk_widget_show(window_option);
}


void
on_button_delete_index_clicked         (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *e1;
	char *ch;
	int index;

	int flag=2;
	write(sid,&flag,sizeof(flag));
	
	e1=lookup_widget(GTK_WIDGET(button),"entry_delete");
	ch=gtk_entry_get_text(e1);
	
	index=atoi(ch);
	write(sid,&index,sizeof(index));
	
	gtk_widget_hide(window_delete);	
	gtk_widget_show(window_option);

}


void
on_button_logout_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{

	gtk_widget_hide(window_option);
        gtk_widget_show(window1);

}


void
on_button_insert_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
	gtk_widget_show(window2);
	gtk_widget_hide(window_option);

}


void
on_button6_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_button7_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{
	
	GtkWidget *e_name,*e_roll,*e_branch,*e_mobno;
	char *name,*roll,*branch,*mobno;
	struct data d;	

	flag=3;
	write(sid,&flag,sizeof(flag));

	e_name=lookup_widget(GTK_WIDGET(button),"entry4");
	e_roll=lookup_widget(GTK_WIDGET(button),"entry5");
	e_branch=lookup_widget(GTK_WIDGET(button),"entry6");
	e_mobno=lookup_widget(GTK_WIDGET(button),"entry7");
	
	name=gtk_entry_get_text(e_name);
	roll=gtk_entry_get_text(e_roll);
	branch=gtk_entry_get_text(e_branch);
	mobno=gtk_entry_get_text(e_mobno);

	strcpy(d.name,name);
	d.roll=atoi(roll);
	strcpy(d.branch,branch);
	strcpy(d.mobno,mobno);

	write(sid,&d,sizeof(struct data));
	
	gtk_entry_set_text(e_name,"");
	gtk_entry_set_text(e_roll,"");
	gtk_entry_set_text(e_branch,"");
	gtk_entry_set_text(e_mobno,"");
	
	gtk_widget_grab_focus(e_name);

}



void
on_button_index_update_clicked         (GtkButton       *button,
                                        gpointer         user_data)
{

	gtk_widget_show(window_update);
	gtk_widget_hide(window_update_index);

}


void
on_window_update_index_destroy         (GtkObject       *object,
                                        gpointer         user_data)
{
	gtk_widget_show(window_option);
	//gtk_widget_hide(window_update_index);

}


void
on_button_search_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{
	GtkWidget *s_e,*l16,*l17,*l18;
	char *index;
	struct data d;
	
	int flag=4;
	write(sid,&flag,sizeof(flag));
	s_e=lookup_widget(GTK_WIDGET(button),"entry12");
	l16=lookup_widget(GTK_WIDGET(button),"label16");
	l17=lookup_widget(GTK_WIDGET(button),"label17");
	l18=lookup_widget(GTK_WIDGET(button),"label18");
	index=gtk_entry_get_text(s_e);
	flag=atoi(index);
	write(sid,&flag,sizeof(flag));
	read(sid,&d,sizeof(struct data));
	if(d.roll==0)
	{
		gtk_label_set_text(l16,"No record Found");
		gtk_label_set_text(l17,"");
		gtk_label_set_text(l18,"");	

		printf("%s  %d  %s  %s\n",d.name,d.roll,d.branch,d.mobno);
	}
	else
	{
		printf("%s  %d  %s  %s\n",d.name,d.roll,d.branch,d.mobno);
		gtk_label_set_text(l16,d.name);
		gtk_label_set_text(l17,d.branch);
		gtk_label_set_text(l18,d.mobno);	
	}
	
	
	
}

