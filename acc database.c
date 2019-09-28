#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <time.h>

/*
    Shihab Sikder
    Islamic University of Technology
    Computer Science and Engineering
    Please do not fully copy paste the code for project.
    It's for learning.

*/
const char username[100] = "Admin";
const char password[100] = "ADMIN";


int ini_ID;
int last_ID;
int start_ID;
char regTime[1000];

void addEmployee();
void login();
void landingPage();
void getTime();
void search();
void user();

int main()
{
    printf("\tChoose log in type:");
    printf("\n\t<1>Admin log in");
    printf("\n\t<2>User log in\n\t");
    int temp;
    scanf("%d",&temp);
    if(temp==1)
    {
        login();
        landingPage();
    }
    if(temp==2)
    {
        user();
    }

}

void login()
{
    char temp_username[100],temp_password[100];
    printf("\n\n\tLog in as Admin");
    printf("\n\tName:");
    scanf("%s",temp_username);
    printf("\tPassword:");
    scanf("%s",temp_password);
    if( strcmp(temp_username,username)==0 && strcmp(temp_password,password)==0 )
    {
        printf("\t.....................");
        printf("\n\n\tLog in Successful");
        FILE *admin;
        admin = fopen("admin.txt","r");
        fscanf(admin,"%d %d",&start_ID,&last_ID);
        ini_ID = last_ID;
        fclose(admin);
    }
    else
    {
        printf("\n\tIncorrect Information!!!");
        exit(1);
    }
}

void landingPage()
{
    int temp_option;
    printf("\n\t(1)Add a new employee");
    printf("\n\t(2)Show employee list\n\t");
    printf("(3)Search Employee\n\t");
    printf("(4)Exit\n\t");
    printf("(5)Go to LOG IN CHOICE menu\n\t");
    printf("Your Choice: \n\t");

    scanf("%d",&temp_option);
    if(temp_option==1)
    {
        addEmployee();
    }
    if(temp_option==2)
    {
        seeEmployeeList();
    }
    if(temp_option==3)
        search();
    if(temp_option==4)
        exit(1);
    if(temp_option==5)
            main();
    landingPage();
}

void addEmployee()
{
    FILE *filePointer ;
    ini_ID++;
    int temp_ID = ini_ID;
    char temp_first_name[100],temp_last_name[100],temp_pass[100],temp_cnf_pass[100];
    printf("\n\tAdding a new employee");
    printf("\n\tFirst name: ");
    scanf("%s",&temp_first_name);
    printf("\tLast name: ");
    scanf("%s",&temp_last_name);
    printf("\tPassword: ");
    scanf("%s",&temp_pass);
    printf("\tConfirm pass: ");
    scanf("%s",&temp_cnf_pass);

    getTime();
    char f_name[100];
    itoa(temp_ID,f_name,10);// int,str,base
    strcat(f_name,".txt");
    filePointer = fopen(f_name, "w");
    fprintf(filePointer, "%s\n%s\n%s\n%d\n%s", temp_first_name, temp_last_name, temp_pass, ini_ID,regTime);
    fclose(filePointer);
    last_ID = temp_ID;
    FILE *admin;
    admin = fopen("admin.txt","w");
    fprintf(admin,"%d %d",start_ID,last_ID);

    printf("\n\t!!!USER SUCCESSFULLY ADDED TO DATABASE!!!\n");

}

void seeEmployeeList()
{
    printf("\n\n");
    printf("\t------------------------------------------------------------\n");
    printf("\t   ID  |          Name         |    Registration time  \n");
    printf("\t------------------------------------------------------------\n");
    int i;
    char view_first_name[100], view_last_name[100], view_pass[100], view_ini_ID[100],view_regTime[100];
    FILE *fp;
    for(i = start_ID+1; i<=last_ID; i++)
    {
        char f_temp[100];
        itoa(i,f_temp,10);
        strcat(f_temp,".txt");
        fp = fopen(f_temp,"r");
        fscanf(fp,"%s\n%s\n%s\n%s\n%[^\n]s",view_first_name, view_last_name, view_pass, view_ini_ID,view_regTime);

        fclose(fp);
        printf("\t%d  | %10s %10s | %s\n",i,view_first_name, view_last_name,view_regTime);
        printf("\t------------------------------------------------------------\n");
    }
}
void search()
{
    char id[100];
    printf("\n\tEnter ID: ");
    scanf("%s",&id);
    char view_first_name[100], view_last_name[100], view_pass[100], view_ini_ID[100],view_regTime[100];
    strcat(id,".txt");
    FILE *fp;
    fp = fopen(id,"r");
    fscanf(fp,"%s\n%s\n%s\n%s\n%[^\n]s",view_first_name, view_last_name, view_pass, view_ini_ID,view_regTime);
    fclose(fp);
    printf("\n\tName: %s %s",view_first_name, view_last_name);
    printf("\n\tPassword: %s",view_pass);
    printf("\n\tReg time: %s",view_regTime);
    printf("\n\tId: %s\n\n",view_ini_ID);
}
void user()
{
    char id[100];
    char pass[100];
    printf("\n\tEnter ID: ");
    scanf("%s",&id);
    printf("\tEnter Pass: ");
    scanf("%s",&pass);
    char view_first_name[100], view_last_name[100], view_pass[100], view_ini_ID[100],view_regTime[100];
    char view_first_name1[100], view_last_name1[100], view_pass1[100], view_ini_ID1[100];
    strcat(id,".txt");
    FILE *fp;
    fp = fopen(id,"r");
    fscanf(fp,"%s\n%s\n%s\n%s\n%[^\n]s",view_first_name, view_last_name, view_pass, view_ini_ID,view_regTime);
    fclose(fp);

    if(strcmp(pass,view_pass)==0)
    {
        printf("\n\t<1>Update profile");
        printf("\n\t<2>See my profile");
        printf("\n\t<3>Change password\n\t");
        int temp;
        printf("Choice: ");
        scanf("%d",&temp);
        if(temp==1)
        {
            printf("\n\tFirst name:");
            scanf("%s",view_first_name1);
            printf("\tLase name:");
            scanf("%s",view_last_name1);
            printf("\tPassword:");
            scanf("%s",view_pass1);
            fp = fopen(id,"w");
            fprintf(fp, "%s\n%s\n%s\n%s\n%s", view_first_name1, view_last_name1, view_pass1, view_ini_ID,view_regTime);
            fclose(fp);
            printf("User information for %s is successful",view_ini_ID);
        }
        if(temp==2)
        {
            search();
        }
        if(temp==3)
        {
            int prev_pass[100];
            printf("\n\tEnter previous pass:");
            scanf("%s",prev_pass);
            if(strcmp(prev_pass,view_pass)==0)
            {
                printf("\tEnter new password:");
                scanf("%s",prev_pass);
                fp = fopen(id,"w");
                fprintf(fp, "%s\n%s\n%s\n%s\n%s", view_first_name, view_last_name, prev_pass, view_ini_ID,view_regTime);
                fclose(fp);
            }
        }
    }
    main();
}

void getTime()
{
    time_t rawtime;
    struct tm * timeinfo;
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    strcpy(regTime, asctime(timeinfo));
}
