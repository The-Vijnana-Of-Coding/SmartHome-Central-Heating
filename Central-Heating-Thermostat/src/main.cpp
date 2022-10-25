/*  NOTE: Central Heating Thermostat
    Target: A-Z ESP32 Dev Board
    Author:M.A.R.C

    Version:
      0.1   - Inital project setup
            - Added debugging file.
*/
//***** - Version Number - *****//
#define ver 0.1

#include <Arduino.h>

//***** - Local Includes - *****//
#include <isDebug.h>

//################## - Main Setup Function - ##################//
void setup() {
    //***** - Serial - *****//
    Serial.begin(115200);
    delay(10);
    debugln("*******Beginning Setup*******");

    debugln("*******Finished Setup*******");
    delay(250);
}
////////////////////////////////////////////////////////////////

//################## - Main Loop Function - ##################//
void loop() {
}
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////