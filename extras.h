static void processing();
int validate(char ch);
int admin_login();

const char *login = "admin";

int admin_login()
{
    int check_u;      //checks username andentered by user, should be 0
    int check_p;
    char c_username;
    char x_password;
    check_u = 0;
    check_p = 0;
    printf("LOGIN: ");
    fflush(stdin);
    c_username = getchar();
    check_u = validate(c_username);
    printf("\nPASSWORD: ");
    fflush(stdin);
    x_password = getchar();
    check_p = validate(x_password);
    if(check_u == 0 && check_p == 0)
    {
        processing();
        system("cls");
        return 0;
    }//end if
    else
    {
        processing();
        system("cls");
        //printf("\nINVALID LOGIN OR PASSWORD.");
        return 1;
    }//end else
}//end func

int validate(char ch)     //ch = character from user input
{
    char x;
    int i;
    /*COMPARE USER ENTERED LOGIN WITH STORED USERNAME */
    for(i =0 ; i < strlen(login); i++)
    {
        x = login[i];
        if((int)ch != (int)x/*cmp != 0*/)
        {
            return 1;
        }//end if
        ch = getchar();
    }//end for
    return 0;
}//end func

static void processing()
{
    int i;
    system("cls");
    printf("\nProcessing ");
    for(i = 0; i < 3; i++)
    {
        Sleep(700);
        printf(".");
    }//end for
}//end func
