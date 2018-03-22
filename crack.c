/*
    crypt() password cracker.
    Handles passwords upto 5 letters. a--z/A--Z only.
    commands are as follows:
        "./crack set" -- Allows you to set a password and get a hash. Useful to getting hash passwords for testing purposes.
        "./crack hash" -- Crack the hash password given. Replace hash with your password.
        "./crack" -- Generates error message which provides you with list of available commands.

    I'd tell you not to use this for malicious/illegal purposes, but it's not like you could.
    - Lorenzo Torelli, 3/22/2018.
*/
/////////////////////////////////////
//Include libraries.
////////////////////////////////////
#define _XOPEN_SOURCE
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
/////////////////////////////////////
//Define functions
////////////////////////////////////
static void SetPassword(void);
static void CrackPassword(string argv); //Primary cracking function.
static char CrackFunc(int i, string passCracked, string passwordHash, int passIndex, string salt);
clock_t begin = 0;
/////////////////////////////////////
//Main function.
//Checks argument count, and takes arguments.
//Runs proper function depending on arguments.
////////////////////////////////////
int main(int argc, string argv[])
{
    if (argc < 1 || argv[1] == NULL)
    {
        printf("\nError! Please provide proper number of CMD arguments\n\nCommands are as follow: \n'./crack 50gGicweI/NT.' (Hash password input.)\n'./crack set' to set a new password/receive new password hash.\n");
        return 1;
    }

    if (strcmp(argv[1],"set") == 0) SetPassword();
    else CrackPassword(argv[1]);

     return 0;
}

/////////////////////////////////////
//Password cracking function.
//Sets password hash string, and initialized current password array.
//Runs nested for-loop that itterates through the alphabet (ignoring values 91-96)
//Runs CrackFunc (Function that rotates characters, and checks password.)
////////////////////////////////////
static void CrackPassword(string argv)
{
    string passwordHash = argv; //get_string("Input hash password: ");
    char salt[2] = {passwordHash[0], passwordHash[1]};
    char passwordCracked[5] = {0};

    //printf("Password is being cracked.... Please wait...Cracking %s ... Salt is: %s\n", passwordHash, salt);
    begin = clock();

    for (int i = 65; i < 122; i++)
    {
       for (int j = 65; j < 123; j++)
       {
            for (int n = 65; n < 123; n++)
            {
                for (int k = 65; k < 123; k++)
                {
                    for (int o = 65; o < 123; o++)
                    {
                        passwordCracked[0] = CrackFunc(o, passwordCracked, passwordHash, 0, salt);
                        if (o == 90) o = 96;
                    }

                   passwordCracked[1] = CrackFunc(k, passwordCracked, passwordHash, 1, salt);
                    if (k == 90) k = 96;

                }
                    passwordCracked[2] = CrackFunc(n, passwordCracked, passwordHash, 2, salt);
                    if (n == 90) n = 96;
            }
                passwordCracked[3] = CrackFunc(j, passwordCracked, passwordHash, 3, salt);
                if (j == 90) j = 96;
        }
            passwordCracked[4] = CrackFunc(i, passwordCracked, passwordHash, 4, salt);
            if (i == 90) i = 96;
    }

}

/////////////////////////////////////
//CrackFunc. Handles char rotation.
//Rotates character based on index.
//Checks equality, and exits program if equal.
//Sets passwordCracked[] to return value.
////////////////////////////////////
static char CrackFunc(int i, string passCracked, string passwordHash, int passIndex, string salt)
{

    if (isalpha(i))
    {
        passCracked[passIndex] = i;

    }
    if (strcmp(crypt(passCracked, salt), passwordHash) == 0)
    {
        //printf("Your password is: %s\n", passCracked);
        printf("%s\n", passCracked);
        //clock_t end = clock();
        //double elapsed_time = (double)(end - begin) / CLOCKS_PER_SEC;
        //printf("Time to crack: %2f\n", elapsed_time);
        exit(0);
    }
    return passCracked[passIndex];
}

/////////////////////////////////////
//Sets password.
//For testing purposes, allows you to set a key and salt.
//This provides a crypt() hash, which can be used to test the cracking functions.
////////////////////////////////////
static void SetPassword(void)
{
    string key = get_string("Input key: ");
    string salt = get_string("Input salt (recommended 50): ");

    printf("Crypt returns: %s\n", crypt(key, salt));

    exit(0);
}