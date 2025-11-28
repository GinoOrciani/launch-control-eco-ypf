#include <Arduino.h>
#include "PID_Servo.h"

float leerRPMMotor() {
  static float rpm = 1200;
  rpm += 50;
  if (rpm > 3000) rpm = 1200;
  return rpm;
}

float leerRPMRueda() {
  static float rpm = 1100;
  rpm += 40;
  if (rpm > 2500) rpm = 1100;
  return rpm;
}

float leerAcelerador() {
  return 0.5f; // 50% de acelerador
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Launch Control Test");
  launchControl_init();
}

void loop() {
  launchControl_update(leerRPMMotor(), leerRPMRueda(), leerAcelerador());
  delay(50);
}

