#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<windows.h>

FILE *p;
void main_menu(void);
void search(void);
void add(void);
void edit(void);
void list(void);
void del(void);
COORD coord = {0, 0};
void gotoxy (int x, int y)
{
coord.X = x; coord.Y = y;
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

struct book{
    char name[20];
    int id;
    float price;
    int s_no;
    char author[20];
    char publisher[30];
}b;

void main_menu(void)
{
    int n;
    system("cls");
    printf("\nWELCOME to Library Management System created by HIMANSHU MAURYA\n");
    printf(" MENU\n");
    printf("1.SEARCH\n2.ADD\n3.EDIT\n4.LIST\n5.DELETE\n6.EXIT\n");
    printf("What do you want to do with a book?\n");
    printf("Please enter the corresponding number- ");
    scanf("%d",&n);

    switch(n)
    {
        case 1:search();
               break;
        case 2:add();
               break;
        case 3:edit();
               break;
        case 4:list();
               break;
        case 5:del();
               break;
        case 6:exit(1);
               break;
        default:printf("INVALID INPUT");
    }
}

void search(void)
{
    int id;
    char name[20],find;
    int n;
    system("cls");
    p=fopen("LMS.dat","rb+");
    rewind(p);
    if(p==NULL)
    {
       printf("There is no data in file, first add some data");
       getch();
       main_menu();
    }
    printf("\n SEARCH by-\n1.NAME\n2.ID number\n");
    printf("Enter the corresponding number- ");
    scanf("%d",&n);
    switch(n)
    {
    case 1:system("cls");
           printf("Enter name of the book- ");
           fflush(stdin);
           gets(name);
           while(fread(&b,sizeof(b),1,p)==1)
            {
                 if(strcmp(b.name,name)==0)
                     {
                         printf("\nBook found\n");
                         printf("\nName of the book- ");
                         puts(b.name);
                         printf("ID number of the book- %ld",b.id);
                         printf("\nPrice of the book- %f",b.price);
                         printf("\nSerial number of the book- %d",b.s_no);
                         printf("\nName of the author of the book- ");
                         puts(b.author);
                         printf("Name of the publisher of the book- ");
                         puts(b.publisher);
                         find='t';
                      }
           }
           if(find!='t')
            printf("\nBook not found");
           break;
    case 2:system("cls");
           printf("Enter Id number of the book- ");
           scanf("%ld",&id);
           while(fread(&b,sizeof(b),1,p)==1)
            {
                 if(id==b.id)
                     {
                         printf("\nBook found\n");
                         printf("\nName of the book- ");
                         puts(b.name);
                         printf("ID number of the book- %ld",b.id);
                         printf("\nPrice of the book- %f",b.price);
                         printf("\nSerial number of the book- %d",b.s_no);
                         printf("\nName of the author of the book- ");
                         puts(b.author);
                         printf("Name of the publisher of the book- ");
                         puts(b.publisher);
                         find='t';
                      }
           }
           if(find!='t')
            printf("\nBook not found");
           break;
    default:printf("INVALID INPUT");
    }
    fclose(p);
    printf("\nIf you want to continue with search press y or to return to main menu press any key- ");
    if(getche()=='y')
        search();
    else
        main_menu();
}

void add(void)
{
    system("cls");
    p=fopen("LMS.dat","ab+");

    printf("\n1.Enter name of the book- ");
    fflush(stdin);
    gets(b.name);
    printf("\n2.Enter Id number of the book- ");
    scanf("%ld",&b.id);
    printf("\n3.Enter price of the book- ");
    scanf("%f",&b.price);
    printf("\n4.Enter serial number of the book- ");
    scanf("%d",&b.s_no);
    printf("\n5.Enter name of the author of the book- ");
    fflush(stdin);
    gets(b.author);
    printf("\n6.Enter name of the publisher of the book- ");
    fflush(stdin);
    gets(b.publisher);

    fwrite(&b,sizeof(b),1,p);
    fclose(p);

    printf("\nYour data successfully added");
    printf("\nIf you want to continue with add press y or to return to main menu press any key- ");
    if(getche()=='y')
        add();
    else
        main_menu();
}

void edit(void)
{
    int id;
    char name[20],find;
    int n;
    FILE *q;
    system("cls");
    q=fopen("SAMPLE.dat","wb+");
    p=fopen("LMS.dat","rb+");
    rewind(p);
    if(p==NULL)
    {
       printf("There is no data in file, first add some data");
       exit(1);
    }
    printf("\n EDIT by using-\n1.NAME\n2.ID number\n");
    printf("Enter the corresponding number- ");
    scanf("%d",&n);
    switch(n)
    {
    case 1:system("cls");
           printf("Enter name of the book- ");
           fflush(stdin);
           gets(name);
           while(fread(&b,sizeof(b),1,p)==1)
            {
                 if(strcmp(b.name,name)==0)
                     {
                         printf("\nBook found\n");
                         printf("\nName of the book- ");
                         puts(b.name);
                         printf("ID number of the book- %ld",b.id);
                         printf("\nPrice of the book- %f",b.price);
                         printf("\nSerial number of the book- %d",b.s_no);
                         printf("\nName of the author of the book- ");
                         puts(b.author);
                         printf("Name of the publisher of the book- ");
                         puts(b.publisher);
                         find='t';
                      }
           }
           if(find!='t')
            printf("\nBook not found");
           if(find=='t')
           {
             printf("\nTo edit this book-press y");
             if(getch()=='y')
             {
                 rewind(p);
                 while(fread(&b,sizeof(b),1,p)==1)
                   {
                       if(strcmp(b.name,name)!=0)
                       {
                           fwrite(&b,sizeof(b),1,q);
                       }

                   }
                 fclose(p);
                 int r=remove("LMS.dat");
                 fclose(q);
                     if(r==0)
                     {
                         int u=rename("SAMPLE.dat","LMS.dat");
                         if(u==0)
                            printf("\nBook can be edited");
                         else
                            printf("\nDue to some problem the book can't be edited");
                     }
                     else{
                        printf("\nDue to some problem the book can't be edited");
                        getchar();
                        main_menu();}
             }
             else
                main_menu();
           }
    system("cls");
    p=fopen("LMS.dat","ab+");

    printf("\n1.Enter name of the book- ");
    fflush(stdin);
    gets(b.name);
    printf("\n2.Enter Id number of the book- ");
    scanf("%ld",&b.id);
    printf("\n3.Enter price of the book- ");
    scanf("%f",&b.price);
    printf("\n4.Enter serial number of the book- ");
    scanf("%d",&b.s_no);
    printf("\n5.Enter name of the author of the book- ");
    fflush(stdin);
    gets(b.author);
    printf("\n6.Enter name of the publisher of the book- ");
    fflush(stdin);
    gets(b.publisher);

    fwrite(&b,sizeof(b),1,p);
    fclose(p);
           break;
    case 2:system("cls");
           printf("Enter Id number of the book- ");
           scanf("%ld",&id);
           while(fread(&b,sizeof(b),1,p)==1)
            {
                 if(id==b.id)
                     {
                         printf("\nBook found\n");
                         printf("\nName of the book- ");
                         puts(b.name);
                         printf("ID number of the book- %ld",b.id);
                         printf("\nPrice of the book- %f",b.price);
                         printf("\nSerial number of the book- %d",b.s_no);
                         printf("\nName of the author of the book- ");
                         puts(b.author);
                         printf("Name of the publisher of the book- ");
                         puts(b.publisher);
                         find='t';
                      }
           }
           if(find!='t')
            printf("\nBook not found");
            if(find=='t')
           {
             printf("\nTo edit this book-press y");
             if(getch()=='y')
             {
                 rewind(p);
                 while(fread(&b,sizeof(b),1,p)==1)
                   {
                       if(id!=b.id)
                       {
                           fwrite(&b,sizeof(b),1,q);
                       }

                   }
                 fclose(p);
                 int r=remove("LMS.dat");
                 fclose(q);
                     if(r==0)
                     {
                         int u=rename("SAMPLE.dat","LMS.dat");
                         if(u==0)
                            printf("\nBook can be edited");
                         else
                            printf("\nDue to some problem the book can't be edited");
                     }
                     else{
                        printf("\nDue to some problem the book can't be edited");
                        getch();
                        main_menu();}
             }
             else
                main_menu();
           }
    system("cls");
    p=fopen("LMS.dat","ab+");

    printf("\n1.Enter name of the book- ");
    fflush(stdin);
    gets(b.name);
    printf("\n2.Enter Id number of the book- ");
    scanf("%ld",&b.id);
    printf("\n3.Enter price of the book- ");
    scanf("%f",&b.price);
    printf("\n4.Enter serial number of the book- ");
    scanf("%d",&b.s_no);
    printf("\n5.Enter name of the author of the book- ");
    fflush(stdin);
    gets(b.author);
    printf("\n6.Enter name of the publisher of the book- ");
    fflush(stdin);
    gets(b.publisher);

    fwrite(&b,sizeof(b),1,p);
    fclose(p);
           break;
    default:printf("INVALID INPUT");
    }
    printf("\nYour book edited successfully");
    printf("\nIf you want to continue with edit press y or to return to main menu press any key- ");
    if(getche()=='y')
        edit();
    else
        main_menu();
}

void list(void)
{
   int i=0;
   p=fopen("LMS.dat","rb+");
   rewind(p);
   system("cls");
   gotoxy(2,1);
   printf("S.No.");
   gotoxy(20,1);
   printf("Name");
   gotoxy(75,1);
   printf("ID no.");
   gotoxy(110,1);
   printf("Price");
   while(fread(&b,sizeof(b),1,p)==1)
    {
        i=i+2;
        gotoxy(2,i);
        printf("%d",b.s_no);
        gotoxy(20,i);
        printf("%s",b.name);
        gotoxy(75,i);
        printf("%ld",b.id);
        gotoxy(110,i);
        printf("%f",b.price);
    }
    fclose(p);
    gotoxy(0,i+2);
    printf("\nIf you want to return to main menu press any key- ");
    if(getche())
        main_menu();
}

void del(void)
{
    int id;
    char name[20],find;
    int n;
    FILE *q;
    system("cls");
    q=fopen("SAMPLE.dat","wb+");
    p=fopen("LMS.dat","rb+");
    if(p==NULL)
    {
       printf("There is no data in file, first add some data");
       exit(1);
    }
    printf("\n DELETE by using-\n1.NAME\n2.ID number\n");
    printf("Enter the corresponding number- ");
    scanf("%d",&n);
    rewind(p);
    switch(n)
    {
    case 1:system("cls");
           printf("Enter name of the book- ");
           fflush(stdin);
           gets(name);
           while(fread(&b,sizeof(b),1,p)==1)
            {
                 if(strcmp(b.name,name)==0)
                     {
                         printf("\nBook found\n");
                         printf("\nName of the book- ");
                         puts(b.name);
                         printf("ID number of the book- %ld",b.id);
                         printf("\nPrice of the book- %f",b.price);
                         printf("\nSerial number of the book- %d",b.s_no);
                         printf("\nName of the author of the book- ");
                         puts(b.author);
                         printf("Name of the publisher of the book- ");
                         puts(b.publisher);
                         find='t';
                      }
           }
           if(find!='t')
            printf("\nBook not found");
           if(find=='t')
           {
             char m;
             printf("\nTo delete this book-press y -");
             scanf("%c",&m);
             if(m=='y')
             {
                 rewind(p);
                 while(fread(&b,sizeof(b),1,p)>0)
                   {
                       if(strcmp(b.name,name)!=0)
                       {
                           fwrite(&b,sizeof(b),1,q);
                       }

                   }
                 fclose(p);
                 int r=remove("LMS.dat");
                 fclose(q);
                     if(r==0)
                     {
                         int u=rename("SAMPLE.dat","LMS.dat");
                         if(u==0)
                            printf("\nBook deleted successfully");
                         else
                            printf("\nUnable to delete the book");
                     }
                     else{
                        printf("\nUnable to delete the book");
                        getch();
                        main_menu();}
             }
             else
                main_menu();
           }
           break;
    case 2:system("cls");
           printf("Enter Id number of the book- ");
           scanf("%ld",&id);
           while(fread(&b,sizeof(b),1,p)==1)
            {
                 if(id==b.id)
                     {
                         printf("\nBook found\n");
                         printf("\nName of the book- ");
                         puts(b.name);
                         printf("ID number of the book- %ld",b.id);
                         printf("\nPrice of the book- %f",b.price);
                         printf("\nSerial number of the book- %d",b.s_no);
                         printf("\nName of the author of the book- ");
                         puts(b.author);
                         printf("Name of the publisher of the book- ");
                         puts(b.publisher);
                         find='t';
                      }
           }
           if(find!='t')
            printf("\nBook not found");
            if(find=='t')
           {
             printf("\nTo delete this book-press y");
             if(getch()=='y')
             {
                 rewind(p);
                 while(fread(&b,sizeof(b),1,p)>0)
                   {
                       if(id!=b.id)
                       {
                           fwrite(&b,sizeof(b),1,q);
                       }

                   }
                 fclose(p);
                 int r=remove("LMS.dat");
                 fclose(q);
                     if(r==0)
                     {
                         int u=rename("SAMPLE.dat","LMS.dat");
                         if(u==0)
                            printf("\nBook deleted successfully");
                         else
                            printf("\nUnable to delete the book");
                     }
                     else{
                        printf("\nUnable to delete the book");
                        getch();
                        main_menu();}
             }
             else
                main_menu();
           }
           break;
    default:printf("INVALID INPUT");
    }
    printf("\nIf you want to continue with delete press y or to return to main menu press any key- ");
    if(getche()=='y')
        del();
    else
        main_menu();
}

void main(void)
{
    system("color 94");
    main_menu();
    getch();
}
