#include <iostream>
#include <stdlib.h>
using namespace std;
void takeString(char *string)
{
    string = (char *)realloc(string, 10 * sizeof(char));
    /*allocation via realloc is same as memory allocated currently to 'string' then no changes will be made*/
    cin.getline(string, 9);
}
int main()
{
    char *string = (char *)malloc(10 * sizeof(char)); //= NULL; // If null then this function doesn't have the address of sting.
    cout << "Address " << (int)string << endl;
    takeString(string);
    cout << "Address " << (int)string << endl;
    cout << "my string is \"" << string << "\"" << endl;
    free(string);
}