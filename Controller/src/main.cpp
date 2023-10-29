#include "common.h"
#include "schedule.cpp"
#include "thermostat.h"
#include "JSON.cpp"
#include "mqtt.h"

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

// Stores LED state
String relayState;

// Replaces placeholder with LED state value
String processor(const String& var) {
  debugln(var);
  if (var == "STATE") {
    if (digitalRead(relayPin)) {
      relayState = "ON";
    } else {
      relayState = "OFF";
    }
    debugln("Relay: " + relayState);
    return relayState;
  }
  return String();
}

void setup() {
  delay(2000);
  pinMode(relayPin, OUTPUT);

  // Start the Serial Monitor
  Serial.begin(115200);
  debugln("");
  debugln("SETUP begin!");

  // Mount the filesystem
  if (!SPIFFS.begin(true)) {
    debugln("Error: Failed to mount the filesystem.");
    return;
  }

  // Connect to Wi-Fi
  setupWiFi();

  // Print ESP32 Local IP Address
  IPAddress localIP = WiFi.localIP();
  debugln("Local IP Address: " + localIP.toString());

  // Setup MQTT
  setupMQTT();
  subscribeToTopics(); // Subscribe to the topic you want to receive messages from

  DynamicJsonDocument scheduleDoc(1024); // Adjust the size as needed
  JsonArray schedule = scheduleDoc.createNestedArray();

  // Call the function to read JSON data from SPIFFS
  readScheduleFromJson(schedule);

  debugln("SETUP end!");
}

void loop() {
  checkMQTTConnection();
  handleMQTTMessages(); // Add this line to check for incoming messages
}
