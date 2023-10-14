#include "common.h"

#include <OneWire.h>
#include <DallasTemperature.h>


// Setup a oneWire instance to communicate with any OneWire devices
OneWire tempSensorOneWire(tempSensorPin);

// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature tempSensor(&tempSensorOneWire);


void setup() {
  debugln("SETUP begin!");
  
  // Start the Serial Monitor
  Serial.begin(115200);

  // ## Temp Sensor Setup ## //
  // Start the DS18B20 sensor
  tempSensor.begin();

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