//GPS
#include <SoftwareSerial.h>
#include <TinyGPS.h>

//Accelerometer // USES PINS 20(SDA) 21(SCL) 2(OUTPUT)
#include <Wire.h>
const int MPU_addr=0x68;  // I2C address of the MPU-6050
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

//GPS
#define RXPIN 17
#define TXPIN 16
//Set this value equal to the baud rate of your GPS
#define GPSBAUD 4800

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

//GPS
// Create an instance of the TinyGPS object
TinyGPS gps;
// Initialize the NewSoftSerial library to the pins you defined above
SoftwareSerial uart_gps(RXPIN, TXPIN);

// This is where you declare prototypes for the functions that will be 
// using the TinyGPS library.
void getgps(TinyGPS &gps);

void setup() {

  //GPS
  //Sets baud rate of your GPS
  uart_gps.begin(GPSBAUD);
  
  Serial.println("");
  Serial.println("GPS Shield QuickStart Example Sketch v12");
  Serial.println("       ...waiting for lock...           ");
  Serial.println("");
  
  //Bluetooth
  pinMode(13, OUTPUT);  //Sets digital pin 13 as output pin
  
  //Accelerometer
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);

//Serial Monitor
  Serial.begin(9600);

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
}
 
void loop() {  

  //GPS
    while(uart_gps.available())     // While there is data on the RX pin...
  {
      int c = uart_gps.read();    // load the data into a variable...
      if(gps.encode(c))      // if there is a new valid sentence...
      {
        getgps(gps);         // then grab the data.
      }
  }

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

//GPS
// The getgps function will get and print the values we want.
void getgps(TinyGPS &gps)
{
  // To get all of the data into varialbes that you can use in your code, 
  // all you need to do is define variables and query the object for the 
  // data. To see the complete list of functions see keywords.txt file in 
  // the TinyGPS and NewSoftSerial libs.
  
  // Define the variables that will be used
  float latitude, longitude;
  // Then call this function
  gps.f_get_position(&latitude, &longitude);
  // You can now print variables latitude and longitude
  Serial.print("Lat/Long: "); 
  Serial.print(latitude,5); 
  Serial.print(", "); 
  Serial.println(longitude,5);
  
  // Same goes for date and time
  int year;
  byte month, day, hour, minute, second, hundredths;
  gps.crack_datetime(&year,&month,&day,&hour,&minute,&second,&hundredths);
  // Print data and time
  Serial.print("Date: "); Serial.print(month, DEC); Serial.print("/"); 
  Serial.print(day, DEC); Serial.print("/"); Serial.print(year);
  Serial.print("  Time: "); Serial.print(hour, DEC); Serial.print(":"); 
  Serial.print(minute, DEC); Serial.print(":"); Serial.print(second, DEC); 
  Serial.print("."); Serial.println(hundredths, DEC);
  //Since month, day, hour, minute, second, and hundr
  
  // Here you can print the altitude and course values directly since 
  // there is only one value for the function
  Serial.print("Altitude (meters): "); Serial.println(gps.f_altitude());  
  // Same goes for course
  Serial.print("Course (degrees): "); Serial.println(gps.f_course()); 
  // And same goes for speed
  Serial.print("Speed(kmph): "); Serial.println(gps.f_speed_kmph());
  Serial.println();
  
  // Here you can print statistics on the sentences.
  unsigned long chars;
  unsigned short sentences, failed_checksum;
  gps.stats(&chars, &sentences, &failed_checksum);
  //Serial.print("Failed Checksums: ");Serial.print(failed_checksum);
  //Serial.println(); Serial.println();
}
