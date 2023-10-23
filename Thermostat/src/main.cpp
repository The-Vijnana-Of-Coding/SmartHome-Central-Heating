#include <OneWire.h>
#include <DallasTemperature.h>
#include "common.h"
#include <PubSubClient.h>
#include <WiFi.h>
#include "thermostat.cpp"
#include "mqtt.h"
#include <ArduinoJson.h>

// Setup a oneWire instance to communicate with any OneWire devices
OneWire tempSensorOneWire(tempSensorPin);

// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature tempSensor(&tempSensorOneWire);

void setup() {
  
  // Start the Serial Monitor
  Serial.begin(115200);
  debugln("SETUP begin!");
  
  debugln("Start Serial Monitor");  

  // ## Temp Sensor Setup ## //
  debugln("Start Temp Sensor");
  tempSensor.begin();

  debugln("Start WiFi");
  // Connect to Wi-Fi
	setupWiFi();
	// Print ESP32 Local IP Address
	debugln(WiFi.localIP());
	// Setup MQTT
	setupMQTT();
  debugln("SETUP end!");
}

void loop() {
  checkMQTTConnection();
  debugln("Temp Sensor");
  tempSensor.requestTemperatures(); 
  float temperatureC = tempSensor.getTempCByIndex(0);
  debug(temperatureC);
  debugln("°C");
  sensor.temp = temperatureC;

  // Serialize the struct to JSON
  const size_t capacity = JSON_OBJECT_SIZE(1);  // Adjust the size as needed
  DynamicJsonDocument jsonDoc(capacity);
  jsonDoc["temperature"] = sensor.temp;

  // Serialize the JSON to a string
  String jsonString;
  serializeJson(jsonDoc, jsonString);
  const char* jsonChar = jsonString.c_str();

  // Publish the JSON message
  publishMessage(jsonChar);
  
  handleMQTTMessages();
  delay(5000);
}

