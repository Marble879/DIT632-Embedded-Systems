// (C) Markus Emilio Puerto Gutiérrez, Markus Järveläinen, Younis Akel, group: 15 (2022)
// Work package 1
// Exercise 5
// Submission code: 903280 (provided by your TA-s)

// Include section
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define section
#define MAX 100                 // Defines the maximum number of the values in the table.
#define MAXNUMBER 20            // Defines the maximum value of random numbers.
#define NEW_LINE '\n'           // Defines the new line character.
#define HISTOGRAM_FREQ_ICON 'x' // Defines the frequency of each number character.

// ------ Function declarations   ----------

// This function generates a set of random numbers
// and fills the table *tab with these numbers
void create_random(int *tab);

// This function takes the *tab of random numbers
// and creates a table with the frequency counts for these numbers
void count_frequency(int *tab, int *freq);

// This function takes the frequency count table
// and draws a histogram of the values in that frequency table
void draw_histogram(int *freq);

// ------ Function definitions   ----------

// Implementation of void create_random(int *tab);
void create_random(int *tab)
{
    // Sets the starting seed based on current time for each iteration of the random number generator
    srand(time(0));

    // Loop the random number generation to generate 100 random numbers
    for (int i = 0; i < MAX; i++)
    {
        // Calculates a random number in the range of 0 - 19. Reference: https://www.includehelp.com/c-programs/generate-random-numbers-within-a-range.aspx. The choice of doing it to 19 because the frequency array has 20 elements, and 0 to 19 = 20 elements (while 0 to 20 = 21 elements).
        int randomNumber = rand() % MAXNUMBER;
        // Assign the random number to tab
        tab[i] = randomNumber;
    }
}

// Implementation of void count_frequency(int *tab, int *freq);
void count_frequency(int *tab, int *freq)
{
    // Loop through tab 100 times and count the frequency
    for (int i = 0; i < MAX; i++)
    {
        // Count the frequency of each value in tab.
        // For each encountered value, increment the corresponding index
        // of the freq table by 1. The values (0 - 19) directly correspond to
        // the index of the freq array.
        freq[tab[i]] = freq[tab[i]] + 1;
    }
}

// Implementation of void draw_histogram(int *freq);
void draw_histogram(int *freq)
{
    // Loop through all 20 numbers (0-19)
    for (int i = 0; i < MAXNUMBER; i++)
    {
        // Condition to skip values with frequency of 0
        if (freq[i] == 0)
            continue;
        // Display the values 0-19 as labels
        printf("%d: ", i);
        // display an amount of x that corresponds to the frequency value of the index.
        for (int j = 0; j < freq[i]; j++)
        {
            // Prints an x to mark each occurance of the values
            printf("%c", HISTOGRAM_FREQ_ICON);
        }
        // Display a newline for formatting the table.
        printf("%c", NEW_LINE);
    }
}
// ------ Main   --------------------------

// The main entry point for the program
int main(void)
{
    int table[MAX];                 // Declare the array of size 100
    int frequency[MAXNUMBER] = {0}; // Declare the array of size 20 with all elements as value 0

    // Method to fill the table with random numbers between 0-19
    create_random(table);

    /* // This can be used for testing to see the random numbers contained in the table
    // Will loop through the array of numbers
    for (int i = 0; i < MAX; i++)
    {
        // Prints the number at position i
        printf("%d\n", table[i]);
    }
    // Prints line for readability
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    */

    // Method to get the frequency of numbers of the first array into the second array
    count_frequency(table, frequency);

    // Method to draw the histogram of the frequency
    draw_histogram(frequency);
}