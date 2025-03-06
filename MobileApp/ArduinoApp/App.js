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

const SERVER = "http://xxx.xxx.xxx.xxx";
const PORT_ADDRESS = ':5000';
const SERVER_URL = SERVER + PORT_ADDRESS;

export default function App() {
  const [devices, setDevices] = useState([
    {
      "device_id": "D001",
      "location": "Anuradhapura",
      "is_animal_detected": false
    },
    {
      "device_id": "D002",
      "location": "Polonnaruwa",
      "is_animal_detected": false
    },
    {
      "device_id": "D003",
      "location": "Ampara",
      "is_animal_detected": false
    }, {
      "device_id": "D004",
      "location": "asdfgh",
      "is_animal_detected": false
    },
  ]);

  const [serverConnectionStatus, setServerConnectionStatus] = useState(null);

  const fetchWithTimeout = (url, options, timeout = 2000) => {
    return Promise.race([
      fetch(url, options),
      new Promise((_, reject) => setTimeout(() => reject(new Error("Request timed out")), timeout))
    ]);
  };

  const fetchStatus = async () => {
    try {
      const response = await fetchWithTimeout(`${SERVER_URL}/get_status`);
      const data = await response.json();
      setDevices(data);
      setServerConnectionStatus(true);
    } catch (error) {
      setServerConnectionStatus(false);
    }
  };

  useEffect(() => {
    const interval = setInterval(() => {
      fetchStatus();
    }, 1000);
    return () => clearInterval(interval);
  }, []);

  return (
    <View style={styles.container}>
      {/* Top Image */}
      <View>
        <ImageBackground source={require('./assets/bg1.jpeg')} style={styles.topBgImage} >
          <Text style={styles.appTitle}>Animal Ditector</Text>
        </ImageBackground>
      </View>

      {/* Bottom Background with Devices */}
      <ImageBackground 
        source={require('./assets/bg2.jpg')} 
        style={styles.bottomBgImage}
      >
        <View style={styles.overlay}>
          {devices.filter( 
            (device) => device.is_animal_detected
          ).map((device, index) => (
            <Device 
              key={device.device_id}
              deviceID={device.device_id}
              isAnimalDetected={device.is_animal_detected}
              location={device.location}
              Distance={"10km"}
            />
          ))}

          {devices.filter( 
            (device) => !device.is_animal_detected
          ).map((device, index) => (
            <Device 
              key={device.device_id}
              deviceID={device.device_id}
              isAnimalDetected={device.is_animal_detected}
              location={device.location}
              Distance={"10km"}
            />
          ))}
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
    paddingHorizontal: 20, // Adjust for better text wrapping
    color: 'white',
    alignSelf: 'center', // Centers the title and shrinks background to fit
  },
  topBgImage: {
    width: '100%',
    height: 250, // Set a fixed height for the first image
  },
  bottomBgImage: {
    flex: 1, // Makes sure it fills the rest of the screen
    resizeMode: 'cover',
    width: '100%',
  },
  overlay: {
    alignItems: 'center',
  },

});
