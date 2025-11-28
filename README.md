# launch-control-eco-ypf
![Uploading image.png…]()

# 🚀 Proyecto Launch Control – Desafío ECO YPF

Sistema de control electrónico para mejorar la salida inicial del kart eléctrico del **Proyecto YPF**.  
Implementa una estrategia de **Launch Control / Control de Tracción** sobre un motor brushless controlado por un ESC.

🧩 Se utiliza una placa **ESP32** para el procesamiento en tiempo real.

---

## 🏁 ¿Qué es el Launch Control?

Es una función que:
- Controla el deslizamiento de la rueda al arrancar
- Mantiene el **torque máximo** con **máxima adherencia**
- Logra una salida más rápida y estable en carrera

Cuando el motor entrega demasiada fuerza al inicio:
❌ La rueda patina  
❌ Se pierde aceleración  
❌ Riesgo de pérdida de control

El Launch Control **mantiene el motor justo al límite del agarre**.

---

## 🔧 Método de Control

### 🔹 Sensores utilizados

| Variable medida | Sensor | Uso |
|---|---|---|
| RPM motor | Sensor Hall integrado | Evaluar torque aplicado |
| RPM rueda | Encoder magnético/óptico | Detectar patinamiento |
| Acelerador del piloto | Potenciómetro | Entrada de demanda |

---

### 🔹 Cálculo del *Slip* (deslizamiento)

Permite saber si la rueda patina:

```cpp
slip = (RPM_motor - RPM_rueda) / RPM_motor;
