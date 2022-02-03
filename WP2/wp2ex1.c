// (C) Markus Emilio Puerto Gutiérrez, Markus Järveläinen, Younis Akel, group: 15 (2022)
// Work package 2
// Exercise 1
// Submission code: 941100 (provided by your TA-s)

// Includes Section
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Define Section
#define EOC 'q'                                                                                                                                                // defines the end of character
#define INPUT_REQUEST_MSG_X "Please input the x coordinate:\n"                                                                                                 // defines the input request message for x coordinate
#define INPUT_REQUEST_MSG_Y "Please input the y coordinate:\n"                                                                                                 // defines the input request message for y coordinate
#define INPUT_REQUEST_MSG_INSTRUCTIONS "Please input the list of the instructions for the robot (m to move forward, and t for turning 90 degrees clockwise)\n" // defines the input request message for the list of instructions for the robot
#define INCORRECT_INSTRUCTION "Invalid character, robot will not change position or direction.\n"                                                              // Defines the error message to the user when a wrong instrction is inputted.
#define COORDINATE_ARR_INPUT_SIZE 50                                                                                                                           // defines the size of the array that stored the coordinate input
#define MAX_INSTRUCTIONS 256                                                                                                                                   // defines the max number of instructions that can be processed
#define EOC_MESSAGE "EOC detected, exiting program...\n"                                                                                                       // defines the message to be displayed when an EOC is encountered
#define SESSION_SEPARATOR "~~~~~~~~ ~~~~~~~~~~~~~~~~~ \n"                                                                                                      // defines a line to separate the session
#define POSITION_OUTPUT "Position now is: x: %d, y: %d, direction: %c\n"                                                                                       // Defines the output message displaying the position of the robot after carrying out instructions
#define NEW_LINE '\n'                                                                                                                                          // defines the new line character
#define EOL '\0'                                                                                                                                               // defines the end of line character
#define INVALID_COORDINATE_MSG "Please input numbers between 0 and 99!\n"                                                                                      // defines the error message when the user inputs an incorrect coordinate
#define INVALID_INSTRUCTION_LENGTH "Instructions not valid! Please enter at least one instruction and less than 51 instructions\n"                             // dfines the error message when the user inputs an incorrect amount of instructions.

// Define the data type for the direction the robot is headed in
enum DIRECTION
{
    N, // Defines North
    E, // Defines East
    S, // Defines South
    W  // Defines West
};

// Define robot dataype
typedef struct
{
    int xpos;           // declare x position of the robot
    int ypos;           // declare y position of the robot
    enum DIRECTION dir; // declare the direction of the robot
} ROBOT;

// ------ Function declarations   ----------

// This function moves the robot in a particular direction
// and updates the robots current coordinates
void move(ROBOT *rob);

// This function turns the robot in a particular direction
// and updates the robots current direction
void turn(enum DIRECTION *dir);

// This function initializes the robot's position according
// to the inputted coordinates
void initializePosition(ROBOT *rob);

// This function executes the robots instructions inputted
// by the user.
int executeInstructions(ROBOT *rob, int *isEOC);

// This function validates the x and y coordinates the user inputs
int validateCoordinateInput(char *input);

// ------ Function definitions   ----------

// Implementation of void move(ROBOT *rob);
void move(ROBOT *rob)
{
    // Switch statement to adjust position based on the direction
    switch (rob->dir)
    {
    // Movement if direction is North
    case 0:
        // Increment y axis
        rob->ypos++;
        // Break switch case
        break;
    // Movement if direction is East
    case 1:
        // Increment x axis
        rob->xpos++;
        // Break switch case
        break;
    // Movement if direction is South
    case 2:
        // Decrement y axis
        rob->ypos--;
        // Break switch case
        break;
    // Movement if direction is West
    case 3:
        // Decrement x axis
        rob->xpos--;
        // Break switch case
        break;
    }
}

// Implementation of void turn(enum DIRECTION *dir);
void turn(enum DIRECTION *dir)
{
    // Increment the direction and mod it by 4 (so if it goes beyond 3, it goes back to 0 (North))
    *dir = (*dir + 1) % 4;
}

// Implementation of int validateInput(char *input);
int validateCoordinateInput(char *input)
{
    // Checks if the input is empty (ie only contains \n)
    // or if the length is more than 3
    // strlen() counts everything up to \0
    if (strlen(input) == 1 || strlen(input) > 3)
    {
        // display invalid coordinate input message
        printf(INVALID_COORDINATE_MSG);
        // return with error status
        return 1;
    }
    // loops through the string to check if digits are within range
    for (int i = 0; i < strlen(input); i++)
    {
        // If the digit is not between 0 and 9 and is not new line, return error.
        // The previous if ensures that there is a character before the \n
        if (!(input[i] >= '0' && input[i] <= '9') && input[i] != NEW_LINE)
        {
            // display invalid coordinate input message
            printf(INVALID_COORDINATE_MSG);
            // return with error status
            return 1;
        }
    }
    return 0;
}

// Implementation of void initializePosition(ROBOT *rob);
void initializePosition(ROBOT *rob)
{
    char x[COORDINATE_ARR_INPUT_SIZE]; // declares x coordinate input array
    char y[COORDINATE_ARR_INPUT_SIZE]; // declares y coordinate input array
    char *endPtr;                      // Declared to be used as a parameter for validation

// Label used for goto
LabelXposInput:
    // Prints message to user to input coordinate x
    printf(INPUT_REQUEST_MSG_X);
    // Gets the coordinate x inputted by the user
    fgets(x, COORDINATE_ARR_INPUT_SIZE, stdin); // according to fgets() documentation "It stops when either (n-1) characters are read, the newline character is read, or the end-of-file is reached", we choose a size of 50 to account for validating incorrect (more than 3 digit) values as if we used a value of 4 for the buffer size,and inputtd 3 digits, the buffer would read the first 3, then the buffer would be read for the next input automatically.
    // if statement to check if an error occured
    if (validateCoordinateInput(x) == 1)
        goto LabelXposInput;
    rob->xpos = strtol(x, NULL, 10);
// Label used for goto
LabelYposInput:
    // Prints message to user to input coordinate y
    printf(INPUT_REQUEST_MSG_Y);
    // Gets the corrdinate y inputted by the user.
    fgets(y, COORDINATE_ARR_INPUT_SIZE, stdin);
    // if statement to check if an error occured
    if (validateCoordinateInput(y) == 1)
        // Goes to the label LabelYposInput
        goto LabelYposInput;

    rob->ypos = strtol(y, NULL, 10); // initialize starting y position of robot
    rob->dir = N;                    // initialize starting direction of robot
}

// Implementation of void executeInstruction(ROBOT *rob);
int executeInstructions(ROBOT *rob, int *isEOC)
{
    char inst[MAX_INSTRUCTIONS]; // defines the list of instructions

// Label used for goto
LabelInstructions:
    //  Prints message to user to input the instructions for the robot.
    printf(INPUT_REQUEST_MSG_INSTRUCTIONS);

    // Gets the instructions for the robot.
    fgets(inst, MAX_INSTRUCTIONS, stdin);

    int strlength = strlen(inst); // Defines the length of the instructions

    // if statement to check the length of the instructions
    if (inst[0] == NEW_LINE || strlength > 51)
    {
        // Prints the error message when the length of instructions is incorrect
        printf(INVALID_INSTRUCTION_LENGTH);
        // Goes to the part defined after Label3 (asks for the list of instructions again)
        goto LabelInstructions;
    }

    // Loops though all the list of instructions
    for (int i = 0; i < (strlength - 1); i++)
    {
        // if statement to check if the char in position i is valid
        if (inst[i] != 'm' && inst[i] != 't' && inst[i] != 'q')
        {
            // Prints the error message when an instruction is not valid
            printf(INCORRECT_INSTRUCTION);
            // Goes to the part defined after Label3 (asks for the list of instructions again)
            goto LabelInstructions;
        }
    }

    int i = 0; // initialize i that will be used to loop through array

    // Loops over the input instructions and calls the appropriate method
    do
    {
        // Switch statement to call appropriate method depending on instruction
        switch (inst[i])
        {
        // Call the move function if m is the instruction
        case 'm':
            // Move the robot one position in the direction its headed
            move(rob);
            // Break switch case
            break;
        // Call the turn function if t is the instruction
        case 't':
            // Turn the robot 90 degrees clockwise
            turn(&rob->dir);
            // Break switch case
            break;
        // If the instruction is end of character, print the appropriate message
        case EOC:
            // Display the end of character message
            printf(EOC_MESSAGE);
            *isEOC = 1;
            // exit program with no enter
            return 0;
        }
        i++; // increment index
        // Keeps looping until it detects end of line or end character
    } while ((inst[i] != NEW_LINE && inst[i] != EOL) || inst[i] == EOC);
}

// ------ Main   --------------------------

// Main function in the program, no program arguments supported
int main()
{
    ROBOT robot;   // Declares the robot
    int isEOC = 0; // Declare and initialize end of character checker

    // Loops the process of initializing the robot's position and executing the user instructions
    do
    {
        // Calls the function to initialize the robot's position
        initializePosition(&robot);
        // Calls the funtion to execute instructions
        executeInstructions(&robot, &isEOC);
        // display the current position of the robot after instructions
        char direction;
        switch (robot.dir)
        {
        case 0:
            direction = 'N';
            break;
        case 1:
            direction = 'E';
            break;
        case 2:
            direction = 'S';
            break;
        case 3:
            direction = 'W';
            break;
        }
        printf(POSITION_OUTPUT, robot.xpos, robot.ypos, direction); // TODO: Change dir to N,E,S or W
        // If the EOC was not reached, then print out formatting
        if (!isEOC)
            // Print line for readability
            printf(SESSION_SEPARATOR);
        // Keeps looping until the end of character has been detected
    } while (isEOC != 1);

    // Exits program with return value 0
    return 0;
}