# Carpeta hardware – Launch Control

Este directorio contiene toda la información de **hardware** utilizada en el proyecto Launch Control del Proyecto YPF.

## Contenido

- `BOM_launch_control.md`: lista de materiales (componentes electrónicos y sensores).
- `esquematico_launch_control.png`: diagrama de conexión entre ESP32, sensores y ESC.
- `notas_conexion.md` (opcional): descripción de pines y señales.

## Descripción general del hardware

El sistema está compuesto por:

- **ESP32 DevKit** como unidad de control.
- **Sensor Hall de motor** para medir RPM del motor.
- **Encoder en la rueda** para medir RPM de rueda.
- **Acelerador electrónico** como entrada del piloto.
- **ESC brushless 24 V** para controlar el motor.
- **Motor brushless 500 W** como actuador principal.
- **Pack de baterías 24 V** según reglamento ECO YPF.

El ESP32 lee los sensores, calcula el *slip* y genera una señal PWM hacia el ESC para regular la potencia del motor.

