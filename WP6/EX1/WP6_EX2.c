// (C) Markus Emilio Puerto Gutiérrez, Markus Järveläinen, Younis Akel, group: 15 (2022)
// Work package 6
// Exercise 2
// Submission code:  (provided by your TA-s)

// Defines section
#define MAX_DISTANCE 200         // Defines the maximum distance used by the ultrasonic sensor
#define MEDIUM_DISTANCE 130      // Defines a medium distance used by the ultrasonic sensor
#define CLOSE_DISTANCE 70        // Defines a close distance used by the ultrasonic sensor
#define SMALL_DISTANCE 30        // Defines a very close distance used by the ultrasonic sensor
#define MIN_DISTANCE 25          // Defines the minimum sistance used by the ultrasonic sensor
#define BUZZER 9                 // Defines the pin for the buzzer
#define CONVERSION_VALUE 0.01723 // Defines the value used for distance reading conversion
#define MAIN_DELAY 10            // Defines the delay for the main loop

#define SPEAKER_MAX 1500        // Defines the maximum frequency of the speaker
#define SPEAKER_ALMOST_MAX 1000 // Defines the almost max frequency of the speaker
#define SPEAKER_MEDIUM 800      // Defines the medium frequency of the speaker
#define SPEAKER_ALMOST_MIN 400  // Defines the small frequency of the speaker
#define SPEAKER_MIN 100         // Defines the smallest frequency of the speaker
#define SPEAKER_OFF 0           // Defines the speaker off frequency
#define SPEAKER_DURATION 3000   // Defines the duration for the piezo peaker

#define ALL_LEDS_ON 0b00111100   // Defines the pins to enable all LEDS
#define THREE_LEDS_ON 0b00011100 // Defines the pins to enable three LEDS
#define TWO_LEDS_ON 0b00001100   // Defines the pins to enable two LEDS
#define ONE_LED_ON 0b00000100    // Defines the pins to enable one LED
#define RESET_PINS 0b1000011     // Defines the pin values to reset the pins. This is the MASK for the bit masking
#define LED_BLINK_DELAY 250      // Defines a delay used for blinking the LEDs

// Function defintions
int getDistanceReading();               // Takes distance reading and returns the distance between car and object
void detectDistanceRange(int distance); // Compares the distance to predefined ranges and calls appropriate methods.
void enableLEDs(unsigned char pins);    // Takes a byte and based on the bits that are set to 1, it enables the appropriate LEDs
void controlSpeaker(int volume);        // Takes the volume and sounds the speaker
void resetLEDs();                       // Turns off all the LEDS
void blinkLEDs();                       // Blinks all of the LEDs

// Function implementations

// Function implementation of int getDistanceReading(int triggerPin, int echoPin);
int getDistanceReading(int triggerPin, int echoPin)
{
    pinMode(triggerPin, OUTPUT); // Set the signal pin to ouput

    digitalWrite(triggerPin, LOW); // Set the value of the pin to LOW
    delayMicroseconds(2);          // Delay for two microseconds

    digitalWrite(triggerPin, HIGH); // Set the value of the pin to HIGH
    delayMicroseconds(10);          // Delay for 10 microseconds

    digitalWrite(triggerPin, LOW); // Set the value of the pin to LOW
    pinMode(echoPin, INPUT);       // Set the signal pin to input

    // Return the distance between the signal and the object
    return pulseIn(echoPin, HIGH);
}

// Function used for taking appropriate action depending on the distance
void detectDistanceRange(int distance)
{
    // If the distance is greater than 200
    if (distance > MAX_DISTANCE)
    {
        // Turn off the leds
        resetLEDS();
        // Turn off the speaker
        controlSpeaker(SPEAKER_OFF);
    }
    // if the distance is between 200 and 130
    else if (distance <= MAX_DISTANCE && distance > MEDIUM_DISTANCE)
    {
        // turn one led on
        enableLEDs(ONE_LED_ON);
        // set the speaker to the min volume
        controlSpeaker(SPEAKER_MIN);
    }
    // if the distance is between 130 and 70
    else if (distance <= MEDIUM_DISTANCE && distance > CLOSE_DISTANCE)
    {
        // Enable two LEDS
        enableLEDs(TWO_LEDS_ON);
        // set speaker to have a volume of almost min
        controlSpeaker(SPEAKER_ALMOST_MIN);
    }
    // if the distance is between 70 and 30
    else if (distance <= CLOSE_DISTANCE && distance > SMALL_DISTANCE)
    {
        // turn on 3 LEDS
        enableLEDs(THREE_LEDS_ON);
        // Set the speaker volume to medium
        controlSpeaker(SPEAKER_MEDIUM);
    }
    // If the distance is between 30 and 25
    else if (distance <= SMALL_DISTANCE && distance > MIN_DISTANCE)
    {
        // enable all of the LEDS
        enableLEDs(ALL_LEDS_ON);
        // Set the speaker to a very high volume
        controlSpeaker(SPEAKER_ALMOST_MAX);
    }
    // If the distance is less tha 2
    else if (distance <= MIN_DISTANCE)
    {
        // Cause LEDS to blink frequently
        blinkLEDs();
        // Set the speaker volume to the max
        controlSpeaker(SPEAKER_MAX);
    }
}

// Function used to turn on the specified LEDs
void enableLEDs(unsigned char pins)
{
    // Set PORTD pins to enable the specified pins
    PORTD = pins;
}

// Function used to blink all LEDs
void blinkLEDs()
{
    // Enables the defined LEDs
    enableLEDs(ALL_LEDS_ON);
    // Delays the blinking by the defined value
    delay(LED_BLINK_DELAY);
    // Turns off all LEDs
    resetLEDS();
    // Delays the blinking by the defined value
    delay(LED_BLINK_DELAY);
}

// Function used for controlling the speaker volume
void controlSpeaker(int volume)
{
    // If the volume received is 0
    if (volume == 0)
    {
        // Call built in function to turn off tone of the buzzer
        noTone(BUZZER);
    }
    // Set the buzzer to volume defined by the parameter
    tone(BUZZER, volume, 3000);
}

// Function used to turn off all the LEDs
void resetLEDS()
{
    // Mask the bits to set all LED pins to 0, and leave other bits the value they were before.
    PORTD = PORTD & RESET_PINS;
}

/* ==== Setup function ==== */
void setup()
{
    DDRD = B00111100; // Set the LED pins to output mode
}

/* ===== Main loop ===== */
void loop()
{
    int iDistance = CONVERSION_VALUE * getDistanceReading(7, 7); // convert the travel time to distance
    // Compare the iDistance to the ranges defined, and call appropriate methods
    detectDistanceRange(iDistance);
    // Delays the loop by the defined value
    delay(MAIN_DELAY);
}