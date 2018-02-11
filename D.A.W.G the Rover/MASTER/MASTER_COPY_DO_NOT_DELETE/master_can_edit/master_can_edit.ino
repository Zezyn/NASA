#include <SPI.h>


void setup (void)
{
  Serial.begin(115200);
  pinMode(SS, OUTPUT); //Slave Select 1
  pinMode(9, OUTPUT); //Slave Select 2
  SPI.begin();
  digitalWrite(SS, HIGH);
  digitalWrite(9, HIGH);

}  // end of setup

int done = 1;
void loop (void)
{
  //Slave 1
  if (done <= 0) return; // just run this `done` times then stop
  // enable Slave Select by setting to low
  digitalWrite(SS, LOW);
  SPI.transfer('U');
  delay(20); // important need time to transfer
  digitalWrite(SS, HIGH);
  //done--;
  //delay (1000);  // 1 seconds delay not need this maybe???
  SPI.endTransaction();
  
  delay(20);

  SPI.begin();
  //Slave 2
  //if (done <= 0) return; // just run this `done` times then stop
  // enable Slave Select by setting to low
  digitalWrite(9, LOW);
  SPI.transfer('Z');
  delay(20); // important need time to transfer
  digitalWrite(9, HIGH);
  done--;  
  SPI.endTransaction();
  
  
}  // end of loop


