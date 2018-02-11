#include <DBH1.h>

#define ENA 6
#define ENB 7
#define IN1A 8 //(Input for motor A - needs to be PWM pin)
#define IN1B 10 // (Input for motor B - needs to be PWM pin)
#define IN2A 9  // (Input for motor A - needs to be PWM pin)
#define IN2B 11 // (Input for motor B - needs to be PWM pin)
#define CTA A0 // Analog Pin 0 (Optional) Current Sense
#define CTB A1 // Analog Pin 1 (Optional) Current Sense

DBH1 motor;

void setup() {
  // put your setup code here, to run once:
pinMode(ENA, OUTPUT);
pinMode(ENB, OUTPUT);
pinMode(IN1A, OUTPUT);
pinMode(IN1B, OUTPUT);
pinMode(IN2A, OUTPUT);
pinMode(IN2B, OUTPUT);
pinMode(CTA, INPUT);
pinMode(CTB, INPUT);

motor.init(IN1A, IN1B, IN2A, IN2B, ENA, ENB, CTA, CTB);
motor.EnableBoth();
}

void loop() {
  // put your main code here, to run repeatedly:
for( int s = 0; s < 245; s += 5){
  motor.ForwardA(s);
  motor.ReverseB(s);
  delay(50);
}
for( int s = 0; s < 245; s += 5){
  motor.ForwardB(s);
  motor.ReverseA(s);
  delay(50);
}
}

