#include <Wire.h>

bool calcdone = false;
char data = 'b';
char lastdata;


void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
 Wire.begin(2);
 Wire.onRequest(requestEvent);
}

void loop() {
  //Serial.println('.');
  docalc();
  requestEvent();
}

void requestEvent()
  {
  if(calcdone == true && data != lastdata) {
    Wire.write(data); // respond with message of 1 byte
    calcdone = false;
    lastdata = data;
    Serial.println("SENDING");
  }
  
  }

  void docalc() {
    calcdone = true;
    
  }

