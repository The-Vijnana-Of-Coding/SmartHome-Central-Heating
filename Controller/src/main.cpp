#include "common.h"
#include "schedule.cpp"
#include "thermostat.h"
#include "JSON.cpp"
#include "mqtt.h"

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

// Stores LED state
String relayState;

// Replaces placeholder with LED state value
String processor(const String& var){
  debugln(var);
  if(var == "STATE"){
    if(digitalRead(relayPin)){
      relayState = "ON";
    }
    else{
      relayState = "OFF";
    }
    debugln("Relay: " + relayState);
    return relayState;
  }
  return String();
}

void setup() {
	delay(2000);
	pinMode(relayPin, OUTPUT);

	// Start the Serial Monitor
	Serial.begin(115200);
	debugln("SETUP begin!");

	// Mount the filesystem
	if (!SPIFFS.begin(true)) {
	debugln("An error occurred while mounting the filesystem.");
	return;
	}
	File file = SPIFFS.open("/index.html");
	if(!file){
	debugln("Failed to open file for reading");
	return;
	}

	// Connect to Wi-Fi
	setupWiFi();
	// Print ESP32 Local IP Address
	debugln(WiFi.localIP());
	// Setup MQTT
	setupMQTT();
	subscribeToTopic(sub_temp);  // Subscribe to the topic you want to receive messages from

	// Route for root / web page
	server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
	request->send(SPIFFS, "/index.html", String(), false, processor);
	});

	// Route to set GPIO to HIGH
	server.on("/on", HTTP_GET, [](AsyncWebServerRequest *request){
	digitalWrite(relayPin, HIGH);    
	request->send(SPIFFS, "/index.html", String(), false, processor);
	});

	// Route to set GPIO to LOW
	server.on("/off", HTTP_GET, [](AsyncWebServerRequest *request){
	digitalWrite(relayPin, LOW);    
	request->send(SPIFFS, "/index.html", String(), false, processor);
	});
	// Start server
	server.begin();

	DynamicJsonDocument scheduleDoc(1024); // Adjust the size as needed
	JsonArray schedule = scheduleDoc.createNestedArray();

	// Call the function to read JSON data from SPIFFS
	readScheduleFromJson(schedule);
	
	debugln("SETUP end!");
}
void loop() {
	checkMQTTConnection();
	handleMQTTMessages();  // Add this line to check for incoming messages
}

