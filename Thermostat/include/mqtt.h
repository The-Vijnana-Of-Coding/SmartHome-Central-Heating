#ifndef MQTT_FUNCTIONS_H
#define MQTT_FUNCTIONS_H
#include "common.h"
#include <WiFi.h>
#include <PubSubClient.h>



WiFiClient espClient;
PubSubClient client(espClient);

void callback(char* topic, byte* payload, unsigned int length) {
  // Handle incoming messages
  Serial.print("Received message on topic: ");
  Serial.println(topic);
  Serial.print("Message: ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Add your message handling code here
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP32Thermostat", mqtt_username, mqtt_password)) {
      Serial.println("Connected to MQTT broker");
    } else {
      Serial.print("Failed to connect to MQTT broker, rc=");
      Serial.println(client.state());
      delay(5000);
    }
  }
}

void checkMQTTConnection() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}

void publishMessage(const char* message) {
  if (client.connected()) {
    client.publish(publish_temp, message);
  }
}

void subscribeToTopic(const char* topic) {
  client.subscribe(topic);
}

void handleMQTTMessages() {
  // This function should be called in the loop() to process incoming MQTT messages
  client.loop();
}

void setupWiFi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void setupMQTT() {
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  if (client.connect("ESP32Client", mqtt_username, mqtt_password)) {
    Serial.println("Connected to MQTT broker");
  } else {
    Serial.print("Failed to connect to MQTT broker, rc=");
    Serial.println(client.state());
  }
}

#endif
