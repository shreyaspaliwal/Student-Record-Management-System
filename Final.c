//Student Record Management System
//This project is prepared using the concepts of File Handling
//Concept of structure is also used in this project
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>/*This header file is used to access the Win32 API functions and it makes it easier for the user to use the in-built functionality.*/
#include <string.h>
void gotoxy(int, int); /*The gotoxy() function is used to set the coordinates from where a line is to be printed on the screen. 
                            It takes two variables each for seperate x and y axis.*/
void menu();
void add();
void view();
void search();
void modify();
void deleterec();

struct student /*When we enter anything, it gets stored in this structure*/
{
    char name[30];
    int rollno;
    char course[20];
    char branch[20];
};

int main()
{
    gotoxy(15, 8);
    printf("Student Database Management System");
    gotoxy(19, 15);
    printf("Press any key to continue..");
    getch(); /* It reads a single character from the keyboard. But it does not use any buffer,
                so the entered character is immediately returned without waiting for the enter key.*/
    menu();  /*It calls the menu function so that the menu will be displayed to get further tasks.*/
    return 0;
}

void menu() /*This function displays the menu to the user to perform his task*/
{
    int choice;
    system("cls"); /*Used to clear the console*/
    gotoxy(10, 3);
    printf("MENU:");
    gotoxy(10, 5);
    printf("Enter the serial number whose task is to be performed");
    gotoxy(10, 7);
    printf("1 : Add Record");
    gotoxy(10, 8);
    printf("2 : View Record");
    gotoxy(10, 9);
    printf("3 : Search Record");
    gotoxy(10, 10);
    printf("4 : Modify Record");
    gotoxy(10, 11);
    printf("5 : Delete Record");
    gotoxy(10, 12);
    printf("6 : Exit");
    gotoxy(10, 15);
    printf("Enter your choice: ");
    scanf("%d", &choice); /*Here,the information entered by the user is stored in the choice variable and this variable will be used in switch case.*/

    switch (choice) /*Switch case will help in getting the user's request to its destination by calling functions as per the menu's serial number.*/
    {
    case 1:
        add();
        break;
    case 2:
        view();
        break;
    case 3:
        search();
        break;
    case 4:
        modify();
        break;
    case 5:
        deleterec();
        break;
    case 6:
        exit(1);
        break;
    default:
        gotoxy(10, 17);
        printf("Invalid choice");
    }
}
// Functions(add(),view(),search(),modify(),delete(),exit()) after this line will be called according to the information entered by the user in menu function.
void add()
{
    FILE *fp; /*Declaring the file pointer*/
    struct student std;
    char another = 'y';
    system("cls");                   /*Used to clear the console*/
    fp = fopen("record.txt", "ab+"); /*Here, the record.txt file is being opened using fopen function*/
    /*“a+” – Searches file. If the file is opened successfully fopen( ) loads it into memory and
     sets up a pointer which points to the last character in it. If the file doesn’t exist, a new file is created. 
     Returns NULL, if unable to open the file.(b=binary)*/
    if (fp == NULL)
    {
        gotoxy(10, 5);
        printf("Error opening file");
        exit(1);
    }
    fflush(stdin);         /*fflush() is typically used for output stream only. 
                             Its purpose is to clear (or flush) the output buffer and move the buffered data to
                             console (in case of stdout) or disk (in case of file output stream).*/
    while (another == 'y') /*In this loop the record which is to be added is submitted by the user*/
    {
        gotoxy(10, 3);
        printf("Add record:");
        gotoxy(10, 5);
        printf("Enter details of the student");
        gotoxy(10, 7);
        printf("Enter Name : ");
        gets(std.name);
        gotoxy(10, 8);
        printf("Enter Roll No. :");
        scanf("%d", &std.rollno);
        gotoxy(10, 9);
        fflush(stdin); /*fflush() is typically used for output stream only. 
                             Its purpose is to clear (or flush) the output buffer and move the buffered data to
                             console (in case of stdout) or disk (in case of file output stream).*/
        gotoxy(10, 10);
        printf("Enter Course :");
        gets(std.course);
        gotoxy(10, 11);
        printf("Enter Branch :");
        gets(std.branch);
        fwrite(&std, sizeof(std), 1, fp); /*The fwrite function will write the record in the file. It takes 4 arguments:-
                                            first argument shows the address(&std) in which the file is stored and new record is to be written
                                            second argument shows the size of the file; sizeof(std)
                                            third argument shows the number of records to be written by the function each time; 1
                                            fourth argument shows the file open variable in which we have declared the file name and type of action; fopen("record.txt","ab+")*/
        gotoxy(10, 12);
        printf("If you want to add another record enter 'Y' else 'N' : ");
        fflush(stdin); /*fflush() is typically used for output stream only. 
                             Its purpose is to clear (or flush) the output buffer and move the buffered data to
                             console (in case of stdout) or disk (in case of file output stream).*/
        another = getch();
        system("cls"); /*Used to clear the console*/
        fflush(stdin); /*fflush() is typically used for output stream only. 
                             Its purpose is to clear (or flush) the output buffer and move the buffered data to
                             console (in case of stdout) or disk (in case of file output stream).*/
    }
    fclose(fp);
    gotoxy(10, 18);
    printf("Press any key to continue");
    getch(); /* It reads a single character from the keyboard. But it does not use any buffer,
                so the entered character is immediately returned without waiting for the enter key.*/
    menu();  /*It again calls the menu function so that the menu will again be displayed to get further tasks.*/
}

void view()
{
    FILE *fp; /*Declaring the file pointer*/
    int i = 1, j;
    struct student std;
    system("cls"); /*Used to clear the console*/
    gotoxy(10, 5);
    printf("Sr.No.   Name of Student    Roll No.    Course    Branch");
    gotoxy(10, 6);
    printf("________________________________________________________");
    fp = fopen("record.txt", "rb+"); /* The record.txt file will be opened in Read Binary mode(rb+)*/
    if (fp == NULL)                  /*This condition will check if the file is empty*/
    {
        gotoxy(10, 8);
        printf("Error opening file");
        exit(1);
    }
    j = 8;
    while (fread(&std, sizeof(std), 1, fp) == 1) /*fread function is used to read the contents of file. It generally takes 4 arguments: 
                                                  first argument shows the address(&std) in which the file is stored which is to be read
                                                  second argument shows the size of the file; sizeof(std)
                                                  third argument shows the number of records to be read by the function each time; 1
                                                  fourth argument shows the file open variable in which we have declared the file name and type of action; fopen("record.txt","rb+")*/
    {
        gotoxy(10, j);
        printf("%-7d%-12s%-9d%-12s%-12s", i, std.name, std.rollno, std.course, std.branch);
        i++;
        j++;
    }
    fclose(fp);
    gotoxy(10, j + 3);
    printf("Press any key to continue : ");
    getch(); /* It reads a single character from the keyboard. But it does not use any buffer,
                so the entered character is immediately returned without waiting for the enter key.*/
    menu();  /*It again calls the menu function so that the menu will again be displayed to get further tasks.*/
}

void search()
{
    FILE *fp; /*Declaring the file pointer*/
    struct student std;
    char stname[30];
    system("cls"); /*Used to clear the console*/
    gotoxy(10, 3);
    printf("Search Record:");
    gotoxy(10, 5);
    printf("Enter the name of student");
    fflush(stdin);                   /*fflush() is typically used for output stream only. 
                             Its purpose is to clear (or flush) the output buffer and move the buffered data to
                             console (in case of stdout) or disk (in case of file output stream).*/
    gets(stname);                    /*Here, we are asking for the name of student to be searched*/
    fp = fopen("record.txt", "rb+"); /* The record.txt file will be opened in Read Binary mode(rb+)*/
    if (fp == NULL)                  /*This condition will check if the file is empty*/
    {
        gotoxy(10, 6);
        printf("Error opening file");
        exit(1);
    }
    while (fread(&std, sizeof(std), 1, fp) == 1) /*fread function is used to read the contents of file. It generally takes 4 arguments: 
                                                  first argument shows the address(&std) in which the file is stored which is to be read
                                                  second argument shows the size of the file; sizeof(std)
                                                  third argument shows the number of records to be read by the function each time; 1
                                                  fourth argument shows the file open variable in which we have declared the file name and type of action; fopen("record.txt","rb+")*/
    {
        if (strcmp(stname, std.name) == 0) /*The strcmp() compares two strings which is added in its arguments. 
                                             Here, we are comparing the string which is entered by the user with all the name string in the file.
                                             As per the condition, if the string exist, it will show the user its desired details
                                             (As we have called all the data in the structure by using it as std.name).*/
        {
            gotoxy(10, 8);
            printf("Name : %s", std.name);
            gotoxy(10, 9);
            printf("Roll No. : %d", std.rollno);
            gotoxy(10, 10);
            printf("Course : %s", std.course);
            gotoxy(10, 11);
            printf("Branch : %s", std.branch);
        }
    }
    fclose(fp);
    gotoxy(10, 16);
    printf("Press any key to continue..");
    getch(); /* It reads a single character from the keyboard. But it does not use any buffer,
                so the entered character is immediately returned without waiting for the enter key.*/
    menu();  /*It again calls the menu function so that the menu will again be displayed to get further tasks.*/
}

void modify()
{
    char stname[30];
    FILE *fp; /*Declaring the file pointer*/
    struct student std;
    system("cls"); /*Used to clear the console*/
    gotoxy(10, 3);
    printf("Modify Record :");
    gotoxy(10, 5);
    printf("enter the name of student to modify :");
    fflush(stdin);                   /*fflush() is typically used for output stream only. 
                             Its purpose is to clear (or flush) the output buffer and move the buffered data to
                             console (in case of stdout) or disk (in case of file output stream).*/
    gets(stname);                    /*Here, we are asking for the name of student to be modified*/
    fp = fopen("record.txt", "rb+"); /* The record.txt file will be opened in Read Binary mode(rb+)*/
    if (fp == NULL)                  /*This condition will check if the file is empty*/
    {
        gotoxy(10, 6);
        printf("Error opening file");
        exit(1);
    }
    rewind(fp);
    fflush(stdin);                               /*fflush() is typically used for output stream only. 
                             Its purpose is to clear (or flush) the output buffer and move the buffered data to
                             console (in case of stdout) or disk (in case of file output stream).*/
    while (fread(&std, sizeof(std), 1, fp) == 1) /*fread function is used to read the contents of file. It generally takes 4 arguments: 
                                                  first argument shows the address(&std) in which the file is stored which is to be read
                                                  second argument shows the size of the file; sizeof(std)
                                                  third argument shows the number of records to be read by the function each time; 1
                                                  fourth argument shows the file open variable in which we have declared the file name and type of action; fopen("record.txt","rb+")*/
    {
        if (strcmp(stname, std.name) == 0) /*The strcmp() compares two strings which is added in its arguments. 
                                             Here, we are comparing the string which is entered by the user with all the name string in the file.
                                             As per the condition, if the string exist, it will ask the user to enter new details
                                             (As we have called all the data in the structure by using it as std.name).*/
        {
            {
                gotoxy(10, 7);
                printf("Enter name: ");
                gets(std.name);
                gotoxy(10, 8);
                printf("Enter roll no : ");
                scanf("%d", &std.rollno);
                gotoxy(10, 9);
                printf("Enter Course : ");
                fflush(stdin); /*fflush() is typically used for output stream only. 
                             Its purpose is to clear (or flush) the output buffer and move the buffered data to
                             console (in case of stdout) or disk (in case of file output stream).*/
                gets(std.course);
                gotoxy(10, 10);
                printf("Enter Branch : ");
                fflush(stdin); /*fflush() is typically used for output stream only. 
                             Its purpose is to clear (or flush) the output buffer and move the buffered data to
                             console (in case of stdout) or disk (in case of file output stream).*/
                gets(std.branch);
                fseek(fp, -sizeof(std), SEEK_CUR);
                fwrite(&std, sizeof(std), 1, fp); /*The fwrite function will write the record in the file. It takes 4 arguments:-
                                            first argument shows the address(&std) in which the file is stored and new record is to be written
                                            second argument shows the size of the file; sizeof(std)
                                            third argument shows the number of records to be written by the function each time; 1
                                            fourth argument shows the file open variable in which we have declared the file name and type of action; fopen("record.txt","ab+")*/
                break;
            }
        }
        fclose(fp);
        gotoxy(10, 16);
        printf("Press any key to continue");
        getch(); /* It reads a single character from the keyboard. But it does not use any buffer,
                so the entered character is immediately returned without waiting for the enter key.*/
        menu();  /*It again calls the menu function so that the menu will again be displayed to get further tasks.*/
    }
}

void deleterec()
{
    char stname[30];
    FILE *fp, *ft; /*Declaring the file pointer*/
    struct student std;
    system("cls"); /*Used to clear the console*/
    gotoxy(10, 3);
    printf("<--:DELETE RECORD:-->");
    gotoxy(10, 5);
    printf("Enter name of student to delete record : ");
    fflush(stdin);                   /*fflush() is typically used for output stream only. 
                             Its purpose is to clear (or flush) the output buffer and move the buffered data to
                             console (in case of stdout) or disk (in case of file output stream).*/
    gets(stname);                    /*Here, we are asking for the name of student to be deleted*/
    fp = fopen("record.txt", "rb+"); /* The record.txt file will be opened in Read Binary mode(rb+)*/
    if (fp == NULL)                  /*This condition will check if the file is empty*/
    {
        gotoxy(10, 6);
        printf("Error opening file");
        exit(1);
    }
    ft = fopen("temp.txt", "wb+"); /*Alonwith opening the main file, we'll add a temporary file(temp.txt) which is an empty file. 
                                     It has all the records of record.txt except for the record which is currently entered by the user.
                                     “w+” – Searches file. If the file exists, its contents are overwritten. 
                                     If the file doesn’t exist a new file is created. Returns NULL, if unable to open the file.*/
    if (ft == NULL)
    {
        gotoxy(10, 6);
        printf("Error opening file");
        exit(1);
    }
    while (fread(&std, sizeof(std), 1, fp) == 1) /*fread function is used to read the contents of file. It generally takes 4 arguments: 
                                                  first argument shows the address(&std) in which the file is stored which is to be read
                                                  second argument shows the size of the file; sizeof(std)
                                                  third argument shows the number of records to be read by the function each time; 1
                                                  fourth argument shows the file open variable in which we have declared the file name and type of action; fopen("record.txt","rb+")*/
    {
        if (strcmp(stname, std.name) != 0) /*The strcmp() compares two strings which is added in its arguments. 
                                             Here, we are comparing the string which is entered by the user with all the name string in the file.
                                             As per the condition, if the string name are not equal, it will write the record which is deleted from the record.txt file in temp.txt file. 
                                             (As we have called all the data in the structure by using it as std.name).*/

        {
            fwrite(&std, sizeof(std), 1, ft); /*The fwrite function will write the record in the file. It takes 4 arguments:-
                                            first argument shows the address(&std) in which the file is stored and new record is to be written
                                            second argument shows the size of the file; sizeof(std)
                                            third argument shows the number of records to be written by the function each time; 1
                                            fourth argument shows the file open variable in which we have declared the file name and write the record in it.
                                            (Here,all the record of record.txt is being entered in the temp.txt file except for the one which is being entered by the user)*/
        }
    }
    fclose(fp);
    fclose(ft);
    remove("record.txt");             /*Here, we will delete the record.txt file*/
    rename("temp.txt", "record.txt"); /*Here, we will rename our temporary filewith original file.So, now this is our original file.*/
    gotoxy(10, 10);
    printf("Press any key to continue.");
    getch(); /* It reads a single character from the keyboard. But it does not use any buffer,
                so the entered character is immediately returned without waiting for the enter key.*/
    menu();  /*It again calls the menu function so that the menu will again be displayed to get further tasks.*/
}

void gotoxy(int x, int y) /*The gotoxy() function is used to set the coordinates from where a line is to be printed on the screen. 
                            It takes two variables each for seperate x and y axis.*/
{
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}