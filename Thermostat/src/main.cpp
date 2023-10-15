#include <OneWire.h>
#include <DallasTemperature.h>
#include "common.h"
#include <PubSubClient.h>
#include <WiFi.h>

WiFiClient espClient;
PubSubClient client;

// Setup a oneWire instance to communicate with any OneWire devices
OneWire tempSensorOneWire(tempSensorPin);

// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature tempSensor(&tempSensorOneWire);

void setup_wifi() {
  delay(10);
  Serial.println("Connecting to WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void mqtt_callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  Serial.print("Message: ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void mqtt_reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ThermostatClient1", mqttUser, mqttPassword)) {
      Serial.println("connected");
      client.subscribe(mqttTopic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void mqtt_loop() {
  if (!client.connected()) {
    mqtt_reconnect();
  }
  client.loop();
}

void setup_mqtt() {
  client.setServer(mqttServer, mqttPort);
  client.setCallback(mqtt_callback);
}

void setup() {
  debugln("SETUP begin!");
  
  debugln("Start Serial Monitor");
  // Start the Serial Monitor
  Serial.begin(115200);

  // ## Temp Sensor Setup ## //
  debugln("Start Temp Sensor");
  tempSensor.begin();

  debugln("Start WiFi");
  setup_wifi();
  debugln("Start MQTT");
  setup_mqtt();

  debugln("SETUP end!");
}

void loop() {
  debugln("Temp Sensor");
  tempSensor.requestTemperatures(); 
  float temperatureC = tempSensor.getTempCByIndex(0);
  debug(temperatureC);
  debugln("°C");
  delay(5000);
}