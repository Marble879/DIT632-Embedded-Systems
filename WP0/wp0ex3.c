// (C) __Markus Emilio Puerto Gutiérrez, Markus Järveläinen, Younis Akel, group: 15 (2022)
// Work package 0
// Exercise 3
// Submission code: XXXXXX (provided by your TA-s)

// Includes Section
#include <stdio.h>
#include <string.h> // Included for string comparison

// Defines Section
#define HELP_FLAG "-h" //defines the help flag.
#define INFO_MESSAGE "Run the program in the terminal with one parameter containing a name\n" //defines message including information on the program functionality.
#define ERROR_MESSAGE "Error in the input! Please type -h for more information on this program\n" //defines error message in the case of invalid argument input.
#define DEFAULT_MESSAGE "Hello World! - I'm " // defines the default Hello World message that came with the exercise.

// Main function in the program, program arguments supported
void main(int argc, char *argv[])
{
    // checks if we have one argument and  if that argument is -h
    // Strcmp was used rather than == to ensure that the comparison is between the actual string value rather than their address.
    if (argc == 2 && strcmp(argv[1], HELP_FLAG) == 0)
    {
        // Print a string to the console
        printf(INFO_MESSAGE);
    }
    // checks if we either have no argument, or more than one argument
    else if (argc == 1 || argc > 2)
    {
        // Print a string to the console
        printf(ERROR_MESSAGE);
    }
    else
    {
        // Print a string to the console
        printf("%s%s!\n", DEFAULT_MESSAGE, argv[1]); // Note: double quotes
    }
}
