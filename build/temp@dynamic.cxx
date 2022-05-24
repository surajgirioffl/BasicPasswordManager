#include <iostream>
#include <stdlib.h>
using namespace std;
int main()
{
    // system("cls"); // to clear the display
    // it's better to initialize ptr with NULL always'
    int *x;
    cout << "Address initially anywhere = " << x << endl;

    x = (int *)malloc(100);
    cout << "Address at 1 = " << x << endl;
    for (int i = 0; i < 20; i++)
        *(x + i) = i + 2;
    // free(x);
    int *y = x;
    // free(y);
    // what free do why 0 printing

    x = (int *)malloc(100);
    cout << "Address at 2 = " << x << endl; // here x contains new base address but previous base address is exist but we don't have any variable which contains the base address of previous location

    x = (int *)calloc(1, 100);
    cout << "Address at 3 = " << x << endl;

    x = (int *)realloc(x, 100);
    cout << "Address at 4 = " << x << endl;

    x = (int *)realloc(x, 110);
    cout << "Address at 5 = " << x << endl;

    x = (int *)realloc(x, 1100);
    cout << "Address at 6 = " << x << endl;

    cout << "x Changed due to allocating again but it's data are :"
         << endl;
    for (int i = 0; i < 20; i++)
        cout << y[i] << " ";
}
// pointer and array
// reallocating the amount with malloc/calloc the what