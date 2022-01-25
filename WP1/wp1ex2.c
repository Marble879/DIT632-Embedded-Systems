// (C) Markus Emilio Puerto Gutiérrez, Markus Järveläinen, Younis Akel, group: 15 (2022)
// Work package 1
// Exercise 2
// Submission code: XXXXXX (provided by your TA-s)

// Includes Section
#include <stdio.h>
#include <stdlib.h>

// Defines Section
#define MAX 50                                                           // defines max array size.
#define INPUT_REQUEST_MSG "Please input a string you want to encrypt:\n" // defines the input request message
#define CONTINUE "Type another text or use OS EOF:\n"                    // defines message whentext has been encrypted
#define NEW_WORD "New word: %s"                                          // defines a message for printing the new word
#define EOL '\0'                                                         // defines EOL character
#define NEW_LINE '\n'                                                    // defines the new line character
#define SPACE_WHITESPACE ' '                                             // defines a space
#define END_CHAR_LOWER 'z'                                               // defines the final letter in the alphabet (in lower case)
#define END_CHAR_UPPER 'Z'                                               // defines the final letter in alphabet (in upper case)

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
    // Variable declarations
    char charToShift;                // Declare variable that will take user input to be encyrpted.
    int numOfShifts = atoi(argv[1]); // Assigned an integer value from terminal arguments.
    char shifted;                    // Declare variable which will store the char to be shifted
    char stringToShift[MAX];         // Declare array that is of size MAX (50)

    // Output a message requesting a user input
    printf(INPUT_REQUEST_MSG);

    // While EOF has not been inputted, keep looping and retreiving user input.
    while (fgets(stringToShift, MAX, stdin) != NULL)
    {
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
                //Shift characters by the number of shifts
                shifted = characterShifter(charToShift, numOfShifts);
                // Replace value in array with shifted value
                stringToShift[i] = shifted;
            }
        }
        //Output shifted string
        printf(NEW_WORD, stringToShift);

        //Output input prompt
        printf(CONTINUE);
    }

    // Exits program
    return 0;
}