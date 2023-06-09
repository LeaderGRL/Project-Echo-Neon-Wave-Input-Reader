#include <Uduino.h>
#include <string.h>

volatile float temp, leftCounter = -4.5f, rightCounter = 4.5f; //This variable will increase or decrease depending on the rotation of encoder
Uduino uduino("encoder");
bool right = false;
float v;
bool FL = false, L = false, R = false, FR = false;

void setup() {
  Serial.begin (9600);

  pinMode(4, INPUT_PULLUP); // broche A de l'encodeur droit
  pinMode(2, INPUT_PULLUP); // broche B de l'encodeur droit
  pinMode(5, INPUT_PULLUP); // broche A de l'encodeur gauche
  pinMode(3, INPUT_PULLUP); // broche B de l'encodeur gauche
  pinMode(10, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);

  // pinMode(2, INPUT_PULLUP); // internal pullup input pin 2 
  // pinMode(3, INPUT_PULLUP); // internal pullup input pin 3
//Setting up interrupt
  //A rising pulse from encodenren activated ai0(). AttachInterrupt 0 is DigitalPin nr 2 on moust Arduino.
  //Serial.println(digitalPinToInterrupt(9));
  attachInterrupt(0, RightRotary, RISING);

  //B rising pulse from encodenren activated ai1(). AttachInterrupt 1 is DigitalPin nr 3 on moust Arduino.
  //attachInterrupt(1, ai1, RISING);

  //B rising pulse from encodenren activated ai1(). AttachInterrupt 1 is DigitalPin nr 3 on moust Arduino.
  attachInterrupt(1, LeftRotary, RISING);
  }

  void loop() {
    FL = false;
    L = false;
    R = false;
    FR = false;
    readInput();

    Serial.println (String(leftCounter) + ";"  + String(rightCounter) + ";" + String(FL) + ";" + String(L) + ";" + String(R) + ";" + String(FR));
    if(uduino.isConnected())
    {
       //Serial.println (rightCounter);
      if( rightCounter != temp )
      {
        //v = map(counter, 0, 1000, -4.5, 4.5);
        //Serial.println (rightCounter);
        temp = rightCounter;
      }
    }
    uduino.update();
    delay(10);
  }

  void RightRotary() {
    // ai0 is activated if DigitalPin nr 2 is going from LOW to HIGH
    // Check pin 3 to determine the direction
    if(digitalRead(4)==LOW) {
      rightCounter += 0.01;
    }else{
      rightCounter -= 0.01;
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

  void readInput()
  {
    //Serial.println("test");
    if (digitalRead(10) == LOW)
    {
      FL = true;
    }
    if (digitalRead(11) == LOW)
    {
      L = true;
    }
    if (digitalRead(12) == LOW)
    {
      R = true;
    }
    if (digitalRead(9) == LOW)
    {
      FR = true;
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
    if(digitalRead(5)==LOW) {
      leftCounter -= 0.01;
    }else{
      leftCounter += 0.01;
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