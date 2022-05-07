/*Testing of functions fwrite() and fread() for block of data into files*/
/*
 *author: Suraj Kumar Giri.
 *Date: 15-02-2022
 *Time: 17:26:16
 */
#include <stdio.h>

int main()
{
    struct suraj
    {
        int roll;
        char name[30];
    };
    typedef struct suraj sur;
    sur s[3];
    for (int i = 0; i < 3; i++)
    {
        scanf("%d", &s[i].roll);
        fflush(stdin);
        puts("write name:");
        gets(s[i].name);
    }
    FILE *ptr = fopen("D://surajTemp.txt", "w");
    fwrite(&s, sizeof(sur), 3, ptr);
    fclose(ptr);
    // FILE *ptr = fopen("D://surajTemp.txt", "r");
    // fwrite(&s, sizeof(sur), 3, ptr);
    // fclose(ptr);
}
/*
 *output
 *data is not
 */