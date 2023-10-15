#include <OneWire.h>
#include <DallasTemperature.h>
#include "common.h"
#include <PubSubClient.h>
#include <WiFi.h>

WiFiUDP udp;

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

  debugln("SETUP end!");
}

void loop() {
  debugln("Temp Sensor");
  tempSensor.requestTemperatures(); 
  float temperatureC = tempSensor.getTempCByIndex(0);
  debug(temperatureC);
  debugln("°C");

  // Send a UDP broadcast message to all devices on the same network
  udp.beginPacket(IPAddress(255, 255, 255, 255), udpServerPort);
  udp.print("Broadcast message");
  udp.endPacket();

  Serial.println("Broadcast message sent via UDP");

  delay(5000);
}