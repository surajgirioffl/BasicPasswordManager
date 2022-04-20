#include <stdio.h>
#include <stdlib.h>
#include "D:\\C Language\\All C Programs\\1) Cxxdroid Application\\Repositories\\C Language Special\\C_Language_Projects\\Header Files Used In this Repository\\color.h"

int main()
{
    system("pause");
    printf("====3 bit color combinations for foreground are following:====\n");

    black('f'); // ch for f/F or b/B
    printf("1 Suraj Kumar Giri ==> \"\\033[1;30m\"\n");

    red('f');
    printf("2 Suraj Kumar Giri ==> \"\\033[1;31m\"\n");

    green('f');
    printf("3 Suraj Kumar Giri ==> \"\\033[1;32m\"\n");

    yellow('f');
    printf("4 Suraj Kumar Giri ==> \"\\033[1;33m\"\n");

    blue('f');
    printf("5 Suraj Kumar Giri ==> \"\\033[1;34m\"\n");

    magenta('f');
    printf("6 Suraj Kumar Giri ==> \"\\033[1;35m\"\n");

    cyan('f');
    printf("7 Suraj Kumar Giri ==> \"\\033[1;36m\"\n");

    white('f');
    printf("8 Suraj Kumar Giri ==> \"\\033[1;37m\"\n\n");
    // reset
    printf("To reset all color: ");
    printf("\033[0mSuraj Kumar Giri ==> \"\\033[0m\"\n");
    // underline
    printf("To underline text:  ");
    printf("\033[4mSuraj Kumar Giri ==> \"\\033[4m\"\n");

    reset(); // to reset all color currently using by control
    printf("\n\n===8 Bit Color Combinations for foreground are following:===\n");
    for (int n = 0; n <= 255; n++)
    {

        printf("\033[38;5;%dm", n);
        printf("%d Suraj Kumar Giri ==> \"\\033[38;5;%dm\"\n\n", n, n);
    }
    system("pause");
}