#include "common.h"
#include "schedule.cpp"
#include "thermostat.h"
#include "JSON.cpp"

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

// Stores LED state
String relayState;

WiFiUDP udp;

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
	WiFi.begin(ssid, password);
	while (WiFi.status() != WL_CONNECTED) {
	delay(1000);
	debugln("Connecting to WiFi..");
	}
	// Print ESP32 Local IP Address
	debugln(WiFi.localIP());

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

	// Set up UDP
	udp.begin(udpServerPort);

	debug("Listening on UDP port: ");
	debugln(udpServerPort);

	DynamicJsonDocument scheduleDoc(1024); // Adjust the size as needed
	JsonArray schedule = scheduleDoc.createNestedArray();

	// Call the function to read JSON data from SPIFFS
	readScheduleFromJson(schedule);
	

	debugln("SETUP end!");
}
void loop() {
    
    int packetSize = udp.parsePacket();
    if (packetSize >= sizeof(struct tempSensor)) {
        Serial.printf("Received %d bytes from %s, port %d\n", packetSize, udp.remoteIP().toString().c_str(), udp.remotePort());

        // Read the data into a tempSensor struct
        struct tempSensor receivedSensor;

        // Manually deserialize the data
        uint8_t buffer[sizeof(struct tempSensor)];
        udp.read(buffer, sizeof(struct tempSensor));

        int offset = 0;
        memcpy(&receivedSensor.temp, &buffer[offset], sizeof(float));
        offset += sizeof(float);
        memcpy(&receivedSensor.name, &buffer[offset], sizeof(receivedSensor.name));
        offset += sizeof(receivedSensor.name);
        memcpy(&receivedSensor.type, &buffer[offset], sizeof(receivedSensor.type));

        // Process the received data
        Serial.printf("Sensor Name: %s\n", receivedSensor.name);
        Serial.printf("Sensor Type: %s\n", receivedSensor.type);
        Serial.printf("Sensor Temperature: %.2f\n", receivedSensor.temp);

        if(receivedSensor.temp > 23.0f)
        {
          digitalWrite(relayPin, HIGH);
        }
        else 
        {
          digitalWrite(relayPin, LOW);
        }
    }
}

