#define MAX 60

typedef struct courses
{
    char cname[MAX];
    int cnum;
    struct courses *next;
}course;


typedef struct student
{
    char name[MAX];
    char usrName[MAX];
    char pswd[MAX];
    int stdNum;
    struct student *next;
    struct courses *down;
}student;


extern student *s_head;
extern student *s_tmp;
extern student *s_last;

static int check_password(struct student *s_ptr, char *s_pass);

void studentListHead()
{
    s_head = realloc(NULL, sizeof(struct student));
    if(s_head == NULL)
    {
        printf("MEMORY ALLOCATION FAILED\n");
        exit(1);
    }//end if
    strcpy(s_head ->name, " ");
    s_head->next = NULL;
    s_tmp = s_head;
    s_last = s_head;
}//end func

/*PRINT LIST OF STUDENTS***************************/
void printStudent(student *ptr)
{
    ptr = s_head;
    FILE *fp;
    fp = fopen("StudentList.txt", "a");
    if(fp == NULL)
    {
        fprintf(stderr, "Can't write to file file\n");
        //exit(1);
    }//end if
     for(ptr = s_head -> next; ptr != NULL; ptr = ptr -> next)
     {
         fprintf(fp, "%s\n", ptr->name);
     }//end for
     fclose(fp);
     ptr = s_head;
    if(ptr ->next == NULL)
    {
        printf("LIST IS EMPTY");
       // exit(1);
    }
    printf("\nLIST:\n");
    for(ptr = s_head -> next; ptr != NULL; ptr = ptr -> next)
    {
        printf("%s\t%d\n",ptr->name, ptr->stdNum);
    }//end for
}//end func
/* ***********************************************/

/*GENERATE STUDNET ID******************************/
int std_id_gen()
{
    int std_id;
    srand ( time(NULL) );
    std_id = (rand() % 1000000) + 1;
    return std_id;
}//end func
/* ***********************************************/

/*GETTING ID OF SPECIFIC STUDENT *****************/
void getID(char *std_name)
{
    s_tmp = s_head;
    for(s_tmp = s_head->next; s_tmp != NULL; s_tmp = s_tmp->next)
    {
        if(s_tmp->name == std_name)
        {
            printf("%s ID: %d",s_tmp->name, s_tmp->stdNum);
        }//end if
        else
        {
            printf("%s ID not found", s_tmp->name);
        }//end else
    }//end for
}//end func
/* ***********************************************/

/*MAIN MENU DISPLAY *************************************/
void mainMenu()
{
    printf("\n---------------------------------------------------------\n");
    printf("PRESS 1 TO ADD STUDENTS\nPRESS 2 TO DISPLAY LIST OF STUDENTS\nPRESS 3 TO SEARCH FOR A STUDENT\nPRESS 4 TO GO TO COURSES MENU\nPRESS 5 FOR STUDENT LOGIN\nPRESS 6 TO EXIT\n");
    printf("--------------------------------------------------------------\n");
}//end func
/* ***********************************************/

/*USER CHOICES OPTION ****************************/
int option()
{
    int choice;
    printf("ENTER CHOICE: ");
    fflush(stdin);
    scanf("%d", &choice);
    system("cls");
    switch(choice)
    {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        return choice;

        default:
        printf("INVALID OPTION.\n");
        break;
    }//end
    return choice;
}//end func
/* ***********************************************/

/*SEARCH METHOD CONFIRMS THAT A NAME OF STUDENT GIVEN EXIST IN LIST */
int search(student *ptr, char *p)
{
    ptr = s_head;
    int cmp;
    for(ptr = s_head->next; ptr != NULL; ptr = ptr->next)
    {
        cmp = strcmp(ptr->name, p);
        if(cmp == 0)
        {
            return cmp;     //if cmp == 0 name in list
        }//end if
    }//end for
    return 1;
}//end func

void write_to_file(struct student *p, FILE *ptr)    //adds new students to a text file
{
    if(p == NULL)
    {
        fprintf(stderr, "Can't write to file file\n");
        exit(1);
    }//end if
    fprintf(ptr,"%10s\t", p->name);
    fprintf(ptr,"%10d\t", p->stdNum);
    fprintf(ptr,"%10s\t", p->usrName);
    fprintf(ptr,"%10s\t", p->pswd);
    fprintf(ptr, "\n");
    fclose(ptr);
}//end method

/*THE FOLLOWING FUNCTION CHECKS IF THE USERNAME AND PASSWORD ENTERED ARE VALID
  THIS USES A STATIC METHOD FOR CHECKING IF THE PASSWORD IS VALID
  *
int user_name_exist(struct student *ptr, char *p_username, char *p_password)
{
    int cmp_username;
    ptr = s_head;
    for(ptr = s_head->next; ptr != NULL; ptr = ptr->next)
    {
        cmp_username = strcmp(p_username, ptr->usrName);
        if(cmp_username == 0)   //means user name exists
        {
            int password_check;
            password_check = check_password(p_password, ptr->pswd);
            if(check_password != 0)
            {
                return 1;
            }//end if
        }//end if
    }//end for
    return 0;
}//end func

static int check_password(struct student *s_ptr, char *s_pass)
{
    int check;
    check = strcmp(s_pass, s_ptr->pswd);
    if(check ==0)
    {
        return 0;
    }//end if
    return 1;
}//end func
*/

void write_to_file_log(char *ptr)
{
    FILE *fp;
    fp = fopen("file_log.txt", "a");
    if(fp == NULL)
    {
        fprintf(stderr, "FILE DOES NOT EXIST OR DAMAGED.");
        exit(1);
    }//end if
    time_t t_ime;
    time(&t_ime);
    fprintf(fp,"%s\t%35s\n",ptr, ctime(&t_ime));
    fclose(fp);
}//end func


int check_username(struct student *sp, char *u_name)
{
    int cmp_username;
    sp = s_head;
    for(sp = s_head->next; sp != NULL; sp = sp->next)
    {
        cmp_username = strcmp(u_name, sp->usrName);
        if(cmp_username == 0)   //means user name exists
        {
            return 0;
        }//end if
    }//end for
    return 1;
}//end func

int check_password(struct student *sp, char *password)
{
    int check;
    check = strcmp(password, sp->pswd);
    if(check == 0)
    {
        return 0;
    }//end if
    return 1;
}//end func
