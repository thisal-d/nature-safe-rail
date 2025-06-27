# Train GPS Device

This folder contains the Arduino firmware for the **Train GPS Device** used in the NatureSafe-Rail system. This device is installed on trains to provide real-time location updates to the NatureSafe-Rail backend server, enabling live monitoring of train positions in relation to animal detector zones.

---

## Overview

- **Purpose:**  
  Continuously track the train's GPS location and report it to the backend server over Wi-Fi.
- **Platform:**  
  Arduino-compatible board with Wi-Fi (e.g., ESP32) and a GPS module (e.g., NEO-6M).

---

## How It Works

1. **GPS Acquisition:**  
   The device reads GPS coordinates (latitude and longitude) from a connected GPS module.
2. **Wi-Fi Connectivity:**  
   Connects to the specified Wi-Fi network for internet access.
3. **Data Packaging:**  
   Periodically (or on schedule), the device prepares a JSON payload with:
   - `device_id`: Unique ID for each train device.
   - `latitude` and `longitude`: Current GPS coordinates.
4. **Data Transmission:**  
   Sends the data as an HTTP POST request to the server endpoint `/update_train_gps_device_status`.
5. **Server Response:**  
   Response is printed to the serial monitor for debugging.

---

## Key Code Snippet

```cpp
void sendStatus(){
  HTTPClient http;
  http.begin(SERVER + "/update_train_gps_device_status");
  http.addHeader("Content-Type", "application/json");

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
}
```

---

## Configuration

- **Wi-Fi Credentials:**  
  Set your Wi-Fi SSID and password in the source code.
- **Server IP:**  
  Update the `SERVER` constant with the IP address and port of your backend server.
- **Device Information:**  
  Set a unique `DEVICE_ID` for each train device.

---

## Dependencies

- [ESP32/ESP8266 Arduino Core](https://github.com/espressif/arduino-esp32)
- [TinyGPS++](https://github.com/mikalhart/TinyGPSPlus)
- [HTTPClient](https://www.arduino.cc/en/Reference/HTTPClient)
- [ArduinoJson](https://arduinojson.org/)

---

## Deployment

1. Edit configuration values (Wi-Fi, server IP, device ID) in `main.ino`.
2. Install the required libraries via Arduino Library Manager.
3. Connect the GPS module to your board (TX/RX pins).
4. Upload `main.ino` to your device.
5. Monitor the serial output for status and debug information.

---

## Integration

- The server endpoint for status updates:  
  `POST /update_train_gps_device_status`
- Data format (JSON):
  ```json
  {
    "device_id": "1",
    "latitude": "6.9271",
    "longitude": "79.8612"
  }
  ```

---

## License

This project is licensed under the MIT License.

---