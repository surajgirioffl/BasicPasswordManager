#include <iostream>
#include <stdlib.h>
using namespace std;
/*testing of 'is realloc() free the memory after copy the data to new address if required space doesn't available at current segment of RAM */
int main()
{
    system("cls"); // clear the display
    char *base = (char *)calloc(200, sizeof(char));
    // int *dog;
    // cout << dog << endl;// it display address but in case of string it display the string by auto dereferencing
    cout << "base address initally by malloc() is " << &base << endl; // base is the base pointer
    cin.getline(base, 200);
    /*stirng is used to print using base address. control auto dereferenced the address and go to next similarly*/
    cout << "base data = " << base << endl; // base will print the string because base treated as base address and control print till NULL

    // char *c; // for taking a single character
    // *c = 't';
    // cout << c << endl; // it will display the address
    // means compiler understand(by checking the base address and allocated space. (if allocated space more than 1 then it will stiring)) that this char* is not a string. So, treated as character/intger
    char *saveBase = base;
    base = (char *)realloc(base, 10000 * sizeof(char));
    cout << "base address after realloc() = " << &base << endl;
    if (saveBase == base)
        cout << "\033[1;31mSame address. Means realloc() haven't changed anything" << endl;
    else
    {
        cout << "base data of new base address  = " << base << endl;
        cout << "base data of main base address = " << saveBase << endl;
    }
    // result. Yes of course realloc() free up the memory in above condition
}