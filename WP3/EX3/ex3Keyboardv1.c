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

/* ==== Function declarations ==== */
// Checks if a key is pressed and outputs to serial the pressed key
void checkIsKeyPressed();

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

// Reference: https://www.tinkercad.com/things/7bSZ2qg5zBn-copy-of-keypad-4x4-/editel
/* ==== Function implementations === */
void checkIsKeyPressed()
{
    digitalWrite(ROW1, LOW);         // send a signal through row 1
    int r1c1 = digitalRead(COLUMN1); // read the column
    int r1c2 = digitalRead(COLUMN2); // read the column
    int r1c3 = digitalRead(COLUMN3); // read the column
    int r1c4 = digitalRead(COLUMN4); // read the column
    digitalWrite(ROW1, HIGH);

    digitalWrite(ROW2, LOW);         // send a signal through row 2
    int r2c1 = digitalRead(COLUMN1); // read the column
    int r2c2 = digitalRead(COLUMN2); // read the column
    int r2c3 = digitalRead(COLUMN3); // read the column
    int r2c4 = digitalRead(COLUMN4); // read the column
    digitalWrite(ROW2, HIGH);

    digitalWrite(ROW3, LOW);         // send a signal through row 3
    int r3c1 = digitalRead(COLUMN1); // read the column
    int r3c2 = digitalRead(COLUMN2); // read the column
    int r3c3 = digitalRead(COLUMN3); // read the column
    int r3c4 = digitalRead(COLUMN4); // read the column
    digitalWrite(ROW3, HIGH);

    digitalWrite(ROW4, LOW);         // send a signal through row 4
    int r4c1 = digitalRead(COLUMN1); // read the column
    int r4c2 = digitalRead(COLUMN2); // read the column
    int r4c3 = digitalRead(COLUMN3); // read the column
    int r4c4 = digitalRead(COLUMN4); // read the column
    digitalWrite(ROW4, HIGH);
    // TODO: Ask Krasen about the Ifs
    //  if statement to check which key has been pressed
    if (r1c1 == LOW)
    {
        Serial.println("1"); // write to the serial port
        delay(DELAY);        // delay 1 second
    }
    // if statement to check which key has been pressed
    if (r1c2 == LOW)
    {
        Serial.println("2"); // write to the serial port
        delay(DELAY);        // delay 1 second
    }
    // if statement to check which key has been pressed
    if (r1c3 == LOW)
    {
        Serial.println("3"); // write to the serial port
        delay(DELAY);        // delay 1 second
    }
    // if statement to check which key has been pressed
    if (r1c4 == LOW)
    {
        Serial.println("A"); // write to the serial port
        delay(DELAY);        // delay 1 second
    }
    // if statement to check which key has been pressed
    if (r2c1 == LOW)
    {
        Serial.println("4"); // write to the serial port
        delay(DELAY);        // delay 1 second
    }
    // if statement to check which key has been pressed
    if (r2c2 == LOW)
    {
        Serial.println("5"); // write to the serial port
        delay(DELAY);        // delay 1 second
    }
    // if statement to check which key has been pressed
    if (r2c3 == LOW)
    {
        Serial.println("6"); // write to the serial port
        delay(DELAY);        // delay 1 second
    }
    // if statement to check which key has been pressed
    if (r2c4 == LOW)
    {
        Serial.println("B"); // write to the serial port
        delay(DELAY);        // delay 1 second
    }
    // if statement to check which key has been pressed
    if (r3c1 == LOW)
    {
        Serial.println("7"); // write to the serial port
        delay(DELAY);        // delay 1 second
    }
    // if statement to check which key has been pressed
    if (r3c2 == LOW)
    {
        Serial.println("8"); // write to the serial port
        delay(DELAY);        // delay 1 second
    }
    // if statement to check which key has been pressed
    if (r3c3 == LOW)
    {
        Serial.println("9"); // write to the serial port
        delay(DELAY);        // delay 1 second
    }
    // if statement to check which key has been pressed
    if (r3c4 == LOW)
    {
        Serial.println("C"); // write to the serial port
        delay(DELAY);        // delay 1 second
    }
    // if statement to check which key has been pressed
    if (r4c1 == LOW)
    {
        Serial.println("*"); // write to the serial port
        delay(DELAY);        // delay 1 second
    }
    // if statement to check which key has been pressed
    if (r4c2 == LOW)
    {
        Serial.println("0"); // write to the serial port
        delay(DELAY);        // delay 1 second
    }
    // if statement to check which key has been pressed
    if (r4c3 == LOW)
    {
        Serial.println("#"); // write to the serial port
        delay(DELAY);        // delay 1 second
    }
    // if statement to check which key has been pressed
    if (r4c4 == LOW)
    {
        Serial.println("D"); // write to the serial port
        delay(DELAY);        // delay 1 second
    }
}

/* ===== Main loop ===== */
void loop()
{
    // calls method to check and print the key that has been pressed
    checkIsKeyPressed();
}
