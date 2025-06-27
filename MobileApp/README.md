# NatureSafe-Rail Mobile App

This folder contains the source code for the NatureSafe-Rail mobile application. The app provides a real-time interface for users to monitor the status of animal detector devices deployed along railway tracks and view the proximity of trains to these areas. It is built using **React Native** for cross-platform support (Android and iOS).

---

## Overview

The mobile app is responsible for:
- Displaying the status of animal detector areas (e.g., whether an animal has been detected in a monitored area).
- Showing the distance between the current train (user's device) and each monitored area.
- Providing warning signals if animals are detected near the railway.

---

## Features

- **Area Status Monitoring:** View a live list of animal detector device statuses, including location and whether an animal is currently detected.
- **Distance Calculation:** For each monitored area, see the distance from the current train location (via GPS device data).
- **Visual Warnings:** Receive clear visual cues and warnings for areas where animals have been detected.
- **Automatic Data Refresh:** The app fetches updates from the backend server every second for real-time monitoring.
- **User-Friendly Interface:** Modern, intuitive design for quick status checks and alerts.

---

## Screenshots

<img src="../README-src/app.png" style="height:600px">

---

## Setup

### 1. Install Dependencies

Make sure you have **Node.js** installed. Then:

```bash
npm install -g react-native-cli
cd MobileApp
npm install
```

### 2. Configuring the Server IP

Edit the [`App.js`](./App.js) file and set the IP address of your Flask backend server:

```javascript
const GPS_DEVICE_ID = 0; // Replace with your Train system device ID
const SERVER = "http://YOUR_SERVER_IP"; // Replace with your server IP address
const PORT_ADDRESS = ':5000';           // Default Flask port (change if needed)
```

Ensure your mobile device/emulator and the backend server are on the same Wi-Fi network.

---

### 3. Running the App

- **For Android:**  
  Ensure Android Studio and an emulator or device are set up, then run:
  ```bash
  react-native run-android
  ```

- **For iOS (on macOS):**
  ```bash
  react-native run-ios
  ```

---

## App Structure

- `App.js` – Main application logic: fetches device statuses, calculates distances, and manages UI updates.
- `Device.js` – Renders each animal detector device and its status.
- `assets/` – Contains images and icons used in the app.

---

## How It Works

- The app queries the backend Flask server for:
  - Animal detector device statuses (`/get_animal_detecting_status`)
  - Train GPS device statuses (`/get_gps_status`)
- Calculates the distance between the train and each animal detector area using the Haversine formula.
- Displays a list of all monitored areas, their status (safe/detected), and the distance from the train.
- Provides a prominent warning icon and color when animals are detected.

---

## License

This project is licensed under the MIT License.  
See [LICENSE](../LICENSE) for more information.

---

## Support & Contribution

Feel free to fork the repository and submit pull requests!  
For questions, please open an issue.
