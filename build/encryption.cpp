#include <iostream>
#include <string.h>
#include <stdlib.h>
using namespace std;
/*encrypt the password*/
class encryption
{
    int lengthOfPassword; // length of the password
    /***********general function used in encryption**************/

    /*take base and exponent as arguments and returns the power. the pow() function returns in double and creating some issue. So, I have created my own function*/
    int power(int base, int exponent)
    {
        /*using recursion*/
        if (exponent == 0)
            return 1;
        else if (exponent == 1)
            return base;
        else
            return base * power(base, --exponent);
    }

    /*takes argument of string and reverse that string*/
    void reverseString(char *string)
    {
        char *tempString = (char *)calloc(strlen(string) + 1, sizeof(char)); //+1 for NULL
        int j = 0;                                                           // for index of tempString
        /*traversing from end to reverse the string*/
        for (int i = strlen(string) - 1; i >= 0; i--, j++) //-1 because array started from zero
            tempString[j] = string[i];
        tempString[j] = '\0'; // adding NULL in last of string

        /*now copying reverse string to original string*/
        strcpy(string, tempString);
        free(tempString); // free memory
    }

    /*reverse the number received via argument and returns the reversed number*/
    int reverseNumber(int number)
    {
        int reverse = 0;
        while (number > 0)
        {
            int r = number % 10; // for remainder
            reverse = (reverse * 10) + r;
            number /= 10;
        }
        return reverse;
    }

    /*returns the sum of digits of passed number*/
    int sumOfDigits(int number)
    {
        int sum = 0; // for some of digits
        while (number > 0)
        {
            int r = number % 10; // for remainder
            sum += r;
            number /= 10;
        }
        return sum;
    }

    /**********functions for encryption************/

    /*Take arguments of string (must each character b/w '0' to '9'). convert string to number. e.g string is 1,2,3,4,\0 then it returns 1234. If string is correct then returns number in long else on error it returns -1. We can use atoi() function of library but I have created my own*/
    long stringToNumber(char *string)
    {
        /**
         * e.g let string is '1','2','3','\0' then length 3.
         * we started from last character i.e 3.
         * number = 3*(10^0)=3
         * number = number i.e 3 + 2*(10^1)=23
         * number = number i.e 23 + 1*(10^2)=123
         * and 123 is our required number
         */
        long requiredNumber = 0;
        short length = strlen(string);
        short exponent = 0;
        int i;
        // 0-9 in ASCII are 48 to 57
        for (i = length - 1; i >= 0 && string[i] >= '0' && string[i] <= '9'; i--) // length-1 because array started from zero. So, last element of string will be length-1
        {
            short number = (int)string[i] - 48; // e.g for 1 it will 49-48
            requiredNumber = requiredNumber + number * power(10, exponent);
            exponent++;
        }
        if (i == -1) // on successfully conversion
            return requiredNumber;
        return -1; // on error
    }

    /*take argument of a decimal number and convert it to hexadecimal and save as string in received char* convertedDataInHex*/
    void convertDecimalToHex(int number, char *convertedDataInHex)
    {
        int i = 0; // for index of array
        while (number != 0)
        {
            int r = number % 16; // for remainder
            number /= 16;        // for quotient
            if (r <= 9)
                convertedDataInHex[i++] = 48 + r; // we have to store in character 0-9 i.e 48 - 57 (ASCII) not in number directly. If we assign r=6 then it will stored as ASCII 6 which is unprintable chars
            else                                  // i.e if (r >= 10)
                convertedDataInHex[i++] = 55 + r; // we have to print r as character from A-E
            /*55 Because
             *In hexadecimal if remainder is 10 then it will 'A', for 11 it will 'B' and so on till for '15' it will 'F'.
             *so simply I have used ASCII. If r=10 means 'A' then add r in 55 i.e 55+10 = 65 = 'A' (ASCII)
             */
        }
        convertedDataInHex[i] = '\0'; // adding NULL in last of string
        /*bottom to up i.e last to 1st remainders are used to be written in hexadecimal*/
        /*so simply reverse the array*/
        reverseString(convertedDataInHex);
    }

    /*take argument of a decimal number and convert it to binary and sve as string in received char* convertedDataInBinary*/
    void convertDecimalToBinary(int number, char *convertedDataInBinary)
    {
        int i = 0; // for index of array
        while (number != 0)
        {
            int r = number % 2;                  // for remainder
            number /= 2;                         // for quotient
                                                 /*r will be always 0 or 1*/
            convertedDataInBinary[i++] = r + 48; // we have to print r as character from 48 to 49 (i.e 0 to 1)
                                                 /*if we write directly r for assign then 'convertedDataInBinary' is char*. So, r will taken as character i.e in ASCII. Let r=6 then it will taken as ASCII 6 but we have write it as '6'*/
        }
        convertedDataInBinary[i] = '\0'; // adding NULL in last of string
                                         /*bottom to up i.e last to 1st remainders are used to be written in binary*/
        /*so simply reverse the array*/
        reverseString(convertedDataInBinary);
    }

    /**
     *base encryption i.e encryption of received character for first time.
     *take argument of character and after basic encryption returns the encrypted character
     */
    char baseEncryption(char ch)
    {
        /*most possible characters are a-z,A-Z,0-9 and basic symbols and these are mainly from 32-126 ASCII*/
        if (lengthOfPassword <= 10)
        {
            if (ch <= 60) // 60 is ASCII
                ch += lengthOfPassword * 4;
            else if (ch <= 100) // 100 is ASCII
                ch -= lengthOfPassword * 2;
            else if (ch <= 126) // 126 is ASCII
                ch -= lengthOfPassword * 3;
        }
        // else if (lengthOfPassword <= 20)
        // {
        //     if (ch <= 60) // 50 is ASCII
        //         ch += lengthOfPassword + sumOfDigits(lengthOfPassword);
        //     else if (ch <= 100) // 100 is ASCII
        //         ch -= lengthOfPassword;
        //     else if (ch <= 126) // 126 is ASCII
        //         ch -= ;
        // }
    }

public:
    /**
     *take password in 'password' and after encryption, assign the encrypted password in variable 'encryptedPassword' which is received via argument and returns the address of 'encryptedPassword'. Returning is compulsory because address may be changed in case dynamic memory allocation
     *Currently all characters are allowed in password. But I have found that ASCII value after 126 are not printing on powershell/cmd.
     *after operation must free the memory allocated for 'encryptedPassword'.
     */
    long *encryptPassword(char *password, long *encryptedPassword)
    {
        // encryptedPassword = NULL; // pointed to NULL. So, realloc allocate memory else realloc() behavior will be undefined. (If long* pointing anywhere which is not allocated by malloc/calloc/realloc)
        lengthOfPassword = strlen(password);
        int spaceRequired = 0;   // for dynamic memory allocation of 'encryptedPassword'. For each integer we will allocate space dynamically because we dont' know what will the size of the password by user and the size of hexadecimal returned and others
        int encryptionIndex = 0; // index for long* encryptedPassword
        // encryptedPassword[encryptionIndex++] = lengthOfPassword; /*we have already allocated one unit of memory for 'encryptedPassword' in calling function for base address. So, we are assigning the length of password without allocating any extra space*/

        /*
         **ENCRYPTION STEPS FOR ONE CHARACTER OF PASSWORD**
         *step:0. assign the length of password as the 1st character of 'encryptedPassword'
         *step:1. reverse whole password
         *step:2. baseEncryption of character
         *step:3. convert that character to hexadecimal
         *step:4. convert all characters of received hex to binary (for each sub character of hex)
         *step:5. convert binary of each sub-character into single number
         *step:6. reverse the number and save
         *step:7. similary save the all reversed number of binary of each sub-character of hex and after completion of each single character of password, terminate it by '\r' for identification of one character encryption completed.
         ** FOLLOW THE SAME ABOVE 7 STEPS FOR EACH CHARACTER
         */

        /*
         **assign the length of password as the 1st character of 'encryptedPassword'
         **HOW ENCRYPTION WORKING (STEP BY STEP..)................................................................
         *1. let password is "suraj";
         *2. revered. Now password = "jarus";
         **-------**ALL BELOW STEPS IS FOR 'j' i.e 1st character. same steps will be iterated for next characters
         *3. Base encryption of 'j' (ASCII = 106). length of password = 5; so, j=106-15=91 ('['). Now all encryption will be perform on ASCII 91
         *4. Convert 91 to hexadecimal. result=5,11 i.e 5,B and it stored in string as {'5','B','\0'} i.e in ASCII {53,66,0}
         **now convert all sub-character of hex i.e result[0,1] each to binary.
         *5. Binary of result[0] i.e 53 is {'1','1','0','1','0',1','\0'}.
         *6. now convert the binary of result[0] to number i.e 1101010.
         *7. reverse the number i.e 0101011 (1s complement of binary)
         *8. save in 1st shell of long* encryptedPassword
         ** now perform the same operation (step 5 to 7) for all other sub-character of hex i.e till result[last index].
         *9. while(result[i]!=result[last_index]), continue the loop from step 5 to 8 for nex sub-character of hex
         *10. Add an extra character '\r' in end of encryption of 1st char for identification of end of one character
         **ITERATE FROM STEP 3 TO 10 FOR NEXT CHARACTERS OF PASSWORD
         **And in last add '\0' to identify the end of long* encryptedPassword
         */

        reverseString(password); /****step 1*****/
        /*now encrypting each character one by one */
        for (int i = 0; password[i] != '\0'; i++) //'i' for each character of password
        {
            password[i] = baseEncryption(password[i]); /****step 2****/
            /*for each character*/
            char tempString[40];  // contains complete hex of current character
            char tempString2[40]; // contains binary of one sub-character of current hex

            /* tempString contains the hex of one character*/
            convertDecimalToHex(password[i], tempString); /****step 3****/
            /*now converting each data i.e sub-character of hex to binary*/
            for (int j = 0; tempString[j] != '\0'; j++) //'j' for each sub-character of hex
            {
                /*tempString2 contains the binary of one character of hex i.e sub-character of one character of password*/
                convertDecimalToBinary(tempString[j], tempString2); /****step 4****/
                /*allocating memory for encryptedPassword each time*/
                encryptedPassword = (long *)realloc(encryptedPassword, sizeof(long) * ++spaceRequired);
                if (encryptedPassword == NULL)
                    cout << "\033[1;31mMemory not allocated" << endl; // for testing purposes
                /*now converting the binary into single number to store in one block of long type*/
                encryptedPassword[encryptionIndex++] = reverseNumber(stringToNumber(tempString2)); // here tempString2 contains binary of one sub-character of hex
                // it's better to add 1 more step i.e multiply each digit of reversed number to length^i and i-- for next digit
                /****step 5 and 6 completed****/
                /// testing
                cout << "i=" << i << "->" << encryptedPassword[encryptionIndex - 1] << endl;
                memset(tempString2, 0, sizeof(tempString2)); // assigning all characters of string2 to 0. So, it will be totally empty for storing the binary for next sub-character of hex. Actually It's not necessary step because we are assigning the character of binary in it and in last we add NULL.
            }                                                /*after termination of this loop all sub-character of hex will be encrypted by next algorithm and encryption of current character of password will completed.*/

            /**
             *after encrypting one character we have to add an indicator which indicates the end of 1st character.
             *It will help in decrypting the password later.
             *In end of each character of password, we are using '\r' i.e 13 (ASCII) after it for indication
             */
            encryptedPassword = (long *)realloc(encryptedPassword, sizeof(long) * ++spaceRequired);
            encryptedPassword[encryptionIndex++] = '\r'; /*step 7 completed*/
        }
        /*After end of all characters, for identification of end of password we are inserting '\0' i.e 0 (ASCII) after last character*/
        encryptedPassword = (long *)realloc(encryptedPassword, sizeof(long) * ++spaceRequired);
        encryptedPassword[encryptionIndex++] = '\0';
        return encryptedPassword;
        // // testing
        // for (int i = 0; encryptedPassword[i] != '\0'; i++)
        // {
        //     if (encryptedPassword[i] == '\r')
        //         cout << "- ";
        //     else
        //         cout << encryptedPassword[i] << " ";
        // }
    }

    //// password is allowed only if characters are b/w 32 to 126 (ASCII)
    ////32 to 126 because only these characters are visible on console of cmd/powershell
    // /*returns true if received character is valid for encryption else returns false*/
    // bool isValidForEncryption(char ch)
    // {
    //     /*characters are allowed b/w 32 to 126 (ASCII) for the encryption algorithm of this program*/
    //     if (ch > 31 && ch < 127)
    //         return true; // valid
    //     return false;    // invalid
    // }
};

/*decrypt the password which is encrypted by the class encryption of this program*/
class decryption
{
};

int main()
{
    system("cls");
    encryption obj;
    long *encryptedPassword = (long *)malloc(sizeof(long)); // we will allocate space dynamically as per need.
    char var[100];
    cout << "write password:" << endl;
    cin.getline(var, 10);
    cout << "Address= " << (int)encryptedPassword << endl; // testing
    encryptedPassword = obj.encryptPassword(var, encryptedPassword);
    cout << "\nAddress= " << (int)encryptedPassword << endl; // testing
    cout << "encrypted password = ";
    for (int i = 0; encryptedPassword[i] != '\0'; i++)
    {
        if (encryptedPassword[i] == '\r')
            cout << "- ";
        else
            cout << encryptedPassword[i] << " ";
    }
    free(encryptedPassword);
    cout << "\n";
    // encryptionClassFriend(obj, var);
    // system("pause");
}