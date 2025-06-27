# Animal Detector Firmware

This folder contains the Arduino firmware for the **Animal Detector** device, a key hardware component of the NatureSafe-Rail system. The Animal Detector is designed to monitor for wildlife presence near railway tracks and report its status to the NatureSafe-Rail backend server in real time.

---

## Overview

- **Purpose:**  
  Detect animals near railway tracks using sensors and transmit detection status, location, and operational time to the Flask backend server.
- **Platform:**  
  Arduino-compatible microcontroller (e.g., ESP32/ESP8266) with Wi-Fi capability.

---

## How It Works

1. **Sensing:**  
   The device continuously monitors for animal presence using connected sensors (sensor integration code to be added as per your hardware).
2. **Data Packaging:**  
   When a detection event occurs (or at regular intervals), the device prepares a JSON payload containing:
   - `device_id`: Unique ID of the device.
   - `location`: Name/description of the geographic location.
   - `latitude` & `longitude`: GPS coordinates.
   - `active_time`: Duration the device has been operational (in seconds).
   - `is_animal_detected`: Whether an animal is detected (1) or not (0).
3. **Data Transmission:**  
   The device connects to the Wi-Fi network and sends an HTTP POST request to the server endpoint `/update_animal_detector_device_status`.
4. **Server Response:**  
   The firmware prints the server's response to the serial console for debugging.

---

## Key Code Snippet

```cpp
void sendStatus(){
  HTTPClient http;
  http.begin(SERVER+"/update_animal_detector_device_status");
  http.addHeader("Content-Type", "application/json");

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
}
```

---

## Configuration

- **Wi-Fi Credentials:**  
  Set your Wi-Fi SSID and password in the source code.
- **Device Information:**  
  Replace `DEVICE_ID`, `LOCATION`, `LATITUDE`, and `LONGITUDE` with values specific to the deployment site.
- **Server IP:**  
  Update the `SERVER` constant with the IP address and port of your backend Flask server.

---

## Dependencies

- [ESP32/ESP8266 Arduino Core](https://github.com/espressif/arduino-esp32)
- [ArduinoJson](https://arduinojson.org/)
- [HTTPClient](https://www.arduino.cc/en/Reference/HTTPClient)
- (Optional) GPS sensor library if GPS is used for location.

---

## Deployment

1. Edit configuration values in `main.ino`.
2. Install required libraries via Arduino Library Manager.
3. Connect your device via USB.
4. Upload `main.ino` to your device.
5. Monitor the serial output for status and debug information.

---

## Integration

- The server endpoint for status updates:  
  `POST /update_animal_detector_device_status`
- Data format (JSON):
  ```json
  {
    "device_id": "3",
    "is_animal_detected": "1",
    "latitude": "6.4169744",
    "longitude": "81.3353611",
    "location": "Katharagama",
    "active_time": "120"
  }
  ```

