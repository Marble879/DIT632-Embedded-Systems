// (C) Markus Emilio Puerto Gutiérrez, Markus Järveläinen, Younis Akel, group: 15 (2022)
// Work package 3
// Exercise 2
// Submission code: XXX (provided by your TA-s)

/* ==== Define section ==== */
#define RED_LED_PIN 7                             // Defines the pin for the red LED
#define GREEN_LED_PIN 6                           // Defines the pin for the green LED
#define YELLOW_LED_PIN 5                          // Defines the pin for the yellow LED
#define TEMP_SENSOR_PIN A0                        // Defines the pin for the temperature sensor
#define LIGHT_SENSOR_PIN A1                       // Defines the pin for the light sensor
#define MAIN_LOOP_DELAY 1000                      // Defines the delay for the main loop
#define LIGHT_INTENSITY_PRINT "Light intensity: " // Defines message for printing light intensity
#define TEMPERATURE_PRINT "Temperature: "         // Defines message for printing temperature
#define LIGHT_ANALOGUE_LOWER_LIMIT 1              // Defines the lower limit for light intensity analogue value
#define LIGHT_ANALOGUE_UPPER_LIMIT 310            // Defines the upper limit for light intensity analogue value
#define PERCENTAGE_MIN 0                          // Defines the min value for the light intensity %
#define PERCENTAGE_MAX 100                        // Defines the max value for the light intensity %
#define VOLTS_5 5.0                               // Defines the volts that the pitemperature sensor is connected to
#define OFFSET 0.5                                // Defines the offset value needed for temperature conversion
#define TEMP_SENSOR_MAX_LIMIT 1024                // defines the maximum limit (non-inclusive) of the temp sensor range
/* ==== Function declarations ==== */
// Reads the temperature sensor's analogue data and returns the temperature in celcius
float readTemperatureCelc();

// Reads the light sensor's analogue data and returns the light intenisty as a percentage
float readLightIntensity();

// Checks for deviations between the temperature and light intensity readings
void checkDeviations(float temperature, float lightIntensity);

// Resets the LEDS to not be on
void resetLeds();

/* ==== Setup function ==== */
void setup()
{
    pinMode(RED_LED_PIN, OUTPUT);     // Sets the pin mode for pin 7 to output
    pinMode(GREEN_LED_PIN, OUTPUT);   // Sets the pin mode for pin 6 to output
    pinMode(YELLOW_LED_PIN, OUTPUT);  // Sets the pin mode for pin 5 to output
    pinMode(TEMP_SENSOR_PIN, INPUT);  // Sets the pin mode for analogue pin 0
    pinMode(LIGHT_SENSOR_PIN, INPUT); // Sets the pin mode for analogue pin 1
    Serial.begin(9600);               // Sets the Serial Monitor speed parameter to 9600
}

/* ==== Function implementations === */

// TODO: too much referencing/online sources?

// Reference: https://learn.adafruit.com/tmp36-temperature-sensor/using-a-temp-sensor
// Reference: https://bc-robotics.com/tutorials/using-a-tmp36-temperature-sensor-with-arduino/
// Function implementation of float readTemperatureCelc();
float readTemperatureCelc()
{
    // Read the value from the temperature sensor pin
    int reading = analogRead(TEMP_SENSOR_PIN);
    // Convert the value into voltage by multiplying by 5 Volts
    float voltage = reading * VOLTS_5;
    // Divide by the range of the value of temperature sensor (0-1023)
    voltage /= TEMP_SENSOR_MAX_LIMIT;

    // Convert to degrees and consider the offset
    float temperatureC = (voltage - OFFSET) * PERCENTAGE_MAX;

    // Return the temperature in Celcius
    return temperatureC;
}

// Reference: https://www.instructables.com/Light-Sensor-Photoresistor-Arduino-Tinkercad/
// Reference: https://techexplorations.com/guides/arduino/programming/map-function/
// Function implmenetation of float readLightIntensity();
float readLightIntensity()
{
    // getting the voltage reading from the temperature sensor
    int reading = analogRead(LIGHT_SENSOR_PIN);
    // Maps the analogue signals to a % representing light amount
    // parameters 1, 310 define the range we are converting from.
    // 0 - 100 defines the range we are converting to.
    float convertedAToD = map(reading, LIGHT_ANALOGUE_LOWER_LIMIT, LIGHT_ANALOGUE_UPPER_LIMIT, PERCENTAGE_MIN, PERCENTAGE_MAX);

    // Return the percentage light intensity
    return convertedAToD;
}

//  Implementation of void checkDeviations(float temperature, float lightIntensity);
void checkDeviations(float temperature, float lightIntensity)
{
    // If the light intensity is 0, and the temperature is higher than -12
    if (lightIntensity == 0 && temperature >= -12)
        // Turn the red LED on due to temperature being too high
        digitalWrite(RED_LED_PIN, HIGH);

    // If the light intensity is  between 1 and 20
    else if (lightIntensity >= 1 && lightIntensity <= 20)
    {
        // If the temperature is lower than -12
        if (temperature < -12)
            // Turn the yellow LED on if the temperature is too low
            digitalWrite(YELLOW_LED_PIN, HIGH);
        // If the temperature is higher than 0
        else if (temperature > 0)
            // Turn the red LED on due to temperature being too high
            digitalWrite(RED_LED_PIN, HIGH);
        else
            // Turn the green LED on if there are no deviations
            digitalWrite(GREEN_LED_PIN, HIGH);
    }
    // If the temperature is between 21 and 60
    else if (lightIntensity >= 21 && lightIntensity <= 60)
    {
        // If the temperature is lower than 0
        if (temperature < 0)
            // Turn the yellow LED on if the temperature is too low
            digitalWrite(YELLOW_LED_PIN, HIGH);
        // If the temperature is higher than 20
        else if (temperature > 20)
            // Turn the red LED on due to temperature being too high
            digitalWrite(RED_LED_PIN, HIGH);
        // If there are no deviations
        else
            // Turn the green LED on if there are no deviations
            digitalWrite(GREEN_LED_PIN, HIGH);
    }
    // If the light intensity is between 61 and 100, and the temperature is below 21
    else if (lightIntensity >= 61 && lightIntensity <= 100 && temperature < 21)
        // Turn the yellow LED on if the temperature is too low
        digitalWrite(YELLOW_LED_PIN, HIGH);
    // If there are no deviations
    else
        // Turn the green LED on if there are no deviations
        digitalWrite(GREEN_LED_PIN, HIGH);
}
// Method that will turn off the LEDs
void resetLeds()
{
    // The below code will set the yellow, green and red leds to low, turning them off
    digitalWrite(YELLOW_LED_PIN, LOW);
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(RED_LED_PIN, LOW);
}

/* ===== Main loop ===== */
void loop()
{
    // Turns all LEDs off
    resetLeds();

    // Reads and converts the temperature sensor's value
    float temp = readTemperatureCelc();

    // Reads and converts the light sensor's value
    float light = readLightIntensity();

    /* Serial prints for testing */
    Serial.println(light);
    Serial.println();
    Serial.println(temp);

    // Checks if there is any deviation in between the light and temperature measurements
    checkDeviations(temp, light);

    // Delays the loop iteration by the value defined
    delay(MAIN_LOOP_DELAY);
}