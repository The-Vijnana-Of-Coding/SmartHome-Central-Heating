#ifndef MQTT_FUNCTIONS_H
#define MQTT_FUNCTIONS_H
#include "common.h"
#include "handleMQTT.h"

#include <WiFi.h>
#include <PubSubClient.h>

WiFiClient espClient;
PubSubClient client(espClient);

void setupWiFi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void callback(char* topic, byte* payload, unsigned int length) {
  // Handle incoming messages
  Serial.print("Received message on topic: ");
  Serial.println(topic);
  Serial.print("Message: ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  
  // Create a buffer to hold the incoming MQTT payload
  char message[length + 1];
  memcpy(message, payload, length);
  message[length] = '\0'; // Null-terminate the string
    // Add your message handling code here
    handleMQTT(topic, message);
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("Controller", mqtt_username, mqtt_password)) {
      Serial.println("Connected to MQTT broker");
    } else {
      Serial.print("Failed to connect to MQTT broker, rc=");
      Serial.println(client.state());
      delay(5000);
    }
  }
}

void checkMQTTConnection() {
  if (WiFi.status() != WL_CONNECTED) {
    // Handle Wi-Fi disconnection
    setupWiFi(); // Attempt to reconnect to Wi-Fi
  }
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}


void publishMessage(const char* topic,const char* message) {
  if (client.connected()) {
    client.publish(topic, message);
  }
}

void subscribeToTopics() 
{
    for (int i = 0; i < num_sub_topics; i++) 
    {
        client.subscribe(sub_topics[i]);
        debugln("Subscribing to: " + String(sub_topics[i]));
    }
}

void handleMQTTMessages() {
  // This function should be called in the loop() to process incoming MQTT messages
  client.loop();
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
