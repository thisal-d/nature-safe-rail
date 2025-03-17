import React, { useState, useEffect } from 'react';
import { 
  StyleSheet,
  Text, 
  View, 
  ScrollView,
  Image,
  ImageBackground
} from 'react-native';
import Device from './Device';

// Configure device
const GPS_DEVICE_ID = 2;
const SERVER = "http://192.168.39.185";
const PORT_ADDRESS = ':5000';
const SERVER_URL = SERVER + PORT_ADDRESS;

// Haversine formula for distance calculation
const toRadians = (degrees) => degrees * (Math.PI / 180);
const haversine = (lat1, lon1, lat2, lon2) => {
    const R = 6371; // Earth radius in km
    const dLat = toRadians(lat2 - lat1);
    const dLon = toRadians(lon2 - lon1);
    const a = Math.sin(dLat / 2) ** 2 + 
              Math.cos(toRadians(lat1)) * Math.cos(toRadians(lat2)) * 
              Math.sin(dLon / 2) ** 2;
    const c = 2 * Math.atan2(Math.sqrt(a), Math.sqrt(1 - a));
    return R * c * 1000; // Distance in km
};

export default function App() {
  const [animalDetectingDevices, setAnimalDetectingDevices] = useState([]);
  const [gpsDevices, setGpsDevices] = useState([]);
  const [serverConnectionStatus, setServerConnectionStatus] = useState(null);

  // Fetch data with timeout
  const fetchWithTimeout = (url, options, timeout = 2000) => {
    return Promise.race([
      fetch(url, options),
      new Promise((_, reject) => setTimeout(() => reject(new Error("Request timed out")), timeout))
    ]);
  };

  // Get data from Flask server
  const fetchStatus = async () => {
    try {
      // Get animal detecting device data
      const animalResponse = await fetchWithTimeout(`${SERVER_URL}/get_animal_detecting_status`);
      const animalData = await animalResponse.json();
      // console.log(animalData);
      setAnimalDetectingDevices(animalData);

      // Get gps device data
      const gpsResponse = await fetchWithTimeout(`${SERVER_URL}/get_gps_status`);
      const gpsData = await gpsResponse.json();
      // console.log(gpsData);
      setGpsDevices(gpsData);

    } catch (error) {
      console.log(error);
    }
  };

  // Call fetchStatus every seconds
  useEffect(() => {
    const interval = setInterval(() => {
      fetchStatus();
    }, 1000);
    return () => clearInterval(interval);
  }, []);

  // Get the GPS device assigned to the phone
  const myGpsDevice = gpsDevices.find(device => device.device_id === GPS_DEVICE_ID);

  return (
    <View style={styles.container}>
      {/* Top Image */}
      <View>
        <ImageBackground source={require('./assets/bg1.jpeg')} style={styles.topBgImage} >
          <Text style={styles.appTitle}>Animal Detector</Text>
        </ImageBackground>
      </View>

      {/* Bottom Background with Devices */}
      <ImageBackground 
        source={require('./assets/bg2.jpg')} 
        style={styles.bottomBgImage}
      >
        <View style={styles.overlay}>
          {animalDetectingDevices.map((device) => {
            let distance = "Unknown";
            if (myGpsDevice) {
              distance = haversine(
                myGpsDevice.latitude, myGpsDevice.longitude, 
                device.latitude, device.longitude
              ).toFixed(2) + " m";
            }
            return (
              <Device 
                key={device.device_id}
                deviceID={device.device_id}
                isAnimalDetected={device.is_animal_detected}
                location={device.location}
                Distance={distance}
                ActiveTime={device.active_time}
              />
            );
          })}
        </View>
      </ImageBackground>
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
  },
  appTitle: {
    fontSize: 38,
    marginTop: 120,
    textAlign: 'center',
    fontWeight: 'bold',
    backgroundColor: 'rgba(0,0,0,0.3)',
    borderRadius: 10,
    paddingVertical: 8, 
    paddingHorizontal: 20, 
    color: 'white',
    alignSelf: 'center',
  },
  topBgImage: {
    width: '100%',
    height: 250, 
  },
  bottomBgImage: {
    flex: 1, 
    resizeMode: 'cover',
    width: '100%',
  },
  overlay: {
    alignItems: 'center',
  },
});
