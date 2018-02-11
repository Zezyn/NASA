#include <SPI.h>

bool notRunning = true; // prevent code from running twice

void setup (void)
{
  Serial.begin (115200);   // debugging

  // Initialize SPI pins.
  pinMode(SCK, INPUT);
  pinMode(MOSI, INPUT);
  pinMode(MISO, OUTPUT);
  pinMode(SS, INPUT);
  
  // Enable SPI as slave.
  SPCR = (1 << SPE);  
}

// main loop - wait for flag set in interrupt routine
void loop (void)
{
  if(notRunning && !digitalRead(SS)) {
    notRunning = false;
    //Serial.println("Slave Enabled.");
    byte x = SPI.transfer(255); // 255 tells spi to recive data
    Serial.println((char) x);
        SPDR = 'P';
  } else {
    delay(20); // must include delay to give time for the pin to change
    notRunning = true;
    //Serial.println("Slave Disabled.");
  }
}
