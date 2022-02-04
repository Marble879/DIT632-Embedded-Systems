// C++ code
//
void setup()
{
  pinMode(5, OUTPUT);
  pinMode(2, INPUT);
}

void blink(){
  digitalWrite(5, HIGH);
  delay(1000); // Delay a little bit to improve simulation performance
  digitalWrite(5, LOW);
  delay(1000);
}

void button_light(){
  if (digitalRead(2) == 1) {
  	digitalWrite(4, HIGH);
  } else {
  	digitalWrite(4, LOW);
  }
}

void loop()
{
  blink();
  button_light();
}
