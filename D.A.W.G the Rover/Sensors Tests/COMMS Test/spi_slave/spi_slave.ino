#include <SPI.h>

//char buf [100];
//volatile byte pos;
//volatile bool process_it;


// SPI Transfer.
byte SPItransfer(byte value) {
  SPDR = value;
  while(!(SPSR & (1<<SPIF)));
  delay(10);
  return SPDR;
}

void setup (void)
{
  Serial.begin (115200);   // debugging


  // Initialize SPI pins.
  pinMode(SCK, INPUT);
  pinMode(MOSI, INPUT);
  pinMode(MISO, INPUT);
  pinMode(SS, INPUT);
  
  // Enable SPI as slave.
  SPCR = (1 << SPE);  
}  // end of setup



// main loop - wait for flag set in interrupt routine
void loop (void)
{
    //Serial.println(digitalRead(SS));
//int i = 0;
  if(!digitalRead(SS)) {
   // i = 1;
    pinMode(MISO, OUTPUT);
          Serial.println("Slave Enabled.");

    byte x = SPItransfer(255);
    Serial.println(x);
  } else {
     //   i = 0;
      pinMode(MISO, INPUT);
            Serial.println("Slave Disabled.");

//byte x = SPI.transfer(6);
  //Serial.println(x);
  }
//  if (process_it)
//    {
//    buf [pos] = 0;
//    Serial.println (buf);
//    pos = 0;
//    process_it = false;
//    }  // end of flag set

}
