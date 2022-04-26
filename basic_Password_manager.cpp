/*
 *SIMPLE PASSWORD MANAGER
 *Basic version of personal password manager ¯\_(ツ)_/¯
 *The PersonalPasswordManager project is discontinued temporarily. Because after learning the C++ advance OOPS and file I/O. The project will be continued.
 */

/**
 *author: Suraj Kumar Giri.
 *Date: 08-04-2022
 *Time: 20:31:01
 */

/*
 * only for website.
 *access password to access (single user only)
 *save all data in block letter except url
 *no advanced configuration of website checking while retriving or adding info
 *only basic work will be performed
 *no domain check, url (https/www/https etc) will be checked
 **user input
 *website name
 *url
 *gmail (if not required then write N/A)
 *username
 *password
 *mobile number
 *more info
 **display
 *search any particular website
 *display all in sorted way as user instructions
 */

/*
 *application data directory will "C:\\Basic Password Manager\\user_config.config"
 *default user directory will "C:\\Basic Password Manager" but it can modifiable
 **user_config.config file contains (C:\\Basic Password Manager)
 *1. database directory
 *2. name of user
 **security.config file contains (C:\Users\Basic Password Manager) (Security provided)
 *1. access password length
 *2. access password
 */

/*for file I/O only C programming functions are used */

#include <iostream>
#include <stdio.h> //c header files
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <windows.h>
#include <winuser.h>
#include <w32api.h>
#include <unistd.h>
using namespace std;
typedef short let; // using 'let' at the place of short
int create_folder(char *path, char *new_folder_name);

/*I have tried this.
 *"C:Users\\Basic Password Manager"
 *but we need administrative permission to created folder in users directory
 *so we will not do so.
 */

/*
 **time wasting bugs or mistakes.
 **1. for backslash I used \"\" but it is for ""
 * for backslash \\ escape sequence is used
 **2. we can't create file/directory in "C:Users". It requires administrative permission
 */

const char applicationDirectory[40] = "C:\\Basic Password Manager"; // directory for application data. Not changable. The directory name will "Basic Password Manager"(Global Variable)
char databaseDirectory[200] = "C:\\Basic Password Manager";         // if user not do anything then it will default for database (Global variable)

/*definition of function used in another class and other*/
class generalWork
{
public:
    /*input the access password from user and stores in the char* taken in argument. Take arguments of char* string and length of password */
    void inputAccessPassword(char *accessPassword, int length)
    {
        int i, error = 0;

        while (true)
        {
            error = 0; // assigning 0 to error indicator. So, if there will be an error then it will increment
            cout << "\033[38;5;15m$ ";
            for (i = 0; i < length; i++)
            {
                char temp = getch(); // to read input from user
                cout << "*";
                accessPassword[i] = temp;
                /* If user pressed enter without writing password*/
                if (temp == '\r') // getch() take and store '\n' as '\r'
                {
                    cout << "\n\033[1;31mFatal Error: Invalid password............." << endl;
                    cout << "\033[1;31mFatal Error: Write password of mentioned length i.e " << length << endl;
                    error++; // incrementing the error indicator
                    break;   // to break the inner loop i.e 'for' loop
                }
            }
            if (error == 0) // in case of no error
                break;
            accessPassword[i] = '\0'; // adding NULL in last of string
        }
    }

    /*input the password from user and stores in the char* taken in argument. Take arguments of char* string and take password from user until newline character encountered*/
    void inputPassword(char *password)
    {
        int i = 0;
        while (true)
        {
            char temp = getch(); // to read input from user
            cout << "*";
            if (temp == 13) // 13 for carriage return i.e /r
                break;
            password[i++] = temp;
        }
        password[i] = '\0'; // adding NULL in last of string
    }

    /*returns 1 if directory exists else 0 on failure*/
    int isDirectoryExist(char *path)
    {
        char command[500]; // for command to external program i.e windows shell
        sprintf(command, "cd %s", path);
        return !system(command); // here system() returns 0 on success and 1 on failure
    }

    /*returns 1 if user is authorized and already registered else returns 0*/
    int isUserRegistered()
    {
        /*if user registered then user_config.config file and security.config file will be available in applicationDirectory*/
        if (isDirectoryExist(databaseDirectory)) // we can also use 'applicationDirectory' but it will error because it's const char* and argument required only char*. But first time applicationDirectory and databaseDiretory both are same.
        {
            char command[500]; // for command to external program i.e windows shell
            sprintf(command, "%s\\user_config.config", applicationDirectory);
            FILE *ptr = fopen(command, "r");
            if (ptr == NULL)
                return 0; // user does not exist
            else
                return 1; // user exist
        }
        return 0; // user does not exist
    }

    /*convert the string received in argument to upper case*/
    void convertToUpper(char *string)
    {
        for (int i = 0; string[i] != '\0'; i++)
            string[i] = toupper(string[i]);
    }
};

class windowsSpecial
{
public:
    /*returns 1 if Caps lock key is on else returns 0*/
    int isCapsLockKeyOn()
    {

        if (GetKeyState(VK_CAPITAL)) // returns 1 if toggled key is turned on  else returns 0 . See more: https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getkeystate?redirectedfrom=MSDN#return-value
            return 1;                // caps lock enabled
        return 0;                    // caps lock disabled
    }
    /*returns 1 if Num lock key is on else returns 0*/
    int isNumLockKeyOn()
    {

        if (GetKeyState(VK_NUMLOCK)) // returns 1 if toggled key is turned on  else returns 0 . See more: https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getkeystate?redirectedfrom=MSDN#return-value
            return 1;                // caps lock enabled
        return 0;                    // caps lock disabled
    }

    void disableTerminalClosing()
    {
        HWND saveData = GetConsoleWindow();
        HMENU saveData2 = GetSystemMenu(saveData, false);
        EnableMenuItem(saveData2, SC_CLOSE, MF_GRAYED);
    }

    void enableTerminalClosing()
    {
        HWND saveData = GetConsoleWindow();
        HMENU saveData2 = GetSystemMenu(saveData, false);
        EnableMenuItem(saveData2, SC_CLOSE, MF_ENABLED);
    }
};

// /*to incrept the password and then save in database for security*/
// class passwordEncryption
// {

// public:
//     /*encrypt the password received in argument and save in database*/
//     void encrypt(char *password)
//     {
//     }

//     /*decrypt the password received in argument and save in same*/
//     void decrypt(char *password) {}
// };

/*for user access the application first time*/
class firstTime
{
    /*it's better to use a structure that contains accessPassword and length of password*/
    char *accessPassword;  // to store the access password from user
    char name[40];         // static because it's fast and there is not requirement of run time memory allocation (because user's don't interact with the no. of characters for his/her name)
    unsigned short length; // to store the length of the access password

    /*Take argument of path and new_folder_name and create a new folder of passed name inside the given path and returns 0 on success else other value.
      if path provided is not directing right path then all given folders will creat in current working directory*/
    int create_folder(char *path, char *new_folder_name) // path for path and new_folder_name for name of new folder
    {
        char *command = (char *)calloc(500, sizeof(char)); // creating 500 block of character having base address stored in 'command'
        sprintf(command, "mkdir \"%s\\%s\"", path, new_folder_name);
        int status = system(command); // system() returns 0 on success
        free(command);
        return status;
    }

    /*to take path of database directory from user else default will be executed*/
    void takeDataBaseDirectory()
    {
        cout << "\033[1;31m ========================WELCOME TO BASIC VERSION OF PERSONAL PASSWORD MANAGER========================" << endl;
        cout << "\033[1;32m>>> This Menu will only appear if user will launch the application for 1st time" << endl;
        cout << "\033[1;34m>>> This is the not the full version of the application." << endl;
        cout << ">>> It's just simple testing version which performs basic operations." << endl;

        while (true)
        {
            cout << "\n\n\033[38;5;84mWrite your sweet name:\033[0m" << endl;
            cout << "\033[38;5;15m$ ";
            fflush(stdin);
            cin.getline(name, 50);
            if (strcmp(name, "\0") == 0) // if user will press enter without writing name
                continue;
            else
                break;
        }

        cout << "\033[38;5;84mDefault directory for database is \033[1;31m" << databaseDirectory << endl;
        cout << "\033[38;5;84mDo you want to continue with default directory. (Press 'enter' for default)\033[1;31m yes/no\033[0m" << endl;
        char choice[4];
        fflush(stdin);
        cout << "\033[38;5;15m$ ";
        cin.getline(choice, 4); // if user write wrong choice then default directory will be set
        if (choice[0] == 'n' || choice[0] == 'N')
        {
            generalWork obj; // for perfrom some work
            while (true)
            {
                cout << "\n\033[38;5;190mWrite the custom database directory path:" << endl;
                cout << "\033[38;5;15m$ ";
                fflush(stdin);
                cin.getline(databaseDirectory, 200);
                if (strcmp(databaseDirectory, "\0") == 0) // if user will press enter without writing
                    continue;
                else if (obj.isDirectoryExist(databaseDirectory))
                {
                    cout << "\033[1;32mDatabase directory added successfully.\033[0m" << endl;
                    break;
                }
                else
                {
                    cout << "\033[1;31mThis directory does not exist. Invalid directory path. Please write again:" << endl;
                    continue;
                }
            }
        }
        else
            cout << "\033[1;31mThanks for choosing the default database directory i.e\033[1;32m " << databaseDirectory << "\033[0m" << endl;

        // now creating the database directory either it is default or as user specified
        // creating application directory also
        create_folder("C:", "Basic Password Manager"); // for directory of application data or default user database directory

        if (choice[0] == 'n' || choice[0] == 'N')                       // means if user added his/her own directory path
            create_folder(databaseDirectory, "Basic Password Manager"); // for directory of database
    }

    /*take password from user first time*/
    void takeAccessPasswordFirstTime()
    {
        cout << "\n\n\033[38;5;84mCreate a access password to access your information from next time:" << endl;
        cout << "\033[38;5;154mWrite the length of access password:" << endl;
        cout << "\033[38;5;15m$ ";
        cin >> length;
        /*allocating memory*/
        accessPassword = (char *)calloc(length + 1, sizeof(char));            //+1 for NULL
        char *againAccessPassword = (char *)calloc(length + 1, sizeof(char)); // to store the access password  2nd time from user for verification purpose

        while (true)
        {
            cout << "\033[1;32mWrite your access password:" << endl;
            generalWork obj;
            obj.inputAccessPassword(accessPassword, length);

            cout << "\n\033[1;32mWrite your access password again:" << endl;
            obj.inputAccessPassword(againAccessPassword, length);

            if (strcmp(againAccessPassword, accessPassword) == 0)
            {
                cout << "\n\033[1;32mExcellent. Your password saved successfully........." << endl;
                break;
            }
            else
            {
                cout << "\n\033[1;31mInvalid access password OR Access password doesn't match with previous one." << endl;
                cout << "\033[1;34mWrite access password again from beginning." << endl;
                continue;
            }
        }
    }

    /*save the user configuration in the configuration database*/
    void saveInfoInConfigurationDatabase()
    {
        char path[300];

        /*1. for user configuration file*/
        sprintf(path, "%s\\user_config.config", applicationDirectory); // path for application directory for user configuration
        FILE *ptr = fopen(path, "w");
        if (ptr == NULL)
        {
            perror("\033[1;31mCouldn't open/create user configuration file. Exit code 101");
            exit(EXIT_FAILURE);
        }
        /**user_config.config file contains (C:\\Basic Password Manager)
         *1. database directory
         *2. name of user
         */

        fprintf(ptr, "%s\n%s", databaseDirectory, name);
        memset(path, 0, sizeof(path)); // to insert 0 at every character

        /*2. for security.config file*/
        sprintf(path, "%s\\security.config", applicationDirectory); // path of security.config file
        if (freopen(path, "w", ptr) == NULL)
        {
            perror("\033[1;31mCouldn't open/create security configuration file. Exit code 102");
            exit(EXIT_FAILURE);
        }
        /**security.config file contains (C:\Users\Basic Password Manager)(Security provided)
         *1. access password length
         *2. access password
         */
        /*we can also use whole block of structure for writing but I am already used the single variable. So, I will not changed it now*/
        fwrite(&length, sizeof(unsigned short), 1, ptr);
        fprintf(ptr, "\n"); // for newline
        fwrite(accessPassword, sizeof(char), length + 1, ptr);
        fclose(ptr);
    }

    /*friend function to access some information*/
    // friend void firstTimeClassFriend(firstTime);

public:
    /*returns 1 on success*/
    int configurationForFirstTime()
    {
        takeDataBaseDirectory();           // to take data base directory from user
        takeAccessPasswordFirstTime();     // to take the accessPassword from user firstTime
        saveInfoInConfigurationDatabase(); // to save info in configuration database
        free(accessPassword);
    }
};

/*class for performing all operation of inserting new data in database*/
class addNewData
{
    struct infoType
    {
        /**
         *I am not using dynamic memory allocation because access of heap is slow than that of static.
         *and here there is no requirement of allocating run time memory with user interation.
         *so, I have used static memory allocation.
         */
        char websiteName[100];
        char websiteUrl[100];
        char category[50]; // for category of website like programming, entertainment etc
        char email[100];
        char password[100];
        char username[20];
        char mobileNumber[11];
        char userFullName[50]; // for taking the real full name of user
        char *moreInfo;        // we use dynamic memory allocation for it. Because info size has no limit like above data
    } var;
    int lastIndex;

    /*returns 1 if correct url, 0 otherwise*/
    int isCorrectUrl(char *url)
    {
        for (int i = 0; url[i] != '\0'; i++)
        {
            if (url[i] == '.')
                return 1; // on success
        }
        return 0; // on failure
    }

    /*returns 1 if corrent email else 0*/
    int isCorrectEmail(char *email)
    {
        int counter = 0; // to count
        for (int i = 0; email[i] != '\0'; i++)
        {
            if (email[i] == '@' || email[i] == '.')
                if (++counter == 2)
                    return 1; // on success
        }
        return 0; // incorrect email
    }

    /*command menu for input info for user*/
    void inputTimeCommandMenu()
    {
        cout << "\n\033[1;31m:|:|:|:|:|:|:|:|:|:\033[4m\033[38;5;51mAPPLICABLE COMMANDS FOR THIS MENU\033[1;31m:|:|:|:|:|:|:|:|:|:\033[0m\033[1;31m" << endl;
        cout << "=>>>  \033[4m\033[38;5;129mWrite \033[1;32mNA \033[38;5;129mif no info available OR simply \033[1;32mpress enter\033[0m\033[1;31m" << endl;
        cout << "=>>>  \033[4m\033[38;5;129mWrite \033[1;32mprv OR '@' \033[38;5;129mif you want to rewrite(modify) the previous info (rewind to last entered info)\033[0m\033[1;31m" << endl;
        cout << "=>>>  \033[4m\033[38;5;129mWrite \033[1;32mclear \033[38;5;129mto clear the display\033[0m\033[1;31m" << endl;
        cout << "=>>>  \033[4m\033[38;5;129mWrite \033[1;32mexit OR '#' \033[38;5;129mto exit properly without saving current info\033[0m\033[1;31m" << endl;
        cout << "=>>>  \033[4m\033[38;5;129mWrite \033[1;32m#cmd \033[38;5;129mto display this command menu\033[0m\033[1;31m"
             << endl
             << endl;
    }

    /**conditions to be checked before termination of an input type
     * if user press enter without writing
     * if user don't have any info for current choice
     * if user want to go previous to modify the prewritten data
     * if user want clear the display (disply the command menu if user clear the display)
     * if user want to exit properly
     * if user want to see the command MENU
     *
     */

    /*1. input of website name. returns 0 if user cancel the operation and exit else returns 1 on successfull input */
    int inputWebsiteName()
    {
        while (true)
        {
            cout << "\033[1;36m01. Write Website Name:" << endl;
            cout << "\033[38;5;15m$ ";
            fflush(stdin);
            cin.getline(var.websiteName, 100);

            /*now checking conditions*/
            if (var.websiteName[0] == 0)                                                       // if user press enter without writing anything                                               // If user press enter without writing //it is better than (strcmp(var.websiteName,"\0")==0))
                continue;                                                                      /* continue to inner while loop*/
            else if (strcmp(var.websiteName, "na") == 0 || strcmp(var.websiteName, "NA") == 0) // if user don't have any info for current choice
            {
                cout << "\033[1;31mError: Website must have a name." << endl;
                cout << "\033[1;32mBut if you are inserting info for any specific reason then also it's not valid here. " << endl
                     << "(see application user manual for more details.....)" << endl
                     << "\033[38;5;141mPlease write again:)\033[0m\n"
                     << endl;
                continue;
            }
            else if (strcmp(var.websiteName, "@") == 0 || strcmp(var.websiteName, "prv") == 0) // if user want to go to modify the previous written info
            {
                cout << "\033[1;31mError: command for rewind to previous choice will not work here. Because it's the first choice.\033[0m" << endl;
                cout << "\033[1;34mWrite the website name again:)\n"
                     << endl;
                continue;
            }
            else if (strcmp(var.websiteName, "clear") == 0) // to clear the display
            {
                system("cls");
                inputTimeCommandMenu(); // to display the command menu after clear the display
                continue;
            }
            else if (strcmp(var.websiteName, "#") == 0 || strcmp(var.websiteName, "exit") == 0) // if user want to exit without saving info
                return 0;
            else if (strcmp(var.websiteName, "#cmd") == 0) // if user want to see the command menu
            {
                inputTimeCommandMenu(); // to display the command menu
                continue;
            }
            else // means user has written something
                break;
        }
        return 1; // on successfull execution
    }

    /*2. input of website url. returns 0 if user cancel the operation and exit else returns 1 on successfull input */
    int inputWebsiteUrl()
    {
        while (true)
        {
            cout << "\033[1;32m02. Write Website URL:" << endl;
            cout << "\033[38;5;15m$ ";
            fflush(stdin);
            cin.getline(var.websiteUrl, 100);

            /*now checking conditions*/
            if (var.websiteUrl[0] == 0)                                                      // if user press enter without writing anything                                               // If user press enter without writing //it is better than (strcmp(var.websiteName,"\0")==0))
                continue;                                                                    /* continue to inner while loop*/
            else if (strcmp(var.websiteUrl, "na") == 0 || strcmp(var.websiteUrl, "NA") == 0) // if user don't have any info for current choice
            {
                cout << "\033[1;31mWarning: Website must have a url." << endl;
                cout << "\033[1;32mBut if you are inserting info for any application then it is valid here." << endl
                     << " (see application user manual for more details..)\033[0m" << endl;
                strcpy(var.websiteUrl, "N/A");
                break;
            }
            else if (strcmp(var.websiteUrl, "@") == 0 || strcmp(var.websiteUrl, "prv") == 0) // if user want to go to modify the previous written info
            {
                cout << "\n\033[38;5;166mRewinding To Previous Input Type........." << endl;
                cout << "\033[38;5;159mNow, Rewrite Or Modify the info again from here and onwards:)\n"
                     << endl;
                if (inputWebsiteName()) // returns 1 on successfull input else 0
                    continue;
                else
                    return 0; // user cancelled the operation i.e exit
            }
            else if (strcmp(var.websiteUrl, "clear") == 0) // to clear the display
            {
                system("cls");
                inputTimeCommandMenu(); // to display the command menu after clear the display
                continue;
            }
            else if (strcmp(var.websiteUrl, "#") == 0 || strcmp(var.websiteUrl, "exit") == 0) // if user want to exit without saving info
                return 0;
            else if (strcmp(var.websiteUrl, "#cmd") == 0) // if user want to see the command menu
            {
                inputTimeCommandMenu(); // to display the command menu
                continue;
            }
            else if (!isCorrectUrl(var.websiteUrl)) // returns 0 if incorrect url
            {
                cout << "\033[1;31mFatal Error: Invalid URL" << endl;
                cout << "\033[1;34mWrite URL again:\033[0m" << endl;
                continue;
            }

            else // means user has written something
                break;
        }
        return 1; // on successfull input
    }

    /*save the name of current structure member int 'char* dataMemberNameForUser' that should be displayed to user on the basis of passed index*/
    void currentDataMemberNameForUser(short structMemberIndex, char *dataMemberNameForUser)
    {
        switch (structMemberIndex) // on the basis of index of member of structure
        {
        case 1:
            strcpy(dataMemberNameForUser, "name of website or application"); // name
            break;
        case 2:
            strcpy(dataMemberNameForUser, "URL of website if applicable"); // url
            break;
        case 3:
            strcpy(dataMemberNameForUser, "category of website or application e.g programming, entertainment etc"); // category
            break;
        case 4:
            strcpy(dataMemberNameForUser, "Email if applicable"); // email
            break;
        case 5:
            strcpy(dataMemberNameForUser, "password"); // password
            break;
        case 6:
            strcpy(dataMemberNameForUser, "username if applicable"); // username
            break;
        case 7:
            strcpy(dataMemberNameForUser, "mobile number if applicable"); // mobile number
            break;
        case 8:
            strcpy(dataMemberNameForUser, "full name of user"); // user full name
            break;
        case 9:
            strcpy(dataMemberNameForUser, "more info about the website or application"); // info
            break;
        }
    }

    /*returns true if NA allowed for the type of data of current data member of structure else false */
    bool isNaAllowed(short structMemberIndex)
    {
        switch (structMemberIndex) // on the basis of index of member of structure
        {
        case 1:
            return false; // name
            break;
        case 2:
            return true; // url
            break;
        case 3:
            return false; // category
            break;
        case 4:
            return true; // email
            break;
        case 5:
            return false; // password
            break;
        case 6:
            return true; // username
            break;
        case 7:
            return true; // mobile number
            break;
        case 8:
            return true; // user full name
            break;
        case 9:
            return true; // info
            break;
        }
    }

    /**FUNCTION TO PERFROM ALL IN ONE INPUT OPERATIONS FOR EACH INPUT TYPE.
     *dataMemberNameForUser or dataMemberNameForUser is the name of type. e.g website name, mobile number, password etc.
     *typeIndex is the index of the type to display indexing to user. e.g index of "website name" (var = websiteName) is 01.
     *structMemberIndex is the variable number. e.g. websiteName have 1 structMemberIndex because it's first variable.
     *naAllowed is 'is NA allowed for current type'. or prvNaAllowed is 'is NA allowed for prv type'
     *
     *
     **returns 1 if user input the data successfully else returns 0 if user cancelled/exit the operation or due to other errors
     *
     *(we will not take argument of 'extraFunctionRequired' and it's name. Because it's required only in case of url(structMemberIndex==4) and email (structMemberIndex=2)). So, we use structMemberIndex and check the same.
     *(rewind allowed in all type except first. So, why we take a special bool variable for rewindAllowed. Simply, we use the structMemberIndex or typeIndex == 1 then rewind not allowed else allowed.)
     */

    /*returns 1 for successfull input of current data else returns 0 on failure or user cancel of exit the operation*/
    int allInOneInputFunction(const int structMemberIndex) // short typeIndex, bool isNaAllowed, bool isPrvNaAllowed, const char* dataMemberNameForUser, bool extraFunctionRequired, const char *extraFunctionName
    {
        /**why we use pointers here.
         *we can't use received variable name to access the data member. So, we have taken structMemberIndex from calling function instead of varName.
         *because to access it we need the original data member name directly.
         *e.g we can't use var.userVariable. It's invalid because userVariable named member doesn't exist in my structure name infoType.
         *So, to solve this we use pointers concept.
         *we use the global(for this class) object of structure infoType i.e var to access the address of member variable.
         *and by address of member variable. We assign or input data on that address and it will work.
         */
        /*we must need to give option to go for previous input type to user to modify the previous input type*/

        /**My structure named 'infoType' members list with index
         *1. char websiteName[100];
         *2. char websiteUrl[100];
         *3. char category[50];
         *4. char email[100];
         *5. char password[100];
         *6. char username[20];
         *7. char mobileNumber[11];
         *8. char userFullName[50];
         *9. char *moreInfo;//we use dynamic memory allocation for it. Because info size has no limit like above data
         */

        char *structVarCurrentDataMemberAddress; // stored address of data member of structure
                                                 // user dataMemberNameForUser instead of dataMemberNameForUser;
        char dataMemberNameForUser[100];         // for name to display to user for current data member
        currentDataMemberNameForUser(structMemberIndex, dataMemberNameForUser);
        // we can use if-else-if ladder here. But switch-case is alternative for easy case like here. i.e condition of checking only 1 variable i.e structMemberIndex==x.

        switch (structMemberIndex) /*for the address of struct member on which operation will be performed currently*/
        {
        case 1:
            structVarCurrentDataMemberAddress = var.websiteName; // assigning address of structure data member
            break;
        case 2:
            structVarCurrentDataMemberAddress = var.websiteUrl;
            break;
        case 3:
            structVarCurrentDataMemberAddress = var.category;
            break;
        case 4:
            structVarCurrentDataMemberAddress = var.email;
            break;
        case 5:
            structVarCurrentDataMemberAddress = var.password;
            break;
        case 6:
            structVarCurrentDataMemberAddress = var.username;
            break;
        case 7:
            structVarCurrentDataMemberAddress = var.mobileNumber;
            break;
        case 8:
            structVarCurrentDataMemberAddress = var.userFullName;
            break;
        case 9:
            structVarCurrentDataMemberAddress = var.moreInfo;
            /*in this case we have to allocate memory because it's not static */
            structVarCurrentDataMemberAddress = (char *)calloc(100, sizeof(char));
            break;
        }

        while (true)
        {
            cout << "\n\033[1;32m" << structMemberIndex << ". Enter " << dataMemberNameForUser << ": (NA allowed: " << isNaAllowed(structMemberIndex) << ")" << endl;
            cout << "\033[38;5;15m$ ";
            fflush(stdin);

            /**
             **PROBLEM
             *char *moreInfo; -> indexNumber=9. This data member is a char pointer because size of moreInfo can't be fixed.
             *we also need to insure that during input in each data member user can write any command like prv, exit, @, #,clear, na, #cmd etc.
             *so, during input in all others data member, we simply take data in same because they are allocated statically. So, if any of command written by user then from if-else-if ladder process the respective work.
             *but here, there is no fixed size of memory
             *If we take input for this data member and terminate the same after completion before visiting the if-else-if ladder then command will not work and it's a huge issue
             *we can't use default input method for this data member i.e cin.getline(xxxx...,100) because there is no limit of size for this data member but in default the size if 100.
             *If we use default by allocating 100 bytes before it then also cin.getline() will not terminate after 100 characters and after 99 chracters rest will ignored but we don't have to do so. We have to store all characters. In others data members, it's fixed that their size will less than 100
             **SOLUTION
             *we will allocate the memory of size = size of maxLengthcommand i.e 5 for 'clear' command + 1 = 6 (for adding '\0' in last of string because it's compulsory to know the last char of string when function like strcmp() etc will use it in if-else-if ladder for checking of Command or other.)
             *store the characters one by one
             *possible conditions:
             *1. command written by user and pressed enter (na,exit,clear,#cmd,#,@,prv etc)
             *2. user don't write anything and press enter means NA applicable here (user can also write NA but it's also option to simply don't write anything and press enter then it will accepted as NA)
             *3. user written 'moreInfo' but it's size is 5 or below
             *4. user continue writing characters i.e more that 5 characters
             *Process:
             *terminate the loop here (before if-else-ladder or default input i.e cin.getline()) if no. of chracters crossed 5 or user press enter within 5 characters (must add NULL in last)
             *after this control will go through if-else-if ladder
             *if command matched then respective operation will be performed
             *if command doesn't match and enter is pressed AND if command doesn't match and user continue writing characters
             *In case of above line, write code for terminate (if command doesn't match and enter is pressed) Or continue taking input (if command doesn't match and user continue writing characters') in one of last (after command checking) of if-else-if ladder
             */
            if (structMemberIndex == 9)
            {
                structVarCurrentDataMemberAddress = (char *)calloc(6, sizeof(char)); // allocating memory for "char* moreInfo" particularly for command point of view. i.e user may write commands (prv,clear,exit etc) instead of 'moreInfo'
                let i;
                for (i = 0; i < 5; i++)
                {
                    structVarCurrentDataMemberAddress[i] = cin.get();
                    if (structVarCurrentDataMemberAddress[i] == '\n') // if user pressed enter without writing 5 characters
                    {
                        structVarCurrentDataMemberAddress[i] = '\0'; // adding newline in last of string
                        break;
                    }
                }
                /*if termination of loop i.e if user have written 5 characters*/
                if (i == 5)                                      // means loop terminated due condition fails
                    structVarCurrentDataMemberAddress[i] = '\0'; // adding newline in last of string
            }
            else
                cin.getline(structVarCurrentDataMemberAddress, 100);
            // cin.getline(structureVar, 100); // here structureVar==var.varName is not true. structureVar is a simple string while var.xyz is the variable inside structure. So, we can't perform this operation

            /*---------------------------------------------------------------------------*/

            /*now checking conditions*/
            /*each block of if() of else if() must contains either 'break' or 'continue' statement. Because if control enters in it then it will not go in any other if-else-if and due to this we must need to break or continue the loop for next operation.*/
            /*if (structVarCurrentDataMemberAddress[0] == 0)                                                                         // if user press enter without writing anything                                               // If user press enter without writing //it is better than (strcmp(var.websiteName,"\0")==0))
                continue;                                                                                                          /* continue to inner while loop*/
            if (strcmp(structVarCurrentDataMemberAddress, "na") == 0 || strcmp(structVarCurrentDataMemberAddress, "NA") == 0 || strcmp(structVarCurrentDataMemberAddress, "\0") == 0) // if user don't have any info for current choice or user simply press enter without writing anything (it may be possible that that input type is compulsory)
            {
                if (structMemberIndex == 1)
                {
                    cout << "\033[1;31mError: Website/Application must have a name." << endl;
                    cout << "\033[1;32mBut if you are inserting info for any specific reason then also it's not valid here. " << endl
                         << "(see application user manual for more details.....)" << endl
                         << "\033[38;5;141mPlease write again:)\033[0m\n"
                         << endl;
                    continue;
                }
                else if (structMemberIndex == 2)
                {
                    cout << "\033[1;31mWarning: Website must have a url." << endl;
                    cout << "\033[1;32mBut if you are inserting info for any application then it is valid here." << endl
                         << "(see application user manual for more details..)\033[0m" << endl;
                    strcpy(structVarCurrentDataMemberAddress, "N/A");
                    cout << "\033[1;36m[---NA---]" << endl;
                    break;
                }
                else if (isNaAllowed(structMemberIndex))
                {
                    strcpy(structVarCurrentDataMemberAddress, "NA");
                    cout << "\033[1;36m[---NA---]" << endl;
                    break;
                }
                else
                {
                    cout << "\a\033[1;31mWarning: " << dataMemberNameForUser << " can't be empty." << endl //'\a' for produce an audiable alert
                         << "\033[38;5;141mPlease write again:)\033[0m" << endl;
                    continue;
                }
            }
            else if (strcmp(structVarCurrentDataMemberAddress, "@") == 0 || strcmp(structVarCurrentDataMemberAddress, "prv") == 0) // if user want to go to modify the previous written info
            {
                if (structMemberIndex == 1) // it's only for 1st input type i.e website name
                {
                    cout << "\033[1;31mError: command for rewind to previous choice will not work here. Because it's the first choice.\033[0m" << endl;
                    cout << "\033[1;34mWrite the website name again:)\n"
                         << endl;
                    continue;
                }
                cout << "\n\033[38;5;166mRewinding To Previous Input Type........." << endl;
                /*just for fun..........s*/

                int i = 0;
                cout << "\033[38;5;155mLoading........";
                while (i < 2)
                {
                    cout << "\033[1;37m" << ++i * 40 << "%"
                         << "\b\b\b";
                    sleep(1);
                }
                cout << "100%";
                /*exit of fun........*/

                cout
                    << "\n\033[38;5;159mNow, Rewrite Or Modify the info again from here and onwards:)\n"
                    << endl;
                /*using recursion to go back to the previous choice*/
                if (allInOneInputFunction(structMemberIndex - 1)) // returns 1 on successfull input else 0
                    continue;                                     // restarting the input in that data member from which user returns back to the previous member for re input
                else
                    return 0; // user cancelled the operation i.e exit
            }
            else if (strcmp(structVarCurrentDataMemberAddress, "clear") == 0) // to clear the display
            {
                system("cls");
                inputTimeCommandMenu(); // to display the command menu after clear the display
                continue;
            }
            else if (strcmp(structVarCurrentDataMemberAddress, "#") == 0 || strcmp(structVarCurrentDataMemberAddress, "exit") == 0) // if user want to exit without saving info
                return 0;
            else if (strcmp(structVarCurrentDataMemberAddress, "#cmd") == 0) // if user want to see the command menu
            {
                inputTimeCommandMenu(); // to display the command menu
                continue;
            }
            else if (structMemberIndex == 5) // special for password (an special condition)
            /*below are the special lines of code from 'start' to 'end' for checking of password only*/
            // start
            /*we have to check twice for password*/
            {
                char againPassword[100];
                cout << "\n\033[1;32mWrite your password again: \033[1;31m(Don't write any command here.)" << endl;
                cout << "\033[38;5;15m$ ";
                cin.getline(againPassword, 100);

                if (strcmp(againPassword, structVarCurrentDataMemberAddress) == 0)
                {
                    cout << "\n\033[1;32mExcellent. Your password saved successfully........." << endl;
                    break;
                }

                else
                {
                    cout << "\n\033[1;31mError: Password doesn't match with previous one." << endl;
                    cout << "\033[1;34mWrite password again" << endl;
                    continue;
                }
                // end
            }
            else if (structMemberIndex == 2) // for url
            {
                if (!isCorrectUrl(structVarCurrentDataMemberAddress)) // returns 0 if incorrect url
                {
                    cout << "\033[1;31mFatal Error: Invalid URL" << endl;
                    cout << "\033[1;34mWrite URL again:\033[0m" << endl;
                    continue;
                }
                break;
            }
            else if (structMemberIndex == 4) // for email
            {
                if (isCorrectEmail(structVarCurrentDataMemberAddress)) // returns 1 if correct email else 0
                    break;
                cout << "\033[1;31mFatal Error: Invalid E-mail" << endl;
                cout << "\033[1;34mWrite E-mail again:\033[0m" << endl;
                continue;
            }
            else if (structMemberIndex == 7) // for mobile number. To check the entered mobile number is correct entered or not
            {
                /*actually we can check each character in number input and display error at the same time if character is not a number. but if we do so then command input (like prv, @, exit etc) will not work. So, we have to take input on the user choice and we will check the possibility of error after checking the possibility of commnads in input*/
                short counter = 0;
                short i = 0;
                while (structVarCurrentDataMemberAddress[i] != '\0')
                {
                    /*actually this block of code was written before input from cin.getline() but if we check the input character by character in case of number then the commands will not work. Due to which after complete input of number, we will check the the possibility of error in input of number*/
                    // below commented lines are cut from above because of the same that mentioned in previous line */f
                    //  structVarCurrentDataMemberAddress[counter] = cin.get();//cut from above
                    //  if (*structVarCurrentDataMemberAddress == '\0') // if user don't want to write number or no info available (NA allowed here. So, if user write then no issue but if user press enter then we need to add NA)
                    //  {
                    //      strcpy(structVarCurrentDataMemberAddress, "NA");
                    //      cout << "\033[1;36m[---NA---]" << endl;
                    //  }

                    if (!isdigit(structVarCurrentDataMemberAddress[i++])) /*isdigit() returns non-zero if argument is 0-9 else returns 0*/
                    {
                        cout << "\033[1;31mError: Invalid input. Only digits are allowed (0-9)\033[0m" << endl;
                        counter = 0; // restarting
                        break;
                    }
                    counter++;
                }
                if (counter == 0 || counter > 10) // means error in input of number (greater than 10 means error in input of number)
                {
                    if (counter > 10) // it only execute if counter>10
                        cout << "\033[1;31mError: Invalid mobile number. Mobile number must of 10 digits." << endl;
                    continue; // for both case restart the input process
                }
                else
                    break; // on successfull input
            }
            else if (structMemberIndex == 9) // for 'moreInfo' of current input type // because we are using dynamic memory allocation for the same and we can realloc memory if size is greater than 100
            {
                /*we have already taken input from user up to 5 chracters and in all case last character will be NULL (if user written all 5 characters then NULL will 6th character on 5th index)*/
                /*control will come in this block only if-else ladder only if user has not written any command in the input*/

                /**we have two possibilities to perform operation:
                 *1. if NULL found within 5 chracters (means user has written something which is not command(because command already checked above in if-else ladder) and less than 5 chracters)
                 *2. if NULL found as 6th character i.e on 5th index (this NULL is added by me for string creation for string related operations). Means user continue writing characters without pressing enter till 5th character
                 *if condition 1 satisfied then we will break the loop (because moreInfo mentioned by user within 5 chracters)
                 *if condition 2 satisfied then we will continue taking input from user until newline character encountered (input will be taken from index 5 i.e 6th position. Because we have manually add NULL in last. So, we assign the same by next data)
                 */
                /*-------------------------------FOR FIRST CONDITION-----------------------------------*/
                bool breakTheInputLoop = false; // flag to break the loop
                for (let i = 0; i < 5; i++)
                {
                    if (structVarCurrentDataMemberAddress[i] == NULL) // means info length is within the 5 characters
                    {
                        breakTheInputLoop++;
                        break; // for break the inner for loop
                    }
                }
                if (breakTheInputLoop)
                    break; // to break the outermost loop

                /*-------------------------------FOR SECOND CONDITION-----------------------------------*/
                // here we can't use cin.getline() because it required fixed size
                short charCounter = 5;                                                                                      // character counter//On the basis of above, 5 characters are already input by user i.e from index 0 to 4. So, we will take input from index 5
                short flag = 1;                                                                                             // count how many times memory of 100*(sizeof(char)) allocated
                structVarCurrentDataMemberAddress = (char *)realloc(structVarCurrentDataMemberAddress, 100 * sizeof(char)); /*6 bytes already allocated in beginning. So, now we are incrementing the space allocated to 100 bytes*/
                /*now taking input from user*/
                while (true)
                {
                    structVarCurrentDataMemberAddress[charCounter++] = cin.get();

                    if (structVarCurrentDataMemberAddress[charCounter - 1] == '\n') //-1 because we have incremented the variable
                        break;                                                      // to break the inner while loop
                    if (charCounter == (flag * 100) - 1)                            // realloc memory if allocated previous 100 bytes (if one block of char is 1 byte) used
                        structVarCurrentDataMemberAddress = (char *)realloc(structVarCurrentDataMemberAddress, ++flag * 100 * sizeof(char));
                }
                structVarCurrentDataMemberAddress[charCounter] = '\0'; // adding NULL as last character of string.
                break;                                                 // to break the outer while loop that input loop for current data member
            }
            else // means user has written something
                break;
        }
        return 1; // on successfull input
    }

    /*below lines are commented because I have performed all the operation of below uncompleted functions in a single above function*/
    // /*3. input of website url. returns 0 if user cancel the operation and exit else returns 1 on successfull input */
    // int inputCategory() {}
    // /*4. input of website url. returns 0 if user cancel the operation and exit else returns 1 on successfull input */
    // int inputEmail() {}

    // /*5. input of website url. returns 0 if user cancel the operation and exit else returns 1 on successfull input */
    // int inputPassword() {}

    // /*6. input of website url. returns 0 if user cancel the operation and exit else returns 1 on successfull input */
    // int inputUsername() {}

    // /*7. input of website url. returns 0 if user cancel the operation and exit else returns 1 on successfull input */
    // int inputMobileNumber() {}

    // /*8. input of website url. returns 0 if user cancel the operation and exit else returns 1 on successfull input */
    // int inputFullName() {}

    // /*09. input of website url. returns 0 if user cancel the operation and exit else returns 1 on successfull input */
    // int inputMoreInfo() {}

    /*main function of this class*/
    /*take input from user. returns 0 if user cancelled the current input operation else returns 1 on successfully data entry from user*/
    int takeInputFromUserMainMenu()
    {
        cout << "\n\033[1;31m-_-_-_-_-_-_-_-_-_-_-_-_-\033[4m\033[1;32mWELCOME TO INFORMATION INPUT MANAGER MENU\033[0m\033[1;31m-_-_-_-_-_-_-_-_-_-_-_-_-\033[0m" << endl;

        /*calling the command menu for 1st time*/
        inputTimeCommandMenu();

        /*input operations*/
        while (true)
        {
            // if (inputWebsiteName()) // returns 1 on successfull input else returns 0
            // {
            //     if (inputWebsiteUrl()) // returns 1 on successfull input else returns 0
            //     {
            //     }
            //     else
            //         return 0; // user cancelled the current input operation
            // }
            /*total number of structure members are 9. So, there index will 1 to 9. So, we have to take input from user in all data member i.e from 1 to 9*/
            short structMemberIndex = 1;   // for index of the structure member
            while (structMemberIndex < 10) // structMemberIndex must be from 0 to 9 here
            {
                if (allInOneInputFunction(structMemberIndex++))
                    continue; // on successfull input in current structure member
                return 0;     // user cancelled/exit the operation or any error
            }
            return 1; // on successfull input of all data
        }
    }

public:
    /*returns 1 on successfull input, 0 on either use cancel the operation or exit or any error*/
    int insertion()
    {
        if (takeInputFromUserMainMenu()) // returns 1 on successfull input else returns 0
        {
        }
        else
            return 0; // user cancelled the current input operation
    }
};

/*store all menu of start and perform login and other essential operations*/
class allMenus
{
    char name[40];   // store the name of user
    generalWork obj; // object of class generalWork
    char *accessPassword;
    unsigned short length;
    /**
     *perform essential operation to start the program. (LogIn and more...)
     *reading the user name
     *display the user name
     *input access password from user and check it.
     *changed the default database directory to user/default database directory as saved in file system
     **
     *returns 1 if user on success logIn and more else returns 0
     */
    int essentialOperations()
    {
        char path[200];
        /*1. for user configuration file*/
        sprintf(path, "%s\\user_config.config", applicationDirectory); // path for application directory for user configuration
        FILE *ptr = fopen(path, "r");
        if (ptr == NULL)
        {
            perror("\033[1;31mCouldn't open user configuration file. Exit code 103");
            return 0; // on failure
        }
        /**user_config.config file contains (C:\\Basic Password Manager)
         *1. database directory
         *2. name of user
         */
        // fscanf(ptr, "%s\n%s", name, databaseDirectory);It will not read the string with space
        fgets(databaseDirectory, 200, ptr);
        fgets(name, 40, ptr);
        // now removing the extra newline character added by fgets() in last of both string
        // String is not containing newline character in c++
        // name[strlen(name) - 1] = '\0';
        // databaseDirectory[strlen(databaseDirectory) - 1] = '\0';
        // done

        /*2. for security.config file*/
        sprintf(path, "%s\\security.config", applicationDirectory); // path of security.config file
        if (freopen(path, "r", ptr) == NULL)
        {
            perror("\033[1;31mCouldn't open security configuration file. Exit code 104");
            return 0; // on failure
        }
        /**security.config file contains (C:\Users\Basic Password Manager)(Security provided)
         *1. access password length
         *2. access password
         */
        /*we can also use whole block of structure for writing but I am already used the single variable. So, I will not changed it now*/
        fread(&length, sizeof(unsigned short), 1, ptr);
        accessPassword = (char *)calloc(length + 1, sizeof(char)); // allocating memory
        fscanf(ptr, "\n");                                         // for reading newline
        fread(accessPassword, sizeof(char), length + 1, ptr);
        fclose(ptr);
        obj.convertToUpper(name); // converting user name to upper case
        return 1;                 // on success
    }

    /*returns 1 successfully login else returns 0 on failure*/
    int login()
    {
        char *userPassword = (char *)calloc(length + 1, sizeof(char)); // allocating memory for storing the user password entered
        int counter = 0;                                               // to count ther number of times user have entered wrong password
        cout << "\n\033[1;31m<<<<<<<<<<<<<<<<<<<<<<<<\033[4m\033[1;34mLOGIN MENU\033[0m\033[1;31m>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl;
        cout << "\033[38;5;14mWELCOME MR./MRS. \033[4m\033[1;31m" << name << "\033[0m" << endl;
        while (counter < 5) // 5 try of password
        {
            /*checking if capsLock or numLock is on*/
            windowsSpecial winObj;
            cout << "-------------------------------------------------------------------------" << endl;
            bool isCapsOn = false;
            if (winObj.isCapsLockKeyOn())
            {
                cout << "\033[1;31mWarning: CapsLock Key is enabled. So, characters will auto capitalized.\033[0m" << endl;
                isCapsOn++; // for true that caps lock is on
            }
            if (!winObj.isNumLockKeyOn()) // return 1 if key is on else 0
                cout << "\033[1;31mWarning: NumLock Key is disabled. So, You can't use NumPad\033[0m" << endl;
            else if (!isCapsOn) // this will execute when capsLock is disabled and Numlock is enabled. Which is correct configuration
                cout << "\033[1;32mThe current keyboard configuration is general.\033[1;34m\nSo, Write access password properly:)\033[0m" << endl;
            cout << "-------------------------------------------------------------------------" << endl;

            cout << "\n\033[0m\033[38;5;3mPlease write your access password for login:" << endl;
            obj.inputAccessPassword(userPassword, length);
            if (strcmp(accessPassword, userPassword) == 0)
            {
                cout << "\n\033[1;32mHello, Mr./Mrs. \033[4m\033[38;5;172m" << name << "\033[0m\033[1;32m You have login successfully..............\033[0m" << endl;
                return 1; // on success
            }
            cout << "\n\033[1;31mFatal Error: Invalid Access Password. You have already tried " << ++counter << " times." << endl;
            if (counter < 5)
                cout << "\033[1;34mPlease write access password again properly." << endl;
        }
        cout << "\n\033[38;5;165m=======\033[4mSECURITY ISSUE\033[0m\033[38;5;165m=========" << endl;
        cout << "\033[1;31mYou have crossed the limit of password try......" << endl;
        cout << "\033[1;36mPlease try after some time." << endl;
        return 0; // on failure
    }

    /*to show welcome message to user*/
    void welcomeMenu()
    {
        system("cls");
        cout << "\033[1;31m-_-_-_-_-_-_-_-_-_-_-_-_-\033[4m\033[1;32m(:WELCOME TO BASIC PERSONAL PASSWORD MANAGER:)\033[0m\033[1;31m-_-_-_-_-_-_-_-_-_-_-_-_-\033[0m" << endl;
        cout << "\033[1;36mDesign and developed by \033[4mMr. Suraj Kumar Giri." << endl;
    }

    /* to display main menu for all main operations. Returns 1 on success else 0 on failure*/
    int mainMenu()
    {
        while (true) // added infinite loop only when user select option 4 or wrong choice
        {
            cout << "\n\n\033[1;31m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\033[4m\033[1;34mMAIN MENU\033[0m\033[1;31m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
            cout << "\033[1;33mPress 1 or write \033[38;5;135m'new'   \033[1;33m for \033[4m\033[1;32mAdd New Websites Login Info\033[0m\033[1;33m" << endl;
            cout << "\033[1;33mPress 2 or write \033[38;5;135m'search'\033[1;33m for \033[4m\033[1;32mSearch Existing Websites Login Info\033[0m\033[1;33m" << endl;
            cout << "\033[1;33mPress 3 or write \033[38;5;135m'adv'   \033[1;33m for \033[4m\033[1;32mDisplay Advanced Existing Websites Login Info\033[0m\033[1;33m" << endl;
            cout << "\033[1;33mPress 4 or write \033[38;5;135m'clear' \033[1;33m for \033[4m\033[1;32mClear The Display\033[0m\033[1;33m" << endl;
            cout << "\033[1;33mPress 5 or write \033[38;5;135m'exit'  \033[1;33m for \033[4m\033[1;32mExit Properly\033[0m\033[1;33m" << endl;
            char choiceString[10];
            char choice;
            while (true)
            {
                cout << "\033[1;36mWrite your choice:" << endl;
                cout << "\033[38;5;15m$ ";
                fflush(stdin);
                cin.getline(choiceString, 10);
                if (choiceString[0] == '\0')
                    continue;
                else
                    break;
            }
            if (strcmp(choiceString, "1") == 0 || strcmp(choiceString, "new") == 0)
            {
                addNewData obj;
                if (obj.insertion()) // returns 1 on successfull input else returns 0
                    cout << "\033[38;5;148mInformation Input Manager Menu exited successfully.........." << endl;
                else // user cancelled the previous input operation
                    cout << "\033[1;31mError: Operation Cancelled By User OR Any error occurred in Information Input Manager Menu" << endl;
            }
            else if (strcmp(choiceString, "2") == 0 || strcmp(choiceString, "search") == 0)
            {
            }
            else if (strcmp(choiceString, "3") == 0 || strcmp(choiceString, "adv") == 0)
            {
            }
            else if (strcmp(choiceString, "4") == 0 || strcmp(choiceString, "clear") == 0)
                system("cls");
            else if (strcmp(choiceString, "5") == 0 || strcmp(choiceString, "exit") == 0)
                return 1; // on successfull exit
            else
            {
                cout << "\033[1;31mWarning: Wrong choice selected" << endl
                     << "\033[1;32mSelect you choice again......" << endl;
            }

            // return 1; // on success
            /*no need to break the infinite loop because function will be return after breaking from switch*/
        }
    }

public:
    /*start menu. Returns 1 on success, 0 on failure*/
    int startMenu()
    {
        welcomeMenu();
        if (essentialOperations()) //    returns 1 on success;
        {
            if (login())
            {
                if (mainMenu())
                    return 1; // on success
                else
                    return 0; // on failure
            }
            else
                return 0; // failure
            free(accessPassword);
        }
        else
            return 0; // failure
    }
};

/*main() function*/
int main()
{
    system("cls");
    generalWork objGeneral;
    if (objGeneral.isUserRegistered())
    {
        // user is registered (already existing)
        allMenus objAllMenu;
        if (objAllMenu.startMenu())
            cout << "\033[1;32mStart Menu exited successfully.........." << endl;
        else
        {
            cout << "\033[1;31mStart Menu exited with some error..." << endl;
            cout << "Exiting main() function" << endl;
            return 1;
        }
    }
    else
    {
        system("cls"); // because path not found (because user doesn't exist). So, an error message will be displayed on terminal.
        firstTime obj;
        if (obj.configurationForFirstTime())
        {
            cout << "\n\n\033[1;32mFirst user configuration executed successfully........." << endl;
            cout << "\033[1;36mPlease restart the application..........." << endl;
        }
    }
    cout << "\033[1;32mMain function exited successfully..........\033[0m" << endl;
    return 0;
}