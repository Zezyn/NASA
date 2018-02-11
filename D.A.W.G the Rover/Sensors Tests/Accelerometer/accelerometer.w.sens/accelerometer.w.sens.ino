
//GPS
/*
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

// Choose two Arduino pins to use for software serial
// The GPS Shield uses D2 and D3 by default when in DLINE mode
int RXPin = 1;
int TXPin = 0;

// The Skytaq EM-506 GPS module included in the GPS Shield Kit
// uses 4800 baud by default
int GPSBaud = 4800;

// Create a TinyGPS++ object called "gps"
TinyGPSPlus gps;

// Create a software serial port called "gpsSerial"
SoftwareSerial gpsSerial(RXPin, TXPin);
*/

//Accelerometer // USES PINS 20(SDA) 21(SCL) 2(OUTPUT)
#include <Wire.h>
const int MPU_addr=0x68;  // I2C address of the MPU-6050
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

// Ultrasonic Sensor 
int trig=3; 
int echo=5;
int trig2=7;
int echo2=8;
//Ultra Sonic Sensor
int duration;        
float distance;  
float meter;       

//Bluetooth
char data = 0;            //Variable for storing received data

void setup() {

  Serial.println("Order of Operation: Serial Monitor, Bluetooth, Accelerometer, GPS, Ultra Sonic Sensors");

  //Serial Monitor
  Serial.begin(115200);
  
  //Bluetooth
  pinMode(14, OUTPUT);  //Sets digital pin 13 as output pin tx
  pinMode(15, INPUT); //rx
  
  //Accelerometer
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
/*
  // Start the software serial port at the GPS's default baud
  gpsSerial.begin(GPSBaud);

  //Ultra Sonic Sensor
  pinMode(trig, OUTPUT);
  digitalWrite(trig, LOW);
  delayMicroseconds(2); 
  pinMode(echo, INPUT);
  delay(6000);
  Serial.println("Distance:");
  //Ultra Sonic Sensor
  pinMode(trig2, OUTPUT);
  digitalWrite(trig2, LOW);
  delayMicroseconds(2); 
  pinMode(echo2, INPUT);
  delay(6000);
  Serial.println("Distance:");
*/
}
 
void loop() {  
/*
  //GPS
    // This sketch displays information every time a new sentence is correctly encoded.
  while (gpsSerial.available() > 0)
    if (gps.encode(gpsSerial.read()))
      displayInfo();

  // If 5000 milliseconds pass and there are no characters coming in
  // over the software serial port, show a "No GPS detected" error
  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected"));
    while(true);
  }
*/
  //Ultra Sonic Sensor
  digitalWrite(trig, HIGH);    
  delayMicroseconds(10);               
  digitalWrite(trig, LOW);    
 
  duration = pulseIn(echo, HIGH); 
 
  if(duration>=38000){
      Serial.print("Out range");  
      } 
 
  else{
      distance = duration/58;   
      Serial.print(distance);    
      Serial.print("cm-left"); 
      meter=distance/100;
      Serial.print("\t");
      Serial.print(meter); 
      Serial.println("m-left");
      } 
  delay(1000);

  //Ultra Sonic Sensor
  digitalWrite(trig2, HIGH);    
  delayMicroseconds(10);               
  digitalWrite(trig2, LOW);    
 
  duration = pulseIn(echo2, HIGH); 
 
  if(duration>=38000){
      Serial.print("Out range");  
      } 
 
  else{
      distance = duration/58;   
      Serial.print(distance);    
      Serial.print("cm-right"); 
      meter=distance/100;
      Serial.print("\t");
      Serial.print(meter); 
      Serial.println("m-right");
      } 
  delay(1000);

  //Accelerometer
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
  Serial.print("AcX = "); Serial.print(AcX);
  Serial.print(" | AcY = "); Serial.print(AcY);
  Serial.print(" | AcZ = "); Serial.print(AcZ);
  Serial.print(" | Tmp = "); Serial.print(Tmp/340.00+36.53);  //equation for temperature in degrees C from datasheet
  Serial.print(" | GyX = "); Serial.print(GyX);
  Serial.print(" | GyY = "); Serial.print(GyY);
  Serial.print(" | GyZ = "); Serial.println(GyZ);
  delay(333);

  //BlueTooth
     if(Serial.available() > 0)      // Send data only when you receive data:
   {
      data = Serial.read();        //Read the incoming data & store into data
      Serial.print(data);          //Print Value inside data in Serial monitor
      Serial.print("\n");        
      if(data == '1')              // Checks whether value of data is equal to 1
         digitalWrite(13, HIGH);   //If value is 1 then LED turns ON
      else if(data == '0')         //  Checks whether value of data is equal to 0
         digitalWrite(13, LOW);    //If value is 0 then LED turns OFF
   }
}
/*
//GPS display
void displayInfo()
{
  Serial.print(F("Location: ")); 
  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F("  Date/Time: "));
  if (gps.date.isValid())
  {
    Serial.print(gps.date.month());
    Serial.print(F("/"));
    Serial.print(gps.date.day());
    Serial.print(F("/"));
    Serial.print(gps.date.year());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F(" "));
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(gps.time.hour());
    Serial.print(F(":"));
    if (gps.time.minute() < 10) Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(F(":"));
    if (gps.time.second() < 10) Serial.print(F("0"));
    Serial.print(gps.time.second());
    Serial.print(F("."));
    if (gps.time.centisecond() < 10) Serial.print(F("0"));
    Serial.print(gps.time.centisecond());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.println();
}
*/
