// (C) Markus Emilio Puerto Gutiérrez, Markus Järveläinen, Younis Akel, group: 15 (2022)
// Work package 1
// Exercise 4
// Submission code: XXXXXX (provided by your TA-s)

// Include section
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Define section
#define HEXADECIMAL_OUTPUT "Hexadecimal: %x"

// Main function in the program - arguments supported.
int main(int argc, char *argv[])
{
    int *stringArray = argv[1];
    int arrSize = sizeof(argv[1]) / sizeof(argv[1]);
    int decimalVal;
    for (int i = arrSize - 1; i >= 0; i--)
    {
        if (stringArray[i] == '1')
        {
            decimalVal = decimalVal + pow(2, arrSize - i);
        }
    }
    printf("Here is the decimal val: %d", decimalVal);
    printf("and in hex: p");
    // loop through string array
    // if there is a 1, add 2^index to the sum
    // after loop, convert to hex.

    | 0 | 1 | 1 | 0 |
        printf(HEXADECIMAL_OUTPUT, 11);

    // Exits program if the conversion was successful
    return 0;
}