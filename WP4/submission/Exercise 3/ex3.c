// (C) Markus Emilio Puerto Gutiérrez, Markus Järveläinen, Younis Akel, group: 15 (2022)
// Work package 4
// Exercise 3
// Submission code: 200908 (provided by your TA-s)

// Includes section
#include <Adafruit_NeoPixel.h>

// Defines section
#define VOLTS_5 5.0                  // Defines the volts that the pitemperature sensor is connected to
#define TEMP_SENSOR_MAX_LIMIT 1024   // defines the maximum limit (non-inclusive) of the temp sensor range
#define OFFSET 0.5                   // Defines the offset value needed for temperature conversion
#define PERCENTAGE_MAX 100           // Defines the maximum value of a percentage
#define TEMP_PIN A0                  // Defines the pin for the temperature sensor analogue input
#define PIN_INITIALIZATION B00001010 // Defines which pins are input/output
#define NUMPIXELS 24                 // Defines the number of all the pixels in the pixel ring
#define NEOPIXEL_PIN 1               // Defines the pin for the Neo Pixel Ring
#define TEMP_LOWEST -20              // Defines the lowest temperature range
#define TEMP_LOWER 0                 // Defines the lower temperature range
#define TEMP_MIDDLE 40               // Defines the middle temperature range
#define TEMP_HIGHER 80               // Defines the higher temperature range
#define TEMP_HIGHEST 125             // Defines the highest temperature range
#define DELAY 1000                   // Defines a 1 second delay
#define LED_PIN B00001000            // Defines the pin for the light pin
#define RESET_PINS B00000000         // Defines the digital pins to not output a voltage
#define RANGE1 6                     // Defines the first temperature range
#define RANGE2 10                    // Defines the Second temperature range
#define RANGE3 16                    // Defines the Third temperature range
#define RANGE4 20                    // Defines the Fourth temperature range
#define RANGE5 24                    // Defines the Fith temperature range

/* ==== Function declarations === */
float readTemperatureCelc();             // Reads and turns the temperature sensor values into temperature
int checkTemperatureRange(float temp);   // Checks which range the sensor reading is in, and turn on appropriate LEDS
int measureTemperature();                // Will call methods to measure and get temperature range
void activatePixels(int numberOfPixels); // Turns a certain num of pixels on

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800); // Create the Neo Pixel Ring with 12 pixels and Pin 1 for the input

/* ==== Setup function ==== */
void setup()
{
    pixels.begin();            // Begin the neopixel
    pixels.show();             // Initialize the pixels to show no colours
    pinMode(TEMP_PIN, INPUT);  // Set the temperature pin to input mode
    DDRD = PIN_INITIALIZATION; // Sets appropriate output/input pins
}

/* ==== Function implementations === */

// Reference: https://learn.adafruit.com/tmp36-temperature-sensor/using-a-temp-sensor
// Reference: https://bc-robotiscs.com/tutorials/using-a-tmp36-temperature-sensor-with-arduino/
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
int checkTemperatureRange(float temp)
{
    // Check if the temperature is below or equal to -20 C
    if (temp <= TEMP_LOWEST)
    {
        // return the number of pixels to turn on for the first range
        return RANGE1;
    }
    // Check if the temperature is greater than -20 C and less or equal to 0 C
    else if (temp > TEMP_LOWEST && temp <= TEMP_LOWER)
    {
        // return the number of pixels to turn on for the second range
        return RANGE2;
    }
    // Check if the temperature is greater than 0 C and less or equal to 40 C
    else if (temp > TEMP_LOWER && temp <= TEMP_MIDDLE)
    {
        // return the number of pixels to turn on for the third range
        return RANGE3;
    }
    // Check if the temperature is greater than 40 C and less or equal to 80 C
    else if (temp > TEMP_MIDDLE && temp <= TEMP_HIGHER)
    {
        // return the number of pixels to turn on for the fourth range
        return RANGE4;
    }
    // Check if the temperature is greater than 80 C and less or equal to 125 C
    else if (temp > TEMP_HIGHER && temp <= TEMP_HIGHEST)
    {
        // Turn on the RED LED
        PORTD = PORTD | LED_PIN;
        // return the number of pixels to turn on for the fith range
        return RANGE5;
    }
}

// Function implementation of void measureTemperature();
int measureTemperature()
{
    float temp = readTemperatureCelc();               // Get the current temperature in Celsius degrees
    int numberOfPixels = checkTemperatureRange(temp); // Checks the temperature and get the number of neo pixel leds to turn on
    return numberOfPixels;                            // Returns the number of pixels to be colored
}

// Function implementation of void activatePixels(int numberOfPixels);
void activatePixels(int numberOfPixels)
{
    // Loop through the pixels that are within the range of pixels
    for (int i = 0; i < numberOfPixels; i++)
    {
        pixels.setPixelColor(i, pixels.Color(0, 0, 255)); // Set the pixel color to blue
        pixels.show();                                    // Show the change of color in the pixel
    }

    // Loop through the remaining pixes that were not changed in the previous loop
    for (int i = 24; i >= numberOfPixels; i--)
    {
        pixels.setPixelColor(i, pixels.Color(0, 0, 0)); // Set the pixel color to white
        pixels.show();                                  // Show the change of color in the pixel
    }
}

/* ===== Main loop ===== */
void loop()
{
    // Resets the LED pin
    PORTD = PORTD & RESET_PINS;

    int numOfPixels = measureTemperature(); // Initialize a variable to store the returned temperature of measureTemperature()

    // Calls the method to color the right amount of pixels
    activatePixels(numOfPixels);

    // Delays the main loop by the defined value
    delay(DELAY);
}
