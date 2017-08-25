char stdName[MAX];  //used for entering student names and searching student names
char stdUsrName[MAX];   //used for storing username of student
char stdPsd[MAX];
FILE *fwp;
student *p;     //students
void studentMenu()
{
    printf("\n---------------------------------------------------------\n");
    printf("PRESS 1 TO ADD COURSE\nPRESS 0 TO GO TO MAIN MENU\n");
    printf("--------------------------------------------------------------\n");
}//end func
/* ***********************************************/

/*USER CHOICES OPTION ****************************/
int student_option()
{
    int choice;
    printf("ENTER CHOICE: ");
    fflush(stdin);
    scanf("%d", &choice);
    system("cls");
    switch(choice)
    {
        case 1:
        case 0:
        return choice;

        default:
        printf("INVALID OPTION.\n");
        break;
    }//end
    return choice;
}//end func
/* ***********************************************/
void add_student(struct student *p)
{
                p = realloc(NULL, sizeof(struct student));
                if(p == NULL)
                {
                    printf("MEMORY ALLOCATION FAILED\n");
                    exit(1);
                }//end if

                printf("Student Name: ");
                fflush(stdin);
                scanf("%[^\n]s",stdName);
                strcpy(p->name, stdName);

                printf("Create Username: ");
                fflush(stdin);
                scanf("%[^\n]s", stdUsrName);
                strcpy(p->usrName, stdUsrName);

                /*MASKING PASWORD */
                int ch;
                int i;
                int j;
                j = 0;
                int check;
                printf("Create password: ");
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
                //printf("%s\n",stdPsd); //DEBUGGING STATEMENT MUST REMOVE
                strcpy(p->pswd, stdPsd);
                /*MSKING FINISH */

                p->stdNum = std_id_gen();
                p->next = NULL;
                p->down = c_head;
                s_last->next = p;
                s_last = p;
                fwp = fopen("StudentInfo.txt", "a");
                write_to_file(p, fwp);
}//end func
