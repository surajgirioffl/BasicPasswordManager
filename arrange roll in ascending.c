#include <stdio.h>
#include <stdlib.h>
// arrange numbers of array in ascending order using bubble short algorithm
void arrange(int *number, int size);
// remove repeated elements from array (operation performs within single array) and return the new size of array
// int remove_repeated(int *number, int size);
// remove repeated elements from array (operation performs using 2 array) and return the new size of array. return size of global_array
int remove_repeated_2(int *number, int size);
int global_array[100]; // use by function remove_repeated_2() for adding no repeated elements of received array

int main()
{
    FILE *ptr = fopen("D://roll.txt", "r");
    FILE *p = fopen("D://arranged_roll.txt", "w");
    int roll;
    int roll_list[100];
    int i = 0;
    while (feof(ptr) == 0)
    {
        fscanf(ptr, "%d\n", &roll);
        roll_list[i] = roll;
        i++;
    }
    arrange(roll_list, i);
    // int new_size = remove_repeated(roll_list, i);
    int new_size = remove_repeated_2(roll_list, i);

    for (int j = 0; j < new_size; j++)
        fprintf(p, "%02d\n", global_array[j]);

    fprintf(p, "\nTotal number of present students = %d\n", new_size);

    // some advanced operations.
    FILE *p_popen = popen("date", "r");
    while (feof(p_popen) == 0)
    {
        int ch = fgetc(p_popen);
        fprintf(p, "%c", ch);
        if (ch == '\n')
            break;
    }

    fclose(ptr);
    fclose(p);
    fclose(p_popen);
    system("cls"); // trigring terminal
    printf("\033[1;32mOperation Successful\n\033[0m");
    system("pause");
    return 0;
}

void arrange(int *number, int size)
{
    int temp;
    // using bubble short algorithm
    for (int i = 0; i < size; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            if (number[i] > number[j])
            {
                temp = number[i];
                number[i] = number[j];
                number[j] = temp;
            }
        }
    }
}

/*
int remove_repeated(int *number, int size)
{
    for (int i = 0; i < size; i++) // for iteration of main array
    {
        for (int j = i + 1; j < size; j++) // for checking the current 'element of iteration' is matched with any other element or not
        {
            if (number[i] == number[j])
            {
                if (j = size - 1) // it's for last element
                    size--;       // means last element is repeated then we simply decreased the size by one. so last element auto removed from array
                else
                {
                    // logic:- repeated element assigned by next element and size will decreased by one
                    for (int k = j; k < size - 1; k++)
                        number[k] = number[k + 1];
                    size--;
                }
            }
        }
    }
    return size;
}
*/

int remove_repeated_2(int *number, int size)
{
    int size_of_global_array = 0;
    for (int i = 0; i < size; i++) // for iteration of main array
    {
        int check = 0;
        for (int j = 0; j <= size_of_global_array; j++)
        {
            if (global_array[j] == number[i])
            {
                check++;
                break;
            }
        }
        if (check == 0)
        {
            global_array[size_of_global_array] = number[i];
            size_of_global_array++;
        }
    }
    return size_of_global_array;
}