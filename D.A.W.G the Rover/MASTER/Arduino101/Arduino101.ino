//SPI
#include <SPI.h>
bool notRunning = true; // prevent code from running twice

//Motor Control
char mcDir;
int speed = 200;

//Variable Controls:
//
// 1 -Motor 1 Left
// 2 -Motor 1 Stop
// 3 -Motor 1 Right
//
// 4 -Motor 2 Left
// 5 -Motor 2 Stop
// 6 -Motor 2 Right

// Declare L298N Dual H-Bridge Motor Controller directly since there is not a library to load.

// Motor 1
int dir1PinA = 2; // IN1
int dir2PinA = 3; // IN2
int speedPinA = 9; // EN Needs to be a PWM pin to be able to control motor speed

// Motor 2
int dir1PinB = 4; // IN1
int dir2PinB = 5; // IN2
int speedPinB = 10; // EN Needs to be a PWM pin to be able to control motor speed

void setup() {  // Setup runs once per reset
// initialize serial communication @ 9600 baud:
Serial.begin(9600);

//SPI
  // Initialize SPI pins.
  pinMode(SCK, INPUT);
  pinMode(MOSI, INPUT);
  pinMode(MISO, INPUT);
  pinMode(SS, INPUT);
  // Enable SPI as slave.
  SPCR = (1 << SPE);  

//Define L298N Dual H-Bridge Motor Controller Pins
pinMode(dir1PinA,OUTPUT);
pinMode(dir2PinA,OUTPUT);
pinMode(speedPinA,OUTPUT);
pinMode(dir1PinB,OUTPUT);
pinMode(dir2PinB,OUTPUT);
pinMode(speedPinB,OUTPUT);
}

void loop() {                   //Compares for motor control
  //SPI
     getData(mcDir);
     mc(mcDir);  
  // Initialize the Serial interface:
  if (Serial.available() > 0) {
    mcDir = Serial.read(); //Here is where you enter motor control int
    speed = 0; // Local variable
    mc(mcDir);
  }
  delay(300);
  
}

char getData(char &y) {
    if(notRunning && !digitalRead(SS)) {
    notRunning = false;
    pinMode(MISO, OUTPUT);
    //Serial.println("Slave Enabled.");
    byte x = SPI.transfer(255); // 255 tells spi to recive data
    Serial.println((char) x);
    return y=x;
  } else {
    delay(20); // must include delay to give time for the pin to change
    notRunning = true;
    pinMode(MISO, INPUT);
    //Serial.println("Slave Disabled.");
  }
}

  void mc(char inByte){
    //Motor Control
    switch (inByte) {

    //______________Motor 1______________
    case '1': // Motor 1 Forward
    analogWrite(speedPinA, 255); //Sets speed variable via PWM 
    digitalWrite(dir1PinA, LOW);
    digitalWrite(dir2PinA, HIGH);
    Serial.println("Motor 1 Forward"); // Prints out “Motor 1 Forward” on the serial monitor
    Serial.println("   "); // Creates a blank line printed on the serial monitor
    break;

    case '2': // Motor 1 Stop (Freespin)
    analogWrite(speedPinA, 0);
    digitalWrite(dir1PinA, LOW);
    digitalWrite(dir2PinA, HIGH);
    Serial.println("Motor 1 Stop");
    Serial.println("   ");
    break;

    case '3': // Motor 1 Reverse
    analogWrite(speedPinA, 255);
    digitalWrite(dir1PinA, HIGH);
    digitalWrite(dir2PinA, LOW);
    Serial.println("Motor 1 Reverse");
    Serial.println("   ");
    break;

    //______________Motor 2______________
    case '4': // Motor 2 Forward
    analogWrite(speedPinB, 255);
    digitalWrite(dir1PinB, LOW);
    digitalWrite(dir2PinB, HIGH);
    Serial.println("Motor 2 Forward");
    Serial.println("   ");
    break;

    case '5': // Motor 1 Stop (Freespin)
    analogWrite(speedPinB, 0);
    digitalWrite(dir1PinB, LOW);
    digitalWrite(dir2PinB, HIGH);
    Serial.println("Motor 2 Stop");
    Serial.println("   ");
    break;

    case '6': // Motor 2 Reverse
    analogWrite(speedPinB, 255);
    digitalWrite(dir1PinB, HIGH);
    digitalWrite(dir2PinB, LOW);
    Serial.println("Motor 2 Reverse");
    Serial.println("   ");
    break;

    case 'U': //Motor 1 & 2 forward
    analogWrite(speedPinA, speed); //Sets speed variable via PWM 
    analogWrite(speedPinB, speed);
    digitalWrite(dir1PinA, LOW);
    digitalWrite(dir1PinB, LOW);
    digitalWrite(dir2PinA, HIGH);
    digitalWrite(dir2PinB, HIGH);
    Serial.println("Motor 1 Forward"); // Prints out “Motor 1 Forward” on the serial monitor
    Serial.println("   "); // Creates a blank line printed on the serial monitor   
    Serial.println("Motor 2 Forward");
    Serial.println("   ");
    break;

      default:
      // turn all the connections off if an unmapped key is pressed:
      for (int thisPin = 2; thisPin < 11; thisPin++) {
      digitalWrite(thisPin, LOW);
      }
    }
  }
    
