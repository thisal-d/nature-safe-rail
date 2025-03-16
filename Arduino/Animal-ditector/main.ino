#include <WiFi.h> // Header for handle wifi
#include <HTTPClient.h> // Handle HTTP Requests
#include <ArduinoJson.h> // Convert String to Json object

// CONFIGURE DEVICE INFO
const int DEVICE_ID = 2;
const String LOCATION = "Anuradhapura";
const double LATITUDE = 8.33183050;
const double LONGITUDE = 80.40290170;

// WIFI INFO
const char* SSID = "SSID";
const char* PASSWORD = "********";

// SERVER INFO
const String SERVER = "http://xxx.xxx.xxx.xxx:5000";

// Pins
const int PRESSURE_SENSOR_PIN = 34;
const int BUZZER_PIN = 32;

// Animal detection status
bool is_animal_detected = false;
long long int active_time = 0;


void sendStatus(){
  // Create HTTP Object
  HTTPClient http;
  http.begin(SERVER+"/update_animal_detector_device_status");
  http.addHeader("Content-Type", "application/json");

  // Create Json obj
  String payLoad = "{\"device_id\":\"" + String(DEVICE_ID) + "\","
              + "\"location\":\"" + String(LOCATION) + "\","
              + "\"latitude\":\"" + String(LATITUDE, 6) + "\","
              + "\"longitude\":\"" + String(LONGITUDE, 6) + "\","
              + "\"active_time\":\"" + String(active_time) + "\","
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
  
  // Configure pins
  pinMode(PRESSURE_SENSOR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);


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
  int pressure = analogRead(PRESSURE_SENSOR_PIN);
  Serial.print("Pressure : ");
  Serial.println(pressure);
  // Map value to 0 to 100
  int mapped_pressure = map(pressure, 4095, 0, 0, 100); // Map pressure 0 to 100
  Serial.print("Pressure (Mapped) : ");
  Serial.println(mapped_pressure);

  // If pressure more than 40% then it mean there is an animal
  if (mapped_pressure > 40){
    is_animal_detected = true;
    active_time ++;
    digitalWrite(BUZZER_PIN, HIGH);
  }
  else {
    is_animal_detected = false;
    active_time = 0;
    digitalWrite(BUZZER_PIN, LOW);
  }

  // Send data to server
  sendStatus();
  
  delay(1000);  // Update every second
}
