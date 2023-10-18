#include "common.h"
#include "schedule.cpp"

void setup() {
  debugln("SETUP begin!");
  
  debugln("Start Serial Monitor");
  // Start the Serial Monitor
  Serial.begin(115200);

  
  debugln("SETUP end!");
}

void loop() {
    // put your main code here, to run repeatedly:
    programSchedule mySchedule(10, 5); // Example day and month
    mySchedule.addOnOffTime(8, 12, 0, 30);
    mySchedule.addOnOffTime(24, 16, 15, 45);
    mySchedule.addOnOffTime(14, 16, 15, 45);
    mySchedule.addOnOffTime(14, 75, 15, 45);

    // Sort the schedule by onHr
    mySchedule.sortScheduleByOnHr();

    // Retrieve and print the sorted schedule
    for (size_t i = 0; i < mySchedule.getScheduleSize(); i++) {
        auto time = mySchedule.getOnOffTime(i);
        debug("On ");
        debug(time.onHr);
        debug(":");
        debug(time.onMin);
        debugln(" ");
        debug("Off ");
        debug(time.onHr);
        debug(":");
        debug(time.offMin);
        debugln();
    }

    delay(10000);
}

