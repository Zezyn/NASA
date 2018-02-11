//SPI
#include <SPI.h>

//Ping Sensor Library
#include <NewPing.h>

//SPI
int done = 1;

// (trigger, echo, maxd)istance
NewPing sens1(2, 3, 200);
NewPing sens2(4, 5, 200);
NewPing sens3(6, 7, 200);
NewPing sens4(8, 9, 200);

void setup() {
  Serial.begin(9600);
  Serial.println("Ping Sensors on");

//SPI
  pinMode(SS, OUTPUT); //Slave Select 1
  pinMode(9, OUTPUT); //Slave Select 2
  digitalWrite(SS, HIGH);
  digitalWrite(9, HIGH);
}

void loop() {

  //SPI
  //char / slave (9 = Motor Control, 10 = GPS/Bluetooth)
  sendData('U', 9);
  

  //Sensor example
  front();
  rear();  
}

void sendData(char x, int slave) {
  SPI.begin();
  if (done <= 0) return; // just run this `done` times then stop
  // enable Slave Select by setting to low
  digitalWrite(slave, LOW);
  SPI.transfer(x);
  delay(20); // important need time to transfer
  digitalWrite(slave, HIGH);
  Serial.print("Sending: ");
  Serial.println(x);
  SPI.endTransaction();
  
  delay(20);
}

void front() {
  ss1();
  delay (500);
  ss2();
}

void rear() {
  ss3();
  delay(500);
  ss4();
}

void ss1() {
  Serial.print("Sensors 1:: ");
  Serial.print(sens1.ping_in());
  Serial.println(" in.");
}

void ss2() {
  Serial.print("Sensors 2:: ");
  Serial.print(sens2.ping_in());
  Serial.println(" in.");  
}

void ss3() {
  Serial.print("Sensors 3:: ");
  Serial.print(sens3.ping_in());
  Serial.println(" in.");  
}

void ss4() {
  Serial.print("Sensors 4:: ");
  Serial.print(sens4.ping_in());
  Serial.println(" in.");
}


