extern course *c_head;
extern course *c_tmp;
extern course *c_last;

char course_name[MAX];      //course name = 4 letters of dept
int course_code;            //4 digits, i.e 1009 = course code
extern student *p;     //students
course *c;      //courses
#define F_MAX 100
void coursesListHead()
{
    c_head = realloc(NULL, sizeof(struct courses));
    if(c_head == NULL)
    {
        printf("MEMORY ALLOCATION FAILED\n");
        exit(1);
    }//end if
    strcpy(c_head ->cname, " ");
    c_head->cnum = 0;
    c_head->next = NULL;
    c_tmp = c_head;
    c_last = c_head;

    s_head->down = c_head;
}//end func


/*COURSES MENU DISPLAYED (READ FROM A FILE) */
void coursesMenu()
{
    printf("---------------------------------------------------------\n");
    printf("PRESS 1 TO DISPLAY LIST OF COURSES OFFERED\nPRESS 2 TO SEARCH FOR A COURSE\nPRESS 4 TO GO TO MAIN MENU\n");
    printf("--------------------------------------------------------------\n");
}//end func
/* ******************************************/

void display(FILE *p)
{
    char file_contents[F_MAX];
    if (p == NULL)
    {
      fprintf(stderr, "Can't open input file courseFile.txt!\n");
      exit(1);
    }//end if

    /*OPEN AND DISPLAYING A FILE */
    fgets(file_contents, F_MAX, p);
    int i;
    for(i = 0; !feof(p); i++)
    {
        printf("%s", file_contents);
        fgets(file_contents, F_MAX, p);
    }
    fclose(p);
    /* *****************************/
}//end func

void sub_menu()
{
    printf("---------------------------------------------------------\n");
    printf("TYPE: \tEECS FOR Computer Science & Engineering\n\tARB FOR Arabic\n\tMATH FOR Mathematics and Statistics\n");
    printf("--------------------------------------------------------------\n");
}//end func

int dept_option()
{
    char choice[5];
    printf("ENTER DEPARTMENT: ");
    fflush(stdin);
    //scanf("%d", &choice);
    fgets(choice, 5, stdin);
    system("cls");

    if( (strcmp(choice, "EECS")) == 0 || (strcmp(choice, "eecs") == 0) )
    {
        return 1;
    }//end if
    else if( (strcmp(choice, "MATH")) == 0 || (strcmp(choice, "math")) == 0 )
    {
        return 2;
    }//end else if
    else
    {
        return 0;
    }//end else
}//end func

void print_student_courses(struct courses *cp)
{
    cp = c_head; //ptr = cp
    if(cp->next == NULL)
    {
        printf("YOU DID NOT ADD ANY COURSE.");
       // exit(1);
    }
    printf("\nCOURSES:\n");
    for(cp = c_head -> next; cp != NULL; cp = cp -> next)
    {
        printf("%s\t%d\n",cp->cname, cp->cnum);
    }//end for
}//end func

void add_course(struct courses *c_ptr)
{
    c = realloc(NULL, sizeof(struct courses));
    if(c == NULL)
    {
        printf("MEMORY ALLOCATION FAILED\n");
        exit(1);
    }//end if
    printf("Enter 4 Letter Department Name: ");
    fflush(stdin);
    scanf("%[^\n]s", course_name);
    strcpy(c->cname, course_name);

    printf("Enter course code: ");
    fflush(stdin);
    scanf("%d", &course_code);
    c->cnum = course_code;
    c->next = NULL;
    p->down = c;
    c_last->next = c;
    c_last = c;
}

/*
void add_course(course *c_p, int num_courses)   //C_p = courses pointer which = c_head, num_courses = how many courses person wants to add
{
    char course_name[MAX];
    int course_code;
    course *course_p;
    int i;
    course_p = realloc(NULL, sizeof(struct courses));
    if(course_p == NULL)
    {
        printf("MEMORY ALLOCATION FAILED\n");
        exit(1);
    }//end if
    c_tmp = course_p;
    for(i = 0; i < num_courses; i++)
    {
        printf("Enter 4 Letter Department Name: ");
        fflush(stdin);
        scanf("%[^\n]s", course_name);
        strcmp(course_p->cname, course_name);

        printf("Enter course code: ");
        fflush(stdin);
        scanf("%d", &course_code);
        course_p->cnum = course_code;

        course_p->next = NULL;
        c_p = course_p;
        c_last = course_p;
        c_last->next = NULL;
    }
}//end func
*/
