// (C) Markus Emilio Puerto Gutiérrez, Markus Järveläinen, Younis Akel, group: 15 (2022)
// Work package 2
// Exercise 3
// Submission code: 941100 (provided by your TA-s)

// Includes section
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

// Defines section
#define MAX 256 // Create a MAX value for string arrays

#define MAX_NAME 21                                                                                                                                                                                                    // Define the maximimum value of 20 for a name input. It is 21 due to considering \n character.
#define INVALID_MENU_INPUT_MSG "ERROR: please input an option from 1 to 5:\n"                                                                                                                                          // defines the error message when an incorrect
#define NEW_LINE '\n'                                                                                                                                                                                                  // defines the new line character
#define MENU_MSG "Please select a menu option\n1. Create a new and delete the old file.\n2. Add a new person to the file. \n3. Search for a person in the file.\n4. Print out all in the file.\n5. Exit the program\n" // Defines the menu message and menu options
#define EXIT_MSG "Exiting...\n"                                                                                                                                                                                        // Defines the exit message
#define FILENAME "database.bin"                                                                                                                                                                                        // defines the default filename
#define NO_FILE_MESSAGE "Can not open file\n"                                                                                                                                                                          // defines no file error message
#define EMPTY_FILE_MESSAGE "File exists, but it is empty.\n"                                                                                                                                                           // Defines the empty file error message
#define INCORRECT_NAME_MESSAGE "Name inputted is incorrect. It must only include characters up to 20 characters long.\n"                                                                                               // Defines the incorrect name message to the user
#define INCORRECT_NAME_CHOICE_MESSAGE "Choice input is not correct\n"                                                                                                                                                  // Defines the incorrect choice message to the user
#define EOL '\0'                                                                                                                                                                                                       // defines EOL character
#define NAME_INPUT_MESSAGE "Please input the name to search: \n"                                                                                                                                                       // Defines the message to input the name to search for to the user
#define NAME_SEARCH_OPTION "Press F for first name, L for last name\n"                                                                                                                                                 // Defines the message asking the user to select whether to search for first name or last name                                                                                                                                                            // Defines the message to input the name to search for to the user
#define NO_PERSON_MESSAGE "No person with that first/last name was found\n"                                                                                                                                            // Defines the message to be displayed if a searched user is not found
#define INCORRECT_PERSON_NUMBER_MESSAGE "The person number is incorrect, it must be 12 characters long\n"                                                                                                              // Defines the error message for the user when the person number input is incorrect
#define MAX_PERSON_NUMBER 13                                                                                                                                                                                           // // Define the maximimum value of 14 for a person number input. It is 14 due to considering \n character.
#define FIRST_NAME_MSG "Enter first name: \n"                                                                                                                                                                          // Defines the message to ask the user for a first name
#define LAST_NAME_MSG "Enter last name: \n"                                                                                                                                                                            // Defines the message to ask the user for a last name
#define PERSON_NUMBER_MSG "Enter personnummer in format yyyymmddnnnc\n"                                                                                                                                                // Defines the message to ask the user for a person number
#define APPEND_ERROR_MSG "\n Can not append to the file"                                                                                                                                                               // Defines the error message for appending

#define DUMMY_FNAME "DummyFname"         // Defines the dummy first name
#define DUMMY_FAM_NAME "DummyFamname"    // Defines the dummy family name
#define DUMMY_PERS_NUMBER "202202031234" // Defines the dummy person number

// -----typedefs -------
typedef struct
{
    char firstname[20];
    char famname[20];
    char pers_number[13]; // yyyymmddnnnc
} PERSON;

// Function declaration (to be extend)
PERSON input_record(void);                  // Reads a person’s record.
void write_new_file(PERSON *inrecord);      // Creates a file and writes the first record
void printfile(void);                       // Prints out all persons in the file
void search_by_firstname(char *name);       // Prints out the person if in list
void append_file(PERSON *inrecord);         // appends a new person to the file
int displayMenu(PERSON *ppost);             // Displays the main menu for the user
int validateMenuInput(char *inputString);   // Validates the menu option inputted by the user
int validateName(char *name);               // Validates the name inputted by the user
void searchPerson(char *name, char choice); // Searches and prints the persons with the name passed in the parameter
int validateNameChoice(char *choice);       // Validate the choice inputted by the user
void createNewPerson(PERSON *pperson);      // Validates the new person the user inputs
int exists(const char *fname);              // Checks if the file exists before appending

/* =========== Validation method implementations =========== */

// Reference: https://stackoverflow.com/questions/29067382/how-to-open-a-file-with-append-mode-only-if-it-exist
int exists(const char *fname)
{
    FILE *file; // declare file pointer
    // check if can open a file
    if ((file = fopen(fname, "r")))
    {
        // if can open, close file
        fclose(file);
        // return file exists status
        return 0;
    }
    // no file exists
    return 1;
}

// Function implementation of int validateNewPerson();
void createNewPerson(PERSON *pperson)
{
    int fnameCheck = 0;     // Used to contain the result of the validation check
    printf(FIRST_NAME_MSG); // Asks the user to input a first name
    char firstName[MAX];    // Initialize the first name array
    // Loop to check if the first name is correct
    do
    {
        // Gets the first name
        fgets(firstName, MAX, stdin);
        // Validates the first name input
        fnameCheck = validateName(firstName);
        // Will loop until the user input is correct
    } while (fnameCheck == 1);

    int lnameCheck = 0;    // Used to contain the result of the validation check
    printf(LAST_NAME_MSG); // Asks the user to input a last name
    char lastName[MAX];    // Initialize the last name array
    // Loop to check if the last name is correct
    do
    {
        // Gets the last name
        fgets(lastName, MAX, stdin);
        // Validates the last name input
        lnameCheck = validateName(lastName);
        // Will loop until the user input is correct
    } while (lnameCheck == 1);

    int PnumCheck = 1;         // Used to contain the result of the validation check
    printf(PERSON_NUMBER_MSG); // Asks the user to input a person number
    char personNumber[MAX];    // Initialize the person number array
    // Loop to check if the person number is correct
    do
    {
        // Gets the person number
        fgets(personNumber, MAX, stdin);
        // if statement to check if the person number is 12 digits long
        if (strlen(personNumber) != MAX_PERSON_NUMBER)
        {
            // Prints error message to user when the person number is too long
            printf(INCORRECT_PERSON_NUMBER_MESSAGE);
        }
        else
        {
            PnumCheck = 0;                                  // Assign 0 to PnumCheck
            for (int i = 0; i < MAX_PERSON_NUMBER - 2; i++) // -2 to ignore \n
            {
                // Check if the element contains a digit character
                if (isdigit(personNumber[i]) == 0)
                {
                    // Print error message
                    printf(INCORRECT_PERSON_NUMBER_MESSAGE);
                    PnumCheck = 1; // Assign 1 to PnumCheck
                }
            }
        }
        // Will loop until the user input is correct
    } while (PnumCheck == 1);
    // The EOLs were removed due to how we store and compare the strings later
    // Remove EOL from the firstname
    // Ref: https://www.geeksforgeeks.org/strcspn-in-c/. method strcspn() calcs  num of characters before 1st occurance of \n. Hence, we get index of \n and replace with EOL.
    firstName[strcspn(firstName, "\n")] = EOL;
    // Remove EOL from the lastname
    lastName[strcspn(lastName, "\n")] = EOL;
    // Remove EOL from the personnummer
    personNumber[strcspn(personNumber, "\n")] = EOL;
    // Copy new firstName into struct
    strcpy(pperson->firstname, firstName);
    // Copy new lastName into struct
    strcpy(pperson->famname, lastName);
    // Copy new personNumber into struct
    strcpy(pperson->pers_number, personNumber);
}

// Function implementation of int validateNameChoice(char choice);
int validateNameChoice(char *choice)
{
    // If the choice is empty or it is larger than 1 character (2 due to \n), then there is an
    // error
    if (strlen(choice) == 1 || strlen(choice) > 2)
    {
        // display invalid choice input message
        printf(INCORRECT_NAME_CHOICE_MESSAGE);
        // return with error status
        return 1;
    }
    // If the input is not F or L, then an error has occured
    if (choice[0] != 'F' && choice[0] != 'L')
    {
        // display invalid choice input message
        printf(INCORRECT_NAME_CHOICE_MESSAGE);
        // return with error status
        return 1;
    }
    // exit function with no error
    return 0;
}

// Function implementation of int validateName(char *name);
int validateName(char *name)
{
    // Checks if the input is empty (ie only contains \n)
    // or if the length is more than 20
    // strlen() counts everything up to \0
    if (strlen(name) == 1 || strlen(name) > MAX_NAME)
    {
        // display invalid coordinate input message
        printf(INCORRECT_NAME_MESSAGE);
        // return with error status
        return 1;
    }
    // loops through the string to check if digits are within range
    for (int i = 0; i < strlen(name); i++)
    {
        // if the string contains other values from a-z, A-Z,
        // then  exit the program
        if (isalpha(name[i]) == 0 && name[i] != NEW_LINE && name[i] != EOL)
        {
            // display invalid coordinate input message
            printf(INCORRECT_NAME_MESSAGE);
            // return with error status
            return 1;
        }
    }
    // exit function with no error
    return 0;
}

// Function implementation of int validateMenuInput(char *inputString);
int validateMenuInput(char *inputString)
{
    // if statement to check if the menu option input is correct
    if (!(inputString[0] >= '1' && inputString[0] <= '5') || (strlen(inputString) == 1 || strlen(inputString) > 2))
    {
        // display invalid coordinate input message
        printf(INVALID_MENU_INPUT_MSG);
        // return with error status
        return 1;
    }
    // Return successful status
    return 0;
}

/*====================EXERCISE FUNCTIONS==================*/

// Function implementation of void append_file(PERSON *inrecord);
void append_file(PERSON *inrecord)
{
    FILE *fileptr; // Points to the binary file

    // check if a file exists
    if (exists(FILENAME) == 0)
    {
        // open file and check if there was an error
        if ((fileptr = fopen(FILENAME, "ab")) == NULL)
        {
            // Print error message
            printf(APPEND_ERROR_MSG);
            // dont continue to write and exit function due to error
            return;
        }
        // Appends the new person at the end of the file
        fwrite(inrecord, sizeof(PERSON), 1, fileptr);
        // close file pointer
        fclose(fileptr);
    }
    else
    {
        // Print error message
        printf(NO_FILE_MESSAGE);
        // dont continue to write and exit function due to error
        return;
    }
}

// Function implementation of void searchPerson(char *name);
void searchPerson(char *name, char choice)
{
    FILE *fileptr; // Points to the binary file
    PERSON person; // Declares a person of type PERSON
    int n = 1;     // Counts the amount of persons in the file
    // Check if there is no file/an errro when opening the file
    if ((fileptr = fopen(FILENAME, "rb")) == NULL) // r for read, b for binary
    {
        // print no file found message
        printf(NO_FILE_MESSAGE);
        // exit method
        return;
    }
    else
    {
        // Move file pointer to end of file
        fseek(fileptr, 0, SEEK_END);
        // Retruns the file position of the file pointer
        int size = ftell(fileptr); // Reference: https://stackoverflow.com/questions/13566082/how-to-check-if-a-file-has-content-or-not-using-c
        // Check if the file pointer is at the beginning of file still.
        // If the size is 0, then the pointer has not moved and file is empty.
        if (0 == size)
        {
            // Output empty file message
            printf(EMPTY_FILE_MESSAGE);
        }
    }
    // Reset the file pointer to point to start of file
    fseek(fileptr, 0, SEEK_SET);
    // Loop while filepointer has not reached the end pointer
    while (!feof(fileptr))
    {
        // Check if the the pointer has reached the end of the file. Reference:https://www.tutorialspoint.com/c_standard_library/c_function_fread.htm
        if (fread(&person, sizeof(PERSON), 1, fileptr))
        {
            name[strcspn(name, "\n")] = EOL; // Replace new line with end of line character.
            // if statement to check for the character F
            if (choice == 'F')
            {
                // if statement to check if the input name matches the first name of the person
                if (strcmp(person.firstname, name) == 0)
                {
                    // Display the person number
                    printf("Person %d:\n", n);
                    // Display the person's firstname
                    printf("\t%s\n", person.firstname);
                    // Display the person's family name
                    printf("\t%s\n", person.famname);
                    // Display the person's personummer
                    printf("\t%s\n", person.pers_number);
                    // Increment the person counter
                    n++;
                }
            }
            // if statement to check for the character L
            else if (choice == 'L')
            {
                // if statement to check if the input name matches the last name of the person
                if (strcmp(person.famname, name) == 0)
                {
                    // Display the person number
                    printf("Person %d:\n", n);
                    // Display the person's firstname
                    printf("\t%s\n", person.firstname);
                    // Display the person's family name
                    printf("\t%s\n", person.famname);
                    // Display the person's personummer
                    printf("\t%s\n", person.pers_number);
                    // Increment the person counter
                    n++;
                }
            }
        }
    }
    // if statement to check if the search had no results
    if (n == 1)
        // Tells the user that the search gave no results
        printf(NO_PERSON_MESSAGE);
    //    Close the file
    fclose(fileptr);
}

// Function implementation for void printfile();
void printfile()
{
    FILE *fileptr; // Declare a Pointer to the binary file
    PERSON person; // declare a variable of type PERSON
    int n = 1;     // Counts the amount of persons in the file
    // Check if there is no file/an errro when opening the file
    if ((fileptr = fopen(FILENAME, "rb")) == NULL) // r for read, b for binary
    {
        // Print no file message
        printf(NO_FILE_MESSAGE);
        // exit method
        return;
    }
    // If the file exists
    else
    {
        // Move file pointer to end of file
        fseek(fileptr, 0, SEEK_END);
        // Retruns the file position of the file pointer
        int size = ftell(fileptr); // Reference: https://stackoverflow.com/questions/13566082/how-to-check-if-a-file-has-content-or-not-using-c
        // Check if the file pointer is at the beginning of file still.
        // If the size is 0, then the pointer has not moved and file is empty.
        if (0 == size)
        {
            // Output empty file message
            printf(EMPTY_FILE_MESSAGE);
        }
    }
    // Reset the file pointer to point to start of file
    fseek(fileptr, 0, SEEK_SET);
    // Loop while filepointer has not reached the end pointer
    while (!feof(fileptr))
    {
        // Check if the the pointer has reached the end of the file. Reference:https://www.tutorialspoint.com/c_standard_library/c_function_fread.htm
        if (fread(&person, sizeof(PERSON), 1, fileptr))
        {
            // Display the person number
            printf("Person %d:\n", n);
            // Display the person's firstname
            printf("\t%s\n", person.firstname);
            // Display the person's family name
            printf("\t%s\n", person.famname);
            // Display the person's personummer
            printf("\t%s\n", person.pers_number);
            // Increment the person counter
            n++;
        }
    }
    //    Close the file
    fclose(fileptr);
}

// Function implementation for void write_new_file(PERSON *inrecord);
void write_new_file(PERSON *inrecord)
{
    FILE *fileptr;
    // Reference: https://stackoverflow.com/questions/29079684/structure-giving-me-expression-must-be-modifiable-value
    // Assign the dummy record firstname a dummy value
    strcpy(inrecord->firstname, DUMMY_FNAME);
    // Assign the dummy record famname a dummy value
    strcpy(inrecord->famname, DUMMY_FAM_NAME);
    // Assign the dummy record pers_number a dummy value
    strcpy(inrecord->pers_number, DUMMY_PERS_NUMBER);
    // Add end of line to the last element of the pers_number array as persnum is 12 characters long
    inrecord->pers_number[12] = EOL;
    // Create the file and write to it in binary.
    if ((fileptr = fopen(FILENAME, "wb")) == NULL)
    {
        // Display error message
        printf("\n Can not create the file");
        // Exit function
        return;
    }
    // Write the dummy record to the file
    fwrite(inrecord, sizeof(PERSON), 1, fileptr);
    // close file pointer
    fclose(fileptr);
}

/* ================== MENU AND MAIN FUNCTION =====================*/

// Function implementation for void displayMenu();
int displayMenu(PERSON *ppost)
{
    char inputString[MAX]; // Declares inputString char array
    char choice;           // Declares variable used for menu choice
    // Loop for the menu
    do
    {
        // Print the menu message
        printf(MENU_MSG);
        int menuInputCheck = 0; // Declares and initializes the input check variable
        // While there is an invalid input, keep looping
        do
        {
            // Retreives the string from the user
            fgets(inputString, MAX, stdin);
            // Check that the input is valid
            menuInputCheck = validateMenuInput(inputString);
            // While there is an error, loop
        } while (menuInputCheck == 1);
        choice = inputString[0]; // assign choice the first element of the input string
        // Switch statement for menu choices
        switch (choice)
        {
            // If the choice is 1, call write_new_file.
        case '1':
            // Create a new file and add dummy to it (deleting old file).
            write_new_file(ppost);
            // Break out of the switch statement
            break;
        case '2':
            // Declare a variable of type PERSON
            PERSON pperson;
            // Call the creation of a new person with the address of the new person as
            // the parameter
            createNewPerson(&pperson);
            // append the newely created person to the file
            append_file(&pperson);
            // Break out of the switch statement
            break;
        case '3':
            char nameTypeChoice[MAX];  // Declares a char array to hold the name type choice, i.e. first name or last name
            int fnameOrLnameCheck = 0; // Declares and initializes a variable used for validating first or last name input
            int nameCheck = 0;         // Declares and initializes a variable used for validating the name
            char name[MAX];            // Declares a char array for the name
                                       // While there is an invalid input, keep looping
            do
            {
                // Prints the message prompting the user to select searching for first or last name
                printf(NAME_SEARCH_OPTION);
                // Gets the name type choice input
                fgets(nameTypeChoice, MAX, stdin);
                fnameOrLnameCheck = validateNameChoice(nameTypeChoice); // assign validation check result
                // While there is an invalid input, keep looping
            } while (fnameOrLnameCheck == 1);
            do
            {
                // Prints the message asking the user to input a name
                printf(NAME_INPUT_MESSAGE);
                // Gets the name input
                fgets(name, MAX, stdin);
                nameCheck = validateName(name); // assign validation check result
            } while (nameCheck == 1);
            searchPerson(name, nameTypeChoice[0]);
            // Break out of the switch statement
            break;
        case '4':
            // Calls the method to print the contents of the file
            printfile();
            // Break out of the switch statement
            break;
        case '5':
            // Prints the exit message
            printf(EXIT_MSG);
            // Break out of the switch statement
            break;
        default:
            // Prints the invalid input message
            printf(INVALID_MENU_INPUT_MSG);
            // Break out of the switch statement
            break;
        }
        // Keeps looping until menu choice 5 is selected
    } while (choice != '5');
}

// Main function in the program, no program arguments supported
int main(void)
{
    PERSON ppost; // Declare a new variable of type PERSON
    // Calls the method that will show the menu
    displayMenu(&ppost);
    // Exit the program with return value 0
    return (0);
}