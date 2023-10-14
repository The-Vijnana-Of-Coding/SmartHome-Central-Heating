/*  NOTE: Central Heating Thermostat
    Target: A-Z ESP32 Dev Board
    Author:M.A.R.C

    Version:
        0.1   - Inital project setup
              - Added debugging file.
        0.2   - Added Dual Core Initial Setup
        0.3   - Added LCD Initial Setup
*/
#include <Arduino.h>
#include <Wire.h>

//***** - Local Includes - *****//
#include <core0Tasks.h>
#include <core1Tasks.h>
#include <isDebug.h>
#include <WiFi.h>


const char* ssid = "Girls";
const char* password = "1Scooby23";


//***** - Version Number - *****//
#define ver 0.3

//***** - Core 0 Tasks - *****//
TaskHandle_t menuTask;

//################## - Main Setup Function - ##################//
void setup() {
    //***** - Serial - *****//
    Serial.begin(115200);
    delay(10);
    debugln("*******Beginning Setup*******");
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.println("");

    // Wait for connection
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

    
    Serial.println("HTTP server started");
    // create a task that will be executed in the menuFunctionality() function, with priority 1 and executed on core 0
    xTaskCreatePinnedToCore(
        menuFunctionality,   /* Task function. */
        "menuFunctionality", /* name of task. */
        10000,               /* Stack size of task */
        NULL,                /* parameter of the task */
        1,                   /* priority of the task */
        &menuTask,           /* Task handle to keep track of created task */
        0);                  /* pin task to core 0 */

    debugln("*******Finished Setup*******");
    delay(250);

}
////////////////////////////////////////////////////////////////

//################## - Main Loop Function - ##################//
void loop() {
    // leave empty as using dual core tasks!!
}
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////