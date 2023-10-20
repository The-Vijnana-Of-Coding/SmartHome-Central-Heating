#include "common.h"

void printScheduleFile() {
    if (!SPIFFS.begin(true)) {
        debugln("Error mounting SPIFFS");
        return;
    }

    // Open the JSON file for reading
    File file = SPIFFS.open("/schedule.json", "r");
    if (!file) {
        debugln("Error opening file for reading");
        return;
    }

    // Print the file contents to the serial monitor
    while (file.available()) {
        Serial.write(file.read());
    }
    debugln("");
    // Close the file
    file.close();
}

void writeScheduleToJson(JsonArray schedule) {
    if (!SPIFFS.begin(true)) {
        debugln("Error mounting SPIFFS");
        return;
    }

    // Create a JSON document
    DynamicJsonDocument doc(1024); // Adjust the size as needed

    // Assign the provided schedule data to the JSON document
    doc["schedule"] = schedule;

    // Open a file for writing
    File file = SPIFFS.open("/schedule.json", "w");
    if (!file) {
        debugln("Error opening file for writing");
        return;
    }

    // Serialize the JSON document to the file
    if (serializeJson(doc, file) == 0) {
        debugln("Failed to write to file");
    }

    // Close the file
    file.close();
}

void readScheduleFromJson(JsonArray& schedule) {
    if (!SPIFFS.begin(true)) {
        debugln("Error mounting SPIFFS");
        return;
    }

    // Open the JSON file for reading
    File file = SPIFFS.open("/schedule.json", "r");
    if (!file) {
        debugln("Error opening file for reading");
        return;
    }

    // Check if the file is empty
    if (file.size() == 0) {
        // If the file is empty, create a new default schedule
        JsonObject entry1 = schedule.createNestedObject();
        entry1["day"] = 10;
        entry1["month"] = 5;
        entry1["onHour"] = 8;
        entry1["onMinute"] = 30;
        entry1["offHour"] = 12;
        entry1["offMinute"] = 0;

        // Serialize the default schedule and write it to the file
        writeScheduleToJson(schedule);
    } else {
        // The file is not empty, proceed to read and deserialize JSON data
        // Create a JSON document to parse the data
        DynamicJsonDocument doc(1024); // Adjust the size as needed

        // Deserialize the JSON data from the file
        DeserializationError error = deserializeJson(doc, file);

        if (error) {
            debugln("Failed to read JSON data. Error: ");
            debugln(error.c_str());
        } else {
            if (doc.containsKey("schedule")) {
                // Extract schedule data from the JSON document
                schedule = doc["schedule"];
            }
        }

        // Call the function to print the file contents
	    printScheduleFile();
    }

    // Close the file
    file.close();
}


