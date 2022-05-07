#include <iostream>
#include <stdlib.h>
#include <unistd.h>
using namespace std;
int main()
{
    system("cls");
    int i = 0;
    cout << "\033[38;5;155mLoading........";
    while (i < 3)
    {
        cout << "\033[1;37m" << ++i * 30 << "%"
             << "\b\b\b";
        sleep(1);
    }
    cout << "100%";
    return 0;
}

/*below are the special lines of code from 'start' to 'end' for password only*/
// start
/*we have to check twice for password*/
if (structMemberIndex == 5) // for password
{
    char againPassword[100];
    cout << "\n\033[1;32mWrite your password again:" << endl;
    cin.getline(againPassword, 100);

    if (strcmp(againPassword, structVarCurrentDataMemberAddress) == 0)
        cout << "\n\033[1;32mExcellent. Your password saved successfully........." << endl;

    else
    {
        cout << "\n\033[1;31mError: Password doesn't match with previous one." << endl;
        cout << "\033[1;34mWrite password again" << endl;
        continue;
    }
}
// end