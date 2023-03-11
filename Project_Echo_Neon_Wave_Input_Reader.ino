#include <Uduino.h>

volatile float temp, counter = 0.0f; //This variable will increase or decrease depending on the rotation of encoder
Uduino uduino("encoder");
bool right = false;
float v;

void setup() {
  Serial.begin (9600);

  pinMode(2, INPUT_PULLUP); // internal pullup input pin 2 

  pinMode(3, INPUT_PULLUP); // internalเป็น pullup input pin 3
//Setting up interrupt
  //A rising pulse from encodenren activated ai0(). AttachInterrupt 0 is DigitalPin nr 2 on moust Arduino.
  attachInterrupt(0, ai0, RISING);

  //B rising pulse from encodenren activated ai1(). AttachInterrupt 1 is DigitalPin nr 3 on moust Arduino.
  attachInterrupt(1, ai1, RISING);
  }

  void loop() {
  // Send the value of counter
  if(uduino.isConnected())
  {
    if( counter != temp )
    {
      //v = map(counter, 0, 1000, -4.5, 4.5);
      Serial.println (counter);
      temp = counter;
    }
  }
    uduino.update();
  }

  void ai0() {
  // ai0 is activated if DigitalPin nr 2 is going from LOW to HIGH
  // Check pin 3 to determine the direction
  if(digitalRead(3)==LOW) {
    counter += 0.01;
  }else{
    counter -= 0.01;
  }
  if(counter >= 4.5)
  {
    counter = 4.5;
  }

  if(counter <= -4.5)
  {
    counter = -4.5;
  }
  }

  void ai1() {
  // ai0 is activated if DigitalPin nr 3 is going from LOW to HIGH
  // Check with pin 2 to determine the direction
  if(digitalRead(2)==LOW) {
  counter -= 0.01;
  }else{
  counter += 0.01;
  }

   if(counter >= 4.5)
  {
    counter = 4.5;
  }

  if(counter <= -4.5)
  {
    counter = -4.5;
  }
  
  }