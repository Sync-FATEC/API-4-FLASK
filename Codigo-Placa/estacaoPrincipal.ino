#include <WiFi.h>
#include <PubSubClient.h>
#include "DHTesp.h"
#include <ArduinoJson.h>
#include <time.h>

// ======= WI‑FI ==========
const char* ssid = "FAMILIA PEREIRA";
const char* password = "lupe2004";

// ======= MQTT ==========
const char* mqtt_server = "test.mosquitto.org";
const int mqtt_port = 1883;
const char* topic = "fatec/api/sync/";

// ======= DHT11 with DHTesp =========
#define DHTPIN 14
DHTesp dht;

// ======= INTERVALO ======
const int intervalo = 5;  // em segundos
time_t lastSent = 0;

// ========= VARIÁVEIS GLOBAIS =========
WiFiClient espClient;
PubSubClient client(espClient);
String uid;
String clientId;

// Forward declarations
void wifiMqttTask(void* pvParameters);
void sensorTask(void* pvParameters);

// ============================
// FUNÇÕES DE CONEXÃO
// ============================
void setup_wifi() {
  Serial.println("===== Conectando ao WiFi =====");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    vTaskDelay(500 / portTICK_PERIOD_MS);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("WiFi conectado. IP: ");
  Serial.println(WiFi.localIP());

  uid = WiFi.macAddress();
  uid.replace(":", "");
  clientId = "esp32-" + uid;
  Serial.print("Client ID: ");
  Serial.println(clientId);
}

void reconnect_mqtt() {
  Serial.println("===== Reconectando ao MQTT =====");
  while (!client.connected()) {
    Serial.print("Tentando MQTT (");
    Serial.print(clientId);
    Serial.print(")... ");
    if (client.connect(clientId.c_str())) {
      Serial.println("OK!");
    } else {
      Serial.print("Falhou, state=");
      Serial.print(client.state());
      Serial.println(" => aguardando 5s");
      vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
  }
}

void setup_time() {
  Serial.print("Sincronizando tempo NTP");
  configTime(0, 0, "pool.ntp.org", "time.nist.gov");
  time_t now = time(nullptr);
  while (now < 8 * 3600 * 2) {
    vTaskDelay(500 / portTICK_PERIOD_MS);
    Serial.print(".");
    now = time(nullptr);
  }
  Serial.println(" OK");
}

// ============================
// setup()
// ============================
void setup() {
  Serial.begin(115200);
  dht.setup(DHTPIN, DHTesp::DHT11);
  randomSeed(analogRead(0));

  setup_wifi();
  setup_time();

  client.setServer(mqtt_server, mqtt_port);
  client.setBufferSize(512);

  xTaskCreatePinnedToCore(wifiMqttTask, "WifiMqtt", 4096, NULL, 1, NULL, 0);
  xTaskCreatePinnedToCore(sensorTask, "Sensor", 8192, NULL, 1, NULL, 1);
}

// ============================
// loop() (FreeRTOS)
// ============================
void loop() {
  vTaskDelete(NULL);
}

// ============================
// Task Wi‑Fi/MQTT
// ============================
void wifiMqttTask(void* pvParameters) {
  for (;;) {
    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("WiFi caiu — reconectando...");
      setup_wifi();
    }
    if (!client.connected()) {
      reconnect_mqtt();
    }
    client.loop();
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

// ============================
// Task Sensores e MQTT
// ============================
void sensorTask(void* pvParameters) {
  for (;;) {
    time_t agora = time(nullptr);
    if (agora - lastSent >= intervalo) {
      lastSent = agora;

      float h = dht.getHumidity();
      float t = dht.getTemperature();

      if (isnan(h) || isnan(t)) {
        Serial.println("Erro DHT — usando valores aleatórios");
        h = random(30, 91);   // Umidade entre 30% e 90%
        t = random(15, 36);   // Temperatura entre 15°C e 35°C
      }

      int rainfall  = random(0, 101);
      int windSpeed = random(0, 101);
      int pressure  = random(950, 1051);

      StaticJsonDocument<512> doc;
      doc["uid"]         = uid;
      doc["temperature"] = t;
      doc["humidity"]    = h;
      doc["unixtime"]    = agora;
      doc["rainfall"]    = rainfall;
      doc["windSpeed"]   = windSpeed;
      doc["pressure"]    = pressure;

      char buffer[512];
      serializeJson(doc, buffer);
      Serial.print("JSON: ");
      Serial.println(buffer);

      bool ok = client.publish(topic, buffer);
      Serial.print("Publish retornou: ");
      Serial.println(ok ? "true" : "false");
      if (!ok) client.disconnect();
    }
    vTaskDelay(200 / portTICK_PERIOD_MS);
  }
}
