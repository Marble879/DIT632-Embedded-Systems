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
#define HEXADECIMAL_MSG "Hexadecimal number: " // Defines the message to be displayed before printing the hexadecimal number
#define NEW_LINE "\n"                          // Defines the new line character
#define NIBBLE 4                               // Defines the length of a nibble
#define INITIAL_EXPONENT 3                     // Defines the initial exponent for when binary is converted to decimal
#define BASE 2                                 // Defines the base for when binary is converted to decimal

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
    printf(NEW_LINE);
}

// Main function in the program - arguments supported.
int main(int argc, char *argv[])
{
    // Variable section
    int size = strlen(argv[1]); // Stores the string length of the argument into a variable called size
    int intArr[size];           // Declares an array of integers with the length of the size variable

    // Convert string array into an array of digits.
    for (int i = 0; i < size; i++)
    {
        int j = (argv[1][i] - '0'); // Convert character into digit. Reference: https://stackoverflow.com/questions/628761/convert-a-character-digit-to-the-corresponding-integer-in-c/32298334 // TODO: Should we do isdigit() check?
        intArr[i] = j;              // Assign the int value to element i of the intArr
    }

    // Calls the method to convert the binary number to hexadecimal
    convertBinToHex(size, intArr);

    // returns 0 value
    return 0;
}

// TODO: Add error handling from spec