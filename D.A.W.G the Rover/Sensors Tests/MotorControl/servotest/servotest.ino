#define DC_MOTOR_PIN 3

void setup() {
  /* Initialize DC motor control pin as digital output */
  pinMode( DC_MOTOR_PIN, OUTPUT );
}

void loop() {
  /* Gradually increase motor speed to full speed */
  for( int i = 0; i < 255; i+5 )
    analogWrite( DC_MOTOR_PIN, i );
  while( 1 );
}



