// (C) Markus Emilio Puerto Gutiérrez, Markus Järveläinen, Younis Akel, group: 15 (2022)
// Work package 1
// Exercise 1
// Submission code: XXXXXX (provided by your TA-s)

// Includes Section
#include <stdio.h>

// Define Section
#define REQUEST_MSG "Enter a number between 1-5:\n"                                 // Input request message defintion.
#define SENTENCE_1 "You have picked the right number\n"                             // Scentence 1 definition
#define SENTENCE_2 "You have picked the best number.\n"                             // Scentence 2 definition
#define SENTENCE_3 "How are you doing today?\n"                                     // Scentence 3 definition
#define SENTENCE_4 "Knock, knock. Who's there?\n"                                   // Scentence 4 definition
#define SENTENCE_5 "If KFC ran a linux system it would be called Kernel Sanders.\n" // Scentence 5 definition
#define EXITING_MSG "Exiting...\n"                                                  // Exiting program message definition.
#define INVALID_TYPE_MSG "Invalid Type input received. Exiting...\n"                // Invalid type message definition

// Main function in the program, no program arguments supported
int main(void)
{
    // variable declarations
    int menuOption; // Declaring variable for user input menu option
    char term;      // Declaring variable for user input validation

    // Loops the code and only exits the loop once a value that is not between 1 and 5 inclusive is received as input.
    do
    {
        // Print message to user asking for an input between 1-5
        printf(REQUEST_MSG);

        // Checks if the input is of type int
        // Takes the input of the user. First check ensures that if the first value in the buffer is
        // not an int, scanf() returns 0. If the second value in the buffer is of type char (and the first /// value is of type int), then the check returns a 2. If the previous scentence occurs, then we // /// also need to ensure that if "term" is not EOL, the "invalid type" message is displayed.
        // reference: https://stackoverflow.com/questions/4072190/check-if-input-is-integer-type-in-c
        if (scanf("%d%c", &menuOption, &term) == 0 || term != '\n')
        {
            // Print invalid type message and exit program
            printf(INVALID_TYPE_MSG);
            return 0;
        }

        // Checks if the input is equal to either 1,2,3,4,5 and outputs a corresponding response.
        if (menuOption == 1)
        {
            // Print the string connected to input 1 to the console
            printf(SENTENCE_1);
        }
        else if (menuOption == 2)
        {
            // Print the string connected to input 2 to the console
            printf(SENTENCE_2);
        }
        else if (menuOption == 3)
        {
            // Print the string connected to input 3 to the console
            printf(SENTENCE_3);
        }
        else if (menuOption == 4)
        {
            // Print the string connected to input 4 to the console
            printf(SENTENCE_4);
        }
        else if (menuOption == 5)
        {
            // Print the string connected to input 5 to the console
            printf(SENTENCE_5);
        }
        else
        {
            // Print Exiting message and exit code
            printf(EXITING_MSG);
            return 0;
        }
    } while (menuOption >= 1 && menuOption <= 5); // Checks that the limits of 1 and 5 are not exceeded.
    // Exit code.
    return 0;
}