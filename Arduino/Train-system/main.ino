#include <HardwareSerial.h>
#include <TinyGPS++.h>

static const int RXPin = 16, TXPin = 17;  // GPS TX → ESP32 RX (16), GPS RX → ESP32 TX (17)
static const uint32_t GPSBaud = 9600;     // Default NEO-6M baud rate

HardwareSerial gpsSerial(2);  // Use UART2 for GPS
TinyGPSPlus gps;

void setup() {
    Serial.begin(115200);  
    gpsSerial.begin(GPSBaud, SERIAL_8N1, RXPin, TXPin);  
    Serial.println("Waiting for GPS signal...");
}

void loop() {
    while (gpsSerial.available()) {  // Read GPS data if available
        gps.encode(gpsSerial.read());
    }
    Serial.println("Conencted");
    Serial.print("Latitude: ");
    Serial.print(gps.location.lat(), 6);
    Serial.print(" | Longitude: ");
    Serial.println(gps.location.lng(), 6);

    if (gps.location.isValid()) {  // Check if GPS has a valid fix
        Serial.print("Latitude: ");
        Serial.print(gps.location.lat(), 6);
        Serial.print(" | Longitude: ");
        Serial.println(gps.location.lng(), 6);
    } else {
        Serial.println("No valid GPS fix! Waiting...");
    }

    delay(1000);  // Update every second
}
