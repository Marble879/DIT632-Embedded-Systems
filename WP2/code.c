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
#define EOL '\0'                                           // Defines end of line character
#define NEW_LINE "\n"                                      // Defines a new line character
#define BASE 2                                             // Defines the base for when binary is converted to decimal
#define HEX_PRINT_MSG "Hexadecimal Number: "               // Defines message for printing hexadecimal values

// Function declarations
int validateArguments(char argToValidate[], int position); // Declare function to validate the initial arguments
void codeArguments(char toCodeArr[]);                      // Method that encodes the arguments

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

/* ===================== EXERCISE METHODS ==================*/

// Function implementation void codeArguments(char toCodeArr[]);
void codeArguments(char toCodeArr[])
{
    char binArray[UCHAR_MAX + 1]; // Make 9 to include EOL
    binArray[0] = toCodeArr[0];   // Assign binArray index 0 to the value of toCodeArr index 0
    int numberToConvert;          // Declare a variable to hold the number that will be converted

    numberToConvert = toCodeArr[1] - '0'; // convert to int
    // Loop from position 3 to 0 in the binary array
    for (int i = 3; i > 0; i--)
    {
        binArray[i] = (numberToConvert % 2) + '0'; // calculate num and convert to char
        numberToConvert = numberToConvert / 2;     // Divide by 2
    }

    numberToConvert = toCodeArr[2] - '0'; // convert to int
    // loop from position 5 to 4 in binary array
    for (int i = 5; i > 3; i--)
    {
        binArray[i] = (numberToConvert % 2) + '0'; // calculate num and convert to char
        numberToConvert = numberToConvert / 2;     // Divide by 2
    }

    binArray[6] = toCodeArr[3]; // Assign binArray index 6 to the value of toCodeArr index 3
    binArray[7] = toCodeArr[4]; // Assign binArray index 7 to the value of toCodeArr index 4
    binArray[8] = EOL;          // Assign EOL to binArray index 8

    // Print the binArray
    printf("%s\n", binArray);
    // Print readability formatting
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    // printf("%x\n", binArray);
    int hexArray[2];  // Declare hexArray
    int firstSum = 0; // Declare and initialize variable for the first sum calculation
    int power = 0;    // Declare and initialize variable used for exponent
    // loop from element 7 to 4 in binary array
    for (int i = 7; i > 3; i--)
    {
        // Check if the value at binArray current index equals to 1
        if (binArray[i] == '1')
        {
            firstSum = firstSum + ((int)(pow(BASE, power))); // calculate the decimal value of binary snippet
        }
        power++; // Increment power
    }
    hexArray[1] = firstSum; // Assign firstSum to index 1 in hexArray
    int secondSum = 0;      // Declare and initialize variable for the second sum calculation
    power = 0;              // Declare and initialize variable used for exponent
    // loop from poisition 3 to 0 in binary array
    for (int i = 3; i > -1; i--)
    {
        // Check if the value at binArray current index equals to 1
        if (binArray[i] == '1')
        {
            secondSum = secondSum + ((int)(pow(BASE, power))); // calculate the decimal value of binary
        }
        power++; // Increment power
    }
    hexArray[0] = secondSum; // Assign secondSum to hexArray index 0
    printf(HEX_PRINT_MSG);   // display hexadecimal values
    // Loops over the hexArray to print its values
    for (int i = 0; i < 2; i++)
    {
        // Prints the value at the current index in the array
        printf("%X", hexArray[i]);
    }
    // Print new line for readability
    printf(NEW_LINE);
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

    char oneString[6]; // To include EOL we make it 6
    int j;
    // Loop through the argument array
    for (int i = 1; i < 6; i++)
    {
        j = i - 1; // Assigns j to one lower than i
        // Copy string from argument array to oneString
        oneString[j] = argv[i][0];
    }
    oneString[6] = EOL; // Assigns EOL to index 6 in oneString array
    // Calls codeArguments and pass oneString to it
    codeArguments(oneString);

    // Exits the program with return value 0
    return 0;
}