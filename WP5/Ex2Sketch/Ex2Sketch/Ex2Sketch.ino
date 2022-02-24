// (C) Markus Emilio Puerto Gutiérrez, Markus Järveläinen, Younis Akel, group: 15 (2022)
// Work package 5
// Exercise 1
// Submission code: (provided by your TA-s)

// Includes section
#include <TimerOne.h>

// Defines section
#define VOLTS_5 5.0                   // Defines the volts that the pitemperature sensor is connected to
#define TEMP_SENSOR_MAX_LIMIT 1024    // defines the maximum limit (non-inclusive) of the temp sensor range
#define OFFSET 0.5                    // Defines the offset value needed for temperature conversion
#define PERCENTAGE_MAX 100            // Defines the maximum value of a percentage
#define LED_B 0b00000010              // Defines the pin used for the blue LED
#define LED_BG 0b00000110             // Defines the digital pins used for the green and blue LED
#define LED_BGY 0b00001110            // Defines the digital pins used for the yellow, green and blue LED
#define LED_BGYR 0b00011110           // Defines the digital pins used for the orange, yellow, green and blue LED
#define LED_BGYRR 0b00111110          // Defines the digital pins used for all the LEDs
#define TEMP_PIN A5                   // Defines the pin for the temperature sensor analogue input
#define SERIAL_DATA_RATE 9600         // Defines the data rate for the serial communication
#define TEMP_LOWEST 22               // Defines the lowest temperature range
#define TEMP_LOWER 24                  // Defines the lower temperature range
#define TEMP_MIDDLE 25                // Defines the middle temperature range
#define TEMP_HIGHER 27                // Defines the higher temperature range
#define TEMP_HIGHEST 29              // Defines the highest temperature range
#define INTERRUPT_TIME_PERIOD 1000000 // Defines the time period for when the interrupt occurs
#define TURN_OFF_LEDS 0b00000000      // Defines the a byte to set all the pins to 0

/* ==== Function declarations === */
float readTemperatureCelc();  // Reads and turns the temperature sensor values into temperature
void checkTemperatureRange(); // Checks which range the sensor reading is, and turns on appropriate LEDS
void resetLeds();             // Method that will turn off the LEDs
void measureTemperature();    // Callback method for the interrupt. Will call methods to read temp and adjust leds

/* ==== Setup function ==== */
void setup()
{
    pinMode(TEMP_PIN, INPUT);                   // Set the temperature pin to input mode
    DDRD = B00111110;                           // Set blue, green, yellow, orange, and red LED pins to output mode
    Serial.begin(SERIAL_DATA_RATE);             // Begin serial communication
    Timer1.initialize(INTERRUPT_TIME_PERIOD);   // Initialize timer with 1 second period
    Timer1.attachInterrupt(measureTemperature); // Set the callback function to be executed by the interrupt
}

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
    // Check if the temperature is below or equal to 22 C
    if (temp <= TEMP_LOWEST)
    {
        // Turn the first LEDs on
        PORTD = LED_B;
    }
    // Check if the temperature is greater than 22 C and less or equal to 24 C
    else if (temp > TEMP_LOWEST && temp <= TEMP_LOWER)
    {
        // Turn the first two LEDs on
        PORTD = LED_BG;
    }
    // Check if the temperature is greater than 24 C and less or equal to 25 C
    else if (temp > TEMP_LOWER && temp <= TEMP_MIDDLE)
    {
        // Turn the first three LEDs on
        PORTD = LED_BGY;
    }
    // Check if the temperature is greater than 25 C and less or equal to 27 C
    else if (temp > TEMP_MIDDLE && temp <= TEMP_HIGHER)
    {
        // Turn the first four LEDs on
        PORTD = LED_BGYR;
    }
    // Check if the temperature is greater than 27 C and less or equal to 29 C
    else if (temp > TEMP_HIGHER && temp <= TEMP_HIGHEST)
    {
        // Turn all the LEDs on
        PORTD = LED_BGYRR;
    }
}

// Function implementation of void resetLeds();
void resetLeds()
{
    // The below code will set all the LEDs to low, turning them off
    PORTD = TURN_OFF_LEDS;
}

// Function implementation of void measureTemperature();
void measureTemperature()
{
    resetLeds();                        // Calls the method to turn all LEDs off
    float temp = readTemperatureCelc(); // Get the current temperature in Celsius degrees
    Serial.println(temp);               // Print out the temperature for testing purposes
    checkTemperatureRange(temp);        // Checks the temperature and changes the values of the LEDs accordingly
}

/* ===== Main loop ===== */
void loop()
{
    // Empty
}
