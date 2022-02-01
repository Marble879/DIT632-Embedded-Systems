// (C) Markus Emilio Puerto Gutiérrez, Markus Järveläinen, Younis Akel, group: 15 (2022)
// Work package 2
// Exercise 3
// Submission code: XXXXXX (provided by your TA-s)

// Includes section
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Defines section
#define MAX 256                                                                                                                                                                                                        // Create a MAX value for string arrays
#define INVALID_MENU_INPUT_MSG "ERROR: please input an option from 1 to 5:\n"                                                                                                                                          // defines the error message when an incorrect
#define NEW_LINE '\n'                                                                                                                                                                                                  // defines the new line character
#define MENU_MSG "Please select a menu option\n1. Create a new and delete the old file.\n2. Add a new person to the file. \n3. Search for a person in the file.\n4. Print out all in the file.\n5. Exit the program\n" // Defines the menu message and menu options
#define EXIT_MSG "Exiting...\n"                                                                                                                                                                                        // Defines the exit message
#define FILENAME "database.bin"                                                                                                                                                                                        // defines the default filename

#define DUMMY_FNAME "DummyFname"      // Defines the dummy first name
#define DUMMY_FAM_NAME "DummyFamname" // Defines the dummy family name
#define DUMMY_PERS_NUMBER "20220203"  // Defines the dummy person number

// -----typedefs -------
typedef struct
{
    char firstname[20];
    char famname[20];
    char pers_number[13]; // yyyymmddnnnc
} PERSON;

// Function declaration (to be extend)
PERSON input_record(void);             // Reads a person’s record.
void write_new_file(PERSON *inrecord); // Creates a file and writes the first record
void printfile(void);                  // Prints out all persons in the file
void search_by_firstname(char *name);  // Prints out the person if in list
void append_file(PERSON *inrecord);    // appends a new person to the file
int displayMenu(PERSON *ppost);        // Displays the main menu for the user

// Implementation of int validateMenuInput(char *inputString);
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

// Function implementation for void displayMenu();
int displayMenu(PERSON *ppost)
{
    char inputString[MAX];
    char choice; // Declares variable used for menu choice
    // Loop for the menu
    do
    {
        printf(MENU_MSG);
        int check = 0;
        do
        {
            fgets(inputString, MAX, stdin);
            check = validateMenuInput(inputString);
        } while (check == 1);
        choice = inputString[0];
        // Switch statement for menu choices
        switch (choice)
        {
        case '1':
            write_new_file(ppost);
            break;
        case '2':
            // append_file(PERSON *inrecord);
            break;
        case '3':
            // search_by_firstname(char *name);
            break;
        case '4':
            // printfile(void);
            break;
        case '5':
            // Prints the exit message
            printf(EXIT_MSG);
            break;
            // Returns success
        default:
            printf(INVALID_MENU_INPUT_MSG);
            break;
        }
        // Keeps looping until menu choice 5 is selected
    } while (choice != '5');
}

// Function implementation for void write_new_file(PERSON *inrecord);
void write_new_file(PERSON *inrecord)
{
    FILE *fileptr;
    // Reference: https://stackoverflow.com/questions/29079684/structure-giving-me-expression-must-be-modifiable-value
    strcpy(inrecord->firstname, DUMMY_FNAME);
    strcpy(inrecord->famname, DUMMY_FAM_NAME);
    strcpy(inrecord->pers_number, DUMMY_PERS_NUMBER);
    if ((fileptr = fopen(FILENAME, "wb")) == NULL)
    {
        printf("\n Can not create the file");
        exit(1);
    }
    fwrite(inrecord, sizeof(PERSON), 1, fileptr);
    fclose(fileptr);
}

int main(void)
{
    PERSON ppost;
    // Calls the method that will show the menu
    displayMenu(&ppost);
    // Exit the program with return value 0
    return (0);
}