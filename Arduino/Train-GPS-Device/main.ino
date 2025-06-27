#include <HardwareSerial.h>
#include <TinyGPS++.h>
#include <WiFi.h> // Header for handle wifi
#include <HTTPClient.h> // Handle HTTP Requests
#include <ArduinoJson.h> // Convert String to Json object

// CONFIGURE DEVICE INFO
const int DEVICE_ID = 2;
double LATITUDE = 0;
double LONGITUDE = 0;

const String SERVER = "http://xxx.xxx.xxx.xxx:5000";

// WIFI INFO
const char* SSID = "SSID";
const char* PASSWORD = "********";

// Pins for GPS module
const int RXPin = 16, TXPin = 17;  // GPS TX → ESP32 RX (16), GPS RX → ESP32 TX (17)
const uint32_t GPSBaud = 9600;     // Default NEO-6M baud rate

const int LED_PIN = 32;

// GPS module start
HardwareSerial gpsSerial(2);  // Use UART2 for GPS
TinyGPSPlus gps;

// SERVER INFO

void sendStatus(){
  // Create HTTP Object
  HTTPClient http;
  http.begin(SERVER+"/update_train_gps_device_status");
  http.addHeader("Content-Type", "application/json");

  // Create json object
  String payLoad = "{\"device_id\":\"" + String(DEVICE_ID) + "\","
              + "\"latitude\":\"" + String(LATITUDE, 6) + "\","
              + "\"longitude\":\"" + String(LONGITUDE, 6) + "\"}";

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
  gpsSerial.begin(GPSBaud, SERIAL_8N1, RXPin, TXPin);  
  Serial.println("Waiting for GPS signal...");

  // Configure lLED
  pinMode(LED_PIN, OUTPUT);
  
  // Connecting to WIFI
  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("WIFI : Connecting...");
    delay(1000);
  }
  Serial.println("WIFI : Connected !");
}

void loop() {
  // Check if gps available
  while (gpsSerial.available()) {  // Read GPS data if available
      gps.encode(gpsSerial.read());
  }
  Serial.println("GPS connected...!");

  // Get latitude and longitude
  LATITUDE = gps.location.lat();
  LONGITUDE = gps.location.lng();

  // Power LED if gps connected
  if (!(LATITUDE == 0.000000 && LONGITUDE == 0.000000)){
    digitalWrite(LED_PIN, HIGH);
  }
  else{
    digitalWrite(LED_PIN, LOW);
  }
  
  // Send data to server
  sendStatus();

  // Print Lat and ng  
  Serial.print("Latitude: ");
  Serial.print(LATITUDE, 6);
  Serial.print(" | Longitude: ");
  Serial.println(LONGITUDE, 6);
  
  delay(1000);  // Update every second
}
