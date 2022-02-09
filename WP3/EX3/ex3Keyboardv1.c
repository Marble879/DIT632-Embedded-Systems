// (C) Markus Emilio Puerto Gutiérrez, Markus Järveläinen, Younis Akel, group: 15 (2022)
// Work package 3
// Exercise 3
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

/* ==== Setup function ==== */
void setup()
{
    // Sets pin11 to OUTPUT
    pinMode(ROW1, OUTPUT);
    // Sets pin10 to OUTPUT
    pinMode(ROW2, OUTPUT);
    // Sets pin9 to OUTPUT
    pinMode(ROW3, OUTPUT);
    // Sets pin8 to OUTPUT
    pinMode(ROW4, OUTPUT);
    // Sets pin7 to OUTPUT
    pinMode(COLUMN1, INPUT);
    // Sets pin6 to OUTPUT
    pinMode(COLUMN2, INPUT);
    // Sets pin5 to OUTPUT
    pinMode(COLUMN3, INPUT);
    // Sets pin4 to OUTPUT
    pinMode(COLUMN4, INPUT);
    // Establish serial communication
    Serial.begin(SERIAL_DATA_RATE);
}

// Reference: https://www.tinkercad.com/things/7bSZ2qg5zBn-copy-of-keypad-4x4-/editel?sharecode=9buIf64v6vqsqXhmqFqn3S8tqacXbhGDk8WLm_iYkKc
/* ==== Function implementations === */
// Implementation of declared function
void checkIsKeyPressed()
{
    // Loop through the number of rows
    for (int i = 0; i < NMBR_ROWS; i++)
    {
        // Set the row to low
        digitalWrite(rowPins[i], LOW);
        // Loop through the columns of a particular row
        for (int j = 0; j < NMBR_COLUMNS; j++)
        {
            // If we read no voltage from a particular column
            if (digitalRead(colPins[j]) == LOW)
            {
                // Print the key value thats being pressed
                Serial.println(keys[i][j]);
                // Delay the program the length of DELAY
                delay(DELAY);
            }
        }
        // Set the row to high
        digitalWrite(rowPins[i], HIGH);
    }
}

/* ===== Main loop ===== */
void loop()
{
    // calls method to check and print the key that has been pressed
    checkIsKeyPressed();
}
