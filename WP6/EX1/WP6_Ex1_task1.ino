// (C) Markus Emilio Puerto Gutiérrez, Markus Järveläinen, Younis Akel, group: 15 (2022)
// Work package 6
// Exercise 1 Task 1
// Submission code:  (provided by your TA-s)

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

void setup()
{

  Serial.begin(9600);
  pinMode(ENCA, INPUT_PULLUP);
  pinMode(ENCB, INPUT_PULLUP);
  pinMode(PWM1, OUTPUT);
  pinMode(PWM2, OUTPUT);

  // Start the motor, just a tiny little bit because otherwise TinkerCad dies....
  analogWrite(PWM2, 10);
  delay(1000); // TinkerCad bug
  analogWrite(PWM1, 10);
  delay(1000);             // TinkerCad bug
  speed = getSpeedInput(); // Get the speed input from the user
}

void loop()
{
  // Send speed signal to motor
  // Rotating clockwise
  if (speed >= 0)
  {
    if (speed < 100) // motor does not react with too low inputs
      speed = 100;
    analogWrite(PWM2, 0);
    analogWrite(PWM1, speed);
  }
  // Rotating counter-clockwise
  else
  {
    if (-speed < 100) // motor does not react with too low inputs
      speed = -100;
    analogWrite(PWM1, 0);
    analogWrite(PWM2, -speed);
  }
}

// Same as the provided getInput() method, just has the output adjusted to ask for
// speed rather than position.
int getSpeedInput()
{
  int ready = 0;
  char buf[3];
  int input = -1;

  Serial.print("Please enter the desired speed: \n");

  while (!ready)
  {
    ready = Serial.readBytes(buf, 3);
    input = atoi(&buf[0]);
  }

  return input;
}
