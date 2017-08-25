#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

#include "functions.h"
#include "coursesFunctions.h"
#include "student.h"
#include "extras.h"

student *s_head;
student *s_tmp;
student *s_last;

course *c_head;
course *c_tmp;
course *c_last;

/*FUNCTION CALLS ON STUDENT */
void studentListHead();
void printStudent();
int std_id_gen();       //need to check
void getID(char *std_name);     //need to check
void mainMenu();
int option();
void write_to_file(struct student *p, FILE *ptr);
//int user_name_exist(struct student *ptr, char *p_username, char *p_password);
int check_username(struct student *sp, char *u_name);
int check_password(struct student *sp, char *password);
int student_option();
void studentMenu();
/* **********************************************/

/*FUNCTION CALLS ON COURSES */
void coursesMenu();
void display(FILE *p);
void print_student_courses(struct courses *cp);
/* **************************/


int main()
{
    int s_num;  //number of students to enter
    int opt;    //option from menu
    int c_opt;   //option for courses menu
    int s_opt;  //option chossen after student login
    extern char stdName[MAX];  //used for entering student names and searching student names
    extern char stdUsrName[MAX];   //used for storing username of student
    extern char stdPsd[MAX];       //used to store password
    FILE *fp;               //used to openn 2 different files to read
    extern FILE *fwp;              //used to write student info on file
    extern student *p;     //students
    extern course *c;      //courses
    extern char course_name[MAX];      //course name = 4 letters of dept
    extern int course_code;            //4 digits, i.e 1009 = course code
    int check_login;

    system("COLOR F0");
    check_login = admin_login();
    if(check_login == 1)
    {
        printf("\nINVALID LOGIN OR PASSWORD.");
        exit(1);
    }//end if
    else
    {
        studentListHead();
        coursesListHead();
        mainMenu();
        opt = option();
        int i;
        for(i = 0; opt != 6; i++)       //main for
        {
            if(opt == 1)
            {
                printf("ENTER NUMBER OF STUDENTS: ");
                fflush(stdin);
                scanf("%d", &s_num);
                int j;
                for(j = 0; j < s_num; j++)
                {
                    add_student(p);
                    write_to_file(p, fwp);
                }//end for
            }//end if
            else if(opt == 2)
            {
                s_tmp = s_head->next;
                printStudent(s_tmp);
                if(s_tmp == NULL)
                {
                    fp = fopen("StudentList.txt", "r");
                    if(fp == NULL)
                    {
                        fprintf(stderr, "Can't write to file file\n");
                        //exit(1);
                    }//end if
                    char f_buff[MAX];
                    fgets(f_buff, MAX, fp);
                    printf("-----------------------------\nSTUDENTS ON FILE\n");
                    while(!feof(fp))
                    {
                        printf("%s", f_buff);
                        fgets(f_buff, MAX, fp);
                    }//end while
                    fclose(fp);
                }//end if
            }//end else if
            else if(opt == 3)
            {
                printf("ENTER NAME OF STUDENT TO SEARCH: ");
                fflush(stdin);
                scanf( "%[^\n]s",stdName);
                int i;
                i = search(s_tmp, stdName);
                if(i == 0)
                {
                    s_tmp = s_head;
                    int compare;
                    for(s_tmp = s_head->next; s_tmp != NULL; s_tmp = s_tmp ->next)
                    {
                        compare = strcmp(s_tmp->name, stdName);
                        if(compare == 0)
                        {
                            printf("%s\n", s_tmp->name);
                        }//end if
                    }//end for
                }//end if
                else
                {
                    printf("STUDENT NOT FOUND\n");
                }//end else
            }//end elseif opt==3
            /*COURSES MENU INSIDE opt==4 */
            else if(opt == 4)
            {
               // fp = fopen("courseFile.txt", "r");
                coursesMenu();
                c_opt = option();
                int k;
                for(k = 0; c_opt != 5; k++)
                {
                    if(c_opt == 1)
                    {
                        int d_opt;
                        sub_menu();
                        d_opt = dept_option();
                        if(d_opt == 1)
                        {
                            fp = fopen("EECS.txt", "r");
                            display(fp);
                        }//end if
                        else if(d_opt == 2)
                        {
                            fp = fopen("MATH.txt", "r");
                            display(fp);
                        }//end else if
                    }//end if
                    else if(c_opt == 4)
                    {
                        break;
                    }
                coursesMenu();
                c_opt = option();
                }//end for in main menu opt==4
            }//end else if opt==4
            if(opt == 5)
            {
                printf("----------STUDENT LOGIN---------------\n\n");
                printf("Enter Username: ");
                fflush(stdin);
                scanf("%[^\n]s", stdUsrName);
                int does_usrname_exsist;    //if 0,means exsist else not exsist
                does_usrname_exsist = check_username(p, stdUsrName);
                    /*MASKING PASWORD */
                    int ch;
                    int i;
                    int j;
                    j = 0;
                    int check;
                    printf("Enter password: ");
                    fflush(stdout);
                    //ch = getchar();
                    for(i = 0;(ch = getch()) != EOF
                     && ch != '\n'
                     && ch != '\r'
                     && i < sizeof(stdPsd) - 1; i++)
                    {
                        if (ch == '\b' && j > 0)
                        {
                            printf("\b \b");
                            fflush(stdout);
                            j--;
                            stdPsd[j] = '\0';
                        }//end if
                        check = isalnum(ch);
                        if (check != 0)
                        {
                            printf("%c", '*');
                            stdPsd[j++] = ch;
                        }//end if
                        // ch = getchar();
                    }//end masking for
                    stdPsd[i] = '\0';
                    int validate_password;
                    validate_password = check_password(p, stdPsd);
                    if(does_usrname_exsist == 0 && validate_password == 0)
                    {
                        write_to_file_log(stdUsrName);
                        studentMenu();
                        s_opt = student_option();
                        int l;
                        for(l = 0; s_opt != 0; l++)
                        {
                            if(s_opt == 1)
                            {
                                printf("Enter number of courses to add: ");
                                int num_courses;
                                scanf("%d", &num_courses);
                                int k;
                                for(k = 0; k < num_courses; k++)
                                {
                                    add_course(c);
                                }//end for add courses
                            }//end if
                           // print_student_courses(c);
                            studentMenu();
                            s_opt = student_option();
                        }//end for student option menu
                    }//end ifhd
                    else
                    {
                        printf("Invalid username or password.");
                    }//end else
            }//end if main menu opt == 5
            mainMenu();
            opt = option();
        }//end main for
    }//end else

    /* FREE-ing ALL POINTERS AND ENDING PROGRAM*/
    free(s_head);
    free(c_head);
    free(s_tmp);
    free(s_last);
    if(p != NULL)
    {
        free(p);
    }//end if
    //free(p);
    free(c_tmp);
    free(c_last);
    free(c);
    system("PAUSE");
    return 0;
}//end main
