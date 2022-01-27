// (C) Markus Emilio Puerto Gutiérrez, Markus Järveläinen, Younis Akel, group: 15 (2022)
// Work package 1
// Exercise 2
// Submission code: XXXXXX (provided by your TA-s)

// Includes Section
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>

// Defines Section
#define MAX 50                                                                                                                                            // defines max array size.
#define INPUT_REQUEST_MSG "Please input a string you want to encrypt:\n"                                                                                  // defines the input request message
#define CONTINUE "Type another text or use OS EOF:\n"                                                                                                     // defines message whentext has been encrypted
#define NEW_WORD "New word: %s"                                                                                                                           // defines a message for printing the new word
#define EOL '\0'                                                                                                                                          // defines EOL character
#define NEW_LINE '\n'                                                                                                                                     // defines the new line character
#define SPACE_WHITESPACE ' '                                                                                                                              // defines a space
#define END_CHAR_LOWER 'z'                                                                                                                                // defines the final letter in the alphabet (in lower case)
#define END_CHAR_UPPER 'Z'                                                                                                                                // defines the final letter in alphabet (in upper case)
#define INVALID_ARGUMENTS_MSG "Invalid input arugments! Please enter an integer value between 0 and maximum of an unsigned long type\n"                   // Defines the message to be displayed if an invalid argument is passed from the terminal.
#define INVALID_STRING_MSG "Invalid string input. Please input a string containing characters between a-z or A-Z (NOTE: sentences are also permitted).\n" // Defines the message to be displayed if a string with invalid characters is input.
#define STRING__OVERFLOW_MSG "Input too large! Please input less than %d characters!\n"                                                                   // Defines the message to be displayed if a string has too many characters
#define NEGATIVE '-'                                                                                                                                      // Defines the negative symbol

// Method to shift the character given in the parameter
char characterShifter(char cToShift, int numShifts)
{
    // Loop that shifts the character to the right position
    for (int i = 0; i < numShifts; i++)
    {
        // Checks whether the end of the alphabet is reached and handles it accordingly.
        if ((cToShift == END_CHAR_LOWER || cToShift == END_CHAR_UPPER))
        {
            // Character loops back and becomes a or A.
            cToShift = cToShift - 25; // counts as one move forward.
        }
        else
        {
            // Increment the character by 1 if it is not yet z or Z
            cToShift = cToShift + 1;
        }
    }
    return cToShift; // Return the shifted character
}

// Main function in the program
int main(int argc, char *argv[])
{
    // Check if no terminal arguments were passed
    if (argc < 2)
    {
        // Output invalid argument message
        printf(INVALID_ARGUMENTS_MSG);
        // Exit program with error status
        return 1;
    }

    // Variable declarations
    char charToShift;                                          // Declare variable that will take user input to be encyrpted.
    char shifted;                                              // Declare variable which will store the char to be shifted
    char stringToShift[MAX];                                   // Declare array that is of size MAX (50)
    char *endPtr;                                              // Declared to be used as a parameter for validation
    errno = 0;                                                 // Set errno to 0 for validation check. This is done to ensure that errno is reset to 0 incase any other programs have previously failed. Reference: https://unix.stackexchange.com/questions/187886/why-to-set-errno-to-zero-at-the-time-of-initialization-of-the-program-and-cant
    unsigned long numOfShifts = strtoul(argv[1], &endPtr, 10); // Assigned an integer value from terminal arguments. Defined as unsigned long to use standard strtoul() method that allows for validation.

    // Check if the endPtr of conversion is equivalent to the arugment received. This checks if it was even possible to parse the received arguments. reference: https://stackoverflow.com/questions/11279767/how-do-i-make-sure-that-strtol-have-returned-successfully
    if (argv[1] == endPtr)
    {
        // Output invalid argument message
        printf(INVALID_ARGUMENTS_MSG);
        // Exit program with error status
        return 1;
    }
    // Check if the arguments passed are less than 0 or larger than unsigned long maximum. The manual check of negative was done as errno was not set to ERANGE when negative values were passed as arguments.
    if (errno == ERANGE || argv[1][0] == NEGATIVE)
    {
        // Output invalid argument message
        printf(INVALID_ARGUMENTS_MSG);
        // Exit program with error status
        return 1;
    }

    // Output a message requesting a user input
    printf(INPUT_REQUEST_MSG);

    // While EOF has not been inputted, keep looping and retreiving user input.
    while (fgets(stringToShift, MAX, stdin) != NULL)
    {
        // Checks that the string is not empty! NOTE: whitespaces such as tabs etc are covered in the next check
        if (stringToShift[0] == NEW_LINE || stringToShift[0] == EOL || stringToShift[0] == SPACE_WHITESPACE)
        {
            // output invalid string error message
            printf(INVALID_STRING_MSG);
            // exit program with error
            return 1;
        }
        // Check if the string has overflown. If there is an overflow, the last element would not be '\0'.
        if (stringToShift[strlen(stringToShift) - 1] != NEW_LINE)
        {
            // output invalid string error message
            printf(STRING__OVERFLOW_MSG, MAX);
            // exit program with error
            return 1;
        }
        for (int i = 0; i < strlen(stringToShift); i++)
        {
            // if the string contains other values from a-z, A-Z and spaces between characters, then  exit the program
            if (isalpha(stringToShift[i]) == 0 && stringToShift[i] != SPACE_WHITESPACE && stringToShift[i] != NEW_LINE && stringToShift[i] != EOL)
            {
                // output invalid string error message
                printf(INVALID_STRING_MSG);
                // exit program with error
                return 1;
            }
        }

        // Read from the buffer the string we want to shift.
        for (int i = 0; i < sizeof(stringToShift); i++)
        {
            charToShift = stringToShift[i]; // Assign the character that may be shifted from the input string.
            // Check if we have reached the new line or end of string
            if (charToShift == EOL || charToShift == NEW_LINE)
                // Break out of loop once \0 or \n occurs.
                break;
            // If there is no space, then shift the character, else leave the space as is.
            if (charToShift != SPACE_WHITESPACE)
            {
                // Shift characters by the number of shifts
                shifted = characterShifter(charToShift, numOfShifts);
                // Replace value in array with shifted value
                stringToShift[i] = shifted;
            }
        }
        // Output shifted string
        printf(NEW_WORD, stringToShift);

        // Output input prompt
        printf(CONTINUE);
    }

    // Exits program
    return 0;
}