// (C) Markus Emilio Puerto Gutiérrez, Markus Järveläinen, Younis Akel, group: 15 (2022)
// Work package 1
// Exercise 4
// Submission code: XXXXXX (provided by your TA-s)

// Include section
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// Define section
#define HEXADECIMAL_OUTPUT "Hexadecimal: %x"

// Main function in the program - arguments supported.
int main(int argc, char *argv[])
{

    int size = strlen(argv[1]);
    int array[size];
    // Convert string array into an array of digits.
    for (int i = 0; i < size; i++)
    {
        int j = (argv[1][i] - '0'); // reference: https://stackoverflow.com/questions/628761/convert-a-character-digit-to-the-corresponding-integer-in-c/32298334 // TODO: Should we do isdigit() check?
        array[i] = j;
    }
    int iteration = 0;
    int i = 0;
    unsigned long decimalNumber = 0;
    int sumArrSize = size / 4;
    int sumArr[sumArrSize];
    while (i < size)
    {
        int sum = 0;
        int limit = i + 4;
        double power = 3;
        // Convert binary to decimal and store results in an array.
        for (int j = i; j < limit; j++)
        {
            if (array[j] == 1)
            {
                sum = sum + ((int)(pow(2, power)));
            }
            power--;
        }
        sumArr[iteration] = sum;
        i = i + 4;
        iteration++;
    }

    printf("Hexadecimal number: ");
    for (int i = 0; i < sumArrSize; i++)
    {
        printf("%X", sumArr[i]);
    }
    printf("\n"); // Remove the % that is output in the terminal

    return 0;
}

// TODO: Add comments
// TODO: Add error handling from spec
// TODO: Defines.