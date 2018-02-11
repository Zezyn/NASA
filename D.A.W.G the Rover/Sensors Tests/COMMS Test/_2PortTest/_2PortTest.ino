/*
  Software serial multple serial test

 Receives from the two software serial ports,
 sends to the hardware serial port.

 In order to listen on a software port, you call port.listen().
 When using two software serial ports, you have to switch ports
 by listen()ing on each one in turn. Pick a logical time to switch
 ports, like the end of an expected transmission, or when the
 buffer is empty. This example switches ports when there is nothing
 more to read from a port

 The circuit:
 Two devices which communicate serially are needed.
 * First serial device's TX attached to digital pin 10(RX), RX to pin 11(TX)
 * Second serial device's TX attached to digital pin 8(RX), RX to pin 9(TX)
 */
#include <Adafruit_GPS.h>
//#include <SoftwareSerial.h>

#define GPSECHO  true

// software serial #1: RX = digital pin 2, TX = digital pin 3
//SoftwareSerial BT(18, 19);

// software serial #2: RX = digital pin 4, TX = digital pin 5
//SoftwareSerial GPSinfo(16, 17);  //GPS
Adafruit_GPS GPS(&GPSinfo);

uint32_t Time = millis();
uint32_t BTtime = millis();
//int Time = 0;
void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  pinMode(13,OUTPUT);
  while (!Serial) {
   ; // wait for serial port to connect. Needed for native USB port only
  }
  
  // Start each software serial port
  BT.begin(9600);
  GPS.begin(9600);
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);   // 1 Hz update rate

}

void loop() {  // By default, the last intialized port is listening. when you want to isten on a port, explicitly select it:
  
  //BLUETOOTH
  if(millis() > (BTtime + 200)){ 
  BT.listen();  //Bluetooth Listen
  while (BT.available()) {
    
    //Serial.print("."); // while there is data coming in, read it and send to the hardware serial port:
    
    char BTByte = BT.read();
    Serial.write(BTByte); 
    Serial.println("");
    
    if(BTByte == 'X') { 
      digitalWrite(13, HIGH);
      }
    else if (BTByte == 'U') { digitalWrite(13, LOW); }
  }
  BTtime = millis();
  
  }

 
  char c = GPS.read();
  if (GPSECHO)
  if (c) Serial.print(c);

  //GPS
  if (millis() > (Time + 2000)) {  // Now listen on the second port
//    GPSinfo.listen(); //GPS Listen while there is data coming in, read it and send to the hardware serial port:

    // read data from the GPS in the 'main loop'
    //char c = GPS.read();
    // if you want to debug, this is a good time to do it!
//    if (GPSECHO)
//      if (c) Serial.print(c);
  
  
  // if a sentence is received, we can check the checksum, parse it...
  if (GPS.newNMEAreceived()) {
    // a tricky thing here is if we print the NMEA sentence, or data
    // we end up not listening and catching other sentences! 
    // so be very wary if using OUTPUT_ALLDATA and trytng to print out data
    //Serial.println(GPS.lastNMEA());   // this also sets the newNMEAreceived() flag to false
  
    if (!GPS.parse(GPS.lastNMEA()))   // this also sets the newNMEAreceived() flag to false
      return;  // we can fail to parse a sentence in which case we should just wait for another
  }
    
    Serial.print("\nTime: ");
    Serial.print(GPS.hour, DEC); Serial.print(':');
    Serial.print(GPS.minute, DEC); Serial.print(':');
    Serial.print(GPS.seconds, DEC); Serial.print('.');
    Serial.println(GPS.milliseconds);
    Serial.print("Date: ");
    Serial.print(GPS.day, DEC); Serial.print('/');
    Serial.print(GPS.month, DEC); Serial.print("/20");
    Serial.println(GPS.year, DEC);
    Serial.print("Fix: "); Serial.print((int)GPS.fix);
    Serial.print(" quality: "); Serial.println((int)GPS.fixquality); 
    
    Serial.print("Location: ");
    Serial.print(GPS.latitude, 4); Serial.print(GPS.lat);
    Serial.print(", "); 
    Serial.print(GPS.longitude, 4); Serial.println(GPS.lon);
    Serial.print("Location (in degrees, works with Google Maps): ");
    Serial.print(GPS.latitudeDegrees, 4);
    Serial.print(", "); 
    Serial.println(GPS.longitudeDegrees, 4);
      
    Serial.print("Speed (knots): "); Serial.println(GPS.speed);
    Serial.print("Angle: "); Serial.println(GPS.angle);
    Serial.print("Altitude: "); Serial.println(GPS.altitude);
    Serial.print("Satellites: "); Serial.println((int)GPS.satellites);
    Time = millis();
  }
}
