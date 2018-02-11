#include <NewPing.h>

NewPing sens1(2, 3, 200);
NewPing sens2(4, 5, 200);
NewPing sens3(6, 7, 200);
NewPing sens4(8, 9, 200);

void setup() {
  Serial.begin(9600);
  Serial.println("Ping Sensors on");
}

void loop() {
  front();  
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
