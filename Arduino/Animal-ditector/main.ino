#include <WiFi.h> // Header for handle wifi
#include <HTTPClient.h> // Handle HTTP Requests
#include <ArduinoJson.h> // Convert String to Json object

// CONFIGURE DEVICE INFO
const int DEVICE_ID = 2;
const String LOCATION = "Anuradhapura";
const double LATITUDE = 6.925569;
const double LONGITUDE = 79.967356;

// WIFI INFO
const char* SSID = "Redmi Note 11";
const char* PASSWORD = "123456789";

// SERVER INFO
const String SERVER = "http://192.168.34.185:5000";

// Pins
const int pressureSensorPin = 34;

// Animal detection status
bool is_animal_detected = false;
long long int animal_detected_for = 0;


void sendStatus(){
  // Create HTTP Object
  HTTPClient http;
  http.begin(SERVER+"/update_status");
  http.addHeader("Content-Type", "application/json");

  String payLoad = "{\"device_id\":\"" + String(DEVICE_ID) + "\","
              + "\"location\":\"" + String(LOCATION) + "\","
              + "\"latitude\":\"" + String(LATITUDE) + "\","
              + "\"longitude\":\"" + String(LONGITUDE) + "\","
              + "\"is_animal_detected\":\"" + String(is_animal_detected) + "\"}";

  int httpResponseCode = http.POST(payLoad);

  if (httpResponseCode > 0) {
    String response = http.getString();
    Serial.println("Status Update Response Code: " + String(httpResponseCode));
    Serial.println(response);
  } else {
    Serial.print("Error on sending POST: ");
    Serial.println(httpResponseCode);
  }
  http.end();
};


void setup() {
  Serial.begin(115200);  
  pinMode(pressureSensorPin, INPUT);


  // Connecting to WIFI
  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("WIFI : Connecting...");
    delay(1000);
  }
  Serial.println("WIFI : Connected !");
}

void loop() {
  // Read sensor
  int pressure = analogRead(pressureSensorPin);
  Serial.print("Pressure : ");
  Serial.println(pressure);
  int mapped_pressure = map(pressure, 4095, 0, 0, 100); // Map pressure 0 to 100
  Serial.print("Pressure (Mapped) : ");
  Serial.println(mapped_pressure);

  // If pressure more than 40% then it mean there is an animal
  if (mapped_pressure > 40){
    is_animal_detected = true;
    animal_detected_for ++;
  }
  else {
    is_animal_detected = false;
    animal_detected_for = 0;
  }

  // Send data to server
  sendStatus();
  
  delay(1000);  // Update every second
}
