// (C) Markus Emilio Puerto Gutiérrez, Markus Järveläinen, Younis Akel, group: 15 (2022)
// Work package 3
// Exercise 3
// Submission code: XXX (provided by your TA-s)

// Defines section
#define VOLTS_5 5.0                // Defines the volts that the pitemperature sensor is connected to
#define TEMP_SENSOR_MAX_LIMIT 1024 // defines the maximum limit (non-inclusive) of the temp sensor range
#define TEMP_PIN A0                // Defines the pin for the temperature sensor analogue input
#define OFFSET 0.5                 // Defines the offset value needed for temperature conversion
#define PERCENTAGE_MAX 100         // Defines the maximum value of a percentage
#define MAIN_LOOP_DELAY 500        // Defines the delay for the main loop
#define SERIAL_DATA_RATE 9600      // Defines the data rate for the serial communication

/* ==== Function declarations ==== */
float readTemperatureCelc(); // Reads and turns the temperature sensor values into temperature

/* ==== Setup function ==== */
void setup()
{
    pinMode(TEMP_PIN, INPUT);       // Set the temperature pin to input mode
    Serial.begin(SERIAL_DATA_RATE); // Establish serial communication
}

/* ==== Function implementations === */

// Reference: https://learn.adafruit.com/tmp36-temperature-sensor/using-a-temp-sensor
// Reference: https://bc-robotics.com/tutorials/using-a-tmp36-temperature-sensor-with-arduino/
// Function implementation of float readTemperatureCelc();
float readTemperatureCelc()
{
    // Read the value from the temperature sensor pin
    int reading = analogRead(TEMP_PIN);
    // Convert the value into voltage by multiplying by 5 Volts
    float voltage = reading * VOLTS_5;
    // Divide by the range of the value of temperature sensor (0-1023)
    voltage /= TEMP_SENSOR_MAX_LIMIT;

    // Convert to degrees and consider the offset
    float temperatureC = (voltage - OFFSET) * PERCENTAGE_MAX; // TODO: ask krasen if this formula is ok

    // Return the temperature in Celcius
    return temperatureC;
}

/* ===== Main loop ===== */
void loop()
{
    float value = readTemperatureCelc(); // Get the current temperature value and assign it to a variable
    // Print value to serial monitor
    Serial.println(value);
    // Delay the loop using the defined value in millisecond(s)
    delay(MAIN_LOOP_DELAY);
}