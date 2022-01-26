// (C) Markus Emilio Puerto Gutiérrez, Markus Järveläinen, Younis Akel, group: 15 (2022)
// Work package 1
// Exercise 4
// Submission code: XXXXXX (provided by your TA-s)

// Includes section
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Defines section
#define NIBBLE 4          // Defines the size of 4 bits
#define BYTE 8            // Defines the size of 8 bits
#define SIXTEEN_BIT 16    // Defines the size of 16 bits
#define THIRTY_TWO_BIT 32 // Defines the size of 32 bits
#define SIXTY_FOUR_BIT 64 // Defines the size of 64 bits
#define BYTE_MAX 15       // Defines the maximum value of a byte
#define EOL '\0'          // Defines the EOL character
#define NEW_LINE '\n'     // Defines the new line character

// Main function in the program - arguments supported.
int main(int argc, char *argv[])
{
    // Convert string to long first.
    unsigned long number = (unsigned long)atoi(argv[1]);

    int arraySize; // Defines variuable that will be assigned the array size

    // If the number input is less that 15, make the array size 4.
    if (number <= 15)
    {
        arraySize = NIBBLE; // Sets the array size to NIBBLE
    }
    // If the number input is more than 15 and less than or equal to 255, make the array size 8.
    else if (number > 15 && number <= UCHAR_MAX)
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

// TODO: Do the fault tolerance checks from assignemnt document
// TODO: check that input is within range.