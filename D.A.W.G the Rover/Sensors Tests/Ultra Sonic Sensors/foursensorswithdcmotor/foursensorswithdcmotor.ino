
int ultraSoundSignalPins[] = {6,7,8,9}; 
/*/ Front Left,Front, Front Right, Rear Ultrasound signal pins*/
char *pingString[] = {"Front Left ","Front ", "Front Right ", "Rear "}; 
/*/just something to print to indicate direction*/

//DC Motor pin
int motorPin = 3;

void setup()
{
 Serial.begin(9600);
}

//Ping function
unsigned long ping(int index)
{
 unsigned long echo;

 pinMode(ultraSoundSignalPins[index], OUTPUT); /* Switch signalpin to output*/
 digitalWrite(ultraSoundSignalPins[index], LOW); /*/ Send low pulse*/
 delayMicroseconds(2); // Wait for 2 microseconds

 digitalWrite(ultraSoundSignalPins[index], HIGH); /*/ Send high pulse*/
 delayMicroseconds(5); // Wait for 5 microseconds
 
 digitalWrite(ultraSoundSignalPins[index], LOW); /*/ Holdoff*/
 pinMode(ultraSoundSignalPins[index], INPUT); /*/ Switch signalpin to input*/
 
 digitalWrite(ultraSoundSignalPins[index], HIGH); /*/ Turn on pullup resistor*/
 
 echo = pulseIn(ultraSoundSignalPins[index], HIGH); /*/Listen for echo*/
  return (echo / 58.138) * .39; /*/convert to CM then to inches*/
}

void loop()
{
 unsigned long ultrasoundValue;
 for(int i=0; i < 4; i++){
   ultrasoundValue = ping(i);
   Serial.print(pingString[i]);
   Serial.print(ultrasoundValue);
   Serial.print("in, ");    
   delay(50);
 }
 Serial.println();
 delay(50);
}

void motor() {
  //DC Motor Control
  analogWrite(motorPin, 0);
  //delay(1000);
  analogWrite(motorPin, 127);
  //delay(5000);
} 

