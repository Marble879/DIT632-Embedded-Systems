// (C) Markus Emilio Puerto Gutiérrez, Markus Järveläinen, Younis Akel, group: 15 (2022)
// Work package 1
// Exercise 4
// Submission code: XXXXXX (provided by your TA-s)

// Include section
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// Defines section
#define HEXADECIMAL_MSG "Hexadecimal number: "                                                                                                         // Defines the message to be displayed before printing the hexadecimal number
#define NEW_LINE '\n'                                                                                                                                  // Defines the new line character
#define NIBBLE 4                                                                                                                                       // Defines the length of a nibble
#define INITIAL_EXPONENT 3                                                                                                                             // Defines the initial exponent for when binary is converted to decimal
#define BASE 2                                                                                                                                         // Defines the base for when binary is converted to decimal
#define HELP_FLAG "-h"                                                                                                                                 // Defines the help flag
#define HELP_MSG "This program takes a binary value as input argument and converts it to hexadecimal.\n"                                               // Defines a message that will be printed when the user inputs the help flag as argument
#define INVALID_BINARY_LENGTH "The binary value is not of the right length, please input a binary value where the number of bits is a multiple of 4\n" // Defines the message that will be printed when the user inputs a binary value with invalid length
#define INVALID_INPUT "The input is not in a correct format! Please input 1s and/or 0s and try again\n"                                                // Defines the message that will be printed when the input value is not a binary number
#define EOL '\0'                                                                                                                                       // Defines end of line character
// Method to turn binary to hexadecimal and output the hexadecimal value
void convertBinToHex(int size, int *intArr)
{
    // Variable section
    int iteration = 0;              // Initializes the number of iterations
    int i = 0;                      // Initializes the index used by the while loop
    int sumArrSize = size / NIBBLE; // Initializes the array size to store the sums of four bits
    int sumArr[sumArrSize];         // Declare an array of size sumArrSize

    // While loop that will go through the binary bits four bits at a time
    while (i < size)
    {
        int sum = 0;                     // Initialize the variable to store the sum of four bits
        int limit = i + NIBBLE;          // Initialize the looping limit of an array to assist in slipping the array into nibbles
        double power = INITIAL_EXPONENT; // Initialize the starting power used in the sum calculation of nibbles
        // Convert binary to decimal and store results in an array.
        for (int j = i; j < limit; j++)
        {
            // Check if the bit is 1
            if (intArr[j] == 1)
            {
                // If the bit is 1, then add 2^power to the sum
                sum = sum + ((int)(pow(BASE, power)));
            }
            // Reduce the power by one as we are looping through the array from left to right.
            power--;
        }
        sumArr[iteration] = sum; // We put the sum of the four bits in decimal form
        i = i + NIBBLE;          // Add four to the index since we move by four numbers
        iteration++;             // Add one to the iteration to keep count
    }

    // Print the hexadecimal message
    printf("%s", HEXADECIMAL_MSG);

    // Print all the hexadecimal values in order
    for (int i = 0; i < sumArrSize; i++)
    {
        // Print the hexadecimal in position i
        printf("%X", sumArr[i]);
    }
    // Prints a new line for readability
    printf("%c", NEW_LINE);
}

// Main function in the program - arguments supported.
int main(int argc, char *argv[])
{
    // Checks if there is an argument and if this argument is the help flag.
    if (argc == 2 && strcmp(argv[1], HELP_FLAG) == 0)
    {
        // Output the help message
        printf(HELP_MSG);
        // Exit the program with no error;
        return 0;
    }
    // Checks if no arguments are input
    else if (argc == 1)
    {
        // Print invalid input message
        printf(INVALID_INPUT);
        // Exit program and return 2
        return 2;
    }

    // Variable section
    int size = strlen(argv[1]); // Stores the string length of the argument into a variable called size
    int intArr[size];           // Declares an array of integers with the length of the size variable

    // Loop through the argument array to check if the bits are in correct format
    for (int i = 0; i < size; i++)
    {
        // If statement that checks if the digit isa 0 or a 1
        if ((argv[1][i] != '0' && argv[1][i] != '1'))
        {
            // Output invalid input
            printf(INVALID_INPUT);
            // Exit program and return 2
            return 2;
        }
    }

    // Check if the number of bits is correct
    if (size % NIBBLE != 0)
    {
        // Output invalid input length
        printf(INVALID_BINARY_LENGTH);
        // Exit program and return 2
        return 2;
    }

    // Convert string array into an array of digits.
    for (int i = 0; i < size; i++)
    {
        int j = (argv[1][i] - '0'); // Convert character into digit. Reference: https://stackoverflow.com/questions/628761/convert-a-character-digit-to-the-corresponding-integer-in-c/32298334
        intArr[i] = j;              // Assign the int value to element i of the intArr
    }

    // Calls the method to convert the binary number to hexadecimal
    convertBinToHex(size, intArr);

    // returns 0 value
    return 0;
}