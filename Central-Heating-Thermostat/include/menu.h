/*  NOTE: Menu System for Programmer
    Target: ESP8266
    Author: Mark Caton
*/

#include <Arduino.h>

//***** - Menu Root Line 1 Text - *****//
String menuRootL1L1 = "Smart-Programmer";
String menuRootL2L1 = "Central-Heating";
String menuRootL3L1 = "Hot-Water";
String menuRootL4L1 = "Settings";
//***** - Menu Root Line 2 Text - *****//
String menuRootL1L2 = "System-Online";
String menuRootL2L2 = "Press Enter";
String menuRootL3L2 = "Press Enter";
String menuRootL4L2 = "Press Enter";
//***** - Menu Root Line 1 Array - *****//
String menuRootLine1[4] = {
    menuRootL1L1,
    menuRootL2L1,
    menuRootL3L1,
    menuRootL4L1};
//***** - Menu Root Line 2 Array - *****//
String menuRootLine2[4] = {
    menuRootL1L2,
    menuRootL2L2,
    menuRootL3L2,
    menuRootL4L2};
//***** - Menu Root Position - *****//
unsigned int menuLevel1Posistion = 1, menuLevel2Posistion = 0, menuLevel3Posistion = 0, enuLevel4Posistion = 0;