// (C) Markus Emilio Puerto Gutiérrez, Markus Järveläinen, Younis Akel, group: 15 (2022)
// Work package 3
// Exercise 2
// Submission code: XXX (provided by your TA-s)

/* ==== Define section ==== */
#define BLINKING_LED_PIN 5  // Defines the pin for the LED the will blink
#define BUTTON_LED_PIN 4    // Defines the pin that is connected to an LED that lights up based on button presses
#define INPUT_BUTTON_PIN 2  // Defines the pin that will read button presses
#define IS_BUTTON_PRESSED 1 // Defines the value of the button being pressed

/* ==== Function declarations ==== */
// Function that will cause an LED to blink repeatedly
void blink();
// Function that turns an LED on/off based on button presses
void button_light();

/* ==== Setup function ==== */
void setup()
{
  // Set the blinking LED pin to output
  pinMode(BLINKING_LED_PIN, OUTPUT);
  // Set the button pin to input
  pinMode(INPUT_BUTTON_PIN, INPUT);
}

/* ==== Function implementations === */

// Implements function void blink();
void blink()
{
  // Turn the LED on
  digitalWrite(BLINKING_LED_PIN, HIGH);
  // wait 500 miliseconds
  delay(500);
  // Turn the LED off
  digitalWrite(BLINKING_LED_PIN, LOW);
  // wait 500 miliseconds
  delay(500);
}

// Implements function void button_light();
void button_light()
{
  // If the button is pressed
  if (digitalRead(INPUT_BUTTON_PIN) == IS_BUTTON_PRESSED)
  {
    // Enable an LED
    digitalWrite(BUTTON_LED_PIN, HIGH);
  }
  // If button is not pressed
  else
  {
    // Turn the LED off
    digitalWrite(BUTTON_LED_PIN, LOW);
  }
}
/* ===== Main loop ===== */
void loop()
{
  // Cause an LED to blink
  blink();
  // Turn LED off/on based on button press
  button_light();
}
