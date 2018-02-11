#include <SPI.h>

void setup (void)
{
  Serial.begin(115200);

  pinMode(SS, OUTPUT);
  pinMode(PB0, OUTPUT);
  //(SPIuno1, HIGH);  // ensure SS stays high for now
  //digitalWrite(SPImega, HIGH);  // ensure SS stays high for now

  // Put SCK, MOSI, SS pins into output mode
  // also put SCK, MOSI into LOW state, and SS into HIGH state.
  // Then put SPI hardware into Master mode and turn SPI on
  //SPI.begin ();
  //SPI.beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE0));
  SPI.begin();


  // Slow down the master a bit
    //SPI.setClockDivider(SPI_CLOCK_DIV2);

}  // end of setup

bool done = false;
void loop (void)
{
  if (done) return;
  // enable Slave Select
  digitalWrite(SS, LOW);    // SS is pin 7
    delay(20);

  SPI.transfer(5);
  delay(200);
  //byte x = SPI.transfer(255);
  //Serial.println(x);
  // disable Slave Select
  digitalWrite(SS, HIGH);
done = true;
  delay (1000);  // 1 seconds delay
}  // end of loop


