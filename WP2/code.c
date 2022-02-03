// (C) Markus Emilio Puerto Gutiérrez, Markus Järveläinen, Younis Akel, group: 15 (2022)
// Work package 2
// Exercise 4
// Submission code: 941100 (provided by your TA-s)

// Includes Section
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>
#include <math.h>

// Define Section
#define ERROR_MSG "Wrong amount of arguments.\n"           // Define the error message when amount of arguments is wrong
#define INVALID_ARGUMENT "Wrong argument in position %d\n" // Define the error message when argument is incorrect
#define CORRECT_ARG_COUNT 6                                // Define the number of arguments supported
#define HEX_PRINT_MSG "Hexadecimal Number: %X\n"           // Defines message for printing hexadecimal values

// Function declarations
int validateArguments(char argToValidate[], int position); // Declare function to validate the initial arguments

/* ============ VALIDATION SECTION ========================= */

// Function implementation int validateArguments(char argToValidate[], int position);
int validateArguments(char argToValidate[], int position)
{
    // Checks if the length of the argument is not equal to 1 and prints an error message
    if (strlen(argToValidate) != 1)
    {
        // output invalid message
        printf(INVALID_ARGUMENT, position);
        // return error status
        return 1;
    }
    // NOTE: we read input left to right here! (MSB to LSB!)
    // If in position 1, 4, or 5 we need to check that its only 1 character and its
    if (position == 1 || position == 4 || position == 5)
    {
        // Checks if the argument contains the correct digits
        if (argToValidate[0] != '0' && argToValidate[0] != '1')
        {
            // output invalid message
            printf(INVALID_ARGUMENT, position);
            // return error status
            return 1;
        }
    }
    // if statement for position 2
    else if (position == 2)
    {
        // Check if arguments are in correct format
        if (argToValidate[0] < '0' || argToValidate[0] > '4')
        {
            // output invalid message
            printf(INVALID_ARGUMENT, position);
            // return error status
            return 1;
        }
    }
    // if statement for position 3
    else
    {
        // Check if arguments are in correct format
        if (argToValidate[0] < '0' || argToValidate[0] > '2')
        {
            // output invalid message
            printf(INVALID_ARGUMENT, position);
            // return error status
            return 1;
        }
    }
}

/* ===================== MAIN ============================ */

// Main function in the program, arguments are supported
int main(int argc, char *argv[])
{

    // Checks if the arguments are of size 5
    if (argc != CORRECT_ARG_COUNT)
    {
        // Prints an error message
        printf(ERROR_MSG);
        // Exits the program with return value 1
        return 1;
    }

    // Loop for validating each char in the argument
    for (int i = 1; i < 6; i++)
    {
        // Calls validateArguments and checks for return value 1
        if (validateArguments(argv[i], i) == 1)
            // Exits with error code
            return 1;
    }

    unsigned char a_byte = 0b00000000; // Declare and initialize an unsigned char
    unsigned char temp_byte;           // Declare temp_byte
    // Loop through arguments
    for (int i = 1; i < 6; i++)
    {
        // If it is the first argument, shift it to end
        if (i == 1)
            // shift bit of argument by 7
            temp_byte = (argv[i][0] - '0') << 7;
        // If it is second argument, shift approriately
        if (i == 2)
            // shift bit of argument by 4
            temp_byte = (argv[i][0] - '0') << 4;
        // If it is third argument, shift appropriately
        if (i == 3)
            // shift bit of argument by 2
            temp_byte = (argv[i][0] - '0') << 2;
        // If it is fourth argument, shift appropriately
        if (i == 4)
            // shift bit of argument by 1
            temp_byte = (argv[i][0] - '0') << 1;
        // If it is fith argument, shift appropriately
        if (i == 5)
            // No need to shift bit as it is first bit
            temp_byte = (argv[i][0] - '0');
        // Bitwise OR to combine results
        a_byte = a_byte | temp_byte;
    }
    // Print the hexidecimal number
    printf(HEX_PRINT_MSG, a_byte);
    // Exit the program with return value 0
    return 0;
}