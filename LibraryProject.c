#include <stdio.h>
#include <string.h>

//fixed array values
#define MAX_SIZE_USER_NAME 20
#define MAX_SIZE_PASSWORD 20
#define FILE_NAME  "OwnPunyatFile.bin"

//macro related to the books info
#define MAX_BOOK_NAME 40
#define MAX_AUTHOR_NAME 40
#define FILE_HEADER_SIZE  sizeof(sFileHeader)

//structure to store date
typedef struct
{
    char username[MAX_SIZE_USER_NAME];
    char password[MAX_SIZE_PASSWORD];
} sFileHeader;

typedef struct //to call in program
{
    int books_id; //declare the integer data type
    char bookName[MAX_BOOK_NAME]; //declare the character data type
    char authorName[MAX_AUTHOR_NAME]; //declare the charecter data type
    int books_pages; //declare the character data type

} s_BooksInfo;

//display message(title)
void printMessageCenter(const char* message)
{
    int len =0;
    int pos = 0;
    //calculate how many space need to print
    len = (92 - strlen(message))/2;
    printf("\t\t\t");
    for(pos =0 ; pos < len ; pos++)
    {
        //print space
        printf(" ");
    }
    //print message
    printf("%s", message);
}

void headMessage(const char *message)
{
    system("cls");
    printf("\t\t\t\t###########################################################################");
    printf("\n\t\t\t\t############                                                   ############");
    printf("\n\t\t\t\t############     Library Project in C by Punyat Tripathi       ############");
    printf("\n\t\t\t\t############     =======================================       ############");
    printf("\n\t\t\t\t############      RN: BC1901 in B.Sc. (Computer Science)       ############");
    printf("\n\t\t\t\t############     National Institute of Speech and Hearing      ############");
    printf("\n\t\t\t\t############                                                   ############");
    printf("\n\t\t\t\t###########################################################################");
    printf("\n\t\t\t\t---------------------------------------------------------------------------\n");
    printMessageCenter(message);
    printf("\n\t\t\t\t----------------------------------------------------------------------------");
}

void welcomeMessage()
{
    headMessage("www.nishlibrary.ac.in");
    printf("\n\n");
    printf("\n\t\t\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
    printf("\n\t\t\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=       ");
    printf("\n\t\t\t\t\t        =                WELCOME                    =       ");
    printf("\n\t\t\t\t\t        =                  TO                       =       ");
    printf("\n\t\t\t\t\t        =              NISH LIBRARY                 =       ");
    printf("\n\t\t\t\t\t        =               MANAGEMENT                  =       ");
    printf("\n\t\t\t\t\t        =                 SYSTEM                    =       ");
    printf("\n\t\t\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=       ");
    printf("\n");
    printf("\n\t\t\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
    printf("\n\n\n\t\t\t\t\t\tEnter any key to continue.....");
    getch();
}

int isNameValid(const char *name)
{
    int validName = 1;
    int len = 0;
    int index = 0;
    len = strlen(name);
    for(index =0; index < len ; ++index)
    {
        if(!(isalpha(name[index])) && (name[index] != '\n') && (name[index] != ' '))
        {
            validName = 0;
            break;
        }
    }
    return validName;
}

//store default username and password in the file
void init()
{
    FILE *fp = NULL;
    int status = 0;
    const char defaultUsername[] ="punyat.cs19\n";
    const char defaultPassword[] ="12345\n";
    sFileHeader fileHeaderInfo = {0};
    status = isFileExists(FILE_NAME);
    if(!status)
    {
        //create the binary file
        fp = fopen(FILE_NAME,"wb");
        if(fp != NULL)
        {
            //Copy default username and password
            strncpy(fileHeaderInfo.username, defaultUsername, sizeof(defaultUsername));
            strncpy(fileHeaderInfo.password, defaultPassword, sizeof(defaultPassword));
            fwrite(&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
            fclose(fp);
        }
    }
}

//login
void login()
{
    unsigned char userName[MAX_SIZE_USER_NAME] = {0};
    unsigned char password[MAX_SIZE_PASSWORD] = {0};
    int i=5, stop=0;
    sFileHeader fileHeaderInfo = {0};
    FILE *fp = NULL;
    headMessage("NISH Library Login");
    fp = fopen(FILE_NAME,"rb");
    if(fp == NULL)
    {
        printf("\t\tFile is not opened\n");
        exit(1);
    }
    fread (&fileHeaderInfo, FILE_HEADER_SIZE, 1, fp);
    fclose(fp);
    
    printf("\n\t\t\t(Note: Invalid username or password. You have 5 attempts before your account is locked for a day)\n");

    //while loop to input a username and to check whether it is correct
    while (i>stop)
    {
        printf("\n\t\t\t\t\t\tEnter your username: ");
        fgets(userName, MAX_SIZE_USER_NAME, stdin);
        
        if (strcmp(userName, fileHeaderInfo.username)!=0)     //string compare the username
        {
            printf("\t\t\t\t\t\tUser doesn't exist (Attempt left %d)\n", i-1);
            i--;
        }
        else
        {
            stop=i;
        }
    }
    //stop if the attempt run out
    if (stop==0)
    {
        printf("\n\t\t\t\t\t\t\tAccess Denied...!");
        exit(0);
    }

    /*reset variables which are same above
    while loop to input a passoword and to check whether it is correct*/ 
    stop = 0;
    while (i>stop)
    {
        printf("\t\t\t\t\t\tEnter your password: ");
        fgets(password, MAX_SIZE_PASSWORD, stdin);
        if(strcmp(password, fileHeaderInfo.password)!=0)
        {
            printf("\n\t\t\t\t\t\tIncorrect Passowrd (Attempt left %d)\n", i-1);
            i--;
        }
        else
        {
            printf("\n\t\t\t\t\t\t\tLoading....");
            sleep(1);
            printf("\n\n\t\t\t\t\t\t\tWelcome to NISH Library");
            printf("\n\t\t\t\t\t\t\tLogin Successful...!");
            sleep(3);
            stop=i;
            menu();
        }
    }
    //stop if the attempt run out
    if (stop==0)
    {
        printf("\n\t\t\t\t\t\t\tAccess Denied...!");
        exit(0);
    }
    fclose(fp);
}

//menu
void menu()
{
    int choice = 0;
    do
    {
        headMessage("MAIN MENU");
        //show list of menu in library in C
        printf("\n\n\n\t\t\t\t\t1. Issue Books");
        printf("\n\t\t\t\t\t2. Display List of books");
        printf("\n\t\t\t\t\t3. Search Subject of Books");
        printf("\n\t\t\t\t\t4. Search Auther of Books");
        printf("\n\t\t\t\t\t5. Return Books");
        printf("\n\t\t\t\t\t6. Update Username & Password");
        printf("\n\t\t\t\t\t0. Exit");
        printf("\n\n\n\t\t\t\t\tEnter choice => ");
        scanf("%d",&choice);
        
        //check if user gives to input value
        switch(choice)
        {
        case 1:
            issueBookInDataBase();
            break;
        case 2:
            viewBooks();
            break;
        case 3:
            searchBooks();
            break;
        case 4:
            searchAuthor();
            break;
        case 5:
            returnBooks();
            break;
        case 6:
            updateUser_Passowrd();
            break;
        case 0:
            printf("\n\n\t\t\t\t\t\t    ___________________________________");
            printf("\n\t\t\t\t\t\t   |                                   |");
            printf("\n\t\t\t\t\t\t   |                                   |");
            printf("\n\t\t\t\t\t\t   |            Thank you!!!           |");
            printf("\n\t\t\t\t\t\t   |                                   |");
            printf("\n\t\t\t\t\t\t   |___________________________________|\n\n\n\n\n");
            exit(1);
            break;
        default:
            printf("\n\n\t\t\t\t\t\t\tINVALID INPUT!!! Try again...");
            sleep(3);
        }                                               //switch ended
    } while(choice!=0);                                 //loop ended
}

//add books in list
void issueBookInDataBase()
{
    int days;
    s_BooksInfo issueBookInfoInDataBase = {0};
    FILE *fp = NULL;
    int status = 0;
    fp = fopen(FILE_NAME,"ab+");
    if(fp == NULL)
    {
        printf("\t\t\t\tFile is not opened\n");
        exit(1);
    }
    headMessage("ISSUE BOOKS");
    printf("\n\t\t\t\t  ENTER YOUR DETAILS BELOW:");
    printf("\n\t\t\t\t---------------------------------------------------------------------------\n");

    //prompt and input from users and store(save) in the file
    printf("\n\t\t\t\t\tEnter Book ID                   : ");
    fflush(stdin);
    scanf("%d", &issueBookInfoInDataBase.books_id);
        
    do
    {
        //prompt and input from users and store(save) in the file
        printf("\t\t\t\t\tBook Name                       : ");
        fflush(stdin);
        fgets(issueBookInfoInDataBase.bookName, MAX_BOOK_NAME, stdin);
        status = isNameValid(issueBookInfoInDataBase.bookName);
        if (!status)
        {
            printf("\n\t\t\t\t\tName contain invalid character. Please enter again.\n");
        }
    } while(!status);

    do
    {
        //prompt and input from users and store(save) in the file
        printf("\t\t\t\t\tEnter Author Name               : ");
        fflush(stdin);
        fgets(issueBookInfoInDataBase.authorName, MAX_AUTHOR_NAME, stdin);
        status = isNameValid(issueBookInfoInDataBase.authorName);
        if (!status)
        {
            printf("\n\t\t\t\t\tName contain invalid character. Please enter again.");
        }
    } while(!status);

    //prompt and input from users and store(save) in the file
    printf("\t\t\t\t\tEnter Book Number of Pages      : ");
    fflush(stdin);
    scanf("%d", &issueBookInfoInDataBase.books_pages);

    printf("\n\t\t\t\t\t-------------------------------------------------------");
    printf("\n\t\t\t\t\t\t   New Record Book Successful...");
    sleep(3);

    fwrite(&issueBookInfoInDataBase, sizeof(issueBookInfoInDataBase), 1, fp);
    fclose(fp);
}

//view books function
void viewBooks()
{
    int found = 0;
    char bookName[MAX_BOOK_NAME] = {0};
    s_BooksInfo issueBookInfoInDataBase = {0};
    FILE *fp = NULL;
    int status = 0;
    int countBk = 1;
    int i, j;
    char copyalphabeticalorderBooks[100];
    headMessage("VIEW BOOKS DETAILS");
    fp = fopen(FILE_NAME,"rb");
    if(fp == NULL)
    {
        printf("\t\tFile is not opened\n");
        exit(1);
    }
    if (fseek(fp,FILE_HEADER_SIZE,SEEK_SET) != 0)
    {
        fclose(fp);
        printf("\t\tFacing issue while reading file\n");
        exit(1);
    }

    /*all books in alphabetical order (it isn't working because memories is confused where)
    for(i=0 ; i<countBk ; i++)
    {
        for(j=i+1 ; j<countBk ;j++)
        {
            if(strcmp(bookName[i], bookName[j])>0)
            {
                strcpy(copyalphabeticalorderBooks, issueBookInfoInDataBase.bookName[i]);
                strcpy(issueBookInfoInDataBase.bookName[i], issueBookInfoInDataBase.bookName[j]);
                strcpy(issueBookInfoInDataBase.bookName[j], copyalphabeticalorderBooks);
            }
        }
    } */

    //while loop to prompt and check if input from users and display output in stored file
    while (fread (&issueBookInfoInDataBase, sizeof(issueBookInfoInDataBase), 1, fp))
    {
        printf("\n\n\t\t\t\t\tBook Count = %d", countBk);
        printf("\n\t\t\t\t\t---------------\n");
        printf("\t\t\t\t\tBook ID = %u", issueBookInfoInDataBase.books_id);
        printf("\n\t\t\t\t\tBook Name = %s", issueBookInfoInDataBase.bookName);
        printf("\t\t\t\t\tBook Author Name = %s", issueBookInfoInDataBase.authorName);
        printf("\t\t\t\t\tBook Page numbers = %d", issueBookInfoInDataBase.books_pages);
        found = 1;
        ++countBk;
    }
    fclose(fp);
    if(!found)
    {
        printf("\n\t\t\t\t\tNo Record");
    }
    printf("\n\n\t\t\t\t\tPress any key to go to main menu.....");
    fflush(stdin);
    getchar();
}

//search books
void searchBooks()
{
    int found = 0;
    char bookName[MAX_BOOK_NAME] = {0};
    s_BooksInfo issueBookInfoInDataBase = {0};
    FILE *fp = NULL;
    int status = 0;
    fp = fopen(FILE_NAME,"rb");
    if(fp == NULL)
    {
        printf("\n\t\t\t\t\tFile is not opened\n");
        exit(1);
    }
    headMessage("SEARCH BOOKS");
    //put the control on books detail
    if (fseek(fp,FILE_HEADER_SIZE,SEEK_SET) != 0)
    {
        fclose(fp);
        printf("\n\t\t\t\t\tFacing issue while reading file\n");
        exit(1);
    }

    //prompt and input books name from users
    printf("\n\n\t\t\t\t\tEnter Book Name to search: ");
    fflush(stdin);
    fgets(bookName,MAX_BOOK_NAME,stdin);
    while (fread (&issueBookInfoInDataBase, sizeof(issueBookInfoInDataBase), 1, fp))
    {
        if(!strcmp(issueBookInfoInDataBase.bookName, bookName))
        {
            found = 1;
            break;
        }
    }

    //check if input from users and display output from stored file
    if(found)
    {
        printf("\n\t\t\t\t\tBook ID = %d\n", issueBookInfoInDataBase.books_id);
        printf("\t\t\t\t\tBook Name = %s", issueBookInfoInDataBase.bookName);
        printf("\t\t\t\t\tBook Author Name = %s", issueBookInfoInDataBase.authorName);
        printf("\t\t\t\t\tBook Pages Numbers = %d", issueBookInfoInDataBase.books_pages);
    }
    else
    {
        printf("\n\t\t\t\t\tNo Record");
    }
    fclose(fp);
    printf("\n\n\n\t\t\t\t\tPress any key to go to main menu.....");
    getchar();
}

// search author
void searchAuthor()
{
    int found = 0;
    char authorName[MAX_AUTHOR_NAME] = {0};
    s_BooksInfo issueBookInfoInDataBase = {0};
    FILE *fp = NULL;
    int status = 0;
    fp = fopen(FILE_NAME,"rb");
    if(fp == NULL)
    {
        printf("\n\t\t\t\t\tFile is not opened\n");
        exit(1);
    }
    headMessage("SEARCH AUTHOR");
    //put the control on books detail
    if (fseek(fp,FILE_HEADER_SIZE,SEEK_SET) != 0)
    {
        fclose(fp);
        printf("\n\t\t\t\t\tFacing issue while reading file\n");
        exit(1);
    }

    //prompt and input authors name from users
    printf("\n\n\t\t\t\t\tEnter Author Name to search: ");
    fflush(stdin);
    fgets(authorName,MAX_BOOK_NAME,stdin);
    while (fread (&issueBookInfoInDataBase, sizeof(issueBookInfoInDataBase), 1, fp))
    {
        if(!strcmp(issueBookInfoInDataBase.authorName, authorName))
        {
            found = 1;
            break;
        }
    }

    //check if input from users and display output from stored file
    if(found)
    {
        printf("\n\t\t\t\t\tBook ID = %u\n", issueBookInfoInDataBase.books_id);
        printf("\t\t\t\t\tBook Name = %s", issueBookInfoInDataBase.bookName);
        printf("\t\t\t\t\tBook Author Name = %s", issueBookInfoInDataBase.authorName);
        printf("\t\t\t\t\tBook Pages Numbers = %d", issueBookInfoInDataBase.books_pages);
    }
    else
    {
        printf("\n\t\t\t\t\tNo Record");
    }
    fclose(fp);
    printf("\n\n\n\t\t\t\t\tPress any key to go to main menu.....");
    getchar();
}

//return books
void returnBooks()
{
    int found = 0;
    int bookDelete = 0;
    sFileHeader fileHeaderInfo = {0};
    char bookName[MAX_BOOK_NAME] = {0};
    s_BooksInfo issueBookInfoInDataBase = {0};
    FILE *fp = NULL;
    FILE *tmpFp = NULL;
    int status = 0;
    headMessage("RETURN BOOKS");
    fp = fopen(FILE_NAME,"rb");
    if(fp == NULL)
    {
        printf("\t\tFile is not opened\n");
        exit(1);
    }
    tmpFp = fopen("tmp.bin","wb");
    if(tmpFp == NULL)
    {
        fclose(fp);
        printf("\t\tFile is not opened\n");
        exit(1);
    }
    fread (&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
    fwrite(&fileHeaderInfo,FILE_HEADER_SIZE, 1, tmpFp);

    //prompt and input books ID from users
    printf("\n\t\t\t\t\tEnter Book ID NO. for Return: ");
    scanf("%d", &bookDelete);
    while (fread (&issueBookInfoInDataBase, sizeof(issueBookInfoInDataBase), 1, fp))
    {
        //check if the user inputs given book ID add count in variable (found)
        if(issueBookInfoInDataBase.books_id != bookDelete)
        {
            fwrite(&issueBookInfoInDataBase,sizeof(issueBookInfoInDataBase), 1, tmpFp);
        }
        else
        {
            found = 1;
        }
    }
    
    //also check if the user inputs given book ID again and display output
    (found)? printf("\n\t\t\t\t\t----------------------------------------------------\n\t\t\t\t\t\tRecord returned book successfully....."):
    printf("\n\t\t\t\t\t-------------------------------------\n\t\t\t\t\t\tRecord not found...");
    sleep(3);
    fclose(fp);
    fclose(tmpFp);
    remove(FILE_NAME);
    rename("tmp.bin",FILE_NAME);
}

//update username & password
void updateUser_Passowrd()
{
    sFileHeader fileHeaderInfo = {0};
    FILE *fp = NULL;
    unsigned char userName[MAX_SIZE_USER_NAME] = {0};
    unsigned char password[MAX_SIZE_PASSWORD] = {0};
    headMessage("UPADTE USERNAME & PASSWORD");
    fp = fopen(FILE_NAME,"rb+");
    if(fp == NULL)
    {
        printf("\t\tFile is not opened\n");
        exit(1);
    }
    fread (&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
    if (fseek(fp, 0, SEEK_SET) != 0)
    {
        fclose(fp);
        printf("\n\t\t\t\t\tFacing issue while updating password\n");
        exit(1);
    }

    //make new username instead of old username
    printf("\n\n\t\t\t\t\tNew Username: ");
    fflush(stdin);
    fgets(userName, MAX_SIZE_USER_NAME, stdin);

    //make new password instead of old password
    printf("\n\n\t\t\t\t\tNew Password: ");
    fflush(stdin);
    fgets(password, MAX_SIZE_PASSWORD, stdin);

    //copy new username and passowrd in the file
    strncpy(fileHeaderInfo.username, userName, sizeof(userName));
    strncpy(fileHeaderInfo.password, password, sizeof(password));
    fwrite(&fileHeaderInfo, FILE_HEADER_SIZE, 1, fp);
    fclose(fp);

    printf("\n\t\t\t\t\t-------------------------------------------------------");
    printf("\n\t\t\t\t\t      Your Password has been changed successfully");
    printf("\n\n\t\t\t\t\t                   Login Again:");
    fflush(stdin);
    getchar();
    exit(1);
}

//run main function
int main()
{
    init();
    welcomeMessage();
    login();
    return 0;
}

//save file from user's inputs
int isFileExists(const char *path)
{
    // Try to open file
    FILE *fp = fopen(path, "rb");
    int status = 0;
    // If file does not exists
    if (fp != NULL)
    {
        status = 1;
        // File exists hence close file
        fclose(fp);
    }
    return status;
}