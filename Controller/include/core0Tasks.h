#include <Arduino.h>
#include <isDebug.h>
#include <LCD.h>

// NOTE: Add core 0 Tasks here
void menuFunctionality( void * pvParameters ){
    debugln();
    debugln((String) "menuFunctionality TASK running on core: " + xPortGetCoreID());
    debugln();
    initScreen();

    // inifinte loop for core 0
    for(;;){
        delay(5); // release CPU to kick watchdog
        
    }
}