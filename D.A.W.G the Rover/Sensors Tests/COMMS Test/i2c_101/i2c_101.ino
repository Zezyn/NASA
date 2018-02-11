#include <Wire.h>

void setup() {
  // put your setup code here, to run once:
Wire.begin();
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.println('.');
  Wire.requestFrom(2, 1); //Request 1 byte from address 2
  if(Wire.available()){
  char Mega = Wire.read(); // receive a byte as character and store in variable
  Serial.println(Mega);         // print the character
  Serial.println("DATA RECIEVED!!!!!!!!!!!!!!!!!!!!!!!!!!");
  Wire.flush();
  }
  else{Serial.println(" NA "); }
  
  
}
