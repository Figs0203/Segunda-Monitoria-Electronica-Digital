# 📡 Monitoreo de Sensor LDR y Control de LEDs con ESP32 y Ubidots

Este proyecto permite **monitorear la cantidad de luz ambiente** mediante un sensor **LDR** conectado a un **ESP32**, y controlar tres LEDs (rojo, amarillo y verde) en función del nivel de luz detectado. Además, los datos se envían a la plataforma **Ubidots** para visualización remota.

## 🔧 Requisitos

### 🛠️ Hardware
- ESP32
- 1 Sensor LDR (fotoresistencia)
- 1 Resistencia de 6,2kΩ (pull-down para el LDR)
- 3 LEDs (Rojo, Amarillo, Verde)
- 3 resistencias de 330Ω (una para cada LED)
- Protoboard y cables de conexión
- Fuente de alimentación o conexión USB

### 🧠 Conexiones
| Componente | Pin ESP32 |
|------------|-----------|
| LDR        | 34 (ADC)  |
| LED Rojo   | 27        |
| LED Amarillo | 25      |
| LED Verde  | 32        |

**Nota:** Conecta una resistencia de 6,2kΩ en paralelo al LDR hacia GND para que funcione correctamente como divisor de voltaje.

### 💻 Software
- Arduino IDE (versión 1.8 o superior)
- Librerías necesarias:
  - `UbidotsEsp32Mqtt` ([GitHub](https://github.com/ubidots/esp32-mqtt/archive/refs/heads/main.zip))
  - `PubSubClient`     ([GitHub](https://github.com/knolleary/pubsubclient))
- Cuenta gratuita en [Ubidots](https://industrial.ubidots.com/)

## 🔌 Configuración en Ubidots

1. Crea un nuevo dispositivo llamado `io`.
2. Dentro del dispositivo, crea una **variable** llamada `sensor_luz`.
3. Copia tu **token** desde tu cuenta (sección API credentials).
4. Sustituye el valor de `UBIDOTS_TOKEN` en el código con el tuyo.

## 🚦 Lógica de los LEDs

- **Rojo:** luz menor o igual a 30%
- **Amarillo:** luz entre 31% y 60%
- **Verde:** luz mayor al 60%

Los datos de luz se envían cada 1 segundo a Ubidots y se imprimen en el monitor serial.

## 📤 Subida del código

1. Abre el archivo `.ino` en el Arduino IDE.
2. Selecciona la placa **ESP32 Dev Module**.
3. Conecta el ESP32 por USB.
4. Sube el código y abre el Monitor Serial (baud rate: 115200).

## 📈 Visualización

Una vez conectado y ejecutando el código, podrás ver el valor de luz reportado desde el dispositivo `io` en Ubidots en tiempo real. Puedes crear dashboards personalizados con widgets de tipo "gauge" o "historical graph".

---

## 👨‍💻 Autor

Agustín Figueroa  
Estudiante de Ingeniería de Sistemas - Universidad EAFIT  
Medellín, Colombia  
2025

