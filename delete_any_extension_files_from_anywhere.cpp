/*Q. To delete any file with *.exe extension in user's entered directory (initally my aim)*/
/*To delete any file with any extension in any directory provided by user*/
// dir /b *.exe
// cd /<drive_name> "<path>" && <other command>

/*
 *author: Suraj Kumar Giri.
 *Date: 17-02-2022
 *Time: 02:29:16
 */

/*
 *Take path from user.
 *Take file extension from user.
 *Check path entered is correct or not.
 *Display the list of all files with *.user_extension.
 *save the file name in a temporary file
 *delete all files with *.user_extension
 */

/*system returns 0 on success and other integer on failure*/
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#define MAX 200 // for sizeof command string
using namespace std;

class deleteXExtensionFiles
{
    char *path;
    char *extension;
    void takePathAndExtensionFromUser();
    int checkPath();
    char extractDriveName();
    int displayAndSaveFiles();
    int performDeletionOperation();
    int isCorrectExtension();
    int failureToDelete; // to count the number of files failed to be deleted successfully

public:
    int deleteMyFiles();
};

typedef class deleteXExtensionFiles delUserFiles;

/*take path of directory from user and also extension of files that need to be deleted*/
void delUserFiles::takePathAndExtensionFromUser()
{
    path = (char *)calloc(500, (sizeof(char))); // allocating memory in heap
    cout << "\033[38;5;189mWrite the path of that directory whose files do you want to delete:" << endl;
    while (1) // if user press enter or path is wrong then loop will continue
    {
        cout << "\033[0m$ ";
        /*we have not used cin() because it ignores leading newline that cause not printing of $ on pressing enter*/
        gets(path);
        if (strcmp(path, "\0") == 0) // if user press enter without writing anything
            continue;
        // checking path entered is correct or not
        else if (checkPath()) // on success i.e path is correct
            break;
        else
        {
            cout << "\033[1;31mError: Invalid Directory Path." << endl;
            cout << "\033[38;5;159mWrite directory path again:" << endl;
        }
    } /*end of while*/

    cout << endl;
    extension = (char *)malloc(10 * sizeof(char)); // allocating memory
    cout << "\033[38;5;11mWrite the extension of files (without dot operator) that you want to delete" << endl;
    while (1) // if user press enter or extension name  is wrong then loop will continue
    {
        cout << "\033[0m$ ";
        /*we have not used cin() because it ignores leading newline that cause not printing of $ on press enter*/
        gets(extension);
        if (strcmp(path, "\0") == 0) // if user press enter without writing anything
            continue;
        else if (isCorrectExtension()) // checking extension name is correct or not
            break;
        else
        {
            cout << "\033[1;31mError: Invalid Extension." << endl;
            cout << "\033[38;5;159mWrite extension again:" << endl;
        }
    }
}

/*returns 1 on success i.e path is correct and exist else returns 0*/
int delUserFiles::checkPath()
{
    char command[MAX];
    sprintf(command, "cd %s", path);
    int status = system(command);
    return !status;
    /*
     *actually system returns 0 on success and 1 on failure.
     *and we have to pass 1 on success i.e path is correct and exist else returns 0.
     *so we have changed the value opposite by using 'not' operator.
     */
}

/*extract drive name from path and returns the it. Drive name is used to switch the control from one drive to another drive to see the files*/
char delUserFiles::extractDriveName()
{
    return path[0]; // in case of other drive
    /*e.g of path*/
    /*D:\Programming\c and cpp projects\Personal Password Manager\src*/
}

/*returns 1 on success i.e files with *.user_extension exist and displayed and saved else returns 0*/
int delUserFiles::displayAndSaveFiles()
{
    char command[MAX];
    /*
     *fixed huge bug on 4th March 2022.
     *actually the default path of control is in C: drive (in cmd).
     *we will not change the drive name if current drive = path drive because it causes problems.
     *so in case of any path of c: drive we don't need to pass the command to go in C: drive as we do in case of other drive.
     *it will cause error and program terminates and error "The filename, directory name, or volume label syntax is incorrect.".
     *so, in case of path of C: drive we will not change the directory of control to C: itself.
     *we have used extra condition below that if(path[0]=='C') then we will eliminate the part of command which is responsible for changing of drive of cmd control.
     */
    /*one more possible error to be fixed in future. That if default drive is not C:. then it will not work. So, we first need to check the current drive using 'cd' commamnd and if it match with drive of user's path drive then we don't change drive*/
    // all error is fixed
    /*
     *see 'https://stackoverflow.com/questions/17753986/how-to-change-directory-using-windows-command-line'
     *we can change drive simply by giving command D: or C: etc and then we can use && for next commands.
     *We will used 'pushd' command to directly go to anywhere without any issue.
     *see stackover flow for more details.
     *Now drive name is not required to check.😁
     *'cd' command is also not required.😁
     */

    // if (path[0] == 'C')
    //     sprintf(command, "cd \"%s\" && dir /b *.%s", path, extension);
    // else
    //     sprintf(command, "cd /%c \"%s\" && dir /b *.%s", extractDriveName(), path, extension);
    sprintf(command, "pushd \"%s\" && dir /b *.%s", path, extension);

    // cout << command << endl;
    /*Display part*/
    cout << "\033[1;32m";
    if (system(command)) // system returns 0 on success and other integer on failure
        return 0;        // on failure

    cout << "\033[38;5;189mAbove file/files will be deleted.\033[1;34m" << endl;
    system("pause");
    cout << "\033[0m";
    system("cls");

    /*we will not return control after successful display because we have to save the files name*/
    /*saving part*/
    FILE *ptr = fopen("tempFilesList", "w"); // we will create file at current working directory of program and delete it before main() returns*/
    // now using popen to copy the output by system()
    FILE *output = popen(command, "r"); // pointing on a temp file created by popen() contains output of system(command).

    if (ptr == NULL || output == NULL)
    {
        cout << "Something went wrong. Error Code 101" << endl;
        return 0; // failure
    }

    while (feof(output) == 0)
    {
        int ch = fgetc(output);
        fputc(ch, ptr);
    }
    fclose(ptr);
    pclose(output);
    return 1; // success
}

/*returns 1 on successfull deletion of files else returns 0*/
int delUserFiles::performDeletionOperation()
{
    // function to delete the file that user wants

    // opening the temp file 'tempFileList' contains the list of files with the specified user extension in user given directory i.e 'path'
    FILE *tempList = fopen("tempFilesList", "r");
    if (tempList == NULL)
    {
        cout << "Error: Couldn't open temp file. Error code 105." << endl;
        return 0;
    }

    failureToDelete = 0; // to count the number of files failed to be deleted successfully
    char fileName[100];
    int index = 0; // to count the number of files deleted successfully
    while (feof(tempList) == 0)
    {
        fgets(fileName, 100, tempList);
        fileName[strlen(fileName) - 1] = '\0';

        // there will one extra line which will taken as one string and obviously taken as a file name (file name will NULL because newline casues termination of fgets())
        // ignoring if string contains only NULL newline (last case)
        if (strcmp(fileName, "\0") == 0)
            continue;

        /*delete the file from user's provided directory*/
        char deletingFilePath[MAX];
        sprintf(deletingFilePath, "%s\\%s", path, fileName);

        if (!remove(deletingFilePath)) // remove() returns 0 on success
            cout << ++index << ". \033[1;32mFile \033[38;5;123m\"\033[4m" << fileName << "\033[0m\033[38;5;123m\"\033[1;32m deleted successfully." << endl;
        else
        {
            cout << "\033[1;31mError: Unable to delete file \"" << fileName << "\". Error code 111.\033[0m" << endl;
            failureToDelete++;
        }

        /*assigning each character of string to 0*/
        memset(fileName, 0, sizeof(fileName));
        memset(deletingFilePath, 0, sizeof(deletingFilePath));
        sleep(1);
    }
    fclose(tempList);
    return 1;
}

/*returns 1 if extension is correct i.e it contains only alphabet else returns 0*/
int delUserFiles::isCorrectExtension()
{
    for (int i = 0; extension[i] != '\0'; i++)
    {
        if (!isalpha(extension[i])) // isalpha() returns 0 if character is not alphabet
            return 0;
    }
    return 1; // on success. i.e extension is correct
}

/*returns 1 to main() on successful deletion else returns 0 on failure */
int delUserFiles::deleteMyFiles()
{
    takePathAndExtensionFromUser(); // input from user along with checking
    if (displayAndSaveFiles())      // display on console and save files with user given extension in temp file 'tempFileList'
    {
        if (performDeletionOperation()) // to perform deletion operation
        {
            if (failureToDelete == 0)
                cout << "\n\033[1;36mAll files with *." << extension << " extension deleted successfully.\033[0m" << endl;
            else
                cout << "\n\033[1;31mError: \033[1;36mFailed to delete all files with *." << extension << " extension.\033[0m" << endl;
        }
        else
        {
            cout << "\033[1;31mError: Something went wrong. Error code 125." << endl;
            free(path); // deallocating memory
            return 0;
        }
        free(path); // deallocating memory
        return 1;
    }
    else
    {
        cout << "\033[1;31mWarning: No files with \033[1;33m\"*." << extension << "\"\033[1;31m extension exist inside the directory \033[1;33m\"" << path << "\"\033[1;31m" << endl;
        free(path); // deallocating memory
        return 0;
    }
}

/*---------------------main()--------------------*/
int main()
{
    system("cls");
    delUserFiles obj;
    if (obj.deleteMyFiles())
    {
        cout << "\n\033[1;34mMain Exited Successfully.\033[0m" << endl;
        remove("tempFilesList"); // to delete temporary file 'tempFileList' created in current directory. temporary file 'tempFileList' created for perform operations of deletion.
        return 0;
    }
    else
        cout << "\n\033[1;34mMain Exited Successfully without fulfilling the delete operation.\033[0m" << endl;
    remove("tempFilesList"); // to delete temporary file 'tempFileList' created in current directory. temporary file 'tempFileList' created for perform operations of deletion.
    return 1;
}
