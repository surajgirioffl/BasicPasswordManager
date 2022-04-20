#include <stdio.h>
#include <stdlib.h>
int main()
{
    while (1)
    {
        system("cls");
        char string[2000];
        printf("write string (# for exit):\n");
        gets(string);
        if (strcmp(string, "#") == 0)
            break;
        int i;
        for (i = 0; string[i] != '\0'; i++)
            printf("%d=%c  ", i + 1, string[i]);
        printf("\n\033[1;31mTotal characters = %d\n\033[0m", i);
        system("pause");
    }
}