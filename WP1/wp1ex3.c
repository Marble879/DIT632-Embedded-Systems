// (C) Markus Emilio Puerto Gutiérrez, Markus Järveläinen, Younis Akel, group: 15 (2022)
// Work package 1
// Exercise 3
// Submission code: XXXXXX (provided by your TA-s)

// Includes Section
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define Section
#define MAX_NUMBER 10 // Defines the max number of guesses allowed
#define RANGE_MAX 100 // Defines the upper bound of the range for a random number
#define RANGE_MIN 1   // Defines the lower bound of the range for a random number

// Random number generator adapted from this example: https://stackoverflow.com/questions/1190870/i-need-to-generate-random-numbers-in-c
int randomValueGenerator(int upperRange, int lowerRange)
{
    int randomNumber; // Holds the random number generated

    // Sets the starting seed based on current time for each iteration of the random number generator
    srand(time(0));

    // Calculates a random number in the range of 1 - 100. In our case, the part in the parenthesis would evaluate to a randomNumber between 0 and 99. Hence, we add the lower bound to ensure that the number is between 1 and 100.
    // Reference: https://www.includehelp.com/c-programs/generate-random-numbers-within-a-range.aspx
    randomNumber = (rand() % (upperRange - lowerRange + 1)) + lowerRange;

    return randomNumber; // return the generated number
}

// Contains a loop and checker on the number of times a user guessed, and also outputs messages depending on the user input.
void userGuesser(int randomNumber)
{
    int userInputGuess; // Holds the user guess input
    int guessCount = 0; // Counts the number of guesses

    // Keep looping while the user has not guessed the random number, and the guess count is below 10.
    do
    {
        // Output message to console
        printf("Guess the random number between 1-100:\n");
        // Take an input from the user
        scanf("%d", &userInputGuess);

        // Condition where the guess is too high, increases guess counter and asks for another guess
        if (userInputGuess <= 100 && userInputGuess >= 1)
        {
            guessCount++; // Count guess if its within range 1-100

            // Checks if the user's guess is larger than the random number
            if (userInputGuess > randomNumber)
            {
                // prints to console
                printf("Your guess is too high. Try again:\n");
            }
            // Condition where the guess is too low, increases guess counter and asks for another guess
            else if (userInputGuess < randomNumber)
            {
                // prints to console
                printf("Your guess is too low. Try again:\n");
            }
            // Condition where the guess is correct, prints the guess count
            else if (userInputGuess == randomNumber)
            {
                // prints to console and exits method.
                printf("You have guessed %d times and your guess is correct\n\n", guessCount);
                return;
            }
        }
        // If the input is out of range, print to the console.
        else
        {
            //output message.
            printf("Choice not registered! Please input a value between 1 and 100 (inclusive)!\n");
        }
        // Keep looping while the user has not guessed the random number, and the guess count is below 10.
    } while (userInputGuess != randomNumber && guessCount < MAX_NUMBER);

    // Output message to console.
    printf("You have exceeded %d guesses!\n", MAX_NUMBER);
}

// Sets up the game session, calls the guessing game session and calls a random value generator.
void gameSession()
{
    int userInputNewRound; // Declares the "start new round" value
    // Loops the gamesession at least once, and for as long as the user selects to play again
    do
    {
        int randomNumber = randomValueGenerator(RANGE_MAX, RANGE_MIN); // Calls the randomValuleGenerator() and stores the returned value to an int variable
        // Method that starts one game session
        userGuesser(randomNumber);
        // Prints the options to continue the game or exit
        printf("Select an option:\n1. Play again\n2. Exit\n");
        // Takes the answer input from the user
        scanf("%d", &userInputNewRound);

        // Continues to loop unless the user inputs 2
    } while (userInputNewRound != 2);
    // Prints message when exiting the game session
    printf("Exiting..\n");
}

// Main function in the program, no program arguments supported
int main()
{
    // Method that begins the guessing game session
    gameSession();
    // Exits program
    return 0;
}