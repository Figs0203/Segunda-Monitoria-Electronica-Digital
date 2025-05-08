// Librerías
#include "UbidotsEsp32Mqtt.h" // Requiere PubSubClient

// Definición de pines
#define LDR_PIN 34           // Pin ADC para el sensor de luz (LDR) — debe ser válido en ESP32
#define LED_ROJO 27          // Pin para el LED rojo
#define LED_AMARILLO 25      // Pin para el LED amarillo
#define LED_VERDE 32         // Pin para el LED verde

// Constantes de conexión y Ubidots
const char* UBIDOTS_TOKEN = "(Token Ubidots)"; // Token Ubidots
const char* UBIDOTS_DEVICE_LABEL = "io";  // Nombre del dispositivo
const char* UBIDOTS_VARIABLE_LABEL = "ldr_luz";  // Variable para la luz
const char* WIFI_SSID = "Red IoT";               // Nombre red Wi-Fi
const char* WIFI_PASS = "012345678";             // Contraseña Wi-Fi
const unsigned long T_SEND = 1000;               // Intervalo de envío (ms)

// Variables
float luz = 0.0;
Ubidots ubidots(UBIDOTS_TOKEN);

// Variables de tiempo
unsigned long tact = 0;
unsigned long tini = 0;
unsigned long trel = 0;

// Callback MQTT (opcional)
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Mensaje recibido [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void setup() {
  // Comunicación
  Serial.begin(115200);
  ubidots.connectToWifi(WIFI_SSID, WIFI_PASS);
  ubidots.setCallback(callback);
  ubidots.setup();
  ubidots.reconnect();

  // Configuración de pines de salida
  pinMode(LED_ROJO, OUTPUT);
  pinMode(LED_AMARILLO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);

  tini = millis();
}

void loop() {
  tact = millis();

  if (!ubidots.connected()) {
    ubidots.reconnect();
  }

  trel = tact - tini;

  if (trel >= T_SEND) {
    // Leer LDR (convertir a %)
    luz = analogRead(LDR_PIN) * 100.0 / 4095.0;

    Serial.println("Nivel de Luz (%): " + String(luz));

    // Control de LEDs
    if (luz <= 30) {
      digitalWrite(LED_ROJO, HIGH);
      digitalWrite(LED_AMARILLO, LOW);
      digitalWrite(LED_VERDE, LOW);
    } else if (luz > 30 && luz <= 60) {
      digitalWrite(LED_ROJO, LOW);
      digitalWrite(LED_AMARILLO, HIGH);
      digitalWrite(LED_VERDE, LOW);
    } else {
      digitalWrite(LED_ROJO, LOW);
      digitalWrite(LED_AMARILLO, LOW);
      digitalWrite(LED_VERDE, HIGH);
    }

    // Enviar variables a Ubidots
    ubidots.add("ldr_luz", luz);
    ubidots.add("led_rojo", digitalRead(LED_ROJO));
    ubidots.add("led_amarillo", digitalRead(LED_AMARILLO));
    ubidots.add("led_verde", digitalRead(LED_VERDE));

    ubidots.publish(UBIDOTS_DEVICE_LABEL);

    tini = millis(); // Reiniciar tiempo
  }

  ubidots.loop(); // Mantener conexión activa
}
