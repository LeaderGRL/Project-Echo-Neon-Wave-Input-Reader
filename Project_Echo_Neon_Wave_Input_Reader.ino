#include <Uduino.h>
#include <string.h>

volatile float temp, leftCounter, rightCounter = 0.0f; //This variable will increase or decrease depending on the rotation of encoder
Uduino uduino("encoder");
bool right = false;
float v;

void setup() {
  Serial.begin (9600);

  pinMode(2, INPUT_PULLUP); // internal pullup input pin 2 

  pinMode(3, INPUT_PULLUP); // internalเป็น pullup input pin 3
//Setting up interrupt
  //A rising pulse from encodenren activated ai0(). AttachInterrupt 0 is DigitalPin nr 2 on moust Arduino.
  attachInterrupt(0, RightRotary, RISING);

  //B rising pulse from encodenren activated ai1(). AttachInterrupt 1 is DigitalPin nr 3 on moust Arduino.
  //attachInterrupt(1, ai1, RISING);

  //B rising pulse from encodenren activated ai1(). AttachInterrupt 1 is DigitalPin nr 3 on moust Arduino.
  attachInterrupt(1, LeftRotary, RISING);
  }

  void loop() {
    char buffer[10];
    dtostrf(leftCounter, 4, 1, buffer);
    //String data = buffer + ",";
    Serial.println(buffer + ",");
    // Send the value of counter
    if(uduino.isConnected())
    {
      if( counter != temp )
      {
        //v = map(counter, 0, 1000, -4.5, 4.5);
        Serial.println (leftCounter);
        temp = counter;
      }
    }
    uduino.update();
  }

  void RightRotary() {
    // ai0 is activated if DigitalPin nr 2 is going from LOW to HIGH
    // Check pin 3 to determine the direction
    if(digitalRead(3)==LOW) {
      leftCounter += 0.01;
    }else{
      leftCounter -= 0.01;
    }
    if(leftCounter >= 4.5)
    {
      leftCounter = 4.5;
    }

    if(leftCounter <= -4.5)
    {
      leftCounter = -4.5;
    }
  }

  // void ai1() {
  // // ai0 is activated if DigitalPin nr 3 is going from LOW to HIGH
  // // Check with pin 2 to determine the direction
  // if(digitalRead(2)==LOW) {
  // counter -= 0.01;
  // }else{
  // counter += 0.01;
  // }

  //  if(counter >= 4.5)
  // {
  //   counter = 4.5;
  // }

  // if(counter <= -4.5)
  // {
  //   counter = -4.5;
  // }
  
  //}


    void LeftRotary() {
    // LeftRotary is activated if DigitalPin nr 4 is going from LOW to HIGH
    // Check pin 5 to determine the direction
    if(digitalRead(3)==LOW) {
      rightCounter -= 0.01;
    }else{
      rightCounter += 0.01;
    }
    if(rightCounter >= 4.5)
    {
      rightCounter = 4.5;
    }

    if(rightCounter <= -4.5)
    {
      rightCounter = -4.5;
    }
  }