// (C) Markus Emilio Puerto Gutiérrez, Markus Järveläinen, Younis Akel, group: 15 (2022)
// Work package 3
// Exercise 4
// Submission code: XXX (provided by your TA-s)

/* ==== Define section ==== */
#define ROW1 11               // Defines the pin for the first row of the keypad
#define ROW2 10               // Defines the pin for the second row of the keypad
#define ROW3 9                // Defines the pin for the third row of the keypad
#define ROW4 8                // Defines the pin for the fourth row of the keypad
#define COLUMN1 7             // Defines the pin for the first column of the keypad
#define COLUMN2 6             // Defines the pin for the second column of the keypad
#define COLUMN3 5             // Defines the pin for the third column of the keypad
#define COLUMN4 4             // Defines the pin for the fourth column of the keypad
#define BUTTON_PRESS 0        // Defines the value of a pressed button
#define DELAY 1000            // Defines the time to delay the program with
#define SERIAL_DATA_RATE 9600 // Defines the data rate for the serial communication
#define NMBR_COLUMNS 4        // Defines the number of columns in the keypad
#define NMBR_ROWS 4           // Defines the numbers of rows in the keypad

/* ==== Includes section ==== */
#include <Keypad.h>

/* ==== Function declarations ==== */
// Checks if a key is pressed and outputs to serial the pressed key
void checkIsKeyPressed();

// Initialize keypad values.
char keys[NMBR_ROWS][NMBR_COLUMNS] =
    {{'1', '2', '3', 'A'},
     {'4', '5', '6', 'B'},
     {'7', '8', '9', 'C'},
     {'*', '0', '#', 'D'}};

// Assign row pin values to an array
byte rowPins[NMBR_ROWS] = {ROW1, ROW2, ROW3, ROW4};

// Assign column pin values to an array
byte colPins[NMBR_COLUMNS] = {COLUMN1, COLUMN2, COLUMN3, COLUMN4};

// Create a keypad object
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, NMBR_ROWS, NMBR_COLUMNS);

/* ==== Function declarations ==== */
// Checks if a key is pressed and outputs to serial the pressed key
void checkIsKeyPressed();

/* ==== Setup function ==== */
void setup()
{
    // Set the default debounce time to 0 (we delay by 1 second manually later)
    keypad.setDebounceTime(0);
    // Begin serial communication
    Serial.begin(SERIAL_DATA_RATE);
}
/* ==== Function implementations === */

// Implementation of declared function void checkIsKeyPressed();
void checkIsKeyPressed()
{
    // Assign the key that is pressed if nay to customeKey
    char customKey = keypad.getKey();
    if (customKey) // Check if there is a key
    {
        // Print out the key
        Serial.println(customKey);
        // Delay for 1 second
        delay(DELAY);
    }
}

/* ===== Main loop ===== */
void loop()
{
    // Check if the key is pressed and print it out
    checkIsKeyPressed();
}
