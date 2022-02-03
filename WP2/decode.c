// (C) Markus Emilio Puerto Gutiérrez, Markus Järveläinen, Younis Akel, group: 15 (2022)
// Work package 2
// Exercise 4
// Submission code: XXXXXX (provided by your TA-s)

// Includes Section
#include <stdio.h>
#include <string.h>
#include <math.h>

// Define Section
#define ERROR_MSG "Wrong amount of arguments.\n"                             // Define the error message when amount of arguments is wrong
#define CORRECT_ARG_COUNT 2                                                  // Define the number of arguments supported
#define INCORRECT_ARGUMENT "Argument is incorrect.\n"                        // Define the error message when the argument is incorrect
#define INCORRECT_ARGUMENT_LENGTH "Argument length is incorrect\n"           // Define the error message when the argument length is wrong
#define EOL '\0'                                                             // defines EOL
#define BASE 2                                                               // defines the base for the pow
#define TABLE_TITLE "Name                Value\n-------------------------\n" // defines the title of the output table
#define ENGINE_ON_TITLE "engine_on           %c\n"                           // defines the title for the engine value
#define GEAR_POS_TITLE "gear_pos            %c\n"                            // defines the gear pos title
#define KEY_POS_TITLE "key_pos             %c\n"                             // defines the title for the key position value
#define BRAKE1_TITLE "brake1              %c\n"                              // defines the title for brake1
#define BRAKE2_TITLE "brake2              %c\n"                              // defines the title for the brake 2 value

// Function declarations
int validateArgument(int argc, char *argv[]);    // Declare function to validate the initial arguments
void binToVal(char binArray[]);                  // Declare function to turn the binary array into a value array
void hexToBinary(char *argv[], char binArray[]); // Declare function to turn hexadecimal value into binary

// Function implementations ///

// Function implementation of int validateArgument(int argc, char *argv[]);
int validateArgument(int argc, char *argv[])
{
    // Checks if the arguments are of size 1
    if (argc != CORRECT_ARG_COUNT)
    {
        // Prints an error message
        printf(ERROR_MSG);
        // Exits the program with return value 1
        return 1;
    }
    // Checks if the argument is of length 2
    else if (strlen(argv[1]) != 2)
    {
        // Prints an error message
        printf(INCORRECT_ARGUMENT_LENGTH);
        // Exits the program with return value 1
        return 1;
    }
    // Loops through the argument length
    for (int i = 0; i < 2; i++)
    {
        // Checks if the argument characters are valid
        if (!(argv[1][i] >= '0' && argv[1][i] <= '9') && !(argv[1][i] >= 'A' && argv[1][i] <= 'F'))
        {
            // Prints an error message
            printf(INCORRECT_ARGUMENT);
            // Exits the program with return value 1
            return 1;
        }
    }
    // Exits the program with return value 0
    return 0;
}

// Function implementation of void binToVal(char binArray[]);
void binToVal(char binArray[])
{
    char valueArray[6];          // Declare an array of size 6 to hold values
    valueArray[5] = EOL;         // Add EOL to end of line
    valueArray[0] = binArray[0]; // Assign first value of binArray to valueArray, as they will be same
    int sumOfBin = 0;            // initialize sum of binary array for bin to dec conversion
    int power = 0;               // Initialize the power used for bin to dec conversion
    // Loop from index 3 to index 1, and convert from bin to dec
    for (int i = 3; i >= 1; i--)
    {
        // If the value is one, include the appropriate 2^power in the sum
        if (binArray[i] == '1')
        {
            // Increment the sum of the binary value under analysis
            sumOfBin = sumOfBin + ((int)(pow(BASE, power)));
        }
        // Increment the power
        power++;
    }
    // Convert from integer to character and assign to the value array
    valueArray[1] = sumOfBin + '0';
    // If the value is greater than 4, we have an error as limit exceeded.
    if (valueArray[1] > '4')
    {
        // display error message
        printf(INCORRECT_ARGUMENT);
        // exit method
        return;
    }

    sumOfBin = 0; // Assign 0 to sumOfBin to restart the sum
    power = 0;    // Assign 0 to power to restart the power iterations
    // Loops through the binary numbers whihc represent the third value in the valueArray
    for (int i = 5; i >= 4; i--)
    {
        // If the value is one, include the appropriate 2^power in the sum
        if (binArray[i] == '1')
        {
            // Increment the sum of the binary value under analysis
            sumOfBin = sumOfBin + ((int)(pow(BASE, power)));
        }
        // Increment the power
        power++;
    }
    // Convert from integer to character and assign to the value array
    valueArray[2] = sumOfBin + '0';
    // If the value is greater than 2, we have an error as limit exceeded.
    if (valueArray[2] > '2')
    {
        // Print error message for incorrect argument and return
        printf(INCORRECT_ARGUMENT);
        return;
    }
    valueArray[3] = binArray[6]; // Assign element 6 of binArray to element 3 of value array
    valueArray[4] = binArray[7]; // Assign element 7 of binArray to element 4 of value array
    // The 6 lines below prints the table including the values
    printf(TABLE_TITLE);
    printf(ENGINE_ON_TITLE, valueArray[0]);
    printf(GEAR_POS_TITLE, valueArray[1]);
    printf(KEY_POS_TITLE, valueArray[2]);
    printf(BRAKE1_TITLE, valueArray[3]);
    printf(BRAKE2_TITLE, valueArray[4]);
}

// Function implementation of void hexToBinary(char *argv[], char binArray[])
void hexToBinary(char *argv[], char binArray[])
{
    char tempBinArr[5];  // Declares a temporary array of size 5
    tempBinArr[4] = EOL; // Assigns end character to index 4 in the array
    // Loop through the array containing hexadecimal
    for (int i = 0; i < 2; i++)
    {
        // Check the value at the index under analysis
        switch (argv[1][i])
        {
        // If hex value is 0
        case '0':
            // Copy nibble to tempBinArr
            strcpy(tempBinArr, "0000");
            // Break out of switch statement
            break;
        // If hex value is 1
        case '1':
            // Copy nibble to tempBinArr
            strcpy(tempBinArr, "0001");
            // Break out of switch statement
            break;
        // If hex value is 2
        case '2':
            // Copy nibble to tempBinArr
            strcpy(tempBinArr, "0010");
            // Break out of switch statement
            break;
        // If hex value is 3
        case '3':
            // Copy nibble to tempBinArr
            strcpy(tempBinArr, "0011");
            // Break out of switch statement
            break;
        // If hex value is 4
        case '4':
            // Copy nibble to tempBinArr
            strcpy(tempBinArr, "0100");
            // Break out of switch statement
            break;
        // If hex value is 5
        case '5':
            // Copy nibble to tempBinArr
            strcpy(tempBinArr, "0101");
            // Break out of switch statement
            break;
        // If hex value is 6
        case '6':
            // Copy nibble to tempBinArr
            strcpy(tempBinArr, "0110");
            // Break out of switch statement
            break;
        // If hex value is 7
        case '7':
            // Copy nibble to tempBinArr
            strcpy(tempBinArr, "0111");
            // Break out of switch statement
            break;
        // If hex value is 8
        case '8':
            // Copy nibble to tempBinArr
            strcpy(tempBinArr, "1000");
            // Break out of switch statement
            break;
        // If hex value is 9
        case '9':
            // Copy nibble to tempBinArr
            strcpy(tempBinArr, "1000");
            // Break out of switch statement
            break;
        // If hex value is A
        case 'A':
            // Copy nibble to tempBinArr
            strcpy(tempBinArr, "1010");
            // Break out of switch statement
            break;
        // If hex value is B
        case 'B':
            // Copy nibble to tempBinArr
            strcpy(tempBinArr, "1011");
            // Break out of switch statement
            break;
        // If hex value is C
        case 'C':
            // Copy nibble to tempBinArr
            strcpy(tempBinArr, "1100");
            // Break out of switch statement
            break;
        // If hex value is D
        case 'D':
            // Copy nibble to tempBinArr
            strcpy(tempBinArr, "1101");
            // Break out of switch statement
            break;
        // If hex value is E
        case 'E':
            // Copy nibble to tempBinArr
            strcpy(tempBinArr, "1110");
            // Break out of switch statement
            break;
        // If hex value is F
        case 'F':
            // Copy nibble to tempBinArr
            strcpy(tempBinArr, "1111");
            // Break out of switch statement
            break;
        }
        // Concatentate the nibble in temp array to the binArray
        strcat(binArray, tempBinArr);
    }
}

/* ===================== MAIN ============================ */

// Main function in the program, arguments are supported
int main(int argc, char *argv[])
{
    // Calls validateArgument and checks for return value 1
    if (validateArgument(argc, argv) == 1)
        // Exits with error code
        return 1;

    char binArray[9];  // 9 for EOL
    binArray[8] = EOL; // add EOL to end of string
    // Convert the hexadecimal arguments to binary
    hexToBinary(argv, binArray);
    // Convert the binary values to the component values
    binToVal(binArray);

    // Exits the program with return value 0
    return 0;
}