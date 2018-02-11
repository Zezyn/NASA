// Ultrasonic Sensor Example
int trig=3; 
int echo=5;
int trig2=7;
int echo2=8;

int duration;        
float distance;  
float meter;       
void setup() {
  Serial.begin(9600);
  pinMode(trig, OUTPUT);
  digitalWrite(trig, LOW);
  delayMicroseconds(2); 
  pinMode(echo, INPUT);
  delay(6000);
  Serial.println("Distance:");
  
  pinMode(trig2, OUTPUT);
  digitalWrite(trig2, LOW);
  delayMicroseconds(2); 
  pinMode(echo2, INPUT);
  delay(6000);
  Serial.println("Distance:");
}
 
void loop() {  

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
}
