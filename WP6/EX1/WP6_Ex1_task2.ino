// (C) Markus Emilio Puerto Gutiérrez, Markus Järveläinen, Younis Akel, group: 15 (2022)
// Work package 6
// Exercise 1 Task 2
// Submission code:  (provided by your TA-s)

// Defines section
#define ENCA 2
#define ENCB 3
#define PWM1 5
#define PWM2 6

int pos = 0; // Position in ticks
int deg = 0; // Position in degrees

int degtarget = 0; // Target position in degrees

int speed = 0; // Desired motor speed

int kp = 5;    // Proportional constant for controller (tuning parameter)
int u_out = 0; // output of controller

int e = 0; // error
int a = 0; // a-encoder signal
int b = 0; // b-encoder signal
int go = 0;

void setup()
{

    Serial.begin(9600);
    pinMode(ENCA, INPUT_PULLUP);
    pinMode(ENCB, INPUT_PULLUP);
    pinMode(PWM1, OUTPUT);
    pinMode(PWM2, OUTPUT);

    /*
    //TODO: TASK 2
    ==> TO DO TO DO TO DO
    ATTACH INTERRUPT HERE.
    */

    // Reference: https://create.arduino.cc/projecthub/curiores/how-to-control-a-dc-motor-with-an-encoder-d1734c
    attachInterrupt(digitalPinToInterrupt(ENCA), ISR_readEncoder, RISING);

    // Start the motor, just a tiny little bit because otherwise TinkerCad dies....
    analogWrite(PWM2, 10);
    delay(1000); // TinkerCad bug
    analogWrite(PWM1, 10);
}

void loop()
{
    // Stop the motor, but not to zero because then TinkerCad dies....
    analogWrite(PWM1, 10);
    delay(1000); // TinkerCad...bug
    analogWrite(PWM2, 10);

    // Check if motor rotated all the way around, and reset counter
    if (pos > 2299)
    {
        deg = deg - 359;
        pos = pos - 2299;
    }
    if (pos < 0)
    {
        deg = 359 + deg;
        pos = 2299 + pos;
    }

    // Print current position
    Serial.print("The current position is: ");
    Serial.print(deg);
    Serial.print("\n");

    // Get input
    degtarget = getInput();

    // Calculate initial error
    e = degtarget - deg;

    go = 1;

    // Loop until error is zero
    while (e)
    {

        // Map current position into degrees
        deg = map(pos, 0, 2299, 0, 359);
        Serial.println("in loop");

        // Get necessary speed signal
        // speed = getAction(e);

        speed = 100;

        // Send speed signal to motor
        // Rotating clockwise
        if (speed >= 0)
        {
            if (speed < 100) // motor does not react with too low inputs
                speed = 100;
            analogWrite(PWM2, 0);

            analogWrite(PWM1, speed); // TODO: NOTE: if comment this out, while loop goes as normal.
                                      //  Is interrupt spammed? But is interupt not called once,
                                      //  then we move on with loop?
        }

        // Rotating counter-clockwise
        else
        {
            if (-speed < 100) // motor does not react with too low inputs
                speed = -100;
            analogWrite(PWM1, 0);
            analogWrite(PWM2, -speed);
        }

        // Calculate new error
        e = degtarget - deg;
    }
    Serial.println("OUTSIDE LOOP");
    go = 0;
}

int getInput()
{

    int ready = 0;
    char buf[3];
    int input = -1;

    Serial.print("Please enter the desired position: \n");

    while (!ready)
    {
        ready = Serial.readBytes(buf, 3);
        input = atoi(&buf[0]);
    }

    return input;
}

int getAction(int error)
{
    /*
    //TODO: TASK 3
    ==> TO DO TO DO TO DO
    Calculate u_out as function of the error and the kp (tuning parameter).
    */

    // u_out = kp*e;

    if (u_out > 254)
    { // u_out cannot be more than 255...
        return 255;
    }
    else if (u_out < -254)
    { //...or less than -254
        return -255;
    }
    else
        return u_out;
}

void ISR_readEncoder()
{
    // if (go == 1)
    //{
    /*
//TODO: task 2
==> TO DO TO DO TO DO
READ THE ENCODER SIGNAL HERE.
Read the encoder signals and increase or decrease pos accordingly.
*/
    Serial.print("ERROR: ");
    Serial.println(e);
    // Reference: https://create.arduino.cc/projecthub/curiores/how-to-control-a-dc-motor-with-an-encoder-d1734c
    b = digitalRead(ENCB);
    // a = digitalRead(ENCA);
    //  If b is greater than 0, we know b must be ahead of a,
    //  hence signal A precedes signal B and the motor is moving
    //  clockwise
    if (b == 0)
    {
        // increment the position
        pos++;
    }
    // Else If b is less than or equal to 0, we know b must be before a,
    // hence signal B precedes signal A and the motor is moving
    // anticlockwise
    else
    {
        // decrement the position
        pos--;
    }
    Serial.print("Pos is: ");
    Serial.println(pos);
    //}
}
// TODO: requirem,ent to read both A and B