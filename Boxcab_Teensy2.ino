#include <PWMServo.h>

PWMServo BoxcabEngine;

int BoxcabEnginePosition = 90; //default servo position, 90 is neutral

void setup() {
  delay(2000); //2 second startup delay, in case voltage drops too low and we reset motor doesn't switch between neutral and fast speeds
  BoxcabEngine.attach(SERVO_PIN_A); //pin 14
  pinMode(20, INPUT_PULLUP); //forward pin
  pinMode(19, INPUT_PULLUP); //reverse pin
  pinMode(A4, INPUT); //throttle
}

void loop() {
  BoxcabEngine.write(BoxcabEnginePosition); //send neutral at start
  if(digitalRead(20) == 0) { //if forward
    BoxcabEnginePosition = map(analogRead(A4), 0, 1024, 90, 180); //map throttle 0-1024 to motor 90-180 (90 = neutral, 180 = full forward)
  }
  else if(digitalRead(19) == 0) { //if reverse
    BoxcabEnginePosition = map(analogRead(A4), 0, 1024, 90, 0); //map throttle 0-1024 to motor 90-0 (0 = full reverse)
  }
  else { //if neither, send neutral value
    BoxcabEnginePosition = 90;
  }
  delay(15); //motor controller can update every 10ms
}
