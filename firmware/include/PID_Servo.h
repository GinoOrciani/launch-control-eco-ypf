#ifndef PID_SERVO_H
#define PID_SERVO_H

#include <Arduino.h>
#include <ESP32Servo.h>

// Pin donde está conectada la señal del ESC
#define ESC_PIN 27

// Objeto Servo que controla el ESC (lo definimos en el .cpp)
extern Servo escDrive;

// Inicializa el Launch Control (ESC y variables internas)
void launchControl_init();

// Actualiza el Launch Control.
//  - rpmMotor: RPM del motor
//  - rpmRueda: RPM de la rueda
//  - mandoPiloto: acelerador normalizado 0.0–1.0
void launchControl_update(float rpmMotor, float rpmRueda, float mandoPiloto);

// Rutina de prueba del ESC
void launchControl_test();

#endif // PID_SERVO_H

