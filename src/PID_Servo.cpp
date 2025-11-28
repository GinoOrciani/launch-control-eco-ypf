#include "PID_Servo.h"

// Objeto global que maneja el ESC
Servo escDrive;

// --------------------- Parámetros de control ---------------------

// Slip objetivo (por ejemplo 5% de deslizamiento)
static const float SLIP_TARGET = 0.05f;

// Constantes del PID sobre slip (ajustar en pruebas reales)
static float gainP = 2.5f;
static float gainI = 0.25f;
static float gainD = 0.05f;

// Estado interno del PID
static float slipErrorPrev   = 0.0f;
static float slipErrorSum    = 0.0f;

// Límites de salida al ESC (en microsegundos)
static const int ESC_MIN_US  = 1000;
static const int ESC_MAX_US  = 2000;

// Tiempo de muestreo
static const uint32_t CONTROL_PERIOD_MS = 50;   // 50 ms
static uint32_t lastControlTime = 0;


// --- Funciones internas ---

// Calcula slip a partir de las RPM del motor y de la rueda
static float calcularSlip(float rpmMotor, float rpmRueda)
{
    if (rpmMotor < 10.0f) {
        return 0.0f;
    }

    float slip = (rpmMotor - rpmRueda) / rpmMotor;

    if (slip < 0.0f) slip = 0.0f;
    if (slip > 1.0f) slip = 1.0f;

    return slip;
}

// Convierte un mando normalizado (0–1) a microsegundos para el ESC
static int mandoToUs(float mando)
{
    if (mando < 0.0f) mando = 0.0f;
    if (mando > 1.0f) mando = 1.0f;

    float span = (float)(ESC_MAX_US - ESC_MIN_US);
    return ESC_MIN_US + (int)(mando * span);
}


// --------------------- API pública ---------------------

void launchControl_init()
{
    escDrive.setPeriodHertz(50);               // 50 Hz típico de servo/ESC
    escDrive.attach(ESC_PIN, ESC_MIN_US, ESC_MAX_US);
    escDrive.writeMicroseconds(ESC_MIN_US);    // arrancamos al mínimo

    lastControlTime = millis();
    slipErrorPrev   = 0.0f;
    slipErrorSum    = 0.0f;
}

void launchControl_update(float rpmMotor, float rpmRueda, float mandoPiloto)
{
    uint32_t now = millis();
    uint32_t elapsed = now - lastControlTime;

    // Control cada CONTROL_PERIOD_MS
    if (elapsed < CONTROL_PERIOD_MS) {
        return;
    }
    lastControlTime = now;
    float dt = (float)elapsed / 1000.0f;

    // Normalizar entrada del piloto
    if (mandoPiloto < 0.0f) mandoPiloto = 0.0f;
    if (mandoPiloto > 1.0f) mandoPiloto = 1.0f;

    // 1) Slip actual
    float slipActual = calcularSlip(rpmMotor, rpmRueda);

    // 2) PID sobre slip
    float e = SLIP_TARGET - slipActual;
    slipErrorSum += e * dt;
    float d = (dt > 0.0f) ? (e - slipErrorPrev) / dt : 0.0f;
    slipErrorPrev = e;

    float ajuste = gainP * e + gainI * slipErrorSum + gainD * d;

    // 3) Mando final = mando piloto + corrección LC
    float mandoFinal = mandoPiloto + ajuste;

    if (mandoFinal < 0.0f) mandoFinal = 0.0f;
    if (mandoFinal > 1.0f) mandoFinal = 1.0f;

    int us = mandoToUs(mandoFinal);
    escDrive.writeMicroseconds(us);

    // Debug
    Serial.print("[LC] Motor RPM: ");
    Serial.print(rpmMotor);
    Serial.print(" | Rueda RPM: ");
    Serial.print(rpmRueda);
    Serial.print(" | Slip: ");
    Serial.print(slipActual * 100.0f);
    Serial.print("% | MandoPiloto: ");
    Serial.print(mandoPiloto);
    Serial.print(" | MandoFinal: ");
    Serial.print(mandoFinal);
    Serial.print(" | ESC(us): ");
    Serial.println(us);
}

void launchControl_test()
{
    escDrive.writeMicroseconds(ESC_MIN_US);
    delay(1000);

    escDrive.writeMicroseconds((ESC_MIN_US + ESC_MAX_US) / 2);
    delay(1000);

    escDrive.writeMicroseconds(ESC_MAX_US);
    delay(1000);

    escDrive.writeMicroseconds(ESC_MIN_US);
}
