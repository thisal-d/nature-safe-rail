# NatureSafe Rail

NatureSafe Rail is an integrated IoT-based system designed to enhance railway safety by monitoring animal presence near railway tracks and tracking train locations in real time. The project combines hardware, a backend server, and a mobile application to help prevent wildlife-train collisions and support remote monitoring.

---

## Table of Contents

- [NatureSafe-Rail](#naturesafe-rail)
  - [Table of Contents](#table-of-contents)
  - [Overview](#overview)
  - [System Components](#system-components)
    - [1. Arduino Firmware](#1-arduino-firmware)
    - [2. Server (`/Server`)](#2-server-server)
    - [3. Mobile Application (`/MobileApp`)](#3-mobile-application-mobileapp)
  - [Features](#features)
  - [Architecture](#architecture)
  - [Getting Started](#getting-started)
    - [Server Setup](#server-setup)
    - [Mobile App Setup](#mobile-app-setup)
    - [Arduino Firmware](#arduino-firmware)
  - [API Endpoints](#api-endpoints)
  - [License](#license)
  - [Contributing](#contributing)

---

## Overview

NatureSafe-Rail is composed of:

- **Animal Detector Devices**: IoT devices deployed along railway tracks to detect the presence of animals using sensors.
    - [Animal Detector Firmware ↗](./Arduino/Animal-Ditector-Device/README.md)
- **Train GPS Devices**: IoT devices mounted on trains to provide real-time GPS tracking.
    - [Train GPS Device Firmware ↗](./Arduino/Train-GPS-Device/README.md)
- **Backend Server**: A Flask-based server that collects, processes, and serves data from the devices via a RESTful API.
    - [Server Documentation ↗](./Server/README.md)
- **Mobile Application**: A React Native app for monitoring system data and displaying warnings and area statuses.
    - [Mobile App Documentation ↗](./MobileApp/README.md)

The goal is to provide early warnings to train operators and authorities, reducing the risk of wildlife collisions and supporting sustainable railway operations.

---

## System Components

### 1. Arduino Firmware

- **Animal Detector**: Monitors and reports animal presence and device status to the backend server.  
  [See Animal Detector README](./Arduino/Animal-Ditector-Device/README.md)
- **Train GPS**: Continuously updates the train's GPS coordinates to the server.  
  [See Train GPS Device README](./Arduino/Train-GPS-Device/README.md)

### 2. Server (`/Server`)

- Built with Python (Flask).
- Handles device data, provides RESTful APIs, and supports CORS.
- Stores and processes statuses from both animal detectors and GPS trackers.

  [See Server README](./Server/README.md)

### 3. Mobile Application (`/MobileApp`)

- Built with React Native (cross-platform).
- Provides a dashboard for real-time monitoring.
- Allows users to view the status of animal detector areas and the distance from the train to each area.
- Displays warnings for specific areas if animals are detected.

  [See Mobile App README](./MobileApp/README.md)

---

## Features

- 🦌 **Animal Detection**: Real-time sensing and reporting of animals near tracks.
- 🚄 **Train Tracking**: Real-time GPS tracking of trains.
- 📱 **Mobile Monitoring**: User-friendly mobile app for remote observation and warning display (no water quality or water level).
- 🔌 **RESTful API**: Easy integration and extension via documented endpoints.
- ⚡ **Cross-Platform**: Supports both Android and iOS for mobile access.
- 🔒 **Open Source**: Licensed under MIT.

---

## Architecture

```
+----------------------+       Wi-Fi/HTTP       +---------------------+        Wi-Fi/HTTP        +-----------------------+
|  Animal Detector(s)  |  <------------------>  |   Flask Server      |  <--------------------> |  Mobile Application   |
+----------------------+                       +---------------------+                         +-----------------------+
|  Train GPS Device(s) |  <------------------>  |  (Status API, etc.) |                        |  (React Native)       |
+----------------------+                       +---------------------+                         +-----------------------+
```

---

## Getting Started

### Server Setup

1. Clone the repository:
   ```bash
   git clone https://github.com/Thisal-D/NatureSafe-Rail.git
   cd NatureSafe-Rail/Server
   ```
2. Install dependencies:
   ```bash
   pip install flask flask-cors
   ```
3. Configure server settings in `server.py`:
   ```python
   IP_ADDRESS = "your.server.ip.address"
   PORT = 5000
   ```
4. Run the server:
   ```bash
   python server.py
   ```

### Mobile App Setup

1. Go to the `MobileApp` directory:
   ```bash
   cd ../MobileApp
   ```
2. Install dependencies:
   ```bash
   npm install
   ```
3. Configure the server IP in the `App.js` file:
   ```javascript
   const SERVER = "http://YOUR_SERVER_IP";
   const PORT_ADDRESS = ':5000';
   ```
   Make sure your mobile device/emulator and the server are on the same Wi-Fi network.
4. Run the app:
   - For Android:
     ```bash
     react-native run-android
     ```
   - For iOS (on macOS):
     ```bash
     react-native run-ios
     ```

### Arduino Firmware

- The `/Arduino` directory contains sketches for both Animal Detector and Train GPS devices.
- Configure Wi-Fi credentials and server IP in the `.ino` files before uploading to your hardware.
- [Animal Detector README](./Arduino/Animal-Ditector-Device/README.md)
- [Train Device README](./Arduino/Train-GPS-Device/README.md)

---

## API Endpoints

The Flask server exposes endpoints for:

- **Animal Detector**
  - `POST /update_animal_detector_device_status`  
    Update status from a detector device.
  - `GET /get_animal_detecting_status`  
    Retrieve all animal detector statuses.

- **Train GPS**
  - `POST /update_train_gps_device_status`  
    Update GPS status from a train device.
  - `GET /get_gps_status`  
    Retrieve all train GPS statuses.

See [Server/README.md](./Server/README.md) for detailed API documentation and data formats.

---

## License

This project is licensed under the [MIT License](LICENSE).

---

## Contributing

1. Fork the project.
2. Create your feature branch (`git checkout -b feature/amazing-feature`).
3. Commit your changes (`git commit -m 'Add some amazing feature'`).
4. Push to the branch (`git push origin feature/amazing-feature`).
5. Open a Pull Request.
