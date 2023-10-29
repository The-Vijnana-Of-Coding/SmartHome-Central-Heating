#ifndef HANDLE_MQTT_H
#define HANDLE_MQTT_H

#include <ArduinoJson.h>
#include <Arduino.h>
#include "thermostat.h"
#include "common.h"

extern void publishMessage(const char* topic,const char* message);

void checkTemp(float temp)
{
    if(temp > 23.0)
    {
        if(digitalRead(relayPin))
        {
            debugln("Relay Already ON!");
        }
        else
        {
            digitalWrite(relayPin, HIGH);
            debugln("Switching Relay ON!");
        }
    } 
    else
    {
        if(!digitalRead(relayPin))
        {
            debugln("Relay Already OFF!");
        }
        else
        {
            digitalWrite(relayPin, LOW);
            debugln("Switching Relay OFF!");
        }
    }
}

void handleMQTT(const char* topic, const char* message)
{
  DynamicJsonDocument jsonDoc(256); // Adjust the buffer size as needed
  DeserializationError error = deserializeJson(jsonDoc, message);

  if (error)
  {
    Serial.print("Failed to parse JSON: ");
    Serial.println(error.c_str());
  }
  else
  {
    if (strcmp(topic, sub_temp) == 0)
    {
      float temperature = jsonDoc["temperature"];
      Serial.print("Received temperature: ");
      Serial.println(temperature);
      checkTemp(temperature);
    }
    else if (strcmp(topic, sub_override_set) == 0)
    {
      if(jsonDoc["chstate"] == "ON")
      {
        if(digitalRead(relayPin))
        {
            debugln("Relay Already ON!");
        }
        else
        {
            digitalWrite(relayPin, HIGH);
            debugln("Switching Relay ON!");
        }
      } 
      else
      {
        if(!digitalRead(relayPin))
        {
            debugln("Relay Already OFF!");
        }
        else
        {
            digitalWrite(relayPin, LOW);
            debugln("Switching Relay OFF!");
        }
      }
    }
    else
    {
      Serial.println("JSON message lacks 'temperature' field.");
    }
  }
}



#endif