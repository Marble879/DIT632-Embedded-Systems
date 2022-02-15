// (C) Markus Emilio Puerto Gutiérrez, Markus Järveläinen, Younis Akel, group: 15 (2022)
// Work package 4
// Exercise 2
// Submission code: XXXXXX (provided by your TA-s)

// Includes section
#include <Servo.h>

// Defines section
#define SERIAL_DATA_RATE 9600 // Defines the data rate for the serial communication
#define MOTOR_PIN A0          // Defines the pin for the Servo Motor
#define LOWER_DEGREE 0        // Defines the lowest degree for the Servo Motor
#define UPPER_DEGREE 180      // Defines the largest degree for the Servo Motor
#define DELAY 1000            // Defines a 1 second delay
#define DEGREE_TIME_MAPPING 6 // Defines the amount of increment to map degrees to time

Servo servoMotor; // Declare the servo motor
int mDegrees = 0; // Initialize the degrees of the motor to 0
int time = 0;     // Initialize the time passed to 0

/* ==== Function declarations === */
void moveClock(); // Moves the motor clockwise

/* ==== Setup function ==== */
void setup()
{
    servoMotor.attach(MOTOR_PIN, LOWER_DEGREE, UPPER_DEGREE); // Set the motor to pin A0, and set the degrees to 0 to 360
    Serial.begin(SERIAL_DATA_RATE);                           // Begin serial communication
}
/* ==== Function implementations === */
// Function implementation of void moveClock();
void moveClock()
{
    mDegrees = (mDegrees + DEGREE_TIME_MAPPING) % (UPPER_DEGREE + 1); // Increment mDegrees and modulou it so if mDegree is > 180, it is set to 0. Incremenet UPPER_DEGREE (360) by 1 so when mDegrees is 360 it does not get set to 0,
    servoMotor.write(mDegrees);                                       // Turn the Servo Motor mDegrees
    Serial.println(time++);                                           // Print out the time that has passed
}

/* ===== Main loop ===== */
void loop()
{
    moveClock();  // Calls the method that moves the motor clockwise
    delay(DELAY); // Delays the loop by the defined value
}
