// (C) Markus Emilio Puerto Gutiérrez, Markus Järveläinen, Younis Akel, group: 15 (2022)
// Work package 1
// Exercise 3
// Submission code: XXXXXX (provided by your TA-s)

// Includes Section
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define Section
#define MAX_NUMBER 10                                                                                   // Defines the max number of guesses allowed
#define RANGE_MAX 100                                                                                   // Defines the upper bound of the range for a random number
#define RANGE_MIN 1                                                                                     // Defines the lower bound of the range for a random number
#define INITIAL_MSG "Guess the random number between 1-100:\n"                                          // Defines a message that is shown when the game starts
#define TOO_HIGH "Your guess is too high. Try again:\n"                                                 // Defines a message when the guess is too high
#define TOO_LOW "Your guess is too low. Try again:\n"                                                   // Defines a message when the guess is too low
#define INCORRECT_CHOICE "Choice not registered! Please input a value between 1 and 100 (inclusive)!\n" // Defines a message when the guess entered is not valid
#define CORRECT_GUESS_MSG "You have guessed %d times and your guess is correct\n\n"                     // Defines a message for when the user makes a correct guess //TODO: test this
#define EXCEED_GUESSES_MSG "You have exceeded %d guesses!\n"                                            // Defines a message when the amount of guesses reaches the limit
#define MENU_MSG "Select an option:\n1. Play again\n2. Exit\n"                                          // Defines a message where the user is presented with a menu to play the game again or exit
#define EXITING_MSG "Exiting..\n"                                                                       // Defines a message when ending/exiting the program

// Random number generator adapted from this example: https://stackoverflow.com/questions/1190870/i-need-to-generate-random-numbers-in-c
int generateRandNumber()
{
    int randomNumber; // Holds the random number generated

    // Sets the starting seed based on current time for each iteration of the random number generator
    srand(time(0));

    // Calculates a random number in the range of 1 - 100. In our case, the part in the parenthesis would evaluate to a randomNumber between 0 and 99. Hence, we add the lower bound to ensure that the number is between 1 and 100.
    // Reference: https://www.includehelp.com/c-programs/generate-random-numbers-within-a-range.aspx
    randomNumber = (rand() % (RANGE_MAX - RANGE_MIN + 1)) + RANGE_MIN;

    return randomNumber; // return the generated number
}

// Contains a loop and checker on the number of times a user guessed, and also outputs messages depending on the user input.
int makeUserGuess(int randomNumber)
{
    int userInputGuess; // Holds the user guess input
    int guessCount = 0; // Counts the number of guesses
    char term;          // declare term variable for error handling

    // Keep looping while the user has not guessed the random number, and the guess count is below 10.
    do
    {
        // Output message to console
        printf(INITIAL_MSG);

        // Takes the input of the user. First check ensures that if the first value in the buffer is not an int, scanf() returns 0. If the second value in the buffer is of type char (and the first value is of type int), then the check returns a 2. If the previous scentence occurs, then we also need to ensure that if "term" is not EOL, the "invalid type" message is displayed.\\Reference: https://stackoverflow.com/questions/4072190/check-if-input-is-integer-type-in-c
        if (scanf("%d%c", &userInputGuess, &term) == 0 || term != '\n')
        {
            // Output incorrect choice message
            printf(INCORRECT_CHOICE);
            // Returns failure
            return 1;
        }

        // Condition where the guess is too high, increases guess counter and asks for another guess
        if (userInputGuess <= 100 && userInputGuess >= 1)
        {
            guessCount++; // Count guess if its within range 1-100

            // Checks if the user's guess is larger than the random number
            if (userInputGuess > randomNumber)
            {
                // prints to console
                printf(TOO_HIGH);
            }
            // Condition where the guess is too low, increases guess counter and asks for another guess
            else if (userInputGuess < randomNumber)
            {
                // prints to console
                printf(TOO_LOW);
            }
            // Condition where the guess is correct, prints the guess count
            else if (userInputGuess == randomNumber)
            {
                // prints to console and exits method.
                printf(CORRECT_GUESS_MSG, guessCount);
                // Returns success
                return 0;
            }
        }
        // If the input is out of range, print to the console.
        else
        {
            // output message.
            printf(INCORRECT_CHOICE);
        }
        // Keep looping while the user has not guessed the random number, and the guess count is below 10.
    } while (userInputGuess != randomNumber && guessCount < MAX_NUMBER);

    // Output message to console.
    printf(EXCEED_GUESSES_MSG, MAX_NUMBER);
    // Returns success
    return 0;
}

// Sets up the game session, calls the guessing game session and calls a random value generator.
int startGame()
{
    int userInputNewRound; // Declares the "start new round" value
    // Loops the gamesession at least once, and for as long as the user selects to play again
    do
    {
        int randomNumber = generateRandNumber(); // Calls the randomValuleGenerator() and stores the returned value to an int variable
        // Method that starts one game session and an if statement to check if the game ended because of a worng input.
        if (makeUserGuess(randomNumber) != 0)
            // Returns failure
            return 1;
        // Prints the options to continue the game or exit
        printf(MENU_MSG);
        // Takes the answer input from the user
        scanf("%d", &userInputNewRound);

        // Continues to loop unless the user inputs 2
    } while (userInputNewRound != 2);
    // Print the exit message
    printf(EXITING_MSG);
    // Returns success
    return 0;
}

// Main function in the program, no program arguments supported
int main()
{
    int errCheck = 0; // initialize error check
    // Method that begins the guessing game session and receives the result of if errors occured
    errCheck = startGame();
    // Exits program
    return errCheck;
}