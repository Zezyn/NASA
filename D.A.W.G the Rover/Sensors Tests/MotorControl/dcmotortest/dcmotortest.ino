int motorSpeed = 255;
int motorPin = 3;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(motorPin, 0);
  delay(1000);
  analogWrite(motorPin, 127);
  delay(5000);
}
