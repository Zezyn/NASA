#include <SPI.h>

char buf [100];
volatile byte pos;
volatile bool process_it;


char data = 0;
volatile uint8_t decStr[4];  //Up to 3 digits plus a newline character 

void setup (void)
{
  Serial.begin (115200);   // debugging

  // turn on SPI in slave mode
  SPCR |= bit (SPE);

  // have to send on master in, *slave out*
  pinMode (MISO, OUTPUT);

  // get ready for an interrupt
  pos = 0;   // buffer empty
  process_it = false;

  // now turn on interrupts
  SPI.attachInterrupt();

}  // end of setup
volatile bool isRunning = false;


// SPI interrupt routine
ISR (SPI_STC_vect)
{
  isRunning = true;
  cli();
  byte c = SPDR;  // grab byte from SPI Data Register
  process_it = true;
  Serial.println("ISR");
  Serial.println(c,HEX);
  sei();
  isRunning = false;
}  // end of interrupt routine SPI_STC_vect


// main loop - wait for flag set in interrupt routine
void loop (void)
{
  if (isRunning) {
    return;
  }
    itoaByte(decStr, data);
    //Serial.print(data);
    /*
    uint8_t index = 0;
    do {
      Serial.println(data);
      index ++;
    } while (decStr[index] != 10);
  */
  
  if (process_it)
    {
    buf [pos] = 0;
    Serial.println("BUF");
    //Serial.println (buf);
    pos = 0;
    process_it = false;
    }  // end of flag set

}

//Convert 8 bit unsigned integer to ASCII character array with newline character.
//Prepended zeros are removed.
//No Libraries, Division or Modulo were harmed in this function.
void itoaByte(volatile uint8_t decStr[], uint8_t data){
  uint8_t index = 0;
  decStr[index] = '0';
  bool sig = false;
  while(data > 99){
    data -= 100;
    decStr[index] ++;   //Increment Hundreds digit
    sig = true;
  }    
  if(sig){
    index ++;   //If hundreds digit != 0 move to next cell.
    decStr[index] = '0';
  }
  while(data > 9){
    data -= 10;
    decStr[index] ++;   //Increment tens digit
    sig = true;    
  }
  if(sig){
    index ++;   //If hundreds digit != 0 or tens digit != 0 move to next cell.
  }
    decStr[index] = data + '0'; //Ones digit
    //decStr[index + 1] = 10; //newline character
}
