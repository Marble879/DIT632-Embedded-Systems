// (C) Markus Emilio Puerto Gutiérrez, Markus Järveläinen, Younis Akel, group: 15 (2022)
// Work package 4
// Exercise 1
// Submission code: XXXXXX (provided by your TA-s)

/*
 *  Interrupt and PWM utilities for 16 bit Timer1 on ATmega168/328
 *  Original code by Jesse Tane for http://labs.ideo.com August 2008
 *  Modified March 2009 by Jérôme Despatis and Jesse Tane for ATmega328 support
 *  Modified June 2009 by Michael Polli and Jesse Tane to fix a bug in setPeriod() which caused the timer to stop
 *  Modified June 2011 by Lex Talionis to add a function to read the timer
 *  Modified Oct 2011 by Andrew Richards to avoid certain problems:
 *  - Add (long) assignments and casts to TimerOne::read() to ensure calculations involving tmp, ICR1 and TCNT1 aren't truncated
 *  - Ensure 16 bit registers accesses are atomic - run with interrupts disabled when accessing
 *  - Remove global enable of interrupts (sei())- could be running within an interrupt routine)
 *  - Disable interrupts whilst TCTN1 == 0.  Datasheet vague on this, but experiment shows that overflow interrupt
 *    flag gets set whilst TCNT1 == 0, resulting in a phantom interrupt.  Could just set to 1, but gets inaccurate
 *    at very short durations
 *  - startBottom() added to start counter at 0 and handle all interrupt enabling.
 *  - start() amended to enable interrupts
 *  - restart() amended to point at startBottom()
 * Modiied 7:26 PM Sunday, October 09, 2011 by Lex Talionis
 *  - renamed start() to resume() to reflect it's actual role
 *  - renamed startBottom() to start(). This breaks some old code that expects start to continue counting where it left off
 *
 *  This program is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  See Google Code project http://code.google.com/p/arduino-timerone/ for latest
 */
#ifndef TIMERONE_h
#define TIMERONE_h

#include <avr/io.h>
#include <avr/interrupt.h>

#define RESOLUTION 65536 // Timer1 is 16 bit

class TimerOne
{
public:
    // properties
    unsigned int pwmPeriod;
    unsigned char clockSelectBits;
    char oldSREG; // To hold Status Register while ints disabled

    // methods
    void initialize(long microseconds = 1000000);
    void start();
    void stop();
    void restart();
    void resume();
    unsigned long read();
    void pwm(char pin, int duty, long microseconds = -1);
    void disablePwm(char pin);
    void attachInterrupt(void (*isr)(), long microseconds = -1);
    void detachInterrupt();
    void setPeriod(long microseconds);
    void setPwmDuty(char pin, int duty);
    void (*isrCallback)();
};

extern TimerOne Timer1;
#endif

/*
 *  Interrupt and PWM utilities for 16 bit Timer1 on ATmega168/328
 *  Original code by Jesse Tane for http://labs.ideo.com August 2008
 *  Modified March 2009 by Jérôme Despatis and Jesse Tane for ATmega328 support
 *  Modified June 2009 by Michael Polli and Jesse Tane to fix a bug in setPeriod() which caused the timer to stop
 *  Modified June 2011 by Lex Talionis to add a function to read the timer
 *  Modified Oct 2011 by Andrew Richards to avoid certain problems:
 *  - Add (long) assignments and casts to TimerOne::read() to ensure calculations involving tmp, ICR1 and TCNT1 aren't truncated
 *  - Ensure 16 bit registers accesses are atomic - run with interrupts disabled when accessing
 *  - Remove global enable of interrupts (sei())- could be running within an interrupt routine)
 *  - Disable interrupts whilst TCTN1 == 0.  Datasheet vague on this, but experiment shows that overflow interrupt
 *    flag gets set whilst TCNT1 == 0, resulting in a phantom interrupt.  Could just set to 1, but gets inaccurate
 *    at very short durations
 *  - startBottom() added to start counter at 0 and handle all interrupt enabling.
 *  - start() amended to enable interrupts
 *  - restart() amended to point at startBottom()
 * Modiied 7:26 PM Sunday, October 09, 2011 by Lex Talionis
 *  - renamed start() to resume() to reflect it's actual role
 *  - renamed startBottom() to start(). This breaks some old code that expects start to continue counting where it left off
 *
 *  This program is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  See Google Code project http://code.google.com/p/arduino-timerone/ for latest
 */
#ifndef TIMERONE_cpp
#define TIMERONE_cpp

// #include "TimerOne.h"

TimerOne Timer1; // preinstatiate

ISR(TIMER1_OVF_vect) // interrupt service routine that wraps a user defined function supplied by attachInterrupt
{
    Timer1.isrCallback();
}

void TimerOne::initialize(long microseconds)
{
    TCCR1A = 0;          // clear control register A
    TCCR1B = _BV(WGM13); // set mode 8: phase and frequency correct pwm, stop the timer
    setPeriod(microseconds);
}

void TimerOne::setPeriod(long microseconds) // AR modified for atomic access
{

    long cycles = (F_CPU / 2000000) * microseconds; // the counter runs backwards after TOP, interrupt is at BOTTOM so divide microseconds by 2
    if (cycles < RESOLUTION)
        clockSelectBits = _BV(CS10); // no prescale, full xtal
    else if ((cycles >>= 3) < RESOLUTION)
        clockSelectBits = _BV(CS11); // prescale by /8
    else if ((cycles >>= 3) < RESOLUTION)
        clockSelectBits = _BV(CS11) | _BV(CS10); // prescale by /64
    else if ((cycles >>= 2) < RESOLUTION)
        clockSelectBits = _BV(CS12); // prescale by /256
    else if ((cycles >>= 2) < RESOLUTION)
        clockSelectBits = _BV(CS12) | _BV(CS10); // prescale by /1024
    else
        cycles = RESOLUTION - 1, clockSelectBits = _BV(CS12) | _BV(CS10); // request was out of bounds, set as maximum

    oldSREG = SREG;
    cli();                     // Disable interrupts for 16 bit register access
    ICR1 = pwmPeriod = cycles; // ICR1 is TOP in p & f correct pwm mode
    SREG = oldSREG;

    TCCR1B &= ~(_BV(CS10) | _BV(CS11) | _BV(CS12));
    TCCR1B |= clockSelectBits; // reset clock select register, and starts the clock
}

void TimerOne::setPwmDuty(char pin, int duty)
{
    unsigned long dutyCycle = pwmPeriod;

    dutyCycle *= duty;
    dutyCycle >>= 10;

    oldSREG = SREG;
    cli();
    if (pin == 1 || pin == 9)
        OCR1A = dutyCycle;
    else if (pin == 2 || pin == 10)
        OCR1B = dutyCycle;
    SREG = oldSREG;
}

void TimerOne::pwm(char pin, int duty, long microseconds) // expects duty cycle to be 10 bit (1024)
{
    if (microseconds > 0)
        setPeriod(microseconds);
    if (pin == 1 || pin == 9)
    {
        DDRB |= _BV(PORTB1);   // sets data direction register for pwm output pin
        TCCR1A |= _BV(COM1A1); // activates the output pin
    }
    else if (pin == 2 || pin == 10)
    {
        DDRB |= _BV(PORTB2);
        TCCR1A |= _BV(COM1B1);
    }
    setPwmDuty(pin, duty);
    resume(); // Lex - make sure the clock is running.  We don't want to restart the count, in case we are starting the second WGM
              // and the first one is in the middle of a cycle
}

void TimerOne::disablePwm(char pin)
{
    if (pin == 1 || pin == 9)
        TCCR1A &= ~_BV(COM1A1); // clear the bit that enables pwm on PB1
    else if (pin == 2 || pin == 10)
        TCCR1A &= ~_BV(COM1B1); // clear the bit that enables pwm on PB2
}

void TimerOne::attachInterrupt(void (*isr)(), long microseconds)
{
    if (microseconds > 0)
        setPeriod(microseconds);
    isrCallback = isr;   // register the user's callback with the real ISR
    TIMSK1 = _BV(TOIE1); // sets the timer overflow interrupt enable bit
                         // might be running with interrupts disabled (eg inside an ISR), so don't touch the global state
                         //  sei();
    resume();
}

void TimerOne::detachInterrupt()
{
    TIMSK1 &= ~_BV(TOIE1); // clears the timer overflow interrupt enable bit
                           // timer continues to count without calling the isr
}

void TimerOne::resume() // AR suggested
{
    TCCR1B |= clockSelectBits;
}

void TimerOne::restart() // Depricated - Public interface to start at zero - Lex 10/9/2011
{
    start();
}

void TimerOne::start() // AR addition, renamed by Lex to reflect it's actual role
{
    unsigned int tcnt1;

    TIMSK1 &= ~_BV(TOIE1); // AR added
    GTCCR |= _BV(PSRSYNC); // AR added - reset prescaler (NB: shared with all 16 bit timers);

    oldSREG = SREG; // AR - save status register
    cli();          // AR - Disable interrupts
    TCNT1 = 0;
    SREG = oldSREG; // AR - Restore status register
    resume();
    do
    { // Nothing -- wait until timer moved on from zero - otherwise get a phantom interrupt
        oldSREG = SREG;
        cli();
        tcnt1 = TCNT1;
        SREG = oldSREG;
    } while (tcnt1 == 0);

    //  TIFR1 = 0xff;              		// AR - Clear interrupt flags
    //  TIMSK1 = _BV(TOIE1);              // sets the timer overflow interrupt enable bit
}

void TimerOne::stop()
{
    TCCR1B &= ~(_BV(CS10) | _BV(CS11) | _BV(CS12)); // clears all clock selects bits
}

unsigned long TimerOne::read() // returns the value of the timer in microseconds
{                              // rember! phase and freq correct mode counts up to then down again
    unsigned long tmp;         // AR amended to hold more than 65536 (could be nearly double this)
    unsigned int tcnt1;        // AR added

    oldSREG = SREG;
    cli();
    tmp = TCNT1;
    SREG = oldSREG;

    char scale = 0;
    switch (clockSelectBits)
    {
    case 1: // no prescalse
        scale = 0;
        break;
    case 2: // x8 prescale
        scale = 3;
        break;
    case 3: // x64
        scale = 6;
        break;
    case 4: // x256
        scale = 8;
        break;
    case 5: // x1024
        scale = 10;
        break;
    }

    do
    { // Nothing -- max delay here is ~1023 cycles.  AR modified
        oldSREG = SREG;
        cli();
        tcnt1 = TCNT1;
        SREG = oldSREG;
    } while (tcnt1 == tmp); // if the timer has not ticked yet

    // if we are counting down add the top value to how far we have counted down
    tmp = ((tcnt1 > tmp) ? (tmp) : (long)(ICR1 - tcnt1) + (long)ICR1); // AR amended to add casts and reuse previous TCNT1
    return ((tmp * 1000L) / (F_CPU / 1000L)) << scale;
}

#endif

// Defines section
#define VOLTS_5 5.0                   // Defines the volts that the pitemperature sensor is connected to
#define TEMP_SENSOR_MAX_LIMIT 1024    // defines the maximum limit (non-inclusive) of the temp sensor range
#define OFFSET 0.5                    // Defines the offset value needed for temperature conversion
#define PERCENTAGE_MAX 100            // Defines the maximum value of a percentage
#define LED_B 0b00000010              // Defines the pin used for the blue LED
#define LED_BG 0b00000110             // Defines the digital pin used for the green and blue LED
#define LED_BGY 0b00001110            // Defines the digital pin used for the yellow, green and blue LED
#define LED_BGYO 0b00011110           // Defines the digital pin used for the orange, yellow, green and blue LED
#define LED_BGYOR 0b00111110          // Defines the digital pin used for all the LEDs
#define TEMP_PIN A5                   // Defines the pin for the temperature sensor analogue input
#define NUM_OF_PINS 5                 // Defines the amount of pins for the array size
#define SERIAL_DATA_RATE 9600         // Defines the data rate for the serial communication
#define TEMP_LOWEST -20               // Defines the lowest temperature range
#define TEMP_LOWER 0                  // Defines the lower temperature range
#define TEMP_MIDDLE 40                // Defines the middle temperature range
#define TEMP_HIGHER 80                // Defines the higher temperature range
#define TEMP_HIGHEST 125              // Defines the highest temperature range
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
    pinMode(TEMP_PIN, INPUT);                 // Set the temperature pin to input mode
    DDRD = B00111110;                         // Set blue, green, yellow, orange, and red LED pins to output mode
    Serial.begin(SERIAL_DATA_RATE);           // Begin serial communication
    Timer1.initialize(INTERRUPT_TIME_PERIOD); // Initialize timer with 1 second period
    Timer1.attachInterrupt(measureTemperature);
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

    // Return the tem0b00111110perature in Celcius
    return temperatureC;
}

// Function implementation of void checkTemperatureRange();
void checkTemperatureRange(float temp)
{
    // Check if the temperature is below or equal to -20 C
    if (temp <= TEMP_LOWEST)
    {
        // Turn the first LEDs on
        PORTD = LED_B;
    }
    // Check if the temperature is greater than -20 C and less or equal to 0 C
    else if (temp > TEMP_LOWEST && temp <= TEMP_LOWER)
    {
        // Turn the first two LEDs on
        PORTD = LED_BG;
    }
    // Check if the temperature is greater than 0 C and less or equal to 40 C
    else if (temp > TEMP_LOWER && temp <= TEMP_MIDDLE)
    {
        // Turn the first three LEDs on
        PORTD = LED_BGY;
    }
    // Check if the temperature is greater than 40 C and less or equal to 80 C
    else if (temp > TEMP_MIDDLE && temp <= TEMP_HIGHER)
    {
        // Turn the first four LEDs on
        PORTD = LED_BGYO;
    }
    // Check if the temperature is greater than 80 C and less or equal to 125 C
    else if (temp > TEMP_HIGHER && temp <= TEMP_HIGHEST)
    {
        // Turn all the LEDs on
        PORTD = LED_BGYOR;
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
}
