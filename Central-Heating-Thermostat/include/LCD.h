#include <ArduinoOTA.h>
#include <LiquidCrystal.h>

//***** - 4Bit LCD - *****//
LiquidCrystal screen(13, 12, 14, 27, 26, 25);

String onBootL1 = "System Loading";

byte screenWidth = 16;


//#####  Center Display Text Function  ######//
int center_Text(int lengthOfString) {
    int position;
    position = floor((screenWidth - lengthOfString) / 2);
    return position;
}
/////////////////////////////////////////////////////

//#####  Clear Display By Line Function  ######//
void clearScreenLine(int line) {               
    screen.setCursor(0,line);
    for(int n = 0; n < screenWidth; n++) {
        screen.print(" ");
    }
}
/////////////////////////////////////////////////////

//#####  Screen Setup Function  ######//
void initScreen() {
   // Initialize The LCD. Parameters: [ Columns, Rows ]
  screen.begin(16, 2);
  delay(500);
  screen.clear();
  // Display Duvine Text to the LCD Display
  screen.setCursor(center_Text(onBootL1.length()),0);
  screen.print(onBootL1);
}
/////////////////////////////////////////////////////
