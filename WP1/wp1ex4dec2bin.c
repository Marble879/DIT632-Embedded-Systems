// (C) Markus Emilio Puerto Gutiérrez, Markus Järveläinen, Younis Akel, group: 15 (2022)
// Work package 1
// Exercise 4
// Submission code: 903280 (provided by your TA-s)

// Includes section
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <errno.h>

// Defines section
#define BYTE 8                                                                                       // Defines the size of 8 bits
#define SIXTEEN_BIT 16                                                                               // Defines the size of 16 bits
#define THIRTY_TWO_BIT 32                                                                            // Defines the size of 32 bits
#define SIXTY_FOUR_BIT 64                                                                            // Defines the size of 64 bits
#define EOL '\0'                                                                                     // Defines the EOL character
#define NEW_LINE '\n'                                                                                // Defines the new line character
#define HELP_FLAG "-h"                                                                               // Defines the help flag
#define INVALID_DECIMAL_SIZE "Please input a decimal value between 0 and 18446744073709551615\n"     // Defines the message that will be rpinted when the user inputs a binary value with invalid length
#define HELP_MSG "This program takes a decimal value as input argument and converts it to binary.\n" // Defines a message that will be printed when the user inputs the help flag as argument
#define INVALID_INPUT "The input is not in a correct format! Please input numbers!\n"                // Defines the message that will be printed when the input value is not a binary number
#define LIMIT_REACHED "The input value is greater than the max value of 18446744073709551615\n"      // Defines the message that will be printed when the input value exceeds the program limits.

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
    else if (argc == 1)
    {
        printf(INVALID_INPUT);
        return 2;
    }

    // Loop through the argument array to check if the numbers are in correct format
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (!(argv[1][i] >= '0' && argv[1][i] <= '9'))
        {
            printf(INVALID_INPUT);
            return 2;
        }
    }

    errno = 0;                                         // Used for error handling
    unsigned long number = strtoul(argv[1], NULL, 10); // converts string to unsinged long and assigns it
    // Checks if the number is above the max range. Reference https://stackoverflow.com/questions/11279767/how-do-i-make-sure-that-strtol-have-returned-successfully
    if ((number == ULONG_MAX) && errno == ERANGE)
    {
        // Prints error message when value is greater than ULONG_MAX
        printf(LIMIT_REACHED);
        // Exits code
        return 2;
    }

    int arraySize; // Defines variuable that will be assigned the array size

    // If the number input is more than 15 and less than or equal to 255, make the array size 8.
    if (number <= UCHAR_MAX)
    {
        arraySize = BYTE; // Sets the array size to BYTE
    }
    // If the number input is more than 255 and less than or equal to 65535, make the array size 16.
    else if (number > UCHAR_MAX && number <= USHRT_MAX)
    {
        arraySize = SIXTEEN_BIT; // Sets the array size to SIXTEEN_BIT
    }
    // If the number input is more than 65535 and less than or equal to 4294967295, make the array size 32.
    else if (number > USHRT_MAX && number <= UINT_MAX)
    {
        arraySize = THIRTY_TWO_BIT; // Sets the array size to THIRTY_TWO_BIT
    }
    // If the number input is more than 4294967295 and less than or equal to 18446744073709551615, make the array size 64.
    else if (number > UINT_MAX && number <= ULONG_MAX)
    {
        arraySize = SIXTY_FOUR_BIT; // Sets the array size to SIXTY_FOUR_BIT
    }

    // The binary array is initialized with the correct amount of bits
    char binaryArray[arraySize + 1]; // increment by 1 to include end of line

    // Loops through the binary array in reverse order, and assigns 1 or 0 accordingly
    for (int i = arraySize - 1; i >= 0; i--)
    {
        // Both calculation operations below are referenced from: https://www.javatpoint.com/c-program-to-convert-decimal-to-binary. Since binary is Base-2, we mod by 2 and hence the remainder will be either a 1 or a 0.
        // Reference: https://www.delftstack.com/howto/c/convert-int-to-char/ to convert the int to a char.
        binaryArray[i] = (number % 2) + '0';
        // Divides the number by two.
        number = number / 2;
    }
    // Assign end of line to end of array so print statement knows end of string
    binaryArray[arraySize] = EOL;

    printf("%s", binaryArray);

    // Ends the line after full array has been printed
    printf("%c", NEW_LINE);

    // Echo to terminal for pipeline
    system("echo $binaryArray");

    // Exits program if the conversion was successful
    return 0;
}
