#include <SPI.h>

bool notRunning = true; // prevent code from running twice

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
}

// main loop - wait for flag set in interrupt routine
void loop (void)
{
  if(notRunning && !digitalRead(SS)) {
    notRunning = false;
    pinMode(MISO, OUTPUT);
    //Serial.println("Slave Enabled.");
    byte x = SPI.transfer(255); // 255 tells spi to recive data
    Serial.println((char) x);
  } else {
    delay(20); // must include delay to give time for the pin to change
    notRunning = true;
    pinMode(MISO, INPUT);
    //Serial.println("Slave Disabled.");
  }
}
