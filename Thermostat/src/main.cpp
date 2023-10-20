#include <OneWire.h>
#include <DallasTemperature.h>
#include "common.h"
#include <PubSubClient.h>
#include <WiFi.h>
#include "thermostat.cpp"

WiFiUDP udp;

// Setup a oneWire instance to communicate with any OneWire devices
OneWire tempSensorOneWire(tempSensorPin);

// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature tempSensor(&tempSensorOneWire);

void setup_wifi() {
  delay(10);
  debugln("Connecting to WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    debugln("Connecting to WiFi...");
  }
  debugln("Connected to WiFi");
  // Print ESP32 Local IP Address
  debugln(WiFi.localIP());
}


void setup() {
  
  // Start the Serial Monitor
  Serial.begin(115200);
  debugln("SETUP begin!");
  
  debugln("Start Serial Monitor");  

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
  sensor.temp = temperatureC;
  uint8_t buffer[sizeof(struct tempSensor)];
  memcpy(buffer, &sensor, sizeof(sensor));
  // Send a UDP broadcast message to all devices on the same network
  udp.beginPacket(IPAddress(255, 255, 255, 255), udpServerPort);
  udp.write(buffer, sizeof(sensor));
  udp.endPacket();
  debugln("Broadcast message sent via UDP");
  delay(5000);
}