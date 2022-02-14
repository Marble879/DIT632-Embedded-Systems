// (C) Markus Emilio Puerto Gutiérrez, Markus Järveläinen, Younis Akel, group: 15 (2022)
// Work package 4
// Exercise 1
// Submission code: XXXXXX (provided by your TA-s)

// Defines section
#define VOLTS_5 5.0                // Defines the volts that the pitemperature sensor is connected to
#define TEMP_SENSOR_MAX_LIMIT 1024 // defines the maximum limit (non-inclusive) of the temp sensor range
#define OFFSET 0.5                 // Defines the offset value needed for temperature conversion
#define PERCENTAGE_MAX 100         // Defines the maximum value of a percentage
#define LED_BLUE 1                 // Defines the digital pin used for the blue LED
#define LED_GREEN 2                // Defines the digital pin used for the green LED
#define LED_YELLOW 3               // Defines the digital pin used for the yellow LED
#define LED_ORANGE 4               // Defines the digital pin used for the orange LED
#define LED_RED 5                  // Defines the digital pin used for the blue LED
#define TEMP_PIN A5                // Defines the pin for the temperature sensor analogue input
#define NUM_OF_PINS 5              // Defines the amount of pins for the array size
#define SERIAL_DATA_RATE 9600      // Defines the data rate for the serial communication
#define TEMP_LOWEST -20            // Defines the lowest temperature range
#define TEMP_LOWER 0               // Defines the lower temperature range
#define TEMP_MIDDLE 40             // Defines the middle temperature range
#define TEMP_HIGHER 80             // Defines the higher temperature range
#define TEMP_HIGHEST 125           // Defines the highest temperature range

/* ==== Function declarations === */
float readTemperatureCelc();    // Reads and turns the temperature sensor values into temperature
void checkTemperatureRange();   // Checks which range the sensor reading is, and turns on appropriate LEDS
void resetLeds();               // Method that will turn off the LEDs
void turnOnLeds(int numOfLeds); // Method that will turn on specific LEDS

/* ==== Setup function ==== */
void setup()
{
    pinMode(TEMP_PIN, INPUT); // Set the temperature pin to input mode

    // TODO: Ask Krasen if bit manipulation would simplify the five lines below
    pinMode(LED_BLUE, OUTPUT);      // Set the blue LED pin to output mode
    pinMode(LED_GREEN, OUTPUT);     // Set the green LED pin to output mode
    pinMode(LED_YELLOW, OUTPUT);    // Set the yellow LED pin to output mode
    pinMode(LED_ORANGE, OUTPUT);    // Set the orange LED pin to output mode
    pinMode(LED_RED, OUTPUT);       // Set the red LED pin to output mode
    Serial.begin(SERIAL_DATA_RATE); // Begin serial communication
}

// Initialize an array of LED pins
byte LEDPins[NUM_OF_PINS] = {LED_BLUE, LED_GREEN, LED_YELLOW, LED_ORANGE, LED_RED};

/* ==== Function implementations === */

// Reference: https://learn.adafruit.com/tmp36-temperature-sensor/using-a-temp-sensor
// Reference: https://bc-robotics.com/tutorials/using-a-tmp36-temperature-sensor-with-arduino/
// Function implementation of float readTemperatureCelc();
float readTemperatureCelc()
{
    // Read the value from the temperature sensor pin
    int reading = analogRead(TEMP_PIN);
    // 1024 analogue if we have 5V. Hence, we do (analogReading * 5) / 1024. (ratios)
    // Convert the value into voltage by multiplying by 5 Volts
    float voltage = reading * VOLTS_5;
    // Divide by the range of the value of temperature sensor (0-1023)
    voltage /= TEMP_SENSOR_MAX_LIMIT;

    // Convert to degrees and consider the offset
    float temperatureC = (voltage - OFFSET) * PERCENTAGE_MAX; // percentage max is because 10mV / 1degrees. Hence, 100 =  1/0.01. Voltage * (1 degrees / 0.01V) = Temp in celcius.

    // Return the temperature in Celcius
    return temperatureC;
}

// Function implementation of void checkTemperatureRange();
void checkTemperatureRange(float temp)
{
    // Check if the temperature is below or equal to -20 C
    if (temp <= TEMP_LOWEST)
    {
        // Turn the first LEDs on
        // TODO: Bit maniuplation vs looping through ask TA?
        // turnOnLeds(1);
        PORTD = 0b00000010;
    }
    // Check if the temperature is greater than -20 C and less or equal to 0 C
    else if (temp > TEMP_LOWEST && temp <= TEMP_LOWER)
    {
        // Turn the first two LEDs on
        // turnOnLeds(2);
        PORTD = 0b00000110;
    }
    // Check if the temperature is greater than 0 C and less or equal to 40 C
    else if (temp > TEMP_LOWER && temp <= TEMP_MIDDLE)
    {
        // Turn the first three LEDs on
        // turnOnLeds(3);
        PORTD = 0b00001110;
    }
    // Check if the temperature is greater than 40 C and less or equal to 80 C
    else if (temp > TEMP_MIDDLE && temp <= TEMP_HIGHER)
    {
        // Turn the first four LEDs on
        // turnOnLeds(4);
        PORTD = 0b00011110;
    }
    // Check if the temperature is greater than 80 C and less or equal to 125 C
    else if (temp > TEMP_HIGHER && temp <= TEMP_HIGHEST)
    {
        // Turn all the LEDs on
        // turnOnLeds(5);
        PORTD = 0b00111110;
    }
}

// Function implementation of void resetLeds();
void resetLeds()
{
    // The below code will set all the LEDs to low, turning them off
    PORTD = 0b00000000;
}

// TODO: Remove?
// Function implementation of void turnOnLeds(int numOfLeds);
void turnOnLeds(int numOfLeds)
{
    // Loop through the amount of LEDs that are given in the parameter.
    for (int i = 0; i < numOfLeds; i++)
        // Set the current pin to HIGH
        digitalWrite(LEDPins[i], HIGH);
}

/* ===== Main loop ===== */
void loop()
{
    // TODO: Use interrupt somehow
    resetLeds();                        // Calls the method to turn all LEDs off
    float temp = readTemperatureCelc(); // Get the current temperature in Celsius degrees
    Serial.println(temp);               // Print out the temperature for testing purposes
    checkTemperatureRange(temp);        // Checks the temperature and changes the values of the LEDs accordingly
    delay(500);                         // Delays the program 500 ms
}
