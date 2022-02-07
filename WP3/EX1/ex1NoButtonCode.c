// (C) Markus Emilio Puerto Gutiérrez, Markus Järveläinen, Younis Akel, group: 15 (2022)
// Work package 3
// Exercise 1
// Submission code: XXX (provided by your TA-s)

/* ==== Define section ==== */
#define BLINKING_LED_PIN 5 // Defines the pin for the LED the will blink

/* ==== Function declarations ==== */
// Function that will cause an LED to blink repeatedly
void blink();

/* ==== Setup function ==== */
void setup()
{
    // Set the blinking LED pin to output
    pinMode(BLINKING_LED_PIN, OUTPUT);
}

/* ==== Function implementations === */

// Implements function void blink();
void blink()
{
    // Turn the LED on
    digitalWrite(BLINKING_LED_PIN, HIGH);
    // wait 500 miliseconds
    delay(1000);
    // Turn the LED off
    digitalWrite(BLINKING_LED_PIN, LOW);
    // wait 500 miliseconds
    delay(1000);
}
/* ===== Main loop ===== */
void loop()
{
    // Cause an LED to blink
    blink();
}
