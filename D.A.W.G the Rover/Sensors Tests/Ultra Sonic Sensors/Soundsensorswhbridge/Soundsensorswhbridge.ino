#include "DualMC33926MotorShield.h"
#include <NewPing.h>

DualMC33926MotorShield md;
int loopme = 1;
int control = 250;

/*
NewPing sen1(A3, A4, 1000);
NewPing sens2(5, 6, 1000);

int distance;
*/

void stopIfFault()
{
  if (md.getFault())
  {
    //Serial.println("fault");
    while(1);
  }
}

void setup()
{
  //Serial.begin(115200);
  //Serial.println("Dual MC33926 Motor Shield");
  md.init();
  Serial.begin(9600);

}

void loop() {
  while (loopme == 1) //for (int i = 0; i <= 1000; i++)
  {
    /*
 //create function
  Serial.print("Sensors 1 ");
  Serial.println(sen1.ping_in());
  distance = sen1.ping_in();
  delay(500);
  Serial.print("Sensors 2 ");
  Serial.println(sens2.ping_in());
  */
//create function  
    md.setM1Speed(control); //md.setM1Speed(i);
    delay(50);
    md.setM2Speed(control);
    Serial.print(".");
    stopIfFault();
    if (abs(250)%200 == 100)
    {
      Serial.print("M1 current: ");
      Serial.println(md.getM1CurrentMilliamps());
    }
    delay(2);
/*    
    if(distance <= 12) {
      for(int i=0;i<5;i++) { 
        if(control == 0) 
             { break; } 
        else { control = (control - 5); delay(100); } //Serial.print("<12"); }
      }
    }  
    else if (distance >= 13) { control = 250; } //Serial.print(">12"); }
    }*/
  }
  }

